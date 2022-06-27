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

    Copyright 2019-2020 Telegram Systems LLP
*/
#pragma once
#include "vm/cells.h"

#include "SmartContract.h"
#include "Ed25519.h"

#include <bitset>

namespace ton {
class MultisigWallet : public ton::SmartContract {
 public:
  MultisigWallet(State state) : SmartContract(std::move(state)) {
  }

  using Mask = std::bitset<128>;
  struct QueryState {
    enum State { Unknown, NotReady, Sent } state = Unknown;
    Mask mask;
  };

  class QueryBuilder {
   public:
    QueryBuilder(td::uint32 wallet_id, td::int64 query_id, td::Ref<vm::Cell> msg, int mode = 3);
    void sign(td::int32 id, td::Ed25519::PrivateKey& pk);

    td::Ref<vm::Cell> create_inner() const;
    td::Ref<vm::Cell> create(td::int32 id, td::Ed25519::PrivateKey& pk) const;
    Mask get_mask() const {
      return mask_;
    }

   private:
    vm::Ref<vm::Cell> dict_;
    td::Ref<vm::Cell> msg_;
    Mask mask_;
  };

  MultisigWallet* make_copy() const override {
    return new MultisigWallet{state_};
  }

  // creation
  static td::Ref<MultisigWallet> create(td::Ref<vm::Cell> data = {});

  td::Ref<vm::Cell> create_init_data(td::uint32 wallet_id, std::vector<td::SecureString> public_keys, int k) const;
  static td::Ref<vm::Cell> create_init_data_fast(td::uint32 wallet_id, std::vector<td::SecureString> public_keys,
                                                 int k);

  // get methods
  int processed(td::uint64 query_id) const;
  QueryState get_query_state(td::uint64 query_id) const;
  std::vector<td::SecureString> get_public_keys() const;
  td::Ref<vm::Cell> merge_queries(td::Ref<vm::Cell> a, td::Ref<vm::Cell> b) const;
  std::pair<int, Mask> check_query_signatures(td::Ref<vm::Cell> a) const;
  std::pair<int, int> get_n_k() const;
  Mask to_mask(td::RefInt256 mask) const;

  struct Message {
    td::uint64 query_id;
    Mask signed_by;
    td::Ref<vm::Cell> message;
  };
  std::vector<Message> get_unsigned_messaged(int id = -1) const;
};
}  // namespace ton
