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

#include "InboundTransfer.h"

#include "common/errorcode.h"

namespace ton {
namespace rldp2 {
size_t InboundTransfer::total_size() const {
  return data_.size();
}

std::map<td::uint32, InboundTransfer::Part> &InboundTransfer::parts() {
  return parts_;
}

bool InboundTransfer::is_part_completed(td::uint32 part_i) {
  return parts_.count(part_i) == 0 && part_i < next_part_;
}

td::Result<InboundTransfer::Part *> InboundTransfer::get_part(td::uint32 part_i, const ton::fec::FecType &fec_type) {
  auto it = parts_.find(part_i);
  if (it != parts_.end()) {
    return &it->second;
  }
  //TODO: pass offset off and process even newer parts.
  //LOG_CHECK(next_part_ >= part_i) << next_part_ << " >= " << part_i;
  if (next_part_ == part_i && parts_.size() < 20) {
    auto offset = offset_;
    offset_ += fec_type.size();
    if (offset_ > total_size()) {
      return td::Status::Error(ErrorCode::protoviolation,
                               PSTRING() << "too big part: offset=" << offset_ << " total_size=" << total_size()
                                         << " total_size=" << fec_type.size() << " part=" << part_i);
    }

    auto decoder = fec_type.create_decoder().move_as_ok();
    auto it = parts_.emplace(part_i, Part{std::move(decoder), RldpReceiver(RldpSender::Config()), offset});
    next_part_++;
    return &it.first->second;
  }
  return nullptr;
}

void InboundTransfer::finish_part(td::uint32 part_i, td::Slice data) {
  auto it = parts_.find(part_i);
  CHECK(it != parts_.end());
  data_.as_slice().substr(it->second.offset).copy_from(data);
  parts_.erase(it);
}

td::optional<td::Result<td::BufferSlice>> InboundTransfer::try_finish() {
  if (parts_.empty() && offset_ == data_.size()) {
    return std::move(data_);
  }
  return {};
}

}  // namespace rldp2
}  // namespace ton
