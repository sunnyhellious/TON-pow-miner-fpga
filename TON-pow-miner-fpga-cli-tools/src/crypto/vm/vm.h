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

#include "common/refcnt.hpp"
#include "vm/cellslice.h"
#include "vm/stack.hpp"
#include "vm/vmstate.h"
#include "vm/log.h"
#include "vm/continuation.h"
#include "td/utils/HashSet.h"

namespace vm {

using td::Ref;
struct GasLimits {
  static constexpr long long infty = (1ULL << 63) - 1;
  long long gas_max, gas_limit, gas_credit, gas_remaining, gas_base;
  GasLimits() : gas_max(infty), gas_limit(infty), gas_credit(0), gas_remaining(infty), gas_base(infty) {
  }
  GasLimits(long long _limit, long long _max = infty, long long _credit = 0)
      : gas_max(_max)
      , gas_limit(_limit)
      , gas_credit(_credit)
      , gas_remaining(_limit + _credit)
      , gas_base(gas_remaining) {
  }
  long long gas_consumed() const {
    return gas_base - gas_remaining;
  }
  void set_limits(long long _max, long long _limit, long long _credit = 0);
  void change_base(long long _base) {
    gas_remaining += _base - gas_base;
    gas_base = _base;
  }
  void change_limit(long long _limit);
  void consume(long long amount) {
    // LOG(DEBUG) << "consume " << amount << " gas (" << gas_remaining << " remaining)";
    gas_remaining -= amount;
  }
  bool try_consume(long long amount) {
    // LOG(DEBUG) << "try consume " << amount << " gas (" << gas_remaining << " remaining)";
    return (gas_remaining -= amount) >= 0;
  }
  void gas_exception() const;
  void gas_exception(bool cond) const {
    if (!cond) {
      gas_exception();
    }
  }
  void consume_chk(long long amount) {
    gas_exception(try_consume(amount));
  }
  void check() const {
    gas_exception(gas_remaining >= 0);
  }
  bool final_ok() const {
    return gas_remaining >= gas_credit;
  }
};

struct CommittedState {
  Ref<vm::Cell> c4, c5;
  bool committed{false};
};

class VmState final : public VmStateInterface {
  Ref<CellSlice> code;
  Ref<Stack> stack;
  ControlRegs cr;
  CommittedState cstate;
  int cp;
  long long steps{0};
  const DispatchTable* dispatch;
  Ref<QuitCont> quit0, quit1;
  VmLog log;
  GasLimits gas;
  std::vector<Ref<Cell>> libraries;
  td::HashSet<CellHash> loaded_cells;
  td::int64 loaded_cells_count{0};
  int stack_trace{0}, debug_off{0};
  bool chksig_always_succeed{false};

