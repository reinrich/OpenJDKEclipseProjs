#line 1 "ad_s390.cpp"
//
// Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
// Copyright (c) 2017, SAP SE. All rights reserved.
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

#include "precompiled.hpp"
#include "adfiles/adGlobals_s390.hpp"
#include "adfiles/ad_s390.hpp"
#include "memory/allocation.inline.hpp"
#include "asm/macroAssembler.inline.hpp"
#include "code/compiledIC.hpp"
#include "code/nativeInst.hpp"
#include "code/vmreg.inline.hpp"
#include "gc/shared/collectedHeap.inline.hpp"
#include "oops/compiledICHolder.hpp"
#include "oops/markOop.hpp"
#include "oops/method.hpp"
#include "oops/oop.inline.hpp"
#include "opto/cfgnode.hpp"
#include "opto/intrinsicnode.hpp"
#include "opto/locknode.hpp"
#include "opto/opcodes.hpp"
#include "opto/regalloc.hpp"
#include "opto/regmask.hpp"
#include "opto/runtime.hpp"
#include "runtime/biasedLocking.hpp"
#include "runtime/safepointMechanism.hpp"
#include "runtime/sharedRuntime.hpp"
#include "runtime/stubRoutines.hpp"
#include "utilities/growableArray.hpp"

//SourceForm

#line 566 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"


#ifdef PRODUCT
#define BLOCK_COMMENT(str)
#define BIND(label)        __ bind(label)
#else
#define BLOCK_COMMENT(str) __ block_comment(str)
#define BIND(label)        __ bind(label); BLOCK_COMMENT(#label ":")
#endif

#define __ _masm.

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

// Indicate if the safepoint node needs the polling page as an input.
// Since z/Architecture does not have absolute addressing, it does.
bool SafePointNode::needs_polling_address_input() {
  return true;
}

void emit_nop(CodeBuffer &cbuf) {
  MacroAssembler _masm(&cbuf);
  __ z_nop();
}

// Emit an interrupt that is caught by the debugger (for debugging compiler).
void emit_break(CodeBuffer &cbuf) {
  MacroAssembler _masm(&cbuf);
  __ z_illtrap();
}

#if !defined(PRODUCT)
void MachBreakpointNode::format(PhaseRegAlloc *, outputStream *os) const {
  os->print("TA");
}
#endif

void MachBreakpointNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  emit_break(cbuf);
}

uint MachBreakpointNode::size(PhaseRegAlloc *ra_) const {
  return MachNode::size(ra_);
}

static inline void z_emit16(CodeBuffer &cbuf, long value) {
  // 32bit instructions may become sign extended.
  assert(value >= 0, "unintended sign extension (int->long)");
  assert(value < (1L << 16), "instruction too large");
  *((unsigned short*)(cbuf.insts_end())) = (unsigned short)value;
  cbuf.set_insts_end(cbuf.insts_end() + sizeof(unsigned short));
}

static inline void z_emit32(CodeBuffer &cbuf, long value) {
  // 32bit instructions may become sign extended.
  assert(value < (1L << 32), "instruction too large");
  *((unsigned int*)(cbuf.insts_end())) = (unsigned int)value;
  cbuf.set_insts_end(cbuf.insts_end() + sizeof(unsigned int));
}

static inline void z_emit48(CodeBuffer &cbuf, long value) {
  // 32bit instructions may become sign extended.
  assert(value >= 0, "unintended sign extension (int->long)");
  assert(value < (1L << 48), "instruction too large");
  value = value<<16;
  memcpy(cbuf.insts_end(), (unsigned char*)&value, 6);
  cbuf.set_insts_end(cbuf.insts_end() + 6);
}

static inline unsigned int z_emit_inst(CodeBuffer &cbuf, long value) {
  if (value < 0) {
    // There obviously has been an unintended sign extension (int->long). Revert it.
    value = (long)((unsigned long)((unsigned int)value));
  }

  if (value < (1L << 16)) { // 2-byte instruction
    z_emit16(cbuf, value);
    return 2;
  }

  if (value < (1L << 32)) { // 4-byte instruction, might be unaligned store
    z_emit32(cbuf, value);
    return 4;
  }

  // 6-byte instruction, probably unaligned store.
  z_emit48(cbuf, value);
  return 6;
}

// Check effective address (at runtime) for required alignment.
static inline void z_assert_aligned(CodeBuffer &cbuf, int disp, Register index, Register base, int alignment) {
  MacroAssembler _masm(&cbuf);

  __ z_lay(Z_R0, disp, index, base);
  __ z_nill(Z_R0, alignment-1);
  __ z_brc(Assembler::bcondEqual, +3);
  __ z_illtrap();
}

