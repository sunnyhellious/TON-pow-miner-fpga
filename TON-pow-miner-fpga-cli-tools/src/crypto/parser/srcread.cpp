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
#include "srcread.h"
#include <algorithm>

namespace src {

/*
 *
 *   SOURCE FILE READER
 *
 */

std::ostream& operator<<(std::ostream& os, const FileDescr* fdescr) {
  return os << (fdescr ? (fdescr->is_stdin ? "stdin" : fdescr->filename) : "unknown-location");
}

std::ostream& operator<<(std::ostream& os, const Fatal& fatal) {
  return os << fatal.get_msg();
}

const char* FileDescr::convert_offset(long offset, long* line_no, long* line_pos, long* line_size) const {
  long lno = 0, lpos = -1, lsize = 0;
  const char* lstart = nullptr;
  if (offset >= 0 && offset < (long)text.size()) {
    auto it = std::upper_bound(line_offs.begin(), line_offs.end(), offset);
    lno = it - line_offs.begin();
    if (lno && it != line_offs.end()) {
      lsize = it[0] - it[-1];
      lpos = offset - it[-1];
      lstart = text.data() + it[-1];
    }
  } else {
    lno = (long)line_offs.size();
  }
  if (line_no) {
    *line_no = lno;
  }
  if (line_pos) {
    *line_pos = lpos;
  }
  if (line_size) {
    *line_size = lsize;
  }
  return lstart;
}

const char* FileDescr::push_line(std::string new_line) {
  if (line_offs.empty()) {
    line_offs.push_back(0);
  }
  std::size_t cur_size = text.size();
  text += new_line;
  text += '\0';
  line_offs.push_back((long)text.size());
  return text.data() + cur_size;
}

void SrcLocation::show(std::ostream& os) const {
  os << fdescr;
  long line_no, line_pos;
  if (fdescr && convert_pos(&line_no, &line_pos)) {
    os << ':' << line_no;
    if (line_pos >= 0) {
      os << ':' << (line_pos + 1);
    }
  }
}

bool SrcLocation::show_context(std::ostream& os) const {
  long line_no, line_pos, line_size;
  if (!fdescr || !convert_pos(&line_no, &line_pos, &line_size)) {
    return false;
  }
  bool skip_left = (line_pos > 200), skip_right = (line_pos + 200u < line_size);
  const char* here = fdescr->text.data() + char_offs;
  const char* base = here - line_pos;
  const char* start = skip_left ? here - 100 : base;
  const char* end = skip_right ? here + 100 : base + line_size;
  os << "  ";
  if (skip_left) {
    os << "... ";
  }
  for (const char* ptr = start; ptr < end; ptr++) {
    os << (char)*ptr;
  }
  if (skip_right) {
    os << " ...";
  }
  os << std::endl;
  os << "  ";
  if (skip_left) {
    os << "... ";
  }
  for (const char* ptr = start; ptr < here; ptr++) {
    char c = *ptr;
    os << (c == 9 || c == 10 ? c : ' ');
  }
  os << '^' << std::endl;
  return true;
}

std::ostream& operator<<(std::ostream& os, const SrcLocation& loc) {
  loc.show(os);
  return os;
}

void SrcLocation::show_gen_error(std::ostream& os, std::string message, std::string err_type) const {
  show(os);
  if (!err_type.empty()) {
    os << ": " << err_type;
  }
  os << ": " << message << std::endl;
  show_context(os);
}

std::ostream& operator<<(std::ostream& os, const Error& error) {
  error.show(os);
  return os;
}

void ParseError::show(std::ostream& os) const {
  os << where << ": error: " << message << std::endl;
  where.show_context(os);
}

SourceReader::SourceReader(std::istream* _is, FileDescr* _fdescr)
    : ifs(_is), fdescr(_fdescr), loc(_fdescr), eof(false), cur_line_len(0), start(0), cur(0), end(0) {
  load_line();
}

void SourceReader::set_eof() {
  if (!eof) {
    eof = true;
    start = cur = end = 0;
  }
}

int SourceReader::skip_spc() {
  if (!cur) {
    return 0;
  }
  const char* ptr = cur;
  int res = 0;
  while (*ptr == ' ' || *ptr == 9) {
    ++ptr;
    ++res;
  }
  set_ptr(ptr);
  return res;
}

bool SourceReader::seek_eof() {
  while (seek_eoln()) {
    if (!load_line()) {
      return true;
    }
  }
  return false;
}

const char* SourceReader::set_ptr(const char* ptr) {
  if (ptr != cur) {
    if (ptr < cur || ptr > end) {
      error("parsing position went outside of line");
    }
    loc.char_offs += ptr - cur;
    cur = ptr;
  }
  return ptr;
}

bool SourceReader::load_line() {
  if (eof) {
    return false;
  }
  loc.set_eof();
  if (ifs->eof()) {
    set_eof();
    return false;
  }
  std::getline(*ifs, cur_line);
  if (ifs->fail()) {
    set_eof();
    if (!ifs->eof()) {
      error("cannot read line from source stream");
    }
    return false;
  }
  std::size_t len = cur_line.size();
  if (len > 0xffffff) {
    set_eof();
    error("line too long");
    return false;
  }
  if (len && cur_line.back() == '\r') {
    // CP/M line breaks support
    cur_line.pop_back();
    --len;
  }
  cur_line_len = (int)len;
  if (fdescr) {
    cur = start = fdescr->push_line(std::move(cur_line));
    end = start + len;
    loc.char_offs = (std::size_t)(cur - fdescr->text.data());
    cur_line.clear();
  } else {
    cur = start = cur_line.c_str();
    end = start + cur_line_len;
  }
  return true;
}

}  // namespace src
