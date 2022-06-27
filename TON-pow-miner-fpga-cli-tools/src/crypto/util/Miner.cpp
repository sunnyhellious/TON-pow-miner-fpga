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
#include "Miner.h"

#include "td/utils/JsonBuilder.h"
#include "td/utils/Random.h"
#include "td/utils/filesystem.h"
#include "td/utils/format.h"
#include "td/utils/misc.h"
#include "td/utils/crypto.h"
#include "td/utils/port/Clocks.h"
#include <openssl/sha.h>

#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <stdint.h>

struct crc32_loc {
  uint32_t table[256];

  void generate_table() {
    uint32_t polynomial = 0xEDB88320;
    for (uint32_t i = 0; i < 256; i++) {
      uint32_t c = i;
      for (size_t j = 0; j < 8; j++) {
        if (c & 1) {
          c = polynomial ^ (c >> 1);
        } else {
          c >>= 1;
        }
      }
      this->table[i] = c;
    }
  }

  uint8_t fl_table = 0;

  uint32_t update(const void *buf, uint64_t len) {
    if (this->fl_table == 0) {
      generate_table();
      this->fl_table = 1;
    }

    uint32_t c = 0xffffffff;  //^0xFFFFFFFF;
    const uint8_t *u = static_cast<const uint8_t *>(buf);

    for (size_t i = 0; i < len; ++i) {
      c = table[(c ^ u[i]) & 0xFF] ^ (c >> 8);
    }

    return c ^ 0xFFFFFFFF;
  }
};

#define M_ERR_P(A)     \
  {                    \
    printf("L%d:", A); \
    goto err_p;        \
  }

#define M_ERR_PR(A)    \
  {                    \
    printf("L%d:", A); \
    goto err_pre;      \
  }

struct com_port_loc {
  HANDLE hComm_l;