int emit_call_reloc(MacroAssembler &_masm, intptr_t entry_point, relocInfo::relocType rtype,
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
    if (call_addr == NULL) {
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

static int emit_call_reloc(MacroAssembler &_masm, intptr_t entry_point, RelocationHolder const& rspec) {
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
int Compile::ConstantTable::calculate_table_base_offset() const {
  return 0;  // absolute addressing, no offset
}

bool MachConstantBaseNode::requires_postalloc_expand() const { return false; }
void MachConstantBaseNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  ShouldNotReachHere();
}

// Even with PC-relative TOC addressing, we still need this node.
// Float loads/stores do not support PC-relative addresses.
void MachConstantBaseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  MacroAssembler _masm(&cbuf);
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

#if !defined(PRODUCT)
void MachPrologNode::format(PhaseRegAlloc *ra_, outputStream *st) const {
  Compile* C = ra_->C;
  st->print_cr("--- MachPrologNode ---");
  st->print("\t");
  for (int i = 0; i < OptoPrologueNops; i++) {
    st->print_cr("NOP"); st->print("\t");
  }

  if (VerifyThread) {
    st->print_cr("Verify_Thread");
    st->print("\t");
  }

  long framesize = C->frame_size_in_bytes();
  int bangsize   = C->bang_size_in_bytes();

  // Calls to C2R adapters often do not accept exceptional returns.
  // We require that their callers must bang for them. But be
  // careful, because some VM calls (such as call site linkage) can
  // use several kilobytes of stack. But the stack safety zone should
  // account for that. See bugs 4446381, 4468289, 4497237.
  if (C->need_stack_bang(bangsize) && UseStackBanging) {
    st->print_cr("# stack bang"); st->print("\t");
  }
  st->print_cr("push_frame %d", (int)-framesize);
  st->print("\t");
}
#endif

void MachPrologNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  Compile* C = ra_->C;
  MacroAssembler _masm(&cbuf);

  __ verify_thread();

  size_t framesize = C->frame_size_in_bytes();
  size_t bangsize  = C->bang_size_in_bytes();

  assert(framesize % wordSize == 0, "must preserve wordSize alignment");

  // Calls to C2R adapters often do not accept exceptional returns.
  // We require that their callers must bang for them. But be
  // careful, because some VM calls (such as call site linkage) can
  // use several kilobytes of stack. But the stack safety zone should
  // account for that. See bugs 4446381, 4468289, 4497237.
  if (C->need_stack_bang(bangsize) && UseStackBanging) {
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
    Compile::ConstantTable& constant_table = C->constant_table();
    constant_table.set_table_base_offset(constant_table.calculate_table_base_offset());
  }
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

void MachEpilogNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  MacroAssembler _masm(&cbuf);
  Compile* C = ra_->C;
  __ verify_thread();

  // If this does safepoint polling, then do it here.
  bool need_polling = do_polling() && C->is_method_compilation();

  // Pop frame, restore return_pc, and all stuff needed by interpreter.
  int frame_size_in_bytes = Assembler::align((C->frame_slots() << LogBytesPerInt), frame::alignment_in_bytes);
  __ pop_frame_restore_retPC(frame_size_in_bytes);

  if (StackReservedPages > 0 && C->has_reserved_stack_access()) {
    __ reserved_stack_check(Z_R14);
  }

  // Touch the polling page.
  if (need_polling) {
    if (SafepointMechanism::uses_thread_local_poll()) {
      __ z_lg(Z_R1_scratch, Address(Z_thread, Thread::polling_page_offset()));
    } else {
      AddressLiteral pp(os::get_polling_page());
      __ load_const_optimized(Z_R1_scratch, pp);
    }
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

int MachEpilogNode::safepoint_offset() const {
  assert(do_polling(), "no return for this epilog node");
  return 0;
}

//=============================================================================

// Figure out which register class each belongs in: rc_int, rc_float, rc_stack.
enum RC { rc_bad, rc_int, rc_float, rc_stack };

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

  // Between float regs & stack are the flags regs.
  assert(reg >= OptoReg::stack0(), "blow up if spilling flags");
  return rc_stack;
}

// Returns size as obtained from z_emit_instr.
static unsigned int z_ld_st_helper(CodeBuffer *cbuf, const char *op_str, unsigned long opcode,
                                   int reg, int offset, bool do_print, outputStream *os) {

  if (cbuf) {
    if (opcode > (1L<<32)) {
      return z_emit_inst(*cbuf, opcode | Assembler::reg(Matcher::_regEncode[reg], 8, 48) |
                         Assembler::simm20(offset) | Assembler::reg(Z_R0, 12, 48) | Assembler::regz(Z_SP, 16, 48));
    } else {
      return z_emit_inst(*cbuf, opcode | Assembler::reg(Matcher::_regEncode[reg], 8, 32) |
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

static unsigned int z_mvc_helper(CodeBuffer *cbuf, int len, int dst_off, int src_off, bool do_print, outputStream *os) {
  if (cbuf) {
    MacroAssembler _masm(cbuf);
    __ z_mvc(dst_off, len-1, Z_SP, src_off, Z_SP);
  }

#if !defined(PRODUCT)
  else if (do_print) {
    os->print("MVC     %d(%d,SP),%d(SP)\t # MachCopy spill code",dst_off, len, src_off);
  }
#endif

  return 6;
}

uint MachSpillCopyNode::implementation(CodeBuffer *cbuf, PhaseRegAlloc *ra_, bool do_size, outputStream *os) const {
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

  if (src_lo == dst_lo && src_hi == dst_hi) {
    return 0;            // Self copy, no move.
  }

  int  src_offset = ra_->reg2offset(src_lo);
  int  dst_offset = ra_->reg2offset(dst_lo);
  bool print = !do_size;
  bool src12 = Immediate::is_uimm12(src_offset);
  bool dst12 = Immediate::is_uimm12(dst_offset);

  const char   *mnemo = NULL;
  unsigned long opc = 0;

  // Memory->Memory Spill. Use Z_R0 to hold the value.
  if (src_lo_rc == rc_stack && dst_lo_rc == rc_stack) {

    assert(!is64 || (src_hi_rc==rc_stack && dst_hi_rc==rc_stack),
           "expected same type of move for high parts");

    if (src12 && dst12) {
      return z_mvc_helper(cbuf, is64 ? 8 : 4, dst_offset, src_offset, print, os);
    }

    int r0 = Z_R0_num;
    if (is64) {
      return z_ld_st_helper(cbuf, "LG  ", LG_ZOPC, r0, src_offset, print, os) +
             z_ld_st_helper(cbuf, "STG ", STG_ZOPC, r0, dst_offset, print, os);
    }

    return z_ld_st_helper(cbuf, "LY   ", LY_ZOPC, r0, src_offset, print, os) +
           z_ld_st_helper(cbuf, "STY  ", STY_ZOPC, r0, dst_offset, print, os);
  }

  // Check for float->int copy. Requires a trip through memory.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_int) {
    Unimplemented();  // Unsafe, do not remove!
  }

  // Check for integer reg-reg copy.
  if (src_lo_rc == rc_int && dst_lo_rc == rc_int) {
    if (cbuf) {
      MacroAssembler _masm(cbuf);
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
      return z_ld_st_helper(cbuf, "STG ", STG_ZOPC, src_lo, dst_offset, print, os);
    }

    // else
    mnemo = dst12 ? "ST  " : "STY ";
    opc = dst12 ? ST_ZOPC : STY_ZOPC;

    return z_ld_st_helper(cbuf, mnemo, opc, src_lo, dst_offset, print, os);
  }

  // Check for integer load
  // Always load cOops zero-extended. That doesn't hurt int loads.
  if (dst_lo_rc == rc_int && src_lo_rc == rc_stack) {

    assert(!is64 || (dst_hi_rc==rc_int && src_hi_rc==rc_stack),
           "expected same type of move for high parts");

    mnemo = is64 ? "LG  " : "LLGF";
    opc = is64 ? LG_ZOPC : LLGF_ZOPC;

    return z_ld_st_helper(cbuf, mnemo, opc, dst_lo, src_offset, print, os);
  }

  // Check for float reg-reg copy.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_float) {
    if (cbuf) {
      MacroAssembler _masm(cbuf);
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
      return z_ld_st_helper(cbuf, mnemo, opc, src_lo, dst_offset, print, os);
    }
    // else

    mnemo = dst12 ? "STE  " : "STEY ";
    opc = dst12 ? STE_ZOPC : STEY_ZOPC;
    return z_ld_st_helper(cbuf, mnemo, opc, src_lo, dst_offset, print, os);
  }

  // Check for float load.
  if (dst_lo_rc == rc_float && src_lo_rc == rc_stack) {
    assert(!is64 || (dst_hi_rc==rc_float && src_hi_rc==rc_stack),
           "expected same type of move for high parts");

    if (is64) {
      mnemo = src12 ? "LD   " : "LDY  ";
      opc = src12 ? LD_ZOPC : LDY_ZOPC;
      return z_ld_st_helper(cbuf, mnemo, opc, dst_lo, src_offset, print, os);
    }
    // else

    mnemo = src12 ? "LE   " : "LEY  ";
    opc = src12 ? LE_ZOPC : LEY_ZOPC;
    return z_ld_st_helper(cbuf, mnemo, opc, dst_lo, src_offset, print, os);
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
    implementation(NULL, ra_, false, os);
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

void MachSpillCopyNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  implementation(&cbuf, ra_, false, NULL);
}

uint MachSpillCopyNode::size(PhaseRegAlloc *ra_) const {
  return implementation(NULL, ra_, true, NULL);
}

//=============================================================================

#if !defined(PRODUCT)
void MachNopNode::format(PhaseRegAlloc *, outputStream *os) const {
  os->print("NOP     # pad for alignment (%d nops, %d bytes)", _count, _count*MacroAssembler::nop_size());
}
#endif

void MachNopNode::emit(CodeBuffer &cbuf, PhaseRegAlloc * ra_) const {
  MacroAssembler _masm(&cbuf);

  int rem_space = 0;
  if (!(ra_->C->in_scratch_emit_size())) {
    rem_space = cbuf.insts()->remaining();
    if (rem_space <= _count*2 + 8) {
      tty->print("NopNode: _count = %3.3d, remaining space before = %d", _count, rem_space);
    }
  }

  for (int i = 0; i < _count; i++) {
    __ z_nop();
  }

  if (!(ra_->C->in_scratch_emit_size())) {
    if (rem_space <= _count*2 + 8) {
      int rem_space2 = cbuf.insts()->remaining();
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
void BoxLockNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  MacroAssembler _masm(&cbuf);

  int offset = ra_->reg2offset(in_RegMask(0).find_first_elem());
  int reg = ra_->get_encode(this);
  __ z_lay(as_Register(reg), offset, Z_SP);
}

uint BoxLockNode::size(PhaseRegAlloc *ra_) const {
  // BoxLockNode is not a MachNode, so we can't just call MachNode::size(ra_)
  return 6;
}

 
#line 771 "ad_s390.cpp"


//SourceForm

#line 1316 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"


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

void MachUEPNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  MacroAssembler _masm(&cbuf);
  const int ic_miss_offset = 2;

  // Inline_cache contains a klass.
  Register ic_klass = as_Register(Matcher::inline_cache_reg_encode());
  // ARG1 is the receiver oop.
  Register R2_receiver = Z_ARG1;
  int      klass_offset = oopDesc::klass_offset_in_bytes();
  AddressLiteral icmiss(SharedRuntime::get_ic_miss_stub());
  Register R1_ic_miss_stub_addr = Z_R1_scratch;

  // Null check of receiver.
  // This is the null check of the receiver that actually should be
  // done in the caller. It's here because in case of implicit null
  // checks we get it for free.
  assert(!MacroAssembler::needs_explicit_null_check(oopDesc::klass_offset_in_bytes()),
         "second word in oop should not require explicit null check.");
  if (!ImplicitNullChecks) {
    Label valid;
    if (VM_Version::has_CompareBranch()) {
      __ z_cgij(R2_receiver, 0, Assembler::bcondNotEqual, valid);
    } else {
      __ z_ltgr(R2_receiver, R2_receiver);
      __ z_bre(valid);
    }
    // The ic_miss_stub will handle the null pointer exception.
    __ load_const_optimized(R1_ic_miss_stub_addr, icmiss);
    __ z_br(R1_ic_miss_stub_addr);
    __ bind(valid);
  }

  // Check whether this method is the proper implementation for the class of
  // the receiver (ic miss check).
  {
    Label valid;
    // Compare cached class against klass from receiver.
    // This also does an implicit null check!
    __ compare_klass_ptr(ic_klass, klass_offset, R2_receiver, false);
    __ z_bre(valid);
    // The inline cache points to the wrong method. Call the
    // ic_miss_stub to find the proper method.
    __ load_const_optimized(R1_ic_miss_stub_addr, icmiss);
    __ z_br(R1_ic_miss_stub_addr);
    __ bind(valid);
  }

}

uint MachUEPNode::size(PhaseRegAlloc *ra_) const {
  // Determine size dynamically.
  return MachNode::size(ra_);
}

//=============================================================================


#line 850 "ad_s390.cpp"


//SourceForm

#line 1409 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"


// This exception handler code snippet is placed after the method's
// code. It is the return point if an exception occurred. it jumps to
// the exception blob.
//
// If the method gets deoptimized, the method and this code snippet
// get patched.
//
// 1) Trampoline code gets patched into the end of this exception
//   handler. the trampoline code jumps to the deoptimization blob.
//
// 2) The return address in the method's code will get patched such
//   that it jumps to the trampoline.
//
// 3) The handler will get patched such that it does not jump to the
//   exception blob, but to an entry in the deoptimization blob being
//   aware of the exception.
int HandlerImpl::emit_exception_handler(CodeBuffer &cbuf) {
  Register temp_reg = Z_R1;
  MacroAssembler _masm(&cbuf);

  address base = __ start_a_stub(size_exception_handler());
  if (base == NULL) {
    return 0;          // CodeBuffer::expand failed
  }

  int offset = __ offset();
  // Use unconditional pc-relative jump with 32-bit range here.
  __ load_const_optimized(temp_reg, (address)OptoRuntime::exception_blob()->content_begin());
  __ z_br(temp_reg);

  assert(__ offset() - offset <= (int) size_exception_handler(), "overflow");

  __ end_a_stub();

  return offset;
}

// Emit deopt handler code.
int HandlerImpl::emit_deopt_handler(CodeBuffer& cbuf) {
  MacroAssembler _masm(&cbuf);
  address        base = __ start_a_stub(size_deopt_handler());

  if (base == NULL) {
    return 0;  // CodeBuffer::expand failed
  }

  int offset = __ offset();

  // Size_deopt_handler() must be exact on zarch, so for simplicity
  // we do not use load_const_opt here.
  __ load_const(Z_R1, SharedRuntime::deopt_blob()->unpack());
  __ call(Z_R1);
  assert(__ offset() - offset == (int) size_deopt_handler(), "must be fixed size");

  __ end_a_stub();
  return offset;
}

//=============================================================================


// Given a register encoding, produce an Integer Register object.
static Register reg_to_register_object(int register_encoding) {
  assert(Z_R12->encoding() == Z_R12_enc, "wrong coding");
  return as_Register(register_encoding);
}

const bool Matcher::match_rule_supported(int opcode) {
  if (!has_match_rule(opcode)) return false;

  switch (opcode) {
    case Op_CountLeadingZerosI:
    case Op_CountLeadingZerosL:
    case Op_CountTrailingZerosI:
    case Op_CountTrailingZerosL:
      // Implementation requires FLOGR instruction, which is available since z9.
      return true;

    case Op_ReverseBytesI:
    case Op_ReverseBytesL:
      return UseByteReverseInstruction;

    // PopCount supported by H/W from z/Architecture G5 (z196) on.
    case Op_PopCountI:
    case Op_PopCountL:
      return UsePopCountInstruction && VM_Version::has_PopCount();

    case Op_StrComp:
      return SpecialStringCompareTo;
    case Op_StrEquals:
      return SpecialStringEquals;
    case Op_StrIndexOf:
    case Op_StrIndexOfChar:
      return SpecialStringIndexOf;

    case Op_GetAndAddI:
    case Op_GetAndAddL:
      return true;
      // return VM_Version::has_AtomicMemWithImmALUOps();
    case Op_GetAndSetI:
    case Op_GetAndSetL:
    case Op_GetAndSetP:
    case Op_GetAndSetN:
      return true;  // General CAS implementation, always available.

    default:
      return true;  // Per default match rules are supported.
                    // BUT: make sure match rule is not disabled by a false predicate!
  }

  return true;  // Per default match rules are supported.
                // BUT: make sure match rule is not disabled by a false predicate!
}

const bool Matcher::match_rule_supported_vector(int opcode, int vlen) {
  // TODO
  // Identify extra cases that we might want to provide match rules for
  // e.g. Op_ vector nodes and other intrinsics while guarding with vlen.
  bool ret_value = match_rule_supported(opcode);
  // Add rules here.

  return ret_value;  // Per default match rules are supported.
}

int Matcher::regnum_to_fpu_offset(int regnum) {
  ShouldNotReachHere();
  return regnum - 32; // The FP registers are in the second chunk.
}

const bool Matcher::has_predicated_vectors(void) {
  return false;
}

const int Matcher::float_pressure(int default_pressure_threshold) {
  return default_pressure_threshold;
}

const bool Matcher::convL2FSupported(void) {
  return true; // False means that conversion is done by runtime call.
}

//----------SUPERWORD HELPERS----------------------------------------

// Vector width in bytes.
const int Matcher::vector_width_in_bytes(BasicType bt) {
  assert(MaxVectorSize == 8, "");
  return 8;
}

// Vector ideal reg.
const uint Matcher::vector_ideal_reg(int size) {
  assert(MaxVectorSize == 8 && size == 8, "");
  return Op_RegL;
}

// Limits on vector size (number of elements) loaded into vector.
const int Matcher::max_vector_size(const BasicType bt) {
  assert(is_java_primitive(bt), "only primitive type vectors");
  return vector_width_in_bytes(bt)/type2aelembytes(bt);
}

const int Matcher::min_vector_size(const BasicType bt) {
  return max_vector_size(bt); // Same as max.
}

const uint Matcher::vector_shift_count_ideal_reg(int size) {
  fatal("vector shift is not supported");
  return Node::NotAMachineReg;
}

// z/Architecture does support misaligned store/load at minimal extra cost.
const bool Matcher::misaligned_vectors_ok() {
  return true;
}

// Not yet ported to z/Architecture.
const bool Matcher::pass_original_key_for_aes() {
  return false;
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

const bool Matcher::isSimpleConstant64(jlong value) {
  // Probably always true, even if a temp register is required.
  return true;
}

// Should correspond to setting above
const bool Matcher::init_array_count_is_in_bytes = false;

// Suppress CMOVL. Conditional move available on z/Architecture only from z196 onwards. Not exploited yet.
const int Matcher::long_cmove_cost() { return ConditionalMoveLimit; }

// Suppress CMOVF. Conditional move available on z/Architecture only from z196 onwards. Not exploited yet.
const int Matcher::float_cmove_cost() { return ConditionalMoveLimit; }

// Does the CPU require postalloc expand (see block.cpp for description of postalloc expand)?
const bool Matcher::require_postalloc_expand = false;

// Do we need to mask the count passed to shift instructions or does
// the cpu only look at the lower 5/6 bits anyway?
// 32bit shifts mask in emitter, 64bit shifts need no mask.
// Constant shift counts are handled in Ideal phase.
const bool Matcher::need_masked_shift_count = false;

// Set this as clone_shift_expressions.
bool Matcher::narrow_oop_use_complex_address() {
  if (Universe::narrow_oop_base() == NULL && Universe::narrow_oop_shift() == 0) return true;
  return false;
}

bool Matcher::narrow_klass_use_complex_address() {
  NOT_LP64(ShouldNotCallThis());
  assert(UseCompressedClassPointers, "only for compressed klass code");
  // TODO HS25: z port if (MatchDecodeNodes) return true;
  return false;
}

bool Matcher::const_oop_prefer_decode() {
  // Prefer ConN+DecodeN over ConP in simple compressed oops mode.
  return Universe::narrow_oop_base() == NULL;
}

bool Matcher::const_klass_prefer_decode() {
  // Prefer ConNKlass+DecodeNKlass over ConP in simple compressed klass mode.
  return Universe::narrow_klass_base() == NULL;
}

// Is it better to copy float constants, or load them directly from memory?
// Most RISCs will have to materialize an address into a
// register first, so they would do better to copy the constant from stack.
const bool Matcher::rematerialize_float_constants = false;

// If CPU can load and store mis-aligned doubles directly then no fixup is
// needed. Else we split the double into 2 integer pieces and move it
// piece-by-piece. Only happens when passing doubles into C code as the
// Java calling convention forces doubles to be aligned.
const bool Matcher::misaligned_doubles_ok = true;

// Advertise here if the CPU requires explicit rounding operations
// to implement the UseStrictFP mode.
const bool Matcher::strict_fp_requires_explicit_rounding = false;

// Do floats take an entire double register or just half?
//
// A float in resides in a zarch double register. When storing it by
// z_std, it cannot be restored in C-code by reloading it as a double
// and casting it into a float afterwards.
bool Matcher::float_in_double() { return false; }

// Do ints take an entire long register or just half?
// The relevant question is how the int is callee-saved:
// the whole long is written but de-opt'ing will have to extract
// the relevant 32 bits.
const bool Matcher::int_in_long = true;

// Constants for c2c and c calling conventions.

const MachRegisterNumbers z_iarg_reg[5] = {
  Z_R2_num, Z_R3_num, Z_R4_num, Z_R5_num, Z_R6_num
};

const MachRegisterNumbers z_farg_reg[4] = {
  Z_F0_num, Z_F2_num, Z_F4_num, Z_F6_num
};

const int z_num_iarg_registers = sizeof(z_iarg_reg) / sizeof(z_iarg_reg[0]);

const int z_num_farg_registers = sizeof(z_farg_reg) / sizeof(z_farg_reg[0]);

// Return whether or not this register is ever used as an argument. This
// function is used on startup to build the trampoline stubs in generateOptoStub.
// Registers not mentioned will be killed by the VM call in the trampoline, and
// arguments in those registers not be available to the callee.
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

bool Matcher::is_spillable_arg(int reg) {
  return can_be_java_arg(reg);
}

bool Matcher::use_asm_for_ldiv_by_con(jlong divisor) {
  return false;
}

// Register for DIVI projection of divmodI
RegMask Matcher::divI_proj_mask() {
  return _Z_RARG4_INT_REG_mask;
}

// Register for MODI projection of divmodI
RegMask Matcher::modI_proj_mask() {
  return _Z_RARG3_INT_REG_mask;
}

// Register for DIVL projection of divmodL
RegMask Matcher::divL_proj_mask() {
  return _Z_RARG4_LONG_REG_mask;
}

// Register for MODL projection of divmodL
RegMask Matcher::modL_proj_mask() {
  return _Z_RARG3_LONG_REG_mask;
}

// Copied from sparc.
const RegMask Matcher::method_handle_invoke_SP_save_mask() {
  return RegMask();
}

const bool Matcher::convi2l_type_required = true;

// Should the Matcher clone shifts on addressing modes, expecting them
// to be subsumed into complex addressing expressions or compute them
// into registers?
bool Matcher::clone_address_expressions(AddPNode* m, Matcher::MStack& mstack, VectorSet& address_visited) {
  return clone_base_plus_offset_address(m, mstack, address_visited);
}

void Compile::reshape_address(AddPNode* addp) {
}


#line 1218 "ad_s390.cpp"


//SourceForm

#line 2374 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"


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


#line 1241 "ad_s390.cpp"


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
  /*    8 */  immB_minus1_rule,
  /*    9 */  immB_n0m1_rule,
  /*   10 */  immS_minus1_rule,
  /*   11 */  immS_n0m1_rule,
  /*   12 */  immI_rule,
  /*   13 */  immI20_rule,
  /*   14 */  immI16_rule,
  /*   15 */  immI8_rule,
  /*   16 */  immI_0_rule,
  /*   17 */  immI_minus1_rule,
  /*   18 */  immI_n0m1_rule,
  /*   19 */  uimmI_rule,
  /*   20 */  uimmI16_rule,
  /*   21 */  uimmI12_rule,
  /*   22 */  uimmI8_rule,
  /*   23 */  uimmI6_rule,
  /*   24 */  uimmI5_rule,
  /*   25 */  SSlenDW_rule,
  /*   26 */  immI_1_rule,
  /*   27 */  immI_16_rule,
  /*   28 */  immI_24_rule,
  /*   29 */  immI_255_rule,
  /*   30 */  immI_32_63_rule,
  /*   31 */  uimmI_LL1_rule,
  /*   32 */  uimmI_LH1_rule,
  /*   33 */  immL_rule,
  /*   34 */  immL32_rule,
  /*   35 */  immL20_rule,
  /*   36 */  immL16_rule,
  /*   37 */  immL8_rule,
  /*   38 */  uimmL32_rule,
  /*   39 */  uimmL16_rule,
  /*   40 */  uimmL12_rule,
  /*   41 */  uimmL8_rule,
  /*   42 */  immL_FF_rule,
  /*   43 */  immL_FFFF_rule,
  /*   44 */  immL_FFFFFFFF_rule,
  /*   45 */  immL_0_rule,
  /*   46 */  uimmL_LL1_rule,
  /*   47 */  uimmL_LH1_rule,
  /*   48 */  uimmL_HL1_rule,
  /*   49 */  uimmL_HH1_rule,
  /*   50 */  immL_32bits_rule,
  /*   51 */  immP_rule,
  /*   52 */  immP32_rule,
  /*   53 */  immP16_rule,
  /*   54 */  immP8_rule,
  /*   55 */  immP0_rule,
  /*   56 */  immN_rule,
  /*   57 */  immNKlass_rule,
  /*   58 */  immN8_rule,
  /*   59 */  immN0_rule,
  /*   60 */  immD_rule,
  /*   61 */  immDpm0_rule,
  /*   62 */  immDp0_rule,
  /*   63 */  immF_rule,
  /*   64 */  immFpm0_rule,
  /*   65 */  immFp0_rule,
  /*   66 */  iRegI_rule,
  /*   67 */  noArg_iRegI_rule,
  /*   68 */  revenRegI_rule,
  /*   69 */  roddRegI_rule,
  /*   70 */  rarg1RegI_rule,
  /*   71 */  rarg2RegI_rule,
  /*   72 */  rarg3RegI_rule,
  /*   73 */  rarg4RegI_rule,
  /*   74 */  rarg5RegI_rule,
  /*   75 */  noOdd_iRegI_rule,
  /*   76 */  iRegP_rule,
  /*   77 */  threadRegP_rule,
  /*   78 */  noArg_iRegP_rule,
  /*   79 */  rarg1RegP_rule,
  /*   80 */  rarg2RegP_rule,
  /*   81 */  rarg3RegP_rule,
  /*   82 */  rarg4RegP_rule,
  /*   83 */  rarg5RegP_rule,
  /*   84 */  memoryRegP_rule,
  /*   85 */  revenRegP_rule,
  /*   86 */  roddRegP_rule,
  /*   87 */  lock_ptr_RegP_rule,
  /*   88 */  rscratch2RegP_rule,
  /*   89 */  iRegN_rule,
  /*   90 */  noArg_iRegN_rule,
  /*   91 */  rarg1RegN_rule,
  /*   92 */  rarg2RegN_rule,
  /*   93 */  rarg3RegN_rule,
  /*   94 */  rarg4RegN_rule,
  /*   95 */  rarg5RegN_rule,
  /*   96 */  iRegL_rule,
  /*   97 */  revenRegL_rule,
  /*   98 */  roddRegL_rule,
  /*   99 */  rarg1RegL_rule,
  /*  100 */  rarg5RegL_rule,
  /*  101 */  flagsReg_rule,
  /*  102 */  TD_flagsReg_rule,
  /*  103 */  regD_rule,
  /*  104 */  rscratchRegD_rule,
  /*  105 */  regF_rule,
  /*  106 */  rscratchRegF_rule,
  /*  107 */  inline_cache_regP_rule,
  /*  108 */  compiler_method_oop_regP_rule,
  /*  109 */  interpreter_method_oop_regP_rule,
  /*  110 */  iRegP2N_rule,
  /*  111 */  iRegN2P_rule,
  /*  112 */  indirect_rule,
  /*  113 */  indOffset20_rule,
  /*  114 */  indOffset20Narrow_rule,
  /*  115 */  indOffset12_rule,
  /*  116 */  indOffset12Narrow_rule,
  /*  117 */  indIndex_rule,
  /*  118 */  indOffset20index_rule,
  /*  119 */  indOffset20indexNarrow_rule,
  /*  120 */  indOffset12index_rule,
  /*  121 */  indOffset12indexNarrow_rule,
  /*  122 */  stackSlotI_rule,
  /*  123 */  stackSlotP_rule,
  /*  124 */  stackSlotF_rule,
  /*  125 */  stackSlotD_rule,
  /*  126 */  stackSlotL_rule,
  /*  127 */  cmpOpT_rule,
  /*  128 */  cmpOpF_rule,
  /*  129 */  cmpOp_rule,
  // last operand
  /*  130 */  memory_rule,
  /*  131 */  memoryRXY_rule,
  /*  132 */  memoryRX_rule,
  /*  133 */  memoryRSY_rule,
  /*  134 */  memoryRS_rule,
  /*  135 */  iRegN_P2N_rule,
  /*  136 */  iRegP_N2P_rule,
  // last operand class
  /*  137 */  _DecodeN_iRegN__rule,
  /*  138 */  _AddP_memoryRegP_iRegL_rule,
  /*  139 */  _AddP__DecodeN_iRegN__iRegL_rule,
  /*  140 */  _LoadB_memory__rule,
  /*  141 */  _LoadUB_memory__rule,
  /*  142 */  _LoadS_memory__rule,
  /*  143 */  _LoadUS_memory__rule,
  /*  144 */  _LoadI_memory__rule,
  /*  145 */  _ConvI2L__LoadI_memory___rule,
  /*  146 */  _LoadP_memory__rule,
  /*  147 */  _LoadN_memory__rule,
  /*  148 */  _LoadNKlass_memory__rule,
  /*  149 */  _Binary_iRegL_iRegN_rule,
  /*  150 */  _Binary_cmpOp_flagsReg_rule,
  /*  151 */  _Binary_iRegN_iRegN_P2N_rule,
  /*  152 */  _Binary_iRegN_immN0_rule,
  /*  153 */  _Binary_iRegI_iRegI_rule,
  /*  154 */  _Binary_iRegI_immI16_rule,
  /*  155 */  _Binary_iRegP_iRegP_N2P_rule,
  /*  156 */  _Binary_iRegP_immP0_rule,
  /*  157 */  _Binary_cmpOpF_flagsReg_rule,
  /*  158 */  _Binary_regF_regF_rule,
  /*  159 */  _Binary_regD_regD_rule,
  /*  160 */  _Binary_iRegL_iRegL_rule,
  /*  161 */  _Binary_iRegL_immL16_rule,
  /*  162 */  _Binary_rarg5RegP_iRegP_N2P_rule,
  /*  163 */  _Binary_rarg5RegL_iRegL_rule,
  /*  164 */  _Binary_rarg5RegI_iRegI_rule,
  /*  165 */  _Binary_rarg5RegN_iRegN_P2N_rule,
  /*  166 */  _AddI_iRegI_iRegI_rule,
  /*  167 */  _LoadI_memoryRSY__rule,
  /*  168 */  _AddI__LoadI_memoryRSY__immI8_rule,
  /*  169 */  _ConvI2L_iRegI__rule,
  /*  170 */  _LoadL_memory__rule,
  /*  171 */  _AddL_iRegL_iRegL_rule,
  /*  172 */  _LoadL_memoryRSY__rule,
  /*  173 */  _AddL__LoadL_memoryRSY__immL8_rule,
  /*  174 */  _AddP_iRegP_N2P_iRegL_rule,
  /*  175 */  _LoadP_memoryRSY__rule,
  /*  176 */  _AddP__LoadP_memoryRSY__immL8_rule,
  /*  177 */  _CastP2X_iRegP_N2P__rule,
  /*  178 */  _LShiftI_iRegI_immI8_rule,
  /*  179 */  _URShiftI_iRegI_immI8_rule,
  /*  180 */  _LShiftL_iRegL_immI8_rule,
  /*  181 */  _URShiftL_iRegL_immI8_rule,
  /*  182 */  _LoadF_memoryRX__rule,
  /*  183 */  _LoadD_memoryRX__rule,
  /*  184 */  _NegF_regF__rule,
  /*  185 */  _NegD_regD__rule,
  /*  186 */  _Binary_regF__LoadF_memoryRX__rule,
  /*  187 */  _Binary_regD__LoadD_memoryRX__rule,
  /*  188 */  _Binary__LoadF_memoryRX__regF_rule,
  /*  189 */  _Binary__LoadD_memoryRX__regD_rule,
  /*  190 */  _AbsF_regF__rule,
  /*  191 */  _AbsD_regD__rule,
  /*  192 */  _ConvF2D_regF__rule,
  /*  193 */  _SqrtD__ConvF2D_regF___rule,
  /*  194 */  _ConvF2D_memoryRX__rule,
  /*  195 */  _SqrtD__ConvF2D_memoryRX___rule,
  /*  196 */  _LShiftI_iRegI_immI_16_rule,
  /*  197 */  _LShiftI_iRegI_immI_24_rule,
  /*  198 */  _RShiftL_iRegL_immI_32_63_rule,
  /*  199 */  _CmpU_iRegI_uimmI16_rule,
  /*  200 */  _CmpU_iRegI_iRegI_rule,
  /*  201 */  _CmpP_iRegP_N2P_immP0_rule,
  /*  202 */  _CmpN_iRegN_P2N_immN0_rule,
  /*  203 */  _AbsI_iRegI__rule,
  /*  204 */  _CmpI_iRegI_iRegI_rule,
  /*  205 */  _CmpL_iRegL_iRegL_rule,
  /*  206 */  _CmpP_iRegP_iRegP_rule,
  /*  207 */  _CmpP__DecodeN_iRegN___DecodeN_iRegN__rule,
  /*  208 */  _CmpI_iRegI_immI8_rule,
  /*  209 */  _CmpU_iRegI_uimmI8_rule,
  /*  210 */  _CmpL_iRegL_immL8_rule,
  /*  211 */  _CmpP_iRegP_immP8_rule,
  /*  212 */  _CmpP__DecodeN_iRegN__immP0_rule,
  /*  213 */  _DecodeN_immN8__rule,
  /*  214 */  _CmpP__DecodeN_iRegN___DecodeN_immN8__rule,
  /*  215 */  _PartialSubtypeCheck_rarg2RegP_rarg3RegP_rule,
  /*  216 */  _Binary_iRegP_iRegP_rule,
  /*  217 */  _Binary_iRegP_rarg2RegI_rule,
  /*  218 */  _Binary_iRegP_rarg5RegI_rule,
  /*  219 */  _Binary_iRegP_iRegI_rule,
  /*  220 */  _Binary_immP_immI_1_rule,
  /*  221 */  _Binary_iRegP_immI16_rule,
  /*  222 */  _Binary_iRegP_immI_rule,
  // last internally defined operand
  /*  223 */  stackSlotI_rule,
  /*  224 */  stackSlotL_rule,
  /*  225 */  stackSlotP_rule,
  /*  226 */  stackSlotF_rule,
  /*  227 */  stackSlotD_rule,
  /*  228 */  stackSlotD_rule,
  /*  229 */  stackSlotF_rule,
  /*  230 */  iRegI_rule,
  /*  231 */  iRegL_rule,
  /*  232 */  iRegP_rule,
  /*  233 */  regF_rule,
  /*  234 */  regD_rule,
  /*  235 */  iRegI_rule,
  /*  236 */  iRegI_rule,
  /*  237 */  iRegI_rule,
  /*  238 */  iRegI_rule,
  /*  239 */  iRegL_rule,
  /*  240 */  iRegL_rule,
  /*  241 */  iRegL_rule,
  /*  242 */  iRegL_rule,
  /*  243 */  iRegP_rule,
  /*  244 */  iRegP_rule,
  /*  245 */  regF_rule,
  /*  246 */  regD_rule,
  /*  247 */  regF_rule,
  /*  248 */  regD_rule,
  /*  249 */  iRegN_rule,
  /*  250 */  iRegN_rule,
  /*  251 */  iRegN_rule,
  /*  252 */  iRegL_rule,
  /*  253 */  0,
  /*  254 */  flagsReg_rule,
  /*  255 */  flagsReg_rule,
  /*  256 */  flagsReg_rule,
  /*  257 */  flagsReg_rule,
  /*  258 */  regD_rule,
  /*  259 */  regF_rule,
  /*  260 */  iRegP_rule,
  /*  261 */  iRegL_rule,
  /*  262 */  threadRegP_rule,
  /*  263 */  iRegP_rule,
  /*  264 */  iRegP_rule,
  /*  265 */  iRegI_rule,
  /*  266 */  flagsReg_rule,
  /*  267 */  flagsReg_rule,
  /*  268 */  flagsReg_rule,
  /*  269 */  flagsReg_rule,
  /*  270 */  flagsReg_rule,
  /*  271 */  flagsReg_rule,
  /*  272 */  flagsReg_rule,
  /*  273 */  flagsReg_rule,
  /*  274 */  flagsReg_rule,
  /*  275 */  flagsReg_rule,
  /*  276 */  flagsReg_rule,
  /*  277 */  flagsReg_rule,
  /*  278 */  iRegI_rule,
  /*  279 */  regF_rule,
  /*  280 */  iRegL_rule,
  /*  281 */  regD_rule,
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
  /*  307 */  flagsReg_rule,
  /*  308 */  flagsReg_rule,
  /*  309 */  flagsReg_rule,
  /*  310 */  flagsReg_rule,
  /*  311 */  flagsReg_rule,
  /*  312 */  flagsReg_rule,
  /*  313 */  0,
  /*  314 */  iRegI_rule,
  /*  315 */  iRegL_rule,
  /*  316 */  iRegI_rule,
  /*  317 */  iRegL_rule,
  /*  318 */  iRegI_rule,
  /*  319 */  iRegL_rule,
  /*  320 */  iRegI_rule,
  /*  321 */  iRegL_rule,
  /*  322 */  iRegI_rule,
  /*  323 */  iRegL_rule,
  /*  324 */  iRegL_rule,
  /*  325 */  iRegI_rule,
  /*  326 */  iRegL_rule,
  /*  327 */  iRegL_rule,
  /*  328 */  iRegP_rule,
  /*  329 */  iRegP_rule,
  /*  330 */  0,
  /*  331 */  regF_rule,
  /*  332 */  regD_rule,
  /*  333 */  regD_rule,
  /*  334 */  Universe_rule,
  /*  335 */  Universe_rule,
  /*  336 */  Universe_rule,
  /*  337 */  Universe_rule,
  /*  338 */  Universe_rule,
  /*  339 */  Universe_rule,
  /*  340 */  Universe_rule,
  /*  341 */  Universe_rule,
  /*  342 */  Universe_rule,
  /*  343 */  Universe_rule,
  /*  344 */  Universe_rule,
  /*  345 */  Universe_rule,
  /*  346 */  Universe_rule,
  /*  347 */  Universe_rule,
  /*  348 */  iRegL_rule,
  /*  349 */  iRegN_rule,
  /*  350 */  iRegN_rule,
  /*  351 */  iRegP_rule,
  /*  352 */  iRegP_rule,
  /*  353 */  iRegP_rule,
  /*  354 */  iRegP_rule,
  /*  355 */  iRegP_rule,
  /*  356 */  iRegP_rule,
  /*  357 */  iRegP_rule,
  /*  358 */  iRegP_rule,
  /*  359 */  iRegP_rule,
  /*  360 */  iRegP_rule,
  /*  361 */  iRegN_rule,
  /*  362 */  iRegN_rule,
  /*  363 */  iRegN_rule,
  /*  364 */  iRegN_rule,
  /*  365 */  iRegN_rule,
  /*  366 */  iRegN_rule,
  /*  367 */  iRegN_rule,
  /*  368 */  Universe_rule,
  /*  369 */  Universe_rule,
  /*  370 */  Universe_rule,
  /*  371 */  Universe_rule,
  /*  372 */  Universe_rule,
  /*  373 */  Universe_rule,
  /*  374 */  Universe_rule,
  /*  375 */  Universe_rule,
  /*  376 */  Universe_rule,
  /*  377 */  Universe_rule,
  /*  378 */  Universe_rule,
  /*  379 */  Universe_rule,
  /*  380 */  iRegN_rule,
  /*  381 */  iRegN_rule,
  /*  382 */  iRegI_rule,
  /*  383 */  iRegI_rule,
  /*  384 */  iRegP_rule,
  /*  385 */  iRegP_rule,
  /*  386 */  regF_rule,
  /*  387 */  regD_rule,
  /*  388 */  iRegL_rule,
  /*  389 */  iRegL_rule,
  /*  390 */  iRegP_rule,
  /*  391 */  iRegI_rule,
  /*  392 */  iRegI_rule,
  /*  393 */  iRegI_rule,
  /*  394 */  iRegI_rule,
  /*  395 */  Universe_rule,
  /*  396 */  iRegI_rule,
  /*  397 */  iRegI_rule,
  /*  398 */  iRegI_rule,
  /*  399 */  Universe_rule,
  /*  400 */  iRegL_rule,
  /*  401 */  iRegL_rule,
  /*  402 */  iRegL_rule,
  /*  403 */  iRegI_rule,
  /*  404 */  iRegL_rule,
  /*  405 */  iRegI_rule,
  /*  406 */  iRegL_rule,
  /*  407 */  iRegN_rule,
  /*  408 */  iRegP_rule,
  /*  409 */  iRegI_rule,
  /*  410 */  iRegI_rule,
  /*  411 */  iRegI_rule,
  /*  412 */  iRegI_rule,
  /*  413 */  iRegI_rule,
  /*  414 */  iRegI_rule,
  /*  415 */  iRegI_rule,
  /*  416 */  iRegI_rule,
  /*  417 */  iRegI_rule,
  /*  418 */  iRegI_rule,
  /*  419 */  iRegI_rule,
  /*  420 */  Universe_rule,
  /*  421 */  iRegL_rule,
  /*  422 */  iRegL_rule,
  /*  423 */  iRegL_rule,
  /*  424 */  iRegL_rule,
  /*  425 */  iRegL_rule,
  /*  426 */  iRegL_rule,
  /*  427 */  iRegL_rule,
  /*  428 */  iRegL_rule,
  /*  429 */  iRegL_rule,
  /*  430 */  iRegL_rule,
  /*  431 */  iRegL_rule,
  /*  432 */  iRegL_rule,
  /*  433 */  iRegL_rule,
  /*  434 */  iRegL_rule,
  /*  435 */  iRegL_rule,
  /*  436 */  Universe_rule,
  /*  437 */  iRegP_rule,
  /*  438 */  iRegP_rule,
  /*  439 */  iRegP_rule,
  /*  440 */  iRegP_rule,
  /*  441 */  iRegP_rule,
  /*  442 */  iRegP_rule,
  /*  443 */  iRegP_rule,
  /*  444 */  iRegP_rule,
  /*  445 */  iRegP_rule,
  /*  446 */  iRegP_rule,
  /*  447 */  iRegP_rule,
  /*  448 */  iRegP_rule,
  /*  449 */  Universe_rule,
  /*  450 */  iRegI_rule,
  /*  451 */  iRegI_rule,
  /*  452 */  iRegI_rule,
  /*  453 */  iRegI_rule,
  /*  454 */  iRegL_rule,
  /*  455 */  iRegL_rule,
  /*  456 */  iRegL_rule,
  /*  457 */  iRegL_rule,
  /*  458 */  iRegL_rule,
  /*  459 */  iRegI_rule,
  /*  460 */  iRegI_rule,
  /*  461 */  iRegI_rule,
  /*  462 */  iRegI_rule,
  /*  463 */  iRegI_rule,
  /*  464 */  iRegL_rule,
  /*  465 */  iRegL_rule,
  /*  466 */  iRegL_rule,
  /*  467 */  iRegL_rule,
  /*  468 */  iRegL_rule,
  /*  469 */  iRegL_rule,
  /*  470 */  iRegL_rule,
  /*  471 */  iRegL_rule,
  /*  472 */  iRegL_rule,
  /*  473 */  revenRegL_rule,
  /*  474 */  Universe_rule,
  /*  475 */  roddRegI_rule,
  /*  476 */  roddRegI_rule,
  /*  477 */  Universe_rule,
  /*  478 */  roddRegL_rule,
  /*  479 */  roddRegL_rule,
  /*  480 */  revenRegI_rule,
  /*  481 */  revenRegI_rule,
  /*  482 */  revenRegL_rule,
  /*  483 */  revenRegL_rule,
  /*  484 */  iRegI_rule,
  /*  485 */  iRegI_rule,
  /*  486 */  iRegI_rule,
  /*  487 */  iRegL_rule,
  /*  488 */  iRegL_rule,
  /*  489 */  iRegL_rule,
  /*  490 */  iRegI_rule,
  /*  491 */  iRegI_rule,
  /*  492 */  iRegL_rule,
  /*  493 */  iRegL_rule,
  /*  494 */  iRegI_rule,
  /*  495 */  iRegI_rule,
  /*  496 */  iRegL_rule,
  /*  497 */  iRegL_rule,
  /*  498 */  iRegL_rule,
  /*  499 */  iRegI_rule,
  /*  500 */  iRegI_rule,
  /*  501 */  iRegL_rule,
  /*  502 */  iRegL_rule,
  /*  503 */  iRegI_rule,
  /*  504 */  iRegI_rule,
  /*  505 */  iRegL_rule,
  /*  506 */  iRegL_rule,
  /*  507 */  regF_rule,
  /*  508 */  regF_rule,
  /*  509 */  regF_rule,
  /*  510 */  regD_rule,
  /*  511 */  regD_rule,
  /*  512 */  regD_rule,
  /*  513 */  regF_rule,
  /*  514 */  regF_rule,
  /*  515 */  regD_rule,
  /*  516 */  regD_rule,
  /*  517 */  regF_rule,
  /*  518 */  regF_rule,
  /*  519 */  regF_rule,
  /*  520 */  regD_rule,
  /*  521 */  regD_rule,
  /*  522 */  regD_rule,
  /*  523 */  regF_rule,
  /*  524 */  regD_rule,
  /*  525 */  regF_rule,
  /*  526 */  regD_rule,
  /*  527 */  regF_rule,
  /*  528 */  regD_rule,
  /*  529 */  regF_rule,
  /*  530 */  regD_rule,
  /*  531 */  regF_rule,
  /*  532 */  regD_rule,
  /*  533 */  regF_rule,
  /*  534 */  regD_rule,
  /*  535 */  regF_rule,
  /*  536 */  regF_rule,
  /*  537 */  regD_rule,
  /*  538 */  regD_rule,
  /*  539 */  regF_rule,
  /*  540 */  regD_rule,
  /*  541 */  regF_rule,
  /*  542 */  regD_rule,
  /*  543 */  regF_rule,
  /*  544 */  regD_rule,
  /*  545 */  regF_rule,
  /*  546 */  regD_rule,
  /*  547 */  regF_rule,
  /*  548 */  regD_rule,
  /*  549 */  iRegI_rule,
  /*  550 */  iRegI_rule,
  /*  551 */  iRegI_rule,
  /*  552 */  iRegI_rule,
  /*  553 */  iRegI_rule,
  /*  554 */  iRegI_rule,
  /*  555 */  iRegL_rule,
  /*  556 */  iRegL_rule,
  /*  557 */  iRegL_rule,
  /*  558 */  iRegL_rule,
  /*  559 */  iRegL_rule,
  /*  560 */  iRegL_rule,
  /*  561 */  iRegL_rule,
  /*  562 */  iRegI_rule,
  /*  563 */  iRegI_rule,
  /*  564 */  iRegI_rule,
  /*  565 */  iRegI_rule,
  /*  566 */  iRegI_rule,
  /*  567 */  iRegL_rule,
  /*  568 */  iRegL_rule,
  /*  569 */  iRegL_rule,
  /*  570 */  iRegL_rule,
  /*  571 */  iRegI_rule,
  /*  572 */  iRegI_rule,
  /*  573 */  iRegI_rule,
  /*  574 */  iRegI_rule,
  /*  575 */  iRegI_rule,
  /*  576 */  iRegL_rule,
  /*  577 */  iRegL_rule,
  /*  578 */  iRegL_rule,
  /*  579 */  iRegL_rule,
  /*  580 */  iRegI_rule,
  /*  581 */  iRegI_rule,
  /*  582 */  iRegI_rule,
  /*  583 */  iRegI_rule,
  /*  584 */  regF_rule,
  /*  585 */  iRegI_rule,
  /*  586 */  iRegI_rule,
  /*  587 */  iRegL_rule,
  /*  588 */  iRegL_rule,
  /*  589 */  regD_rule,
  /*  590 */  regD_rule,
  /*  591 */  regD_rule,
  /*  592 */  regF_rule,
  /*  593 */  iRegL_rule,
  /*  594 */  iRegL_rule,
  /*  595 */  iRegL_rule,
  /*  596 */  iRegL_rule,
  /*  597 */  iRegI_rule,
  /*  598 */  iRegI_rule,
  /*  599 */  stackSlotF_rule,
  /*  600 */  stackSlotL_rule,
  /*  601 */  stackSlotD_rule,
  /*  602 */  regF_rule,
  /*  603 */  regD_rule,
  /*  604 */  iRegI_rule,
  /*  605 */  iRegI_rule,
  /*  606 */  Universe_rule,
  /*  607 */  Universe_rule,
  /*  608 */  Universe_rule,
  /*  609 */  Universe_rule,
  /*  610 */  Universe_rule,
  /*  611 */  iRegI_rule,
  /*  612 */  iRegI_rule,
  /*  613 */  iRegI_rule,
  /*  614 */  iRegI_rule,
  /*  615 */  iRegI_rule,
  /*  616 */  iRegI_rule,
  /*  617 */  iRegI_rule,
  /*  618 */  iRegI_rule,
  /*  619 */  iRegI_rule,
  /*  620 */  iRegI_rule,
  /*  621 */  iRegI_rule,
  /*  622 */  iRegI_rule,
  /*  623 */  iRegI_rule,
  /*  624 */  iRegI_rule,
  /*  625 */  iRegI_rule,
  /*  626 */  iRegI_rule,
  /*  627 */  iRegI_rule,
  /*  628 */  iRegI_rule,
  /*  629 */  iRegI_rule,
  /*  630 */  iRegI_rule,
  /*  631 */  Universe_rule,
  /*  632 */  Universe_rule,
  /*  633 */  Universe_rule,
  /*  634 */  Universe_rule,
  /*  635 */  Universe_rule,
  /*  636 */  Universe_rule,
  /*  637 */  Universe_rule,
  /*  638 */  Universe_rule,
  /*  639 */  Universe_rule,
  /*  640 */  Universe_rule,
  /*  641 */  Universe_rule,
  /*  642 */  Universe_rule,
  /*  643 */  Universe_rule,
  /*  644 */  Universe_rule,
  /*  645 */  Universe_rule,
  /*  646 */  Universe_rule,
  /*  647 */  Universe_rule,
  /*  648 */  Universe_rule,
  /*  649 */  Universe_rule,
  /*  650 */  Universe_rule,
  /*  651 */  Universe_rule,
  /*  652 */  Universe_rule,
  /*  653 */  Universe_rule,
  /*  654 */  Universe_rule,
  /*  655 */  Universe_rule,
  /*  656 */  Universe_rule,
  /*  657 */  Universe_rule,
  /*  658 */  Universe_rule,
  /*  659 */  Universe_rule,
  /*  660 */  Universe_rule,
  /*  661 */  Universe_rule,
  /*  662 */  Universe_rule,
  /*  663 */  iRegI_rule,
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
  /*  674 */  rarg1RegP_rule,
  /*  675 */  Universe_rule,
  /*  676 */  Universe_rule,
  /*  677 */  rarg1RegP_rule,
  /*  678 */  Universe_rule,
  /*  679 */  Universe_rule,
  /*  680 */  Universe_rule,
  /*  681 */  iRegI_rule,
  /*  682 */  iRegI_rule,
  /*  683 */  iRegI_rule,
  /*  684 */  iRegI_rule,
  /*  685 */  iRegI_rule,
  /*  686 */  iRegI_rule,
  /*  687 */  iRegI_rule,
  /*  688 */  iRegI_rule,
  /*  689 */  iRegI_rule,
  /*  690 */  iRegI_rule,
  /*  691 */  iRegI_rule,
  /*  692 */  iRegI_rule,
  /*  693 */  iRegI_rule,
  /*  694 */  iRegI_rule,
  /*  695 */  iRegI_rule,
  /*  696 */  iRegI_rule,
  /*  697 */  iRegI_rule,
  /*  698 */  iRegI_rule,
  /*  699 */  iRegI_rule,
  /*  700 */  iRegI_rule,
  /*  701 */  iRegI_rule,
  /*  702 */  Universe_rule,
  /*  703 */  Universe_rule,
  /*  704 */  iRegI_rule,
  /*  705 */  iRegI_rule,
  /*  706 */  0,
  /*  707 */  iRegL_rule,
  /*  708 */  iRegL_rule,
  /*  709 */  iRegL_rule,
  /*  710 */  iRegL_rule,
  /*  711 */  iRegL_rule,
  /*  712 */  iRegL_rule,
  /*  713 */  iRegL_rule,
  /*  714 */  iRegL_rule,
  /*  715 */  iRegL_rule,
  /*  716 */  iRegL_rule,
  /*  717 */  iRegL_rule,
  /*  718 */  iRegL_rule,
  /*  719 */  iRegL_rule,
  /*  720 */  iRegL_rule,
  /*  721 */  iRegL_rule,
  /*  722 */  iRegL_rule,
  /*  723 */  iRegL_rule,
  /*  724 */  Universe_rule,
  /*  725 */  iRegL_rule,
  /*  726 */  iRegI_rule,
  /*  727 */  iRegL_rule,
  /*  728 */  revenRegI_rule,
  /*  729 */  revenRegI_rule,
  /*  730 */  revenRegI_rule,
  /*  731 */  revenRegI_rule,
  /*  732 */  iRegI_rule,
  /*  733 */  iRegI_rule,
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
  /*  110 */  iRegP_rule,
  /*  111 */  iRegN_rule,
  /*  112 */  0,
  /*  113 */  memoryRegP_rule,
  /*  114 */  _DecodeN_iRegN__rule,
  /*  115 */  memoryRegP_rule,
  /*  116 */  _DecodeN_iRegN__rule,
  /*  117 */  memoryRegP_rule,
  /*  118 */  _AddP_memoryRegP_iRegL_rule,
  /*  119 */  _AddP__DecodeN_iRegN__iRegL_rule,
  /*  120 */  _AddP_memoryRegP_iRegL_rule,
  /*  121 */  _AddP__DecodeN_iRegN__iRegL_rule,
  /*  122 */  0,
  /*  123 */  0,
  /*  124 */  0,
  /*  125 */  0,
  /*  126 */  0,
  /*  127 */  0,
  /*  128 */  0,
  /*  129 */  0,
  // last operand
  /*  130 */  0,
  /*  131 */  0,
  /*  132 */  0,
  /*  133 */  0,
  /*  134 */  0,
  /*  135 */  0,
  /*  136 */  0,
  // last operand class
  /*  137 */  iRegN_rule,
  /*  138 */  memoryRegP_rule,
  /*  139 */  _DecodeN_iRegN__rule,
  /*  140 */  memory_rule,
  /*  141 */  memory_rule,
  /*  142 */  memory_rule,
  /*  143 */  memory_rule,
  /*  144 */  memory_rule,
  /*  145 */  _LoadI_memory__rule,
  /*  146 */  memory_rule,
  /*  147 */  memory_rule,
  /*  148 */  memory_rule,
  /*  149 */  iRegL_rule,
  /*  150 */  cmpOp_rule,
  /*  151 */  iRegN_rule,
  /*  152 */  iRegN_rule,
  /*  153 */  iRegI_rule,
  /*  154 */  iRegI_rule,
  /*  155 */  iRegP_rule,
  /*  156 */  iRegP_rule,
  /*  157 */  cmpOpF_rule,
  /*  158 */  regF_rule,
  /*  159 */  regD_rule,
  /*  160 */  iRegL_rule,
  /*  161 */  iRegL_rule,
  /*  162 */  rarg5RegP_rule,
  /*  163 */  rarg5RegL_rule,
  /*  164 */  rarg5RegI_rule,
  /*  165 */  rarg5RegN_rule,
  /*  166 */  iRegI_rule,
  /*  167 */  memoryRSY_rule,
  /*  168 */  _LoadI_memoryRSY__rule,
  /*  169 */  iRegI_rule,
  /*  170 */  memory_rule,
  /*  171 */  iRegL_rule,
  /*  172 */  memoryRSY_rule,
  /*  173 */  _LoadL_memoryRSY__rule,
  /*  174 */  iRegP_N2P_rule,
  /*  175 */  memoryRSY_rule,
  /*  176 */  _LoadP_memoryRSY__rule,
  /*  177 */  iRegP_N2P_rule,
  /*  178 */  iRegI_rule,
  /*  179 */  iRegI_rule,
  /*  180 */  iRegL_rule,
  /*  181 */  iRegL_rule,
  /*  182 */  memoryRX_rule,
  /*  183 */  memoryRX_rule,
  /*  184 */  regF_rule,
  /*  185 */  regD_rule,
  /*  186 */  regF_rule,
  /*  187 */  regD_rule,
  /*  188 */  _LoadF_memoryRX__rule,
  /*  189 */  _LoadD_memoryRX__rule,
  /*  190 */  regF_rule,
  /*  191 */  regD_rule,
  /*  192 */  regF_rule,
  /*  193 */  _ConvF2D_regF__rule,
  /*  194 */  memoryRX_rule,
  /*  195 */  _ConvF2D_memoryRX__rule,
  /*  196 */  iRegI_rule,
  /*  197 */  iRegI_rule,
  /*  198 */  iRegL_rule,
  /*  199 */  iRegI_rule,
  /*  200 */  iRegI_rule,
  /*  201 */  iRegP_N2P_rule,
  /*  202 */  iRegN_P2N_rule,
  /*  203 */  iRegI_rule,
  /*  204 */  iRegI_rule,
  /*  205 */  iRegL_rule,
  /*  206 */  iRegP_rule,
  /*  207 */  _DecodeN_iRegN__rule,
  /*  208 */  iRegI_rule,
  /*  209 */  iRegI_rule,
  /*  210 */  iRegL_rule,
  /*  211 */  iRegP_rule,
  /*  212 */  _DecodeN_iRegN__rule,
  /*  213 */  immN8_rule,
  /*  214 */  _DecodeN_iRegN__rule,
  /*  215 */  rarg2RegP_rule,
  /*  216 */  iRegP_rule,
  /*  217 */  iRegP_rule,
  /*  218 */  iRegP_rule,
  /*  219 */  iRegP_rule,
  /*  220 */  immP_rule,
  /*  221 */  iRegP_rule,
  /*  222 */  iRegP_rule,
  // last internally defined operand
  /*  223 */  iRegI_rule,
  /*  224 */  iRegL_rule,
  /*  225 */  iRegP_rule,
  /*  226 */  regF_rule,
  /*  227 */  regD_rule,
  /*  228 */  regD_rule,
  /*  229 */  regF_rule,
  /*  230 */  stackSlotI_rule,
  /*  231 */  stackSlotL_rule,
  /*  232 */  stackSlotP_rule,
  /*  233 */  stackSlotF_rule,
  /*  234 */  stackSlotD_rule,
  /*  235 */  immI_rule,
  /*  236 */  immI16_rule,
  /*  237 */  immI_0_rule,
  /*  238 */  uimmI16_rule,
  /*  239 */  immL_rule,
  /*  240 */  immL32_rule,
  /*  241 */  immL16_rule,
  /*  242 */  immL_0_rule,
  /*  243 */  immP_rule,
  /*  244 */  immP0_rule,
  /*  245 */  immF_rule,
  /*  246 */  immD_rule,
  /*  247 */  immFp0_rule,
  /*  248 */  immDp0_rule,
  /*  249 */  immN_rule,
  /*  250 */  immN0_rule,
  /*  251 */  immNKlass_rule,
  /*  252 */  _LoadP_memory__rule,
  /*  253 */  0,
  /*  254 */  iRegN_P2N_rule,
  /*  255 */  iRegN_P2N_rule,
  /*  256 */  iRegN_rule,
  /*  257 */  iRegN_P2N_rule,
  /*  258 */  regD_rule,
  /*  259 */  regF_rule,
  /*  260 */  iRegL_rule,
  /*  261 */  iRegP_N2P_rule,
  /*  262 */  0,
  /*  263 */  iRegP_rule,
  /*  264 */  iRegP_rule,
  /*  265 */  iRegI_rule,
  /*  266 */  indirect_rule,
  /*  267 */  indirect_rule,
  /*  268 */  iRegI_rule,
  /*  269 */  iRegI_rule,
  /*  270 */  iRegL_rule,
  /*  271 */  iRegL_rule,
  /*  272 */  iRegI_rule,
  /*  273 */  iRegI_rule,
  /*  274 */  iRegL_rule,
  /*  275 */  iRegL_rule,
  /*  276 */  immI_0_rule,
  /*  277 */  immL_0_rule,
  /*  278 */  stackSlotF_rule,
  /*  279 */  stackSlotI_rule,
  /*  280 */  stackSlotD_rule,
  /*  281 */  stackSlotL_rule,
  /*  282 */  iRegI_rule,
  /*  283 */  iRegI_rule,
  /*  284 */  iRegI_rule,
  /*  285 */  iRegI_rule,
  /*  286 */  iRegI_rule,
  /*  287 */  iRegI_rule,
  /*  288 */  iRegI_rule,
  /*  289 */  iRegI_rule,
  /*  290 */  iRegL_rule,
  /*  291 */  iRegL_rule,
  /*  292 */  iRegL_rule,
  /*  293 */  iRegL_rule,
  /*  294 */  iRegL_rule,
  /*  295 */  _ConvI2L_iRegI__rule,
  /*  296 */  iRegL_rule,
  /*  297 */  iRegL_rule,
  /*  298 */  iRegL_rule,
  /*  299 */  iRegL_rule,
  /*  300 */  iRegP_N2P_rule,
  /*  301 */  iRegP_N2P_rule,
  /*  302 */  _DecodeN_iRegN__rule,
  /*  303 */  iRegP_rule,
  /*  304 */  regF_rule,
  /*  305 */  regD_rule,
  /*  306 */  regF_rule,
  /*  307 */  regD_rule,
  /*  308 */  regF_rule,
  /*  309 */  regD_rule,
  /*  310 */  _PartialSubtypeCheck_rarg2RegP_rarg3RegP_rule,
  /*  311 */  iRegP_N2P_rule,
  /*  312 */  iRegP_N2P_rule,
  /*  313 */  0,
  /*  314 */  memory_rule,
  /*  315 */  _LoadB_memory__rule,
  /*  316 */  memory_rule,
  /*  317 */  _LoadUB_memory__rule,
  /*  318 */  memory_rule,
  /*  319 */  _LoadS_memory__rule,
  /*  320 */  memory_rule,
  /*  321 */  _LoadUS_memory__rule,
  /*  322 */  memory_rule,
  /*  323 */  _LoadI_memory__rule,
  /*  324 */  _ConvI2L__LoadI_memory___rule,
  /*  325 */  memory_rule,
  /*  326 */  memory_rule,
  /*  327 */  memory_rule,
  /*  328 */  memory_rule,
  /*  329 */  memory_rule,
  /*  330 */  0,
  /*  331 */  memory_rule,
  /*  332 */  memory_rule,
  /*  333 */  memory_rule,
  /*  334 */  memory_rule,
  /*  335 */  memory_rule,
  /*  336 */  memory_rule,
  /*  337 */  memory_rule,
  /*  338 */  memory_rule,
  /*  339 */  memory_rule,
  /*  340 */  memory_rule,
  /*  341 */  memory_rule,
  /*  342 */  memory_rule,
  /*  343 */  memoryRSY_rule,
  /*  344 */  memoryRS_rule,
  /*  345 */  memoryRS_rule,
  /*  346 */  memoryRS_rule,
  /*  347 */  memoryRS_rule,
  /*  348 */  immL_0_rule,
  /*  349 */  memory_rule,
  /*  350 */  memory_rule,
  /*  351 */  _LoadN_memory__rule,
  /*  352 */  _LoadNKlass_memory__rule,
  /*  353 */  immNKlass_rule,
  /*  354 */  iRegN_rule,
  /*  355 */  iRegN_rule,
  /*  356 */  iRegN_rule,
  /*  357 */  iRegN_rule,
  /*  358 */  iRegN_rule,
  /*  359 */  iRegN_rule,
  /*  360 */  iRegN_rule,
  /*  361 */  iRegP_rule,
  /*  362 */  iRegP_rule,
  /*  363 */  iRegP_rule,
  /*  364 */  iRegP_rule,
  /*  365 */  iRegP_rule,
  /*  366 */  iRegP_rule,
  /*  367 */  iRegP_rule,
  /*  368 */  memory_rule,
  /*  369 */  memory_rule,
  /*  370 */  0,
  /*  371 */  0,
  /*  372 */  0,
  /*  373 */  0,
  /*  374 */  0,
  /*  375 */  0,
  /*  376 */  0,
  /*  377 */  0,
  /*  378 */  0,
  /*  379 */  0,
  /*  380 */  _Binary_cmpOp_flagsReg_rule,
  /*  381 */  _Binary_cmpOp_flagsReg_rule,
  /*  382 */  _Binary_cmpOp_flagsReg_rule,
  /*  383 */  _Binary_cmpOp_flagsReg_rule,
  /*  384 */  _Binary_cmpOp_flagsReg_rule,
  /*  385 */  _Binary_cmpOp_flagsReg_rule,
  /*  386 */  _Binary_cmpOpF_flagsReg_rule,
  /*  387 */  _Binary_cmpOpF_flagsReg_rule,
  /*  388 */  _Binary_cmpOp_flagsReg_rule,
  /*  389 */  _Binary_cmpOp_flagsReg_rule,
  /*  390 */  memory_rule,
  /*  391 */  iRegP_rule,
  /*  392 */  iRegP_rule,
  /*  393 */  iRegP_rule,
  /*  394 */  iRegP_rule,
  /*  395 */  memoryRSY_rule,
  /*  396 */  memoryRSY_rule,
  /*  397 */  memoryRSY_rule,
  /*  398 */  memoryRSY_rule,
  /*  399 */  memoryRSY_rule,
  /*  400 */  memoryRSY_rule,
  /*  401 */  memoryRSY_rule,
  /*  402 */  memoryRSY_rule,
  /*  403 */  memoryRSY_rule,
  /*  404 */  memoryRSY_rule,
  /*  405 */  memoryRSY_rule,
  /*  406 */  memoryRSY_rule,
  /*  407 */  memoryRSY_rule,
  /*  408 */  memoryRSY_rule,
  /*  409 */  iRegI_rule,
  /*  410 */  iRegI_rule,
  /*  411 */  iRegI_rule,
  /*  412 */  iRegI_rule,
  /*  413 */  iRegI_rule,
  /*  414 */  iRegI_rule,
  /*  415 */  iRegI_rule,
  /*  416 */  _AddI_iRegI_iRegI_rule,
  /*  417 */  _AddI_iRegI_iRegI_rule,
  /*  418 */  iRegI_rule,
  /*  419 */  _LoadI_memory__rule,
  /*  420 */  memoryRSY_rule,
  /*  421 */  iRegL_rule,
  /*  422 */  _ConvI2L_iRegI__rule,
  /*  423 */  iRegL_rule,
  /*  424 */  iRegL_rule,
  /*  425 */  iRegL_rule,
  /*  426 */  iRegL_rule,
  /*  427 */  iRegL_rule,
  /*  428 */  iRegL_rule,
  /*  429 */  iRegL_rule,
  /*  430 */  iRegL_rule,
  /*  431 */  _ConvI2L__LoadI_memory___rule,
  /*  432 */  iRegL_rule,
  /*  433 */  _LoadL_memory__rule,
  /*  434 */  _AddL_iRegL_iRegL_rule,
  /*  435 */  _AddL_iRegL_iRegL_rule,
  /*  436 */  memoryRSY_rule,
  /*  437 */  iRegP_N2P_rule,
  /*  438 */  iRegP_rule,
  /*  439 */  iRegP_N2P_rule,
  /*  440 */  iRegP_N2P_rule,
  /*  441 */  iRegP_rule,
  /*  442 */  iRegP_N2P_rule,
  /*  443 */  memoryRegP_rule,
  /*  444 */  iRegP_rule,
  /*  445 */  _AddP_memoryRegP_iRegL_rule,
  /*  446 */  _AddP_iRegP_N2P_iRegL_rule,
  /*  447 */  _AddP_memoryRegP_iRegL_rule,
  /*  448 */  _AddP_iRegP_N2P_iRegL_rule,
  /*  449 */  memoryRSY_rule,
  /*  450 */  iRegI_rule,
  /*  451 */  iRegI_rule,
  /*  452 */  iRegI_rule,
  /*  453 */  immI_0_rule,
  /*  454 */  iRegL_rule,
  /*  455 */  iRegL_rule,
  /*  456 */  iRegL_rule,
  /*  457 */  iRegL_rule,
  /*  458 */  iRegL_rule,
  /*  459 */  iRegI_rule,
  /*  460 */  iRegI_rule,
  /*  461 */  iRegI_rule,
  /*  462 */  iRegI_rule,
  /*  463 */  _LoadI_memory__rule,
  /*  464 */  iRegL_rule,
  /*  465 */  _ConvI2L_iRegI__rule,
  /*  466 */  iRegL_rule,
  /*  467 */  iRegL_rule,
  /*  468 */  iRegL_rule,
  /*  469 */  iRegL_rule,
  /*  470 */  _ConvI2L__LoadI_memory___rule,
  /*  471 */  iRegL_rule,
  /*  472 */  _LoadL_memory__rule,
  /*  473 */  roddRegL_rule,
  /*  474 */  roddRegI_rule,
  /*  475 */  iRegI_rule,
  /*  476 */  iRegI_rule,
  /*  477 */  roddRegL_rule,
  /*  478 */  roddRegL_rule,
  /*  479 */  iRegL_rule,
  /*  480 */  iRegI_rule,
  /*  481 */  iRegI_rule,
  /*  482 */  roddRegL_rule,
  /*  483 */  iRegL_rule,
  /*  484 */  iRegI_rule,
  /*  485 */  iRegI_rule,
  /*  486 */  iRegI_rule,
  /*  487 */  iRegL_rule,
  /*  488 */  iRegL_rule,
  /*  489 */  iRegL_rule,
  /*  490 */  iRegI_rule,
  /*  491 */  iRegI_rule,
  /*  492 */  iRegL_rule,
  /*  493 */  iRegL_rule,
  /*  494 */  iRegI_rule,
  /*  495 */  iRegI_rule,
  /*  496 */  iRegL_rule,
  /*  497 */  iRegL_rule,
  /*  498 */  _CastP2X_iRegP_N2P__rule,
  /*  499 */  _LShiftI_iRegI_immI8_rule,
  /*  500 */  _URShiftI_iRegI_immI8_rule,
  /*  501 */  _LShiftL_iRegL_immI8_rule,
  /*  502 */  _URShiftL_iRegL_immI8_rule,
  /*  503 */  _URShiftI_iRegI_immI8_rule,
  /*  504 */  _LShiftI_iRegI_immI8_rule,
  /*  505 */  _URShiftL_iRegL_immI8_rule,
  /*  506 */  _LShiftL_iRegL_immI8_rule,
  /*  507 */  regF_rule,
  /*  508 */  regF_rule,
  /*  509 */  _LoadF_memoryRX__rule,
  /*  510 */  regD_rule,
  /*  511 */  regD_rule,
  /*  512 */  _LoadD_memoryRX__rule,
  /*  513 */  regF_rule,
  /*  514 */  regF_rule,
  /*  515 */  regD_rule,
  /*  516 */  regD_rule,
  /*  517 */  regF_rule,
  /*  518 */  regF_rule,
  /*  519 */  _LoadF_memoryRX__rule,
  /*  520 */  regD_rule,
  /*  521 */  regD_rule,
  /*  522 */  _LoadD_memoryRX__rule,
  /*  523 */  regF_rule,
  /*  524 */  regD_rule,
  /*  525 */  _NegF_regF__rule,
  /*  526 */  _NegD_regD__rule,
  /*  527 */  regF_rule,
  /*  528 */  regD_rule,
  /*  529 */  _NegF_regF__rule,
  /*  530 */  _NegD_regD__rule,
  /*  531 */  regF_rule,
  /*  532 */  regD_rule,
  /*  533 */  _NegF_regF__rule,
  /*  534 */  _NegD_regD__rule,
  /*  535 */  regF_rule,
  /*  536 */  regF_rule,
  /*  537 */  regD_rule,
  /*  538 */  regD_rule,
  /*  539 */  regF_rule,
  /*  540 */  regD_rule,
  /*  541 */  _AbsF_regF__rule,
  /*  542 */  _AbsD_regD__rule,
  /*  543 */  regF_rule,
  /*  544 */  regD_rule,
  /*  545 */  _SqrtD__ConvF2D_regF___rule,
  /*  546 */  regD_rule,
  /*  547 */  _SqrtD__ConvF2D_memoryRX___rule,
  /*  548 */  memoryRX_rule,
  /*  549 */  iRegI_rule,
  /*  550 */  iRegI_rule,
  /*  551 */  _LoadI_memory__rule,
  /*  552 */  iRegI_rule,
  /*  553 */  iRegI_rule,
  /*  554 */  iRegI_rule,
  /*  555 */  iRegL_rule,
  /*  556 */  iRegL_rule,
  /*  557 */  _LoadL_memory__rule,
  /*  558 */  iRegL_rule,
  /*  559 */  iRegL_rule,
  /*  560 */  iRegL_rule,
  /*  561 */  iRegL_rule,
  /*  562 */  iRegI_rule,
  /*  563 */  iRegI_rule,
  /*  564 */  _LoadI_memory__rule,
  /*  565 */  iRegI_rule,
  /*  566 */  iRegI_rule,
  /*  567 */  iRegL_rule,
  /*  568 */  iRegL_rule,
  /*  569 */  _LoadL_memory__rule,
  /*  570 */  iRegL_rule,
  /*  571 */  iRegI_rule,
  /*  572 */  iRegI_rule,
  /*  573 */  iRegI_rule,
  /*  574 */  _LoadI_memory__rule,
  /*  575 */  iRegI_rule,
  /*  576 */  iRegL_rule,
  /*  577 */  iRegL_rule,
  /*  578 */  _LoadL_memory__rule,
  /*  579 */  iRegL_rule,
  /*  580 */  iRegI_rule,
  /*  581 */  iRegP_N2P_rule,
  /*  582 */  iRegI_rule,
  /*  583 */  iRegI_rule,
  /*  584 */  regD_rule,
  /*  585 */  regF_rule,
  /*  586 */  regD_rule,
  /*  587 */  regF_rule,
  /*  588 */  regD_rule,
  /*  589 */  regF_rule,
  /*  590 */  memoryRX_rule,
  /*  591 */  iRegI_rule,
  /*  592 */  iRegI_rule,
  /*  593 */  iRegI_rule,
  /*  594 */  _ConvI2L_iRegI__rule,
  /*  595 */  _ConvI2L__LoadI_memory___rule,
  /*  596 */  iRegL_rule,
  /*  597 */  _LShiftI_iRegI_immI_16_rule,
  /*  598 */  _LShiftI_iRegI_immI_24_rule,
  /*  599 */  iRegI_rule,
  /*  600 */  regD_rule,
  /*  601 */  iRegL_rule,
  /*  602 */  iRegL_rule,
  /*  603 */  iRegL_rule,
  /*  604 */  iRegL_rule,
  /*  605 */  _RShiftL_iRegL_immI_32_63_rule,
  /*  606 */  cmpOpT_rule,
  /*  607 */  cmpOpT_rule,
  /*  608 */  cmpOpT_rule,
  /*  609 */  cmpOpT_rule,
  /*  610 */  cmpOpT_rule,
  /*  611 */  iRegI_rule,
  /*  612 */  iRegI_rule,
  /*  613 */  iRegI_rule,
  /*  614 */  iRegI_rule,
  /*  615 */  iRegI_rule,
  /*  616 */  iRegI_rule,
  /*  617 */  iRegI_rule,
  /*  618 */  iRegI_rule,
  /*  619 */  iRegI_rule,
  /*  620 */  iRegI_rule,
  /*  621 */  iRegI_rule,
  /*  622 */  iRegI_rule,
  /*  623 */  iRegI_rule,
  /*  624 */  iRegI_rule,
  /*  625 */  iRegI_rule,
  /*  626 */  iRegI_rule,
  /*  627 */  iRegI_rule,
  /*  628 */  immI_0_rule,
  /*  629 */  regF_rule,
  /*  630 */  regD_rule,
  /*  631 */  0,
  /*  632 */  0,
  /*  633 */  cmpOp_rule,
  /*  634 */  cmpOp_rule,
  /*  635 */  cmpOp_rule,
  /*  636 */  cmpOp_rule,
  /*  637 */  cmpOpT_rule,
  /*  638 */  cmpOpT_rule,
  /*  639 */  cmpOpT_rule,
  /*  640 */  cmpOpT_rule,
  /*  641 */  cmpOpT_rule,
  /*  642 */  cmpOpT_rule,
  /*  643 */  cmpOpT_rule,
  /*  644 */  cmpOpT_rule,
  /*  645 */  cmpOpT_rule,
  /*  646 */  cmpOpT_rule,
  /*  647 */  cmpOpT_rule,
  /*  648 */  cmpOpT_rule,
  /*  649 */  cmpOpT_rule,
  /*  650 */  cmpOpT_rule,
  /*  651 */  cmpOpT_rule,
  /*  652 */  cmpOpT_rule,
  /*  653 */  cmpOpT_rule,
  /*  654 */  cmpOpT_rule,
  /*  655 */  cmpOpT_rule,
  /*  656 */  cmpOpT_rule,
  /*  657 */  cmpOpT_rule,
  /*  658 */  cmpOpT_rule,
  /*  659 */  cmpOpT_rule,
  /*  660 */  cmpOpT_rule,
  /*  661 */  cmpOpT_rule,
  /*  662 */  cmpOpT_rule,
  /*  663 */  iRegL_rule,
  /*  664 */  0,
  /*  665 */  iRegP_rule,
  /*  666 */  0,
  /*  667 */  0,
  /*  668 */  0,
  /*  669 */  0,
  /*  670 */  0,
  /*  671 */  iRegP_rule,
  /*  672 */  0,
  /*  673 */  iRegP_rule,
  /*  674 */  0,
  /*  675 */  0,
  /*  676 */  0,
  /*  677 */  rarg2RegP_rule,
  /*  678 */  SSlenDW_rule,
  /*  679 */  immL_rule,
  /*  680 */  iRegL_rule,
  /*  681 */  _Binary_iRegP_iRegP_rule,
  /*  682 */  _Binary_iRegP_iRegP_rule,
  /*  683 */  _Binary_iRegP_iRegP_rule,
  /*  684 */  _Binary_iRegP_iRegP_rule,
  /*  685 */  iRegP_rule,
  /*  686 */  iRegP_rule,
  /*  687 */  _Binary_iRegP_rarg2RegI_rule,
  /*  688 */  _Binary_iRegP_rarg2RegI_rule,
  /*  689 */  _Binary_iRegP_rarg2RegI_rule,
  /*  690 */  _Binary_iRegP_rarg2RegI_rule,
  /*  691 */  _Binary_iRegP_iRegI_rule,
  /*  692 */  _Binary_iRegP_iRegI_rule,
  /*  693 */  _Binary_iRegP_iRegI_rule,
  /*  694 */  _Binary_iRegP_iRegI_rule,
  /*  695 */  _Binary_iRegP_rarg2RegI_rule,
  /*  696 */  _Binary_iRegP_rarg2RegI_rule,
  /*  697 */  _Binary_iRegP_rarg2RegI_rule,
  /*  698 */  _Binary_iRegP_rarg2RegI_rule,
  /*  699 */  _Binary_iRegP_rarg2RegI_rule,
  /*  700 */  _Binary_iRegP_rarg2RegI_rule,
  /*  701 */  iRegP_rule,
  /*  702 */  iRegP_rule,
  /*  703 */  iRegP_rule,
  /*  704 */  rarg5RegP_rule,
  /*  705 */  iRegP_rule,
  /*  706 */  0,
  /*  707 */  iRegL_rule,
  /*  708 */  iRegI_rule,
  /*  709 */  immB_n0m1_rule,
  /*  710 */  immI_0_rule,
  /*  711 */  immB_minus1_rule,
  /*  712 */  iRegI_rule,
  /*  713 */  immS_n0m1_rule,
  /*  714 */  immI_0_rule,
  /*  715 */  immS_minus1_rule,
  /*  716 */  iRegI_rule,
  /*  717 */  immI_n0m1_rule,
  /*  718 */  immI_0_rule,
  /*  719 */  immI_minus1_rule,
  /*  720 */  regF_rule,
  /*  721 */  regF_rule,
  /*  722 */  immF_rule,
  /*  723 */  immFp0_rule,
  /*  724 */  memory_rule,
  /*  725 */  memory_rule,
  /*  726 */  iRegI_rule,
  /*  727 */  iRegL_rule,
  /*  728 */  iRegI_rule,
  /*  729 */  iRegL_rule,
  /*  730 */  iRegI_rule,
  /*  731 */  iRegL_rule,
  /*  732 */  iRegI_rule,
  /*  733 */  iRegL_rule,
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
  /*  111 */  0,
  /*  112 */  0,
  /*  113 */  immL20_rule,
  /*  114 */  immL20_rule,
  /*  115 */  uimmL12_rule,
  /*  116 */  uimmL12_rule,
  /*  117 */  iRegL_rule,
  /*  118 */  immL20_rule,
  /*  119 */  immL20_rule,
  /*  120 */  uimmL12_rule,
  /*  121 */  uimmL12_rule,
  /*  122 */  0,
  /*  123 */  0,
  /*  124 */  0,
  /*  125 */  0,
  /*  126 */  0,
  /*  127 */  0,
  /*  128 */  0,
  /*  129 */  0,
  // last operand
  /*  130 */  0,
  /*  131 */  0,
  /*  132 */  0,
  /*  133 */  0,
  /*  134 */  0,
  /*  135 */  0,
  /*  136 */  0,
  // last operand class
  /*  137 */  0,
  /*  138 */  iRegL_rule,
  /*  139 */  iRegL_rule,
  /*  140 */  0,
  /*  141 */  0,
  /*  142 */  0,
  /*  143 */  0,
  /*  144 */  0,
  /*  145 */  0,
  /*  146 */  0,
  /*  147 */  0,
  /*  148 */  0,
  /*  149 */  iRegN_rule,
  /*  150 */  flagsReg_rule,
  /*  151 */  iRegN_P2N_rule,
  /*  152 */  immN0_rule,
  /*  153 */  iRegI_rule,
  /*  154 */  immI16_rule,
  /*  155 */  iRegP_N2P_rule,
  /*  156 */  immP0_rule,
  /*  157 */  flagsReg_rule,
  /*  158 */  regF_rule,
  /*  159 */  regD_rule,
  /*  160 */  iRegL_rule,
  /*  161 */  immL16_rule,
  /*  162 */  iRegP_N2P_rule,
  /*  163 */  iRegL_rule,
  /*  164 */  iRegI_rule,
  /*  165 */  iRegN_P2N_rule,
  /*  166 */  iRegI_rule,
  /*  167 */  0,
  /*  168 */  immI8_rule,
  /*  169 */  0,
  /*  170 */  0,
  /*  171 */  iRegL_rule,
  /*  172 */  0,
  /*  173 */  immL8_rule,
  /*  174 */  iRegL_rule,
  /*  175 */  0,
  /*  176 */  immL8_rule,
  /*  177 */  0,
  /*  178 */  immI8_rule,
  /*  179 */  immI8_rule,
  /*  180 */  immI8_rule,
  /*  181 */  immI8_rule,
  /*  182 */  0,
  /*  183 */  0,
  /*  184 */  0,
  /*  185 */  0,
  /*  186 */  _LoadF_memoryRX__rule,
  /*  187 */  _LoadD_memoryRX__rule,
  /*  188 */  regF_rule,
  /*  189 */  regD_rule,
  /*  190 */  0,
  /*  191 */  0,
  /*  192 */  0,
  /*  193 */  0,
  /*  194 */  0,
  /*  195 */  0,
  /*  196 */  immI_16_rule,
  /*  197 */  immI_24_rule,
  /*  198 */  immI_32_63_rule,
  /*  199 */  uimmI16_rule,
  /*  200 */  iRegI_rule,
  /*  201 */  immP0_rule,
  /*  202 */  immN0_rule,
  /*  203 */  0,
  /*  204 */  iRegI_rule,
  /*  205 */  iRegL_rule,
  /*  206 */  iRegP_rule,
  /*  207 */  _DecodeN_iRegN__rule,
  /*  208 */  immI8_rule,
  /*  209 */  uimmI8_rule,
  /*  210 */  immL8_rule,
  /*  211 */  immP8_rule,
  /*  212 */  immP0_rule,
  /*  213 */  0,
  /*  214 */  _DecodeN_immN8__rule,
  /*  215 */  rarg3RegP_rule,
  /*  216 */  iRegP_rule,
  /*  217 */  rarg2RegI_rule,
  /*  218 */  rarg5RegI_rule,
  /*  219 */  iRegI_rule,
  /*  220 */  immI_1_rule,
  /*  221 */  immI16_rule,
  /*  222 */  immI_rule,
  // last internally defined operand
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
  /*  249 */  0,
  /*  250 */  0,
  /*  251 */  0,
  /*  252 */  0,
  /*  253 */  0,
  /*  254 */  iRegN_P2N_rule,
  /*  255 */  immN_rule,
  /*  256 */  immNKlass_rule,
  /*  257 */  immN0_rule,
  /*  258 */  0,
  /*  259 */  0,
  /*  260 */  0,
  /*  261 */  0,
  /*  262 */  0,
  /*  263 */  0,
  /*  264 */  0,
  /*  265 */  0,
  /*  266 */  _Binary_rarg5RegP_iRegP_N2P_rule,
  /*  267 */  _Binary_rarg5RegL_iRegL_rule,
  /*  268 */  iRegI_rule,
  /*  269 */  immI_rule,
  /*  270 */  iRegL_rule,
  /*  271 */  immL_rule,
  /*  272 */  iRegI_rule,
  /*  273 */  immI_rule,
  /*  274 */  iRegL_rule,
  /*  275 */  immL_rule,
  /*  276 */  iRegI_rule,
  /*  277 */  iRegL_rule,
  /*  278 */  0,
  /*  279 */  0,
  /*  280 */  0,
  /*  281 */  0,
  /*  282 */  iRegI_rule,
  /*  283 */  immI_rule,
  /*  284 */  immI16_rule,
  /*  285 */  immI_0_rule,
  /*  286 */  _LoadI_memory__rule,
  /*  287 */  iRegI_rule,
  /*  288 */  uimmI_rule,
  /*  289 */  _LoadI_memory__rule,
  /*  290 */  iRegL_rule,
  /*  291 */  _ConvI2L_iRegI__rule,
  /*  292 */  immL32_rule,
  /*  293 */  immL16_rule,
  /*  294 */  immL_0_rule,
  /*  295 */  immL_0_rule,
  /*  296 */  _LoadL_memory__rule,
  /*  297 */  _ConvI2L__LoadI_memory___rule,
  /*  298 */  iRegL_rule,
  /*  299 */  uimmL32_rule,
  /*  300 */  iRegP_N2P_rule,
  /*  301 */  immP0_rule,
  /*  302 */  immP0_rule,
  /*  303 */  _LoadP_memory__rule,
  /*  304 */  regF_rule,
  /*  305 */  regD_rule,
  /*  306 */  _LoadF_memoryRX__rule,
  /*  307 */  _LoadD_memoryRX__rule,
  /*  308 */  immFpm0_rule,
  /*  309 */  immDpm0_rule,
  /*  310 */  immP0_rule,
  /*  311 */  iRegP_N2P_rule,
  /*  312 */  iRegP_N2P_rule,
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
  /*  324 */  immL_FFFFFFFF_rule,
  /*  325 */  0,
  /*  326 */  0,
  /*  327 */  0,
  /*  328 */  0,
  /*  329 */  0,
  /*  330 */  0,
  /*  331 */  0,
  /*  332 */  0,
  /*  333 */  0,
  /*  334 */  iRegI_rule,
  /*  335 */  immI_0_rule,
  /*  336 */  iRegI_rule,
  /*  337 */  iRegI_rule,
  /*  338 */  iRegL_rule,
  /*  339 */  memoryRegP_rule,
  /*  340 */  regF_rule,
  /*  341 */  regD_rule,
  /*  342 */  0,
  /*  343 */  immI8_rule,
  /*  344 */  immI16_rule,
  /*  345 */  immI16_rule,
  /*  346 */  immL16_rule,
  /*  347 */  immP16_rule,
  /*  348 */  iRegL_rule,
  /*  349 */  0,
  /*  350 */  0,
  /*  351 */  0,
  /*  352 */  0,
  /*  353 */  0,
  /*  354 */  0,
  /*  355 */  0,
  /*  356 */  0,
  /*  357 */  iRegL_rule,
  /*  358 */  iRegL_rule,
  /*  359 */  0,
  /*  360 */  0,
  /*  361 */  0,
  /*  362 */  0,
  /*  363 */  0,
  /*  364 */  _Binary_iRegL_iRegN_rule,
  /*  365 */  iRegL_rule,
  /*  366 */  0,
  /*  367 */  0,
  /*  368 */  iRegN_P2N_rule,
  /*  369 */  iRegN_rule,
  /*  370 */  0,
  /*  371 */  0,
  /*  372 */  0,
  /*  373 */  0,
  /*  374 */  0,
  /*  375 */  0,
  /*  376 */  0,
  /*  377 */  0,
  /*  378 */  0,
  /*  379 */  0,
  /*  380 */  _Binary_iRegN_iRegN_P2N_rule,
  /*  381 */  _Binary_iRegN_immN0_rule,
  /*  382 */  _Binary_iRegI_iRegI_rule,
  /*  383 */  _Binary_iRegI_immI16_rule,
  /*  384 */  _Binary_iRegP_iRegP_N2P_rule,
  /*  385 */  _Binary_iRegP_immP0_rule,
  /*  386 */  _Binary_regF_regF_rule,
  /*  387 */  _Binary_regD_regD_rule,
  /*  388 */  _Binary_iRegL_iRegL_rule,
  /*  389 */  _Binary_iRegL_immL16_rule,
  /*  390 */  0,
  /*  391 */  _Binary_rarg5RegI_iRegI_rule,
  /*  392 */  _Binary_rarg5RegL_iRegL_rule,
  /*  393 */  _Binary_rarg5RegP_iRegP_N2P_rule,
  /*  394 */  _Binary_rarg5RegN_iRegN_P2N_rule,
  /*  395 */  immI8_rule,
  /*  396 */  immI16_rule,
  /*  397 */  immI_rule,
  /*  398 */  iRegI_rule,
  /*  399 */  immL8_rule,
  /*  400 */  immL16_rule,
  /*  401 */  immL32_rule,
  /*  402 */  iRegL_rule,
  /*  403 */  iRegI_rule,
  /*  404 */  iRegL_rule,
  /*  405 */  iRegI_rule,
  /*  406 */  iRegL_rule,
  /*  407 */  iRegN_rule,
  /*  408 */  iRegP_rule,
  /*  409 */  iRegI_rule,
  /*  410 */  iRegI_rule,
  /*  411 */  immI16_rule,
  /*  412 */  immI16_rule,
  /*  413 */  immI_rule,
  /*  414 */  uimmI12_rule,
  /*  415 */  immI20_rule,
  /*  416 */  uimmI12_rule,
  /*  417 */  immI20_rule,
  /*  418 */  _LoadI_memory__rule,
  /*  419 */  iRegI_rule,
  /*  420 */  _AddI__LoadI_memoryRSY__immI8_rule,
  /*  421 */  _ConvI2L_iRegI__rule,
  /*  422 */  iRegL_rule,
  /*  423 */  iRegL_rule,
  /*  424 */  iRegL_rule,
  /*  425 */  uimmL12_rule,
  /*  426 */  immL20_rule,
  /*  427 */  immL32_rule,
  /*  428 */  immL16_rule,
  /*  429 */  immL16_rule,
  /*  430 */  _ConvI2L__LoadI_memory___rule,
  /*  431 */  iRegL_rule,
  /*  432 */  _LoadL_memory__rule,
  /*  433 */  iRegL_rule,
  /*  434 */  uimmL12_rule,
  /*  435 */  immL20_rule,
  /*  436 */  _AddL__LoadL_memoryRSY__immL8_rule,
  /*  437 */  iRegL_rule,
  /*  438 */  iRegL_rule,
  /*  439 */  iRegL_rule,
  /*  440 */  uimmL12_rule,
  /*  441 */  immL16_rule,
  /*  442 */  immL16_rule,
  /*  443 */  immL20_rule,
  /*  444 */  immL32_rule,
  /*  445 */  uimmL12_rule,
  /*  446 */  uimmL12_rule,
  /*  447 */  immL20_rule,
  /*  448 */  immL20_rule,
  /*  449 */  _AddP__LoadP_memoryRSY__immL8_rule,
  /*  450 */  iRegI_rule,
  /*  451 */  iRegI_rule,
  /*  452 */  _LoadI_memory__rule,
  /*  453 */  iRegI_rule,
  /*  454 */  iRegL_rule,
  /*  455 */  iRegL_rule,
  /*  456 */  _ConvI2L_iRegI__rule,
  /*  457 */  _ConvI2L__LoadI_memory___rule,
  /*  458 */  _LoadL_memory__rule,
  /*  459 */  iRegI_rule,
  /*  460 */  immI16_rule,
  /*  461 */  immI_rule,
  /*  462 */  _LoadI_memory__rule,
  /*  463 */  iRegI_rule,
  /*  464 */  _ConvI2L_iRegI__rule,
  /*  465 */  iRegL_rule,
  /*  466 */  iRegL_rule,
  /*  467 */  immL16_rule,
  /*  468 */  immL32_rule,
  /*  469 */  _ConvI2L__LoadI_memory___rule,
  /*  470 */  iRegL_rule,
  /*  471 */  _LoadL_memory__rule,
  /*  472 */  iRegL_rule,
  /*  473 */  iRegL_rule,
  /*  474 */  noOdd_iRegI_rule,
  /*  475 */  noOdd_iRegI_rule,
  /*  476 */  immI16_rule,
  /*  477 */  iRegL_rule,
  /*  478 */  iRegL_rule,
  /*  479 */  immL16_rule,
  /*  480 */  noOdd_iRegI_rule,
  /*  481 */  immI16_rule,
  /*  482 */  iRegL_rule,
  /*  483 */  immL16_rule,
  /*  484 */  iRegI_rule,
  /*  485 */  immI_rule,
  /*  486 */  immI_1_rule,
  /*  487 */  iRegI_rule,
  /*  488 */  immI_rule,
  /*  489 */  immI_1_rule,
  /*  490 */  iRegI_rule,
  /*  491 */  immI_rule,
  /*  492 */  iRegI_rule,
  /*  493 */  immI_rule,
  /*  494 */  iRegI_rule,
  /*  495 */  immI_rule,
  /*  496 */  iRegI_rule,
  /*  497 */  immI_rule,
  /*  498 */  immI_rule,
  /*  499 */  _URShiftI_iRegI_immI8_rule,
  /*  500 */  _LShiftI_iRegI_immI8_rule,
  /*  501 */  _URShiftL_iRegL_immI8_rule,
  /*  502 */  _LShiftL_iRegL_immI8_rule,
  /*  503 */  _LShiftI_iRegI_immI8_rule,
  /*  504 */  _URShiftI_iRegI_immI8_rule,
  /*  505 */  _LShiftL_iRegL_immI8_rule,
  /*  506 */  _URShiftL_iRegL_immI8_rule,
  /*  507 */  regF_rule,
  /*  508 */  _LoadF_memoryRX__rule,
  /*  509 */  regF_rule,
  /*  510 */  regD_rule,
  /*  511 */  _LoadD_memoryRX__rule,
  /*  512 */  regD_rule,
  /*  513 */  regF_rule,
  /*  514 */  _LoadF_memoryRX__rule,
  /*  515 */  regD_rule,
  /*  516 */  _LoadD_memoryRX__rule,
  /*  517 */  regF_rule,
  /*  518 */  _LoadF_memoryRX__rule,
  /*  519 */  regF_rule,
  /*  520 */  regD_rule,
  /*  521 */  _LoadD_memoryRX__rule,
  /*  522 */  regD_rule,
  /*  523 */  _Binary_regF_regF_rule,
  /*  524 */  _Binary_regD_regD_rule,
  /*  525 */  _Binary_regF_regF_rule,
  /*  526 */  _Binary_regD_regD_rule,
  /*  527 */  _Binary_regF__LoadF_memoryRX__rule,
  /*  528 */  _Binary_regD__LoadD_memoryRX__rule,
  /*  529 */  _Binary_regF__LoadF_memoryRX__rule,
  /*  530 */  _Binary_regD__LoadD_memoryRX__rule,
  /*  531 */  _Binary__LoadF_memoryRX__regF_rule,
  /*  532 */  _Binary__LoadD_memoryRX__regD_rule,
  /*  533 */  _Binary__LoadF_memoryRX__regF_rule,
  /*  534 */  _Binary__LoadD_memoryRX__regD_rule,
  /*  535 */  regF_rule,
  /*  536 */  _LoadF_memoryRX__rule,
  /*  537 */  regD_rule,
  /*  538 */  _LoadD_memoryRX__rule,
  /*  539 */  0,
  /*  540 */  0,
  /*  541 */  0,
  /*  542 */  0,
  /*  543 */  0,
  /*  544 */  0,
  /*  545 */  0,
  /*  546 */  0,
  /*  547 */  0,
  /*  548 */  0,
  /*  549 */  iRegI_rule,
  /*  550 */  _LoadI_memory__rule,
  /*  551 */  iRegI_rule,
  /*  552 */  uimmI_rule,
  /*  553 */  uimmI_LH1_rule,
  /*  554 */  uimmI_LL1_rule,
  /*  555 */  iRegL_rule,
  /*  556 */  _LoadL_memory__rule,
  /*  557 */  iRegL_rule,
  /*  558 */  uimmL_LL1_rule,
  /*  559 */  uimmL_LH1_rule,
  /*  560 */  uimmL_HL1_rule,
  /*  561 */  uimmL_HH1_rule,
  /*  562 */  iRegI_rule,
  /*  563 */  _LoadI_memory__rule,
  /*  564 */  iRegI_rule,
  /*  565 */  uimmI16_rule,
  /*  566 */  uimmI_rule,
  /*  567 */  iRegL_rule,
  /*  568 */  _LoadL_memory__rule,
  /*  569 */  iRegL_rule,
  /*  570 */  uimmL16_rule,
  /*  571 */  uimmL32_rule,
  /*  572 */  iRegI_rule,
  /*  573 */  _LoadI_memory__rule,
  /*  574 */  iRegI_rule,
  /*  575 */  uimmI_rule,
  /*  576 */  iRegL_rule,
  /*  577 */  _LoadL_memory__rule,
  /*  578 */  iRegL_rule,
  /*  579 */  uimmL32_rule,
  /*  580 */  0,
  /*  581 */  0,
  /*  582 */  iRegI_rule,
  /*  583 */  immI_0_rule,
  /*  584 */  0,
  /*  585 */  0,
  /*  586 */  0,
  /*  587 */  0,
  /*  588 */  0,
  /*  589 */  0,
  /*  590 */  0,
  /*  591 */  0,
  /*  592 */  0,
  /*  593 */  0,
  /*  594 */  immL_32bits_rule,
  /*  595 */  immL_32bits_rule,
  /*  596 */  immL_32bits_rule,
  /*  597 */  immI_16_rule,
  /*  598 */  immI_24_rule,
  /*  599 */  0,
  /*  600 */  0,
  /*  601 */  0,
  /*  602 */  0,
  /*  603 */  0,
  /*  604 */  0,
  /*  605 */  0,
  /*  606 */  _CmpU_iRegI_uimmI16_rule,
  /*  607 */  _CmpU_iRegI_iRegI_rule,
  /*  608 */  _CmpU_iRegI_uimmI16_rule,
  /*  609 */  _CmpP_iRegP_N2P_immP0_rule,
  /*  610 */  _CmpN_iRegN_P2N_immN0_rule,
  /*  611 */  iRegI_rule,
  /*  612 */  iRegI_rule,
  /*  613 */  iRegI_rule,
  /*  614 */  immI_rule,
  /*  615 */  immI_rule,
  /*  616 */  immI16_rule,
  /*  617 */  immI16_rule,
  /*  618 */  immI8_rule,
  /*  619 */  iRegI_rule,
  /*  620 */  iRegI_rule,
  /*  621 */  iRegI_rule,
  /*  622 */  immI_rule,
  /*  623 */  immI_rule,
  /*  624 */  immI16_rule,
  /*  625 */  immI16_rule,
  /*  626 */  immI8_rule,
  /*  627 */  0,
  /*  628 */  _AbsI_iRegI__rule,
  /*  629 */  regF_rule,
  /*  630 */  regD_rule,
  /*  631 */  0,
  /*  632 */  0,
  /*  633 */  flagsReg_rule,
  /*  634 */  flagsReg_rule,
  /*  635 */  flagsReg_rule,
  /*  636 */  flagsReg_rule,
  /*  637 */  _CmpI_iRegI_iRegI_rule,
  /*  638 */  _CmpI_iRegI_iRegI_rule,
  /*  639 */  _CmpU_iRegI_iRegI_rule,
  /*  640 */  _CmpL_iRegL_iRegL_rule,
  /*  641 */  _CmpP_iRegP_iRegP_rule,
  /*  642 */  _CmpP__DecodeN_iRegN___DecodeN_iRegN__rule,
  /*  643 */  _CmpI_iRegI_immI8_rule,
  /*  644 */  _CmpI_iRegI_immI8_rule,
  /*  645 */  _CmpU_iRegI_uimmI8_rule,
  /*  646 */  _CmpL_iRegL_immL8_rule,
  /*  647 */  _CmpP_iRegP_immP8_rule,
  /*  648 */  _CmpP__DecodeN_iRegN__immP0_rule,
  /*  649 */  _CmpP__DecodeN_iRegN___DecodeN_immN8__rule,
  /*  650 */  _CmpI_iRegI_iRegI_rule,
  /*  651 */  _CmpI_iRegI_iRegI_rule,
  /*  652 */  _CmpU_iRegI_iRegI_rule,
  /*  653 */  _CmpL_iRegL_iRegL_rule,
  /*  654 */  _CmpP_iRegP_iRegP_rule,
  /*  655 */  _CmpP__DecodeN_iRegN___DecodeN_iRegN__rule,
  /*  656 */  _CmpI_iRegI_immI8_rule,
  /*  657 */  _CmpI_iRegI_immI8_rule,
  /*  658 */  _CmpU_iRegI_uimmI8_rule,
  /*  659 */  _CmpL_iRegL_immL8_rule,
  /*  660 */  _CmpP_iRegP_immP8_rule,
  /*  661 */  _CmpP__DecodeN_iRegN__immP0_rule,
  /*  662 */  _CmpP__DecodeN_iRegN___DecodeN_immN8__rule,
  /*  663 */  iRegL_rule,
  /*  664 */  0,
  /*  665 */  0,
  /*  666 */  0,
  /*  667 */  0,
  /*  668 */  0,
  /*  669 */  0,
  /*  670 */  0,
  /*  671 */  inline_cache_regP_rule,
  /*  672 */  0,
  /*  673 */  rarg1RegP_rule,
  /*  674 */  0,
  /*  675 */  0,
  /*  676 */  0,
  /*  677 */  rarg3RegP_rule,
  /*  678 */  iRegP_N2P_rule,
  /*  679 */  iRegP_N2P_rule,
  /*  680 */  iRegP_N2P_rule,
  /*  681 */  iRegI_rule,
  /*  682 */  iRegI_rule,
  /*  683 */  uimmI8_rule,
  /*  684 */  immI8_rule,
  /*  685 */  iRegP_rule,
  /*  686 */  iRegP_rule,
  /*  687 */  _Binary_iRegP_rarg5RegI_rule,
  /*  688 */  _Binary_iRegP_rarg5RegI_rule,
  /*  689 */  _Binary_iRegP_rarg5RegI_rule,
  /*  690 */  _Binary_iRegP_rarg5RegI_rule,
  /*  691 */  iRegI_rule,
  /*  692 */  _Binary_immP_immI_1_rule,
  /*  693 */  _Binary_immP_immI_1_rule,
  /*  694 */  _Binary_immP_immI_1_rule,
  /*  695 */  _Binary_iRegP_immI16_rule,
  /*  696 */  _Binary_iRegP_immI16_rule,
  /*  697 */  _Binary_iRegP_immI16_rule,
  /*  698 */  _Binary_iRegP_rarg5RegI_rule,
  /*  699 */  _Binary_iRegP_rarg5RegI_rule,
  /*  700 */  _Binary_iRegP_rarg5RegI_rule,
  /*  701 */  _Binary_iRegP_iRegI_rule,
  /*  702 */  _Binary_iRegP_iRegI_rule,
  /*  703 */  _Binary_iRegP_immI_rule,
  /*  704 */  iRegI_rule,
  /*  705 */  _Binary_iRegP_iRegI_rule,
  /*  706 */  0,
  /*  707 */  0,
  /*  708 */  0,
  /*  709 */  0,
  /*  710 */  0,
  /*  711 */  0,
  /*  712 */  0,
  /*  713 */  0,
  /*  714 */  0,
  /*  715 */  0,
  /*  716 */  0,
  /*  717 */  0,
  /*  718 */  0,
  /*  719 */  0,
  /*  720 */  0,
  /*  721 */  0,
  /*  722 */  0,
  /*  723 */  0,
  /*  724 */  iRegL_rule,
  /*  725 */  0,
  /*  726 */  0,
  /*  727 */  0,
  /*  728 */  0,
  /*  729 */  0,
  /*  730 */  0,
  /*  731 */  0,
  /*  732 */  0,
  /*  733 */  0,
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
  /*    8 */  "IMMB_MINUS1",
  /*    9 */  "IMMB_N0M1",
  /*   10 */  "IMMS_MINUS1",
  /*   11 */  "IMMS_N0M1",
  /*   12 */  "IMMI",
  /*   13 */  "IMMI20",
  /*   14 */  "IMMI16",
  /*   15 */  "IMMI8",
  /*   16 */  "IMMI_0",
  /*   17 */  "IMMI_MINUS1",
  /*   18 */  "IMMI_N0M1",
  /*   19 */  "UIMMI",
  /*   20 */  "UIMMI16",
  /*   21 */  "UIMMI12",
  /*   22 */  "UIMMI8",
  /*   23 */  "UIMMI6",
  /*   24 */  "UIMMI5",
  /*   25 */  "SSLENDW",
  /*   26 */  "IMMI_1",
  /*   27 */  "IMMI_16",
  /*   28 */  "IMMI_24",
  /*   29 */  "IMMI_255",
  /*   30 */  "IMMI_32_63",
  /*   31 */  "UIMMI_LL1",
  /*   32 */  "UIMMI_LH1",
  /*   33 */  "IMML",
  /*   34 */  "IMML32",
  /*   35 */  "IMML20",
  /*   36 */  "IMML16",
  /*   37 */  "IMML8",
  /*   38 */  "UIMML32",
  /*   39 */  "UIMML16",
  /*   40 */  "UIMML12",
  /*   41 */  "UIMML8",
  /*   42 */  "IMML_FF",
  /*   43 */  "IMML_FFFF",
  /*   44 */  "IMML_FFFFFFFF",
  /*   45 */  "IMML_0",
  /*   46 */  "UIMML_LL1",
  /*   47 */  "UIMML_LH1",
  /*   48 */  "UIMML_HL1",
  /*   49 */  "UIMML_HH1",
  /*   50 */  "IMML_32BITS",
  /*   51 */  "IMMP",
  /*   52 */  "IMMP32",
  /*   53 */  "IMMP16",
  /*   54 */  "IMMP8",
  /*   55 */  "IMMP0",
  /*   56 */  "IMMN",
  /*   57 */  "IMMNKLASS",
  /*   58 */  "IMMN8",
  /*   59 */  "IMMN0",
  /*   60 */  "IMMD",
  /*   61 */  "IMMDPM0",
  /*   62 */  "IMMDP0",
  /*   63 */  "IMMF",
  /*   64 */  "IMMFPM0",
  /*   65 */  "IMMFP0",
  /*   66 */  "IREGI",
  /*   67 */  "NOARG_IREGI",
  /*   68 */  "REVENREGI",
  /*   69 */  "RODDREGI",
  /*   70 */  "RARG1REGI",
  /*   71 */  "RARG2REGI",
  /*   72 */  "RARG3REGI",
  /*   73 */  "RARG4REGI",
  /*   74 */  "RARG5REGI",
  /*   75 */  "NOODD_IREGI",
  /*   76 */  "IREGP",
  /*   77 */  "THREADREGP",
  /*   78 */  "NOARG_IREGP",
  /*   79 */  "RARG1REGP",
  /*   80 */  "RARG2REGP",
  /*   81 */  "RARG3REGP",
  /*   82 */  "RARG4REGP",
  /*   83 */  "RARG5REGP",
  /*   84 */  "MEMORYREGP",
  /*   85 */  "REVENREGP",
  /*   86 */  "RODDREGP",
  /*   87 */  "LOCK_PTR_REGP",
  /*   88 */  "RSCRATCH2REGP",
  /*   89 */  "IREGN",
  /*   90 */  "NOARG_IREGN",
  /*   91 */  "RARG1REGN",
  /*   92 */  "RARG2REGN",
  /*   93 */  "RARG3REGN",
  /*   94 */  "RARG4REGN",
  /*   95 */  "RARG5REGN",
  /*   96 */  "IREGL",
  /*   97 */  "REVENREGL",
  /*   98 */  "RODDREGL",
  /*   99 */  "RARG1REGL",
  /*  100 */  "RARG5REGL",
  /*  101 */  "FLAGSREG",
  /*  102 */  "TD_FLAGSREG",
  /*  103 */  "REGD",
  /*  104 */  "RSCRATCHREGD",
  /*  105 */  "REGF",
  /*  106 */  "RSCRATCHREGF",
  /*  107 */  "INLINE_CACHE_REGP",
  /*  108 */  "COMPILER_METHOD_OOP_REGP",
  /*  109 */  "INTERPRETER_METHOD_OOP_REGP",
  /*  110 */  "IREGP2N",
  /*  111 */  "IREGN2P",
  /*  112 */  "INDIRECT",
  /*  113 */  "INDOFFSET20",
  /*  114 */  "INDOFFSET20NARROW",
  /*  115 */  "INDOFFSET12",
  /*  116 */  "INDOFFSET12NARROW",
  /*  117 */  "INDINDEX",
  /*  118 */  "INDOFFSET20INDEX",
  /*  119 */  "INDOFFSET20INDEXNARROW",
  /*  120 */  "INDOFFSET12INDEX",
  /*  121 */  "INDOFFSET12INDEXNARROW",
  /*  122 */  "STACKSLOTI",
  /*  123 */  "STACKSLOTP",
  /*  124 */  "STACKSLOTF",
  /*  125 */  "STACKSLOTD",
  /*  126 */  "STACKSLOTL",
  /*  127 */  "CMPOPT",
  /*  128 */  "CMPOPF",
  /*  129 */  "CMPOP",
  // last operand
  /*  130 */  "MEMORY",
  /*  131 */  "MEMORYRXY",
  /*  132 */  "MEMORYRX",
  /*  133 */  "MEMORYRSY",
  /*  134 */  "MEMORYRS",
  /*  135 */  "IREGN_P2N",
  /*  136 */  "IREGP_N2P",
  // last operand class
  /*  137 */  "_DecodeN_iRegN_",
  /*  138 */  "_AddP_memoryRegP_iRegL",
  /*  139 */  "_AddP__DecodeN_iRegN__iRegL",
  /*  140 */  "_LoadB_memory_",
  /*  141 */  "_LoadUB_memory_",
  /*  142 */  "_LoadS_memory_",
  /*  143 */  "_LoadUS_memory_",
  /*  144 */  "_LoadI_memory_",
  /*  145 */  "_ConvI2L__LoadI_memory__",
  /*  146 */  "_LoadP_memory_",
  /*  147 */  "_LoadN_memory_",
  /*  148 */  "_LoadNKlass_memory_",
  /*  149 */  "_Binary_iRegL_iRegN",
  /*  150 */  "_Binary_cmpOp_flagsReg",
  /*  151 */  "_Binary_iRegN_iRegN_P2N",
  /*  152 */  "_Binary_iRegN_immN0",
  /*  153 */  "_Binary_iRegI_iRegI",
  /*  154 */  "_Binary_iRegI_immI16",
  /*  155 */  "_Binary_iRegP_iRegP_N2P",
  /*  156 */  "_Binary_iRegP_immP0",
  /*  157 */  "_Binary_cmpOpF_flagsReg",
  /*  158 */  "_Binary_regF_regF",
  /*  159 */  "_Binary_regD_regD",
  /*  160 */  "_Binary_iRegL_iRegL",
  /*  161 */  "_Binary_iRegL_immL16",
  /*  162 */  "_Binary_rarg5RegP_iRegP_N2P",
  /*  163 */  "_Binary_rarg5RegL_iRegL",
  /*  164 */  "_Binary_rarg5RegI_iRegI",
  /*  165 */  "_Binary_rarg5RegN_iRegN_P2N",
  /*  166 */  "_AddI_iRegI_iRegI",
  /*  167 */  "_LoadI_memoryRSY_",
  /*  168 */  "_AddI__LoadI_memoryRSY__immI8",
  /*  169 */  "_ConvI2L_iRegI_",
  /*  170 */  "_LoadL_memory_",
  /*  171 */  "_AddL_iRegL_iRegL",
  /*  172 */  "_LoadL_memoryRSY_",
  /*  173 */  "_AddL__LoadL_memoryRSY__immL8",
  /*  174 */  "_AddP_iRegP_N2P_iRegL",
  /*  175 */  "_LoadP_memoryRSY_",
  /*  176 */  "_AddP__LoadP_memoryRSY__immL8",
  /*  177 */  "_CastP2X_iRegP_N2P_",
  /*  178 */  "_LShiftI_iRegI_immI8",
  /*  179 */  "_URShiftI_iRegI_immI8",
  /*  180 */  "_LShiftL_iRegL_immI8",
  /*  181 */  "_URShiftL_iRegL_immI8",
  /*  182 */  "_LoadF_memoryRX_",
  /*  183 */  "_LoadD_memoryRX_",
  /*  184 */  "_NegF_regF_",
  /*  185 */  "_NegD_regD_",
  /*  186 */  "_Binary_regF__LoadF_memoryRX_",
  /*  187 */  "_Binary_regD__LoadD_memoryRX_",
  /*  188 */  "_Binary__LoadF_memoryRX__regF",
  /*  189 */  "_Binary__LoadD_memoryRX__regD",
  /*  190 */  "_AbsF_regF_",
  /*  191 */  "_AbsD_regD_",
  /*  192 */  "_ConvF2D_regF_",
  /*  193 */  "_SqrtD__ConvF2D_regF__",
  /*  194 */  "_ConvF2D_memoryRX_",
  /*  195 */  "_SqrtD__ConvF2D_memoryRX__",
  /*  196 */  "_LShiftI_iRegI_immI_16",
  /*  197 */  "_LShiftI_iRegI_immI_24",
  /*  198 */  "_RShiftL_iRegL_immI_32_63",
  /*  199 */  "_CmpU_iRegI_uimmI16",
  /*  200 */  "_CmpU_iRegI_iRegI",
  /*  201 */  "_CmpP_iRegP_N2P_immP0",
  /*  202 */  "_CmpN_iRegN_P2N_immN0",
  /*  203 */  "_AbsI_iRegI_",
  /*  204 */  "_CmpI_iRegI_iRegI",
  /*  205 */  "_CmpL_iRegL_iRegL",
  /*  206 */  "_CmpP_iRegP_iRegP",
  /*  207 */  "_CmpP__DecodeN_iRegN___DecodeN_iRegN_",
  /*  208 */  "_CmpI_iRegI_immI8",
  /*  209 */  "_CmpU_iRegI_uimmI8",
  /*  210 */  "_CmpL_iRegL_immL8",
  /*  211 */  "_CmpP_iRegP_immP8",
  /*  212 */  "_CmpP__DecodeN_iRegN__immP0",
  /*  213 */  "_DecodeN_immN8_",
  /*  214 */  "_CmpP__DecodeN_iRegN___DecodeN_immN8_",
  /*  215 */  "_PartialSubtypeCheck_rarg2RegP_rarg3RegP",
  /*  216 */  "_Binary_iRegP_iRegP",
  /*  217 */  "_Binary_iRegP_rarg2RegI",
  /*  218 */  "_Binary_iRegP_rarg5RegI",
  /*  219 */  "_Binary_iRegP_iRegI",
  /*  220 */  "_Binary_immP_immI_1",
  /*  221 */  "_Binary_iRegP_immI16",
  /*  222 */  "_Binary_iRegP_immI",
  // last internally defined operand
  /*  223 */  "regI_to_stkI",
  /*  224 */  "regL_to_stkL",
  /*  225 */  "regP_to_stkP",
  /*  226 */  "regF_to_stkF",
  /*  227 */  "regD_to_stkD",
  /*  228 */  "stfSSD",
  /*  229 */  "stfSSF",
  /*  230 */  "stkI_to_regI",
  /*  231 */  "stkL_to_regL",
  /*  232 */  "stkP_to_regP",
  /*  233 */  "stkF_to_regF",
  /*  234 */  "stkD_to_regD",
  /*  235 */  "loadConI",
  /*  236 */  "loadConI16",
  /*  237 */  "loadConI_0",
  /*  238 */  "loadConUI16",
  /*  239 */  "loadConL_pcrelTOC",
  /*  240 */  "loadConL32",
  /*  241 */  "loadConL16",
  /*  242 */  "loadConL_0",
  /*  243 */  "loadConP_pcrelTOC",
  /*  244 */  "loadConP0",
  /*  245 */  "loadConF_dynTOC",
  /*  246 */  "loadConD_dynTOC",
  /*  247 */  "loadConF0",
  /*  248 */  "loadConD0",
  /*  249 */  "loadConN",
  /*  250 */  "loadConN0",
  /*  251 */  "loadConNKlass",
  /*  252 */  "castP2X_loadP",
  /*  253 */  "loadBase",
  /*  254 */  "compN_iRegN",
  /*  255 */  "compN_iRegN_immN",
  /*  256 */  "compNKlass_iRegN_immN",
  /*  257 */  "compN_iRegN_immN0",
  /*  258 */  "roundDouble_nop",
  /*  259 */  "roundFloat_nop",
  /*  260 */  "castX2P",
  /*  261 */  "castP2X",
  /*  262 */  "tlsLoadP",
  /*  263 */  "checkCastPP",
  /*  264 */  "castPP",
  /*  265 */  "castII",
  /*  266 */  "storePConditional",
  /*  267 */  "storeLConditional",
  /*  268 */  "overflowAddI_reg_reg",
  /*  269 */  "overflowAddI_reg_imm",
  /*  270 */  "overflowAddL_reg_reg",
  /*  271 */  "overflowAddL_reg_imm",
  /*  272 */  "overflowSubI_reg_reg",
  /*  273 */  "overflowSubI_reg_imm",
  /*  274 */  "overflowSubL_reg_reg",
  /*  275 */  "overflowSubL_reg_imm",
  /*  276 */  "overflowNegI_rReg",
  /*  277 */  "overflowNegL_rReg",
  /*  278 */  "MoveF2I_stack_reg",
  /*  279 */  "MoveI2F_stack_reg",
  /*  280 */  "MoveD2L_stack_reg",
  /*  281 */  "MoveL2D_stack_reg",
  /*  282 */  "compI_reg_reg",
  /*  283 */  "compI_reg_imm",
  /*  284 */  "compI_reg_imm16",
  /*  285 */  "compI_reg_imm0",
  /*  286 */  "compI_reg_mem",
  /*  287 */  "compU_reg_reg",
  /*  288 */  "compU_reg_uimm",
  /*  289 */  "compU_reg_mem",
  /*  290 */  "compL_reg_reg",
  /*  291 */  "compL_reg_regI",
  /*  292 */  "compL_reg_imm32",
  /*  293 */  "compL_reg_imm16",
  /*  294 */  "compL_reg_imm0",
  /*  295 */  "compL_conv_reg_imm0",
  /*  296 */  "compL_reg_mem",
  /*  297 */  "compL_reg_memI",
  /*  298 */  "compUL_reg_reg",
  /*  299 */  "compUL_reg_imm32",
  /*  300 */  "compP_reg_reg",
  /*  301 */  "compP_reg_imm0",
  /*  302 */  "compP_decode_reg_imm0",
  /*  303 */  "compP_reg_mem",
  /*  304 */  "cmpF_cc",
  /*  305 */  "cmpD_cc",
  /*  306 */  "cmpF_cc_mem",
  /*  307 */  "cmpD_cc_mem",
  /*  308 */  "cmpF0_cc",
  /*  309 */  "cmpD0_cc",
  /*  310 */  "partialSubtypeCheck_vs_zero",
  /*  311 */  "cmpFastLock",
  /*  312 */  "cmpFastUnlock",
  /*  313 */  "expand_LoadLogical_I2L",
  /*  314 */  "loadB",
  /*  315 */  "loadB2L",
  /*  316 */  "loadUB",
  /*  317 */  "loadUB2L",
  /*  318 */  "loadS",
  /*  319 */  "loadS2L",
  /*  320 */  "loadUS",
  /*  321 */  "loadUS2L",
  /*  322 */  "loadI",
  /*  323 */  "loadI2L",
  /*  324 */  "loadUI2L",
  /*  325 */  "loadRange",
  /*  326 */  "loadL",
  /*  327 */  "loadL_unaligned",
  /*  328 */  "loadP",
  /*  329 */  "loadKlass",
  /*  330 */  "loadTOC",
  /*  331 */  "loadF",
  /*  332 */  "loadD",
  /*  333 */  "loadD_unaligned",
  /*  334 */  "storeB",
  /*  335 */  "storeCM",
  /*  336 */  "storeC",
  /*  337 */  "storeI",
  /*  338 */  "storeL",
  /*  339 */  "storeP",
  /*  340 */  "storeF",
  /*  341 */  "storeD",
  /*  342 */  "prefetchAlloc",
  /*  343 */  "memInitB",
  /*  344 */  "memInitC",
  /*  345 */  "memInitI",
  /*  346 */  "memInitL",
  /*  347 */  "memInitP",
  /*  348 */  "negL_reg_reg",
  /*  349 */  "loadN",
  /*  350 */  "loadNKlass",
  /*  351 */  "decodeLoadN",
  /*  352 */  "decodeLoadNKlass",
  /*  353 */  "decodeLoadConNKlass",
  /*  354 */  "decodeN",
  /*  355 */  "decodeKlass",
  /*  356 */  "decodeN_NN",
  /*  357 */  "decodeN_base",
  /*  358 */  "decodeN_NN_base",
  /*  359 */  "decodeN_Ex",
  /*  360 */  "decodeN_NN_Ex",
  /*  361 */  "encodeP",
  /*  362 */  "encodeKlass",
  /*  363 */  "encodeP_NN",
  /*  364 */  "encodeP_base",
  /*  365 */  "encodeP_NN_base",
  /*  366 */  "encodeP_Ex",
  /*  367 */  "encodeP_NN_Ex",
  /*  368 */  "storeN",
  /*  369 */  "storeNKlass",
  /*  370 */  "membar_acquire",
  /*  371 */  "membar_acquire_0",
  /*  372 */  "membar_acquire_lock",
  /*  373 */  "membar_release",
  /*  374 */  "membar_release_0",
  /*  375 */  "membar_release_lock",
  /*  376 */  "membar_volatile",
  /*  377 */  "unnecessary_membar_volatile",
  /*  378 */  "membar_CPUOrder",
  /*  379 */  "membar_storestore",
  /*  380 */  "cmovN_reg",
  /*  381 */  "cmovN_imm",
  /*  382 */  "cmovI_reg",
  /*  383 */  "cmovI_imm",
  /*  384 */  "cmovP_reg",
  /*  385 */  "cmovP_imm",
  /*  386 */  "cmovF_reg",
  /*  387 */  "cmovD_reg",
  /*  388 */  "cmovL_reg",
  /*  389 */  "cmovL_imm",
  /*  390 */  "loadPLocked",
  /*  391 */  "compareAndSwapI_bool",
  /*  392 */  "compareAndSwapL_bool",
  /*  393 */  "compareAndSwapP_bool",
  /*  394 */  "compareAndSwapN_bool",
  /*  395 */  "addI_mem_imm8_atomic_no_res",
  /*  396 */  "addI_mem_imm16_atomic",
  /*  397 */  "addI_mem_imm32_atomic",
  /*  398 */  "addI_mem_reg_atomic",
  /*  399 */  "addL_mem_imm8_atomic_no_res",
  /*  400 */  "addL_mem_imm16_atomic",
  /*  401 */  "addL_mem_imm32_atomic",
  /*  402 */  "addL_mem_reg_atomic",
  /*  403 */  "addI_mem_reg_atomic_z196",
  /*  404 */  "addL_mem_reg_atomic_z196",
  /*  405 */  "xchgI_reg_mem",
  /*  406 */  "xchgL_reg_mem",
  /*  407 */  "xchgN_reg_mem",
  /*  408 */  "xchgP_reg_mem",
  /*  409 */  "addI_reg_reg_CISC",
  /*  410 */  "addI_reg_reg_RISC",
  /*  411 */  "addI_reg_imm16_CISC",
  /*  412 */  "addI_reg_imm16_RISC",
  /*  413 */  "addI_reg_imm32",
  /*  414 */  "addI_reg_imm12",
  /*  415 */  "addI_reg_imm20",
  /*  416 */  "addI_reg_reg_imm12",
  /*  417 */  "addI_reg_reg_imm20",
  /*  418 */  "addI_Reg_mem",
  /*  419 */  "addI_Reg_mem_0",
  /*  420 */  "addI_mem_imm",
  /*  421 */  "addL_reg_regI",
  /*  422 */  "addL_reg_regI_0",
  /*  423 */  "addL_reg_reg_CISC",
  /*  424 */  "addL_reg_reg_RISC",
  /*  425 */  "addL_reg_imm12",
  /*  426 */  "addL_reg_imm20",
  /*  427 */  "addL_reg_imm32",
  /*  428 */  "addL_reg_imm16_CISC",
  /*  429 */  "addL_reg_imm16_RISC",
  /*  430 */  "addL_Reg_memI",
  /*  431 */  "addL_Reg_memI_0",
  /*  432 */  "addL_Reg_mem",
  /*  433 */  "addL_Reg_mem_0",
  /*  434 */  "addL_reg_reg_imm12",
  /*  435 */  "addL_reg_reg_imm20",
  /*  436 */  "addL_mem_imm",
  /*  437 */  "addP_reg_reg_LA",
  /*  438 */  "addP_reg_reg_CISC",
  /*  439 */  "addP_reg_reg_RISC",
  /*  440 */  "addP_reg_imm12",
  /*  441 */  "addP_reg_imm16_CISC",
  /*  442 */  "addP_reg_imm16_RISC",
  /*  443 */  "addP_reg_imm20",
  /*  444 */  "addP_reg_imm32",
  /*  445 */  "addP_reg_reg_imm12",
  /*  446 */  "addP_regN_reg_imm12",
  /*  447 */  "addP_reg_reg_imm20",
  /*  448 */  "addP_regN_reg_imm20",
  /*  449 */  "addP_mem_imm",
  /*  450 */  "subI_reg_reg_CISC",
  /*  451 */  "subI_reg_reg_RISC",
  /*  452 */  "subI_Reg_mem",
  /*  453 */  "subI_zero_reg",
  /*  454 */  "subL_reg_reg_CISC",
  /*  455 */  "subL_reg_reg_RISC",
  /*  456 */  "subL_reg_regI_CISC",
  /*  457 */  "subL_Reg_memI",
  /*  458 */  "subL_Reg_mem",
  /*  459 */  "mulI_reg_reg",
  /*  460 */  "mulI_reg_imm16",
  /*  461 */  "mulI_reg_imm32",
  /*  462 */  "mulI_Reg_mem",
  /*  463 */  "mulI_Reg_mem_0",
  /*  464 */  "mulL_reg_regI",
  /*  465 */  "mulL_reg_regI_0",
  /*  466 */  "mulL_reg_reg",
  /*  467 */  "mulL_reg_imm16",
  /*  468 */  "mulL_reg_imm32",
  /*  469 */  "mulL_Reg_memI",
  /*  470 */  "mulL_Reg_memI_0",
  /*  471 */  "mulL_Reg_mem",
  /*  472 */  "mulL_Reg_mem_0",
  /*  473 */  "mulHiL_reg_reg",
  /*  474 */  "divModI_reg_divmod",
  /*  475 */  "divI_reg_reg",
  /*  476 */  "divI_reg_imm16",
  /*  477 */  "divModL_reg_divmod",
  /*  478 */  "divL_reg_reg",
  /*  479 */  "divL_reg_imm16",
  /*  480 */  "modI_reg_reg",
  /*  481 */  "modI_reg_imm16",
  /*  482 */  "modL_reg_reg",
  /*  483 */  "modL_reg_imm16",
  /*  484 */  "sllI_reg_reg",
  /*  485 */  "sllI_reg_imm",
  /*  486 */  "sllI_reg_imm_1",
  /*  487 */  "sllL_reg_reg",
  /*  488 */  "sllL_reg_imm",
  /*  489 */  "sllL_reg_imm_1",
  /*  490 */  "sraI_reg_reg",
  /*  491 */  "sraI_reg_imm",
  /*  492 */  "sraL_reg_reg",
  /*  493 */  "sraL_reg_imm",
  /*  494 */  "srlI_reg_reg",
  /*  495 */  "srlI_reg_imm",
  /*  496 */  "srlL_reg_reg",
  /*  497 */  "srlL_reg_imm",
  /*  498 */  "srlP_reg_imm",
  /*  499 */  "rotlI_reg_immI8",
  /*  500 */  "rotlI_reg_immI8_0",
  /*  501 */  "rotlL_reg_immI8",
  /*  502 */  "rotlL_reg_immI8_0",
  /*  503 */  "rotrI_reg_immI8",
  /*  504 */  "rotrI_reg_immI8_0",
  /*  505 */  "rotrL_reg_immI8",
  /*  506 */  "rotrL_reg_immI8_0",
  /*  507 */  "addF_reg_reg",
  /*  508 */  "addF_reg_mem",
  /*  509 */  "addF_reg_mem_0",
  /*  510 */  "addD_reg_reg",
  /*  511 */  "addD_reg_mem",
  /*  512 */  "addD_reg_mem_0",
  /*  513 */  "subF_reg_reg",
  /*  514 */  "subF_reg_mem",
  /*  515 */  "subD_reg_reg",
  /*  516 */  "subD_reg_mem",
  /*  517 */  "mulF_reg_reg",
  /*  518 */  "mulF_reg_mem",
  /*  519 */  "mulF_reg_mem_0",
  /*  520 */  "mulD_reg_reg",
  /*  521 */  "mulD_reg_mem",
  /*  522 */  "mulD_reg_mem_0",
  /*  523 */  "maddF_reg_reg",
  /*  524 */  "maddD_reg_reg",
  /*  525 */  "msubF_reg_reg",
  /*  526 */  "msubD_reg_reg",
  /*  527 */  "maddF_reg_mem",
  /*  528 */  "maddD_reg_mem",
  /*  529 */  "msubF_reg_mem",
  /*  530 */  "msubD_reg_mem",
  /*  531 */  "maddF_mem_reg",
  /*  532 */  "maddD_mem_reg",
  /*  533 */  "msubF_mem_reg",
  /*  534 */  "msubD_mem_reg",
  /*  535 */  "divF_reg_reg",
  /*  536 */  "divF_reg_mem",
  /*  537 */  "divD_reg_reg",
  /*  538 */  "divD_reg_mem",
  /*  539 */  "absF_reg",
  /*  540 */  "absD_reg",
  /*  541 */  "nabsF_reg",
  /*  542 */  "nabsD_reg",
  /*  543 */  "negF_reg",
  /*  544 */  "negD_reg",
  /*  545 */  "sqrtF_reg",
  /*  546 */  "sqrtD_reg",
  /*  547 */  "sqrtF_mem",
  /*  548 */  "sqrtD_mem",
  /*  549 */  "andI_reg_reg",
  /*  550 */  "andI_Reg_mem",
  /*  551 */  "andI_Reg_mem_0",
  /*  552 */  "andI_reg_uimm32",
  /*  553 */  "andI_reg_uimmI_LH1",
  /*  554 */  "andI_reg_uimmI_LL1",
  /*  555 */  "andL_reg_reg",
  /*  556 */  "andL_Reg_mem",
  /*  557 */  "andL_Reg_mem_0",
  /*  558 */  "andL_reg_uimmL_LL1",
  /*  559 */  "andL_reg_uimmL_LH1",
  /*  560 */  "andL_reg_uimmL_HL1",
  /*  561 */  "andL_reg_uimmL_HH1",
  /*  562 */  "orI_reg_reg",
  /*  563 */  "orI_Reg_mem",
  /*  564 */  "orI_Reg_mem_0",
  /*  565 */  "orI_reg_uimm16",
  /*  566 */  "orI_reg_uimm32",
  /*  567 */  "orL_reg_reg",
  /*  568 */  "orL_Reg_mem",
  /*  569 */  "orL_Reg_mem_0",
  /*  570 */  "orL_reg_uimm16",
  /*  571 */  "orL_reg_uimm32",
  /*  572 */  "xorI_reg_reg",
  /*  573 */  "xorI_Reg_mem",
  /*  574 */  "xorI_Reg_mem_0",
  /*  575 */  "xorI_reg_uimm32",
  /*  576 */  "xorL_reg_reg",
  /*  577 */  "xorL_Reg_mem",
  /*  578 */  "xorL_Reg_mem_0",
  /*  579 */  "xorL_reg_uimm32",
  /*  580 */  "convI2B",
  /*  581 */  "convP2B",
  /*  582 */  "cmpLTMask_reg_reg",
  /*  583 */  "cmpLTMask_reg_zero",
  /*  584 */  "convD2F_reg",
  /*  585 */  "convF2I_reg",
  /*  586 */  "convD2I_reg",
  /*  587 */  "convF2L_reg",
  /*  588 */  "convD2L_reg",
  /*  589 */  "convF2D_reg",
  /*  590 */  "convF2D_mem",
  /*  591 */  "convI2D_reg",
  /*  592 */  "convI2F_ireg",
  /*  593 */  "convI2L_reg",
  /*  594 */  "convI2L_reg_zex",
  /*  595 */  "convI2L_mem_zex",
  /*  596 */  "zeroExtend_long",
  /*  597 */  "rShiftI16_lShiftI16_reg",
  /*  598 */  "rShiftI24_lShiftI24_reg",
  /*  599 */  "MoveI2F_reg_stack",
  /*  600 */  "MoveD2L_reg_stack",
  /*  601 */  "MoveL2D_reg_stack",
  /*  602 */  "convL2F_reg",
  /*  603 */  "convL2D_reg",
  /*  604 */  "convL2I_reg",
  /*  605 */  "shrL_reg_imm6_L2I",
  /*  606 */  "rangeCheck_iReg_uimmI16",
  /*  607 */  "rangeCheck_iReg_iReg",
  /*  608 */  "rangeCheck_uimmI16_iReg",
  /*  609 */  "zeroCheckP_iReg_imm0",
  /*  610 */  "zeroCheckN_iReg_imm0",
  /*  611 */  "z196_minI_reg_reg",
  /*  612 */  "z10_minI_reg_reg",
  /*  613 */  "minI_reg_reg",
  /*  614 */  "z196_minI_reg_imm32",
  /*  615 */  "minI_reg_imm32",
  /*  616 */  "z196_minI_reg_imm16",
  /*  617 */  "minI_reg_imm16",
  /*  618 */  "z10_minI_reg_imm8",
  /*  619 */  "z196_maxI_reg_reg",
  /*  620 */  "z10_maxI_reg_reg",
  /*  621 */  "maxI_reg_reg",
  /*  622 */  "z196_maxI_reg_imm32",
  /*  623 */  "maxI_reg_imm32",
  /*  624 */  "z196_maxI_reg_imm16",
  /*  625 */  "maxI_reg_imm16",
  /*  626 */  "z10_maxI_reg_imm8",
  /*  627 */  "absI_reg",
  /*  628 */  "negabsI_reg",
  /*  629 */  "cmpF_reg",
  /*  630 */  "cmpD_reg",
  /*  631 */  "branch",
  /*  632 */  "branchFar",
  /*  633 */  "branchCon",
  /*  634 */  "branchConFar",
  /*  635 */  "branchLoopEnd",
  /*  636 */  "branchLoopEndFar",
  /*  637 */  "testAndBranchLoopEnd_Reg",
  /*  638 */  "cmpb_RegI",
  /*  639 */  "cmpbU_RegI",
  /*  640 */  "cmpb_RegL",
  /*  641 */  "cmpb_RegPP",
  /*  642 */  "cmpb_RegNN",
  /*  643 */  "testAndBranchLoopEnd_Imm",
  /*  644 */  "cmpb_RegI_imm",
  /*  645 */  "cmpbU_RegI_imm",
  /*  646 */  "cmpb_RegL_imm",
  /*  647 */  "cmpb_RegP_immP",
  /*  648 */  "cmpb_RegN_immP0",
  /*  649 */  "cmpb_RegN_imm",
  /*  650 */  "testAndBranchLoopEnd_RegFar",
  /*  651 */  "cmpb_RegI_Far",
  /*  652 */  "cmpbU_RegI_Far",
  /*  653 */  "cmpb_RegL_Far",
  /*  654 */  "cmpb_RegPP_Far",
  /*  655 */  "cmpb_RegNN_Far",
  /*  656 */  "testAndBranchLoopEnd_ImmFar",
  /*  657 */  "cmpb_RegI_imm_Far",
  /*  658 */  "cmpbU_RegI_imm_Far",
  /*  659 */  "cmpb_RegL_imm_Far",
  /*  660 */  "cmpb_RegP_immP_Far",
  /*  661 */  "cmpb_RegN_immP0_Far",
  /*  662 */  "cmpb_RegN_immN_Far",
  /*  663 */  "cmpL3_reg_reg",
  /*  664 */  "safePoint",
  /*  665 */  "safePoint_poll",
  /*  666 */  "CallStaticJavaDirect_dynTOC",
  /*  667 */  "CallDynamicJavaDirect_dynTOC",
  /*  668 */  "CallRuntimeDirect",
  /*  669 */  "CallLeafDirect",
  /*  670 */  "CallLeafNoFPDirect",
  /*  671 */  "TailCalljmpInd",
  /*  672 */  "Ret",
  /*  673 */  "tailjmpInd",
  /*  674 */  "CreateException",
  /*  675 */  "RethrowException",
  /*  676 */  "ShouldNotReachHere",
  /*  677 */  "partialSubtypeCheck",
  /*  678 */  "inlineCallClearArrayConst",
  /*  679 */  "inlineCallClearArrayConstBig",
  /*  680 */  "inlineCallClearArray",
  /*  681 */  "string_equalsL",
  /*  682 */  "string_equalsU",
  /*  683 */  "string_equals_imm",
  /*  684 */  "string_equalsC_imm",
  /*  685 */  "array_equalsB",
  /*  686 */  "array_equalsC",
  /*  687 */  "string_compareL",
  /*  688 */  "string_compareU",
  /*  689 */  "string_compareLU",
  /*  690 */  "string_compareUL",
  /*  691 */  "indexOfChar_U",
  /*  692 */  "indexOf_imm1_U",
  /*  693 */  "indexOf_imm1_L",
  /*  694 */  "indexOf_imm1_UL",
  /*  695 */  "indexOf_imm_U",
  /*  696 */  "indexOf_imm_L",
  /*  697 */  "indexOf_imm_UL",
  /*  698 */  "indexOf_U",
  /*  699 */  "indexOf_L",
  /*  700 */  "indexOf_UL",
  /*  701 */  "string_compress",
  /*  702 */  "string_inflate",
  /*  703 */  "string_inflate_const",
  /*  704 */  "has_negatives",
  /*  705 */  "encode_iso_array",
  /*  706 */  "expand_storeF",
  /*  707 */  "expand_Repl2I_reg",
  /*  708 */  "Repl8B_reg_risbg",
  /*  709 */  "Repl8B_imm",
  /*  710 */  "Repl8B_imm0",
  /*  711 */  "Repl8B_immm1",
  /*  712 */  "Repl4S_reg_risbg",
  /*  713 */  "Repl4S_imm",
  /*  714 */  "Repl4S_imm0",
  /*  715 */  "Repl4S_immm1",
  /*  716 */  "Repl2I_reg_risbg",
  /*  717 */  "Repl2I_imm",
  /*  718 */  "Repl2I_imm0",
  /*  719 */  "Repl2I_immm1",
  /*  720 */  "Repl2F_reg_indirect",
  /*  721 */  "Repl2F_reg_direct",
  /*  722 */  "Repl2F_imm",
  /*  723 */  "Repl2F_imm0",
  /*  724 */  "storeA8B",
  /*  725 */  "loadV8",
  /*  726 */  "bytes_reverse_int",
  /*  727 */  "bytes_reverse_long",
  /*  728 */  "countLeadingZerosI",
  /*  729 */  "countLeadingZerosL",
  /*  730 */  "countTrailingZerosI",
  /*  731 */  "countTrailingZerosL",
  /*  732 */  "popCountI",
  /*  733 */  "popCountL",
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
  /*    8 */  true,
  /*    9 */  true,
  /*   10 */  true,
  /*   11 */  true,
  /*   12 */  true,
  /*   13 */  true,
  /*   14 */  true,
  /*   15 */  true,
  /*   16 */  true,
  /*   17 */  true,
  /*   18 */  true,
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
  /*   66 */  false,
  /*   67 */  false,
  /*   68 */  false,
  /*   69 */  false,
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
  /*  125 */  false,
  /*  126 */  false,
  /*  127 */  true,
  /*  128 */  true,
  /*  129 */  true,
  // last operand
  /*  130 */  false,
  /*  131 */  false,
  /*  132 */  false,
  /*  133 */  false,
  /*  134 */  false,
  /*  135 */  false,
  /*  136 */  false,
  // last operand class
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
  /*  218 */  false,
  /*  219 */  false,
  /*  220 */  false,
  /*  221 */  false,
  /*  222 */  false,
  // last internally defined operand
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
  0, // RegFlags: 8
  0, // VecS: 9
  0, // VecD: 10
  0, // VecX: 11
  0, // VecY: 12
  0, // VecZ: 13
  0, // _last_machine_leaf: 14
  0, // AbsD: 15
  0, // AbsF: 16
  0, // AbsI: 17
  0, // AddD: 18
  0, // AddF: 19
  0, // AddI: 20
  0, // AddL: 21
  0, // AddP: 22
  0, // Allocate: 23
  0, // AllocateArray: 24
  0, // AndI: 25
  0, // AndL: 26
  0, // ArrayCopy: 27
  0, // AryEq: 28
  0, // AtanD: 29
  1, // Binary: 30
  1, // Bool: 31
  0, // BoxLock: 32
  0, // ReverseBytesI: 33
  0, // ReverseBytesL: 34
  0, // ReverseBytesUS: 35
  0, // ReverseBytesS: 36
  0, // CProj: 37
  0, // CallDynamicJava: 38
  0, // CallJava: 39
  0, // CallLeaf: 40
  0, // CallLeafNoFP: 41
  0, // CallRuntime: 42
  0, // CallStaticJava: 43
  0, // CastII: 44
  0, // CastX2P: 45
  0, // CastP2X: 46
  0, // CastPP: 47
  0, // Catch: 48
  0, // CatchProj: 49
  0, // CheckCastPP: 50
  0, // ClearArray: 51
  0, // ConstraintCast: 52
  0, // CMoveD: 53
  0, // CMoveVD: 54
  0, // CMoveF: 55
  0, // CMoveVF: 56
  0, // CMoveI: 57
  0, // CMoveL: 58
  0, // CMoveP: 59
  0, // CMoveN: 60
  1, // CmpN: 61
  1, // CmpD: 62
  0, // CmpD3: 63
  1, // CmpF: 64
  0, // CmpF3: 65
  1, // CmpI: 66
  1, // CmpL: 67
  0, // CmpL3: 68
  0, // CmpLTMask: 69
  1, // CmpP: 70
  1, // CmpU: 71
  1, // CmpUL: 72
  0, // CompareAndSwapB: 73
  0, // CompareAndSwapS: 74
  0, // CompareAndSwapI: 75
  0, // CompareAndSwapL: 76
  0, // CompareAndSwapP: 77
  0, // CompareAndSwapN: 78
  0, // WeakCompareAndSwapB: 79
  0, // WeakCompareAndSwapS: 80
  0, // WeakCompareAndSwapI: 81
  0, // WeakCompareAndSwapL: 82
  0, // WeakCompareAndSwapP: 83
  0, // WeakCompareAndSwapN: 84
  0, // CompareAndExchangeB: 85
  0, // CompareAndExchangeS: 86
  0, // CompareAndExchangeI: 87
  0, // CompareAndExchangeL: 88
  0, // CompareAndExchangeP: 89
  0, // CompareAndExchangeN: 90
  0, // GetAndAddB: 91
  0, // GetAndAddS: 92
  0, // GetAndAddI: 93
  0, // GetAndAddL: 94
  0, // GetAndSetB: 95
  0, // GetAndSetS: 96
  0, // GetAndSetI: 97
  0, // GetAndSetL: 98
  0, // GetAndSetP: 99
  0, // GetAndSetN: 100
  0, // Con: 101
  0, // ConN: 102
  0, // ConNKlass: 103
  0, // ConD: 104
  0, // ConF: 105
  0, // ConI: 106
  0, // ConL: 107
  0, // ConP: 108
  0, // Conv2B: 109
  0, // ConvD2F: 110
  0, // ConvD2I: 111
  0, // ConvD2L: 112
  0, // ConvF2D: 113
  0, // ConvF2I: 114
  0, // ConvF2L: 115
  0, // ConvI2D: 116
  0, // ConvI2F: 117
  0, // ConvI2L: 118
  0, // ConvL2D: 119
  0, // ConvL2F: 120
  0, // ConvL2I: 121
  0, // CountedLoop: 122
  0, // CountedLoopEnd: 123
  0, // OuterStripMinedLoop: 124
  0, // OuterStripMinedLoopEnd: 125
  0, // CountLeadingZerosI: 126
  0, // CountLeadingZerosL: 127
  0, // CountTrailingZerosI: 128
  0, // CountTrailingZerosL: 129
  0, // CreateEx: 130
  0, // DecodeN: 131
  0, // DecodeNKlass: 132
  0, // DivD: 133
  0, // DivF: 134
  0, // DivI: 135
  0, // DivL: 136
  0, // DivMod: 137
  0, // DivModI: 138
  0, // DivModL: 139
  0, // EncodeISOArray: 140
  0, // EncodeP: 141
  0, // EncodePKlass: 142
  1, // FastLock: 143
  1, // FastUnlock: 144
  0, // FmaD: 145
  0, // FmaF: 146
  0, // Goto: 147
  0, // Halt: 148
  0, // HasNegatives: 149
  0, // If: 150
  0, // RangeCheck: 151
  0, // IfFalse: 152
  0, // IfTrue: 153
  0, // Initialize: 154
  0, // JProj: 155
  0, // Jump: 156
  0, // JumpProj: 157
  0, // LShiftI: 158
  0, // LShiftL: 159
  0, // LoadB: 160
  0, // LoadUB: 161
  0, // LoadUS: 162
  0, // LoadD: 163
  0, // LoadD_unaligned: 164
  0, // LoadF: 165
  0, // LoadI: 166
  0, // LoadKlass: 167
  0, // LoadNKlass: 168
  0, // LoadL: 169
  0, // LoadL_unaligned: 170
  0, // LoadPLocked: 171
  0, // LoadP: 172
  0, // LoadN: 173
  0, // LoadRange: 174
  0, // LoadS: 175
  0, // LoadBarrier: 176
  0, // LoadBarrierSlowReg: 177
  0, // LoadBarrierWeakSlowReg: 178
  0, // Lock: 179
  0, // Loop: 180
  0, // LoopLimit: 181
  0, // Mach: 182
  0, // MachProj: 183
  0, // MaxI: 184
  0, // MemBarAcquire: 185
  0, // LoadFence: 186
  0, // SetVectMaskI: 187
  0, // MemBarAcquireLock: 188
  0, // MemBarCPUOrder: 189
  0, // MemBarRelease: 190
  0, // StoreFence: 191
  0, // MemBarReleaseLock: 192
  0, // MemBarVolatile: 193
  0, // MemBarStoreStore: 194
  0, // MergeMem: 195
  0, // MinI: 196
  0, // ModD: 197
  0, // ModF: 198
  0, // ModI: 199
  0, // ModL: 200
  0, // MoveI2F: 201
  0, // MoveF2I: 202
  0, // MoveL2D: 203
  0, // MoveD2L: 204
  0, // MulD: 205
  0, // MulF: 206
  0, // MulHiL: 207
  0, // MulI: 208
  0, // MulL: 209
  0, // Multi: 210
  0, // NegD: 211
  0, // NegF: 212
  0, // NeverBranch: 213
  0, // OnSpinWait: 214
  0, // Opaque1: 215
  0, // Opaque2: 216
  0, // Opaque3: 217
  0, // Opaque4: 218
  0, // ProfileBoolean: 219
  0, // OrI: 220
  0, // OrL: 221
  1, // OverflowAddI: 222
  1, // OverflowSubI: 223
  1, // OverflowMulI: 224
  1, // OverflowAddL: 225
  1, // OverflowSubL: 226
  1, // OverflowMulL: 227
  0, // PCTable: 228
  0, // Parm: 229
  0, // PartialSubtypeCheck: 230
  0, // Phi: 231
  0, // PopCountI: 232
  0, // PopCountL: 233
  0, // PopCountVI: 234
  0, // PrefetchAllocation: 235
  0, // Proj: 236
  0, // RShiftI: 237
  0, // RShiftL: 238
  0, // Region: 239
  0, // Rethrow: 240
  0, // Return: 241
  0, // Root: 242
  0, // RoundDouble: 243
  0, // RoundFloat: 244
  0, // SafePoint: 245
  0, // SafePointScalarObject: 246
  0, // SCMemProj: 247
  0, // SqrtD: 248
  0, // SqrtF: 249
  0, // Start: 250
  0, // StartOSR: 251
  0, // StoreB: 252
  0, // StoreC: 253
  0, // StoreCM: 254
  0, // StorePConditional: 255
  0, // StoreIConditional: 256
  0, // StoreLConditional: 257
  0, // StoreD: 258
  0, // StoreF: 259
  0, // StoreI: 260
  0, // StoreL: 261
  0, // StoreP: 262
  0, // StoreN: 263
  0, // StoreNKlass: 264
  0, // StrComp: 265
  0, // StrCompressedCopy: 266
  0, // StrEquals: 267
  0, // StrIndexOf: 268
  0, // StrIndexOfChar: 269
  0, // StrInflatedCopy: 270
  0, // SubD: 271
  0, // SubF: 272
  0, // SubI: 273
  0, // SubL: 274
  0, // TailCall: 275
  0, // TailJump: 276
  0, // ThreadLocal: 277
  0, // Unlock: 278
  0, // URShiftI: 279
  0, // URShiftL: 280
  0, // XorI: 281
  0, // XorL: 282
  0, // Vector: 283
  0, // AddVB: 284
  0, // AddVS: 285
  0, // AddVI: 286
  0, // AddReductionVI: 287
  0, // AddVL: 288
  0, // AddReductionVL: 289
  0, // AddVF: 290
  0, // AddReductionVF: 291
  0, // AddVD: 292
  0, // AddReductionVD: 293
  0, // SubVB: 294
  0, // SubVS: 295
  0, // SubVI: 296
  0, // SubVL: 297
  0, // SubVF: 298
  0, // SubVD: 299
  0, // MulVS: 300
  0, // MulVI: 301
  0, // MulReductionVI: 302
  0, // MulVL: 303
  0, // MulReductionVL: 304
  0, // MulVF: 305
  0, // MulReductionVF: 306
  0, // MulVD: 307
  0, // MulReductionVD: 308
  0, // FmaVD: 309
  0, // FmaVF: 310
  0, // DivVF: 311
  0, // DivVD: 312
  0, // AbsVF: 313
  0, // AbsVD: 314
  0, // NegVF: 315
  0, // NegVD: 316
  0, // SqrtVD: 317
  0, // SqrtVF: 318
  0, // LShiftCntV: 319
  0, // RShiftCntV: 320
  0, // LShiftVB: 321
  0, // LShiftVS: 322
  0, // LShiftVI: 323
  0, // LShiftVL: 324
  0, // RShiftVB: 325
  0, // RShiftVS: 326
  0, // RShiftVI: 327
  0, // RShiftVL: 328
  0, // URShiftVB: 329
  0, // URShiftVS: 330
  0, // URShiftVI: 331
  0, // URShiftVL: 332
  0, // AndV: 333
  0, // OrV: 334
  0, // XorV: 335
  0, // LoadVector: 336
  0, // StoreVector: 337
  0, // Pack: 338
  0, // PackB: 339
  0, // PackS: 340
  0, // PackI: 341
  0, // PackL: 342
  0, // PackF: 343
  0, // PackD: 344
  0, // Pack2L: 345
  0, // Pack2D: 346
  0, // ReplicateB: 347
  0, // ReplicateS: 348
  0, // ReplicateI: 349
  0, // ReplicateL: 350
  0, // ReplicateF: 351
  0, // ReplicateD: 352
  0, // Extract: 353
  0, // ExtractB: 354
  0, // ExtractUB: 355
  0, // ExtractC: 356
  0, // ExtractS: 357
  0, // ExtractI: 358
  0, // ExtractL: 359
  0, // ExtractF: 360
  0 // no trailing comma // ExtractD: 361
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

const RegMask *lock_ptr_RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_LOCK_PTR_REG_mask();
}

const RegMask *rscratch2RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RSCRATCH2_BITS64_REG_mask();
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

const RegMask *TD_flagsRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_CONDITION_REG_mask();
}

const RegMask *regDOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_DBL_REG_mask();
}

const RegMask *rscratchRegDOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RSCRATCH1_DBL_REG_mask();
}

const RegMask *regFOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_FLT_REG_mask();
}

const RegMask *rscratchRegFOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_RSCRATCH1_FLT_REG_mask();
}

const RegMask *inline_cache_regPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_R9_REGP_mask();
}

