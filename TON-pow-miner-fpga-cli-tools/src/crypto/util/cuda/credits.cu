/* creditscoin SHA256 djm34 implementation - 2015 */

#include <iostream>

#include "miner.h"
#include "cuda_helper.h"
#include "td/utils/Slice-decl.h"
#include "td/utils/misc.h"

extern bool bitcredit_setBlockTarget(uint32_t gpu_id, uint32_t gpu_threads, uint32_t cpu_id, uint32_t expired,
                                     const unsigned char *data, const void *ptarget, const unsigned char *rdata);
extern void bitcredit_cpu_init(uint32_t gpu_id, uint32_t cpu_id, uint64_t threads);
extern HashResult bitcredit_cpu_hash(uint32_t gpu_id, uint32_t cpu_id, uint32_t gpu_threads, uint64_t threads,
                                     uint64_t startNounce, uint32_t expired);

extern "C" int scanhash_credits(int gpu_id, int cpu_id, ton::HDataEnv H, const ton::Miner::Options &options,
                                uint64_t *pdata, const uint32_t *ptarget, uint64_t max_nonce, unsigned char *rdata) {
  td::Slice data = H.as_slice();
  constexpr size_t prefix_size = 72;
  td::Slice head = data.substr(0, prefix_size);
  td::Slice tail = data.substr(prefix_size);
  char guard = head.back();

  // throughput
  td::uint64 throughput = (td::uint64)((1U << 19) * options.factor);// 256*256*64*8*factor/64
  if (options.max_iterations < throughput) {
    throughput = options.max_iterations;
  }
  LOG(WARNING) << "[ START MINER, GPU ID: " << gpu_id << ", boost factor: " << options.factor << ", throughput: " << throughput << " ]";

  // allocate mem
  bitcredit_cpu_init(gpu_id, cpu_id, throughput);

  // set once at start
  uint32_t expired = options.expire_base;

  // set data
  // std::cout << "data: " << hex_encode(data) << std::endl;
  unsigned char input[123], complexity[32];
  memcpy(input, data.ubegin(), data.size());
  if (!bitcredit_setBlockTarget(gpu_id, options.gpu_threads, cpu_id, expired, input, options.complexity.data(), rdata)) {
    abort();
  }

  if (options.instant_hashes_computed) {
    *options.instant_hashes_computed = throughput;
  }

  td::int64 i = 0;
  for (; i < options.max_iterations;) {
    td::Timestamp instant_start_at = td::Timestamp::now();
    HashResult foundNonce = bitcredit_cpu_hash(gpu_id, cpu_id, options.gpu_threads, throughput, i, expired);
    *options.instant_passed = td::Timestamp::now().at() - instant_start_at.at();
    if (foundNonce.nonce != UINT64_MAX && foundNonce.vcpu != UINT64_MAX) {
      pdata[0] = foundNonce.nonce;
      pdata[1] = foundNonce.vcpu;
      pdata[2] = expired;
      if (options.hashes_computed) {
        *options.hashes_computed += foundNonce.nonce * foundNonce.vcpu;
      }
      if (options.instant_hashes_computed) {
        *options.instant_hashes_computed = foundNonce.nonce * foundNonce.vcpu;
      }
      return 1;
    }
    i += throughput;
    if (options.hashes_computed) {
      *options.hashes_computed += throughput;
    }
    if (options.token_) {
      break;
    }
    if (options.expire_at && options.expire_at.value().is_in_past(td::Timestamp::now())) {
      break;
    }
  }
  return 0;
}
