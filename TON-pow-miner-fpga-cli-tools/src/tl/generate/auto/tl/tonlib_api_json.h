#pragma once

#include "auto/tl/tonlib_api.h"

#include "auto/tl/tonlib_api.hpp"

#include "td/utils/JsonBuilder.h"
#include "td/utils/Status.h"

#include "crypto/common/bitstring.h"
namespace ton {
namespace tonlib_api{
  using namespace td;
Result<int32> tl_constructor_from_string(tonlib_api::AccountState *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::Action *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::InitialAccountState *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::InputKey *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::KeyStoreType *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::LogStream *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::SyncState *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::Update *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::dns_Action *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::dns_EntryData *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::msg_Data *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::pchan_Action *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::pchan_State *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::smc_MethodId *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::tvm_StackEntry *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::Object *object, const std::string &str);

Result<int32> tl_constructor_from_string(tonlib_api::Function *object, const std::string &str);

Status from_json(tonlib_api::accountAddress &to, JsonObject &from);
Status from_json(tonlib_api::accountList &to, JsonObject &from);
Status from_json(tonlib_api::accountRevisionList &to, JsonObject &from);
Status from_json(tonlib_api::raw_accountState &to, JsonObject &from);
Status from_json(tonlib_api::wallet_v3_accountState &to, JsonObject &from);
Status from_json(tonlib_api::wallet_highload_v1_accountState &to, JsonObject &from);
Status from_json(tonlib_api::wallet_highload_v2_accountState &to, JsonObject &from);
Status from_json(tonlib_api::dns_accountState &to, JsonObject &from);
Status from_json(tonlib_api::rwallet_accountState &to, JsonObject &from);
Status from_json(tonlib_api::pchan_accountState &to, JsonObject &from);
Status from_json(tonlib_api::uninited_accountState &to, JsonObject &from);
Status from_json(tonlib_api::actionNoop &to, JsonObject &from);
Status from_json(tonlib_api::actionMsg &to, JsonObject &from);
Status from_json(tonlib_api::actionDns &to, JsonObject &from);
Status from_json(tonlib_api::actionPchan &to, JsonObject &from);
Status from_json(tonlib_api::actionRwallet &to, JsonObject &from);
Status from_json(tonlib_api::adnlAddress &to, JsonObject &from);
Status from_json(tonlib_api::bip39Hints &to, JsonObject &from);
Status from_json(tonlib_api::config &to, JsonObject &from);
Status from_json(tonlib_api::data &to, JsonObject &from);
Status from_json(tonlib_api::error &to, JsonObject &from);
Status from_json(tonlib_api::exportedEncryptedKey &to, JsonObject &from);
Status from_json(tonlib_api::exportedKey &to, JsonObject &from);
Status from_json(tonlib_api::exportedPemKey &to, JsonObject &from);
Status from_json(tonlib_api::exportedUnencryptedKey &to, JsonObject &from);
Status from_json(tonlib_api::fees &to, JsonObject &from);
Status from_json(tonlib_api::fullAccountState &to, JsonObject &from);
Status from_json(tonlib_api::raw_initialAccountState &to, JsonObject &from);
Status from_json(tonlib_api::wallet_v3_initialAccountState &to, JsonObject &from);
Status from_json(tonlib_api::wallet_highload_v1_initialAccountState &to, JsonObject &from);
Status from_json(tonlib_api::wallet_highload_v2_initialAccountState &to, JsonObject &from);
Status from_json(tonlib_api::rwallet_initialAccountState &to, JsonObject &from);
Status from_json(tonlib_api::dns_initialAccountState &to, JsonObject &from);
Status from_json(tonlib_api::pchan_initialAccountState &to, JsonObject &from);
Status from_json(tonlib_api::inputKeyRegular &to, JsonObject &from);
Status from_json(tonlib_api::inputKeyFake &to, JsonObject &from);
Status from_json(tonlib_api::key &to, JsonObject &from);
Status from_json(tonlib_api::keyStoreTypeDirectory &to, JsonObject &from);
Status from_json(tonlib_api::keyStoreTypeInMemory &to, JsonObject &from);
Status from_json(tonlib_api::logStreamDefault &to, JsonObject &from);
Status from_json(tonlib_api::logStreamFile &to, JsonObject &from);
Status from_json(tonlib_api::logStreamEmpty &to, JsonObject &from);
Status from_json(tonlib_api::logTags &to, JsonObject &from);
Status from_json(tonlib_api::logVerbosityLevel &to, JsonObject &from);
Status from_json(tonlib_api::ok &to, JsonObject &from);
Status from_json(tonlib_api::options &to, JsonObject &from);
Status from_json(tonlib_api::syncStateDone &to, JsonObject &from);
Status from_json(tonlib_api::syncStateInProgress &to, JsonObject &from);
Status from_json(tonlib_api::unpackedAccountAddress &to, JsonObject &from);
Status from_json(tonlib_api::updateSendLiteServerQuery &to, JsonObject &from);
Status from_json(tonlib_api::updateSyncState &to, JsonObject &from);
Status from_json(tonlib_api::blocks_accountTransactionId &to, JsonObject &from);
Status from_json(tonlib_api::blocks_header &to, JsonObject &from);
Status from_json(tonlib_api::blocks_masterchainInfo &to, JsonObject &from);
Status from_json(tonlib_api::blocks_shards &to, JsonObject &from);
Status from_json(tonlib_api::blocks_transactions &to, JsonObject &from);
Status from_json(tonlib_api::dns_actionDeleteAll &to, JsonObject &from);
Status from_json(tonlib_api::dns_actionDelete &to, JsonObject &from);
Status from_json(tonlib_api::dns_actionSet &to, JsonObject &from);
Status from_json(tonlib_api::dns_entry &to, JsonObject &from);
Status from_json(tonlib_api::dns_entryDataUnknown &to, JsonObject &from);
Status from_json(tonlib_api::dns_entryDataText &to, JsonObject &from);
Status from_json(tonlib_api::dns_entryDataNextResolver &to, JsonObject &from);
Status from_json(tonlib_api::dns_entryDataSmcAddress &to, JsonObject &from);
Status from_json(tonlib_api::dns_entryDataAdnlAddress &to, JsonObject &from);
Status from_json(tonlib_api::dns_resolved &to, JsonObject &from);
Status from_json(tonlib_api::ton_blockId &to, JsonObject &from);
Status from_json(tonlib_api::internal_transactionId &to, JsonObject &from);
Status from_json(tonlib_api::liteServer_info &to, JsonObject &from);
Status from_json(tonlib_api::blocks_shortTxId &to, JsonObject &from);
Status from_json(tonlib_api::msg_dataRaw &to, JsonObject &from);
Status from_json(tonlib_api::msg_dataText &to, JsonObject &from);
Status from_json(tonlib_api::msg_dataDecryptedText &to, JsonObject &from);
Status from_json(tonlib_api::msg_dataEncryptedText &to, JsonObject &from);
Status from_json(tonlib_api::msg_dataDecrypted &to, JsonObject &from);
Status from_json(tonlib_api::msg_dataDecryptedArray &to, JsonObject &from);
Status from_json(tonlib_api::msg_dataEncrypted &to, JsonObject &from);
Status from_json(tonlib_api::msg_dataEncryptedArray &to, JsonObject &from);
Status from_json(tonlib_api::msg_message &to, JsonObject &from);
Status from_json(tonlib_api::options_configInfo &to, JsonObject &from);
Status from_json(tonlib_api::options_info &to, JsonObject &from);
Status from_json(tonlib_api::pchan_actionInit &to, JsonObject &from);
Status from_json(tonlib_api::pchan_actionClose &to, JsonObject &from);
Status from_json(tonlib_api::pchan_actionTimeout &to, JsonObject &from);
Status from_json(tonlib_api::pchan_config &to, JsonObject &from);
Status from_json(tonlib_api::pchan_promise &to, JsonObject &from);
Status from_json(tonlib_api::pchan_stateInit &to, JsonObject &from);
Status from_json(tonlib_api::pchan_stateClose &to, JsonObject &from);
Status from_json(tonlib_api::pchan_statePayout &to, JsonObject &from);
Status from_json(tonlib_api::query_fees &to, JsonObject &from);
Status from_json(tonlib_api::query_info &to, JsonObject &from);
Status from_json(tonlib_api::raw_fullAccountState &to, JsonObject &from);
Status from_json(tonlib_api::raw_message &to, JsonObject &from);
Status from_json(tonlib_api::raw_transaction &to, JsonObject &from);
Status from_json(tonlib_api::raw_transactions &to, JsonObject &from);
Status from_json(tonlib_api::rwallet_actionInit &to, JsonObject &from);
Status from_json(tonlib_api::rwallet_config &to, JsonObject &from);
Status from_json(tonlib_api::rwallet_limit &to, JsonObject &from);
Status from_json(tonlib_api::smc_info &to, JsonObject &from);
Status from_json(tonlib_api::smc_methodIdNumber &to, JsonObject &from);
Status from_json(tonlib_api::smc_methodIdName &to, JsonObject &from);
Status from_json(tonlib_api::smc_runResult &to, JsonObject &from);
Status from_json(tonlib_api::ton_blockIdExt &to, JsonObject &from);
Status from_json(tonlib_api::tvm_cell &to, JsonObject &from);
Status from_json(tonlib_api::tvm_list &to, JsonObject &from);
Status from_json(tonlib_api::tvm_numberDecimal &to, JsonObject &from);
Status from_json(tonlib_api::tvm_slice &to, JsonObject &from);
Status from_json(tonlib_api::tvm_stackEntrySlice &to, JsonObject &from);
Status from_json(tonlib_api::tvm_stackEntryCell &to, JsonObject &from);
Status from_json(tonlib_api::tvm_stackEntryNumber &to, JsonObject &from);
Status from_json(tonlib_api::tvm_stackEntryTuple &to, JsonObject &from);
Status from_json(tonlib_api::tvm_stackEntryList &to, JsonObject &from);
Status from_json(tonlib_api::tvm_stackEntryUnsupported &to, JsonObject &from);
Status from_json(tonlib_api::tvm_tuple &to, JsonObject &from);
Status from_json(tonlib_api::addLogMessage &to, JsonObject &from);
Status from_json(tonlib_api::blocks_getBlockHeader &to, JsonObject &from);
Status from_json(tonlib_api::blocks_getMasterchainInfo &to, JsonObject &from);
Status from_json(tonlib_api::blocks_getShards &to, JsonObject &from);
Status from_json(tonlib_api::blocks_getTransactions &to, JsonObject &from);
Status from_json(tonlib_api::blocks_lookupBlock &to, JsonObject &from);
Status from_json(tonlib_api::changeLocalPassword &to, JsonObject &from);
Status from_json(tonlib_api::close &to, JsonObject &from);
Status from_json(tonlib_api::createNewKey &to, JsonObject &from);
Status from_json(tonlib_api::createQuery &to, JsonObject &from);
Status from_json(tonlib_api::decrypt &to, JsonObject &from);
Status from_json(tonlib_api::deleteAllKeys &to, JsonObject &from);
Status from_json(tonlib_api::deleteKey &to, JsonObject &from);
Status from_json(tonlib_api::dns_resolve &to, JsonObject &from);
Status from_json(tonlib_api::encrypt &to, JsonObject &from);
Status from_json(tonlib_api::exportEncryptedKey &to, JsonObject &from);
Status from_json(tonlib_api::exportKey &to, JsonObject &from);
Status from_json(tonlib_api::exportPemKey &to, JsonObject &from);
Status from_json(tonlib_api::exportUnencryptedKey &to, JsonObject &from);
Status from_json(tonlib_api::getAccountAddress &to, JsonObject &from);
Status from_json(tonlib_api::getAccountState &to, JsonObject &from);
Status from_json(tonlib_api::getBip39Hints &to, JsonObject &from);
Status from_json(tonlib_api::getLogStream &to, JsonObject &from);
Status from_json(tonlib_api::getLogTagVerbosityLevel &to, JsonObject &from);
Status from_json(tonlib_api::getLogTags &to, JsonObject &from);
Status from_json(tonlib_api::getLogVerbosityLevel &to, JsonObject &from);
Status from_json(tonlib_api::guessAccount &to, JsonObject &from);
Status from_json(tonlib_api::guessAccountRevision &to, JsonObject &from);
Status from_json(tonlib_api::importEncryptedKey &to, JsonObject &from);
Status from_json(tonlib_api::importKey &to, JsonObject &from);
Status from_json(tonlib_api::importPemKey &to, JsonObject &from);
Status from_json(tonlib_api::importUnencryptedKey &to, JsonObject &from);
Status from_json(tonlib_api::init &to, JsonObject &from);
Status from_json(tonlib_api::kdf &to, JsonObject &from);
Status from_json(tonlib_api::liteServer_getInfo &to, JsonObject &from);
Status from_json(tonlib_api::msg_decrypt &to, JsonObject &from);
Status from_json(tonlib_api::msg_decryptWithProof &to, JsonObject &from);
Status from_json(tonlib_api::onLiteServerQueryError &to, JsonObject &from);
Status from_json(tonlib_api::onLiteServerQueryResult &to, JsonObject &from);
Status from_json(tonlib_api::options_setConfig &to, JsonObject &from);
Status from_json(tonlib_api::options_validateConfig &to, JsonObject &from);
Status from_json(tonlib_api::packAccountAddress &to, JsonObject &from);
Status from_json(tonlib_api::pchan_packPromise &to, JsonObject &from);
Status from_json(tonlib_api::pchan_signPromise &to, JsonObject &from);
Status from_json(tonlib_api::pchan_unpackPromise &to, JsonObject &from);
Status from_json(tonlib_api::pchan_validatePromise &to, JsonObject &from);
Status from_json(tonlib_api::query_estimateFees &to, JsonObject &from);
Status from_json(tonlib_api::query_forget &to, JsonObject &from);
Status from_json(tonlib_api::query_getInfo &to, JsonObject &from);
Status from_json(tonlib_api::query_send &to, JsonObject &from);
Status from_json(tonlib_api::raw_createAndSendMessage &to, JsonObject &from);
Status from_json(tonlib_api::raw_createQuery &to, JsonObject &from);
Status from_json(tonlib_api::raw_getAccountState &to, JsonObject &from);
Status from_json(tonlib_api::raw_getTransactions &to, JsonObject &from);
Status from_json(tonlib_api::raw_sendMessage &to, JsonObject &from);
Status from_json(tonlib_api::runTests &to, JsonObject &from);
Status from_json(tonlib_api::setLogStream &to, JsonObject &from);
Status from_json(tonlib_api::setLogTagVerbosityLevel &to, JsonObject &from);
Status from_json(tonlib_api::setLogVerbosityLevel &to, JsonObject &from);
Status from_json(tonlib_api::smc_getCode &to, JsonObject &from);
Status from_json(tonlib_api::smc_getData &to, JsonObject &from);
Status from_json(tonlib_api::smc_getState &to, JsonObject &from);
Status from_json(tonlib_api::smc_load &to, JsonObject &from);
Status from_json(tonlib_api::smc_runGetMethod &to, JsonObject &from);
Status from_json(tonlib_api::sync &to, JsonObject &from);
Status from_json(tonlib_api::unpackAccountAddress &to, JsonObject &from);
Status from_json(tonlib_api::withBlock &to, JsonObject &from);
void to_json(JsonValueScope &jv, const tonlib_api::accountAddress &object);

void to_json(JsonValueScope &jv, const tonlib_api::accountList &object);

void to_json(JsonValueScope &jv, const tonlib_api::accountRevisionList &object);

void to_json(JsonValueScope &jv, const tonlib_api::AccountState &object);
void to_json(JsonValueScope &jv, const tonlib_api::raw_accountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::wallet_v3_accountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::wallet_highload_v1_accountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::wallet_highload_v2_accountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_accountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::rwallet_accountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_accountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::uninited_accountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::Action &object);
void to_json(JsonValueScope &jv, const tonlib_api::actionNoop &object);

void to_json(JsonValueScope &jv, const tonlib_api::actionMsg &object);

void to_json(JsonValueScope &jv, const tonlib_api::actionDns &object);

void to_json(JsonValueScope &jv, const tonlib_api::actionPchan &object);

void to_json(JsonValueScope &jv, const tonlib_api::actionRwallet &object);

void to_json(JsonValueScope &jv, const tonlib_api::adnlAddress &object);

void to_json(JsonValueScope &jv, const tonlib_api::bip39Hints &object);

void to_json(JsonValueScope &jv, const tonlib_api::config &object);

void to_json(JsonValueScope &jv, const tonlib_api::data &object);

void to_json(JsonValueScope &jv, const tonlib_api::error &object);

void to_json(JsonValueScope &jv, const tonlib_api::exportedEncryptedKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::exportedKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::exportedPemKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::exportedUnencryptedKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::fees &object);

void to_json(JsonValueScope &jv, const tonlib_api::fullAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::InitialAccountState &object);
void to_json(JsonValueScope &jv, const tonlib_api::raw_initialAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::wallet_v3_initialAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::wallet_highload_v1_initialAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::wallet_highload_v2_initialAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::rwallet_initialAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_initialAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_initialAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::InputKey &object);
void to_json(JsonValueScope &jv, const tonlib_api::inputKeyRegular &object);

void to_json(JsonValueScope &jv, const tonlib_api::inputKeyFake &object);

void to_json(JsonValueScope &jv, const tonlib_api::key &object);

void to_json(JsonValueScope &jv, const tonlib_api::KeyStoreType &object);
void to_json(JsonValueScope &jv, const tonlib_api::keyStoreTypeDirectory &object);

void to_json(JsonValueScope &jv, const tonlib_api::keyStoreTypeInMemory &object);

void to_json(JsonValueScope &jv, const tonlib_api::LogStream &object);
void to_json(JsonValueScope &jv, const tonlib_api::logStreamDefault &object);

void to_json(JsonValueScope &jv, const tonlib_api::logStreamFile &object);

void to_json(JsonValueScope &jv, const tonlib_api::logStreamEmpty &object);

void to_json(JsonValueScope &jv, const tonlib_api::logTags &object);

void to_json(JsonValueScope &jv, const tonlib_api::logVerbosityLevel &object);

void to_json(JsonValueScope &jv, const tonlib_api::ok &object);

void to_json(JsonValueScope &jv, const tonlib_api::options &object);

void to_json(JsonValueScope &jv, const tonlib_api::SyncState &object);
void to_json(JsonValueScope &jv, const tonlib_api::syncStateDone &object);

void to_json(JsonValueScope &jv, const tonlib_api::syncStateInProgress &object);

void to_json(JsonValueScope &jv, const tonlib_api::unpackedAccountAddress &object);

void to_json(JsonValueScope &jv, const tonlib_api::Update &object);
void to_json(JsonValueScope &jv, const tonlib_api::updateSendLiteServerQuery &object);

void to_json(JsonValueScope &jv, const tonlib_api::updateSyncState &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_accountTransactionId &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_header &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_masterchainInfo &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_shards &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_transactions &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_Action &object);
void to_json(JsonValueScope &jv, const tonlib_api::dns_actionDeleteAll &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_actionDelete &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_actionSet &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_entry &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_EntryData &object);
void to_json(JsonValueScope &jv, const tonlib_api::dns_entryDataUnknown &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_entryDataText &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_entryDataNextResolver &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_entryDataSmcAddress &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_entryDataAdnlAddress &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_resolved &object);

void to_json(JsonValueScope &jv, const tonlib_api::ton_blockId &object);

void to_json(JsonValueScope &jv, const tonlib_api::internal_transactionId &object);

void to_json(JsonValueScope &jv, const tonlib_api::liteServer_info &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_shortTxId &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_Data &object);
void to_json(JsonValueScope &jv, const tonlib_api::msg_dataRaw &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_dataText &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_dataDecryptedText &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_dataEncryptedText &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_dataDecrypted &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_dataDecryptedArray &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_dataEncrypted &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_dataEncryptedArray &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_message &object);

void to_json(JsonValueScope &jv, const tonlib_api::options_configInfo &object);

void to_json(JsonValueScope &jv, const tonlib_api::options_info &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_Action &object);
void to_json(JsonValueScope &jv, const tonlib_api::pchan_actionInit &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_actionClose &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_actionTimeout &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_config &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_promise &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_State &object);
void to_json(JsonValueScope &jv, const tonlib_api::pchan_stateInit &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_stateClose &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_statePayout &object);

void to_json(JsonValueScope &jv, const tonlib_api::query_fees &object);

void to_json(JsonValueScope &jv, const tonlib_api::query_info &object);

void to_json(JsonValueScope &jv, const tonlib_api::raw_fullAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::raw_message &object);

void to_json(JsonValueScope &jv, const tonlib_api::raw_transaction &object);

void to_json(JsonValueScope &jv, const tonlib_api::raw_transactions &object);

void to_json(JsonValueScope &jv, const tonlib_api::rwallet_actionInit &object);

void to_json(JsonValueScope &jv, const tonlib_api::rwallet_config &object);

void to_json(JsonValueScope &jv, const tonlib_api::rwallet_limit &object);

void to_json(JsonValueScope &jv, const tonlib_api::smc_info &object);

void to_json(JsonValueScope &jv, const tonlib_api::smc_MethodId &object);
void to_json(JsonValueScope &jv, const tonlib_api::smc_methodIdNumber &object);

void to_json(JsonValueScope &jv, const tonlib_api::smc_methodIdName &object);

void to_json(JsonValueScope &jv, const tonlib_api::smc_runResult &object);

void to_json(JsonValueScope &jv, const tonlib_api::ton_blockIdExt &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_cell &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_list &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_numberDecimal &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_slice &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_StackEntry &object);
void to_json(JsonValueScope &jv, const tonlib_api::tvm_stackEntrySlice &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_stackEntryCell &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_stackEntryNumber &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_stackEntryTuple &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_stackEntryList &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_stackEntryUnsupported &object);

void to_json(JsonValueScope &jv, const tonlib_api::tvm_tuple &object);

void to_json(JsonValueScope &jv, const tonlib_api::addLogMessage &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_getBlockHeader &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_getMasterchainInfo &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_getShards &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_getTransactions &object);

void to_json(JsonValueScope &jv, const tonlib_api::blocks_lookupBlock &object);

void to_json(JsonValueScope &jv, const tonlib_api::changeLocalPassword &object);

void to_json(JsonValueScope &jv, const tonlib_api::close &object);

void to_json(JsonValueScope &jv, const tonlib_api::createNewKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::createQuery &object);

void to_json(JsonValueScope &jv, const tonlib_api::decrypt &object);

void to_json(JsonValueScope &jv, const tonlib_api::deleteAllKeys &object);

void to_json(JsonValueScope &jv, const tonlib_api::deleteKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::dns_resolve &object);

void to_json(JsonValueScope &jv, const tonlib_api::encrypt &object);

void to_json(JsonValueScope &jv, const tonlib_api::exportEncryptedKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::exportKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::exportPemKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::exportUnencryptedKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::getAccountAddress &object);

void to_json(JsonValueScope &jv, const tonlib_api::getAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::getBip39Hints &object);

void to_json(JsonValueScope &jv, const tonlib_api::getLogStream &object);

void to_json(JsonValueScope &jv, const tonlib_api::getLogTagVerbosityLevel &object);

void to_json(JsonValueScope &jv, const tonlib_api::getLogTags &object);

void to_json(JsonValueScope &jv, const tonlib_api::getLogVerbosityLevel &object);

void to_json(JsonValueScope &jv, const tonlib_api::guessAccount &object);

void to_json(JsonValueScope &jv, const tonlib_api::guessAccountRevision &object);

void to_json(JsonValueScope &jv, const tonlib_api::importEncryptedKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::importKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::importPemKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::importUnencryptedKey &object);

void to_json(JsonValueScope &jv, const tonlib_api::init &object);

void to_json(JsonValueScope &jv, const tonlib_api::kdf &object);

void to_json(JsonValueScope &jv, const tonlib_api::liteServer_getInfo &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_decrypt &object);

void to_json(JsonValueScope &jv, const tonlib_api::msg_decryptWithProof &object);

void to_json(JsonValueScope &jv, const tonlib_api::onLiteServerQueryError &object);

void to_json(JsonValueScope &jv, const tonlib_api::onLiteServerQueryResult &object);

void to_json(JsonValueScope &jv, const tonlib_api::options_setConfig &object);

void to_json(JsonValueScope &jv, const tonlib_api::options_validateConfig &object);

void to_json(JsonValueScope &jv, const tonlib_api::packAccountAddress &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_packPromise &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_signPromise &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_unpackPromise &object);

void to_json(JsonValueScope &jv, const tonlib_api::pchan_validatePromise &object);

void to_json(JsonValueScope &jv, const tonlib_api::query_estimateFees &object);

void to_json(JsonValueScope &jv, const tonlib_api::query_forget &object);

void to_json(JsonValueScope &jv, const tonlib_api::query_getInfo &object);

void to_json(JsonValueScope &jv, const tonlib_api::query_send &object);

void to_json(JsonValueScope &jv, const tonlib_api::raw_createAndSendMessage &object);

void to_json(JsonValueScope &jv, const tonlib_api::raw_createQuery &object);

void to_json(JsonValueScope &jv, const tonlib_api::raw_getAccountState &object);

void to_json(JsonValueScope &jv, const tonlib_api::raw_getTransactions &object);

void to_json(JsonValueScope &jv, const tonlib_api::raw_sendMessage &object);

void to_json(JsonValueScope &jv, const tonlib_api::runTests &object);

void to_json(JsonValueScope &jv, const tonlib_api::setLogStream &object);

void to_json(JsonValueScope &jv, const tonlib_api::setLogTagVerbosityLevel &object);

void to_json(JsonValueScope &jv, const tonlib_api::setLogVerbosityLevel &object);

void to_json(JsonValueScope &jv, const tonlib_api::smc_getCode &object);

void to_json(JsonValueScope &jv, const tonlib_api::smc_getData &object);

void to_json(JsonValueScope &jv, const tonlib_api::smc_getState &object);

void to_json(JsonValueScope &jv, const tonlib_api::smc_load &object);

void to_json(JsonValueScope &jv, const tonlib_api::smc_runGetMethod &object);

void to_json(JsonValueScope &jv, const tonlib_api::sync &object);

void to_json(JsonValueScope &jv, const tonlib_api::unpackAccountAddress &object);

void to_json(JsonValueScope &jv, const tonlib_api::withBlock &object);

inline void to_json(JsonValueScope &jv, const ton::tonlib_api::Object &object) {
  ton::tonlib_api::downcast_call(const_cast<ton::tonlib_api::Object &>(object),[&jv](const auto &object) { to_json(jv, object); });
}
inline void to_json(JsonValueScope &jv, const ton::tonlib_api::Function &object) {
  ton::tonlib_api::downcast_call(const_cast<ton::tonlib_api::Function &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
}  // namespace tonlib_api
}  // namespace ton