const RegMask *compiler_method_oop_regPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_R1_REGP_mask();
}

const RegMask *interpreter_method_oop_regPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_R9_REGP_mask();
}

const RegMask *iRegP2NOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_PTR_REG_mask();
}

const RegMask *iRegN2POper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &Z_INT_REG_mask();
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
  return NULL;
}

const RegMask *indOffset20indexOper::in_RegMask(int index) const {
  assert(0 <= index && index < 2, "index out of range");
  switch (index) {
  case 0: return &Z_MEMORY_PTR_REG_mask();
  case 1: return &Z_LONG_REG_mask();
  }
  ShouldNotReachHere();
  return NULL;
}

const RegMask *indOffset20indexNarrowOper::in_RegMask(int index) const {
  assert(0 <= index && index < 2, "index out of range");
  switch (index) {
  case 0: return &Z_INT_REG_mask();
  case 1: return &Z_LONG_REG_mask();
  }
  ShouldNotReachHere();
  return NULL;
}

const RegMask *indOffset12indexOper::in_RegMask(int index) const {
  assert(0 <= index && index < 2, "index out of range");
  switch (index) {
  case 0: return &Z_MEMORY_PTR_REG_mask();
  case 1: return &Z_LONG_REG_mask();
  }
  ShouldNotReachHere();
  return NULL;
}

