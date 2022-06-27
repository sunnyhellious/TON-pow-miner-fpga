#include "tonlib_api.h"

#include "tl/tl_object_parse.h"
#include "tl/tl_object_store.h"
#include "td/utils/int_types.h"

#include "td/utils/common.h"
#include "td/utils/format.h"
#include "td/utils/logging.h"
#include "td/utils/tl_parsers.h"
#include "td/utils/tl_storers.h"

namespace ton {
namespace tonlib_api {

std::string to_string(const BaseObject &value) {
  td::TlStorerToString storer;
  value.store(storer, "");
  return storer.move_as_str();
}

accountAddress::accountAddress()
  : account_address_()
{}

accountAddress::accountAddress(std::string const &account_address_)
  : account_address_(std::move(account_address_))
{}

const std::int32_t accountAddress::ID;

void accountAddress::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "accountAddress");
    s.store_field("account_address", account_address_);
    s.store_class_end();
  }
}

accountList::accountList()
  : accounts_()
{}

accountList::accountList(std::vector<object_ptr<fullAccountState>> &&accounts_)
  : accounts_(std::move(accounts_))
{}

const std::int32_t accountList::ID;

void accountList::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "accountList");
    { const std::vector<object_ptr<fullAccountState>> &v = accounts_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("accounts", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

accountRevisionList::accountRevisionList()
  : revisions_()
{}

accountRevisionList::accountRevisionList(std::vector<object_ptr<fullAccountState>> &&revisions_)
  : revisions_(std::move(revisions_))
{}

const std::int32_t accountRevisionList::ID;

void accountRevisionList::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "accountRevisionList");
    { const std::vector<object_ptr<fullAccountState>> &v = revisions_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("revisions", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

raw_accountState::raw_accountState()
  : code_()
  , data_()
  , frozen_hash_()
{}

raw_accountState::raw_accountState(std::string const &code_, std::string const &data_, std::string const &frozen_hash_)
  : code_(std::move(code_))
  , data_(std::move(data_))
  , frozen_hash_(std::move(frozen_hash_))
{}

const std::int32_t raw_accountState::ID;

void raw_accountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_accountState");
    s.store_bytes_field("code", code_);
    s.store_bytes_field("data", data_);
    s.store_bytes_field("frozen_hash", frozen_hash_);
    s.store_class_end();
  }
}

wallet_v3_accountState::wallet_v3_accountState()
  : wallet_id_()
  , seqno_()
{}

wallet_v3_accountState::wallet_v3_accountState(std::int64_t wallet_id_, std::int32_t seqno_)
  : wallet_id_(wallet_id_)
  , seqno_(seqno_)
{}

const std::int32_t wallet_v3_accountState::ID;

void wallet_v3_accountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "wallet_v3_accountState");
    s.store_field("wallet_id", wallet_id_);
    s.store_field("seqno", seqno_);
    s.store_class_end();
  }
}

wallet_highload_v1_accountState::wallet_highload_v1_accountState()
  : wallet_id_()
  , seqno_()
{}

wallet_highload_v1_accountState::wallet_highload_v1_accountState(std::int64_t wallet_id_, std::int32_t seqno_)
  : wallet_id_(wallet_id_)
  , seqno_(seqno_)
{}

const std::int32_t wallet_highload_v1_accountState::ID;

void wallet_highload_v1_accountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "wallet_highload_v1_accountState");
    s.store_field("wallet_id", wallet_id_);
    s.store_field("seqno", seqno_);
    s.store_class_end();
  }
}

wallet_highload_v2_accountState::wallet_highload_v2_accountState()
  : wallet_id_()
{}

wallet_highload_v2_accountState::wallet_highload_v2_accountState(std::int64_t wallet_id_)
  : wallet_id_(wallet_id_)
{}

const std::int32_t wallet_highload_v2_accountState::ID;

void wallet_highload_v2_accountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "wallet_highload_v2_accountState");
    s.store_field("wallet_id", wallet_id_);
    s.store_class_end();
  }
}

dns_accountState::dns_accountState()
  : wallet_id_()
{}

dns_accountState::dns_accountState(std::int64_t wallet_id_)
  : wallet_id_(wallet_id_)
{}

const std::int32_t dns_accountState::ID;

void dns_accountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_accountState");
    s.store_field("wallet_id", wallet_id_);
    s.store_class_end();
  }
}

rwallet_accountState::rwallet_accountState()
  : wallet_id_()
  , seqno_()
  , unlocked_balance_()
  , config_()
{}

rwallet_accountState::rwallet_accountState(std::int64_t wallet_id_, std::int32_t seqno_, std::int64_t unlocked_balance_, object_ptr<rwallet_config> &&config_)
  : wallet_id_(wallet_id_)
  , seqno_(seqno_)
  , unlocked_balance_(unlocked_balance_)
  , config_(std::move(config_))
{}

const std::int32_t rwallet_accountState::ID;

void rwallet_accountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rwallet_accountState");
    s.store_field("wallet_id", wallet_id_);
    s.store_field("seqno", seqno_);
    s.store_field("unlocked_balance", unlocked_balance_);
    if (config_ == nullptr) { s.store_field("config", "null"); } else { config_->store(s, "config"); }
    s.store_class_end();
  }
}

pchan_accountState::pchan_accountState()
  : config_()
  , state_()
  , description_()
{}

pchan_accountState::pchan_accountState(object_ptr<pchan_config> &&config_, object_ptr<pchan_State> &&state_, std::string const &description_)
  : config_(std::move(config_))
  , state_(std::move(state_))
  , description_(std::move(description_))
{}

const std::int32_t pchan_accountState::ID;

void pchan_accountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_accountState");
    if (config_ == nullptr) { s.store_field("config", "null"); } else { config_->store(s, "config"); }
    if (state_ == nullptr) { s.store_field("state", "null"); } else { state_->store(s, "state"); }
    s.store_field("description", description_);
    s.store_class_end();
  }
}

uninited_accountState::uninited_accountState()
  : frozen_hash_()
{}

uninited_accountState::uninited_accountState(std::string const &frozen_hash_)
  : frozen_hash_(std::move(frozen_hash_))
{}

const std::int32_t uninited_accountState::ID;

void uninited_accountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "uninited_accountState");
    s.store_bytes_field("frozen_hash", frozen_hash_);
    s.store_class_end();
  }
}

actionNoop::actionNoop() {
}

const std::int32_t actionNoop::ID;

void actionNoop::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "actionNoop");
    s.store_class_end();
  }
}

actionMsg::actionMsg()
  : messages_()
  , allow_send_to_uninited_()
{}

actionMsg::actionMsg(std::vector<object_ptr<msg_message>> &&messages_, bool allow_send_to_uninited_)
  : messages_(std::move(messages_))
  , allow_send_to_uninited_(allow_send_to_uninited_)
{}

const std::int32_t actionMsg::ID;

void actionMsg::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "actionMsg");
    { const std::vector<object_ptr<msg_message>> &v = messages_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("messages", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_field("allow_send_to_uninited", allow_send_to_uninited_);
    s.store_class_end();
  }
}

actionDns::actionDns()
  : actions_()
{}

actionDns::actionDns(std::vector<object_ptr<dns_Action>> &&actions_)
  : actions_(std::move(actions_))
{}

const std::int32_t actionDns::ID;

void actionDns::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "actionDns");
    { const std::vector<object_ptr<dns_Action>> &v = actions_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("actions", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

actionPchan::actionPchan()
  : action_()
{}

actionPchan::actionPchan(object_ptr<pchan_Action> &&action_)
  : action_(std::move(action_))
{}

const std::int32_t actionPchan::ID;

void actionPchan::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "actionPchan");
    if (action_ == nullptr) { s.store_field("action", "null"); } else { action_->store(s, "action"); }
    s.store_class_end();
  }
}

actionRwallet::actionRwallet()
  : action_()
{}

actionRwallet::actionRwallet(object_ptr<rwallet_actionInit> &&action_)
  : action_(std::move(action_))
{}

const std::int32_t actionRwallet::ID;

void actionRwallet::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "actionRwallet");
    if (action_ == nullptr) { s.store_field("action", "null"); } else { action_->store(s, "action"); }
    s.store_class_end();
  }
}

adnlAddress::adnlAddress()
  : adnl_address_()
{}

adnlAddress::adnlAddress(std::string const &adnl_address_)
  : adnl_address_(std::move(adnl_address_))
{}

const std::int32_t adnlAddress::ID;

void adnlAddress::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnlAddress");
    s.store_field("adnl_address", adnl_address_);
    s.store_class_end();
  }
}

bip39Hints::bip39Hints()
  : words_()
{}

bip39Hints::bip39Hints(std::vector<std::string> &&words_)
  : words_(std::move(words_))
{}

const std::int32_t bip39Hints::ID;

void bip39Hints::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "bip39Hints");
    { const std::vector<std::string> &v = words_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("words", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

config::config()
  : config_()
  , blockchain_name_()
  , use_callbacks_for_network_()
  , ignore_cache_()
{}

config::config(std::string const &config_, std::string const &blockchain_name_, bool use_callbacks_for_network_, bool ignore_cache_)
  : config_(std::move(config_))
  , blockchain_name_(std::move(blockchain_name_))
  , use_callbacks_for_network_(use_callbacks_for_network_)
  , ignore_cache_(ignore_cache_)
{}

const std::int32_t config::ID;

void config::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "config");
    s.store_field("config", config_);
    s.store_field("blockchain_name", blockchain_name_);
    s.store_field("use_callbacks_for_network", use_callbacks_for_network_);
    s.store_field("ignore_cache", ignore_cache_);
    s.store_class_end();
  }
}

data::data()
  : bytes_()
{}

data::data(td::SecureString &&bytes_)
  : bytes_(std::move(bytes_))
{}

const std::int32_t data::ID;

void data::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "data");
    s.store_bytes_field("bytes", bytes_);
    s.store_class_end();
  }
}

error::error()
  : code_()
  , message_()
{}

error::error(std::int32_t code_, std::string const &message_)
  : code_(code_)
  , message_(std::move(message_))
{}

const std::int32_t error::ID;

void error::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "error");
    s.store_field("code", code_);
    s.store_field("message", message_);
    s.store_class_end();
  }
}

exportedEncryptedKey::exportedEncryptedKey()
  : data_()
{}

exportedEncryptedKey::exportedEncryptedKey(td::SecureString &&data_)
  : data_(std::move(data_))
{}

const std::int32_t exportedEncryptedKey::ID;

void exportedEncryptedKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "exportedEncryptedKey");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

exportedKey::exportedKey()
  : word_list_()
{}

exportedKey::exportedKey(std::vector<td::SecureString> &&word_list_)
  : word_list_(std::move(word_list_))
{}

const std::int32_t exportedKey::ID;

void exportedKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "exportedKey");
    { const std::vector<td::SecureString> &v = word_list_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("word_list", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

exportedPemKey::exportedPemKey()
  : pem_()
{}

exportedPemKey::exportedPemKey(td::SecureString &&pem_)
  : pem_(std::move(pem_))
{}

const std::int32_t exportedPemKey::ID;

void exportedPemKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "exportedPemKey");
    s.store_field("pem", pem_);
    s.store_class_end();
  }
}

exportedUnencryptedKey::exportedUnencryptedKey()
  : data_()
{}

exportedUnencryptedKey::exportedUnencryptedKey(td::SecureString &&data_)
  : data_(std::move(data_))
{}

const std::int32_t exportedUnencryptedKey::ID;

void exportedUnencryptedKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "exportedUnencryptedKey");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

fees::fees()
  : in_fwd_fee_()
  , storage_fee_()
  , gas_fee_()
  , fwd_fee_()
{}

fees::fees(std::int64_t in_fwd_fee_, std::int64_t storage_fee_, std::int64_t gas_fee_, std::int64_t fwd_fee_)
  : in_fwd_fee_(in_fwd_fee_)
  , storage_fee_(storage_fee_)
  , gas_fee_(gas_fee_)
  , fwd_fee_(fwd_fee_)
{}

const std::int32_t fees::ID;

void fees::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "fees");
    s.store_field("in_fwd_fee", in_fwd_fee_);
    s.store_field("storage_fee", storage_fee_);
    s.store_field("gas_fee", gas_fee_);
    s.store_field("fwd_fee", fwd_fee_);
    s.store_class_end();
  }
}

