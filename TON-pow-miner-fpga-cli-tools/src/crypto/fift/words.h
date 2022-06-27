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
#pragma once
#include "Dictionary.h"

namespace fift {

void init_words_common(Dictionary& dictionary);
void init_words_vm(Dictionary& dictionary, bool debug_enabled = false);
void init_words_ton(Dictionary& dictionary);

void import_cmdline_args(Dictionary& d, std::string arg0, int n, const char* const argv[]);

}  // namespace fift