const RegMask *indOffset12indexNarrowOper::in_RegMask(int index) const {
  assert(0 <= index && index < 2, "index out of range");
  switch (index) {
  case 0: return &Z_INT_REG_mask();
  case 1: return &Z_LONG_REG_mask();
  }
  ShouldNotReachHere();
  return NULL;
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


// Copy _idx, inputs and operands to new node
void MachNode::fill_new_machnode(MachNode* node) const {
  // New node must use same node index
  node->set_idx( _idx );
  // Copy machine-independent inputs
  for( uint j = 0; j < req(); j++ ) {
    node->add_req(in(j));
  }
  // Copy my operands, except for cisc position
  int nopnds = num_opnds();
  assert( node->num_opnds() == (uint)nopnds, "Must have same number of operands");
  MachOper **to = node->_opnds;
  for( int i = 0; i < nopnds; i++ ) {
    if( i != cisc_operand() ) 
      to[i] = _opnds[i]->clone();
  }
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

int storeCMNode::reloc() const {
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

int loadPLockedNode::reloc() const {
  return 1;
}

int storePConditionalNode::reloc() const {
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

int xorL_Reg_mem_0Node::reloc() const {
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

int RethrowExceptionNode::reloc() const {
  return 1;
}

int partialSubtypeCheck_vs_zeroNode::reloc() const {
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

int storeA8BNode::reloc() const {
  return 2;
}

int loadV8Node::reloc() const {
  return 1;
}


void stkI_to_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((L_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (L_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (L_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 8166 "ad_s390.cpp"
  }
}

void regI_to_stkINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((ST_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (ST_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (ST_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 8195 "ad_s390.cpp"
  }
}

void stkL_to_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 8224 "ad_s390.cpp"
  }
}

void regL_to_stkLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 8253 "ad_s390.cpp"
  }
}

uint regL_to_stkLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void stkP_to_regPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 8287 "ad_s390.cpp"
  }
}

void regP_to_stkPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 8316 "ad_s390.cpp"
  }
}

void stkF_to_regFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LE_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (LE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (LE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 8345 "ad_s390.cpp"
  }
}

uint stkF_to_regFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void regF_to_stkFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STE_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 8379 "ad_s390.cpp"
  }
}