fullAccountState::fullAccountState()
  : address_()
  , balance_()
  , last_transaction_id_()
  , block_id_()
  , sync_utime_()
  , account_state_()
  , revision_()
{}

fullAccountState::fullAccountState(object_ptr<accountAddress> &&address_, std::int64_t balance_, object_ptr<internal_transactionId> &&last_transaction_id_, object_ptr<ton_blockIdExt> &&block_id_, std::int64_t sync_utime_, object_ptr<AccountState> &&account_state_, std::int32_t revision_)
  : address_(std::move(address_))
  , balance_(balance_)
  , last_transaction_id_(std::move(last_transaction_id_))
  , block_id_(std::move(block_id_))
  , sync_utime_(sync_utime_)
  , account_state_(std::move(account_state_))
  , revision_(revision_)
{}

const std::int32_t fullAccountState::ID;

void fullAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "fullAccountState");
    if (address_ == nullptr) { s.store_field("address", "null"); } else { address_->store(s, "address"); }
    s.store_field("balance", balance_);
    if (last_transaction_id_ == nullptr) { s.store_field("last_transaction_id", "null"); } else { last_transaction_id_->store(s, "last_transaction_id"); }
    if (block_id_ == nullptr) { s.store_field("block_id", "null"); } else { block_id_->store(s, "block_id"); }
    s.store_field("sync_utime", sync_utime_);
    if (account_state_ == nullptr) { s.store_field("account_state", "null"); } else { account_state_->store(s, "account_state"); }
    s.store_field("revision", revision_);
    s.store_class_end();
  }
}

raw_initialAccountState::raw_initialAccountState()
  : code_()
  , data_()
{}

raw_initialAccountState::raw_initialAccountState(std::string const &code_, std::string const &data_)
  : code_(std::move(code_))
  , data_(std::move(data_))
{}

const std::int32_t raw_initialAccountState::ID;

void raw_initialAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_initialAccountState");
    s.store_bytes_field("code", code_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

wallet_v3_initialAccountState::wallet_v3_initialAccountState()
  : public_key_()
  , wallet_id_()
{}

wallet_v3_initialAccountState::wallet_v3_initialAccountState(std::string const &public_key_, std::int64_t wallet_id_)
  : public_key_(std::move(public_key_))
  , wallet_id_(wallet_id_)
{}

const std::int32_t wallet_v3_initialAccountState::ID;

void wallet_v3_initialAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "wallet_v3_initialAccountState");
    s.store_field("public_key", public_key_);
    s.store_field("wallet_id", wallet_id_);
    s.store_class_end();
  }
}

wallet_highload_v1_initialAccountState::wallet_highload_v1_initialAccountState()
  : public_key_()
  , wallet_id_()
{}

wallet_highload_v1_initialAccountState::wallet_highload_v1_initialAccountState(std::string const &public_key_, std::int64_t wallet_id_)
  : public_key_(std::move(public_key_))
  , wallet_id_(wallet_id_)
{}

const std::int32_t wallet_highload_v1_initialAccountState::ID;

void wallet_highload_v1_initialAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "wallet_highload_v1_initialAccountState");
    s.store_field("public_key", public_key_);
    s.store_field("wallet_id", wallet_id_);
    s.store_class_end();
  }
}

wallet_highload_v2_initialAccountState::wallet_highload_v2_initialAccountState()
  : public_key_()
  , wallet_id_()
{}

wallet_highload_v2_initialAccountState::wallet_highload_v2_initialAccountState(std::string const &public_key_, std::int64_t wallet_id_)
  : public_key_(std::move(public_key_))
  , wallet_id_(wallet_id_)
{}

const std::int32_t wallet_highload_v2_initialAccountState::ID;

void wallet_highload_v2_initialAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "wallet_highload_v2_initialAccountState");
    s.store_field("public_key", public_key_);
    s.store_field("wallet_id", wallet_id_);
    s.store_class_end();
  }
}

rwallet_initialAccountState::rwallet_initialAccountState()
  : init_public_key_()
  , public_key_()
  , wallet_id_()
{}

rwallet_initialAccountState::rwallet_initialAccountState(std::string const &init_public_key_, std::string const &public_key_, std::int64_t wallet_id_)
  : init_public_key_(std::move(init_public_key_))
  , public_key_(std::move(public_key_))
  , wallet_id_(wallet_id_)
{}

const std::int32_t rwallet_initialAccountState::ID;

void rwallet_initialAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rwallet_initialAccountState");
    s.store_field("init_public_key", init_public_key_);
    s.store_field("public_key", public_key_);
    s.store_field("wallet_id", wallet_id_);
    s.store_class_end();
  }
}

dns_initialAccountState::dns_initialAccountState()
  : public_key_()
  , wallet_id_()
{}

dns_initialAccountState::dns_initialAccountState(std::string const &public_key_, std::int64_t wallet_id_)
  : public_key_(std::move(public_key_))
  , wallet_id_(wallet_id_)
{}

const std::int32_t dns_initialAccountState::ID;

void dns_initialAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_initialAccountState");
    s.store_field("public_key", public_key_);
    s.store_field("wallet_id", wallet_id_);
    s.store_class_end();
  }
}

pchan_initialAccountState::pchan_initialAccountState()
  : config_()
{}

pchan_initialAccountState::pchan_initialAccountState(object_ptr<pchan_config> &&config_)
  : config_(std::move(config_))
{}

const std::int32_t pchan_initialAccountState::ID;

void pchan_initialAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_initialAccountState");
    if (config_ == nullptr) { s.store_field("config", "null"); } else { config_->store(s, "config"); }
    s.store_class_end();
  }
}

inputKeyRegular::inputKeyRegular()
  : key_()
  , local_password_()
{}

inputKeyRegular::inputKeyRegular(object_ptr<key> &&key_, td::SecureString &&local_password_)
  : key_(std::move(key_))
  , local_password_(std::move(local_password_))
{}

const std::int32_t inputKeyRegular::ID;

void inputKeyRegular::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "inputKeyRegular");
    if (key_ == nullptr) { s.store_field("key", "null"); } else { key_->store(s, "key"); }
    s.store_bytes_field("local_password", local_password_);
    s.store_class_end();
  }
}

inputKeyFake::inputKeyFake() {
}

const std::int32_t inputKeyFake::ID;

void inputKeyFake::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "inputKeyFake");
    s.store_class_end();
  }
}

key::key()
  : public_key_()
  , secret_()
{}

key::key(std::string const &public_key_, td::SecureString &&secret_)
  : public_key_(std::move(public_key_))
  , secret_(std::move(secret_))
{}

const std::int32_t key::ID;

void key::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "key");
    s.store_field("public_key", public_key_);
    s.store_bytes_field("secret", secret_);
    s.store_class_end();
  }
}

keyStoreTypeDirectory::keyStoreTypeDirectory()
  : directory_()
{}

keyStoreTypeDirectory::keyStoreTypeDirectory(std::string const &directory_)
  : directory_(std::move(directory_))
{}

const std::int32_t keyStoreTypeDirectory::ID;

void keyStoreTypeDirectory::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "keyStoreTypeDirectory");
    s.store_field("directory", directory_);
    s.store_class_end();
  }
}

keyStoreTypeInMemory::keyStoreTypeInMemory() {
}

const std::int32_t keyStoreTypeInMemory::ID;

void keyStoreTypeInMemory::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "keyStoreTypeInMemory");
    s.store_class_end();
  }
}

logStreamDefault::logStreamDefault() {
}

const std::int32_t logStreamDefault::ID;

void logStreamDefault::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "logStreamDefault");
    s.store_class_end();
  }
}

logStreamFile::logStreamFile()
  : path_()
  , max_file_size_()
{}

logStreamFile::logStreamFile(std::string const &path_, std::int64_t max_file_size_)
  : path_(std::move(path_))
  , max_file_size_(max_file_size_)
{}

const std::int32_t logStreamFile::ID;

void logStreamFile::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "logStreamFile");
    s.store_field("path", path_);
    s.store_field("max_file_size", max_file_size_);
    s.store_class_end();
  }
}

logStreamEmpty::logStreamEmpty() {
}

const std::int32_t logStreamEmpty::ID;

void logStreamEmpty::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "logStreamEmpty");
    s.store_class_end();
  }
}

logTags::logTags()
  : tags_()
{}

logTags::logTags(std::vector<std::string> &&tags_)
  : tags_(std::move(tags_))
{}

const std::int32_t logTags::ID;

void logTags::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "logTags");
    { const std::vector<std::string> &v = tags_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("tags", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

logVerbosityLevel::logVerbosityLevel()
  : verbosity_level_()
{}

logVerbosityLevel::logVerbosityLevel(std::int32_t verbosity_level_)
  : verbosity_level_(verbosity_level_)
{}

const std::int32_t logVerbosityLevel::ID;

void logVerbosityLevel::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "logVerbosityLevel");
    s.store_field("verbosity_level", verbosity_level_);
    s.store_class_end();
  }
}

ok::ok() {
}

const std::int32_t ok::ID;

void ok::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "ok");
    s.store_class_end();
  }
}

options::options()
  : config_()
  , keystore_type_()
{}

options::options(object_ptr<config> &&config_, object_ptr<KeyStoreType> &&keystore_type_)
  : config_(std::move(config_))
  , keystore_type_(std::move(keystore_type_))
{}

const std::int32_t options::ID;

void options::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "options");
    if (config_ == nullptr) { s.store_field("config", "null"); } else { config_->store(s, "config"); }
    if (keystore_type_ == nullptr) { s.store_field("keystore_type", "null"); } else { keystore_type_->store(s, "keystore_type"); }
    s.store_class_end();
  }
}

syncStateDone::syncStateDone() {
}

const std::int32_t syncStateDone::ID;

void syncStateDone::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "syncStateDone");
    s.store_class_end();
  }
}

syncStateInProgress::syncStateInProgress()
  : from_seqno_()
  , to_seqno_()
  , current_seqno_()
{}

syncStateInProgress::syncStateInProgress(std::int32_t from_seqno_, std::int32_t to_seqno_, std::int32_t current_seqno_)
  : from_seqno_(from_seqno_)
  , to_seqno_(to_seqno_)
  , current_seqno_(current_seqno_)
{}

const std::int32_t syncStateInProgress::ID;

void syncStateInProgress::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "syncStateInProgress");
    s.store_field("from_seqno", from_seqno_);
    s.store_field("to_seqno", to_seqno_);
    s.store_field("current_seqno", current_seqno_);
    s.store_class_end();
  }
}

unpackedAccountAddress::unpackedAccountAddress()
  : workchain_id_()
  , bounceable_()
  , testnet_()
  , addr_()
{}

unpackedAccountAddress::unpackedAccountAddress(std::int32_t workchain_id_, bool bounceable_, bool testnet_, std::string const &addr_)
  : workchain_id_(workchain_id_)
  , bounceable_(bounceable_)
  , testnet_(testnet_)
  , addr_(std::move(addr_))
{}

const std::int32_t unpackedAccountAddress::ID;

void unpackedAccountAddress::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "unpackedAccountAddress");
    s.store_field("workchain_id", workchain_id_);
    s.store_field("bounceable", bounceable_);
    s.store_field("testnet", testnet_);
    s.store_bytes_field("addr", addr_);
    s.store_class_end();
  }
}

updateSendLiteServerQuery::updateSendLiteServerQuery()
  : id_()
  , data_()
{}

updateSendLiteServerQuery::updateSendLiteServerQuery(std::int64_t id_, std::string const &data_)
  : id_(id_)
  , data_(std::move(data_))
{}

const std::int32_t updateSendLiteServerQuery::ID;

void updateSendLiteServerQuery::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "updateSendLiteServerQuery");
    s.store_field("id", id_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

updateSyncState::updateSyncState()
  : sync_state_()
{}

updateSyncState::updateSyncState(object_ptr<SyncState> &&sync_state_)
  : sync_state_(std::move(sync_state_))
{}

const std::int32_t updateSyncState::ID;

void updateSyncState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "updateSyncState");
    if (sync_state_ == nullptr) { s.store_field("sync_state", "null"); } else { sync_state_->store(s, "sync_state"); }
    s.store_class_end();
  }
}

