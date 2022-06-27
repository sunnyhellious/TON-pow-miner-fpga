/*
    This file is part of TON Blockchain Library.

    TON Blockchain Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    TON Blockchain Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with TON Blockchain Library.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2017-2020 Telegram Systems LLP
*/
#include "state-serializer.hpp"
#include "td/utils/Random.h"
#include "adnl/utils.hpp"
#include "ton/ton-io.hpp"
#include "common/delay.h"

namespace ton {

namespace validator {

void AsyncStateSerializer::start_up() {
  alarm_timestamp() = td::Timestamp::in(1.0 + td::Random::fast(0, 10) * 1.0);
  running_ = true;

  //next_iteration();
  auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<AsyncSerializerState> R) {
    R.ensure();
    td::actor::send_closure(SelfId, &AsyncStateSerializer::got_self_state, R.move_as_ok());
  });
  td::actor::send_closure(manager_, &ValidatorManager::get_async_serializer_state, std::move(P));
}

void AsyncStateSerializer::got_self_state(AsyncSerializerState state) {
  if (state.last_block_id.is_valid()) {
    last_block_id_ = state.last_block_id;
    last_key_block_id_ = state.last_written_block_id;
    last_key_block_ts_ = state.last_written_block_ts;

    running_ = false;

    next_iteration();
  } else {
    auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<BlockHandle> R) {
      R.ensure();
      td::actor::send_closure(SelfId, &AsyncStateSerializer::got_init_handle, R.move_as_ok());
    });
    td::actor::send_closure(manager_, &ValidatorManager::get_block_handle, last_block_id_, true, std::move(P));
  }
}

void AsyncStateSerializer::got_init_handle(BlockHandle handle) {
  CHECK(handle->id().id.seqno == 0 || handle->is_key_block());
  last_key_block_id_ = handle->id();
  last_key_block_ts_ = handle->unix_time();

  masterchain_handle_ = std::move(handle);

  running_ = false;
  saved_to_db_ = false;

  next_iteration();
}

void AsyncStateSerializer::alarm() {
  alarm_timestamp() = td::Timestamp::in(1.0 + td::Random::fast(0, 10) * 1.0);

  next_iteration();

  auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<BlockIdExt> R) {
    R.ensure();
    td::actor::send_closure(SelfId, &AsyncStateSerializer::got_top_masterchain_handle, R.move_as_ok());
  });
  td::actor::send_closure(manager_, &ValidatorManager::get_top_masterchain_block, std::move(P));
}

void AsyncStateSerializer::next_iteration() {
  if (running_) {
    return;
  }
  if (!masterchain_handle_) {
    running_ = true;
    auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<BlockHandle> R) {
      R.ensure();
      td::actor::send_closure(SelfId, &AsyncStateSerializer::got_masterchain_handle, R.move_as_ok());
    });
    td::actor::send_closure(manager_, &ValidatorManager::get_block_handle, last_block_id_, true, std::move(P));
    return;
  }
  if (!masterchain_handle_->inited_unix_time() || !masterchain_handle_->inited_is_key_block() ||
      !masterchain_handle_->is_applied()) {
    return;
  }
  CHECK(masterchain_handle_->id() == last_block_id_);
  if (attempt_ < max_attempt() && last_key_block_id_.id.seqno < last_block_id_.id.seqno &&
      need_serialize(masterchain_handle_)) {
    if (masterchain_state_.is_null()) {
      running_ = true;
      auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<td::Ref<ShardState>> R) {
        if (R.is_error()) {
          td::actor::send_closure(SelfId, &AsyncStateSerializer::fail_handler,
                                  R.move_as_error_prefix("failed to get masterchain state: "));
        } else {
          td::actor::send_closure(SelfId, &AsyncStateSerializer::got_masterchain_state,
                                  td::Ref<MasterchainState>(R.move_as_ok()));
        }
      });
      td::actor::send_closure(manager_, &ValidatorManager::get_shard_state_from_db, masterchain_handle_, std::move(P));
      return;
    }
    while (next_idx_ < shards_.size()) {
      if (!need_monitor(shards_[next_idx_].shard_full())) {
        next_idx_++;
      } else {
        running_ = true;
        auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<BlockHandle> R) {
          R.ensure();
          td::actor::send_closure(SelfId, &AsyncStateSerializer::got_shard_handle, R.move_as_ok());
        });
        td::actor::send_closure(manager_, &ValidatorManager::get_block_handle, shards_[next_idx_], true, std::move(P));
        return;
      }
    }
    last_key_block_ts_ = masterchain_handle_->unix_time();
    last_key_block_id_ = masterchain_handle_->id();
  }
  if (!saved_to_db_) {
    running_ = true;
    auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<td::Unit> R) {
      R.ensure();
      td::actor::send_closure(SelfId, &AsyncStateSerializer::saved_to_db);
    });
    td::actor::send_closure(manager_, &ValidatorManager::update_async_serializer_state,
                            AsyncSerializerState{masterchain_handle_->id(), last_key_block_id_, last_key_block_ts_},
                            std::move(P));
    return;
  }
  if (masterchain_handle_->inited_next_left()) {
    last_block_id_ = masterchain_handle_->one_next(true);
    masterchain_state_ = td::Ref<MasterchainState>{};
    masterchain_handle_ = nullptr;
    saved_to_db_ = false;
    shards_.clear();
    next_idx_ = 0;
    next_iteration();
  }
}