uint regF_to_stkFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void stkD_to_regDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LD_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (LD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (LD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 8413 "ad_s390.cpp"
  }
}

void regD_to_stkDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STD_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 8442 "ad_s390.cpp"
  }
}

uint regD_to_stkDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadBNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LB_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LB_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LB_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8487 "ad_s390.cpp"
  }
}

uint loadBNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadB2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LGB_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LGB_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LGB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LGB_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8532 "ad_s390.cpp"
  }
}

uint loadB2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadUBNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGC_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGC_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGC_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LLGC_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8577 "ad_s390.cpp"
  }
}

uint loadUBNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadUB2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGC_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGC_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGC_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LLGC_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8622 "ad_s390.cpp"
  }
}

uint loadUB2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadSNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LH_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LH_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LHY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LH_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8667 "ad_s390.cpp"
  }
}

uint loadSNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadS2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LGH_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LGH_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LGH_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LGH_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8712 "ad_s390.cpp"
  }
}

uint loadS2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadUSNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGH_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGH_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGH_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LLGH_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8757 "ad_s390.cpp"
  }
}

uint loadUSNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadUS2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGH_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGH_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGH_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LLGH_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8802 "ad_s390.cpp"
  }
}

uint loadUS2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (L_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (L_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (L_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8847 "ad_s390.cpp"
  }
}

uint loadINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadI2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8892 "ad_s390.cpp"
  }
}

uint loadI2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadUI2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8938 "ad_s390.cpp"
  }
}

uint loadUI2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadRangeNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (L_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (L_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (L_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 8983 "ad_s390.cpp"
  }
}

uint loadRangeNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9028 "ad_s390.cpp"
  }
}

uint loadLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadL_unalignedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9073 "ad_s390.cpp"
  }
}

uint loadL_unalignedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9118 "ad_s390.cpp"
  }
}

uint loadPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void castP2X_loadPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9163 "ad_s390.cpp"
  }
}

uint castP2X_loadPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9208 "ad_s390.cpp"
  }
}

uint loadKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadTOCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 4249 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ load_toc(opnd_array(0)->as_Register(ra_,this)/* dst */); 
#line 9227 "ad_s390.cpp"
  }
}

void loadFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LE_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LE_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LEY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LE_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9267 "ad_s390.cpp"
  }
}

uint loadFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LD_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LD_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LDY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LD_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9312 "ad_s390.cpp"
  }
}

uint loadDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadD_unalignedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LD_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LD_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LDY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LD_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9357 "ad_s390.cpp"
  }
}

uint loadD_unalignedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void loadConINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4300 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lgfi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constant()); 
#line 9376 "ad_s390.cpp"
  }
}

uint loadConINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConI16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4309 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constant()); 
#line 9395 "ad_s390.cpp"
  }
}

uint loadConI16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConI_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (XGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,28,32));
  
#line 9418 "ad_s390.cpp"
  }
}

uint loadConI_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConUI16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1839 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LLILL_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LLILL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::uimm16(opnd_array(1)->constant(),16,32));
  
#line 9441 "ad_s390.cpp"
  }
}

void loadConL_pcrelTOCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4339 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    address long_address = __ long_constant(opnd_array(1)->constantL());
    if (long_address == NULL) {
      Compile::current()->env()->record_out_of_memory_failure();
      return;
    }
    __ load_long_pcrelative(opnd_array(0)->as_Register(ra_,this)/* dst */, long_address);
  
#line 9462 "ad_s390.cpp"
  }
}

uint loadConL_pcrelTOCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConL32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4355 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lgfi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constantL()); 
#line 9481 "ad_s390.cpp"
  }
}

uint loadConL32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConL16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4364 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constantL()); 
#line 9500 "ad_s390.cpp"
  }
}

uint loadConL16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConL_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (XGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,28,32));
  
#line 9523 "ad_s390.cpp"
  }
}

void loadConP_pcrelTOCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4385 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
      if (const_toc_addr == NULL) {
        Compile::current()->env()->record_out_of_memory_failure();
        return;
      }
      __ load_long_pcrelative(opnd_array(0)->as_Register(ra_,this)/* dst */, const_toc_addr);
    } else {          // Non-oop pointers, e.g. card mark base, heap top.
      address long_address = __ long_constant((jlong)opnd_array(1)->constant());
      if (long_address == NULL) {
        Compile::current()->env()->record_out_of_memory_failure();
        return;
      }
      __ load_long_pcrelative(opnd_array(0)->as_Register(ra_,this)/* dst */, long_address);
    }
  
#line 9562 "ad_s390.cpp"
  }
}

uint loadConP_pcrelTOCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConP0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (XGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,28,32));
  
#line 9585 "ad_s390.cpp"
  }
}

uint loadConP0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConF_dynTOCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4440 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_float_largeoffset(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, constant_offset(), as_Register(ra_->get_encode(in(mach_constant_base_node_input()))), Z_R1_scratch);
  
#line 9606 "ad_s390.cpp"
  }
}

void loadConF_dynTOCNode::eval_constant(Compile* C) {
  {

#line 4441 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
    _constant = C->constant_table().add(this, opnd_array(1));
#line 9615 "ad_s390.cpp"
  }
}
uint loadConF_dynTOCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConD_dynTOCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4459 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_double_largeoffset(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, constant_offset(), as_Register(ra_->get_encode(in(mach_constant_base_node_input()))), Z_R1_scratch);
  
#line 9635 "ad_s390.cpp"
  }
}

void loadConD_dynTOCNode::eval_constant(Compile* C) {
  {

#line 4460 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
    _constant = C->constant_table().add(this, opnd_array(1));
#line 9644 "ad_s390.cpp"
  }
}
uint loadConD_dynTOCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConF0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LZER_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LZER_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg((Z_F0_enc),28,32));
  
#line 9666 "ad_s390.cpp"
  }
}

uint loadConF0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConD0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LZDR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LZDR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg((Z_F0_enc),28,32));
  
#line 9689 "ad_s390.cpp"
  }
}

uint loadConD0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeBNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STC_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STC_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STCY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (STC_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9735 "ad_s390.cpp"
  }
}

