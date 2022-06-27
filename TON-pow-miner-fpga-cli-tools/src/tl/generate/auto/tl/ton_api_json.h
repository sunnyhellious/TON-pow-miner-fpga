#pragma once

#include "auto/tl/ton_api.h"

#include "auto/tl/ton_api.hpp"

#include "td/utils/JsonBuilder.h"
#include "td/utils/Status.h"

#include "crypto/common/bitstring.h"
namespace ton {
namespace ton_api{
  using namespace td;
Result<int32> tl_constructor_from_string(ton_api::Hashable *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::PrivateKey *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::PublicKey *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::TestObject *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::adnl_Address *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::adnl_Message *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::adnl_Proxy *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::adnl_ProxyControlPacket *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::catchain_BlockResult *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::catchain_Difference *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::catchain_block_inner_Data *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::db_block_Info *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::db_blockdb_Key *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::db_filedb_Key *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::db_files_Key *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::db_lt_Key *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::db_root_Key *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::db_state_Key *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::dht_UpdateRule *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::dht_ValueResult *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::dht_config_Local *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::engine_Addr *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::fec_Type *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::liteserver_config_Local *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::overlay_Broadcast *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::overlay_Certificate *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::rldp_Message *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::rldp_MessagePart *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::rldp2_MessagePart *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::storage_Update *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::tcp_Message *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::ton_BlockId *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::tonNode_ArchiveInfo *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::tonNode_BlockDescription *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::tonNode_Broadcast *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::tonNode_DataFull *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::tonNode_Prepared *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::tonNode_PreparedProof *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::tonNode_PreparedState *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::validator_Group *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::validator_config_Local *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::validatorSession_Config *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::validatorSession_Message *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::validatorSession_round_Message *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::Object *object, const std::string &str);

Result<int32> tl_constructor_from_string(ton_api::Function *object, const std::string &str);

Status from_json(ton_api::hashable_bool &to, JsonObject &from);
Status from_json(ton_api::hashable_int32 &to, JsonObject &from);
Status from_json(ton_api::hashable_int64 &to, JsonObject &from);
Status from_json(ton_api::hashable_int256 &to, JsonObject &from);
Status from_json(ton_api::hashable_bytes &to, JsonObject &from);
Status from_json(ton_api::hashable_pair &to, JsonObject &from);
Status from_json(ton_api::hashable_vector &to, JsonObject &from);
Status from_json(ton_api::hashable_validatorSessionOldRound &to, JsonObject &from);
Status from_json(ton_api::hashable_validatorSessionRoundAttempt &to, JsonObject &from);
Status from_json(ton_api::hashable_validatorSessionRound &to, JsonObject &from);
Status from_json(ton_api::hashable_blockSignature &to, JsonObject &from);
Status from_json(ton_api::hashable_sentBlock &to, JsonObject &from);
Status from_json(ton_api::hashable_sentBlockEmpty &to, JsonObject &from);
Status from_json(ton_api::hashable_vote &to, JsonObject &from);
Status from_json(ton_api::hashable_blockCandidate &to, JsonObject &from);
Status from_json(ton_api::hashable_blockVoteCandidate &to, JsonObject &from);
Status from_json(ton_api::hashable_blockCandidateAttempt &to, JsonObject &from);
Status from_json(ton_api::hashable_cntVector &to, JsonObject &from);
Status from_json(ton_api::hashable_cntSortedVector &to, JsonObject &from);
Status from_json(ton_api::hashable_validatorSession &to, JsonObject &from);
Status from_json(ton_api::storage_ok &to, JsonObject &from);
Status from_json(ton_api::pk_unenc &to, JsonObject &from);
Status from_json(ton_api::pk_ed25519 &to, JsonObject &from);
Status from_json(ton_api::pk_aes &to, JsonObject &from);
Status from_json(ton_api::pk_overlay &to, JsonObject &from);
Status from_json(ton_api::pub_unenc &to, JsonObject &from);
Status from_json(ton_api::pub_ed25519 &to, JsonObject &from);
Status from_json(ton_api::pub_aes &to, JsonObject &from);
Status from_json(ton_api::pub_overlay &to, JsonObject &from);
Status from_json(ton_api::testObject &to, JsonObject &from);
Status from_json(ton_api::testString &to, JsonObject &from);
Status from_json(ton_api::testInt &to, JsonObject &from);
Status from_json(ton_api::testVectorBytes &to, JsonObject &from);
Status from_json(ton_api::adnl_address_udp &to, JsonObject &from);
Status from_json(ton_api::adnl_address_udp6 &to, JsonObject &from);
Status from_json(ton_api::adnl_address_tunnel &to, JsonObject &from);
Status from_json(ton_api::adnl_addressList &to, JsonObject &from);
Status from_json(ton_api::adnl_message_createChannel &to, JsonObject &from);
Status from_json(ton_api::adnl_message_confirmChannel &to, JsonObject &from);
Status from_json(ton_api::adnl_message_custom &to, JsonObject &from);
Status from_json(ton_api::adnl_message_nop &to, JsonObject &from);
Status from_json(ton_api::adnl_message_reinit &to, JsonObject &from);
Status from_json(ton_api::adnl_message_query &to, JsonObject &from);
Status from_json(ton_api::adnl_message_answer &to, JsonObject &from);
Status from_json(ton_api::adnl_message_part &to, JsonObject &from);
Status from_json(ton_api::adnl_node &to, JsonObject &from);
Status from_json(ton_api::adnl_nodes &to, JsonObject &from);
Status from_json(ton_api::adnl_packetContents &to, JsonObject &from);
Status from_json(ton_api::adnl_pong &to, JsonObject &from);
Status from_json(ton_api::adnl_proxy_none &to, JsonObject &from);
Status from_json(ton_api::adnl_proxy_fast &to, JsonObject &from);
Status from_json(ton_api::adnl_proxyControlPacketPing &to, JsonObject &from);
Status from_json(ton_api::adnl_proxyControlPacketPong &to, JsonObject &from);
Status from_json(ton_api::adnl_proxyControlPacketRegister &to, JsonObject &from);
Status from_json(ton_api::adnl_proxyPacketHeader &to, JsonObject &from);
Status from_json(ton_api::adnl_proxyToFastHash &to, JsonObject &from);
Status from_json(ton_api::adnl_proxyToFast &to, JsonObject &from);
Status from_json(ton_api::adnl_tunnelPacketContents &to, JsonObject &from);
Status from_json(ton_api::adnl_config_global &to, JsonObject &from);
Status from_json(ton_api::adnl_db_node_key &to, JsonObject &from);
Status from_json(ton_api::adnl_db_node_value &to, JsonObject &from);
Status from_json(ton_api::adnl_id_short &to, JsonObject &from);
Status from_json(ton_api::catchain_block &to, JsonObject &from);
Status from_json(ton_api::catchain_blockNotFound &to, JsonObject &from);
Status from_json(ton_api::catchain_blockResult &to, JsonObject &from);
Status from_json(ton_api::catchain_blocks &to, JsonObject &from);
Status from_json(ton_api::catchain_difference &to, JsonObject &from);
Status from_json(ton_api::catchain_differenceFork &to, JsonObject &from);
Status from_json(ton_api::catchain_firstblock &to, JsonObject &from);
Status from_json(ton_api::catchain_sent &to, JsonObject &from);
Status from_json(ton_api::catchain_blockUpdate &to, JsonObject &from);
Status from_json(ton_api::catchain_block_data &to, JsonObject &from);
Status from_json(ton_api::catchain_block_dep &to, JsonObject &from);
Status from_json(ton_api::catchain_block_id &to, JsonObject &from);
Status from_json(ton_api::catchain_block_data_badBlock &to, JsonObject &from);
Status from_json(ton_api::catchain_block_data_fork &to, JsonObject &from);
Status from_json(ton_api::catchain_block_data_nop &to, JsonObject &from);
Status from_json(ton_api::catchain_block_data_vector &to, JsonObject &from);
Status from_json(ton_api::catchain_config_global &to, JsonObject &from);
Status from_json(ton_api::config_global &to, JsonObject &from);
Status from_json(ton_api::config_local &to, JsonObject &from);
Status from_json(ton_api::control_config_local &to, JsonObject &from);
Status from_json(ton_api::db_candidate &to, JsonObject &from);
Status from_json(ton_api::db_block_info &to, JsonObject &from);
Status from_json(ton_api::db_block_packedInfo &to, JsonObject &from);
Status from_json(ton_api::db_block_archivedInfo &to, JsonObject &from);
Status from_json(ton_api::db_blockdb_key_lru &to, JsonObject &from);
Status from_json(ton_api::db_blockdb_key_value &to, JsonObject &from);
Status from_json(ton_api::db_blockdb_lru &to, JsonObject &from);
Status from_json(ton_api::db_blockdb_value &to, JsonObject &from);
Status from_json(ton_api::db_candidate_id &to, JsonObject &from);
Status from_json(ton_api::db_celldb_value &to, JsonObject &from);
Status from_json(ton_api::db_celldb_key_value &to, JsonObject &from);
Status from_json(ton_api::db_filedb_key_empty &to, JsonObject &from);
Status from_json(ton_api::db_filedb_key_blockFile &to, JsonObject &from);
Status from_json(ton_api::db_filedb_key_zeroStateFile &to, JsonObject &from);
Status from_json(ton_api::db_filedb_key_persistentStateFile &to, JsonObject &from);
Status from_json(ton_api::db_filedb_key_proof &to, JsonObject &from);
Status from_json(ton_api::db_filedb_key_proofLink &to, JsonObject &from);
Status from_json(ton_api::db_filedb_key_signatures &to, JsonObject &from);
Status from_json(ton_api::db_filedb_key_candidate &to, JsonObject &from);
Status from_json(ton_api::db_filedb_key_blockInfo &to, JsonObject &from);
Status from_json(ton_api::db_filedb_value &to, JsonObject &from);
Status from_json(ton_api::db_files_index_key &to, JsonObject &from);
Status from_json(ton_api::db_files_package_key &to, JsonObject &from);
Status from_json(ton_api::db_files_index_value &to, JsonObject &from);
Status from_json(ton_api::db_files_package_firstBlock &to, JsonObject &from);
Status from_json(ton_api::db_files_package_value &to, JsonObject &from);
Status from_json(ton_api::db_lt_el_key &to, JsonObject &from);
Status from_json(ton_api::db_lt_desc_key &to, JsonObject &from);
Status from_json(ton_api::db_lt_shard_key &to, JsonObject &from);
Status from_json(ton_api::db_lt_status_key &to, JsonObject &from);
Status from_json(ton_api::db_lt_desc_value &to, JsonObject &from);
Status from_json(ton_api::db_lt_el_value &to, JsonObject &from);
Status from_json(ton_api::db_lt_shard_value &to, JsonObject &from);
Status from_json(ton_api::db_lt_status_value &to, JsonObject &from);
Status from_json(ton_api::db_root_config &to, JsonObject &from);
Status from_json(ton_api::db_root_dbDescription &to, JsonObject &from);
Status from_json(ton_api::db_root_key_cellDb &to, JsonObject &from);
Status from_json(ton_api::db_root_key_blockDb &to, JsonObject &from);
Status from_json(ton_api::db_root_key_config &to, JsonObject &from);
Status from_json(ton_api::db_state_asyncSerializer &to, JsonObject &from);
Status from_json(ton_api::db_state_dbVersion &to, JsonObject &from);
Status from_json(ton_api::db_state_destroyedSessions &to, JsonObject &from);
Status from_json(ton_api::db_state_gcBlockId &to, JsonObject &from);
Status from_json(ton_api::db_state_hardforks &to, JsonObject &from);
Status from_json(ton_api::db_state_initBlockId &to, JsonObject &from);
Status from_json(ton_api::db_state_key_destroyedSessions &to, JsonObject &from);
Status from_json(ton_api::db_state_key_initBlockId &to, JsonObject &from);
Status from_json(ton_api::db_state_key_gcBlockId &to, JsonObject &from);
Status from_json(ton_api::db_state_key_shardClient &to, JsonObject &from);
Status from_json(ton_api::db_state_key_asyncSerializer &to, JsonObject &from);
Status from_json(ton_api::db_state_key_hardforks &to, JsonObject &from);
Status from_json(ton_api::db_state_key_dbVersion &to, JsonObject &from);
Status from_json(ton_api::db_state_shardClient &to, JsonObject &from);
Status from_json(ton_api::dht_key &to, JsonObject &from);
Status from_json(ton_api::dht_keyDescription &to, JsonObject &from);
Status from_json(ton_api::dht_message &to, JsonObject &from);
Status from_json(ton_api::dht_node &to, JsonObject &from);
Status from_json(ton_api::dht_nodes &to, JsonObject &from);
Status from_json(ton_api::dht_pong &to, JsonObject &from);
Status from_json(ton_api::dht_stored &to, JsonObject &from);
Status from_json(ton_api::dht_updateRule_signature &to, JsonObject &from);
Status from_json(ton_api::dht_updateRule_anybody &to, JsonObject &from);
Status from_json(ton_api::dht_updateRule_overlayNodes &to, JsonObject &from);
Status from_json(ton_api::dht_value &to, JsonObject &from);
Status from_json(ton_api::dht_valueNotFound &to, JsonObject &from);
Status from_json(ton_api::dht_valueFound &to, JsonObject &from);
Status from_json(ton_api::dht_config_global &to, JsonObject &from);
Status from_json(ton_api::dht_config_local &to, JsonObject &from);
Status from_json(ton_api::dht_config_random_local &to, JsonObject &from);
Status from_json(ton_api::dht_db_bucket &to, JsonObject &from);
Status from_json(ton_api::dht_db_key_bucket &to, JsonObject &from);
Status from_json(ton_api::dummyworkchain0_config_global &to, JsonObject &from);
Status from_json(ton_api::engine_addr &to, JsonObject &from);
Status from_json(ton_api::engine_addrProxy &to, JsonObject &from);
Status from_json(ton_api::engine_adnl &to, JsonObject &from);
Status from_json(ton_api::engine_controlInterface &to, JsonObject &from);
Status from_json(ton_api::engine_controlProcess &to, JsonObject &from);
Status from_json(ton_api::engine_dht &to, JsonObject &from);
Status from_json(ton_api::engine_gc &to, JsonObject &from);
Status from_json(ton_api::engine_liteServer &to, JsonObject &from);
Status from_json(ton_api::engine_validator &to, JsonObject &from);
Status from_json(ton_api::engine_validatorAdnlAddress &to, JsonObject &from);
Status from_json(ton_api::engine_validatorTempKey &to, JsonObject &from);
Status from_json(ton_api::engine_adnlProxy_config &to, JsonObject &from);
Status from_json(ton_api::engine_adnlProxy_port &to, JsonObject &from);
Status from_json(ton_api::engine_dht_config &to, JsonObject &from);
Status from_json(ton_api::engine_validator_config &to, JsonObject &from);
Status from_json(ton_api::engine_validator_controlQueryError &to, JsonObject &from);
Status from_json(ton_api::engine_validator_dhtServerStatus &to, JsonObject &from);
Status from_json(ton_api::engine_validator_dhtServersStatus &to, JsonObject &from);
Status from_json(ton_api::engine_validator_electionBid &to, JsonObject &from);
Status from_json(ton_api::engine_validator_fullNodeMaster &to, JsonObject &from);
Status from_json(ton_api::engine_validator_fullNodeSlave &to, JsonObject &from);
Status from_json(ton_api::validator_groupMember &to, JsonObject &from);
Status from_json(ton_api::engine_validator_jsonConfig &to, JsonObject &from);
Status from_json(ton_api::engine_validator_keyHash &to, JsonObject &from);
Status from_json(ton_api::engine_validator_oneStat &to, JsonObject &from);
Status from_json(ton_api::engine_validator_proposalVote &to, JsonObject &from);
Status from_json(ton_api::engine_validator_signature &to, JsonObject &from);
Status from_json(ton_api::engine_validator_stats &to, JsonObject &from);
Status from_json(ton_api::engine_validator_success &to, JsonObject &from);
Status from_json(ton_api::engine_validator_time &to, JsonObject &from);
Status from_json(ton_api::fec_raptorQ &to, JsonObject &from);
Status from_json(ton_api::fec_roundRobin &to, JsonObject &from);
Status from_json(ton_api::fec_online &to, JsonObject &from);
Status from_json(ton_api::http_header &to, JsonObject &from);
Status from_json(ton_api::http_payloadPart &to, JsonObject &from);
Status from_json(ton_api::http_response &to, JsonObject &from);
Status from_json(ton_api::http_server_config &to, JsonObject &from);
Status from_json(ton_api::http_server_dnsEntry &to, JsonObject &from);
Status from_json(ton_api::http_server_host &to, JsonObject &from);
Status from_json(ton_api::id_config_local &to, JsonObject &from);
Status from_json(ton_api::liteclient_config_global &to, JsonObject &from);
Status from_json(ton_api::liteserver_desc &to, JsonObject &from);
Status from_json(ton_api::liteserver_config_local &to, JsonObject &from);
Status from_json(ton_api::liteserver_config_random_local &to, JsonObject &from);
Status from_json(ton_api::overlay_fec_received &to, JsonObject &from);
Status from_json(ton_api::overlay_fec_completed &to, JsonObject &from);
Status from_json(ton_api::overlay_unicast &to, JsonObject &from);
Status from_json(ton_api::overlay_broadcast &to, JsonObject &from);
Status from_json(ton_api::overlay_broadcastFec &to, JsonObject &from);
Status from_json(ton_api::overlay_broadcastFecShort &to, JsonObject &from);
Status from_json(ton_api::overlay_broadcastNotFound &to, JsonObject &from);
Status from_json(ton_api::overlay_broadcastList &to, JsonObject &from);
Status from_json(ton_api::overlay_certificate &to, JsonObject &from);
Status from_json(ton_api::overlay_emptyCertificate &to, JsonObject &from);
Status from_json(ton_api::overlay_certificateId &to, JsonObject &from);
Status from_json(ton_api::overlay_message &to, JsonObject &from);
Status from_json(ton_api::overlay_node &to, JsonObject &from);
Status from_json(ton_api::overlay_nodes &to, JsonObject &from);
Status from_json(ton_api::overlay_broadcast_id &to, JsonObject &from);
Status from_json(ton_api::overlay_broadcast_toSign &to, JsonObject &from);
Status from_json(ton_api::overlay_broadcastFec_id &to, JsonObject &from);
Status from_json(ton_api::overlay_broadcastFec_partId &to, JsonObject &from);
Status from_json(ton_api::overlay_db_key_nodes &to, JsonObject &from);
Status from_json(ton_api::overlay_db_nodes &to, JsonObject &from);
Status from_json(ton_api::overlay_node_toSign &to, JsonObject &from);
Status from_json(ton_api::rldp_message &to, JsonObject &from);
Status from_json(ton_api::rldp_query &to, JsonObject &from);
Status from_json(ton_api::rldp_answer &to, JsonObject &from);
Status from_json(ton_api::rldp_messagePart &to, JsonObject &from);
Status from_json(ton_api::rldp_confirm &to, JsonObject &from);
Status from_json(ton_api::rldp_complete &to, JsonObject &from);
Status from_json(ton_api::rldp2_messagePart &to, JsonObject &from);
Status from_json(ton_api::rldp2_confirm &to, JsonObject &from);
Status from_json(ton_api::rldp2_complete &to, JsonObject &from);
Status from_json(ton_api::storage_piece &to, JsonObject &from);
Status from_json(ton_api::storage_pong &to, JsonObject &from);
Status from_json(ton_api::storage_state &to, JsonObject &from);
Status from_json(ton_api::storage_updateInit &to, JsonObject &from);
Status from_json(ton_api::storage_updateHavePieces &to, JsonObject &from);
Status from_json(ton_api::storage_updateState &to, JsonObject &from);
Status from_json(ton_api::tcp_authentificate &to, JsonObject &from);
Status from_json(ton_api::tcp_authentificationNonce &to, JsonObject &from);
Status from_json(ton_api::tcp_authentificationComplete &to, JsonObject &from);
Status from_json(ton_api::tcp_pong &to, JsonObject &from);
Status from_json(ton_api::ton_blockId &to, JsonObject &from);
Status from_json(ton_api::ton_blockIdApprove &to, JsonObject &from);
Status from_json(ton_api::tonNode_archiveNotFound &to, JsonObject &from);
Status from_json(ton_api::tonNode_archiveInfo &to, JsonObject &from);
Status from_json(ton_api::tonNode_blockDescriptionEmpty &to, JsonObject &from);
Status from_json(ton_api::tonNode_blockDescription &to, JsonObject &from);
Status from_json(ton_api::tonNode_blockId &to, JsonObject &from);
Status from_json(ton_api::tonNode_blockIdExt &to, JsonObject &from);
Status from_json(ton_api::tonNode_blockSignature &to, JsonObject &from);
Status from_json(ton_api::tonNode_blocksDescription &to, JsonObject &from);
Status from_json(ton_api::tonNode_blockBroadcast &to, JsonObject &from);
Status from_json(ton_api::tonNode_ihrMessageBroadcast &to, JsonObject &from);
Status from_json(ton_api::tonNode_externalMessageBroadcast &to, JsonObject &from);
Status from_json(ton_api::tonNode_newShardBlockBroadcast &to, JsonObject &from);
Status from_json(ton_api::tonNode_capabilities &to, JsonObject &from);
Status from_json(ton_api::tonNode_data &to, JsonObject &from);
Status from_json(ton_api::tonNode_dataFull &to, JsonObject &from);
Status from_json(ton_api::tonNode_dataFullEmpty &to, JsonObject &from);
Status from_json(ton_api::tonNode_dataList &to, JsonObject &from);
Status from_json(ton_api::tonNode_externalMessage &to, JsonObject &from);
Status from_json(ton_api::tonNode_ihrMessage &to, JsonObject &from);
Status from_json(ton_api::tonNode_keyBlocks &to, JsonObject &from);
Status from_json(ton_api::tonNode_newShardBlock &to, JsonObject &from);
Status from_json(ton_api::tonNode_prepared &to, JsonObject &from);
Status from_json(ton_api::tonNode_notFound &to, JsonObject &from);
Status from_json(ton_api::tonNode_preparedProofEmpty &to, JsonObject &from);
Status from_json(ton_api::tonNode_preparedProof &to, JsonObject &from);
Status from_json(ton_api::tonNode_preparedProofLink &to, JsonObject &from);
Status from_json(ton_api::tonNode_preparedState &to, JsonObject &from);
Status from_json(ton_api::tonNode_notFoundState &to, JsonObject &from);
Status from_json(ton_api::tonNode_sessionId &to, JsonObject &from);
Status from_json(ton_api::tonNode_shardPublicOverlayId &to, JsonObject &from);
Status from_json(ton_api::tonNode_success &to, JsonObject &from);
Status from_json(ton_api::tonNode_zeroStateIdExt &to, JsonObject &from);
Status from_json(ton_api::validator_group &to, JsonObject &from);
Status from_json(ton_api::validator_groupEx &to, JsonObject &from);
Status from_json(ton_api::validator_groupNew &to, JsonObject &from);
Status from_json(ton_api::validator_config_global &to, JsonObject &from);
Status from_json(ton_api::validator_config_local &to, JsonObject &from);
Status from_json(ton_api::validator_config_random_local &to, JsonObject &from);
Status from_json(ton_api::validatorSession_blockUpdate &to, JsonObject &from);
Status from_json(ton_api::validatorSession_candidate &to, JsonObject &from);
Status from_json(ton_api::validatorSession_candidateId &to, JsonObject &from);
Status from_json(ton_api::validatorSession_config &to, JsonObject &from);
Status from_json(ton_api::validatorSession_configVersioned &to, JsonObject &from);
Status from_json(ton_api::validatorSession_configNew &to, JsonObject &from);
Status from_json(ton_api::validatorSession_message_startSession &to, JsonObject &from);
Status from_json(ton_api::validatorSession_message_finishSession &to, JsonObject &from);
Status from_json(ton_api::validatorSession_pong &to, JsonObject &from);
Status from_json(ton_api::validatorSession_round_id &to, JsonObject &from);
Status from_json(ton_api::validatorSession_message_submittedBlock &to, JsonObject &from);
Status from_json(ton_api::validatorSession_message_approvedBlock &to, JsonObject &from);
Status from_json(ton_api::validatorSession_message_rejectedBlock &to, JsonObject &from);
Status from_json(ton_api::validatorSession_message_commit &to, JsonObject &from);
Status from_json(ton_api::validatorSession_message_vote &to, JsonObject &from);
Status from_json(ton_api::validatorSession_message_voteFor &to, JsonObject &from);
Status from_json(ton_api::validatorSession_message_precommit &to, JsonObject &from);
Status from_json(ton_api::validatorSession_message_empty &to, JsonObject &from);
Status from_json(ton_api::validatorSession_candidate_id &to, JsonObject &from);
Status from_json(ton_api::adnl_ping &to, JsonObject &from);
Status from_json(ton_api::catchain_getBlock &to, JsonObject &from);
Status from_json(ton_api::catchain_getBlockHistory &to, JsonObject &from);
Status from_json(ton_api::catchain_getBlocks &to, JsonObject &from);
Status from_json(ton_api::catchain_getDifference &to, JsonObject &from);
Status from_json(ton_api::dht_findNode &to, JsonObject &from);
Status from_json(ton_api::dht_findValue &to, JsonObject &from);
Status from_json(ton_api::dht_getSignedAddressList &to, JsonObject &from);
Status from_json(ton_api::dht_ping &to, JsonObject &from);
Status from_json(ton_api::dht_query &to, JsonObject &from);
Status from_json(ton_api::dht_store &to, JsonObject &from);
Status from_json(ton_api::engine_validator_addAdnlId &to, JsonObject &from);
Status from_json(ton_api::engine_validator_addControlInterface &to, JsonObject &from);
Status from_json(ton_api::engine_validator_addControlProcess &to, JsonObject &from);
Status from_json(ton_api::engine_validator_addDhtId &to, JsonObject &from);
Status from_json(ton_api::engine_validator_addListeningPort &to, JsonObject &from);
Status from_json(ton_api::engine_validator_addLiteserver &to, JsonObject &from);
Status from_json(ton_api::engine_validator_addProxy &to, JsonObject &from);
Status from_json(ton_api::engine_validator_addValidatorAdnlAddress &to, JsonObject &from);
Status from_json(ton_api::engine_validator_addValidatorPermanentKey &to, JsonObject &from);
Status from_json(ton_api::engine_validator_addValidatorTempKey &to, JsonObject &from);
Status from_json(ton_api::engine_validator_changeFullNodeAdnlAddress &to, JsonObject &from);
Status from_json(ton_api::engine_validator_checkDhtServers &to, JsonObject &from);
Status from_json(ton_api::engine_validator_controlQuery &to, JsonObject &from);
Status from_json(ton_api::engine_validator_createComplaintVote &to, JsonObject &from);
Status from_json(ton_api::engine_validator_createElectionBid &to, JsonObject &from);
Status from_json(ton_api::engine_validator_createProposalVote &to, JsonObject &from);
Status from_json(ton_api::engine_validator_delAdnlId &to, JsonObject &from);
Status from_json(ton_api::engine_validator_delDhtId &to, JsonObject &from);
Status from_json(ton_api::engine_validator_delListeningPort &to, JsonObject &from);
Status from_json(ton_api::engine_validator_delProxy &to, JsonObject &from);
Status from_json(ton_api::engine_validator_delValidatorAdnlAddress &to, JsonObject &from);
Status from_json(ton_api::engine_validator_delValidatorPermanentKey &to, JsonObject &from);
Status from_json(ton_api::engine_validator_delValidatorTempKey &to, JsonObject &from);
Status from_json(ton_api::engine_validator_exportPrivateKey &to, JsonObject &from);
Status from_json(ton_api::engine_validator_exportPublicKey &to, JsonObject &from);
Status from_json(ton_api::engine_validator_generateKeyPair &to, JsonObject &from);
Status from_json(ton_api::engine_validator_getConfig &to, JsonObject &from);
Status from_json(ton_api::engine_validator_getStats &to, JsonObject &from);
Status from_json(ton_api::engine_validator_getTime &to, JsonObject &from);
Status from_json(ton_api::engine_validator_importPrivateKey &to, JsonObject &from);
Status from_json(ton_api::engine_validator_setVerbosity &to, JsonObject &from);
Status from_json(ton_api::engine_validator_sign &to, JsonObject &from);
Status from_json(ton_api::getTestObject &to, JsonObject &from);
Status from_json(ton_api::http_getNextPayloadPart &to, JsonObject &from);
Status from_json(ton_api::http_request &to, JsonObject &from);
Status from_json(ton_api::overlay_getBroadcast &to, JsonObject &from);
Status from_json(ton_api::overlay_getBroadcastList &to, JsonObject &from);
Status from_json(ton_api::overlay_getRandomPeers &to, JsonObject &from);
Status from_json(ton_api::overlay_query &to, JsonObject &from);
Status from_json(ton_api::storage_addUpdate &to, JsonObject &from);
Status from_json(ton_api::storage_getPiece &to, JsonObject &from);
Status from_json(ton_api::storage_ping &to, JsonObject &from);
Status from_json(ton_api::storage_queryPrefix &to, JsonObject &from);
Status from_json(ton_api::tcp_ping &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadBlock &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadBlockFull &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadBlockProof &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadBlockProofLink &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadBlockProofLinks &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadBlockProofs &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadBlocks &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadKeyBlockProof &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadKeyBlockProofLink &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadKeyBlockProofLinks &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadKeyBlockProofs &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadNextBlockFull &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadPersistentState &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadPersistentStateSlice &to, JsonObject &from);
Status from_json(ton_api::tonNode_downloadZeroState &to, JsonObject &from);
Status from_json(ton_api::tonNode_getArchiveInfo &to, JsonObject &from);
Status from_json(ton_api::tonNode_getArchiveSlice &to, JsonObject &from);
Status from_json(ton_api::tonNode_getCapabilities &to, JsonObject &from);
Status from_json(ton_api::tonNode_getNextBlockDescription &to, JsonObject &from);
Status from_json(ton_api::tonNode_getNextBlocksDescription &to, JsonObject &from);
Status from_json(ton_api::tonNode_getNextKeyBlockIds &to, JsonObject &from);
Status from_json(ton_api::tonNode_getPrevBlocksDescription &to, JsonObject &from);
Status from_json(ton_api::tonNode_prepareBlock &to, JsonObject &from);
Status from_json(ton_api::tonNode_prepareBlockProof &to, JsonObject &from);
Status from_json(ton_api::tonNode_prepareBlockProofs &to, JsonObject &from);
Status from_json(ton_api::tonNode_prepareBlocks &to, JsonObject &from);
Status from_json(ton_api::tonNode_prepareKeyBlockProof &to, JsonObject &from);
Status from_json(ton_api::tonNode_prepareKeyBlockProofs &to, JsonObject &from);
Status from_json(ton_api::tonNode_preparePersistentState &to, JsonObject &from);
Status from_json(ton_api::tonNode_prepareZeroState &to, JsonObject &from);
Status from_json(ton_api::tonNode_query &to, JsonObject &from);
Status from_json(ton_api::tonNode_slave_sendExtMessage &to, JsonObject &from);
Status from_json(ton_api::validatorSession_downloadCandidate &to, JsonObject &from);
Status from_json(ton_api::validatorSession_ping &to, JsonObject &from);
void to_json(JsonValueScope &jv, const ton_api::Hashable &object);
void to_json(JsonValueScope &jv, const ton_api::hashable_bool &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_int32 &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_int64 &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_int256 &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_bytes &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_pair &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_vector &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_validatorSessionOldRound &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_validatorSessionRoundAttempt &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_validatorSessionRound &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_blockSignature &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_sentBlock &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_sentBlockEmpty &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_vote &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_blockCandidate &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_blockVoteCandidate &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_blockCandidateAttempt &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_cntVector &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_cntSortedVector &object);

void to_json(JsonValueScope &jv, const ton_api::hashable_validatorSession &object);

void to_json(JsonValueScope &jv, const ton_api::storage_ok &object);

void to_json(JsonValueScope &jv, const ton_api::PrivateKey &object);
void to_json(JsonValueScope &jv, const ton_api::pk_unenc &object);

void to_json(JsonValueScope &jv, const ton_api::pk_ed25519 &object);

void to_json(JsonValueScope &jv, const ton_api::pk_aes &object);

void to_json(JsonValueScope &jv, const ton_api::pk_overlay &object);

void to_json(JsonValueScope &jv, const ton_api::PublicKey &object);
void to_json(JsonValueScope &jv, const ton_api::pub_unenc &object);

void to_json(JsonValueScope &jv, const ton_api::pub_ed25519 &object);

void to_json(JsonValueScope &jv, const ton_api::pub_aes &object);

void to_json(JsonValueScope &jv, const ton_api::pub_overlay &object);

void to_json(JsonValueScope &jv, const ton_api::TestObject &object);
void to_json(JsonValueScope &jv, const ton_api::testObject &object);

void to_json(JsonValueScope &jv, const ton_api::testString &object);

void to_json(JsonValueScope &jv, const ton_api::testInt &object);

void to_json(JsonValueScope &jv, const ton_api::testVectorBytes &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_Address &object);
void to_json(JsonValueScope &jv, const ton_api::adnl_address_udp &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_address_udp6 &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_address_tunnel &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_addressList &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_Message &object);
void to_json(JsonValueScope &jv, const ton_api::adnl_message_createChannel &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_message_confirmChannel &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_message_custom &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_message_nop &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_message_reinit &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_message_query &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_message_answer &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_message_part &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_node &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_nodes &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_packetContents &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_pong &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_Proxy &object);
void to_json(JsonValueScope &jv, const ton_api::adnl_proxy_none &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_proxy_fast &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_ProxyControlPacket &object);
void to_json(JsonValueScope &jv, const ton_api::adnl_proxyControlPacketPing &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_proxyControlPacketPong &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_proxyControlPacketRegister &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_proxyPacketHeader &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_proxyToFastHash &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_proxyToFast &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_tunnelPacketContents &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_config_global &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_db_node_key &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_db_node_value &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_id_short &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_block &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_BlockResult &object);
void to_json(JsonValueScope &jv, const ton_api::catchain_blockNotFound &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_blockResult &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_blocks &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_Difference &object);
void to_json(JsonValueScope &jv, const ton_api::catchain_difference &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_differenceFork &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_firstblock &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_sent &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_blockUpdate &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_block_data &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_block_dep &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_block_id &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_block_inner_Data &object);
void to_json(JsonValueScope &jv, const ton_api::catchain_block_data_badBlock &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_block_data_fork &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_block_data_nop &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_block_data_vector &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_config_global &object);

void to_json(JsonValueScope &jv, const ton_api::config_global &object);

void to_json(JsonValueScope &jv, const ton_api::config_local &object);

void to_json(JsonValueScope &jv, const ton_api::control_config_local &object);

void to_json(JsonValueScope &jv, const ton_api::db_candidate &object);

void to_json(JsonValueScope &jv, const ton_api::db_block_Info &object);
void to_json(JsonValueScope &jv, const ton_api::db_block_info &object);

void to_json(JsonValueScope &jv, const ton_api::db_block_packedInfo &object);

void to_json(JsonValueScope &jv, const ton_api::db_block_archivedInfo &object);

void to_json(JsonValueScope &jv, const ton_api::db_blockdb_Key &object);
void to_json(JsonValueScope &jv, const ton_api::db_blockdb_key_lru &object);

void to_json(JsonValueScope &jv, const ton_api::db_blockdb_key_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_blockdb_lru &object);

void to_json(JsonValueScope &jv, const ton_api::db_blockdb_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_candidate_id &object);

void to_json(JsonValueScope &jv, const ton_api::db_celldb_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_celldb_key_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_filedb_Key &object);
void to_json(JsonValueScope &jv, const ton_api::db_filedb_key_empty &object);

void to_json(JsonValueScope &jv, const ton_api::db_filedb_key_blockFile &object);

void to_json(JsonValueScope &jv, const ton_api::db_filedb_key_zeroStateFile &object);

void to_json(JsonValueScope &jv, const ton_api::db_filedb_key_persistentStateFile &object);

void to_json(JsonValueScope &jv, const ton_api::db_filedb_key_proof &object);

void to_json(JsonValueScope &jv, const ton_api::db_filedb_key_proofLink &object);

void to_json(JsonValueScope &jv, const ton_api::db_filedb_key_signatures &object);

void to_json(JsonValueScope &jv, const ton_api::db_filedb_key_candidate &object);

void to_json(JsonValueScope &jv, const ton_api::db_filedb_key_blockInfo &object);

void to_json(JsonValueScope &jv, const ton_api::db_filedb_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_files_Key &object);
void to_json(JsonValueScope &jv, const ton_api::db_files_index_key &object);

void to_json(JsonValueScope &jv, const ton_api::db_files_package_key &object);

void to_json(JsonValueScope &jv, const ton_api::db_files_index_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_files_package_firstBlock &object);

void to_json(JsonValueScope &jv, const ton_api::db_files_package_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_lt_Key &object);
void to_json(JsonValueScope &jv, const ton_api::db_lt_el_key &object);

void to_json(JsonValueScope &jv, const ton_api::db_lt_desc_key &object);

void to_json(JsonValueScope &jv, const ton_api::db_lt_shard_key &object);

void to_json(JsonValueScope &jv, const ton_api::db_lt_status_key &object);

void to_json(JsonValueScope &jv, const ton_api::db_lt_desc_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_lt_el_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_lt_shard_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_lt_status_value &object);

void to_json(JsonValueScope &jv, const ton_api::db_root_config &object);

void to_json(JsonValueScope &jv, const ton_api::db_root_dbDescription &object);

void to_json(JsonValueScope &jv, const ton_api::db_root_Key &object);
void to_json(JsonValueScope &jv, const ton_api::db_root_key_cellDb &object);

void to_json(JsonValueScope &jv, const ton_api::db_root_key_blockDb &object);

void to_json(JsonValueScope &jv, const ton_api::db_root_key_config &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_asyncSerializer &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_dbVersion &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_destroyedSessions &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_gcBlockId &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_hardforks &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_initBlockId &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_Key &object);
void to_json(JsonValueScope &jv, const ton_api::db_state_key_destroyedSessions &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_key_initBlockId &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_key_gcBlockId &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_key_shardClient &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_key_asyncSerializer &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_key_hardforks &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_key_dbVersion &object);

void to_json(JsonValueScope &jv, const ton_api::db_state_shardClient &object);

void to_json(JsonValueScope &jv, const ton_api::dht_key &object);

void to_json(JsonValueScope &jv, const ton_api::dht_keyDescription &object);

void to_json(JsonValueScope &jv, const ton_api::dht_message &object);

void to_json(JsonValueScope &jv, const ton_api::dht_node &object);

void to_json(JsonValueScope &jv, const ton_api::dht_nodes &object);

void to_json(JsonValueScope &jv, const ton_api::dht_pong &object);

void to_json(JsonValueScope &jv, const ton_api::dht_stored &object);

void to_json(JsonValueScope &jv, const ton_api::dht_UpdateRule &object);
void to_json(JsonValueScope &jv, const ton_api::dht_updateRule_signature &object);

void to_json(JsonValueScope &jv, const ton_api::dht_updateRule_anybody &object);

void to_json(JsonValueScope &jv, const ton_api::dht_updateRule_overlayNodes &object);

void to_json(JsonValueScope &jv, const ton_api::dht_value &object);

void to_json(JsonValueScope &jv, const ton_api::dht_ValueResult &object);
void to_json(JsonValueScope &jv, const ton_api::dht_valueNotFound &object);

void to_json(JsonValueScope &jv, const ton_api::dht_valueFound &object);

void to_json(JsonValueScope &jv, const ton_api::dht_config_global &object);

void to_json(JsonValueScope &jv, const ton_api::dht_config_Local &object);
void to_json(JsonValueScope &jv, const ton_api::dht_config_local &object);

void to_json(JsonValueScope &jv, const ton_api::dht_config_random_local &object);

void to_json(JsonValueScope &jv, const ton_api::dht_db_bucket &object);

void to_json(JsonValueScope &jv, const ton_api::dht_db_key_bucket &object);

void to_json(JsonValueScope &jv, const ton_api::dummyworkchain0_config_global &object);

void to_json(JsonValueScope &jv, const ton_api::engine_Addr &object);
void to_json(JsonValueScope &jv, const ton_api::engine_addr &object);

void to_json(JsonValueScope &jv, const ton_api::engine_addrProxy &object);

void to_json(JsonValueScope &jv, const ton_api::engine_adnl &object);

void to_json(JsonValueScope &jv, const ton_api::engine_controlInterface &object);

void to_json(JsonValueScope &jv, const ton_api::engine_controlProcess &object);

void to_json(JsonValueScope &jv, const ton_api::engine_dht &object);

void to_json(JsonValueScope &jv, const ton_api::engine_gc &object);

void to_json(JsonValueScope &jv, const ton_api::engine_liteServer &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validatorAdnlAddress &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validatorTempKey &object);

void to_json(JsonValueScope &jv, const ton_api::engine_adnlProxy_config &object);

void to_json(JsonValueScope &jv, const ton_api::engine_adnlProxy_port &object);

void to_json(JsonValueScope &jv, const ton_api::engine_dht_config &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_config &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_controlQueryError &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_dhtServerStatus &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_dhtServersStatus &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_electionBid &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_fullNodeMaster &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_fullNodeSlave &object);

void to_json(JsonValueScope &jv, const ton_api::validator_groupMember &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_jsonConfig &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_keyHash &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_oneStat &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_proposalVote &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_signature &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_stats &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_success &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_time &object);

void to_json(JsonValueScope &jv, const ton_api::fec_Type &object);
void to_json(JsonValueScope &jv, const ton_api::fec_raptorQ &object);

void to_json(JsonValueScope &jv, const ton_api::fec_roundRobin &object);

void to_json(JsonValueScope &jv, const ton_api::fec_online &object);

void to_json(JsonValueScope &jv, const ton_api::http_header &object);

void to_json(JsonValueScope &jv, const ton_api::http_payloadPart &object);

void to_json(JsonValueScope &jv, const ton_api::http_response &object);

void to_json(JsonValueScope &jv, const ton_api::http_server_config &object);

void to_json(JsonValueScope &jv, const ton_api::http_server_dnsEntry &object);

void to_json(JsonValueScope &jv, const ton_api::http_server_host &object);

void to_json(JsonValueScope &jv, const ton_api::id_config_local &object);

void to_json(JsonValueScope &jv, const ton_api::liteclient_config_global &object);

void to_json(JsonValueScope &jv, const ton_api::liteserver_desc &object);

void to_json(JsonValueScope &jv, const ton_api::liteserver_config_Local &object);
void to_json(JsonValueScope &jv, const ton_api::liteserver_config_local &object);

void to_json(JsonValueScope &jv, const ton_api::liteserver_config_random_local &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_Broadcast &object);
void to_json(JsonValueScope &jv, const ton_api::overlay_fec_received &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_fec_completed &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_unicast &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_broadcast &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastFec &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastFecShort &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastNotFound &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastList &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_Certificate &object);
void to_json(JsonValueScope &jv, const ton_api::overlay_certificate &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_emptyCertificate &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_certificateId &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_message &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_node &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_nodes &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_broadcast_id &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_broadcast_toSign &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastFec_id &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastFec_partId &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_db_key_nodes &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_db_nodes &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_node_toSign &object);

void to_json(JsonValueScope &jv, const ton_api::rldp_Message &object);
void to_json(JsonValueScope &jv, const ton_api::rldp_message &object);

void to_json(JsonValueScope &jv, const ton_api::rldp_query &object);

void to_json(JsonValueScope &jv, const ton_api::rldp_answer &object);

void to_json(JsonValueScope &jv, const ton_api::rldp_MessagePart &object);
void to_json(JsonValueScope &jv, const ton_api::rldp_messagePart &object);

void to_json(JsonValueScope &jv, const ton_api::rldp_confirm &object);

void to_json(JsonValueScope &jv, const ton_api::rldp_complete &object);

void to_json(JsonValueScope &jv, const ton_api::rldp2_MessagePart &object);
void to_json(JsonValueScope &jv, const ton_api::rldp2_messagePart &object);

void to_json(JsonValueScope &jv, const ton_api::rldp2_confirm &object);

void to_json(JsonValueScope &jv, const ton_api::rldp2_complete &object);

void to_json(JsonValueScope &jv, const ton_api::storage_piece &object);

void to_json(JsonValueScope &jv, const ton_api::storage_pong &object);

void to_json(JsonValueScope &jv, const ton_api::storage_state &object);

void to_json(JsonValueScope &jv, const ton_api::storage_Update &object);
void to_json(JsonValueScope &jv, const ton_api::storage_updateInit &object);

void to_json(JsonValueScope &jv, const ton_api::storage_updateHavePieces &object);

void to_json(JsonValueScope &jv, const ton_api::storage_updateState &object);

void to_json(JsonValueScope &jv, const ton_api::tcp_Message &object);
void to_json(JsonValueScope &jv, const ton_api::tcp_authentificate &object);

void to_json(JsonValueScope &jv, const ton_api::tcp_authentificationNonce &object);

void to_json(JsonValueScope &jv, const ton_api::tcp_authentificationComplete &object);

void to_json(JsonValueScope &jv, const ton_api::tcp_pong &object);

void to_json(JsonValueScope &jv, const ton_api::ton_BlockId &object);
void to_json(JsonValueScope &jv, const ton_api::ton_blockId &object);

void to_json(JsonValueScope &jv, const ton_api::ton_blockIdApprove &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_ArchiveInfo &object);
void to_json(JsonValueScope &jv, const ton_api::tonNode_archiveNotFound &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_archiveInfo &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_BlockDescription &object);
void to_json(JsonValueScope &jv, const ton_api::tonNode_blockDescriptionEmpty &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_blockDescription &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_blockId &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_blockIdExt &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_blockSignature &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_blocksDescription &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_Broadcast &object);
void to_json(JsonValueScope &jv, const ton_api::tonNode_blockBroadcast &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_ihrMessageBroadcast &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_externalMessageBroadcast &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_newShardBlockBroadcast &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_capabilities &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_data &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_DataFull &object);
void to_json(JsonValueScope &jv, const ton_api::tonNode_dataFull &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_dataFullEmpty &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_dataList &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_externalMessage &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_ihrMessage &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_keyBlocks &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_newShardBlock &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_Prepared &object);
void to_json(JsonValueScope &jv, const ton_api::tonNode_prepared &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_notFound &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_PreparedProof &object);
void to_json(JsonValueScope &jv, const ton_api::tonNode_preparedProofEmpty &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_preparedProof &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_preparedProofLink &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_PreparedState &object);
void to_json(JsonValueScope &jv, const ton_api::tonNode_preparedState &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_notFoundState &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_sessionId &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_shardPublicOverlayId &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_success &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_zeroStateIdExt &object);

void to_json(JsonValueScope &jv, const ton_api::validator_Group &object);
void to_json(JsonValueScope &jv, const ton_api::validator_group &object);

void to_json(JsonValueScope &jv, const ton_api::validator_groupEx &object);

void to_json(JsonValueScope &jv, const ton_api::validator_groupNew &object);

void to_json(JsonValueScope &jv, const ton_api::validator_config_global &object);

void to_json(JsonValueScope &jv, const ton_api::validator_config_Local &object);
void to_json(JsonValueScope &jv, const ton_api::validator_config_local &object);

void to_json(JsonValueScope &jv, const ton_api::validator_config_random_local &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_blockUpdate &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_candidate &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_candidateId &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_Config &object);
void to_json(JsonValueScope &jv, const ton_api::validatorSession_config &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_configVersioned &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_configNew &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_Message &object);
void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_startSession &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_finishSession &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_pong &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_round_id &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_round_Message &object);
void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_submittedBlock &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_approvedBlock &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_rejectedBlock &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_commit &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_vote &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_voteFor &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_precommit &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_empty &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_candidate_id &object);

