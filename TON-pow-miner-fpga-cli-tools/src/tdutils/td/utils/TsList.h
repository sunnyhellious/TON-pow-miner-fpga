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
#include "td/utils/List.h"

#include <mutex>

namespace td {

template <class DataT>
class TsList;

template <class DataT>
class TsListNode : protected ListNode {
 public:
  TsListNode() {
    clear();
  }
  explicit TsListNode(DataT &&data) : data_(std::move(data)) {
    clear();
  }

  ~TsListNode() {
    remove();
  }

  std::unique_lock<std::mutex> lock() TD_WARN_UNUSED_RESULT;

  TsListNode(const TsListNode &) = delete;
  TsListNode &operator=(const TsListNode &) = delete;

  TsListNode(TsListNode &&other) {
    other.validate();
    if (other.empty()) {
      data_ = std::move(other.data_);
      clear();
    } else {
      auto guard = other.lock();
      init_from(std::move(other));
    }
    validate();
    other.validate();
  }

  TsListNode &operator=(TsListNode &&other) {
    validate();
    if (this == &other) {
      return *this;
    }
    other.validate();
    remove();

    if (other.empty()) {
      data_ = std::move(other.data_);
    } else {
      auto guard = other.lock();
      init_from(std::move(other));
    }

    validate();
    other.validate();
    return *this;
  }

  void validate() {
    CHECK(empty() || !ListNode::empty() || is_root);
    CHECK(!empty() || ListNode::empty());
  }

  void remove() {
    validate();
    if (is_root) {
      CHECK(ListNode::empty());
      return;
    }
    if (empty()) {
      CHECK(ListNode::empty());
      return;
    }
    {
      auto guard = lock();
      ListNode::remove();
      if (!is_root) {
        parent = nullptr;
      }
    }
    validate();
  }

  void put(TsListNode *other) {
    validate();
    other->validate();
    DCHECK(other->empty());
    DCHECK(!empty());
    DCHECK(!other->is_root);
    {
      auto guard = lock();
      ListNode::put(other);
      other->parent = parent;
    }
    validate();
    other->validate();
  }

  void put_back(TsListNode *other) {
    DCHECK(other->empty());
    DCHECK(!empty());
    DCHECK(!other->is_root);
    auto guard = lock();
    ListNode::put_back(other);
    other->parent = parent;
  }

  bool empty() const {
    return parent == nullptr;
  }

  TsListNode *get_next() {
    return static_cast<TsListNode *>(next);
  }
  TsListNode *get_prev() {
    return static_cast<TsListNode *>(prev);
  }

  DataT &get_data_unsafe() {
    return data_;
  }

 private:
  TsList<DataT> *parent;
  bool is_root{false};
  DataT data_;

  friend class TsList<DataT>;

  void clear() {
    ListNode::clear();
    if (!is_root) {
      parent = nullptr;
    }
  }

  void init_from(TsListNode &&other) {
    ListNode::init_from(std::move(other));
    parent = other.parent;
    other.parent = nullptr;
    data_ = std::move(other.data_);
  }
};

template <class DataT>
class TsList : public TsListNode<DataT> {
 public:
  TsList() {
    this->parent = this;
    this->is_root = true;
  }
  TsList(const TsList &) = delete;
  TsList &operator=(const TsList &) = delete;
  TsList(TsList &&) = delete;
  TsList &operator=(TsList &&) = delete;
  ~TsList() {
    CHECK(ListNode::empty());
    this->parent = nullptr;
  }
  std::unique_lock<std::mutex> lock() TD_WARN_UNUSED_RESULT {
    return std::unique_lock<std::mutex>(mutex_);
  }
  TsListNode<DataT> *begin() {
    return this->get_next();
  }
  TsListNode<DataT> *end() {
    return this;
  }
  TsListNode<DataT> *get() {
    auto guard = lock();
    auto res = static_cast<TsListNode<DataT> *>(ListNode::get());
    if (res) {
      res->parent = nullptr;
    }
    return res;
  }

 private:
  std::mutex mutex_;
};

template <class DataT>
std::unique_lock<std::mutex> TsListNode<DataT>::lock() {
  CHECK(parent != nullptr);
  return parent->lock();
}

}  // namespace td