  bool comport_init(LPCSTR nComm) {
    // L"\\\\.\\COM4"

    HANDLE *hComm = &this->hComm_l;

    DCB dcb;

    COMMTIMEOUTS touts;

    *hComm = CreateFileA(nComm, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

    if (*hComm == INVALID_HANDLE_VALUE)
      M_ERR_P(__LINE__);

    if (!GetCommState(*hComm, &dcb))
      M_ERR_P(__LINE__);

    dcb.BaudRate = 900000;  //  baud rate
    dcb.ByteSize = 8;       //  data size, xmit and rcv

    if (!SetCommState(*hComm, &dcb))
      M_ERR_P(__LINE__);

    touts.ReadIntervalTimeout = 0;
    touts.ReadTotalTimeoutMultiplier = 0;
    touts.ReadTotalTimeoutConstant = 10;
    touts.WriteTotalTimeoutMultiplier = 0;
    touts.WriteTotalTimeoutConstant = 0;

    if (!SetCommTimeouts(*hComm, &touts))
      M_ERR_P(__LINE__);

    if (!SetCommMask(*hComm, EV_RXCHAR | EV_ERR))
      M_ERR_P(__LINE__);

    return 0;

  err_p:;

    printf("ERR: comport_init: some shit happened\n");

    return 1;
  }

  int comport_write(char *lpBuf, uint32_t dwToWrite) {
    HANDLE *hComm = &this->hComm_l;

    OVERLAPPED osWrite = {0};
    DWORD dwWritten;
    DWORD dwRes;

    static crc32_loc crc32_1;
    uint32_t crc32_;

    crc32_ = crc32_1.update(lpBuf, dwToWrite);

    memcpy(&lpBuf[dwToWrite], &crc32_, 4);

    dwToWrite = dwToWrite + 4;

    /*
    printf("UART_TX len[%d] = 0x", dwToWrite);
    for (int j = 0; j < dwToWrite; j += 1)
      printf("%02X", lpBuf[j] & 0xFF);
    printf("\n");
		*/

    osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (osWrite.hEvent == NULL)
      M_ERR_P(__LINE__);

    if (!WriteFile(*hComm, lpBuf, dwToWrite, &dwWritten, &osWrite)) {
      if (GetLastError() != ERROR_IO_PENDING)
        M_ERR_PR(__LINE__)
      else
        dwRes = WaitForSingleObject(osWrite.hEvent, INFINITE);

      switch (dwRes) {
        case WAIT_OBJECT_0:
          if (!GetOverlappedResult(*hComm, &osWrite, &dwWritten, FALSE))
            M_ERR_PR(__LINE__);
          break;

        default:
          M_ERR_PR(__LINE__);
          break;
      }
    }

    CloseHandle(osWrite.hEvent);

    return 0;

  err_pre:;

    CloseHandle(osWrite.hEvent);

  err_p:;

    printf("ERR: comport_read: some shit happened\n");

    return 1;
  }

  int comport_read(char *buffer, uint64_t max_len, uint64_t *bytes_read) {
    DWORD dwRead = 0;
    BOOL fWaitingOnRead = FALSE;
    OVERLAPPED osReader = {0};

    HANDLE *hComm = &this->hComm_l;

    static crc32_loc crc32_1;
    uint32_t crc32_;

    max_len = max_len + 4;

    char byte;

    *bytes_read = 0;

    osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (osReader.hEvent == NULL)
      M_ERR_P(__LINE__);

    uint32_t cnt = 0;

    while (1) {
      if (!fWaitingOnRead) {
        if (!ReadFile(*hComm, &buffer[*bytes_read], max_len - *bytes_read, &dwRead, &osReader)) {
          if (GetLastError() != ERROR_IO_PENDING)
            M_ERR_P(__LINE__)
          else
            fWaitingOnRead = TRUE;

        } else {
          *bytes_read = *bytes_read + dwRead;

          if (*bytes_read >= max_len)
            goto parse_crc_p;
        }
      }

      DWORD dwRes;

      if (fWaitingOnRead) {
        dwRes = WaitForSingleObject(osReader.hEvent, 10);

        switch (dwRes) {
          case WAIT_OBJECT_0:

            if (!GetOverlappedResult(*hComm, &osReader, &dwRead, FALSE))
              M_ERR_P(__LINE__)

            *bytes_read = *bytes_read + dwRead;

            if (*bytes_read >= max_len)
              goto parse_crc_p;

            fWaitingOnRead = FALSE;

            break;

          case WAIT_TIMEOUT:

            cnt = cnt + 1;

            if (cnt > 5) {
              CloseHandle(osReader.hEvent);
              return 1;
            }

            break;

          default:
            M_ERR_P(__LINE__);
            break;
        }
      }
    }

  parse_crc_p:;

    CloseHandle(osReader.hEvent);

    crc32_ = crc32_1.update(buffer, max_len - 4);

    if (memcmp(&crc32_, &buffer[max_len - 4], 4) != 0)
      return 1;

    return 0;

  err_p:;

    printf("ERR: comport_read: some shit happened\n");

    return 1;
  }
};

int app_exec_command(com_port_loc *com, char *tx_b, uint64_t tx_len, char *rx_b, uint64_t rx_len) {
  char buff[256];
  uint64_t r_len = 0;

  int i = 0;

  // com->comport_read(buff, 256, &r_len);

  for (i = 0; i < 3; i++) {
    Sleep(1);

    if (!com->comport_write(tx_b, tx_len)) {
      Sleep(1);

      if (!com->comport_read(buff, rx_len, &r_len)) {
        if ((buff[0] & 0xFF) == ((tx_b[0] | 0x80) & 0xFF))
          break;
      }

    } else
      M_ERR_P(__LINE__);
  }

  if (r_len == 0)
    goto err_p;

  if (rx_b != NULL)
    memcpy(rx_b, buff, rx_len);

  return 0;

err_p:;

  // printf("ERR: app_exec_command:iter[%d]:len[%d]: some shit happened on command 0x%02X\n", i, tx_len, tx_b[0] & 0xFF);

  return 1;
}

#define APP_FPGA_VERSION

namespace ton {

#ifdef APP_FPGA_VERSION

td::optional<std::string> Miner::run(const Options &options) {
  HDataEnv H;
  std::array<td::uint8, 32> hash;
  SHA256_CTX shactx1, shactx2;

	com_port_loc com_port_loc_1;

	
  td::int64 i = 0, i0 = 0;
  char uart_tx_buff[256];
  char uart_rx_buff[256];
  uint64_t bnum = 0;
	int cores_qnt_gl = 0;

	td::Slice data;
	std::string str_;

  std::string com_num = "\\\\.\\COM" + std::to_string(options.factor) + "\\";

  printf("INFO:com_num = \"%s\"\n", com_num.c_str());

  if (com_port_loc_1.comport_init(com_num.c_str()))
    return {};

	start_p:;

	i = 0;
	i0 = 0;

  H.init(options.my_address, td::Slice(options.seed.data(), options.seed.size()));

  data = H.as_slice();
  CHECK(data.size() == 123);

  str_ = data.str();

  printf("H len[%d] = 0x", data.size());
  for (int j = 0; j < data.size(); j += 1)
    printf("%02x", str_.c_str()[j] & 0xFF);
  printf("\n");


  //---------

  uart_tx_buff[0] = 0x06;
  bnum = 1;

  if (app_exec_command(&com_port_loc_1, uart_tx_buff, bnum, NULL, 1) != 0)
    printf("INFO: no active process on fpga\n");

  //---------

  bnum = 0;

  uart_tx_buff[bnum] = 0x01;
  bnum = bnum + 1;

  memcpy(&uart_tx_buff[bnum], &H.d1, 1);
  bnum = bnum + 1;
  memcpy(&uart_tx_buff[bnum], &H.d2, 1);
  bnum = bnum + 1;

  memcpy(&uart_tx_buff[bnum], &H.body.op, 4);
  bnum = bnum + 4;

  memcpy(&uart_tx_buff[bnum], &H.body.flags, 1);
  bnum = bnum + 1;

  memcpy(&uart_tx_buff[bnum], &H.body.expire, 4);
  bnum = bnum + 4;

  memcpy(&uart_tx_buff[bnum], &H.body.myaddr, 32);
  bnum = bnum + 32;

  if (app_exec_command(&com_port_loc_1, uart_tx_buff, bnum, NULL, 1) != 0)
    return {};

  //---------

  bnum = 0;

  uart_tx_buff[bnum] = 0x02;
  bnum = bnum + 1;

  memcpy(&uart_tx_buff[bnum], &H.body.rdata1, 32);
  bnum = bnum + 32;
  memcpy(&uart_tx_buff[bnum], &H.body.pseed, 16);
  bnum = bnum + 16;

  if (app_exec_command(&com_port_loc_1, uart_tx_buff, bnum, NULL, 1) != 0)
    return {};

  //---------

  bnum = 0;

  uart_tx_buff[bnum] = 0x03;
  bnum = bnum + 1;

  memcpy(&uart_tx_buff[bnum], &H.body.rdata2, 32);
  bnum = bnum + 32;

  if (app_exec_command(&com_port_loc_1, uart_tx_buff, bnum, NULL, 1) != 0)
    return {};

  //---------

  bnum = 0;

  uart_tx_buff[bnum] = 0x04;
  bnum = bnum + 1;

  memcpy(&uart_tx_buff[bnum], options.complexity.data(), 32);
  bnum = bnum + 32;

  if (app_exec_command(&com_port_loc_1, uart_tx_buff, bnum, NULL, 1) != 0)
    return {};

  printf("complexity len[%d] = 0x", 32);
  for (int j = 0; j < 32; j += 1)
    printf("%02X", options.complexity.data()[j] & 0xFF);
  printf("\n");

  //---------

  uart_tx_buff[0] = 0x05;
  bnum = 1;
  if (app_exec_command(&com_port_loc_1, uart_tx_buff, bnum, NULL, 1) != 0)
    return {};

	

  for (; i < options.max_iterations;) {
    
		HDataEnv H_new;
    H_new = H;

		H_new.init2(options.my_address, td::Slice(options.seed.data(), options.seed.size()));
    td::Slice data_new = H_new.as_slice();

		if (memcmp(data_new.data(), data.data(), 123) != 0) {
      printf("NOT_ERR: task for fpga miner changed\n");
			// Sleep(1000);			
			goto start_p;
    }

		if (options.hashes_computed) {
      *options.hashes_computed += i - i0;
    }

    i0 = i;


    if (options.expire_at && options.expire_at.value().is_in_past(td::Timestamp::now())) {
      // printf("INFO:EXPIRED\n");
      // break;
    }

    uart_tx_buff[0] = 0x07;

    if (app_exec_command(&com_port_loc_1, uart_tx_buff, 1, uart_rx_buff, 12) == 0) {
      if ((uart_rx_buff[0] & 0xFF) == 0x87) {
        uint32_t hashes_65536_qnt;
        uint32_t cores_qnt;
        uint8_t found;

        memcpy(&hashes_65536_qnt, &uart_rx_buff[1], 4);
        memcpy(&cores_qnt, &uart_rx_buff[8], 4);
        memcpy(&found, &uart_rx_buff[7], 1);

				cores_qnt_gl = cores_qnt;

        /*
				printf("INFO: hashes_65536_qnt = %d\n", hashes_65536_qnt);
				printf("INFO: cores_qnt = %d\n", cores_qnt);
				printf("INFO: found = %d\n", found);
				printf("INFO: i = %lld\n", 65536 * hashes_65536_qnt * cores_qnt);
				*/
				

        i += 65536 * hashes_65536_qnt * cores_qnt;

        if (found == 0xFF) {
          // printf("found == 0xFF\n");
          goto found_p;
        }
      }
    }

    Sleep(1000);
  }

  return {};

found_p:;

  /*
	uart_tx_buff[0] = 0x0A;
  if (app_exec_command(&com_port_loc_1, uart_tx_buff, 1, uart_rx_buff, 33) == 0) {
    printf("GOT SHA256\n");
    printf("SHA256[%d] = 0x", 32);
    for (int j = 1; j < 33; j += 1)
      printf("%02X", uart_rx_buff[j] & 0xFF);
    printf("\n");
  } else {
  
		printf("ERROR ON GOT SHA256\n");
	
	}
	*/

  uart_tx_buff[0] = 0x08;
  if (app_exec_command(&com_port_loc_1, uart_tx_buff, 1, uart_rx_buff, 33) == 0) {
    // printf("GOT RDATA 1\n");
    memcpy(H.body.rdata1, &uart_rx_buff[1], 32);
  }

  uart_tx_buff[0] = 0x09;
  if (app_exec_command(&com_port_loc_1, uart_tx_buff, 1, uart_rx_buff, 33) == 0) {
    // printf("GOT RDATA 2\n");
    memcpy(H.body.rdata2, &uart_rx_buff[1], 32);
  }

	for ( int cq = 0; cq < cores_qnt_gl; cq++ ) {

		char rdata[64] = {0x00000000};

		memcpy(&rdata[0], H.body.rdata1, 32);
		memcpy(&rdata[32], H.body.rdata2, 32);

		/*
		printf("rdata_norm[%d] = 0x", 64);
		for (int j = 0; j < 64; j += 1)
			printf("%02X", rdata[j] & 0xFF);
		printf("\n");
		*/

	
		for (long k = 63; k >= 0; k--) {
			if ((rdata[k] & 0xFF) != 0x00) {
				rdata[k] = ((rdata[k] & 0xFF) - 1) & 0xFF;
				break;
			} else {
				rdata[k] = 0xFF;
			}
		}
	

		/*
		printf("rdata_decr[%d] = 0x", 64);
		for (int j = 0; j < 64; j += 1)
			printf("%02X", rdata[j] & 0xFF);
		printf("\n");
		*/

		memcpy(H.body.rdata1, &rdata[0], 32);
		memcpy(H.body.rdata2, &rdata[32], 32);

		/*
		printf("H.body.rdata1[%d] = 0x", 32);
		for (int j = 0; j < 32; j += 1)
			printf("%02X", H.body.rdata1[j] & 0xFF);
		printf("\n");
		*/

		data = H.as_slice();
		
		auto head = data.substr(0, 72);
		auto tail = data.substr(72);

		SHA256_Init(&shactx1);
		SHA256_Update(&shactx1, head.ubegin(), head.size());
		shactx2 = shactx1;
		SHA256_Update(&shactx2, tail.ubegin(), tail.size());
		SHA256_Final(hash.data(), &shactx2);

		if (memcmp(hash.data(), options.complexity.data(), 32) < 0) {
			break;
		}

	}

	data = H.as_slice();

  printf("FOUND:H[%d] = 0x", data.size());
  for (int j = 0; j < data.size(); j += 1)
    printf("%02X", data.data()[j] & 0xFF);
  printf("\n");

  auto head = data.substr(0, 72);
  auto tail = data.substr(72);

  SHA256_Init(&shactx1);
  SHA256_Update(&shactx1, head.ubegin(), head.size());
  shactx2 = shactx1;
  SHA256_Update(&shactx2, tail.ubegin(), tail.size());
  SHA256_Final(hash.data(), &shactx2);

  printf("FOUND:hash[%d] = 0x", hash.size());
  for (int j = 0; j < hash.size(); j += 1)
    printf("%02X", hash.data()[j] & 0xFF);
  printf("\n");

  if (memcmp(hash.data(), options.complexity.data(), 32) < 0) {
    printf("SUCCESSFULL FOUND\n");
    return H.body.as_slice().str();
  } else {
    printf("ERROR FOUND\n");
    return {};
  }

}

#endif

#ifndef APP_FPGA_VERSION

td::optional<std::string> Miner::run(const Options &options) {
  HDataEnv H;
  H.init(options.my_address, td::Slice(options.seed.data(), options.seed.size()));

  td::Slice data = H.as_slice();
  CHECK(data.size() == 123);

  constexpr size_t prefix_size = 72;
  constexpr size_t guard_pos = prefix_size - (72 - 28);
  CHECK(0 <= guard_pos && guard_pos < 32);
  size_t got_prefix_size = (const unsigned char *)H.body.rdata1 + guard_pos + 1 - (const unsigned char *)&H;
  CHECK(prefix_size == got_prefix_size);

  auto head = data.substr(0, prefix_size);
  auto tail = data.substr(prefix_size);

  SHA256_CTX shactx1, shactx2;
  std::array<td::uint8, 32> hash;
  SHA256_Init(&shactx1);
  auto guard = head.back();

  td::int64 i = 0, i0 = 0;
  for (; i < options.max_iterations; i++) {
    if (!(i & 0xfffff) || head.back() != guard) {
      if (options.token_) {
        break;
      }
      if (options.hashes_computed) {
        *options.hashes_computed += i - i0;
      }
      i0 = i;
      if (options.expire_at && options.expire_at.value().is_in_past(td::Timestamp::now())) {
        break;
      }
      H.body.set_expire((unsigned)td::Clocks::system() + 900);
      guard = head.back();
      SHA256_Init(&shactx1);
      SHA256_Update(&shactx1, head.ubegin(), head.size());
    }
    shactx2 = shactx1;
    SHA256_Update(&shactx2, tail.ubegin(), tail.size());
    SHA256_Final(hash.data(), &shactx2);

    if (memcmp(hash.data(), options.complexity.data(), 32) < 0) {
      // FOUND
      if (options.hashes_computed) {
        *options.hashes_computed += i - i0;
      }
      return H.body.as_slice().str();
    }
    H.body.inc();
  }
  if (options.hashes_computed) {
    *options.hashes_computed += i - i0;
  }
  return {};
}

#endif

double Miner::print_stats(std::string status, td::Timestamp start_at, td::uint64 hashes_computed, double instant_passed,
                          td::uint64 instant_hashes_computed) {
  auto passed = td::Timestamp::now().at() - start_at.at();
  if (passed < 1e-9) {
    passed = 1;
  }
  double speed = static_cast<double>(hashes_computed) / passed;
  std::stringstream ss, ss2;
  ss << std::fixed << std::setprecision(3) << speed / 1e+6;

  if (instant_passed < 1e-9) {
    instant_passed = 1;
  }
  double instant_speed = static_cast<double>(instant_hashes_computed) / instant_passed;
  ss2 << std::fixed << std::setprecision(3) << instant_speed / 1e+6;

  LOG(INFO) << "[ " << status << ", passed: " << td::format::as_time(passed) << ", hashes computed: " << hashes_computed
            << ", instant speed: " << ss2.str() << " Mhash/s, average speed: " << ss.str() << " Mhash/s ]";

  return speed;
};

void Miner::write_stats(std::string filename, const ton::Miner::Options &options, std::string giver) {
  if (!filename.length()) {
    return;
  }
  auto passed = td::Timestamp::now().at() - options.start_at.at();
  if (passed < 1e-9) {
    passed = 1;
  }
  double hashes_computed = options.hashes_computed ? static_cast<double>(*options.hashes_computed) : 0;
  double speed = hashes_computed / passed;
  std::stringstream ss, ss2;
  ss << std::fixed << std::setprecision(3) << speed / 1e+6;

  double instant_passed = 1;
  if (options.instant_passed) {
    instant_passed = *options.instant_passed;
  }
  if (instant_passed < 1e-9) {
    instant_passed = 1;
  }

  double instant_hashes_computed =
      options.instant_hashes_computed ? static_cast<double>(*options.instant_hashes_computed) : 0;
  double instant_speed = instant_hashes_computed / instant_passed;
  ss2 << std::fixed << std::setprecision(3) << instant_speed / 1e+6;

  td::JsonBuilder jb;
  auto jo = jb.enter_object();
  jo("timestamp", std::to_string(td::Timestamp::now().at_unix()));
  jo("giver", giver);
  jo("seed", hex_encode(td::Slice(options.seed.data(), options.seed.size())));
  jo("complexity", hex_encode(td::Slice(options.complexity.data(), options.complexity.size())));
  jo("passed", std::to_string(passed));
  jo("hashes_computed", std::to_string(hashes_computed));
  jo("speed", ss.str());
  jo("instant_passed", std::to_string(instant_passed));
  jo("instant_hashes_computed", std::to_string(instant_hashes_computed));
  jo("instant_speed", ss2.str());
  jo.leave();
  auto s = jb.string_builder().as_cslice();
  auto S = td::write_file(filename, s);
  if (S.is_error()) {
    LOG(ERROR) << S.move_as_error();
  }
}

td::optional<std::string> build_mine_result(int cpu_id, ton::HDataEnv H, const ton::Miner::Options &options,
                                            unsigned char *rdata, uint64_t nonce, uint64_t vcpu, uint32_t expired) {
  printf("INFORMATION: build_mine_result called\n");

  //    std::cout << cpu_id << ": "<< "rdata[" << vcpu << "]: ";
  //    for (int i = 0; i < 32; i++) {
  //      printf("%02x", rdata[32 * vcpu + i]);
  //    }
  //    std::cout << std::endl;

  // read last 8 bytes of rdata1
  uint64_t rdata1 = (uint64_t)rdata[32 * vcpu + 24] << (8 * 7) | (uint64_t)rdata[32 * vcpu + 25] << (8 * 6) |
                    (uint64_t)rdata[32 * vcpu + 26] << (8 * 5) | (uint64_t)rdata[32 * vcpu + 27] << (8 * 4) |
                    (uint64_t)rdata[32 * vcpu + 28] << (8 * 3) | (uint64_t)rdata[32 * vcpu + 29] << (8 * 2) |
                    (uint64_t)rdata[32 * vcpu + 30] << (8 * 1) | (uint64_t)rdata[32 * vcpu + 31];

  rdata1 += nonce;  // add nonce

  // write rdata1
  for (int i = 0; i <= 23; i++) {
    H.body.rdata1[i] = rdata[32 * vcpu + i];
  }
  H.body.rdata1[24] = (uint8_t)(rdata1 >> 7 * 8);
  H.body.rdata1[25] = (uint8_t)(rdata1 >> 6 * 8);
  H.body.rdata1[26] = (uint8_t)(rdata1 >> 5 * 8);
  H.body.rdata1[27] = (uint8_t)(rdata1 >> 4 * 8);
  H.body.rdata1[28] = (uint8_t)(rdata1 >> 3 * 8);
  H.body.rdata1[29] = (uint8_t)(rdata1 >> 2 * 8);
  H.body.rdata1[30] = (uint8_t)(rdata1 >> 1 * 8);
  H.body.rdata1[31] = (uint8_t)(rdata1);
  // write back rdata2
  std::memcpy(H.body.rdata2, H.body.rdata1, 32);

  // set expire
  H.body.set_expire(expired);

  // check solution
  SHA256_CTX shactx1;
  td::Slice data = H.as_slice();
  std::array<td::uint8, 32> hash;
  SHA256_Init(&shactx1);
  SHA256_Update(&shactx1, data.ubegin(), data.size());
  SHA256_Final(hash.data(), &shactx1);

  if (memcmp(hash.data(), options.complexity.data(), 32) < 0) {
    LOG(ERROR) << "FOUND! GPU ID: " << options.gpu_id << ", nonce=" << nonce << ", expired=" << expired;

    printf("FOUND : H[%d:%d:%lu]: H0=%08x H1=%08x H2=%08x H3=%08x H4=%08x H5=%08x H6=%08x H7=%08x\n", cpu_id, vcpu,
           nonce, *((uint32_t *)&hash.data()[0]), *((uint32_t *)&hash.data()[4]), *((uint32_t *)&hash.data()[8]),
           *((uint32_t *)&hash.data()[12]), *((uint32_t *)&hash.data()[16]), *((uint32_t *)&hash.data()[20]),
           *((uint32_t *)&hash.data()[24]), *((uint32_t *)&hash.data()[28]));

    return H.body.as_slice().str();
  } else {
    for (int i = 0; i < 32; i += 4) {
      printf("H%d = 0x%02x%02x%02x%02x\n", i / 4, hash.data()[i], hash.data()[i + 1], hash.data()[i + 2],
             hash.data()[i + 3]);
    }

    LOG(ERROR) << "OVERCLOCK DETECTED! GPU ID: " << options.gpu_id;
  }
  return {};
}
}  // namespace ton
