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

#include "td/utils/port/detail/PollableFd.h"
#include "td/utils/port/PollFlags.h"

namespace td {
class PollBase {
 public:
  PollBase() = default;
  PollBase(const PollBase &) = delete;
  PollBase &operator=(const PollBase &) = delete;
  PollBase(PollBase &&) = default;
  PollBase &operator=(PollBase &&) = default;
  virtual ~PollBase() = default;
  virtual void init() = 0;
  virtual void clear() = 0;
  virtual void subscribe(PollableFd fd, PollFlags flags) = 0;
  virtual void unsubscribe(PollableFdRef fd) = 0;
  virtual void unsubscribe_before_close(PollableFdRef fd) = 0;
  virtual void run(int timeout_ms) = 0;
};
}  // namespace td
