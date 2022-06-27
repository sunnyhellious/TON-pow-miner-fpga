#include <iostream>

#include "sha256.h"
#include "miner.h"
#include "opencl.h"
#include "sha256_cl.h"

#include "crypto/util/Miner.h"

#ifndef DEFAULT_HPF
	#define DEFAULT_HPF 3
#endif

namespace opencl {

td::optional<std::string> SHA256::run(ton::HDataEnv H, unsigned char *rdata, const ton::Miner::Options &options,
                                      int cpu_id) {
  // opencl
  auto opencl = OpenCL();
  
  opencl.load_source("sha256.cl");
  // opencl.set_source(sha256_cl, sha256_cl_len);
  
  opencl.print_devices();
  opencl.create_context(options.platform_id, options.gpu_id);

  int HPF = DEFAULT_HPF;
  
  char cl_build_options[256];
  sprintf(cl_build_options, "-D HPF=%d", HPF);	
  
  // data
  td::Slice data = H.as_slice();

  // set data
  //std::cout << "data: " << hex_encode(data) << std::endl;
  unsigned char input[123], complexity[32];
  memcpy(input, data.ubegin(), data.size());

  // opencl.create_kernel(cl_build_options, input, rdata, options.gpu_threads, options.complexity.data());
  opencl.create_kernel(cl_build_options, input, rdata, options.gpu_threads, options.complexity.data());

  td::uint64 throughput = (td::uint64)((1U << 19) * options.factor * HPF);// 256*256*64*8*factor/64
  if (options.max_iterations < throughput) {
    throughput = options.max_iterations;
  }
  LOG(WARNING) << "[ START MINER, GPU ID: " << options.gpu_id << ", boost factor: " << options.factor << ", throughput: " << throughput << " ]";

  opencl.load_objects(options.gpu_id, cpu_id, input, options.complexity.data(), rdata, options.gpu_threads);
   
  if (options.instant_hashes_computed) {
    *options.instant_hashes_computed = throughput;
  }

  // set once at start
  uint32_t expired = options.expire_base;
  
  td::int64 i = 0;
  
  for (; i < options.max_iterations;) {
    td::Timestamp instant_start_at = td::Timestamp::now();
    HashResult foundNonce = opencl.scan_hash(cpu_id, options.gpu_threads, throughput/HPF, i, expired);
    *options.instant_passed = td::Timestamp::now().at() - instant_start_at.at();
    if (foundNonce.nonce != UINT64_MAX && foundNonce.vcpu != UINT64_MAX) {
      if (options.hashes_computed) {
        *options.hashes_computed += foundNonce.nonce * foundNonce.vcpu;
      }
      if (options.instant_hashes_computed) {
        *options.instant_hashes_computed = foundNonce.nonce * foundNonce.vcpu;
      }
      auto result = ton::build_mine_result(cpu_id, H, options, rdata, foundNonce.nonce, foundNonce.vcpu, expired);
      if (result) {
        opencl.release();
        return result;
      }
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

  opencl.release();
  return {};
}

}  // namespace opencl
