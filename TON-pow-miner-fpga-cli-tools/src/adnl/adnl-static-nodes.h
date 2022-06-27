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
#include "td/utils/Status.h"
#include "td/actor/PromiseFuture.h"
#include "auto/tl/ton_api.h"

#include "adnl-peer-table.h"

namespace ton {

namespace adnl {

class AdnlStaticNodesManager : public td::actor::Actor {
 public:
  virtual void add_node(AdnlNode node) = 0;
  virtual void del_node(AdnlNodeIdShort id) = 0;
  virtual td::Result<AdnlNode> get_node(AdnlNodeIdShort id) = 0;

  static td::actor::ActorOwn<AdnlStaticNodesManager> create();
};

}  // namespace adnl

}  // namespace ton