uint storeBNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void storeCMNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4510 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    guarantee(as_Register(opnd_array(1)->index(ra_,this,idx1))!= Z_R0, "content will not be used.");
    if (as_Register(opnd_array(1)->index(ra_,this,idx1))!= noreg) {
      // Can't use clear_mem --> load const zero and store character.
      __ load_const_optimized(Z_R0_scratch, (long)0);
      if (Immediate::is_uimm12(opnd_array(1)->disp(ra_,this,idx1))) {
        __ z_stc(Z_R0_scratch, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));
      } else {
        __ z_stcy(Z_R0_scratch, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()));
      }
    } else {
      __ clear_mem(Address(Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())), 1);
    }
  
#line 9768 "ad_s390.cpp"
  }
}

void storeCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STH_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STH_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STHY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (STH_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9809 "ad_s390.cpp"
  }
}

uint storeCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void storeINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (ST_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (ST_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (ST_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9855 "ad_s390.cpp"
  }
}

uint storeINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void storeLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (STG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9901 "ad_s390.cpp"
  }
}

uint storeLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void storePNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (STG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9947 "ad_s390.cpp"
  }
}

uint storePNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void storeFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STE_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STE_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STEY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (STE_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 9993 "ad_s390.cpp"
  }
}

uint storeFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void storeDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STD_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STD_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STDY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (STD_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10039 "ad_s390.cpp"
  }
}

uint storeDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void prefetchAllocNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 4614 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_pfd(0x02, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); 
#line 10058 "ad_s390.cpp"
  }
}

void memInitBNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4626 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    if (Immediate::is_uimm12((long)opnd_array(1)->disp(ra_,this,idx1))) {
      __ z_mvi(Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()), opnd_array(2)->constant());
    } else {
      __ z_mviy(Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc()), opnd_array(2)->constant());
    }
  
#line 10079 "ad_s390.cpp"
  }
}

void memInitCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1928 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit_inst(cbuf, (MVHHI_ZOPC /*primary()*/) |
                Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)),16,48) |
                Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1),20,48) |
                Assembler::simm16(opnd_array(2)->constant(),32,48));
  
#line 10098 "ad_s390.cpp"
  }
}

uint memInitCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void memInitINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1928 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit_inst(cbuf, (MVHI_ZOPC /*primary()*/) |
                Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)),16,48) |
                Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1),20,48) |
                Assembler::simm16(opnd_array(2)->constant(),32,48));
  
#line 10122 "ad_s390.cpp"
  }
}

uint memInitINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void memInitLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1928 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit_inst(cbuf, (MVGHI_ZOPC /*primary()*/) |
                Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)),16,48) |
                Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1),20,48) |
                Assembler::simm16(opnd_array(2)->constantL(),32,48));
  
#line 10146 "ad_s390.cpp"
  }
}

uint memInitLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void memInitPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1928 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit_inst(cbuf, (MVGHI_ZOPC /*primary()*/) |
                Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)),16,48) |
                Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1),20,48) |
                Assembler::simm16(opnd_array(2)->constant(),32,48));
  
#line 10170 "ad_s390.cpp"
  }
}

uint memInitPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void negL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4693 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lcgr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */); 
#line 10190 "ad_s390.cpp"
  }
}

uint negL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10235 "ad_s390.cpp"
  }
}

uint loadNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadNKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10280 "ad_s390.cpp"
  }
}

uint loadNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void loadConNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4728 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral cOop = __ constant_oop_address((jobject)opnd_array(1)->constant());
    __ relocate(cOop.rspec(), 1);
    __ load_narrow_oop(opnd_array(0)->as_Register(ra_,this)/* dst */, (narrowOop)cOop.value());
  
#line 10303 "ad_s390.cpp"
  }
}

uint loadConNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void loadConN0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (XGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,28,32));
  
#line 10326 "ad_s390.cpp"
  }
}

uint loadConN0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConNKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4752 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral NKlass = __ constant_metadata_address((Metadata*)opnd_array(1)->constant());
    __ relocate(NKlass.rspec(), 1);
    __ load_narrow_klass(opnd_array(0)->as_Register(ra_,this)/* dst */, (Klass*)NKlass.value());
  
#line 10349 "ad_s390.cpp"
  }
}

uint loadConNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void decodeLoadNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10394 "ad_s390.cpp"
  }
}

uint decodeLoadNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void decodeLoadNKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10439 "ad_s390.cpp"
  }
}

uint decodeLoadNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void decodeLoadConNKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4790 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral NKlass = __ constant_metadata_address((Metadata*)opnd_array(1)->constant());
    __ relocate(NKlass.rspec(), 1);
    __ load_const(opnd_array(0)->as_Register(ra_,this)/* dst */, (Klass*)NKlass.value());
  
#line 10462 "ad_s390.cpp"
  }
}

uint decodeLoadConNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void decodeNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4808 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ oop_decoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, true); 
#line 10481 "ad_s390.cpp"
  }
}

void decodeKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4818 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ decode_klass_not_null(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 10495 "ad_s390.cpp"
  }
}

void decodeN_NNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4832 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ oop_decoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, false); 
#line 10509 "ad_s390.cpp"
  }
}

void loadBaseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// baseImm
  {
    MacroAssembler _masm(&cbuf);

#line 4840 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ get_oop_base(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constantL()); 
#line 10523 "ad_s390.cpp"
  }
}

void decodeN_baseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {
    MacroAssembler _masm(&cbuf);

#line 4855 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

      __ oop_decoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, true, opnd_array(2)->as_Register(ra_,this,idx2)/* base */,
                     (jlong)MacroAssembler::get_oop_base_pow2_offset((uint64_t)(intptr_t)Universe::narrow_oop_base()));
    
#line 10541 "ad_s390.cpp"
  }
}

void decodeN_NN_baseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {
    MacroAssembler _masm(&cbuf);

#line 4869 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

      __ oop_decoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, false, opnd_array(2)->as_Register(ra_,this,idx2)/* base */,
                     (jlong)MacroAssembler::get_oop_base_pow2_offset((uint64_t)(intptr_t)Universe::narrow_oop_base()));
    
#line 10559 "ad_s390.cpp"
  }
}

void encodePNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4919 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ oop_encoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, true, Z_R1_scratch, -1, all_outs_are_Stores(this)); 
#line 10573 "ad_s390.cpp"
  }
}

void encodeKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4928 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ encode_klass_not_null(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 10587 "ad_s390.cpp"
  }
}

void encodeP_NNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 4942 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ oop_encoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, false, Z_R1_scratch, -1, all_outs_are_Stores(this)); 
#line 10601 "ad_s390.cpp"
  }
}

void encodeP_baseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  {
    MacroAssembler _masm(&cbuf);

#line 4954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

      jlong offset = -(jlong)MacroAssembler::get_oop_base_pow2_offset
        (((uint64_t)(intptr_t)Universe::narrow_oop_base()) >> Universe::narrow_oop_shift());
      __ oop_encoder(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, true, opnd_array(2)->as_Register(ra_,this,idx2)/* base */, offset);
    
#line 10621 "ad_s390.cpp"
  }
}

void encodeP_NN_baseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pow2_offset
  {
    MacroAssembler _masm(&cbuf);

#line 4970 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ oop_encoder(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, false, opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(3)->constantL()); 
#line 10637 "ad_s390.cpp"
  }
}

void storeNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (ST_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (ST_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (ST_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10678 "ad_s390.cpp"
  }
}

uint storeNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void storeNKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (ST_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (ST_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (ST_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 10724 "ad_s390.cpp"
  }
}

uint storeNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP_SIZE);
}

void compN_iRegNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((CLR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (CLR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,12,16));
  
#line 10749 "ad_s390.cpp"
  }
}

uint compN_iRegNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void compN_iRegN_immNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 5056 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral cOop = __ constant_oop_address((jobject)opnd_array(2)->constant());
    __ relocate(cOop.rspec(), 1);
    __ compare_immediate_narrow_oop(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (narrowOop)cOop.value());
  
#line 10773 "ad_s390.cpp"
  }
}

uint compN_iRegN_immNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compNKlass_iRegN_immNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 5069 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral NKlass = __ constant_metadata_address((Metadata*)opnd_array(2)->constant());
    __ relocate(NKlass.rspec(), 1);
    __ compare_immediate_narrow_klass(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (Klass*)NKlass.value());
  
#line 10797 "ad_s390.cpp"
  }
}

uint compNKlass_iRegN_immNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compN_iRegN_immN0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((LTR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (LTR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,8,16) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,16));
  
#line 10822 "ad_s390.cpp"
  }
}

uint compN_iRegN_immN0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void membar_acquireNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 5098 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_acquire(); 
#line 10841 "ad_s390.cpp"
  }
}

uint membar_acquireNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_acquire_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 5098 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_acquire(); 
#line 10860 "ad_s390.cpp"
  }
}

uint membar_acquire_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_acquire_lockNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint membar_acquire_lockNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_releaseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 5117 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_release(); 
#line 10892 "ad_s390.cpp"
  }
}

uint membar_releaseNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_release_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 5117 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_release(); 
#line 10911 "ad_s390.cpp"
  }
}

uint membar_release_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_release_lockNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint membar_release_lockNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_volatileNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 5135 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_fence(); 
#line 10943 "ad_s390.cpp"
  }
}

uint membar_volatileNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void unnecessary_membar_volatileNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint unnecessary_membar_volatileNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void membar_CPUOrderNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

void membar_storestoreNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint membar_storestoreNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void roundDouble_nopNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

void roundFloat_nopNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

void castX2PNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 5192 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ lgr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 11012 "ad_s390.cpp"
  }
}

void castP2XNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 5201 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ lgr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 11026 "ad_s390.cpp"
  }
}

void stfSSDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STD_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 11055 "ad_s390.cpp"
  }
}

void stfSSFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STE_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 11084 "ad_s390.cpp"
  }
}

void cmovN_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2267 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11119 "ad_s390.cpp"
  }
}

void cmovN_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2288 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11150 "ad_s390.cpp"
  }
}

void cmovI_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2267 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11185 "ad_s390.cpp"
  }
}

void cmovI_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2288 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11216 "ad_s390.cpp"
  }
}

void cmovP_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2267 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11251 "ad_s390.cpp"
  }
}

void cmovP_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2288 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11282 "ad_s390.cpp"
  }
}

void cmovF_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 5288 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    // Don't emit code if operands are identical (same register).
    if (opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */!= opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */) {
      Label done;
      __ z_brc(Assembler::inverse_float_condition((Assembler::branch_condition)opnd_array(1)->ccode()), done);
      __ z_ler(opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */, opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */);
      __ bind(done);
    }
  
#line 11307 "ad_s390.cpp"
  }
}

void cmovD_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 5305 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    // Don't emit code if operands are identical (same register).
    if (opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */!= opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */) {
      Label done;
      __ z_brc(Assembler::inverse_float_condition((Assembler::branch_condition)opnd_array(1)->ccode()), done);
      __ z_ldr(opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */, opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */);
      __ bind(done);
    }
  
#line 11332 "ad_s390.cpp"
  }
}

void cmovL_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2267 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11367 "ad_s390.cpp"
  }
}

void cmovL_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 2288 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11398 "ad_s390.cpp"
  }
}

void tlsLoadPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint tlsLoadPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void checkCastPPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint checkCastPPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castPPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castPPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castIINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castIINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void loadPLockedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 11490 "ad_s390.cpp"
  }
}

uint loadPLockedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void storePConditionalNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  {

#line 2331 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    __ z_csg(Rcomp, Rnew, 0, Raddr);
  
#line 11517 "ad_s390.cpp"
  }
}

void storeLConditionalNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  {

#line 2331 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    __ z_csg(Rcomp, Rnew, 0, Raddr);
  
#line 11539 "ad_s390.cpp"
  }
}

void compareAndSwapI_boolNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  {

#line 2322 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    __ z_cs(Rcomp, Rnew, 0, Raddr);
  
#line 11561 "ad_s390.cpp"
  }
  {

#line 2305 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11582 "ad_s390.cpp"
  }
}

uint compareAndSwapI_boolNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void compareAndSwapL_boolNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  {

#line 2331 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    __ z_csg(Rcomp, Rnew, 0, Raddr);
  
#line 11609 "ad_s390.cpp"
  }
  {

#line 2305 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11630 "ad_s390.cpp"
  }
}

uint compareAndSwapL_boolNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 18, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 18);
}

void compareAndSwapP_boolNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  {

#line 2331 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    __ z_csg(Rcomp, Rnew, 0, Raddr);
  
#line 11657 "ad_s390.cpp"
  }
  {

#line 2305 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11678 "ad_s390.cpp"
  }
}

uint compareAndSwapP_boolNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 18, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 18);
}

void compareAndSwapN_boolNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  {

#line 2322 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Register Rcomp = reg_to_register_object(opnd_array(2)->reg(ra_,this,idx2)/* oldval */);
    Register Rnew  = reg_to_register_object(opnd_array(3)->reg(ra_,this,idx3)/* newval */);
    Register Raddr = reg_to_register_object(opnd_array(1)->reg(ra_,this,idx1)/* mem_ptr */);

    __ z_cs(Rcomp, Rnew, 0, Raddr);
  
#line 11705 "ad_s390.cpp"
  }
  {

#line 2305 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 11726 "ad_s390.cpp"
  }
}

uint compareAndSwapN_boolNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void addI_mem_imm8_atomic_no_resNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1916 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int      disp = opnd_array(1)->disp(ra_,this,idx1);
    Register base = reg_to_register_object(opnd_array(1)->base(ra_,this,idx1));
    int      con  = opnd_array(2)->constant();

    assert(VM_Version::has_MemWithImmALUOps(), "unsupported CPU");
    z_emit_inst(cbuf, (ASI_ZOPC /*primary()*/) |
                Assembler::regz(base,16,48) |
                Assembler::simm20(disp) |
                Assembler::simm8(con,8,48));
  
#line 11755 "ad_s390.cpp"
  }
}

uint addI_mem_imm8_atomic_no_resNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addI_mem_imm16_atomicNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 5499 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 11796 "ad_s390.cpp"
  }
}

void addI_mem_imm32_atomicNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 5534 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 11828 "ad_s390.cpp"
  }
}

void addI_mem_reg_atomicNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 5564 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 11863 "ad_s390.cpp"
  }
}

void addL_mem_imm8_atomic_no_resNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1916 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int      disp = opnd_array(1)->disp(ra_,this,idx1);
    Register base = reg_to_register_object(opnd_array(1)->base(ra_,this,idx1));
    int      con  = opnd_array(2)->constantL();

    assert(VM_Version::has_MemWithImmALUOps(), "unsupported CPU");
    z_emit_inst(cbuf, (AGSI_ZOPC /*primary()*/) |
                Assembler::regz(base,16,48) |
                Assembler::simm20(disp) |
                Assembler::simm8(con,8,48));
  
#line 11887 "ad_s390.cpp"
  }
}

uint addL_mem_imm8_atomic_no_resNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_mem_imm16_atomicNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 5619 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 11927 "ad_s390.cpp"
  }
}

void addL_mem_imm32_atomicNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 5653 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 11958 "ad_s390.cpp"
  }
}

void addL_mem_reg_atomicNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 5682 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 11993 "ad_s390.cpp"
  }
}

void addI_mem_reg_atomic_z196Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 5711 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laa(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); 
#line 12008 "ad_s390.cpp"
  }
}

uint addI_mem_reg_atomic_z196Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_mem_reg_atomic_z196Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 5722 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laag(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Address::make_raw(opnd_array(1)->base(ra_,this,idx1), opnd_array(1)->index(ra_,this,idx1), opnd_array(1)->scale(), opnd_array(1)->disp(ra_,this,idx1), opnd_array(1)->disp_reloc())); 
#line 12028 "ad_s390.cpp"
  }
}

uint addL_mem_reg_atomic_z196Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void xchgI_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 2340 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 12062 "ad_s390.cpp"
  }
}

void xchgL_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 2356 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 12091 "ad_s390.cpp"
  }
}

void xchgN_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 2340 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 12120 "ad_s390.cpp"
  }
}

void xchgP_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {

#line 2356 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
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
  
#line 12149 "ad_s390.cpp"
  }
}

void addI_reg_reg_CISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((AR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (AR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 12169 "ad_s390.cpp"
  }
}

void addI_reg_reg_RISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1824 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((ARK_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (ARK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32));
  
#line 12189 "ad_s390.cpp"
  }
}

uint addI_reg_reg_RISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_reg_imm16_CISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1832 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (AHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::simm16(opnd_array(2)->constant(),16,32));
  
#line 12213 "ad_s390.cpp"
  }
}

void addI_reg_imm16_RISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1846 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AHIK_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (AHIK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm16(opnd_array(2)->constant(),16,48));
  
#line 12233 "ad_s390.cpp"
  }
}

void addI_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1854 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (AFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::simm32(opnd_array(2)->constant(),16,48));
  
#line 12252 "ad_s390.cpp"
  }
}

uint addI_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addI_reg_imm12Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1892 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(cbuf, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,32) |
             Assembler::uimm12(opnd_array(2)->constant(),20,32));
  
#line 12277 "ad_s390.cpp"
  }
}

uint addI_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_reg_imm20Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1908 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 12301 "ad_s390.cpp"
  }
}

uint addI_reg_imm20Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addI_reg_reg_imm12Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 1883 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(cbuf, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32) |
             Assembler::uimm12(opnd_array(3)->constant(),20,32));
  
#line 12328 "ad_s390.cpp"
  }
}

uint addI_reg_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_reg_reg_imm20Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 1900 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(opnd_array(3)->constant()));
  
#line 12354 "ad_s390.cpp"
  }
}

uint addI_reg_reg_imm20Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addI_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (A_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (A_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (AY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (A_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 12400 "ad_s390.cpp"
  }
}

void addI_Reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (A_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (A_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (AY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (A_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 12441 "ad_s390.cpp"
  }
}

void addI_mem_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1916 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int      disp = opnd_array(1)->disp(ra_,this,idx1);
    Register base = reg_to_register_object(opnd_array(1)->base(ra_,this,idx1));
    int      con  = opnd_array(2)->constant();

    assert(VM_Version::has_MemWithImmALUOps(), "unsupported CPU");
    z_emit_inst(cbuf, (ASI_ZOPC /*primary()*/) |
                Assembler::regz(base,16,48) |
                Assembler::simm20(disp) |
                Assembler::simm8(con,8,48));
  
#line 12465 "ad_s390.cpp"
  }
}

uint addI_mem_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_reg_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (AGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 12489 "ad_s390.cpp"
  }
}

uint addL_reg_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_regI_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (AGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 12513 "ad_s390.cpp"
  }
}

uint addL_reg_regI_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_reg_CISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (AGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 12537 "ad_s390.cpp"
  }
}

void addL_reg_reg_RISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1824 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGRK_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (AGRK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32));
  
#line 12557 "ad_s390.cpp"
  }
}

uint addL_reg_reg_RISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_imm12Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1892 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(cbuf, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,32) |
             Assembler::uimm12(opnd_array(2)->constantL(),20,32));
  
#line 12582 "ad_s390.cpp"
  }
}

uint addL_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_imm20Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1908 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,48) |
             Assembler::simm20(opnd_array(2)->constantL()));
  
#line 12606 "ad_s390.cpp"
  }
}

uint addL_reg_imm20Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1854 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (AGFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::simm32(opnd_array(2)->constantL(),16,48));
  
#line 12630 "ad_s390.cpp"
  }
}

uint addL_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_reg_imm16_CISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1832 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (AGHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::simm16(opnd_array(2)->constantL(),16,32));
  
#line 12654 "ad_s390.cpp"
  }
}

void addL_reg_imm16_RISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1846 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGHIK_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (AGHIK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm16(opnd_array(2)->constantL(),16,48));
  
#line 12674 "ad_s390.cpp"
  }
}

uint addL_reg_imm16_RISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_Reg_memINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (AGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (AGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (AGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (AGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 12720 "ad_s390.cpp"
  }
}

uint addL_Reg_memINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void addL_Reg_memI_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (AGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (AGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (AGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (AGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 12766 "ad_s390.cpp"
  }
}

uint addL_Reg_memI_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void addL_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (AG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (AG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (AG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (AG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 12812 "ad_s390.cpp"
  }
}

uint addL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void addL_Reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (AG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (AG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (AG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (AG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 12858 "ad_s390.cpp"
  }
}

uint addL_Reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void addL_reg_reg_imm12Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 1883 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(cbuf, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32) |
             Assembler::uimm12(opnd_array(3)->constantL(),20,32));
  
#line 12885 "ad_s390.cpp"
  }
}

uint addL_reg_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_reg_imm20Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 1900 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(opnd_array(3)->constantL()));
  
#line 12911 "ad_s390.cpp"
  }
}

uint addL_reg_reg_imm20Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addL_mem_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1916 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int      disp = opnd_array(1)->disp(ra_,this,idx1);
    Register base = reg_to_register_object(opnd_array(1)->base(ra_,this,idx1));
    int      con  = opnd_array(2)->constantL();

    assert(VM_Version::has_MemWithImmALUOps(), "unsupported CPU");
    z_emit_inst(cbuf, (AGSI_ZOPC /*primary()*/) |
                Assembler::regz(base,16,48) |
                Assembler::simm20(disp) |
                Assembler::simm8(con,8,48));
  
#line 12940 "ad_s390.cpp"
  }
}

uint addL_mem_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addP_reg_reg_LANode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1883 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(cbuf, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32) |
             Assembler::uimm12((0x0),20,32));
  
#line 12966 "ad_s390.cpp"
  }
}

uint addP_reg_reg_LANode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_reg_reg_CISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((ALGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (ALGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 12990 "ad_s390.cpp"
  }
}

void addP_reg_reg_RISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1824 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((ALGRK_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (ALGRK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32));
  
#line 13010 "ad_s390.cpp"
  }
}

void addP_reg_imm12Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1892 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(cbuf, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,32) |
             Assembler::uimm12(opnd_array(2)->constantL(),20,32));
  
#line 13030 "ad_s390.cpp"
  }
}

uint addP_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_reg_imm16_CISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1832 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (AGHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::simm16(opnd_array(2)->constantL(),16,32));
  
#line 13054 "ad_s390.cpp"
  }
}

void addP_reg_imm16_RISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1846 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((ALGHSIK_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (ALGHSIK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm16(opnd_array(2)->constantL(),16,48));
  
#line 13074 "ad_s390.cpp"
  }
}

void addP_reg_imm20Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1908 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,16,48) |
             Assembler::simm20(opnd_array(2)->constantL()));
  
#line 13093 "ad_s390.cpp"
  }
}

uint addP_reg_imm20Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addP_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1854 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AGFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (AGFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::simm32(opnd_array(2)->constantL(),16,48));
  
#line 13117 "ad_s390.cpp"
  }
}

void addP_reg_reg_imm12Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 1883 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(cbuf, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32) |
             Assembler::uimm12(opnd_array(3)->constantL(),20,32));
  
#line 13139 "ad_s390.cpp"
  }
}

uint addP_reg_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_regN_reg_imm12Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 1883 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LA_ZOPC /*primary()*/)>>30) & 0x03) == 1, "Instruction format error");
    z_emit32(cbuf, (LA_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32) |
             Assembler::uimm12(opnd_array(3)->constantL(),20,32));
  
#line 13166 "ad_s390.cpp"
  }
}

uint addP_regN_reg_imm12Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_reg_reg_imm20Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 1900 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(opnd_array(3)->constantL()));
  
#line 13192 "ad_s390.cpp"
  }
}

void addP_regN_reg_imm20Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  {

#line 1900 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (LAY_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(opnd_array(3)->constantL()));
  
#line 13213 "ad_s390.cpp"
  }
}

void addP_mem_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1916 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int      disp = opnd_array(1)->disp(ra_,this,idx1);
    Register base = reg_to_register_object(opnd_array(1)->base(ra_,this,idx1));
    int      con  = opnd_array(2)->constantL();

    assert(VM_Version::has_MemWithImmALUOps(), "unsupported CPU");
    z_emit_inst(cbuf, (AGSI_ZOPC /*primary()*/) |
                Assembler::regz(base,16,48) |
                Assembler::simm20(disp) |
                Assembler::simm8(con,8,48));
  
#line 13237 "ad_s390.cpp"
  }
}

uint addP_mem_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void subI_reg_reg_CISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((SR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (SR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 13262 "ad_s390.cpp"
  }
}

void subI_reg_reg_RISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1824 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SRK_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (SRK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32));
  
#line 13282 "ad_s390.cpp"
  }
}

uint subI_reg_reg_RISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subI_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (S_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (S_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (SY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (S_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 13328 "ad_s390.cpp"
  }
}

void subI_zero_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6277 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lcr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */); 
#line 13343 "ad_s390.cpp"
  }
}

uint subI_zero_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void subL_reg_reg_CISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (SGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 13367 "ad_s390.cpp"
  }
}

void subL_reg_reg_RISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1824 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SGRK_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (SGRK_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,32));
  
#line 13387 "ad_s390.cpp"
  }
}

uint subL_reg_reg_RISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subL_reg_regI_CISCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (SGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 13411 "ad_s390.cpp"
  }
}

uint subL_reg_regI_CISCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subL_Reg_memINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (SGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (SGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (SGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (SGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 13457 "ad_s390.cpp"
  }
}

uint subL_Reg_memINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void subL_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (SG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (SG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (SG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (SG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 13503 "ad_s390.cpp"
  }
}

uint subL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void mulI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (MSR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 13527 "ad_s390.cpp"
  }
}

uint mulI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulI_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1832 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (MHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::simm16(opnd_array(2)->constant(),16,32));
  
#line 13551 "ad_s390.cpp"
  }
}

void mulI_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1854 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (MSFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::simm32(opnd_array(2)->constant(),16,48));
  
#line 13570 "ad_s390.cpp"
  }
}

uint mulI_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulI_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MS_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (MS_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (MSY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (MS_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 13616 "ad_s390.cpp"
  }
}

void mulI_Reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MS_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (MS_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (MSY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (MS_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 13657 "ad_s390.cpp"
  }
}

void mulL_reg_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (MSGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 13676 "ad_s390.cpp"
  }
}

void mulL_reg_regI_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (MSGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 13695 "ad_s390.cpp"
  }
}

void mulL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (MSGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 13714 "ad_s390.cpp"
  }
}

uint mulL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulL_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1832 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MGHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (MGHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::simm16(opnd_array(2)->constantL(),16,32));
  
#line 13738 "ad_s390.cpp"
  }
}

void mulL_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1854 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MSGFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (MSGFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::simm32(opnd_array(2)->constantL(),16,48));
  
#line 13757 "ad_s390.cpp"
  }
}

uint mulL_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulL_Reg_memINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MSGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (MSGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (MSGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (MSGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 13803 "ad_s390.cpp"
  }
}

uint mulL_Reg_memINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void mulL_Reg_memI_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MSGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (MSGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (MSGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (MSGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 13849 "ad_s390.cpp"
  }
}

uint mulL_Reg_memI_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void mulL_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MSG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (MSG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (MSG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (MSG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 13895 "ad_s390.cpp"
  }
}

uint mulL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void mulL_Reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (MSG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (MSG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (MSG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (MSG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 13941 "ad_s390.cpp"
  }
}

uint mulL_Reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void mulHiL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// Rsrc1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// Rsrc2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// Rdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// Rtmp1
  {
    MacroAssembler _masm(&cbuf);

#line 6456 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register dst  = opnd_array(3)->as_Register(ra_,this,idx3)/* Rdst */;
    Register src1 = opnd_array(1)->as_Register(ra_,this,idx1)/* Rsrc1 */;
    Register src2 = opnd_array(2)->as_Register(ra_,this,idx2)/* Rsrc2 */;
    Register tmp1 = opnd_array(4)->as_Register(ra_,this,idx4)/* Rtmp1 */;
    Register tmp2 = opnd_array(3)->as_Register(ra_,this,idx3)/* Rdst */;
    // z/Architecture has only unsigned multiply (64 * 64 -> 128).
    // implementing mulhs(a,b) = mulhu(a,b) – (a & (b>>63)) – (b & (a>>63))
    __ z_srag(tmp2, src1, 63);  // a>>63
    __ z_srag(tmp1, src2, 63);  // b>>63
    __ z_ngr(tmp2, src2);       // b & (a>>63)
    __ z_ngr(tmp1, src1);       // a & (b>>63)
    __ z_agr(tmp1, tmp2);       // ((a & (b>>63)) + (b & (a>>63)))
    __ z_mlgr(dst, src2);       // tricky: 128-bit product is written to even/odd pair (dst,src1),
                                //         multiplicand is taken from oddReg (src1), multiplier in src2.
    __ z_sgr(dst, tmp1);
  
#line 13979 "ad_s390.cpp"
  }
}

void divModI_reg_divmodNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst2
  {
    MacroAssembler _masm(&cbuf);

#line 6485 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 14015 "ad_s390.cpp"
  }
}

uint divModI_reg_divmodNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= VM_Version::has_CompareBranch() ? 24 : 26, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : VM_Version::has_CompareBranch() ? 24 : 26);
}

void divI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6518 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 14055 "ad_s390.cpp"
  }
}

uint divI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= VM_Version::has_CompareBranch() ? 20 : 22, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : VM_Version::has_CompareBranch() ? 20 : 22);
}

void divI_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6549 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    // No sign extension of Rdividend needed here.
    if (opnd_array(2)->constant()!= -1) {
      __ z_lghi(Z_R0_scratch, opnd_array(2)->constant());
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
      __ z_dsgfr(opnd_array(0)->as_Register(ra_,this)/* dst */->predecessor()/* Dst is odd part of a register pair. */, Z_R0_scratch);
    } else {
      __ z_lcr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
  
#line 14084 "ad_s390.cpp"
  }
}

void divModL_reg_divmodNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst2
  {
    MacroAssembler _masm(&cbuf);

#line 6569 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 14118 "ad_s390.cpp"
  }
}

uint divModL_reg_divmodNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= VM_Version::has_CompareBranch() ? 22 : 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : VM_Version::has_CompareBranch() ? 22 : 24);
}

void divL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6599 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 14153 "ad_s390.cpp"
  }
}

uint divL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= VM_Version::has_CompareBranch() ? 18 : 20, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : VM_Version::has_CompareBranch() ? 18 : 20);
}

void divL_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6625 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    if (opnd_array(2)->constantL()!= -1) {
      __ z_lghi(Z_R0_scratch, opnd_array(2)->constantL());
      __ lgr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
      __ z_dsgr(opnd_array(0)->as_Register(ra_,this)/* dst */->predecessor()/* Dst is odd part of a register pair. */, Z_R0_scratch);
    } else {
      __ z_lcgr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
  
#line 14181 "ad_s390.cpp"
  }
}

void modI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6647 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 14228 "ad_s390.cpp"
  }
}

void modI_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6690 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 14255 "ad_s390.cpp"
  }
}

void modL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6713 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 14299 "ad_s390.cpp"
  }
}

void modL_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6753 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int divisor = opnd_array(2)->constantL();
    if (divisor != -1) {
      __ z_lghi(Z_R0_scratch, divisor);
      __ z_lgr(opnd_array(0)->as_Register(ra_,this)/* dst */->successor(), opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
      __ z_dsgr(opnd_array(0)->as_Register(ra_,this)/* dst */, Z_R0_scratch);  // Instruction kills tmp.
    } else {
      __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, true, false);
    }
  
#line 14323 "ad_s390.cpp"
  }
}

void sllI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {
    MacroAssembler _masm(&cbuf);

#line 6777 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lgr(Z_R1_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* nbits */);
    __ z_nill(Z_R1_scratch, BitsPerJavaInteger-1);
    __ z_sllg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0, Z_R1_scratch);
  
#line 14342 "ad_s390.cpp"
  }
}

uint sllI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 14, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 14);
}

void sllI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {
    MacroAssembler _masm(&cbuf);

#line 6791 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int Nbit = opnd_array(2)->constant();
    assert((Nbit & (BitsPerJavaInteger - 1)) == Nbit, "Check shift mask in ideal graph");
    __ z_sllg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Nbit & (BitsPerJavaInteger - 1), Z_R0);
  
#line 14366 "ad_s390.cpp"
  }
}

uint sllI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void sllI_reg_imm_1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {
    MacroAssembler _masm(&cbuf);

#line 6806 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_la(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 14386 "ad_s390.cpp"
  }
}

uint sllI_reg_imm_1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sllL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {

#line 1875 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (SLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* nbits */,16,48) |
             Assembler::simm20(0));
  
#line 14411 "ad_s390.cpp"
  }
}

uint sllL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void sllL_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (SLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 14435 "ad_s390.cpp"
  }
}

uint sllL_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void sllL_reg_imm_1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  {
    MacroAssembler _masm(&cbuf);

#line 6837 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_la(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */); 
#line 14455 "ad_s390.cpp"
  }
}

uint sllL_reg_imm_1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sraI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6850 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lgr(Z_R1_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* src */);
    __ z_nill(Z_R1_scratch, BitsPerJavaInteger-1);
    __ z_sra(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 0, Z_R1_scratch);
  
#line 14479 "ad_s390.cpp"
  }
}

uint sraI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void sraI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6865 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int Nbit = opnd_array(2)->constant();
    assert((Nbit & (BitsPerJavaInteger - 1)) == Nbit, "Check shift mask in ideal graph");
    __ z_sra(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, Nbit & (BitsPerJavaInteger - 1), Z_R0);
  
#line 14503 "ad_s390.cpp"
  }
}

uint sraI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sraL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1875 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (SRAG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(0));
  
#line 14528 "ad_s390.cpp"
  }
}

uint sraL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void sraL_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (SRAG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 14552 "ad_s390.cpp"
  }
}

uint sraL_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void srlI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6904 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lgr(Z_R1_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* src */);
    __ z_nill(Z_R1_scratch, BitsPerJavaInteger-1);
    __ z_srl(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 0, Z_R1_scratch);
  
#line 14576 "ad_s390.cpp"
  }
}

