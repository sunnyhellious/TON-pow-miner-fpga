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
#include "fec.h"
#include "td/utils/overloaded.h"
#include "auto/tl/ton_api.hpp"

namespace ton {

namespace fec {

tl_object_ptr<ton_api::fec_Type> FecType::tl() const {
  tl_object_ptr<ton_api::fec_Type> res;
  type_.visit(td::overloaded([&](const Empty &obj) { UNREACHABLE(); },
                             [&](const td::fec::RaptorQEncoder::Parameters &obj) {
                               res = create_tl_object<ton_api::fec_raptorQ>(static_cast<td::uint32>(obj.data_size),
                                                                            static_cast<td::uint32>(obj.symbol_size),
                                                                            static_cast<td::uint32>(obj.symbols_count));
                             },
                             [&](const td::fec::RoundRobinEncoder::Parameters &obj) {
                               res = create_tl_object<ton_api::fec_roundRobin>(
                                   static_cast<td::uint32>(obj.data_size), static_cast<td::uint32>(obj.symbol_size),
                                   static_cast<td::uint32>(obj.symbols_count));
                             },
                             [&](const td::fec::OnlineEncoder::Parameters &obj) {
                               res = create_tl_object<ton_api::fec_online>(static_cast<td::uint32>(obj.data_size),
                                                                           static_cast<td::uint32>(obj.symbol_size),
                                                                           static_cast<td::uint32>(obj.symbols_count));
                             }));
  return res;
}

td::Result<std::unique_ptr<td::fec::Decoder>> FecType::create_decoder() const {
  std::unique_ptr<td::fec::Decoder> res;
  type_.visit(td::overloaded(
      [&](const Empty &obj) { UNREACHABLE(); },
      [&](const td::fec::RaptorQEncoder::Parameters &obj) { res = td::fec::RaptorQDecoder::create(obj); },
      [&](const td::fec::RoundRobinEncoder::Parameters &obj) { res = td::fec::RoundRobinDecoder::create(obj); },
      [&](const td::fec::OnlineEncoder::Parameters &obj) { res = td::fec::OnlineDecoder::create(obj); }));
  return std::move(res);
}

td::Result<std::unique_ptr<td::fec::Encoder>> FecType::create_encoder(td::BufferSlice data) {
  std::unique_ptr<td::fec::Encoder> res;
  type_.visit(td::overloaded([&](const Empty &obj) { UNREACHABLE(); },
                             [&](const td::fec::RaptorQEncoder::Parameters &obj) {
                               auto R = td::fec::RaptorQEncoder::create(std::move(data), obj.symbol_size);
                               type_ = R->get_parameters();
                               res = std::move(R);
                             },
                             [&](const td::fec::RoundRobinEncoder::Parameters &obj) {
                               auto R = td::fec::RoundRobinEncoder::create(std::move(data), obj.symbol_size);
                               type_ = R->get_parameters();
                               res = std::move(R);
                             },
                             [&](const td::fec::OnlineEncoder::Parameters &obj) {
                               auto R = td::fec::OnlineEncoder::create(std::move(data), obj.symbol_size);
                               type_ = R->get_parameters();
                               res = std::move(R);
                             }));
  return std::move(res);
}

td::uint32 FecType::size() const {
  td::uint32 res = 0;
  type_.visit(td::overloaded([&](const Empty &obj) { UNREACHABLE(); },
                             [&](const auto &obj) { res = static_cast<td::uint32>(obj.data_size); }));
  return res;
}

td::uint32 FecType::symbols_count() const {
  td::uint32 res = 0;
  type_.visit(td::overloaded([&](const Empty &obj) { UNREACHABLE(); },
                             [&](const auto &obj) { res = static_cast<td::uint32>(obj.symbols_count); }));
  return res;
}

td::uint32 FecType::symbol_size() const {
  td::uint32 res = 0;
  type_.visit(td::overloaded([&](const Empty &obj) { UNREACHABLE(); },
                             [&](const auto &obj) { res = static_cast<td::uint32>(obj.symbol_size); }));
  return res;
}

td::Result<FecType> FecType::create(tl_object_ptr<ton_api::fec_Type> obj) {
  FecType T;
  ton_api::downcast_call(
      *obj.get(), td::overloaded(
                      [&](const ton_api::fec_raptorQ &obj) {
                        T.type_ = td::fec::RaptorQEncoder::Parameters{static_cast<size_t>(obj.data_size_),
                                                                      static_cast<size_t>(obj.symbol_size_),
                                                                      static_cast<size_t>(obj.symbols_count_)};
                      },
                      [&](const ton_api::fec_roundRobin &obj) {
                        T.type_ = td::fec::RoundRobinEncoder::Parameters{static_cast<size_t>(obj.data_size_),
                                                                         static_cast<size_t>(obj.symbol_size_),
                                                                         static_cast<size_t>(obj.symbols_count_)};
                      },
                      [&](const ton_api::fec_online &obj) {
                        T.type_ = td::fec::OnlineEncoder::Parameters{static_cast<size_t>(obj.data_size_),
                                                                     static_cast<size_t>(obj.symbol_size_),
                                                                     static_cast<size_t>(obj.symbols_count_)};
                      }));
  return T;
}

}  // namespace fec

}  // namespace ton
