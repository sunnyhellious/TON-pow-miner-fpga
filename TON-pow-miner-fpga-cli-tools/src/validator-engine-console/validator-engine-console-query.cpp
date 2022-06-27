/* 
    This file is part of TON Blockchain source code.

    TON Blockchain is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    TON Blockchain is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TON Blockchain.  If not, see <http://www.gnu.org/licenses/>.

    In addition, as a special exception, the copyright holders give permission 
    to link the code of portions of this program with the OpenSSL library. 
    You must obey the GNU General Public License in all respects for all 
    of the code used other than OpenSSL. If you modify file(s) with this 
    exception, you may extend this exception to your version of the file(s), 
    but you are not obligated to do so. If you do not wish to do so, delete this 
    exception statement from your version. If you delete this exception statement 
    from all source files in the program, then also delete it here.

    Copyright 2017-2020 Telegram Systems LLP
*/
#include "validator-engine-console-query.h"
#include "validator-engine-console.h"
#include "terminal/terminal.h"
#include "td/utils/filesystem.h"

#include <cctype>

Tokenizer::Tokenizer(td::BufferSlice data) : data_(std::move(data)) {
  remaining_ = data_.as_slice();
}

void Tokenizer::skipspc() {
  while (remaining_.size() > 0 && std::isspace(remaining_[0])) {
    remaining_.remove_prefix(1);
  }
}

bool Tokenizer::endl() {
  skipspc();
  return remaining_.size() == 0;
}

td::Result<td::Slice> Tokenizer::get_raw_token() {
  skipspc();
  if (remaining_.size() == 0) {
    return td::Status::Error("failed to parse token: EOL");
  }
  size_t idx = 0;
  while (idx < remaining_.size() && !std::isspace(remaining_[idx])) {
    idx++;
  }
  auto r = remaining_.copy().truncate(idx);
  remaining_.remove_prefix(idx);
  return r;
}

td::Result<td::Slice> Tokenizer::peek_raw_token() {
  skipspc();
  if (remaining_.size() == 0) {
    return td::Status::Error("failed to parse token: EOL");
  }
  size_t idx = 0;
  while (idx < remaining_.size() && !std::isspace(remaining_[idx])) {
    idx++;
  }
  auto r = remaining_.copy().truncate(idx);
  return r;
}

void Query::start_up() {
  auto R = [&]() -> td::Status {
    TRY_STATUS(run());
    TRY_STATUS(send());
    return td::Status::OK();
  }();
  if (R.is_error()) {
    handle_error(std::move(R));
  }
}

void Query::handle_error(td::Status error) {
  td::TerminalIO::out() << "Failed " << name() << " query: " << error << "\n";
  stop();
}

void Query::receive_wrap(td::BufferSlice R) {
  auto S = receive(std::move(R));
  if (S.is_error()) {
    handle_error(std::move(S));
  } else {
    td::actor::send_closure(console_, &ValidatorEngineConsole::got_result);
    stop();
  }
}

