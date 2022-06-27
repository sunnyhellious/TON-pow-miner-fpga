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

    Copyright 2019-2020 Telegram Systems LLP
*/
#include "http/http-server.h"
#include "http/http-client.h"

#include "td/utils/port/signals.h"
#include "td/utils/OptionParser.h"
#include "td/utils/FileLog.h"
#include "td/utils/Random.h"
#include "td/utils/filesystem.h"
#include "td/utils/overloaded.h"

#include "auto/tl/ton_api_json.h"
#include "auto/tl/tonlib_api.hpp"

#include "td/actor/MultiPromise.h"

#include "common/errorcode.h"

#include "tonlib/tonlib/TonlibClient.h"

#include "adnl/adnl.h"
#include "rldp/rldp.h"
#include "dht/dht.h"

#include <algorithm>
#include <list>
#include <set>
#include "git.h"

#if TD_DARWIN || TD_LINUX
#include <unistd.h>
#endif

class RldpHttpProxy;

class HttpRemote : public td::actor::Actor {
 public:
  struct Query {
    std::unique_ptr<ton::http::HttpRequest> request;
    std::shared_ptr<ton::http::HttpPayload> payload;
    td::Timestamp timeout;
    td::Promise<std::pair<std::unique_ptr<ton::http::HttpResponse>, std::shared_ptr<ton::http::HttpPayload>>> promise;
  };
  HttpRemote(td::IPAddress addr) : addr_(addr) {
  }
  void start_up() override {
    class Cb : public ton::http::HttpClient::Callback {
     public:
      Cb(td::actor::ActorId<HttpRemote> id) : id_(id) {
      }
      void on_ready() override {
        td::actor::send_closure(id_, &HttpRemote::set_ready, true);
      }
      void on_stop_ready() override {
        td::actor::send_closure(id_, &HttpRemote::set_ready, false);
      }

     private:
      td::actor::ActorId<HttpRemote> id_;
    };
    client_ = ton::http::HttpClient::create_multi("", addr_, 1000, 100, std::make_shared<Cb>(actor_id(this)));
  }
  void set_ready(bool ready) {
    ready_ = ready;
  }
  void receive_request(
      std::unique_ptr<ton::http::HttpRequest> request, std::shared_ptr<ton::http::HttpPayload> payload,
      td::Promise<std::pair<std::unique_ptr<ton::http::HttpResponse>, std::shared_ptr<ton::http::HttpPayload>>>
          promise) {
    if (ready_) {
      bool keep = request->keep_alive();
      auto P = td::PromiseCreator::lambda(
          [promise = std::move(promise), keep](
              td::Result<std::pair<std::unique_ptr<ton::http::HttpResponse>, std::shared_ptr<ton::http::HttpPayload>>>
                  R) mutable {
            if (R.is_error()) {
              promise.set_error(R.move_as_error());
            } else {
              auto v = R.move_as_ok();
              v.first->set_keep_alive(keep);
              if (v.second->payload_type() != ton::http::HttpPayload::PayloadType::pt_empty &&
                  !v.first->found_content_length() && !v.first->found_transfer_encoding()) {
                v.first->add_header(ton::http::HttpHeader{"Transfer-Encoding", "Chunked"});
              }
              promise.set_value(std::move(v));
            }
          });
      td::actor::send_closure(client_, &ton::http::HttpClient::send_request, std::move(request), std::move(payload),
                              td::Timestamp::in(30.0), std::move(P));
    } else {
      ton::http::answer_error(ton::http::HttpStatusCode::status_bad_request, "", std::move(promise));
    }
  }

 private:
  td::IPAddress addr_;
  bool ready_ = false;
  td::actor::ActorOwn<ton::http::HttpClient> client_;
};

class HttpRldpPayloadReceiver : public td::actor::Actor {
 public:
  HttpRldpPayloadReceiver(std::shared_ptr<ton::http::HttpPayload> payload, td::Bits256 transfer_id,
                          ton::adnl::AdnlNodeIdShort src, ton::adnl::AdnlNodeIdShort local_id,
                          td::actor::ActorId<ton::adnl::Adnl> adnl, td::actor::ActorId<ton::rldp::Rldp> rldp)
      : payload_(std::move(payload)), id_(transfer_id), src_(src), local_id_(local_id), adnl_(adnl), rldp_(rldp) {
  }

  void start_up() override {
    class Cb : public ton::http::HttpPayload::Callback {
     public:
      Cb(td::actor::ActorId<HttpRldpPayloadReceiver> id) : self_id_(id) {
      }
      void run(size_t ready_bytes) override {
        if (!reached_ && ready_bytes < watermark_) {
          reached_ = true;
          td::actor::send_closure(self_id_, &HttpRldpPayloadReceiver::request_more_data);
        } else if (reached_ && ready_bytes >= watermark_) {
          reached_ = false;
        }
      }
      void completed() override {
      }

     private:
      size_t watermark_ = watermark();
      bool reached_ = false;
      td::actor::ActorId<HttpRldpPayloadReceiver> self_id_;
    };

    payload_->add_callback(std::make_unique<Cb>(actor_id(this)));
    request_more_data();
  }

