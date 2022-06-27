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
#include "td/utils/Slice.h"
#include "td/utils/Span.h"

#include "td/fec/raptorq/Rfc.h"
#include "td/fec/common/SymbolRef.h"

namespace td {
namespace raptorq {

class Solver {
 public:
  static Result<MatrixGF256> run(const Rfc::Parameters &p, Span<SymbolRef> symbols);
};

}  // namespace raptorq
}  // namespace td