blocks_accountTransactionId::blocks_accountTransactionId()
  : account_()
  , lt_()
{}

blocks_accountTransactionId::blocks_accountTransactionId(std::string const &account_, std::int64_t lt_)
  : account_(std::move(account_))
  , lt_(lt_)
{}

const std::int32_t blocks_accountTransactionId::ID;

void blocks_accountTransactionId::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_accountTransactionId");
    s.store_bytes_field("account", account_);
    s.store_field("lt", lt_);
    s.store_class_end();
  }
}

blocks_header::blocks_header()
  : id_()
  , global_id_()
  , version_()
  , after_merge_()
  , after_split_()
  , before_split_()
  , want_merge_()
  , want_split_()
  , validator_list_hash_short_()
  , catchain_seqno_()
  , min_ref_mc_seqno_()
  , is_key_block_()
  , prev_key_block_seqno_()
  , start_lt_()
  , end_lt_()
  , vert_seqno_()
  , prev_blocks_()
{}

blocks_header::blocks_header(object_ptr<ton_blockIdExt> &&id_, std::int32_t global_id_, std::int32_t version_, bool after_merge_, bool after_split_, bool before_split_, bool want_merge_, bool want_split_, std::int32_t validator_list_hash_short_, std::int32_t catchain_seqno_, std::int32_t min_ref_mc_seqno_, bool is_key_block_, std::int32_t prev_key_block_seqno_, std::int64_t start_lt_, std::int64_t end_lt_, std::int32_t vert_seqno_, std::vector<object_ptr<ton_blockIdExt>> &&prev_blocks_)
  : id_(std::move(id_))
  , global_id_(global_id_)
  , version_(version_)
  , after_merge_(after_merge_)
  , after_split_(after_split_)
  , before_split_(before_split_)
  , want_merge_(want_merge_)
  , want_split_(want_split_)
  , validator_list_hash_short_(validator_list_hash_short_)
  , catchain_seqno_(catchain_seqno_)
  , min_ref_mc_seqno_(min_ref_mc_seqno_)
  , is_key_block_(is_key_block_)
  , prev_key_block_seqno_(prev_key_block_seqno_)
  , start_lt_(start_lt_)
  , end_lt_(end_lt_)
  , vert_seqno_(vert_seqno_)
  , prev_blocks_(std::move(prev_blocks_))
{}

const std::int32_t blocks_header::ID;

void blocks_header::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_header");
  std::int32_t var0;
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_field("global_id", global_id_);
    s.store_field("version", version_);
    s.store_field("after_merge", after_merge_);
    s.store_field("after_split", after_split_);
    s.store_field("before_split", before_split_);
    s.store_field("want_merge", want_merge_);
    s.store_field("want_split", want_split_);
    s.store_field("validator_list_hash_short", validator_list_hash_short_);
    s.store_field("catchain_seqno", catchain_seqno_);
    s.store_field("min_ref_mc_seqno", min_ref_mc_seqno_);
    s.store_field("is_key_block", is_key_block_);
    s.store_field("prev_key_block_seqno", prev_key_block_seqno_);
    s.store_field("start_lt", start_lt_);
    s.store_field("end_lt", end_lt_);
    s.store_field("vert_seqno", (var0 = vert_seqno_));
    { const std::vector<object_ptr<ton_blockIdExt>> &v = prev_blocks_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("prev_blocks", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

blocks_masterchainInfo::blocks_masterchainInfo()
  : last_()
  , state_root_hash_()
  , init_()
{}

blocks_masterchainInfo::blocks_masterchainInfo(object_ptr<ton_blockIdExt> &&last_, std::string const &state_root_hash_, object_ptr<ton_blockIdExt> &&init_)
  : last_(std::move(last_))
  , state_root_hash_(std::move(state_root_hash_))
  , init_(std::move(init_))
{}

const std::int32_t blocks_masterchainInfo::ID;

void blocks_masterchainInfo::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_masterchainInfo");
    if (last_ == nullptr) { s.store_field("last", "null"); } else { last_->store(s, "last"); }
    s.store_bytes_field("state_root_hash", state_root_hash_);
    if (init_ == nullptr) { s.store_field("init", "null"); } else { init_->store(s, "init"); }
    s.store_class_end();
  }
}

blocks_shards::blocks_shards()
  : shards_()
{}

blocks_shards::blocks_shards(std::vector<object_ptr<ton_blockIdExt>> &&shards_)
  : shards_(std::move(shards_))
{}

const std::int32_t blocks_shards::ID;

void blocks_shards::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_shards");
    { const std::vector<object_ptr<ton_blockIdExt>> &v = shards_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("shards", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

blocks_transactions::blocks_transactions()
  : id_()
  , req_count_()
  , incomplete_()
  , transactions_()
{}

blocks_transactions::blocks_transactions(object_ptr<ton_blockIdExt> &&id_, std::int32_t req_count_, bool incomplete_, std::vector<object_ptr<blocks_shortTxId>> &&transactions_)
  : id_(std::move(id_))
  , req_count_(req_count_)
  , incomplete_(incomplete_)
  , transactions_(std::move(transactions_))
{}

const std::int32_t blocks_transactions::ID;

void blocks_transactions::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_transactions");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_field("req_count", req_count_);
    s.store_field("incomplete", incomplete_);
    { const std::vector<object_ptr<blocks_shortTxId>> &v = transactions_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("transactions", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

dns_actionDeleteAll::dns_actionDeleteAll() {
}

const std::int32_t dns_actionDeleteAll::ID;

void dns_actionDeleteAll::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_actionDeleteAll");
    s.store_class_end();
  }
}

dns_actionDelete::dns_actionDelete()
  : name_()
  , category_()
{}

dns_actionDelete::dns_actionDelete(std::string const &name_, std::int32_t category_)
  : name_(std::move(name_))
  , category_(category_)
{}

const std::int32_t dns_actionDelete::ID;

void dns_actionDelete::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_actionDelete");
    s.store_field("name", name_);
    s.store_field("category", category_);
    s.store_class_end();
  }
}

dns_actionSet::dns_actionSet()
  : entry_()
{}

dns_actionSet::dns_actionSet(object_ptr<dns_entry> &&entry_)
  : entry_(std::move(entry_))
{}

const std::int32_t dns_actionSet::ID;

void dns_actionSet::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_actionSet");
    if (entry_ == nullptr) { s.store_field("entry", "null"); } else { entry_->store(s, "entry"); }
    s.store_class_end();
  }
}

dns_entry::dns_entry()
  : name_()
  , category_()
  , entry_()
{}

dns_entry::dns_entry(std::string const &name_, std::int32_t category_, object_ptr<dns_EntryData> &&entry_)
  : name_(std::move(name_))
  , category_(category_)
  , entry_(std::move(entry_))
{}

const std::int32_t dns_entry::ID;

void dns_entry::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_entry");
    s.store_field("name", name_);
    s.store_field("category", category_);
    if (entry_ == nullptr) { s.store_field("entry", "null"); } else { entry_->store(s, "entry"); }
    s.store_class_end();
  }
}

dns_entryDataUnknown::dns_entryDataUnknown()
  : bytes_()
{}

dns_entryDataUnknown::dns_entryDataUnknown(std::string const &bytes_)
  : bytes_(std::move(bytes_))
{}

const std::int32_t dns_entryDataUnknown::ID;

void dns_entryDataUnknown::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_entryDataUnknown");
    s.store_bytes_field("bytes", bytes_);
    s.store_class_end();
  }
}

dns_entryDataText::dns_entryDataText()
  : text_()
{}

dns_entryDataText::dns_entryDataText(std::string const &text_)
  : text_(std::move(text_))
{}

const std::int32_t dns_entryDataText::ID;

void dns_entryDataText::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_entryDataText");
    s.store_field("text", text_);
    s.store_class_end();
  }
}

dns_entryDataNextResolver::dns_entryDataNextResolver()
  : resolver_()
{}

dns_entryDataNextResolver::dns_entryDataNextResolver(object_ptr<accountAddress> &&resolver_)
  : resolver_(std::move(resolver_))
{}

const std::int32_t dns_entryDataNextResolver::ID;

void dns_entryDataNextResolver::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_entryDataNextResolver");
    if (resolver_ == nullptr) { s.store_field("resolver", "null"); } else { resolver_->store(s, "resolver"); }
    s.store_class_end();
  }
}

dns_entryDataSmcAddress::dns_entryDataSmcAddress()
  : smc_address_()
{}

dns_entryDataSmcAddress::dns_entryDataSmcAddress(object_ptr<accountAddress> &&smc_address_)
  : smc_address_(std::move(smc_address_))
{}

const std::int32_t dns_entryDataSmcAddress::ID;

void dns_entryDataSmcAddress::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_entryDataSmcAddress");
    if (smc_address_ == nullptr) { s.store_field("smc_address", "null"); } else { smc_address_->store(s, "smc_address"); }
    s.store_class_end();
  }
}

dns_entryDataAdnlAddress::dns_entryDataAdnlAddress()
  : adnl_address_()
{}

dns_entryDataAdnlAddress::dns_entryDataAdnlAddress(object_ptr<adnlAddress> &&adnl_address_)
  : adnl_address_(std::move(adnl_address_))
{}

const std::int32_t dns_entryDataAdnlAddress::ID;

void dns_entryDataAdnlAddress::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_entryDataAdnlAddress");
    if (adnl_address_ == nullptr) { s.store_field("adnl_address", "null"); } else { adnl_address_->store(s, "adnl_address"); }
    s.store_class_end();
  }
}

dns_resolved::dns_resolved()
  : entries_()
{}

dns_resolved::dns_resolved(std::vector<object_ptr<dns_entry>> &&entries_)
  : entries_(std::move(entries_))
{}

const std::int32_t dns_resolved::ID;

void dns_resolved::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_resolved");
    { const std::vector<object_ptr<dns_entry>> &v = entries_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("entries", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

ton_blockId::ton_blockId()
  : workchain_()
  , shard_()
  , seqno_()
{}

ton_blockId::ton_blockId(std::int32_t workchain_, std::int64_t shard_, std::int32_t seqno_)
  : workchain_(workchain_)
  , shard_(shard_)
  , seqno_(seqno_)
{}

const std::int32_t ton_blockId::ID;

void ton_blockId::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "ton_blockId");
    s.store_field("workchain", workchain_);
    s.store_field("shard", shard_);
    s.store_field("seqno", seqno_);
    s.store_class_end();
  }
}

internal_transactionId::internal_transactionId()
  : lt_()
  , hash_()
{}

internal_transactionId::internal_transactionId(std::int64_t lt_, std::string const &hash_)
  : lt_(lt_)
  , hash_(std::move(hash_))
{}

const std::int32_t internal_transactionId::ID;

void internal_transactionId::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "internal_transactionId");
    s.store_field("lt", lt_);
    s.store_bytes_field("hash", hash_);
    s.store_class_end();
  }
}

liteServer_info::liteServer_info()
  : now_()
  , version_()
  , capabilities_()
{}

liteServer_info::liteServer_info(std::int64_t now_, std::int32_t version_, std::int64_t capabilities_)
  : now_(now_)
  , version_(version_)
  , capabilities_(capabilities_)
{}

const std::int32_t liteServer_info::ID;

void liteServer_info::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_info");
    s.store_field("now", now_);
    s.store_field("version", version_);
    s.store_field("capabilities", capabilities_);
    s.store_class_end();
  }
}

blocks_shortTxId::blocks_shortTxId()
  : mode_()
  , account_()
  , lt_()
  , hash_()
{}

blocks_shortTxId::blocks_shortTxId(std::int32_t mode_, std::string const &account_, std::int64_t lt_, std::string const &hash_)
  : mode_(mode_)
  , account_(std::move(account_))
  , lt_(lt_)
  , hash_(std::move(hash_))
{}

const std::int32_t blocks_shortTxId::ID;

void blocks_shortTxId::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_shortTxId");
  std::int32_t var0;
    s.store_field("mode", (var0 = mode_));
    if (var0 & 1) { s.store_bytes_field("account", account_); }
    if (var0 & 2) { s.store_field("lt", lt_); }
    if (var0 & 4) { s.store_bytes_field("hash", hash_); }
    s.store_class_end();
  }
}