  void request_more_data() {
    LOG(INFO) << "HttpPayloadReceiver: sent=" << sent_ << " completed=" << payload_->parse_completed()
              << " ready=" << payload_->ready_bytes() << " watermark=" << watermark();
    if (sent_ || payload_->parse_completed()) {
      return;
    }
    if (payload_->ready_bytes() >= watermark()) {
      return;
    }
    sent_ = true;
    auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<td::BufferSlice> R) {
      if (R.is_error()) {
        td::actor::send_closure(SelfId, &HttpRldpPayloadReceiver::abort_query, R.move_as_error());
      } else {
        td::actor::send_closure(SelfId, &HttpRldpPayloadReceiver::add_data, R.move_as_ok());
      }
    });

    auto f = ton::create_serialize_tl_object<ton::ton_api::http_getNextPayloadPart>(
        id_, seqno_++, static_cast<td::int32>(chunk_size()));
    td::actor::send_closure(rldp_, &ton::rldp::Rldp::send_query_ex, local_id_, src_, "payload part", std::move(P),
                            td::Timestamp::in(15.0), std::move(f), 2 * chunk_size() + 1024);
  }

  void add_data(td::BufferSlice data) {
    LOG(INFO) << "HttpPayloadReceiver: received answer (size " << data.size() << ")";
    auto F = ton::fetch_tl_object<ton::ton_api::http_payloadPart>(std::move(data), true);
    if (F.is_error()) {
      abort_query(F.move_as_error());
      return;
    }
    auto f = F.move_as_ok();
    LOG(INFO) << "HttpPayloadReceiver: received answer datasize=" << f->data_.size()
              << " trailers_cnt=" << f->trailer_.size() << " last=" << f->last_;
    if (f->data_.size() != 0) {
      payload_->add_chunk(std::move(f->data_));
    }
    for (auto &x : f->trailer_) {
      ton::http::HttpHeader h{x->name_, x->value_};
      auto S = h.basic_check();
      if (S.is_error()) {
        abort_query(S.move_as_error());
        return;
      }
      payload_->add_trailer(std::move(h));
    }
    sent_ = false;
    if (f->last_) {
      payload_->complete_parse();
      LOG(INFO) << "received HTTP payload";
      stop();
    } else {
      if (payload_->ready_bytes() < watermark()) {
        request_more_data();
      }
    }
  }

  void abort_query(td::Status error) {
    LOG(INFO) << "failed to receive HTTP payload: " << error;
    if (payload_) {
      payload_->set_error();
    }
    stop();
  }

 private:
  static constexpr size_t watermark() {
    return 1 << 15;
  }
  static constexpr size_t chunk_size() {
    return 1 << 17;
  }

  std::shared_ptr<ton::http::HttpPayload> payload_;

  td::Bits256 id_;

  ton::adnl::AdnlNodeIdShort src_;
  ton::adnl::AdnlNodeIdShort local_id_;
  td::actor::ActorId<ton::adnl::Adnl> adnl_;
  td::actor::ActorId<ton::rldp::Rldp> rldp_;

  bool sent_ = false;
  td::int32 seqno_ = 0;
};

class HttpRldpPayloadSender : public td::actor::Actor {
 public:
  HttpRldpPayloadSender(std::shared_ptr<ton::http::HttpPayload> payload, td::Bits256 transfer_id,
                        ton::adnl::AdnlNodeIdShort local_id, td::actor::ActorId<ton::adnl::Adnl> adnl,
                        td::actor::ActorId<ton::rldp::Rldp> rldp)
      : payload_(std::move(payload)), id_(transfer_id), local_id_(local_id), adnl_(adnl), rldp_(rldp) {
  }

  std::string generate_prefix() const {
    std::string x(static_cast<size_t>(36), '\0');
    auto S = td::MutableSlice{x};
    CHECK(S.size() == 36);

    auto id = ton::ton_api::http_getNextPayloadPart::ID;
    S.copy_from(td::Slice(reinterpret_cast<const td::uint8 *>(&id), 4));
    S.remove_prefix(4);
    S.copy_from(id_.as_slice());
    return x;
  }

  void start_up() override {
    class AdnlCb : public ton::adnl::Adnl::Callback {
     public:
      AdnlCb(td::actor::ActorId<HttpRldpPayloadSender> id) : self_id_(id) {
      }
      void receive_message(ton::adnl::AdnlNodeIdShort src, ton::adnl::AdnlNodeIdShort dst,
                           td::BufferSlice data) override {
        LOG(INFO) << "http payload sender: dropping message";
      }
      void receive_query(ton::adnl::AdnlNodeIdShort src, ton::adnl::AdnlNodeIdShort dst, td::BufferSlice data,
                         td::Promise<td::BufferSlice> promise) override {
        td::actor::send_closure(self_id_, &HttpRldpPayloadSender::receive_query, std::move(data), std::move(promise));
      }

     private:
      td::actor::ActorId<HttpRldpPayloadSender> self_id_;
    };
    td::actor::send_closure(adnl_, &ton::adnl::Adnl::subscribe, local_id_, generate_prefix(),
                            std::make_unique<AdnlCb>(actor_id(this)));

    class Cb : public ton::http::HttpPayload::Callback {
     public:
      Cb(td::actor::ActorId<HttpRldpPayloadSender> id) : self_id_(id) {
      }
      void run(size_t ready_bytes) override {
        if (!reached_ && ready_bytes >= watermark_) {
          reached_ = true;
          td::actor::send_closure(self_id_, &HttpRldpPayloadSender::try_answer_query);
        } else if (reached_ && ready_bytes < watermark_) {
          reached_ = false;
        }
      }
      void completed() override {
        td::actor::send_closure(self_id_, &HttpRldpPayloadSender::try_answer_query);
      }

     private:
      size_t watermark_ = ton::http::HttpRequest::low_watermark();
      bool reached_ = false;
      td::actor::ActorId<HttpRldpPayloadSender> self_id_;
    };

    payload_->add_callback(std::make_unique<Cb>(actor_id(this)));

    alarm_timestamp() = td::Timestamp::in(10.0);
  }

  void try_answer_query() {
    if (!cur_query_promise_) {
      return;
    }
    if (payload_->is_error()) {
      return;
    }
    if (payload_->parse_completed() || payload_->ready_bytes() >= ton::http::HttpRequest::low_watermark()) {
      answer_query();
    }
  }

  void send_data(ton::tl_object_ptr<ton::ton_api::http_getNextPayloadPart> query,
                 td::Promise<td::BufferSlice> promise) {
    CHECK(query->id_ == id_);
    if (query->seqno_ != seqno_) {
      LOG(INFO) << "seqno mismatch. closing http transfer";
      stop();
      return;
    }

    if (cur_query_promise_) {
      LOG(INFO) << "duplicate http query. closing http transfer";
      stop();
      return;
    }

    cur_query_size_ = query->max_chunk_size_;
    if (cur_query_size_ > watermark()) {
      cur_query_size_ = watermark();
    }
    cur_query_promise_ = std::move(promise);

    LOG(INFO) << "received request. size=" << cur_query_size_ << " parse_completed=" << payload_->parse_completed()
              << " ready_bytes=" << payload_->ready_bytes();

    if (payload_->parse_completed() || payload_->ready_bytes() >= ton::http::HttpRequest::low_watermark()) {
      answer_query();
      return;
    }

    alarm_timestamp() = td::Timestamp::in(10.0);
  }

