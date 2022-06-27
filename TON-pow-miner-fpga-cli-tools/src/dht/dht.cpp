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
#include "dht.hpp"

#include "td/utils/tl_storers.h"
#include "td/utils/crypto.h"
#include "td/utils/tl_parsers.h"
#include "td/utils/Random.h"
#include "td/utils/base64.h"

#include "td/utils/format.h"

#include "td/db/RocksDb.h"

#include "keys/encryptor.h"
#include "adnl/utils.hpp"

#include "auto/tl/ton_api.hpp"

#include "dht.h"
#include "dht-bucket.hpp"
#include "dht-query.hpp"
#include "dht-in.hpp"

namespace ton {

namespace dht {

td::actor::ActorOwn<DhtMember> DhtMember::create(adnl::AdnlNodeIdShort id, std::string db_root,
                                                 td::actor::ActorId<keyring::Keyring> keyring,
                                                 td::actor::ActorId<adnl::Adnl> adnl, td::uint32 k, td::uint32 a,
                                                 bool client_only) {
  return td::actor::ActorOwn<DhtMember>(
      td::actor::create_actor<DhtMemberImpl>("dht", id, db_root, keyring, adnl, k, a, client_only));
}

td::Result<td::actor::ActorOwn<Dht>> Dht::create(adnl::AdnlNodeIdShort id, std::string db_root,
                                                 std::shared_ptr<DhtGlobalConfig> conf,
                                                 td::actor::ActorId<keyring::Keyring> keyring,
                                                 td::actor::ActorId<adnl::Adnl> adnl) {
  CHECK(conf->get_k() > 0);
  CHECK(conf->get_a() > 0);

  auto D = DhtMember::create(id, db_root, keyring, adnl, conf->get_k(), conf->get_a());
  auto &nodes = conf->nodes();

  for (auto &node : nodes.list()) {
    auto key = node.get_key();
    td::actor::send_closure(D, &DhtMember::add_full_node, key, node.clone());
  }
  return std::move(D);
}

td::Result<td::actor::ActorOwn<Dht>> Dht::create_client(adnl::AdnlNodeIdShort id, std::string db_root,
                                                        std::shared_ptr<DhtGlobalConfig> conf,
                                                        td::actor::ActorId<keyring::Keyring> keyring,
                                                        td::actor::ActorId<adnl::Adnl> adnl) {
  CHECK(conf->get_k() > 0);
  CHECK(conf->get_a() > 0);

  auto D = DhtMember::create(id, db_root, keyring, adnl, conf->get_k(), conf->get_a(), true);
  auto &nodes = conf->nodes();

  for (auto &node : nodes.list()) {
    auto key = node.get_key();
    td::actor::send_closure(D, &DhtMember::add_full_node, key, node.clone());
  }
  return std::move(D);
}

void DhtMemberImpl::start_up() {
  std::vector<td::int32> methods = {ton_api::dht_getSignedAddressList::ID,
                                    ton_api::dht_findNode::ID,
                                    ton_api::dht_findValue::ID,
                                    ton_api::dht_store::ID,
                                    ton_api::dht_ping::ID,
                                    ton_api::dht_query::ID,
                                    ton_api::dht_message::ID};

  for (auto it : methods) {
    td::actor::send_closure(adnl_, &adnl::Adnl::subscribe, id_, adnl::Adnl::int_to_bytestring(it),
                            std::make_unique<Callback>(actor_id(this), id_));
  }
  alarm_timestamp() = td::Timestamp::in(1.0);

  if (!db_root_.empty()) {
    std::shared_ptr<td::KeyValue> kv = std::make_shared<td::RocksDb>(
        td::RocksDb::open(PSTRING() << db_root_ << "/dht-" << td::base64url_encode(id_.as_slice())).move_as_ok());
    for (td::uint32 bit = 0; bit < 256; bit++) {
      auto key = create_hash_tl_object<ton_api::dht_db_key_bucket>(bit);
      std::string value;
      auto R = kv->get(key.as_slice(), value);
      R.ensure();
      if (R.move_as_ok() == td::KeyValue::GetStatus::Ok) {
        auto V = fetch_tl_object<ton_api::dht_db_bucket>(td::BufferSlice{value}, true);
        V.ensure();
        auto nodes = std::move(V.move_as_ok()->nodes_);
        auto s = nodes->nodes_.size();
        DhtNodesList list{std::move(nodes)};
        CHECK(list.size() == s);
        auto &B = buckets_[bit];
        for (auto &node : list.list()) {
          auto key = node.get_key();
          B.add_full_node(key, std::move(node), adnl_, id_);
        }
      }
    }
    db_ = DbType{std::move(kv)};
  }
}

void DhtMemberImpl::tear_down() {
  std::vector<td::int32> methods = {ton_api::dht_getSignedAddressList::ID,
                                    ton_api::dht_findNode::ID,
                                    ton_api::dht_findValue::ID,
                                    ton_api::dht_store::ID,
                                    ton_api::dht_ping::ID,
                                    ton_api::dht_query::ID,
                                    ton_api::dht_message::ID};

  for (auto it : methods) {
    td::actor::send_closure(adnl_, &adnl::Adnl::unsubscribe, id_, adnl::Adnl::int_to_bytestring(it));
  }
}

void DhtMemberImpl::save_to_db() {
  if (db_root_.empty()) {
    return;
  }
  next_save_to_db_at_ = td::Timestamp::in(10.0);
  alarm_timestamp().relax(next_save_to_db_at_);

  td::uint32 bit = td::Random::fast(0, 255);
  auto &B = buckets_[bit];
  auto list = B.export_nodes();
  if (list.size() > 0) {
    auto key = create_hash_tl_object<ton_api::dht_db_key_bucket>(bit);
    auto value = create_serialize_tl_object<ton_api::dht_db_bucket>(list.tl());

    db_.set(key, std::move(value));
  }
}

DhtNodesList DhtMemberImpl::get_nearest_nodes(DhtKeyId id, td::uint32 k) {
  DhtNodesList vec;

  auto id_xor = id ^ key_;

  for (td::uint32 bit = 0; bit < 256; bit++) {
    if (id_xor.get_bit(bit)) {
      buckets_[bit].get_nearest_nodes(id, bit, vec, k);
      if (vec.size() >= k) {
        break;
      }
    }
  }

  for (auto &el : vec.list()) {
    CHECK((el.get_key() ^ id) < id_xor);
  }
  if (vec.size() < k) {
    for (td::uint32 bit = 255; bit != 256; bit = bit ? (bit - 1) : 256) {
      if (!id_xor.get_bit(bit)) {
        buckets_[bit].get_nearest_nodes(id, bit, vec, k);
        if (vec.size() >= k) {
          break;
        }
      }
    }
  }
  CHECK(vec.size() <= k);
  return vec;
}

td::uint32 DhtMemberImpl::distance(DhtKeyId key_id, td::uint32 max_value) {
  if (!max_value) {
    max_value = 2 * k_;
  }
  td::uint32 res = 0;
  auto id_xor = key_id ^ key_;

  for (td::uint32 bit = 0; bit < 256; bit++) {
    if (id_xor.get_bit(bit)) {
      res += buckets_[bit].active_cnt();
      if (res >= max_value) {
        return max_value;
      }
    }
  }
  return res;
}

void DhtMemberImpl::process_query(adnl::AdnlNodeIdShort src, ton_api::dht_ping &query,
                                  td::Promise<td::BufferSlice> promise) {
  ping_queries_++;
  promise.set_value(create_serialize_tl_object<ton_api::dht_pong>(query.random_id_));
}

void DhtMemberImpl::process_query(adnl::AdnlNodeIdShort src, ton_api::dht_findNode &query,
                                  td::Promise<td::BufferSlice> promise) {
  find_node_queries_++;
  auto k = static_cast<td::uint32>(query.k_);
  if (k > max_k()) {
    k = max_k();
  }
  auto R = get_nearest_nodes(DhtKeyId{query.key_}, k);
  promise.set_value(serialize_tl_object(R.tl(), true));
}

void DhtMemberImpl::process_query(adnl::AdnlNodeIdShort src, ton_api::dht_findValue &query,
                                  td::Promise<td::BufferSlice> promise) {
  find_value_queries_++;
  auto it = values_.find(DhtKeyId{query.key_});
  if (it != values_.end() && it->second.expired()) {
    values_.erase(it);
    it = values_.end();
  }
  if (it != values_.end()) {
    promise.set_value(create_serialize_tl_object<ton_api::dht_valueFound>(it->second.tl()));
    return;
  }

  auto k = static_cast<td::uint32>(query.k_);
  if (k > max_k()) {
    k = max_k();
  }
  auto R = get_nearest_nodes(DhtKeyId{query.key_}, k);

  promise.set_value(create_serialize_tl_object<ton_api::dht_valueNotFound>(R.tl()));
}

td::Status DhtMemberImpl::store_in(DhtValue value) {
  if (value.expired()) {
    VLOG(DHT_INFO) << this << ": dropping expired value: " << value.key_id() << " expire_at = " << value.ttl();
    return td::Status::OK();
  }
  TRY_STATUS(value.check());

  auto key_id = value.key_id();

  auto dist = distance(key_id, k_ + 10);
  if (dist < k_ + 10) {
    auto it = values_.find(key_id);
    if (it != values_.end()) {
      it->second.update(std::move(value));
    } else {
      values_.emplace(key_id, std::move(value));
    }
  } else {
    VLOG(DHT_INFO) << this << ": dropping too remote value: " << value.key_id() << " distance = " << dist;
  }
  return td::Status::OK();
}

void DhtMemberImpl::process_query(adnl::AdnlNodeIdShort src, ton_api::dht_store &query,
                                  td::Promise<td::BufferSlice> promise) {
  store_queries_++;
  auto V = DhtValue::create(std::move(query.value_), true);
  if (V.is_error()) {
    promise.set_error(td::Status::Error(ErrorCode::protoviolation,
                                        PSTRING() << "dropping invalid dht_store() value: " << V.error().to_string()));
    VLOG(DHT_INFO) << this << ": dropping invalid value: " << V.move_as_error();
    return;
  }
  auto b = store_in(V.move_as_ok());

  if (b.is_ok()) {
    promise.set_value(create_serialize_tl_object<ton_api::dht_stored>());
  } else {
    VLOG(DHT_INFO) << this << ": dropping store() query from " << src << ": " << b.move_as_error();
    promise.set_error(td::Status::Error(ErrorCode::protoviolation, "dropping dht_store() query"));
  }
}

void DhtMemberImpl::process_query(adnl::AdnlNodeIdShort src, ton_api::dht_getSignedAddressList &query,
                                  td::Promise<td::BufferSlice> promise) {
  get_addr_list_queries_++;

  auto P = td::PromiseCreator::lambda([promise = std::move(promise)](td::Result<DhtNode> R) mutable {
    R.ensure();
    promise.set_value(serialize_tl_object(R.move_as_ok().tl(), true));
  });
  get_self_node(std::move(P));
}

void DhtMemberImpl::receive_query(adnl::AdnlNodeIdShort src, td::BufferSlice data,
                                  td::Promise<td::BufferSlice> promise) {
  if (client_only_) {
    return;
  }
  {
    auto R = fetch_tl_prefix<ton_api::dht_query>(data, true);
    if (R.is_ok()) {
      auto N = DhtNode::create(std::move(R.move_as_ok()->node_));
      if (N.is_ok()) {
        auto node = N.move_as_ok();
        auto key = node.get_key();
        add_full_node(key, std::move(node));
      } else {
        VLOG(DHT_WARNING) << this << ": dropping bad node " << N.move_as_error();
      }
    }
  }
  auto R = fetch_tl_object<ton_api::Function>(std::move(data), true);

  if (R.is_error()) {
    VLOG(DHT_WARNING) << this << ": dropping unknown query to DHT node: " << R.move_as_error();
    promise.set_error(td::Status::Error(ErrorCode::protoviolation, "failed to parse dht query"));
    return;
  }

  auto Q = R.move_as_ok();
  if (td::Random::fast(0, 127) == 0) {
    VLOG(DHT_DEBUG) << this << ": ping=" << ping_queries_ << " fnode=" << find_node_queries_
                    << " fvalue=" << find_value_queries_ << " store=" << store_queries_
                    << " addrlist=" << get_addr_list_queries_;
    VLOG(DHT_DEBUG) << this << ": query to DHT from " << src << ": " << ton_api::to_string(Q);
  }

  VLOG(DHT_EXTRA_DEBUG) << this << ": query to DHT from " << src << ": " << ton_api::to_string(Q);

  ton_api::downcast_call(*Q.get(), [&](auto &object) { this->process_query(src, object, std::move(promise)); });
}

void DhtMemberImpl::add_full_node(DhtKeyId key, DhtNode node) {
  VLOG(DHT_EXTRA_DEBUG) << this << ": adding full node " << key;

  auto eid = key ^ key_;
  auto bit = eid.count_leading_zeroes();
#ifndef NDEBUG
  for (td::uint32 i = 0; i < bit; i++) {
    CHECK(key.get_bit(i) == key_.get_bit(i));
  }
#endif
  if (bit < 256) {
    CHECK(key.get_bit(bit) != key_.get_bit(bit));
    buckets_[bit].add_full_node(key, std::move(node), adnl_, id_);
  } else {
    CHECK(key == key_);
  }
}

void DhtMemberImpl::receive_ping(DhtKeyId key, DhtNode result) {
  VLOG(DHT_EXTRA_DEBUG) << this << ": received ping from " << key;

  auto eid = key ^ key_;
  auto bit = eid.count_leading_zeroes();
  if (bit < 256) {
    buckets_[bit].receive_ping(key, std::move(result), adnl_, id_);
  } else {
    CHECK(key == key_);
  }
}

void DhtMemberImpl::receive_message(adnl::AdnlNodeIdShort src, td::BufferSlice data) {
}

void DhtMemberImpl::set_value(DhtValue value, td::Promise<td::Unit> promise) {
  auto S = value.check();
  if (S.is_error()) {
    promise.set_error(std::move(S));
    return;
  }
  auto h = value.key_id();
  our_values_.emplace(h, value.clone());

  send_store(std::move(value), std::move(promise));
}

void DhtMemberImpl::get_value_in(DhtKeyId key, td::Promise<DhtValue> result) {
  auto P = td::PromiseCreator::lambda([key, promise = std::move(result), SelfId = actor_id(this), print_id = print_id(),
                                       adnl = adnl_, list = get_nearest_nodes(key, k_), k = k_, a = a_, id = id_,
                                       client_only = client_only_](td::Result<DhtNode> R) mutable {
    R.ensure();
    td::actor::create_actor<DhtQueryFindValue>("FindValueQuery", key, print_id, id, std::move(list), k, a,
                                               R.move_as_ok(), client_only, SelfId, adnl, std::move(promise))
        .release();
  });

  get_self_node(std::move(P));
}

void DhtMemberImpl::check() {
  VLOG(DHT_INFO) << this << ": ping=" << ping_queries_ << " fnode=" << find_node_queries_
                 << " fvalue=" << find_value_queries_ << " store=" << store_queries_
                 << " addrlist=" << get_addr_list_queries_;
  for (auto &bucket : buckets_) {
    bucket.check(client_only_, adnl_, actor_id(this), id_);
  }
  if (next_save_to_db_at_.is_in_past()) {
    save_to_db();
  }

  if (values_.size() > 0) {
    auto it = values_.lower_bound(last_check_key_);
    if (it != values_.end() && it->first == last_check_key_) {
      it++;
    }
    if (it == values_.end()) {
      it = values_.begin();
    }

    td::uint32 cnt = 0;
    auto s = last_check_key_;
    while (values_.size() > 0 && cnt < 1 && it->first != s) {
      last_check_key_ = it->first;
      cnt++;
      if (it->second.expired()) {
        it = values_.erase(it);

        // do not republish soon-to-be-expired values
      } else if (it->second.ttl() > td::Clocks::system() + 60) {
        auto dist = distance(it->first, k_ + 10);

        if (dist == 0) {
          if (it->second.key().update_rule()->need_republish()) {
            auto P = td::PromiseCreator::lambda([print_id = print_id()](td::Result<td::Unit> R) {
              if (R.is_error()) {
                VLOG(DHT_INFO) << print_id << ": failed to store: " << R.move_as_error();
              }
            });
            send_store(it->second.clone(), std::move(P));
          }
          it++;
        } else if (dist >= k_ + 10) {
          it = values_.erase(it);
        } else {
          it++;
        }
      } else {
        it++;
      }
      if (values_.size() == 0) {
        break;
      }
      if (it == values_.end()) {
        it = values_.begin();
      }
    }
  }

  if (republish_att_.is_in_past()) {
    auto it = our_values_.lower_bound(last_republish_key_);
    if (it != our_values_.end() && it->first == last_republish_key_) {
      it++;
    }
    if (it == our_values_.end()) {
      it = our_values_.begin();
    }
    if (it != our_values_.end()) {
      if (it->second.ttl() > td::Clocks::system() + 60) {
        auto P = td::PromiseCreator::lambda([print_id = print_id()](td::Result<td::Unit> R) {
          if (R.is_error()) {
            VLOG(DHT_INFO) << print_id << ": failed to store: " << R.move_as_error();
          }
        });
        send_store(it->second.clone(), std::move(P));
      }
      last_republish_key_ = it->first;
    }
    republish_att_ = td::Timestamp::in(10.0 + td::Random::fast(0, 1000) * 0.001);
  }

  if (fill_att_.is_in_past()) {
    auto promise = td::PromiseCreator::lambda([](td::Result<DhtNodesList> R) {
      if (R.is_error()) {
        VLOG(DHT_WARNING) << "failed find self query: " << R.move_as_error();
      }
    });

    td::Bits256 x;

    td::uint32 t = td::Random::fast(0, 6);
    td::uint32 b = 64 - td::Random::fast(0, 1 << t);
    td::Random::secure_bytes(x.as_slice());
    for (td::uint32 i = 0; i < b; i++) {
      x.bits()[i] = key_.get_bit(i);
    }

    DhtKeyId key{x};
    auto P = td::PromiseCreator::lambda([key, promise = std::move(promise), SelfId = actor_id(this),
                                         print_id = print_id(), adnl = adnl_, list = get_nearest_nodes(key, k_), k = k_,
                                         a = a_, id = id_, client_only = client_only_](td::Result<DhtNode> R) mutable {
      R.ensure();
      td::actor::create_actor<DhtQueryFindNodes>("FindNodesQuery", key, print_id, id, std::move(list), k, a,
                                                 R.move_as_ok(), client_only, SelfId, adnl, std::move(promise))
          .release();
    });

    get_self_node(std::move(P));

    fill_att_ = td::Timestamp::in(10.0 + td::Random::fast(0, 100) * 0.1);
  }
}

void DhtMemberImpl::dump(td::StringBuilder &sb) const {
  for (auto &B : buckets_) {
    B.dump(sb);
  }
}

void DhtMemberImpl::send_store(DhtValue value, td::Promise<td::Unit> promise) {
  value.check().ensure();
  auto key_id = value.key_id();

  auto P =
      td::PromiseCreator::lambda([value = std::move(value), print_id = print_id(), id = id_, client_only = client_only_,
                                  list = get_nearest_nodes(key_id, k_), k = k_, a = a_, SelfId = actor_id(this),
                                  adnl = adnl_, promise = std::move(promise)](td::Result<DhtNode> R) mutable {
        R.ensure();
        td::actor::create_actor<DhtQueryStore>("StoreQuery", std::move(value), print_id, id, std::move(list), k, a,
                                               R.move_as_ok(), client_only, SelfId, adnl, std::move(promise))
            .release();
      });

  get_self_node(std::move(P));
}

void DhtMemberImpl::get_self_node(td::Promise<DhtNode> promise) {
  auto P =
      td::PromiseCreator::lambda([promise = std::move(promise), print_id = print_id(), id = id_, keyring = keyring_,
                                  client_only = client_only_](td::Result<adnl::AdnlNode> R) mutable {
        R.ensure();
        auto node = R.move_as_ok();
        auto version = static_cast<td::int32>(td::Clocks::system());
        auto B = create_serialize_tl_object<ton_api::dht_node>(node.pub_id().tl(), node.addr_list().tl(), version,
                                                               td::BufferSlice());
        if (!client_only) {
          CHECK(node.addr_list().size() > 0);
        }
        auto P = td::PromiseCreator::lambda(
            [promise = std::move(promise), node = std::move(node), version](td::Result<td::BufferSlice> R) mutable {
              R.ensure();
              DhtNode n{node.pub_id(), node.addr_list(), version, R.move_as_ok()};
              promise.set_result(std::move(n));
            });
        td::actor::send_closure(keyring, &keyring::Keyring::sign_message, id.pubkey_hash(), std::move(B), std::move(P));
      });
  td::actor::send_closure(adnl_, &adnl::Adnl::get_self_node, id_, std::move(P));
}

td::Result<std::shared_ptr<DhtGlobalConfig>> Dht::create_global_config(tl_object_ptr<ton_api::dht_config_global> conf) {
  td::uint32 k;
  if (conf->k_ == 0) {
    k = DhtMember::default_k();
  } else if (conf->k_ > 0 && static_cast<td::uint32>(conf->k_) <= DhtMember::max_k()) {
    k = conf->k_;
  } else {
    return td::Status::Error(ErrorCode::protoviolation, PSTRING() << "bad value k=" << conf->k_);
  }
  td::uint32 a;
  if (conf->a_ == 0) {
    a = DhtMember::default_a();
  } else if (conf->a_ > 0 && static_cast<td::uint32>(conf->a_) <= DhtMember::max_a()) {
    a = conf->a_;
  } else {
    return td::Status::Error(ErrorCode::protoviolation, PSTRING() << "bad value a=" << conf->a_);
  }

  DhtNodesList l{std::move(conf->static_nodes_)};

  return std::make_shared<DhtGlobalConfig>(k, a, std::move(l));
}

}  // namespace dht

}  // namespace ton