msg_dataRaw::msg_dataRaw()
  : body_()
  , init_state_()
{}

msg_dataRaw::msg_dataRaw(std::string const &body_, std::string const &init_state_)
  : body_(std::move(body_))
  , init_state_(std::move(init_state_))
{}

const std::int32_t msg_dataRaw::ID;

void msg_dataRaw::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_dataRaw");
    s.store_bytes_field("body", body_);
    s.store_bytes_field("init_state", init_state_);
    s.store_class_end();
  }
}

msg_dataText::msg_dataText()
  : text_()
{}

msg_dataText::msg_dataText(std::string const &text_)
  : text_(std::move(text_))
{}

const std::int32_t msg_dataText::ID;

void msg_dataText::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_dataText");
    s.store_bytes_field("text", text_);
    s.store_class_end();
  }
}

msg_dataDecryptedText::msg_dataDecryptedText()
  : text_()
{}

msg_dataDecryptedText::msg_dataDecryptedText(std::string const &text_)
  : text_(std::move(text_))
{}

const std::int32_t msg_dataDecryptedText::ID;

void msg_dataDecryptedText::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_dataDecryptedText");
    s.store_bytes_field("text", text_);
    s.store_class_end();
  }
}

msg_dataEncryptedText::msg_dataEncryptedText()
  : text_()
{}

msg_dataEncryptedText::msg_dataEncryptedText(std::string const &text_)
  : text_(std::move(text_))
{}

const std::int32_t msg_dataEncryptedText::ID;

void msg_dataEncryptedText::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_dataEncryptedText");
    s.store_bytes_field("text", text_);
    s.store_class_end();
  }
}

msg_dataDecrypted::msg_dataDecrypted()
  : proof_()
  , data_()
{}

msg_dataDecrypted::msg_dataDecrypted(std::string const &proof_, object_ptr<msg_Data> &&data_)
  : proof_(std::move(proof_))
  , data_(std::move(data_))
{}

const std::int32_t msg_dataDecrypted::ID;

void msg_dataDecrypted::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_dataDecrypted");
    s.store_bytes_field("proof", proof_);
    if (data_ == nullptr) { s.store_field("data", "null"); } else { data_->store(s, "data"); }
    s.store_class_end();
  }
}

msg_dataDecryptedArray::msg_dataDecryptedArray()
  : elements_()
{}

msg_dataDecryptedArray::msg_dataDecryptedArray(std::vector<object_ptr<msg_dataDecrypted>> &&elements_)
  : elements_(std::move(elements_))
{}

const std::int32_t msg_dataDecryptedArray::ID;

void msg_dataDecryptedArray::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_dataDecryptedArray");
    { const std::vector<object_ptr<msg_dataDecrypted>> &v = elements_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("elements", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

msg_dataEncrypted::msg_dataEncrypted()
  : source_()
  , data_()
{}

msg_dataEncrypted::msg_dataEncrypted(object_ptr<accountAddress> &&source_, object_ptr<msg_Data> &&data_)
  : source_(std::move(source_))
  , data_(std::move(data_))
{}

const std::int32_t msg_dataEncrypted::ID;

void msg_dataEncrypted::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_dataEncrypted");
    if (source_ == nullptr) { s.store_field("source", "null"); } else { source_->store(s, "source"); }
    if (data_ == nullptr) { s.store_field("data", "null"); } else { data_->store(s, "data"); }
    s.store_class_end();
  }
}

msg_dataEncryptedArray::msg_dataEncryptedArray()
  : elements_()
{}

msg_dataEncryptedArray::msg_dataEncryptedArray(std::vector<object_ptr<msg_dataEncrypted>> &&elements_)
  : elements_(std::move(elements_))
{}

const std::int32_t msg_dataEncryptedArray::ID;

void msg_dataEncryptedArray::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_dataEncryptedArray");
    { const std::vector<object_ptr<msg_dataEncrypted>> &v = elements_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("elements", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

msg_message::msg_message()
  : destination_()
  , public_key_()
  , amount_()
  , data_()
  , send_mode_()
{}

msg_message::msg_message(object_ptr<accountAddress> &&destination_, std::string const &public_key_, std::int64_t amount_, object_ptr<msg_Data> &&data_, std::int32_t send_mode_)
  : destination_(std::move(destination_))
  , public_key_(std::move(public_key_))
  , amount_(amount_)
  , data_(std::move(data_))
  , send_mode_(send_mode_)
{}

const std::int32_t msg_message::ID;

void msg_message::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_message");
    if (destination_ == nullptr) { s.store_field("destination", "null"); } else { destination_->store(s, "destination"); }
    s.store_field("public_key", public_key_);
    s.store_field("amount", amount_);
    if (data_ == nullptr) { s.store_field("data", "null"); } else { data_->store(s, "data"); }
    s.store_field("send_mode", send_mode_);
    s.store_class_end();
  }
}

options_configInfo::options_configInfo()
  : default_wallet_id_()
  , default_rwallet_init_public_key_()
{}

options_configInfo::options_configInfo(std::int64_t default_wallet_id_, std::string const &default_rwallet_init_public_key_)
  : default_wallet_id_(default_wallet_id_)
  , default_rwallet_init_public_key_(std::move(default_rwallet_init_public_key_))
{}

const std::int32_t options_configInfo::ID;

void options_configInfo::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "options_configInfo");
    s.store_field("default_wallet_id", default_wallet_id_);
    s.store_field("default_rwallet_init_public_key", default_rwallet_init_public_key_);
    s.store_class_end();
  }
}

options_info::options_info()
  : config_info_()
{}

options_info::options_info(object_ptr<options_configInfo> &&config_info_)
  : config_info_(std::move(config_info_))
{}

const std::int32_t options_info::ID;

void options_info::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "options_info");
    if (config_info_ == nullptr) { s.store_field("config_info", "null"); } else { config_info_->store(s, "config_info"); }
    s.store_class_end();
  }
}

pchan_actionInit::pchan_actionInit()
  : inc_A_()
  , inc_B_()
  , min_A_()
  , min_B_()
{}

pchan_actionInit::pchan_actionInit(std::int64_t inc_A_, std::int64_t inc_B_, std::int64_t min_A_, std::int64_t min_B_)
  : inc_A_(inc_A_)
  , inc_B_(inc_B_)
  , min_A_(min_A_)
  , min_B_(min_B_)
{}

const std::int32_t pchan_actionInit::ID;

void pchan_actionInit::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_actionInit");
    s.store_field("inc_A", inc_A_);
    s.store_field("inc_B", inc_B_);
    s.store_field("min_A", min_A_);
    s.store_field("min_B", min_B_);
    s.store_class_end();
  }
}

pchan_actionClose::pchan_actionClose()
  : extra_A_()
  , extra_B_()
  , promise_()
{}

pchan_actionClose::pchan_actionClose(std::int64_t extra_A_, std::int64_t extra_B_, object_ptr<pchan_promise> &&promise_)
  : extra_A_(extra_A_)
  , extra_B_(extra_B_)
  , promise_(std::move(promise_))
{}

const std::int32_t pchan_actionClose::ID;

void pchan_actionClose::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_actionClose");
    s.store_field("extra_A", extra_A_);
    s.store_field("extra_B", extra_B_);
    if (promise_ == nullptr) { s.store_field("promise", "null"); } else { promise_->store(s, "promise"); }
    s.store_class_end();
  }
}

pchan_actionTimeout::pchan_actionTimeout() {
}

const std::int32_t pchan_actionTimeout::ID;

void pchan_actionTimeout::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_actionTimeout");
    s.store_class_end();
  }
}

pchan_config::pchan_config()
  : alice_public_key_()
  , alice_address_()
  , bob_public_key_()
  , bob_address_()
  , init_timeout_()
  , close_timeout_()
  , channel_id_()
{}

pchan_config::pchan_config(std::string const &alice_public_key_, object_ptr<accountAddress> &&alice_address_, std::string const &bob_public_key_, object_ptr<accountAddress> &&bob_address_, std::int32_t init_timeout_, std::int32_t close_timeout_, std::int64_t channel_id_)
  : alice_public_key_(std::move(alice_public_key_))
  , alice_address_(std::move(alice_address_))
  , bob_public_key_(std::move(bob_public_key_))
  , bob_address_(std::move(bob_address_))
  , init_timeout_(init_timeout_)
  , close_timeout_(close_timeout_)
  , channel_id_(channel_id_)
{}

const std::int32_t pchan_config::ID;

void pchan_config::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_config");
    s.store_field("alice_public_key", alice_public_key_);
    if (alice_address_ == nullptr) { s.store_field("alice_address", "null"); } else { alice_address_->store(s, "alice_address"); }
    s.store_field("bob_public_key", bob_public_key_);
    if (bob_address_ == nullptr) { s.store_field("bob_address", "null"); } else { bob_address_->store(s, "bob_address"); }
    s.store_field("init_timeout", init_timeout_);
    s.store_field("close_timeout", close_timeout_);
    s.store_field("channel_id", channel_id_);
    s.store_class_end();
  }
}

pchan_promise::pchan_promise()
  : signature_()
  , promise_A_()
  , promise_B_()
  , channel_id_()
{}

pchan_promise::pchan_promise(std::string const &signature_, std::int64_t promise_A_, std::int64_t promise_B_, std::int64_t channel_id_)
  : signature_(std::move(signature_))
  , promise_A_(promise_A_)
  , promise_B_(promise_B_)
  , channel_id_(channel_id_)
{}

const std::int32_t pchan_promise::ID;

void pchan_promise::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_promise");
    s.store_bytes_field("signature", signature_);
    s.store_field("promise_A", promise_A_);
    s.store_field("promise_B", promise_B_);
    s.store_field("channel_id", channel_id_);
    s.store_class_end();
  }
}

pchan_stateInit::pchan_stateInit()
  : signed_A_()
  , signed_B_()
  , min_A_()
  , min_B_()
  , expire_at_()
  , A_()
  , B_()
{}

pchan_stateInit::pchan_stateInit(bool signed_A_, bool signed_B_, std::int64_t min_A_, std::int64_t min_B_, std::int64_t expire_at_, std::int64_t A_, std::int64_t B_)
  : signed_A_(signed_A_)
  , signed_B_(signed_B_)
  , min_A_(min_A_)
  , min_B_(min_B_)
  , expire_at_(expire_at_)
  , A_(A_)
  , B_(B_)
{}

const std::int32_t pchan_stateInit::ID;

void pchan_stateInit::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_stateInit");
    s.store_field("signed_A", signed_A_);
    s.store_field("signed_B", signed_B_);
    s.store_field("min_A", min_A_);
    s.store_field("min_B", min_B_);
    s.store_field("expire_at", expire_at_);
    s.store_field("A", A_);
    s.store_field("B", B_);
    s.store_class_end();
  }
}

pchan_stateClose::pchan_stateClose()
  : signed_A_()
  , signed_B_()
  , min_A_()
  , min_B_()
  , expire_at_()
  , A_()
  , B_()
{}

pchan_stateClose::pchan_stateClose(bool signed_A_, bool signed_B_, std::int64_t min_A_, std::int64_t min_B_, std::int64_t expire_at_, std::int64_t A_, std::int64_t B_)
  : signed_A_(signed_A_)
  , signed_B_(signed_B_)
  , min_A_(min_A_)
  , min_B_(min_B_)
  , expire_at_(expire_at_)
  , A_(A_)
  , B_(B_)
{}

const std::int32_t pchan_stateClose::ID;

void pchan_stateClose::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_stateClose");
    s.store_field("signed_A", signed_A_);
    s.store_field("signed_B", signed_B_);
    s.store_field("min_A", min_A_);
    s.store_field("min_B", min_B_);
    s.store_field("expire_at", expire_at_);
    s.store_field("A", A_);
    s.store_field("B", B_);
    s.store_class_end();
  }
}

pchan_statePayout::pchan_statePayout()
  : A_()
  , B_()
{}

pchan_statePayout::pchan_statePayout(std::int64_t A_, std::int64_t B_)
  : A_(A_)
  , B_(B_)
{}

