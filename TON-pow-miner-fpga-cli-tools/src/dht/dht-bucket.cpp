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
#include "td/utils/tl_storers.h"
#include "td/utils/crypto.h"
#include "td/utils/tl_parsers.h"
#include "td/utils/Random.h"

#include "td/utils/format.h"

#include "keys/encryptor.h"

#include "auto/tl/ton_api.hpp"

#include "dht-remote-node.hpp"
#include "dht-bucket.hpp"
#include "dht.hpp"

//#include <algorithm>

namespace ton {

namespace dht {

void DhtBucket::get_nearest_nodes(DhtKeyId id, td::uint32 bit, DhtNodesList &vec, td::uint32 k) {
  if (active_nodes_.size() == 0) {
    return;
  }
  std::map<DhtKeyId, size_t> list;

  for (size_t i = 0; i < active_nodes_.size(); i++) {
    auto &node = active_nodes_[i];
    if (node) {
      list.emplace(id ^ node->get_key(), i);
    }
  }

  for (auto it = list.begin(); it != list.end() && vec.size() < k; it++) {
    vec.push_back(active_nodes_[it->second]->get_node());
  }
}

td::uint32 DhtBucket::active_cnt() {
  td::uint32 cnt = 0;
  for (auto &node : active_nodes_) {
    if (node) {
      cnt++;
    }
  }
  return cnt;
}

td::Status DhtBucket::add_full_node(DhtKeyId id, DhtNode newnode, td::actor::ActorId<adnl::Adnl> adnl,
                                    adnl::AdnlNodeIdShort self_id) {
  for (auto &node : active_nodes_) {
    if (node && node->get_key() == id) {
      return node->update_value(std::move(newnode), adnl, self_id);
    }
  }
  for (auto &node : backup_nodes_) {
    if (node && node->get_key() == id) {
      return node->update_value(std::move(newnode), adnl, self_id);
    }
  }

  TRY_RESULT_PREFIX(N, DhtRemoteNode::create(std::move(newnode), max_missed_pings_), "failed to add new node: ");

  for (auto &node : backup_nodes_) {
    if (node == nullptr) {
      node = std::move(N);
      return td::Status::OK();
    }
  }

  for (auto &node : backup_nodes_) {
    CHECK(node);
    if (node->ready_from() == 0 && node->failed_from() + 60 < td::Time::now_cached()) {
      node = std::move(N);
      return td::Status::OK();
    }
  }

  return td::Status::OK();
}

void DhtBucket::receive_ping(DhtKeyId id, DhtNode result, td::actor::ActorId<adnl::Adnl> adnl,
                             adnl::AdnlNodeIdShort self_id) {
  for (auto &node : active_nodes_) {
    if (node && node->get_key() == id) {
      node->receive_ping(std::move(result), adnl, self_id);
      return;
    }
  }
  for (size_t i = 0; i < backup_nodes_.size(); i++) {
    auto &node = backup_nodes_[i];
    if (node && node->get_key() == id) {
      node->receive_ping(std::move(result), adnl, self_id);
      if (node->is_ready()) {
        promote_node(i);
      }
      return;
    }
  }
}

void DhtBucket::demote_node(size_t idx) {
  for (auto &node : backup_nodes_) {
    if (node == nullptr) {
      node = std::move(active_nodes_[idx]);
      return;
    }
  }
  for (auto &node : backup_nodes_) {
    if (node->ready_from() == 0 && node->failed_from() + 60 < td::Time::now_cached()) {
      node = std::move(active_nodes_[idx]);
      return;
    }
  }
  active_nodes_[idx] = nullptr;
}

void DhtBucket::promote_node(size_t idx) {
  CHECK(backup_nodes_[idx]);
  for (auto &node : active_nodes_) {
    if (node == nullptr) {
      node = std::move(backup_nodes_[idx]);
      return;
    }
    CHECK(node->is_ready());
  }
}

void DhtBucket::check(bool client_only, td::actor::ActorId<adnl::Adnl> adnl, td::actor::ActorId<DhtMember> dht,
                      adnl::AdnlNodeIdShort src) {
  size_t have_space = 0;
  for (size_t i = 0; i < active_nodes_.size(); i++) {
    auto &node = active_nodes_[i];
    if (node && td::Time::now_cached() - node->last_ping_at() > ping_timeout_) {
      node->send_ping(client_only, adnl, dht, src);
      if (node->ready_from() == 0) {
        demote_node(i);
      }
    }
    if (node == nullptr) {
      have_space++;
    }
  }
  for (size_t i = 0; i < backup_nodes_.size(); i++) {
    auto &node = backup_nodes_[i];
    if (node && td::Time::now_cached() - node->last_ping_at() > ping_timeout_) {
      node->send_ping(client_only, adnl, dht, src);
    }
    if (node && have_space > 0 && node->is_ready()) {
      promote_node(i);
      have_space--;
    }
  }
}

void DhtBucket::dump(td::StringBuilder &sb) const {
  sb << "  bucket:\n";
  sb << "    active:\n";
  for (auto &node : active_nodes_) {
    if (node) {
      sb << "      " << node->get_key() << "\n";
    }
  }
  sb << "    backup:\n";
  for (auto &node : backup_nodes_) {
    if (node) {
      sb << "      " << node->get_key() << "\n";
    }
  }
}

DhtNodesList DhtBucket::export_nodes() const {
  DhtNodesList list;
  for (auto &node : active_nodes_) {
    if (node) {
      list.push_back(node->get_node());
    }
  }
  for (auto &node : backup_nodes_) {
    if (node) {
      list.push_back(node->get_node());
    }
  }
  return list;
}

}  // namespace dht

}  // namespace ton
