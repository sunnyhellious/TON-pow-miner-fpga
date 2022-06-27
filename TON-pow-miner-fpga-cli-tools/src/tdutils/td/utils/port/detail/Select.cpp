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
#include "td/utils/port/detail/Select.h"

char disable_linker_warning_about_empty_file_select_cpp TD_UNUSED;

#ifdef TD_POLL_SELECT

#include "td/utils/logging.h"

#include <utility>

namespace td {
namespace detail {

void Select::init() {
  FD_ZERO(&all_fd_);
  FD_ZERO(&read_fd_);
  FD_ZERO(&write_fd_);
  FD_ZERO(&except_fd_);
  max_fd_ = -1;
}

void Select::clear() {
  fds_.clear();
}

void Select::subscribe(PollableFd fd, PollFlags flags) {
  int native_fd = fd.native_fd().fd();
  for (auto &it : fds_) {
    CHECK(it.fd.native_fd().fd() != native_fd);
  }
  fds_.push_back(FdInfo{std::move(fd), flags});
  LOG_CHECK(0 <= native_fd && native_fd < FD_SETSIZE) << native_fd << " " << FD_SETSIZE;
  FD_SET(native_fd, &all_fd_);
  if (native_fd > max_fd_) {
    max_fd_ = native_fd;
  }
}

void Select::unsubscribe(PollableFdRef fd) {
  auto fd_locked = fd.lock();
  int native_fd = fd_locked.native_fd().fd();
  fd_locked.release_as_list_node();

  LOG_CHECK(0 <= native_fd && native_fd < FD_SETSIZE) << native_fd << " " << FD_SETSIZE;
  FD_CLR(native_fd, &all_fd_);
  FD_CLR(native_fd, &read_fd_);
  FD_CLR(native_fd, &write_fd_);
  FD_CLR(native_fd, &except_fd_);
  while (max_fd_ >= 0 && !FD_ISSET(max_fd_, &all_fd_)) {
    max_fd_--;
  }
  for (auto it = fds_.begin(); it != fds_.end();) {
    if (it->fd.native_fd().fd() == native_fd) {
      std::swap(*it, fds_.back());
      fds_.pop_back();
      break;
    } else {
      ++it;
    }
  }
}

void Select::unsubscribe_before_close(PollableFdRef fd) {
  unsubscribe(fd);
}

void Select::run(int timeout_ms) {
  timeval timeout_data;
  timeval *timeout_ptr;
  if (timeout_ms == -1) {
    timeout_ptr = nullptr;
  } else {
    timeout_data.tv_sec = timeout_ms / 1000;
    timeout_data.tv_usec = timeout_ms % 1000 * 1000;
    timeout_ptr = &timeout_data;
  }

  for (auto &it : fds_) {
    int native_fd = it.fd.native_fd().fd();
    PollFlags fd_flags = it.fd.get_flags_unsafe();  // concurrent calls are UB
    if (it.flags.can_write() && !fd_flags.can_write()) {
      FD_SET(native_fd, &write_fd_);
    } else {
      FD_CLR(native_fd, &write_fd_);
    }
    if (it.flags.can_read() && !fd_flags.can_read()) {
      FD_SET(native_fd, &read_fd_);
    } else {
      FD_CLR(native_fd, &read_fd_);
    }
    FD_SET(native_fd, &except_fd_);
  }

  select(max_fd_ + 1, &read_fd_, &write_fd_, &except_fd_, timeout_ptr);
  for (auto &it : fds_) {
    int native_fd = it.fd.native_fd().fd();
    PollFlags flags;
    if (FD_ISSET(native_fd, &read_fd_)) {
      flags = flags | PollFlags::Read();
    }
    if (FD_ISSET(native_fd, &write_fd_)) {
      flags = flags | PollFlags::Write();
    }
    if (FD_ISSET(native_fd, &except_fd_)) {
      flags = flags | PollFlags::Error();
    }
    it.fd.add_flags(flags);
  }
}

}  // namespace detail
}  // namespace td

#endif