  void receive_query(td::BufferSlice data, td::Promise<td::BufferSlice> promise) {
    auto F = ton::fetch_tl_object<ton::ton_api::http_getNextPayloadPart>(std::move(data), true);
    if (F.is_error()) {
      LOG(INFO) << "failed to parse query: " << F.move_as_error();
      return;
    }
    send_data(F.move_as_ok(), std::move(promise));
  }

  void alarm() override {
    if (cur_query_promise_) {
      LOG(INFO) << "timeout on inbound connection. closing http transfer";
    } else {
      LOG(INFO) << "timeout on RLDP connection. closing http transfer";
    }
    stop();
  }

  void answer_query() {
    cur_query_promise_.set_value(ton::serialize_tl_object(payload_->store_tl(cur_query_size_), true));
    if (payload_->written()) {
      LOG(INFO) << "sent HTTP payload";
      stop();
    }
    seqno_++;

    alarm_timestamp() = td::Timestamp::in(30.0);
  }

  void abort_query(td::Status error) {
    LOG(INFO) << error;
    stop();
  }

  void tear_down() override {
    td::actor::send_closure(adnl_, &ton::adnl::Adnl::unsubscribe, local_id_, generate_prefix());
  }

 private:
  static constexpr size_t watermark() {
    return 1 << 15;
  }

  std::shared_ptr<ton::http::HttpPayload> payload_;

  td::Bits256 id_;

  bool sent_ = false;
  td::int32 seqno_ = 0;

  ton::adnl::AdnlNodeIdShort local_id_;
  td::actor::ActorId<ton::adnl::Adnl> adnl_;
  td::actor::ActorId<ton::rldp::Rldp> rldp_;

  size_t cur_query_size_;
  td::Promise<td::BufferSlice> cur_query_promise_;
};

class RldpHttpProxy;

class TcpToRldpRequestSender : public td::actor::Actor {
 public:
  TcpToRldpRequestSender(
      ton::adnl::AdnlNodeIdShort local_id, std::string host, std::unique_ptr<ton::http::HttpRequest> request,
      std::shared_ptr<ton::http::HttpPayload> request_payload,
      td::Promise<std::pair<std::unique_ptr<ton::http::HttpResponse>, std::shared_ptr<ton::http::HttpPayload>>> promise,
      td::actor::ActorId<ton::adnl::Adnl> adnl, td::actor::ActorId<ton::dht::Dht> dht,
      td::actor::ActorId<ton::rldp::Rldp> rldp, td::actor::ActorId<RldpHttpProxy> proxy)
      : local_id_(local_id)
      , host_(std::move(host))
      , request_(std::move(request))
      , request_payload_(std::move(request_payload))
      , promise_(std::move(promise))
      , adnl_(adnl)
      , dht_(dht)
      , rldp_(rldp)
      , proxy_(proxy) {
  }
  void start_up() override {
    resolve();
  }

  void resolve();

  void resolved(ton::adnl::AdnlNodeIdShort id) {
    dst_ = id;
    td::Random::secure_bytes(id_.as_slice());

    auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<td::BufferSlice> R) {
      if (R.is_error()) {
        td::actor::send_closure(SelfId, &TcpToRldpRequestSender::abort_query, R.move_as_error());
      } else {
        td::actor::send_closure(SelfId, &TcpToRldpRequestSender::got_result, R.move_as_ok());
      }
    });

    td::actor::create_actor<HttpRldpPayloadSender>("HttpPayloadSender", request_payload_, id_, local_id_, adnl_, rldp_)
        .release();

    auto f = ton::serialize_tl_object(request_->store_tl(id_), true);
    td::actor::send_closure(rldp_, &ton::rldp::Rldp::send_query_ex, local_id_, dst_, "http request over rldp",
                            std::move(P), td::Timestamp::in(30.0), std::move(f), 16 << 10);
  }

  void got_result(td::BufferSlice data) {
    auto F = ton::fetch_tl_object<ton::ton_api::http_response>(std::move(data), true);
    if (F.is_error()) {
      abort_query(F.move_as_error());
      return;
    }
    auto f = F.move_as_ok();
    auto R = ton::http::HttpResponse::create(f->http_version_, f->status_code_, f->reason_, false, true);
    if (R.is_error()) {
      abort_query(R.move_as_error());
      return;
    }
    response_ = R.move_as_ok();
    for (auto &e : f->headers_) {
      ton::http::HttpHeader h{e->name_, e->value_};
      auto S = h.basic_check();
      if (S.is_error()) {
        abort_query(S.move_as_error());
        return;
      }
      response_->add_header(std::move(h));
    }
    auto S = response_->complete_parse_header();
    if (S.is_error()) {
      abort_query(S.move_as_error());
      return;
    }

    response_payload_ = response_->create_empty_payload().move_as_ok();

    auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<td::Unit> R) {
      if (R.is_error()) {
        td::actor::send_closure(SelfId, &TcpToRldpRequestSender::abort_query, R.move_as_error());
      } else {
        td::actor::send_closure(SelfId, &TcpToRldpRequestSender::finished_payload_transfer);
      }
    });
    td::actor::create_actor<HttpRldpPayloadReceiver>("HttpPayloadReceiver", response_payload_, id_, dst_, local_id_,
                                                     adnl_, rldp_)
        .release();

    promise_.set_value(std::make_pair(std::move(response_), std::move(response_payload_)));
    stop();
  };

  void finished_payload_transfer() {
    stop();
  }

  void abort_query(td::Status error) {
    LOG(INFO) << "aborting http over rldp query: " << error;
    stop();
  }

 protected:
  td::Bits256 id_;

  ton::adnl::AdnlNodeIdShort local_id_;
  std::string host_;
  ton::adnl::AdnlNodeIdShort dst_;

  std::unique_ptr<ton::http::HttpRequest> request_;
  std::shared_ptr<ton::http::HttpPayload> request_payload_;

  td::Promise<std::pair<std::unique_ptr<ton::http::HttpResponse>, std::shared_ptr<ton::http::HttpPayload>>> promise_;

  td::actor::ActorId<ton::adnl::Adnl> adnl_;
  td::actor::ActorId<ton::dht::Dht> dht_;
  td::actor::ActorId<ton::rldp::Rldp> rldp_;
  td::actor::ActorId<RldpHttpProxy> proxy_;

  std::unique_ptr<ton::http::HttpResponse> response_;
  std::shared_ptr<ton::http::HttpPayload> response_payload_;
};