const std::int32_t pchan_statePayout::ID;

void pchan_statePayout::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_statePayout");
    s.store_field("A", A_);
    s.store_field("B", B_);
    s.store_class_end();
  }
}

query_fees::query_fees()
  : source_fees_()
  , destination_fees_()
{}

query_fees::query_fees(object_ptr<fees> &&source_fees_, std::vector<object_ptr<fees>> &&destination_fees_)
  : source_fees_(std::move(source_fees_))
  , destination_fees_(std::move(destination_fees_))
{}

const std::int32_t query_fees::ID;

void query_fees::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "query_fees");
    if (source_fees_ == nullptr) { s.store_field("source_fees", "null"); } else { source_fees_->store(s, "source_fees"); }
    { const std::vector<object_ptr<fees>> &v = destination_fees_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("destination_fees", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

query_info::query_info()
  : id_()
  , valid_until_()
  , body_hash_()
  , body_()
  , init_state_()
{}

query_info::query_info(std::int64_t id_, std::int64_t valid_until_, std::string const &body_hash_, std::string const &body_, std::string const &init_state_)
  : id_(id_)
  , valid_until_(valid_until_)
  , body_hash_(std::move(body_hash_))
  , body_(std::move(body_))
  , init_state_(std::move(init_state_))
{}

const std::int32_t query_info::ID;

void query_info::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "query_info");
    s.store_field("id", id_);
    s.store_field("valid_until", valid_until_);
    s.store_bytes_field("body_hash", body_hash_);
    s.store_bytes_field("body", body_);
    s.store_bytes_field("init_state", init_state_);
    s.store_class_end();
  }
}

raw_fullAccountState::raw_fullAccountState()
  : balance_()
  , code_()
  , data_()
  , last_transaction_id_()
  , block_id_()
  , frozen_hash_()
  , sync_utime_()
{}

raw_fullAccountState::raw_fullAccountState(std::int64_t balance_, std::string const &code_, std::string const &data_, object_ptr<internal_transactionId> &&last_transaction_id_, object_ptr<ton_blockIdExt> &&block_id_, std::string const &frozen_hash_, std::int64_t sync_utime_)
  : balance_(balance_)
  , code_(std::move(code_))
  , data_(std::move(data_))
  , last_transaction_id_(std::move(last_transaction_id_))
  , block_id_(std::move(block_id_))
  , frozen_hash_(std::move(frozen_hash_))
  , sync_utime_(sync_utime_)
{}

const std::int32_t raw_fullAccountState::ID;

void raw_fullAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_fullAccountState");
    s.store_field("balance", balance_);
    s.store_bytes_field("code", code_);
    s.store_bytes_field("data", data_);
    if (last_transaction_id_ == nullptr) { s.store_field("last_transaction_id", "null"); } else { last_transaction_id_->store(s, "last_transaction_id"); }
    if (block_id_ == nullptr) { s.store_field("block_id", "null"); } else { block_id_->store(s, "block_id"); }
    s.store_bytes_field("frozen_hash", frozen_hash_);
    s.store_field("sync_utime", sync_utime_);
    s.store_class_end();
  }
}

raw_message::raw_message()
  : source_()
  , destination_()
  , value_()
  , fwd_fee_()
  , ihr_fee_()
  , created_lt_()
  , body_hash_()
  , msg_data_()
{}

raw_message::raw_message(object_ptr<accountAddress> &&source_, object_ptr<accountAddress> &&destination_, std::int64_t value_, std::int64_t fwd_fee_, std::int64_t ihr_fee_, std::int64_t created_lt_, std::string const &body_hash_, object_ptr<msg_Data> &&msg_data_)
  : source_(std::move(source_))
  , destination_(std::move(destination_))
  , value_(value_)
  , fwd_fee_(fwd_fee_)
  , ihr_fee_(ihr_fee_)
  , created_lt_(created_lt_)
  , body_hash_(std::move(body_hash_))
  , msg_data_(std::move(msg_data_))
{}

const std::int32_t raw_message::ID;

void raw_message::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_message");
    if (source_ == nullptr) { s.store_field("source", "null"); } else { source_->store(s, "source"); }
    if (destination_ == nullptr) { s.store_field("destination", "null"); } else { destination_->store(s, "destination"); }
    s.store_field("value", value_);
    s.store_field("fwd_fee", fwd_fee_);
    s.store_field("ihr_fee", ihr_fee_);
    s.store_field("created_lt", created_lt_);
    s.store_bytes_field("body_hash", body_hash_);
    if (msg_data_ == nullptr) { s.store_field("msg_data", "null"); } else { msg_data_->store(s, "msg_data"); }
    s.store_class_end();
  }
}

raw_transaction::raw_transaction()
  : utime_()
  , data_()
  , transaction_id_()
  , fee_()
  , storage_fee_()
  , other_fee_()
  , in_msg_()
  , out_msgs_()
{}

raw_transaction::raw_transaction(std::int64_t utime_, std::string const &data_, object_ptr<internal_transactionId> &&transaction_id_, std::int64_t fee_, std::int64_t storage_fee_, std::int64_t other_fee_, object_ptr<raw_message> &&in_msg_, std::vector<object_ptr<raw_message>> &&out_msgs_)
  : utime_(utime_)
  , data_(std::move(data_))
  , transaction_id_(std::move(transaction_id_))
  , fee_(fee_)
  , storage_fee_(storage_fee_)
  , other_fee_(other_fee_)
  , in_msg_(std::move(in_msg_))
  , out_msgs_(std::move(out_msgs_))
{}

const std::int32_t raw_transaction::ID;

void raw_transaction::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_transaction");
    s.store_field("utime", utime_);
    s.store_bytes_field("data", data_);
    if (transaction_id_ == nullptr) { s.store_field("transaction_id", "null"); } else { transaction_id_->store(s, "transaction_id"); }
    s.store_field("fee", fee_);
    s.store_field("storage_fee", storage_fee_);
    s.store_field("other_fee", other_fee_);
    if (in_msg_ == nullptr) { s.store_field("in_msg", "null"); } else { in_msg_->store(s, "in_msg"); }
    { const std::vector<object_ptr<raw_message>> &v = out_msgs_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("out_msgs", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

raw_transactions::raw_transactions()
  : transactions_()
  , previous_transaction_id_()
{}

raw_transactions::raw_transactions(std::vector<object_ptr<raw_transaction>> &&transactions_, object_ptr<internal_transactionId> &&previous_transaction_id_)
  : transactions_(std::move(transactions_))
  , previous_transaction_id_(std::move(previous_transaction_id_))
{}

const std::int32_t raw_transactions::ID;

void raw_transactions::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_transactions");
    { const std::vector<object_ptr<raw_transaction>> &v = transactions_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("transactions", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    if (previous_transaction_id_ == nullptr) { s.store_field("previous_transaction_id", "null"); } else { previous_transaction_id_->store(s, "previous_transaction_id"); }
    s.store_class_end();
  }
}

rwallet_actionInit::rwallet_actionInit()
  : config_()
{}

rwallet_actionInit::rwallet_actionInit(object_ptr<rwallet_config> &&config_)
  : config_(std::move(config_))
{}

const std::int32_t rwallet_actionInit::ID;

void rwallet_actionInit::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rwallet_actionInit");
    if (config_ == nullptr) { s.store_field("config", "null"); } else { config_->store(s, "config"); }
    s.store_class_end();
  }
}

rwallet_config::rwallet_config()
  : start_at_()
  , limits_()
{}

rwallet_config::rwallet_config(std::int64_t start_at_, std::vector<object_ptr<rwallet_limit>> &&limits_)
  : start_at_(start_at_)
  , limits_(std::move(limits_))
{}

const std::int32_t rwallet_config::ID;

void rwallet_config::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rwallet_config");
    s.store_field("start_at", start_at_);
    { const std::vector<object_ptr<rwallet_limit>> &v = limits_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("limits", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

rwallet_limit::rwallet_limit()
  : seconds_()
  , value_()
{}

rwallet_limit::rwallet_limit(std::int32_t seconds_, std::int64_t value_)
  : seconds_(seconds_)
  , value_(value_)
{}

const std::int32_t rwallet_limit::ID;

void rwallet_limit::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rwallet_limit");
    s.store_field("seconds", seconds_);
    s.store_field("value", value_);
    s.store_class_end();
  }
}

smc_info::smc_info()
  : id_()
{}

smc_info::smc_info(std::int64_t id_)
  : id_(id_)
{}

const std::int32_t smc_info::ID;

void smc_info::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "smc_info");
    s.store_field("id", id_);
    s.store_class_end();
  }
}

smc_methodIdNumber::smc_methodIdNumber()
  : number_()
{}

smc_methodIdNumber::smc_methodIdNumber(std::int32_t number_)
  : number_(number_)
{}

const std::int32_t smc_methodIdNumber::ID;

void smc_methodIdNumber::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "smc_methodIdNumber");
    s.store_field("number", number_);
    s.store_class_end();
  }
}

smc_methodIdName::smc_methodIdName()
  : name_()
{}

smc_methodIdName::smc_methodIdName(std::string const &name_)
  : name_(std::move(name_))
{}

const std::int32_t smc_methodIdName::ID;

void smc_methodIdName::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "smc_methodIdName");
    s.store_field("name", name_);
    s.store_class_end();
  }
}

smc_runResult::smc_runResult()
  : gas_used_()
  , stack_()
  , exit_code_()
{}

smc_runResult::smc_runResult(std::int64_t gas_used_, std::vector<object_ptr<tvm_StackEntry>> &&stack_, std::int32_t exit_code_)
  : gas_used_(gas_used_)
  , stack_(std::move(stack_))
  , exit_code_(exit_code_)
{}

const std::int32_t smc_runResult::ID;

void smc_runResult::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "smc_runResult");
    s.store_field("gas_used", gas_used_);
    { const std::vector<object_ptr<tvm_StackEntry>> &v = stack_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("stack", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_field("exit_code", exit_code_);
    s.store_class_end();
  }
}

ton_blockIdExt::ton_blockIdExt()
  : workchain_()
  , shard_()
  , seqno_()
  , root_hash_()
  , file_hash_()
{}

ton_blockIdExt::ton_blockIdExt(std::int32_t workchain_, std::int64_t shard_, std::int32_t seqno_, std::string const &root_hash_, std::string const &file_hash_)
  : workchain_(workchain_)
  , shard_(shard_)
  , seqno_(seqno_)
  , root_hash_(std::move(root_hash_))
  , file_hash_(std::move(file_hash_))
{}

const std::int32_t ton_blockIdExt::ID;

void ton_blockIdExt::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "ton_blockIdExt");
    s.store_field("workchain", workchain_);
    s.store_field("shard", shard_);
    s.store_field("seqno", seqno_);
    s.store_bytes_field("root_hash", root_hash_);
    s.store_bytes_field("file_hash", file_hash_);
    s.store_class_end();
  }
}

tvm_cell::tvm_cell()
  : bytes_()
{}

tvm_cell::tvm_cell(std::string const &bytes_)
  : bytes_(std::move(bytes_))
{}

const std::int32_t tvm_cell::ID;

void tvm_cell::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_cell");
    s.store_bytes_field("bytes", bytes_);
    s.store_class_end();
  }
}

tvm_list::tvm_list()
  : elements_()
{}

tvm_list::tvm_list(std::vector<object_ptr<tvm_StackEntry>> &&elements_)
  : elements_(std::move(elements_))
{}

const std::int32_t tvm_list::ID;

void tvm_list::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_list");
    { const std::vector<object_ptr<tvm_StackEntry>> &v = elements_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("elements", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

tvm_numberDecimal::tvm_numberDecimal()
  : number_()
{}

tvm_numberDecimal::tvm_numberDecimal(std::string const &number_)
  : number_(std::move(number_))
{}

const std::int32_t tvm_numberDecimal::ID;

void tvm_numberDecimal::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_numberDecimal");
    s.store_field("number", number_);
    s.store_class_end();
  }
}

tvm_slice::tvm_slice()
  : bytes_()
{}

tvm_slice::tvm_slice(std::string const &bytes_)
  : bytes_(std::move(bytes_))
{}

const std::int32_t tvm_slice::ID;