td::Status GetTimeQuery::run() {
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status GetTimeQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_getTime>();
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status GetTimeQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_time>(std::move(data), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "received validator time: time=" << f->time_ << "\n";
  return td::Status::OK();
}

td::Status GetHelpQuery::run() {
  if (tokenizer_.endl()) {
    return td::Status::OK();
  }
  TRY_RESULT_ASSIGN(command_, tokenizer_.get_token<std::string>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status GetHelpQuery::send() {
  td::actor::send_closure(console_, &ValidatorEngineConsole::show_help, command_, create_promise());
  return td::Status::OK();
}

td::Status GetHelpQuery::receive(td::BufferSlice R) {
  CHECK(R.size() == 0);
  return td::Status::OK();
}

td::Status GetLicenseQuery::run() {
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status GetLicenseQuery::send() {
  td::actor::send_closure(console_, &ValidatorEngineConsole::show_license, create_promise());
  return td::Status::OK();
}

td::Status GetLicenseQuery::receive(td::BufferSlice R) {
  CHECK(R.size() == 0);
  return td::Status::OK();
}

td::Status NewKeyQuery::run() {
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status NewKeyQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_generateKeyPair>();
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status NewKeyQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_keyHash>(std::move(data), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "created new key " << f->key_hash_.to_hex() << "\n";
  return td::Status::OK();
}

td::Status ImportPrivateKeyFileQuery::run() {
  TRY_RESULT_ASSIGN(file_name_, tokenizer_.get_token<std::string>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status ImportPrivateKeyFileQuery::send() {
  TRY_RESULT(data, td::read_file_secure(file_name_));
  TRY_RESULT(pk, ton::PrivateKey::import(data.as_slice()));
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_importPrivateKey>(pk.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status ImportPrivateKeyFileQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_keyHash>(std::move(data), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "imported key " << f->key_hash_.to_hex() << "\n";
  return td::Status::OK();
}

td::Status ExportPublicKeyQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status ExportPublicKeyQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_exportPublicKey>(key_hash_.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status ExportPublicKeyQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::PublicKey>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "got public key: " << td::base64_encode(data.as_slice()) << "\n";
  return td::Status::OK();
}

td::Status ExportPublicKeyFileQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(file_name_, tokenizer_.get_token<std::string>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status ExportPublicKeyFileQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_exportPublicKey>(key_hash_.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status ExportPublicKeyFileQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::PublicKey>(data.as_slice(), true),
                    "received incorrect answer: ");
  TRY_STATUS(td::write_file(file_name_, data.as_slice()));
  td::TerminalIO::out() << "got public key\n";
  return td::Status::OK();
}

td::Status SignQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(data_, tokenizer_.get_token<td::BufferSlice>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status SignQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_sign>(key_hash_.tl(), std::move(data_));
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status SignQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_signature>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "got signature " << td::base64_encode(f->signature_) << "\n";
  return td::Status::OK();
}

td::Status SignFileQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(in_file_, tokenizer_.get_token<std::string>());
  TRY_RESULT_ASSIGN(out_file_, tokenizer_.get_token<std::string>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status SignFileQuery::send() {
  TRY_RESULT(data, td::read_file(in_file_));
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_sign>(key_hash_.tl(), std::move(data));
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status SignFileQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_signature>(data.as_slice(), true),
                    "received incorrect answer: ");
  TRY_STATUS(td::write_file(out_file_, f->signature_.as_slice()));
  td::TerminalIO::out() << "got signature\n";
  return td::Status::OK();
}

td::Status AddAdnlAddrQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(category_, tokenizer_.get_token<td::uint32>());

  if (category_ > 15) {
    return td::Status::Error("too big category");
  }
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status AddAdnlAddrQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_addAdnlId>(key_hash_.tl(), category_);
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status AddAdnlAddrQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status AddDhtIdQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status AddDhtIdQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_addDhtId>(key_hash_.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status AddDhtIdQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status AddValidatorPermanentKeyQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(election_date_, tokenizer_.get_token<td::uint32>());
  TRY_RESULT_ASSIGN(expire_at_, tokenizer_.get_token<td::uint32>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status AddValidatorPermanentKeyQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_addValidatorPermanentKey>(
      key_hash_.tl(), election_date_, expire_at_);
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status AddValidatorPermanentKeyQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status AddValidatorTempKeyQuery::run() {
  TRY_RESULT_ASSIGN(perm_key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(expire_at_, tokenizer_.get_token<td::uint32>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status AddValidatorTempKeyQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_addValidatorTempKey>(
      perm_key_hash_.tl(), key_hash_.tl(), expire_at_);
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status AddValidatorTempKeyQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status ChangeFullNodeAdnlAddrQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status ChangeFullNodeAdnlAddrQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_changeFullNodeAdnlAddress>(key_hash_.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status ChangeFullNodeAdnlAddrQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status AddValidatorAdnlAddrQuery::run() {
  TRY_RESULT_ASSIGN(perm_key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(expire_at_, tokenizer_.get_token<td::uint32>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status AddValidatorAdnlAddrQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_addValidatorAdnlAddress>(
      perm_key_hash_.tl(), key_hash_.tl(), expire_at_);
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status AddValidatorAdnlAddrQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status AddLiteServerQuery::run() {
  TRY_RESULT_ASSIGN(port_, tokenizer_.get_token<td::uint16>());
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status AddLiteServerQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_addLiteserver>(key_hash_.tl(), port_);
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status AddLiteServerQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status DelAdnlAddrQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status DelAdnlAddrQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_delAdnlId>(key_hash_.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status DelAdnlAddrQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status DelDhtIdQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status DelDhtIdQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_delDhtId>(key_hash_.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status DelDhtIdQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status DelValidatorPermanentKeyQuery::run() {
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status DelValidatorPermanentKeyQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_delValidatorPermanentKey>(key_hash_.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status DelValidatorPermanentKeyQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status DelValidatorTempKeyQuery::run() {
  TRY_RESULT_ASSIGN(perm_key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status DelValidatorTempKeyQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_delValidatorTempKey>(perm_key_hash_.tl(),
                                                                                               key_hash_.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status DelValidatorTempKeyQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status DelValidatorAdnlAddrQuery::run() {
  TRY_RESULT_ASSIGN(perm_key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_RESULT_ASSIGN(key_hash_, tokenizer_.get_token<ton::PublicKeyHash>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status DelValidatorAdnlAddrQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_delValidatorAdnlAddress>(perm_key_hash_.tl(),
                                                                                                   key_hash_.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status DelValidatorAdnlAddrQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status GetConfigQuery::run() {
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status GetConfigQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_getConfig>();
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status GetConfigQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_jsonConfig>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "---------\n" << f->data_ << "--------\n";
  return td::Status::OK();
}

td::Status SetVerbosityQuery::run() {
  TRY_RESULT_ASSIGN(verbosity_, tokenizer_.get_token<td::uint8>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status SetVerbosityQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_setVerbosity>(verbosity_);
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status SetVerbosityQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status GetStatsQuery::run() {
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status GetStatsQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_getStats>();
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status GetStatsQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_stats>(data.as_slice(), true),
                    "received incorrect answer: ");

  for (auto &v : f->stats_) {
    td::TerminalIO::out() << v->key_ << "\t\t\t" << v->value_ << "\n";
  }
  return td::Status::OK();
}

td::Status QuitQuery::send() {
  td::actor::send_closure(console_, &ValidatorEngineConsole::close);
  return td::Status::OK();
}

td::Status AddNetworkAddressQuery::run() {
  TRY_RESULT_ASSIGN(addr_, tokenizer_.get_token<td::IPAddress>());
  TRY_RESULT_ASSIGN(cats_, tokenizer_.get_token_vector<td::int32>());
  TRY_RESULT_ASSIGN(prio_cats_, tokenizer_.get_token_vector<td::int32>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status AddNetworkAddressQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_addListeningPort>(
      static_cast<td::int32>(addr_.get_ipv4()), addr_.get_port(), std::move(cats_), std::move(prio_cats_));
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status AddNetworkAddressQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status AddNetworkProxyAddressQuery::run() {
  TRY_RESULT_ASSIGN(in_addr_, tokenizer_.get_token<td::IPAddress>());
  TRY_RESULT_ASSIGN(out_addr_, tokenizer_.get_token<td::IPAddress>());
  TRY_RESULT_ASSIGN(id_, tokenizer_.get_token<td::Bits256>());
  TRY_RESULT_ASSIGN(shared_secret_, tokenizer_.get_token<td::BufferSlice>());
  TRY_RESULT_ASSIGN(cats_, tokenizer_.get_token_vector<td::int32>());
  TRY_RESULT_ASSIGN(prio_cats_, tokenizer_.get_token_vector<td::int32>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status AddNetworkProxyAddressQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_addProxy>(
      static_cast<td::int32>(in_addr_.get_ipv4()), in_addr_.get_port(), static_cast<td::int32>(out_addr_.get_ipv4()),
      out_addr_.get_port(), ton::create_tl_object<ton::ton_api::adnl_proxy_fast>(id_, std::move(shared_secret_)),
      std::move(cats_), std::move(prio_cats_));
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status AddNetworkProxyAddressQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_success>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success\n";
  return td::Status::OK();
}

td::Status CreateElectionBidQuery::run() {
  TRY_RESULT_ASSIGN(date_, tokenizer_.get_token<td::uint32>());
  TRY_RESULT_ASSIGN(elector_addr_, tokenizer_.get_token<std::string>());
  TRY_RESULT_ASSIGN(wallet_, tokenizer_.get_token<std::string>());
  TRY_RESULT_ASSIGN(fname_, tokenizer_.get_token<std::string>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status CreateElectionBidQuery::send() {
  auto b =
      ton::create_serialize_tl_object<ton::ton_api::engine_validator_createElectionBid>(date_, elector_addr_, wallet_);
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status CreateElectionBidQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_electionBid>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success: permkey=" << f->perm_key_.to_hex() << " adnl=" << f->adnl_addr_.to_hex() << "\n";
  TRY_STATUS(td::write_file(fname_, f->to_send_payload_.as_slice()));
  return td::Status::OK();
}

td::Status CreateProposalVoteQuery::run() {
  TRY_RESULT_ASSIGN(data_, tokenizer_.get_token<std::string>());
  TRY_RESULT_ASSIGN(fname_, tokenizer_.get_token<std::string>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status CreateProposalVoteQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_createProposalVote>(td::BufferSlice(data_));
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status CreateProposalVoteQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_proposalVote>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success: permkey=" << f->perm_key_.to_hex() << "\n";
  TRY_STATUS(td::write_file(fname_, f->to_send_.as_slice()));
  return td::Status::OK();
}

td::Status CreateComplaintVoteQuery::run() {
  TRY_RESULT_ASSIGN(election_id_, tokenizer_.get_token<td::uint32>());
  TRY_RESULT_ASSIGN(data_, tokenizer_.get_token<std::string>());
  TRY_RESULT_ASSIGN(fname_, tokenizer_.get_token<std::string>());
  TRY_STATUS(tokenizer_.check_endl());
  return td::Status::OK();
}

td::Status CreateComplaintVoteQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_createComplaintVote>(election_id_,
                                                                                               td::BufferSlice(data_));
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status CreateComplaintVoteQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_proposalVote>(data.as_slice(), true),
                    "received incorrect answer: ");
  td::TerminalIO::out() << "success: permkey=" << f->perm_key_.to_hex() << "\n";
  TRY_STATUS(td::write_file(fname_, f->to_send_.as_slice()));
  return td::Status::OK();
}

td::Status CheckDhtServersQuery::run() {
  TRY_RESULT_ASSIGN(id_, tokenizer_.get_token<ton::PublicKeyHash>());
  return td::Status::OK();
}

td::Status CheckDhtServersQuery::send() {
  auto b = ton::create_serialize_tl_object<ton::ton_api::engine_validator_checkDhtServers>(id_.tl());
  td::actor::send_closure(console_, &ValidatorEngineConsole::envelope_send_query, std::move(b), create_promise());
  return td::Status::OK();
}

td::Status CheckDhtServersQuery::receive(td::BufferSlice data) {
  TRY_RESULT_PREFIX(f, ton::fetch_tl_object<ton::ton_api::engine_validator_dhtServersStatus>(data.as_slice(), true),
                    "received incorrect answer: ");
  for (auto &s : f->servers_) {
    td::TerminalIO::out() << "id=" << s->id_ << " status=" << (s->status_ ? "SUCCESS" : "FAIL") << "\n";
  }
  return td::Status::OK();
}
