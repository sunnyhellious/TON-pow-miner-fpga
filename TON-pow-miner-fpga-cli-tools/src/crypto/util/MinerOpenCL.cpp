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
----------
    Copyright 2017-2020 Telegram Systems LLP
*/
#include "Miner.h"

#include "td/utils/Random.h"
#include "td/utils/misc.h"
#include "td/utils/crypto.h"
#include "td/utils/port/Clocks.h"
#include <openssl/sha.h>
#include "opencl/sha256.h"
#include "opencl/miner.h"

namespace ton {
td::optional<std::string> MinerOpenCL::run(const Options& options) {
  HDataEnv H;
  H.init(options.my_address, td::Slice(options.seed.data(), options.seed.size()));

  // random start values
  unsigned char rdata[32 * MAX_GPU_THREADS] = {};
  td::Random::secure_bytes(rdata, 32 * options.gpu_threads);
  
  auto miner = opencl::SHA256();
  return miner.run(H, rdata, options, 0);
}
}  // namespace ton