void tvm_slice::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_slice");
    s.store_bytes_field("bytes", bytes_);
    s.store_class_end();
  }
}

tvm_stackEntrySlice::tvm_stackEntrySlice()
  : slice_()
{}

tvm_stackEntrySlice::tvm_stackEntrySlice(object_ptr<tvm_slice> &&slice_)
  : slice_(std::move(slice_))
{}

const std::int32_t tvm_stackEntrySlice::ID;

void tvm_stackEntrySlice::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_stackEntrySlice");
    if (slice_ == nullptr) { s.store_field("slice", "null"); } else { slice_->store(s, "slice"); }
    s.store_class_end();
  }
}

tvm_stackEntryCell::tvm_stackEntryCell()
  : cell_()
{}

tvm_stackEntryCell::tvm_stackEntryCell(object_ptr<tvm_cell> &&cell_)
  : cell_(std::move(cell_))
{}

const std::int32_t tvm_stackEntryCell::ID;

void tvm_stackEntryCell::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_stackEntryCell");
    if (cell_ == nullptr) { s.store_field("cell", "null"); } else { cell_->store(s, "cell"); }
    s.store_class_end();
  }
}

tvm_stackEntryNumber::tvm_stackEntryNumber()
  : number_()
{}

tvm_stackEntryNumber::tvm_stackEntryNumber(object_ptr<tvm_numberDecimal> &&number_)
  : number_(std::move(number_))
{}

const std::int32_t tvm_stackEntryNumber::ID;

void tvm_stackEntryNumber::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_stackEntryNumber");
    if (number_ == nullptr) { s.store_field("number", "null"); } else { number_->store(s, "number"); }
    s.store_class_end();
  }
}

tvm_stackEntryTuple::tvm_stackEntryTuple()
  : tuple_()
{}

tvm_stackEntryTuple::tvm_stackEntryTuple(object_ptr<tvm_tuple> &&tuple_)
  : tuple_(std::move(tuple_))
{}

const std::int32_t tvm_stackEntryTuple::ID;

void tvm_stackEntryTuple::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_stackEntryTuple");
    if (tuple_ == nullptr) { s.store_field("tuple", "null"); } else { tuple_->store(s, "tuple"); }
    s.store_class_end();
  }
}

tvm_stackEntryList::tvm_stackEntryList()
  : list_()
{}

tvm_stackEntryList::tvm_stackEntryList(object_ptr<tvm_list> &&list_)
  : list_(std::move(list_))
{}

const std::int32_t tvm_stackEntryList::ID;

void tvm_stackEntryList::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_stackEntryList");
    if (list_ == nullptr) { s.store_field("list", "null"); } else { list_->store(s, "list"); }
    s.store_class_end();
  }
}

tvm_stackEntryUnsupported::tvm_stackEntryUnsupported() {
}

const std::int32_t tvm_stackEntryUnsupported::ID;

void tvm_stackEntryUnsupported::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_stackEntryUnsupported");
    s.store_class_end();
  }
}

tvm_tuple::tvm_tuple()
  : elements_()
{}

tvm_tuple::tvm_tuple(std::vector<object_ptr<tvm_StackEntry>> &&elements_)
  : elements_(std::move(elements_))
{}

const std::int32_t tvm_tuple::ID;

void tvm_tuple::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tvm_tuple");
    { const std::vector<object_ptr<tvm_StackEntry>> &v = elements_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("elements", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

addLogMessage::addLogMessage()
  : verbosity_level_()
  , text_()
{}

addLogMessage::addLogMessage(std::int32_t verbosity_level_, std::string const &text_)
  : verbosity_level_(verbosity_level_)
  , text_(std::move(text_))
{}

const std::int32_t addLogMessage::ID;

void addLogMessage::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "addLogMessage");
    s.store_field("verbosity_level", verbosity_level_);
    s.store_field("text", text_);
    s.store_class_end();
  }
}

blocks_getBlockHeader::blocks_getBlockHeader()
  : id_()
{}

blocks_getBlockHeader::blocks_getBlockHeader(object_ptr<ton_blockIdExt> &&id_)
  : id_(std::move(id_))
{}

const std::int32_t blocks_getBlockHeader::ID;

void blocks_getBlockHeader::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_getBlockHeader");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

blocks_getMasterchainInfo::blocks_getMasterchainInfo() {
}

const std::int32_t blocks_getMasterchainInfo::ID;

void blocks_getMasterchainInfo::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_getMasterchainInfo");
    s.store_class_end();
  }
}

blocks_getShards::blocks_getShards()
  : id_()
{}

blocks_getShards::blocks_getShards(object_ptr<ton_blockIdExt> &&id_)
  : id_(std::move(id_))
{}

const std::int32_t blocks_getShards::ID;

void blocks_getShards::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_getShards");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

blocks_getTransactions::blocks_getTransactions()
  : id_()
  , mode_()
  , count_()
  , after_()
{}

blocks_getTransactions::blocks_getTransactions(object_ptr<ton_blockIdExt> &&id_, std::int32_t mode_, std::int32_t count_, object_ptr<blocks_accountTransactionId> &&after_)
  : id_(std::move(id_))
  , mode_(mode_)
  , count_(count_)
  , after_(std::move(after_))
{}

const std::int32_t blocks_getTransactions::ID;

void blocks_getTransactions::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_getTransactions");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_field("mode", (var0 = mode_));
    s.store_field("count", (var1 = count_));
    if (after_ == nullptr) { s.store_field("after", "null"); } else { after_->store(s, "after"); }
    s.store_class_end();
  }
}

blocks_lookupBlock::blocks_lookupBlock()
  : mode_()
  , id_()
  , lt_()
  , utime_()
{}

blocks_lookupBlock::blocks_lookupBlock(std::int32_t mode_, object_ptr<ton_blockId> &&id_, std::int64_t lt_, std::int32_t utime_)
  : mode_(mode_)
  , id_(std::move(id_))
  , lt_(lt_)
  , utime_(utime_)
{}

const std::int32_t blocks_lookupBlock::ID;

void blocks_lookupBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "blocks_lookupBlock");
    s.store_field("mode", mode_);
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_field("lt", lt_);
    s.store_field("utime", utime_);
    s.store_class_end();
  }
}

changeLocalPassword::changeLocalPassword()
  : input_key_()
  , new_local_password_()
{}

changeLocalPassword::changeLocalPassword(object_ptr<InputKey> &&input_key_, td::SecureString &&new_local_password_)
  : input_key_(std::move(input_key_))
  , new_local_password_(std::move(new_local_password_))
{}

const std::int32_t changeLocalPassword::ID;

void changeLocalPassword::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "changeLocalPassword");
    if (input_key_ == nullptr) { s.store_field("input_key", "null"); } else { input_key_->store(s, "input_key"); }
    s.store_bytes_field("new_local_password", new_local_password_);
    s.store_class_end();
  }
}

close::close() {
}

const std::int32_t close::ID;

void close::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "close");
    s.store_class_end();
  }
}

createNewKey::createNewKey()
  : local_password_()
  , mnemonic_password_()
  , random_extra_seed_()
{}

createNewKey::createNewKey(td::SecureString &&local_password_, td::SecureString &&mnemonic_password_, td::SecureString &&random_extra_seed_)
  : local_password_(std::move(local_password_))
  , mnemonic_password_(std::move(mnemonic_password_))
  , random_extra_seed_(std::move(random_extra_seed_))
{}

const std::int32_t createNewKey::ID;

void createNewKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "createNewKey");
    s.store_bytes_field("local_password", local_password_);
    s.store_bytes_field("mnemonic_password", mnemonic_password_);
    s.store_bytes_field("random_extra_seed", random_extra_seed_);
    s.store_class_end();
  }
}

createQuery::createQuery()
  : private_key_()
  , address_()
  , timeout_()
  , action_()
  , initial_account_state_()
{}

createQuery::createQuery(object_ptr<InputKey> &&private_key_, object_ptr<accountAddress> &&address_, std::int32_t timeout_, object_ptr<Action> &&action_, object_ptr<InitialAccountState> &&initial_account_state_)
  : private_key_(std::move(private_key_))
  , address_(std::move(address_))
  , timeout_(timeout_)
  , action_(std::move(action_))
  , initial_account_state_(std::move(initial_account_state_))
{}

const std::int32_t createQuery::ID;

void createQuery::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "createQuery");
    if (private_key_ == nullptr) { s.store_field("private_key", "null"); } else { private_key_->store(s, "private_key"); }
    if (address_ == nullptr) { s.store_field("address", "null"); } else { address_->store(s, "address"); }
    s.store_field("timeout", timeout_);
    if (action_ == nullptr) { s.store_field("action", "null"); } else { action_->store(s, "action"); }
    if (initial_account_state_ == nullptr) { s.store_field("initial_account_state", "null"); } else { initial_account_state_->store(s, "initial_account_state"); }
    s.store_class_end();
  }
}

decrypt::decrypt()
  : encrypted_data_()
  , secret_()
{}

decrypt::decrypt(td::SecureString &&encrypted_data_, td::SecureString &&secret_)
  : encrypted_data_(std::move(encrypted_data_))
  , secret_(std::move(secret_))
{}

const std::int32_t decrypt::ID;

void decrypt::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "decrypt");
    s.store_bytes_field("encrypted_data", encrypted_data_);
    s.store_bytes_field("secret", secret_);
    s.store_class_end();
  }
}

deleteAllKeys::deleteAllKeys() {
}

const std::int32_t deleteAllKeys::ID;

void deleteAllKeys::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "deleteAllKeys");
    s.store_class_end();
  }
}

deleteKey::deleteKey()
  : key_()
{}

deleteKey::deleteKey(object_ptr<key> &&key_)
  : key_(std::move(key_))
{}

const std::int32_t deleteKey::ID;

void deleteKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "deleteKey");
    if (key_ == nullptr) { s.store_field("key", "null"); } else { key_->store(s, "key"); }
    s.store_class_end();
  }
}

dns_resolve::dns_resolve()
  : account_address_()
  , name_()
  , category_()
  , ttl_()
{}

dns_resolve::dns_resolve(object_ptr<accountAddress> &&account_address_, std::string const &name_, std::int32_t category_, std::int32_t ttl_)
  : account_address_(std::move(account_address_))
  , name_(std::move(name_))
  , category_(category_)
  , ttl_(ttl_)
{}

const std::int32_t dns_resolve::ID;

void dns_resolve::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dns_resolve");
    if (account_address_ == nullptr) { s.store_field("account_address", "null"); } else { account_address_->store(s, "account_address"); }
    s.store_field("name", name_);
    s.store_field("category", category_);
    s.store_field("ttl", ttl_);
    s.store_class_end();
  }
}

encrypt::encrypt()
  : decrypted_data_()
  , secret_()
{}

encrypt::encrypt(td::SecureString &&decrypted_data_, td::SecureString &&secret_)
  : decrypted_data_(std::move(decrypted_data_))
  , secret_(std::move(secret_))
{}

const std::int32_t encrypt::ID;

void encrypt::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "encrypt");
    s.store_bytes_field("decrypted_data", decrypted_data_);
    s.store_bytes_field("secret", secret_);
    s.store_class_end();
  }
}

exportEncryptedKey::exportEncryptedKey()
  : input_key_()
  , key_password_()
{}

exportEncryptedKey::exportEncryptedKey(object_ptr<InputKey> &&input_key_, td::SecureString &&key_password_)
  : input_key_(std::move(input_key_))
  , key_password_(std::move(key_password_))
{}

const std::int32_t exportEncryptedKey::ID;

void exportEncryptedKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "exportEncryptedKey");
    if (input_key_ == nullptr) { s.store_field("input_key", "null"); } else { input_key_->store(s, "input_key"); }
    s.store_bytes_field("key_password", key_password_);
    s.store_class_end();
  }
}

exportKey::exportKey()
  : input_key_()
{}

exportKey::exportKey(object_ptr<InputKey> &&input_key_)
  : input_key_(std::move(input_key_))
{}

const std::int32_t exportKey::ID;

void exportKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "exportKey");
    if (input_key_ == nullptr) { s.store_field("input_key", "null"); } else { input_key_->store(s, "input_key"); }
    s.store_class_end();
  }
}