uint srlI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void srlI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6918 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int Nbit = opnd_array(2)->constant();
    assert((Nbit & (BitsPerJavaInteger - 1)) == Nbit, "Check shift mask in ideal graph");
    __ z_srl(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, Nbit & (BitsPerJavaInteger - 1), Z_R0);
  
#line 14600 "ad_s390.cpp"
  }
}

uint srlI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void srlL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1875 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (SRLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src2 */,16,48) |
             Assembler::simm20(0));
  
#line 14625 "ad_s390.cpp"
  }
}

uint srlL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void srlL_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (SRLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 14649 "ad_s390.cpp"
  }
}

uint srlL_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void srlP_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (SRLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 14673 "ad_s390.cpp"
  }
}

uint srlP_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rotlI_reg_immI8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (RLL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 14698 "ad_s390.cpp"
  }
}

uint rotlI_reg_immI8Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rotlI_reg_immI8_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (RLL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(3)->constant()));
  
#line 14723 "ad_s390.cpp"
  }
}

uint rotlI_reg_immI8_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rotlL_reg_immI8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (RLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 14748 "ad_s390.cpp"
  }
}

uint rotlL_reg_immI8Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rotlL_reg_immI8_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (RLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(3)->constant()));
  
#line 14773 "ad_s390.cpp"
  }
}

uint rotlL_reg_immI8_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rotrI_reg_immI8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (RLL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 14798 "ad_s390.cpp"
  }
}

void rotrI_reg_immI8_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (RLL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(3)->constant()));
  
#line 14818 "ad_s390.cpp"
  }
}

void rotrL_reg_immI8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (RLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 14838 "ad_s390.cpp"
  }
}

void rotrL_reg_immI8_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (RLLG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(3)->constant()));
  
#line 14858 "ad_s390.cpp"
  }
}

void overflowAddI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 7010 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_ar(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 14876 "ad_s390.cpp"
  }
}

void overflowAddI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 7022 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_const_optimized(Z_R0_scratch, opnd_array(2)->constant());
    __ z_ar(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
  
#line 14894 "ad_s390.cpp"
  }
}

void overflowAddL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 7034 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lgr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_agr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 14912 "ad_s390.cpp"
  }
}

void overflowAddL_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 7046 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_const_optimized(Z_R0_scratch, opnd_array(2)->constantL());
    __ z_agr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
  
#line 14930 "ad_s390.cpp"
  }
}

void overflowSubI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 7058 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_sr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 14948 "ad_s390.cpp"
  }
}

void overflowSubI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 7070 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_const_optimized(Z_R1_scratch, opnd_array(2)->constant());
    __ z_lr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_sr(Z_R0_scratch, Z_R1_scratch);
  
#line 14967 "ad_s390.cpp"
  }
}

void overflowSubL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 7083 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lgr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_sgr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 14985 "ad_s390.cpp"
  }
}

void overflowSubL_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 7095 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ load_const_optimized(Z_R1_scratch, opnd_array(2)->constantL());
    __ z_lgr(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
    __ z_sgr(Z_R0_scratch, Z_R1_scratch);
  
#line 15004 "ad_s390.cpp"
  }
}

void overflowNegI_rRegNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 7107 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ clear_reg(Z_R0_scratch, false, false);
    __ z_sr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 15022 "ad_s390.cpp"
  }
}

void overflowNegL_rRegNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 7118 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ clear_reg(Z_R0_scratch, true, false);
    __ z_sgr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 15040 "ad_s390.cpp"
  }
}

void addF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((AEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (AEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 15059 "ad_s390.cpp"
  }
}

uint addF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addF_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((AEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (AEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(cbuf, (AEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 15094 "ad_s390.cpp"
  }
}

uint addF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addF_reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((AEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (AEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (AEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 15129 "ad_s390.cpp"
  }
}

uint addF_reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((ADBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (ADBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 15153 "ad_s390.cpp"
  }
}

uint addD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addD_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((ADB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (ADB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(cbuf, (ADB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 15188 "ad_s390.cpp"
  }
}

uint addD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void addD_reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((ADB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (ADB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (ADB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 15223 "ad_s390.cpp"
  }
}

uint addD_reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void subF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (SEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 15247 "ad_s390.cpp"
  }
}

uint subF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subF_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((SEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (SEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(cbuf, (SEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 15282 "ad_s390.cpp"
  }
}

uint subF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void subD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (SDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 15306 "ad_s390.cpp"
  }
}

uint subD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subD_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((SDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (SDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(cbuf, (SDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 15341 "ad_s390.cpp"
  }
}

uint subD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MEEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (MEEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 15365 "ad_s390.cpp"
  }
}

uint mulF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulF_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((MEEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (MEEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(cbuf, (MEEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 15400 "ad_s390.cpp"
  }
}

uint mulF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulF_reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((MEEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (MEEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (MEEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 15435 "ad_s390.cpp"
  }
}

uint mulF_reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((MDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (MDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 15459 "ad_s390.cpp"
  }
}

uint mulD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulD_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((MDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (MDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(cbuf, (MDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 15494 "ad_s390.cpp"
  }
}

uint mulD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void mulD_reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((MDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (MDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (MDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 15529 "ad_s390.cpp"
  }
}

uint mulD_reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void maddF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7283 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_maebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */);
  
#line 15552 "ad_s390.cpp"
  }
}

uint maddF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void maddD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7296 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_madbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */);
  
#line 15575 "ad_s390.cpp"
  }
}

uint maddD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void msubF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7309 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_msebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */);
  
#line 15598 "ad_s390.cpp"
  }
}

uint msubF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void msubD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7322 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_msdbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */);
  
#line 15621 "ad_s390.cpp"
  }
}

uint msubD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void maddF_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7335 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_maeb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */,
              Address(reg_to_register_object(opnd_array(3)->base(ra_,this,idx3)), as_Register(opnd_array(3)->index(ra_,this,idx3)), opnd_array(3)->disp(ra_,this,idx3)));
  
#line 15645 "ad_s390.cpp"
  }
}

uint maddF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void maddD_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7349 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_madb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */,
              Address(reg_to_register_object(opnd_array(3)->base(ra_,this,idx3)), as_Register(opnd_array(3)->index(ra_,this,idx3)), opnd_array(3)->disp(ra_,this,idx3)));
  
#line 15669 "ad_s390.cpp"
  }
}

uint maddD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void msubF_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7363 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_mseb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */,
              Address(reg_to_register_object(opnd_array(3)->base(ra_,this,idx3)), as_Register(opnd_array(3)->index(ra_,this,idx3)), opnd_array(3)->disp(ra_,this,idx3)));
  
#line 15693 "ad_s390.cpp"
  }
}

uint msubF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void msubD_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7377 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_msdb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */,
              Address(reg_to_register_object(opnd_array(3)->base(ra_,this,idx3)), as_Register(opnd_array(3)->index(ra_,this,idx3)), opnd_array(3)->disp(ra_,this,idx3)));
  
#line 15717 "ad_s390.cpp"
  }
}

uint msubD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void maddF_mem_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7391 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_maeb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */,
              Address(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), as_Register(opnd_array(2)->index(ra_,this,idx2)), opnd_array(2)->disp(ra_,this,idx2)));
  
#line 15741 "ad_s390.cpp"
  }
}

uint maddF_mem_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void maddD_mem_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7405 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_madb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */,
              Address(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), as_Register(opnd_array(2)->index(ra_,this,idx2)), opnd_array(2)->disp(ra_,this,idx2)));
  
#line 15765 "ad_s390.cpp"
  }
}

uint maddD_mem_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void msubF_mem_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7419 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_mseb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */,
              Address(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), as_Register(opnd_array(2)->index(ra_,this,idx2)), opnd_array(2)->disp(ra_,this,idx2)));
  
#line 15789 "ad_s390.cpp"
  }
}

uint msubF_mem_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void msubD_mem_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 7433 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_msdb(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* dst */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */,
              Address(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), as_Register(opnd_array(2)->index(ra_,this,idx2)), opnd_array(2)->disp(ra_,this,idx2)));
  
#line 15813 "ad_s390.cpp"
  }
}

uint msubD_mem_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void divF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((DEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (DEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 15837 "ad_s390.cpp"
  }
}

uint divF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void divF_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((DEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (DEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(cbuf, (DEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 15872 "ad_s390.cpp"
  }
}

uint divF_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void divD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((DDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (DDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 15896 "ad_s390.cpp"
  }
}

uint divD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void divD_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((DDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (DDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(cbuf, (DDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 15931 "ad_s390.cpp"
  }
}

uint divD_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void absF_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LPEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LPEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 15954 "ad_s390.cpp"
  }
}

uint absF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void absD_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LPDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LPDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 15977 "ad_s390.cpp"
  }
}

uint absD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void nabsF_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LNEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LNEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 16000 "ad_s390.cpp"
  }
}

uint nabsF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void nabsD_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LNDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LNDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 16023 "ad_s390.cpp"
  }
}

uint nabsD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void negF_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7543 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lcebr(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */); 
#line 16042 "ad_s390.cpp"
  }
}

uint negF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void negD_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7552 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lcdbr(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */); 
#line 16061 "ad_s390.cpp"
  }
}

uint negD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sqrtF_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SQEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (SQEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 16084 "ad_s390.cpp"
  }
}

uint sqrtF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sqrtD_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((SQDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (SQDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 16107 "ad_s390.cpp"
  }
}

uint sqrtD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sqrtF_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((SQEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (SQEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (SQEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 16141 "ad_s390.cpp"
  }
}

uint sqrtF_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void sqrtD_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((SQDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (SQDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (SQDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 16175 "ad_s390.cpp"
  }
}

void andI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((NR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((NR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (NR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 16195 "ad_s390.cpp"
  }
}

uint andI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void andI_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (N_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (N_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (NY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (N_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 16241 "ad_s390.cpp"
  }
}

void andI_Reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (N_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (N_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (NY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (N_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 16282 "ad_s390.cpp"
  }
}

void andI_reg_uimm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1861 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((NILF_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (NILF_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::uimm32(opnd_array(2)->constant(),16,48));
  
#line 16301 "ad_s390.cpp"
  }
}

uint andI_reg_uimm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void andI_reg_uimmI_LH1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7647 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nilh(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, (opnd_array(2)->constant()>> 16) & 0xFFFF); 
#line 16321 "ad_s390.cpp"
  }
}

uint andI_reg_uimmI_LH1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andI_reg_uimmI_LL1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7657 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nill(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(2)->constant()& 0xFFFF); 
#line 16341 "ad_s390.cpp"
  }
}

uint andI_reg_uimmI_LL1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((NGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (NGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 16365 "ad_s390.cpp"
  }
}

uint andL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (NG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (NG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (NG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (NG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 16411 "ad_s390.cpp"
  }
}

uint andL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void andL_Reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (NG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (NG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (NG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (NG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 16457 "ad_s390.cpp"
  }
}

uint andL_Reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void andL_reg_uimmL_LL1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7690 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nill(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(2)->constantL()& 0xFFFF); 
#line 16477 "ad_s390.cpp"
  }
}

uint andL_reg_uimmL_LL1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_uimmL_LH1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7700 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nilh(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, (opnd_array(2)->constantL()>> 16) & 0xFFFF); 
#line 16497 "ad_s390.cpp"
  }
}

uint andL_reg_uimmL_LH1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_uimmL_HL1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7710 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nihl(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, (opnd_array(2)->constantL()>> 32) & 0xFFFF); 
#line 16517 "ad_s390.cpp"
  }
}

uint andL_reg_uimmL_HL1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_uimmL_HH1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7720 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_nihh(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, (opnd_array(2)->constantL()>> 48) & 0xFFFF); 
#line 16537 "ad_s390.cpp"
  }
}

uint andL_reg_uimmL_HH1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((OR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (OR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 16562 "ad_s390.cpp"
  }
}

uint orI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void orI_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (O_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (O_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (OY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (O_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 16608 "ad_s390.cpp"
  }
}

void orI_Reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (O_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (O_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (OY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (O_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 16649 "ad_s390.cpp"
  }
}

void orI_reg_uimm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1839 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OILL_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (OILL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::uimm16(opnd_array(2)->constant(),16,32));
  
#line 16668 "ad_s390.cpp"
  }
}

uint orI_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orI_reg_uimm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1861 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OILF_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (OILF_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::uimm32(opnd_array(2)->constant(),16,48));
  
#line 16692 "ad_s390.cpp"
  }
}

uint orI_reg_uimm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void orL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (OGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 16716 "ad_s390.cpp"
  }
}

uint orL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orL_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (OG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (OG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (OG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (OG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 16762 "ad_s390.cpp"
  }
}

uint orL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void orL_Reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (OG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (OG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (OG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (OG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 16808 "ad_s390.cpp"
  }
}

uint orL_Reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void orL_reg_uimm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1839 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OILL_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (OILL_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,32) |
             Assembler::uimm16(opnd_array(2)->constantL(),16,32));
  
#line 16832 "ad_s390.cpp"
  }
}

uint orL_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orL_reg_uimm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1861 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((OILF_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (OILF_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::uimm32(opnd_array(2)->constantL(),16,48));
  
#line 16856 "ad_s390.cpp"
  }
}

void xorI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((XR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (XR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 16876 "ad_s390.cpp"
  }
}

uint xorI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void xorI_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (X_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (X_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (XY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (X_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 16922 "ad_s390.cpp"
  }
}

void xorI_Reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (X_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (X_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (XY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (X_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 16963 "ad_s390.cpp"
  }
}

void xorI_reg_uimm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1861 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XILF_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (XILF_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::uimm32(opnd_array(2)->constant(),16,48));
  
#line 16982 "ad_s390.cpp"
  }
}

uint xorI_reg_uimm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void xorL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (XGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,28,32));
  
#line 17006 "ad_s390.cpp"
  }
}

uint xorL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xorL_Reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (XG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (XG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (XG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (XG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 17052 "ad_s390.cpp"
  }
}

uint xorL_Reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void xorL_Reg_mem_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (XG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (XG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (XG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (XG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 17098 "ad_s390.cpp"
  }
}

uint xorL_Reg_mem_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void xorL_reg_uimm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1861 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((XILF_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (XILF_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */,8,48) |
             Assembler::uimm32(opnd_array(2)->constantL(),16,48));
  
#line 17122 "ad_s390.cpp"
  }
}

uint xorL_reg_uimm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void convI2BNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7897 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lnr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);  // Rdst := -|Rsrc|, i.e. Rdst == 0 <=> Rsrc == 0
    __ z_srl(opnd_array(0)->as_Register(ra_,this)/* dst */, 31);              // Rdst := sign(Rdest)
  
#line 17144 "ad_s390.cpp"
  }
}

uint convI2BNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void convP2BNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7910 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lngr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);     // Rdst := -|Rsrc| i.e. Rdst == 0 <=> Rsrc == 0
    __ z_srlg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */, 63); // Rdst := sign(Rdest)
  
#line 17166 "ad_s390.cpp"
  }
}

uint convP2BNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 10, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 10);
}

void cmpLTMask_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7923 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    // Avoid signed 32 bit overflow: Do sign extend and sub 64 bit.
    __ z_lgfr(Z_R0_scratch, opnd_array(2)->as_Register(ra_,this,idx2)/* src */);
    __ z_lgfr(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* dst */);
    __ z_sgr(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, Z_R0_scratch);
    __ z_srag(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 63);
  
#line 17192 "ad_s390.cpp"
  }
}

uint cmpLTMask_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 18, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 18);
}

void cmpLTMask_reg_zeroNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 7939 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_sra(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 31); 
#line 17212 "ad_s390.cpp"
  }
}

uint cmpLTMask_reg_zeroNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convD2F_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LEDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LEDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17235 "ad_s390.cpp"
  }
}

uint convD2F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convF2I_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7963 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, false, false);  // Initialize with result for unordered: 0.
    __ z_cebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);   // Round.
    __ z_brno(done);                             // Result is zero if unordered argument.
    __ z_cfebr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Assembler::to_zero);
    __ bind(done);
  
#line 17261 "ad_s390.cpp"
  }
}

uint convF2I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void convD2I_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7980 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, false, false);  // Initialize with result for unordered: 0.
    __ z_cdbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);   // Round.
    __ z_brno(done);                             // Result is zero if unordered argument.
    __ z_cfdbr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Assembler::to_zero);
    __ bind(done);
  
#line 17287 "ad_s390.cpp"
  }
}

uint convD2I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void convF2L_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7997 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, true, false);  // Initialize with result for unordered: 0.
    __ z_cebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);   // Round.
    __ z_brno(done);                             // Result is zero if unordered argument.
    __ z_cgebr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Assembler::to_zero);
    __ bind(done);
  
#line 17313 "ad_s390.cpp"
  }
}

uint convF2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void convD2L_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 8014 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    __ clear_reg(opnd_array(0)->as_Register(ra_,this)/* dst */, true, false);  // Initialize with result for unordered: 0.
    __ z_cdbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);   // Round.
    __ z_brno(done);                             // Result is zero if unordered argument.
    __ z_cgdbr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Assembler::to_zero);
    __ bind(done);
  
#line 17339 "ad_s390.cpp"
  }
}

uint convD2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void convF2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LDEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LDEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17362 "ad_s390.cpp"
  }
}

uint convF2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convF2D_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LDEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (LDEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (LDEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 17396 "ad_s390.cpp"
  }
}

uint convF2D_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void convI2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CDFBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (CDFBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17419 "ad_s390.cpp"
  }
}

uint convI2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convI2F_iregNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CEFBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (CEFBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17442 "ad_s390.cpp"
  }
}

uint convI2F_iregNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convI2L_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17465 "ad_s390.cpp"
  }
}

uint convI2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convI2L_reg_zexNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {
    MacroAssembler _masm(&cbuf);

#line 8082 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_llgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 17485 "ad_s390.cpp"
  }
}

uint convI2L_reg_zexNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convI2L_mem_zexNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LLGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LLGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 17531 "ad_s390.cpp"
  }
}

void zeroExtend_longNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {
    MacroAssembler _masm(&cbuf);

#line 8102 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_llgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 17546 "ad_s390.cpp"
  }
}

uint zeroExtend_longNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rShiftI16_lShiftI16_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// amount
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LHR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LHR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17570 "ad_s390.cpp"
  }
}

uint rShiftI16_lShiftI16_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rShiftI24_lShiftI24_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// amount
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17594 "ad_s390.cpp"
  }
}

uint rShiftI24_lShiftI24_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void MoveF2I_stack_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((L_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (L_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (L_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 17628 "ad_s390.cpp"
  }
}

uint MoveF2I_stack_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void MoveI2F_stack_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LE_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (LE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (LE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 17662 "ad_s390.cpp"
  }
}

void MoveD2L_stack_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 17691 "ad_s390.cpp"
  }
}

uint MoveD2L_stack_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void MoveL2D_stack_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LD_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (LD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (LD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 17725 "ad_s390.cpp"
  }
}

uint MoveL2D_stack_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void MoveI2F_reg_stackNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((ST_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (ST_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (ST_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 17759 "ad_s390.cpp"
  }
}

uint MoveI2F_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void MoveD2L_reg_stackNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STD_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (STD_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 17793 "ad_s390.cpp"
  }
}

uint MoveD2L_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void MoveL2D_reg_stackNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STG_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 17827 "ad_s390.cpp"
  }
}

uint MoveL2D_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void convL2F_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CEGBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (CEGBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17850 "ad_s390.cpp"
  }
}

uint convL2F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convL2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CDGBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (CDGBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 17873 "ad_s390.cpp"
  }
}

uint convL2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convL2I_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 8222 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ lr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 17892 "ad_s390.cpp"
  }
}

void shrL_reg_imm6_L2INode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt
  {

#line 1868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    z_emit48(cbuf, (SRAG_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,48) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,48) |
             Assembler::simm20(opnd_array(2)->constant()));
  
#line 17911 "ad_s390.cpp"
  }
}

uint shrL_reg_imm6_L2INode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void rangeCheck_iReg_uimmI16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// length
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// index
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 8258 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_clfit(opnd_array(2)->as_Register(ra_,this,idx2)/* length */, opnd_array(3)->constant(), opnd_array(1)->ccode()); 
#line 17933 "ad_s390.cpp"
  }
}

void rangeCheck_iReg_iRegNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// index
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// length
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {
    MacroAssembler _masm(&cbuf);

#line 8276 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_clrt(opnd_array(2)->as_Register(ra_,this,idx2)/* index */, opnd_array(3)->as_Register(ra_,this,idx3)/* length */, opnd_array(1)->ccode()); 
#line 17950 "ad_s390.cpp"
  }
}

void rangeCheck_uimmI16_iRegNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// index
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// length
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 8294 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_clfit(opnd_array(2)->as_Register(ra_,this,idx2)/* index */, opnd_array(3)->constant(), opnd_array(1)->ccode()); 
#line 17967 "ad_s390.cpp"
  }
}

void zeroCheckP_iReg_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// value
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 8311 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_cgit(opnd_array(2)->as_Register(ra_,this,idx2)/* value */, 0, opnd_array(1)->ccode()); 
#line 17984 "ad_s390.cpp"
  }
}

uint zeroCheckP_iReg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void zeroCheckN_iReg_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// value
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 8328 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_cit(opnd_array(2)->as_Register(ra_,this,idx2)/* value */, 0, opnd_array(1)->ccode()); 
#line 18006 "ad_s390.cpp"
  }
}

uint zeroCheckN_iReg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((CR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (CR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,12,16));
  
#line 18031 "ad_s390.cpp"
  }
}

uint compI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void compI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1854 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (CFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,48) |
             Assembler::simm32(opnd_array(2)->constant(),16,48));
  
#line 18055 "ad_s390.cpp"
  }
}

uint compI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compI_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1832 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (CHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,32) |
             Assembler::simm16(opnd_array(2)->constant(),16,32));
  
#line 18079 "ad_s390.cpp"
  }
}

uint compI_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compI_reg_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((LTR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (LTR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,16) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,12,16));
  
#line 18104 "ad_s390.cpp"
  }
}

uint compI_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void compI_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (C_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (C_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (CY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (C_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 18150 "ad_s390.cpp"
  }
}

void compU_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((CLR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (CLR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,12,16));
  
#line 18170 "ad_s390.cpp"
  }
}

uint compU_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void compU_reg_uimmNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1861 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (CLFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,48) |
             Assembler::uimm32(opnd_array(2)->constant(),16,48));
  
#line 18194 "ad_s390.cpp"
  }
}

uint compU_reg_uimmNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compU_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (CL_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (CL_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (CLY_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (CL_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 18240 "ad_s390.cpp"
  }
}

void compL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (CGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,28,32));
  
#line 18259 "ad_s390.cpp"
  }
}

uint compL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compL_reg_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (CGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,28,32));
  
#line 18283 "ad_s390.cpp"
  }
}

uint compL_reg_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compL_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1854 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CGFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (CGFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,48) |
             Assembler::simm32(opnd_array(2)->constantL(),16,48));
  
#line 18307 "ad_s390.cpp"
  }
}

uint compL_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compL_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1832 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CGHI_ZOPC /*primary()*/)>>30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (CGHI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,32) |
             Assembler::simm16(opnd_array(2)->constantL(),16,32));
  
#line 18331 "ad_s390.cpp"
  }
}

uint compL_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compL_reg_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LTGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,28,32));
  
#line 18355 "ad_s390.cpp"
  }
}

uint compL_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compL_conv_reg_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTGFR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LTGFR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,28,32));
  
#line 18379 "ad_s390.cpp"
  }
}

uint compL_conv_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compL_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (CG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (CG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (CG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (CG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 18425 "ad_s390.cpp"
  }
}

uint compL_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void compL_reg_memINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (CGF_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (CGF_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (CGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (CGF_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 18471 "ad_s390.cpp"
  }
}

uint compL_reg_memINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void compUL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (CLGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,28,32));
  
#line 18495 "ad_s390.cpp"
  }
}

uint compUL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compUL_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {

#line 1861 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLGFI_ZOPC /*primary()*/)>>46) & 0x03) == 3, "Instruction format error");
    z_emit48(cbuf, (CLGFI_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,48) |
             Assembler::uimm32(opnd_array(2)->constantL(),16,48));
  
#line 18519 "ad_s390.cpp"
  }
}

uint compUL_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void compP_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((CLGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (CLGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* op2 */,28,32));
  
#line 18543 "ad_s390.cpp"
  }
}

uint compP_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compP_reg_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LTGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,28,32));
  
#line 18567 "ad_s390.cpp"
  }
}

uint compP_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compP_decode_reg_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((LTR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (LTR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,8,16) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* op1 */,12,16));
  
#line 18592 "ad_s390.cpp"
  }
}

uint compP_decode_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void compP_reg_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (CLG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (CLG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(2)->disp(ra_,this,idx2))) {
      z_emit_inst(cbuf, (CLG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(2)->disp(ra_,this,idx2)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(2)->disp(ra_,this,idx2));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (CLG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, isize));
    }
  
#line 18638 "ad_s390.cpp"
  }
}

uint compP_reg_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= Z_DISP3_SIZE, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : Z_DISP3_SIZE);
}

void z196_minI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8565 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 18679 "ad_s390.cpp"
  }
}

void z10_minI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8598 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 18716 "ad_s390.cpp"
  }
}

void minI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8631 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 18756 "ad_s390.cpp"
  }
}

void z196_minI_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8667 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 18785 "ad_s390.cpp"
  }
}

void minI_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8691 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_cfi(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
    __ z_brl(done);
    __ z_lgfi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 18809 "ad_s390.cpp"
  }
}

void z196_minI_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8711 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 18838 "ad_s390.cpp"
  }
}

void minI_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8735 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_chi(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
    __ z_brl(done);
    __ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 18862 "ad_s390.cpp"
  }
}

void z10_minI_reg_imm8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8755 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_cij(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant(), Assembler::bcondLow, done);
    __ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 18885 "ad_s390.cpp"
  }
}

void z196_maxI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8775 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 18920 "ad_s390.cpp"
  }
}

void z10_maxI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8807 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 18957 "ad_s390.cpp"
  }
}

void maxI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8840 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 18998 "ad_s390.cpp"
  }
}

void z196_maxI_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8878 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 19027 "ad_s390.cpp"
  }
}

void maxI_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8902 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_cfi(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
    __ z_brh(done);
    __ z_lgfi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 19051 "ad_s390.cpp"
  }
}

void z196_maxI_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8922 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 19079 "ad_s390.cpp"
  }
}

void maxI_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8945 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_chi(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
    __ z_brh(done);
    __ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 19103 "ad_s390.cpp"
  }
}

void z10_maxI_reg_imm8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8965 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Label done;
    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */) {
      __ z_lgfr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
    }
    __ z_cij(opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant(), Assembler::bcondHigh, done);
    __ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->constant());
    __ bind(done);
  
#line 19126 "ad_s390.cpp"
  }
}

void absI_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LPR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((LPR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (LPR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,16) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,12,16));
  
#line 19145 "ad_s390.cpp"
  }
}

void negabsI_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1809 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LNR_ZOPC /*primary()*/) >> 14) & 0x03) == 0, "Instruction format error");
    assert( ((LNR_ZOPC /*primary()*/) >> 16)         == 0, "Instruction format error");
    z_emit16(cbuf, (LNR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,8,16) |
             Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */,12,16));
  
#line 19165 "ad_s390.cpp"
  }
}

void cmpF_ccNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9009 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_cebr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */); 
#line 19180 "ad_s390.cpp"
  }
}

uint cmpF_ccNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpD_ccNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9018 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_cdbr(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */); 
#line 19200 "ad_s390.cpp"
  }
}

uint cmpD_ccNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpF_cc_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((CEB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (CEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(cbuf, (CEB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 19235 "ad_s390.cpp"
  }
}

uint cmpF_cc_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void cmpD_cc_memNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1936 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(2)->index(ra_,this,idx2));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((CDB_ZOPC /*primary()*/) > (1L << 32)) {
      z_emit_inst(cbuf, (CDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */, 8, 48) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 48) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 48));
    } else {
      z_emit_inst(cbuf, (CDB_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */, 8, 32) |
                  Assembler::uimm12(opnd_array(2)->disp(ra_,this,idx2), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(2)->base(ra_,this,idx2)), 16, 32));
    }
  
#line 19270 "ad_s390.cpp"
  }
}

uint cmpD_cc_memNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void cmpF0_ccNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTEBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LTEBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32));
  
#line 19294 "ad_s390.cpp"
  }
}

uint cmpF0_ccNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpD0_ccNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LTDBR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LTDBR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src1 */,28,32));
  
#line 19318 "ad_s390.cpp"
  }
}

uint cmpD0_ccNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpF_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9070 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 19362 "ad_s390.cpp"
  }
}

uint cmpF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 24);
}

void cmpD_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9104 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 19407 "ad_s390.cpp"
  }
}

uint cmpD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 24);
}

void branchNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2014 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(1)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
    __ z_bru(l);
  
#line 19436 "ad_s390.cpp"
  }
}

uint branchNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void branchFarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2001 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(1)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
    __ z_brul(l);
  
#line 19465 "ad_s390.cpp"
  }
}

uint branchFarNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void branchConNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 2040 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(3)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
    __ z_brc((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 19496 "ad_s390.cpp"
  }
}

uint branchConNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void branchConFarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 2027 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(3)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 19527 "ad_s390.cpp"
  }
}

uint branchConFarNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void branchLoopEndNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 2040 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(3)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
    __ z_brc((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 19558 "ad_s390.cpp"
  }
}

uint branchLoopEndNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void branchLoopEndFarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 2027 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(3)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
    __ z_brcl((Assembler::branch_condition)opnd_array(1)->ccode(), l);
  
#line 19589 "ad_s390.cpp"
  }
}

uint branchLoopEndFarNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 6, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 6);
}

void testAndBranchLoopEnd_RegNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2053 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
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
  
#line 19632 "ad_s390.cpp"
  }
}

void cmpb_RegINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2053 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
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
  
#line 19670 "ad_s390.cpp"
  }
}

void cmpbU_RegINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2053 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
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
  
#line 19708 "ad_s390.cpp"
  }
}

void cmpb_RegLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2053 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
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
  
#line 19746 "ad_s390.cpp"
  }
}

void cmpb_RegPPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2053 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
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
  
#line 19784 "ad_s390.cpp"
  }
}

void cmpb_RegNNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2053 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);
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
  
#line 19822 "ad_s390.cpp"
  }
}

void testAndBranchLoopEnd_ImmNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2103 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 19861 "ad_s390.cpp"
  }
}

void cmpb_RegI_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2103 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 19900 "ad_s390.cpp"
  }
}

void cmpbU_RegI_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2103 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 19939 "ad_s390.cpp"
  }
}

void cmpb_RegL_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2103 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 19978 "ad_s390.cpp"
  }
}

void cmpb_RegP_immPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2103 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20017 "ad_s390.cpp"
  }
}

void cmpb_RegN_immP0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2103 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20056 "ad_s390.cpp"
  }
}

void cmpb_RegN_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2103 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20095 "ad_s390.cpp"
  }
}

void testAndBranchLoopEnd_RegFarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2077 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20135 "ad_s390.cpp"
  }
}

void cmpb_RegI_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2077 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20175 "ad_s390.cpp"
  }
}

void cmpbU_RegI_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2077 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20215 "ad_s390.cpp"
  }
}

void cmpb_RegL_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2077 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20255 "ad_s390.cpp"
  }
}

void cmpb_RegPP_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2077 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20295 "ad_s390.cpp"
  }
}

void cmpb_RegNN_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2077 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20335 "ad_s390.cpp"
  }
}

void testAndBranchLoopEnd_ImmFarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2128 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20375 "ad_s390.cpp"
  }
}

void cmpb_RegI_imm_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2128 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20415 "ad_s390.cpp"
  }
}

void cmpbU_RegI_imm_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2128 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20455 "ad_s390.cpp"
  }
}

void cmpb_RegL_imm_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2128 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20495 "ad_s390.cpp"
  }
}

void cmpb_RegP_immP_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2128 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20535 "ad_s390.cpp"
  }
}

void cmpb_RegN_immP0_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2128 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20575 "ad_s390.cpp"
  }
}

void cmpb_RegN_immN_FarNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  {

#line 2128 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    Label* p = opnd_array(4)->label();

    // 'p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    // Use a bound dummy label in that case.
    Label d;
    __ bind(d);
    Label& l = (NULL == p) ? d : *(p);

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
  
#line 20615 "ad_s390.cpp"
  }
}

void cmpL3_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9634 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 20654 "ad_s390.cpp"
  }
}

uint cmpL3_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 24);
}

void safePointNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {

#line 1797 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    __ unimplemented("Unimplemented mach node encoding in AD file.", 13);
  
#line 20675 "ad_s390.cpp"
  }
}

void safePoint_pollNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// cr
  {
    MacroAssembler _masm(&cbuf);

#line 9679 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    // Mark the code position where the load from the safepoint
    // polling page was emitted as relocInfo::poll_type.
    __ relocate(relocInfo::poll_type);
    __ load_from_polling_page(opnd_array(1)->as_Register(ra_,this,idx1)/* poll */);
  
#line 20694 "ad_s390.cpp"
  }
}

void CallStaticJavaDirect_dynTOCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2181 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    // Call to fixup routine. Fixup routine uses ScopeDesc info to determine
    // whom we intended to call.
    MacroAssembler _masm(&cbuf);
    int ret_offset = 0;

    if (!_method) {
      ret_offset = emit_call_reloc(_masm, opnd_array(1)->method(),
                                   relocInfo::runtime_call_w_cp_type, ra_);
    } else {
      int method_index = resolved_method_index(cbuf);
      if (_optimized_virtual) {
        ret_offset = emit_call_reloc(_masm, opnd_array(1)->method(),
                                     opt_virtual_call_Relocation::spec(method_index));
      } else {
        ret_offset = emit_call_reloc(_masm, opnd_array(1)->method(),
                                     static_call_Relocation::spec(method_index));
      }
    }
    assert(__ inst_mark() != NULL, "emit_call_reloc must set_inst_mark()");

    if (_method) { // Emit stub for static call.
      address stub = CompiledStaticCall::emit_to_interp_stub(cbuf);
      if (stub == NULL) {
        ciEnv::current()->record_failure("CodeCache is full");
        return;
      }
    }
  
