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
#pragma once
#include "td/actor/actor.h"

#include "tonlib/Config.h"
#include "tonlib/ExtClient.h"

#include "td/utils/CancellationToken.h"
#include "td/utils/tl_helpers.h"

namespace block {
struct BlockProofChain;
}
namespace tonlib {
td::StringBuilder &operator<<(td::StringBuilder &sb, const LastBlockState &state);
template <unsigned int N, class StorerT>
void store(const td::BitArray<N> &arr, StorerT &storer) {
  storer.store_binary(arr);
}
template <unsigned int N, class ParserT>
void parse(td::BitArray<N> &arr, ParserT &parser) {
  arr = parser.template fetch_binary<td::BitArray<N>>();
}

template <class StorerT>
void store(const ton::ZeroStateIdExt &zero_state_id, StorerT &storer) {
  using td::store;
  using tonlib::store;
  store(zero_state_id.workchain, storer);
  store(zero_state_id.root_hash, storer);
  store(zero_state_id.file_hash, storer);
}
template <class ParserT>
void parse(ton::ZeroStateIdExt &zero_state_id, ParserT &parser) {
  using td::parse;
  using tonlib::parse;
  parse(zero_state_id.workchain, parser);
  parse(zero_state_id.root_hash, parser);
  parse(zero_state_id.file_hash, parser);
}
template <class StorerT>
void store(const ton::BlockId &block_id, StorerT &storer) {
  using td::store;
  using tonlib::store;
  store(block_id.workchain, storer);
  store(block_id.shard, storer);
  store(block_id.seqno, storer);
}
template <class ParserT>
void parse(ton::BlockId &block_id, ParserT &parser) {
  using td::parse;
  using tonlib::parse;
  parse(block_id.workchain, parser);
  parse(block_id.shard, parser);
  parse(block_id.seqno, parser);
}
template <class StorerT>
void store(const ton::BlockIdExt &block_id, StorerT &storer) {
  using td::store;
  using tonlib::store;
  store(block_id.id, storer);
  store(block_id.root_hash, storer);
  store(block_id.file_hash, storer);
}
template <class ParserT>
void parse(ton::BlockIdExt &block_id, ParserT &parser) {
  using td::parse;
  using tonlib::parse;
  parse(block_id.id, parser);
  parse(block_id.root_hash, parser);
  parse(block_id.file_hash, parser);
}
struct LastBlockState {
  ton::ZeroStateIdExt zero_state_id;
  ton::BlockIdExt last_key_block_id;
  ton::BlockIdExt last_block_id;
  td::int64 utime{0};
  ton::BlockIdExt init_block_id;
  td::int32 vert_seqno{0};

  static constexpr td::int32 magic = 0xa7f171a4;
  enum Version { None = 0, Magic, InitBlock, VertSeqno, Next };
  static constexpr td::int32 version = Version::Next - 1;

  template <class StorerT>
  void store(StorerT &storer) const {
    using td::store;
    using tonlib::store;
    store(magic, storer);
    store(version, storer);

    store(zero_state_id, storer);
    store(last_key_block_id, storer);
    store(last_block_id, storer);
    store(utime, storer);
    store(init_block_id, storer);
    store(vert_seqno, storer);
  }

  template <class ParserT>
  void parse(ParserT &parser) {
    using td::parse;
    using tonlib::parse;
    td::int32 version = 0;
    if (parser.can_prefetch_int() && parser.prefetch_int_unsafe() == magic) {
      td::int32 magic;
      parse(magic, parser);
      parse(version, parser);
    }

    parse(zero_state_id, parser);
    parse(last_key_block_id, parser);
    parse(last_block_id, parser);
    parse(utime, parser);
    if (version >= InitBlock) {
      parse(init_block_id, parser);
    }
    if (version >= VertSeqno) {
      parse(vert_seqno, parser);
    }
  }
};

struct LastBlockSyncState {
  enum Type { Invalid, InProgress, Done } type = Invalid;
  td::int32 from_seqno{0};
  td::int32 to_seqno{0};
  td::int32 current_seqno{0};