void to_json(JsonValueScope &jv, const ton_api::adnl_ping &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_getBlock &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_getBlockHistory &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_getBlocks &object);

void to_json(JsonValueScope &jv, const ton_api::catchain_getDifference &object);

void to_json(JsonValueScope &jv, const ton_api::dht_findNode &object);

void to_json(JsonValueScope &jv, const ton_api::dht_findValue &object);

void to_json(JsonValueScope &jv, const ton_api::dht_getSignedAddressList &object);

void to_json(JsonValueScope &jv, const ton_api::dht_ping &object);

void to_json(JsonValueScope &jv, const ton_api::dht_query &object);

void to_json(JsonValueScope &jv, const ton_api::dht_store &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_addAdnlId &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_addControlInterface &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_addControlProcess &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_addDhtId &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_addListeningPort &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_addLiteserver &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_addProxy &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_addValidatorAdnlAddress &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_addValidatorPermanentKey &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_addValidatorTempKey &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_changeFullNodeAdnlAddress &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_checkDhtServers &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_controlQuery &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_createComplaintVote &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_createElectionBid &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_createProposalVote &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_delAdnlId &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_delDhtId &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_delListeningPort &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_delProxy &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_delValidatorAdnlAddress &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_delValidatorPermanentKey &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_delValidatorTempKey &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_exportPrivateKey &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_exportPublicKey &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_generateKeyPair &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_getConfig &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_getStats &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_getTime &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_importPrivateKey &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_setVerbosity &object);