exportPemKey::exportPemKey()
  : input_key_()
  , key_password_()
{}

exportPemKey::exportPemKey(object_ptr<InputKey> &&input_key_, td::SecureString &&key_password_)
  : input_key_(std::move(input_key_))
  , key_password_(std::move(key_password_))
{}

const std::int32_t exportPemKey::ID;

void exportPemKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "exportPemKey");
    if (input_key_ == nullptr) { s.store_field("input_key", "null"); } else { input_key_->store(s, "input_key"); }
    s.store_bytes_field("key_password", key_password_);
    s.store_class_end();
  }
}

exportUnencryptedKey::exportUnencryptedKey()
  : input_key_()
{}

exportUnencryptedKey::exportUnencryptedKey(object_ptr<InputKey> &&input_key_)
  : input_key_(std::move(input_key_))
{}

const std::int32_t exportUnencryptedKey::ID;

void exportUnencryptedKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "exportUnencryptedKey");
    if (input_key_ == nullptr) { s.store_field("input_key", "null"); } else { input_key_->store(s, "input_key"); }
    s.store_class_end();
  }
}

getAccountAddress::getAccountAddress()
  : initial_account_state_()
  , revision_()
  , workchain_id_()
{}

getAccountAddress::getAccountAddress(object_ptr<InitialAccountState> &&initial_account_state_, std::int32_t revision_, std::int32_t workchain_id_)
  : initial_account_state_(std::move(initial_account_state_))
  , revision_(revision_)
  , workchain_id_(workchain_id_)
{}

const std::int32_t getAccountAddress::ID;

void getAccountAddress::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "getAccountAddress");
    if (initial_account_state_ == nullptr) { s.store_field("initial_account_state", "null"); } else { initial_account_state_->store(s, "initial_account_state"); }
    s.store_field("revision", revision_);
    s.store_field("workchain_id", workchain_id_);
    s.store_class_end();
  }
}

getAccountState::getAccountState()
  : account_address_()
{}

getAccountState::getAccountState(object_ptr<accountAddress> &&account_address_)
  : account_address_(std::move(account_address_))
{}

const std::int32_t getAccountState::ID;

void getAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "getAccountState");
    if (account_address_ == nullptr) { s.store_field("account_address", "null"); } else { account_address_->store(s, "account_address"); }
    s.store_class_end();
  }
}

getBip39Hints::getBip39Hints()
  : prefix_()
{}

getBip39Hints::getBip39Hints(std::string const &prefix_)
  : prefix_(std::move(prefix_))
{}

const std::int32_t getBip39Hints::ID;

void getBip39Hints::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "getBip39Hints");
    s.store_field("prefix", prefix_);
    s.store_class_end();
  }
}

getLogStream::getLogStream() {
}

const std::int32_t getLogStream::ID;

void getLogStream::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "getLogStream");
    s.store_class_end();
  }
}

getLogTagVerbosityLevel::getLogTagVerbosityLevel()
  : tag_()
{}

getLogTagVerbosityLevel::getLogTagVerbosityLevel(std::string const &tag_)
  : tag_(std::move(tag_))
{}

const std::int32_t getLogTagVerbosityLevel::ID;

void getLogTagVerbosityLevel::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "getLogTagVerbosityLevel");
    s.store_field("tag", tag_);
    s.store_class_end();
  }
}

getLogTags::getLogTags() {
}

const std::int32_t getLogTags::ID;

void getLogTags::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "getLogTags");
    s.store_class_end();
  }
}

getLogVerbosityLevel::getLogVerbosityLevel() {
}

const std::int32_t getLogVerbosityLevel::ID;

void getLogVerbosityLevel::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "getLogVerbosityLevel");
    s.store_class_end();
  }
}

guessAccount::guessAccount()
  : public_key_()
  , rwallet_init_public_key_()
{}

guessAccount::guessAccount(std::string const &public_key_, std::string const &rwallet_init_public_key_)
  : public_key_(std::move(public_key_))
  , rwallet_init_public_key_(std::move(rwallet_init_public_key_))
{}

const std::int32_t guessAccount::ID;

void guessAccount::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "guessAccount");
    s.store_field("public_key", public_key_);
    s.store_field("rwallet_init_public_key", rwallet_init_public_key_);
    s.store_class_end();
  }
}

guessAccountRevision::guessAccountRevision()
  : initial_account_state_()
  , workchain_id_()
{}

guessAccountRevision::guessAccountRevision(object_ptr<InitialAccountState> &&initial_account_state_, std::int32_t workchain_id_)
  : initial_account_state_(std::move(initial_account_state_))
  , workchain_id_(workchain_id_)
{}

const std::int32_t guessAccountRevision::ID;

void guessAccountRevision::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "guessAccountRevision");
    if (initial_account_state_ == nullptr) { s.store_field("initial_account_state", "null"); } else { initial_account_state_->store(s, "initial_account_state"); }
    s.store_field("workchain_id", workchain_id_);
    s.store_class_end();
  }
}

importEncryptedKey::importEncryptedKey()
  : local_password_()
  , key_password_()
  , exported_encrypted_key_()
{}

importEncryptedKey::importEncryptedKey(td::SecureString &&local_password_, td::SecureString &&key_password_, object_ptr<exportedEncryptedKey> &&exported_encrypted_key_)
  : local_password_(std::move(local_password_))
  , key_password_(std::move(key_password_))
  , exported_encrypted_key_(std::move(exported_encrypted_key_))
{}

const std::int32_t importEncryptedKey::ID;

void importEncryptedKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "importEncryptedKey");
    s.store_bytes_field("local_password", local_password_);
    s.store_bytes_field("key_password", key_password_);
    if (exported_encrypted_key_ == nullptr) { s.store_field("exported_encrypted_key", "null"); } else { exported_encrypted_key_->store(s, "exported_encrypted_key"); }
    s.store_class_end();
  }
}

importKey::importKey()
  : local_password_()
  , mnemonic_password_()
  , exported_key_()
{}

importKey::importKey(td::SecureString &&local_password_, td::SecureString &&mnemonic_password_, object_ptr<exportedKey> &&exported_key_)
  : local_password_(std::move(local_password_))
  , mnemonic_password_(std::move(mnemonic_password_))
  , exported_key_(std::move(exported_key_))
{}

const std::int32_t importKey::ID;

void importKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "importKey");
    s.store_bytes_field("local_password", local_password_);
    s.store_bytes_field("mnemonic_password", mnemonic_password_);
    if (exported_key_ == nullptr) { s.store_field("exported_key", "null"); } else { exported_key_->store(s, "exported_key"); }
    s.store_class_end();
  }
}

importPemKey::importPemKey()
  : local_password_()
  , key_password_()
  , exported_key_()
{}

importPemKey::importPemKey(td::SecureString &&local_password_, td::SecureString &&key_password_, object_ptr<exportedPemKey> &&exported_key_)
  : local_password_(std::move(local_password_))
  , key_password_(std::move(key_password_))
  , exported_key_(std::move(exported_key_))
{}

const std::int32_t importPemKey::ID;

void importPemKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "importPemKey");
    s.store_bytes_field("local_password", local_password_);
    s.store_bytes_field("key_password", key_password_);
    if (exported_key_ == nullptr) { s.store_field("exported_key", "null"); } else { exported_key_->store(s, "exported_key"); }
    s.store_class_end();
  }
}

importUnencryptedKey::importUnencryptedKey()
  : local_password_()
  , exported_unencrypted_key_()
{}

importUnencryptedKey::importUnencryptedKey(td::SecureString &&local_password_, object_ptr<exportedUnencryptedKey> &&exported_unencrypted_key_)
  : local_password_(std::move(local_password_))
  , exported_unencrypted_key_(std::move(exported_unencrypted_key_))
{}

const std::int32_t importUnencryptedKey::ID;

void importUnencryptedKey::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "importUnencryptedKey");
    s.store_bytes_field("local_password", local_password_);
    if (exported_unencrypted_key_ == nullptr) { s.store_field("exported_unencrypted_key", "null"); } else { exported_unencrypted_key_->store(s, "exported_unencrypted_key"); }
    s.store_class_end();
  }
}

init::init()
  : options_()
{}

init::init(object_ptr<options> &&options_)
  : options_(std::move(options_))
{}

const std::int32_t init::ID;

void init::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "init");
    if (options_ == nullptr) { s.store_field("options", "null"); } else { options_->store(s, "options"); }
    s.store_class_end();
  }
}

kdf::kdf()
  : password_()
  , salt_()
  , iterations_()
{}

kdf::kdf(td::SecureString &&password_, td::SecureString &&salt_, std::int32_t iterations_)
  : password_(std::move(password_))
  , salt_(std::move(salt_))
  , iterations_(iterations_)
{}

const std::int32_t kdf::ID;

void kdf::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "kdf");
    s.store_bytes_field("password", password_);
    s.store_bytes_field("salt", salt_);
    s.store_field("iterations", iterations_);
    s.store_class_end();
  }
}

liteServer_getInfo::liteServer_getInfo() {
}

const std::int32_t liteServer_getInfo::ID;

void liteServer_getInfo::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_getInfo");
    s.store_class_end();
  }
}

msg_decrypt::msg_decrypt()
  : input_key_()
  , data_()
{}

msg_decrypt::msg_decrypt(object_ptr<InputKey> &&input_key_, object_ptr<msg_dataEncryptedArray> &&data_)
  : input_key_(std::move(input_key_))
  , data_(std::move(data_))
{}

const std::int32_t msg_decrypt::ID;

void msg_decrypt::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_decrypt");
    if (input_key_ == nullptr) { s.store_field("input_key", "null"); } else { input_key_->store(s, "input_key"); }
    if (data_ == nullptr) { s.store_field("data", "null"); } else { data_->store(s, "data"); }
    s.store_class_end();
  }
}

msg_decryptWithProof::msg_decryptWithProof()
  : proof_()
  , data_()
{}

msg_decryptWithProof::msg_decryptWithProof(std::string const &proof_, object_ptr<msg_dataEncrypted> &&data_)
  : proof_(std::move(proof_))
  , data_(std::move(data_))
{}

const std::int32_t msg_decryptWithProof::ID;

void msg_decryptWithProof::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "msg_decryptWithProof");
    s.store_bytes_field("proof", proof_);
    if (data_ == nullptr) { s.store_field("data", "null"); } else { data_->store(s, "data"); }
    s.store_class_end();
  }
}

onLiteServerQueryError::onLiteServerQueryError()
  : id_()
  , error_()
{}

onLiteServerQueryError::onLiteServerQueryError(std::int64_t id_, object_ptr<error> &&error_)
  : id_(id_)
  , error_(std::move(error_))
{}

const std::int32_t onLiteServerQueryError::ID;

void onLiteServerQueryError::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "onLiteServerQueryError");
    s.store_field("id", id_);
    if (error_ == nullptr) { s.store_field("error", "null"); } else { error_->store(s, "error"); }
    s.store_class_end();
  }
}

onLiteServerQueryResult::onLiteServerQueryResult()
  : id_()
  , bytes_()
{}

onLiteServerQueryResult::onLiteServerQueryResult(std::int64_t id_, std::string const &bytes_)
  : id_(id_)
  , bytes_(std::move(bytes_))
{}

const std::int32_t onLiteServerQueryResult::ID;

void onLiteServerQueryResult::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "onLiteServerQueryResult");
    s.store_field("id", id_);
    s.store_bytes_field("bytes", bytes_);
    s.store_class_end();
  }
}

options_setConfig::options_setConfig()
  : config_()
{}

options_setConfig::options_setConfig(object_ptr<config> &&config_)
  : config_(std::move(config_))
{}

const std::int32_t options_setConfig::ID;

void options_setConfig::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "options_setConfig");
    if (config_ == nullptr) { s.store_field("config", "null"); } else { config_->store(s, "config"); }
    s.store_class_end();
  }
}

options_validateConfig::options_validateConfig()
  : config_()
{}

options_validateConfig::options_validateConfig(object_ptr<config> &&config_)
  : config_(std::move(config_))
{}

const std::int32_t options_validateConfig::ID;

void options_validateConfig::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "options_validateConfig");
    if (config_ == nullptr) { s.store_field("config", "null"); } else { config_->store(s, "config"); }
    s.store_class_end();
  }
}