class RldpToTcpRequestSender : public td::actor::Actor {
 public:
  RldpToTcpRequestSender(td::Bits256 id, ton::adnl::AdnlNodeIdShort local_id, ton::adnl::AdnlNodeIdShort dst,
                         std::unique_ptr<ton::http::HttpRequest> request,
                         std::shared_ptr<ton::http::HttpPayload> request_payload, td::Promise<td::BufferSlice> promise,
                         td::actor::ActorId<ton::adnl::Adnl> adnl, td::actor::ActorId<ton::rldp::Rldp> rldp,
                         td::actor::ActorId<HttpRemote> remote)
      : id_(id)
      , local_id_(local_id)
      , dst_(dst)
      , request_(std::move(request))
      , request_payload_(std::move(request_payload))
      , promise_(std::move(promise))
      , adnl_(adnl)
      , rldp_(rldp)
      , remote_(std::move(remote)) {
  }
  void start_up() override {
    auto P = td::PromiseCreator::lambda(
        [SelfId = actor_id(this)](
            td::Result<std::pair<std::unique_ptr<ton::http::HttpResponse>, std::shared_ptr<ton::http::HttpPayload>>>
                R) {
          if (R.is_error()) {
            td::actor::send_closure(SelfId, &RldpToTcpRequestSender::abort_query, R.move_as_error());
          } else {
            td::actor::send_closure(SelfId, &RldpToTcpRequestSender::got_result, R.move_as_ok());
          }
        });
    td::actor::send_closure(remote_, &HttpRemote::receive_request, std::move(request_), request_payload_, std::move(P));
    td::actor::create_actor<HttpRldpPayloadReceiver>("HttpPayloadReceiver(R)", std::move(request_payload_), id_, dst_,
                                                     local_id_, adnl_, rldp_)
        .release();
  }

  void got_result(std::pair<std::unique_ptr<ton::http::HttpResponse>, std::shared_ptr<ton::http::HttpPayload>> R) {
    td::actor::create_actor<HttpRldpPayloadSender>("HttpPayloadSender(R)", std::move(R.second), id_, local_id_, adnl_,
                                                   rldp_)
        .release();
    auto f = ton::serialize_tl_object(R.first->store_tl(), true);
    promise_.set_value(std::move(f));
    stop();
  }

  void abort_query(td::Status error) {
    LOG(INFO) << "aborting http over rldp query: " << error;
    promise_.set_error(std::move(error));
    stop();
  }

 protected:
  td::Bits256 id_;

  ton::adnl::AdnlNodeIdShort local_id_;
  ton::adnl::AdnlNodeIdShort dst_;

  std::unique_ptr<ton::http::HttpRequest> request_;
  std::shared_ptr<ton::http::HttpPayload> request_payload_;

  td::Promise<td::BufferSlice> promise_;

  td::actor::ActorId<ton::adnl::Adnl> adnl_;
  td::actor::ActorId<ton::rldp::Rldp> rldp_;

  td::actor::ActorId<HttpRemote> remote_;
};

class RldpHttpProxy : public td::actor::Actor {
 public:
  RldpHttpProxy() {
  }

  void set_port(td::uint16 port) {
    if (port_) {
      LOG(ERROR) << "duplicate listening port";
      std::_Exit(2);
    }
    port_ = port;
  }

  void set_global_config(std::string path) {
    global_config_ = std::move(path);
  }

  void set_addr(td::IPAddress addr) {
    addr_ = addr;
  }

  void set_client_port(td::uint16 port) {
    is_client_ = true;
    client_port_ = port;
  }

  void set_local_host(std::string name, td::IPAddress remote) {
    local_hosts_.emplace_back(std::move(name), std::move(remote));
  }

  void receive_request_result(td::uint64 id, td::Result<tonlib_api::object_ptr<tonlib_api::Object>> R) {
    if (id == 0) {
      return;
    }
    auto it = tonlib_requests_.find(id);
    CHECK(it != tonlib_requests_.end());
    auto promise = std::move(it->second);
    tonlib_requests_.erase(it);

    promise.set_result(std::move(R));
  }

  void send_tonlib_request(tonlib_api::object_ptr<tonlib_api::Function> obj,
                           td::Promise<tonlib_api::object_ptr<tonlib_api::Object>> promise) {
    auto id = next_tonlib_requests_id_++;

    CHECK(tonlib_requests_.emplace(id, std::move(promise)).second);

    td::actor::send_closure(tonlib_client_, &tonlib::TonlibClient::request, id, std::move(obj));
  }

  td::Status load_global_config() {
    TRY_RESULT_PREFIX(conf_data, td::read_file(global_config_), "failed to read: ");
    TRY_RESULT_PREFIX(conf_json, td::json_decode(conf_data.as_slice()), "failed to parse json: ");

    ton::ton_api::config_global conf;
    TRY_STATUS_PREFIX(ton::ton_api::from_json(conf, conf_json.get_object()), "json does not fit TL scheme: ");

    if (!conf.dht_) {
      return td::Status::Error(ton::ErrorCode::error, "does not contain [dht] section");
    }

    TRY_RESULT_PREFIX(dht, ton::dht::Dht::create_global_config(std::move(conf.dht_)), "bad [dht] section: ");
    dht_config_ = std::move(dht);

    class Cb : public tonlib::TonlibCallback {
     public:
      Cb(td::actor::ActorId<RldpHttpProxy> self_id) : self_id_(self_id) {
      }
      void on_result(std::uint64_t id, tonlib_api::object_ptr<tonlib_api::Object> result) override {
        td::actor::send_closure(self_id_, &RldpHttpProxy::receive_request_result, id, std::move(result));
      }
      void on_error(std::uint64_t id, tonlib_api::object_ptr<tonlib_api::error> error) override {
        td::actor::send_closure(self_id_, &RldpHttpProxy::receive_request_result, id,
                                td::Status::Error(error->code_, std::move(error->message_)));
      }

     private:
      td::actor::ActorId<RldpHttpProxy> self_id_;
    };

    tonlib_client_ = td::actor::create_actor<tonlib::TonlibClient>("tonlibclient", td::make_unique<Cb>(actor_id(this)));

    return td::Status::OK();
  }

