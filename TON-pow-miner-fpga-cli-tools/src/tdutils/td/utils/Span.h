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

#include "td/utils/common.h"

#include <array>
#include <iterator>

namespace td {

namespace detail {
template <class T, class InnerT>
class SpanImpl {
  InnerT *data_{nullptr};
  size_t size_{0};

 public:
  SpanImpl() = default;
  SpanImpl(InnerT *data, size_t size) : data_(data), size_(size) {
  }
  SpanImpl(InnerT &data) : SpanImpl(&data, 1) {
  }

  template <class OtherInnerT>
  SpanImpl(const SpanImpl<T, OtherInnerT> &other) : SpanImpl(other.data(), other.size()) {
  }

  template <size_t N>
  SpanImpl(const std::array<T, N> &arr) : SpanImpl(arr.data(), arr.size()) {
  }
  template <size_t N>
  SpanImpl(std::array<T, N> &arr) : SpanImpl(arr.data(), arr.size()) {
  }
  template <size_t N>
  SpanImpl(const T (&arr)[N]) : SpanImpl(arr, N) {
  }
  template <size_t N>
  SpanImpl(T (&arr)[N]) : SpanImpl(arr, N) {
  }
  SpanImpl(const vector<T> &v) : SpanImpl(v.data(), v.size()) {
  }
  SpanImpl(vector<T> &v) : SpanImpl(v.data(), v.size()) {
  }

  template <class OtherInnerT>
  SpanImpl &operator=(const SpanImpl<T, OtherInnerT> &other) {
    SpanImpl copy{other};
    *this = copy;
  }
  template <class OtherInnerT>
  bool operator==(const SpanImpl<T, OtherInnerT> &other) const {
    if (size() != other.size()) {
      return false;
    }
    for (size_t i = 0; i < size(); i++) {
      if (!((*this)[i] == other[i])) {
        return false;
      }
    }
    return true;
  }

  InnerT &operator[](size_t i) {
    DCHECK(i < size());
    return data_[i];
  }

  const InnerT &operator[](size_t i) const {
    DCHECK(i < size());
    return data_[i];
  }

  InnerT &back() {
    DCHECK(!empty());
    return data_[size() - 1];
  }

  const InnerT &back() const {
    DCHECK(!empty());
    return data_[size() - 1];
  }

  InnerT &front() {
    DCHECK(!empty());
    return data_[0];
  }

  const InnerT &front() const {
    DCHECK(!empty());
    return data_[0];
  }

  InnerT *data() const {
    return data_;
  }

  InnerT *begin() const {
    return data_;
  }
  InnerT *end() const {
    return data_ + size_;
  }
  std::reverse_iterator<InnerT *> rbegin() const {
    return std::reverse_iterator<InnerT *>(end());
  }
  std::reverse_iterator<InnerT *> rend() const {
    return std::reverse_iterator<InnerT *>(begin());
  }

  size_t size() const {
    return size_;
  }
  bool empty() const {
    return size() == 0;
  }

  SpanImpl &truncate(size_t size) {
    if (size < size_) {
      size_ = size;
    }
    return *this;
  }

  SpanImpl substr(size_t offset) const {
    CHECK(offset <= size_);
    return SpanImpl(begin() + offset, size_ - offset);
  }
  SpanImpl substr(size_t offset, size_t size) const {
    CHECK(offset <= size_);
    CHECK(size_ - offset >= size);
    return SpanImpl(begin() + offset, size);
  }
};
}  // namespace detail

template <class T>
using Span = detail::SpanImpl<T, const T>;

template <class T>
using MutableSpan = detail::SpanImpl<T, T>;

template <class T>
Span<T> span(const T *ptr, size_t size) {
  return Span<T>(ptr, size);
}
template <class T>
Span<T> span(const std::vector<T> &vec) {
  return Span<T>(vec);
}

template <class T>
MutableSpan<T> mutable_span(T *ptr, size_t size) {
  return MutableSpan<T>(ptr, size);
}
template <class T>
MutableSpan<T> mutable_span(std::vector<T> &vec) {
  return MutableSpan<T>(vec);
}

template <class T>
Span<T> span_one(const T &value) {
  return td::Span<T>(&value, 1);
}
template <class T>
MutableSpan<T> mutable_span_one(T &value) {
  return td::MutableSpan<T>(&value, 1);
}

template <class T>
Span<T> as_span(Span<T> span) {
  return span;
}
template <class T>
Span<T> as_span(const std::vector<T> &vec) {
  return Span<T>(vec);
}

template <class T>
MutableSpan<T> as_mutable_span(MutableSpan<T> span) {
  return span;
}
template <class T>
MutableSpan<T> as_mutable_span(std::vector<T> &vec) {
  return MutableSpan<T>(vec);
}

}  // namespace td
