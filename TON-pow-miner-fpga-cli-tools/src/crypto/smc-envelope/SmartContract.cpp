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
#include "SmartContract.h"

#include "GenericAccount.h"

#include "block/block.h"
#include "block/block-auto.h"
#include "vm/cellslice.h"
#include "vm/cp0.h"
#include "vm/memo.h"
#include "vm/vm.h"

#include "td/utils/crypto.h"

namespace ton {
int SmartContract::Answer::output_actions_count(td::Ref<vm::Cell> list) {
  int i = -1;
  do {
    ++i;
    list = load_cell_slice(std::move(list)).prefetch_ref();
  } while (list.not_null());
  return i;
}
namespace {

td::Ref<vm::Stack> prepare_vm_stack(td::RefInt256 amount, td::Ref<vm::CellSlice> body) {
  td::Ref<vm::Stack> stack_ref{true};
  td::RefInt256 acc_addr{true};
  //CHECK(acc_addr.write().import_bits(account.addr.cbits(), 256));
  vm::Stack& stack = stack_ref.write();
  stack.push_int(td::make_refint(10000000000));
  stack.push_int(std::move(amount));
  stack.push_cell(vm::CellBuilder().finalize());
  stack.push_cellslice(std::move(body));
  return stack_ref;
}

td::Ref<vm::Tuple> prepare_vm_c7(td::uint32 now, td::uint64 balance) {
  // TODO: fix initialization of c7
  td::BitArray<256> rand_seed;
  rand_seed.as_slice().fill(0);
  td::RefInt256 rand_seed_int{true};
  rand_seed_int.unique_write().import_bits(rand_seed.cbits(), 256, false);
  auto tuple = vm::make_tuple_ref(
      td::make_refint(0x076ef1ea),                           // [ magic:0x076ef1ea
      td::make_refint(0),                                    //   actions:Integer
      td::make_refint(0),                                    //   msgs_sent:Integer
      td::make_refint(now),                                  //   unixtime:Integer
      td::make_refint(0),                                    //   block_lt:Integer
      td::make_refint(0),                                    //   trans_lt:Integer
      std::move(rand_seed_int),                              //   rand_seed:Integer
      block::CurrencyCollection(balance).as_vm_tuple(),      //   balance_remaining:[Integer (Maybe Cell)]
      vm::load_cell_slice_ref(vm::CellBuilder().finalize())  //  myself:MsgAddressInt
                                                             //vm::StackEntry::maybe(td::Ref<vm::Cell>())
  );                                                         //  global_config:(Maybe Cell) ] = SmartContractInfo;
  //LOG(DEBUG) << "SmartContractInfo initialized with " << vm::StackEntry(tuple).to_string();
  return vm::make_tuple_ref(std::move(tuple));
}

SmartContract::Answer run_smartcont(SmartContract::State state, td::Ref<vm::Stack> stack, td::Ref<vm::Tuple> c7,
                                    vm::GasLimits gas, bool ignore_chksig) {
  auto gas_credit = gas.gas_credit;
  vm::init_op_cp0();
  vm::DictionaryBase::get_empty_dictionary();

  class Logger : public td::LogInterface {
   public:
    void append(td::CSlice slice) override {
      res.append(slice.data(), slice.size());
    }
    std::string res;
  };
  Logger logger;
  vm::VmLog log{&logger, td::LogOptions::plain()};

  if (GET_VERBOSITY_LEVEL() >= VERBOSITY_NAME(DEBUG)) {
    log.log_options.level = 4;
    log.log_options.fix_newlines = true;
    log.log_mask |= vm::VmLog::DumpStack;
  } else {
    log.log_options.level = 0;
    log.log_mask = 0;
  }

  SmartContract::Answer res;
  if (GET_VERBOSITY_LEVEL() >= VERBOSITY_NAME(DEBUG)) {
    std::ostringstream os;
    stack->dump(os, 2);
    LOG(DEBUG) << "VM stack:\n" << os.str();
  }
  vm::VmState vm{state.code, std::move(stack), gas, 1, state.data, log};
  vm.set_c7(std::move(c7));
  vm.set_chksig_always_succeed(ignore_chksig);
  try {
    res.code = ~vm.run();
  } catch (...) {
    LOG(FATAL) << "catch unhandled exception";
  }
  res.new_state = std::move(state);
  res.stack = vm.get_stack_ref();
  gas = vm.get_gas_limits();
  res.gas_used = gas.gas_consumed();
  res.accepted = gas.gas_credit == 0;
  res.success = (res.accepted && (unsigned)res.code <= 1);
  if (GET_VERBOSITY_LEVEL() >= VERBOSITY_NAME(DEBUG)) {
    LOG(DEBUG) << "VM log\n" << logger.res;
    std::ostringstream os;
    res.stack->dump(os, 2);
    LOG(DEBUG) << "VM stack:\n" << os.str();
    LOG(DEBUG) << "VM exit code: " << res.code;
    LOG(DEBUG) << "VM accepted: " << res.accepted;
    LOG(DEBUG) << "VM success: " << res.success;
  }
  if (res.success) {
    res.new_state.data = vm.get_c4();
    res.actions = vm.get_d(5);
    LOG(DEBUG) << "output actions:\n"
               << block::gen::OutList{res.output_actions_count(res.actions)}.as_string_ref(res.actions);
  }
  LOG_IF(ERROR, gas_credit != 0 && (res.accepted && !res.success))
      << "Accepted but failed with code " << res.code << "\n"
      << res.gas_used << "\n";
  return res;
}
}  // namespace

td::Result<td::BufferSlice> SmartContract::Args::get_serialized_stack() {
  if (!stack) {
    return td::Status::Error("Args has no stack");
  }
  vm::FakeVmStateLimits fstate(1000);  // limit recursive (de)serialization calls
  vm::VmStateInterface::Guard guard(&fstate);
  // serialize parameters
  vm::CellBuilder cb;
  td::Ref<vm::Cell> cell;
  if (!(stack.value()->serialize(cb) && cb.finalize_to(cell))) {
    return td::Status::Error("Cannot serialize stack in args");
  }
  return vm::std_boc_serialize(std::move(cell));
}

td::Ref<vm::CellSlice> SmartContract::empty_slice() {
  return vm::load_cell_slice_ref(vm::CellBuilder().finalize());
}

size_t SmartContract::code_size() const {
  return vm::std_boc_serialize(state_.code).ok().size();
}
size_t SmartContract::data_size() const {
  return vm::std_boc_serialize(state_.data).ok().size();
}

block::StdAddress SmartContract::get_address(WorkchainId workchain_id) const {
  return GenericAccount::get_address(workchain_id, get_init_state());
}

td::Ref<vm::Cell> SmartContract::get_init_state() const {
  return GenericAccount::get_init_state(get_state().code, get_state().data);
}

SmartContract::Answer SmartContract::run_method(Args args) {
  td::uint32 now = 0;
  if (args.now) {
    now = args.now.unwrap();
  }
  if (!args.c7) {
    args.c7 = prepare_vm_c7(now, args.balance);
  }
  if (!args.limits) {
    bool is_internal = args.get_method_id().ok() == 0;

    args.limits = vm::GasLimits{is_internal ? (long long)args.amount * 1000 : (long long)0, (long long)1000000,
                                is_internal ? 0 : (long long)10000};
  }
  CHECK(args.stack);
  CHECK(args.method_id);
  args.stack.value().write().push_smallint(args.method_id.unwrap());
  auto res =
      run_smartcont(get_state(), args.stack.unwrap(), args.c7.unwrap(), args.limits.unwrap(), args.ignore_chksig);
  state_ = res.new_state;
  return res;
}

SmartContract::Answer SmartContract::run_get_method(Args args) const {
  td::uint32 now = 0;
  if (args.now) {
    now = args.now.unwrap();
  }
  if (!args.c7) {
    args.c7 = prepare_vm_c7(now, args.balance);
  }
  if (!args.limits) {
    args.limits = vm::GasLimits{1000000};
  }
  if (!args.stack) {
    args.stack = td::Ref<vm::Stack>(true);
  }
  CHECK(args.method_id);
  args.stack.value().write().push_smallint(args.method_id.unwrap());
  return run_smartcont(get_state(), args.stack.unwrap(), args.c7.unwrap(), args.limits.unwrap(), args.ignore_chksig);
}

SmartContract::Answer SmartContract::run_get_method(td::Slice method, Args args) const {
  return run_get_method(args.set_method_id(method));
}

SmartContract::Answer SmartContract::send_external_message(td::Ref<vm::Cell> cell, Args args) {
  return run_method(
      args.set_stack(prepare_vm_stack(td::make_refint(0), vm::load_cell_slice_ref(cell))).set_method_id(-1));
}
SmartContract::Answer SmartContract::send_internal_message(td::Ref<vm::Cell> cell, Args args) {
  return run_method(
      args.set_stack(prepare_vm_stack(td::make_refint(args.amount), vm::load_cell_slice_ref(cell))).set_method_id(0));
}
}  // namespace ton