  void store_dht() {
    for (auto &serv : local_hosts_) {
      if (serv.first != "*") {
        for (auto &serv_id : server_ids_) {
          ton::PublicKey key = ton::pubkeys::Unenc{"http." + serv.first};
          ton::dht::DhtKey dht_key{key.compute_short_id(), "http." + serv.first, 0};
          auto dht_update_rule = ton::dht::DhtUpdateRuleAnybody::create().move_as_ok();
          ton::dht::DhtKeyDescription dht_key_description{std::move(dht_key), key, std::move(dht_update_rule),
                                                          td::BufferSlice()};
          dht_key_description.check().ensure();

          auto ttl = static_cast<td::uint32>(td::Clocks::system() + 3600);
          ton::dht::DhtValue dht_value{std::move(dht_key_description), td::BufferSlice{serv_id.as_slice()}, ttl,
                                       td::BufferSlice("")};

          td::actor::send_closure(dht_, &ton::dht::Dht::set_value, std::move(dht_value), [](td::Unit) {});
        }
      }
    }
    alarm_timestamp() = td::Timestamp::in(60.0);
  }

  void alarm() override {
    store_dht();
  }

  void got_full_id(ton::adnl::AdnlNodeIdShort short_id, ton::adnl::AdnlNodeIdFull full_id) {
    server_ids_full_[short_id] = full_id;
  }