 public:
  enum {
    cell_load_gas_price = 100,
    cell_reload_gas_price = 25,
    cell_create_gas_price = 500,
    exception_gas_price = 50,
    tuple_entry_gas_price = 1,
    implicit_jmpref_gas_price = 10,
    implicit_ret_gas_price = 5,
    free_stack_depth = 32,
    stack_entry_gas_price = 1,
    max_data_depth = 512
  };
  VmState();
  VmState(Ref<CellSlice> _code);
  VmState(Ref<CellSlice> _code, Ref<Stack> _stack, int flags = 0, Ref<Cell> _data = {}, VmLog log = {},
          std::vector<Ref<Cell>> _libraries = {}, Ref<Tuple> init_c7 = {});
  VmState(Ref<CellSlice> _code, Ref<Stack> _stack, const GasLimits& _gas, int flags = 0, Ref<Cell> _data = {},
          VmLog log = {}, std::vector<Ref<Cell>> _libraries = {}, Ref<Tuple> init_c7 = {});
  template <typename... Args>
  VmState(Ref<Cell> code_cell, Args&&... args)
      : VmState(convert_code_cell(std::move(code_cell)), std::forward<Args>(args)...) {
  }
  VmState(const VmState&) = delete;
  VmState(VmState&&) = delete;
  VmState& operator=(const VmState&) = delete;
  VmState& operator=(VmState&&) = delete;
  bool set_gas_limits(long long _max, long long _limit, long long _credit = 0);
  bool final_gas_ok() const {
    return gas.final_ok();
  }
  long long gas_consumed() const {
    return gas.gas_consumed();
  }
  bool committed() const {
    return cstate.committed;
  }
  const CommittedState& get_committed_state() const {
    return cstate;
  }
  void consume_gas(long long amount) {
    gas.consume(amount);
  }
  void consume_tuple_gas(unsigned tuple_len) {
    consume_gas(tuple_len * tuple_entry_gas_price);
  }
  void consume_tuple_gas(const Ref<Tuple>& tup) {
    if (tup.not_null()) {
      consume_tuple_gas((unsigned)tup->size());
    }
  }
  void consume_stack_gas(unsigned stack_depth) {
    consume_gas((std::max(stack_depth, (unsigned)free_stack_depth) - free_stack_depth) * stack_entry_gas_price);
  }
  void consume_stack_gas(const Ref<Stack>& stk) {
    if (stk.not_null()) {
      consume_stack_gas((unsigned)stk->depth());
    }
  }
  GasLimits get_gas_limits() const {
    return gas;
  }
  void change_gas_limit(long long new_limit);
  template <typename... Args>
  void check_underflow(Args... args) {
    stack->check_underflow(args...);
  }
  bool register_library_collection(Ref<Cell> lib);
  Ref<Cell> load_library(
      td::ConstBitPtr hash) override;  // may throw a dictionary exception; returns nullptr if library is not found
  void register_cell_load(const CellHash& cell_hash) override;
  void register_cell_create() override;
  bool init_cp(int new_cp);
  bool set_cp(int new_cp);
  void force_cp(int new_cp);
  int get_cp() const {
    return cp;
  }
  int incr_stack_trace(int v) {
    return stack_trace += v;
  }
  long long get_steps_count() const {
    return steps;
  }
  td::BitArray<256> get_state_hash() const;
  td::BitArray<256> get_final_state_hash(int exit_code) const;
  int step();
  int run();
  Stack& get_stack() {
    return stack.write();
  }
  const Stack& get_stack_const() const {
    return *stack;
  }
  Ref<Stack> get_stack_ref() const {
    return stack;
  }
  Ref<Continuation> get_c0() const {
    return cr.c[0];
  }
  Ref<Continuation> get_c1() const {
    return cr.c[1];
  }
  Ref<Continuation> get_c2() const {
    return cr.c[2];
  }
  Ref<Continuation> get_c3() const {
    return cr.c[3];
  }
  Ref<Cell> get_c4() const {
    return cr.d[0];
  }
  Ref<Tuple> get_c7() const {
    return cr.c7;
  }
  Ref<Continuation> get_c(unsigned idx) const {
    return cr.get_c(idx);
  }
  Ref<Cell> get_d(unsigned idx) const {
    return cr.get_d(idx);
  }
  StackEntry get(unsigned idx) const {
    return cr.get(idx);
  }
  const VmLog& get_log() const {
    return log;
  }
  void define_c0(Ref<Continuation> cont) {
    cr.define_c0(std::move(cont));
  }
  void set_c0(Ref<Continuation> cont) {
    cr.set_c0(std::move(cont));
  }
  void set_c1(Ref<Continuation> cont) {
    cr.set_c1(std::move(cont));
  }
  void set_c2(Ref<Continuation> cont) {
    cr.set_c2(std::move(cont));
  }
  bool set_c(unsigned idx, Ref<Continuation> val) {
    return cr.set_c(idx, std::move(val));
  }
  bool set_d(unsigned idx, Ref<Cell> val) {
    return cr.set_d(idx, std::move(val));
  }
  void set_c4(Ref<Cell> val) {
    cr.set_c4(std::move(val));
  }
  bool set_c7(Ref<Tuple> val) {
    return cr.set_c7(std::move(val));
  }
  bool set(unsigned idx, StackEntry val) {
    return cr.set(idx, std::move(val));
  }
  void set_stack(Ref<Stack> new_stk) {
    stack = std::move(new_stk);
  }
  Ref<Stack> swap_stack(Ref<Stack> new_stk) {
    stack.swap(new_stk);
    return new_stk;
  }
  void ensure_throw(bool cond) const {
    if (!cond) {
      fatal();
    }
  }
  void set_code(Ref<CellSlice> _code, int _cp) {
    code = std::move(_code);
    force_cp(_cp);
  }
  Ref<CellSlice> get_code() const {
    return code;
  }
  void push_code() {
    get_stack().push_cellslice(get_code());
  }
  void adjust_cr(const ControlRegs& save) {
    cr ^= save;
  }
  void adjust_cr(ControlRegs&& save) {
    cr ^= save;
  }
  void preclear_cr(const ControlRegs& save) {
    cr &= save;
  }
  int call(Ref<Continuation> cont);
  int call(Ref<Continuation> cont, int pass_args, int ret_args = -1);
  int jump(Ref<Continuation> cont);
  int jump(Ref<Continuation> cont, int pass_args);
  int ret();
  int ret(int ret_args);
  int ret_alt();
  int ret_alt(int ret_args);
  int repeat(Ref<Continuation> body, Ref<Continuation> after, long long count);
  int again(Ref<Continuation> body);
  int until(Ref<Continuation> body, Ref<Continuation> after);
  int loop_while(Ref<Continuation> cond, Ref<Continuation> body, Ref<Continuation> after);
  int throw_exception(int excno, StackEntry&& arg);
  int throw_exception(int excno);
  Ref<OrdCont> extract_cc(int save_cr = 1, int stack_copy = -1, int cc_args = -1);
  Ref<Continuation> c1_envelope(Ref<Continuation> cont, bool save = true);
  Ref<Continuation> c1_envelope_if(bool cond, Ref<Continuation> cont, bool save = true) {
    return cond ? c1_envelope(std::move(cont), save) : std::move(cont);
  }
  void c1_save_set(bool save = true);
  void fatal(void) const {
    throw VmFatal{};
  }
  int jump_to(Ref<Continuation> cont) {
    return cont->is_unique() ? cont.unique_write().jump_w(this) : cont->jump(this);
  }
  static Ref<CellSlice> convert_code_cell(Ref<Cell> code_cell);
  bool try_commit();
  void force_commit();