packAccountAddress::packAccountAddress()
  : account_address_()
{}

packAccountAddress::packAccountAddress(object_ptr<unpackedAccountAddress> &&account_address_)
  : account_address_(std::move(account_address_))
{}

const std::int32_t packAccountAddress::ID;

void packAccountAddress::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "packAccountAddress");
    if (account_address_ == nullptr) { s.store_field("account_address", "null"); } else { account_address_->store(s, "account_address"); }
    s.store_class_end();
  }
}

pchan_packPromise::pchan_packPromise()
  : promise_()
{}

pchan_packPromise::pchan_packPromise(object_ptr<pchan_promise> &&promise_)
  : promise_(std::move(promise_))
{}

const std::int32_t pchan_packPromise::ID;

void pchan_packPromise::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_packPromise");
    if (promise_ == nullptr) { s.store_field("promise", "null"); } else { promise_->store(s, "promise"); }
    s.store_class_end();
  }
}

pchan_signPromise::pchan_signPromise()
  : input_key_()
  , promise_()
{}

pchan_signPromise::pchan_signPromise(object_ptr<InputKey> &&input_key_, object_ptr<pchan_promise> &&promise_)
  : input_key_(std::move(input_key_))
  , promise_(std::move(promise_))
{}

const std::int32_t pchan_signPromise::ID;

void pchan_signPromise::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_signPromise");
    if (input_key_ == nullptr) { s.store_field("input_key", "null"); } else { input_key_->store(s, "input_key"); }
    if (promise_ == nullptr) { s.store_field("promise", "null"); } else { promise_->store(s, "promise"); }
    s.store_class_end();
  }
}

pchan_unpackPromise::pchan_unpackPromise()
  : data_()
{}

pchan_unpackPromise::pchan_unpackPromise(td::SecureString &&data_)
  : data_(std::move(data_))
{}

const std::int32_t pchan_unpackPromise::ID;

void pchan_unpackPromise::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_unpackPromise");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

pchan_validatePromise::pchan_validatePromise()
  : public_key_()
  , promise_()
{}

pchan_validatePromise::pchan_validatePromise(std::string const &public_key_, object_ptr<pchan_promise> &&promise_)
  : public_key_(std::move(public_key_))
  , promise_(std::move(promise_))
{}

const std::int32_t pchan_validatePromise::ID;

void pchan_validatePromise::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "pchan_validatePromise");
    s.store_bytes_field("public_key", public_key_);
    if (promise_ == nullptr) { s.store_field("promise", "null"); } else { promise_->store(s, "promise"); }
    s.store_class_end();
  }
}

query_estimateFees::query_estimateFees()
  : id_()
  , ignore_chksig_()
{}

query_estimateFees::query_estimateFees(std::int64_t id_, bool ignore_chksig_)
  : id_(id_)
  , ignore_chksig_(ignore_chksig_)
{}

const std::int32_t query_estimateFees::ID;

void query_estimateFees::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "query_estimateFees");
    s.store_field("id", id_);
    s.store_field("ignore_chksig", ignore_chksig_);
    s.store_class_end();
  }
}

query_forget::query_forget()
  : id_()
{}

query_forget::query_forget(std::int64_t id_)
  : id_(id_)
{}

const std::int32_t query_forget::ID;

void query_forget::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "query_forget");
    s.store_field("id", id_);
    s.store_class_end();
  }
}

query_getInfo::query_getInfo()
  : id_()
{}

query_getInfo::query_getInfo(std::int64_t id_)
  : id_(id_)
{}

const std::int32_t query_getInfo::ID;

void query_getInfo::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "query_getInfo");
    s.store_field("id", id_);
    s.store_class_end();
  }
}

query_send::query_send()
  : id_()
{}

query_send::query_send(std::int64_t id_)
  : id_(id_)
{}

const std::int32_t query_send::ID;

void query_send::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "query_send");
    s.store_field("id", id_);
    s.store_class_end();
  }
}

raw_createAndSendMessage::raw_createAndSendMessage()
  : destination_()
  , initial_account_state_()
  , data_()
{}

raw_createAndSendMessage::raw_createAndSendMessage(object_ptr<accountAddress> &&destination_, std::string const &initial_account_state_, std::string const &data_)
  : destination_(std::move(destination_))
  , initial_account_state_(std::move(initial_account_state_))
  , data_(std::move(data_))
{}

const std::int32_t raw_createAndSendMessage::ID;

void raw_createAndSendMessage::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_createAndSendMessage");
    if (destination_ == nullptr) { s.store_field("destination", "null"); } else { destination_->store(s, "destination"); }
    s.store_bytes_field("initial_account_state", initial_account_state_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

raw_createQuery::raw_createQuery()
  : destination_()
  , init_code_()
  , init_data_()
  , body_()
{}

raw_createQuery::raw_createQuery(object_ptr<accountAddress> &&destination_, std::string const &init_code_, std::string const &init_data_, std::string const &body_)
  : destination_(std::move(destination_))
  , init_code_(std::move(init_code_))
  , init_data_(std::move(init_data_))
  , body_(std::move(body_))
{}

const std::int32_t raw_createQuery::ID;

void raw_createQuery::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_createQuery");
    if (destination_ == nullptr) { s.store_field("destination", "null"); } else { destination_->store(s, "destination"); }
    s.store_bytes_field("init_code", init_code_);
    s.store_bytes_field("init_data", init_data_);
    s.store_bytes_field("body", body_);
    s.store_class_end();
  }
}

raw_getAccountState::raw_getAccountState()
  : account_address_()
{}

raw_getAccountState::raw_getAccountState(object_ptr<accountAddress> &&account_address_)
  : account_address_(std::move(account_address_))
{}

const std::int32_t raw_getAccountState::ID;

void raw_getAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_getAccountState");
    if (account_address_ == nullptr) { s.store_field("account_address", "null"); } else { account_address_->store(s, "account_address"); }
    s.store_class_end();
  }
}

raw_getTransactions::raw_getTransactions()
  : private_key_()
  , account_address_()
  , from_transaction_id_()
{}

raw_getTransactions::raw_getTransactions(object_ptr<InputKey> &&private_key_, object_ptr<accountAddress> &&account_address_, object_ptr<internal_transactionId> &&from_transaction_id_)
  : private_key_(std::move(private_key_))
  , account_address_(std::move(account_address_))
  , from_transaction_id_(std::move(from_transaction_id_))
{}

const std::int32_t raw_getTransactions::ID;

void raw_getTransactions::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_getTransactions");
    if (private_key_ == nullptr) { s.store_field("private_key", "null"); } else { private_key_->store(s, "private_key"); }
    if (account_address_ == nullptr) { s.store_field("account_address", "null"); } else { account_address_->store(s, "account_address"); }
    if (from_transaction_id_ == nullptr) { s.store_field("from_transaction_id", "null"); } else { from_transaction_id_->store(s, "from_transaction_id"); }
    s.store_class_end();
  }
}

raw_sendMessage::raw_sendMessage()
  : body_()
{}

raw_sendMessage::raw_sendMessage(std::string const &body_)
  : body_(std::move(body_))
{}

const std::int32_t raw_sendMessage::ID;

void raw_sendMessage::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "raw_sendMessage");
    s.store_bytes_field("body", body_);
    s.store_class_end();
  }
}

runTests::runTests()
  : dir_()
{}

runTests::runTests(std::string const &dir_)
  : dir_(std::move(dir_))
{}

const std::int32_t runTests::ID;

void runTests::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "runTests");
    s.store_field("dir", dir_);
    s.store_class_end();
  }
}

setLogStream::setLogStream()
  : log_stream_()
{}

setLogStream::setLogStream(object_ptr<LogStream> &&log_stream_)
  : log_stream_(std::move(log_stream_))
{}

const std::int32_t setLogStream::ID;

void setLogStream::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "setLogStream");
    if (log_stream_ == nullptr) { s.store_field("log_stream", "null"); } else { log_stream_->store(s, "log_stream"); }
    s.store_class_end();
  }
}

setLogTagVerbosityLevel::setLogTagVerbosityLevel()
  : tag_()
  , new_verbosity_level_()
{}

setLogTagVerbosityLevel::setLogTagVerbosityLevel(std::string const &tag_, std::int32_t new_verbosity_level_)
  : tag_(std::move(tag_))
  , new_verbosity_level_(new_verbosity_level_)
{}

const std::int32_t setLogTagVerbosityLevel::ID;

void setLogTagVerbosityLevel::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "setLogTagVerbosityLevel");
    s.store_field("tag", tag_);
    s.store_field("new_verbosity_level", new_verbosity_level_);
    s.store_class_end();
  }
}

setLogVerbosityLevel::setLogVerbosityLevel()
  : new_verbosity_level_()
{}

setLogVerbosityLevel::setLogVerbosityLevel(std::int32_t new_verbosity_level_)
  : new_verbosity_level_(new_verbosity_level_)
{}

const std::int32_t setLogVerbosityLevel::ID;

void setLogVerbosityLevel::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "setLogVerbosityLevel");
    s.store_field("new_verbosity_level", new_verbosity_level_);
    s.store_class_end();
  }
}

smc_getCode::smc_getCode()
  : id_()
{}

smc_getCode::smc_getCode(std::int64_t id_)
  : id_(id_)
{}

const std::int32_t smc_getCode::ID;

void smc_getCode::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "smc_getCode");
    s.store_field("id", id_);
    s.store_class_end();
  }
}

smc_getData::smc_getData()
  : id_()
{}

smc_getData::smc_getData(std::int64_t id_)
  : id_(id_)
{}

const std::int32_t smc_getData::ID;

void smc_getData::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "smc_getData");
    s.store_field("id", id_);
    s.store_class_end();
  }
}

smc_getState::smc_getState()
  : id_()
{}

smc_getState::smc_getState(std::int64_t id_)
  : id_(id_)
{}

const std::int32_t smc_getState::ID;

void smc_getState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "smc_getState");
    s.store_field("id", id_);
    s.store_class_end();
  }
}

smc_load::smc_load()
  : account_address_()
{}

smc_load::smc_load(object_ptr<accountAddress> &&account_address_)
  : account_address_(std::move(account_address_))
{}

const std::int32_t smc_load::ID;

void smc_load::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "smc_load");
    if (account_address_ == nullptr) { s.store_field("account_address", "null"); } else { account_address_->store(s, "account_address"); }
    s.store_class_end();
  }
}

smc_runGetMethod::smc_runGetMethod()
  : id_()
  , method_()
  , stack_()
{}

smc_runGetMethod::smc_runGetMethod(std::int64_t id_, object_ptr<smc_MethodId> &&method_, std::vector<object_ptr<tvm_StackEntry>> &&stack_)
  : id_(id_)
  , method_(std::move(method_))
  , stack_(std::move(stack_))
{}

const std::int32_t smc_runGetMethod::ID;

void smc_runGetMethod::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "smc_runGetMethod");
    s.store_field("id", id_);
    if (method_ == nullptr) { s.store_field("method", "null"); } else { method_->store(s, "method"); }
    { const std::vector<object_ptr<tvm_StackEntry>> &v = stack_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const auto vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("stack", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

sync::sync() {
}

const std::int32_t sync::ID;

void sync::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "sync");
    s.store_class_end();
  }
}

unpackAccountAddress::unpackAccountAddress()
  : account_address_()
{}

unpackAccountAddress::unpackAccountAddress(std::string const &account_address_)
  : account_address_(std::move(account_address_))
{}

const std::int32_t unpackAccountAddress::ID;

void unpackAccountAddress::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "unpackAccountAddress");
    s.store_field("account_address", account_address_);
    s.store_class_end();
  }
}

withBlock::withBlock()
  : id_()
  , function_()
{}

withBlock::withBlock(object_ptr<ton_blockIdExt> &&id_, object_ptr<Function> &&function_)
  : id_(std::move(id_))
  , function_(std::move(function_))
{}

const std::int32_t withBlock::ID;

void withBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "withBlock");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    if (function_ == nullptr) { s.store_field("function", "null"); } else { function_->store(s, "function"); }
    s.store_class_end();
  }
}
}  // namespace tonlib_api
}  // namespace ton