  void run() {
    keyring_ = ton::keyring::Keyring::create(is_client_ ? std::string("") : (db_root_ + "/keyring"));
    {
      auto S = load_global_config();
      if (S.is_error()) {
        LOG(INFO) << S;
        std::_Exit(2);
      }
    }
    if (is_client_ && server_ids_.size() > 0) {
      LOG(ERROR) << "client-only node cannot be server";
      std::_Exit(2);
    }
    auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<td::Unit> R) {
      R.ensure();
      td::actor::send_closure(SelfId, &RldpHttpProxy::run_cont);
    });
    td::MultiPromise mp;
    auto ig = mp.init_guard();
    ig.add_promise(std::move(P));
    for (auto &x : server_ids_) {
      auto Q = td::PromiseCreator::lambda([promise = ig.get_promise(), SelfId = actor_id(this),
                                           x](td::Result<ton::PublicKey> R) mutable {
        if (R.is_error()) {
          promise.set_error(R.move_as_error());
        } else {
          td::actor::send_closure(SelfId, &RldpHttpProxy::got_full_id, x, ton::adnl::AdnlNodeIdFull{R.move_as_ok()});
          promise.set_value(td::Unit());
        }
      });
      td::actor::send_closure(keyring_, &ton::keyring::Keyring::get_public_key, x.pubkey_hash(), std::move(Q));
    }
    auto Q = td::PromiseCreator::lambda(
        [promise = ig.get_promise()](td::Result<tonlib_api::object_ptr<tonlib_api::Object>> R) mutable {
          R.ensure();
          promise.set_value(td::Unit());
        });

    auto conf_dataR = td::read_file(global_config_);
    conf_dataR.ensure();

    auto req = tonlib_api::make_object<tonlib_api::init>(tonlib_api::make_object<tonlib_api::options>(
        tonlib_api::make_object<tonlib_api::config>(conf_dataR.move_as_ok().as_slice().str(), "", false, false),
        tonlib_api::make_object<tonlib_api::keyStoreTypeInMemory>()));
    send_tonlib_request(std::move(req), std::move(Q));
  }

  void run_cont() {
    if (is_client_ && local_hosts_.size() > 0) {
      LOG(ERROR) << "client-only node cannot be server";
      std::_Exit(2);
    }
    if (is_client_ && client_port_ == 0) {
      LOG(ERROR) << "client-only expects client port";
      std::_Exit(2);
    }
    {
      adnl_network_manager_ =
          ton::adnl::AdnlNetworkManager::create(is_client_ ? client_port_ : static_cast<td::uint16>(addr_.get_port()));
      adnl_ = ton::adnl::Adnl::create(is_client_ ? std::string("") : (db_root_), keyring_.get());
      td::actor::send_closure(adnl_, &ton::adnl::Adnl::register_network_manager, adnl_network_manager_.get());
      ton::adnl::AdnlCategoryMask cat_mask;
      cat_mask[0] = true;
      if (is_client_) {
        td::IPAddress addr;
        addr.init_host_port("127.0.0.1", client_port_).ensure();
        td::actor::send_closure(adnl_network_manager_, &ton::adnl::AdnlNetworkManager::add_self_addr, addr,
                                std::move(cat_mask), 0);
      } else {
        td::actor::send_closure(adnl_network_manager_, &ton::adnl::AdnlNetworkManager::add_self_addr, addr_,
                                std::move(cat_mask), 0);
      }

      ton::adnl::AdnlAddressList addr_list;
      if (!is_client_) {
        ton::adnl::AdnlAddress x = ton::adnl::AdnlAddressImpl::create(
            ton::create_tl_object<ton::ton_api::adnl_address_udp>(addr_.get_ipv4(), addr_.get_port()));
        addr_list.add_addr(std::move(x));
      }
      addr_list.set_version(static_cast<td::int32>(td::Clocks::system()));
      addr_list.set_reinit_date(ton::adnl::Adnl::adnl_start_time());
      {
        auto pk = ton::PrivateKey{ton::privkeys::Ed25519::random()};
        auto pub = pk.compute_public_key();
        td::actor::send_closure(keyring_, &ton::keyring::Keyring::add_key, std::move(pk), true, [](td::Unit) {});
        local_id_ = ton::adnl::AdnlNodeIdShort{pub.compute_short_id()};
        td::actor::send_closure(adnl_, &ton::adnl::Adnl::add_id, ton::adnl::AdnlNodeIdFull{pub}, addr_list,
                                static_cast<td::uint8>(0));

        if (server_ids_.size() == 0 && !is_client_) {
          server_ids_.insert(local_id_);
        }
      }
      {
        auto pk = ton::PrivateKey{ton::privkeys::Ed25519::random()};
        auto pub = pk.compute_public_key();
        td::actor::send_closure(keyring_, &ton::keyring::Keyring::add_key, std::move(pk), true, [](td::Unit) {});
        dht_id_ = ton::adnl::AdnlNodeIdShort{pub.compute_short_id()};
        td::actor::send_closure(adnl_, &ton::adnl::Adnl::add_id, ton::adnl::AdnlNodeIdFull{pub}, addr_list,
                                static_cast<td::uint8>(0));
      }
      for (auto &serv_id : server_ids_) {
        td::actor::send_closure(adnl_, &ton::adnl::Adnl::add_id, server_ids_full_[serv_id], addr_list,
                                static_cast<td::uint8>(0));
      }
    }
    {
      if (is_client_) {
        auto D = ton::dht::Dht::create_client(dht_id_, "", dht_config_, keyring_.get(), adnl_.get());
        D.ensure();
        dht_ = D.move_as_ok();
      } else {
        auto D = ton::dht::Dht::create(dht_id_, db_root_, dht_config_, keyring_.get(), adnl_.get());
        D.ensure();
        dht_ = D.move_as_ok();
      }
      td::actor::send_closure(adnl_, &ton::adnl::Adnl::register_dht_node, dht_.get());
    }
    if (port_) {
      class Cb : public ton::http::HttpServer::Callback {
       public:
        Cb(td::actor::ActorId<RldpHttpProxy> proxy) : proxy_(proxy) {
        }
        void receive_request(
            std::unique_ptr<ton::http::HttpRequest> request, std::shared_ptr<ton::http::HttpPayload> payload,
            td::Promise<std::pair<std::unique_ptr<ton::http::HttpResponse>, std::shared_ptr<ton::http::HttpPayload>>>
                promise) override {
          td::actor::send_closure(proxy_, &RldpHttpProxy::receive_http_request, std::move(request), std::move(payload),
                                  std::move(promise));
        }

       private:
        td::actor::ActorId<RldpHttpProxy> proxy_;
      };

      server_ = ton::http::HttpServer::create(port_, std::make_shared<Cb>(actor_id(this)));
    }

    for (auto &serv_id : server_ids_) {
      class AdnlCb : public ton::adnl::Adnl::Callback {
       public:
        AdnlCb(td::actor::ActorId<RldpHttpProxy> id) : self_id_(id) {
        }
        void receive_message(ton::adnl::AdnlNodeIdShort src, ton::adnl::AdnlNodeIdShort dst,
                             td::BufferSlice data) override {
        }
        void receive_query(ton::adnl::AdnlNodeIdShort src, ton::adnl::AdnlNodeIdShort dst, td::BufferSlice data,
                           td::Promise<td::BufferSlice> promise) override {
          td::actor::send_closure(self_id_, &RldpHttpProxy::receive_rldp_request, src, dst, std::move(data),
                                  std::move(promise));
        }

       private:
        td::actor::ActorId<RldpHttpProxy> self_id_;
      };
      td::actor::send_closure(adnl_, &ton::adnl::Adnl::subscribe, serv_id,
                              ton::adnl::Adnl::int_to_bytestring(ton::ton_api::http_request::ID),
                              std::make_unique<AdnlCb>(actor_id(this)));
    }
    for (auto &serv : local_hosts_) {
      servers_.emplace(serv.first, td::actor::create_actor<HttpRemote>("remote", serv.second));
    }

    rldp_ = ton::rldp::Rldp::create(adnl_.get());
    td::actor::send_closure(rldp_, &ton::rldp::Rldp::add_id, local_id_);
    for (auto &serv_id : server_ids_) {
      td::actor::send_closure(rldp_, &ton::rldp::Rldp::add_id, serv_id);
    }

    store_dht();
  }

  void receive_http_request(
      std::unique_ptr<ton::http::HttpRequest> request, std::shared_ptr<ton::http::HttpPayload> payload,
      td::Promise<std::pair<std::unique_ptr<ton::http::HttpResponse>, std::shared_ptr<ton::http::HttpPayload>>>
          promise) {
    auto host = request->host();
    if (host.size() == 0) {
      host = request->url();
      if (host.size() >= 7 && host.substr(0, 7) == "http://") {
        host = host.substr(7);
      } else if (host.size() >= 8 && host.substr(0, 8) == "https://") {
        host = host.substr(8);
      }
      auto p = host.find('/');
      if (p != std::string::npos) {
        host = host.substr(0, p);
      }
    } else {
      if (host.size() >= 7 && host.substr(0, 7) == "http://") {
        host = host.substr(7);
      } else if (host.size() >= 8 && host.substr(0, 8) == "https://") {
        host = host.substr(8);
      }
      auto p = host.find('/');
      if (p != std::string::npos) {
        host = host.substr(0, p);
      }
    }
    {
      auto p = host.find(':');
      if (p != std::string::npos) {
        host = host.substr(0, p);
      }
    }
    std::transform(host.begin(), host.end(), host.begin(), [](unsigned char c) { return std::tolower(c); });
    if (!proxy_all_ &&
        (host.size() < 5 || (host.substr(host.size() - 4) != ".ton" && host.substr(host.size() - 5) != ".adnl"))) {
      promise.set_error(td::Status::Error(ton::ErrorCode::error, "bad server name"));
      return;
    }

    td::actor::create_actor<TcpToRldpRequestSender>("outboundreq", local_id_, host, std::move(request),
                                                    std::move(payload), std::move(promise), adnl_.get(), dht_.get(),
                                                    rldp_.get(), actor_id(this))
        .release();
  }

  void receive_rldp_request(ton::adnl::AdnlNodeIdShort src, ton::adnl::AdnlNodeIdShort dst, td::BufferSlice data,
                            td::Promise<td::BufferSlice> promise) {
    LOG(INFO) << "got HTTP request over rldp from " << src;
    TRY_RESULT_PROMISE(promise, f, ton::fetch_tl_object<ton::ton_api::http_request>(std::move(data), true));
    TRY_RESULT_PROMISE(promise, request, ton::http::HttpRequest::create(f->method_, f->url_, f->http_version_));
    for (auto &x : f->headers_) {
      ton::http::HttpHeader h{x->name_, x->value_};
      TRY_STATUS_PROMISE(promise, h.basic_check());
      request->add_header(std::move(h));
    }
    TRY_STATUS_PROMISE(promise, request->complete_parse_header());
    auto host = request->host();
    if (host.size() == 0) {
      host = request->url();
      if (host.size() >= 7 && host.substr(0, 7) == "http://") {
        host = host.substr(7);
      } else if (host.size() >= 8 && host.substr(0, 8) == "https://") {
        host = host.substr(8);
      }
      auto p = host.find('/');
      if (p != std::string::npos) {
        host = host.substr(0, p);
      }
    } else {
      if (host.size() >= 7 && host.substr(0, 7) == "http://") {
        host = host.substr(7);
      } else if (host.size() >= 8 && host.substr(0, 8) == "https://") {
        host = host.substr(8);
      }
      auto p = host.find('/');
      if (p != std::string::npos) {
        host = host.substr(0, p);
      }
    }
    {
      auto p = host.find(':');
      if (p != std::string::npos) {
        host = host.substr(0, p);
      }
    }
    std::transform(host.begin(), host.end(), host.begin(), [](unsigned char c) { return std::tolower(c); });

    auto it = servers_.find(host);
    if (it == servers_.end()) {
      it = servers_.find("*");
      if (it == servers_.end()) {
        promise.set_error(td::Status::Error(ton::ErrorCode::error, "unknown server name"));
        return;
      }
    }

    TRY_RESULT_PROMISE(promise, payload, request->create_empty_payload());

    LOG(INFO) << "starting HTTP over RLDP request";
    td::actor::create_actor<RldpToTcpRequestSender>("inboundreq", f->id_, dst, src, std::move(request),
                                                    std::move(payload), std::move(promise), adnl_.get(), rldp_.get(),
                                                    it->second.get())
        .release();
  }

  void add_adnl_addr(ton::adnl::AdnlNodeIdShort id) {
    server_ids_.insert(id);
  }

  void set_db_root(std::string db_root) {
    db_root_ = std::move(db_root);
  }

  void set_proxy_all(bool value) {
    proxy_all_ = value;
  }

 private:
  td::uint16 port_{0};
  td::IPAddress addr_;
  std::string global_config_;
  std::vector<std::pair<std::string, td::IPAddress>> local_hosts_;

  bool is_client_{false};
  td::uint16 client_port_{0};

  std::set<ton::adnl::AdnlNodeIdShort> server_ids_;
  std::map<ton::adnl::AdnlNodeIdShort, ton::adnl::AdnlNodeIdFull> server_ids_full_;
  ton::adnl::AdnlNodeIdShort local_id_;
  ton::adnl::AdnlNodeIdShort dht_id_;

  td::actor::ActorOwn<ton::http::HttpServer> server_;
  std::map<std::string, ton::adnl::AdnlNodeIdShort> dns_;
  std::map<std::string, td::actor::ActorOwn<HttpRemote>> servers_;

  td::actor::ActorOwn<ton::keyring::Keyring> keyring_;
  td::actor::ActorOwn<ton::adnl::AdnlNetworkManager> adnl_network_manager_;
  td::actor::ActorOwn<ton::adnl::Adnl> adnl_;
  td::actor::ActorOwn<ton::dht::Dht> dht_;
  td::actor::ActorOwn<ton::rldp::Rldp> rldp_;

  std::shared_ptr<ton::dht::DhtGlobalConfig> dht_config_;

  std::string db_root_ = ".";
  bool proxy_all_ = false;

  td::actor::ActorOwn<tonlib::TonlibClient> tonlib_client_;
  std::map<td::uint64, td::Promise<tonlib_api::object_ptr<tonlib_api::Object>>> tonlib_requests_;
  td::uint64 next_tonlib_requests_id_{1};
};

