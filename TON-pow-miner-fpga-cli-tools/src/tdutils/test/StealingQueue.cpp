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

#include "td/utils/tests.h"
#include "td/utils/benchmark.h"

#include "td/utils/AtomicRead.h"
#include "td/utils/StealingQueue.h"
#include "td/utils/MpmcQueue.h"

namespace td {
TEST(StealingQueue, very_simple) {
  StealingQueue<int, 8> q;
  q.local_push(1, [](auto x) { UNREACHABLE(); });
  int x;
  CHECK(q.local_pop(x));
  ASSERT_EQ(1, x);
}
TEST(AtomicRead, simple) {
  td::Stage run;
  td::Stage check;

  size_t threads_n = 10;
  std::vector<td::thread> threads;

  int x{0};
  std::atomic<int> version{0};

  int64 res = 0;
  for (size_t i = 0; i < threads_n; i++) {
    threads.push_back(td::thread([&, id = static_cast<uint32>(i)] {
      for (uint64 round = 1; round < 10000; round++) {
        if (id == 0) {
        }
        run.wait(round * threads_n);
        if (id == 0) {
          version++;
          x++;
          version++;
        } else {
          int y = 0;
          auto v1 = version.load();
          y = x;
          auto v2 = version.load();
          if (v1 == v2 && v1 % 2 == 0) {
            res += y;
          }
        }

        check.wait(round * threads_n);
      }
    }));
  }
  td::do_not_optimize_away(res);
  for (auto &thread : threads) {
    thread.join();
  }
}
TEST(AtomicRead, simple2) {
  td::Stage run;
  td::Stage check;

  size_t threads_n = 10;
  std::vector<td::thread> threads;

  struct Value {
    td::uint64 value = 0;
    char str[50] = "0 0 0 0";
  };
  AtomicRead<Value> value;

  auto to_str = [](size_t i) { return PSTRING() << i << " " << i << " " << i << " " << i; };
  for (size_t i = 0; i < threads_n; i++) {
    threads.push_back(td::thread([&, id = static_cast<uint32>(i)] {
      for (uint64 round = 1; round < 10000; round++) {
        if (id == 0) {
        }
        run.wait(round * threads_n);
        if (id == 0) {
          auto x = value.lock();
          x->value = round;
          auto str = to_str(round);
          memcpy(x->str, str.c_str(), str.size() + 1);
        } else {
          Value x;
          value.read(x);
          LOG_CHECK(x.value == round || x.value == round - 1) << x.value << " " << round;
          CHECK(x.str == to_str(x.value));
        }
        check.wait(round * threads_n);
      }
    }));
  }
  for (auto &thread : threads) {
    thread.join();
  }
}

TEST(StealingQueue, simple) {
  uint64 sum;
  std::atomic<uint64> got_sum;

  td::Stage run;
  td::Stage check;

  size_t threads_n = 10;
  std::vector<td::thread> threads;
  std::vector<StealingQueue<int, 8>> lq(threads_n);
  MpmcQueue<int> gq(threads_n);

  constexpr uint64 XN = 20;
  uint64 x_sum[XN];
  x_sum[0] = 0;
  x_sum[1] = 1;
  for (uint64 i = 2; i < XN; i++) {
    x_sum[i] = i + x_sum[i - 1] + x_sum[i - 2];
  }

  td::Random::Xorshift128plus rnd(123);
  for (size_t i = 0; i < threads_n; i++) {
    threads.push_back(td::thread([&, id = static_cast<uint32>(i)] {
      for (uint64 round = 1; round < 10000; round++) {
        if (id == 0) {
          sum = 0;
          int n = rnd() % 5;
          for (int j = 0; j < n; j++) {
            int x = rand() % XN;
            sum += x_sum[x];
            gq.push(x, id);
          }
          got_sum = 0;
        }
        run.wait(round * threads_n);
        while (got_sum.load() != sum) {
          auto x = [&] {
            int res;
            if (lq[id].local_pop(res)) {
              return res;
            }
            if (gq.try_pop(res, id)) {
              return res;
            }
            if (lq[id].steal(res, lq[rand() % threads_n])) {
              //LOG(ERROR) << "STEAL";
              return res;
            }
            return 0;
          }();
          if (x == 0) {
            continue;
          }
          //LOG(ERROR) << x << " " << got_sum.load() << " " << sum;
          got_sum.fetch_add(x, std::memory_order_relaxed);
          lq[id].local_push(x - 1, [&](auto y) {
            //LOG(ERROR) << "OVERFLOW";
            gq.push(y, id);
          });
          if (x > 1) {
            lq[id].local_push(x - 2, [&](auto y) { gq.push(y, id); });
          }
        }
        check.wait(round * threads_n);
      }
    }));
  }
  for (auto &thread : threads) {
    thread.join();
  }
}
}  // namespace td