  void set_chksig_always_succeed(bool flag) {
    chksig_always_succeed = flag;
  }
  bool get_chksig_always_succeed() const {
    return chksig_always_succeed;
  }
  Ref<OrdCont> ref_to_cont(Ref<Cell> cell) const {
    return td::make_ref<OrdCont>(load_cell_slice_ref(std::move(cell)), get_cp());
  }

 private:
  void init_cregs(bool same_c3 = false, bool push_0 = true);
};

int run_vm_code(Ref<CellSlice> _code, Ref<Stack>& _stack, int flags = 0, Ref<Cell>* data_ptr = nullptr, VmLog log = {},
                long long* steps = nullptr, GasLimits* gas_limits = nullptr, std::vector<Ref<Cell>> libraries = {},
                Ref<Tuple> init_c7 = {}, Ref<Cell>* actions_ptr = nullptr);
int run_vm_code(Ref<CellSlice> _code, Stack& _stack, int flags = 0, Ref<Cell>* data_ptr = nullptr, VmLog log = {},
                long long* steps = nullptr, GasLimits* gas_limits = nullptr, std::vector<Ref<Cell>> libraries = {},
                Ref<Tuple> init_c7 = {}, Ref<Cell>* actions_ptr = nullptr);

Ref<vm::Cell> lookup_library_in(td::ConstBitPtr key, Ref<vm::Cell> lib_root);

}  // namespace vm