void TcpToRldpRequestSender::resolve() {
  auto S = td::Slice(host_);
  if (S.size() >= 5 && S.substr(S.size() - 5) == ".adnl") {
    S.truncate(S.size() - 5);
    auto R = ton::adnl::AdnlNodeIdShort::parse(S);
    if (R.is_error()) {
      abort_query(R.move_as_error_prefix("failed to parse adnl addr: "));
      return;
    }
    resolved(R.move_as_ok());
    return;
  }
  if (false) {
    auto P = td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<ton::dht::DhtValue> R) {
      if (R.is_error()) {
        td::actor::send_closure(SelfId, &TcpToRldpRequestSender::abort_query, R.move_as_error());
        return;
      }
      auto value = R.move_as_ok();
      if (value.value().size() != 32) {
        td::actor::send_closure(SelfId, &TcpToRldpRequestSender::abort_query, td::Status::Error("bad value in dht"));
        return;
      }

      ton::PublicKeyHash h{value.value().as_slice()};
      td::actor::send_closure(SelfId, &TcpToRldpRequestSender::resolved, ton::adnl::AdnlNodeIdShort{h});
    });

    ton::PublicKey key = ton::pubkeys::Unenc{"http." + host_};
    ton::dht::DhtKey dht_key{key.compute_short_id(), "http." + host_, 0};
    td::actor::send_closure(dht_, &ton::dht::Dht::get_value, std::move(dht_key), std::move(P));
  } else {
    auto obj = tonlib_api::make_object<tonlib_api::dns_resolve>(nullptr, host_, 0, 16);

    auto P =
        td::PromiseCreator::lambda([SelfId = actor_id(this)](td::Result<tonlib_api::object_ptr<tonlib_api::Object>> R) {
          if (R.is_error()) {
            td::actor::send_closure(SelfId, &TcpToRldpRequestSender::abort_query,
                                    R.move_as_error_prefix("failed to resolve: "));
          } else {
            auto v = R.move_as_ok();
            auto obj = static_cast<tonlib_api::dns_resolved *>(v.get());
            ton::adnl::AdnlNodeIdShort id;
            td::uint32 cnt = 0;
            for (auto &e : obj->entries_) {
              tonlib_api::downcast_call(
                  *e->entry_.get(), td::overloaded(
                                        [&](tonlib_api::dns_entryDataAdnlAddress &x) {
                                          if (td::Random::fast(0, cnt) == 0) {
                                            auto R = ton::adnl::AdnlNodeIdShort::parse(x.adnl_address_->adnl_address_);
                                            if (R.is_ok()) {
                                              id = R.move_as_ok();
                                              cnt++;
                                            }
                                          }
                                        },
                                        [&](auto &x) {}));
            }
            if (cnt == 0) {
              td::actor::send_closure(SelfId, &TcpToRldpRequestSender::abort_query,
                                      td::Status::Error(ton::ErrorCode::notready, "failed to resolve"));
            } else {
              td::actor::send_closure(SelfId, &TcpToRldpRequestSender::resolved, id);
            }
          }
        });
    td::actor::send_closure(proxy_, &RldpHttpProxy::send_tonlib_request, std::move(obj), std::move(P));
  }
}