  auto as_key() const {
    return std::tie(type, from_seqno, to_seqno, current_seqno);
  }
  bool operator==(const LastBlockSyncState &other) const {
    return as_key() == other.as_key();
  }
};

class LastBlock : public td::actor::Actor {
 public:
  class Callback {
   public:
    virtual ~Callback() {
    }
    virtual void on_state_changed(LastBlockState state) = 0;
    virtual void on_sync_state_changed(LastBlockSyncState state) = 0;
  };

  explicit LastBlock(ExtClientRef client, LastBlockState state, Config config, td::CancellationToken cancellation_token,
                     td::unique_ptr<Callback> callback);
  void get_last_block(td::Promise<LastBlockState> promise);

 private:
  td::unique_ptr<Callback> callback_;
  ExtClient client_;
  LastBlockState state_;
  Config config_;
  td::CancellationToken cancellation_token_;

  td::Status fatal_error_;

  enum class QueryState { Empty, Active, Done };
  QueryState get_mc_info_state_{QueryState::Empty};       // just to check zero state
  QueryState check_init_block_state_{QueryState::Empty};  // init_block <---> last_key_block (from older to newer)
  QueryState get_last_block_state_{QueryState::Empty};    // last_key_block_id --> ?

  unsigned min_seqno_ = 0;
  unsigned current_seqno_ = 0;
  unsigned max_seqno_ = 0;
  LastBlockSyncState sync_state_;

  // stats
  struct Stats {
    td::Timer total_sync_;
    td::Timer validate_;
    td::uint32 queries_;

    void start() {
      total_sync_ = td::Timer();
      validate_ = td::Timer(true);
      queries_ = 0;
    }

    friend td::StringBuilder &operator<<(td::StringBuilder &sb, const Stats &stats) {
      return sb << "   net queries: " << stats.queries_ << "\n"
                << "   total: " << stats.total_sync_ << " validation: " << stats.validate_;
    }
  };

  Stats check_init_block_stats_;
  Stats get_last_block_stats_;

  std::vector<td::Promise<LastBlockState>> promises_;

  void do_check_init_block(ton::BlockIdExt from, ton::BlockIdExt to);
  void on_init_block_proof(
      ton::BlockIdExt from, ton::BlockIdExt to,
      td::Result<ton::ton_api::object_ptr<ton::lite_api::liteServer_partialBlockProof>> r_block_proof);
  void on_masterchain_info(td::Result<ton::ton_api::object_ptr<ton::lite_api::liteServer_masterchainInfo>> r_info);
  void do_get_last_block();
  void on_block_proof(ton::BlockIdExt from,
                      td::Result<ton::ton_api::object_ptr<ton::lite_api::liteServer_partialBlockProof>> r_block_proof);
  td::Result<std::unique_ptr<block::BlockProofChain>> process_block_proof(
      ton::BlockIdExt from,
      td::Result<ton::ton_api::object_ptr<ton::lite_api::liteServer_partialBlockProof>> r_block_proof);

  td::Result<std::unique_ptr<block::BlockProofChain>> process_block_proof(
      ton::BlockIdExt from, ton::ton_api::object_ptr<ton::lite_api::liteServer_partialBlockProof> block_proof);

  void update_state(block::BlockProofChain &chain);
  void update_zero_state(ton::ZeroStateIdExt zero_state_id, td::Slice source);

  bool update_mc_last_block(ton::BlockIdExt mc_block_id);
  bool update_mc_last_key_block(ton::BlockIdExt mc_key_block_id);
  void update_utime(td::int64 utime);
  bool update_init_block(ton::BlockIdExt init_block_id);

  void save_state();
  void on_sync_ok();
  void on_sync_error(td::Status status);
  void on_fatal_error(td::Status status);
  bool has_fatal_error() const;

  LastBlockSyncState get_sync_state();
  void update_sync_state();
  void sync_loop();

  void tear_down() override;
};
}  // namespace tonlib