void AsyncStateSerializer::got_top_masterchain_handle(BlockIdExt block_id) {
  if (masterchain_handle_ && masterchain_handle_->id().id.seqno < block_id.id.seqno) {
    CHECK(masterchain_handle_->inited_next_left());
  }
}

void AsyncStateSerializer::got_masterchain_handle(BlockHandle handle) {
  CHECK(!masterchain_handle_);
  masterchain_handle_ = std::move(handle);
  running_ = false;
  attempt_ = 0;
  next_iteration();
}

void AsyncStateSerializer::got_masterchain_state(td::Ref<MasterchainState> state) {
  masterchain_state_ = state;
  CHECK(next_idx_ == 0);
  CHECK(shards_.size() == 0);

  auto vec = masterchain_state_->get_shards();
  shards_.push_back(masterchain_handle_->id());
  for (auto &v : vec) {
    shards_.push_back(v->top_block_id());
  }

  auto B = masterchain_state_->serialize();
  B.ensure();
  auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<td::Unit> R) {
    R.ensure();
    td::actor::send_closure(SelfId, &AsyncStateSerializer::stored_masterchain_state);
  });

  td::actor::send_closure(manager_, &ValidatorManager::store_persistent_state_file, masterchain_handle_->id(),
                          masterchain_handle_->id(), B.move_as_ok(), std::move(P));
}

void AsyncStateSerializer::stored_masterchain_state() {
  running_ = false;
  next_iteration();
}

void AsyncStateSerializer::got_shard_handle(BlockHandle handle) {
  auto P = td::PromiseCreator::lambda([SelfId = actor_id(this), handle](td::Result<td::Ref<ShardState>> R) {
    if (R.is_error()) {
      td::actor::send_closure(SelfId, &AsyncStateSerializer::fail_handler, R.move_as_error());
    } else {
      td::actor::send_closure(SelfId, &AsyncStateSerializer::got_shard_state, handle, R.move_as_ok());
    }
  });

  td::actor::send_closure(manager_, &ValidatorManager::get_shard_state_from_db, handle, std::move(P));
}

void AsyncStateSerializer::got_shard_state(BlockHandle handle, td::Ref<ShardState> state) {
  auto B = state->serialize().move_as_ok();
  auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<td::Unit> R) {
    R.ensure();
    td::actor::send_closure(SelfId, &AsyncStateSerializer::success_handler);
  });
  td::actor::send_closure(manager_, &ValidatorManager::store_persistent_state_file, handle->id(),
                          masterchain_handle_->id(), std::move(B), std::move(P));
  LOG(INFO) << "storing persistent state for " << masterchain_handle_->id().seqno() << ":" << handle->id().id.shard;
  next_idx_++;
}

void AsyncStateSerializer::fail_handler(td::Status reason) {
  VLOG(VALIDATOR_NOTICE) << "failure: " << reason;
  attempt_++;
  delay_action(
      [SelfId = actor_id(this)]() { td::actor::send_closure(SelfId, &AsyncStateSerializer::fail_handler_cont); },
      td::Timestamp::in(16.0));
}

void AsyncStateSerializer::fail_handler_cont() {
  running_ = false;
  next_iteration();
}

void AsyncStateSerializer::success_handler() {
  running_ = false;
  next_iteration();
}

bool AsyncStateSerializer::need_monitor(ShardIdFull shard) {
  return opts_->need_monitor(shard);
}

bool AsyncStateSerializer::need_serialize(BlockHandle handle) {
  if (handle->id().id.seqno == 0 || !handle->is_key_block()) {
    return false;
  }
  return ValidatorManager::is_persistent_state(handle->unix_time(), last_key_block_ts_);
}

}  // namespace validator

}  // namespace ton