int main(int argc, char *argv[]) {
  SET_VERBOSITY_LEVEL(verbosity_WARNING);

  td::set_default_failure_signal_handler().ensure();

  td::actor::ActorOwn<RldpHttpProxy> x;
  td::unique_ptr<td::LogInterface> logger_;
  SCOPE_EXIT {
    td::log_interface = td::default_log_interface;
  };

  td::OptionParser p;
  p.set_description(
      "A simple rldp-to-http and http-to-rldp proxy for running and accessing ton sites\n"
      "Example:\n\trldp-http-proxy -p 8080 -c 3333 -C ton-global.config.json\tRuns a local HTTP->RLDP proxy that "
      "accepts HTTP proxy queries at localhost:8080\n"
      "Example:\n\trldp-http-proxy -a <global-ip>:3333 -L example.ton -C ton-global.config.json\tRuns a local "
      "RLDP->HTTP proxy on UDP port <global-ip>:3333 that forwards all queries for http://example.ton to HTTP server "
      "at localhost:80\n");
  p.add_option('v', "verbosity", "set verbosity level", [&](td::Slice arg) {
    int v = VERBOSITY_NAME(FATAL) + (td::to_integer<int>(arg));
    SET_VERBOSITY_LEVEL(v);
  });
  p.add_option('V', "version", "shows rldp-http-proxy build information", [&]() {
    std::cout << "rldp-http-proxy build information: [ Commit: " << GitMetadata::CommitSHA1() << ", Date: " << GitMetadata::CommitDate() << "]\n";
    std::exit(0);
  });
  p.add_option('h', "help", "prints a help message", [&]() {
    char b[10240];
    td::StringBuilder sb(td::MutableSlice{b, 10000});
    sb << p;
    std::cout << sb.as_cslice().c_str();
    std::exit(2);
  });
  p.add_checked_option('p', "port", "sets http listening port", [&](td::Slice arg) -> td::Status {
    TRY_RESULT(port, td::to_integer_safe<td::uint16>(arg));
    td::actor::send_closure(x, &RldpHttpProxy::set_port, port);
    return td::Status::OK();
  });
  p.add_checked_option('a', "address", "local <ip>:<port> to use for adnl queries", [&](td::Slice arg) -> td::Status {
    td::IPAddress addr;
    TRY_STATUS(addr.init_host_port(arg.str()));
    td::actor::send_closure(x, &RldpHttpProxy::set_addr, addr);
    return td::Status::OK();
  });
  p.add_checked_option('A', "adnl", "server ADNL addr", [&](td::Slice arg) -> td::Status {
    TRY_RESULT(adnl, ton::adnl::AdnlNodeIdShort::parse(arg));
    td::actor::send_closure(x, &RldpHttpProxy::add_adnl_addr, adnl);
    return td::Status::OK();
  });
  p.add_checked_option('c', "client-port", "local <port> to use for client adnl queries",
                       [&](td::Slice arg) -> td::Status {
                         TRY_RESULT(port, td::to_integer_safe<td::uint16>(arg));
                         td::actor::send_closure(x, &RldpHttpProxy::set_client_port, port);
                         return td::Status::OK();
                       });
  p.add_option('C', "global-config", "global TON configuration file",
               [&](td::Slice arg) { td::actor::send_closure(x, &RldpHttpProxy::set_global_config, arg.str()); });
  p.add_checked_option('L', "local", "http hostname that will be proxied to http server at localhost:80",
                       [&](td::Slice arg) -> td::Status {
                         td::IPAddress addr;
                         TRY_STATUS(addr.init_ipv4_port("127.0.0.1", 80));
                         td::actor::send_closure(x, &RldpHttpProxy::set_local_host, arg.str(), addr);
                         return td::Status::OK();
                       });
  p.add_option('D', "db", "db root",
               [&](td::Slice arg) { td::actor::send_closure(x, &RldpHttpProxy::set_db_root, arg.str()); });
  p.add_checked_option(
      'R', "remote",
      "<hostname>@<ip>:<port>, indicates a http hostname that will be proxied to remote http server at <ip>:<port>",
      [&](td::Slice arg) -> td::Status {
        auto ch = arg.find('@');
        if (ch == td::Slice::npos) {
          return td::Status::Error("bad format for --remote");
        }
        td::IPAddress addr;
        TRY_STATUS(addr.init_host_port(arg.substr(ch + 1).str()));
        td::actor::send_closure(x, &RldpHttpProxy::set_local_host, arg.substr(0, ch).str(), addr);
        return td::Status::OK();
      });
  p.add_option('d', "daemonize", "set SIGHUP", [&]() {
    td::set_signal_handler(td::SignalType::HangUp, [](int sig) {
#if TD_DARWIN || TD_LINUX
      close(0);
      setsid();
#endif
    }).ensure();
  });
  p.add_option('l', "logname", "log to file", [&](td::Slice fname) {
    logger_ = td::FileLog::create(fname.str()).move_as_ok();
    td::log_interface = logger_.get();
  });
  p.add_checked_option('P', "proxy-all", "value=[YES|NO]. proxy all HTTP requests (default only *.ton and *.adnl)",
                       [&](td::Slice value) {
                         if (value == "YES" || value == "yes") {
                           td::actor::send_closure(x, &RldpHttpProxy::set_proxy_all, true);
                         } else if (value == "NO" || value == "no") {
                           td::actor::send_closure(x, &RldpHttpProxy::set_proxy_all, false);
                         } else {
                           return td::Status::Error("--proxy-all expected YES or NO");
                         }

                         return td::Status::OK();
                       });

  td::actor::Scheduler scheduler({7});

  scheduler.run_in_context([&] { x = td::actor::create_actor<RldpHttpProxy>("proxymain"); });

  scheduler.run_in_context([&] { p.run(argc, argv).ensure(); });
  scheduler.run_in_context([&] { td::actor::send_closure(x, &RldpHttpProxy::run); });
  while (scheduler.run(1)) {
  }

  return 0;
}
