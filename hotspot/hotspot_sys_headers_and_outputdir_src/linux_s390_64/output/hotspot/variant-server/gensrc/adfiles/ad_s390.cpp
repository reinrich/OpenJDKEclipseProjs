#line 1 "ad_s390.cpp"
//
// Copyright (c) 2017, 2026, Oracle and/or its affiliates. All rights reserved.
// Copyright (c) 2017, 2024 SAP SE. All rights reserved.
// DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
//
// This code is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 2 only, as
// published by the Free Software Foundation.
//
// This code is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// version 2 for more details (a copy is included in the LICENSE file that
// accompanied this code).
//
// You should have received a copy of the GNU General Public License version
// 2 along with this work; if not, write to the Free Software Foundation,
// Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
//
// Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
// or visit www.oracle.com if you need additional information or have any
// questions.
//

// Machine Generated File.  Do Not Edit!

#include "adfiles/adGlobals_s390.hpp"
#include "adfiles/ad_s390.hpp"
#include "memory/allocation.inline.hpp"
#include "code/aotCodeCache.hpp"
#include "code/codeCache.hpp"
#include "code/compiledIC.hpp"
#include "code/nativeInst.hpp"
#include "code/vmreg.inline.hpp"
#include "gc/shared/collectedHeap.inline.hpp"
#include "oops/compressedOops.hpp"
#include "oops/markWord.hpp"
#include "oops/method.hpp"
#include "oops/oop.inline.hpp"
#include "opto/c2_MacroAssembler.hpp"
#include "opto/cfgnode.hpp"
#include "opto/intrinsicnode.hpp"
#include "opto/locknode.hpp"
#include "opto/opcodes.hpp"
#include "opto/regalloc.hpp"
#include "opto/regmask.hpp"
#include "opto/runtime.hpp"
#include "runtime/safepointMechanism.hpp"
#include "runtime/sharedRuntime.hpp"
#include "runtime/stubRoutines.hpp"
#include "utilities/growableArray.hpp"
#include "utilities/powerOfTwo.hpp"

//SourceForm

#line 849 "/work/jdk/src/hotspot/cpu/s390/s390.ad"


#ifdef PRODUCT
#define BLOCK_COMMENT(str)
#define BIND(label)        __ bind(label)
#else
#define BLOCK_COMMENT(str) __ block_comment(str)
#define BIND(label)        __ bind(label); BLOCK_COMMENT(#label ":")
#endif

#define __ masm->

#define Z_DISP_SIZE Immediate::is_uimm12((long)opnd_array(1)->disp(ra_,this,2)) ?  4 : 6
#define Z_DISP3_SIZE 6

// Tertiary op of a LoadP or StoreP encoding.
#define REGP_OP true

// Given a register encoding, produce an Integer Register object.
static Register reg_to_register_object(int register_encoding);

// ****************************************************************************

// REQUIRED FUNCTIONALITY

// !!!!! Special hack to get all type of calls to specify the byte offset
//       from the start of the call to the point where the return address
//       will point.

void PhaseOutput::pd_perform_mach_node_analysis() {
}

int MachNode::pd_alignment_required() const {
  return 1;
}

int MachNode::compute_padding(int current_offset) const {
  return 0;
}

int MachCallStaticJavaNode::ret_addr_offset() {
  if (_method) {
    return 8;
  } else {
    return MacroAssembler::call_far_patchable_ret_addr_offset();
  }
}

int MachCallDynamicJavaNode::ret_addr_offset() {
  // Consider size of receiver type profiling (C2 tiers).
  int profile_receiver_type_size = 0;

  int vtable_index = this->_vtable_index;
  if (vtable_index == -4) {
    return 14 + profile_receiver_type_size;
  } else {
    assert(!UseInlineCaches, "expect vtable calls only if not using ICs");
    return 36 + profile_receiver_type_size;
  }
}

int MachCallRuntimeNode::ret_addr_offset() {
  return 12 + MacroAssembler::call_far_patchable_ret_addr_offset();
}

// Compute padding required for nodes which need alignment
//
// The addresses of the call instructions needs to be 4-byte aligned to
// ensure that they don't span a cache line so that they are atomically patchable.
// The actual calls get emitted at different offsets within the node emitters.
// ins_alignment needs to be set to 2 which means that up to 1 nop may get inserted.

int CallStaticJavaDirect_dynTOCNode::compute_padding(int current_offset) const {
  return (0 - current_offset) & 2;
}

int CallDynamicJavaDirect_dynTOCNode::compute_padding(int current_offset) const {
  return (6 - current_offset) & 2;
}

int CallRuntimeDirectNode::compute_padding(int current_offset) const {
  return (12 - current_offset) & 2;
}

int CallLeafDirectNode::compute_padding(int current_offset) const {
  return (12 - current_offset) & 2;
}

int CallLeafNoFPDirectNode::compute_padding(int current_offset) const {
  return (12 - current_offset) & 2;
}

void emit_nop(C2_MacroAssembler *masm) {
  __ z_nop();
}

// Emit an interrupt that is caught by the debugger (for debugging compiler).
void emit_break(C2_MacroAssembler *masm) {
  __ z_illtrap();
}

#if !defined(PRODUCT)
void MachBreakpointNode::format(PhaseRegAlloc *, outputStream *os) const {
  os->print("TA");
}
#endif

void MachBreakpointNode::emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const {
  emit_break(masm);
}

uint MachBreakpointNode::size(PhaseRegAlloc *ra_) const {
  return MachNode::size(ra_);
}

static inline void z_emit16(C2_MacroAssembler *masm, long value) {
  __ emit_instruction((unsigned long)value, 2);
}

static inline void z_emit32(C2_MacroAssembler *masm, long value) {
  __ emit_instruction((unsigned long)value, 4);
}

static inline void z_emit48(C2_MacroAssembler *masm, long value) {
  __ emit_instruction((unsigned long)value, 6);
}

static inline unsigned int z_emit_inst(C2_MacroAssembler *masm, long value) {
  if (value < 0) {
    // There obviously has been an unintended sign extension (int->long). Revert it.
    value = (long)((unsigned long)((unsigned int)value));
  }

  int len = __ emit_instruction((unsigned long)value, 0);
  return len;
}

// Check effective address (at runtime) for required alignment.
static inline void z_assert_aligned(C2_MacroAssembler *masm, int disp, Register index, Register base, int alignment) {
  __ z_lay(Z_R0, disp, index, base);
  __ z_nill(Z_R0, alignment-1);
  __ z_brc(Assembler::bcondEqual, +3);
  __ z_illtrap();
}

int emit_call_reloc(C2_MacroAssembler *masm, intptr_t entry_point, relocInfo::relocType rtype,
                    PhaseRegAlloc* ra_, bool is_native_call = false) {
  __ set_inst_mark(); // Used in z_enc_java_static_call() and emit_java_to_interp().
  address old_mark = __ inst_mark();
  unsigned int start_off = __ offset();

  if (is_native_call) {
    ShouldNotReachHere();
  }

  if (rtype == relocInfo::runtime_call_w_cp_type) {
    assert((__ offset() & 2) == 0, "misaligned emit_call_reloc");
    address call_addr = __ call_c_opt((address)entry_point);
    if (call_addr == nullptr) {
      Compile::current()->env()->record_out_of_memory_failure();
      return -1;
    }
  } else {
    assert(rtype == relocInfo::none || rtype == relocInfo::opt_virtual_call_type ||
           rtype == relocInfo::static_call_type, "unexpected rtype");
    __ relocate(rtype);
    // BRASL must be prepended with a nop to identify it in the instruction stream.
    __ z_nop();
    __ z_brasl(Z_R14, (address)entry_point);
  }

  unsigned int ret_off = __ offset();

  return (ret_off - start_off);
}

static int emit_call_reloc(C2_MacroAssembler *masm, intptr_t entry_point, RelocationHolder const& rspec) {
  __ set_inst_mark(); // Used in z_enc_java_static_call() and emit_java_to_interp().
  address old_mark = __ inst_mark();
  unsigned int start_off = __ offset();

  relocInfo::relocType rtype = rspec.type();
  assert(rtype == relocInfo::opt_virtual_call_type || rtype == relocInfo::static_call_type,
         "unexpected rtype");

  __ relocate(rspec);
  __ z_nop();
  __ z_brasl(Z_R14, (address)entry_point);

  unsigned int ret_off = __ offset();

  return (ret_off - start_off);
}

//=============================================================================

const RegMask& MachConstantBaseNode::_out_RegMask = _Z_PTR_REG_mask;
int ConstantTable::calculate_table_base_offset() const {
  return 0;  // absolute addressing, no offset
}

bool MachConstantBaseNode::requires_postalloc_expand() const { return false; }
void MachConstantBaseNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  ShouldNotReachHere();
}

// Even with PC-relative TOC addressing, we still need this node.
// Float loads/stores do not support PC-relative addresses.
void MachConstantBaseNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  Register Rtoc = as_Register(ra_->get_encode(this));
  __ load_toc(Rtoc);
}

uint MachConstantBaseNode::size(PhaseRegAlloc* ra_) const {
  // PCrelative TOC access.
  return 6;   // sizeof(LARL)
}

#if !defined(PRODUCT)
void MachConstantBaseNode::format(PhaseRegAlloc* ra_, outputStream* st) const {
  Register r = as_Register(ra_->get_encode(this));
  st->print("LARL    %s,&constant_pool # MachConstantBaseNode", r->name());
}
#endif

//=============================================================================

#include "gc/shared/barrierSetAssembler.hpp"

#if !defined(PRODUCT)
void MachPrologNode::format(PhaseRegAlloc *ra_, outputStream *st) const {
  Compile* C = ra_->C;
  st->print_cr("--- MachPrologNode ---");
  st->print("\t");
  for (int i = 0; i < OptoPrologueNops; i++) {
    st->print_cr("NOP"); st->print("\t");
  }

  long framesize = C->output()->frame_size_in_bytes();
  int bangsize   = C->output()->bang_size_in_bytes();

  // Calls to C2R adapters often do not accept exceptional returns.
  // We require that their callers must bang for them. But be
  // careful, because some VM calls (such as call site linkage) can
  // use several kilobytes of stack. But the stack safety zone should
  // account for that. See bugs 4446381, 4468289, 4497237.
  if (C->output()->need_stack_bang(bangsize)) {
    st->print_cr("# stack bang"); st->print("\t");
  }
  st->print_cr("push_frame %d", (int)-framesize);
  st->print("\t");

  if (C->stub_function() == nullptr) {
    st->print("nmethod entry barrier\n\t");
  }
}
#endif

void MachPrologNode::emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const {
  Compile* C = ra_->C;

  size_t framesize = C->output()->frame_size_in_bytes();
  size_t bangsize  = C->output()->bang_size_in_bytes();

  assert(framesize % wordSize == 0, "must preserve wordSize alignment");

  if (C->clinit_barrier_on_entry()) {
    assert(!C->method()->holder()->is_not_initialized(), "initialization should have been started");

    Label L_skip_barrier;
    Register klass = Z_R1_scratch;

    // Notify OOP recorder (don't need the relocation)
    AddressLiteral md = __ constant_metadata_address(C->method()->holder()->constant_encoding());
    __ load_const_optimized(klass, md.value());
    __ clinit_barrier(klass, Z_thread, &L_skip_barrier /*L_fast_path*/);

    __ load_const_optimized(klass, SharedRuntime::get_handle_wrong_method_stub());
    __ z_br(klass);

    __ bind(L_skip_barrier);
  }

  // Calls to C2R adapters often do not accept exceptional returns.
  // We require that their callers must bang for them. But be
  // careful, because some VM calls (such as call site linkage) can
  // use several kilobytes of stack. But the stack safety zone should
  // account for that. See bugs 4446381, 4468289, 4497237.
  if (C->output()->need_stack_bang(bangsize)) {
    __ generate_stack_overflow_check(bangsize);
  }

  assert(Immediate::is_uimm32((long)framesize), "to do: choose suitable types!");
  __ save_return_pc();

  // The z/Architecture abi is already accounted for in `framesize' via the
  // 'out_preserve_stack_slots' declaration.
  __ push_frame((unsigned int)framesize/*includes JIT ABI*/);

  if (C->has_mach_constant_base_node()) {
    // NOTE: We set the table base offset here because users might be
    // emitted before MachConstantBaseNode.
    ConstantTable& constant_table = C->output()->constant_table();
    constant_table.set_table_base_offset(constant_table.calculate_table_base_offset());
  }

  if (C->stub_function() == nullptr) {
    BarrierSetAssembler* bs = BarrierSet::barrier_set()->barrier_set_assembler();
    bs->nmethod_entry_barrier(masm);
  }

  C->output()->set_frame_complete(__ offset());
}

uint MachPrologNode::size(PhaseRegAlloc *ra_) const {
  // Variable size. Determine dynamically.
  return MachNode::size(ra_);
}

int MachPrologNode::reloc() const {
  // Return number of relocatable values contained in this instruction.
  return 1; // One reloc entry for load_const(toc).
}

//=============================================================================

#if !defined(PRODUCT)
void MachEpilogNode::format(PhaseRegAlloc *ra_, outputStream *os) const {
  os->print_cr("epilog");
  os->print("\t");
  if (do_polling() && ra_->C->is_method_compilation()) {
    os->print_cr("load_from_polling_page Z_R1_scratch");
    os->print("\t");
  }
}
#endif

void MachEpilogNode::emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const {
  Compile* C = ra_->C;

  // If this does safepoint polling, then do it here.
  bool need_polling = do_polling() && C->is_method_compilation();

  // Pop frame, restore return_pc, and all stuff needed by interpreter.
  int frame_size_in_bytes = Assembler::align((C->output()->frame_slots() << LogBytesPerInt), frame::alignment_in_bytes);
  __ pop_frame_restore_retPC(frame_size_in_bytes);

  if (StackReservedPages > 0 && C->has_reserved_stack_access()) {
    __ reserved_stack_check(Z_R14);
  }

  // Touch the polling page.
  if (need_polling) {
    __ z_lg(Z_R1_scratch, Address(Z_thread, JavaThread::polling_page_offset()));
    // We need to mark the code position where the load from the safepoint
    // polling page was emitted as relocInfo::poll_return_type here.
    __ relocate(relocInfo::poll_return_type);
    __ load_from_polling_page(Z_R1_scratch);
  }
}

uint MachEpilogNode::size(PhaseRegAlloc *ra_) const {
  // Variable size. determine dynamically.
  return MachNode::size(ra_);
}

int MachEpilogNode::reloc() const {
  // Return number of relocatable values contained in this instruction.
  return 1; // One for load_from_polling_page.
}

const Pipeline * MachEpilogNode::pipeline() const {
  return MachNode::pipeline_class();
}

//=============================================================================

// Figure out which register class each belongs in: rc_int, rc_float, rc_vector, rc_stack.
enum RC { rc_bad, rc_int, rc_float, rc_vector, rc_stack };

static enum RC rc_class(OptoReg::Name reg) {
  // Return the register class for the given register. The given register
  // reg is a <register>_num value, which is an index into the MachRegisterNumbers
  // enumeration in adGlobals_s390.hpp.

  if (reg == OptoReg::Bad) {
    return rc_bad;
  }

  // We have 32 integer register halves, starting at index 0.
  if (reg < 32) {
    return rc_int;
  }

  // We have 32 floating-point register halves, starting at index 32.
  if (reg < 32+32) {
    return rc_float;
  }

  // we have 128 vector register halves at index 64
  if (reg < 32+32+128) {
    return rc_vector;
  }

  // Between float regs & stack are the flags regs.
  assert(OptoReg::is_stack(reg) || reg < 32+32+128, "blow up if spilling flags");
  return rc_stack;
}

// Returns size as obtained from z_emit_instr.
static unsigned int z_ld_st_helper(C2_MacroAssembler *masm, const char *op_str, unsigned long opcode,
                                   int reg, int offset, bool do_print, outputStream *os) {

  if (masm) {
    if (opcode > (1L<<32)) {
      return z_emit_inst(masm, opcode | Assembler::reg(Matcher::_regEncode[reg], 8, 48) |
                         Assembler::simm20(offset) | Assembler::reg(Z_R0, 12, 48) | Assembler::regz(Z_SP, 16, 48));
    } else {
      return z_emit_inst(masm, opcode | Assembler::reg(Matcher::_regEncode[reg], 8, 32) |
                         Assembler::uimm12(offset, 20, 32) | Assembler::reg(Z_R0, 12, 32) | Assembler::regz(Z_SP, 16, 32));
    }
  }

#if !defined(PRODUCT)
  if (do_print) {
    os->print("%s    %s,#%d[,SP]\t # MachCopy spill code",op_str, Matcher::regName[reg], offset);
  }
#endif
  return (opcode > (1L << 32)) ? 6 : 4;
}

static unsigned int z_mvc_helper(C2_MacroAssembler *masm, int len, int dst_off, int src_off, bool do_print, outputStream *os) {
  if (masm) {
    __ z_mvc(dst_off, len-1, Z_SP, src_off, Z_SP);
  }

#if !defined(PRODUCT)
  else if (do_print) {
    os->print("MVC     %d(%d,SP),%d(SP)\t # MachCopy spill code",dst_off, len, src_off);
  }
#endif

  return 6;
}

uint MachSpillCopyNode::implementation(C2_MacroAssembler *masm, PhaseRegAlloc *ra_, bool do_size, outputStream *os) const {
  // Get registers to move.
  OptoReg::Name src_hi = ra_->get_reg_second(in(1));
  OptoReg::Name src_lo = ra_->get_reg_first(in(1));
  OptoReg::Name dst_hi = ra_->get_reg_second(this);
  OptoReg::Name dst_lo = ra_->get_reg_first(this);

  enum RC src_hi_rc = rc_class(src_hi);
  enum RC src_lo_rc = rc_class(src_lo);
  enum RC dst_hi_rc = rc_class(dst_hi);
  enum RC dst_lo_rc = rc_class(dst_lo);

  assert(src_lo != OptoReg::Bad && dst_lo != OptoReg::Bad, "must move at least 1 register");
  bool is64 = (src_hi_rc != rc_bad);
  assert(!is64 ||
         ((src_lo&1) == 0 && src_lo+1 == src_hi && (dst_lo&1) == 0 && dst_lo+1 == dst_hi),
         "expected aligned-adjacent pairs");

  // Generate spill code!
  int size = 0;
  if (src_lo == dst_lo && src_hi == dst_hi) {
    return 0;            // Self copy, no move.
  }

  int  src_offset = ra_->reg2offset(src_lo);
  int  dst_offset = ra_->reg2offset(dst_lo);
  bool print = !do_size;
  bool src12 = Immediate::is_uimm12(src_offset);
  bool dst12 = Immediate::is_uimm12(dst_offset);

  const char   *mnemo = nullptr;
  unsigned long opc = 0;

  if (bottom_type()->isa_vect() != nullptr && ideal_reg() == Op_VecX) {
    if (src_lo_rc == rc_stack && dst_lo_rc == rc_stack) {
      if (masm != nullptr) {
        __ z_mvc(Address(Z_SP, 0,  dst_offset), Address(Z_SP, 0, src_offset), 16);
      }
      size += 6;
    } else if (src_lo_rc == rc_vector && dst_lo_rc == rc_stack) {
      VectorRegister Rsrc = as_VectorRegister(Matcher::_regEncode[src_lo]);
      if (masm != nullptr) {
        __ z_vst(Rsrc, Address(Z_SP, 0, dst_offset));
      }
      size += 6;
    } else if (src_lo_rc == rc_stack && dst_lo_rc == rc_vector) {
      VectorRegister Rdst = as_VectorRegister(Matcher::_regEncode[dst_lo]);
      if (masm != nullptr) {
        __ z_vl(Rdst, Address(Z_SP, 0, src_offset));
      }
      size += 6;
    } else if (src_lo_rc == rc_vector && dst_lo_rc == rc_vector) {
      VectorRegister Rsrc = as_VectorRegister(Matcher::_regEncode[src_lo]);
      VectorRegister Rdst = as_VectorRegister(Matcher::_regEncode[dst_lo]);
      if (masm != nullptr) {
        __ z_vlr(Rdst, Rsrc);
      }
      size += 6;
    } else {
      ShouldNotReachHere();
    }
    return size;
  }

  // Memory->Memory Spill. Use Z_R0 to hold the value.
  if (src_lo_rc == rc_stack && dst_lo_rc == rc_stack) {

    assert(!is64 || (src_hi_rc==rc_stack && dst_hi_rc==rc_stack),
           "expected same type of move for high parts");

    if (src12 && dst12) {
      return z_mvc_helper(masm, is64 ? 8 : 4, dst_offset, src_offset, print, os);
    }

    int r0 = Z_R0_num;
    if (is64) {
      return z_ld_st_helper(masm, "LG  ", LG_ZOPC, r0, src_offset, print, os) +
             z_ld_st_helper(masm, "STG ", STG_ZOPC, r0, dst_offset, print, os);
    }

    return z_ld_st_helper(masm, "LY   ", LY_ZOPC, r0, src_offset, print, os) +
           z_ld_st_helper(masm, "STY  ", STY_ZOPC, r0, dst_offset, print, os);
  }

  // Check for float->int copy. Requires a trip through memory.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_int) {
    Unimplemented();  // Unsafe, do not remove!
  }

  // Check for integer reg-reg copy.
  if (src_lo_rc == rc_int && dst_lo_rc == rc_int) {
    if (masm) {
      Register Rsrc = as_Register(Matcher::_regEncode[src_lo]);
      Register Rdst = as_Register(Matcher::_regEncode[dst_lo]);
      __ z_lgr(Rdst, Rsrc);
      return 4;
    }
#if !defined(PRODUCT)
    // else
    if (print) {
      os->print("LGR     %s,%s\t # MachCopy spill code", Matcher::regName[dst_lo], Matcher::regName[src_lo]);
    }
#endif
    return 4;
  }

  // Check for integer store.
  if (src_lo_rc == rc_int && dst_lo_rc == rc_stack) {
    assert(!is64 || (src_hi_rc==rc_int && dst_hi_rc==rc_stack),
           "expected same type of move for high parts");

    if (is64) {
      return z_ld_st_helper(masm, "STG ", STG_ZOPC, src_lo, dst_offset, print, os);
    }

    // else
    mnemo = dst12 ? "ST  " : "STY ";
    opc = dst12 ? ST_ZOPC : STY_ZOPC;

    return z_ld_st_helper(masm, mnemo, opc, src_lo, dst_offset, print, os);
  }

  // Check for integer load
  // Always load cOops zero-extended. That doesn't hurt int loads.
  if (dst_lo_rc == rc_int && src_lo_rc == rc_stack) {

    assert(!is64 || (dst_hi_rc==rc_int && src_hi_rc==rc_stack),
           "expected same type of move for high parts");

    mnemo = is64 ? "LG  " : "LLGF";
    opc = is64 ? LG_ZOPC : LLGF_ZOPC;

    return z_ld_st_helper(masm, mnemo, opc, dst_lo, src_offset, print, os);
  }

  // Check for float reg-reg copy.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_float) {
    if (masm) {
      FloatRegister Rsrc = as_FloatRegister(Matcher::_regEncode[src_lo]);
      FloatRegister Rdst = as_FloatRegister(Matcher::_regEncode[dst_lo]);
      __ z_ldr(Rdst, Rsrc);
      return 2;
    }
#if !defined(PRODUCT)
    // else
    if (print) {
      os->print("LDR      %s,%s\t # MachCopy spill code", Matcher::regName[dst_lo], Matcher::regName[src_lo]);
    }
#endif
    return 2;
  }

  // Check for float store.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_stack) {
    assert(!is64 || (src_hi_rc==rc_float && dst_hi_rc==rc_stack),
           "expected same type of move for high parts");

    if (is64) {
      mnemo = dst12 ? "STD  " : "STDY ";
      opc = dst12 ? STD_ZOPC : STDY_ZOPC;
      return z_ld_st_helper(masm, mnemo, opc, src_lo, dst_offset, print, os);
    }
    // else

    mnemo = dst12 ? "STE  " : "STEY ";
    opc = dst12 ? STE_ZOPC : STEY_ZOPC;
    return z_ld_st_helper(masm, mnemo, opc, src_lo, dst_offset, print, os);
  }

  // Check for float load.
  if (dst_lo_rc == rc_float && src_lo_rc == rc_stack) {
    assert(!is64 || (dst_hi_rc==rc_float && src_hi_rc==rc_stack),
           "expected same type of move for high parts");

    if (is64) {
      mnemo = src12 ? "LD   " : "LDY  ";
      opc = src12 ? LD_ZOPC : LDY_ZOPC;
      return z_ld_st_helper(masm, mnemo, opc, dst_lo, src_offset, print, os);
    }
    // else

    mnemo = src12 ? "LE   " : "LEY  ";
    opc = src12 ? LE_ZOPC : LEY_ZOPC;
    return z_ld_st_helper(masm, mnemo, opc, dst_lo, src_offset, print, os);
  }

  // --------------------------------------------------------------------
  // Check for hi bits still needing moving. Only happens for misaligned
  // arguments to native calls.
  if (src_hi == dst_hi) {
    return 0;               // Self copy, no move.
  }

  assert(is64 && dst_hi_rc != rc_bad, "src_hi & dst_hi cannot be Bad");
  Unimplemented();  // Unsafe, do not remove!

  return 0; // never reached, but make the compiler shut up!
}

#if !defined(PRODUCT)
void MachSpillCopyNode::format(PhaseRegAlloc *ra_, outputStream *os) const {
  if (ra_ && ra_->node_regs_max_index() > 0) {
    implementation(nullptr, ra_, false, os);
  } else {
    if (req() == 2 && in(1)) {
      os->print("N%d = N%d\n", _idx, in(1)->_idx);
    } else {
      const char *c = "(";
      os->print("N%d = ", _idx);
      for (uint i = 1; i < req(); ++i) {
        os->print("%sN%d", c, in(i)->_idx);
        c = ", ";
      }
      os->print(")");
    }
  }
}
#endif

void MachSpillCopyNode::emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const {
  implementation(masm, ra_, false, nullptr);
}

uint MachSpillCopyNode::size(PhaseRegAlloc *ra_) const {
  return implementation(nullptr, ra_, true, nullptr);
}

//=============================================================================

#if !defined(PRODUCT)
void MachNopNode::format(PhaseRegAlloc *, outputStream *os) const {
  os->print("NOP     # pad for alignment (%d nops, %d bytes)", _count, _count*MacroAssembler::nop_size());
}
#endif

void MachNopNode::emit(C2_MacroAssembler *masm, PhaseRegAlloc * ra_) const {
  int rem_space = 0;
  if (!(ra_->C->output()->in_scratch_emit_size())) {
    rem_space = __ code()->insts()->remaining();
    if (rem_space <= _count*2 + 8) {
      tty->print("NopNode: _count = %3.3d, remaining space before = %d", _count, rem_space);
    }
  }

  for (int i = 0; i < _count; i++) {
    __ z_nop();
  }

  if (!(ra_->C->output()->in_scratch_emit_size())) {
    if (rem_space <= _count*2 + 8) {
      int rem_space2 = __ code()->insts()->remaining();
      tty->print_cr(", after = %d", rem_space2);
    }
  }
}

uint MachNopNode::size(PhaseRegAlloc *ra_) const {
   return 2 * _count;
}

#if !defined(PRODUCT)
void BoxLockNode::format(PhaseRegAlloc *ra_, outputStream *os) const {
  int offset = ra_->reg2offset(in_RegMask(0).find_first_elem());
  if (ra_ && ra_->node_regs_max_index() > 0) {
    int reg = ra_->get_reg_first(this);
    os->print("ADDHI  %s, SP, %d\t//box node", Matcher::regName[reg], offset);
  } else {
    os->print("ADDHI  N%d = SP + %d\t// box node", _idx, offset);
  }
}
#endif

// Take care of the size function, if you make changes here!
void BoxLockNode::emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const {
  int offset = ra_->reg2offset(in_RegMask(0).find_first_elem());
  int reg = ra_->get_encode(this);
  __ z_lay(as_Register(reg), offset, Z_SP);
}

uint BoxLockNode::size(PhaseRegAlloc *ra_) const {
  // BoxLockNode is not a MachNode, so we can't just call MachNode::size(ra_)
  return 6;
}

 
#line 788 "ad_s390.cpp"


//SourceForm

#line 1617 "/work/jdk/src/hotspot/cpu/s390/s390.ad"


#if !defined(PRODUCT)
void MachUEPNode::format(PhaseRegAlloc *ra_, outputStream *os) const {
  os->print_cr("---- MachUEPNode ----");
  os->print_cr("\tTA");
  os->print_cr("\tload_const Z_R1, SharedRuntime::get_ic_miss_stub()");
  os->print_cr("\tBR(Z_R1)");
  os->print_cr("\tTA  # pad with illtraps");
  os->print_cr("\t...");
  os->print_cr("\tTA");
  os->print_cr("\tLTGR    Z_R2, Z_R2");
  os->print_cr("\tBRU     ic_miss");
}
#endif

void MachUEPNode::emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const {
  // This is Unverified Entry Point
  __ ic_check(CodeEntryAlignment);
}

uint MachUEPNode::size(PhaseRegAlloc *ra_) const {
  // Determine size dynamically.
  return MachNode::size(ra_);
}

//=============================================================================


#line 823 "ad_s390.cpp"


//SourceForm

#line 1668 "/work/jdk/src/hotspot/cpu/s390/s390.ad"


// Emit deopt handler code.
int HandlerImpl::emit_deopt_handler(C2_MacroAssembler* masm) {
  address        base = __ start_a_stub(size_deopt_handler());

  if (base == nullptr) {
    ciEnv::current()->record_failure("CodeCache is full");
    return 0;  // CodeBuffer::expand failed
  }

  int offset = __ offset();

  Label start;
  __ bind(start);

  // Size_deopt_handler() must be exact on zarch, so for simplicity
  // we do not use load_const_opt here.
  __ load_const(Z_R1, SharedRuntime::deopt_blob()->unpack());
  __ call(Z_R1);

  int entry_offset = __ offset();

  __ z_bru(start);

  assert(__ offset() - offset == (int) size_deopt_handler(), "must be fixed size");
  assert(__ offset() - entry_offset >= NativePostCallNop::first_check_size,
         "out of bounds read in post-call NOP check");

  __ end_a_stub();
  return entry_offset;
}

//=============================================================================


// Given a register encoding, produce an Integer Register object.
static Register reg_to_register_object(int register_encoding) {
  assert(Z_R12->encoding() == Z_R12_enc, "wrong coding");
  return as_Register(register_encoding);
}

bool Matcher::match_rule_supported(int opcode) {
  if (!has_match_rule(opcode)) {
    return false; // no match rule present
  }

  switch (opcode) {
    case Op_ReverseBytesI:
    case Op_ReverseBytesL:
    case Op_ReverseBytesS:
    case Op_ReverseBytesUS:
      return UseByteReverseInstruction;
    case Op_PopCountI:
    case Op_PopCountL:
      // PopCount supported by H/W from z/Architecture G5 (z196) on.
      return (UsePopCountInstruction && VM_Version::has_PopCount());
    case Op_AddVB:
    case Op_AddVS:
    case Op_AddVI:
    case Op_AddVL:
    case Op_AddVD:
    case Op_SubVB:
    case Op_SubVS:
    case Op_SubVI:
    case Op_SubVL:
    case Op_SubVD:
    case Op_MulVB:
    case Op_MulVS:
    case Op_MulVI:
    case Op_MulVD:
    case Op_DivVD:
    case Op_SqrtVD:
    case Op_RoundDoubleModeV:
      return SuperwordUseVX;
    case Op_AddVF:
    case Op_SubVF:
    case Op_MulVF:
    case Op_DivVF:
    case Op_SqrtVF:
    //PopCountVI supported by z14 onwards.
    case Op_PopCountVI:
      return (SuperwordUseVX && UseSFPV);
    case Op_FmaF:
    case Op_FmaD:
      return UseFMA;
  }

  return true; // Per default match rules are supported.
}

bool Matcher::match_rule_supported_auto_vectorization(int opcode, int vlen, BasicType bt) {
  return match_rule_supported_vector(opcode, vlen, bt);
}

bool Matcher::match_rule_supported_vector(int opcode, int vlen, BasicType bt) {
  if (!match_rule_supported(opcode) || !vector_size_supported(bt, vlen)) {
    return false;
  }
  return true; // Per default match rules are supported.
}

bool Matcher::match_rule_supported_vector_masked(int opcode, int vlen, BasicType bt) {
  return false;
}

bool Matcher::vector_needs_partial_operations(Node* node, const TypeVect* vt) {
  return false;
}

bool Matcher::vector_rearrange_requires_load_shuffle(BasicType elem_bt, int vlen) {
  return false;
}

bool Matcher::mask_op_prefers_predicate(int opcode, const TypeVect* vt) {
  return false;
}

const RegMask* Matcher::predicate_reg_mask(void) {
  return nullptr;
}

// Vector calling convention not yet implemented.
bool Matcher::supports_vector_calling_convention(void) {
  return false;
}

OptoRegPair Matcher::vector_return_value(uint ideal_reg) {
  Unimplemented();
  return OptoRegPair(0, 0);
}

//----------SUPERWORD HELPERS----------------------------------------

// Vector width in bytes.
int Matcher::vector_width_in_bytes(BasicType bt) {
  if (SuperwordUseVX) {
    assert(MaxVectorSize == 16, "");
    return 16;
  } else {
    assert(MaxVectorSize == 8, "");
    return 8;
  }
}

// Vector ideal reg.
uint Matcher::vector_ideal_reg(int size) {
  if (SuperwordUseVX) {
    assert(MaxVectorSize == 16 && size == 16, "");
    return Op_VecX;
  } else {
    assert(MaxVectorSize == 8 && size == 8, "");
    return Op_RegL;
  }
}

// Limits on vector size (number of elements) loaded into vector.
int Matcher::max_vector_size(const BasicType bt) {
  assert(is_java_primitive(bt), "only primitive type vectors");
  return vector_width_in_bytes(bt)/type2aelembytes(bt);
}

int Matcher::min_vector_size(const BasicType bt) {
  return max_vector_size(bt); // Same as max.
}

int Matcher::max_vector_size_auto_vectorization(const BasicType bt) {
  return Matcher::max_vector_size(bt);
}

int Matcher::scalable_vector_reg_size(const BasicType bt) {
  return -1;
}

// RETURNS: whether this branch offset is short enough that a short
// branch can be used.
//
// If the platform does not provide any short branch variants, then
// this method should return `false' for offset 0.
//
// `Compile::Fill_buffer' will decide on basis of this information
// whether to do the pass `Compile::Shorten_branches' at all.
//
// And `Compile::Shorten_branches' will decide on basis of this
// information whether to replace particular branch sites by short
// ones.
bool Matcher::is_short_branch_offset(int rule, int br_size, int offset) {
  // On zarch short branches use a 16 bit signed immediate that
  // is the pc-relative offset in halfword (= 2 bytes) units.
  return Assembler::is_within_range_of_RelAddr16((address)((long)offset), (address)0);
}

MachOper* Matcher::pd_specialize_generic_vector_operand(MachOper* original_opnd, uint ideal_reg, bool is_temp) {
  ShouldNotReachHere(); // generic vector operands not supported
  return nullptr;
}

bool Matcher::is_reg2reg_move(MachNode* m) {
  ShouldNotReachHere();  // generic vector operands not supported
  return false;
}

bool Matcher::is_register_biasing_candidate(const MachNode* mdef, int oper_index) {
  return false;
}

bool Matcher::is_generic_vector(MachOper* opnd)  {
  ShouldNotReachHere();  // generic vector operands not supported
  return false;
}

// Constants for c2c and c calling conventions.

const MachRegisterNumbers z_iarg_reg[5] = {
  Z_R2_num, Z_R3_num, Z_R4_num, Z_R5_num, Z_R6_num
};

const MachRegisterNumbers z_farg_reg[4] = {
  Z_F0_num, Z_F2_num, Z_F4_num, Z_F6_num
};

const int z_num_iarg_registers = sizeof(z_iarg_reg) / sizeof(z_iarg_reg[0]);

const int z_num_farg_registers = sizeof(z_farg_reg) / sizeof(z_farg_reg[0]);

#ifdef ASSERT
// Return whether or not this register is ever used as an argument.
bool Matcher::can_be_java_arg(int reg) {
  // We return true for all registers contained in z_iarg_reg[] and
  // z_farg_reg[] and their virtual halves.
  // We must include the virtual halves in order to get STDs and LDs
  // instead of STWs and LWs in the trampoline stubs.

  if (reg == Z_R2_num || reg == Z_R2_H_num ||
      reg == Z_R3_num || reg == Z_R3_H_num ||
      reg == Z_R4_num || reg == Z_R4_H_num ||
      reg == Z_R5_num || reg == Z_R5_H_num ||
      reg == Z_R6_num || reg == Z_R6_H_num) {
    return true;
  }

  if (reg == Z_F0_num || reg == Z_F0_H_num ||
      reg == Z_F2_num || reg == Z_F2_H_num ||
      reg == Z_F4_num || reg == Z_F4_H_num ||
      reg == Z_F6_num || reg == Z_F6_H_num) {
    return true;
  }

  return false;
}
#endif

uint Matcher::int_pressure_limit()
{
  // Medium size register set, 6 special purpose regs, 3 SOE regs.
  // 10 prevents spill-split-recycle sanity check in JVM2008.xml.transform.
  return (INTPRESSURE == -1) ? 10 : INTPRESSURE;
}

uint Matcher::float_pressure_limit()
{
  return (FLOATPRESSURE == -1) ? 15 : FLOATPRESSURE;
}

// Register for DIVI projection of divmodI
const RegMask& Matcher::divI_proj_mask() {
  return _Z_RARG4_INT_REG_mask;
}

// Register for MODI projection of divmodI
const RegMask& Matcher::modI_proj_mask() {
  return _Z_RARG3_INT_REG_mask;
}

// Register for DIVL projection of divmodL
const RegMask& Matcher::divL_proj_mask() {
  return _Z_RARG4_LONG_REG_mask;
}

// Register for MODL projection of divmodL
const RegMask& Matcher::modL_proj_mask() {
  return _Z_RARG3_LONG_REG_mask;
}

// Should the matcher clone input 'm' of node 'n'?
bool Matcher::pd_clone_node(Node* n, Node* m, Matcher::MStack& mstack) {
  if (is_encode_and_store_pattern(n, m)) {
    mstack.push(m, Visit);
    return true;
  }
  return false;
}

// Should the Matcher clone shifts on addressing modes, expecting them
// to be subsumed into complex addressing expressions or compute them
// into registers?
bool Matcher::pd_clone_address_expressions(AddPNode* m, Matcher::MStack& mstack, VectorSet& address_visited) {
  return clone_base_plus_offset_address(m, mstack, address_visited);
}


#line 1130 "ad_s390.cpp"


//SourceForm

#line 2554 "/work/jdk/src/hotspot/cpu/s390/s390.ad"


  // Check whether outs are all Stores. If so, we can omit clearing the upper
  // 32 bits after encoding.
  static bool all_outs_are_Stores(const Node *n) {
    for (DUIterator_Fast imax, k = n->fast_outs(imax); k < imax; k++) {
      Node *out = n->fast_out(k);
      if (!out->is_Mach() || out->as_Mach()->ideal_Opcode() != Op_StoreN) {
        // Most other outs are SpillCopy, but there are various other.
        // jvm98 has arond 9% Encodes where we return false.
        return false;
      }
    }
    return true;
  }


#line 1153 "ad_s390.cpp"


//SourceForm

#line 32 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"


#include "gc/g1/g1BarrierSetAssembler_s390.hpp"
#include "gc/g1/g1BarrierSetRuntime.hpp"

static void write_barrier_pre(MacroAssembler* masm,
                              const MachNode* node,
                              Register obj,
                              Register pre_val,
                              Register tmp1,
                              RegSet preserve = RegSet(),
                              RegSet no_preserve = RegSet()) {
  if (!G1PreBarrierStubC2::needs_barrier(node)) {
    return;
  }
  Assembler::InlineSkippedInstructionsCounter skip_counter(masm);
  G1BarrierSetAssembler* g1_asm = static_cast<G1BarrierSetAssembler*>(BarrierSet::barrier_set()->barrier_set_assembler());
  G1PreBarrierStubC2* const stub = G1PreBarrierStubC2::create(node);
  for (RegSetIterator<Register> reg = preserve.begin(); *reg != noreg; ++reg) {
    stub->preserve(*reg);
  }
  for (RegSetIterator<Register> reg = no_preserve.begin(); *reg != noreg; ++reg) {
    stub->dont_preserve(*reg);
  }
  g1_asm->g1_write_barrier_pre_c2(masm, obj, pre_val, Z_thread, tmp1, stub);
}

static void write_barrier_post(MacroAssembler* masm,
                               const MachNode* node,
                               Register store_addr,
                               Register new_val,
                               Register tmp1,
                               Register tmp2) {
  if (!G1BarrierStubC2::needs_post_barrier(node)) {
    return;
  }
  Assembler::InlineSkippedInstructionsCounter skip_counter(masm);
  G1BarrierSetAssembler* g1_asm = static_cast<G1BarrierSetAssembler*>(BarrierSet::barrier_set()->barrier_set_assembler());
  bool new_val_may_be_null = G1BarrierStubC2::post_new_val_may_be_null(node);
  g1_asm->g1_write_barrier_post_c2(masm, store_addr, new_val, Z_thread, tmp1, tmp2, new_val_may_be_null);
}


#line 1202 "ad_s390.cpp"


#ifndef PRODUCT
void Compile::adlc_verification() {

  // Following assertions generated from definition section
  assert( DEFAULT_COST == 100, "Expect (100) to equal 100");
  assert( DEFAULT_COST_LOW == 80, "Expect (80) to equal 80");
  assert( DEFAULT_COST_HIGH == 120, "Expect (120) to equal 120");
  assert( HUGE_COST == 1000000, "Expect (1000000) to equal 1000000");
  assert( ALU_REG_COST == 100, "Expect (DEFAULT_COST) to equal 100");
  assert( ALU_MEMORY_COST == 150, "Expect (150) to equal 150");
  assert( MEMORY_REF_COST_HI == 220, "Expect (2 * DEFAULT_COST+20) to equal 220");
  assert( MEMORY_REF_COST == 200, "Expect (2 * DEFAULT_COST) to equal 200");
  assert( MEMORY_REF_COST_LO == 180, "Expect (2 * DEFAULT_COST-20) to equal 180");
  assert( BRANCH_COST == 300, "Expect (DEFAULT_COST * 3) to equal 300");
  assert( CALL_COST == 300, "Expect (DEFAULT_COST * 3) to equal 300");
}
#endif

// Map from machine-independent register number to register_save_policy
const        char register_save_policy[] = {
  'C', // Z_R13
  'C', // Z_R13_H
  'C', // Z_R12
  'C', // Z_R12_H
  'C', // Z_R11
  'C', // Z_R11_H
  'C', // Z_R10
  'C', // Z_R10_H
  'C', // Z_R9
  'C', // Z_R9_H
  'C', // Z_R8
  'C', // Z_R8_H
  'C', // Z_R7
  'C', // Z_R7_H
  'C', // Z_R1
  'C', // Z_R1_H
  'C', // Z_R0
  'C', // Z_R0_H
  'C', // Z_R6
  'C', // Z_R6_H
  'C', // Z_R5
  'C', // Z_R5_H
  'C', // Z_R4
  'C', // Z_R4_H
  'C', // Z_R3
  'C', // Z_R3_H
  'C', // Z_R2
  'C', // Z_R2_H
  'N', // Z_R14
  'N', // Z_R14_H
  'N', // Z_R15
  'N', // Z_R15_H
  'C', // Z_F15
  'C', // Z_F15_H
  'C', // Z_F14
  'C', // Z_F14_H
  'C', // Z_F13
  'C', // Z_F13_H
  'C', // Z_F12
  'C', // Z_F12_H
  'C', // Z_F11
  'C', // Z_F11_H
  'C', // Z_F10
  'C', // Z_F10_H
  'C', // Z_F9
  'C', // Z_F9_H
  'C', // Z_F8
  'C', // Z_F8_H
  'C', // Z_F7
  'C', // Z_F7_H
  'C', // Z_F5
  'C', // Z_F5_H
  'C', // Z_F3
  'C', // Z_F3_H
  'C', // Z_F1
  'C', // Z_F1_H
  'C', // Z_F6
  'C', // Z_F6_H
  'C', // Z_F4
  'C', // Z_F4_H
  'C', // Z_F2
  'C', // Z_F2_H
  'C', // Z_F0
  'C', // Z_F0_H
  'C', // Z_VR0
  'C', // Z_VR0_H
  'C', // Z_VR0_J
  'C', // Z_VR0_K
  'C', // Z_VR1
  'C', // Z_VR1_H
  'C', // Z_VR1_J
  'C', // Z_VR1_K
  'C', // Z_VR2
  'C', // Z_VR2_H
  'C', // Z_VR2_J
  'C', // Z_VR2_K
  'C', // Z_VR3
  'C', // Z_VR3_H
  'C', // Z_VR3_J
  'C', // Z_VR3_K
  'C', // Z_VR4
  'C', // Z_VR4_H
  'C', // Z_VR4_J
  'C', // Z_VR4_K
  'C', // Z_VR5
  'C', // Z_VR5_H
  'C', // Z_VR5_J
  'C', // Z_VR5_K
  'C', // Z_VR6
  'C', // Z_VR6_H
  'C', // Z_VR6_J
  'C', // Z_VR6_K
  'C', // Z_VR7
  'C', // Z_VR7_H
  'C', // Z_VR7_J
  'C', // Z_VR7_K
  'C', // Z_VR8
  'C', // Z_VR8_H
  'C', // Z_VR8_J
  'C', // Z_VR8_K
  'C', // Z_VR9
  'C', // Z_VR9_H
  'C', // Z_VR9_J
  'C', // Z_VR9_K
  'C', // Z_VR10
  'C', // Z_VR10_H
  'C', // Z_VR10_J
  'C', // Z_VR10_K
  'C', // Z_VR11
  'C', // Z_VR11_H
  'C', // Z_VR11_J
  'C', // Z_VR11_K
  'C', // Z_VR12
  'C', // Z_VR12_H
  'C', // Z_VR12_J
  'C', // Z_VR12_K
  'C', // Z_VR13
  'C', // Z_VR13_H
  'C', // Z_VR13_J
  'C', // Z_VR13_K
  'C', // Z_VR14
  'C', // Z_VR14_H
  'C', // Z_VR14_J
  'C', // Z_VR14_K
  'C', // Z_VR15
  'C', // Z_VR15_H
  'C', // Z_VR15_J
  'C', // Z_VR15_K
  'C', // Z_VR16
  'C', // Z_VR16_H
  'C', // Z_VR16_J
  'C', // Z_VR16_K
  'C', // Z_VR17
  'C', // Z_VR17_H
  'C', // Z_VR17_J
  'C', // Z_VR17_K
  'C', // Z_VR18
  'C', // Z_VR18_H
  'C', // Z_VR18_J
  'C', // Z_VR18_K
  'C', // Z_VR19
  'C', // Z_VR19_H
  'C', // Z_VR19_J
  'C', // Z_VR19_K
  'C', // Z_VR20
  'C', // Z_VR20_H
  'C', // Z_VR20_J
  'C', // Z_VR20_K
  'C', // Z_VR21
  'C', // Z_VR21_H
  'C', // Z_VR21_J
  'C', // Z_VR21_K
  'C', // Z_VR22
  'C', // Z_VR22_H
  'C', // Z_VR22_J
  'C', // Z_VR22_K
  'C', // Z_VR23
  'C', // Z_VR23_H
  'C', // Z_VR23_J
  'C', // Z_VR23_K
  'C', // Z_VR24
  'C', // Z_VR24_H
  'C', // Z_VR24_J
  'C', // Z_VR24_K
  'C', // Z_VR25
  'C', // Z_VR25_H
  'C', // Z_VR25_J
  'C', // Z_VR25_K
  'C', // Z_VR26
  'C', // Z_VR26_H
  'C', // Z_VR26_J
  'C', // Z_VR26_K
  'C', // Z_VR27
  'C', // Z_VR27_H
  'C', // Z_VR27_J
  'C', // Z_VR27_K
  'C', // Z_VR28
  'C', // Z_VR28_H
  'C', // Z_VR28_J
  'C', // Z_VR28_K
  'C', // Z_VR29
  'C', // Z_VR29_H
  'C', // Z_VR29_J
  'C', // Z_VR29_K
  'C', // Z_VR30
  'C', // Z_VR30_H
  'C', // Z_VR30_J
  'C', // Z_VR30_K
  'C', // Z_VR31
  'C', // Z_VR31_H
  'C', // Z_VR31_J
  'C', // Z_VR31_K
  'C' // no trailing comma // Z_CR
};

// Map from machine-independent register number to c_reg_save_policy
const        char c_reg_save_policy[] = {
  'E', // Z_R13
  'E', // Z_R13_H
  'E', // Z_R12
  'E', // Z_R12_H
  'E', // Z_R11
  'E', // Z_R11_H
  'E', // Z_R10
  'E', // Z_R10_H
  'E', // Z_R9
  'E', // Z_R9_H
  'E', // Z_R8
  'E', // Z_R8_H
  'E', // Z_R7
  'E', // Z_R7_H
  'C', // Z_R1
  'C', // Z_R1_H
  'C', // Z_R0
  'C', // Z_R0_H
  'E', // Z_R6
  'E', // Z_R6_H
  'C', // Z_R5
  'C', // Z_R5_H
  'C', // Z_R4
  'C', // Z_R4_H
  'C', // Z_R3
  'C', // Z_R3_H
  'C', // Z_R2
  'C', // Z_R2_H
  'N', // Z_R14
  'N', // Z_R14_H
  'N', // Z_R15
  'N', // Z_R15_H
  'E', // Z_F15
  'E', // Z_F15_H
  'E', // Z_F14
  'E', // Z_F14_H
  'E', // Z_F13
  'E', // Z_F13_H
  'E', // Z_F12
  'E', // Z_F12_H
  'E', // Z_F11
  'E', // Z_F11_H
  'E', // Z_F10
  'E', // Z_F10_H
  'E', // Z_F9
  'E', // Z_F9_H
  'E', // Z_F8
  'E', // Z_F8_H
  'C', // Z_F7
  'C', // Z_F7_H
  'C', // Z_F5
  'C', // Z_F5_H
  'C', // Z_F3
  'C', // Z_F3_H
  'C', // Z_F1
  'C', // Z_F1_H
  'C', // Z_F6
  'C', // Z_F6_H
  'C', // Z_F4
  'C', // Z_F4_H
  'C', // Z_F2
  'C', // Z_F2_H
  'C', // Z_F0
  'C', // Z_F0_H
  'C', // Z_VR0
  'C', // Z_VR0_H
  'C', // Z_VR0_J
  'C', // Z_VR0_K
  'C', // Z_VR1
  'C', // Z_VR1_H
  'C', // Z_VR1_J
  'C', // Z_VR1_K
  'C', // Z_VR2
  'C', // Z_VR2_H
  'C', // Z_VR2_J
  'C', // Z_VR2_K
  'C', // Z_VR3
  'C', // Z_VR3_H
  'C', // Z_VR3_J
  'C', // Z_VR3_K
  'C', // Z_VR4
  'C', // Z_VR4_H
  'C', // Z_VR4_J
  'C', // Z_VR4_K
  'C', // Z_VR5
  'C', // Z_VR5_H
  'C', // Z_VR5_J
  'C', // Z_VR5_K
  'C', // Z_VR6
  'C', // Z_VR6_H
  'C', // Z_VR6_J
  'C', // Z_VR6_K
  'C', // Z_VR7
  'C', // Z_VR7_H
  'C', // Z_VR7_J
  'C', // Z_VR7_K
  'C', // Z_VR8
  'C', // Z_VR8_H
  'C', // Z_VR8_J
  'C', // Z_VR8_K
  'C', // Z_VR9
  'C', // Z_VR9_H
  'C', // Z_VR9_J
  'C', // Z_VR9_K
  'C', // Z_VR10
  'C', // Z_VR10_H
  'C', // Z_VR10_J
  'C', // Z_VR10_K
  'C', // Z_VR11
  'C', // Z_VR11_H
  'C', // Z_VR11_J
  'C', // Z_VR11_K
  'C', // Z_VR12
  'C', // Z_VR12_H
  'C', // Z_VR12_J
  'C', // Z_VR12_K
  'C', // Z_VR13
  'C', // Z_VR13_H
  'C', // Z_VR13_J
  'C', // Z_VR13_K
  'C', // Z_VR14
  'C', // Z_VR14_H
  'C', // Z_VR14_J
  'C', // Z_VR14_K
  'C', // Z_VR15
  'C', // Z_VR15_H
  'C', // Z_VR15_J
  'C', // Z_VR15_K
  'C', // Z_VR16
  'C', // Z_VR16_H
  'C', // Z_VR16_J
  'C', // Z_VR16_K
  'C', // Z_VR17
  'C', // Z_VR17_H
  'C', // Z_VR17_J
  'C', // Z_VR17_K
  'C', // Z_VR18
  'C', // Z_VR18_H
  'C', // Z_VR18_J
  'C', // Z_VR18_K
  'C', // Z_VR19
  'C', // Z_VR19_H
  'C', // Z_VR19_J
  'C', // Z_VR19_K
  'C', // Z_VR20
  'C', // Z_VR20_H
  'C', // Z_VR20_J
  'C', // Z_VR20_K
  'C', // Z_VR21
  'C', // Z_VR21_H
  'C', // Z_VR21_J
  'C', // Z_VR21_K
  'C', // Z_VR22
  'C', // Z_VR22_H
  'C', // Z_VR22_J
  'C', // Z_VR22_K
  'C', // Z_VR23
  'C', // Z_VR23_H
  'C', // Z_VR23_J
  'C', // Z_VR23_K
  'C', // Z_VR24
  'C', // Z_VR24_H
  'C', // Z_VR24_J
  'C', // Z_VR24_K
  'C', // Z_VR25
  'C', // Z_VR25_H
  'C', // Z_VR25_J
  'C', // Z_VR25_K
  'C', // Z_VR26
  'C', // Z_VR26_H
  'C', // Z_VR26_J
  'C', // Z_VR26_K
  'C', // Z_VR27
  'C', // Z_VR27_H
  'C', // Z_VR27_J
  'C', // Z_VR27_K
  'C', // Z_VR28
  'C', // Z_VR28_H
  'C', // Z_VR28_J
  'C', // Z_VR28_K
  'C', // Z_VR29
  'C', // Z_VR29_H
  'C', // Z_VR29_J
  'C', // Z_VR29_K
  'C', // Z_VR30
  'C', // Z_VR30_H
  'C', // Z_VR30_J
  'C', // Z_VR30_K
  'C', // Z_VR31
  'C', // Z_VR31_H
  'C', // Z_VR31_J
  'C', // Z_VR31_K
  'C' // no trailing comma // Z_CR
};

// Map from machine-independent register number to register_save_type
const        int register_save_type[] = {
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegI,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegF,
  Op_RegFlags // no trailing comma
};


const        int   reduceOp[] = {
  /*    0 */  0,
  /*    1 */  0,
  /*    2 */  0,
  /*    3 */  0,
  /*    4 */  0,
  /*    5 */  0,
  /*    6 */  0,
  /*    7 */  0,
  /*    8 */  vecX_rule,
  /*    9 */  v16TempReg_rule,
  /*   10 */  v17TempReg_rule,
  /*   11 */  v18TempReg_rule,
  /*   12 */  v19TempReg_rule,
  /*   13 */  v20TempReg_rule,
  /*   14 */  v21TempReg_rule,
  /*   15 */  v22TempReg_rule,
  /*   16 */  v23TempReg_rule,
  /*   17 */  v24TempReg_rule,
  /*   18 */  v25TempReg_rule,
  /*   19 */  immB_minus1_rule,
  /*   20 */  immB_n0m1_rule,
  /*   21 */  immS_minus1_rule,
  /*   22 */  immS_n0m1_rule,
  /*   23 */  immI_rule,
  /*   24 */  immI20_rule,
  /*   25 */  immI16_rule,
  /*   26 */  immI8_rule,
  /*   27 */  immI_0_rule,
  /*   28 */  immI_minus1_rule,
  /*   29 */  immI_n0m1_rule,
  /*   30 */  uimmI_rule,
  /*   31 */  uimmI16_rule,
  /*   32 */  uimmI12_rule,
  /*   33 */  uimmI8_rule,
  /*   34 */  SSlenDW_rule,
  /*   35 */  immI_1_rule,
  /*   36 */  immI_16_rule,
  /*   37 */  immI_24_rule,
  /*   38 */  immI_32_63_rule,
  /*   39 */  uimmI_LL1_rule,
  /*   40 */  uimmI_LH1_rule,
  /*   41 */  immL_rule,
  /*   42 */  immL32_rule,
  /*   43 */  immL20_rule,
  /*   44 */  immL16_rule,
  /*   45 */  immL8_rule,
  /*   46 */  uimmL32_rule,
  /*   47 */  uimmL16_rule,
  /*   48 */  uimmL12_rule,
  /*   49 */  immL_FFFFFFFF_rule,
  /*   50 */  immL_0_rule,
  /*   51 */  uimmL_LL1_rule,
  /*   52 */  uimmL_LH1_rule,
  /*   53 */  uimmL_HL1_rule,
  /*   54 */  uimmL_HH1_rule,
  /*   55 */  immL_32bits_rule,
  /*   56 */  immP_rule,
  /*   57 */  immP16_rule,
  /*   58 */  immP8_rule,
  /*   59 */  immP0_rule,
  /*   60 */  immN_rule,
  /*   61 */  immNKlass_rule,
  /*   62 */  immN8_rule,
  /*   63 */  immN0_rule,
  /*   64 */  immD_rule,
  /*   65 */  immDpm0_rule,
  /*   66 */  immDp0_rule,
  /*   67 */  immF_rule,
  /*   68 */  immFpm0_rule,
  /*   69 */  immFp0_rule,
  /*   70 */  iRegI_rule,
  /*   71 */  noArg_iRegI_rule,
  /*   72 */  revenRegI_rule,
  /*   73 */  roddRegI_rule,
  /*   74 */  rarg1RegI_rule,
  /*   75 */  rarg2RegI_rule,
  /*   76 */  rarg3RegI_rule,
  /*   77 */  rarg4RegI_rule,
  /*   78 */  rarg5RegI_rule,
  /*   79 */  noOdd_iRegI_rule,
  /*   80 */  iRegP_rule,
  /*   81 */  threadRegP_rule,
  /*   82 */  r10TempRegP_rule,
  /*   83 */  r11TempRegP_rule,
  /*   84 */  noArg_iRegP_rule,
  /*   85 */  rarg1RegP_rule,
  /*   86 */  rarg2RegP_rule,
  /*   87 */  rarg3RegP_rule,
  /*   88 */  rarg4RegP_rule,
  /*   89 */  rarg5RegP_rule,
  /*   90 */  memoryRegP_rule,
  /*   91 */  revenRegP_rule,
  /*   92 */  roddRegP_rule,
  /*   93 */  iRegN_rule,
  /*   94 */  noArg_iRegN_rule,
  /*   95 */  rarg1RegN_rule,
  /*   96 */  rarg2RegN_rule,
  /*   97 */  rarg3RegN_rule,
  /*   98 */  rarg4RegN_rule,
  /*   99 */  rarg5RegN_rule,
  /*  100 */  iRegL_rule,
  /*  101 */  revenRegL_rule,
  /*  102 */  roddRegL_rule,
  /*  103 */  allRoddRegL_rule,
  /*  104 */  rarg1RegL_rule,
  /*  105 */  rarg5RegL_rule,
  /*  106 */  flagsReg_rule,
  /*  107 */  regD_rule,
  /*  108 */  regF_rule,
  /*  109 */  inline_cache_regP_rule,
  /*  110 */  indirect_rule,
  /*  111 */  indOffset20_rule,
  /*  112 */  indOffset20Narrow_rule,
  /*  113 */  indOffset12_rule,
  /*  114 */  indOffset12Narrow_rule,
  /*  115 */  indIndex_rule,
  /*  116 */  indOffset20index_rule,
  /*  117 */  indOffset20indexNarrow_rule,
  /*  118 */  indOffset12index_rule,
  /*  119 */  indOffset12indexNarrow_rule,
  /*  120 */  stackSlotI_rule,
  /*  121 */  stackSlotP_rule,
  /*  122 */  stackSlotF_rule,
  /*  123 */  stackSlotD_rule,
  /*  124 */  stackSlotL_rule,
  /*  125 */  cmpOpT_rule,
  /*  126 */  cmpOpF_rule,
  /*  127 */  cmpOp_rule,
  // last operand
  /*  128 */  memory_rule,
  /*  129 */  memoryRXY_rule,
  /*  130 */  memoryRX_rule,
  /*  131 */  memoryRSY_rule,
  /*  132 */  memoryRS_rule,
  /*  133 */  iRegN_P2N_rule,
  /*  134 */  iRegP_N2P_rule,
  // last operand class
  /*  135 */  _DecodeN_iRegN__rule,
  /*  136 */  _AddP_memoryRegP_iRegL_rule,
  /*  137 */  _AddP__DecodeN_iRegN__iRegL_rule,
  /*  138 */  _LoadB_memory__rule,
  /*  139 */  _LoadUB_memory__rule,
  /*  140 */  _LoadS_memory__rule,
  /*  141 */  _LoadUS_memory__rule,
  /*  142 */  _LoadI_memory__rule,
  /*  143 */  _ConvI2L__LoadI_memory___rule,
  /*  144 */  _LoadP_memory__rule,
  /*  145 */  _LoadN_memory__rule,
  /*  146 */  _LoadNKlass_memory__rule,
  /*  147 */  _Binary_iRegL_iRegN_rule,
  /*  148 */  _Binary_cmpOp_flagsReg_rule,
  /*  149 */  _Binary_iRegN_iRegN_P2N_rule,
  /*  150 */  _Binary_iRegN_immN0_rule,
  /*  151 */  _Binary_iRegI_iRegI_rule,
  /*  152 */  _Binary_iRegI_immI16_rule,
  /*  153 */  _Binary_iRegP_iRegP_N2P_rule,
  /*  154 */  _Binary_iRegP_immP0_rule,
  /*  155 */  _Binary_cmpOpF_flagsReg_rule,
  /*  156 */  _Binary_regF_regF_rule,
  /*  157 */  _Binary_regD_regD_rule,
  /*  158 */  _Binary_iRegL_iRegL_rule,
  /*  159 */  _Binary_iRegL_immL16_rule,
  /*  160 */  _Binary_rarg5RegI_iRegI_rule,
  /*  161 */  _Binary_rarg5RegL_iRegL_rule,
  /*  162 */  _Binary_rarg5RegP_iRegP_N2P_rule,
  /*  163 */  _Binary_rarg5RegN_iRegN_P2N_rule,
  /*  164 */  _AddI_iRegI_iRegI_rule,
  /*  165 */  _LoadI_memoryRSY__rule,
  /*  166 */  _AddI__LoadI_memoryRSY__immI8_rule,
  /*  167 */  _ConvI2L_iRegI__rule,
  /*  168 */  _LoadL_memory__rule,
  /*  169 */  _AddL_iRegL_iRegL_rule,
  /*  170 */  _LoadL_memoryRSY__rule,
  /*  171 */  _AddL__LoadL_memoryRSY__immL8_rule,
  /*  172 */  _AddP_iRegP_N2P_iRegL_rule,
  /*  173 */  _LoadP_memoryRSY__rule,
  /*  174 */  _AddP__LoadP_memoryRSY__immL8_rule,
  /*  175 */  _CastP2X_iRegP_N2P__rule,
  /*  176 */  _LShiftI_iRegI_immI8_rule,
  /*  177 */  _URShiftI_iRegI_immI8_rule,
  /*  178 */  _LShiftL_iRegL_immI8_rule,
  /*  179 */  _URShiftL_iRegL_immI8_rule,
  /*  180 */  _LoadF_memoryRX__rule,
  /*  181 */  _LoadD_memoryRX__rule,
  /*  182 */  _NegF_regF__rule,
  /*  183 */  _NegD_regD__rule,
  /*  184 */  _Binary_regF__LoadF_memoryRX__rule,
  /*  185 */  _Binary_regD__LoadD_memoryRX__rule,
  /*  186 */  _Binary__LoadF_memoryRX__regF_rule,
  /*  187 */  _Binary__LoadD_memoryRX__regD_rule,
  /*  188 */  _AbsF_regF__rule,
  /*  189 */  _AbsD_regD__rule,
  /*  190 */  _LShiftI_iRegI_immI_16_rule,
  /*  191 */  _LShiftI_iRegI_immI_24_rule,
  /*  192 */  _RShiftL_iRegL_immI_32_63_rule,
  /*  193 */  _CmpU_iRegI_uimmI16_rule,
  /*  194 */  _CmpU_iRegI_iRegI_rule,
  /*  195 */  _CmpP_iRegP_N2P_immP0_rule,
  /*  196 */  _CmpN_iRegN_P2N_immN0_rule,
  /*  197 */  _AbsI_iRegI__rule,
  /*  198 */  _CmpI_iRegI_iRegI_rule,
  /*  199 */  _CmpL_iRegL_iRegL_rule,
  /*  200 */  _CmpP_iRegP_iRegP_rule,
  /*  201 */  _CmpP__DecodeN_iRegN___DecodeN_iRegN__rule,
  /*  202 */  _CmpI_iRegI_immI8_rule,
  /*  203 */  _CmpU_iRegI_uimmI8_rule,
  /*  204 */  _CmpL_iRegL_immL8_rule,
  /*  205 */  _CmpP_iRegP_immP8_rule,
  /*  206 */  _CmpP__DecodeN_iRegN__immP0_rule,
  /*  207 */  _DecodeN_immN8__rule,
  /*  208 */  _CmpP__DecodeN_iRegN___DecodeN_immN8__rule,
  /*  209 */  _Binary_rarg1RegP_immP_rule,
  /*  210 */  _Binary_iRegP_iRegP_rule,
  /*  211 */  _Binary_iRegP_rarg2RegI_rule,
  /*  212 */  _Binary_iRegP_rarg5RegI_rule,
  /*  213 */  _Binary_iRegP_iRegI_rule,
  /*  214 */  _Binary_immP_immI_1_rule,
  /*  215 */  _Binary_iRegP_immI16_rule,
  /*  216 */  _Binary_iRegP_immI_rule,
  /*  217 */  _EncodeP_iRegP__rule,
  // last internally defined operand
  /*  218 */  stackSlotI_rule,
  /*  219 */  stackSlotL_rule,
  /*  220 */  stackSlotP_rule,
  /*  221 */  stackSlotF_rule,
  /*  222 */  stackSlotD_rule,
  /*  223 */  stackSlotD_rule,
  /*  224 */  stackSlotF_rule,
  /*  225 */  iRegI_rule,
  /*  226 */  iRegL_rule,
  /*  227 */  iRegP_rule,
  /*  228 */  regF_rule,
  /*  229 */  regD_rule,
  /*  230 */  iRegI_rule,
  /*  231 */  iRegI_rule,
  /*  232 */  iRegI_rule,
  /*  233 */  iRegI_rule,
  /*  234 */  iRegL_rule,
  /*  235 */  iRegL_rule,
  /*  236 */  iRegL_rule,
  /*  237 */  iRegL_rule,
  /*  238 */  iRegP_rule,
  /*  239 */  iRegP_rule,
  /*  240 */  regF_rule,
  /*  241 */  regD_rule,
  /*  242 */  regF_rule,
  /*  243 */  regD_rule,
  /*  244 */  iRegN_rule,
  /*  245 */  iRegN_rule,
  /*  246 */  iRegN_rule,
  /*  247 */  iRegL_rule,
  /*  248 */  0,
  /*  249 */  flagsReg_rule,
  /*  250 */  flagsReg_rule,
  /*  251 */  flagsReg_rule,
  /*  252 */  flagsReg_rule,
  /*  253 */  iRegP_rule,
  /*  254 */  iRegL_rule,
  /*  255 */  threadRegP_rule,
  /*  256 */  iRegP_rule,
  /*  257 */  iRegP_rule,
  /*  258 */  iRegI_rule,
  /*  259 */  iRegL_rule,
  /*  260 */  regF_rule,
  /*  261 */  regD_rule,
  /*  262 */  iRegL_rule,
  /*  263 */  flagsReg_rule,
  /*  264 */  flagsReg_rule,
  /*  265 */  flagsReg_rule,
  /*  266 */  flagsReg_rule,
  /*  267 */  flagsReg_rule,
  /*  268 */  flagsReg_rule,
  /*  269 */  flagsReg_rule,
  /*  270 */  flagsReg_rule,
  /*  271 */  flagsReg_rule,
  /*  272 */  flagsReg_rule,
  /*  273 */  iRegI_rule,
  /*  274 */  regF_rule,
  /*  275 */  iRegL_rule,
  /*  276 */  regD_rule,
  /*  277 */  flagsReg_rule,
  /*  278 */  flagsReg_rule,
  /*  279 */  flagsReg_rule,
  /*  280 */  flagsReg_rule,
  /*  281 */  flagsReg_rule,
  /*  282 */  flagsReg_rule,
  /*  283 */  flagsReg_rule,
  /*  284 */  flagsReg_rule,
  /*  285 */  flagsReg_rule,
  /*  286 */  flagsReg_rule,
  /*  287 */  flagsReg_rule,
  /*  288 */  flagsReg_rule,
  /*  289 */  flagsReg_rule,
  /*  290 */  flagsReg_rule,
  /*  291 */  flagsReg_rule,
  /*  292 */  flagsReg_rule,
  /*  293 */  flagsReg_rule,
  /*  294 */  flagsReg_rule,
  /*  295 */  flagsReg_rule,
  /*  296 */  flagsReg_rule,
  /*  297 */  flagsReg_rule,
  /*  298 */  flagsReg_rule,
  /*  299 */  flagsReg_rule,
  /*  300 */  flagsReg_rule,
  /*  301 */  flagsReg_rule,
  /*  302 */  flagsReg_rule,
  /*  303 */  flagsReg_rule,
  /*  304 */  flagsReg_rule,
  /*  305 */  flagsReg_rule,
  /*  306 */  flagsReg_rule,
  /*  307 */  0,
  /*  308 */  iRegL_rule,
  /*  309 */  iRegL_rule,
  /*  310 */  iRegL_rule,
  /*  311 */  iRegL_rule,
  /*  312 */  iRegL_rule,
  /*  313 */  iRegL_rule,
  /*  314 */  vecX_rule,
  /*  315 */  vecX_rule,
  /*  316 */  vecX_rule,
  /*  317 */  iRegL_rule,
  /*  318 */  iRegL_rule,
  /*  319 */  iRegL_rule,
  /*  320 */  vecX_rule,
  /*  321 */  vecX_rule,
  /*  322 */  vecX_rule,
  /*  323 */  iRegL_rule,
  /*  324 */  iRegL_rule,
  /*  325 */  vecX_rule,
  /*  326 */  vecX_rule,
  /*  327 */  vecX_rule,
  /*  328 */  vecX_rule,
  /*  329 */  vecX_rule,
  /*  330 */  vecX_rule,
  /*  331 */  vecX_rule,
  /*  332 */  vecX_rule,
  /*  333 */  vecX_rule,
  /*  334 */  vecX_rule,
  /*  335 */  iRegL_rule,
  /*  336 */  vecX_rule,
  /*  337 */  vecX_rule,
  /*  338 */  vecX_rule,
  /*  339 */  vecX_rule,
  /*  340 */  iRegI_rule,
  /*  341 */  iRegL_rule,
  /*  342 */  iRegI_rule,
  /*  343 */  iRegL_rule,
  /*  344 */  iRegI_rule,
  /*  345 */  iRegL_rule,
  /*  346 */  iRegI_rule,
  /*  347 */  iRegL_rule,
  /*  348 */  iRegI_rule,
  /*  349 */  iRegL_rule,
  /*  350 */  iRegL_rule,
  /*  351 */  iRegI_rule,
  /*  352 */  iRegL_rule,
  /*  353 */  iRegL_rule,
  /*  354 */  iRegP_rule,
  /*  355 */  iRegP_rule,
  /*  356 */  0,
  /*  357 */  regF_rule,
  /*  358 */  regD_rule,
  /*  359 */  regD_rule,
  /*  360 */  Universe_rule,
  /*  361 */  Universe_rule,
  /*  362 */  Universe_rule,
  /*  363 */  Universe_rule,
  /*  364 */  Universe_rule,
  /*  365 */  Universe_rule,
  /*  366 */  Universe_rule,
  /*  367 */  Universe_rule,
  /*  368 */  Universe_rule,
  /*  369 */  Universe_rule,
  /*  370 */  Universe_rule,
  /*  371 */  Universe_rule,
  /*  372 */  Universe_rule,
  /*  373 */  iRegL_rule,
  /*  374 */  iRegN_rule,
  /*  375 */  iRegN_rule,
  /*  376 */  iRegN_rule,
  /*  377 */  iRegP_rule,
  /*  378 */  iRegP_rule,
  /*  379 */  iRegP_rule,
  /*  380 */  iRegP_rule,
  /*  381 */  iRegP_rule,
  /*  382 */  iRegP_rule,
  /*  383 */  iRegP_rule,
  /*  384 */  iRegP_rule,
  /*  385 */  iRegP_rule,
  /*  386 */  iRegP_rule,
  /*  387 */  iRegN_rule,
  /*  388 */  iRegN_rule,
  /*  389 */  iRegN_rule,
  /*  390 */  iRegN_rule,
  /*  391 */  iRegN_rule,
  /*  392 */  iRegN_rule,
  /*  393 */  iRegN_rule,
  /*  394 */  Universe_rule,
  /*  395 */  Universe_rule,
  /*  396 */  Universe_rule,
  /*  397 */  Universe_rule,
  /*  398 */  Universe_rule,
  /*  399 */  Universe_rule,
  /*  400 */  Universe_rule,
  /*  401 */  Universe_rule,
  /*  402 */  Universe_rule,
  /*  403 */  Universe_rule,
  /*  404 */  Universe_rule,
  /*  405 */  Universe_rule,
  /*  406 */  Universe_rule,
  /*  407 */  Universe_rule,
  /*  408 */  Universe_rule,
  /*  409 */  iRegN_rule,
  /*  410 */  iRegN_rule,
  /*  411 */  iRegI_rule,
  /*  412 */  iRegI_rule,
  /*  413 */  iRegP_rule,
  /*  414 */  iRegP_rule,
  /*  415 */  regF_rule,
  /*  416 */  regD_rule,
  /*  417 */  iRegL_rule,
  /*  418 */  iRegL_rule,
  /*  419 */  iRegI_rule,
  /*  420 */  iRegI_rule,
  /*  421 */  iRegI_rule,
  /*  422 */  iRegI_rule,
  /*  423 */  Universe_rule,
  /*  424 */  iRegI_rule,
  /*  425 */  iRegI_rule,
  /*  426 */  iRegI_rule,
  /*  427 */  Universe_rule,
  /*  428 */  iRegL_rule,
  /*  429 */  iRegL_rule,
  /*  430 */  iRegL_rule,
  /*  431 */  iRegI_rule,
  /*  432 */  iRegL_rule,
  /*  433 */  iRegI_rule,
  /*  434 */  iRegL_rule,
  /*  435 */  iRegN_rule,
  /*  436 */  iRegP_rule,
  /*  437 */  iRegI_rule,
  /*  438 */  iRegI_rule,
  /*  439 */  iRegI_rule,
  /*  440 */  iRegI_rule,
  /*  441 */  iRegI_rule,
  /*  442 */  iRegI_rule,
  /*  443 */  iRegI_rule,
  /*  444 */  iRegI_rule,
  /*  445 */  iRegI_rule,
  /*  446 */  iRegI_rule,
  /*  447 */  iRegI_rule,
  /*  448 */  Universe_rule,
  /*  449 */  iRegL_rule,
  /*  450 */  iRegL_rule,
  /*  451 */  iRegL_rule,
  /*  452 */  iRegL_rule,
  /*  453 */  iRegL_rule,
  /*  454 */  iRegL_rule,
  /*  455 */  iRegL_rule,
  /*  456 */  iRegL_rule,
  /*  457 */  iRegL_rule,
  /*  458 */  iRegL_rule,
  /*  459 */  iRegL_rule,
  /*  460 */  iRegL_rule,
  /*  461 */  iRegL_rule,
  /*  462 */  iRegL_rule,
  /*  463 */  iRegL_rule,
  /*  464 */  Universe_rule,
  /*  465 */  iRegP_rule,
  /*  466 */  iRegP_rule,
  /*  467 */  iRegP_rule,
  /*  468 */  iRegP_rule,
  /*  469 */  iRegP_rule,
  /*  470 */  iRegP_rule,
  /*  471 */  iRegP_rule,
  /*  472 */  iRegP_rule,
  /*  473 */  iRegP_rule,
  /*  474 */  iRegP_rule,
  /*  475 */  iRegP_rule,
  /*  476 */  iRegP_rule,
  /*  477 */  Universe_rule,
  /*  478 */  iRegI_rule,
  /*  479 */  iRegI_rule,
  /*  480 */  iRegI_rule,
  /*  481 */  iRegI_rule,
  /*  482 */  iRegL_rule,
  /*  483 */  iRegL_rule,
  /*  484 */  iRegL_rule,
  /*  485 */  iRegL_rule,
  /*  486 */  iRegL_rule,
  /*  487 */  iRegI_rule,
  /*  488 */  iRegI_rule,
  /*  489 */  iRegI_rule,
  /*  490 */  iRegI_rule,
  /*  491 */  iRegI_rule,
  /*  492 */  iRegL_rule,
  /*  493 */  iRegL_rule,
  /*  494 */  iRegL_rule,
  /*  495 */  iRegL_rule,
  /*  496 */  iRegL_rule,
  /*  497 */  iRegL_rule,
  /*  498 */  iRegL_rule,
  /*  499 */  iRegL_rule,
  /*  500 */  iRegL_rule,
  /*  501 */  revenRegL_rule,
  /*  502 */  Universe_rule,
  /*  503 */  roddRegI_rule,
  /*  504 */  roddRegI_rule,
  /*  505 */  roddRegI_rule,
  /*  506 */  Universe_rule,
  /*  507 */  roddRegL_rule,
  /*  508 */  roddRegL_rule,
  /*  509 */  roddRegL_rule,
  /*  510 */  revenRegI_rule,
  /*  511 */  revenRegI_rule,
  /*  512 */  revenRegI_rule,
  /*  513 */  revenRegL_rule,
  /*  514 */  revenRegL_rule,
  /*  515 */  revenRegL_rule,
  /*  516 */  iRegI_rule,
  /*  517 */  iRegI_rule,
  /*  518 */  iRegI_rule,
  /*  519 */  iRegL_rule,
  /*  520 */  iRegL_rule,
  /*  521 */  iRegL_rule,
  /*  522 */  iRegI_rule,
  /*  523 */  iRegI_rule,
  /*  524 */  iRegL_rule,
  /*  525 */  iRegL_rule,
  /*  526 */  iRegI_rule,
  /*  527 */  iRegI_rule,
  /*  528 */  iRegL_rule,
  /*  529 */  iRegL_rule,
  /*  530 */  iRegL_rule,
  /*  531 */  iRegI_rule,
  /*  532 */  iRegI_rule,
  /*  533 */  iRegL_rule,
  /*  534 */  iRegL_rule,
  /*  535 */  iRegI_rule,
  /*  536 */  iRegI_rule,
  /*  537 */  iRegL_rule,
  /*  538 */  iRegL_rule,
  /*  539 */  regF_rule,
  /*  540 */  regF_rule,
  /*  541 */  regF_rule,
  /*  542 */  regD_rule,
  /*  543 */  regD_rule,
  /*  544 */  regD_rule,
  /*  545 */  regF_rule,
  /*  546 */  regF_rule,
  /*  547 */  regD_rule,
  /*  548 */  regD_rule,
  /*  549 */  regF_rule,
  /*  550 */  regF_rule,
  /*  551 */  regF_rule,
  /*  552 */  regD_rule,
  /*  553 */  regD_rule,
  /*  554 */  regD_rule,
  /*  555 */  regF_rule,
  /*  556 */  regD_rule,
  /*  557 */  regF_rule,
  /*  558 */  regD_rule,
  /*  559 */  regF_rule,
  /*  560 */  regD_rule,
  /*  561 */  regF_rule,
  /*  562 */  regD_rule,
  /*  563 */  regF_rule,
  /*  564 */  regD_rule,
  /*  565 */  regF_rule,
  /*  566 */  regD_rule,
  /*  567 */  regF_rule,
  /*  568 */  regF_rule,
  /*  569 */  regD_rule,
  /*  570 */  regD_rule,
  /*  571 */  regF_rule,
  /*  572 */  regD_rule,
  /*  573 */  regF_rule,
  /*  574 */  regD_rule,
  /*  575 */  regF_rule,
  /*  576 */  regD_rule,
  /*  577 */  regF_rule,
  /*  578 */  regD_rule,
  /*  579 */  regF_rule,
  /*  580 */  regD_rule,
  /*  581 */  iRegI_rule,
  /*  582 */  iRegI_rule,
  /*  583 */  iRegI_rule,
  /*  584 */  iRegI_rule,
  /*  585 */  iRegI_rule,
  /*  586 */  iRegI_rule,
  /*  587 */  iRegL_rule,
  /*  588 */  iRegL_rule,
  /*  589 */  iRegL_rule,
  /*  590 */  iRegL_rule,
  /*  591 */  iRegL_rule,
  /*  592 */  iRegL_rule,
  /*  593 */  iRegL_rule,
  /*  594 */  iRegI_rule,
  /*  595 */  iRegI_rule,
  /*  596 */  iRegI_rule,
  /*  597 */  iRegI_rule,
  /*  598 */  iRegI_rule,
  /*  599 */  iRegL_rule,
  /*  600 */  iRegL_rule,
  /*  601 */  iRegL_rule,
  /*  602 */  iRegL_rule,
  /*  603 */  iRegI_rule,
  /*  604 */  iRegI_rule,
  /*  605 */  iRegI_rule,
  /*  606 */  iRegI_rule,
  /*  607 */  iRegI_rule,
  /*  608 */  iRegL_rule,
  /*  609 */  iRegL_rule,
  /*  610 */  iRegL_rule,
  /*  611 */  iRegI_rule,
  /*  612 */  iRegI_rule,
  /*  613 */  iRegI_rule,
  /*  614 */  iRegI_rule,
  /*  615 */  regF_rule,
  /*  616 */  iRegI_rule,
  /*  617 */  iRegI_rule,
  /*  618 */  iRegL_rule,
  /*  619 */  iRegL_rule,
  /*  620 */  regD_rule,
  /*  621 */  regD_rule,
  /*  622 */  regD_rule,
  /*  623 */  regF_rule,
  /*  624 */  iRegL_rule,
  /*  625 */  iRegL_rule,
  /*  626 */  iRegL_rule,
  /*  627 */  iRegL_rule,
  /*  628 */  iRegI_rule,
  /*  629 */  iRegI_rule,
  /*  630 */  stackSlotF_rule,
  /*  631 */  stackSlotL_rule,
  /*  632 */  stackSlotD_rule,
  /*  633 */  regF_rule,
  /*  634 */  regD_rule,
  /*  635 */  iRegI_rule,
  /*  636 */  iRegI_rule,
  /*  637 */  Universe_rule,
  /*  638 */  Universe_rule,
  /*  639 */  Universe_rule,
  /*  640 */  Universe_rule,
  /*  641 */  Universe_rule,
  /*  642 */  iRegI_rule,
  /*  643 */  iRegI_rule,
  /*  644 */  iRegI_rule,
  /*  645 */  iRegI_rule,
  /*  646 */  iRegI_rule,
  /*  647 */  iRegI_rule,
  /*  648 */  iRegI_rule,
  /*  649 */  iRegI_rule,
  /*  650 */  iRegI_rule,
  /*  651 */  iRegI_rule,
  /*  652 */  iRegI_rule,
  /*  653 */  iRegI_rule,
  /*  654 */  iRegI_rule,
  /*  655 */  iRegI_rule,
  /*  656 */  iRegI_rule,
  /*  657 */  iRegI_rule,
  /*  658 */  iRegI_rule,
  /*  659 */  iRegL_rule,
  /*  660 */  iRegI_rule,
  /*  661 */  iRegI_rule,
  /*  662 */  iRegI_rule,
  /*  663 */  Universe_rule,
  /*  664 */  Universe_rule,
  /*  665 */  Universe_rule,
  /*  666 */  Universe_rule,
  /*  667 */  Universe_rule,
  /*  668 */  Universe_rule,
  /*  669 */  Universe_rule,
  /*  670 */  Universe_rule,
  /*  671 */  Universe_rule,
  /*  672 */  Universe_rule,
  /*  673 */  Universe_rule,
  /*  674 */  Universe_rule,
  /*  675 */  Universe_rule,
  /*  676 */  Universe_rule,
  /*  677 */  Universe_rule,
  /*  678 */  Universe_rule,
  /*  679 */  Universe_rule,
  /*  680 */  Universe_rule,
  /*  681 */  Universe_rule,
  /*  682 */  Universe_rule,
  /*  683 */  Universe_rule,
  /*  684 */  Universe_rule,
  /*  685 */  Universe_rule,
  /*  686 */  Universe_rule,
  /*  687 */  Universe_rule,
  /*  688 */  Universe_rule,
  /*  689 */  Universe_rule,
  /*  690 */  Universe_rule,
  /*  691 */  Universe_rule,
  /*  692 */  Universe_rule,
  /*  693 */  Universe_rule,
  /*  694 */  Universe_rule,
  /*  695 */  iRegI_rule,
  /*  696 */  Universe_rule,
  /*  697 */  Universe_rule,
  /*  698 */  Universe_rule,
  /*  699 */  Universe_rule,
  /*  700 */  Universe_rule,
  /*  701 */  Universe_rule,
  /*  702 */  Universe_rule,
  /*  703 */  Universe_rule,
  /*  704 */  Universe_rule,
  /*  705 */  Universe_rule,
  /*  706 */  Universe_rule,
  /*  707 */  rarg1RegP_rule,
  /*  708 */  Universe_rule,
  /*  709 */  Universe_rule,
  /*  710 */  rarg1RegP_rule,
  /*  711 */  r11TempRegP_rule,
  /*  712 */  r11TempRegP_rule,
  /*  713 */  Universe_rule,
  /*  714 */  Universe_rule,
  /*  715 */  Universe_rule,
  /*  716 */  iRegI_rule,
  /*  717 */  iRegI_rule,
  /*  718 */  iRegI_rule,
  /*  719 */  iRegI_rule,
  /*  720 */  iRegI_rule,
  /*  721 */  iRegI_rule,
  /*  722 */  iRegI_rule,
  /*  723 */  iRegI_rule,
  /*  724 */  iRegI_rule,
  /*  725 */  iRegI_rule,
  /*  726 */  iRegI_rule,
  /*  727 */  iRegI_rule,
  /*  728 */  iRegI_rule,
  /*  729 */  iRegI_rule,
  /*  730 */  iRegI_rule,
  /*  731 */  iRegI_rule,
  /*  732 */  iRegI_rule,
  /*  733 */  iRegI_rule,
  /*  734 */  iRegI_rule,
  /*  735 */  iRegI_rule,
  /*  736 */  iRegI_rule,
  /*  737 */  Universe_rule,
  /*  738 */  Universe_rule,
  /*  739 */  iRegI_rule,
  /*  740 */  iRegI_rule,
  /*  741 */  iRegI_rule,
  /*  742 */  0,
  /*  743 */  iRegL_rule,
  /*  744 */  iRegL_rule,
  /*  745 */  iRegL_rule,
  /*  746 */  iRegL_rule,
  /*  747 */  iRegL_rule,
  /*  748 */  iRegL_rule,
  /*  749 */  Universe_rule,
  /*  750 */  Universe_rule,
  /*  751 */  iRegL_rule,
  /*  752 */  vecX_rule,
  /*  753 */  vecX_rule,
  /*  754 */  vecX_rule,
  /*  755 */  vecX_rule,
  /*  756 */  vecX_rule,
  /*  757 */  vecX_rule,
  /*  758 */  vecX_rule,
  /*  759 */  vecX_rule,
  /*  760 */  vecX_rule,
  /*  761 */  vecX_rule,
  /*  762 */  vecX_rule,
  /*  763 */  vecX_rule,
  /*  764 */  vecX_rule,
  /*  765 */  vecX_rule,
  /*  766 */  vecX_rule,
  /*  767 */  vecX_rule,
  /*  768 */  vecX_rule,
  /*  769 */  vecX_rule,
  /*  770 */  vecX_rule,
  /*  771 */  vecX_rule,
  /*  772 */  vecX_rule,
  /*  773 */  iRegI_rule,
  /*  774 */  iRegI_rule,
  /*  775 */  iRegI_rule,
  /*  776 */  iRegL_rule,
  /*  777 */  revenRegI_rule,
  /*  778 */  revenRegI_rule,
  /*  779 */  revenRegI_rule,
  /*  780 */  revenRegI_rule,
  /*  781 */  iRegI_rule,
  /*  782 */  iRegI_rule,
  /*  783 */  iRegI_rule,
  /*  784 */  iRegI_rule,
  /*  785 */  Universe_rule,
  /*  786 */  Universe_rule,
  /*  787 */  iRegI_rule,
  /*  788 */  iRegI_rule,
  /*  789 */  iRegN_rule,
  /*  790 */  iRegN_rule,
  /*  791 */  iRegN_rule,
  /*  792 */  iRegI_rule,
  /*  793 */  iRegI_rule,
  /*  794 */  iRegP_rule,
  /*  795 */  iRegP_rule,
  /*  796 */  iRegP_rule,
  /*  797 */  Universe_rule,
  // last instruction
  0 // no trailing comma
};

const        int   leftOp[] = {
  /*    0 */  0,
  /*    1 */  0,
  /*    2 */  0,
  /*    3 */  0,
  /*    4 */  0,
  /*    5 */  0,
  /*    6 */  0,
  /*    7 */  0,
  /*    8 */  0,
  /*    9 */  0,
  /*   10 */  0,
  /*   11 */  0,
  /*   12 */  0,
  /*   13 */  0,
  /*   14 */  0,
  /*   15 */  0,
  /*   16 */  0,
  /*   17 */  0,
  /*   18 */  0,
  /*   19 */  0,
  /*   20 */  0,
  /*   21 */  0,
  /*   22 */  0,
  /*   23 */  0,
  /*   24 */  0,
  /*   25 */  0,
  /*   26 */  0,
  /*   27 */  0,
  /*   28 */  0,
  /*   29 */  0,
  /*   30 */  0,
  /*   31 */  0,
  /*   32 */  0,
  /*   33 */  0,
  /*   34 */  0,
  /*   35 */  0,
  /*   36 */  0,
  /*   37 */  0,
  /*   38 */  0,
  /*   39 */  0,
  /*   40 */  0,
  /*   41 */  0,
  /*   42 */  0,
  /*   43 */  0,
  /*   44 */  0,
  /*   45 */  0,
  /*   46 */  0,
  /*   47 */  0,
  /*   48 */  0,
  /*   49 */  0,
  /*   50 */  0,
  /*   51 */  0,
  /*   52 */  0,
  /*   53 */  0,
  /*   54 */  0,
  /*   55 */  0,
  /*   56 */  0,
  /*   57 */  0,
  /*   58 */  0,
  /*   59 */  0,
  /*   60 */  0,
  /*   61 */  0,
  /*   62 */  0,
  /*   63 */  0,
  /*   64 */  0,
  /*   65 */  0,
  /*   66 */  0,
  /*   67 */  0,
  /*   68 */  0,
  /*   69 */  0,
  /*   70 */  0,
  /*   71 */  0,
  /*   72 */  0,
  /*   73 */  0,
  /*   74 */  0,
  /*   75 */  0,
  /*   76 */  0,
  /*   77 */  0,
  /*   78 */  0,
  /*   79 */  0,
  /*   80 */  0,
  /*   81 */  0,
  /*   82 */  0,
  /*   83 */  0,
  /*   84 */  0,
  /*   85 */  0,
  /*   86 */  0,
  /*   87 */  0,
  /*   88 */  0,
  /*   89 */  0,
  /*   90 */  0,
  /*   91 */  0,
  /*   92 */  0,
  /*   93 */  0,
  /*   94 */  0,
  /*   95 */  0,
  /*   96 */  0,
  /*   97 */  0,
  /*   98 */  0,
  /*   99 */  0,
  /*  100 */  0,
  /*  101 */  0,
  /*  102 */  0,
  /*  103 */  0,
  /*  104 */  0,
  /*  105 */  0,
  /*  106 */  0,
  /*  107 */  0,
  /*  108 */  0,
  /*  109 */  0,
  /*  110 */  0,
  /*  111 */  memoryRegP_rule,
  /*  112 */  _DecodeN_iRegN__rule,
  /*  113 */  memoryRegP_rule,
  /*  114 */  _DecodeN_iRegN__rule,
  /*  115 */  memoryRegP_rule,
  /*  116 */  _AddP_memoryRegP_iRegL_rule,
  /*  117 */  _AddP__DecodeN_iRegN__iRegL_rule,
  /*  118 */  _AddP_memoryRegP_iRegL_rule,
  /*  119 */  _AddP__DecodeN_iRegN__iRegL_rule,
  /*  120 */  0,
  /*  121 */  0,
  /*  122 */  0,
  /*  123 */  0,
  /*  124 */  0,
  /*  125 */  0,
  /*  126 */  0,
  /*  127 */  0,
  // last operand
  /*  128 */  0,
  /*  129 */  0,
  /*  130 */  0,
  /*  131 */  0,
  /*  132 */  0,
  /*  133 */  0,
  /*  134 */  0,
  // last operand class
  /*  135 */  iRegN_rule,
  /*  136 */  memoryRegP_rule,
  /*  137 */  _DecodeN_iRegN__rule,
  /*  138 */  memory_rule,
  /*  139 */  memory_rule,
  /*  140 */  memory_rule,
  /*  141 */  memory_rule,
  /*  142 */  memory_rule,
  /*  143 */  _LoadI_memory__rule,
  /*  144 */  memory_rule,
  /*  145 */  memory_rule,
  /*  146 */  memory_rule,
  /*  147 */  iRegL_rule,
  /*  148 */  cmpOp_rule,
  /*  149 */  iRegN_rule,
  /*  150 */  iRegN_rule,
  /*  151 */  iRegI_rule,
  /*  152 */  iRegI_rule,
  /*  153 */  iRegP_rule,
  /*  154 */  iRegP_rule,
  /*  155 */  cmpOpF_rule,
  /*  156 */  regF_rule,
  /*  157 */  regD_rule,
  /*  158 */  iRegL_rule,
  /*  159 */  iRegL_rule,
  /*  160 */  rarg5RegI_rule,
  /*  161 */  rarg5RegL_rule,
  /*  162 */  rarg5RegP_rule,
  /*  163 */  rarg5RegN_rule,
  /*  164 */  iRegI_rule,
  /*  165 */  memoryRSY_rule,
  /*  166 */  _LoadI_memoryRSY__rule,
  /*  167 */  iRegI_rule,
  /*  168 */  memory_rule,
  /*  169 */  iRegL_rule,
  /*  170 */  memoryRSY_rule,
  /*  171 */  _LoadL_memoryRSY__rule,
  /*  172 */  iRegP_N2P_rule,
  /*  173 */  memoryRSY_rule,
  /*  174 */  _LoadP_memoryRSY__rule,
  /*  175 */  iRegP_N2P_rule,
  /*  176 */  iRegI_rule,
  /*  177 */  iRegI_rule,
  /*  178 */  iRegL_rule,
  /*  179 */  iRegL_rule,
  /*  180 */  memoryRX_rule,
  /*  181 */  memoryRX_rule,
  /*  182 */  regF_rule,
  /*  183 */  regD_rule,
  /*  184 */  regF_rule,
  /*  185 */  regD_rule,
  /*  186 */  _LoadF_memoryRX__rule,
  /*  187 */  _LoadD_memoryRX__rule,
  /*  188 */  regF_rule,
  /*  189 */  regD_rule,
  /*  190 */  iRegI_rule,
  /*  191 */  iRegI_rule,
  /*  192 */  iRegL_rule,
  /*  193 */  iRegI_rule,
  /*  194 */  iRegI_rule,
  /*  195 */  iRegP_N2P_rule,
  /*  196 */  iRegN_P2N_rule,
  /*  197 */  iRegI_rule,
  /*  198 */  iRegI_rule,
  /*  199 */  iRegL_rule,
  /*  200 */  iRegP_rule,
  /*  201 */  _DecodeN_iRegN__rule,
  /*  202 */  iRegI_rule,
  /*  203 */  iRegI_rule,
  /*  204 */  iRegL_rule,
  /*  205 */  iRegP_rule,
  /*  206 */  _DecodeN_iRegN__rule,
  /*  207 */  immN8_rule,
  /*  208 */  _DecodeN_iRegN__rule,
  /*  209 */  rarg1RegP_rule,
  /*  210 */  iRegP_rule,
  /*  211 */  iRegP_rule,
  /*  212 */  iRegP_rule,
  /*  213 */  iRegP_rule,
  /*  214 */  immP_rule,
  /*  215 */  iRegP_rule,
  /*  216 */  iRegP_rule,
  /*  217 */  iRegP_rule,
  // last internally defined operand
  /*  218 */  iRegI_rule,
  /*  219 */  iRegL_rule,
  /*  220 */  iRegP_rule,
  /*  221 */  regF_rule,
  /*  222 */  regD_rule,
  /*  223 */  regD_rule,
  /*  224 */  regF_rule,
  /*  225 */  stackSlotI_rule,
  /*  226 */  stackSlotL_rule,
  /*  227 */  stackSlotP_rule,
  /*  228 */  stackSlotF_rule,
  /*  229 */  stackSlotD_rule,
  /*  230 */  immI_rule,
  /*  231 */  immI16_rule,
  /*  232 */  immI_0_rule,
  /*  233 */  uimmI16_rule,
  /*  234 */  immL_rule,
  /*  235 */  immL32_rule,
  /*  236 */  immL16_rule,
  /*  237 */  immL_0_rule,
  /*  238 */  immP_rule,
  /*  239 */  immP0_rule,
  /*  240 */  immF_rule,
  /*  241 */  immD_rule,
  /*  242 */  immFp0_rule,
  /*  243 */  immDp0_rule,
  /*  244 */  immN_rule,
  /*  245 */  immN0_rule,
  /*  246 */  immNKlass_rule,
  /*  247 */  _LoadP_memory__rule,
  /*  248 */  0,
  /*  249 */  iRegN_P2N_rule,
  /*  250 */  iRegN_P2N_rule,
  /*  251 */  iRegN_rule,
  /*  252 */  iRegN_P2N_rule,
  /*  253 */  iRegL_rule,
  /*  254 */  iRegP_N2P_rule,
  /*  255 */  0,
  /*  256 */  iRegP_rule,
  /*  257 */  iRegP_rule,
  /*  258 */  iRegI_rule,
  /*  259 */  iRegL_rule,
  /*  260 */  regF_rule,
  /*  261 */  regD_rule,
  /*  262 */  iRegL_rule,
  /*  263 */  iRegI_rule,
  /*  264 */  iRegI_rule,
  /*  265 */  iRegL_rule,
  /*  266 */  iRegL_rule,
  /*  267 */  iRegI_rule,
  /*  268 */  iRegI_rule,
  /*  269 */  iRegL_rule,
  /*  270 */  iRegL_rule,
  /*  271 */  immI_0_rule,
  /*  272 */  immL_0_rule,
  /*  273 */  stackSlotF_rule,
  /*  274 */  stackSlotI_rule,
  /*  275 */  stackSlotD_rule,
  /*  276 */  stackSlotL_rule,
  /*  277 */  iRegI_rule,
  /*  278 */  iRegI_rule,
  /*  279 */  iRegI_rule,
  /*  280 */  iRegI_rule,
  /*  281 */  iRegI_rule,
  /*  282 */  iRegI_rule,
  /*  283 */  iRegI_rule,
  /*  284 */  iRegI_rule,
  /*  285 */  iRegL_rule,
  /*  286 */  iRegL_rule,
  /*  287 */  iRegL_rule,
  /*  288 */  iRegL_rule,
  /*  289 */  iRegL_rule,
  /*  290 */  _ConvI2L_iRegI__rule,
  /*  291 */  iRegL_rule,
  /*  292 */  iRegL_rule,
  /*  293 */  iRegL_rule,
  /*  294 */  iRegL_rule,
  /*  295 */  iRegP_N2P_rule,
  /*  296 */  iRegP_N2P_rule,
  /*  297 */  _DecodeN_iRegN__rule,
  /*  298 */  iRegP_rule,
  /*  299 */  regF_rule,
  /*  300 */  regD_rule,
  /*  301 */  regF_rule,
  /*  302 */  regD_rule,
  /*  303 */  regF_rule,
  /*  304 */  regD_rule,
  /*  305 */  iRegP_N2P_rule,
  /*  306 */  iRegP_N2P_rule,
  /*  307 */  0,
  /*  308 */  immB_n0m1_rule,
  /*  309 */  immI_0_rule,
  /*  310 */  immB_minus1_rule,
  /*  311 */  immS_n0m1_rule,
  /*  312 */  immI_0_rule,
  /*  313 */  immS_minus1_rule,
  /*  314 */  iRegI_rule,
  /*  315 */  immI_minus1_rule,
  /*  316 */  immI_0_rule,
  /*  317 */  immI_n0m1_rule,
  /*  318 */  immI_0_rule,
  /*  319 */  immI_minus1_rule,
  /*  320 */  iRegI_rule,
  /*  321 */  immI_0_rule,
  /*  322 */  immI_minus1_rule,
  /*  323 */  immF_rule,
  /*  324 */  immFp0_rule,
  /*  325 */  regF_rule,
  /*  326 */  immFp0_rule,
  /*  327 */  regD_rule,
  /*  328 */  immDp0_rule,
  /*  329 */  iRegI_rule,
  /*  330 */  immI_minus1_rule,
  /*  331 */  immI_0_rule,
  /*  332 */  iRegL_rule,
  /*  333 */  immI_minus1_rule,
  /*  334 */  immI_0_rule,
  /*  335 */  iRegL_rule,
  /*  336 */  vecX_rule,
  /*  337 */  vecX_rule,
  /*  338 */  vecX_rule,
  /*  339 */  vecX_rule,
  /*  340 */  memory_rule,
  /*  341 */  _LoadB_memory__rule,
  /*  342 */  memory_rule,
  /*  343 */  _LoadUB_memory__rule,
  /*  344 */  memory_rule,
  /*  345 */  _LoadS_memory__rule,
  /*  346 */  memory_rule,
  /*  347 */  _LoadUS_memory__rule,
  /*  348 */  memory_rule,
  /*  349 */  _LoadI_memory__rule,
  /*  350 */  _ConvI2L__LoadI_memory___rule,
  /*  351 */  memory_rule,
  /*  352 */  memory_rule,
  /*  353 */  memory_rule,
  /*  354 */  memory_rule,
  /*  355 */  memory_rule,
  /*  356 */  0,
  /*  357 */  memory_rule,
  /*  358 */  memory_rule,
  /*  359 */  memory_rule,
  /*  360 */  memory_rule,
  /*  361 */  memory_rule,
  /*  362 */  memory_rule,
  /*  363 */  memory_rule,
  /*  364 */  memory_rule,
  /*  365 */  memory_rule,
  /*  366 */  memory_rule,
  /*  367 */  memory_rule,
  /*  368 */  memoryRSY_rule,
  /*  369 */  memoryRS_rule,
  /*  370 */  memoryRS_rule,
  /*  371 */  memoryRS_rule,
  /*  372 */  memoryRS_rule,
  /*  373 */  immL_0_rule,
  /*  374 */  memory_rule,
  /*  375 */  memory_rule,
  /*  376 */  memory_rule,
  /*  377 */  _LoadN_memory__rule,
  /*  378 */  _LoadNKlass_memory__rule,
  /*  379 */  immNKlass_rule,
  /*  380 */  iRegN_rule,
  /*  381 */  iRegN_rule,
  /*  382 */  iRegN_rule,
  /*  383 */  iRegN_rule,
  /*  384 */  iRegN_rule,
  /*  385 */  iRegN_rule,
  /*  386 */  iRegN_rule,
  /*  387 */  iRegP_rule,
  /*  388 */  iRegP_rule,
  /*  389 */  iRegP_rule,
  /*  390 */  iRegP_rule,
  /*  391 */  iRegP_rule,
  /*  392 */  iRegP_rule,
  /*  393 */  iRegP_rule,
  /*  394 */  memory_rule,
  /*  395 */  memory_rule,
  /*  396 */  0,
  /*  397 */  0,
  /*  398 */  0,
  /*  399 */  0,
  /*  400 */  0,
  /*  401 */  0,
  /*  402 */  0,
  /*  403 */  0,
  /*  404 */  0,
  /*  405 */  0,
  /*  406 */  0,
  /*  407 */  0,
  /*  408 */  0,
  /*  409 */  _Binary_cmpOp_flagsReg_rule,
  /*  410 */  _Binary_cmpOp_flagsReg_rule,
  /*  411 */  _Binary_cmpOp_flagsReg_rule,
  /*  412 */  _Binary_cmpOp_flagsReg_rule,
  /*  413 */  _Binary_cmpOp_flagsReg_rule,
  /*  414 */  _Binary_cmpOp_flagsReg_rule,
  /*  415 */  _Binary_cmpOpF_flagsReg_rule,
  /*  416 */  _Binary_cmpOpF_flagsReg_rule,
  /*  417 */  _Binary_cmpOp_flagsReg_rule,
  /*  418 */  _Binary_cmpOp_flagsReg_rule,
  /*  419 */  iRegP_rule,
  /*  420 */  iRegP_rule,
  /*  421 */  iRegP_rule,
  /*  422 */  iRegP_rule,
  /*  423 */  memoryRSY_rule,
  /*  424 */  memoryRSY_rule,
  /*  425 */  memoryRSY_rule,
  /*  426 */  memoryRSY_rule,
  /*  427 */  memoryRSY_rule,
  /*  428 */  memoryRSY_rule,
  /*  429 */  memoryRSY_rule,
  /*  430 */  memoryRSY_rule,
  /*  431 */  memoryRSY_rule,
  /*  432 */  memoryRSY_rule,
  /*  433 */  memoryRSY_rule,
  /*  434 */  memoryRSY_rule,
  /*  435 */  memoryRSY_rule,
  /*  436 */  memoryRSY_rule,
  /*  437 */  iRegI_rule,
  /*  438 */  iRegI_rule,
  /*  439 */  iRegI_rule,
  /*  440 */  iRegI_rule,
  /*  441 */  iRegI_rule,
  /*  442 */  iRegI_rule,
  /*  443 */  iRegI_rule,
  /*  444 */  _AddI_iRegI_iRegI_rule,
  /*  445 */  _AddI_iRegI_iRegI_rule,
  /*  446 */  iRegI_rule,
  /*  447 */  _LoadI_memory__rule,
  /*  448 */  memoryRSY_rule,
  /*  449 */  iRegL_rule,
  /*  450 */  _ConvI2L_iRegI__rule,
  /*  451 */  iRegL_rule,
  /*  452 */  iRegL_rule,
  /*  453 */  iRegL_rule,
  /*  454 */  iRegL_rule,
  /*  455 */  iRegL_rule,
  /*  456 */  iRegL_rule,
  /*  457 */  iRegL_rule,
  /*  458 */  iRegL_rule,
  /*  459 */  _ConvI2L__LoadI_memory___rule,
  /*  460 */  iRegL_rule,
  /*  461 */  _LoadL_memory__rule,
  /*  462 */  _AddL_iRegL_iRegL_rule,
  /*  463 */  _AddL_iRegL_iRegL_rule,
  /*  464 */  memoryRSY_rule,
  /*  465 */  iRegP_N2P_rule,
  /*  466 */  iRegP_rule,
  /*  467 */  iRegP_N2P_rule,
  /*  468 */  iRegP_N2P_rule,
  /*  469 */  iRegP_rule,
  /*  470 */  iRegP_N2P_rule,
  /*  471 */  memoryRegP_rule,
  /*  472 */  iRegP_rule,
  /*  473 */  _AddP_memoryRegP_iRegL_rule,
  /*  474 */  _AddP_iRegP_N2P_iRegL_rule,
  /*  475 */  _AddP_memoryRegP_iRegL_rule,
  /*  476 */  _AddP_iRegP_N2P_iRegL_rule,
  /*  477 */  memoryRSY_rule,
  /*  478 */  iRegI_rule,
  /*  479 */  iRegI_rule,
  /*  480 */  iRegI_rule,
  /*  481 */  immI_0_rule,
  /*  482 */  iRegL_rule,
  /*  483 */  iRegL_rule,
  /*  484 */  iRegL_rule,
  /*  485 */  iRegL_rule,
  /*  486 */  iRegL_rule,
  /*  487 */  iRegI_rule,
  /*  488 */  iRegI_rule,
  /*  489 */  iRegI_rule,
  /*  490 */  iRegI_rule,
  /*  491 */  _LoadI_memory__rule,
  /*  492 */  iRegL_rule,
  /*  493 */  _ConvI2L_iRegI__rule,
  /*  494 */  iRegL_rule,
  /*  495 */  iRegL_rule,
  /*  496 */  iRegL_rule,
  /*  497 */  iRegL_rule,
  /*  498 */  _ConvI2L__LoadI_memory___rule,
  /*  499 */  iRegL_rule,
  /*  500 */  _LoadL_memory__rule,
  /*  501 */  roddRegL_rule,
  /*  502 */  roddRegI_rule,
  /*  503 */  iRegI_rule,
  /*  504 */  iRegI_rule,
  /*  505 */  roddRegI_rule,
  /*  506 */  roddRegL_rule,
  /*  507 */  roddRegL_rule,
  /*  508 */  roddRegL_rule,
  /*  509 */  iRegL_rule,
  /*  510 */  iRegI_rule,
  /*  511 */  revenRegI_rule,
  /*  512 */  iRegI_rule,
  /*  513 */  roddRegL_rule,
  /*  514 */  revenRegL_rule,
  /*  515 */  iRegL_rule,
  /*  516 */  iRegI_rule,
  /*  517 */  iRegI_rule,
  /*  518 */  iRegI_rule,
  /*  519 */  iRegL_rule,
  /*  520 */  iRegL_rule,
  /*  521 */  iRegL_rule,
  /*  522 */  iRegI_rule,
  /*  523 */  iRegI_rule,
  /*  524 */  iRegL_rule,
  /*  525 */  iRegL_rule,
  /*  526 */  iRegI_rule,
  /*  527 */  iRegI_rule,
  /*  528 */  iRegL_rule,
  /*  529 */  iRegL_rule,
  /*  530 */  _CastP2X_iRegP_N2P__rule,
  /*  531 */  _LShiftI_iRegI_immI8_rule,
  /*  532 */  _URShiftI_iRegI_immI8_rule,
  /*  533 */  _LShiftL_iRegL_immI8_rule,
  /*  534 */  _URShiftL_iRegL_immI8_rule,
  /*  535 */  _URShiftI_iRegI_immI8_rule,
  /*  536 */  _LShiftI_iRegI_immI8_rule,
  /*  537 */  _URShiftL_iRegL_immI8_rule,
  /*  538 */  _LShiftL_iRegL_immI8_rule,
  /*  539 */  regF_rule,
  /*  540 */  regF_rule,
  /*  541 */  _LoadF_memoryRX__rule,
  /*  542 */  regD_rule,
  /*  543 */  regD_rule,
  /*  544 */  _LoadD_memoryRX__rule,
  /*  545 */  regF_rule,
  /*  546 */  regF_rule,
  /*  547 */  regD_rule,
  /*  548 */  regD_rule,
  /*  549 */  regF_rule,
  /*  550 */  regF_rule,
  /*  551 */  _LoadF_memoryRX__rule,
  /*  552 */  regD_rule,
  /*  553 */  regD_rule,
  /*  554 */  _LoadD_memoryRX__rule,
  /*  555 */  regF_rule,
  /*  556 */  regD_rule,
  /*  557 */  _NegF_regF__rule,
  /*  558 */  _NegD_regD__rule,
  /*  559 */  regF_rule,
  /*  560 */  regD_rule,
  /*  561 */  _NegF_regF__rule,
  /*  562 */  _NegD_regD__rule,
  /*  563 */  regF_rule,
  /*  564 */  regD_rule,
  /*  565 */  _NegF_regF__rule,
  /*  566 */  _NegD_regD__rule,
  /*  567 */  regF_rule,
  /*  568 */  regF_rule,
  /*  569 */  regD_rule,
  /*  570 */  regD_rule,
  /*  571 */  regF_rule,
  /*  572 */  regD_rule,
  /*  573 */  _AbsF_regF__rule,
  /*  574 */  _AbsD_regD__rule,
  /*  575 */  regF_rule,
  /*  576 */  regD_rule,
  /*  577 */  regF_rule,
  /*  578 */  regD_rule,
  /*  579 */  memoryRX_rule,
  /*  580 */  memoryRX_rule,
  /*  581 */  iRegI_rule,
  /*  582 */  iRegI_rule,
  /*  583 */  _LoadI_memory__rule,
  /*  584 */  iRegI_rule,
  /*  585 */  iRegI_rule,
  /*  586 */  iRegI_rule,
  /*  587 */  iRegL_rule,
  /*  588 */  iRegL_rule,
  /*  589 */  _LoadL_memory__rule,
  /*  590 */  iRegL_rule,
  /*  591 */  iRegL_rule,
  /*  592 */  iRegL_rule,
  /*  593 */  iRegL_rule,
  /*  594 */  iRegI_rule,
  /*  595 */  iRegI_rule,
  /*  596 */  _LoadI_memory__rule,
  /*  597 */  iRegI_rule,
  /*  598 */  iRegI_rule,
  /*  599 */  iRegL_rule,
  /*  600 */  iRegL_rule,
  /*  601 */  _LoadL_memory__rule,
  /*  602 */  iRegL_rule,
  /*  603 */  iRegI_rule,
  /*  604 */  iRegI_rule,
  /*  605 */  iRegI_rule,
  /*  606 */  _LoadI_memory__rule,
  /*  607 */  iRegI_rule,
  /*  608 */  iRegL_rule,
  /*  609 */  iRegL_rule,
  /*  610 */  iRegL_rule,
  /*  611 */  iRegI_rule,
  /*  612 */  iRegP_N2P_rule,
  /*  613 */  iRegI_rule,
  /*  614 */  iRegI_rule,
  /*  615 */  regD_rule,
  /*  616 */  regF_rule,
  /*  617 */  regD_rule,
  /*  618 */  regF_rule,
  /*  619 */  regD_rule,
  /*  620 */  regF_rule,
  /*  621 */  memoryRX_rule,
  /*  622 */  iRegI_rule,
  /*  623 */  iRegI_rule,
  /*  624 */  iRegI_rule,
  /*  625 */  _ConvI2L_iRegI__rule,
  /*  626 */  _ConvI2L__LoadI_memory___rule,
  /*  627 */  iRegL_rule,
  /*  628 */  _LShiftI_iRegI_immI_16_rule,
  /*  629 */  _LShiftI_iRegI_immI_24_rule,
  /*  630 */  iRegI_rule,
  /*  631 */  regD_rule,
  /*  632 */  iRegL_rule,
  /*  633 */  iRegL_rule,
  /*  634 */  iRegL_rule,
  /*  635 */  iRegL_rule,
  /*  636 */  _RShiftL_iRegL_immI_32_63_rule,
  /*  637 */  cmpOpT_rule,
  /*  638 */  cmpOpT_rule,
  /*  639 */  cmpOpT_rule,
  /*  640 */  cmpOpT_rule,
  /*  641 */  cmpOpT_rule,
  /*  642 */  iRegI_rule,
  /*  643 */  iRegI_rule,
  /*  644 */  iRegI_rule,
  /*  645 */  iRegI_rule,
  /*  646 */  iRegI_rule,
  /*  647 */  iRegI_rule,
  /*  648 */  iRegI_rule,
  /*  649 */  iRegI_rule,
  /*  650 */  iRegI_rule,
  /*  651 */  iRegI_rule,
  /*  652 */  iRegI_rule,
  /*  653 */  iRegI_rule,
  /*  654 */  iRegI_rule,
  /*  655 */  iRegI_rule,
  /*  656 */  iRegI_rule,
  /*  657 */  iRegI_rule,
  /*  658 */  iRegI_rule,
  /*  659 */  iRegL_rule,
  /*  660 */  immI_0_rule,
  /*  661 */  regF_rule,
  /*  662 */  regD_rule,
  /*  663 */  0,
  /*  664 */  0,
  /*  665 */  cmpOp_rule,
  /*  666 */  cmpOp_rule,
  /*  667 */  cmpOp_rule,
  /*  668 */  cmpOp_rule,
  /*  669 */  cmpOpT_rule,
  /*  670 */  cmpOpT_rule,
  /*  671 */  cmpOpT_rule,
  /*  672 */  cmpOpT_rule,
  /*  673 */  cmpOpT_rule,
  /*  674 */  cmpOpT_rule,
  /*  675 */  cmpOpT_rule,
  /*  676 */  cmpOpT_rule,
  /*  677 */  cmpOpT_rule,
  /*  678 */  cmpOpT_rule,
  /*  679 */  cmpOpT_rule,
  /*  680 */  cmpOpT_rule,
  /*  681 */  cmpOpT_rule,
  /*  682 */  cmpOpT_rule,
  /*  683 */  cmpOpT_rule,
  /*  684 */  cmpOpT_rule,
  /*  685 */  cmpOpT_rule,
  /*  686 */  cmpOpT_rule,
  /*  687 */  cmpOpT_rule,
  /*  688 */  cmpOpT_rule,
  /*  689 */  cmpOpT_rule,
  /*  690 */  cmpOpT_rule,
  /*  691 */  cmpOpT_rule,
  /*  692 */  cmpOpT_rule,
  /*  693 */  cmpOpT_rule,
  /*  694 */  cmpOpT_rule,
  /*  695 */  iRegL_rule,
  /*  696 */  0,
  /*  697 */  iRegP_rule,
  /*  698 */  0,
  /*  699 */  0,
  /*  700 */  0,
  /*  701 */  0,
  /*  702 */  0,
  /*  703 */  iRegP_rule,
  /*  704 */  0,
  /*  705 */  iRegP_rule,
  /*  706 */  0,
  /*  707 */  0,
  /*  708 */  0,
  /*  709 */  0,
  /*  710 */  rarg2RegP_rule,
  /*  711 */  rarg2RegP_rule,
  /*  712 */  rarg2RegP_rule,
  /*  713 */  SSlenDW_rule,
  /*  714 */  immL_rule,
  /*  715 */  iRegL_rule,
  /*  716 */  _Binary_iRegP_iRegP_rule,
  /*  717 */  _Binary_iRegP_iRegP_rule,
  /*  718 */  _Binary_iRegP_iRegP_rule,
  /*  719 */  iRegP_rule,
  /*  720 */  iRegP_rule,
  /*  721 */  _Binary_iRegP_rarg2RegI_rule,
  /*  722 */  _Binary_iRegP_rarg2RegI_rule,
  /*  723 */  _Binary_iRegP_rarg2RegI_rule,
  /*  724 */  _Binary_iRegP_rarg2RegI_rule,
  /*  725 */  _Binary_iRegP_iRegI_rule,
  /*  726 */  _Binary_iRegP_iRegI_rule,
  /*  727 */  _Binary_iRegP_iRegI_rule,
  /*  728 */  _Binary_iRegP_iRegI_rule,
  /*  729 */  _Binary_iRegP_iRegI_rule,
  /*  730 */  _Binary_iRegP_rarg2RegI_rule,
  /*  731 */  _Binary_iRegP_rarg2RegI_rule,
  /*  732 */  _Binary_iRegP_rarg2RegI_rule,
  /*  733 */  _Binary_iRegP_rarg2RegI_rule,
  /*  734 */  _Binary_iRegP_rarg2RegI_rule,
  /*  735 */  _Binary_iRegP_rarg2RegI_rule,
  /*  736 */  iRegP_rule,
  /*  737 */  iRegP_rule,
  /*  738 */  iRegP_rule,
  /*  739 */  iRegP_rule,
  /*  740 */  iRegP_rule,
  /*  741 */  iRegP_rule,
  /*  742 */  0,
  /*  743 */  iRegL_rule,
  /*  744 */  iRegI_rule,
  /*  745 */  iRegI_rule,
  /*  746 */  iRegI_rule,
  /*  747 */  regF_rule,
  /*  748 */  regF_rule,
  /*  749 */  memory_rule,
  /*  750 */  memoryRX_rule,
  /*  751 */  memory_rule,
  /*  752 */  memoryRX_rule,
  /*  753 */  vecX_rule,
  /*  754 */  vecX_rule,
  /*  755 */  vecX_rule,
  /*  756 */  vecX_rule,
  /*  757 */  vecX_rule,
  /*  758 */  vecX_rule,
  /*  759 */  vecX_rule,
  /*  760 */  vecX_rule,
  /*  761 */  vecX_rule,
  /*  762 */  vecX_rule,
  /*  763 */  vecX_rule,
  /*  764 */  vecX_rule,
  /*  765 */  vecX_rule,
  /*  766 */  vecX_rule,
  /*  767 */  vecX_rule,
  /*  768 */  vecX_rule,
  /*  769 */  vecX_rule,
  /*  770 */  vecX_rule,
  /*  771 */  vecX_rule,
  /*  772 */  vecX_rule,
  /*  773 */  iRegI_rule,
  /*  774 */  iRegI_rule,
  /*  775 */  iRegI_rule,
  /*  776 */  iRegL_rule,
  /*  777 */  iRegI_rule,
  /*  778 */  iRegL_rule,
  /*  779 */  iRegI_rule,
  /*  780 */  iRegL_rule,
  /*  781 */  iRegI_rule,
  /*  782 */  iRegL_rule,
  /*  783 */  iRegI_rule,
  /*  784 */  iRegL_rule,
  /*  785 */  indirect_rule,
  /*  786 */  indirect_rule,
  /*  787 */  indirect_rule,
  /*  788 */  indirect_rule,
  /*  789 */  iRegP_rule,
  /*  790 */  indirect_rule,
  /*  791 */  indirect_rule,
  /*  792 */  iRegP_rule,
  /*  793 */  iRegP_rule,
  /*  794 */  iRegP_rule,
  /*  795 */  memory_rule,
  /*  796 */  indirect_rule,
  /*  797 */  indirect_rule,
  // last instruction
  0 // no trailing comma
};

const        int   rightOp[] = {
  /*    0 */  0,
  /*    1 */  0,
  /*    2 */  0,
  /*    3 */  0,
  /*    4 */  0,
  /*    5 */  0,
  /*    6 */  0,
  /*    7 */  0,
  /*    8 */  0,
  /*    9 */  0,
  /*   10 */  0,
  /*   11 */  0,
  /*   12 */  0,
  /*   13 */  0,
  /*   14 */  0,
  /*   15 */  0,
  /*   16 */  0,
  /*   17 */  0,
  /*   18 */  0,
  /*   19 */  0,
  /*   20 */  0,
  /*   21 */  0,
  /*   22 */  0,
  /*   23 */  0,
  /*   24 */  0,
  /*   25 */  0,
  /*   26 */  0,
  /*   27 */  0,
  /*   28 */  0,
  /*   29 */  0,
  /*   30 */  0,
  /*   31 */  0,
  /*   32 */  0,
  /*   33 */  0,
  /*   34 */  0,
  /*   35 */  0,
  /*   36 */  0,
  /*   37 */  0,
  /*   38 */  0,
  /*   39 */  0,
  /*   40 */  0,
  /*   41 */  0,
  /*   42 */  0,
  /*   43 */  0,
  /*   44 */  0,
  /*   45 */  0,
  /*   46 */  0,
  /*   47 */  0,
  /*   48 */  0,
  /*   49 */  0,
  /*   50 */  0,
  /*   51 */  0,
  /*   52 */  0,
  /*   53 */  0,
  /*   54 */  0,
  /*   55 */  0,
  /*   56 */  0,
  /*   57 */  0,
  /*   58 */  0,
  /*   59 */  0,
  /*   60 */  0,
  /*   61 */  0,
  /*   62 */  0,
  /*   63 */  0,
  /*   64 */  0,
  /*   65 */  0,
  /*   66 */  0,
  /*   67 */  0,
  /*   68 */  0,
  /*   69 */  0,
  /*   70 */  0,
  /*   71 */  0,
  /*   72 */  0,
  /*   73 */  0,
  /*   74 */  0,
  /*   75 */  0,
  /*   76 */  0,
  /*   77 */  0,
  /*   78 */  0,
  /*   79 */  0,
  /*   80 */  0,
  /*   81 */  0,
  /*   82 */  0,
  /*   83 */  0,
  /*   84 */  0,
  /*   85 */  0,
  /*   86 */  0,
  /*   87 */  0,
  /*   88 */  0,
  /*   89 */  0,
  /*   90 */  0,
  /*   91 */  0,
  /*   92 */  0,
  /*   93 */  0,
  /*   94 */  0,
  /*   95 */  0,
  /*   96 */  0,
  /*   97 */  0,
  /*   98 */  0,
  /*   99 */  0,
  /*  100 */  0,
  /*  101 */  0,
  /*  102 */  0,
  /*  103 */  0,
  /*  104 */  0,
  /*  105 */  0,
  /*  106 */  0,
  /*  107 */  0,
  /*  108 */  0,
  /*  109 */  0,
  /*  110 */  0,
  /*  111 */  immL20_rule,
  /*  112 */  immL20_rule,
  /*  113 */  uimmL12_rule,
  /*  114 */  uimmL12_rule,
  /*  115 */  iRegL_rule,
  /*  116 */  immL20_rule,
  /*  117 */  immL20_rule,
  /*  118 */  uimmL12_rule,
  /*  119 */  uimmL12_rule,
  /*  120 */  0,
  /*  121 */  0,
  /*  122 */  0,
  /*  123 */  0,
  /*  124 */  0,
  /*  125 */  0,
  /*  126 */  0,
  /*  127 */  0,
  // last operand
  /*  128 */  0,
  /*  129 */  0,
  /*  130 */  0,
  /*  131 */  0,
  /*  132 */  0,
  /*  133 */  0,
  /*  134 */  0,
  // last operand class
  /*  135 */  0,
  /*  136 */  iRegL_rule,
  /*  137 */  iRegL_rule,
  /*  138 */  0,
  /*  139 */  0,
  /*  140 */  0,
  /*  141 */  0,
  /*  142 */  0,
  /*  143 */  0,
  /*  144 */  0,
  /*  145 */  0,
  /*  146 */  0,
  /*  147 */  iRegN_rule,
  /*  148 */  flagsReg_rule,
  /*  149 */  iRegN_P2N_rule,
  /*  150 */  immN0_rule,
  /*  151 */  iRegI_rule,
  /*  152 */  immI16_rule,
  /*  153 */  iRegP_N2P_rule,
  /*  154 */  immP0_rule,
  /*  155 */  flagsReg_rule,
  /*  156 */  regF_rule,
  /*  157 */  regD_rule,
  /*  158 */  iRegL_rule,
  /*  159 */  immL16_rule,
  /*  160 */  iRegI_rule,
  /*  161 */  iRegL_rule,
  /*  162 */  iRegP_N2P_rule,
  /*  163 */  iRegN_P2N_rule,
  /*  164 */  iRegI_rule,
  /*  165 */  0,
  /*  166 */  immI8_rule,
  /*  167 */  0,
  /*  168 */  0,
  /*  169 */  iRegL_rule,
  /*  170 */  0,
  /*  171 */  immL8_rule,
  /*  172 */  iRegL_rule,
  /*  173 */  0,
  /*  174 */  immL8_rule,
  /*  175 */  0,
  /*  176 */  immI8_rule,
  /*  177 */  immI8_rule,
  /*  178 */  immI8_rule,
  /*  179 */  immI8_rule,
  /*  180 */  0,
  /*  181 */  0,
  /*  182 */  0,
  /*  183 */  0,
  /*  184 */  _LoadF_memoryRX__rule,
  /*  185 */  _LoadD_memoryRX__rule,
  /*  186 */  regF_rule,
  /*  187 */  regD_rule,
  /*  188 */  0,
  /*  189 */  0,
  /*  190 */  immI_16_rule,
  /*  191 */  immI_24_rule,
  /*  192 */  immI_32_63_rule,
  /*  193 */  uimmI16_rule,
  /*  194 */  iRegI_rule,
  /*  195 */  immP0_rule,
  /*  196 */  immN0_rule,
  /*  197 */  0,
  /*  198 */  iRegI_rule,
  /*  199 */  iRegL_rule,
  /*  200 */  iRegP_rule,
  /*  201 */  _DecodeN_iRegN__rule,
  /*  202 */  immI8_rule,
  /*  203 */  uimmI8_rule,
  /*  204 */  immL8_rule,
  /*  205 */  immP8_rule,
  /*  206 */  immP0_rule,
  /*  207 */  0,
  /*  208 */  _DecodeN_immN8__rule,
  /*  209 */  immP_rule,
  /*  210 */  iRegP_rule,
  /*  211 */  rarg2RegI_rule,
  /*  212 */  rarg5RegI_rule,
  /*  213 */  iRegI_rule,
  /*  214 */  immI_1_rule,
  /*  215 */  immI16_rule,
  /*  216 */  immI_rule,
  /*  217 */  0,
  // last internally defined operand
  /*  218 */  0,
  /*  219 */  0,
  /*  220 */  0,
  /*  221 */  0,
  /*  222 */  0,
  /*  223 */  0,
  /*  224 */  0,
  /*  225 */  0,
  /*  226 */  0,
  /*  227 */  0,
  /*  228 */  0,
  /*  229 */  0,
  /*  230 */  0,
  /*  231 */  0,
  /*  232 */  0,
  /*  233 */  0,
  /*  234 */  0,
  /*  235 */  0,
  /*  236 */  0,
  /*  237 */  0,
  /*  238 */  0,
  /*  239 */  0,
  /*  240 */  0,
  /*  241 */  0,
  /*  242 */  0,
  /*  243 */  0,
  /*  244 */  0,
  /*  245 */  0,
  /*  246 */  0,
  /*  247 */  0,
  /*  248 */  0,
  /*  249 */  iRegN_P2N_rule,
  /*  250 */  immN_rule,
  /*  251 */  immNKlass_rule,
  /*  252 */  immN0_rule,
  /*  253 */  0,
  /*  254 */  0,
  /*  255 */  0,
  /*  256 */  0,
  /*  257 */  0,
  /*  258 */  0,
  /*  259 */  0,
  /*  260 */  0,
  /*  261 */  0,
  /*  262 */  0,
  /*  263 */  iRegI_rule,
  /*  264 */  immI_rule,
  /*  265 */  iRegL_rule,
  /*  266 */  immL_rule,
  /*  267 */  iRegI_rule,
  /*  268 */  immI_rule,
  /*  269 */  iRegL_rule,
  /*  270 */  immL_rule,
  /*  271 */  iRegI_rule,
  /*  272 */  iRegL_rule,
  /*  273 */  0,
  /*  274 */  0,
  /*  275 */  0,
  /*  276 */  0,
  /*  277 */  iRegI_rule,
  /*  278 */  immI_rule,
  /*  279 */  immI16_rule,
  /*  280 */  immI_0_rule,
  /*  281 */  _LoadI_memory__rule,
  /*  282 */  iRegI_rule,
  /*  283 */  uimmI_rule,
  /*  284 */  _LoadI_memory__rule,
  /*  285 */  iRegL_rule,
  /*  286 */  _ConvI2L_iRegI__rule,
  /*  287 */  immL32_rule,
  /*  288 */  immL16_rule,
  /*  289 */  immL_0_rule,
  /*  290 */  immL_0_rule,
  /*  291 */  _LoadL_memory__rule,
  /*  292 */  _ConvI2L__LoadI_memory___rule,
  /*  293 */  iRegL_rule,
  /*  294 */  uimmL32_rule,
  /*  295 */  iRegP_N2P_rule,
  /*  296 */  immP0_rule,
  /*  297 */  immP0_rule,
  /*  298 */  _LoadP_memory__rule,
  /*  299 */  regF_rule,
  /*  300 */  regD_rule,
  /*  301 */  _LoadF_memoryRX__rule,
  /*  302 */  _LoadD_memoryRX__rule,
  /*  303 */  immFpm0_rule,
  /*  304 */  immDpm0_rule,
  /*  305 */  iRegP_N2P_rule,
  /*  306 */  iRegP_N2P_rule,
  /*  307 */  0,
  /*  308 */  0,
  /*  309 */  0,
  /*  310 */  0,
  /*  311 */  0,
  /*  312 */  0,
  /*  313 */  0,
  /*  314 */  0,
  /*  315 */  0,
  /*  316 */  0,
  /*  317 */  0,
  /*  318 */  0,
  /*  319 */  0,
  /*  320 */  0,
  /*  321 */  0,
  /*  322 */  0,
  /*  323 */  0,
  /*  324 */  0,
  /*  325 */  0,
  /*  326 */  0,
  /*  327 */  0,
  /*  328 */  0,
  /*  329 */  0,
  /*  330 */  0,
  /*  331 */  0,
  /*  332 */  0,
  /*  333 */  0,
  /*  334 */  0,
  /*  335 */  0,
  /*  336 */  0,
  /*  337 */  0,
  /*  338 */  0,
  /*  339 */  0,
  /*  340 */  0,
  /*  341 */  0,
  /*  342 */  0,
  /*  343 */  0,
  /*  344 */  0,
  /*  345 */  0,
  /*  346 */  0,
  /*  347 */  0,
  /*  348 */  0,
  /*  349 */  0,
  /*  350 */  immL_FFFFFFFF_rule,
  /*  351 */  0,
  /*  352 */  0,
  /*  353 */  0,
  /*  354 */  0,
  /*  355 */  0,
  /*  356 */  0,
  /*  357 */  0,
  /*  358 */  0,
  /*  359 */  0,
  /*  360 */  iRegI_rule,
  /*  361 */  iRegI_rule,
  /*  362 */  iRegI_rule,
  /*  363 */  iRegL_rule,
  /*  364 */  memoryRegP_rule,
  /*  365 */  regF_rule,
  /*  366 */  regD_rule,
  /*  367 */  0,
  /*  368 */  immI8_rule,
  /*  369 */  immI16_rule,
  /*  370 */  immI16_rule,
  /*  371 */  immL16_rule,
  /*  372 */  immP16_rule,
  /*  373 */  iRegL_rule,
  /*  374 */  0,
  /*  375 */  0,
  /*  376 */  0,
  /*  377 */  0,
  /*  378 */  0,
  /*  379 */  0,
  /*  380 */  0,
  /*  381 */  0,
  /*  382 */  0,
  /*  383 */  iRegL_rule,
  /*  384 */  iRegL_rule,
  /*  385 */  0,
  /*  386 */  0,
  /*  387 */  0,
  /*  388 */  0,
  /*  389 */  0,
  /*  390 */  _Binary_iRegL_iRegN_rule,
  /*  391 */  iRegL_rule,
  /*  392 */  0,
  /*  393 */  0,
  /*  394 */  iRegN_P2N_rule,
  /*  395 */  iRegN_rule,
  /*  396 */  0,
  /*  397 */  0,
  /*  398 */  0,
  /*  399 */  0,
  /*  400 */  0,
  /*  401 */  0,
  /*  402 */  0,
  /*  403 */  0,
  /*  404 */  0,
  /*  405 */  0,
  /*  406 */  0,
  /*  407 */  0,
  /*  408 */  0,
  /*  409 */  _Binary_iRegN_iRegN_P2N_rule,
  /*  410 */  _Binary_iRegN_immN0_rule,
  /*  411 */  _Binary_iRegI_iRegI_rule,
  /*  412 */  _Binary_iRegI_immI16_rule,
  /*  413 */  _Binary_iRegP_iRegP_N2P_rule,
  /*  414 */  _Binary_iRegP_immP0_rule,
  /*  415 */  _Binary_regF_regF_rule,
  /*  416 */  _Binary_regD_regD_rule,
  /*  417 */  _Binary_iRegL_iRegL_rule,
  /*  418 */  _Binary_iRegL_immL16_rule,
  /*  419 */  _Binary_rarg5RegI_iRegI_rule,
  /*  420 */  _Binary_rarg5RegL_iRegL_rule,
  /*  421 */  _Binary_rarg5RegP_iRegP_N2P_rule,
  /*  422 */  _Binary_rarg5RegN_iRegN_P2N_rule,
  /*  423 */  immI8_rule,
  /*  424 */  immI16_rule,
  /*  425 */  immI_rule,
  /*  426 */  iRegI_rule,
  /*  427 */  immL8_rule,
  /*  428 */  immL16_rule,
  /*  429 */  immL32_rule,
  /*  430 */  iRegL_rule,
  /*  431 */  iRegI_rule,
  /*  432 */  iRegL_rule,
  /*  433 */  iRegI_rule,
  /*  434 */  iRegL_rule,
  /*  435 */  iRegN_rule,
  /*  436 */  iRegP_rule,
  /*  437 */  iRegI_rule,
  /*  438 */  iRegI_rule,
  /*  439 */  immI16_rule,
  /*  440 */  immI16_rule,
  /*  441 */  immI_rule,
  /*  442 */  uimmI12_rule,
  /*  443 */  immI20_rule,
  /*  444 */  uimmI12_rule,
  /*  445 */  immI20_rule,
  /*  446 */  _LoadI_memory__rule,
  /*  447 */  iRegI_rule,
  /*  448 */  _AddI__LoadI_memoryRSY__immI8_rule,
  /*  449 */  _ConvI2L_iRegI__rule,
  /*  450 */  iRegL_rule,
  /*  451 */  iRegL_rule,
  /*  452 */  iRegL_rule,
  /*  453 */  uimmL12_rule,
  /*  454 */  immL20_rule,
  /*  455 */  immL32_rule,
  /*  456 */  immL16_rule,
  /*  457 */  immL16_rule,
  /*  458 */  _ConvI2L__LoadI_memory___rule,
  /*  459 */  iRegL_rule,
  /*  460 */  _LoadL_memory__rule,
  /*  461 */  iRegL_rule,
  /*  462 */  uimmL12_rule,
  /*  463 */  immL20_rule,
  /*  464 */  _AddL__LoadL_memoryRSY__immL8_rule,
  /*  465 */  iRegL_rule,
  /*  466 */  iRegL_rule,
  /*  467 */  iRegL_rule,
  /*  468 */  uimmL12_rule,
  /*  469 */  immL16_rule,
  /*  470 */  immL16_rule,
  /*  471 */  immL20_rule,
  /*  472 */  immL32_rule,
  /*  473 */  uimmL12_rule,
  /*  474 */  uimmL12_rule,
  /*  475 */  immL20_rule,
  /*  476 */  immL20_rule,
  /*  477 */  _AddP__LoadP_memoryRSY__immL8_rule,
  /*  478 */  iRegI_rule,
  /*  479 */  iRegI_rule,
  /*  480 */  _LoadI_memory__rule,
  /*  481 */  iRegI_rule,
  /*  482 */  iRegL_rule,
  /*  483 */  iRegL_rule,
  /*  484 */  _ConvI2L_iRegI__rule,
  /*  485 */  _ConvI2L__LoadI_memory___rule,
  /*  486 */  _LoadL_memory__rule,
  /*  487 */  iRegI_rule,
  /*  488 */  immI16_rule,
  /*  489 */  immI_rule,
  /*  490 */  _LoadI_memory__rule,
  /*  491 */  iRegI_rule,
  /*  492 */  _ConvI2L_iRegI__rule,
  /*  493 */  iRegL_rule,
  /*  494 */  iRegL_rule,
  /*  495 */  immL16_rule,
  /*  496 */  immL32_rule,
  /*  497 */  _ConvI2L__LoadI_memory___rule,
  /*  498 */  iRegL_rule,
  /*  499 */  _LoadL_memory__rule,
  /*  500 */  iRegL_rule,
  /*  501 */  iRegL_rule,
  /*  502 */  noOdd_iRegI_rule,
  /*  503 */  noOdd_iRegI_rule,
  /*  504 */  immI16_rule,
  /*  505 */  iRegI_rule,
  /*  506 */  iRegL_rule,
  /*  507 */  iRegL_rule,
  /*  508 */  iRegL_rule,
  /*  509 */  immL16_rule,
  /*  510 */  noOdd_iRegI_rule,
  /*  511 */  iRegI_rule,
  /*  512 */  immI16_rule,
  /*  513 */  iRegL_rule,
  /*  514 */  iRegL_rule,
  /*  515 */  immL16_rule,
  /*  516 */  iRegI_rule,
  /*  517 */  immI_rule,
  /*  518 */  immI_1_rule,
  /*  519 */  iRegI_rule,
  /*  520 */  immI_rule,
  /*  521 */  immI_1_rule,
  /*  522 */  iRegI_rule,
  /*  523 */  immI_rule,
  /*  524 */  iRegI_rule,
  /*  525 */  immI_rule,
  /*  526 */  iRegI_rule,
  /*  527 */  immI_rule,
  /*  528 */  iRegI_rule,
  /*  529 */  immI_rule,
  /*  530 */  immI_rule,
  /*  531 */  _URShiftI_iRegI_immI8_rule,
  /*  532 */  _LShiftI_iRegI_immI8_rule,
  /*  533 */  _URShiftL_iRegL_immI8_rule,
  /*  534 */  _LShiftL_iRegL_immI8_rule,
  /*  535 */  _LShiftI_iRegI_immI8_rule,
  /*  536 */  _URShiftI_iRegI_immI8_rule,
  /*  537 */  _LShiftL_iRegL_immI8_rule,
  /*  538 */  _URShiftL_iRegL_immI8_rule,
  /*  539 */  regF_rule,
  /*  540 */  _LoadF_memoryRX__rule,
  /*  541 */  regF_rule,
  /*  542 */  regD_rule,
  /*  543 */  _LoadD_memoryRX__rule,
  /*  544 */  regD_rule,
  /*  545 */  regF_rule,
  /*  546 */  _LoadF_memoryRX__rule,
  /*  547 */  regD_rule,
  /*  548 */  _LoadD_memoryRX__rule,
  /*  549 */  regF_rule,
  /*  550 */  _LoadF_memoryRX__rule,
  /*  551 */  regF_rule,
  /*  552 */  regD_rule,
  /*  553 */  _LoadD_memoryRX__rule,
  /*  554 */  regD_rule,
  /*  555 */  _Binary_regF_regF_rule,
  /*  556 */  _Binary_regD_regD_rule,
  /*  557 */  _Binary_regF_regF_rule,
  /*  558 */  _Binary_regD_regD_rule,
  /*  559 */  _Binary_regF__LoadF_memoryRX__rule,
  /*  560 */  _Binary_regD__LoadD_memoryRX__rule,
  /*  561 */  _Binary_regF__LoadF_memoryRX__rule,
  /*  562 */  _Binary_regD__LoadD_memoryRX__rule,
  /*  563 */  _Binary__LoadF_memoryRX__regF_rule,
  /*  564 */  _Binary__LoadD_memoryRX__regD_rule,
  /*  565 */  _Binary__LoadF_memoryRX__regF_rule,
  /*  566 */  _Binary__LoadD_memoryRX__regD_rule,
  /*  567 */  regF_rule,
  /*  568 */  _LoadF_memoryRX__rule,
  /*  569 */  regD_rule,
  /*  570 */  _LoadD_memoryRX__rule,
  /*  571 */  0,
  /*  572 */  0,
  /*  573 */  0,
  /*  574 */  0,
  /*  575 */  0,
  /*  576 */  0,
  /*  577 */  0,
  /*  578 */  0,
  /*  579 */  0,
  /*  580 */  0,
  /*  581 */  iRegI_rule,
  /*  582 */  _LoadI_memory__rule,
  /*  583 */  iRegI_rule,
  /*  584 */  uimmI_rule,
  /*  585 */  uimmI_LH1_rule,
  /*  586 */  uimmI_LL1_rule,
  /*  587 */  iRegL_rule,
  /*  588 */  _LoadL_memory__rule,
  /*  589 */  iRegL_rule,
  /*  590 */  uimmL_LL1_rule,
  /*  591 */  uimmL_LH1_rule,
  /*  592 */  uimmL_HL1_rule,
  /*  593 */  uimmL_HH1_rule,
  /*  594 */  iRegI_rule,
  /*  595 */  _LoadI_memory__rule,
  /*  596 */  iRegI_rule,
  /*  597 */  uimmI16_rule,
  /*  598 */  uimmI_rule,
  /*  599 */  iRegL_rule,
  /*  600 */  _LoadL_memory__rule,
  /*  601 */  iRegL_rule,
  /*  602 */  uimmL16_rule,
  /*  603 */  uimmL32_rule,
  /*  604 */  iRegI_rule,
  /*  605 */  _LoadI_memory__rule,
  /*  606 */  iRegI_rule,
  /*  607 */  uimmI_rule,
  /*  608 */  iRegL_rule,
  /*  609 */  _LoadL_memory__rule,
  /*  610 */  uimmL32_rule,
  /*  611 */  0,
  /*  612 */  0,
  /*  613 */  iRegI_rule,
  /*  614 */  immI_0_rule,
  /*  615 */  0,
  /*  616 */  0,
  /*  617 */  0,
  /*  618 */  0,
  /*  619 */  0,
  /*  620 */  0,
  /*  621 */  0,
  /*  622 */  0,
  /*  623 */  0,
  /*  624 */  0,
  /*  625 */  immL_32bits_rule,
  /*  626 */  immL_32bits_rule,
  /*  627 */  immL_32bits_rule,
  /*  628 */  immI_16_rule,
  /*  629 */  immI_24_rule,
  /*  630 */  0,
  /*  631 */  0,
  /*  632 */  0,
  /*  633 */  0,
  /*  634 */  0,
  /*  635 */  0,
  /*  636 */  0,
  /*  637 */  _CmpU_iRegI_uimmI16_rule,
  /*  638 */  _CmpU_iRegI_iRegI_rule,
  /*  639 */  _CmpU_iRegI_uimmI16_rule,
  /*  640 */  _CmpP_iRegP_N2P_immP0_rule,
  /*  641 */  _CmpN_iRegN_P2N_immN0_rule,
  /*  642 */  iRegI_rule,
  /*  643 */  iRegI_rule,
  /*  644 */  iRegI_rule,
  /*  645 */  immI_rule,
  /*  646 */  immI_rule,
  /*  647 */  immI16_rule,
  /*  648 */  immI16_rule,
  /*  649 */  immI8_rule,
  /*  650 */  iRegI_rule,
  /*  651 */  iRegI_rule,
  /*  652 */  iRegI_rule,
  /*  653 */  immI_rule,
  /*  654 */  immI_rule,
  /*  655 */  immI16_rule,
  /*  656 */  immI16_rule,
  /*  657 */  immI8_rule,
  /*  658 */  0,
  /*  659 */  0,
  /*  660 */  _AbsI_iRegI__rule,
  /*  661 */  regF_rule,
  /*  662 */  regD_rule,
  /*  663 */  0,
  /*  664 */  0,
  /*  665 */  flagsReg_rule,
  /*  666 */  flagsReg_rule,
  /*  667 */  flagsReg_rule,
  /*  668 */  flagsReg_rule,
  /*  669 */  _CmpI_iRegI_iRegI_rule,
  /*  670 */  _CmpI_iRegI_iRegI_rule,
  /*  671 */  _CmpU_iRegI_iRegI_rule,
  /*  672 */  _CmpL_iRegL_iRegL_rule,
  /*  673 */  _CmpP_iRegP_iRegP_rule,
  /*  674 */  _CmpP__DecodeN_iRegN___DecodeN_iRegN__rule,
  /*  675 */  _CmpI_iRegI_immI8_rule,
  /*  676 */  _CmpI_iRegI_immI8_rule,
  /*  677 */  _CmpU_iRegI_uimmI8_rule,
  /*  678 */  _CmpL_iRegL_immL8_rule,
  /*  679 */  _CmpP_iRegP_immP8_rule,
  /*  680 */  _CmpP__DecodeN_iRegN__immP0_rule,
  /*  681 */  _CmpP__DecodeN_iRegN___DecodeN_immN8__rule,
  /*  682 */  _CmpI_iRegI_iRegI_rule,
  /*  683 */  _CmpI_iRegI_iRegI_rule,
  /*  684 */  _CmpU_iRegI_iRegI_rule,
  /*  685 */  _CmpL_iRegL_iRegL_rule,
  /*  686 */  _CmpP_iRegP_iRegP_rule,
  /*  687 */  _CmpP__DecodeN_iRegN___DecodeN_iRegN__rule,
  /*  688 */  _CmpI_iRegI_immI8_rule,
  /*  689 */  _CmpI_iRegI_immI8_rule,
  /*  690 */  _CmpU_iRegI_uimmI8_rule,
  /*  691 */  _CmpL_iRegL_immL8_rule,
  /*  692 */  _CmpP_iRegP_immP8_rule,
  /*  693 */  _CmpP__DecodeN_iRegN__immP0_rule,
  /*  694 */  _CmpP__DecodeN_iRegN___DecodeN_immN8__rule,
  /*  695 */  iRegL_rule,
  /*  696 */  0,
  /*  697 */  0,
  /*  698 */  0,
  /*  699 */  0,
  /*  700 */  0,
  /*  701 */  0,
  /*  702 */  0,
  /*  703 */  inline_cache_regP_rule,
  /*  704 */  0,
  /*  705 */  rarg1RegP_rule,
  /*  706 */  0,
  /*  707 */  0,
  /*  708 */  0,
  /*  709 */  0,
  /*  710 */  rarg3RegP_rule,
  /*  711 */  rarg3RegP_rule,
  /*  712 */  _Binary_rarg1RegP_immP_rule,
  /*  713 */  iRegP_N2P_rule,
  /*  714 */  iRegP_N2P_rule,
  /*  715 */  iRegP_N2P_rule,
  /*  716 */  iRegI_rule,
  /*  717 */  uimmI8_rule,
  /*  718 */  immI8_rule,
  /*  719 */  iRegP_rule,
  /*  720 */  iRegP_rule,
  /*  721 */  _Binary_iRegP_rarg5RegI_rule,
  /*  722 */  _Binary_iRegP_rarg5RegI_rule,
  /*  723 */  _Binary_iRegP_rarg5RegI_rule,
  /*  724 */  _Binary_iRegP_rarg5RegI_rule,
  /*  725 */  iRegI_rule,
  /*  726 */  iRegI_rule,
  /*  727 */  _Binary_immP_immI_1_rule,
  /*  728 */  _Binary_immP_immI_1_rule,
  /*  729 */  _Binary_immP_immI_1_rule,
  /*  730 */  _Binary_iRegP_immI16_rule,
  /*  731 */  _Binary_iRegP_immI16_rule,
  /*  732 */  _Binary_iRegP_immI16_rule,
  /*  733 */  _Binary_iRegP_rarg5RegI_rule,
  /*  734 */  _Binary_iRegP_rarg5RegI_rule,
  /*  735 */  _Binary_iRegP_rarg5RegI_rule,
  /*  736 */  _Binary_iRegP_iRegI_rule,
  /*  737 */  _Binary_iRegP_iRegI_rule,
  /*  738 */  _Binary_iRegP_immI_rule,
  /*  739 */  iRegI_rule,
  /*  740 */  _Binary_iRegP_iRegI_rule,
  /*  741 */  _Binary_iRegP_iRegI_rule,
  /*  742 */  0,
  /*  743 */  0,
  /*  744 */  0,
  /*  745 */  0,
  /*  746 */  0,
  /*  747 */  0,
  /*  748 */  0,
  /*  749 */  iRegL_rule,
  /*  750 */  vecX_rule,
  /*  751 */  0,
  /*  752 */  0,
  /*  753 */  vecX_rule,
  /*  754 */  vecX_rule,
  /*  755 */  vecX_rule,
  /*  756 */  vecX_rule,
  /*  757 */  vecX_rule,
  /*  758 */  vecX_rule,
  /*  759 */  vecX_rule,
  /*  760 */  vecX_rule,
  /*  761 */  vecX_rule,
  /*  762 */  vecX_rule,
  /*  763 */  vecX_rule,
  /*  764 */  vecX_rule,
  /*  765 */  vecX_rule,
  /*  766 */  vecX_rule,
  /*  767 */  vecX_rule,
  /*  768 */  vecX_rule,
  /*  769 */  vecX_rule,
  /*  770 */  vecX_rule,
  /*  771 */  vecX_rule,
  /*  772 */  immI8_rule,
  /*  773 */  0,
  /*  774 */  0,
  /*  775 */  0,
  /*  776 */  0,
  /*  777 */  0,
  /*  778 */  0,
  /*  779 */  0,
  /*  780 */  0,
  /*  781 */  0,
  /*  782 */  0,
  /*  783 */  0,
  /*  784 */  0,
  /*  785 */  memoryRegP_rule,
  /*  786 */  iRegN_P2N_rule,
  /*  787 */  _Binary_rarg5RegN_iRegN_P2N_rule,
  /*  788 */  _Binary_rarg5RegN_iRegN_P2N_rule,
  /*  789 */  _Binary_rarg5RegN_iRegN_P2N_rule,
  /*  790 */  0,
  /*  791 */  iRegN_rule,
  /*  792 */  _Binary_rarg5RegP_iRegP_N2P_rule,
  /*  793 */  _Binary_rarg5RegP_iRegP_N2P_rule,
  /*  794 */  _Binary_rarg5RegP_iRegP_N2P_rule,
  /*  795 */  0,
  /*  796 */  iRegP_rule,
  /*  797 */  _EncodeP_iRegP__rule,
  // last instruction
  0 // no trailing comma
};

const char        *ruleName[] = {
  /*    0 */  "UNIVERSE",
  /*    1 */  "LABEL",
  /*    2 */  "SREGI",
  /*    3 */  "SREGP",
  /*    4 */  "SREGF",
  /*    5 */  "SREGD",
  /*    6 */  "SREGL",
  /*    7 */  "METHOD",
  /*    8 */  "VECX",
  /*    9 */  "V16TEMPREG",
  /*   10 */  "V17TEMPREG",
  /*   11 */  "V18TEMPREG",
  /*   12 */  "V19TEMPREG",
  /*   13 */  "V20TEMPREG",
  /*   14 */  "V21TEMPREG",
  /*   15 */  "V22TEMPREG",
  /*   16 */  "V23TEMPREG",
  /*   17 */  "V24TEMPREG",
  /*   18 */  "V25TEMPREG",
  /*   19 */  "IMMB_MINUS1",
  /*   20 */  "IMMB_N0M1",
  /*   21 */  "IMMS_MINUS1",
  /*   22 */  "IMMS_N0M1",
  /*   23 */  "IMMI",
  /*   24 */  "IMMI20",
  /*   25 */  "IMMI16",
  /*   26 */  "IMMI8",
  /*   27 */  "IMMI_0",
  /*   28 */  "IMMI_MINUS1",
  /*   29 */  "IMMI_N0M1",
  /*   30 */  "UIMMI",
  /*   31 */  "UIMMI16",
  /*   32 */  "UIMMI12",
  /*   33 */  "UIMMI8",
  /*   34 */  "SSLENDW",
  /*   35 */  "IMMI_1",
  /*   36 */  "IMMI_16",
  /*   37 */  "IMMI_24",
  /*   38 */  "IMMI_32_63",
  /*   39 */  "UIMMI_LL1",
  /*   40 */  "UIMMI_LH1",
  /*   41 */  "IMML",
  /*   42 */  "IMML32",
  /*   43 */  "IMML20",
  /*   44 */  "IMML16",
  /*   45 */  "IMML8",
  /*   46 */  "UIMML32",
  /*   47 */  "UIMML16",
  /*   48 */  "UIMML12",
  /*   49 */  "IMML_FFFFFFFF",
  /*   50 */  "IMML_0",
  /*   51 */  "UIMML_LL1",
  /*   52 */  "UIMML_LH1",
  /*   53 */  "UIMML_HL1",
  /*   54 */  "UIMML_HH1",
  /*   55 */  "IMML_32BITS",
  /*   56 */  "IMMP",
  /*   57 */  "IMMP16",
  /*   58 */  "IMMP8",
  /*   59 */  "IMMP0",
  /*   60 */  "IMMN",
  /*   61 */  "IMMNKLASS",
  /*   62 */  "IMMN8",
  /*   63 */  "IMMN0",
  /*   64 */  "IMMD",
  /*   65 */  "IMMDPM0",
  /*   66 */  "IMMDP0",
  /*   67 */  "IMMF",
  /*   68 */  "IMMFPM0",
  /*   69 */  "IMMFP0",
  /*   70 */  "IREGI",
  /*   71 */  "NOARG_IREGI",
  /*   72 */  "REVENREGI",
  /*   73 */  "RODDREGI",
  /*   74 */  "RARG1REGI",
  /*   75 */  "RARG2REGI",
  /*   76 */  "RARG3REGI",
  /*   77 */  "RARG4REGI",
  /*   78 */  "RARG5REGI",
  /*   79 */  "NOODD_IREGI",
  /*   80 */  "IREGP",
  /*   81 */  "THREADREGP",
  /*   82 */  "R10TEMPREGP",
  /*   83 */  "R11TEMPREGP",
  /*   84 */  "NOARG_IREGP",
  /*   85 */  "RARG1REGP",
  /*   86 */  "RARG2REGP",
  /*   87 */  "RARG3REGP",
  /*   88 */  "RARG4REGP",
  /*   89 */  "RARG5REGP",
  /*   90 */  "MEMORYREGP",
  /*   91 */  "REVENREGP",
  /*   92 */  "RODDREGP",
  /*   93 */  "IREGN",
  /*   94 */  "NOARG_IREGN",
  /*   95 */  "RARG1REGN",
  /*   96 */  "RARG2REGN",
  /*   97 */  "RARG3REGN",
  /*   98 */  "RARG4REGN",
  /*   99 */  "RARG5REGN",
  /*  100 */  "IREGL",
  /*  101 */  "REVENREGL",
  /*  102 */  "RODDREGL",
  /*  103 */  "ALLRODDREGL",
  /*  104 */  "RARG1REGL",
  /*  105 */  "RARG5REGL",
  /*  106 */  "FLAGSREG",
  /*  107 */  "REGD",
  /*  108 */  "REGF",
  /*  109 */  "INLINE_CACHE_REGP",
  /*  110 */  "INDIRECT",
  /*  111 */  "INDOFFSET20",
  /*  112 */  "INDOFFSET20NARROW",
  /*  113 */  "INDOFFSET12",
  /*  114 */  "INDOFFSET12NARROW",
  /*  115 */  "INDINDEX",
  /*  116 */  "INDOFFSET20INDEX",
  /*  117 */  "INDOFFSET20INDEXNARROW",
  /*  118 */  "INDOFFSET12INDEX",
  /*  119 */  "INDOFFSET12INDEXNARROW",
  /*  120 */  "STACKSLOTI",
  /*  121 */  "STACKSLOTP",
  /*  122 */  "STACKSLOTF",
  /*  123 */  "STACKSLOTD",
  /*  124 */  "STACKSLOTL",
  /*  125 */  "CMPOPT",
  /*  126 */  "CMPOPF",
  /*  127 */  "CMPOP",
  // last operand
  /*  128 */  "MEMORY",
  /*  129 */  "MEMORYRXY",
  /*  130 */  "MEMORYRX",
  /*  131 */  "MEMORYRSY",
  /*  132 */  "MEMORYRS",
  /*  133 */  "IREGN_P2N",
  /*  134 */  "IREGP_N2P",
  // last operand class
  /*  135 */  "_DecodeN_iRegN_",
  /*  136 */  "_AddP_memoryRegP_iRegL",
  /*  137 */  "_AddP__DecodeN_iRegN__iRegL",
  /*  138 */  "_LoadB_memory_",
  /*  139 */  "_LoadUB_memory_",
  /*  140 */  "_LoadS_memory_",
  /*  141 */  "_LoadUS_memory_",
  /*  142 */  "_LoadI_memory_",
  /*  143 */  "_ConvI2L__LoadI_memory__",
  /*  144 */  "_LoadP_memory_",
  /*  145 */  "_LoadN_memory_",
  /*  146 */  "_LoadNKlass_memory_",
  /*  147 */  "_Binary_iRegL_iRegN",
  /*  148 */  "_Binary_cmpOp_flagsReg",
  /*  149 */  "_Binary_iRegN_iRegN_P2N",
  /*  150 */  "_Binary_iRegN_immN0",
  /*  151 */  "_Binary_iRegI_iRegI",
  /*  152 */  "_Binary_iRegI_immI16",
  /*  153 */  "_Binary_iRegP_iRegP_N2P",
  /*  154 */  "_Binary_iRegP_immP0",
  /*  155 */  "_Binary_cmpOpF_flagsReg",
  /*  156 */  "_Binary_regF_regF",
  /*  157 */  "_Binary_regD_regD",
  /*  158 */  "_Binary_iRegL_iRegL",
  /*  159 */  "_Binary_iRegL_immL16",
  /*  160 */  "_Binary_rarg5RegI_iRegI",
  /*  161 */  "_Binary_rarg5RegL_iRegL",
  /*  162 */  "_Binary_rarg5RegP_iRegP_N2P",
  /*  163 */  "_Binary_rarg5RegN_iRegN_P2N",
  /*  164 */  "_AddI_iRegI_iRegI",
  /*  165 */  "_LoadI_memoryRSY_",
  /*  166 */  "_AddI__LoadI_memoryRSY__immI8",
  /*  167 */  "_ConvI2L_iRegI_",
  /*  168 */  "_LoadL_memory_",
  /*  169 */  "_AddL_iRegL_iRegL",
  /*  170 */  "_LoadL_memoryRSY_",
  /*  171 */  "_AddL__LoadL_memoryRSY__immL8",
  /*  172 */  "_AddP_iRegP_N2P_iRegL",
  /*  173 */  "_LoadP_memoryRSY_",
  /*  174 */  "_AddP__LoadP_memoryRSY__immL8",
  /*  175 */  "_CastP2X_iRegP_N2P_",
  /*  176 */  "_LShiftI_iRegI_immI8",
  /*  177 */  "_URShiftI_iRegI_immI8",
  /*  178 */  "_LShiftL_iRegL_immI8",
  /*  179 */  "_URShiftL_iRegL_immI8",
  /*  180 */  "_LoadF_memoryRX_",
  /*  181 */  "_LoadD_memoryRX_",
  /*  182 */  "_NegF_regF_",
  /*  183 */  "_NegD_regD_",
  /*  184 */  "_Binary_regF__LoadF_memoryRX_",
  /*  185 */  "_Binary_regD__LoadD_memoryRX_",
  /*  186 */  "_Binary__LoadF_memoryRX__regF",
  /*  187 */  "_Binary__LoadD_memoryRX__regD",
  /*  188 */  "_AbsF_regF_",
  /*  189 */  "_AbsD_regD_",
  /*  190 */  "_LShiftI_iRegI_immI_16",
  /*  191 */  "_LShiftI_iRegI_immI_24",
  /*  192 */  "_RShiftL_iRegL_immI_32_63",
  /*  193 */  "_CmpU_iRegI_uimmI16",
  /*  194 */  "_CmpU_iRegI_iRegI",
  /*  195 */  "_CmpP_iRegP_N2P_immP0",
  /*  196 */  "_CmpN_iRegN_P2N_immN0",
  /*  197 */  "_AbsI_iRegI_",
  /*  198 */  "_CmpI_iRegI_iRegI",
  /*  199 */  "_CmpL_iRegL_iRegL",
  /*  200 */  "_CmpP_iRegP_iRegP",
  /*  201 */  "_CmpP__DecodeN_iRegN___DecodeN_iRegN_",
  /*  202 */  "_CmpI_iRegI_immI8",
  /*  203 */  "_CmpU_iRegI_uimmI8",
  /*  204 */  "_CmpL_iRegL_immL8",
  /*  205 */  "_CmpP_iRegP_immP8",
  /*  206 */  "_CmpP__DecodeN_iRegN__immP0",
  /*  207 */  "_DecodeN_immN8_",
  /*  208 */  "_CmpP__DecodeN_iRegN___DecodeN_immN8_",
  /*  209 */  "_Binary_rarg1RegP_immP",
  /*  210 */  "_Binary_iRegP_iRegP",
  /*  211 */  "_Binary_iRegP_rarg2RegI",
  /*  212 */  "_Binary_iRegP_rarg5RegI",
  /*  213 */  "_Binary_iRegP_iRegI",
  /*  214 */  "_Binary_immP_immI_1",
  /*  215 */  "_Binary_iRegP_immI16",
  /*  216 */  "_Binary_iRegP_immI",
  /*  217 */  "_EncodeP_iRegP_",
  // last internally defined operand
  /*  218 */  "regI_to_stkI",
  /*  219 */  "regL_to_stkL",
  /*  220 */  "regP_to_stkP",
  /*  221 */  "regF_to_stkF",
  /*  222 */  "regD_to_stkD",
  /*  223 */  "stfSSD",
  /*  224 */  "stfSSF",
  /*  225 */  "stkI_to_regI",
  /*  226 */  "stkL_to_regL",
  /*  227 */  "stkP_to_regP",
  /*  228 */  "stkF_to_regF",
  /*  229 */  "stkD_to_regD",
  /*  230 */  "loadConI",
  /*  231 */  "loadConI16",
  /*  232 */  "loadConI_0",
  /*  233 */  "loadConUI16",
  /*  234 */  "loadConL_pcrelTOC",
  /*  235 */  "loadConL32",
  /*  236 */  "loadConL16",
  /*  237 */  "loadConL_0",
  /*  238 */  "loadConP_pcrelTOC",
  /*  239 */  "loadConP0",
  /*  240 */  "loadConF_dynTOC",
  /*  241 */  "loadConD_dynTOC",
  /*  242 */  "loadConF0",
  /*  243 */  "loadConD0",
  /*  244 */  "loadConN",
  /*  245 */  "loadConN0",
  /*  246 */  "loadConNKlass",
  /*  247 */  "castP2X_loadP",
  /*  248 */  "loadBase",
  /*  249 */  "compN_iRegN",
  /*  250 */  "compN_iRegN_immN",
  /*  251 */  "compNKlass_iRegN_immN",
  /*  252 */  "compN_iRegN_immN0",
  /*  253 */  "castX2P",
  /*  254 */  "castP2X",
  /*  255 */  "tlsLoadP",
  /*  256 */  "checkCastPP",
  /*  257 */  "castPP",
  /*  258 */  "castII",
  /*  259 */  "castLL",
  /*  260 */  "castFF",
  /*  261 */  "castDD",
  /*  262 */  "castVV",
  /*  263 */  "overflowAddI_reg_reg",
  /*  264 */  "overflowAddI_reg_imm",
  /*  265 */  "overflowAddL_reg_reg",
  /*  266 */  "overflowAddL_reg_imm",
  /*  267 */  "overflowSubI_reg_reg",
  /*  268 */  "overflowSubI_reg_imm",
  /*  269 */  "overflowSubL_reg_reg",
  /*  270 */  "overflowSubL_reg_imm",
  /*  271 */  "overflowNegI_rReg",
  /*  272 */  "overflowNegL_rReg",
  /*  273 */  "MoveF2I_stack_reg",
  /*  274 */  "MoveI2F_stack_reg",
  /*  275 */  "MoveD2L_stack_reg",
  /*  276 */  "MoveL2D_stack_reg",
  /*  277 */  "compI_reg_reg",
  /*  278 */  "compI_reg_imm",
  /*  279 */  "compI_reg_imm16",
  /*  280 */  "compI_reg_imm0",
  /*  281 */  "compI_reg_mem",
  /*  282 */  "compU_reg_reg",
  /*  283 */  "compU_reg_uimm",
  /*  284 */  "compU_reg_mem",
  /*  285 */  "compL_reg_reg",
  /*  286 */  "compL_reg_regI",
  /*  287 */  "compL_reg_imm32",
  /*  288 */  "compL_reg_imm16",
  /*  289 */  "compL_reg_imm0",
  /*  290 */  "compL_conv_reg_imm0",
  /*  291 */  "compL_reg_mem",
  /*  292 */  "compL_reg_memI",
  /*  293 */  "compUL_reg_reg",
  /*  294 */  "compUL_reg_imm32",
  /*  295 */  "compP_reg_reg",
  /*  296 */  "compP_reg_imm0",
  /*  297 */  "compP_decode_reg_imm0",
  /*  298 */  "compP_reg_mem",
  /*  299 */  "cmpF_cc",
  /*  300 */  "cmpD_cc",
  /*  301 */  "cmpF_cc_mem",
  /*  302 */  "cmpD_cc_mem",
  /*  303 */  "cmpF0_cc",
  /*  304 */  "cmpD0_cc",
  /*  305 */  "cmpFastLock",
  /*  306 */  "cmpFastUnlock",
  /*  307 */  "expand_LoadLogical_I2L",
  /*  308 */  "Repl8B_imm",
  /*  309 */  "Repl8B_imm0",
  /*  310 */  "Repl8B_immm1",
  /*  311 */  "Repl4S_imm",
  /*  312 */  "Repl4S_imm0",
  /*  313 */  "Repl4S_immm1",
  /*  314 */  "repl8S_reg_Ex",
  /*  315 */  "repl8S_immIminus1",
  /*  316 */  "repl8S_immI0",
  /*  317 */  "Repl2I_imm",
  /*  318 */  "Repl2I_imm0",
  /*  319 */  "Repl2I_immm1",
  /*  320 */  "repl4I_reg_Ex",
  /*  321 */  "repl4I_immI0",
  /*  322 */  "repl4I_immIminus1",
  /*  323 */  "Repl2F_imm",
  /*  324 */  "Repl2F_imm0",
  /*  325 */  "repl4F_reg_Ex",
  /*  326 */  "repl4F_immF0",
  /*  327 */  "repl2D_reg_Ex",
  /*  328 */  "repl2D_immD0",
  /*  329 */  "repl16B_reg_Ex",
  /*  330 */  "repl16B_immIminus1",
  /*  331 */  "repl16B_immI0",
  /*  332 */  "repl2L_reg_Ex",
  /*  333 */  "repl2L_immIminus1",
  /*  334 */  "repl2L_immI0",
  /*  335 */  "reinterpret",
  /*  336 */  "reinterpretX",
  /*  337 */  "vsqrt4F_reg",
  /*  338 */  "vsqrt2D_reg",
  /*  339 */  "vpopcnt_reg",
  /*  340 */  "loadB",
  /*  341 */  "loadB2L",
  /*  342 */  "loadUB",
  /*  343 */  "loadUB2L",
  /*  344 */  "loadS",
  /*  345 */  "loadS2L",
  /*  346 */  "loadUS",
  /*  347 */  "loadUS2L",
  /*  348 */  "loadI",
  /*  349 */  "loadI2L",
  /*  350 */  "loadUI2L",
  /*  351 */  "loadRange",
  /*  352 */  "loadL",
  /*  353 */  "loadL_unaligned",
  /*  354 */  "loadP",
  /*  355 */  "loadKlass",
  /*  356 */  "loadTOC",
  /*  357 */  "loadF",
  /*  358 */  "loadD",
  /*  359 */  "loadD_unaligned",
  /*  360 */  "storeB",
  /*  361 */  "storeC",
  /*  362 */  "storeI",
  /*  363 */  "storeL",
  /*  364 */  "storeP",
  /*  365 */  "storeF",
  /*  366 */  "storeD",
  /*  367 */  "prefetchAlloc",
  /*  368 */  "memInitB",
  /*  369 */  "memInitC",
  /*  370 */  "memInitI",
  /*  371 */  "memInitL",
  /*  372 */  "memInitP",
  /*  373 */  "negL_reg_reg",
  /*  374 */  "loadN",
  /*  375 */  "loadNKlass",
  /*  376 */  "loadNKlassCompactHeaders",
  /*  377 */  "decodeLoadN",
  /*  378 */  "decodeLoadNKlass",
  /*  379 */  "decodeLoadConNKlass",
  /*  380 */  "decodeN",
  /*  381 */  "decodeKlass",
  /*  382 */  "decodeN_NN",
  /*  383 */  "decodeN_base",
  /*  384 */  "decodeN_NN_base",
  /*  385 */  "decodeN_Ex",
  /*  386 */  "decodeN_NN_Ex",
  /*  387 */  "encodeP",
  /*  388 */  "encodeKlass",
  /*  389 */  "encodeP_NN",
  /*  390 */  "encodeP_base",
  /*  391 */  "encodeP_NN_base",
  /*  392 */  "encodeP_Ex",
  /*  393 */  "encodeP_NN_Ex",
  /*  394 */  "storeN",
  /*  395 */  "storeNKlass",
  /*  396 */  "membar_acquire",
  /*  397 */  "membar_acquire_0",
  /*  398 */  "membar_acquire_lock",
  /*  399 */  "membar_release",
  /*  400 */  "membar_release_0",
  /*  401 */  "membar_release_lock",
  /*  402 */  "membar_storeload",
  /*  403 */  "membar_volatile",
  /*  404 */  "unnecessary_membar_volatile",
  /*  405 */  "membar_full",
  /*  406 */  "membar_CPUOrder",
  /*  407 */  "membar_storestore",
  /*  408 */  "membar_storestore_0",
  /*  409 */  "cmovN_reg",
  /*  410 */  "cmovN_imm",
  /*  411 */  "cmovI_reg",
  /*  412 */  "cmovI_imm",
  /*  413 */  "cmovP_reg",
  /*  414 */  "cmovP_imm",
  /*  415 */  "cmovF_reg",
  /*  416 */  "cmovD_reg",
  /*  417 */  "cmovL_reg",
  /*  418 */  "cmovL_imm",
  /*  419 */  "compareAndSwapI_bool",
  /*  420 */  "compareAndSwapL_bool",
  /*  421 */  "compareAndSwapP_bool",
  /*  422 */  "compareAndSwapN_bool",
  /*  423 */  "addI_mem_imm8_atomic_no_res",
  /*  424 */  "addI_mem_imm16_atomic",
  /*  425 */  "addI_mem_imm32_atomic",
  /*  426 */  "addI_mem_reg_atomic",
  /*  427 */  "addL_mem_imm8_atomic_no_res",
  /*  428 */  "addL_mem_imm16_atomic",
  /*  429 */  "addL_mem_imm32_atomic",
  /*  430 */  "addL_mem_reg_atomic",
  /*  431 */  "addI_mem_reg_atomic_z196",
  /*  432 */  "addL_mem_reg_atomic_z196",
  /*  433 */  "xchgI_reg_mem",
  /*  434 */  "xchgL_reg_mem",
  /*  435 */  "xchgN_reg_mem",
  /*  436 */  "xchgP_reg_mem",
  /*  437 */  "addI_reg_reg_CISC",
  /*  438 */  "addI_reg_reg_RISC",
  /*  439 */  "addI_reg_imm16_CISC",
  /*  440 */  "addI_reg_imm16_RISC",
  /*  441 */  "addI_reg_imm32",
  /*  442 */  "addI_reg_imm12",
  /*  443 */  "addI_reg_imm20",
  /*  444 */  "addI_reg_reg_imm12",
  /*  445 */  "addI_reg_reg_imm20",
  /*  446 */  "addI_Reg_mem",
  /*  447 */  "addI_Reg_mem_0",
  /*  448 */  "addI_mem_imm",
  /*  449 */  "addL_reg_regI",
  /*  450 */  "addL_reg_regI_0",
  /*  451 */  "addL_reg_reg_CISC",
  /*  452 */  "addL_reg_reg_RISC",
  /*  453 */  "addL_reg_imm12",
  /*  454 */  "addL_reg_imm20",
  /*  455 */  "addL_reg_imm32",
  /*  456 */  "addL_reg_imm16_CISC",
  /*  457 */  "addL_reg_imm16_RISC",
  /*  458 */  "addL_Reg_memI",
  /*  459 */  "addL_Reg_memI_0",
  /*  460 */  "addL_Reg_mem",
  /*  461 */  "addL_Reg_mem_0",
  /*  462 */  "addL_reg_reg_imm12",
  /*  463 */  "addL_reg_reg_imm20",
  /*  464 */  "addL_mem_imm",
  /*  465 */  "addP_reg_reg_LA",
  /*  466 */  "addP_reg_reg_CISC",
  /*  467 */  "addP_reg_reg_RISC",
  /*  468 */  "addP_reg_imm12",
  /*  469 */  "addP_reg_imm16_CISC",
  /*  470 */  "addP_reg_imm16_RISC",
  /*  471 */  "addP_reg_imm20",
  /*  472 */  "addP_reg_imm32",
  /*  473 */  "addP_reg_reg_imm12",
  /*  474 */  "addP_regN_reg_imm12",
  /*  475 */  "addP_reg_reg_imm20",
  /*  476 */  "addP_regN_reg_imm20",
  /*  477 */  "addP_mem_imm",
  /*  478 */  "subI_reg_reg_CISC",
  /*  479 */  "subI_reg_reg_RISC",
  /*  480 */  "subI_Reg_mem",
  /*  481 */  "subI_zero_reg",
  /*  482 */  "subL_reg_reg_CISC",
  /*  483 */  "subL_reg_reg_RISC",
  /*  484 */  "subL_reg_regI_CISC",
  /*  485 */  "subL_Reg_memI",
  /*  486 */  "subL_Reg_mem",
  /*  487 */  "mulI_reg_reg",
  /*  488 */  "mulI_reg_imm16",
  /*  489 */  "mulI_reg_imm32",
  /*  490 */  "mulI_Reg_mem",
  /*  491 */  "mulI_Reg_mem_0",
  /*  492 */  "mulL_reg_regI",
  /*  493 */  "mulL_reg_regI_0",
  /*  494 */  "mulL_reg_reg",
  /*  495 */  "mulL_reg_imm16",
  /*  496 */  "mulL_reg_imm32",
  /*  497 */  "mulL_Reg_memI",
  /*  498 */  "mulL_Reg_memI_0",
  /*  499 */  "mulL_Reg_mem",
  /*  500 */  "mulL_Reg_mem_0",
  /*  501 */  "mulHiL_reg_reg",
  /*  502 */  "divModI_reg_divmod",
  /*  503 */  "divI_reg_reg",
  /*  504 */  "divI_reg_imm16",
  /*  505 */  "udivI_reg_reg",
  /*  506 */  "divModL_reg_divmod",
  /*  507 */  "divL_reg_reg",
  /*  508 */  "udivL_reg_reg",
  /*  509 */  "divL_reg_imm16",
  /*  510 */  "modI_reg_reg",
  /*  511 */  "umodI_reg_reg",
  /*  512 */  "modI_reg_imm16",
  /*  513 */  "modL_reg_reg",
  /*  514 */  "umodL_reg_reg",
  /*  515 */  "modL_reg_imm16",
  /*  516 */  "sllI_reg_reg",
  /*  517 */  "sllI_reg_imm",
  /*  518 */  "sllI_reg_imm_1",
  /*  519 */  "sllL_reg_reg",
  /*  520 */  "sllL_reg_imm",
  /*  521 */  "sllL_reg_imm_1",
  /*  522 */  "sraI_reg_reg",
  /*  523 */  "sraI_reg_imm",
  /*  524 */  "sraL_reg_reg",
  /*  525 */  "sraL_reg_imm",
  /*  526 */  "srlI_reg_reg",
  /*  527 */  "srlI_reg_imm",
  /*  528 */  "srlL_reg_reg",
  /*  529 */  "srlL_reg_imm",
  /*  530 */  "srlP_reg_imm",
  /*  531 */  "rotlI_reg_immI8",
  /*  532 */  "rotlI_reg_immI8_0",
  /*  533 */  "rotlL_reg_immI8",
  /*  534 */  "rotlL_reg_immI8_0",
  /*  535 */  "rotrI_reg_immI8",
  /*  536 */  "rotrI_reg_immI8_0",
  /*  537 */  "rotrL_reg_immI8",
  /*  538 */  "rotrL_reg_immI8_0",
  /*  539 */  "addF_reg_reg",
  /*  540 */  "addF_reg_mem",
  /*  541 */  "addF_reg_mem_0",
  /*  542 */  "addD_reg_reg",
  /*  543 */  "addD_reg_mem",
  /*  544 */  "addD_reg_mem_0",
  /*  545 */  "subF_reg_reg",
  /*  546 */  "subF_reg_mem",
  /*  547 */  "subD_reg_reg",
  /*  548 */  "subD_reg_mem",
  /*  549 */  "mulF_reg_reg",
  /*  550 */  "mulF_reg_mem",
  /*  551 */  "mulF_reg_mem_0",
  /*  552 */  "mulD_reg_reg",
  /*  553 */  "mulD_reg_mem",
  /*  554 */  "mulD_reg_mem_0",
  /*  555 */  "maddF_reg_reg",
  /*  556 */  "maddD_reg_reg",
  /*  557 */  "msubF_reg_reg",
  /*  558 */  "msubD_reg_reg",
  /*  559 */  "maddF_reg_mem",
  /*  560 */  "maddD_reg_mem",
  /*  561 */  "msubF_reg_mem",
  /*  562 */  "msubD_reg_mem",
  /*  563 */  "maddF_mem_reg",
  /*  564 */  "maddD_mem_reg",
  /*  565 */  "msubF_mem_reg",
  /*  566 */  "msubD_mem_reg",
  /*  567 */  "divF_reg_reg",
  /*  568 */  "divF_reg_mem",
  /*  569 */  "divD_reg_reg",
  /*  570 */  "divD_reg_mem",
  /*  571 */  "absF_reg",
  /*  572 */  "absD_reg",
  /*  573 */  "nabsF_reg",
  /*  574 */  "nabsD_reg",
  /*  575 */  "negF_reg",
  /*  576 */  "negD_reg",
  /*  577 */  "sqrtF_reg",
  /*  578 */  "sqrtD_reg",
  /*  579 */  "sqrtF_mem",
  /*  580 */  "sqrtD_mem",
  /*  581 */  "andI_reg_reg",
  /*  582 */  "andI_Reg_mem",
  /*  583 */  "andI_Reg_mem_0",
  /*  584 */  "andI_reg_uimm32",
  /*  585 */  "andI_reg_uimmI_LH1",
  /*  586 */  "andI_reg_uimmI_LL1",
  /*  587 */  "andL_reg_reg",
  /*  588 */  "andL_Reg_mem",
  /*  589 */  "andL_Reg_mem_0",
  /*  590 */  "andL_reg_uimmL_LL1",
  /*  591 */  "andL_reg_uimmL_LH1",
  /*  592 */  "andL_reg_uimmL_HL1",
  /*  593 */  "andL_reg_uimmL_HH1",
  /*  594 */  "orI_reg_reg",
  /*  595 */  "orI_Reg_mem",
  /*  596 */  "orI_Reg_mem_0",
  /*  597 */  "orI_reg_uimm16",
  /*  598 */  "orI_reg_uimm32",
  /*  599 */  "orL_reg_reg",
  /*  600 */  "orL_Reg_mem",
  /*  601 */  "orL_Reg_mem_0",
  /*  602 */  "orL_reg_uimm16",
  /*  603 */  "orL_reg_uimm32",
  /*  604 */  "xorI_reg_reg",
  /*  605 */  "xorI_Reg_mem",
  /*  606 */  "xorI_Reg_mem_0",
  /*  607 */  "xorI_reg_uimm32",
  /*  608 */  "xorL_reg_reg",
  /*  609 */  "xorL_Reg_mem",
  /*  610 */  "xorL_reg_uimm32",
  /*  611 */  "convI2B",
  /*  612 */  "convP2B",
  /*  613 */  "cmpLTMask_reg_reg",
  /*  614 */  "cmpLTMask_reg_zero",
  /*  615 */  "convD2F_reg",
  /*  616 */  "convF2I_reg",
  /*  617 */  "convD2I_reg",
  /*  618 */  "convF2L_reg",
  /*  619 */  "convD2L_reg",
  /*  620 */  "convF2D_reg",
  /*  621 */  "convF2D_mem",
  /*  622 */  "convI2D_reg",
  /*  623 */  "convI2F_ireg",
  /*  624 */  "convI2L_reg",
  /*  625 */  "convI2L_reg_zex",
  /*  626 */  "convI2L_mem_zex",
  /*  627 */  "zeroExtend_long",
  /*  628 */  "rShiftI16_lShiftI16_reg",
  /*  629 */  "rShiftI24_lShiftI24_reg",
  /*  630 */  "MoveI2F_reg_stack",
  /*  631 */  "MoveD2L_reg_stack",
  /*  632 */  "MoveL2D_reg_stack",
  /*  633 */  "convL2F_reg",
  /*  634 */  "convL2D_reg",
  /*  635 */  "convL2I_reg",
  /*  636 */  "shrL_reg_imm6_L2I",
  /*  637 */  "rangeCheck_iReg_uimmI16",
  /*  638 */  "rangeCheck_iReg_iReg",
  /*  639 */  "rangeCheck_uimmI16_iReg",
  /*  640 */  "zeroCheckP_iReg_imm0",
  /*  641 */  "zeroCheckN_iReg_imm0",
  /*  642 */  "z196_minI_reg_reg",
  /*  643 */  "z10_minI_reg_reg",
  /*  644 */  "minI_reg_reg",
  /*  645 */  "z196_minI_reg_imm32",
  /*  646 */  "minI_reg_imm32",
  /*  647 */  "z196_minI_reg_imm16",
  /*  648 */  "minI_reg_imm16",
  /*  649 */  "z10_minI_reg_imm8",
  /*  650 */  "z196_maxI_reg_reg",
  /*  651 */  "z10_maxI_reg_reg",
  /*  652 */  "maxI_reg_reg",
  /*  653 */  "z196_maxI_reg_imm32",
  /*  654 */  "maxI_reg_imm32",
  /*  655 */  "z196_maxI_reg_imm16",
  /*  656 */  "maxI_reg_imm16",
  /*  657 */  "z10_maxI_reg_imm8",
  /*  658 */  "absI_reg",
  /*  659 */  "absL_reg",
  /*  660 */  "negabsI_reg",
  /*  661 */  "cmpF_reg",
  /*  662 */  "cmpD_reg",
  /*  663 */  "branch",
  /*  664 */  "branchFar",
  /*  665 */  "branchCon",
  /*  666 */  "branchConFar",
  /*  667 */  "branchLoopEnd",
  /*  668 */  "branchLoopEndFar",
  /*  669 */  "testAndBranchLoopEnd_Reg",
  /*  670 */  "cmpb_RegI",
  /*  671 */  "cmpbU_RegI",
  /*  672 */  "cmpb_RegL",
  /*  673 */  "cmpb_RegPP",
  /*  674 */  "cmpb_RegNN",
  /*  675 */  "testAndBranchLoopEnd_Imm",
  /*  676 */  "cmpb_RegI_imm",
  /*  677 */  "cmpbU_RegI_imm",
  /*  678 */  "cmpb_RegL_imm",
  /*  679 */  "cmpb_RegP_immP",
  /*  680 */  "cmpb_RegN_immP0",
  /*  681 */  "cmpb_RegN_imm",
  /*  682 */  "testAndBranchLoopEnd_RegFar",
  /*  683 */  "cmpb_RegI_Far",
  /*  684 */  "cmpbU_RegI_Far",
  /*  685 */  "cmpb_RegL_Far",
  /*  686 */  "cmpb_RegPP_Far",
  /*  687 */  "cmpb_RegNN_Far",
  /*  688 */  "testAndBranchLoopEnd_ImmFar",
  /*  689 */  "cmpb_RegI_imm_Far",
  /*  690 */  "cmpbU_RegI_imm_Far",
  /*  691 */  "cmpb_RegL_imm_Far",
  /*  692 */  "cmpb_RegP_immP_Far",
  /*  693 */  "cmpb_RegN_immP0_Far",
  /*  694 */  "cmpb_RegN_immN_Far",
  /*  695 */  "cmpL3_reg_reg",
  /*  696 */  "safePoint",
  /*  697 */  "safePoint_poll",
  /*  698 */  "CallStaticJavaDirect_dynTOC",
  /*  699 */  "CallDynamicJavaDirect_dynTOC",
  /*  700 */  "CallRuntimeDirect",
  /*  701 */  "CallLeafDirect",
  /*  702 */  "CallLeafNoFPDirect",
  /*  703 */  "TailCalljmpInd",
  /*  704 */  "Ret",
  /*  705 */  "tailjmpInd",
  /*  706 */  "ForwardExceptionjmp",
  /*  707 */  "CreateException",
  /*  708 */  "RethrowException",
  /*  709 */  "ShouldNotReachHere",
  /*  710 */  "partialSubtypeCheck",
  /*  711 */  "partialSubtypeCheckVarSuper",
  /*  712 */  "partialSubtypeCheckConstSuper",
  /*  713 */  "inlineCallClearArrayConst",
  /*  714 */  "inlineCallClearArrayConstBig",
  /*  715 */  "inlineCallClearArray",
  /*  716 */  "string_equalsL",
  /*  717 */  "string_equals_imm",
  /*  718 */  "string_equalsC_imm",
  /*  719 */  "array_equalsB",
  /*  720 */  "array_equalsC",
  /*  721 */  "string_compareL",
  /*  722 */  "string_compareU",
  /*  723 */  "string_compareLU",
  /*  724 */  "string_compareUL",
  /*  725 */  "indexOfChar_U",
  /*  726 */  "indexOfChar_L",
  /*  727 */  "indexOf_imm1_U",
  /*  728 */  "indexOf_imm1_L",
  /*  729 */  "indexOf_imm1_UL",
  /*  730 */  "indexOf_imm_U",
  /*  731 */  "indexOf_imm_L",
  /*  732 */  "indexOf_imm_UL",
  /*  733 */  "indexOf_U",
  /*  734 */  "indexOf_L",
  /*  735 */  "indexOf_UL",
  /*  736 */  "string_compress",
  /*  737 */  "string_inflate",
  /*  738 */  "string_inflate_const",
  /*  739 */  "count_positives",
  /*  740 */  "encode_iso_array",
  /*  741 */  "encode_ascii_array",
  /*  742 */  "expand_storeF",
  /*  743 */  "expand_Repl2I_reg",
  /*  744 */  "Repl8B_reg_risbg",
  /*  745 */  "Repl4S_reg_risbg",
  /*  746 */  "Repl2I_reg_risbg",
  /*  747 */  "Repl2F_reg_indirect",
  /*  748 */  "Repl2F_reg_direct",
  /*  749 */  "storeA8B",
  /*  750 */  "storeV16",
  /*  751 */  "loadV8",
  /*  752 */  "loadV16",
  /*  753 */  "vadd16B_reg",
  /*  754 */  "vadd8S_reg",
  /*  755 */  "vadd4I_reg",
  /*  756 */  "vadd2L_reg",
  /*  757 */  "vmul16B_reg",
  /*  758 */  "vmul8S_reg",
  /*  759 */  "vmul4I_reg",
  /*  760 */  "vsub16B_reg",
  /*  761 */  "vsub8S_reg",
  /*  762 */  "vsub4I_reg",
  /*  763 */  "vsub2L_reg",
  /*  764 */  "vadd4F_reg",
  /*  765 */  "vadd2D_reg",
  /*  766 */  "vsub4F_reg",
  /*  767 */  "vsub2D_reg",
  /*  768 */  "vmul4F_reg",
  /*  769 */  "vmul2D_reg",
  /*  770 */  "vdiv4F_reg",
  /*  771 */  "vdiv2D_reg",
  /*  772 */  "vround2D_reg",
  /*  773 */  "bytes_reverse_short",
  /*  774 */  "bytes_reverse_unsigned_short",
  /*  775 */  "bytes_reverse_int",
  /*  776 */  "bytes_reverse_long",
  /*  777 */  "countLeadingZerosI",
  /*  778 */  "countLeadingZerosL",
  /*  779 */  "countTrailingZerosI",
  /*  780 */  "countTrailingZerosL",
  /*  781 */  "popCountI_Ext3",
  /*  782 */  "popCountL_Ext3",
  /*  783 */  "popCountI",
  /*  784 */  "popCountL",
  /*  785 */  "g1StoreP",
  /*  786 */  "g1StoreN",
  /*  787 */  "g1CompareAndSwapN",
  /*  788 */  "g1CompareAndSwapN_0",
  /*  789 */  "g1CompareAndExchangeN",
  /*  790 */  "g1LoadN",
  /*  791 */  "g1GetAndSetN",
  /*  792 */  "g1CompareAndSwapP",
  /*  793 */  "g1CompareAndSwapP_0",
  /*  794 */  "g1CompareAndExchangeP",
  /*  795 */  "g1LoadP",
  /*  796 */  "g1GetAndSetP",
  /*  797 */  "g1EncodePAndStoreN",
  // last instruction
  "invalid rule name" // no trailing comma
};

const        bool  swallowed[] = {
  /*    0 */  false,
  /*    1 */  false,
  /*    2 */  false,
  /*    3 */  false,
  /*    4 */  false,
  /*    5 */  false,
  /*    6 */  false,
  /*    7 */  false,
  /*    8 */  false,
  /*    9 */  false,
  /*   10 */  false,
  /*   11 */  false,
  /*   12 */  false,
  /*   13 */  false,
  /*   14 */  false,
  /*   15 */  false,
  /*   16 */  false,
  /*   17 */  false,
  /*   18 */  false,
  /*   19 */  true,
  /*   20 */  true,
  /*   21 */  true,
  /*   22 */  true,
  /*   23 */  true,
  /*   24 */  true,
  /*   25 */  true,
  /*   26 */  true,
  /*   27 */  true,
  /*   28 */  true,
  /*   29 */  true,
  /*   30 */  true,
  /*   31 */  true,
  /*   32 */  true,
  /*   33 */  true,
  /*   34 */  true,
  /*   35 */  true,
  /*   36 */  true,
  /*   37 */  true,
  /*   38 */  true,
  /*   39 */  true,
  /*   40 */  true,
  /*   41 */  true,
  /*   42 */  true,
  /*   43 */  true,
  /*   44 */  true,
  /*   45 */  true,
  /*   46 */  true,
  /*   47 */  true,
  /*   48 */  true,
  /*   49 */  true,
  /*   50 */  true,
  /*   51 */  true,
  /*   52 */  true,
  /*   53 */  true,
  /*   54 */  true,
  /*   55 */  true,
  /*   56 */  true,
  /*   57 */  true,
  /*   58 */  true,
  /*   59 */  true,
  /*   60 */  true,
  /*   61 */  true,
  /*   62 */  true,
  /*   63 */  true,
  /*   64 */  true,
  /*   65 */  true,
  /*   66 */  true,
  /*   67 */  true,
  /*   68 */  true,
  /*   69 */  true,
  /*   70 */  false,
  /*   71 */  false,
  /*   72 */  false,
  /*   73 */  false,
  /*   74 */  false,
  /*   75 */  false,
  /*   76 */  false,
  /*   77 */  false,
  /*   78 */  false,
  /*   79 */  false,
  /*   80 */  false,
  /*   81 */  false,
  /*   82 */  false,
  /*   83 */  false,
  /*   84 */  false,
  /*   85 */  false,
  /*   86 */  false,
  /*   87 */  false,
  /*   88 */  false,
  /*   89 */  false,
  /*   90 */  false,
  /*   91 */  false,
  /*   92 */  false,
  /*   93 */  false,
  /*   94 */  false,
  /*   95 */  false,
  /*   96 */  false,
  /*   97 */  false,
  /*   98 */  false,
  /*   99 */  false,
  /*  100 */  false,
  /*  101 */  false,
  /*  102 */  false,
  /*  103 */  false,
  /*  104 */  false,
  /*  105 */  false,
  /*  106 */  false,
  /*  107 */  false,
  /*  108 */  false,
  /*  109 */  false,
  /*  110 */  false,
  /*  111 */  false,
  /*  112 */  false,
  /*  113 */  false,
  /*  114 */  false,
  /*  115 */  false,
  /*  116 */  false,
  /*  117 */  false,
  /*  118 */  false,
  /*  119 */  false,
  /*  120 */  false,
  /*  121 */  false,
  /*  122 */  false,
  /*  123 */  false,
  /*  124 */  false,
  /*  125 */  true,
  /*  126 */  true,
  /*  127 */  true,
  // last operand
  /*  128 */  false,
  /*  129 */  false,
  /*  130 */  false,
  /*  131 */  false,
  /*  132 */  false,
  /*  133 */  false,
  /*  134 */  false,
  // last operand class
  /*  135 */  false,
  /*  136 */  false,
  /*  137 */  false,
  /*  138 */  false,
  /*  139 */  false,
  /*  140 */  false,
  /*  141 */  false,
  /*  142 */  false,
  /*  143 */  false,
  /*  144 */  false,
  /*  145 */  false,
  /*  146 */  false,
  /*  147 */  false,
  /*  148 */  false,
  /*  149 */  false,
  /*  150 */  false,
  /*  151 */  false,
  /*  152 */  false,
  /*  153 */  false,
  /*  154 */  false,
  /*  155 */  false,
  /*  156 */  false,
  /*  157 */  false,
  /*  158 */  false,
  /*  159 */  false,
  /*  160 */  false,
  /*  161 */  false,
  /*  162 */  false,
  /*  163 */  false,
  /*  164 */  false,
  /*  165 */  false,
  /*  166 */  false,
  /*  167 */  false,
  /*  168 */  false,
  /*  169 */  false,
  /*  170 */  false,
  /*  171 */  false,
  /*  172 */  false,
  /*  173 */  false,
  /*  174 */  false,
  /*  175 */  false,
  /*  176 */  false,
  /*  177 */  false,
  /*  178 */  false,
  /*  179 */  false,
  /*  180 */  false,
  /*  181 */  false,
  /*  182 */  false,
  /*  183 */  false,
  /*  184 */  false,
  /*  185 */  false,
  /*  186 */  false,
  /*  187 */  false,
  /*  188 */  false,
  /*  189 */  false,
  /*  190 */  false,
  /*  191 */  false,
  /*  192 */  false,
  /*  193 */  false,
  /*  194 */  false,
  /*  195 */  false,
  /*  196 */  false,
  /*  197 */  false,
  /*  198 */  false,
  /*  199 */  false,
  /*  200 */  false,
  /*  201 */  false,
  /*  202 */  false,
  /*  203 */  false,
  /*  204 */  false,
  /*  205 */  false,
  /*  206 */  false,
  /*  207 */  false,
  /*  208 */  false,
  /*  209 */  false,
  /*  210 */  false,
  /*  211 */  false,
  /*  212 */  false,
  /*  213 */  false,
  /*  214 */  false,
  /*  215 */  false,
  /*  216 */  false,
  /*  217 */  false,
  // last internally defined operand
  /*  218 */  false,
  /*  219 */  false,
  /*  220 */  false,
  /*  221 */  false,
  /*  222 */  false,
  /*  223 */  false,
  /*  224 */  false,
  /*  225 */  false,
  /*  226 */  false,
  /*  227 */  false,
  /*  228 */  false,
  /*  229 */  false,
  /*  230 */  false,
  /*  231 */  false,
  /*  232 */  false,
  /*  233 */  false,
  /*  234 */  false,
  /*  235 */  false,
  /*  236 */  false,
  /*  237 */  false,
  /*  238 */  false,
  /*  239 */  false,
  /*  240 */  false,
  /*  241 */  false,
  /*  242 */  false,
  /*  243 */  false,
  /*  244 */  false,
  /*  245 */  false,
  /*  246 */  false,
  /*  247 */  false,
  /*  248 */  false,
  /*  249 */  false,
  /*  250 */  false,
  /*  251 */  false,
  /*  252 */  false,
  /*  253 */  false,
  /*  254 */  false,
  /*  255 */  false,
  /*  256 */  false,
  /*  257 */  false,
  /*  258 */  false,
  /*  259 */  false,
  /*  260 */  false,
  /*  261 */  false,
  /*  262 */  false,
  /*  263 */  false,
  /*  264 */  false,
  /*  265 */  false,
  /*  266 */  false,
  /*  267 */  false,
  /*  268 */  false,
  /*  269 */  false,
  /*  270 */  false,
  /*  271 */  false,
  /*  272 */  false,
  /*  273 */  false,
  /*  274 */  false,
  /*  275 */  false,
  /*  276 */  false,
  /*  277 */  false,
  /*  278 */  false,
  /*  279 */  false,
  /*  280 */  false,
  /*  281 */  false,
  /*  282 */  false,
  /*  283 */  false,
  /*  284 */  false,
  /*  285 */  false,
  /*  286 */  false,
  /*  287 */  false,
  /*  288 */  false,
  /*  289 */  false,
  /*  290 */  false,
  /*  291 */  false,
  /*  292 */  false,
  /*  293 */  false,
  /*  294 */  false,
  /*  295 */  false,
  /*  296 */  false,
  /*  297 */  false,
  /*  298 */  false,
  /*  299 */  false,
  /*  300 */  false,
  /*  301 */  false,
  /*  302 */  false,
  /*  303 */  false,
  /*  304 */  false,
  /*  305 */  false,
  /*  306 */  false,
  /*  307 */  false,
  /*  308 */  false,
  /*  309 */  false,
  /*  310 */  false,
  /*  311 */  false,
  /*  312 */  false,
  /*  313 */  false,
  /*  314 */  false,
  /*  315 */  false,
  /*  316 */  false,
  /*  317 */  false,
  /*  318 */  false,
  /*  319 */  false,
  /*  320 */  false,
  /*  321 */  false,
  /*  322 */  false,
  /*  323 */  false,
  /*  324 */  false,
  /*  325 */  false,
  /*  326 */  false,
  /*  327 */  false,
  /*  328 */  false,
  /*  329 */  false,
  /*  330 */  false,
  /*  331 */  false,
  /*  332 */  false,
  /*  333 */  false,
  /*  334 */  false,
  /*  335 */  false,
  /*  336 */  false,
  /*  337 */  false,
  /*  338 */  false,
  /*  339 */  false,
  /*  340 */  false,
  /*  341 */  false,
  /*  342 */  false,
  /*  343 */  false,
  /*  344 */  false,
  /*  345 */  false,
  /*  346 */  false,
  /*  347 */  false,
  /*  348 */  false,
  /*  349 */  false,
  /*  350 */  false,
  /*  351 */  false,
  /*  352 */  false,
  /*  353 */  false,
  /*  354 */  false,
  /*  355 */  false,
  /*  356 */  false,
  /*  357 */  false,
  /*  358 */  false,
  /*  359 */  false,
  /*  360 */  false,
  /*  361 */  false,
  /*  362 */  false,
  /*  363 */  false,
  /*  364 */  false,
  /*  365 */  false,
  /*  366 */  false,
  /*  367 */  false,
  /*  368 */  false,
  /*  369 */  false,
  /*  370 */  false,
  /*  371 */  false,
  /*  372 */  false,
  /*  373 */  false,
  /*  374 */  false,
  /*  375 */  false,
  /*  376 */  false,
  /*  377 */  false,
  /*  378 */  false,
  /*  379 */  false,
  /*  380 */  false,
  /*  381 */  false,
  /*  382 */  false,
  /*  383 */  false,
  /*  384 */  false,
  /*  385 */  false,
  /*  386 */  false,
  /*  387 */  false,
  /*  388 */  false,
  /*  389 */  false,
  /*  390 */  false,
  /*  391 */  false,
  /*  392 */  false,
  /*  393 */  false,
  /*  394 */  false,
  /*  395 */  false,
  /*  396 */  false,
  /*  397 */  false,
  /*  398 */  false,
  /*  399 */  false,
  /*  400 */  false,
  /*  401 */  false,
  /*  402 */  false,
  /*  403 */  false,
  /*  404 */  false,
  /*  405 */  false,
  /*  406 */  false,
  /*  407 */  false,
  /*  408 */  false,
  /*  409 */  false,
  /*  410 */  false,
  /*  411 */  false,
  /*  412 */  false,
  /*  413 */  false,
  /*  414 */  false,
  /*  415 */  false,
  /*  416 */  false,
  /*  417 */  false,
  /*  418 */  false,
  /*  419 */  false,
  /*  420 */  false,
  /*  421 */  false,
  /*  422 */  false,
  /*  423 */  false,
  /*  424 */  false,
  /*  425 */  false,
  /*  426 */  false,
  /*  427 */  false,
  /*  428 */  false,
  /*  429 */  false,
  /*  430 */  false,
  /*  431 */  false,
  /*  432 */  false,
  /*  433 */  false,
  /*  434 */  false,
  /*  435 */  false,
  /*  436 */  false,
  /*  437 */  false,
  /*  438 */  false,
  /*  439 */  false,
  /*  440 */  false,
  /*  441 */  false,
  /*  442 */  false,
  /*  443 */  false,
  /*  444 */  false,
  /*  445 */  false,
  /*  446 */  false,
  /*  447 */  false,
  /*  448 */  false,
  /*  449 */  false,
  /*  450 */  false,
  /*  451 */  false,
  /*  452 */  false,
  /*  453 */  false,
  /*  454 */  false,
  /*  455 */  false,
  /*  456 */  false,
  /*  457 */  false,
  /*  458 */  false,
  /*  459 */  false,
  /*  460 */  false,
  /*  461 */  false,
  /*  462 */  false,
  /*  463 */  false,
  /*  464 */  false,
  /*  465 */  false,
  /*  466 */  false,
  /*  467 */  false,
  /*  468 */  false,
  /*  469 */  false,
  /*  470 */  false,
  /*  471 */  false,
  /*  472 */  false,
  /*  473 */  false,
  /*  474 */  false,
  /*  475 */  false,
  /*  476 */  false,
  /*  477 */  false,
  /*  478 */  false,
  /*  479 */  false,
  /*  480 */  false,
  /*  481 */  false,
  /*  482 */  false,
  /*  483 */  false,
  /*  484 */  false,
  /*  485 */  false,
  /*  486 */  false,
  /*  487 */  false,
  /*  488 */  false,
  /*  489 */  false,
  /*  490 */  false,
  /*  491 */  false,
  /*  492 */  false,
  /*  493 */  false,
  /*  494 */  false,
  /*  495 */  false,
  /*  496 */  false,
  /*  497 */  false,
  /*  498 */  false,
  /*  499 */  false,
  /*  500 */  false,
  /*  501 */  false,
  /*  502 */  false,
  /*  503 */  false,
  /*  504 */  false,
  /*  505 */  false,
  /*  506 */  false,
  /*  507 */  false,
  /*  508 */  false,
  /*  509 */  false,
  /*  510 */  false,
  /*  511 */  false,
  /*  512 */  false,
  /*  513 */  false,
  /*  514 */  false,
  /*  515 */  false,
  /*  516 */  false,
  /*  517 */  false,
  /*  518 */  false,
  /*  519 */  false,
  /*  520 */  false,
  /*  521 */  false,
  /*  522 */  false,
  /*  523 */  false,
  /*  524 */  false,
  /*  525 */  false,
  /*  526 */  false,
  /*  527 */  false,
  /*  528 */  false,
  /*  529 */  false,
  /*  530 */  false,
  /*  531 */  false,
  /*  532 */  false,
  /*  533 */  false,
  /*  534 */  false,
  /*  535 */  false,
  /*  536 */  false,
  /*  537 */  false,
  /*  538 */  false,
  /*  539 */  false,
  /*  540 */  false,
  /*  541 */  false,
  /*  542 */  false,
  /*  543 */  false,
  /*  544 */  false,
  /*  545 */  false,
  /*  546 */  false,
  /*  547 */  false,
  /*  548 */  false,
  /*  549 */  false,
  /*  550 */  false,
  /*  551 */  false,
  /*  552 */  false,
  /*  553 */  false,
  /*  554 */  false,
  /*  555 */  false,
  /*  556 */  false,
  /*  557 */  false,
  /*  558 */  false,
  /*  559 */  false,
  /*  560 */  false,
  /*  561 */  false,
  /*  562 */  false,
  /*  563 */  false,
  /*  564 */  false,
  /*  565 */  false,
  /*  566 */  false,
  /*  567 */  false,
  /*  568 */  false,
  /*  569 */  false,
  /*  570 */  false,
  /*  571 */  false,
  /*  572 */  false,
  /*  573 */  false,
  /*  574 */  false,
  /*  575 */  false,
  /*  576 */  false,
  /*  577 */  false,
  /*  578 */  false,
  /*  579 */  false,
  /*  580 */  false,
  /*  581 */  false,
  /*  582 */  false,
  /*  583 */  false,
  /*  584 */  false,
  /*  585 */  false,
  /*  586 */  false,
  /*  587 */  false,
  /*  588 */  false,
  /*  589 */  false,
  /*  590 */  false,
  /*  591 */  false,
  /*  592 */  false,
  /*  593 */  false,
  /*  594 */  false,
  /*  595 */  false,
  /*  596 */  false,
  /*  597 */  false,
  /*  598 */  false,
  /*  599 */  false,
  /*  600 */  false,
  /*  601 */  false,
  /*  602 */  false,
  /*  603 */  false,
  /*  604 */  false,
  /*  605 */  false,
  /*  606 */  false,
  /*  607 */  false,
  /*  608 */  false,
  /*  609 */  false,
  /*  610 */  false,
  /*  611 */  false,
  /*  612 */  false,
  /*  613 */  false,
  /*  614 */  false,
  /*  615 */  false,
  /*  616 */  false,
  /*  617 */  false,
  /*  618 */  false,
  /*  619 */  false,
  /*  620 */  false,
  /*  621 */  false,
  /*  622 */  false,
  /*  623 */  false,
  /*  624 */  false,
  /*  625 */  false,
  /*  626 */  false,
  /*  627 */  false,
  /*  628 */  false,
  /*  629 */  false,
  /*  630 */  false,
  /*  631 */  false,
  /*  632 */  false,
  /*  633 */  false,
  /*  634 */  false,
  /*  635 */  false,
  /*  636 */  false,
  /*  637 */  false,
  /*  638 */  false,
  /*  639 */  false,
  /*  640 */  false,
  /*  641 */  false,
  /*  642 */  false,
  /*  643 */  false,
  /*  644 */  false,
  /*  645 */  false,
  /*  646 */  false,
  /*  647 */  false,
  /*  648 */  false,
  /*  649 */  false,
  /*  650 */  false,
  /*  651 */  false,
  /*  652 */  false,
  /*  653 */  false,
  /*  654 */  false,
  /*  655 */  false,
  /*  656 */  false,
  /*  657 */  false,
  /*  658 */  false,
  /*  659 */  false,
  /*  660 */  false,
  /*  661 */  false,
  /*  662 */  false,
  /*  663 */  false,
  /*  664 */  false,
  /*  665 */  false,
  /*  666 */  false,
  /*  667 */  false,
  /*  668 */  false,
  /*  669 */  false,
  /*  670 */  false,
  /*  671 */  false,
  /*  672 */  false,
  /*  673 */  false,
  /*  674 */  false,
  /*  675 */  false,
  /*  676 */  false,
  /*  677 */  false,
  /*  678 */  false,
  /*  679 */  false,
  /*  680 */  false,
  /*  681 */  false,
  /*  682 */  false,
  /*  683 */  false,
  /*  684 */  false,
  /*  685 */  false,
  /*  686 */  false,
  /*  687 */  false,
  /*  688 */  false,
  /*  689 */  false,
  /*  690 */  false,
  /*  691 */  false,
  /*  692 */  false,
  /*  693 */  false,
  /*  694 */  false,
  /*  695 */  false,
  /*  696 */  false,
  /*  697 */  false,
  /*  698 */  false,
  /*  699 */  false,
  /*  700 */  false,
  /*  701 */  false,
  /*  702 */  false,
  /*  703 */  false,
  /*  704 */  false,
  /*  705 */  false,
  /*  706 */  false,
  /*  707 */  false,
  /*  708 */  false,
  /*  709 */  false,
  /*  710 */  false,
  /*  711 */  false,
  /*  712 */  false,
  /*  713 */  false,
  /*  714 */  false,
  /*  715 */  false,
  /*  716 */  false,
  /*  717 */  false,
  /*  718 */  false,
  /*  719 */  false,
  /*  720 */  false,
  /*  721 */  false,
  /*  722 */  false,
  /*  723 */  false,
  /*  724 */  false,
  /*  725 */  false,
  /*  726 */  false,
  /*  727 */  false,
  /*  728 */  false,
  /*  729 */  false,
  /*  730 */  false,
  /*  731 */  false,
  /*  732 */  false,
  /*  733 */  false,
  /*  734 */  false,
  /*  735 */  false,
  /*  736 */  false,
  /*  737 */  false,
  /*  738 */  false,
  /*  739 */  false,
  /*  740 */  false,
  /*  741 */  false,
  /*  742 */  false,
  /*  743 */  false,
  /*  744 */  false,
  /*  745 */  false,
  /*  746 */  false,
  /*  747 */  false,
  /*  748 */  false,
  /*  749 */  false,
  /*  750 */  false,
  /*  751 */  false,
  /*  752 */  false,
  /*  753 */  false,
  /*  754 */  false,
  /*  755 */  false,
  /*  756 */  false,
  /*  757 */  false,
  /*  758 */  false,
  /*  759 */  false,
  /*  760 */  false,
  /*  761 */  false,
  /*  762 */  false,
  /*  763 */  false,
  /*  764 */  false,
  /*  765 */  false,
  /*  766 */  false,
  /*  767 */  false,
  /*  768 */  false,
  /*  769 */  false,
  /*  770 */  false,
  /*  771 */  false,
  /*  772 */  false,
  /*  773 */  false,
  /*  774 */  false,
  /*  775 */  false,
  /*  776 */  false,
  /*  777 */  false,
  /*  778 */  false,
  /*  779 */  false,
  /*  780 */  false,
  /*  781 */  false,
  /*  782 */  false,
  /*  783 */  false,
  /*  784 */  false,
  /*  785 */  false,
  /*  786 */  false,
  /*  787 */  false,
  /*  788 */  false,
  /*  789 */  false,
  /*  790 */  false,
  /*  791 */  false,
  /*  792 */  false,
  /*  793 */  false,
  /*  794 */  false,
  /*  795 */  false,
  /*  796 */  false,
  /*  797 */  false,
  // last instruction
  false // no trailing comma
};

// Mapping from machine-independent opcode to boolean
const        char must_clone[] = {
  0, // Node: 0
  0, // Set: 1
  0, // RegN: 2
  0, // RegI: 3
  0, // RegP: 4
  0, // RegF: 5
  0, // RegD: 6
  0, // RegL: 7
  0, // VecA: 8
  0, // VecS: 9
  0, // VecD: 10
  0, // VecX: 11
  0, // VecY: 12
  0, // VecZ: 13
  0, // RegVectMask: 14
  0, // RegFlags: 15
  0, // _last_machine_leaf: 16
  0, // AbsD: 17
  0, // AbsF: 18
  0, // AbsI: 19
  0, // AbsL: 20
  0, // AddD: 21
  0, // AddF: 22
  0, // AddI: 23
  0, // AddL: 24
  0, // AddP: 25
  0, // AddHF: 26
  0, // Allocate: 27
  0, // AllocateArray: 28
  0, // AndI: 29
  0, // AndL: 30
  0, // ArrayCopy: 31
  0, // AryEq: 32
  0, // AtanD: 33
  1, // Binary: 34
  0, // Blackhole: 35
  1, // Bool: 36
  0, // BoxLock: 37
  0, // ReverseBytesI: 38
  0, // ReverseBytesL: 39
  0, // ReverseBytesUS: 40
  0, // ReverseBytesS: 41
  0, // ReverseBytesV: 42
  0, // CProj: 43
  0, // CacheWB: 44
  0, // CacheWBPreSync: 45
  0, // CacheWBPostSync: 46
  0, // CallDynamicJava: 47
  0, // CallJava: 48
  0, // CallLeaf: 49
  0, // CallLeafNoFP: 50
  0, // CallLeafPure: 51
  0, // CallLeafVector: 52
  0, // CallRuntime: 53
  0, // CallStaticJava: 54
  0, // CastDD: 55
  0, // CastHH: 56
  0, // CastFF: 57
  0, // CastII: 58
  0, // CastLL: 59
  0, // CastVV: 60
  0, // CastX2P: 61
  0, // CastP2X: 62
  0, // CastPP: 63
  0, // Catch: 64
  0, // CatchProj: 65
  0, // CheckCastPP: 66
  0, // ClearArray: 67
  0, // CompressBits: 68
  0, // ExpandBits: 69
  0, // CompressBitsV: 70
  0, // ExpandBitsV: 71
  0, // ConstraintCast: 72
  0, // CMoveD: 73
  0, // CMoveF: 74
  0, // CMoveI: 75
  0, // CMoveL: 76
  0, // CMoveP: 77
  0, // CMoveN: 78
  1, // CmpN: 79
  1, // CmpD: 80
  0, // CmpD3: 81
  1, // CmpF: 82
  0, // CmpF3: 83
  1, // CmpI: 84
  1, // CmpL: 85
  0, // CmpL3: 86
  0, // CmpLTMask: 87
  1, // CmpP: 88
  1, // CmpU: 89
  0, // CmpU3: 90
  1, // CmpUL: 91
  0, // CmpUL3: 92
  0, // CompareAndSwapB: 93
  0, // CompareAndSwapS: 94
  0, // CompareAndSwapI: 95
  0, // CompareAndSwapL: 96
  0, // CompareAndSwapP: 97
  0, // CompareAndSwapN: 98
  0, // WeakCompareAndSwapB: 99
  0, // WeakCompareAndSwapS: 100
  0, // WeakCompareAndSwapI: 101
  0, // WeakCompareAndSwapL: 102
  0, // WeakCompareAndSwapP: 103
  0, // WeakCompareAndSwapN: 104
  0, // CompareAndExchangeB: 105
  0, // CompareAndExchangeS: 106
  0, // CompareAndExchangeI: 107
  0, // CompareAndExchangeL: 108
  0, // CompareAndExchangeP: 109
  0, // CompareAndExchangeN: 110
  0, // GetAndAddB: 111
  0, // GetAndAddS: 112
  0, // GetAndAddI: 113
  0, // GetAndAddL: 114
  0, // GetAndSetB: 115
  0, // GetAndSetS: 116
  0, // GetAndSetI: 117
  0, // GetAndSetL: 118
  0, // GetAndSetP: 119
  0, // GetAndSetN: 120
  0, // Con: 121
  0, // ConN: 122
  0, // ConNKlass: 123
  0, // ConD: 124
  0, // ConH: 125
  0, // ConF: 126
  0, // ConI: 127
  0, // ConL: 128
  0, // ConP: 129
  0, // Conv2B: 130
  0, // ConvD2F: 131
  0, // ConvD2I: 132
  0, // ConvD2L: 133
  0, // ConvF2D: 134
  0, // ConvF2I: 135
  0, // ConvF2L: 136
  0, // ConvI2D: 137
  0, // ConvI2F: 138
  0, // ConvI2L: 139
  0, // ConvL2D: 140
  0, // ConvL2F: 141
  0, // ConvL2I: 142
  0, // ConvF2HF: 143
  0, // ConvHF2F: 144
  0, // CountedLoop: 145
  0, // CountedLoopEnd: 146
  0, // OuterStripMinedLoop: 147
  0, // OuterStripMinedLoopEnd: 148
  0, // LongCountedLoop: 149
  0, // LongCountedLoopEnd: 150
  0, // CountLeadingZerosI: 151
  0, // CountLeadingZerosL: 152
  0, // CountLeadingZerosV: 153
  0, // CountTrailingZerosI: 154
  0, // CountTrailingZerosL: 155
  0, // CountTrailingZerosV: 156
  0, // CreateEx: 157
  0, // DecodeN: 158
  0, // DecodeNKlass: 159
  0, // DivHF: 160
  0, // DivD: 161
  0, // DivF: 162
  0, // DivI: 163
  0, // DivL: 164
  0, // UDivI: 165
  0, // UDivL: 166
  0, // DivMod: 167
  0, // DivModI: 168
  0, // DivModL: 169
  0, // UDivModI: 170
  0, // UDivModL: 171
  0, // EncodeISOArray: 172
  0, // EncodeP: 173
  0, // EncodePKlass: 174
  1, // FastLock: 175
  1, // FastUnlock: 176
  0, // FmaD: 177
  0, // FmaF: 178
  0, // FmaHF: 179
  0, // ForwardException: 180
  0, // Goto: 181
  0, // Halt: 182
  0, // CountPositives: 183
  0, // If: 184
  0, // RangeCheck: 185
  0, // IfFalse: 186
  0, // IfTrue: 187
  0, // Initialize: 188
  0, // JProj: 189
  0, // Jump: 190
  0, // JumpProj: 191
  0, // LShiftI: 192
  0, // LShiftL: 193
  0, // LoadB: 194
  0, // LoadUB: 195
  0, // LoadUS: 196
  0, // LoadD: 197
  0, // LoadD_unaligned: 198
  0, // LoadF: 199
  0, // LoadI: 200
  0, // LoadKlass: 201
  0, // LoadNKlass: 202
  0, // LoadL: 203
  0, // LoadL_unaligned: 204
  0, // LoadP: 205
  0, // LoadN: 206
  0, // LoadRange: 207
  0, // LoadS: 208
  0, // Lock: 209
  0, // Loop: 210
  0, // LoopLimit: 211
  0, // Mach: 212
  0, // MachNullCheck: 213
  0, // MachProj: 214
  0, // MulAddS2I: 215
  0, // MaxI: 216
  0, // MaxL: 217
  0, // MaxHF: 218
  0, // MaxD: 219
  0, // MaxF: 220
  0, // MemBarAcquire: 221
  0, // LoadFence: 222
  0, // MemBarAcquireLock: 223
  0, // MemBarCPUOrder: 224
  0, // MemBarRelease: 225
  0, // StoreFence: 226
  0, // StoreStoreFence: 227
  0, // MemBarReleaseLock: 228
  0, // MemBarStoreLoad: 229
  0, // MemBarVolatile: 230
  0, // MemBarStoreStore: 231
  0, // MemBarFull: 232
  0, // MergeMem: 233
  0, // MinI: 234
  0, // MinL: 235
  0, // MinHF: 236
  0, // MinF: 237
  0, // MinD: 238
  0, // ModD: 239
  0, // ModF: 240
  0, // ModI: 241
  0, // ModL: 242
  0, // UModI: 243
  0, // UModL: 244
  0, // MoveI2F: 245
  0, // MoveF2I: 246
  0, // MoveL2D: 247
  0, // MoveD2L: 248
  0, // IsInfiniteF: 249
  0, // IsFiniteF: 250
  0, // IsInfiniteD: 251
  0, // IsFiniteD: 252
  0, // MulHF: 253
  0, // MulD: 254
  0, // MulF: 255
  0, // MulHiL: 256
  0, // UMulHiL: 257
  0, // MulI: 258
  0, // MulL: 259
  0, // Multi: 260
  0, // NegI: 261
  0, // NegL: 262
  0, // NegD: 263
  0, // NegF: 264
  0, // NeverBranch: 265
  0, // NarrowMemProj: 266
  0, // OnSpinWait: 267
  0, // Opaque1: 268
  0, // OpaqueLoopInit: 269
  0, // OpaqueLoopStride: 270
  0, // OpaqueMultiversioning: 271
  0, // OpaqueZeroTripGuard: 272
  0, // OpaqueConstantBool: 273
  0, // OpaqueInitializedAssertionPredicate: 274
  0, // OpaqueTemplateAssertionPredicate: 275
  0, // PowD: 276
  0, // ProfileBoolean: 277
  0, // OrI: 278
  0, // OrL: 279
  1, // OverflowAddI: 280
  1, // OverflowSubI: 281
  1, // OverflowMulI: 282
  1, // OverflowAddL: 283
  1, // OverflowSubL: 284
  1, // OverflowMulL: 285
  0, // PCTable: 286
  0, // Parm: 287
  0, // ParsePredicate: 288
  0, // PartialSubtypeCheck: 289
  0, // SubTypeCheck: 290
  0, // Phi: 291
  0, // PopCountI: 292
  0, // PopCountL: 293
  0, // PopCountVI: 294
  0, // PopCountVL: 295
  0, // PopulateIndex: 296
  0, // PrefetchAllocation: 297
  0, // Proj: 298
  0, // RShiftI: 299
  0, // RShiftL: 300
  0, // Region: 301
  0, // Rethrow: 302
  0, // Return: 303
  0, // ReverseI: 304
  0, // ReverseL: 305
  0, // ReverseV: 306
  0, // Root: 307
  0, // RoundDoubleMode: 308
  0, // RoundDoubleModeV: 309
  0, // RotateLeft: 310
  0, // RotateLeftV: 311
  0, // RotateRight: 312
  0, // RotateRightV: 313
  0, // SafePoint: 314
  0, // SafePointScalarObject: 315
  0, // SafePointScalarMerge: 316
  0, // ShenandoahCompareAndExchangeP: 317
  0, // ShenandoahCompareAndExchangeN: 318
  0, // ShenandoahCompareAndSwapN: 319
  0, // ShenandoahCompareAndSwapP: 320
  0, // ShenandoahWeakCompareAndSwapN: 321
  0, // ShenandoahWeakCompareAndSwapP: 322
  0, // ShenandoahLoadReferenceBarrier: 323
  0, // SCMemProj: 324
  0, // CopySignD: 325
  0, // CopySignF: 326
  0, // SaturatingAddV: 327
  0, // SaturatingSubV: 328
  0, // SignumD: 329
  0, // SignumF: 330
  0, // SignumVF: 331
  0, // SignumVD: 332
  0, // SqrtD: 333
  0, // SqrtF: 334
  0, // SqrtHF: 335
  0, // RoundF: 336
  0, // RoundD: 337
  0, // Start: 338
  0, // StartOSR: 339
  0, // StoreB: 340
  0, // StoreC: 341
  0, // StoreD: 342
  0, // StoreF: 343
  0, // StoreI: 344
  0, // StoreL: 345
  0, // StoreP: 346
  0, // StoreN: 347
  0, // StoreNKlass: 348
  0, // StrComp: 349
  0, // StrCompressedCopy: 350
  0, // StrEquals: 351
  0, // StrIndexOf: 352
  0, // StrIndexOfChar: 353
  0, // StrInflatedCopy: 354
  0, // SubHF: 355
  0, // SubD: 356
  0, // SubF: 357
  0, // SubI: 358
  0, // SubL: 359
  0, // TailCall: 360
  0, // TailJump: 361
  0, // Tuple: 362
  0, // MacroLogicV: 363
  0, // ThreadLocal: 364
  0, // Unlock: 365
  0, // URShiftB: 366
  0, // URShiftS: 367
  0, // URShiftI: 368
  0, // URShiftL: 369
  0, // XorI: 370
  0, // XorL: 371
  0, // Vector: 372
  0, // AddVB: 373
  0, // AddVS: 374
  0, // AddVI: 375
  0, // AddReductionVI: 376
  0, // AddVL: 377
  0, // AddReductionVL: 378
  0, // AddVF: 379
  0, // AddVHF: 380
  0, // AddReductionVF: 381
  0, // AddVD: 382
  0, // AddReductionVD: 383
  0, // SubVB: 384
  0, // SubVS: 385
  0, // SubVI: 386
  0, // SubVL: 387
  0, // SubVF: 388
  0, // SubVHF: 389
  0, // SubVD: 390
  0, // MulVB: 391
  0, // MulVS: 392
  0, // MulVI: 393
  0, // MulReductionVI: 394
  0, // MulVL: 395
  0, // MulReductionVL: 396
  0, // MulVF: 397
  0, // MulReductionVF: 398
  0, // MulVD: 399
  0, // MulReductionVD: 400
  0, // MulVHF: 401
  0, // MulAddVS2VI: 402
  0, // FmaVD: 403
  0, // FmaVF: 404
  0, // FmaVHF: 405
  0, // DivVHF: 406
  0, // DivVF: 407
  0, // DivVD: 408
  0, // AbsVB: 409
  0, // AbsVS: 410
  0, // AbsVI: 411
  0, // AbsVL: 412
  0, // AbsVF: 413
  0, // AbsVD: 414
  0, // NegVI: 415
  0, // NegVL: 416
  0, // NegVF: 417
  0, // NegVD: 418
  0, // SqrtVD: 419
  0, // SqrtVF: 420
  0, // SqrtVHF: 421
  0, // LShiftCntV: 422
  0, // RShiftCntV: 423
  0, // LShiftVB: 424
  0, // LShiftVS: 425
  0, // LShiftVI: 426
  0, // LShiftVL: 427
  0, // RShiftVB: 428
  0, // RShiftVS: 429
  0, // RShiftVI: 430
  0, // RShiftVL: 431
  0, // URShiftVB: 432
  0, // URShiftVS: 433
  0, // URShiftVI: 434
  0, // URShiftVL: 435
  0, // AndV: 436
  0, // AndReductionV: 437
  0, // OrV: 438
  0, // OrReductionV: 439
  0, // XorV: 440
  0, // XorReductionV: 441
  0, // MinV: 442
  0, // MaxV: 443
  0, // MinVHF: 444
  0, // MaxVHF: 445
  0, // UMinV: 446
  0, // UMaxV: 447
  0, // MinReductionV: 448
  0, // MaxReductionV: 449
  0, // UMinReductionV: 450
  0, // UMaxReductionV: 451
  0, // CompressV: 452
  0, // CompressM: 453
  0, // ExpandV: 454
  0, // LoadVector: 455
  0, // LoadVectorGather: 456
  0, // LoadVectorGatherMasked: 457
  0, // StoreVector: 458
  0, // StoreVectorScatter: 459
  0, // StoreVectorScatterMasked: 460
  0, // LoadVectorMasked: 461
  0, // StoreVectorMasked: 462
  0, // VerifyVectorAlignment: 463
  0, // VectorCmpMasked: 464
  0, // VectorMaskGen: 465
  0, // VectorMaskOp: 466
  0, // VectorMaskTrueCount: 467
  0, // VectorMaskFirstTrue: 468
  0, // VectorMaskLastTrue: 469
  0, // VectorMaskToLong: 470
  0, // VectorLongToMask: 471
  0, // Pack: 472
  0, // PackB: 473
  0, // PackS: 474
  0, // PackI: 475
  0, // PackL: 476
  0, // PackF: 477
  0, // PackD: 478
  0, // Pack2L: 479
  0, // Pack2D: 480
  0, // Replicate: 481
  0, // RoundVF: 482
  0, // RoundVD: 483
  0, // Extract: 484
  0, // ExtractB: 485
  0, // ExtractUB: 486
  0, // ExtractC: 487
  0, // ExtractS: 488
  0, // ExtractI: 489
  0, // ExtractL: 490
  0, // ExtractF: 491
  0, // ExtractD: 492
  0, // Digit: 493
  0, // LowerCase: 494
  0, // ReinterpretS2HF: 495
  0, // ReinterpretHF2S: 496
  0, // UpperCase: 497
  0, // Whitespace: 498
  0, // SelectFromTwoVector: 499
  0, // VectorBox: 500
  0, // VectorBoxAllocate: 501
  0, // VectorUnbox: 502
  0, // VectorMaskWrapper: 503
  0, // VectorMaskCmp: 504
  0, // VectorMaskCast: 505
  1, // VectorTest: 506
  0, // VectorBlend: 507
  0, // VectorRearrange: 508
  0, // VectorLoadMask: 509
  0, // VectorLoadShuffle: 510
  0, // VectorLoadConst: 511
  0, // VectorStoreMask: 512
  0, // VectorReinterpret: 513
  0, // VectorCast: 514
  0, // VectorCastB2X: 515
  0, // VectorCastS2X: 516
  0, // VectorCastI2X: 517
  0, // VectorCastL2X: 518
  0, // VectorCastF2X: 519
  0, // VectorCastD2X: 520
  0, // VectorCastF2HF: 521
  0, // VectorCastHF2F: 522
  0, // VectorUCastB2X: 523
  0, // VectorUCastS2X: 524
  0, // VectorUCastI2X: 525
  0, // VectorizedHashCode: 526
  0, // VectorInsert: 527
  0, // MaskAll: 528
  0, // AndVMask: 529
  0, // OrVMask: 530
  0 // no trailing comma // XorVMask: 531
};
//  The following instructions can cisc-spill
//  addI_reg_reg_CISC can cisc-spill operand 2 to addI_Reg_mem
//  addL_reg_regI can cisc-spill operand 2 to addL_Reg_memI
//  addL_reg_regI_0 can cisc-spill operand 1 to addL_Reg_memI_0
//  addL_reg_reg_CISC can cisc-spill operand 2 to addL_Reg_mem
//  subI_reg_reg_CISC can cisc-spill operand 2 to subI_Reg_mem
//  subL_reg_reg_CISC can cisc-spill operand 2 to subL_Reg_mem
//  subL_reg_regI_CISC can cisc-spill operand 2 to subL_Reg_memI
//  mulI_reg_reg can cisc-spill operand 2 to mulI_Reg_mem
//  mulL_reg_regI can cisc-spill operand 2 to mulL_Reg_memI
//  mulL_reg_regI_0 can cisc-spill operand 1 to mulL_Reg_memI_0
//  mulL_reg_reg can cisc-spill operand 2 to mulL_Reg_mem
//  addF_reg_reg can cisc-spill operand 2 to addF_reg_mem
//  addD_reg_reg can cisc-spill operand 2 to addD_reg_mem
//  subF_reg_reg can cisc-spill operand 2 to subF_reg_mem
//  subD_reg_reg can cisc-spill operand 2 to subD_reg_mem
//  mulF_reg_reg can cisc-spill operand 2 to mulF_reg_mem
//  mulD_reg_reg can cisc-spill operand 2 to mulD_reg_mem
//  maddF_reg_reg can cisc-spill operand 3 to maddF_reg_mem
//  maddD_reg_reg can cisc-spill operand 3 to maddD_reg_mem
//  msubF_reg_reg can cisc-spill operand 3 to msubF_reg_mem
//  msubD_reg_reg can cisc-spill operand 3 to msubD_reg_mem
//  divF_reg_reg can cisc-spill operand 2 to divF_reg_mem
//  divD_reg_reg can cisc-spill operand 2 to divD_reg_mem
//  sqrtF_reg can cisc-spill operand 1 to sqrtF_mem
//  sqrtD_reg can cisc-spill operand 1 to sqrtD_mem
//  andI_reg_reg can cisc-spill operand 2 to andI_Reg_mem
//  andL_reg_reg can cisc-spill operand 2 to andL_Reg_mem
//  orI_reg_reg can cisc-spill operand 2 to orI_Reg_mem
//  orL_reg_reg can cisc-spill operand 2 to orL_Reg_mem
//  xorI_reg_reg can cisc-spill operand 2 to xorI_Reg_mem
//  xorL_reg_reg can cisc-spill operand 2 to xorL_Reg_mem
//  convF2D_reg can cisc-spill operand 1 to convF2D_mem
//  convI2L_reg can cisc-spill operand 1 to loadI2L
//  convI2L_reg_zex can cisc-spill operand 1 to convI2L_mem_zex
//  compI_reg_reg can cisc-spill operand 2 to compI_reg_mem
//  compU_reg_reg can cisc-spill operand 2 to compU_reg_mem
//  compL_reg_reg can cisc-spill operand 2 to compL_reg_mem
//  compL_reg_regI can cisc-spill operand 2 to compL_reg_memI
//  cmpF_cc can cisc-spill operand 2 to cmpF_cc_mem
//  cmpD_cc can cisc-spill operand 2 to cmpD_cc_mem



// An array of character pointers to machine register names.
const char *Matcher::regName[REG_COUNT] = {
  "Z_R13",
  "Z_R13_H",
  "Z_R12",
  "Z_R12_H",
  "Z_R11",
  "Z_R11_H",
  "Z_R10",
  "Z_R10_H",
  "Z_R9",
  "Z_R9_H",
  "Z_R8",
  "Z_R8_H",
  "Z_R7",
  "Z_R7_H",
  "Z_R1",
  "Z_R1_H",
  "Z_R0",
  "Z_R0_H",
  "Z_R6",
  "Z_R6_H",
  "Z_R5",
  "Z_R5_H",
  "Z_R4",
  "Z_R4_H",
  "Z_R3",
  "Z_R3_H",
  "Z_R2",
  "Z_R2_H",
  "Z_R14",
  "Z_R14_H",
  "Z_R15",
  "Z_R15_H",
  "Z_F15",
  "Z_F15_H",
  "Z_F14",
  "Z_F14_H",
  "Z_F13",
  "Z_F13_H",
  "Z_F12",
  "Z_F12_H",
  "Z_F11",
  "Z_F11_H",
  "Z_F10",
  "Z_F10_H",
  "Z_F9",
  "Z_F9_H",
  "Z_F8",
  "Z_F8_H",
  "Z_F7",
  "Z_F7_H",
  "Z_F5",
  "Z_F5_H",
  "Z_F3",
  "Z_F3_H",
  "Z_F1",
  "Z_F1_H",
  "Z_F6",
  "Z_F6_H",
  "Z_F4",
  "Z_F4_H",
  "Z_F2",
  "Z_F2_H",
  "Z_F0",
  "Z_F0_H",
  "Z_VR0",
  "Z_VR0_H",
  "Z_VR0_J",
  "Z_VR0_K",
  "Z_VR1",
  "Z_VR1_H",
  "Z_VR1_J",
  "Z_VR1_K",
  "Z_VR2",
  "Z_VR2_H",
  "Z_VR2_J",
  "Z_VR2_K",
  "Z_VR3",
  "Z_VR3_H",
  "Z_VR3_J",
  "Z_VR3_K",
  "Z_VR4",
  "Z_VR4_H",
  "Z_VR4_J",
  "Z_VR4_K",
  "Z_VR5",
  "Z_VR5_H",
  "Z_VR5_J",
  "Z_VR5_K",
  "Z_VR6",
  "Z_VR6_H",
  "Z_VR6_J",
  "Z_VR6_K",
  "Z_VR7",
  "Z_VR7_H",
  "Z_VR7_J",
  "Z_VR7_K",
  "Z_VR8",
  "Z_VR8_H",
  "Z_VR8_J",
  "Z_VR8_K",
  "Z_VR9",
  "Z_VR9_H",
  "Z_VR9_J",
  "Z_VR9_K",
  "Z_VR10",
  "Z_VR10_H",
  "Z_VR10_J",
  "Z_VR10_K",
  "Z_VR11",
  "Z_VR11_H",
  "Z_VR11_J",
  "Z_VR11_K",
  "Z_VR12",
  "Z_VR12_H",
  "Z_VR12_J",
  "Z_VR12_K",
  "Z_VR13",
  "Z_VR13_H",
  "Z_VR13_J",
  "Z_VR13_K",
  "Z_VR14",
  "Z_VR14_H",
  "Z_VR14_J",
  "Z_VR14_K",
  "Z_VR15",
  "Z_VR15_H",
  "Z_VR15_J",
  "Z_VR15_K",
  "Z_VR16",
  "Z_VR16_H",
  "Z_VR16_J",
  "Z_VR16_K",
  "Z_VR17",
  "Z_VR17_H",
  "Z_VR17_J",
  "Z_VR17_K",
  "Z_VR18",
  "Z_VR18_H",
  "Z_VR18_J",
  "Z_VR18_K",
  "Z_VR19",
  "Z_VR19_H",
  "Z_VR19_J",
  "Z_VR19_K",
  "Z_VR20",
  "Z_VR20_H",
  "Z_VR20_J",
  "Z_VR20_K",
  "Z_VR21",
  "Z_VR21_H",
  "Z_VR21_J",
  "Z_VR21_K",
  "Z_VR22",
  "Z_VR22_H",
  "Z_VR22_J",
  "Z_VR22_K",
  "Z_VR23",
  "Z_VR23_H",
  "Z_VR23_J",
  "Z_VR23_K",
  "Z_VR24",
  "Z_VR24_H",
  "Z_VR24_J",
  "Z_VR24_K",
  "Z_VR25",
  "Z_VR25_H",
  "Z_VR25_J",
  "Z_VR25_K",
  "Z_VR26",
  "Z_VR26_H",
  "Z_VR26_J",
  "Z_VR26_K",
  "Z_VR27",
  "Z_VR27_H",
  "Z_VR27_J",
  "Z_VR27_K",
  "Z_VR28",
  "Z_VR28_H",
  "Z_VR28_J",
  "Z_VR28_K",
  "Z_VR29",
  "Z_VR29_H",
  "Z_VR29_J",
  "Z_VR29_K",
  "Z_VR30",
  "Z_VR30_H",
  "Z_VR30_J",
  "Z_VR30_K",
  "Z_VR31",
  "Z_VR31_H",
  "Z_VR31_J",
  "Z_VR31_K",
  "Z_CR" // no trailing comma
};

// An array of character pointers to machine register names.
const VMReg OptoReg::opto2vm[REG_COUNT] = {
	Z_R13->as_VMReg(),
	Z_R13->as_VMReg()->next(),
	Z_R12->as_VMReg(),
	Z_R12->as_VMReg()->next(),
	Z_R11->as_VMReg(),
	Z_R11->as_VMReg()->next(),
	Z_R10->as_VMReg(),
	Z_R10->as_VMReg()->next(),
	Z_R9->as_VMReg(),
	Z_R9->as_VMReg()->next(),
	Z_R8->as_VMReg(),
	Z_R8->as_VMReg()->next(),
	Z_R7->as_VMReg(),
	Z_R7->as_VMReg()->next(),
	Z_R1->as_VMReg(),
	Z_R1->as_VMReg()->next(),
	Z_R0->as_VMReg(),
	Z_R0->as_VMReg()->next(),
	Z_R6->as_VMReg(),
	Z_R6->as_VMReg()->next(),
	Z_R5->as_VMReg(),
	Z_R5->as_VMReg()->next(),
	Z_R4->as_VMReg(),
	Z_R4->as_VMReg()->next(),
	Z_R3->as_VMReg(),
	Z_R3->as_VMReg()->next(),
	Z_R2->as_VMReg(),
	Z_R2->as_VMReg()->next(),
	Z_R14->as_VMReg(),
	Z_R14->as_VMReg()->next(),
	Z_R15->as_VMReg(),
	Z_R15->as_VMReg()->next(),
	Z_F15->as_VMReg(),
	Z_F15->as_VMReg()->next(),
	Z_F14->as_VMReg(),
	Z_F14->as_VMReg()->next(),
	Z_F13->as_VMReg(),
	Z_F13->as_VMReg()->next(),
	Z_F12->as_VMReg(),
	Z_F12->as_VMReg()->next(),
	Z_F11->as_VMReg(),
	Z_F11->as_VMReg()->next(),
	Z_F10->as_VMReg(),
	Z_F10->as_VMReg()->next(),
	Z_F9->as_VMReg(),
	Z_F9->as_VMReg()->next(),
	Z_F8->as_VMReg(),
	Z_F8->as_VMReg()->next(),
	Z_F7->as_VMReg(),
	Z_F7->as_VMReg()->next(),
	Z_F5->as_VMReg(),
	Z_F5->as_VMReg()->next(),
	Z_F3->as_VMReg(),
	Z_F3->as_VMReg()->next(),
	Z_F1->as_VMReg(),
	Z_F1->as_VMReg()->next(),
	Z_F6->as_VMReg(),
	Z_F6->as_VMReg()->next(),
	Z_F4->as_VMReg(),
	Z_F4->as_VMReg()->next(),
	Z_F2->as_VMReg(),
	Z_F2->as_VMReg()->next(),
	Z_F0->as_VMReg(),
	Z_F0->as_VMReg()->next(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	VMRegImpl::Bad(),
	Z_V16->as_VMReg()          ,
	Z_V16->as_VMReg()->next()  ,
	Z_V16->as_VMReg()->next(2) ,
	Z_V16->as_VMReg()->next(3) ,
	Z_V17->as_VMReg()          ,
	Z_V17->as_VMReg()->next()  ,
	Z_V17->as_VMReg()->next(2) ,
	Z_V17->as_VMReg()->next(3) ,
	Z_V18->as_VMReg()          ,
	Z_V18->as_VMReg()->next()  ,
	Z_V18->as_VMReg()->next(2) ,
	Z_V18->as_VMReg()->next(3) ,
	Z_V19->as_VMReg()          ,
	Z_V19->as_VMReg()->next()  ,
	Z_V19->as_VMReg()->next(2) ,
	Z_V19->as_VMReg()->next(3) ,
	Z_V20->as_VMReg()          ,
	Z_V20->as_VMReg()->next()  ,
	Z_V20->as_VMReg()->next(2) ,
	Z_V20->as_VMReg()->next(3) ,
	Z_V21->as_VMReg()          ,
	Z_V21->as_VMReg()->next()  ,
	Z_V21->as_VMReg()->next(2) ,
	Z_V21->as_VMReg()->next(3) ,
	Z_V22->as_VMReg()          ,
	Z_V22->as_VMReg()->next()  ,
	Z_V22->as_VMReg()->next(2) ,
	Z_V22->as_VMReg()->next(3) ,
	Z_V23->as_VMReg()          ,
	Z_V23->as_VMReg()->next()  ,
	Z_V23->as_VMReg()->next(2) ,
	Z_V23->as_VMReg()->next(3) ,
	Z_V24->as_VMReg()          ,
	Z_V24->as_VMReg()->next()  ,
	Z_V24->as_VMReg()->next(2) ,
	Z_V24->as_VMReg()->next(3) ,
	Z_V25->as_VMReg()          ,
	Z_V25->as_VMReg()->next()  ,
	Z_V25->as_VMReg()->next(2) ,
	Z_V25->as_VMReg()->next(3) ,
	Z_V26->as_VMReg()          ,
	Z_V26->as_VMReg()->next()  ,
	Z_V26->as_VMReg()->next(2) ,
	Z_V26->as_VMReg()->next(3) ,
	Z_V27->as_VMReg()          ,
	Z_V27->as_VMReg()->next()  ,
	Z_V27->as_VMReg()->next(2) ,
	Z_V27->as_VMReg()->next(3) ,
	Z_V28->as_VMReg()          ,
	Z_V28->as_VMReg()->next()  ,
	Z_V28->as_VMReg()->next(2) ,
	Z_V28->as_VMReg()->next(3) ,
	Z_V29->as_VMReg()          ,
	Z_V29->as_VMReg()->next()  ,
	Z_V29->as_VMReg()->next(2) ,
	Z_V29->as_VMReg()->next(3) ,
	Z_V30->as_VMReg()          ,
	Z_V30->as_VMReg()->next()  ,
	Z_V30->as_VMReg()->next(2) ,
	Z_V30->as_VMReg()->next(3) ,
	Z_V31->as_VMReg()          ,
	Z_V31->as_VMReg()->next()  ,
	Z_V31->as_VMReg()->next(2) ,
	Z_V31->as_VMReg()->next(3) ,
	Z_CR->as_VMReg() // no trailing comma
	};

 OptoReg::Name OptoReg::vm2opto[ConcreteRegisterImpl::number_of_registers];

// An array of the machine register encode values
const unsigned char Matcher::_regEncode[REG_COUNT] = {
  (unsigned char)'\xD',  // Z_R13
  (unsigned char)'\x63',  // Z_R13_H
  (unsigned char)'\xC',  // Z_R12
  (unsigned char)'\x63',  // Z_R12_H
  (unsigned char)'\xB',  // Z_R11
  (unsigned char)'\x63',  // Z_R11_H
  (unsigned char)'\xA',  // Z_R10
  (unsigned char)'\x63',  // Z_R10_H
  (unsigned char)'\x9',  // Z_R9
  (unsigned char)'\x63',  // Z_R9_H
  (unsigned char)'\x8',  // Z_R8
  (unsigned char)'\x63',  // Z_R8_H
  (unsigned char)'\x7',  // Z_R7
  (unsigned char)'\x63',  // Z_R7_H
  (unsigned char)'\x1',  // Z_R1
  (unsigned char)'\x63',  // Z_R1_H
  (unsigned char)'\x0',  // Z_R0
  (unsigned char)'\x63',  // Z_R0_H
  (unsigned char)'\x6',  // Z_R6
  (unsigned char)'\x63',  // Z_R6_H
  (unsigned char)'\x5',  // Z_R5
  (unsigned char)'\x63',  // Z_R5_H
  (unsigned char)'\x4',  // Z_R4
  (unsigned char)'\x63',  // Z_R4_H
  (unsigned char)'\x3',  // Z_R3
  (unsigned char)'\x63',  // Z_R3_H
  (unsigned char)'\x2',  // Z_R2
  (unsigned char)'\x63',  // Z_R2_H
  (unsigned char)'\xE',  // Z_R14
  (unsigned char)'\x63',  // Z_R14_H
  (unsigned char)'\xF',  // Z_R15
  (unsigned char)'\x63',  // Z_R15_H
  (unsigned char)'\xF',  // Z_F15
  (unsigned char)'\x63',  // Z_F15_H
  (unsigned char)'\xE',  // Z_F14
  (unsigned char)'\x63',  // Z_F14_H
  (unsigned char)'\xD',  // Z_F13
  (unsigned char)'\x63',  // Z_F13_H
  (unsigned char)'\xC',  // Z_F12
  (unsigned char)'\x63',  // Z_F12_H
  (unsigned char)'\xB',  // Z_F11
  (unsigned char)'\x63',  // Z_F11_H
  (unsigned char)'\xA',  // Z_F10
  (unsigned char)'\x63',  // Z_F10_H
  (unsigned char)'\x9',  // Z_F9
  (unsigned char)'\x63',  // Z_F9_H
  (unsigned char)'\x8',  // Z_F8
  (unsigned char)'\x63',  // Z_F8_H
  (unsigned char)'\x7',  // Z_F7
  (unsigned char)'\x63',  // Z_F7_H
  (unsigned char)'\x5',  // Z_F5
  (unsigned char)'\x63',  // Z_F5_H
  (unsigned char)'\x3',  // Z_F3
  (unsigned char)'\x63',  // Z_F3_H
  (unsigned char)'\x1',  // Z_F1
  (unsigned char)'\x63',  // Z_F1_H
  (unsigned char)'\x6',  // Z_F6
  (unsigned char)'\x63',  // Z_F6_H
  (unsigned char)'\x4',  // Z_F4
  (unsigned char)'\x63',  // Z_F4_H
  (unsigned char)'\x2',  // Z_F2
  (unsigned char)'\x63',  // Z_F2_H
  (unsigned char)'\x0',  // Z_F0
  (unsigned char)'\x63',  // Z_F0_H
  (unsigned char)'\x0',  // Z_VR0
  (unsigned char)'\x0',  // Z_VR0_H
  (unsigned char)'\x0',  // Z_VR0_J
  (unsigned char)'\x0',  // Z_VR0_K
  (unsigned char)'\x1',  // Z_VR1
  (unsigned char)'\x1',  // Z_VR1_H
  (unsigned char)'\x1',  // Z_VR1_J
  (unsigned char)'\x1',  // Z_VR1_K
  (unsigned char)'\x2',  // Z_VR2
  (unsigned char)'\x2',  // Z_VR2_H
  (unsigned char)'\x2',  // Z_VR2_J
  (unsigned char)'\x2',  // Z_VR2_K
  (unsigned char)'\x3',  // Z_VR3
  (unsigned char)'\x3',  // Z_VR3_H
  (unsigned char)'\x3',  // Z_VR3_J
  (unsigned char)'\x3',  // Z_VR3_K
  (unsigned char)'\x4',  // Z_VR4
  (unsigned char)'\x4',  // Z_VR4_H
  (unsigned char)'\x4',  // Z_VR4_J
  (unsigned char)'\x4',  // Z_VR4_K
  (unsigned char)'\x5',  // Z_VR5
  (unsigned char)'\x5',  // Z_VR5_H
  (unsigned char)'\x5',  // Z_VR5_J
  (unsigned char)'\x5',  // Z_VR5_K
  (unsigned char)'\x6',  // Z_VR6
  (unsigned char)'\x6',  // Z_VR6_H
  (unsigned char)'\x6',  // Z_VR6_J
  (unsigned char)'\x6',  // Z_VR6_K
  (unsigned char)'\x7',  // Z_VR7
  (unsigned char)'\x7',  // Z_VR7_H
  (unsigned char)'\x7',  // Z_VR7_J
  (unsigned char)'\x7',  // Z_VR7_K
  (unsigned char)'\x8',  // Z_VR8
  (unsigned char)'\x8',  // Z_VR8_H
  (unsigned char)'\x8',  // Z_VR8_J
  (unsigned char)'\x8',  // Z_VR8_K
  (unsigned char)'\x9',  // Z_VR9
  (unsigned char)'\x9',  // Z_VR9_H
  (unsigned char)'\x9',  // Z_VR9_J
  (unsigned char)'\x9',  // Z_VR9_K
  (unsigned char)'\xA',  // Z_VR10
  (unsigned char)'\xA',  // Z_VR10_H
  (unsigned char)'\xA',  // Z_VR10_J
  (unsigned char)'\xA',  // Z_VR10_K
  (unsigned char)'\xB',  // Z_VR11
  (unsigned char)'\xB',  // Z_VR11_H
  (unsigned char)'\xB',  // Z_VR11_J
  (unsigned char)'\xB',  // Z_VR11_K
  (unsigned char)'\xC',  // Z_VR12
  (unsigned char)'\xC',  // Z_VR12_H
  (unsigned char)'\xC',  // Z_VR12_J
  (unsigned char)'\xC',  // Z_VR12_K
  (unsigned char)'\xD',  // Z_VR13
  (unsigned char)'\xD',  // Z_VR13_H
  (unsigned char)'\xD',  // Z_VR13_J
  (unsigned char)'\xD',  // Z_VR13_K
  (unsigned char)'\xE',  // Z_VR14
  (unsigned char)'\xE',  // Z_VR14_H
  (unsigned char)'\xE',  // Z_VR14_J
  (unsigned char)'\xE',  // Z_VR14_K
  (unsigned char)'\xF',  // Z_VR15
  (unsigned char)'\xF',  // Z_VR15_H
  (unsigned char)'\xF',  // Z_VR15_J
  (unsigned char)'\xF',  // Z_VR15_K
  (unsigned char)'\x10',  // Z_VR16
  (unsigned char)'\x10',  // Z_VR16_H
  (unsigned char)'\x10',  // Z_VR16_J
  (unsigned char)'\x10',  // Z_VR16_K
  (unsigned char)'\x11',  // Z_VR17
  (unsigned char)'\x11',  // Z_VR17_H
  (unsigned char)'\x11',  // Z_VR17_J
  (unsigned char)'\x11',  // Z_VR17_K
  (unsigned char)'\x12',  // Z_VR18
  (unsigned char)'\x12',  // Z_VR18_H
  (unsigned char)'\x12',  // Z_VR18_J
  (unsigned char)'\x12',  // Z_VR18_K
  (unsigned char)'\x13',  // Z_VR19
  (unsigned char)'\x13',  // Z_VR19_H
  (unsigned char)'\x13',  // Z_VR19_J
  (unsigned char)'\x13',  // Z_VR19_K
  (unsigned char)'\x14',  // Z_VR20
  (unsigned char)'\x14',  // Z_VR20_H
  (unsigned char)'\x14',  // Z_VR20_J
  (unsigned char)'\x14',  // Z_VR20_K
  (unsigned char)'\x15',  // Z_VR21
  (unsigned char)'\x15',  // Z_VR21_H
  (unsigned char)'\x15',  // Z_VR21_J
  (unsigned char)'\x15',  // Z_VR21_K
  (unsigned char)'\x16',  // Z_VR22
  (unsigned char)'\x16',  // Z_VR22_H
  (unsigned char)'\x16',  // Z_VR22_J
  (unsigned char)'\x16',  // Z_VR22_K
  (unsigned char)'\x17',  // Z_VR23
  (unsigned char)'\x17',  // Z_VR23_H
  (unsigned char)'\x17',  // Z_VR23_J
  (unsigned char)'\x17',  // Z_VR23_K
  (unsigned char)'\x18',  // Z_VR24
  (unsigned char)'\x18',  // Z_VR24_H
  (unsigned char)'\x18',  // Z_VR24_J
  (unsigned char)'\x18',  // Z_VR24_K
  (unsigned char)'\x19',  // Z_VR25
  (unsigned char)'\x19',  // Z_VR25_H
  (unsigned char)'\x19',  // Z_VR25_J
  (unsigned char)'\x19',  // Z_VR25_K
  (unsigned char)'\x1A',  // Z_VR26
  (unsigned char)'\x1A',  // Z_VR26_H
  (unsigned char)'\x1A',  // Z_VR26_J
  (unsigned char)'\x1A',  // Z_VR26_K
  (unsigned char)'\x1B',  // Z_VR27
  (unsigned char)'\x1B',  // Z_VR27_H
  (unsigned char)'\x1B',  // Z_VR27_J
  (unsigned char)'\x1B',  // Z_VR27_K
  (unsigned char)'\x1C',  // Z_VR28
  (unsigned char)'\x1C',  // Z_VR28_H
  (unsigned char)'\x1C',  // Z_VR28_J
  (unsigned char)'\x1C',  // Z_VR28_K
  (unsigned char)'\x1D',  // Z_VR29
  (unsigned char)'\x1D',  // Z_VR29_H
  (unsigned char)'\x1D',  // Z_VR29_J
  (unsigned char)'\x1D',  // Z_VR29_K
  (unsigned char)'\x1E',  // Z_VR30
  (unsigned char)'\x1E',  // Z_VR30_H
  (unsigned char)'\x1E',  // Z_VR30_J
  (unsigned char)'\x1E',  // Z_VR30_K
  (unsigned char)'\x1F',  // Z_VR31
  (unsigned char)'\x1F',  // Z_VR31_H
  (unsigned char)'\x1F',  // Z_VR31_J
  (unsigned char)'\x1F',  // Z_VR31_K
  (unsigned char)'\x0' // no trailing comma  // Z_CR
};


//------------------Define classes derived from MachOper---------------------
MachOper  *labelOper::clone() const {
  return  new labelOper(_label, _block_num);
}
uint labelOper::opcode() const { return LABEL; }

const RegMask *sRegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

const RegMask *sRegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

const RegMask *sRegFOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

const RegMask *sRegDOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

const RegMask *sRegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

MachOper  *methodOper::clone() const {
  return  new methodOper(_method);
}
uint methodOper::opcode() const { return METHOD; }

const RegMask *vecXOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_V_REG_mask();
}

const RegMask *v16TempRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_VREG_16_mask();
}

const RegMask *v17TempRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_VREG_17_mask();
}

const RegMask *v18TempRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_VREG_18_mask();
}

const RegMask *v19TempRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_VREG_19_mask();
}

const RegMask *v20TempRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_VREG_20_mask();
}

const RegMask *v21TempRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_VREG_21_mask();
}

const RegMask *v22TempRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_VREG_22_mask();
}

const RegMask *v23TempRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_VREG_23_mask();
}

const RegMask *v24TempRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_VREG_24_mask();
}

const RegMask *v25TempRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_VREG_25_mask();
}

const RegMask *iRegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_INT_REG_mask();
}

const RegMask *noArg_iRegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_NO_ARG_INT_REG_mask();
}

const RegMask *revenRegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG3_INT_REG_mask();
}

const RegMask *roddRegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG4_INT_REG_mask();
}

const RegMask *rarg1RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG1_INT_REG_mask();
}

const RegMask *rarg2RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG2_INT_REG_mask();
}

const RegMask *rarg3RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG3_INT_REG_mask();
}

const RegMask *rarg4RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG4_INT_REG_mask();
}

const RegMask *rarg5RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG5_INT_REG_mask();
}

const RegMask *noOdd_iRegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_NO_ODD_INT_REG_mask();
}

const RegMask *iRegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_PTR_REG_mask();
}

const RegMask *threadRegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_THREAD_PTR_REG_mask();
}

const RegMask *r10TempRegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_R10_PTR_REG_mask();
}

const RegMask *r11TempRegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_R11_PTR_REG_mask();
}

const RegMask *noArg_iRegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_NO_ARG_PTR_REG_mask();
}

const RegMask *rarg1RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG1_PTR_REG_mask();
}

const RegMask *rarg2RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG2_PTR_REG_mask();
}

const RegMask *rarg3RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG3_PTR_REG_mask();
}

const RegMask *rarg4RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG4_PTR_REG_mask();
}

const RegMask *rarg5RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG5_PTR_REG_mask();
}

const RegMask *memoryRegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_MEMORY_PTR_REG_mask();
}

const RegMask *revenRegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG3_PTR_REG_mask();
}

const RegMask *roddRegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG4_PTR_REG_mask();
}

const RegMask *iRegNOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_INT_REG_mask();
}

const RegMask *noArg_iRegNOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_NO_ARG_INT_REG_mask();
}

const RegMask *rarg1RegNOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG1_INT_REG_mask();
}

const RegMask *rarg2RegNOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG2_INT_REG_mask();
}

const RegMask *rarg3RegNOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG3_INT_REG_mask();
}

const RegMask *rarg4RegNOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG4_INT_REG_mask();
}

const RegMask *rarg5RegNOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG5_PTRN_REG_mask();
}

const RegMask *iRegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_LONG_REG_mask();
}

const RegMask *revenRegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG3_LONG_REG_mask();
}

const RegMask *roddRegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG4_LONG_REG_mask();
}

const RegMask *allRoddRegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_LONG_ODD_REG_mask();
}

const RegMask *rarg1RegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG1_LONG_REG_mask();
}

const RegMask *rarg5RegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RARG5_LONG_REG_mask();
}

const RegMask *flagsRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_CONDITION_REG_mask();
}

const RegMask *regDOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_DBL_REG_mask();
}

const RegMask *regFOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_FLT_REG_mask();
}

const RegMask *inline_cache_regPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_R9_REGP_mask();
}

const RegMask *indirectOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_MEMORY_PTR_REG_mask();
}

const RegMask *indOffset20Oper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_MEMORY_PTR_REG_mask();
}

const RegMask *indOffset20NarrowOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_INT_REG_mask();
}

const RegMask *indOffset12Oper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_MEMORY_PTR_REG_mask();
}

const RegMask *indOffset12NarrowOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_INT_REG_mask();
}

const RegMask *indIndexOper::in_RegMask(int index) const {
  assert(0 <= index && index < 2, "index out of range");
  switch (index) {
  case 0: return &Z_MEMORY_PTR_REG_mask();
  case 1: return &Z_LONG_REG_mask();
  }
  ShouldNotReachHere();
  return nullptr;
}

const RegMask *indOffset20indexOper::in_RegMask(int index) const {
  assert(0 <= index && index < 2, "index out of range");
  switch (index) {
  case 0: return &Z_MEMORY_PTR_REG_mask();
  case 1: return &Z_LONG_REG_mask();
  }
  ShouldNotReachHere();
  return nullptr;
}

const RegMask *indOffset20indexNarrowOper::in_RegMask(int index) const {
  assert(0 <= index && index < 2, "index out of range");
  switch (index) {
  case 0: return &Z_INT_REG_mask();
  case 1: return &Z_LONG_REG_mask();
  }
  ShouldNotReachHere();
  return nullptr;
}

const RegMask *indOffset12indexOper::in_RegMask(int index) const {
  assert(0 <= index && index < 2, "index out of range");
  switch (index) {
  case 0: return &Z_MEMORY_PTR_REG_mask();
  case 1: return &Z_LONG_REG_mask();
  }
  ShouldNotReachHere();
  return nullptr;
}

const RegMask *indOffset12indexNarrowOper::in_RegMask(int index) const {
  assert(0 <= index && index < 2, "index out of range");
  switch (index) {
  case 0: return &Z_INT_REG_mask();
  case 1: return &Z_LONG_REG_mask();
  }
  ShouldNotReachHere();
  return nullptr;
}

const RegMask *stackSlotIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

const RegMask *stackSlotPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

const RegMask *stackSlotFOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

const RegMask *stackSlotDOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

const RegMask *stackSlotLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

//------------------Define members for classes derived from MachNode----------

void addI_reg_reg_CISCNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *addI_reg_reg_CISCNode::cisc_version(int offset) {
  addI_Reg_memNode *node = new addI_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void addL_reg_regINode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *addL_reg_regINode::cisc_version(int offset) {
  addL_Reg_memINode *node = new addL_Reg_memINode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void addL_reg_regI_0Node::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *addL_reg_regI_0Node::cisc_version(int offset) {
  addL_Reg_memI_0Node *node = new addL_Reg_memI_0Node();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void addL_reg_reg_CISCNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_LONG_REG_mask();
}

// Build CISC version of this instruction
MachNode *addL_reg_reg_CISCNode::cisc_version(int offset) {
  addL_Reg_memNode *node = new addL_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void subI_reg_reg_CISCNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *subI_reg_reg_CISCNode::cisc_version(int offset) {
  subI_Reg_memNode *node = new subI_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void subL_reg_reg_CISCNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_LONG_REG_mask();
}

// Build CISC version of this instruction
MachNode *subL_reg_reg_CISCNode::cisc_version(int offset) {
  subL_Reg_memNode *node = new subL_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void subL_reg_regI_CISCNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *subL_reg_regI_CISCNode::cisc_version(int offset) {
  subL_Reg_memINode *node = new subL_Reg_memINode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void mulI_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *mulI_reg_regNode::cisc_version(int offset) {
  mulI_Reg_memNode *node = new mulI_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void mulL_reg_regINode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *mulL_reg_regINode::cisc_version(int offset) {
  mulL_Reg_memINode *node = new mulL_Reg_memINode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void mulL_reg_regI_0Node::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *mulL_reg_regI_0Node::cisc_version(int offset) {
  mulL_Reg_memI_0Node *node = new mulL_Reg_memI_0Node();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void mulL_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_LONG_REG_mask();
}

// Build CISC version of this instruction
MachNode *mulL_reg_regNode::cisc_version(int offset) {
  mulL_Reg_memNode *node = new mulL_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void addF_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_FLT_REG_mask();
}

// Build CISC version of this instruction
MachNode *addF_reg_regNode::cisc_version(int offset) {
  addF_reg_memNode *node = new addF_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void addD_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_DBL_REG_mask();
}

// Build CISC version of this instruction
MachNode *addD_reg_regNode::cisc_version(int offset) {
  addD_reg_memNode *node = new addD_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void subF_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_FLT_REG_mask();
}

// Build CISC version of this instruction
MachNode *subF_reg_regNode::cisc_version(int offset) {
  subF_reg_memNode *node = new subF_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void subD_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_DBL_REG_mask();
}

// Build CISC version of this instruction
MachNode *subD_reg_regNode::cisc_version(int offset) {
  subD_reg_memNode *node = new subD_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void mulF_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_FLT_REG_mask();
}

// Build CISC version of this instruction
MachNode *mulF_reg_regNode::cisc_version(int offset) {
  mulF_reg_memNode *node = new mulF_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void mulD_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_DBL_REG_mask();
}

// Build CISC version of this instruction
MachNode *mulD_reg_regNode::cisc_version(int offset) {
  mulD_reg_memNode *node = new mulD_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void maddF_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_FLT_REG_mask();
}

// Build CISC version of this instruction
MachNode *maddF_reg_regNode::cisc_version(int offset) {
  maddF_reg_memNode *node = new maddF_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void maddD_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_DBL_REG_mask();
}

// Build CISC version of this instruction
MachNode *maddD_reg_regNode::cisc_version(int offset) {
  maddD_reg_memNode *node = new maddD_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void msubF_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_FLT_REG_mask();
}

// Build CISC version of this instruction
MachNode *msubF_reg_regNode::cisc_version(int offset) {
  msubF_reg_memNode *node = new msubF_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void msubD_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_DBL_REG_mask();
}

// Build CISC version of this instruction
MachNode *msubD_reg_regNode::cisc_version(int offset) {
  msubD_reg_memNode *node = new msubD_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void divF_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_FLT_REG_mask();
}

// Build CISC version of this instruction
MachNode *divF_reg_regNode::cisc_version(int offset) {
  divF_reg_memNode *node = new divF_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void divD_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_DBL_REG_mask();
}

// Build CISC version of this instruction
MachNode *divD_reg_regNode::cisc_version(int offset) {
  divD_reg_memNode *node = new divD_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void sqrtF_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_FLT_REG_mask();
}

// Build CISC version of this instruction
MachNode *sqrtF_regNode::cisc_version(int offset) {
  sqrtF_memNode *node = new sqrtF_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void sqrtD_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_DBL_REG_mask();
}

// Build CISC version of this instruction
MachNode *sqrtD_regNode::cisc_version(int offset) {
  sqrtD_memNode *node = new sqrtD_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void andI_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *andI_reg_regNode::cisc_version(int offset) {
  andI_Reg_memNode *node = new andI_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void andL_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_LONG_REG_mask();
}

// Build CISC version of this instruction
MachNode *andL_reg_regNode::cisc_version(int offset) {
  andL_Reg_memNode *node = new andL_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void orI_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *orI_reg_regNode::cisc_version(int offset) {
  orI_Reg_memNode *node = new orI_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void orL_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_LONG_REG_mask();
}

// Build CISC version of this instruction
MachNode *orL_reg_regNode::cisc_version(int offset) {
  orL_Reg_memNode *node = new orL_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void xorI_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *xorI_reg_regNode::cisc_version(int offset) {
  xorI_Reg_memNode *node = new xorI_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void xorL_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_LONG_REG_mask();
}

// Build CISC version of this instruction
MachNode *xorL_reg_regNode::cisc_version(int offset) {
  xorL_Reg_memNode *node = new xorL_Reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void convF2D_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_FLT_REG_mask();
}

// Build CISC version of this instruction
MachNode *convF2D_regNode::cisc_version(int offset) {
  convF2D_memNode *node = new convF2D_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void convI2L_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *convI2L_regNode::cisc_version(int offset) {
  loadI2LNode *node = new loadI2LNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void convI2L_reg_zexNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *convI2L_reg_zexNode::cisc_version(int offset) {
  convI2L_mem_zexNode *node = new convI2L_mem_zexNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}

// Build short branch version of this instruction
MachNode *rangeCheck_iReg_iRegNode::short_branch_version() {
  cmpbU_RegINode *node = new cmpbU_RegINode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}


void compI_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *compI_reg_regNode::cisc_version(int offset) {
  compI_reg_memNode *node = new compI_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void compU_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *compU_reg_regNode::cisc_version(int offset) {
  compU_reg_memNode *node = new compU_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void compL_reg_regNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_LONG_REG_mask();
}

// Build CISC version of this instruction
MachNode *compL_reg_regNode::cisc_version(int offset) {
  compL_reg_memNode *node = new compL_reg_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void compL_reg_regINode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_INT_REG_mask();
}

// Build CISC version of this instruction
MachNode *compL_reg_regINode::cisc_version(int offset) {
  compL_reg_memINode *node = new compL_reg_memINode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void cmpF_ccNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_FLT_REG_mask();
}

// Build CISC version of this instruction
MachNode *cmpF_ccNode::cisc_version(int offset) {
  cmpF_cc_memNode *node = new cmpF_cc_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}


void cmpD_ccNode::use_cisc_RegMask() {
  _cisc_RegMask = &STACK_OR_Z_DBL_REG_mask();
}

// Build CISC version of this instruction
MachNode *cmpD_ccNode::cisc_version(int offset) {
  cmpD_cc_memNode *node = new cmpD_cc_memNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  // Construct operand to access [stack_pointer + offset]
  node->set_opnd_array(cisc_operand(), new indOffset12Oper(offset));

  return node;
}

// Build short branch version of this instruction
MachNode *branchFarNode::short_branch_version() {
  branchNode *node = new branchNode();

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *branchConFarNode::short_branch_version() {
  branchConNode *node = new branchConNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *branchLoopEndFarNode::short_branch_version() {
  branchLoopEndNode *node = new branchLoopEndNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *testAndBranchLoopEnd_RegFarNode::short_branch_version() {
  testAndBranchLoopEnd_RegNode *node = new testAndBranchLoopEnd_RegNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpb_RegI_FarNode::short_branch_version() {
  cmpb_RegINode *node = new cmpb_RegINode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpbU_RegI_FarNode::short_branch_version() {
  cmpbU_RegINode *node = new cmpbU_RegINode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpb_RegL_FarNode::short_branch_version() {
  cmpb_RegLNode *node = new cmpb_RegLNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpb_RegPP_FarNode::short_branch_version() {
  cmpb_RegPPNode *node = new cmpb_RegPPNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpb_RegNN_FarNode::short_branch_version() {
  cmpb_RegNNNode *node = new cmpb_RegNNNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *testAndBranchLoopEnd_ImmFarNode::short_branch_version() {
  testAndBranchLoopEnd_ImmNode *node = new testAndBranchLoopEnd_ImmNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpb_RegI_imm_FarNode::short_branch_version() {
  cmpb_RegI_immNode *node = new cmpb_RegI_immNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpbU_RegI_imm_FarNode::short_branch_version() {
  cmpbU_RegI_immNode *node = new cmpbU_RegI_immNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpb_RegL_imm_FarNode::short_branch_version() {
  cmpb_RegL_immNode *node = new cmpb_RegL_immNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpb_RegP_immP_FarNode::short_branch_version() {
  cmpb_RegP_immPNode *node = new cmpb_RegP_immPNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpb_RegN_immP0_FarNode::short_branch_version() {
  cmpb_RegN_immP0Node *node = new cmpb_RegN_immP0Node();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

// Build short branch version of this instruction
MachNode *cmpb_RegN_immN_FarNode::short_branch_version() {
  cmpb_RegN_immNode *node = new cmpb_RegN_immNode();
  node->_prob = _prob;
  node->_fcnt = _fcnt;

  // Copy _idx, inputs and operands to new node
  fill_new_machnode(node);
  return node;
}

void rangeCheck_iReg_uimmI16Node::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void rangeCheck_iReg_uimmI16Node::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void rangeCheck_iReg_iRegNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void rangeCheck_iReg_iRegNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void rangeCheck_uimmI16_iRegNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void rangeCheck_uimmI16_iRegNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void zeroCheckP_iReg_imm0Node::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void zeroCheckP_iReg_imm0Node::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void zeroCheckN_iReg_imm0Node::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void zeroCheckN_iReg_imm0Node::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void branchNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(1));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void branchNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(1));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void branchFarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(1));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void branchFarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(1));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void branchConNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void branchConNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void branchConFarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void branchConFarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void branchLoopEndNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void branchLoopEndNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void branchLoopEndFarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void branchLoopEndFarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void testAndBranchLoopEnd_RegNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void testAndBranchLoopEnd_RegNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegINode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegINode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpbU_RegINode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpbU_RegINode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegLNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegLNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegPPNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegPPNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegNNNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegNNNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void testAndBranchLoopEnd_ImmNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void testAndBranchLoopEnd_ImmNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegI_immNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegI_immNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpbU_RegI_immNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpbU_RegI_immNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegL_immNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegL_immNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegP_immPNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegP_immPNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegN_immP0Node::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegN_immP0Node::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegN_immNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegN_immNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void testAndBranchLoopEnd_RegFarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void testAndBranchLoopEnd_RegFarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegI_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegI_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpbU_RegI_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpbU_RegI_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegL_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegL_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegPP_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegPP_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegNN_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegNN_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void testAndBranchLoopEnd_ImmFarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void testAndBranchLoopEnd_ImmFarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegI_imm_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegI_imm_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpbU_RegI_imm_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpbU_RegI_imm_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegL_imm_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegL_imm_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegP_immP_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegP_immP_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegN_immP0_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegN_immP0_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void cmpb_RegN_immN_FarNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void cmpb_RegN_immN_FarNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void CallStaticJavaDirect_dynTOCNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallDynamicJavaDirect_dynTOCNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallRuntimeDirectNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallLeafDirectNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallLeafNoFPDirectNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

int loadBNode::reloc() const {
  return 1;
}

int loadB2LNode::reloc() const {
  return 1;
}

int loadUBNode::reloc() const {
  return 1;
}

int loadUB2LNode::reloc() const {
  return 1;
}

int loadSNode::reloc() const {
  return 1;
}

int loadS2LNode::reloc() const {
  return 1;
}

int loadUSNode::reloc() const {
  return 1;
}

int loadUS2LNode::reloc() const {
  return 1;
}

int loadINode::reloc() const {
  return 1;
}

int loadI2LNode::reloc() const {
  return 1;
}

int loadUI2LNode::reloc() const {
  return 1;
}

int loadRangeNode::reloc() const {
  return 1;
}

int loadLNode::reloc() const {
  return 1;
}

int loadL_unalignedNode::reloc() const {
  return 1;
}

int loadPNode::reloc() const {
  return 1;
}

int castP2X_loadPNode::reloc() const {
  return 1;
}

int loadKlassNode::reloc() const {
  return 1;
}

int loadFNode::reloc() const {
  return 1;
}

int loadDNode::reloc() const {
  return 1;
}

int loadD_unalignedNode::reloc() const {
  return 1;
}

int loadConP_pcrelTOCNode::reloc() const {
  return 1;
}

int loadConP0Node::reloc() const {
  return 1;
}

int loadConF_dynTOCNode::reloc() const {
  return 2;
}

int loadConD_dynTOCNode::reloc() const {
  return 2;
}

int loadConF0Node::reloc() const {
  return 2;
}

int loadConD0Node::reloc() const {
  return 2;
}

int storeBNode::reloc() const {
  return 2;
}

int storeCNode::reloc() const {
  return 2;
}

int storeINode::reloc() const {
  return 2;
}

int storeLNode::reloc() const {
  return 2;
}

int storePNode::reloc() const {
  return 2;
}

int storeFNode::reloc() const {
  return 2;
}

int storeDNode::reloc() const {
  return 2;
}

int prefetchAllocNode::reloc() const {
  return 1;
}

int memInitBNode::reloc() const {
  return 2;
}

int memInitCNode::reloc() const {
  return 2;
}

int memInitINode::reloc() const {
  return 2;
}

int memInitLNode::reloc() const {
  return 2;
}

int memInitPNode::reloc() const {
  return 3;
}

int loadNNode::reloc() const {
  return 1;
}

int loadNKlassNode::reloc() const {
  return 1;
}

int loadNKlassCompactHeadersNode::reloc() const {
  return 1;
}

int decodeLoadNNode::reloc() const {
  return 1;
}

int decodeLoadNKlassNode::reloc() const {
  return 1;
}

int storeNNode::reloc() const {
  return 3;
}

int storeNKlassNode::reloc() const {
  return 2;
}

int compN_iRegNNode::reloc() const {
  return 2;
}

int compN_iRegN_immNNode::reloc() const {
  return 1;
}

int compN_iRegN_immN0Node::reloc() const {
  return 1;
}

int castP2XNode::reloc() const {
  return 1;
}

int cmovN_regNode::reloc() const {
  return 1;
}

int cmovP_regNode::reloc() const {
  return 1;
}

int cmovP_immNode::reloc() const {
  return 1;
}

int compareAndSwapP_boolNode::reloc() const {
  return 1;
}

int compareAndSwapN_boolNode::reloc() const {
  return 1;
}

int addI_mem_imm8_atomic_no_resNode::reloc() const {
  return 1;
}

int addI_mem_imm16_atomicNode::reloc() const {
  return 1;
}

int addI_mem_imm32_atomicNode::reloc() const {
  return 1;
}

int addI_mem_reg_atomicNode::reloc() const {
  return 1;
}

int addL_mem_imm8_atomic_no_resNode::reloc() const {
  return 1;
}

int addL_mem_imm16_atomicNode::reloc() const {
  return 1;
}

int addL_mem_imm32_atomicNode::reloc() const {
  return 1;
}

int addL_mem_reg_atomicNode::reloc() const {
  return 1;
}

int addI_mem_reg_atomic_z196Node::reloc() const {
  return 1;
}

int addL_mem_reg_atomic_z196Node::reloc() const {
  return 1;
}

int xchgI_reg_memNode::reloc() const {
  return 1;
}

int xchgL_reg_memNode::reloc() const {
  return 1;
}

int xchgN_reg_memNode::reloc() const {
  return 1;
}

int xchgP_reg_memNode::reloc() const {
  return 1;
}

int addI_Reg_memNode::reloc() const {
  return 1;
}

int addI_Reg_mem_0Node::reloc() const {
  return 1;
}

int addI_mem_immNode::reloc() const {
  return 3;
}

int addL_Reg_memINode::reloc() const {
  return 1;
}

int addL_Reg_memI_0Node::reloc() const {
  return 1;
}

int addL_Reg_memNode::reloc() const {
  return 1;
}

int addL_Reg_mem_0Node::reloc() const {
  return 1;
}

int addL_mem_immNode::reloc() const {
  return 3;
}

int addP_reg_reg_LANode::reloc() const {
  return 1;
}

int addP_reg_reg_RISCNode::reloc() const {
  return 1;
}

int addP_reg_imm12Node::reloc() const {
  return 1;
}

int addP_reg_imm16_RISCNode::reloc() const {
  return 1;
}

int addP_regN_reg_imm12Node::reloc() const {
  return 1;
}

int addP_regN_reg_imm20Node::reloc() const {
  return 1;
}

int addP_mem_immNode::reloc() const {
  return 3;
}

int subI_Reg_memNode::reloc() const {
  return 1;
}

int subL_Reg_memINode::reloc() const {
  return 1;
}

int subL_Reg_memNode::reloc() const {
  return 1;
}

int mulI_Reg_memNode::reloc() const {
  return 1;
}

int mulI_Reg_mem_0Node::reloc() const {
  return 1;
}

int mulL_Reg_memINode::reloc() const {
  return 1;
}

int mulL_Reg_memI_0Node::reloc() const {
  return 1;
}

int mulL_Reg_memNode::reloc() const {
  return 1;
}

int mulL_Reg_mem_0Node::reloc() const {
  return 1;
}

int srlP_reg_immNode::reloc() const {
  return 1;
}

int addF_reg_memNode::reloc() const {
  return 1;
}

int addF_reg_mem_0Node::reloc() const {
  return 1;
}

int addD_reg_memNode::reloc() const {
  return 1;
}

int addD_reg_mem_0Node::reloc() const {
  return 1;
}

int subF_reg_memNode::reloc() const {
  return 1;
}

int subD_reg_memNode::reloc() const {
  return 1;
}

int mulF_reg_memNode::reloc() const {
  return 1;
}

int mulF_reg_mem_0Node::reloc() const {
  return 1;
}

int mulD_reg_memNode::reloc() const {
  return 1;
}

int mulD_reg_mem_0Node::reloc() const {
  return 1;
}

int maddF_reg_memNode::reloc() const {
  return 1;
}

int maddD_reg_memNode::reloc() const {
  return 1;
}

int msubF_reg_memNode::reloc() const {
  return 1;
}

int msubD_reg_memNode::reloc() const {
  return 1;
}

int maddF_mem_regNode::reloc() const {
  return 1;
}

int maddD_mem_regNode::reloc() const {
  return 1;
}

int msubF_mem_regNode::reloc() const {
  return 1;
}

int msubD_mem_regNode::reloc() const {
  return 1;
}

int divF_reg_memNode::reloc() const {
  return 1;
}

int divD_reg_memNode::reloc() const {
  return 1;
}

int sqrtF_memNode::reloc() const {
  return 1;
}

int sqrtD_memNode::reloc() const {
  return 1;
}

int andI_Reg_memNode::reloc() const {
  return 1;
}

int andI_Reg_mem_0Node::reloc() const {
  return 1;
}

int andL_Reg_memNode::reloc() const {
  return 1;
}

int andL_Reg_mem_0Node::reloc() const {
  return 1;
}

int orI_Reg_memNode::reloc() const {
  return 1;
}

int orI_Reg_mem_0Node::reloc() const {
  return 1;
}

int orL_Reg_memNode::reloc() const {
  return 1;
}

int orL_Reg_mem_0Node::reloc() const {
  return 1;
}

int xorI_Reg_memNode::reloc() const {
  return 1;
}

int xorI_Reg_mem_0Node::reloc() const {
  return 1;
}

int xorL_Reg_memNode::reloc() const {
  return 1;
}

int convP2BNode::reloc() const {
  return 1;
}

int convF2D_memNode::reloc() const {
  return 1;
}

int convI2L_mem_zexNode::reloc() const {
  return 1;
}

int zeroCheckP_iReg_imm0Node::reloc() const {
  return 2;
}

int zeroCheckN_iReg_imm0Node::reloc() const {
  return 1;
}

int compI_reg_memNode::reloc() const {
  return 1;
}

int compU_reg_memNode::reloc() const {
  return 1;
}

int compL_reg_memNode::reloc() const {
  return 1;
}

int compL_reg_memINode::reloc() const {
  return 1;
}

int compP_reg_regNode::reloc() const {
  return 2;
}

int compP_reg_imm0Node::reloc() const {
  return 2;
}

int compP_decode_reg_imm0Node::reloc() const {
  return 1;
}

int compP_reg_memNode::reloc() const {
  return 1;
}

int cmpF_cc_memNode::reloc() const {
  return 1;
}

int cmpD_cc_memNode::reloc() const {
  return 1;
}

int cmpF0_ccNode::reloc() const {
  return 1;
}

int cmpD0_ccNode::reloc() const {
  return 1;
}

int cmpb_RegP_immPNode::reloc() const {
  return 1;
}

int cmpb_RegN_immP0Node::reloc() const {
  return 1;
}

int cmpb_RegP_immP_FarNode::reloc() const {
  return 1;
}

int cmpb_RegN_immP0_FarNode::reloc() const {
  return 1;
}

int safePointNode::reloc() const {
  return 1;
}

int safePoint_pollNode::reloc() const {
  return 1;
}

int CallStaticJavaDirect_dynTOCNode::reloc() const {
  return 1;
}

int CallDynamicJavaDirect_dynTOCNode::reloc() const {
  return 1;
}

int CallRuntimeDirectNode::reloc() const {
  return 1;
}

int CallLeafDirectNode::reloc() const {
  return 1;
}

int CallLeafNoFPDirectNode::reloc() const {
  return 1;
}

int TailCalljmpIndNode::reloc() const {
  return 1;
}

int RetNode::reloc() const {
  return 1;
}

int tailjmpIndNode::reloc() const {
  return 1;
}

int ForwardExceptionjmpNode::reloc() const {
  return 1;
}

int RethrowExceptionNode::reloc() const {
  return 1;
}

int partialSubtypeCheckConstSuperNode::reloc() const {
  return 1;
}

int cmpFastLockNode::reloc() const {
  return 2;
}

int cmpFastUnlockNode::reloc() const {
  return 2;
}

int inlineCallClearArrayConstNode::reloc() const {
  return 1;
}

int inlineCallClearArrayConstBigNode::reloc() const {
  return 1;
}

int inlineCallClearArrayNode::reloc() const {
  return 1;
}

int indexOf_imm1_UNode::reloc() const {
  return 1;
}

int indexOf_imm1_LNode::reloc() const {
  return 1;
}

int indexOf_imm1_ULNode::reloc() const {
  return 1;
}

int Repl2F_immNode::reloc() const {
  return 1;
}

int Repl2F_imm0Node::reloc() const {
  return 1;
}

int repl4F_immF0Node::reloc() const {
  return 1;
}

int repl2D_immD0Node::reloc() const {
  return 1;
}

int storeA8BNode::reloc() const {
  return 2;
}

int storeV16Node::reloc() const {
  return 2;
}

int loadV8Node::reloc() const {
  return 1;
}

int loadV16Node::reloc() const {
  return 1;
}

int g1StoreNNode::reloc() const {
  return 1;
}

int g1CompareAndSwapNNode::reloc() const {
  return 1;
}

int g1CompareAndSwapN_0Node::reloc() const {
  return 1;
}

int g1CompareAndExchangeNNode::reloc() const {
  return 1;
}

int g1CompareAndSwapPNode::reloc() const {
  return 1;
}

int g1CompareAndSwapP_0Node::reloc() const {
  return 1;
}

int g1CompareAndExchangePNode::reloc() const {
  return 1;
}

int g1LoadPNode::reloc() const {
  return 1;
}


void stkI_to_regINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((L_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (L_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (L_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 9430 "ad_s390.cpp"
  }
}

void regI_to_stkINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((ST_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (ST_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (ST_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 9458 "ad_s390.cpp"
  }
}

void stkL_to_regLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 9486 "ad_s390.cpp"
  }
}

void regL_to_stkLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 9514 "ad_s390.cpp"
  }
}

uint regL_to_stkLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void stkP_to_regPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 9547 "ad_s390.cpp"
  }
}

void regP_to_stkPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 9575 "ad_s390.cpp"
  }
}

void stkF_to_regFNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LE_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (LE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (LE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 9603 "ad_s390.cpp"
  }
}

uint stkF_to_regFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void regF_to_stkFNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STE_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 9636 "ad_s390.cpp"
  }
}

uint regF_to_stkFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void stkD_to_regDNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LD_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (LD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (LD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 9669 "ad_s390.cpp"
  }
}

void regD_to_stkDNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STD_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 9697 "ad_s390.cpp"
  }
}

uint regD_to_stkDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadBNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LB_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LB_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LB_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9740 "ad_s390.cpp"
  }
}

uint loadBNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadB2LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LGB_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LGB_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LGB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LGB_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9783 "ad_s390.cpp"
  }
}

uint loadB2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadUBNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGC_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGC_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGC_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LLGC_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9826 "ad_s390.cpp"
  }
}

uint loadUBNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadUB2LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGC_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGC_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGC_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LLGC_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9869 "ad_s390.cpp"
  }
}

uint loadUB2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadSNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LH_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LH_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LHY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LH_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9912 "ad_s390.cpp"
  }
}

uint loadSNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadS2LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LGH_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LGH_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LGH_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LGH_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9955 "ad_s390.cpp"
  }
}

uint loadS2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadUSNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGH_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGH_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGH_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LLGH_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9998 "ad_s390.cpp"
  }
}

uint loadUSNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadUS2LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGH_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGH_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGH_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LLGH_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10041 "ad_s390.cpp"
  }
}

uint loadUS2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (L_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (L_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (L_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10084 "ad_s390.cpp"
  }
}

uint loadINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadI2LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10127 "ad_s390.cpp"
  }
}

uint loadI2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadUI2LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10171 "ad_s390.cpp"
  }
}

uint loadUI2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadRangeNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (L_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (L_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (L_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10214 "ad_s390.cpp"
  }
}

uint loadRangeNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10257 "ad_s390.cpp"
  }
}

uint loadLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadL_unalignedNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10300 "ad_s390.cpp"
  }
}

uint loadL_unalignedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10343 "ad_s390.cpp"
  }
}

uint loadPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void castP2X_loadPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10386 "ad_s390.cpp"
  }
}

uint castP2X_loadPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadKlassNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10429 "ad_s390.cpp"
  }
}

uint loadKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadTOCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 4359 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ load_toc(opnd_array(0)->as_Register(ra_,this)/* dst */); 
#line 10446 "ad_s390.cpp"
  }
}

void loadFNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LE_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LE_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LEY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LE_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10484 "ad_s390.cpp"
  }
}

uint loadFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadDNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LD_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LD_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LDY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LD_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10527 "ad_s390.cpp"
  }
}

uint loadDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadD_unalignedNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LD_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LD_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LDY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LD_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10570 "ad_s390.cpp"
  }
}

uint loadD_unalignedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadConINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4410 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lgfi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constant()); 
#line 10587 "ad_s390.cpp"
  }
}

uint loadConINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConI16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4419 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constant()); 
#line 10604 "ad_s390.cpp"
  }
}

uint loadConI16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConI_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (XGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,28,32));
  
#line 10626 "ad_s390.cpp"
  }
}

uint loadConI_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConUI16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2035 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LLILL_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LLILL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::uimm16(opnd_array(1)->constant(),16,32));
  
#line 10648 "ad_s390.cpp"
  }
}

void loadConL_pcrelTOCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4449 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    address long_address = __ long_constant(opnd_array(1)->constantL());
    if (long_address == nullptr) {
      Compile::current()->env()->record_out_of_memory_failure();
      return;
    }
    __ load_long_pcrelative(opnd_array(0)->as_Register(ra_,this)/* dst */, long_address);
  
#line 10667 "ad_s390.cpp"
  }
}

uint loadConL_pcrelTOCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConL32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4465 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lgfi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constantL()); 
#line 10684 "ad_s390.cpp"
  }
}

uint loadConL32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConL16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4474 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constantL()); 
#line 10701 "ad_s390.cpp"
  }
}

uint loadConL16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConL_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (XGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,28,32));
  
#line 10723 "ad_s390.cpp"
  }
}

void loadConP_pcrelTOCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4495 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    relocInfo::relocType constant_reloc = opnd_array(1)->constant_reloc();
    if (constant_reloc == relocInfo::oop_type) {
      AddressLiteral a = __ allocate_oop_address((jobject)opnd_array(1)->constant());
      bool success = __ load_oop_from_toc(opnd_array(0)->as_Register(ra_,this)/* dst */, a);
      if (!success) {
        Compile::current()->env()->record_out_of_memory_failure();
        return;
      }
    } else if (constant_reloc == relocInfo::metadata_type) {
      AddressLiteral a = __ constant_metadata_address((Metadata *)opnd_array(1)->constant());
      address const_toc_addr = __ address_constant((address)a.value(), RelocationHolder::none);
      if (const_toc_addr == nullptr) {
        Compile::current()->env()->record_out_of_memory_failure();
        return;
      }
      __ load_long_pcrelative(opnd_array(0)->as_Register(ra_,this)/* dst */, const_toc_addr);
    } else {          // Non-oop pointers, e.g. card mark base, heap top.
      address long_address = __ long_constant((jlong)opnd_array(1)->constant());
      if (long_address == nullptr) {
        Compile::current()->env()->record_out_of_memory_failure();
        return;
      }
      __ load_long_pcrelative(opnd_array(0)->as_Register(ra_,this)/* dst */, long_address);
    }
  
#line 10760 "ad_s390.cpp"
  }
}

uint loadConP_pcrelTOCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConP0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (XGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,28,32));
  
#line 10782 "ad_s390.cpp"
  }
}

uint loadConP0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConF_dynTOCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4550 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_float_largeoffset(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, constant_offset(), as_Register(ra_->get_encode(in(mach_constant_base_node_input()))), Z_R1_scratch);
  
#line 10801 "ad_s390.cpp"
  }
}

void loadConF_dynTOCNode::eval_constant(Compile* C) {
  {

#line 4551 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
    _constant = C->output()->constant_table().add(this, opnd_array(1));
#line 10810 "ad_s390.cpp"
  }
}
uint loadConF_dynTOCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConD_dynTOCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4569 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_double_largeoffset(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, constant_offset(), as_Register(ra_->get_encode(in(mach_constant_base_node_input()))), Z_R1_scratch);
  
#line 10828 "ad_s390.cpp"
  }
}

void loadConD_dynTOCNode::eval_constant(Compile* C) {
  {

#line 4570 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
    _constant = C->output()->constant_table().add(this, opnd_array(1));
#line 10837 "ad_s390.cpp"
  }
}
uint loadConD_dynTOCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConF0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LZER_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LZER_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg((Z_F0_enc),28,32));
  
#line 10858 "ad_s390.cpp"
  }
}

uint loadConF0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConD0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LZDR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LZDR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg((Z_F0_enc),28,32));
  
#line 10880 "ad_s390.cpp"
  }
}

uint loadConD0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeBNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STC_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STC_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STCY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (STC_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10924 "ad_s390.cpp"
  }
}

uint storeBNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void storeCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STH_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STH_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STHY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (STH_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10968 "ad_s390.cpp"
  }
}

uint storeCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void storeINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (ST_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (ST_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (ST_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11012 "ad_s390.cpp"
  }
}

uint storeINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void storeLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (STG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11056 "ad_s390.cpp"
  }
}

uint storeLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void storePNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (STG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11100 "ad_s390.cpp"
  }
}

uint storePNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void storeFNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STE_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STE_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STEY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (STE_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11144 "ad_s390.cpp"
  }
}

uint storeFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void storeDNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STD_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STD_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STDY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (STD_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11188 "ad_s390.cpp"
  }
}

uint storeDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void prefetchAllocNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  {

#line 4703 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_pfd(0x02, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); 
#line 11205 "ad_s390.cpp"
  }
}

void memInitBNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 4715 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    if (Immediate::is_uimm12((long)opnd_array(1)->disp(ra_,this,idx1))) {
      __ z_mvi(Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()), opnd_array(2)->constant());
    } else {
      __ z_mviy(Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()), opnd_array(2)->constant());
    }
  
#line 11224 "ad_s390.cpp"
  }
}

void memInitCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2124 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit_inst(masm, (MVHHI_ZOPC /*primary()*/) |
                Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)),16,48) |
                Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1),20,48) |
                Assembler::simm16(opnd_array(2)->constant(),32,48));
  
#line 11242 "ad_s390.cpp"
  }
}

uint memInitCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void memInitINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2124 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit_inst(masm, (MVHI_ZOPC /*primary()*/) |
                Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)),16,48) |
                Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1),20,48) |
                Assembler::simm16(opnd_array(2)->constant(),32,48));
  
#line 11265 "ad_s390.cpp"
  }
}

uint memInitINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void memInitLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2124 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit_inst(masm, (MVGHI_ZOPC /*primary()*/) |
                Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)),16,48) |
                Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1),20,48) |
                Assembler::simm16(opnd_array(2)->constantL(),32,48));
  
#line 11288 "ad_s390.cpp"
  }
}

uint memInitLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void memInitPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2124 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit_inst(masm, (MVGHI_ZOPC /*primary()*/) |
                Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)),16,48) |
                Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1),20,48) |
                Assembler::simm16(opnd_array(2)->constant(),32,48));
  
#line 11311 "ad_s390.cpp"
  }
}

uint memInitPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void negL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 4783 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lcgr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */); 
#line 11329 "ad_s390.cpp"
  }
}

uint negL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11372 "ad_s390.cpp"
  }
}

uint loadNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadNKlassNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11415 "ad_s390.cpp"
  }
}

uint loadNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadNKlassCompactHeadersNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 4820 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ block_comment("load_narrow_klass_compact_c2 {");
    __ load_narrow_klass_compact_c2(opnd_array(0)->as_Register(ra_,this)/* dst */, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));
    __ block_comment("} load_narrow_klass_compact");
  
#line 11436 "ad_s390.cpp"
  }
}

void loadConNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4835 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral cOop = __ constant_oop_address((jobject)opnd_array(1)->constant());
    __ relocate(cOop.rspec(), 1);
    __ load_narrow_oop(opnd_array(0)->as_Register(ra_,this)/* dst */, (narrowOop)cOop.value());
  
#line 11452 "ad_s390.cpp"
  }
}

uint loadConNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConN0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (XGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,28,32));
  
#line 11474 "ad_s390.cpp"
  }
}

uint loadConN0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConNKlassNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4859 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral NKlass = __ constant_metadata_address((Metadata*)opnd_array(1)->constant());
    __ relocate(NKlass.rspec(), 1);
    __ load_narrow_klass(opnd_array(0)->as_Register(ra_,this)/* dst */, (Klass*)NKlass.value());
  
#line 11495 "ad_s390.cpp"
  }
}

uint loadConNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void decodeLoadNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11538 "ad_s390.cpp"
  }
}

uint decodeLoadNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void decodeLoadNKlassNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11581 "ad_s390.cpp"
  }
}

uint decodeLoadNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void decodeLoadConNKlassNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4897 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral NKlass = __ constant_metadata_address((Metadata*)opnd_array(1)->constant());
    __ relocate(NKlass.rspec(), 1);
    __ load_const(opnd_array(0)->as_Register(ra_,this)/* dst */, (Klass*)NKlass.value());
  
#line 11602 "ad_s390.cpp"
  }
}

uint decodeLoadConNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void decodeNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4915 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ oop_decoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, true); 
#line 11619 "ad_s390.cpp"
  }
}

void decodeKlassNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4925 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ decode_klass_not_null(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 11631 "ad_s390.cpp"
  }
}

void decodeN_NNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 4939 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ oop_decoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, false); 
#line 11643 "ad_s390.cpp"
  }
}

void loadBaseNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// baseImm
  {

#line 4947 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ get_oop_base(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constantL()); 
#line 11655 "ad_s390.cpp"
  }
}

void decodeN_baseNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {

#line 4962 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

      __ oop_decoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, true, opnd_array(2)->as_Register(ra_,this,idx2)/* base */,
                     (jlong)MacroAssembler::get_oop_base_pow2_offset((uint64_t)(intptr_t)CompressedOops::base()));
    
#line 11671 "ad_s390.cpp"
  }
}

void decodeN_NN_baseNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {

#line 4976 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

      __ oop_decoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, false, opnd_array(2)->as_Register(ra_,this,idx2)/* base */,
                     (jlong)MacroAssembler::get_oop_base_pow2_offset((uint64_t)(intptr_t)CompressedOops::base()));
    
#line 11687 "ad_s390.cpp"
  }
}

void encodePNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 5026 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ oop_encoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, true, Z_R1_scratch, -1, all_outs_are_Stores(this)); 
#line 11699 "ad_s390.cpp"
  }
}

void encodeKlassNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 5035 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ encode_klass_not_null(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 11711 "ad_s390.cpp"
  }
}

void encodeP_NNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 5049 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ oop_encoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, false, Z_R1_scratch, -1, all_outs_are_Stores(this)); 
#line 11723 "ad_s390.cpp"
  }
}

void encodeP_baseNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  {

#line 5061 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

      jlong offset = -(jlong)MacroAssembler::get_oop_base_pow2_offset
        (((uint64_t)(intptr_t)CompressedOops::base()) >> CompressedOops::shift());
      __ oop_encoder(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, true, opnd_array(2)->as_Register(ra_,this,idx2)/* base */, offset);
    
#line 11741 "ad_s390.cpp"
  }
}

void encodeP_NN_baseNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pow2_offset
  {

#line 5077 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ oop_encoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, false, opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(3)->constantL()); 
#line 11755 "ad_s390.cpp"
  }
}

void storeNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (ST_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (ST_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (ST_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11794 "ad_s390.cpp"
  }
}

uint storeNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void storeNKlassNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (ST_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (ST_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (ST_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11838 "ad_s390.cpp"
  }
}

uint storeNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void compN_iRegNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((CLR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (CLR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,12,16));
  
#line 11862 "ad_s390.cpp"
  }
}

uint compN_iRegNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void compN_iRegN_immNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 5164 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral cOop = __ constant_oop_address((jobject)opnd_array(2)->constant());
    __ relocate(cOop.rspec(), 1);
    __ compare_immediate_narrow_oop(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (narrowOop)cOop.value());
  
#line 11884 "ad_s390.cpp"
  }
}

uint compN_iRegN_immNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compNKlass_iRegN_immNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 5177 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral NKlass = __ constant_metadata_address((Metadata*)opnd_array(2)->constant());
    __ relocate(NKlass.rspec(), 1);
    __ compare_immediate_narrow_klass(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (Klass*)NKlass.value());
  
#line 11906 "ad_s390.cpp"
  }
}

uint compNKlass_iRegN_immNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compN_iRegN_immN0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((LTR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (LTR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,8,16) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,16));
  
#line 11930 "ad_s390.cpp"
  }
}

uint compN_iRegN_immN0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void membar_acquireNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 5206 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_acquire(); 
#line 11947 "ad_s390.cpp"
  }
}

uint membar_acquireNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_acquire_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 5206 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_acquire(); 
#line 11964 "ad_s390.cpp"
  }
}

uint membar_acquire_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_acquire_lockNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint membar_acquire_lockNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_releaseNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 5225 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_release(); 
#line 11993 "ad_s390.cpp"
  }
}

uint membar_releaseNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_release_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 5225 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_release(); 
#line 12010 "ad_s390.cpp"
  }
}

uint membar_release_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_release_lockNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint membar_release_lockNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_storeloadNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 5243 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_fence(); 
#line 12039 "ad_s390.cpp"
  }
}

uint membar_storeloadNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void membar_volatileNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 5252 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_fence(); 
#line 12056 "ad_s390.cpp"
  }
}

uint membar_volatileNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void unnecessary_membar_volatileNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint unnecessary_membar_volatileNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_fullNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 5271 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_fence(); 
#line 12085 "ad_s390.cpp"
  }
}

uint membar_fullNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void membar_CPUOrderNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

void membar_storestoreNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint membar_storestoreNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_storestore_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint membar_storestore_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castX2PNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 5302 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ lgr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 12133 "ad_s390.cpp"
  }
}

void castP2XNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 5311 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ lgr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 12145 "ad_s390.cpp"
  }
}

void stfSSDNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STD_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 12173 "ad_s390.cpp"
  }
}

void stfSSFNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STE_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 12201 "ad_s390.cpp"
  }
}

void cmovN_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2454 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* dst */);
    Register Rsrc = reg_to_register_object(opnd_array(4)->reg(ra_,this,idx4)/* src */);

    // Don't emit code if operands are identical (same register).
    if (Rsrc != Rdst) {
      Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();

      if (VM_Version::has_LoadStoreConditional()) {
        __ z_locgr(Rdst, Rsrc, cc);
      } else {
        // Branch if not (cmp cr).
        Label done;
        __ z_brc(Assembler::inverse_condition(cc), done);
        __ z_lgr(Rdst, Rsrc); // Used for int and long+ptr.
        __ bind(done);
      }
    }
  
#line 12234 "ad_s390.cpp"
  }
}

void cmovN_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2474 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* dst */);
    int      Csrc = opnd_array(4)->constant();
    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    Label done;
    // Branch if not (cmp cr).
    __ z_brc(Assembler::inverse_condition(cc), done);
    if (Csrc == 0) {
      // Don't set CC.
      __ clear_reg(Rdst, true, false);  // Use for int, long & ptr.
    } else {
      __ z_lghi(Rdst, Csrc); // Use for int, long & ptr.
    }
    __ bind(done);
  
#line 12263 "ad_s390.cpp"
  }
}

void cmovI_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2454 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* dst */);
    Register Rsrc = reg_to_register_object(opnd_array(4)->reg(ra_,this,idx4)/* src */);

    // Don't emit code if operands are identical (same register).
    if (Rsrc != Rdst) {
      Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();

      if (VM_Version::has_LoadStoreConditional()) {
        __ z_locgr(Rdst, Rsrc, cc);
      } else {
        // Branch if not (cmp cr).
        Label done;
        __ z_brc(Assembler::inverse_condition(cc), done);
        __ z_lgr(Rdst, Rsrc); // Used for int and long+ptr.
        __ bind(done);
      }
    }
  
#line 12296 "ad_s390.cpp"
  }
}

void cmovI_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2474 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* dst */);
    int      Csrc = opnd_array(4)->constant();
    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    Label done;
    // Branch if not (cmp cr).
    __ z_brc(Assembler::inverse_condition(cc), done);
    if (Csrc == 0) {
      // Don't set CC.
      __ clear_reg(Rdst, true, false);  // Use for int, long & ptr.
    } else {
      __ z_lghi(Rdst, Csrc); // Use for int, long & ptr.
    }
    __ bind(done);
  
#line 12325 "ad_s390.cpp"
  }
}

void cmovP_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2454 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* dst */);
    Register Rsrc = reg_to_register_object(opnd_array(4)->reg(ra_,this,idx4)/* src */);

    // Don't emit code if operands are identical (same register).
    if (Rsrc != Rdst) {
      Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();

      if (VM_Version::has_LoadStoreConditional()) {
        __ z_locgr(Rdst, Rsrc, cc);
      } else {
        // Branch if not (cmp cr).
        Label done;
        __ z_brc(Assembler::inverse_condition(cc), done);
        __ z_lgr(Rdst, Rsrc); // Used for int and long+ptr.
        __ bind(done);
      }
    }
  
#line 12358 "ad_s390.cpp"
  }
}

void cmovP_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2474 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* dst */);
    int      Csrc = opnd_array(4)->constant();
    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    Label done;
    // Branch if not (cmp cr).
    __ z_brc(Assembler::inverse_condition(cc), done);
    if (Csrc == 0) {
      // Don't set CC.
      __ clear_reg(Rdst, true, false);  // Use for int, long & ptr.
    } else {
      __ z_lghi(Rdst, Csrc); // Use for int, long & ptr.
    }
    __ bind(done);
  
#line 12387 "ad_s390.cpp"
  }
}

void cmovF_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 5398 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // Don't emit code if operands are identical (same register).
    if (opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */!= opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */) {
      Label done;
      __ z_brc(Assembler::inverse_float_condition((Assembler::branch_condition)opnd_array(1)->ccode()), done);
      __ z_ler(opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */, opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */);
      __ bind(done);
    }
  
#line 12410 "ad_s390.cpp"
  }
}

void cmovD_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 5415 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // Don't emit code if operands are identical (same register).
    if (opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */!= opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */) {
      Label done;
      __ z_brc(Assembler::inverse_float_condition((Assembler::branch_condition)opnd_array(1)->ccode()), done);
      __ z_ldr(opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */, opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */);
      __ bind(done);
    }
  
#line 12433 "ad_s390.cpp"
  }
}

void cmovL_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2454 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* dst */);
    Register Rsrc = reg_to_register_object(opnd_array(4)->reg(ra_,this,idx4)/* src */);

    // Don't emit code if operands are identical (same register).
    if (Rsrc != Rdst) {
      Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();

      if (VM_Version::has_LoadStoreConditional()) {
        __ z_locgr(Rdst, Rsrc, cc);
      } else {
        // Branch if not (cmp cr).
        Label done;
        __ z_brc(Assembler::inverse_condition(cc), done);
        __ z_lgr(Rdst, Rsrc); // Used for int and long+ptr.
        __ bind(done);
      }
    }
  
#line 12466 "ad_s390.cpp"
  }
}

void cmovL_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2474 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* dst */);
    int      Csrc = opnd_array(4)->constantL();
    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    Label done;
    // Branch if not (cmp cr).
    __ z_brc(Assembler::inverse_condition(cc), done);
    if (Csrc == 0) {
      // Don't set CC.
      __ clear_reg(Rdst, true, false);  // Use for int, long & ptr.
    } else {
      __ z_lghi(Rdst, Csrc); // Use for int, long & ptr.
    }
    __ bind(done);
  
#line 12495 "ad_s390.cpp"
  }
}

void tlsLoadPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint tlsLoadPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void checkCastPPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint checkCastPPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castPPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castPPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castIINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castIINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castLLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castLLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castFFNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castFFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castDDNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castDDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castVVNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castVVNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void compareAndSwapI_boolNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  {

#line 2506 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    __ z_cs(Rcomp, Rnew, 0, Raddr);
  
#line 12611 "ad_s390.cpp"
  }
  {

#line 2490 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rres = reg_to_register_object(opnd_array(0)->reg(ra_,this)/* res */);

    if (VM_Version::has_LoadStoreConditional()) {
      __ load_const_optimized(Z_R0_scratch, 0L); // false (failed)
      __ load_const_optimized(Rres, 1L);         // true  (succeed)
      __ z_locgr(Rres, Z_R0_scratch, Assembler::bcondNotEqual);
    } else {
      Label done;
      __ load_const_optimized(Rres, 0L); // false (failed)
      __ z_brne(done);                   // Assume true to be the common case.
      __ load_const_optimized(Rres, 1L); // true  (succeed)
      __ bind(done);
    }
  
#line 12631 "ad_s390.cpp"
  }
}

uint compareAndSwapI_boolNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void compareAndSwapL_boolNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  {

#line 2514 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    __ z_csg(Rcomp, Rnew, 0, Raddr);
  
#line 12656 "ad_s390.cpp"
  }
  {

#line 2490 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rres = reg_to_register_object(opnd_array(0)->reg(ra_,this)/* res */);

    if (VM_Version::has_LoadStoreConditional()) {
      __ load_const_optimized(Z_R0_scratch, 0L); // false (failed)
      __ load_const_optimized(Rres, 1L);         // true  (succeed)
      __ z_locgr(Rres, Z_R0_scratch, Assembler::bcondNotEqual);
    } else {
      Label done;
      __ load_const_optimized(Rres, 0L); // false (failed)
      __ z_brne(done);                   // Assume true to be the common case.
      __ load_const_optimized(Rres, 1L); // true  (succeed)
      __ bind(done);
    }
  
#line 12676 "ad_s390.cpp"
  }
}

uint compareAndSwapL_boolNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 18, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 18);
}

void compareAndSwapP_boolNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  {

#line 2514 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    __ z_csg(Rcomp, Rnew, 0, Raddr);
  
#line 12701 "ad_s390.cpp"
  }
  {

#line 2490 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rres = reg_to_register_object(opnd_array(0)->reg(ra_,this)/* res */);

    if (VM_Version::has_LoadStoreConditional()) {
      __ load_const_optimized(Z_R0_scratch, 0L); // false (failed)
      __ load_const_optimized(Rres, 1L);         // true  (succeed)
      __ z_locgr(Rres, Z_R0_scratch, Assembler::bcondNotEqual);
    } else {
      Label done;
      __ load_const_optimized(Rres, 0L); // false (failed)
      __ z_brne(done);                   // Assume true to be the common case.
      __ load_const_optimized(Rres, 1L); // true  (succeed)
      __ bind(done);
    }
  
#line 12721 "ad_s390.cpp"
  }
}

uint compareAndSwapP_boolNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 18, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 18);
}

void compareAndSwapN_boolNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  {

#line 2506 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    __ z_cs(Rcomp, Rnew, 0, Raddr);
  
#line 12746 "ad_s390.cpp"
  }
  {

#line 2490 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rres = reg_to_register_object(opnd_array(0)->reg(ra_,this)/* res */);

    if (VM_Version::has_LoadStoreConditional()) {
      __ load_const_optimized(Z_R0_scratch, 0L); // false (failed)
      __ load_const_optimized(Rres, 1L);         // true  (succeed)
      __ z_locgr(Rres, Z_R0_scratch, Assembler::bcondNotEqual);
    } else {
      Label done;
      __ load_const_optimized(Rres, 0L); // false (failed)
      __ z_brne(done);                   // Assume true to be the common case.
      __ load_const_optimized(Rres, 1L); // true  (succeed)
      __ bind(done);
    }
  
#line 12766 "ad_s390.cpp"
  }
}

uint compareAndSwapN_boolNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void addI_mem_imm8_atomic_no_resNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2112 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int      disp = opnd_array(1)->disp(ra_,this,idx1);
    Register base = reg_to_register_object(opnd_array(1)->base(ra_,this,idx1));
    int      con  = opnd_array(2)->constant();

    assert(VM_Version::has_MemWithImmALUOps(), "unsupported CPU");
    z_emit_inst(masm, (ASI_ZOPC /*primary()*/) |
                Assembler::regz(base,16,48) |
                Assembler::simm20(disp) |
                Assembler::simm8(con,8,48));
  
#line 12794 "ad_s390.cpp"
  }
}

uint addI_mem_imm8_atomic_no_resNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addI_mem_imm16_atomicNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {

#line 5594 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(3)->as_Register(ra_,this,idx3)/* dst */;
    Register Rtmp = opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */;
    int      Isrc = opnd_array(2)->constant();
    Label    retry;

    // Iterate until update with incremented value succeeds.
    __ z_lgf(Rdst, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));    // current contents
    __ bind(retry);
      // Calculate incremented value.
      if (VM_Version::has_DistinctOpnds()) {
        __ z_ahik(Rtmp, Rdst, Isrc);
      } else {
        __ z_lr(Rtmp, Rdst);
        __ z_ahi(Rtmp, Isrc);
      }
      // Swap into memory location.
      __ z_csy(Rdst, Rtmp, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); // Try to store new value.
    __ z_brne(retry);                      // Yikes, concurrent update, need to retry.
  
#line 12833 "ad_s390.cpp"
  }
}

void addI_mem_imm32_atomicNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {

#line 5629 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(3)->as_Register(ra_,this,idx3)/* dst */;
    Register Rtmp = opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */;
    int      Isrc = opnd_array(2)->constant();
    Label    retry;

    // Iterate until update with incremented value succeeds.
    __ z_lgf(Rdst, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));    // current contents
    __ bind(retry);
      // Calculate incremented value.
      __ z_lr(Rtmp, Rdst);
      __ z_afi(Rtmp, Isrc);
      // Swap into memory location.
      __ z_csy(Rdst, Rtmp, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); // Try to store new value.
    __ z_brne(retry);                      // Yikes, concurrent update, need to retry.
  
#line 12863 "ad_s390.cpp"
  }
}

void addI_mem_reg_atomicNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {

#line 5659 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rsrc = opnd_array(2)->as_Register(ra_,this,idx2)/* src */;
    Register Rdst = opnd_array(3)->as_Register(ra_,this,idx3)/* dst */;
    Register Rtmp = opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */;
    Label    retry;

    // Iterate until update with incremented value succeeds.
    __ z_lgf(Rdst, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));  // current contents
    __ bind(retry);
      // Calculate incremented value.
      if (VM_Version::has_DistinctOpnds()) {
        __ z_ark(Rtmp, Rdst, Rsrc);
      } else {
        __ z_lr(Rtmp, Rdst);
        __ z_ar(Rtmp, Rsrc);
      }
      __ z_csy(Rdst, Rtmp, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); // Try to store new value.
    __ z_brne(retry);                      // Yikes, concurrent update, need to retry.
  
#line 12896 "ad_s390.cpp"
  }
}

void addL_mem_imm8_atomic_no_resNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2112 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int      disp = opnd_array(1)->disp(ra_,this,idx1);
    Register base = reg_to_register_object(opnd_array(1)->base(ra_,this,idx1));
    int      con  = opnd_array(2)->constantL();

    assert(VM_Version::has_MemWithImmALUOps(), "unsupported CPU");
    z_emit_inst(masm, (AGSI_ZOPC /*primary()*/) |
                Assembler::regz(base,16,48) |
                Assembler::simm20(disp) |
                Assembler::simm8(con,8,48));
  
#line 12919 "ad_s390.cpp"
  }
}

uint addL_mem_imm8_atomic_no_resNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_mem_imm16_atomicNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {

#line 5714 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(3)->as_Register(ra_,this,idx3)/* dst */;
    Register Rtmp = opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */;
    int      Isrc = opnd_array(2)->constantL();
    Label    retry;

    // Iterate until update with incremented value succeeds.
    __ z_lg(Rdst, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));  // current contents
    __ bind(retry);
      // Calculate incremented value.
      if (VM_Version::has_DistinctOpnds()) {
        __ z_aghik(Rtmp, Rdst, Isrc);
      } else {
        __ z_lgr(Rtmp, Rdst);
        __ z_aghi(Rtmp, Isrc);
      }
      __ z_csg(Rdst, Rtmp, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); // Try to store new value.
    __ z_brne(retry);                      // Yikes, concurrent update, need to retry.
  
#line 12957 "ad_s390.cpp"
  }
}

void addL_mem_imm32_atomicNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {

#line 5748 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(3)->as_Register(ra_,this,idx3)/* dst */;
    Register Rtmp = opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */;
    int      Isrc = opnd_array(2)->constantL();
    Label    retry;

    // Iterate until update with incremented value succeeds.
    __ z_lg(Rdst, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));  // current contents
    __ bind(retry);
      // Calculate incremented value.
      __ z_lgr(Rtmp, Rdst);
      __ z_agfi(Rtmp, Isrc);
      __ z_csg(Rdst, Rtmp, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); // Try to store new value.
    __ z_brne(retry);                      // Yikes, concurrent update, need to retry.
  
#line 12986 "ad_s390.cpp"
  }
}

void addL_mem_reg_atomicNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {

#line 5777 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rsrc = opnd_array(2)->as_Register(ra_,this,idx2)/* src */;
    Register Rdst = opnd_array(3)->as_Register(ra_,this,idx3)/* dst */;
    Register Rtmp = opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */;
    Label    retry;

    // Iterate until update with incremented value succeeds.
    __ z_lg(Rdst, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));  // current contents
    __ bind(retry);
      // Calculate incremented value.
      if (VM_Version::has_DistinctOpnds()) {
        __ z_agrk(Rtmp, Rdst, Rsrc);
      } else {
        __ z_lgr(Rtmp, Rdst);
        __ z_agr(Rtmp, Rsrc);
      }
      __ z_csg(Rdst, Rtmp, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); // Try to store new value.
    __ z_brne(retry);                      // Yikes, concurrent update, need to retry.
  
#line 13019 "ad_s390.cpp"
  }
}

void addI_mem_reg_atomic_z196Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 5806 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laa(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); 
#line 13032 "ad_s390.cpp"
  }
}

uint addI_mem_reg_atomic_z196Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_mem_reg_atomic_z196Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 5817 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laag(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); 
#line 13050 "ad_s390.cpp"
  }
}

uint addL_mem_reg_atomic_z196Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void xchgI_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 2522 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* dst */);
    Register Rtmp = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* tmp */);
    guarantee(Rdst != Rtmp, "Fix match rule to use TEMP_DEF");
    Label    retry;

    // Iterate until swap succeeds.
    __ z_llgf(Rtmp, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));  // current contents
    __ bind(retry);
      // Calculate incremented value.
      __ z_csy(Rtmp, Rdst, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); // Try to store new value.
      __ z_brne(retry);                    // Yikes, concurrent update, need to retry.
    __ z_lgr(Rdst, Rtmp);                  // Exchanged value from memory is return value.
  
#line 13082 "ad_s390.cpp"
  }
}

void xchgL_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 2537 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* dst */);
    Register Rtmp = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* tmp */);
    guarantee(Rdst != Rtmp, "Fix match rule to use TEMP_DEF");
    Label    retry;

    // Iterate until swap succeeds.
    __ z_lg(Rtmp, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));  // current contents
    __ bind(retry);
      // Calculate incremented value.
      __ z_csg(Rtmp, Rdst, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); // Try to store new value.
      __ z_brne(retry);                    // Yikes, concurrent update, need to retry.
    __ z_lgr(Rdst, Rtmp);                  // Exchanged value from memory is return value.
  
#line 13109 "ad_s390.cpp"
  }
}

void xchgN_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 2522 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* dst */);
    Register Rtmp = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* tmp */);
    guarantee(Rdst != Rtmp, "Fix match rule to use TEMP_DEF");
    Label    retry;

    // Iterate until swap succeeds.
    __ z_llgf(Rtmp, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));  // current contents
    __ bind(retry);
      // Calculate incremented value.
      __ z_csy(Rtmp, Rdst, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); // Try to store new value.
      __ z_brne(retry);                    // Yikes, concurrent update, need to retry.
    __ z_lgr(Rdst, Rtmp);                  // Exchanged value from memory is return value.
  
#line 13136 "ad_s390.cpp"
  }
}

void xchgP_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 2537 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* dst */);
    Register Rtmp = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* tmp */);
    guarantee(Rdst != Rtmp, "Fix match rule to use TEMP_DEF");
    Label    retry;

    // Iterate until swap succeeds.
    __ z_lg(Rtmp, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));  // current contents
    __ bind(retry);
      // Calculate incremented value.
      __ z_csg(Rtmp, Rdst, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); // Try to store new value.
      __ z_brne(retry);                    // Yikes, concurrent update, need to retry.
    __ z_lgr(Rdst, Rtmp);                  // Exchanged value from memory is return value.
  
#line 13163 "ad_s390.cpp"
  }
}

void addI_reg_reg_CISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((AR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (AR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 13182 "ad_s390.cpp"
  }
}

void addI_reg_reg_RISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2020 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((ARK_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (ARK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32));
  
#line 13201 "ad_s390.cpp"
  }
}

uint addI_reg_reg_RISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_reg_imm16_CISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2028 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (AHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::simm16(opnd_array(2)->constant(),16,32));
  
#line 13224 "ad_s390.cpp"
  }
}

void addI_reg_imm16_RISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2042 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AHIK_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (AHIK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm16(opnd_array(2)->constant(),16,48));
  
#line 13243 "ad_s390.cpp"
  }
}

void addI_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2050 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (AFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::simm32(opnd_array(2)->constant(),16,48));
  
#line 13261 "ad_s390.cpp"
  }
}

uint addI_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addI_reg_imm12Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2088 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(masm, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,32) |
             Assembler::uimm12(opnd_array(2)->constant(),20,32));
  
#line 13285 "ad_s390.cpp"
  }
}

uint addI_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_reg_imm20Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2104 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 13308 "ad_s390.cpp"
  }
}

uint addI_reg_imm20Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addI_reg_reg_imm12Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 2079 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(masm, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32) |
             Assembler::uimm12(opnd_array(3)->constant(),20,32));
  
#line 13334 "ad_s390.cpp"
  }
}

uint addI_reg_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_reg_reg_imm20Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 2096 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(opnd_array(3)->constant()));
  
#line 13359 "ad_s390.cpp"
  }
}

uint addI_reg_reg_imm20Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addI_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (A_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (A_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (AY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (A_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 13403 "ad_s390.cpp"
  }
}

void addI_Reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (A_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (A_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (AY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (A_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 13442 "ad_s390.cpp"
  }
}

void addI_mem_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2112 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int      disp = opnd_array(1)->disp(ra_,this,idx1);
    Register base = reg_to_register_object(opnd_array(1)->base(ra_,this,idx1));
    int      con  = opnd_array(2)->constant();

    assert(VM_Version::has_MemWithImmALUOps(), "unsupported CPU");
    z_emit_inst(masm, (ASI_ZOPC /*primary()*/) |
                Assembler::regz(base,16,48) |
                Assembler::simm20(disp) |
                Assembler::simm8(con,8,48));
  
#line 13465 "ad_s390.cpp"
  }
}

uint addI_mem_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_reg_regINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (AGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 13488 "ad_s390.cpp"
  }
}

uint addL_reg_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_regI_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (AGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 13511 "ad_s390.cpp"
  }
}

uint addL_reg_regI_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_reg_CISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (AGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 13534 "ad_s390.cpp"
  }
}

void addL_reg_reg_RISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2020 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGRK_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (AGRK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32));
  
#line 13553 "ad_s390.cpp"
  }
}

uint addL_reg_reg_RISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_imm12Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2088 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(masm, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,32) |
             Assembler::uimm12(opnd_array(2)->constantL(),20,32));
  
#line 13577 "ad_s390.cpp"
  }
}

uint addL_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_imm20Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2104 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,48) |
             Assembler::simm20(opnd_array(2)->constantL()));
  
#line 13600 "ad_s390.cpp"
  }
}

uint addL_reg_imm20Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2050 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (AGFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::simm32(opnd_array(2)->constantL(),16,48));
  
#line 13623 "ad_s390.cpp"
  }
}

uint addL_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_reg_imm16_CISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2028 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (AGHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::simm16(opnd_array(2)->constantL(),16,32));
  
#line 13646 "ad_s390.cpp"
  }
}

void addL_reg_imm16_RISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2042 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGHIK_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (AGHIK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm16(opnd_array(2)->constantL(),16,48));
  
#line 13665 "ad_s390.cpp"
  }
}

uint addL_reg_imm16_RISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_Reg_memINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (AGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (AGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (AGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (AGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 13709 "ad_s390.cpp"
  }
}

uint addL_Reg_memINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void addL_Reg_memI_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (AGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (AGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (AGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (AGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 13753 "ad_s390.cpp"
  }
}

uint addL_Reg_memI_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void addL_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (AG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (AG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (AG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (AG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 13797 "ad_s390.cpp"
  }
}

uint addL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void addL_Reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (AG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (AG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (AG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (AG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 13841 "ad_s390.cpp"
  }
}

uint addL_Reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void addL_reg_reg_imm12Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 2079 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(masm, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32) |
             Assembler::uimm12(opnd_array(3)->constantL(),20,32));
  
#line 13867 "ad_s390.cpp"
  }
}

uint addL_reg_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_reg_imm20Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 2096 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(opnd_array(3)->constantL()));
  
#line 13892 "ad_s390.cpp"
  }
}

uint addL_reg_reg_imm20Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_mem_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2112 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int      disp = opnd_array(1)->disp(ra_,this,idx1);
    Register base = reg_to_register_object(opnd_array(1)->base(ra_,this,idx1));
    int      con  = opnd_array(2)->constantL();

    assert(VM_Version::has_MemWithImmALUOps(), "unsupported CPU");
    z_emit_inst(masm, (AGSI_ZOPC /*primary()*/) |
                Assembler::regz(base,16,48) |
                Assembler::simm20(disp) |
                Assembler::simm8(con,8,48));
  
#line 13920 "ad_s390.cpp"
  }
}

uint addL_mem_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addP_reg_reg_LANode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2079 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(masm, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32) |
             Assembler::uimm12((0x0),20,32));
  
#line 13945 "ad_s390.cpp"
  }
}

uint addP_reg_reg_LANode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_reg_reg_CISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((ALGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (ALGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 13968 "ad_s390.cpp"
  }
}

void addP_reg_reg_RISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2020 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((ALGRK_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (ALGRK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32));
  
#line 13987 "ad_s390.cpp"
  }
}

void addP_reg_imm12Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2088 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(masm, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,32) |
             Assembler::uimm12(opnd_array(2)->constantL(),20,32));
  
#line 14006 "ad_s390.cpp"
  }
}

uint addP_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_reg_imm16_CISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2028 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (AGHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::simm16(opnd_array(2)->constantL(),16,32));
  
#line 14029 "ad_s390.cpp"
  }
}

void addP_reg_imm16_RISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2042 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((ALGHSIK_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (ALGHSIK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm16(opnd_array(2)->constantL(),16,48));
  
#line 14048 "ad_s390.cpp"
  }
}

void addP_reg_imm20Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2104 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,48) |
             Assembler::simm20(opnd_array(2)->constantL()));
  
#line 14066 "ad_s390.cpp"
  }
}

uint addP_reg_imm20Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addP_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2050 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (AGFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::simm32(opnd_array(2)->constantL(),16,48));
  
#line 14089 "ad_s390.cpp"
  }
}

void addP_reg_reg_imm12Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 2079 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(masm, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32) |
             Assembler::uimm12(opnd_array(3)->constantL(),20,32));
  
#line 14110 "ad_s390.cpp"
  }
}

uint addP_reg_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_regN_reg_imm12Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 2079 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(masm, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32) |
             Assembler::uimm12(opnd_array(3)->constantL(),20,32));
  
#line 14136 "ad_s390.cpp"
  }
}

uint addP_regN_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_reg_reg_imm20Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 2096 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(opnd_array(3)->constantL()));
  
#line 14161 "ad_s390.cpp"
  }
}

void addP_regN_reg_imm20Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 2096 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(opnd_array(3)->constantL()));
  
#line 14181 "ad_s390.cpp"
  }
}

void addP_mem_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2112 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int      disp = opnd_array(1)->disp(ra_,this,idx1);
    Register base = reg_to_register_object(opnd_array(1)->base(ra_,this,idx1));
    int      con  = opnd_array(2)->constantL();

    assert(VM_Version::has_MemWithImmALUOps(), "unsupported CPU");
    z_emit_inst(masm, (AGSI_ZOPC /*primary()*/) |
                Assembler::regz(base,16,48) |
                Assembler::simm20(disp) |
                Assembler::simm8(con,8,48));
  
#line 14204 "ad_s390.cpp"
  }
}

uint addP_mem_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void subI_reg_reg_CISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((SR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (SR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 14228 "ad_s390.cpp"
  }
}

void subI_reg_reg_RISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2020 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SRK_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (SRK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32));
  
#line 14247 "ad_s390.cpp"
  }
}

uint subI_reg_reg_RISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subI_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (S_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (S_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (SY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (S_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 14291 "ad_s390.cpp"
  }
}

void subI_zero_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 6374 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lcr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */); 
#line 14304 "ad_s390.cpp"
  }
}

uint subI_zero_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void subL_reg_reg_CISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (SGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 14327 "ad_s390.cpp"
  }
}

void subL_reg_reg_RISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2020 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SGRK_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (SGRK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32));
  
#line 14346 "ad_s390.cpp"
  }
}

uint subL_reg_reg_RISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subL_reg_regI_CISCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (SGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 14369 "ad_s390.cpp"
  }
}

uint subL_reg_regI_CISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subL_Reg_memINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (SGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (SGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (SGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (SGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 14413 "ad_s390.cpp"
  }
}

uint subL_Reg_memINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void subL_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (SG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (SG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (SG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (SG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 14457 "ad_s390.cpp"
  }
}

uint subL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void mulI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (MSR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 14480 "ad_s390.cpp"
  }
}

uint mulI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulI_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2028 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (MHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::simm16(opnd_array(2)->constant(),16,32));
  
#line 14503 "ad_s390.cpp"
  }
}

void mulI_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2050 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (MSFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::simm32(opnd_array(2)->constant(),16,48));
  
#line 14521 "ad_s390.cpp"
  }
}

uint mulI_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulI_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MS_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (MS_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (MSY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (MS_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 14565 "ad_s390.cpp"
  }
}

void mulI_Reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MS_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (MS_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (MSY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (MS_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 14604 "ad_s390.cpp"
  }
}

void mulL_reg_regINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (MSGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 14622 "ad_s390.cpp"
  }
}

void mulL_reg_regI_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (MSGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 14640 "ad_s390.cpp"
  }
}

void mulL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (MSGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 14658 "ad_s390.cpp"
  }
}

uint mulL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulL_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2028 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MGHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (MGHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::simm16(opnd_array(2)->constantL(),16,32));
  
#line 14681 "ad_s390.cpp"
  }
}

void mulL_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2050 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSGFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (MSGFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::simm32(opnd_array(2)->constantL(),16,48));
  
#line 14699 "ad_s390.cpp"
  }
}

uint mulL_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulL_Reg_memINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MSGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (MSGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (MSGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (MSGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 14743 "ad_s390.cpp"
  }
}

uint mulL_Reg_memINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void mulL_Reg_memI_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MSGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (MSGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (MSGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (MSGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 14787 "ad_s390.cpp"
  }
}

uint mulL_Reg_memI_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void mulL_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MSG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (MSG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (MSG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (MSG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 14831 "ad_s390.cpp"
  }
}

uint mulL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void mulL_Reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MSG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (MSG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (MSG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (MSG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 14875 "ad_s390.cpp"
  }
}

uint mulL_Reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void mulHiL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// Rsrc1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// Rsrc2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// Rdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// Rtmp1
  {

#line 6553 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register dst  = opnd_array(3)->as_Register(ra_,this,idx3)/* Rdst */;
    Register src1 = opnd_array(1)->as_Register(ra_,this,idx1)/* Rsrc1 */;
    Register src2 = opnd_array(2)->as_Register(ra_,this,idx2)/* Rsrc2 */;
    Register tmp1 = opnd_array(4)->as_Register(ra_,this,idx4)/* Rtmp1 */;
    Register tmp2 = opnd_array(3)->as_Register(ra_,this,idx3)/* Rdst */;
    // z/Architecture has only unsigned multiply (64 * 64 -> 128).
    // implementing mulhs(a,b) = mulhu(a,b) - (a & (b>>63)) - (b & (a>>63))
    __ z_srag(tmp2, src1, 63);  // a>>63
    __ z_srag(tmp1, src2, 63);  // b>>63
    __ z_ngr(tmp2, src2);       // b & (a>>63)
    __ z_ngr(tmp1, src1);       // a & (b>>63)
    __ z_agr(tmp1, tmp2);       // ((a & (b>>63)) + (b & (a>>63)))
    __ z_mlgr(dst, src2);       // tricky: 128-bit product is written to even/odd pair (dst,src1),
                                //         multiplicand is taken from oddReg (src1), multiplier in src2.
    __ z_sgr(dst, tmp1);
  
#line 14911 "ad_s390.cpp"
  }
}

void divModI_reg_divmodNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst2
  {

#line 6582 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register d1s1 = opnd_array(1)->as_Register(ra_,this,idx1)/* dst1src1 */;
    Register d2   = as_Register(Z_R4_enc);
    Register s2   = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;

    assert_different_registers(d1s1, s2);

    Label do_div, done_div;
    if (VM_Version::has_CompareBranch()) {
      __ z_cij(s2, -1, Assembler::bcondNotEqual, do_div);
    } else {
      __ z_chi(s2, -1);
      __ z_brne(do_div);
    }
    __ z_lcr(d1s1, d1s1);
    __ clear_reg(d2, false, false);
    __ z_bru(done_div);
    __ bind(do_div);
    __ z_lgfr(d1s1, d1s1);
    __ z_dsgfr(d2, s2);
    __ bind(done_div);
  
#line 14945 "ad_s390.cpp"
  }
}

uint divModI_reg_divmodNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= (VM_Version::has_CompareBranch() ? 24 : 26), "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : (VM_Version::has_CompareBranch() ? 24 : 26));
}

void divI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 6615 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register a = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    Register b = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;
    Register t = opnd_array(0)->as_Register(ra_,this)/* dst */;

    assert_different_registers(t, b);

    Label do_div, done_div;
    if (VM_Version::has_CompareBranch()) {
      __ z_cij(b, -1, Assembler::bcondNotEqual, do_div);
    } else {
      __ z_chi(b, -1);
      __ z_brne(do_div);
    }
    __ z_lcr(t, a);
    __ z_bru(done_div);
    __ bind(do_div);
    __ z_lgfr(t, a);
    __ z_dsgfr(t->predecessor()/* t is odd part of a register pair. */, b);
    __ bind(done_div);
  
#line 14983 "ad_s390.cpp"
  }
}

uint divI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= (VM_Version::has_CompareBranch() ? 20 : 22), "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : (VM_Version::has_CompareBranch() ? 20 : 22));
}

void divI_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 6646 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // No sign extension of Rdividend needed here.
    if (opnd_array(2)->constant()!= -1) {
      __ z_lghi(Z_R0_scratch, opnd_array(2)->constant());
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
      __ z_dsgfr(opnd_array(0)->as_Register(ra_,this)/* dst */->predecessor()/* Dst is odd part of a register pair. */, Z_R0_scratch);
    } else {
      __ z_lcr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
  
#line 15010 "ad_s390.cpp"
  }
}

void udivI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// r5_rodd_dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// r4_reven_tmp
  {

#line 6667 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register b = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;
    Register r4_reven_tmp = opnd_array(3)->as_Register(ra_,this,idx3)/* r4_reven_tmp */;
    Register r5_rodd_dst  = opnd_array(1)->as_Register(ra_,this,idx1)/* r5_rodd_dst */;
    assert_different_registers(r4_reven_tmp, r5_rodd_dst, b);
    assert(r4_reven_tmp->successor() == r5_rodd_dst, "even-odd pair required for the instruction");

    __ block_comment("unsigned_div_int {");
    __ z_lhi(r4_reven_tmp, 0); // make upper 32bits 0
    __ z_dlr(r4_reven_tmp, b);
    __ block_comment("} unsigned_div_int");
  
#line 15035 "ad_s390.cpp"
  }
}

void divModL_reg_divmodNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst2
  {

#line 6689 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register d1s1 = opnd_array(1)->as_Register(ra_,this,idx1)/* dst1src1 */;
    Register d2   = as_Register(Z_R4_enc);
    Register s2   = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;

    Label do_div, done_div;
    if (VM_Version::has_CompareBranch()) {
      __ z_cgij(s2, -1, Assembler::bcondNotEqual, do_div);
    } else {
      __ z_cghi(s2, -1);
      __ z_brne(do_div);
    }
    __ z_lcgr(d1s1, d1s1);
    // indicate unused result
    (void) __ clear_reg(d2, true, false);
    __ z_bru(done_div);
    __ bind(do_div);
    __ z_dsgr(d2, s2);
    __ bind(done_div);
  
#line 15067 "ad_s390.cpp"
  }
}

uint divModL_reg_divmodNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= (VM_Version::has_CompareBranch() ? 22 : 24), "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : (VM_Version::has_CompareBranch() ? 22 : 24));
}

void divL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 6719 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register b = opnd_array(2)->as_Register(ra_,this,idx2)/* src */;
    Register t = opnd_array(1)->as_Register(ra_,this,idx1)/* dst */;

    Label done_div;
    __ z_lcgr(t, t);    // Does no harm. divisor is in other register.
    if (VM_Version::has_CompareBranch()) {
      __ z_cgij(b, -1, Assembler::bcondEqual, done_div);
    } else {
      __ z_cghi(b, -1);
      __ z_bre(done_div);
    }
    __ z_lcgr(t, t);    // Restore sign.
    __ z_dsgr(t->predecessor()/* t is odd part of a register pair. */, b);
    __ bind(done_div);
  
#line 15100 "ad_s390.cpp"
  }
}

uint divL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= (VM_Version::has_CompareBranch() ? 18 : 20), "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : (VM_Version::has_CompareBranch() ? 18 : 20));
}

void udivL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// r5_rodd_dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// r4_reven_tmp
  {

#line 6747 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register b            = opnd_array(2)->as_Register(ra_,this,idx2)/* src */;
    Register r5_rodd_dst  = opnd_array(1)->as_Register(ra_,this,idx1)/* r5_rodd_dst */;
    Register r4_reven_tmp = opnd_array(3)->as_Register(ra_,this,idx3)/* r4_reven_tmp */;
    assert_different_registers(r5_rodd_dst, r4_reven_tmp, b);
    __ block_comment("unsigned_div_long {");
    __ z_lghi(r4_reven_tmp, 0); // make upper 64bits 0
    __ z_dlgr(r4_reven_tmp, b);
    __ block_comment("} unsigned_div_long");
  
#line 15128 "ad_s390.cpp"
  }
}

void divL_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 6767 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    if (opnd_array(2)->constantL()!= -1) {
      __ z_lghi(Z_R0_scratch, opnd_array(2)->constantL());
      __ lgr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
      __ z_dsgr(opnd_array(0)->as_Register(ra_,this)/* dst */->predecessor()/* Dst is odd part of a register pair. */, Z_R0_scratch);
    } else {
      __ z_lcgr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
  
#line 15149 "ad_s390.cpp"
  }
}

void modI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 6789 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register a = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    Register b = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;
    Register t = opnd_array(0)->as_Register(ra_,this)/* dst */;
    assert_different_registers(t->successor(), b);

    Label do_div, done_div;

    if ((t->encoding() != b->encoding()) && (t->encoding() != a->encoding())) {
      (void) __ clear_reg(t, true, false);  // Does no harm. Operands are in other regs.
      if (VM_Version::has_CompareBranch()) {
        __ z_cij(b, -1, Assembler::bcondEqual, done_div);
      } else {
        __ z_chi(b, -1);
        __ z_bre(done_div);
      }
      __ z_lgfr(t->successor(), a);
      __ z_dsgfr(t/* t is even part of a register pair. */, b);
    } else {
      if (VM_Version::has_CompareBranch()) {
        __ z_cij(b, -1, Assembler::bcondNotEqual, do_div);
      } else {
        __ z_chi(b, -1);
        __ z_brne(do_div);
      }
      __ clear_reg(t, true, false);
      __ z_bru(done_div);
      __ bind(do_div);
      __ z_lgfr(t->successor(), a);
      __ z_dsgfr(t/* t is even part of a register pair. */, b);
    }
    __ bind(done_div);
  
#line 15194 "ad_s390.cpp"
  }
}

void umodI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// r4_reven_dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// r5_rodd_tmp
  {

#line 6834 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register b            = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;
    Register r4_reven_dst = opnd_array(1)->as_Register(ra_,this,idx1)/* r4_reven_dst */;
    Register r5_rodd_tmp  = opnd_array(3)->as_Register(ra_,this,idx3)/* r5_rodd_tmp */;
    assert_different_registers(r4_reven_dst, r5_rodd_tmp, b);
    assert(r4_reven_dst->successor() == r5_rodd_tmp, "must be an even-odd pair");

    __ block_comment("unsigned_mod_integer {");
    __ z_lr(r5_rodd_tmp, r4_reven_dst); // load lower 32bits in odd register
    __ z_lhi(r4_reven_dst, 0);          // make upper 32bits 0
    __ z_dlr(r4_reven_dst, b);
    __ block_comment("} unsigned_mod_integer");
  
#line 15220 "ad_s390.cpp"
  }
}

void modI_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 6857 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert_different_registers(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    assert_different_registers(opnd_array(0)->as_Register(ra_,this)/* dst */->successor(), opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    int divisor = opnd_array(2)->constant();

    if (divisor != -1) {
      __ z_lghi(Z_R0_scratch, divisor);
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */->successor(), opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
      __ z_dsgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, Z_R0_scratch); // Instruction kills tmp.
    } else {
      __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, true, false);
    }
  
#line 15245 "ad_s390.cpp"
  }
}

void modL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 6880 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register a = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    Register b = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;
    Register t = opnd_array(0)->as_Register(ra_,this)/* dst */;
    assert(t->successor() == a, "(t,a) is an even-odd pair" );

    Label do_div, done_div;
    if (t->encoding() != b->encoding()) {
      (void) __ clear_reg(t, true, false); // Does no harm. Dividend is in successor.
      if (VM_Version::has_CompareBranch()) {
        __ z_cgij(b, -1, Assembler::bcondEqual, done_div);
      } else {
        __ z_cghi(b, -1);
        __ z_bre(done_div);
      }
      __ z_dsgr(t, b);
    } else {
      if (VM_Version::has_CompareBranch()) {
        __ z_cgij(b, -1, Assembler::bcondNotEqual, do_div);
      } else {
        __ z_cghi(b, -1);
        __ z_brne(do_div);
      }
      __ clear_reg(t, true, false);
      __ z_bru(done_div);
      __ bind(do_div);
      __ z_dsgr(t, b);
    }
    __ bind(done_div);
  
#line 15287 "ad_s390.cpp"
  }
}

void umodL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// r4_reven_dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// r5_rodd_tmp
  {

#line 6922 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register b            = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;
    Register r4_reven_dst = opnd_array(1)->as_Register(ra_,this,idx1)/* r4_reven_dst */;
    Register r5_rodd_tmp  = opnd_array(3)->as_Register(ra_,this,idx3)/* r5_rodd_tmp */;
    assert_different_registers(r4_reven_dst, r5_rodd_tmp, b);
    assert(r4_reven_dst->successor() == r5_rodd_tmp, "instruction requires an even-odd pair" );

    __ block_comment("unsigned_mod_long {");
    __ z_lgr(r5_rodd_tmp, r4_reven_dst); // load lower 64bits in even register
    __ z_lghi(r4_reven_dst, 0);          // make upper 64bits 0
    __ z_dlgr(r4_reven_dst, b);
    __ block_comment("} unsigned_mod_long");
  
#line 15313 "ad_s390.cpp"
  }
}

void modL_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 6945 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int divisor = opnd_array(2)->constantL();
    if (divisor != -1) {
      __ z_lghi(Z_R0_scratch, divisor);
      __ z_lgr(opnd_array(0)->as_Register(ra_,this)/* dst */->successor(), opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
      __ z_dsgr(opnd_array(0)->as_Register(ra_,this)/* dst */, Z_R0_scratch);  // Instruction kills tmp.
    } else {
      __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, true, false);
    }
  
#line 15335 "ad_s390.cpp"
  }
}

void sllI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {

#line 6969 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lgr(Z_R1_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* nbits */);
    __ z_nill(Z_R1_scratch, BitsPerJavaInteger-1);
    __ z_sllg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0, Z_R1_scratch);
  
#line 15352 "ad_s390.cpp"
  }
}

uint sllI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 14, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 14);
}

void sllI_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {

#line 6983 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int Nbit = opnd_array(2)->constant();
    assert((Nbit & (BitsPerJavaInteger - 1)) == Nbit, "Check shift mask in ideal graph");
    __ z_sllg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Nbit & (BitsPerJavaInteger - 1), Z_R0);
  
#line 15374 "ad_s390.cpp"
  }
}

uint sllI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void sllI_reg_imm_1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {

#line 6998 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_la(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 15392 "ad_s390.cpp"
  }
}

uint sllI_reg_imm_1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sllL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {

#line 2071 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (SLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* nbits */,16,48) |
             Assembler::simm20(0));
  
#line 15416 "ad_s390.cpp"
  }
}

uint sllL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void sllL_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (SLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 15439 "ad_s390.cpp"
  }
}

uint sllL_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void sllL_reg_imm_1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {

#line 7029 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_la(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */); 
#line 15457 "ad_s390.cpp"
  }
}

uint sllL_reg_imm_1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sraI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 7042 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lgr(Z_R1_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* src */);
    __ z_nill(Z_R1_scratch, BitsPerJavaInteger-1);
    __ z_sra(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 0, Z_R1_scratch);
  
#line 15479 "ad_s390.cpp"
  }
}

uint sraI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void sraI_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 7057 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int Nbit = opnd_array(2)->constant();
    assert((Nbit & (BitsPerJavaInteger - 1)) == Nbit, "Check shift mask in ideal graph");
    __ z_sra(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, Nbit & (BitsPerJavaInteger - 1), Z_R0);
  
#line 15501 "ad_s390.cpp"
  }
}

uint sraI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sraL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2071 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (SRAG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(0));
  
#line 15525 "ad_s390.cpp"
  }
}

uint sraL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void sraL_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (SRAG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 15548 "ad_s390.cpp"
  }
}

uint sraL_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void srlI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 7096 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lgr(Z_R1_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* src */);
    __ z_nill(Z_R1_scratch, BitsPerJavaInteger-1);
    __ z_srl(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 0, Z_R1_scratch);
  
#line 15570 "ad_s390.cpp"
  }
}

uint srlI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void srlI_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 7110 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int Nbit = opnd_array(2)->constant();
    assert((Nbit & (BitsPerJavaInteger - 1)) == Nbit, "Check shift mask in ideal graph");
    __ z_srl(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, Nbit & (BitsPerJavaInteger - 1), Z_R0);
  
#line 15592 "ad_s390.cpp"
  }
}

uint srlI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void srlL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2071 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (SRLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(0));
  
#line 15616 "ad_s390.cpp"
  }
}

uint srlL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void srlL_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (SRLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 15639 "ad_s390.cpp"
  }
}

uint srlL_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void srlP_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (SRLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 15662 "ad_s390.cpp"
  }
}

uint srlP_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rotlI_reg_immI8Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (RLL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 15686 "ad_s390.cpp"
  }
}

uint rotlI_reg_immI8Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rotlI_reg_immI8_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (RLL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(3)->constant()));
  
#line 15710 "ad_s390.cpp"
  }
}

uint rotlI_reg_immI8_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rotlL_reg_immI8Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (RLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 15734 "ad_s390.cpp"
  }
}

uint rotlL_reg_immI8Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rotlL_reg_immI8_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (RLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(3)->constant()));
  
#line 15758 "ad_s390.cpp"
  }
}

uint rotlL_reg_immI8_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rotrI_reg_immI8Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (RLL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 15782 "ad_s390.cpp"
  }
}

void rotrI_reg_immI8_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (RLL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(3)->constant()));
  
#line 15801 "ad_s390.cpp"
  }
}

void rotrL_reg_immI8Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (RLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 15820 "ad_s390.cpp"
  }
}

void rotrL_reg_immI8_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (RLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(3)->constant()));
  
#line 15839 "ad_s390.cpp"
  }
}

void overflowAddI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 7202 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_ar(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 15855 "ad_s390.cpp"
  }
}

void overflowAddI_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 7214 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_const_optimized(Z_R0_scratch, opnd_array(2)->constant());
    __ z_ar(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
  
#line 15871 "ad_s390.cpp"
  }
}

void overflowAddL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 7226 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lgr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_agr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 15887 "ad_s390.cpp"
  }
}

void overflowAddL_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 7238 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_const_optimized(Z_R0_scratch, opnd_array(2)->constantL());
    __ z_agr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
  
#line 15903 "ad_s390.cpp"
  }
}

void overflowSubI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 7250 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_sr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 15919 "ad_s390.cpp"
  }
}

void overflowSubI_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 7262 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_const_optimized(Z_R1_scratch, opnd_array(2)->constant());
    __ z_lr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_sr(Z_R0_scratch, Z_R1_scratch);
  
#line 15936 "ad_s390.cpp"
  }
}

void overflowSubL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 7275 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lgr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_sgr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 15952 "ad_s390.cpp"
  }
}

void overflowSubL_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 7287 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_const_optimized(Z_R1_scratch, opnd_array(2)->constantL());
    __ z_lgr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_sgr(Z_R0_scratch, Z_R1_scratch);
  
#line 15969 "ad_s390.cpp"
  }
}

void overflowNegI_rRegNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 7299 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ clear_reg(Z_R0_scratch, false, false);
    __ z_sr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 15985 "ad_s390.cpp"
  }
}

void overflowNegL_rRegNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 7310 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ clear_reg(Z_R0_scratch, true, false);
    __ z_sgr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 16001 "ad_s390.cpp"
  }
}

void addF_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (AEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 16019 "ad_s390.cpp"
  }
}

uint addF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addF_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((AEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (AEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(masm, (AEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 16053 "ad_s390.cpp"
  }
}

uint addF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addF_reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((AEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (AEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (AEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 16087 "ad_s390.cpp"
  }
}

uint addF_reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addD_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((ADBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (ADBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 16110 "ad_s390.cpp"
  }
}

uint addD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addD_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((ADB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (ADB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(masm, (ADB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 16144 "ad_s390.cpp"
  }
}

uint addD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addD_reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((ADB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (ADB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (ADB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 16178 "ad_s390.cpp"
  }
}

uint addD_reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void subF_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (SEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 16201 "ad_s390.cpp"
  }
}

uint subF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subF_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((SEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (SEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(masm, (SEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 16235 "ad_s390.cpp"
  }
}

uint subF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void subD_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (SDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 16258 "ad_s390.cpp"
  }
}

uint subD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subD_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((SDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (SDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(masm, (SDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 16292 "ad_s390.cpp"
  }
}

uint subD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulF_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MEEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (MEEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 16315 "ad_s390.cpp"
  }
}

uint mulF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulF_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((MEEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (MEEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(masm, (MEEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 16349 "ad_s390.cpp"
  }
}

uint mulF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulF_reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((MEEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (MEEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (MEEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 16383 "ad_s390.cpp"
  }
}

uint mulF_reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulD_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (MDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 16406 "ad_s390.cpp"
  }
}

uint mulD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulD_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((MDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (MDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(masm, (MDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 16440 "ad_s390.cpp"
  }
}

uint mulD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulD_reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((MDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (MDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (MDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 16474 "ad_s390.cpp"
  }
}

uint mulD_reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void maddF_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7475 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_maebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */);
  
#line 16496 "ad_s390.cpp"
  }
}

uint maddF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void maddD_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7489 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_madbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */);
  
#line 16518 "ad_s390.cpp"
  }
}

uint maddD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void msubF_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7503 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_msebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */);
  
#line 16540 "ad_s390.cpp"
  }
}

uint msubF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void msubD_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7517 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_msdbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */);
  
#line 16562 "ad_s390.cpp"
  }
}

uint msubD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void maddF_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7531 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_maeb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */,
              Address(reg_to_register_object(opnd_array(3)->base(ra_,this,idx3)), as_Register(opnd_array(3)->index(ra_,this,idx3)), opnd_array(3)->disp(ra_,this,idx3)));
  
#line 16585 "ad_s390.cpp"
  }
}

uint maddF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void maddD_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7546 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_madb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */,
              Address(reg_to_register_object(opnd_array(3)->base(ra_,this,idx3)), as_Register(opnd_array(3)->index(ra_,this,idx3)), opnd_array(3)->disp(ra_,this,idx3)));
  
#line 16608 "ad_s390.cpp"
  }
}

uint maddD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void msubF_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7561 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_mseb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */,
              Address(reg_to_register_object(opnd_array(3)->base(ra_,this,idx3)), as_Register(opnd_array(3)->index(ra_,this,idx3)), opnd_array(3)->disp(ra_,this,idx3)));
  
#line 16631 "ad_s390.cpp"
  }
}

uint msubF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void msubD_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7576 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_msdb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */,
              Address(reg_to_register_object(opnd_array(3)->base(ra_,this,idx3)), as_Register(opnd_array(3)->index(ra_,this,idx3)), opnd_array(3)->disp(ra_,this,idx3)));
  
#line 16654 "ad_s390.cpp"
  }
}

uint msubD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void maddF_mem_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7591 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_maeb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */,
              Address(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), as_Register(opnd_array(2)->index(ra_,this,idx2)), opnd_array(2)->disp(ra_,this,idx2)));
  
#line 16677 "ad_s390.cpp"
  }
}

uint maddF_mem_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void maddD_mem_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7606 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_madb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */,
              Address(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), as_Register(opnd_array(2)->index(ra_,this,idx2)), opnd_array(2)->disp(ra_,this,idx2)));
  
#line 16700 "ad_s390.cpp"
  }
}

uint maddD_mem_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void msubF_mem_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7621 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_mseb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */,
              Address(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), as_Register(opnd_array(2)->index(ra_,this,idx2)), opnd_array(2)->disp(ra_,this,idx2)));
  
#line 16723 "ad_s390.cpp"
  }
}

uint msubF_mem_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void msubD_mem_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 7636 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(UseFMA, "Needs FMA instructions support.");
    __ z_msdb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */,
              Address(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), as_Register(opnd_array(2)->index(ra_,this,idx2)), opnd_array(2)->disp(ra_,this,idx2)));
  
#line 16746 "ad_s390.cpp"
  }
}

uint msubD_mem_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void divF_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((DEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (DEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 16769 "ad_s390.cpp"
  }
}

uint divF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void divF_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((DEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (DEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(masm, (DEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 16803 "ad_s390.cpp"
  }
}

uint divF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void divD_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((DDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (DDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 16826 "ad_s390.cpp"
  }
}

uint divD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void divD_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((DDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (DDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(masm, (DDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 16860 "ad_s390.cpp"
  }
}

uint divD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void absF_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LPEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LPEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 16882 "ad_s390.cpp"
  }
}

uint absF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void absD_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LPDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LPDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 16904 "ad_s390.cpp"
  }
}

uint absD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void nabsF_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LNEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LNEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 16926 "ad_s390.cpp"
  }
}

uint nabsF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void nabsD_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LNDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LNDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 16948 "ad_s390.cpp"
  }
}

uint nabsD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void negF_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 7747 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lcebr(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */); 
#line 16965 "ad_s390.cpp"
  }
}

uint negF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void negD_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 7756 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lcdbr(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */); 
#line 16982 "ad_s390.cpp"
  }
}

uint negD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sqrtF_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SQEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (SQEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17004 "ad_s390.cpp"
  }
}

uint sqrtF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sqrtD_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SQDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (SQDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17026 "ad_s390.cpp"
  }
}

uint sqrtD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sqrtF_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((SQEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (SQEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (SQEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 17059 "ad_s390.cpp"
  }
}

uint sqrtF_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void sqrtD_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((SQDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (SQDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (SQDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 17092 "ad_s390.cpp"
  }
}

void andI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((NR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((NR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (NR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 17111 "ad_s390.cpp"
  }
}

uint andI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void andI_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (N_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (N_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (NY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (N_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 17155 "ad_s390.cpp"
  }
}

void andI_Reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (N_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (N_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (NY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (N_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 17194 "ad_s390.cpp"
  }
}

void andI_reg_uimm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2057 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((NILF_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (NILF_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::uimm32(opnd_array(2)->constant(),16,48));
  
#line 17212 "ad_s390.cpp"
  }
}

uint andI_reg_uimm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void andI_reg_uimmI_LH1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 7851 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nilh(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, (opnd_array(2)->constant()>> 16) & 0xFFFF); 
#line 17230 "ad_s390.cpp"
  }
}

uint andI_reg_uimmI_LH1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andI_reg_uimmI_LL1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 7861 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nill(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(2)->constant()& 0xFFFF); 
#line 17248 "ad_s390.cpp"
  }
}

uint andI_reg_uimmI_LL1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((NGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (NGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 17271 "ad_s390.cpp"
  }
}

uint andL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (NG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (NG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (NG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (NG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 17315 "ad_s390.cpp"
  }
}

uint andL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void andL_Reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (NG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (NG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (NG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (NG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 17359 "ad_s390.cpp"
  }
}

uint andL_Reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void andL_reg_uimmL_LL1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 7894 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nill(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(2)->constantL()& 0xFFFF); 
#line 17377 "ad_s390.cpp"
  }
}

uint andL_reg_uimmL_LL1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_uimmL_LH1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 7904 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nilh(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, (opnd_array(2)->constantL()>> 16) & 0xFFFF); 
#line 17395 "ad_s390.cpp"
  }
}

uint andL_reg_uimmL_LH1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_uimmL_HL1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 7914 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nihl(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, (opnd_array(2)->constantL()>> 32) & 0xFFFF); 
#line 17413 "ad_s390.cpp"
  }
}

uint andL_reg_uimmL_HL1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_uimmL_HH1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 7924 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nihh(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, (opnd_array(2)->constantL()>> 48) & 0xFFFF); 
#line 17431 "ad_s390.cpp"
  }
}

uint andL_reg_uimmL_HH1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((OR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (OR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 17455 "ad_s390.cpp"
  }
}

uint orI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void orI_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (O_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (O_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (OY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (O_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 17499 "ad_s390.cpp"
  }
}

void orI_Reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (O_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (O_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (OY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (O_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 17538 "ad_s390.cpp"
  }
}

void orI_reg_uimm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2035 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OILL_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (OILL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::uimm16(opnd_array(2)->constant(),16,32));
  
#line 17556 "ad_s390.cpp"
  }
}

uint orI_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orI_reg_uimm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2057 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OILF_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (OILF_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::uimm32(opnd_array(2)->constant(),16,48));
  
#line 17579 "ad_s390.cpp"
  }
}

uint orI_reg_uimm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void orL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (OGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 17602 "ad_s390.cpp"
  }
}

uint orL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orL_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (OG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (OG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (OG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (OG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 17646 "ad_s390.cpp"
  }
}

uint orL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void orL_Reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (OG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (OG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (OG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (OG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 17690 "ad_s390.cpp"
  }
}

uint orL_Reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void orL_reg_uimm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2035 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OILL_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (OILL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::uimm16(opnd_array(2)->constantL(),16,32));
  
#line 17713 "ad_s390.cpp"
  }
}

uint orL_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orL_reg_uimm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2057 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OILF_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (OILF_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::uimm32(opnd_array(2)->constantL(),16,48));
  
#line 17736 "ad_s390.cpp"
  }
}

void xorI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((XR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (XR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 17755 "ad_s390.cpp"
  }
}

uint xorI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void xorI_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (X_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (X_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (XY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (X_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 17799 "ad_s390.cpp"
  }
}

void xorI_Reg_mem_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (X_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (X_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (XY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (X_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 17838 "ad_s390.cpp"
  }
}

void xorI_reg_uimm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2057 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XILF_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (XILF_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::uimm32(opnd_array(2)->constant(),16,48));
  
#line 17856 "ad_s390.cpp"
  }
}

uint xorI_reg_uimm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void xorL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (XGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 17879 "ad_s390.cpp"
  }
}

uint xorL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xorL_Reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (XG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (XG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (XG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (XG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 17923 "ad_s390.cpp"
  }
}

uint xorL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void xorL_reg_uimm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2057 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XILF_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (XILF_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::uimm32(opnd_array(2)->constantL(),16,48));
  
#line 17946 "ad_s390.cpp"
  }
}

uint xorL_reg_uimm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void convI2BNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 8101 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lnr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);  // Rdst := -|Rsrc|, i.e. Rdst == 0 <=> Rsrc == 0
    __ z_srl(opnd_array(0)->as_Register(ra_,this)/* dst */, 31);              // Rdst := sign(Rdest)
  
#line 17966 "ad_s390.cpp"
  }
}

uint convI2BNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void convP2BNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 8114 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lngr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);     // Rdst := -|Rsrc| i.e. Rdst == 0 <=> Rsrc == 0
    __ z_srlg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */, 63); // Rdst := sign(Rdest)
  
#line 17986 "ad_s390.cpp"
  }
}

uint convP2BNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 10, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 10);
}

void cmpLTMask_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 8127 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // Avoid signed 32 bit overflow: Do sign extend and sub 64 bit.
    __ z_lgfr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* src */);
    __ z_lgfr(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* dst */);
    __ z_sgr(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, Z_R0_scratch);
    __ z_srag(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 63);
  
#line 18010 "ad_s390.cpp"
  }
}

uint cmpLTMask_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 18, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 18);
}

void cmpLTMask_reg_zeroNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  {

#line 8143 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_sra(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 31); 
#line 18028 "ad_s390.cpp"
  }
}

uint cmpLTMask_reg_zeroNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convD2F_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LEDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LEDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 18050 "ad_s390.cpp"
  }
}

uint convD2F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convF2I_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 8167 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, false, false);  // Initialize with result for unordered: 0.
    __ z_cebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);   // Round.
    __ z_brno(done);                             // Result is zero if unordered argument.
    __ z_cfebr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Assembler::to_zero);
    __ bind(done);
  
#line 18074 "ad_s390.cpp"
  }
}

uint convF2I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void convD2I_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 8184 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, false, false);  // Initialize with result for unordered: 0.
    __ z_cdbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);   // Round.
    __ z_brno(done);                             // Result is zero if unordered argument.
    __ z_cfdbr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Assembler::to_zero);
    __ bind(done);
  
#line 18098 "ad_s390.cpp"
  }
}

uint convD2I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void convF2L_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 8201 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, true, false);  // Initialize with result for unordered: 0.
    __ z_cebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);   // Round.
    __ z_brno(done);                             // Result is zero if unordered argument.
    __ z_cgebr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Assembler::to_zero);
    __ bind(done);
  
#line 18122 "ad_s390.cpp"
  }
}

uint convF2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void convD2L_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 8218 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, true, false);  // Initialize with result for unordered: 0.
    __ z_cdbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);   // Round.
    __ z_brno(done);                             // Result is zero if unordered argument.
    __ z_cgdbr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Assembler::to_zero);
    __ bind(done);
  
#line 18146 "ad_s390.cpp"
  }
}

uint convD2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void convF2D_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LDEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LDEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 18168 "ad_s390.cpp"
  }
}

uint convF2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convF2D_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LDEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (LDEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (LDEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 18201 "ad_s390.cpp"
  }
}

uint convF2D_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void convI2D_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CDFBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (CDFBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 18223 "ad_s390.cpp"
  }
}

uint convI2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convI2F_iregNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CEFBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (CEFBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 18245 "ad_s390.cpp"
  }
}

uint convI2F_iregNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convI2L_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 18267 "ad_s390.cpp"
  }
}

uint convI2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convI2L_reg_zexNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {

#line 8286 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_llgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 18285 "ad_s390.cpp"
  }
}

uint convI2L_reg_zexNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convI2L_mem_zexNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 18329 "ad_s390.cpp"
  }
}

void zeroExtend_longNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {

#line 8306 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_llgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 18342 "ad_s390.cpp"
  }
}

uint zeroExtend_longNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rShiftI16_lShiftI16_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// amount
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LHR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LHR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 18365 "ad_s390.cpp"
  }
}

uint rShiftI16_lShiftI16_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rShiftI24_lShiftI24_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// amount
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 18388 "ad_s390.cpp"
  }
}

uint rShiftI24_lShiftI24_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void MoveF2I_stack_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((L_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (L_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (L_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 18421 "ad_s390.cpp"
  }
}

uint MoveF2I_stack_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void MoveI2F_stack_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LE_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (LE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (LE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 18454 "ad_s390.cpp"
  }
}

void MoveD2L_stack_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 18482 "ad_s390.cpp"
  }
}

uint MoveD2L_stack_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void MoveL2D_stack_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LD_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (LD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (LD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 18515 "ad_s390.cpp"
  }
}

uint MoveL2D_stack_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void MoveI2F_reg_stackNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((ST_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (ST_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (ST_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 18548 "ad_s390.cpp"
  }
}

uint MoveI2F_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void MoveD2L_reg_stackNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STD_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 18581 "ad_s390.cpp"
  }
}

uint MoveD2L_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void MoveL2D_reg_stackNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 18614 "ad_s390.cpp"
  }
}

uint MoveL2D_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void convL2F_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CEGBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (CEGBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 18636 "ad_s390.cpp"
  }
}

uint convL2F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convL2D_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CDGBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (CDGBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 18658 "ad_s390.cpp"
  }
}

uint convL2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convL2I_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 8426 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ lr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 18675 "ad_s390.cpp"
  }
}

void shrL_reg_imm6_L2INode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt
  {

#line 2064 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(masm, (SRAG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 18693 "ad_s390.cpp"
  }
}

uint shrL_reg_imm6_L2INode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rangeCheck_iReg_uimmI16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// length
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// index
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {

#line 8462 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_clfit(opnd_array(2)->as_Register(ra_,this,idx2)/* length */, opnd_array(3)->constant(), opnd_array(1)->ccode()); 
#line 18713 "ad_s390.cpp"
  }
}

void rangeCheck_iReg_iRegNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// index
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// length
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 8480 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_clrt(opnd_array(2)->as_Register(ra_,this,idx2)/* index */, opnd_array(3)->as_Register(ra_,this,idx3)/* length */, opnd_array(1)->ccode()); 
#line 18728 "ad_s390.cpp"
  }
}

void rangeCheck_uimmI16_iRegNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// index
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// length
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {

#line 8498 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_clfit(opnd_array(2)->as_Register(ra_,this,idx2)/* index */, opnd_array(3)->constant(), opnd_array(1)->ccode()); 
#line 18743 "ad_s390.cpp"
  }
}

void zeroCheckP_iReg_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// value
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {

#line 8515 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_cgit(opnd_array(2)->as_Register(ra_,this,idx2)/* value */, 0, opnd_array(1)->ccode()); 
#line 18758 "ad_s390.cpp"
  }
}

uint zeroCheckP_iReg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void zeroCheckN_iReg_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// value
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {

#line 8532 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_cit(opnd_array(2)->as_Register(ra_,this,idx2)/* value */, 0, opnd_array(1)->ccode()); 
#line 18778 "ad_s390.cpp"
  }
}

uint zeroCheckN_iReg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((CR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (CR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,12,16));
  
#line 18802 "ad_s390.cpp"
  }
}

uint compI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void compI_reg_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2050 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (CFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,48) |
             Assembler::simm32(opnd_array(2)->constant(),16,48));
  
#line 18825 "ad_s390.cpp"
  }
}

uint compI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compI_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2028 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (CHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,32) |
             Assembler::simm16(opnd_array(2)->constant(),16,32));
  
#line 18848 "ad_s390.cpp"
  }
}

uint compI_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compI_reg_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((LTR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (LTR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,16) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,12,16));
  
#line 18872 "ad_s390.cpp"
  }
}

uint compI_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void compI_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (C_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (C_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (CY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (C_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 18916 "ad_s390.cpp"
  }
}

void compU_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((CLR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (CLR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,12,16));
  
#line 18935 "ad_s390.cpp"
  }
}

uint compU_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void compU_reg_uimmNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2057 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (CLFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,48) |
             Assembler::uimm32(opnd_array(2)->constant(),16,48));
  
#line 18958 "ad_s390.cpp"
  }
}

uint compU_reg_uimmNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compU_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (CL_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (CL_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (CLY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (CL_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 19002 "ad_s390.cpp"
  }
}

void compL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (CGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,28,32));
  
#line 19020 "ad_s390.cpp"
  }
}

uint compL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compL_reg_regINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (CGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,28,32));
  
#line 19043 "ad_s390.cpp"
  }
}

uint compL_reg_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compL_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2050 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CGFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (CGFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,48) |
             Assembler::simm32(opnd_array(2)->constantL(),16,48));
  
#line 19066 "ad_s390.cpp"
  }
}

uint compL_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compL_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2028 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CGHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (CGHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,32) |
             Assembler::simm16(opnd_array(2)->constantL(),16,32));
  
#line 19089 "ad_s390.cpp"
  }
}

uint compL_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compL_reg_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LTGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,28,32));
  
#line 19112 "ad_s390.cpp"
  }
}

uint compL_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compL_conv_reg_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LTGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,28,32));
  
#line 19135 "ad_s390.cpp"
  }
}

uint compL_conv_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compL_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (CG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (CG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (CG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (CG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 19179 "ad_s390.cpp"
  }
}

uint compL_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void compL_reg_memINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (CGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (CGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (CGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (CGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 19223 "ad_s390.cpp"
  }
}

uint compL_reg_memINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void compUL_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (CLGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,28,32));
  
#line 19246 "ad_s390.cpp"
  }
}

uint compUL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compUL_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 2057 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLGFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(masm, (CLGFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,48) |
             Assembler::uimm32(opnd_array(2)->constantL(),16,48));
  
#line 19269 "ad_s390.cpp"
  }
}

uint compUL_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compP_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (CLGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,28,32));
  
#line 19292 "ad_s390.cpp"
  }
}

uint compP_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compP_reg_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LTGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,28,32));
  
#line 19315 "ad_s390.cpp"
  }
}

uint compP_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compP_decode_reg_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((LTR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (LTR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,16) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,12,16));
  
#line 19339 "ad_s390.cpp"
  }
}

uint compP_decode_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void compP_reg_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (CLG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (CLG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(masm, (CLG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (CLG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 19383 "ad_s390.cpp"
  }
}

uint compP_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void z196_minI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 8769 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(0)->as_Register(ra_,this)/* dst */;
    Register Rsrc1 = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    Register Rsrc2 = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;

    if (Rsrc1 == Rsrc2) {
      if (Rdst != Rsrc1) {
        __ z_lgfr(Rdst, Rsrc1);
      }
    } else if (Rdst == Rsrc1) {   // Rdst preset with src1.
      __ z_cr(Rsrc1, Rsrc2);      // Move src2 only if src1 is NotLow.
      __ z_locr(Rdst, Rsrc2, Assembler::bcondNotLow);
    } else if (Rdst == Rsrc2) {   // Rdst preset with src2.
      __ z_cr(Rsrc2, Rsrc1);      // Move src1 only if src2 is NotLow.
      __ z_locr(Rdst, Rsrc1, Assembler::bcondNotLow);
    } else {
      // Rdst is disjoint from operands, move in either case.
      __ z_cr(Rsrc1, Rsrc2);
      __ z_locr(Rdst, Rsrc2, Assembler::bcondNotLow);
      __ z_locr(Rdst, Rsrc1, Assembler::bcondLow);
    }
  
#line 19422 "ad_s390.cpp"
  }
}

void z10_minI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 8802 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(0)->as_Register(ra_,this)/* dst */;
    Register Rsrc1 = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    Register Rsrc2 = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;
    Label done;

    if (Rsrc1 == Rsrc2) {
      if (Rdst != Rsrc1) {
        __ z_lgfr(Rdst, Rsrc1);
      }
    } else if (Rdst == Rsrc1) {
      __ z_crj(Rsrc1, Rsrc2, Assembler::bcondLow, done);
      __ z_lgfr(Rdst, Rsrc2);
    } else if (Rdst == Rsrc2) {
      __ z_crj(Rsrc2, Rsrc1, Assembler::bcondLow, done);
      __ z_lgfr(Rdst, Rsrc1);
    } else {
      __ z_lgfr(Rdst, Rsrc1);
      __ z_crj(Rsrc1, Rsrc2, Assembler::bcondLow, done);
      __ z_lgfr(Rdst, Rsrc2);
    }
    __ bind(done);
  
#line 19457 "ad_s390.cpp"
  }
}

void minI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 8835 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(0)->as_Register(ra_,this)/* dst */;
    Register Rsrc1 = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    Register Rsrc2 = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;
    Label done;

    if (Rsrc1 == Rsrc2) {
      if (Rdst != Rsrc1) {
        __ z_lgfr(Rdst, Rsrc1);
      }
    } else if (Rdst == Rsrc1) {
      __ z_cr(Rsrc1, Rsrc2);
      __ z_brl(done);
      __ z_lgfr(Rdst, Rsrc2);
    } else if (Rdst == Rsrc2) {
      __ z_cr(Rsrc2, Rsrc1);
      __ z_brl(done);
      __ z_lgfr(Rdst, Rsrc1);
    } else {
      __ z_lgfr(Rdst, Rsrc1);
      __ z_cr(Rsrc1, Rsrc2);
      __ z_brl(done);
      __ z_lgfr(Rdst, Rsrc2);
    }
    __ bind(done);
  
#line 19495 "ad_s390.cpp"
  }
}

void z196_minI_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 8871 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(0)->as_Register(ra_,this)/* dst */;
    Register Rsrc1 = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    int      Isrc2 = opnd_array(2)->constant();

    if (Rdst == Rsrc1) {
      __ load_const_optimized(Z_R0_scratch, Isrc2);
      __ z_cfi(Rsrc1, Isrc2);
      __ z_locr(Rdst, Z_R0_scratch, Assembler::bcondNotLow);
    } else {
      __ load_const_optimized(Rdst, Isrc2);
      __ z_cfi(Rsrc1, Isrc2);
      __ z_locr(Rdst, Rsrc1, Assembler::bcondLow);
    }
  
#line 19522 "ad_s390.cpp"
  }
}

void minI_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 8895 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_cfi(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
    __ z_brl(done);
    __ z_lgfi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 19544 "ad_s390.cpp"
  }
}

void z196_minI_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 8915 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(0)->as_Register(ra_,this)/* dst */;
    Register Rsrc1 = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    int      Isrc2 = opnd_array(2)->constant();

    if (Rdst == Rsrc1) {
      __ load_const_optimized(Z_R0_scratch, Isrc2);
      __ z_chi(Rsrc1, Isrc2);
      __ z_locr(Rdst, Z_R0_scratch, Assembler::bcondNotLow);
    } else {
      __ load_const_optimized(Rdst, Isrc2);
      __ z_chi(Rsrc1, Isrc2);
      __ z_locr(Rdst, Rsrc1, Assembler::bcondLow);
    }
  
#line 19571 "ad_s390.cpp"
  }
}

void minI_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 8939 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_chi(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
    __ z_brl(done);
    __ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 19593 "ad_s390.cpp"
  }
}

void z10_minI_reg_imm8Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 8959 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_cij(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant(), Assembler::bcondLow, done);
    __ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 19614 "ad_s390.cpp"
  }
}

void z196_maxI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 8979 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(0)->as_Register(ra_,this)/* dst */;
    Register Rsrc1 = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    Register Rsrc2 = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;

    if (Rsrc1 == Rsrc2) {
      if (Rdst != Rsrc1) {
        __ z_lgfr(Rdst, Rsrc1);
      }
    } else if (Rdst == Rsrc1) { // Rdst preset with src1.
      __ z_cr(Rsrc1, Rsrc2);    // Move src2 only if src1 is NotHigh.
      __ z_locr(Rdst, Rsrc2, Assembler::bcondNotHigh);
    } else if (Rdst == Rsrc2) { // Rdst preset with src2.
      __ z_cr(Rsrc2, Rsrc1);    // Move src1 only if src2 is NotHigh.
      __ z_locr(Rdst, Rsrc1, Assembler::bcondNotHigh);
    } else {                    // Rdst is disjoint from operands, move in either case.
      __ z_cr(Rsrc1, Rsrc2);
      __ z_locr(Rdst, Rsrc2, Assembler::bcondNotHigh);
      __ z_locr(Rdst, Rsrc1, Assembler::bcondHigh);
    }
  
#line 19647 "ad_s390.cpp"
  }
}

void z10_maxI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9011 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(0)->as_Register(ra_,this)/* dst */;
    Register Rsrc1 = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    Register Rsrc2 = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;
    Label done;

    if (Rsrc1 == Rsrc2) {
      if (Rdst != Rsrc1) {
        __ z_lgfr(Rdst, Rsrc1);
      }
    } else if (Rdst == Rsrc1) {
      __ z_crj(Rsrc1, Rsrc2, Assembler::bcondHigh, done);
      __ z_lgfr(Rdst, Rsrc2);
    } else if (Rdst == Rsrc2) {
      __ z_crj(Rsrc2, Rsrc1, Assembler::bcondHigh, done);
      __ z_lgfr(Rdst, Rsrc1);
    } else {
      __ z_lgfr(Rdst, Rsrc1);
      __ z_crj(Rsrc1, Rsrc2, Assembler::bcondHigh, done);
      __ z_lgfr(Rdst, Rsrc2);
    }
    __ bind(done);
  
#line 19682 "ad_s390.cpp"
  }
}

void maxI_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9044 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(0)->as_Register(ra_,this)/* dst */;
    Register Rsrc1 = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    Register Rsrc2 = opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */;
    Label done;

    if (Rsrc1 == Rsrc2) {
      if (Rdst != Rsrc1) {
        __ z_lgfr(Rdst, Rsrc1);
      }
    } else if (Rdst == Rsrc1) {
      __ z_cr(Rsrc1, Rsrc2);
      __ z_brh(done);
      __ z_lgfr(Rdst, Rsrc2);
    } else if (Rdst == Rsrc2) {
      __ z_cr(Rsrc2, Rsrc1);
      __ z_brh(done);
      __ z_lgfr(Rdst, Rsrc1);
    } else {
      __ z_lgfr(Rdst, Rsrc1);
      __ z_cr(Rsrc1, Rsrc2);
      __ z_brh(done);
      __ z_lgfr(Rdst, Rsrc2);
    }

    __ bind(done);
  
#line 19721 "ad_s390.cpp"
  }
}

void z196_maxI_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9082 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(0)->as_Register(ra_,this)/* dst */;
    Register Rsrc1 = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    int      Isrc2 = opnd_array(2)->constant();

    if (Rdst == Rsrc1) {
      __ load_const_optimized(Z_R0_scratch, Isrc2);
      __ z_cfi(Rsrc1, Isrc2);
      __ z_locr(Rdst, Z_R0_scratch, Assembler::bcondNotHigh);
    } else {
      __ load_const_optimized(Rdst, Isrc2);
      __ z_cfi(Rsrc1, Isrc2);
      __ z_locr(Rdst, Rsrc1, Assembler::bcondHigh);
    }
  
#line 19748 "ad_s390.cpp"
  }
}

void maxI_reg_imm32Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9106 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_cfi(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
    __ z_brh(done);
    __ z_lgfi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 19770 "ad_s390.cpp"
  }
}

void z196_maxI_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9126 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(0)->as_Register(ra_,this)/* dst */;
    Register Rsrc1 = opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */;
    int      Isrc2 = opnd_array(2)->constant();
    if (Rdst == Rsrc1) {
      __ load_const_optimized(Z_R0_scratch, Isrc2);
      __ z_chi(Rsrc1, Isrc2);
      __ z_locr(Rdst, Z_R0_scratch, Assembler::bcondNotHigh);
    } else {
      __ load_const_optimized(Rdst, Isrc2);
      __ z_chi(Rsrc1, Isrc2);
      __ z_locr(Rdst, Rsrc1, Assembler::bcondHigh);
    }
  
#line 19796 "ad_s390.cpp"
  }
}

void maxI_reg_imm16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9149 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_chi(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
    __ z_brh(done);
    __ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 19818 "ad_s390.cpp"
  }
}

void z10_maxI_reg_imm8Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9169 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_cij(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant(), Assembler::bcondHigh, done);
    __ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 19839 "ad_s390.cpp"
  }
}

void absI_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LPR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((LPR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (LPR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,16) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,16));
  
#line 19857 "ad_s390.cpp"
  }
}

void absL_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LPGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LPGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 19874 "ad_s390.cpp"
  }
}

void negabsI_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2005 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LNR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((LNR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(masm, (LNR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 19893 "ad_s390.cpp"
  }
}

void cmpF_ccNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9224 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_cebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */); 
#line 19906 "ad_s390.cpp"
  }
}

uint cmpF_ccNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpD_ccNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9233 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_cdbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */); 
#line 19924 "ad_s390.cpp"
  }
}

uint cmpD_ccNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpF_cc_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((CEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (CEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(masm, (CEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 19958 "ad_s390.cpp"
  }
}

uint cmpF_cc_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void cmpD_cc_memNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((CDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(masm, (CDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(masm, (CDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 19992 "ad_s390.cpp"
  }
}

uint cmpD_cc_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void cmpF0_ccNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LTEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32));
  
#line 20015 "ad_s390.cpp"
  }
}

uint cmpF0_ccNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpD0_ccNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LTDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32));
  
#line 20038 "ad_s390.cpp"
  }
}

uint cmpD0_ccNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpF_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9285 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // compare registers
    __ z_cebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
    // Convert condition code into -1,0,1, where
    // -1 means unordered or less
    //  0 means equal
    //  1 means greater.
    if (VM_Version::has_LoadStoreConditional()) {
      Register one       = Z_R0_scratch;
      Register minus_one = Z_R1_scratch;
      __ z_lghi(minus_one, -1);
      __ z_lghi(one, 1);
      __ z_lghi( opnd_array(0)->as_Register(ra_,this)/* dst */, 0);
      __ z_locgr(opnd_array(0)->as_Register(ra_,this)/* dst */, one,       Assembler::bcondHigh);
      __ z_locgr(opnd_array(0)->as_Register(ra_,this)/* dst */, minus_one, Assembler::bcondLowOrNotOrdered);
    } else {
      Label done;
      __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, true, false);
      __ z_bre(done);
      __ z_lhi(opnd_array(0)->as_Register(ra_,this)/* dst */, 1);
      __ z_brh(done);
      __ z_lhi(opnd_array(0)->as_Register(ra_,this)/* dst */, -1);
      __ bind(done);
    }
  
#line 20080 "ad_s390.cpp"
  }
}

uint cmpF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 24);
}

void cmpD_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9319 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // compare registers
    __ z_cdbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
    // Convert condition code into -1,0,1, where
    // -1 means unordered or less
    //  0 means equal
    //  1 means greater.
    if (VM_Version::has_LoadStoreConditional()) {
      Register one       = Z_R0_scratch;
      Register minus_one = Z_R1_scratch;
      __ z_lghi(minus_one, -1);
      __ z_lghi(one, 1);
      __ z_lghi( opnd_array(0)->as_Register(ra_,this)/* dst */, 0);
      __ z_locgr(opnd_array(0)->as_Register(ra_,this)/* dst */, one,       Assembler::bcondHigh);
      __ z_locgr(opnd_array(0)->as_Register(ra_,this)/* dst */, minus_one, Assembler::bcondLowOrNotOrdered);
    } else {
      Label done;
      // indicate unused result
      (void) __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, true, false);
      __ z_bre(done);
      __ z_lhi(opnd_array(0)->as_Register(ra_,this)/* dst */, 1);
      __ z_brh(done);
      __ z_lhi(opnd_array(0)->as_Register(ra_,this)/* dst */, -1);
      __ bind(done);
    }
  
#line 20123 "ad_s390.cpp"
  }
}

uint cmpD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 24);
}

void branchNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2208 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(1)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    __ z_bru(l);
  
#line 20150 "ad_s390.cpp"
  }
}

uint branchNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void branchFarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2196 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(1)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    __ z_brul(l);
  
#line 20177 "ad_s390.cpp"
  }
}

uint branchFarNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void branchConNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 2232 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(3)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    __ z_brc((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 20206 "ad_s390.cpp"
  }
}

uint branchConNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void branchConFarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 2220 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(3)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 20235 "ad_s390.cpp"
  }
}

uint branchConFarNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void branchLoopEndNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 2232 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(3)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    __ z_brc((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 20264 "ad_s390.cpp"
  }
}

uint branchLoopEndNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void branchLoopEndFarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 2220 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(3)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 20293 "ad_s390.cpp"
  }
}

uint branchLoopEndFarNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void testAndBranchLoopEnd_RegNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2244 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CRJ_ZOPC /*primary()*/);
    if (instr == CRJ_ZOPC) {
      __ z_crj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CLRJ_ZOPC) {
      __ z_clrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CGRJ_ZOPC) {
      __ z_cgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else {
      guarantee(instr == CLGRJ_ZOPC, "opcode not implemented");
      __ z_clgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    }
  
#line 20334 "ad_s390.cpp"
  }
}

void cmpb_RegINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2244 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CRJ_ZOPC /*primary()*/);
    if (instr == CRJ_ZOPC) {
      __ z_crj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CLRJ_ZOPC) {
      __ z_clrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CGRJ_ZOPC) {
      __ z_cgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else {
      guarantee(instr == CLGRJ_ZOPC, "opcode not implemented");
      __ z_clgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    }
  
#line 20370 "ad_s390.cpp"
  }
}

void cmpbU_RegINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2244 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CLRJ_ZOPC /*primary()*/);
    if (instr == CRJ_ZOPC) {
      __ z_crj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CLRJ_ZOPC) {
      __ z_clrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CGRJ_ZOPC) {
      __ z_cgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else {
      guarantee(instr == CLGRJ_ZOPC, "opcode not implemented");
      __ z_clgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    }
  
#line 20406 "ad_s390.cpp"
  }
}

void cmpb_RegLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2244 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CGRJ_ZOPC /*primary()*/);
    if (instr == CRJ_ZOPC) {
      __ z_crj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CLRJ_ZOPC) {
      __ z_clrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CGRJ_ZOPC) {
      __ z_cgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else {
      guarantee(instr == CLGRJ_ZOPC, "opcode not implemented");
      __ z_clgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    }
  
#line 20442 "ad_s390.cpp"
  }
}

void cmpb_RegPPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2244 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CLGRJ_ZOPC /*primary()*/);
    if (instr == CRJ_ZOPC) {
      __ z_crj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CLRJ_ZOPC) {
      __ z_clrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CGRJ_ZOPC) {
      __ z_cgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else {
      guarantee(instr == CLGRJ_ZOPC, "opcode not implemented");
      __ z_clgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    }
  
#line 20478 "ad_s390.cpp"
  }
}

void cmpb_RegNNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2244 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);
    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CLGRJ_ZOPC /*primary()*/);
    if (instr == CRJ_ZOPC) {
      __ z_crj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CLRJ_ZOPC) {
      __ z_clrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else if (instr == CGRJ_ZOPC) {
      __ z_cgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    } else {
      guarantee(instr == CLGRJ_ZOPC, "opcode not implemented");
      __ z_clgrj(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, cc, l);
    }
  
#line 20514 "ad_s390.cpp"
  }
}

void testAndBranchLoopEnd_ImmNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2292 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CIJ_ZOPC /*primary()*/);
    if (instr == CIJ_ZOPC) {
      __ z_cij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CLIJ_ZOPC) {
      __ z_clij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CGIJ_ZOPC) {
      __ z_cgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else {
      guarantee(instr == CLGIJ_ZOPC, "opcode not implemented");
      __ z_clgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    }
  
#line 20551 "ad_s390.cpp"
  }
}

void cmpb_RegI_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2292 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CIJ_ZOPC /*primary()*/);
    if (instr == CIJ_ZOPC) {
      __ z_cij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CLIJ_ZOPC) {
      __ z_clij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CGIJ_ZOPC) {
      __ z_cgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else {
      guarantee(instr == CLGIJ_ZOPC, "opcode not implemented");
      __ z_clgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    }
  
#line 20588 "ad_s390.cpp"
  }
}

void cmpbU_RegI_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2292 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CLIJ_ZOPC /*primary()*/);
    if (instr == CIJ_ZOPC) {
      __ z_cij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CLIJ_ZOPC) {
      __ z_clij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CGIJ_ZOPC) {
      __ z_cgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else {
      guarantee(instr == CLGIJ_ZOPC, "opcode not implemented");
      __ z_clgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    }
  
#line 20625 "ad_s390.cpp"
  }
}

void cmpb_RegL_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2292 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CGIJ_ZOPC /*primary()*/);
    if (instr == CIJ_ZOPC) {
      __ z_cij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constantL(), cc, l);
    } else if (instr == CLIJ_ZOPC) {
      __ z_clij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constantL(), cc, l);
    } else if (instr == CGIJ_ZOPC) {
      __ z_cgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constantL(), cc, l);
    } else {
      guarantee(instr == CLGIJ_ZOPC, "opcode not implemented");
      __ z_clgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constantL(), cc, l);
    }
  
#line 20662 "ad_s390.cpp"
  }
}

void cmpb_RegP_immPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2292 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CLGIJ_ZOPC /*primary()*/);
    if (instr == CIJ_ZOPC) {
      __ z_cij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CLIJ_ZOPC) {
      __ z_clij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CGIJ_ZOPC) {
      __ z_cgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else {
      guarantee(instr == CLGIJ_ZOPC, "opcode not implemented");
      __ z_clgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    }
  
#line 20699 "ad_s390.cpp"
  }
}

void cmpb_RegN_immP0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2292 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CLGIJ_ZOPC /*primary()*/);
    if (instr == CIJ_ZOPC) {
      __ z_cij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CLIJ_ZOPC) {
      __ z_clij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CGIJ_ZOPC) {
      __ z_cgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else {
      guarantee(instr == CLGIJ_ZOPC, "opcode not implemented");
      __ z_clgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    }
  
#line 20736 "ad_s390.cpp"
  }
}

void cmpb_RegN_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2292 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    Assembler::branch_condition cc = (Assembler::branch_condition)opnd_array(1)->ccode();
    unsigned long instr = (CLGIJ_ZOPC /*primary()*/);
    if (instr == CIJ_ZOPC) {
      __ z_cij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CLIJ_ZOPC) {
      __ z_clij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else if (instr == CGIJ_ZOPC) {
      __ z_cgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    } else {
      guarantee(instr == CLGIJ_ZOPC, "opcode not implemented");
      __ z_clgij(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant(), cc, l);
    }
  
#line 20773 "ad_s390.cpp"
  }
}

void testAndBranchLoopEnd_RegFarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2267 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CR_ZOPC /*primary()*/);
    if (instr == CR_ZOPC) {
      __ z_cr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CLR_ZOPC) {
      __ z_clr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CGR_ZOPC) {
      __ z_cgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else {
      guarantee(instr == CLGR_ZOPC, "opcode not implemented");
      __ z_clgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 20811 "ad_s390.cpp"
  }
}

void cmpb_RegI_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2267 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CR_ZOPC /*primary()*/);
    if (instr == CR_ZOPC) {
      __ z_cr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CLR_ZOPC) {
      __ z_clr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CGR_ZOPC) {
      __ z_cgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else {
      guarantee(instr == CLGR_ZOPC, "opcode not implemented");
      __ z_clgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 20849 "ad_s390.cpp"
  }
}

void cmpbU_RegI_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2267 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CLR_ZOPC /*primary()*/);
    if (instr == CR_ZOPC) {
      __ z_cr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CLR_ZOPC) {
      __ z_clr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CGR_ZOPC) {
      __ z_cgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else {
      guarantee(instr == CLGR_ZOPC, "opcode not implemented");
      __ z_clgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 20887 "ad_s390.cpp"
  }
}

void cmpb_RegL_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2267 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CGR_ZOPC /*primary()*/);
    if (instr == CR_ZOPC) {
      __ z_cr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CLR_ZOPC) {
      __ z_clr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CGR_ZOPC) {
      __ z_cgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else {
      guarantee(instr == CLGR_ZOPC, "opcode not implemented");
      __ z_clgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 20925 "ad_s390.cpp"
  }
}

void cmpb_RegPP_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2267 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CLGR_ZOPC /*primary()*/);
    if (instr == CR_ZOPC) {
      __ z_cr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CLR_ZOPC) {
      __ z_clr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CGR_ZOPC) {
      __ z_cgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else {
      guarantee(instr == CLGR_ZOPC, "opcode not implemented");
      __ z_clgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 20963 "ad_s390.cpp"
  }
}

void cmpb_RegNN_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2267 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CLGR_ZOPC /*primary()*/);
    if (instr == CR_ZOPC) {
      __ z_cr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CLR_ZOPC) {
      __ z_clr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else if (instr == CGR_ZOPC) {
      __ z_cgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    } else {
      guarantee(instr == CLGR_ZOPC, "opcode not implemented");
      __ z_clgr(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */);
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 21001 "ad_s390.cpp"
  }
}

void testAndBranchLoopEnd_ImmFarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2316 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CHI_ZOPC /*primary()*/);
    if (instr == CHI_ZOPC) {
      __ z_chi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CLFI_ZOPC) {
      __ z_clfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CGHI_ZOPC) {
      __ z_cghi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else {
      guarantee(instr == CLGFI_ZOPC, "opcode not implemented");
      __ z_clgfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 21039 "ad_s390.cpp"
  }
}

void cmpb_RegI_imm_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2316 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CHI_ZOPC /*primary()*/);
    if (instr == CHI_ZOPC) {
      __ z_chi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CLFI_ZOPC) {
      __ z_clfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CGHI_ZOPC) {
      __ z_cghi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else {
      guarantee(instr == CLGFI_ZOPC, "opcode not implemented");
      __ z_clgfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 21077 "ad_s390.cpp"
  }
}

void cmpbU_RegI_imm_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2316 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CLFI_ZOPC /*primary()*/);
    if (instr == CHI_ZOPC) {
      __ z_chi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CLFI_ZOPC) {
      __ z_clfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CGHI_ZOPC) {
      __ z_cghi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else {
      guarantee(instr == CLGFI_ZOPC, "opcode not implemented");
      __ z_clgfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 21115 "ad_s390.cpp"
  }
}

void cmpb_RegL_imm_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2316 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CGHI_ZOPC /*primary()*/);
    if (instr == CHI_ZOPC) {
      __ z_chi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constantL());
    } else if (instr == CLFI_ZOPC) {
      __ z_clfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constantL());
    } else if (instr == CGHI_ZOPC) {
      __ z_cghi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constantL());
    } else {
      guarantee(instr == CLGFI_ZOPC, "opcode not implemented");
      __ z_clgfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constantL());
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 21153 "ad_s390.cpp"
  }
}

void cmpb_RegP_immP_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2316 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CLGFI_ZOPC /*primary()*/);
    if (instr == CHI_ZOPC) {
      __ z_chi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CLFI_ZOPC) {
      __ z_clfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CGHI_ZOPC) {
      __ z_cghi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else {
      guarantee(instr == CLGFI_ZOPC, "opcode not implemented");
      __ z_clgfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 21191 "ad_s390.cpp"
  }
}

void cmpb_RegN_immP0_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2316 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CLGFI_ZOPC /*primary()*/);
    if (instr == CHI_ZOPC) {
      __ z_chi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CLFI_ZOPC) {
      __ z_clfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CGHI_ZOPC) {
      __ z_cghi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else {
      guarantee(instr == CLGFI_ZOPC, "opcode not implemented");
      __ z_clgfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 21229 "ad_s390.cpp"
  }
}

void cmpb_RegN_immN_FarNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2316 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label* p = opnd_array(4)->label();

    // 'p' is `nullptr' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (nullptr == p) ? d : *(p);

    unsigned long instr = (CLGFI_ZOPC /*primary()*/);
    if (instr == CHI_ZOPC) {
      __ z_chi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CLFI_ZOPC) {
      __ z_clfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else if (instr == CGHI_ZOPC) {
      __ z_cghi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    } else {
      guarantee(instr == CLGFI_ZOPC, "opcode not implemented");
      __ z_clgfi(opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->constant());
    }

    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 21267 "ad_s390.cpp"
  }
}

void cmpL3_reg_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 9849 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    // compare registers
    __ z_cgr(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    // Convert condition code into -1,0,1, where
    // -1 means less
    //  0 means equal
    //  1 means greater.
    if (VM_Version::has_LoadStoreConditional()) {
      Register one       = Z_R0_scratch;
      Register minus_one = Z_R1_scratch;
      __ z_lghi(minus_one, -1);
      __ z_lghi(one, 1);
      __ z_lghi( opnd_array(0)->as_Register(ra_,this)/* dst */, 0);
      __ z_locgr(opnd_array(0)->as_Register(ra_,this)/* dst */, one,       Assembler::bcondHigh);
      __ z_locgr(opnd_array(0)->as_Register(ra_,this)/* dst */, minus_one, Assembler::bcondLow);
    } else {
      __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, true, false);
      __ z_bre(done);
      __ z_lhi(opnd_array(0)->as_Register(ra_,this)/* dst */, 1);
      __ z_brh(done);
      __ z_lhi(opnd_array(0)->as_Register(ra_,this)/* dst */, -1);
    }
    __ bind(done);
  
#line 21304 "ad_s390.cpp"
  }
}

uint cmpL3_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 24);
}

void safePointNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {

#line 1995 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ unimplemented("Unimplemented mach node encoding in AD file.", 13);
  
#line 21323 "ad_s390.cpp"
  }
}

void safePoint_pollNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// cr
  {

#line 9894 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // Mark the code position where the load from the safepoint
    // polling page was emitted as relocInfo::poll_type.
    __ relocate(relocInfo::poll_type);
    __ load_from_polling_page(opnd_array(1)->as_Register(ra_,this,idx1)/* poll */);
  
#line 21340 "ad_s390.cpp"
  }
}

void CallStaticJavaDirect_dynTOCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2366 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // Call to fixup routine. Fixup routine uses ScopeDesc info to determine
    // whom we intended to call.
    int ret_offset = 0;

    if (!_method) {
      ret_offset = emit_call_reloc(masm, opnd_array(1)->method(),
                                   relocInfo::runtime_call_w_cp_type, ra_);
    } else {
      int method_index = resolved_method_index(masm);
      if (_optimized_virtual) {
        ret_offset = emit_call_reloc(masm, opnd_array(1)->method(),
                                     opt_virtual_call_Relocation::spec(method_index));
      } else {
        ret_offset = emit_call_reloc(masm, opnd_array(1)->method(),
                                     static_call_Relocation::spec(method_index));
      }
    }
    assert(__ inst_mark() != nullptr, "emit_call_reloc must set_inst_mark()");

    if (_method) { // Emit stub for static call.
      address stub = CompiledDirectCall::emit_to_interp_stub(masm);
      if (stub == nullptr) {
        __ clear_inst_mark();
        ciEnv::current()->record_failure("CodeCache is full");
        return;
      }
    }

    __ clear_inst_mark();
  
#line 21382 "ad_s390.cpp"
  }
}

void CallDynamicJavaDirect_dynTOCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2399 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    unsigned int start_off = __ offset();

    int vtable_index = this->_vtable_index;
    if (vtable_index == -4) {
      Register ic_reg = reg_to_register_object(Matcher::inline_cache_reg_encode());
      address virtual_call_oop_addr = nullptr;

      AddressLiteral empty_ic((address) Universe::non_oop_word());
      virtual_call_oop_addr = __ pc();
      bool success = __ load_const_from_toc(ic_reg, empty_ic);
      if (!success) {
        Compile::current()->env()->record_out_of_memory_failure();
        return;
      }

      // Call to fixup routine. Fixup routine uses ScopeDesc info
      // to determine who we intended to call.
      int method_index = resolved_method_index(masm);
      __ relocate(virtual_call_Relocation::spec(virtual_call_oop_addr, method_index));
      unsigned int ret_off = __ offset();
      assert(__ offset() - start_off == 6, "bad prelude len: %d", __ offset() - start_off);
      ret_off += emit_call_reloc(masm, opnd_array(1)->method(), relocInfo::none, ra_);
      __ clear_inst_mark();
      assert(_method, "lazy_constant may be wrong when _method==null");
    } else {
      assert(!UseInlineCaches, "expect vtable calls only if not using ICs");
      // Go through the vtable. Get receiver klass. Receiver already
      // checked for non-null. If we'll go thru a C2I adapter, the
      // interpreter expects method in Z_method.
      // Use Z_method to temporarily hold the klass oop.
      // Z_R1_scratch is destroyed.
      __ load_klass(Z_method, Z_R2);

      int entry_offset = in_bytes(Klass::vtable_start_offset()) + vtable_index * vtableEntry::size_in_bytes();
      int v_off        = entry_offset + in_bytes(vtableEntry::method_offset());

      if (Displacement::is_validDisp(v_off) ) {
        // Can use load instruction with large offset.
        __ z_lg(Z_method, Address(Z_method /*class oop*/, v_off /*method offset*/));
      } else {
        // Worse case, must load offset into register.
        __ load_const(Z_R1_scratch, v_off);
        __ z_lg(Z_method, Address(Z_method /*class oop*/, Z_R1_scratch /*method offset*/));
      }
      // NOTE: for vtable dispatches, the vtable entry will never be
      // null. However it may very well end up in handle_wrong_method
      // if the method is abstract for the particular class.
      __ z_lg(Z_R1_scratch, Address(Z_method, Method::from_compiled_offset()));
      // Call target. Either compiled code or C2I adapter.
      __ z_basr(Z_R14, Z_R1_scratch);
      unsigned int ret_off = __ offset();
    }
  
#line 21447 "ad_s390.cpp"
  }
}

void CallRuntimeDirectNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2342 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // Save return pc before call to the place where we need it, since
    // callee doesn't.
    unsigned int start_off = __ offset();
    // Compute size of "larl + stg + call_c_opt".
    const int size_of_code = 6 + 6 + MacroAssembler::call_far_patchable_size();
    __ get_PC(Z_R14, size_of_code);
    __ save_return_pc();
    assert(__ offset() - start_off == 12, "bad prelude len: %d", __ offset() - start_off);

    assert((__ offset() & 2) == 0, "misaligned z_enc_java_to_runtime_call");
    address call_addr = __ call_c_opt((address)opnd_array(1)->method());
    if (call_addr == nullptr) {
      Compile::current()->env()->record_out_of_memory_failure();
      return;
    }

#ifdef ASSERT
    // Plausibility check for size_of_code assumptions.
    unsigned int actual_ret_off = __ offset();
    assert(start_off + size_of_code == actual_ret_off, "wrong return_pc");
#endif
  
#line 21481 "ad_s390.cpp"
  }
}

void CallLeafDirectNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2342 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // Save return pc before call to the place where we need it, since
    // callee doesn't.
    unsigned int start_off = __ offset();
    // Compute size of "larl + stg + call_c_opt".
    const int size_of_code = 6 + 6 + MacroAssembler::call_far_patchable_size();
    __ get_PC(Z_R14, size_of_code);
    __ save_return_pc();
    assert(__ offset() - start_off == 12, "bad prelude len: %d", __ offset() - start_off);

    assert((__ offset() & 2) == 0, "misaligned z_enc_java_to_runtime_call");
    address call_addr = __ call_c_opt((address)opnd_array(1)->method());
    if (call_addr == nullptr) {
      Compile::current()->env()->record_out_of_memory_failure();
      return;
    }

#ifdef ASSERT
    // Plausibility check for size_of_code assumptions.
    unsigned int actual_ret_off = __ offset();
    assert(start_off + size_of_code == actual_ret_off, "wrong return_pc");
#endif
  
#line 21515 "ad_s390.cpp"
  }
}

void CallLeafNoFPDirectNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2342 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // Save return pc before call to the place where we need it, since
    // callee doesn't.
    unsigned int start_off = __ offset();
    // Compute size of "larl + stg + call_c_opt".
    const int size_of_code = 6 + 6 + MacroAssembler::call_far_patchable_size();
    __ get_PC(Z_R14, size_of_code);
    __ save_return_pc();
    assert(__ offset() - start_off == 12, "bad prelude len: %d", __ offset() - start_off);

    assert((__ offset() & 2) == 0, "misaligned z_enc_java_to_runtime_call");
    address call_addr = __ call_c_opt((address)opnd_array(1)->method());
    if (call_addr == nullptr) {
      Compile::current()->env()->record_out_of_memory_failure();
      return;
    }

#ifdef ASSERT
    // Plausibility check for size_of_code assumptions.
    unsigned int actual_ret_off = __ offset();
    assert(start_off + size_of_code == actual_ret_off, "wrong return_pc");
#endif
  
#line 21549 "ad_s390.cpp"
  }
}

void TailCalljmpIndNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// method_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  {

#line 9979 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_br(opnd_array(1)->as_Register(ra_,this,idx1)/* jump_target */); 
#line 21562 "ad_s390.cpp"
  }
}

uint TailCalljmpIndNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void RetNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {

#line 9988 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_br(Z_R14); 
#line 21579 "ad_s390.cpp"
  }
}

uint RetNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void tailjmpIndNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// ex_oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  {

#line 10003 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lg(Z_ARG2/* issuing pc */, _z_abi(return_pc), Z_SP);
    __ z_br(opnd_array(1)->as_Register(ra_,this,idx1)/* jump_target */);
  
#line 21600 "ad_s390.cpp"
  }
}

uint tailjmpIndNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void ForwardExceptionjmpNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {

#line 10015 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ set_inst_mark();
    __ load_const_optimized(Z_R1_scratch, (address)StubRoutines::forward_exception_entry());
    __ z_br(Z_R1_scratch);
    __ clear_inst_mark();
  
#line 21622 "ad_s390.cpp"
  }
}

void CreateExceptionNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint CreateExceptionNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void RethrowExceptionNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {

#line 10043 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ set_inst_mark();
    __ load_const_optimized(Z_R1_scratch, (address)OptoRuntime::rethrow_stub());
    __ z_br(Z_R1_scratch);
    __ clear_inst_mark();
  
#line 21651 "ad_s390.cpp"
  }
}

void ShouldNotReachHereNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {

#line 10057 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    if (is_reachable()) {
      const char* str = __ code_string(_halt_reason);
      __ stop(str);
    }
  
#line 21668 "ad_s390.cpp"
  }
}

void partialSubtypeCheckNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// sub
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// super
  {

#line 10079 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral stub_address(StubRoutines::zarch::partial_subtype_check());
    __ load_const_optimized(Z_ARG4, stub_address);
    __ z_basr(Z_R14, Z_ARG4);
  
#line 21685 "ad_s390.cpp"
  }
}

void partialSubtypeCheckVarSuperNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// sub
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// super
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// temp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// temp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// temp3
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// temp4
  {

#line 10102 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ lookup_secondary_supers_table_var(opnd_array(1)->as_Register(ra_,this,idx1)/* sub */, opnd_array(2)->as_Register(ra_,this,idx2)/* super */,
                                         opnd_array(3)->as_Register(ra_,this,idx3)/* temp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* temp2 */, opnd_array(5)->as_Register(ra_,this,idx5)/* temp3 */, opnd_array(6)->as_Register(ra_,this,idx6)/* temp4 */,
                                         opnd_array(0)->as_Register(ra_,this)/* result */);
  
#line 21706 "ad_s390.cpp"
  }
}

void partialSubtypeCheckConstSuperNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// sub
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// super
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// super_con
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// temp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// temp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// temp3
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// temp4
  {

#line 10120 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    u1 super_klass_slot = ((Klass*)opnd_array(3)->constant())->hash_slot();
    if (InlineSecondarySupersTest) {
      __ lookup_secondary_supers_table_const(opnd_array(1)->as_Register(ra_,this,idx1)/* sub */, opnd_array(2)->as_Register(ra_,this,idx2)/* super */,
                                             opnd_array(4)->as_Register(ra_,this,idx4)/* temp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* temp2 */, opnd_array(6)->as_Register(ra_,this,idx6)/* temp3 */,
                                             opnd_array(7)->as_Register(ra_,this,idx7)/* temp4 */, opnd_array(0)->as_Register(ra_,this)/* result */, super_klass_slot);
    } else {
      AddressLiteral stub_address(StubRoutines::lookup_secondary_supers_table_stub(super_klass_slot));
      __ load_const_optimized(Z_ARG4, stub_address);
      __ z_basr(Z_R14, Z_ARG4);
    }

  
#line 21736 "ad_s390.cpp"
  }
}

void cmpFastLockNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  {

#line 10146 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ fast_lock(opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */, opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */);
    // If locking was successful, cc should indicate 'EQ'.
    // The compiler generates a branch to the runtime call to
    // _complete_monitor_locking_Java for the case where cc is 'NE'.
  
#line 21756 "ad_s390.cpp"
  }
}

void cmpFastUnlockNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  {

#line 10161 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ fast_unlock(opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */, opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */);
    // If unlocking was successful, cc should indicate 'EQ'.
    // The compiler generates a branch to the runtime call to
    // _complete_monitor_unlocking_Java for the case where cc is 'NE'.
  
#line 21776 "ad_s390.cpp"
  }
}

void inlineCallClearArrayConstNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {

#line 10176 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ Clear_Array_Const(opnd_array(1)->constantL(), opnd_array(2)->as_Register(ra_,this,idx2)/* base */); 
#line 21789 "ad_s390.cpp"
  }
}

void inlineCallClearArrayConstBigNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmpL
  {

#line 10186 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ Clear_Array_Const_Big(opnd_array(1)->constantL(), opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(3)->as_Register(ra_,this,idx3)/* tmpL */); 
#line 21803 "ad_s390.cpp"
  }
}

void inlineCallClearArrayNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmpL
  {

#line 10196 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ Clear_Array(opnd_array(1)->as_Register(ra_,this,idx1)/* cnt */, opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(3)->as_Register(ra_,this,idx3)/* tmpL */); 
#line 21817 "ad_s390.cpp"
  }
}

void string_equalsLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// oddReg
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// evenReg
  {

#line 10210 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ array_equals(false, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* str2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* cnt */, opnd_array(4)->as_Register(ra_,this,idx4)/* oddReg */, opnd_array(5)->as_Register(ra_,this,idx5)/* evenReg */,
                    opnd_array(0)->as_Register(ra_,this)/* result */, true /* byte */);
  
#line 21837 "ad_s390.cpp"
  }
}

void string_equals_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  {

#line 10224 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    const int cnt_imm = opnd_array(3)->constant();
    if (cnt_imm) { __ z_clc(0, cnt_imm - 1, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, 0, opnd_array(2)->as_Register(ra_,this,idx2)/* str2 */); }
    __ z_lhi(opnd_array(0)->as_Register(ra_,this)/* result */, 1);
    if (cnt_imm) {
      if (VM_Version::has_LoadStoreConditional()) {
        __ z_lhi(Z_R0_scratch, 0);
        __ z_locr(opnd_array(0)->as_Register(ra_,this)/* result */, Z_R0_scratch, Assembler::bcondNotEqual);
      } else {
        Label Lskip;
        __ z_bre(Lskip);
        __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* result */);
        __ bind(Lskip);
      }
    }
  
#line 21866 "ad_s390.cpp"
  }
}

void string_equalsC_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  {

#line 10249 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    const int cnt_imm = opnd_array(3)->constant(); // positive immI8 (7 bits used)
    if (cnt_imm) { __ z_clc(0, (cnt_imm << 1) - 1, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, 0, opnd_array(2)->as_Register(ra_,this,idx2)/* str2 */); }
    __ z_lhi(opnd_array(0)->as_Register(ra_,this)/* result */, 1);
    if (cnt_imm) {
      if (VM_Version::has_LoadStoreConditional()) {
        __ z_lhi(Z_R0_scratch, 0);
        __ z_locr(opnd_array(0)->as_Register(ra_,this)/* result */, Z_R0_scratch, Assembler::bcondNotEqual);
      } else {
        Label Lskip;
        __ z_bre(Lskip);
        __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* result */);
        __ bind(Lskip);
      }
    }
  
#line 21895 "ad_s390.cpp"
  }
}

void array_equalsBNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// oddReg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// evenReg
  {

#line 10275 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ array_equals(true, opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* ary2 */,
                    noreg, opnd_array(3)->as_Register(ra_,this,idx3)/* oddReg */, opnd_array(4)->as_Register(ra_,this,idx4)/* evenReg */,
                    opnd_array(0)->as_Register(ra_,this)/* result */, true /* byte */);
  
#line 21914 "ad_s390.cpp"
  }
}

void array_equalsCNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// oddReg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// evenReg
  {

#line 10289 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ array_equals(true, opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* ary2 */,
                    noreg, opnd_array(3)->as_Register(ra_,this,idx3)/* oddReg */, opnd_array(4)->as_Register(ra_,this,idx4)/* evenReg */,
                    opnd_array(0)->as_Register(ra_,this)/* result */, false /* byte */);
  
#line 21933 "ad_s390.cpp"
  }
}

void string_compareLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10304 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::LL);
  
#line 21956 "ad_s390.cpp"
  }
}

void string_compareUNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10319 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::UU);
  
#line 21979 "ad_s390.cpp"
  }
}

void string_compareLUNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10334 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::LU);
  
#line 22002 "ad_s390.cpp"
  }
}

void string_compareULNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10349 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compare(opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */,
                      opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */, opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::UL);
  
#line 22025 "ad_s390.cpp"
  }
}

void indexOfChar_UNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// oddReg
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// evenReg
  {

#line 10365 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof_char(opnd_array(4)->as_Register(ra_,this,idx4)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           opnd_array(3)->as_Register(ra_,this,idx3)/* ch */, 0 /* unused, ch is in register */,
                           opnd_array(5)->as_Register(ra_,this,idx5)/* oddReg */, opnd_array(6)->as_Register(ra_,this,idx6)/* evenReg */, false /*is_byte*/);
  
#line 22047 "ad_s390.cpp"
  }
}

void indexOfChar_LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// oddReg
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// evenReg
  {

#line 10380 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof_char(opnd_array(4)->as_Register(ra_,this,idx4)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           opnd_array(3)->as_Register(ra_,this,idx3)/* ch */, 0 /* unused, ch is in register */,
                           opnd_array(5)->as_Register(ra_,this,idx5)/* oddReg */, opnd_array(6)->as_Register(ra_,this,idx6)/* evenReg */, true /*is_byte*/);
  
#line 22069 "ad_s390.cpp"
  }
}

void indexOf_imm1_UNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10395 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    immPOper *needleOper = (immPOper *)opnd_array(3);
    const TypeOopPtr *t = needleOper->type()->isa_oopptr();
    ciTypeArray* needle_values = t->const_oop()->as_type_array();  // Pointer to live char *
    jchar chr;
#ifdef VM_LITTLE_ENDIAN
    Unimplemented();
#else
    chr = (((jchar)(unsigned char)needle_values->element_value(0).as_byte()) << 8) |
           ((jchar)(unsigned char)needle_values->element_value(1).as_byte());
#endif
    __ string_indexof_char(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           noreg, chr,
                           opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, false /*is_byte*/);
  
#line 22102 "ad_s390.cpp"
  }
}

void indexOf_imm1_LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10420 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    immPOper *needleOper = (immPOper *)opnd_array(3);
    const TypeOopPtr *t = needleOper->type()->isa_oopptr();
    ciTypeArray* needle_values = t->const_oop()->as_type_array();  // Pointer to live char *
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           noreg, chr,
                           opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, true /*is_byte*/);
  
#line 22129 "ad_s390.cpp"
  }
}

void indexOf_imm1_ULNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10439 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    immPOper *needleOper = (immPOper *)opnd_array(3);
    const TypeOopPtr *t = needleOper->type()->isa_oopptr();
    ciTypeArray* needle_values = t->const_oop()->as_type_array();  // Pointer to live char *
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           noreg, chr,
                           opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, false /*is_byte*/);
  
#line 22156 "ad_s390.cpp"
  }
}

void indexOf_imm_UNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10459 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, noreg, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::UU);
  
#line 22179 "ad_s390.cpp"
  }
}

void indexOf_imm_LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10474 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, noreg, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::LL);
  
#line 22202 "ad_s390.cpp"
  }
}

void indexOf_imm_ULNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10489 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, noreg, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::UL);
  
#line 22225 "ad_s390.cpp"
  }
}

void indexOf_UNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10504 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::UU);
  
#line 22248 "ad_s390.cpp"
  }
}

void indexOf_LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10519 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::LL);
  
#line 22271 "ad_s390.cpp"
  }
}

void indexOf_ULNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  {

#line 10534 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::UL);
  
#line 22294 "ad_s390.cpp"
  }
}

void string_compressNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// v16
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// v17
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// v18
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// v19
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// v20
  unsigned idx11 = idx10 + opnd_array(10)->num_edges(); 	// v21
  unsigned idx12 = idx11 + opnd_array(11)->num_edges(); 	// v22
  unsigned idx13 = idx12 + opnd_array(12)->num_edges(); 	// v23
  {

#line 10550 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compress(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */, true, false, opnd_array(6)->as_VectorRegister(ra_,this,idx6)/* v16 */, opnd_array(7)->as_VectorRegister(ra_,this,idx7)/* v17 */, opnd_array(8)->as_VectorRegister(ra_,this,idx8)/* v18 */,
                       opnd_array(9)->as_VectorRegister(ra_,this,idx9)/* v19 */, opnd_array(10)->as_VectorRegister(ra_,this,idx10)/* v20 */, opnd_array(11)->as_VectorRegister(ra_,this,idx11)/* v21 */, opnd_array(12)->as_VectorRegister(ra_,this,idx12)/* v22 */,
                       opnd_array(13)->as_VectorRegister(ra_,this,idx13)/* v23 */);
  
#line 22323 "ad_s390.cpp"
  }
}

void string_inflateNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// v20
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// v21
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// v22
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// v23
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// v24
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// v25
  {

#line 10579 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_inflate(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */, opnd_array(5)->as_VectorRegister(ra_,this,idx5)/* v20 */,
                      opnd_array(6)->as_VectorRegister(ra_,this,idx6)/* v21 */, opnd_array(7)->as_VectorRegister(ra_,this,idx7)/* v22 */, opnd_array(8)->as_VectorRegister(ra_,this,idx8)/* v23 */, opnd_array(9)->as_VectorRegister(ra_,this,idx9)/* v24 */,
                      opnd_array(10)->as_VectorRegister(ra_,this,idx10)/* v25 */);
  
#line 22348 "ad_s390.cpp"
  }
}

void string_inflate_constNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// v20
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// v21
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// v22
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// v23
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// v24
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// v25
  {

#line 10594 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_inflate_const(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */, opnd_array(3)->constant(), opnd_array(5)->as_VectorRegister(ra_,this,idx5)/* v20 */,
                            opnd_array(6)->as_VectorRegister(ra_,this,idx6)/* v21 */, opnd_array(7)->as_VectorRegister(ra_,this,idx7)/* v22 */, opnd_array(8)->as_VectorRegister(ra_,this,idx8)/* v23 */, opnd_array(9)->as_VectorRegister(ra_,this,idx9)/* v24 */,
                            opnd_array(10)->as_VectorRegister(ra_,this,idx10)/* v25 */);
  
#line 22373 "ad_s390.cpp"
  }
}

void count_positivesNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// len
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {

#line 10608 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ count_positives(opnd_array(3)->as_Register(ra_,this,idx3)/* result */, opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* len */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */);
  
#line 22390 "ad_s390.cpp"
  }
}

void encode_iso_arrayNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// v16
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// v17
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// v18
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// v19
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// v20
  unsigned idx11 = idx10 + opnd_array(10)->num_edges(); 	// v21
  unsigned idx12 = idx11 + opnd_array(11)->num_edges(); 	// v22
  unsigned idx13 = idx12 + opnd_array(12)->num_edges(); 	// v23
  {

#line 10623 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compress(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */, true, false, opnd_array(6)->as_VectorRegister(ra_,this,idx6)/* v16 */, opnd_array(7)->as_VectorRegister(ra_,this,idx7)/* v17 */, opnd_array(8)->as_VectorRegister(ra_,this,idx8)/* v18 */,
                       opnd_array(9)->as_VectorRegister(ra_,this,idx9)/* v19 */, opnd_array(10)->as_VectorRegister(ra_,this,idx10)/* v20 */, opnd_array(11)->as_VectorRegister(ra_,this,idx11)/* v21 */, opnd_array(12)->as_VectorRegister(ra_,this,idx12)/* v22 */,
                       opnd_array(13)->as_VectorRegister(ra_,this,idx13)/* v23 */);
  
#line 22419 "ad_s390.cpp"
  }
}

void encode_ascii_arrayNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// v16
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// v17
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// v18
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// v19
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// v20
  unsigned idx11 = idx10 + opnd_array(10)->num_edges(); 	// v21
  unsigned idx12 = idx11 + opnd_array(11)->num_edges(); 	// v22
  unsigned idx13 = idx12 + opnd_array(12)->num_edges(); 	// v23
  {

#line 10641 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compress(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */, true, true, opnd_array(6)->as_VectorRegister(ra_,this,idx6)/* v16 */, opnd_array(7)->as_VectorRegister(ra_,this,idx7)/* v17 */, opnd_array(8)->as_VectorRegister(ra_,this,idx8)/* v18 */,
                       opnd_array(9)->as_VectorRegister(ra_,this,idx9)/* v19 */, opnd_array(10)->as_VectorRegister(ra_,this,idx10)/* v20 */, opnd_array(11)->as_VectorRegister(ra_,this,idx11)/* v21 */, opnd_array(12)->as_VectorRegister(ra_,this,idx12)/* v22 */,
                       opnd_array(13)->as_VectorRegister(ra_,this,idx13)/* v23 */);
  
#line 22448 "ad_s390.cpp"
  }
}

void expand_storeFNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STE_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(masm, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 22476 "ad_s390.cpp"
  }
}

void expand_LoadLogical_I2LNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// mem
  {

#line 2150 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LLGF_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(masm, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(masm, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 22504 "ad_s390.cpp"
  }
}

void expand_Repl2I_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10807 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    if (opnd_array(0)->as_Register(ra_,this)/* dst */== opnd_array(1)->as_Register(ra_,this,idx1)/* src */) {
      __ z_sllg(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 64-32);
      __ z_ogr(opnd_array(0)->as_Register(ra_,this)/* dst */, Z_R0_scratch);
    }  else {
      __ z_sllg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 64-32);
      __ z_ogr( opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    }
  
#line 22524 "ad_s390.cpp"
  }
}

void Repl8B_reg_risbgNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10828 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src */) {
      __ z_lgr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    }
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */, 48, 55,  8, false);
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */, 32, 47, 16, false);
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */,  0, 31, 32, false);
  
#line 22543 "ad_s390.cpp"
  }
}

void Repl8B_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10845 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int64_t  Isrc8 = opnd_array(1)->constant()& 0x000000ff;
    int64_t Isrc16 =  Isrc8 <<  8 |  Isrc8;
    int64_t Isrc32 = Isrc16 << 16 | Isrc16;
    assert(Isrc8 != 0x000000ff && Isrc8 != 0, "should be handled by other match rules.");

    __ z_llilf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
    __ z_iihf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
  
#line 22563 "ad_s390.cpp"
  }
}

void Repl8B_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10863 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laz(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, Z_R0); 
#line 22575 "ad_s390.cpp"
  }
}

void Repl8B_immm1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10873 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, -1); 
#line 22587 "ad_s390.cpp"
  }
}

void Repl4S_reg_risbgNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10884 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src */) {
      __ z_lgr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    }
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */, 32, 47, 16, false);
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */,  0, 31, 32, false);
  
#line 22605 "ad_s390.cpp"
  }
}

void Repl4S_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10900 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int64_t Isrc16 = opnd_array(1)->constant()& 0x0000ffff;
    int64_t Isrc32 = Isrc16 << 16 | Isrc16;
    assert(Isrc16 != 0x0000ffff && Isrc16 != 0, "Repl4S_imm: (src == " INT64_FORMAT
           ") should be handled by other match rules.", opnd_array(1)->constant());

    __ z_llilf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
    __ z_iihf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
  
#line 22625 "ad_s390.cpp"
  }
}

void Repl4S_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10918 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laz(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, Z_R0); 
#line 22637 "ad_s390.cpp"
  }
}

void Repl4S_immm1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10928 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, -1); 
#line 22649 "ad_s390.cpp"
  }
}

void repl8S_reg_ExNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10938 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vlvgh(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ z_vreph(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, 0);
  
#line 22664 "ad_s390.cpp"
  }
}

uint repl8S_reg_ExNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void repl8S_immIminus1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10952 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

     __ z_vone(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */);
  
#line 22683 "ad_s390.cpp"
  }
}

uint repl8S_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void repl8S_immI0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {

#line 10965 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

     __ z_vzero(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */);
  
#line 22702 "ad_s390.cpp"
  }
}

uint repl8S_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void Repl2I_reg_risbgNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10978 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src */) {
      __ z_lgr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    }
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */, 0, 31, 32, false);
  
#line 22724 "ad_s390.cpp"
  }
}

void Repl2I_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 10993 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int64_t Isrc32 = opnd_array(1)->constant();
    assert(Isrc32 != -1 && Isrc32 != 0, "should be handled by other match rules.");

    __ z_llilf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
    __ z_iihf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
  
#line 22742 "ad_s390.cpp"
  }
}

void Repl2I_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11009 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laz(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, Z_R0); 
#line 22754 "ad_s390.cpp"
  }
}

void Repl2I_immm1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11019 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, -1); 
#line 22766 "ad_s390.cpp"
  }
}

void repl4I_reg_ExNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11029 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vlvgf(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ z_vrepf(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, 0);
  
#line 22781 "ad_s390.cpp"
  }
}

uint repl4I_reg_ExNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void repl4I_immI0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {

#line 11043 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vzero(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */);
  
#line 22800 "ad_s390.cpp"
  }
}

uint repl4I_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void repl4I_immIminus1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11056 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vone(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */);
  
#line 22819 "ad_s390.cpp"
  }
}

uint repl4I_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void Repl2F_reg_directNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11084 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(VM_Version::has_FPSupportEnhancements(), "encoder should never be called on old H/W");
    __ z_lgdr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);

    __ z_srlg(Z_R0_scratch, opnd_array(0)->as_Register(ra_,this)/* dst */, 32);  // Floats are left-justified in 64bit reg.
    __ z_iilf(opnd_array(0)->as_Register(ra_,this)/* dst */, 0);                 // Save a "result not ready" stall.
    __ z_ogr(opnd_array(0)->as_Register(ra_,this)/* dst */, Z_R0_scratch);
  
#line 22843 "ad_s390.cpp"
  }
}

void Repl2F_immNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11101 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    union {
      int   Isrc32;
      float Fsrc32;
    };
    Fsrc32 = opnd_array(1)->constantF();
    __ z_llilf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
    __ z_iihf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
  
#line 22863 "ad_s390.cpp"
  }
}

void Repl2F_imm0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11120 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laz(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, Z_R0); 
#line 22875 "ad_s390.cpp"
  }
}

void repl4F_reg_ExNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11132 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vrepf(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */->to_vr(), 0);
  
#line 22889 "ad_s390.cpp"
  }
}

uint repl4F_reg_ExNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void repl4F_immF0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {

#line 11145 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

     __ z_vzero(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */);
  
#line 22908 "ad_s390.cpp"
  }
}

uint repl4F_immF0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void repl2D_reg_ExNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11159 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vrepg(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */->to_vr(), 0);
  
#line 22927 "ad_s390.cpp"
  }
}

uint repl2D_reg_ExNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void repl2D_immD0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {

#line 11172 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

     __ z_vzero(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */);
  
#line 22946 "ad_s390.cpp"
  }
}

uint repl2D_immD0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void repl16B_reg_ExNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11184 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vlvgb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ z_vrepb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, 0);
  
#line 22966 "ad_s390.cpp"
  }
}

uint repl16B_reg_ExNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void repl16B_immIminus1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11198 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

     __ z_vone(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */);
  
#line 22985 "ad_s390.cpp"
  }
}

uint repl16B_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void repl16B_immI0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {

#line 11211 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

     __ z_vzero(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */);
  
#line 23004 "ad_s390.cpp"
  }
}

uint repl16B_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void repl2L_reg_ExNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11223 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vlvgg(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ z_vrepg(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, 0);
  
#line 23024 "ad_s390.cpp"
  }
}

uint repl2L_reg_ExNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void repl2L_immIminus1Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11237 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

     __ z_vone(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */);
  
#line 23043 "ad_s390.cpp"
  }
}

uint repl2L_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void repl2L_immI0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {

#line 11250 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

     __ z_vzero(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */);
  
#line 23062 "ad_s390.cpp"
  }
}

uint repl2L_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void storeA8BNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (STG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 23106 "ad_s390.cpp"
  }
}

void storeV16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 11279 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vst(opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src */,
              Address(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), as_Register(opnd_array(1)->index(ra_,this,idx1)), opnd_array(1)->disp(ra_,this,idx1)));
  
#line 23122 "ad_s390.cpp"
  }
}

uint storeV16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadV8Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2168 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(masm, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(masm, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 23165 "ad_s390.cpp"
  }
}

void loadV16Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 11305 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

     __ z_vl(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */,
              Address(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), as_Register(opnd_array(1)->index(ra_,this,idx1)), opnd_array(1)->disp(ra_,this,idx1)));
  
#line 23180 "ad_s390.cpp"
  }
}

uint loadV16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void reinterpretNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

void reinterpretXNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

void vadd16B_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11338 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vab(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23214 "ad_s390.cpp"
  }
}

uint vadd16B_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vadd8S_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11349 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vah(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23234 "ad_s390.cpp"
  }
}

uint vadd8S_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vadd4I_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11360 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vaf(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23254 "ad_s390.cpp"
  }
}

uint vadd4I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vadd2L_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11371 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vag(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23274 "ad_s390.cpp"
  }
}

uint vadd2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vmul16B_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11382 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vmlb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23294 "ad_s390.cpp"
  }
}

uint vmul16B_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vmul8S_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11393 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vmlhw(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23314 "ad_s390.cpp"
  }
}

uint vmul8S_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vmul4I_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11404 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vmlf(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23334 "ad_s390.cpp"
  }
}

uint vmul4I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vsub16B_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11415 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vsb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23354 "ad_s390.cpp"
  }
}

uint vsub16B_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vsub8S_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11426 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vsh(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23374 "ad_s390.cpp"
  }
}

uint vsub8S_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vsub4I_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11437 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vsf(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23394 "ad_s390.cpp"
  }
}

uint vsub4I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vsub2L_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11448 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vsg(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23414 "ad_s390.cpp"
  }
}

uint vsub2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vadd4F_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11459 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vfasb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23434 "ad_s390.cpp"
  }
}

uint vadd4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vadd2D_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11470 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vfadb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23454 "ad_s390.cpp"
  }
}

uint vadd2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vsub4F_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11481 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vfssb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23474 "ad_s390.cpp"
  }
}

uint vsub4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vsub2D_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11492 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vfsdb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23494 "ad_s390.cpp"
  }
}

uint vsub2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vmul4F_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11503 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vfmsb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23514 "ad_s390.cpp"
  }
}

uint vmul4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vmul2D_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11514 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vfmdb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23534 "ad_s390.cpp"
  }
}

uint vmul2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vdiv4F_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11525 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vfdsb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23554 "ad_s390.cpp"
  }
}

uint vdiv4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vdiv2D_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 11536 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vfddb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorRegister(ra_,this,idx2)/* src2 */);
  
#line 23574 "ad_s390.cpp"
  }
}

uint vdiv2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vsqrt4F_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11549 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vfsqsb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src */);
  
#line 23593 "ad_s390.cpp"
  }
}

uint vsqrt4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vsqrt2D_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11560 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_vfsqdb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src */);
  
#line 23612 "ad_s390.cpp"
  }
}

uint vsqrt2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vpopcnt_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11572 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    BasicType bt = Matcher::vector_element_basic_type(this);
    switch (bt) {
      case T_BYTE:
        __ z_vpopctb(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src */);
        break;
      case T_SHORT:
        __ z_vpopcth(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src */);
        break;
      case T_INT:
        __ z_vpopctf(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src */);
        break;
      case T_LONG:
        __ z_vpopctg(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src */);
        break;
      default:
        ShouldNotReachHere();
    }
  
#line 23647 "ad_s390.cpp"
  }
}

uint vpopcnt_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void vround2D_regNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rmode
  {

#line 11600 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    switch (opnd_array(2)->constant()) {
      case RoundDoubleModeNode::rmode_rint:
        __ z_vflrd(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src */, 0);
        break;
      case RoundDoubleModeNode::rmode_floor:
        __ z_vflrd(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src */, 7);
        break;
      case RoundDoubleModeNode::rmode_ceil:
        __ z_vflrd(opnd_array(0)->as_VectorRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorRegister(ra_,this,idx1)/* src */, 6);
        break;
      default:
        ShouldNotReachHere();
    }
  
#line 23679 "ad_s390.cpp"
  }
}

uint vround2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void bytes_reverse_shortNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11631 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lrvr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    __ z_sra(opnd_array(0)->as_Register(ra_,this)/* dst */, 0x0010);
  
#line 23699 "ad_s390.cpp"
  }
}

uint bytes_reverse_shortNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void bytes_reverse_unsigned_shortNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11647 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lrvr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    __ z_srl(opnd_array(0)->as_Register(ra_,this)/* dst */, 0x0010);
  
#line 23719 "ad_s390.cpp"
  }
}

uint bytes_reverse_unsigned_shortNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void bytes_reverse_intNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LRVR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LRVR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 23741 "ad_s390.cpp"
  }
}

uint bytes_reverse_intNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void bytes_reverse_longNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2013 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LRVGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(masm, (LRVGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 23763 "ad_s390.cpp"
  }
}

void countLeadingZerosINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11694 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    // Performance experiments indicate that "FLOGR" is using some kind of
    // iteration to find the leftmost "1" bit.
    //
    // The prior implementation zero-extended the 32-bit argument to 64 bit,
    // thus forcing "FLOGR" to count 32 bits of which we know they are zero.
    // We could gain measurable speedup in micro benchmark:
    //
    //               leading   trailing
    //   z10:   int     2.04       1.68
    //         long     1.00       1.02
    //   z196:  int     0.99       1.23
    //         long     1.00       1.11
    //
    // By shifting the argument into the high-word instead of zero-extending it.
    // The add'l branch on condition (taken for a zero argument, very infrequent,
    // good prediction) is well compensated for by the savings.
    //
    // We leave the previous implementation in for some time in the future when
    // the "FLOGR" instruction may become less iterative.

    // Version 2: shows 62%(z9), 204%(z10), -1%(z196) improvement over original
    __ z_sllg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 32); // No need to always count 32 zeroes first.
    __ z_iilh(opnd_array(0)->as_Register(ra_,this)/* dst */, 0x8000);   // Insert "stop bit" to force result 32 for zero src.
    __ z_flogr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */);
  
#line 23800 "ad_s390.cpp"
  }
}

uint countLeadingZerosINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 14, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 14);
}

void countLeadingZerosLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 11729 "/work/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_flogr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 23817 "ad_s390.cpp"
  }
}

uint countLeadingZerosLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void countTrailingZerosINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 11762 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(2)->as_Register(ra_,this,idx2)/* dst */;
    Register Rsrc = opnd_array(1)->as_Register(ra_,this,idx1)/* src */;
    // Rtmp only needed for for zero-argument shortcut. With kill effect in
    // match rule Rsrc = roddReg would be possible, saving one register.
    Register Rtmp = opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */;

    assert_different_registers(Rdst, Rsrc, Rtmp);

    // Algorithm:
    // - Isolate the least significant (rightmost) set bit using (src & (-src)).
    //   All other bits in the result are zero.
    // - Find the "leftmost one" bit position in the single-bit result from previous step.
    // - 63-("leftmost one" bit position) gives the # of trailing zeros.

    // Version 2: shows 79%(z9), 68%(z10), 23%(z196) improvement over original.
    Label done;
    __ load_const_optimized(Rdst, 32); // Prepare for shortcut (zero argument), result will be 32.
    __ z_lcgfr(Rtmp, Rsrc);
    __ z_bre(done);                    // Taken very infrequently, good prediction, no BHT entry.

    __ z_nr(Rtmp, Rsrc);               // (src) & (-src) leaves nothing but least significant bit.
    __ z_ahi(Rtmp,  -1);               // Subtract one to fill all trailing zero positions with ones.
                                       // Use 32bit op to prevent borrow propagation (case Rdst = 0x80000000)
                                       // into upper half of reg. Not relevant with sllg below.
    __ z_sllg(Rdst, Rtmp, 32);         // Shift interesting contents to upper half of register.
    __ z_bre(done);                    // Shortcut for argument = 1, result will be 0.
                                       // Depends on CC set by ahi above.
                                       // Taken very infrequently, good prediction, no BHT entry.
                                       // Branch delayed to have Rdst set correctly (Rtmp == 0(32bit)
                                       // after SLLG Rdst == 0(64bit)).
    __ z_flogr(Rdst, Rdst);            // Kills tmp which is the oddReg for dst.
    __ add2reg(Rdst,  -32);            // 32-pos(leftmost1) is #trailing zeros
    __ z_lcgfr(Rdst, Rdst);            // Provide 64bit result at no cost.
    __ bind(done);
  
#line 23871 "ad_s390.cpp"
  }
}

void countTrailingZerosLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 11813 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(2)->as_Register(ra_,this,idx2)/* dst */;
    Register Rsrc = opnd_array(1)->as_Register(ra_,this,idx1)/* src */;
    assert_different_registers(Rdst, Rsrc); // Rtmp == Rsrc allowed.

    // New version: shows 5%(z9), 2%(z10), 11%(z196) improvement over original.
    __ z_lcgr(Rdst, Rsrc);
    __ z_ngr(Rdst, Rsrc);
    __ add2reg(Rdst,   -1);
    __ z_flogr(Rdst, Rdst); // Kills tmp which is the oddReg for dst.
    __ add2reg(Rdst,  -64);
    __ z_lcgfr(Rdst, Rdst); // Provide 64bit result at no cost.
  
#line 23896 "ad_s390.cpp"
  }
}

void popCountI_Ext3Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 11841 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(2)->as_Register(ra_,this,idx2)/* dst */;
    Register Rsrc = opnd_array(1)->as_Register(ra_,this,idx1)/* src */;

    __ pop_count_int_with_ext3(Rdst, Rsrc);

  
#line 23915 "ad_s390.cpp"
  }
}

uint popCountI_Ext3Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void popCountL_Ext3Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 11860 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(2)->as_Register(ra_,this,idx2)/* dst */;
    Register Rsrc = opnd_array(1)->as_Register(ra_,this,idx1)/* src */;

    __ pop_count_long_with_ext3(Rdst, Rsrc);
  
#line 23938 "ad_s390.cpp"
  }
}

uint popCountL_Ext3Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void popCountINode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 11878 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(2)->as_Register(ra_,this,idx2)/* dst */;
    Register Rsrc = opnd_array(1)->as_Register(ra_,this,idx1)/* src */;
    Register Rtmp = opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */;

    __ pop_count_int_without_ext3(Rdst, Rsrc, Rtmp);

  
#line 23964 "ad_s390.cpp"
  }
}

uint popCountINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 24);
}

void popCountLNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 11898 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(2)->as_Register(ra_,this,idx2)/* dst */;
    Register Rsrc = opnd_array(1)->as_Register(ra_,this,idx1)/* src */;
    Register Rtmp = opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */;

    __ pop_count_long_without_ext3(Rdst, Rsrc, Rtmp);
  
#line 23989 "ad_s390.cpp"
  }
}

uint popCountLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 34, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 34);
}

void g1StorePNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  {

#line 83 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    __ block_comment("g1StoreP {");
    write_barrier_pre(masm, this,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* dst */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */,
                      opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */,
                      RegSet::of(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */) /* preserve */);

    __ z_stg(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Address(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */));

    write_barrier_post(masm, this,
                       opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, /* store_addr */
                       opnd_array(2)->as_Register(ra_,this,idx2)/* src */,
                       opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */,
                       opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */);
    __ block_comment("} g1StoreP");
  
#line 24025 "ad_s390.cpp"
  }
}

void g1StoreNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  {

#line 110 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    __ block_comment("g1StoreN {");
    write_barrier_pre(masm, this,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* mem */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */,
                      opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */,
                      RegSet::of(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */) /* preserve */);

    __ z_sty(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Address(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */));

    if ((barrier_data() & G1C2BarrierPost) != 0) {
      if ((barrier_data() & G1C2BarrierPostNotNull) == 0) {
        __ oop_decoder(opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, true /* maybe_null */);
      } else {
        __ oop_decoder(opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, false /* maybe_null */);
      }
    }

    write_barrier_post(masm, this,
                       opnd_array(1)->as_Register(ra_,this,idx1)/* mem */,
                       opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */,
                       opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp3 */);
    __ block_comment("} g1StoreN");
  
#line 24065 "ad_s390.cpp"
  }
}

void g1CompareAndSwapNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  {

#line 145 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    assert_different_registers(opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);
    assert_different_registers(opnd_array(3)->as_Register(ra_,this,idx3)/* newval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);
    __ block_comment("g1compareAndSwapN {");

    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);
    Register Rres  = reg_to_register_object(opnd_array(4)->reg(ra_,this,idx4)/* res */);

    write_barrier_pre(masm, this,
                      Raddr           /* obj     */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                      RegSet::of(Raddr, Rcomp, Rnew) /* preserve */,
                      RegSet::of(Rres) /* no_preserve */);

    __ z_cs(Rcomp, Rnew, 0, Raddr);

    assert_different_registers(Rres, Raddr);
    if (VM_Version::has_LoadStoreConditional()) {
      __ load_const_optimized(Z_R0_scratch, 0L); // false (failed)
      __ load_const_optimized(Rres, 1L);         // true  (succeed)
      __ z_locgr(Rres, Z_R0_scratch, Assembler::bcondNotEqual);
    } else {
      Label done;
      __ load_const_optimized(Rres, 0L); // false (failed)
      __ z_brne(done);                   // Assume true to be the common case.
      __ load_const_optimized(Rres, 1L); // true  (succeed)
      __ bind(done);
    }

    __ oop_decoder(opnd_array(7)->as_Register(ra_,this,idx7)/* tmp3 */, Rnew, true /* maybe_null */);

    write_barrier_post(masm, this,
                       Raddr            /* store_addr */,
                       opnd_array(7)->as_Register(ra_,this,idx7)/* tmp3 */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                       opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */);
    __ block_comment("} g1compareAndSwapN");
  
#line 24123 "ad_s390.cpp"
  }
}

void g1CompareAndSwapN_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  {

#line 145 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    assert_different_registers(opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);
    assert_different_registers(opnd_array(3)->as_Register(ra_,this,idx3)/* newval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);
    __ block_comment("g1compareAndSwapN {");

    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);
    Register Rres  = reg_to_register_object(opnd_array(4)->reg(ra_,this,idx4)/* res */);

    write_barrier_pre(masm, this,
                      Raddr           /* obj     */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                      RegSet::of(Raddr, Rcomp, Rnew) /* preserve */,
                      RegSet::of(Rres) /* no_preserve */);

    __ z_cs(Rcomp, Rnew, 0, Raddr);

    assert_different_registers(Rres, Raddr);
    if (VM_Version::has_LoadStoreConditional()) {
      __ load_const_optimized(Z_R0_scratch, 0L); // false (failed)
      __ load_const_optimized(Rres, 1L);         // true  (succeed)
      __ z_locgr(Rres, Z_R0_scratch, Assembler::bcondNotEqual);
    } else {
      Label done;
      __ load_const_optimized(Rres, 0L); // false (failed)
      __ z_brne(done);                   // Assume true to be the common case.
      __ load_const_optimized(Rres, 1L); // true  (succeed)
      __ bind(done);
    }

    __ oop_decoder(opnd_array(7)->as_Register(ra_,this,idx7)/* tmp3 */, Rnew, true /* maybe_null */);

    write_barrier_post(masm, this,
                       Raddr            /* store_addr */,
                       opnd_array(7)->as_Register(ra_,this,idx7)/* tmp3 */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                       opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */);
    __ block_comment("} g1compareAndSwapN");
  
#line 24181 "ad_s390.cpp"
  }
}

void g1CompareAndExchangeNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  {

#line 194 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    assert_different_registers(opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);
    assert_different_registers(opnd_array(3)->as_Register(ra_,this,idx3)/* newval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);
    __ block_comment("g1CompareAndExchangeN {");
    write_barrier_pre(masm, this,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                      RegSet::of(opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */) /* preserve */,
                      RegSet::of(opnd_array(4)->as_Register(ra_,this,idx4)/* res */) /* no_preserve */);

    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    Register Rres = reg_to_register_object(opnd_array(4)->reg(ra_,this,idx4)/* res */);
    assert_different_registers(Rres, Raddr);

    __ z_lgr(Rres, Rcomp);  // previous contents
    __ z_csy(Rres, Rnew, 0, Raddr); // Try to store new value.

    __ oop_decoder(opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, Rnew, true /* maybe_null */);

    write_barrier_post(masm, this,
                       Raddr           /* store_addr */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                       opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                       opnd_array(7)->as_Register(ra_,this,idx7)/* tmp3 */);
    __ block_comment("} g1CompareAndExchangeN");
  
#line 24228 "ad_s390.cpp"
  }
}

void g1LoadNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  {

#line 234 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    __ block_comment("g1LoadN {");
    __ z_llgf(opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, Address(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */));
    if ((barrier_data() & G1C2BarrierPre) != 0) {
      __ oop_decoder(opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, true);
      write_barrier_pre(masm, this,
                        noreg           /* obj     */,
                        opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */,
                        opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */);
    }
    __ block_comment("} g1LoadN");
  
#line 24254 "ad_s390.cpp"
  }
}

void g1GetAndSetNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp3
  {

#line 254 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    __ block_comment("g1GetAndSetN {");
    assert_different_registers(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */);
    write_barrier_pre(masm, this,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* mem */,
                      opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */,
                      RegSet::of(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */) /* preserve */);

    Register Rdst = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* dst */);
    Register Rtmp = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* tmp */);
    guarantee(Rdst != Rtmp, "Fix match rule to use TEMP_DEF");
    Label    retry;

    // Iterate until swap succeeds.
    __ z_llgf(Rtmp, Address(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */)); // current contents
    __ bind(retry);
    // Calculate incremented value.
    __ z_csy(Rtmp, Rdst, Address(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */)); // Try to store new value.
    __ z_brne(retry); // Yikes, concurrent update, need to retry.

    __ oop_decoder(opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, true /* maybe_null */);

    __ z_lgr(Rdst, Rtmp);  // Exchanged value from memory is return value.

    write_barrier_post(masm, this,
                       opnd_array(1)->as_Register(ra_,this,idx1)/* mem */,
                       opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */,
                       opnd_array(6)->as_Register(ra_,this,idx6)/* tmp3 */);

    __ block_comment("} g1GetAndSetN");
  
#line 24303 "ad_s390.cpp"
  }
}

void g1CompareAndSwapPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {

#line 296 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    __ block_comment("g1CompareAndSwapP {");
    assert_different_registers(opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);
    assert_different_registers(opnd_array(3)->as_Register(ra_,this,idx3)/* newval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);

    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);
    Register Rres  = reg_to_register_object(opnd_array(4)->reg(ra_,this,idx4)/* res */);

    write_barrier_pre(masm, this,
                      noreg           /* obj     */,
                      Rcomp           /* pre_val */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                      RegSet::of(Raddr, Rcomp, Rnew) /* preserve */,
                      RegSet::of(Rres) /* no_preserve */);

    __ z_csg(Rcomp, Rnew, 0, Raddr);

    if (VM_Version::has_LoadStoreConditional()) {
      __ load_const_optimized(Z_R0_scratch, 0L); // false (failed)
      __ load_const_optimized(Rres, 1L);         // true  (succeed)
      __ z_locgr(Rres, Z_R0_scratch, Assembler::bcondNotEqual);
    } else {
      Label done;
      __ load_const_optimized(Rres, 0L); // false (failed)
      __ z_brne(done);                   // Assume true to be the common case.
      __ load_const_optimized(Rres, 1L); // true  (succeed)
      __ bind(done);
    }

    write_barrier_post(masm, this,
                       Raddr           /* store_addr */,
                       Rnew            /* new_val    */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                       opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */);
    __ block_comment("} g1CompareAndSwapP");
  
#line 24357 "ad_s390.cpp"
  }
}

void g1CompareAndSwapP_0Node::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {

#line 296 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    __ block_comment("g1CompareAndSwapP {");
    assert_different_registers(opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);
    assert_different_registers(opnd_array(3)->as_Register(ra_,this,idx3)/* newval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);

    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);
    Register Rres  = reg_to_register_object(opnd_array(4)->reg(ra_,this,idx4)/* res */);

    write_barrier_pre(masm, this,
                      noreg           /* obj     */,
                      Rcomp           /* pre_val */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                      RegSet::of(Raddr, Rcomp, Rnew) /* preserve */,
                      RegSet::of(Rres) /* no_preserve */);

    __ z_csg(Rcomp, Rnew, 0, Raddr);

    if (VM_Version::has_LoadStoreConditional()) {
      __ load_const_optimized(Z_R0_scratch, 0L); // false (failed)
      __ load_const_optimized(Rres, 1L);         // true  (succeed)
      __ z_locgr(Rres, Z_R0_scratch, Assembler::bcondNotEqual);
    } else {
      Label done;
      __ load_const_optimized(Rres, 0L); // false (failed)
      __ z_brne(done);                   // Assume true to be the common case.
      __ load_const_optimized(Rres, 1L); // true  (succeed)
      __ bind(done);
    }

    write_barrier_post(masm, this,
                       Raddr           /* store_addr */,
                       Rnew            /* new_val    */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                       opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */);
    __ block_comment("} g1CompareAndSwapP");
  
#line 24411 "ad_s390.cpp"
  }
}

void g1CompareAndExchangePNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {

#line 342 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    __ block_comment("g1CompareAndExchangeP {");
    assert_different_registers(opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);
    assert_different_registers(opnd_array(3)->as_Register(ra_,this,idx3)/* newval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);

    // Pass $oldval to the pre-barrier (instead of loading from $mem), because
    // $oldval is the only value that can be overwritten.
    // The same holds for g1CompareAndSwapP.
    write_barrier_pre(masm, this,
                      noreg             /* obj     */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                      RegSet::of(opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */) /* preserve */,
                      RegSet::of(opnd_array(4)->as_Register(ra_,this,idx4)/* res */) /* no_preserve */);

    __ z_lgr(opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */); // previous content

    __ z_csg(opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */, 0, opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    write_barrier_post(masm, this,
                       opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                       opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                       opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */);
    __ block_comment("} g1CompareAndExchangeP");
  
#line 24453 "ad_s390.cpp"
  }
}

void g1LoadPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  {

#line 378 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    __ block_comment("g1LoadP {");
    __ z_lg(opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));
    write_barrier_pre(masm, this,
                      noreg /* obj */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* dst */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */);
    __ block_comment("} g1LoadP");
  
#line 24475 "ad_s390.cpp"
  }
}

void g1GetAndSetPNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  {

#line 395 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    __ block_comment("g1GetAndSetP {");

    write_barrier_pre(masm, this,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* mem */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */,
                      opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */,
                      RegSet::of(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */) /* preserve */);

    __ z_lgr(opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */);
    Register Rdst = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* dst */);
    Register Rtmp = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* tmp */);
    guarantee(Rdst != Rtmp, "Fix match rule to use TEMP_DEF");
    Label    retry;

    // Iterate until swap succeeds.
    __ z_lg(Rtmp, Address(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */));  // current contents
    __ bind(retry);
    // Calculate incremented value.
    __ z_csg(Rtmp, Rdst, Address(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */)); // Try to store new value.
    __ z_brne(retry);                              // Yikes, concurrent update, need to retry.
    __ z_lgr(Rdst, Rtmp);                          // Exchanged value from memory is return value.

    write_barrier_post(masm, this,
                       opnd_array(1)->as_Register(ra_,this,idx1)/* mem */,
                       opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */,
                       opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */);
    __ block_comment("} g1GetAndSetP");
  
#line 24520 "ad_s390.cpp"
  }
}

void g1EncodePAndStoreNNode::emit(C2_MacroAssembler* masm, PhaseRegAlloc* ra_) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  {

#line 436 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"

    __ block_comment("g1EncodePAndStoreN {");
    write_barrier_pre(masm, this,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* mem */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */,
                      opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */,
                      RegSet::of(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */) /* preserve */);
    if ((barrier_data() & G1C2BarrierPostNotNull) == 0) {
      __ oop_encoder(opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, true /* maybe_null */);
    } else {
      __ oop_encoder(opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, false /* maybe_null */);
    }
    __ z_st(opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, Address(opnd_array(1)->as_Register(ra_,this,idx1)/* mem */));
    write_barrier_post(masm, this,
                       opnd_array(1)->as_Register(ra_,this,idx1)/* mem */,
                       opnd_array(2)->as_Register(ra_,this,idx2)/* src */,
                       opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */,
                       opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */);
    __ block_comment("} g1EncodePAndStoreN");
  
#line 24554 "ad_s390.cpp"
  }
}

const MachOper* loadBNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadB2LNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUBNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUB2LNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadSNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadS2LNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUSNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUS2LNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadINode::memory_operand() const { return _opnds[1]; }
const MachOper* loadI2LNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUI2LNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadRangeNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadLNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadL_unalignedNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadPNode::memory_operand() const { return _opnds[1]; }
const MachOper* castP2X_loadPNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadKlassNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadFNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadDNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadD_unalignedNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeBNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeCNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeINode::memory_operand() const { return _opnds[1]; }
const MachOper* storeLNode::memory_operand() const { return _opnds[1]; }
const MachOper* storePNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeFNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeDNode::memory_operand() const { return _opnds[1]; }
const MachOper* prefetchAllocNode::memory_operand() const { return _opnds[1]; }
const MachOper* memInitBNode::memory_operand() const { return _opnds[1]; }
const MachOper* memInitCNode::memory_operand() const { return _opnds[1]; }
const MachOper* memInitINode::memory_operand() const { return _opnds[1]; }
const MachOper* memInitLNode::memory_operand() const { return _opnds[1]; }
const MachOper* memInitPNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadNNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadNKlassNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadNKlassCompactHeadersNode::memory_operand() const { return _opnds[1]; }
const MachOper* decodeLoadNNode::memory_operand() const { return _opnds[1]; }
const MachOper* decodeLoadNKlassNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeNNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeNKlassNode::memory_operand() const { return _opnds[1]; }
const MachOper* addI_mem_imm8_atomic_no_resNode::memory_operand() const { return _opnds[1]; }
const MachOper* addI_mem_imm16_atomicNode::memory_operand() const { return _opnds[1]; }
const MachOper* addI_mem_imm32_atomicNode::memory_operand() const { return _opnds[1]; }
const MachOper* addI_mem_reg_atomicNode::memory_operand() const { return _opnds[1]; }
const MachOper* addL_mem_imm8_atomic_no_resNode::memory_operand() const { return _opnds[1]; }
const MachOper* addL_mem_imm16_atomicNode::memory_operand() const { return _opnds[1]; }
const MachOper* addL_mem_imm32_atomicNode::memory_operand() const { return _opnds[1]; }
const MachOper* addL_mem_reg_atomicNode::memory_operand() const { return _opnds[1]; }
const MachOper* addI_mem_reg_atomic_z196Node::memory_operand() const { return _opnds[1]; }
const MachOper* addL_mem_reg_atomic_z196Node::memory_operand() const { return _opnds[1]; }
const MachOper* xchgI_reg_memNode::memory_operand() const { return _opnds[1]; }
const MachOper* xchgL_reg_memNode::memory_operand() const { return _opnds[1]; }
const MachOper* xchgN_reg_memNode::memory_operand() const { return _opnds[1]; }
const MachOper* xchgP_reg_memNode::memory_operand() const { return _opnds[1]; }
const MachOper* addI_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* addI_Reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* addI_mem_immNode::memory_operand() const { return _opnds[1]; }
const MachOper* addL_Reg_memINode::memory_operand() const { return _opnds[2]; }
const MachOper* addL_Reg_memI_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* addL_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* addL_Reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* addL_mem_immNode::memory_operand() const { return _opnds[1]; }
const MachOper* addP_mem_immNode::memory_operand() const { return _opnds[1]; }
const MachOper* subI_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* subL_Reg_memINode::memory_operand() const { return _opnds[2]; }
const MachOper* subL_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* mulI_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* mulI_Reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* mulL_Reg_memINode::memory_operand() const { return _opnds[2]; }
const MachOper* mulL_Reg_memI_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* mulL_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* mulL_Reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* addF_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* addF_reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* addD_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* addD_reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* subF_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* subD_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* mulF_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* mulF_reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* mulD_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* mulD_reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* maddF_reg_memNode::memory_operand() const { return _opnds[3]; }
const MachOper* maddD_reg_memNode::memory_operand() const { return _opnds[3]; }
const MachOper* msubF_reg_memNode::memory_operand() const { return _opnds[3]; }
const MachOper* msubD_reg_memNode::memory_operand() const { return _opnds[3]; }
const MachOper* maddF_mem_regNode::memory_operand() const { return _opnds[2]; }
const MachOper* maddD_mem_regNode::memory_operand() const { return _opnds[2]; }
const MachOper* msubF_mem_regNode::memory_operand() const { return _opnds[2]; }
const MachOper* msubD_mem_regNode::memory_operand() const { return _opnds[2]; }
const MachOper* divF_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* divD_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* sqrtF_memNode::memory_operand() const { return _opnds[1]; }
const MachOper* sqrtD_memNode::memory_operand() const { return _opnds[1]; }
const MachOper* andI_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* andI_Reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* andL_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* andL_Reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* orI_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* orI_Reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* orL_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* orL_Reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* xorI_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* xorI_Reg_mem_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* xorL_Reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* convF2D_memNode::memory_operand() const { return _opnds[1]; }
const MachOper* convI2L_mem_zexNode::memory_operand() const { return _opnds[1]; }
const MachOper* compI_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* compU_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* compL_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* compL_reg_memINode::memory_operand() const { return _opnds[2]; }
const MachOper* compP_reg_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* cmpF_cc_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* cmpD_cc_memNode::memory_operand() const { return _opnds[2]; }
const MachOper* storeA8BNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeV16Node::memory_operand() const { return _opnds[1]; }
const MachOper* loadV8Node::memory_operand() const { return _opnds[1]; }
const MachOper* loadV16Node::memory_operand() const { return _opnds[1]; }
const MachOper* g1StorePNode::memory_operand() const { return _opnds[1]; }
const MachOper* g1StoreNNode::memory_operand() const { return _opnds[1]; }
const MachOper* g1CompareAndSwapNNode::memory_operand() const { return _opnds[1]; }
const MachOper* g1CompareAndSwapN_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* g1LoadNNode::memory_operand() const { return _opnds[1]; }
const MachOper* g1GetAndSetNNode::memory_operand() const { return _opnds[1]; }
const MachOper* g1LoadPNode::memory_operand() const { return _opnds[1]; }
const MachOper* g1GetAndSetPNode::memory_operand() const { return _opnds[1]; }
const MachOper* g1EncodePAndStoreNNode::memory_operand() const { return _opnds[1]; }


bool Matcher::has_match_rule(int opcode) {
  assert(_last_machine_leaf < opcode && opcode < _last_opcode, "opcode in range");
  return _hasMatchRule[opcode];
}

const bool Matcher::_hasMatchRule[_last_opcode] = {
    false,  // Node
    false,  // Set
    false,  // RegN
    false,  // RegI
    false,  // RegP
    false,  // RegF
    false,  // RegD
    false,  // RegL
    false,  // VecA
    false,  // VecS
    false,  // VecD
    false,  // VecX
    false,  // VecY
    false,  // VecZ
    false,  // RegVectMask
    false,  // RegFlags
    false,  // _last_machine_leaf
    true ,  // AbsD
    true ,  // AbsF
    true ,  // AbsI
    true ,  // AbsL
    true ,  // AddD
    true ,  // AddF
    true ,  // AddI
    true ,  // AddL
    true ,  // AddP
    false,  // AddHF
    false,  // Allocate
    false,  // AllocateArray
    true ,  // AndI
    true ,  // AndL
    false,  // ArrayCopy
    true ,  // AryEq
    false,  // AtanD
    true ,  // Binary
    false,  // Blackhole
    true ,  // Bool
    false,  // BoxLock
    true ,  // ReverseBytesI
    true ,  // ReverseBytesL
    true ,  // ReverseBytesUS
    true ,  // ReverseBytesS
    false,  // ReverseBytesV
    false,  // CProj
    false,  // CacheWB
    false,  // CacheWBPreSync
    false,  // CacheWBPostSync
    true ,  // CallDynamicJava
    false,  // CallJava
    true ,  // CallLeaf
    true ,  // CallLeafNoFP
    false,  // CallLeafPure
    false,  // CallLeafVector
    true ,  // CallRuntime
    true ,  // CallStaticJava
    true ,  // CastDD
    false,  // CastHH
    true ,  // CastFF
    true ,  // CastII
    true ,  // CastLL
    true ,  // CastVV
    true ,  // CastX2P
    true ,  // CastP2X
    true ,  // CastPP
    false,  // Catch
    false,  // CatchProj
    true ,  // CheckCastPP
    true ,  // ClearArray
    false,  // CompressBits
    false,  // ExpandBits
    false,  // CompressBitsV
    false,  // ExpandBitsV
    false,  // ConstraintCast
    true ,  // CMoveD
    true ,  // CMoveF
    true ,  // CMoveI
    true ,  // CMoveL
    true ,  // CMoveP
    true ,  // CMoveN
    true ,  // CmpN
    true ,  // CmpD
    true ,  // CmpD3
    true ,  // CmpF
    true ,  // CmpF3
    true ,  // CmpI
    true ,  // CmpL
    true ,  // CmpL3
    true ,  // CmpLTMask
    true ,  // CmpP
    true ,  // CmpU
    false,  // CmpU3
    true ,  // CmpUL
    false,  // CmpUL3
    false,  // CompareAndSwapB
    false,  // CompareAndSwapS
    true ,  // CompareAndSwapI
    true ,  // CompareAndSwapL
    true ,  // CompareAndSwapP
    true ,  // CompareAndSwapN
    false,  // WeakCompareAndSwapB
    false,  // WeakCompareAndSwapS
    false,  // WeakCompareAndSwapI
    false,  // WeakCompareAndSwapL
    true ,  // WeakCompareAndSwapP
    true ,  // WeakCompareAndSwapN
    false,  // CompareAndExchangeB
    false,  // CompareAndExchangeS
    false,  // CompareAndExchangeI
    false,  // CompareAndExchangeL
    true ,  // CompareAndExchangeP
    true ,  // CompareAndExchangeN
    false,  // GetAndAddB
    false,  // GetAndAddS
    true ,  // GetAndAddI
    true ,  // GetAndAddL
    false,  // GetAndSetB
    false,  // GetAndSetS
    true ,  // GetAndSetI
    true ,  // GetAndSetL
    true ,  // GetAndSetP
    true ,  // GetAndSetN
    false,  // Con
    true ,  // ConN
    true ,  // ConNKlass
    true ,  // ConD
    false,  // ConH
    true ,  // ConF
    true ,  // ConI
    true ,  // ConL
    true ,  // ConP
    true ,  // Conv2B
    true ,  // ConvD2F
    true ,  // ConvD2I
    true ,  // ConvD2L
    true ,  // ConvF2D
    true ,  // ConvF2I
    true ,  // ConvF2L
    true ,  // ConvI2D
    true ,  // ConvI2F
    true ,  // ConvI2L
    true ,  // ConvL2D
    true ,  // ConvL2F
    true ,  // ConvL2I
    false,  // ConvF2HF
    false,  // ConvHF2F
    false,  // CountedLoop
    true ,  // CountedLoopEnd
    false,  // OuterStripMinedLoop
    false,  // OuterStripMinedLoopEnd
    false,  // LongCountedLoop
    false,  // LongCountedLoopEnd
    true ,  // CountLeadingZerosI
    true ,  // CountLeadingZerosL
    false,  // CountLeadingZerosV
    true ,  // CountTrailingZerosI
    true ,  // CountTrailingZerosL
    false,  // CountTrailingZerosV
    true ,  // CreateEx
    true ,  // DecodeN
    true ,  // DecodeNKlass
    false,  // DivHF
    true ,  // DivD
    true ,  // DivF
    true ,  // DivI
    true ,  // DivL
    true ,  // UDivI
    true ,  // UDivL
    false,  // DivMod
    true ,  // DivModI
    true ,  // DivModL
    false,  // UDivModI
    false,  // UDivModL
    true ,  // EncodeISOArray
    true ,  // EncodeP
    true ,  // EncodePKlass
    true ,  // FastLock
    true ,  // FastUnlock
    true ,  // FmaD
    true ,  // FmaF
    false,  // FmaHF
    true ,  // ForwardException
    true ,  // Goto
    true ,  // Halt
    true ,  // CountPositives
    true ,  // If
    false,  // RangeCheck
    false,  // IfFalse
    false,  // IfTrue
    false,  // Initialize
    false,  // JProj
    false,  // Jump
    false,  // JumpProj
    true ,  // LShiftI
    true ,  // LShiftL
    true ,  // LoadB
    true ,  // LoadUB
    true ,  // LoadUS
    true ,  // LoadD
    true ,  // LoadD_unaligned
    true ,  // LoadF
    true ,  // LoadI
    true ,  // LoadKlass
    true ,  // LoadNKlass
    true ,  // LoadL
    true ,  // LoadL_unaligned
    true ,  // LoadP
    true ,  // LoadN
    true ,  // LoadRange
    true ,  // LoadS
    false,  // Lock
    false,  // Loop
    false,  // LoopLimit
    false,  // Mach
    false,  // MachNullCheck
    false,  // MachProj
    false,  // MulAddS2I
    true ,  // MaxI
    false,  // MaxL
    false,  // MaxHF
    false,  // MaxD
    false,  // MaxF
    true ,  // MemBarAcquire
    true ,  // LoadFence
    true ,  // MemBarAcquireLock
    true ,  // MemBarCPUOrder
    true ,  // MemBarRelease
    true ,  // StoreFence
    true ,  // StoreStoreFence
    true ,  // MemBarReleaseLock
    true ,  // MemBarStoreLoad
    true ,  // MemBarVolatile
    true ,  // MemBarStoreStore
    true ,  // MemBarFull
    false,  // MergeMem
    true ,  // MinI
    false,  // MinL
    false,  // MinHF
    false,  // MinF
    false,  // MinD
    false,  // ModD
    false,  // ModF
    true ,  // ModI
    true ,  // ModL
    true ,  // UModI
    true ,  // UModL
    true ,  // MoveI2F
    true ,  // MoveF2I
    true ,  // MoveL2D
    true ,  // MoveD2L
    false,  // IsInfiniteF
    false,  // IsFiniteF
    false,  // IsInfiniteD
    false,  // IsFiniteD
    false,  // MulHF
    true ,  // MulD
    true ,  // MulF
    true ,  // MulHiL
    false,  // UMulHiL
    true ,  // MulI
    true ,  // MulL
    false,  // Multi
    false,  // NegI
    false,  // NegL
    true ,  // NegD
    true ,  // NegF
    false,  // NeverBranch
    false,  // NarrowMemProj
    false,  // OnSpinWait
    false,  // Opaque1
    false,  // OpaqueLoopInit
    false,  // OpaqueLoopStride
    false,  // OpaqueMultiversioning
    false,  // OpaqueZeroTripGuard
    false,  // OpaqueConstantBool
    false,  // OpaqueInitializedAssertionPredicate
    false,  // OpaqueTemplateAssertionPredicate
    false,  // PowD
    false,  // ProfileBoolean
    true ,  // OrI
    true ,  // OrL
    true ,  // OverflowAddI
    true ,  // OverflowSubI
    false,  // OverflowMulI
    true ,  // OverflowAddL
    true ,  // OverflowSubL
    false,  // OverflowMulL
    false,  // PCTable
    false,  // Parm
    false,  // ParsePredicate
    true ,  // PartialSubtypeCheck
    false,  // SubTypeCheck
    false,  // Phi
    true ,  // PopCountI
    true ,  // PopCountL
    true ,  // PopCountVI
    false,  // PopCountVL
    false,  // PopulateIndex
    true ,  // PrefetchAllocation
    false,  // Proj
    true ,  // RShiftI
    true ,  // RShiftL
    false,  // Region
    true ,  // Rethrow
    true ,  // Return
    false,  // ReverseI
    false,  // ReverseL
    false,  // ReverseV
    false,  // Root
    false,  // RoundDoubleMode
    true ,  // RoundDoubleModeV
    false,  // RotateLeft
    false,  // RotateLeftV
    false,  // RotateRight
    false,  // RotateRightV
    true ,  // SafePoint
    false,  // SafePointScalarObject
    false,  // SafePointScalarMerge
    false,  // ShenandoahCompareAndExchangeP
    false,  // ShenandoahCompareAndExchangeN
    false,  // ShenandoahCompareAndSwapN
    false,  // ShenandoahCompareAndSwapP
    false,  // ShenandoahWeakCompareAndSwapN
    false,  // ShenandoahWeakCompareAndSwapP
    false,  // ShenandoahLoadReferenceBarrier
    false,  // SCMemProj
    false,  // CopySignD
    false,  // CopySignF
    false,  // SaturatingAddV
    false,  // SaturatingSubV
    false,  // SignumD
    false,  // SignumF
    false,  // SignumVF
    false,  // SignumVD
    true ,  // SqrtD
    true ,  // SqrtF
    false,  // SqrtHF
    false,  // RoundF
    false,  // RoundD
    false,  // Start
    false,  // StartOSR
    true ,  // StoreB
    true ,  // StoreC
    true ,  // StoreD
    true ,  // StoreF
    true ,  // StoreI
    true ,  // StoreL
    true ,  // StoreP
    true ,  // StoreN
    true ,  // StoreNKlass
    true ,  // StrComp
    true ,  // StrCompressedCopy
    true ,  // StrEquals
    true ,  // StrIndexOf
    true ,  // StrIndexOfChar
    true ,  // StrInflatedCopy
    false,  // SubHF
    true ,  // SubD
    true ,  // SubF
    true ,  // SubI
    true ,  // SubL
    true ,  // TailCall
    true ,  // TailJump
    false,  // Tuple
    false,  // MacroLogicV
    true ,  // ThreadLocal
    false,  // Unlock
    false,  // URShiftB
    false,  // URShiftS
    true ,  // URShiftI
    true ,  // URShiftL
    true ,  // XorI
    true ,  // XorL
    false,  // Vector
    true ,  // AddVB
    true ,  // AddVS
    true ,  // AddVI
    false,  // AddReductionVI
    true ,  // AddVL
    false,  // AddReductionVL
    true ,  // AddVF
    false,  // AddVHF
    false,  // AddReductionVF
    true ,  // AddVD
    false,  // AddReductionVD
    true ,  // SubVB
    true ,  // SubVS
    true ,  // SubVI
    true ,  // SubVL
    true ,  // SubVF
    false,  // SubVHF
    true ,  // SubVD
    true ,  // MulVB
    true ,  // MulVS
    true ,  // MulVI
    false,  // MulReductionVI
    false,  // MulVL
    false,  // MulReductionVL
    true ,  // MulVF
    false,  // MulReductionVF
    true ,  // MulVD
    false,  // MulReductionVD
    false,  // MulVHF
    false,  // MulAddVS2VI
    false,  // FmaVD
    false,  // FmaVF
    false,  // FmaVHF
    false,  // DivVHF
    true ,  // DivVF
    true ,  // DivVD
    false,  // AbsVB
    false,  // AbsVS
    false,  // AbsVI
    false,  // AbsVL
    false,  // AbsVF
    false,  // AbsVD
    false,  // NegVI
    false,  // NegVL
    false,  // NegVF
    false,  // NegVD
    true ,  // SqrtVD
    true ,  // SqrtVF
    false,  // SqrtVHF
    false,  // LShiftCntV
    false,  // RShiftCntV
    false,  // LShiftVB
    false,  // LShiftVS
    false,  // LShiftVI
    false,  // LShiftVL
    false,  // RShiftVB
    false,  // RShiftVS
    false,  // RShiftVI
    false,  // RShiftVL
    false,  // URShiftVB
    false,  // URShiftVS
    false,  // URShiftVI
    false,  // URShiftVL
    false,  // AndV
    false,  // AndReductionV
    false,  // OrV
    false,  // OrReductionV
    false,  // XorV
    false,  // XorReductionV
    false,  // MinV
    false,  // MaxV
    false,  // MinVHF
    false,  // MaxVHF
    false,  // UMinV
    false,  // UMaxV
    false,  // MinReductionV
    false,  // MaxReductionV
    false,  // UMinReductionV
    false,  // UMaxReductionV
    false,  // CompressV
    false,  // CompressM
    false,  // ExpandV
    true ,  // LoadVector
    false,  // LoadVectorGather
    false,  // LoadVectorGatherMasked
    true ,  // StoreVector
    false,  // StoreVectorScatter
    false,  // StoreVectorScatterMasked
    false,  // LoadVectorMasked
    false,  // StoreVectorMasked
    false,  // VerifyVectorAlignment
    false,  // VectorCmpMasked
    false,  // VectorMaskGen
    false,  // VectorMaskOp
    false,  // VectorMaskTrueCount
    false,  // VectorMaskFirstTrue
    false,  // VectorMaskLastTrue
    false,  // VectorMaskToLong
    false,  // VectorLongToMask
    false,  // Pack
    false,  // PackB
    false,  // PackS
    false,  // PackI
    false,  // PackL
    false,  // PackF
    false,  // PackD
    false,  // Pack2L
    false,  // Pack2D
    true ,  // Replicate
    false,  // RoundVF
    false,  // RoundVD
    false,  // Extract
    false,  // ExtractB
    false,  // ExtractUB
    false,  // ExtractC
    false,  // ExtractS
    false,  // ExtractI
    false,  // ExtractL
    false,  // ExtractF
    false,  // ExtractD
    false,  // Digit
    false,  // LowerCase
    false,  // ReinterpretS2HF
    false,  // ReinterpretHF2S
    false,  // UpperCase
    false,  // Whitespace
    false,  // SelectFromTwoVector
    false,  // VectorBox
    false,  // VectorBoxAllocate
    false,  // VectorUnbox
    false,  // VectorMaskWrapper
    false,  // VectorMaskCmp
    false,  // VectorMaskCast
    false,  // VectorTest
    false,  // VectorBlend
    false,  // VectorRearrange
    false,  // VectorLoadMask
    false,  // VectorLoadShuffle
    false,  // VectorLoadConst
    false,  // VectorStoreMask
    true ,  // VectorReinterpret
    false,  // VectorCast
    false,  // VectorCastB2X
    false,  // VectorCastS2X
    false,  // VectorCastI2X
    false,  // VectorCastL2X
    false,  // VectorCastF2X
    false,  // VectorCastD2X
    false,  // VectorCastF2HF
    false,  // VectorCastHF2F
    false,  // VectorUCastB2X
    false,  // VectorUCastS2X
    false,  // VectorUCastI2X
    false,  // VectorizedHashCode
    false,  // VectorInsert
    false,  // MaskAll
    false,  // AndVMask
    false,  // OrVMask
    false   // XorVMask
};


int Compile::sync_stack_slots() const { return frame::jit_monitor_size_in_4_byte_units; }

uint Matcher::stack_alignment_in_bytes() { return frame::alignment_in_bytes; }

OptoReg::Name Matcher::return_addr() const { return OptoReg::Name(Z_R14_num); }

uint Compile::varargs_C_out_slots_killed() const { return ((frame::z_abi_160_size - frame::z_jit_out_preserve_size) / VMRegImpl::stack_slot_size); }

OptoRegPair Matcher::return_value(uint ideal_reg) {

#line 2634 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(ideal_reg >= Op_RegI && ideal_reg <= Op_RegL, "only return normal values");
    static int typeToRegLo[Op_RegL+1] = { 0, 0, Z_R2_num, Z_R2_num, Z_R2_num, Z_F0_num, Z_F0_num, Z_R2_num };
    static int typeToRegHi[Op_RegL+1] = { 0, 0, OptoReg::Bad, OptoReg::Bad, Z_R2_H_num, OptoReg::Bad, Z_F0_H_num, Z_R2_H_num };
    return OptoRegPair(typeToRegHi[ideal_reg], typeToRegLo[ideal_reg]);
  
#line 25245 "ad_s390.cpp"

}

OptoRegPair Matcher::c_return_value(uint ideal_reg) {

#line 2625 "/work/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(ideal_reg >= Op_RegI && ideal_reg <= Op_RegL, "only return normal values");
    static int typeToRegLo[Op_RegL+1] = { 0, 0, Z_R2_num, Z_R2_num, Z_R2_num, Z_F0_num, Z_F0_num, Z_R2_num };
    static int typeToRegHi[Op_RegL+1] = { 0, 0, OptoReg::Bad, OptoReg::Bad, Z_R2_H_num, OptoReg::Bad, Z_F0_H_num, Z_R2_H_num };
    return OptoRegPair(typeToRegHi[ideal_reg], typeToRegLo[ideal_reg]);
  
#line 25258 "ad_s390.cpp"

}

OptoReg::Name Matcher::inline_cache_reg() { return OptoReg::Name(Z_R9_num); }

int Matcher::inline_cache_reg_encode() { return _regEncode[inline_cache_reg()]; }

OptoReg::Name Matcher::c_frame_pointer() const { return OptoReg::Name(Z_R15_num); }

// Number of callee-save + always-save registers
int  Matcher::number_of_saved_registers() {
  return 0;
};

bool Compile::needs_deep_clone_jvms() { return false; }

// Check consistency of C++ compilation with ADLC options:
// Check adlc -DLINUX=1
#ifndef LINUX
#  error "LINUX must be defined"
#endif // LINUX
// Check adlc -D_GNU_SOURCE=1
#ifndef _GNU_SOURCE
#  error "_GNU_SOURCE must be defined"
#endif // _GNU_SOURCE
// Check adlc -DS390=1
#ifndef S390
#  error "S390 must be defined"
#endif // S390
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
// Check adlc -DASSERT=1
#ifndef ASSERT
#  error "ASSERT must be defined"
#endif // ASSERT