void to_json(JsonValueScope &jv, const ton_api::engine_validator_sign &object);

void to_json(JsonValueScope &jv, const ton_api::getTestObject &object);

void to_json(JsonValueScope &jv, const ton_api::http_getNextPayloadPart &object);

void to_json(JsonValueScope &jv, const ton_api::http_request &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_getBroadcast &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_getBroadcastList &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_getRandomPeers &object);

void to_json(JsonValueScope &jv, const ton_api::overlay_query &object);

void to_json(JsonValueScope &jv, const ton_api::storage_addUpdate &object);

void to_json(JsonValueScope &jv, const ton_api::storage_getPiece &object);

void to_json(JsonValueScope &jv, const ton_api::storage_ping &object);

void to_json(JsonValueScope &jv, const ton_api::storage_queryPrefix &object);

void to_json(JsonValueScope &jv, const ton_api::tcp_ping &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadBlock &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadBlockFull &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadBlockProof &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadBlockProofLink &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadBlockProofLinks &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadBlockProofs &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadBlocks &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadKeyBlockProof &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadKeyBlockProofLink &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadKeyBlockProofLinks &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadKeyBlockProofs &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadNextBlockFull &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadPersistentState &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadPersistentStateSlice &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadZeroState &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_getArchiveInfo &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_getArchiveSlice &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_getCapabilities &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_getNextBlockDescription &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_getNextBlocksDescription &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_getNextKeyBlockIds &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_getPrevBlocksDescription &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_prepareBlock &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_prepareBlockProof &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_prepareBlockProofs &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_prepareBlocks &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_prepareKeyBlockProof &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_prepareKeyBlockProofs &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_preparePersistentState &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_prepareZeroState &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_query &object);

void to_json(JsonValueScope &jv, const ton_api::tonNode_slave_sendExtMessage &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_downloadCandidate &object);

void to_json(JsonValueScope &jv, const ton_api::validatorSession_ping &object);

inline void to_json(JsonValueScope &jv, const ton::ton_api::Object &object) {
  ton::ton_api::downcast_call(const_cast<ton::ton_api::Object &>(object),[&jv](const auto &object) { to_json(jv, object); });
}
inline void to_json(JsonValueScope &jv, const ton::ton_api::Function &object) {
  ton::ton_api::downcast_call(const_cast<ton::ton_api::Function &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
}  // namespace ton_api
}  // namespace ton