#line 20735 "ad_s390.cpp"
  }
}

void CallDynamicJavaDirect_dynTOCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2212 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);
    unsigned int start_off = __ offset();

    int vtable_index = this->_vtable_index;
    if (vtable_index == -4) {
      Register ic_reg = reg_to_register_object(Matcher::inline_cache_reg_encode());
      address virtual_call_oop_addr = NULL;

      AddressLiteral empty_ic((address) Universe::non_oop_word());
      virtual_call_oop_addr = __ pc();
      bool success = __ load_const_from_toc(ic_reg, empty_ic);
      if (!success) {
        Compile::current()->env()->record_out_of_memory_failure();
        return;
      }

      // Call to fixup routine. Fixup routine uses ScopeDesc info
      // to determine who we intended to call.
      int method_index = resolved_method_index(cbuf);
      __ relocate(virtual_call_Relocation::spec(virtual_call_oop_addr, method_index));
      unsigned int ret_off = __ offset();
      assert(__ offset() - start_off == 6, "bad prelude len: %d", __ offset() - start_off);
      ret_off += emit_call_reloc(_masm, opnd_array(1)->method(), relocInfo::none, ra_);
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
      int v_off        = entry_offset + vtableEntry::method_offset_in_bytes();

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
  
#line 20801 "ad_s390.cpp"
  }
}

void CallRuntimeDirectNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2155 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);

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
    if (call_addr == NULL) {
      Compile::current()->env()->record_out_of_memory_failure();
      return;
    }

#ifdef ASSERT
    // Plausibility check for size_of_code assumptions.
    unsigned int actual_ret_off = __ offset();
    assert(start_off + size_of_code == actual_ret_off, "wrong return_pc");
#endif
  
#line 20838 "ad_s390.cpp"
  }
}

void CallLeafDirectNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2155 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);

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
    if (call_addr == NULL) {
      Compile::current()->env()->record_out_of_memory_failure();
      return;
    }

#ifdef ASSERT
    // Plausibility check for size_of_code assumptions.
    unsigned int actual_ret_off = __ offset();
    assert(start_off + size_of_code == actual_ret_off, "wrong return_pc");
#endif
  
#line 20875 "ad_s390.cpp"
  }
}

void CallLeafNoFPDirectNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 2155 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    MacroAssembler _masm(&cbuf);

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
    if (call_addr == NULL) {
      Compile::current()->env()->record_out_of_memory_failure();
      return;
    }

#ifdef ASSERT
    // Plausibility check for size_of_code assumptions.
    unsigned int actual_ret_off = __ offset();
    assert(start_off + size_of_code == actual_ret_off, "wrong return_pc");
#endif
  
#line 20912 "ad_s390.cpp"
  }
}

void TailCalljmpIndNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// method_oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 9764 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_br(opnd_array(1)->as_Register(ra_,this,idx1)/* jump_target */); 
#line 20927 "ad_s390.cpp"
  }
}

uint TailCalljmpIndNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void RetNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 9773 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_br(Z_R14); 
#line 20946 "ad_s390.cpp"
  }
}

uint RetNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void tailjmpIndNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// ex_oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 9788 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ z_lg(Z_ARG2/* issuing pc */, _z_abi(return_pc), Z_SP);
    __ z_br(opnd_array(1)->as_Register(ra_,this,idx1)/* jump_target */);
  
#line 20969 "ad_s390.cpp"
  }
}

uint tailjmpIndNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void CreateExceptionNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint CreateExceptionNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void RethrowExceptionNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 9814 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    cbuf.set_insts_mark();
    __ load_const_optimized(Z_R1_scratch, (address)OptoRuntime::rethrow_stub());
    __ z_br(Z_R1_scratch);
  
#line 21005 "ad_s390.cpp"
  }
}

void ShouldNotReachHereNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 9828 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_illtrap(); 
#line 21019 "ad_s390.cpp"
  }
}

uint ShouldNotReachHereNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 2, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 2);
}

void partialSubtypeCheckNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// sub
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// super
  {
    MacroAssembler _masm(&cbuf);

#line 9844 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral stub_address(StubRoutines::zarch::partial_subtype_check());
    __ load_const_optimized(Z_ARG4, stub_address);
    __ z_basr(Z_R14, Z_ARG4);
  
#line 21043 "ad_s390.cpp"
  }
}

void partialSubtypeCheck_vs_zeroNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// sub
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// super
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 9859 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    AddressLiteral stub_address(StubRoutines::zarch::partial_subtype_check());
    __ load_const_optimized(Z_ARG4, stub_address);
    __ z_basr(Z_R14, Z_ARG4);
  
#line 21063 "ad_s390.cpp"
  }
}

void cmpFastLockNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 9876 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ compiler_fast_lock_object(opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */, opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */,
                                             UseBiasedLocking && !UseOptoBiasInlining); 
#line 21081 "ad_s390.cpp"
  }
}

void cmpFastUnlockNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 9887 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ compiler_fast_unlock_object(opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */, opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */,
                                               UseBiasedLocking && !UseOptoBiasInlining); 
#line 21099 "ad_s390.cpp"
  }
}

void inlineCallClearArrayConstNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {
    MacroAssembler _masm(&cbuf);

#line 9898 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ Clear_Array_Const(opnd_array(1)->constantL(), opnd_array(2)->as_Register(ra_,this,idx2)/* base */); 
#line 21114 "ad_s390.cpp"
  }
}

void inlineCallClearArrayConstBigNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// srcA
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// srcL
  {
    MacroAssembler _masm(&cbuf);

#line 9908 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ Clear_Array_Const_Big(opnd_array(1)->constantL(), opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(3)->as_Register(ra_,this,idx3)/* srcA */, opnd_array(4)->as_Register(ra_,this,idx4)/* srcL */); 
#line 21131 "ad_s390.cpp"
  }
}

void inlineCallClearArrayNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// srcA
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// srcL
  {
    MacroAssembler _masm(&cbuf);

#line 9918 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ Clear_Array(opnd_array(1)->as_Register(ra_,this,idx1)/* cnt */, opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(3)->as_Register(ra_,this,idx3)/* srcA */, opnd_array(4)->as_Register(ra_,this,idx4)/* srcL */); 
#line 21148 "ad_s390.cpp"
  }
}

void string_equalsLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// oddReg
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// evenReg
  {
    MacroAssembler _masm(&cbuf);

#line 9932 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ array_equals(false, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* str2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* cnt */, opnd_array(4)->as_Register(ra_,this,idx4)/* oddReg */, opnd_array(5)->as_Register(ra_,this,idx5)/* evenReg */,
                    opnd_array(0)->as_Register(ra_,this)/* result */, true /* byte */);
  
#line 21170 "ad_s390.cpp"
  }
}

void string_equalsUNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// oddReg
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// evenReg
  {
    MacroAssembler _masm(&cbuf);

#line 9946 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ array_equals(false, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* str2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* cnt */, opnd_array(4)->as_Register(ra_,this,idx4)/* oddReg */, opnd_array(5)->as_Register(ra_,this,idx5)/* evenReg */,
                    opnd_array(0)->as_Register(ra_,this)/* result */, false /* byte */);
  
#line 21192 "ad_s390.cpp"
  }
}

void string_equals_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  {
    MacroAssembler _masm(&cbuf);

#line 9960 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 21223 "ad_s390.cpp"
  }
}

void string_equalsC_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  {
    MacroAssembler _masm(&cbuf);

#line 9985 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 21254 "ad_s390.cpp"
  }
}

void array_equalsBNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// oddReg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// evenReg
  {
    MacroAssembler _masm(&cbuf);

#line 10011 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ array_equals(true, opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* ary2 */,
                    noreg, opnd_array(3)->as_Register(ra_,this,idx3)/* oddReg */, opnd_array(4)->as_Register(ra_,this,idx4)/* evenReg */,
                    opnd_array(0)->as_Register(ra_,this)/* result */, true /* byte */);
  
#line 21275 "ad_s390.cpp"
  }
}

void array_equalsCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// oddReg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// evenReg
  {
    MacroAssembler _masm(&cbuf);

#line 10025 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ array_equals(true, opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* ary2 */,
                    noreg, opnd_array(3)->as_Register(ra_,this,idx3)/* oddReg */, opnd_array(4)->as_Register(ra_,this,idx4)/* evenReg */,
                    opnd_array(0)->as_Register(ra_,this)/* result */, false /* byte */);
  
#line 21296 "ad_s390.cpp"
  }
}

void string_compareLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10040 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::LL);
  
#line 21321 "ad_s390.cpp"
  }
}

void string_compareUNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10055 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::UU);
  
#line 21346 "ad_s390.cpp"
  }
}

void string_compareLUNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10070 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::LU);
  
#line 21371 "ad_s390.cpp"
  }
}

void string_compareULNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10085 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compare(opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */,
                      opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */, opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::UL);
  
#line 21396 "ad_s390.cpp"
  }
}

void indexOfChar_UNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// oddReg
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// evenReg
  {
    MacroAssembler _masm(&cbuf);

#line 10100 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof_char(opnd_array(4)->as_Register(ra_,this,idx4)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           opnd_array(3)->as_Register(ra_,this,idx3)/* ch */, 0 /* unused, ch is in register */,
                           opnd_array(5)->as_Register(ra_,this,idx5)/* oddReg */, opnd_array(6)->as_Register(ra_,this,idx6)/* evenReg */, false /*is_byte*/);
  
#line 21420 "ad_s390.cpp"
  }
}

void indexOf_imm1_UNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10115 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 21455 "ad_s390.cpp"
  }
}

void indexOf_imm1_LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10140 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    immPOper *needleOper = (immPOper *)opnd_array(3);
    const TypeOopPtr *t = needleOper->type()->isa_oopptr();
    ciTypeArray* needle_values = t->const_oop()->as_type_array();  // Pointer to live char *
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           noreg, chr,
                           opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, true /*is_byte*/);
  
#line 21484 "ad_s390.cpp"
  }
}

void indexOf_imm1_ULNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10159 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    immPOper *needleOper = (immPOper *)opnd_array(3);
    const TypeOopPtr *t = needleOper->type()->isa_oopptr();
    ciTypeArray* needle_values = t->const_oop()->as_type_array();  // Pointer to live char *
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           noreg, chr,
                           opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, false /*is_byte*/);
  
#line 21513 "ad_s390.cpp"
  }
}

void indexOf_imm_UNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10179 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, noreg, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::UU);
  
#line 21538 "ad_s390.cpp"
  }
}

void indexOf_imm_LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10194 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, noreg, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::LL);
  
#line 21563 "ad_s390.cpp"
  }
}

void indexOf_imm_ULNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10209 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, noreg, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::UL);
  
#line 21588 "ad_s390.cpp"
  }
}

void indexOf_UNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10224 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::UU);
  
#line 21613 "ad_s390.cpp"
  }
}

void indexOf_LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10239 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::LL);
  
#line 21638 "ad_s390.cpp"
  }
}

void indexOf_ULNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
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
    MacroAssembler _masm(&cbuf);

#line 10254 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* oddReg */, opnd_array(7)->as_Register(ra_,this,idx7)/* evenReg */, StrIntrinsicNode::UL);
  
#line 21663 "ad_s390.cpp"
  }
}

void string_compressNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 10269 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compress(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */, false);
  
#line 21684 "ad_s390.cpp"
  }
}

void string_inflateNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 10295 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_inflate(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */);
  
#line 21703 "ad_s390.cpp"
  }
}

void string_inflate_constNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 10307 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_inflate_const(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */, opnd_array(3)->constant());
  
#line 21722 "ad_s390.cpp"
  }
}

void has_negativesNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// len
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// oddReg
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// evenReg
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 10319 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ has_negatives(opnd_array(3)->as_Register(ra_,this,idx3)/* result */, opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* len */,
                     opnd_array(4)->as_Register(ra_,this,idx4)/* oddReg */, opnd_array(5)->as_Register(ra_,this,idx5)/* evenReg */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp */);
  
#line 21744 "ad_s390.cpp"
  }
}

void encode_iso_arrayNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 10332 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    __ string_compress(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */, true);
  
#line 21765 "ad_s390.cpp"
  }
}

void expand_storeFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(0)->index(ra_,this,idx0));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((STE_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(0)->disp(ra_,this,0)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 48));
    } else {
      z_emit_inst(cbuf, (STE_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */, 8, 32) |
                  Assembler::uimm12(opnd_array(0)->disp(ra_,this,0), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(0)->base(ra_,this,idx0)), 16, 32));
    }
  
#line 21794 "ad_s390.cpp"
  }
}

void expand_LoadLogical_I2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// mem
  {

#line 1954 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.
    if ((LLGF_ZOPC /*primary()*/) > (1L<<32)) {
      z_emit_inst(cbuf, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
      z_emit_inst(cbuf, (LLGF_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 32) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, 32) |
                  Assembler::reg(Ridx, 12, 32) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 32));
    }
  
#line 21823 "ad_s390.cpp"
  }
}

void expand_Repl2I_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10496 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    if (opnd_array(0)->as_Register(ra_,this)/* dst */== opnd_array(1)->as_Register(ra_,this,idx1)/* src */) {
      __ z_sllg(Z_R0_scratch, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 64-32);
      __ z_ogr(opnd_array(0)->as_Register(ra_,this)/* dst */, Z_R0_scratch);
    }  else {
      __ z_sllg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 64-32);
      __ z_ogr( opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    }
  
#line 21845 "ad_s390.cpp"
  }
}

void Repl8B_reg_risbgNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10517 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src */) {
      __ z_lgr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    }
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */, 48, 55,  8, false);
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */, 32, 47, 16, false);
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */,  0, 31, 32, false);
  
#line 21866 "ad_s390.cpp"
  }
}

void Repl8B_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10534 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int64_t  Isrc8 = opnd_array(1)->constant()& 0x000000ff;
    int64_t Isrc16 =  Isrc8 <<  8 |  Isrc8;
    int64_t Isrc32 = Isrc16 << 16 | Isrc16;
    assert(Isrc8 != 0x000000ff && Isrc8 != 0, "should be handled by other match rules.");

    __ z_llilf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
    __ z_iihf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
  
#line 21888 "ad_s390.cpp"
  }
}

void Repl8B_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10552 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laz(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, Z_R0); 
#line 21902 "ad_s390.cpp"
  }
}

void Repl8B_immm1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10562 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, -1); 
#line 21916 "ad_s390.cpp"
  }
}

void Repl4S_reg_risbgNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10573 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src */) {
      __ z_lgr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    }
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */, 32, 47, 16, false);
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */,  0, 31, 32, false);
  
#line 21936 "ad_s390.cpp"
  }
}

void Repl4S_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10589 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int64_t Isrc16 = opnd_array(1)->constant()& 0x0000ffff;
    int64_t Isrc32 = Isrc16 << 16 | Isrc16;
    assert(Isrc16 != 0x0000ffff && Isrc16 != 0, "Repl4S_imm: (src == " INT64_FORMAT
           ") should be handled by other match rules.", opnd_array(1)->constant());

    __ z_llilf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
    __ z_iihf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
  
#line 21958 "ad_s390.cpp"
  }
}

void Repl4S_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10607 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laz(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, Z_R0); 
#line 21972 "ad_s390.cpp"
  }
}

void Repl4S_immm1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10617 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, -1); 
#line 21986 "ad_s390.cpp"
  }
}

void Repl2I_reg_risbgNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10628 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    if (opnd_array(0)->as_Register(ra_,this)/* dst */!= opnd_array(1)->as_Register(ra_,this,idx1)/* src */) {
      __ z_lgr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    }
    __ rotate_then_insert(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */, 0, 31, 32, false);
  
#line 22005 "ad_s390.cpp"
  }
}

void Repl2I_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10643 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int64_t Isrc32 = opnd_array(1)->constant();
    assert(Isrc32 != -1 && Isrc32 != 0, "should be handled by other match rules.");

    __ z_llilf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
    __ z_iihf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
  
#line 22025 "ad_s390.cpp"
  }
}

void Repl2I_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10659 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laz(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, Z_R0); 
#line 22039 "ad_s390.cpp"
  }
}

void Repl2I_immm1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10669 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_lghi(opnd_array(0)->as_Register(ra_,this)/* dst */, -1); 
#line 22053 "ad_s390.cpp"
  }
}

void Repl2F_reg_directNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10695 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(VM_Version::has_FPSupportEnhancements(), "encoder should never be called on old H/W");
    __ z_lgdr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);

    __ z_srlg(Z_R0_scratch, opnd_array(0)->as_Register(ra_,this)/* dst */, 32);  // Floats are left-justified in 64bit reg.
    __ z_iilf(opnd_array(0)->as_Register(ra_,this)/* dst */, 0);                 // Save a "result not ready" stall.
    __ z_ogr(opnd_array(0)->as_Register(ra_,this)/* dst */, Z_R0_scratch);
  
#line 22074 "ad_s390.cpp"
  }
}

void Repl2F_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10712 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    union {
      int   Isrc32;
      float Fsrc32;
    };
    Fsrc32 = opnd_array(1)->constantF();
    __ z_llilf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
    __ z_iihf(opnd_array(0)->as_Register(ra_,this)/* dst */, Isrc32);
  
#line 22096 "ad_s390.cpp"
  }
}

void Repl2F_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10731 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_laz(opnd_array(0)->as_Register(ra_,this)/* dst */, 0, Z_R0); 
#line 22110 "ad_s390.cpp"
  }
}

void storeA8BNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (STG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (STG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (STG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(2)->reg(ra_,this,idx2)/* src */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 22151 "ad_s390.cpp"
  }
}

void loadV8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 1972 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    int isize = (LG_ZOPC /*secondary()*/) > 1L << 32 ? 48 : 32;
    Register Ridx = as_Register(opnd_array(1)->index(ra_,this,idx1));
    if (Ridx == noreg) { Ridx = Z_R0; } // Index is 0.

    if (Displacement::is_shortDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                  Assembler::uimm12(opnd_array(1)->disp(ra_,this,idx1), 20, isize) |
                  Assembler::reg(Ridx, 12, isize) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    } else if (Displacement::is_validDisp((long)opnd_array(1)->disp(ra_,this,idx1))) {
      z_emit_inst(cbuf, (LG_ZOPC /*primary()*/) |
                  Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, 48) |
                  Assembler::simm20(opnd_array(1)->disp(ra_,this,idx1)) |
                  Assembler::reg(Ridx, 12, 48) |
                  Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, 48));
    } else {
        MacroAssembler _masm(&cbuf);
        __ load_const_optimized(Z_R1_scratch, opnd_array(1)->disp(ra_,this,idx1));
        if (Ridx != Z_R0) { __ z_agr(Z_R1_scratch, Ridx); }
        z_emit_inst(cbuf, (LG_ZOPC /*secondary()*/) |
                    Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */, 8, isize) |
                    Assembler::uimm12(0, 20, isize) |
                    Assembler::reg(Z_R1_scratch, 12, isize) |
                    Assembler::regz(reg_to_register_object(opnd_array(1)->base(ra_,this,idx1)), 16, isize));
    }
  
#line 22191 "ad_s390.cpp"
  }
}

void bytes_reverse_intNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LRVR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LRVR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 22209 "ad_s390.cpp"
  }
}

uint bytes_reverse_intNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void bytes_reverse_longNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 1817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert((((LRVGR_ZOPC /*primary()*/) >> 30) & 0x03) == 2, "Instruction format error");
    z_emit32(cbuf, (LRVGR_ZOPC /*primary()*/) |
             Assembler::reg(opnd_array(0)->reg(ra_,this)/* dst */,24,32) |
             Assembler::reg(opnd_array(1)->reg(ra_,this,idx1)/* src */,28,32));
  
#line 22232 "ad_s390.cpp"
  }
}

void countLeadingZerosINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10806 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 22271 "ad_s390.cpp"
  }
}

uint countLeadingZerosINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 14, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 14);
}

void countLeadingZerosLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10841 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
__ z_flogr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */); 
#line 22290 "ad_s390.cpp"
  }
}

uint countLeadingZerosLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void countTrailingZerosINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 10874 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 22346 "ad_s390.cpp"
  }
}

void countTrailingZerosLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  {
    MacroAssembler _masm(&cbuf);

#line 10925 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

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
  
#line 22373 "ad_s390.cpp"
  }
}

void popCountINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 10951 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(2)->as_Register(ra_,this,idx2)/* dst */;
    Register Rsrc = opnd_array(1)->as_Register(ra_,this,idx1)/* src */;
    Register Rtmp = opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */;

    // Prefer compile-time assertion over run-time SIGILL.
    assert(VM_Version::has_PopCount(), "bad predicate for countLeadingZerosI");
    assert_different_registers(Rdst, Rtmp);

    // Version 2: shows 10%(z196) improvement over original.
    __ z_popcnt(Rdst, Rsrc);
    __ z_srlg(Rtmp, Rdst, 16); // calc  byte4+byte6 and byte5+byte7
    __ z_alr(Rdst, Rtmp);      //   into byte6 and byte7
    __ z_srlg(Rtmp, Rdst,  8); // calc (byte4+byte6) + (byte5+byte7)
    __ z_alr(Rdst, Rtmp);      //   into byte7
    __ z_llgcr(Rdst, Rdst);    // zero-extend sum
  
#line 22405 "ad_s390.cpp"
  }
}

uint popCountINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 24);
}

void popCountLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 10978 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    Register Rdst = opnd_array(2)->as_Register(ra_,this,idx2)/* dst */;
    Register Rsrc = opnd_array(1)->as_Register(ra_,this,idx1)/* src */;
    Register Rtmp = opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */;

    // Prefer compile-time assertion over run-time SIGILL.
    assert(VM_Version::has_PopCount(), "bad predicate for countLeadingZerosI");
    assert_different_registers(Rdst, Rtmp);

    // Original version. Using LA instead of algr seems to be a really bad idea (-35%).
    __ z_popcnt(Rdst, Rsrc);
    __ z_ahhlr(Rdst, Rdst, Rdst);
    __ z_sllg(Rtmp, Rdst, 16);
    __ z_algr(Rdst, Rtmp);
    __ z_sllg(Rtmp, Rdst,  8);
    __ z_algr(Rdst, Rtmp);
    __ z_srlg(Rdst, Rdst, 56);
  
#line 22443 "ad_s390.cpp"
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
const MachOper* storeCMNode::memory_operand() const { return _opnds[1]; }
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
const MachOper* decodeLoadNNode::memory_operand() const { return _opnds[1]; }
const MachOper* decodeLoadNKlassNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeNNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeNKlassNode::memory_operand() const { return _opnds[1]; }
const TypePtr *membar_acquireNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_acquireNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_acquire_0Node::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_acquire_0Node::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_acquire_lockNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_acquire_lockNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_releaseNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_releaseNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_release_0Node::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_release_0Node::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_release_lockNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_release_lockNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_volatileNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_volatileNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *unnecessary_membar_volatileNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* unnecessary_membar_volatileNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_storestoreNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_storestoreNode::memory_operand() const { return (MachOper*)-1; }
const MachOper* loadPLockedNode::memory_operand() const { return _opnds[1]; }
const MachOper* storePConditionalNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeLConditionalNode::memory_operand() const { return _opnds[1]; }
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
const MachOper* xorL_Reg_mem_0Node::memory_operand() const { return _opnds[1]; }
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
const MachOper* loadV8Node::memory_operand() const { return _opnds[1]; }


const bool Matcher::has_match_rule(int opcode) {
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
    false,  // RegFlags
    false,  // VecS
    false,  // VecD
    false,  // VecX
    false,  // VecY
    false,  // VecZ
    false,  // _last_machine_leaf
    true ,  // AbsD
    true ,  // AbsF
    true ,  // AbsI
    true ,  // AddD
    true ,  // AddF
    true ,  // AddI
    true ,  // AddL
    true ,  // AddP
    false,  // Allocate
    false,  // AllocateArray
    true ,  // AndI
    true ,  // AndL
    false,  // ArrayCopy
    true ,  // AryEq
    false,  // AtanD
    true ,  // Binary
    true ,  // Bool
    false,  // BoxLock
    true ,  // ReverseBytesI
    true ,  // ReverseBytesL
    false,  // ReverseBytesUS
    false,  // ReverseBytesS
    false,  // CProj
    true ,  // CallDynamicJava
    false,  // CallJava
    true ,  // CallLeaf
    true ,  // CallLeafNoFP
    true ,  // CallRuntime
    true ,  // CallStaticJava
    true ,  // CastII
    true ,  // CastX2P
    true ,  // CastP2X
    true ,  // CastPP
    false,  // Catch
    false,  // CatchProj
    true ,  // CheckCastPP
    true ,  // ClearArray
    false,  // ConstraintCast
    true ,  // CMoveD
    false,  // CMoveVD
    true ,  // CMoveF
    false,  // CMoveVF
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
    true ,  // CmpUL
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
    false,  // WeakCompareAndSwapP
    false,  // WeakCompareAndSwapN
    false,  // CompareAndExchangeB
    false,  // CompareAndExchangeS
    false,  // CompareAndExchangeI
    false,  // CompareAndExchangeL
    false,  // CompareAndExchangeP
    false,  // CompareAndExchangeN
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
    false,  // CountedLoop
    true ,  // CountedLoopEnd
    false,  // OuterStripMinedLoop
    false,  // OuterStripMinedLoopEnd
    true ,  // CountLeadingZerosI
    true ,  // CountLeadingZerosL
    true ,  // CountTrailingZerosI
    true ,  // CountTrailingZerosL
    true ,  // CreateEx
    true ,  // DecodeN
    true ,  // DecodeNKlass
    true ,  // DivD
    true ,  // DivF
    true ,  // DivI
    true ,  // DivL
    false,  // DivMod
    true ,  // DivModI
    true ,  // DivModL
    true ,  // EncodeISOArray
    true ,  // EncodeP
    true ,  // EncodePKlass
    true ,  // FastLock
    true ,  // FastUnlock
    true ,  // FmaD
    true ,  // FmaF
    true ,  // Goto
    true ,  // Halt
    true ,  // HasNegatives
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
    true ,  // LoadPLocked
    true ,  // LoadP
    true ,  // LoadN
    true ,  // LoadRange
    true ,  // LoadS
    false,  // LoadBarrier
    false,  // LoadBarrierSlowReg
    false,  // LoadBarrierWeakSlowReg
    false,  // Lock
    false,  // Loop
    false,  // LoopLimit
    false,  // Mach
    false,  // MachProj
    true ,  // MaxI
    true ,  // MemBarAcquire
    true ,  // LoadFence
    false,  // SetVectMaskI
    true ,  // MemBarAcquireLock
    true ,  // MemBarCPUOrder
    true ,  // MemBarRelease
    true ,  // StoreFence
    true ,  // MemBarReleaseLock
    true ,  // MemBarVolatile
    true ,  // MemBarStoreStore
    false,  // MergeMem
    true ,  // MinI
    false,  // ModD
    false,  // ModF
    true ,  // ModI
    true ,  // ModL
    true ,  // MoveI2F
    true ,  // MoveF2I
    true ,  // MoveL2D
    true ,  // MoveD2L
    true ,  // MulD
    true ,  // MulF
    true ,  // MulHiL
    true ,  // MulI
    true ,  // MulL
    false,  // Multi
    true ,  // NegD
    true ,  // NegF
    false,  // NeverBranch
    false,  // OnSpinWait
    false,  // Opaque1
    false,  // Opaque2
    false,  // Opaque3
    false,  // Opaque4
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
    true ,  // PartialSubtypeCheck
    false,  // Phi
    true ,  // PopCountI
    true ,  // PopCountL
    false,  // PopCountVI
    true ,  // PrefetchAllocation
    false,  // Proj
    true ,  // RShiftI
    true ,  // RShiftL
    false,  // Region
    true ,  // Rethrow
    true ,  // Return
    false,  // Root
    true ,  // RoundDouble
    true ,  // RoundFloat
    true ,  // SafePoint
    false,  // SafePointScalarObject
    false,  // SCMemProj
    true ,  // SqrtD
    false,  // SqrtF
    false,  // Start
    false,  // StartOSR
    true ,  // StoreB
    true ,  // StoreC
    true ,  // StoreCM
    true ,  // StorePConditional
    false,  // StoreIConditional
    true ,  // StoreLConditional
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
    true ,  // SubD
    true ,  // SubF
    true ,  // SubI
    true ,  // SubL
    true ,  // TailCall
    true ,  // TailJump
    true ,  // ThreadLocal
    false,  // Unlock
    true ,  // URShiftI
    true ,  // URShiftL
    true ,  // XorI
    true ,  // XorL
    false,  // Vector
    false,  // AddVB
    false,  // AddVS
    false,  // AddVI
    false,  // AddReductionVI
    false,  // AddVL
    false,  // AddReductionVL
    false,  // AddVF
    false,  // AddReductionVF
    false,  // AddVD
    false,  // AddReductionVD
    false,  // SubVB
    false,  // SubVS
    false,  // SubVI
    false,  // SubVL
    false,  // SubVF
    false,  // SubVD
    false,  // MulVS
    false,  // MulVI
    false,  // MulReductionVI
    false,  // MulVL
    false,  // MulReductionVL
    false,  // MulVF
    false,  // MulReductionVF
    false,  // MulVD
    false,  // MulReductionVD
    false,  // FmaVD
    false,  // FmaVF
    false,  // DivVF
    false,  // DivVD
    false,  // AbsVF
    false,  // AbsVD
    false,  // NegVF
    false,  // NegVD
    false,  // SqrtVD
    false,  // SqrtVF
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
    false,  // OrV
    false,  // XorV
    true ,  // LoadVector
    true ,  // StoreVector
    false,  // Pack
    false,  // PackB
    false,  // PackS
    false,  // PackI
    false,  // PackL
    false,  // PackF
    false,  // PackD
    false,  // Pack2L
    false,  // Pack2D
    true ,  // ReplicateB
    true ,  // ReplicateS
    true ,  // ReplicateI
    false,  // ReplicateL
    true ,  // ReplicateF
    false,  // ReplicateD
    false,  // Extract
    false,  // ExtractB
    false,  // ExtractUB
    false,  // ExtractC
    false,  // ExtractS
    false,  // ExtractI
    false,  // ExtractL
    false,  // ExtractF
    false   // ExtractD
};


bool Matcher::stack_direction() const { return false; }

int Compile::sync_stack_slots() const { return frame::jit_monitor_size_in_4_byte_units; }

uint Matcher::stack_alignment_in_bytes() { return frame::alignment_in_bytes; }

OptoReg::Name Matcher::return_addr() const { return OptoReg::Name(Z_R14_num); }

uint Compile::in_preserve_stack_slots() { return frame::jit_in_preserve_size_in_4_byte_units; }

uint Compile::out_preserve_stack_slots() { return SharedRuntime::out_preserve_stack_slots(); }

uint Compile::varargs_C_out_slots_killed() const { return ((frame::z_abi_160_size - frame::z_jit_out_preserve_size) / VMRegImpl::stack_slot_size); }

void Matcher::calling_convention(BasicType *sig_bt, VMRegPair *regs, uint length, bool is_outgoing) {

#line 2470 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    // No difference between ingoing/outgoing just pass false.
    SharedRuntime::java_calling_convention(sig_bt, regs, length, false);
  
#line 22979 "ad_s390.cpp"

}

void Matcher::c_calling_convention(BasicType *sig_bt, VMRegPair *regs, uint length) {

#line 2481 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    // This is obviously always outgoing.
    // C argument must be in register AND stack slot.
    (void) SharedRuntime::c_calling_convention(sig_bt, regs, /*regs2=*/NULL, length);
  
#line 22991 "ad_s390.cpp"

}

OptoRegPair Matcher::return_value(uint ideal_reg, bool is_outgoing) {

#line 2504 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(ideal_reg >= Op_RegI && ideal_reg <= Op_RegL, "only return normal values");
    static int typeToRegLo[Op_RegL+1] = { 0, 0, Z_R2_num, Z_R2_num, Z_R2_num, Z_F0_num, Z_F0_num, Z_R2_num };
    static int typeToRegHi[Op_RegL+1] = { 0, 0, OptoReg::Bad, OptoReg::Bad, Z_R2_H_num, OptoReg::Bad, Z_F0_H_num, Z_R2_H_num };
    return OptoRegPair(typeToRegHi[ideal_reg], typeToRegLo[ideal_reg]);
  
#line 23004 "ad_s390.cpp"

}

OptoRegPair Matcher::c_return_value(uint ideal_reg, bool is_outgoing) {

#line 2495 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"

    assert(ideal_reg >= Op_RegI && ideal_reg <= Op_RegL, "only return normal values");
    static int typeToRegLo[Op_RegL+1] = { 0, 0, Z_R2_num, Z_R2_num, Z_R2_num, Z_F0_num, Z_F0_num, Z_R2_num };
    static int typeToRegHi[Op_RegL+1] = { 0, 0, OptoReg::Bad, OptoReg::Bad, Z_R2_H_num, OptoReg::Bad, Z_F0_H_num, Z_R2_H_num };
    return OptoRegPair(typeToRegHi[ideal_reg], typeToRegLo[ideal_reg]);
  
#line 23017 "ad_s390.cpp"

}

OptoReg::Name Matcher::inline_cache_reg() { return OptoReg::Name(Z_R9_num); }

int Matcher::inline_cache_reg_encode() { return _regEncode[inline_cache_reg()]; }

OptoReg::Name Matcher::interpreter_method_oop_reg() { return OptoReg::Name(Z_R9_num); }

int Matcher::interpreter_method_oop_reg_encode() { return _regEncode[interpreter_method_oop_reg()]; }

OptoReg::Name Matcher::interpreter_frame_pointer_reg() { return OptoReg::Name(Z_R7_num); }

OptoReg::Name Matcher::c_frame_pointer() const { return OptoReg::Name(Z_R15_num); }

// Number of callee-save + always-save registers
int  Matcher::number_of_saved_registers() {
  return 0;
};

bool Compile::needs_clone_jvms() { return false; }

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
