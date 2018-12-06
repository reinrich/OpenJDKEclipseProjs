#line 1 "ad_ppc.cpp"
//
// Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
// Copyright (c) 2012, 2017 SAP SE. All rights reserved.
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
//

// Machine Generated File.  Do Not Edit!

#include "precompiled.hpp"
#include "adfiles/adGlobals_ppc.hpp"
#include "adfiles/ad_ppc.hpp"
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

#line 991 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"


// Should the Matcher clone shifts on addressing modes, expecting them
// to be subsumed into complex addressing expressions or compute them
// into registers?
bool Matcher::clone_address_expressions(AddPNode* m, Matcher::MStack& mstack, VectorSet& address_visited) {
  return clone_base_plus_offset_address(m, mstack, address_visited);
}

void Compile::reshape_address(AddPNode* addp) {
}

// Optimize load-acquire.
//
// Check if acquire is unnecessary due to following operation that does
// acquire anyways.
// Walk the pattern:
//
//      n: Load.acq
//           |
//      MemBarAcquire
//       |         |
//  Proj(ctrl)  Proj(mem)
//       |         |
//   MemBarRelease/Volatile
//
bool followed_by_acquire(const Node *load) {
  assert(load->is_Load(), "So far implemented only for loads.");

  // Find MemBarAcquire.
  const Node *mba = NULL;
  for (DUIterator_Fast imax, i = load->fast_outs(imax); i < imax; i++) {
    const Node *out = load->fast_out(i);
    if (out->Opcode() == Op_MemBarAcquire) {
      if (out->in(0) == load) continue; // Skip control edge, membar should be found via precedence edge.
      mba = out;
      break;
    }
  }
  if (!mba) return false;

  // Find following MemBar node.
  //
  // The following node must be reachable by control AND memory
  // edge to assure no other operations are in between the two nodes.
  //
  // So first get the Proj node, mem_proj, to use it to iterate forward.
  Node *mem_proj = NULL;
  for (DUIterator_Fast imax, i = mba->fast_outs(imax); i < imax; i++) {
    mem_proj = mba->fast_out(i);      // Runs out of bounds and asserts if Proj not found.
    assert(mem_proj->is_Proj(), "only projections here");
    ProjNode *proj = mem_proj->as_Proj();
    if (proj->_con == TypeFunc::Memory &&
        !Compile::current()->node_arena()->contains(mem_proj)) // Unmatched old-space only
      break;
  }
  assert(mem_proj->as_Proj()->_con == TypeFunc::Memory, "Graph broken");

  // Search MemBar behind Proj. If there are other memory operations
  // behind the Proj we lost.
  for (DUIterator_Fast jmax, j = mem_proj->fast_outs(jmax); j < jmax; j++) {
    Node *x = mem_proj->fast_out(j);
    // Proj might have an edge to a store or load node which precedes the membar.
    if (x->is_Mem()) return false;

    // On PPC64 release and volatile are implemented by an instruction
    // that also has acquire semantics. I.e. there is no need for an
    // acquire before these.
    int xop = x->Opcode();
    if (xop == Op_MemBarRelease || xop == Op_MemBarVolatile) {
      // Make sure we're not missing Call/Phi/MergeMem by checking
      // control edges. The control edge must directly lead back
      // to the MemBarAcquire
      Node *ctrl_proj = x->in(0);
      if (ctrl_proj->is_Proj() && ctrl_proj->in(0) == mba) {
        return true;
      }
    }
  }

  return false;
}

#define __ _masm.

// Tertiary op of a LoadP or StoreP encoding.
#define REGP_OP true

// ****************************************************************************

// REQUIRED FUNCTIONALITY

// !!!!! Special hack to get all type of calls to specify the byte offset
//       from the start of the call to the point where the return address
//       will point.

// PPC port: Removed use of lazy constant construct.

int MachCallStaticJavaNode::ret_addr_offset() {
  // It's only a single branch-and-link instruction.
  return 4;
}

int MachCallDynamicJavaNode::ret_addr_offset() {
  // Offset is 4 with postalloc expanded calls (bl is one instruction). We use
  // postalloc expanded calls if we use inline caches and do not update method data.
  if (UseInlineCaches)
    return 4;

  int vtable_index = this->_vtable_index;
  if (vtable_index < 0) {
    // Must be invalid_vtable_index, not nonvirtual_vtable_index.
    assert(vtable_index == Method::invalid_vtable_index, "correct sentinel value");
    return 12;
  } else {
    assert(!UseInlineCaches, "expect vtable calls only if not using ICs");
    return 24;
  }
}

int MachCallRuntimeNode::ret_addr_offset() {
#if defined(ABI_ELFv2)
  return 28;
#else
  return 40;
#endif
}

//=============================================================================

// condition code conversions

static int cc_to_boint(int cc) {
  return Assembler::bcondCRbiIs0 | (cc & 8);
}

static int cc_to_inverse_boint(int cc) {
  return Assembler::bcondCRbiIs0 | (8-(cc & 8));
}

static int cc_to_biint(int cc, int flags_reg) {
  return (flags_reg << 2) | (cc & 3);
}

//=============================================================================

// Compute padding required for nodes which need alignment. The padding
// is the number of bytes (not instructions) which will be inserted before
// the instruction. The padding must match the size of a NOP instruction.

// Currently not used on this platform.

//=============================================================================

// Indicate if the safepoint node needs the polling page as an input.
bool SafePointNode::needs_polling_address_input() {
  // The address is loaded from thread by a seperate node.
  return true;
}

//=============================================================================

// Emit an interrupt that is caught by the debugger (for debugging compiler).
void emit_break(CodeBuffer &cbuf) {
  MacroAssembler _masm(&cbuf);
  __ illtrap();
}

#ifndef PRODUCT
void MachBreakpointNode::format(PhaseRegAlloc *ra_, outputStream *st) const {
  st->print("BREAKPOINT");
}
#endif

void MachBreakpointNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  emit_break(cbuf);
}

uint MachBreakpointNode::size(PhaseRegAlloc *ra_) const {
  return MachNode::size(ra_);
}

//=============================================================================

void emit_nop(CodeBuffer &cbuf) {
  MacroAssembler _masm(&cbuf);
  __ nop();
}

static inline void emit_long(CodeBuffer &cbuf, int value) {
  *((int*)(cbuf.insts_end())) = value;
  cbuf.set_insts_end(cbuf.insts_end() + BytesPerInstWord);
}

//=============================================================================


#line 255 "ad_ppc.cpp"


//SourceForm

#line 1218 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"


// Emit a trampoline stub for a call to a target which is too far away.
//
// code sequences:
//
// call-site:
//   branch-and-link to <destination> or <trampoline stub>
//
// Related trampoline stub for this call-site in the stub section:
//   load the call target from the constant pool
//   branch via CTR (LR/link still points to the call-site above)

void CallStubImpl::emit_trampoline_stub(MacroAssembler &_masm, int destination_toc_offset, int insts_call_instruction_offset) {
  address stub = __ emit_trampoline_stub(destination_toc_offset, insts_call_instruction_offset);
  if (stub == NULL) {
    ciEnv::current()->record_out_of_memory_failure();
  }
}

//=============================================================================

// Emit an inline branch-and-link call and a related trampoline stub.
//
// code sequences:
//
// call-site:
//   branch-and-link to <destination> or <trampoline stub>
//
// Related trampoline stub for this call-site in the stub section:
//   load the call target from the constant pool
//   branch via CTR (LR/link still points to the call-site above)
//

typedef struct {
  int insts_call_instruction_offset;
  int ret_addr_offset;
} EmitCallOffsets;

// Emit a branch-and-link instruction that branches to a trampoline.
// - Remember the offset of the branch-and-link instruction.
// - Add a relocation at the branch-and-link instruction.
// - Emit a branch-and-link.
// - Remember the return pc offset.
EmitCallOffsets emit_call_with_trampoline_stub(MacroAssembler &_masm, address entry_point, relocInfo::relocType rtype) {
  EmitCallOffsets offsets = { -1, -1 };
  const int start_offset = __ offset();
  offsets.insts_call_instruction_offset = __ offset();

  // No entry point given, use the current pc.
  if (entry_point == NULL) entry_point = __ pc();

  // Put the entry point as a constant into the constant pool.
  const address entry_point_toc_addr   = __ address_constant(entry_point, RelocationHolder::none);
  if (entry_point_toc_addr == NULL) {
    ciEnv::current()->record_out_of_memory_failure();
    return offsets;
  }
  const int     entry_point_toc_offset = __ offset_to_method_toc(entry_point_toc_addr);

  // Emit the trampoline stub which will be related to the branch-and-link below.
  CallStubImpl::emit_trampoline_stub(_masm, entry_point_toc_offset, offsets.insts_call_instruction_offset);
  if (ciEnv::current()->failing()) { return offsets; } // Code cache may be full.
  __ relocate(rtype);

  // Note: At this point we do not have the address of the trampoline
  // stub, and the entry point might be too far away for bl, so __ pc()
  // serves as dummy and the bl will be patched later.
  __ bl((address) __ pc());

  offsets.ret_addr_offset = __ offset() - start_offset;

  return offsets;
}

//=============================================================================

// Factory for creating loadConL* nodes for large/small constant pool.

static inline jlong replicate_immF(float con) {
  // Replicate float con 2 times and pack into vector.
  int val = *((int*)&con);
  jlong lval = val;
  lval = (lval << 32) | (lval & 0xFFFFFFFFl);
  return lval;
}

//=============================================================================

const RegMask& MachConstantBaseNode::_out_RegMask = BITS64_CONSTANT_TABLE_BASE_mask();
int Compile::ConstantTable::calculate_table_base_offset() const {
  return 0;  // absolute addressing, no offset
}

bool MachConstantBaseNode::requires_postalloc_expand() const { return true; }
void MachConstantBaseNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  iRegPdstOper *op_dst = new iRegPdstOper();
  MachNode *m1 = new loadToc_hiNode();
  MachNode *m2 = new loadToc_loNode();

  m1->add_req(NULL);
  m2->add_req(NULL, m1);
  m1->_opnds[0] = op_dst;
  m2->_opnds[0] = op_dst;
  m2->_opnds[1] = op_dst;
  ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
  ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
  nodes->push(m1);
  nodes->push(m2);
}

void MachConstantBaseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  // Is postalloc expanded.
  ShouldNotReachHere();
}

uint MachConstantBaseNode::size(PhaseRegAlloc* ra_) const {
  return 0;
}

#ifndef PRODUCT
void MachConstantBaseNode::format(PhaseRegAlloc* ra_, outputStream* st) const {
  st->print("-- \t// MachConstantBaseNode (empty encoding)");
}
#endif

//=============================================================================

#ifndef PRODUCT
void MachPrologNode::format(PhaseRegAlloc *ra_, outputStream *st) const {
  Compile* C = ra_->C;
  const long framesize = C->frame_slots() << LogBytesPerInt;

  st->print("PROLOG\n\t");
  if (C->need_stack_bang(framesize)) {
    st->print("stack_overflow_check\n\t");
  }

  if (!false /* TODO: PPC port C->is_frameless_method()*/) {
    st->print("save return pc\n\t");
    st->print("push frame %ld\n\t", -framesize);
  }
}
#endif

// Macro used instead of the common __ to emulate the pipes of PPC.
// Instead of e.g. __ ld(...) one hase to write ___(ld) ld(...) This enables the
// micro scheduler to cope with "hand written" assembler like in the prolog. Though
// still no scheduling of this code is possible, the micro scheduler is aware of the
// code and can update its internal data. The following mechanism is used to achieve this:
// The micro scheduler calls size() of each compound node during scheduling. size() does a
// dummy emit and only during this dummy emit C->hb_scheduling() is not NULL.
#if 0 // TODO: PPC port
#define ___(op) if (UsePower6SchedulerPPC64 && C->hb_scheduling())                    \
                  C->hb_scheduling()->_pdScheduling->PdEmulatePipe(ppc64Opcode_##op); \
                _masm.
#define ___stop if (UsePower6SchedulerPPC64 && C->hb_scheduling())                    \
                  C->hb_scheduling()->_pdScheduling->PdEmulatePipe(archOpcode_none)
#define ___advance if (UsePower6SchedulerPPC64 && C->hb_scheduling())                 \
                  C->hb_scheduling()->_pdScheduling->advance_offset
#else
#define ___(op) if (UsePower6SchedulerPPC64)                                          \
                  Unimplemented();                                                    \
                _masm.
#define ___stop if (UsePower6SchedulerPPC64)                                          \
                  Unimplemented()
#define ___advance if (UsePower6SchedulerPPC64)                                       \
                  Unimplemented()
#endif

void MachPrologNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  Compile* C = ra_->C;
  MacroAssembler _masm(&cbuf);

  const long framesize = C->frame_size_in_bytes();
  assert(framesize % (2 * wordSize) == 0, "must preserve 2*wordSize alignment");

  const bool method_is_frameless      = false /* TODO: PPC port C->is_frameless_method()*/;

  const Register return_pc            = R20; // Must match return_addr() in frame section.
  const Register callers_sp           = R21;
  const Register push_frame_temp      = R22;
  const Register toc_temp             = R23;
  assert_different_registers(R11, return_pc, callers_sp, push_frame_temp, toc_temp);

  if (method_is_frameless) {
    // Add nop at beginning of all frameless methods to prevent any
    // oop instructions from getting overwritten by make_not_entrant
    // (patching attempt would fail).
    ___(nop) nop();
  } else {
    // Get return pc.
    ___(mflr) mflr(return_pc);
  }

  // Calls to C2R adapters often do not accept exceptional returns.
  // We require that their callers must bang for them. But be
  // careful, because some VM calls (such as call site linkage) can
  // use several kilobytes of stack. But the stack safety zone should
  // account for that. See bugs 4446381, 4468289, 4497237.

  int bangsize = C->bang_size_in_bytes();
  assert(bangsize >= framesize || bangsize <= 0, "stack bang size incorrect");
  if (C->need_stack_bang(bangsize) && UseStackBanging) {
    // Unfortunately we cannot use the function provided in
    // assembler.cpp as we have to emulate the pipes. So I had to
    // insert the code of generate_stack_overflow_check(), see
    // assembler.cpp for some illuminative comments.
    const int page_size = os::vm_page_size();
    int bang_end = JavaThread::stack_shadow_zone_size();

    // This is how far the previous frame's stack banging extended.
    const int bang_end_safe = bang_end;

    if (bangsize > page_size) {
      bang_end += bangsize;
    }

    int bang_offset = bang_end_safe;

    while (bang_offset <= bang_end) {
      // Need at least one stack bang at end of shadow zone.

      // Again I had to copy code, this time from assembler_ppc.cpp,
      // bang_stack_with_offset - see there for comments.

      // Stack grows down, caller passes positive offset.
      assert(bang_offset > 0, "must bang with positive offset");

      long stdoffset = -bang_offset;

      if (Assembler::is_simm(stdoffset, 16)) {
        // Signed 16 bit offset, a simple std is ok.
        if (UseLoadInstructionsForStackBangingPPC64) {
          ___(ld) ld(R0,  (int)(signed short)stdoffset, R1_SP);
        } else {
          ___(std) std(R0, (int)(signed short)stdoffset, R1_SP);
        }
      } else if (Assembler::is_simm(stdoffset, 31)) {
        // Use largeoffset calculations for addis & ld/std.
        const int hi = MacroAssembler::largeoffset_si16_si16_hi(stdoffset);
        const int lo = MacroAssembler::largeoffset_si16_si16_lo(stdoffset);

        Register tmp = R11;
        ___(addis) addis(tmp, R1_SP, hi);
        if (UseLoadInstructionsForStackBangingPPC64) {
          ___(ld) ld(R0, lo, tmp);
        } else {
          ___(std) std(R0, lo, tmp);
        }
      } else {
        ShouldNotReachHere();
      }

      bang_offset += page_size;
    }
    // R11 trashed
  } // C->need_stack_bang(framesize) && UseStackBanging

  unsigned int bytes = (unsigned int)framesize;
  long offset = Assembler::align_addr(bytes, frame::alignment_in_bytes);
  ciMethod *currMethod = C->method();

  // Optimized version for most common case.
  if (UsePower6SchedulerPPC64 &&
      !method_is_frameless && Assembler::is_simm((int)(-offset), 16) &&
      !(false /* ConstantsALot TODO: PPC port*/)) {
    ___(or) mr(callers_sp, R1_SP);
    ___(std) std(return_pc, _abi(lr), R1_SP);
    ___(stdu) stdu(R1_SP, -offset, R1_SP);
    return;
  }

  if (!method_is_frameless) {
    // Get callers sp.
    ___(or) mr(callers_sp, R1_SP);

    // Push method's frame, modifies SP.
    assert(Assembler::is_uimm(framesize, 32U), "wrong type");
    // The ABI is already accounted for in 'framesize' via the
    // 'out_preserve' area.
    Register tmp = push_frame_temp;
    // Had to insert code of push_frame((unsigned int)framesize, push_frame_temp).
    if (Assembler::is_simm(-offset, 16)) {
      ___(stdu) stdu(R1_SP, -offset, R1_SP);
    } else {
      long x = -offset;
      // Had to insert load_const(tmp, -offset).
      ___(addis)  lis( tmp, (int)((signed short)(((x >> 32) & 0xffff0000) >> 16)));
      ___(ori)    ori( tmp, tmp, ((x >> 32) & 0x0000ffff));
      ___(rldicr) sldi(tmp, tmp, 32);
      ___(oris)   oris(tmp, tmp, (x & 0xffff0000) >> 16);
      ___(ori)    ori( tmp, tmp, (x & 0x0000ffff));

      ___(stdux) stdux(R1_SP, R1_SP, tmp);
    }
  }
#if 0 // TODO: PPC port
  // For testing large constant pools, emit a lot of constants to constant pool.
  // "Randomize" const_size.
  if (ConstantsALot) {
    const int num_consts = const_size();
    for (int i = 0; i < num_consts; i++) {
      __ long_constant(0xB0B5B00BBABE);
    }
  }
#endif
  if (!method_is_frameless) {
    // Save return pc.
    ___(std) std(return_pc, _abi(lr), callers_sp);
  }

  C->set_frame_complete(cbuf.insts_size());
}
#undef ___
#undef ___stop
#undef ___advance

uint MachPrologNode::size(PhaseRegAlloc *ra_) const {
  // Variable size. determine dynamically.
  return MachNode::size(ra_);
}

int MachPrologNode::reloc() const {
  // Return number of relocatable values contained in this instruction.
  return 1; // 1 reloc entry for load_const(toc).
}

//=============================================================================

#ifndef PRODUCT
void MachEpilogNode::format(PhaseRegAlloc *ra_, outputStream *st) const {
  Compile* C = ra_->C;

  st->print("EPILOG\n\t");
  st->print("restore return pc\n\t");
  st->print("pop frame\n\t");

  if (do_polling() && C->is_method_compilation()) {
    st->print("touch polling page\n\t");
  }
}
#endif

void MachEpilogNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  Compile* C = ra_->C;
  MacroAssembler _masm(&cbuf);

  const long framesize = ((long)C->frame_slots()) << LogBytesPerInt;
  assert(framesize >= 0, "negative frame-size?");

  const bool method_needs_polling = do_polling() && C->is_method_compilation();
  const bool method_is_frameless  = false /* TODO: PPC port C->is_frameless_method()*/;
  const Register return_pc        = R31;  // Must survive C-call to enable_stack_reserved_zone().
  const Register polling_page     = R12;

  if (!method_is_frameless) {
    // Restore return pc relative to callers' sp.
    __ ld(return_pc, ((int)framesize) + _abi(lr), R1_SP);
  }

  if (method_needs_polling) {
    if (SafepointMechanism::uses_thread_local_poll()) {
      __ ld(polling_page, in_bytes(JavaThread::polling_page_offset()), R16_thread);
    } else {
      __ load_const_optimized(polling_page, (long)(address) os::get_polling_page());
    }
  }

  if (!method_is_frameless) {
    // Move return pc to LR.
    __ mtlr(return_pc);
    // Pop frame (fixed frame-size).
    __ addi(R1_SP, R1_SP, (int)framesize);
  }

  if (StackReservedPages > 0 && C->has_reserved_stack_access()) {
    __ reserved_stack_check(return_pc);
  }

  if (method_needs_polling) {
    // We need to mark the code position where the load from the safepoint
    // polling page was emitted as relocInfo::poll_return_type here.
    __ relocate(relocInfo::poll_return_type);
    __ load_from_polling_page(polling_page);
  }
}

uint MachEpilogNode::size(PhaseRegAlloc *ra_) const {
  // Variable size. Determine dynamically.
  return MachNode::size(ra_);
}

int MachEpilogNode::reloc() const {
  // Return number of relocatable values contained in this instruction.
  return 1; // 1 for load_from_polling_page.
}

const Pipeline * MachEpilogNode::pipeline() const {
  return MachNode::pipeline_class();
}

// This method seems to be obsolete. It is declared in machnode.hpp
// and defined in all *.ad files, but it is never called. Should we
// get rid of it?
int MachEpilogNode::safepoint_offset() const {
  assert(do_polling(), "no return for this epilog node");
  return 0;
}

#if 0 // TODO: PPC port
void MachLoadPollAddrLateNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  MacroAssembler _masm(&cbuf);
  if (LoadPollAddressFromThread) {
    _masm.ld(R11, in_bytes(JavaThread::poll_address_offset()), R16_thread);
  } else {
    _masm.nop();
  }
}

uint MachLoadPollAddrLateNode::size(PhaseRegAlloc* ra_) const {
  if (LoadPollAddressFromThread) {
    return 4;
  } else {
    return 4;
  }
}

#ifndef PRODUCT
void MachLoadPollAddrLateNode::format(PhaseRegAlloc* ra_, outputStream* st) const {
  st->print_cr(" LD R11, PollAddressOffset, R16_thread \t// LoadPollAddressFromThread");
}
#endif

const RegMask &MachLoadPollAddrLateNode::out_RegMask() const {
  return RSCRATCH1_BITS64_REG_mask();
}
#endif // PPC port

// =============================================================================

// Figure out which register class each belongs in: rc_int, rc_float, rc_vs or
// rc_stack.
enum RC { rc_bad, rc_int, rc_float, rc_vs, rc_stack };

static enum RC rc_class(OptoReg::Name reg) {
  // Return the register class for the given register. The given register
  // reg is a <register>_num value, which is an index into the MachRegisterNumbers
  // enumeration in adGlobals_ppc.hpp.

  if (reg == OptoReg::Bad) return rc_bad;

  // We have 64 integer register halves, starting at index 0.
  if (reg < 64) return rc_int;

  // We have 64 floating-point register halves, starting at index 64.
  if (reg < 64+64) return rc_float;

  // We have 64 vector-scalar registers, starting at index 128.
  if (reg < 64+64+64) return rc_vs;

  // Between float regs & stack are the flags regs.
  assert(OptoReg::is_stack(reg) || reg < 64+64+64, "blow up if spilling flags");

  return rc_stack;
}

static int ld_st_helper(CodeBuffer *cbuf, const char *op_str, uint opcode, int reg, int offset,
                        bool do_print, Compile* C, outputStream *st) {

  assert(opcode == Assembler::LD_OPCODE   ||
         opcode == Assembler::STD_OPCODE  ||
         opcode == Assembler::LWZ_OPCODE  ||
         opcode == Assembler::STW_OPCODE  ||
         opcode == Assembler::LFD_OPCODE  ||
         opcode == Assembler::STFD_OPCODE ||
         opcode == Assembler::LFS_OPCODE  ||
         opcode == Assembler::STFS_OPCODE,
         "opcode not supported");

  if (cbuf) {
    int d =
      (Assembler::LD_OPCODE == opcode || Assembler::STD_OPCODE == opcode) ?
        Assembler::ds(offset+0 /* TODO: PPC port C->frame_slots_sp_bias_in_bytes()*/)
      : Assembler::d1(offset+0 /* TODO: PPC port C->frame_slots_sp_bias_in_bytes()*/); // Makes no difference in opt build.
    emit_long(*cbuf, opcode | Assembler::rt(Matcher::_regEncode[reg]) | d | Assembler::ra(R1_SP));
  }
#ifndef PRODUCT
  else if (do_print) {
    st->print("%-7s %s, [R1_SP + #%d+%d] \t// spill copy",
              op_str,
              Matcher::regName[reg],
              offset, 0 /* TODO: PPC port C->frame_slots_sp_bias_in_bytes()*/);
  }
#endif
  return 4; // size
}

uint MachSpillCopyNode::implementation(CodeBuffer *cbuf, PhaseRegAlloc *ra_, bool do_size, outputStream *st) const {
  Compile* C = ra_->C;

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
  if (src_hi != OptoReg::Bad)
    assert((src_lo&1)==0 && src_lo+1==src_hi &&
           (dst_lo&1)==0 && dst_lo+1==dst_hi,
           "expected aligned-adjacent pairs");
  // Generate spill code!
  int size = 0;

  if (src_lo == dst_lo && src_hi == dst_hi)
    return size;            // Self copy, no move.

  if (bottom_type()->isa_vect() != NULL && ideal_reg() == Op_VecX) {
    // Memory->Memory Spill.
    if (src_lo_rc == rc_stack && dst_lo_rc == rc_stack) {
      int src_offset = ra_->reg2offset(src_lo);
      int dst_offset = ra_->reg2offset(dst_lo);
      if (cbuf) {
        MacroAssembler _masm(cbuf);
        __ ld(R0, src_offset, R1_SP);
        __ std(R0, dst_offset, R1_SP);
        __ ld(R0, src_offset+8, R1_SP);
        __ std(R0, dst_offset+8, R1_SP);
      }
      size += 16;
    }
    // VectorSRegister->Memory Spill.
    else if (src_lo_rc == rc_vs && dst_lo_rc == rc_stack) {
      VectorSRegister Rsrc = as_VectorSRegister(Matcher::_regEncode[src_lo]);
      int dst_offset = ra_->reg2offset(dst_lo);
      if (cbuf) {
        MacroAssembler _masm(cbuf);
        __ addi(R0, R1_SP, dst_offset);
        __ stxvd2x(Rsrc, R0);
      }
      size += 8;
    }
    // Memory->VectorSRegister Spill.
    else if (src_lo_rc == rc_stack && dst_lo_rc == rc_vs) {
      VectorSRegister Rdst = as_VectorSRegister(Matcher::_regEncode[dst_lo]);
      int src_offset = ra_->reg2offset(src_lo);
      if (cbuf) {
        MacroAssembler _masm(cbuf);
        __ addi(R0, R1_SP, src_offset);
        __ lxvd2x(Rdst, R0);
      }
      size += 8;
    }
    // VectorSRegister->VectorSRegister.
    else if (src_lo_rc == rc_vs && dst_lo_rc == rc_vs) {
      VectorSRegister Rsrc = as_VectorSRegister(Matcher::_regEncode[src_lo]);
      VectorSRegister Rdst = as_VectorSRegister(Matcher::_regEncode[dst_lo]);
      if (cbuf) {
        MacroAssembler _masm(cbuf);
        __ xxlor(Rdst, Rsrc, Rsrc);
      }
      size += 4;
    }
    else {
      ShouldNotReachHere(); // No VSR spill.
    }
    return size;
  }

  // --------------------------------------
  // Memory->Memory Spill. Use R0 to hold the value.
  if (src_lo_rc == rc_stack && dst_lo_rc == rc_stack) {
    int src_offset = ra_->reg2offset(src_lo);
    int dst_offset = ra_->reg2offset(dst_lo);
    if (src_hi != OptoReg::Bad) {
      assert(src_hi_rc==rc_stack && dst_hi_rc==rc_stack,
             "expected same type of move for high parts");
      size += ld_st_helper(cbuf, "LD  ", Assembler::LD_OPCODE,  R0_num, src_offset, !do_size, C, st);
      if (!cbuf && !do_size) st->print("\n\t");
      size += ld_st_helper(cbuf, "STD ", Assembler::STD_OPCODE, R0_num, dst_offset, !do_size, C, st);
    } else {
      size += ld_st_helper(cbuf, "LWZ ", Assembler::LWZ_OPCODE, R0_num, src_offset, !do_size, C, st);
      if (!cbuf && !do_size) st->print("\n\t");
      size += ld_st_helper(cbuf, "STW ", Assembler::STW_OPCODE, R0_num, dst_offset, !do_size, C, st);
    }
    return size;
  }

  // --------------------------------------
  // Check for float->int copy; requires a trip through memory.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_int) {
    Unimplemented();
  }

  // --------------------------------------
  // Check for integer reg-reg copy.
  if (src_lo_rc == rc_int && dst_lo_rc == rc_int) {
      Register Rsrc = as_Register(Matcher::_regEncode[src_lo]);
      Register Rdst = as_Register(Matcher::_regEncode[dst_lo]);
      size = (Rsrc != Rdst) ? 4 : 0;

      if (cbuf) {
        MacroAssembler _masm(cbuf);
        if (size) {
          __ mr(Rdst, Rsrc);
        }
      }
#ifndef PRODUCT
      else if (!do_size) {
        if (size) {
          st->print("%-7s %s, %s \t// spill copy", "MR", Matcher::regName[dst_lo], Matcher::regName[src_lo]);
        } else {
          st->print("%-7s %s, %s \t// spill copy", "MR-NOP", Matcher::regName[dst_lo], Matcher::regName[src_lo]);
        }
      }
#endif
      return size;
  }

  // Check for integer store.
  if (src_lo_rc == rc_int && dst_lo_rc == rc_stack) {
    int dst_offset = ra_->reg2offset(dst_lo);
    if (src_hi != OptoReg::Bad) {
      assert(src_hi_rc==rc_int && dst_hi_rc==rc_stack,
             "expected same type of move for high parts");
      size += ld_st_helper(cbuf, "STD ", Assembler::STD_OPCODE, src_lo, dst_offset, !do_size, C, st);
    } else {
      size += ld_st_helper(cbuf, "STW ", Assembler::STW_OPCODE, src_lo, dst_offset, !do_size, C, st);
    }
    return size;
  }

  // Check for integer load.
  if (dst_lo_rc == rc_int && src_lo_rc == rc_stack) {
    int src_offset = ra_->reg2offset(src_lo);
    if (src_hi != OptoReg::Bad) {
      assert(dst_hi_rc==rc_int && src_hi_rc==rc_stack,
             "expected same type of move for high parts");
      size += ld_st_helper(cbuf, "LD  ", Assembler::LD_OPCODE, dst_lo, src_offset, !do_size, C, st);
    } else {
      size += ld_st_helper(cbuf, "LWZ ", Assembler::LWZ_OPCODE, dst_lo, src_offset, !do_size, C, st);
    }
    return size;
  }

  // Check for float reg-reg copy.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_float) {
    if (cbuf) {
      MacroAssembler _masm(cbuf);
      FloatRegister Rsrc = as_FloatRegister(Matcher::_regEncode[src_lo]);
      FloatRegister Rdst = as_FloatRegister(Matcher::_regEncode[dst_lo]);
      __ fmr(Rdst, Rsrc);
    }
#ifndef PRODUCT
    else if (!do_size) {
      st->print("%-7s %s, %s \t// spill copy", "FMR", Matcher::regName[dst_lo], Matcher::regName[src_lo]);
    }
#endif
    return 4;
  }

  // Check for float store.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_stack) {
    int dst_offset = ra_->reg2offset(dst_lo);
    if (src_hi != OptoReg::Bad) {
      assert(src_hi_rc==rc_float && dst_hi_rc==rc_stack,
             "expected same type of move for high parts");
      size += ld_st_helper(cbuf, "STFD", Assembler::STFD_OPCODE, src_lo, dst_offset, !do_size, C, st);
    } else {
      size += ld_st_helper(cbuf, "STFS", Assembler::STFS_OPCODE, src_lo, dst_offset, !do_size, C, st);
    }
    return size;
  }

  // Check for float load.
  if (dst_lo_rc == rc_float && src_lo_rc == rc_stack) {
    int src_offset = ra_->reg2offset(src_lo);
    if (src_hi != OptoReg::Bad) {
      assert(dst_hi_rc==rc_float && src_hi_rc==rc_stack,
             "expected same type of move for high parts");
      size += ld_st_helper(cbuf, "LFD ", Assembler::LFD_OPCODE, dst_lo, src_offset, !do_size, C, st);
    } else {
      size += ld_st_helper(cbuf, "LFS ", Assembler::LFS_OPCODE, dst_lo, src_offset, !do_size, C, st);
    }
    return size;
  }

  // --------------------------------------------------------------------
  // Check for hi bits still needing moving. Only happens for misaligned
  // arguments to native calls.
  if (src_hi == dst_hi)
    return size;               // Self copy; no move.

  assert(src_hi_rc != rc_bad && dst_hi_rc != rc_bad, "src_hi & dst_hi cannot be Bad");
  ShouldNotReachHere(); // Unimplemented
  return 0;
}

#ifndef PRODUCT
void MachSpillCopyNode::format(PhaseRegAlloc *ra_, outputStream *st) const {
  if (!ra_)
    st->print("N%d = SpillCopy(N%d)", _idx, in(1)->_idx);
  else
    implementation(NULL, ra_, false, st);
}
#endif

void MachSpillCopyNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  implementation(&cbuf, ra_, false, NULL);
}

uint MachSpillCopyNode::size(PhaseRegAlloc *ra_) const {
  return implementation(NULL, ra_, true, NULL);
}

#if 0 // TODO: PPC port
ArchOpcode MachSpillCopyNode_archOpcode(MachSpillCopyNode *n, PhaseRegAlloc *ra_) {
#ifndef PRODUCT
  if (ra_->node_regs_max_index() == 0) return archOpcode_undefined;
#endif
  assert(ra_->node_regs_max_index() != 0, "");

  // Get registers to move.
  OptoReg::Name src_hi = ra_->get_reg_second(n->in(1));
  OptoReg::Name src_lo = ra_->get_reg_first(n->in(1));
  OptoReg::Name dst_hi = ra_->get_reg_second(n);
  OptoReg::Name dst_lo = ra_->get_reg_first(n);

  enum RC src_lo_rc = rc_class(src_lo);
  enum RC dst_lo_rc = rc_class(dst_lo);

  if (src_lo == dst_lo && src_hi == dst_hi)
    return ppc64Opcode_none;            // Self copy, no move.

  // --------------------------------------
  // Memory->Memory Spill. Use R0 to hold the value.
  if (src_lo_rc == rc_stack && dst_lo_rc == rc_stack) {
    return ppc64Opcode_compound;
  }

  // --------------------------------------
  // Check for float->int copy; requires a trip through memory.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_int) {
    Unimplemented();
  }

  // --------------------------------------
  // Check for integer reg-reg copy.
  if (src_lo_rc == rc_int && dst_lo_rc == rc_int) {
    Register Rsrc = as_Register(Matcher::_regEncode[src_lo]);
    Register Rdst = as_Register(Matcher::_regEncode[dst_lo]);
    if (Rsrc == Rdst) {
      return ppc64Opcode_none;
    } else {
      return ppc64Opcode_or;
    }
  }

  // Check for integer store.
  if (src_lo_rc == rc_int && dst_lo_rc == rc_stack) {
    if (src_hi != OptoReg::Bad) {
      return ppc64Opcode_std;
    } else {
      return ppc64Opcode_stw;
    }
  }

  // Check for integer load.
  if (dst_lo_rc == rc_int && src_lo_rc == rc_stack) {
    if (src_hi != OptoReg::Bad) {
      return ppc64Opcode_ld;
    } else {
      return ppc64Opcode_lwz;
    }
  }

  // Check for float reg-reg copy.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_float) {
    return ppc64Opcode_fmr;
  }

  // Check for float store.
  if (src_lo_rc == rc_float && dst_lo_rc == rc_stack) {
    if (src_hi != OptoReg::Bad) {
      return ppc64Opcode_stfd;
    } else {
      return ppc64Opcode_stfs;
    }
  }

  // Check for float load.
  if (dst_lo_rc == rc_float && src_lo_rc == rc_stack) {
    if (src_hi != OptoReg::Bad) {
      return ppc64Opcode_lfd;
    } else {
      return ppc64Opcode_lfs;
    }
  }

  // --------------------------------------------------------------------
  // Check for hi bits still needing moving. Only happens for misaligned
  // arguments to native calls.
  if (src_hi == dst_hi) {
    return ppc64Opcode_none;               // Self copy; no move.
  }

  ShouldNotReachHere();
  return ppc64Opcode_undefined;
}
#endif // PPC port

#ifndef PRODUCT
void MachNopNode::format(PhaseRegAlloc *ra_, outputStream *st) const {
  st->print("NOP \t// %d nops to pad for loops.", _count);
}
#endif

void MachNopNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *) const {
  MacroAssembler _masm(&cbuf);
  // _count contains the number of nops needed for padding.
  for (int i = 0; i < _count; i++) {
    __ nop();
  }
}

uint MachNopNode::size(PhaseRegAlloc *ra_) const {
  return _count * 4;
}

#ifndef PRODUCT
void BoxLockNode::format(PhaseRegAlloc *ra_, outputStream *st) const {
  int offset = ra_->reg2offset(in_RegMask(0).find_first_elem());
  char reg_str[128];
  ra_->dump_register(this, reg_str);
  st->print("ADDI    %s, SP, %d \t// box node", reg_str, offset);
}
#endif

void BoxLockNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  MacroAssembler _masm(&cbuf);

  int offset = ra_->reg2offset(in_RegMask(0).find_first_elem());
  int reg    = ra_->get_encode(this);

  if (Assembler::is_simm(offset, 16)) {
    __ addi(as_Register(reg), R1, offset);
  } else {
    ShouldNotReachHere();
  }
}

uint BoxLockNode::size(PhaseRegAlloc *ra_) const {
  // BoxLockNode is not a MachNode, so we can't just call MachNode::size(ra_).
  return 4;
}

#ifndef PRODUCT
void MachUEPNode::format(PhaseRegAlloc *ra_, outputStream *st) const {
  st->print_cr("---- MachUEPNode ----");
  st->print_cr("...");
}
#endif

void MachUEPNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  // This is the unverified entry point.
  MacroAssembler _masm(&cbuf);

  // Inline_cache contains a klass.
  Register ic_klass       = as_Register(Matcher::inline_cache_reg_encode());
  Register receiver_klass = R12_scratch2;  // tmp

  assert_different_registers(ic_klass, receiver_klass, R11_scratch1, R3_ARG1);
  assert(R11_scratch1 == R11, "need prologue scratch register");

  // Check for NULL argument if we don't have implicit null checks.
  if (!ImplicitNullChecks || !os::zero_page_read_protected()) {
    if (TrapBasedNullChecks) {
      __ trap_null_check(R3_ARG1);
    } else {
      Label valid;
      __ cmpdi(CCR0, R3_ARG1, 0);
      __ bne_predict_taken(CCR0, valid);
      // We have a null argument, branch to ic_miss_stub.
      __ b64_patchable((address)SharedRuntime::get_ic_miss_stub(),
                           relocInfo::runtime_call_type);
      __ bind(valid);
    }
  }
  // Assume argument is not NULL, load klass from receiver.
  __ load_klass(receiver_klass, R3_ARG1);

  if (TrapBasedICMissChecks) {
    __ trap_ic_miss_check(receiver_klass, ic_klass);
  } else {
    Label valid;
    __ cmpd(CCR0, receiver_klass, ic_klass);
    __ beq_predict_taken(CCR0, valid);
    // We have an unexpected klass, branch to ic_miss_stub.
    __ b64_patchable((address)SharedRuntime::get_ic_miss_stub(),
                         relocInfo::runtime_call_type);
    __ bind(valid);
  }

  // Argument is valid and klass is as expected, continue.
}

#if 0 // TODO: PPC port
// Optimize UEP code on z (save a load_const() call in main path).
int MachUEPNode::ep_offset() {
  return 0;
}
#endif

uint MachUEPNode::size(PhaseRegAlloc *ra_) const {
  // Variable size. Determine dynamically.
  return MachNode::size(ra_);
}

//=============================================================================


#line 1188 "ad_ppc.cpp"


//SourceForm

#line 2169 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"


int HandlerImpl::emit_exception_handler(CodeBuffer &cbuf) {
  MacroAssembler _masm(&cbuf);

  address base = __ start_a_stub(size_exception_handler());
  if (base == NULL) return 0; // CodeBuffer::expand failed

  int offset = __ offset();
  __ b64_patchable((address)OptoRuntime::exception_blob()->content_begin(),
                       relocInfo::runtime_call_type);
  assert(__ offset() - offset == (int)size_exception_handler(), "must be fixed size");
  __ end_a_stub();

  return offset;
}

// The deopt_handler is like the exception handler, but it calls to
// the deoptimization blob instead of jumping to the exception blob.
int HandlerImpl::emit_deopt_handler(CodeBuffer& cbuf) {
  MacroAssembler _masm(&cbuf);

  address base = __ start_a_stub(size_deopt_handler());
  if (base == NULL) return 0; // CodeBuffer::expand failed

  int offset = __ offset();
  __ bl64_patchable((address)SharedRuntime::deopt_blob()->unpack(),
                        relocInfo::runtime_call_type);
  assert(__ offset() - offset == (int) size_deopt_handler(), "must be fixed size");
  __ end_a_stub();

  return offset;
}

//=============================================================================

// Use a frame slots bias for frameless methods if accessing the stack.
static int frame_slots_bias(int reg_enc, PhaseRegAlloc* ra_) {
  if (as_Register(reg_enc) == R1_SP) {
    return 0; // TODO: PPC port ra_->C->frame_slots_sp_bias_in_bytes();
  }
  return 0;
}

const bool Matcher::match_rule_supported(int opcode) {
  if (!has_match_rule(opcode))
    return false;

  switch (opcode) {
  case Op_SqrtD:
    return VM_Version::has_fsqrt();
  case Op_CountLeadingZerosI:
  case Op_CountLeadingZerosL:
  case Op_CountTrailingZerosI:
  case Op_CountTrailingZerosL:
    if (!UseCountLeadingZerosInstructionsPPC64)
      return false;
    break;

  case Op_PopCountI:
  case Op_PopCountL:
    return (UsePopCountInstruction && VM_Version::has_popcntw());

  case Op_StrComp:
    return SpecialStringCompareTo;
  case Op_StrEquals:
    return SpecialStringEquals;
  case Op_StrIndexOf:
    return SpecialStringIndexOf;
  case Op_StrIndexOfChar:
    return SpecialStringIndexOf;
  }

  return true;  // Per default match rules are supported.
}

const bool Matcher::match_rule_supported_vector(int opcode, int vlen) {

  // TODO
  // identify extra cases that we might want to provide match rules for
  // e.g. Op_ vector nodes and other intrinsics while guarding with vlen
  bool ret_value = match_rule_supported(opcode);
  // Add rules here.

  return ret_value;  // Per default match rules are supported.
}

const bool Matcher::has_predicated_vectors(void) {
  return false;
}

const int Matcher::float_pressure(int default_pressure_threshold) {
  return default_pressure_threshold;
}

int Matcher::regnum_to_fpu_offset(int regnum) {
  // No user for this method?
  Unimplemented();
  return 999;
}

const bool Matcher::convL2FSupported(void) {
  // fcfids can do the conversion (>= Power7).
  // fcfid + frsp showed rounding problem when result should be 0x3f800001.
  return VM_Version::has_fcfids(); // False means that conversion is done by runtime call.
}

// Vector width in bytes.
const int Matcher::vector_width_in_bytes(BasicType bt) {
  if (SuperwordUseVSX) {
    assert(MaxVectorSize == 16, "");
    return 16;
  } else {
    assert(MaxVectorSize == 8, "");
    return 8;
  }
}

// Vector ideal reg.
const uint Matcher::vector_ideal_reg(int size) {
  if (SuperwordUseVSX) {
    assert(MaxVectorSize == 16 && size == 16, "");
    return Op_VecX;
  } else {
    assert(MaxVectorSize == 8 && size == 8, "");
    return Op_RegL;
  }
}

const uint Matcher::vector_shift_count_ideal_reg(int size) {
  fatal("vector shift is not supported");
  return Node::NotAMachineReg;
}

// Limits on vector size (number of elements) loaded into vector.
const int Matcher::max_vector_size(const BasicType bt) {
  assert(is_java_primitive(bt), "only primitive type vectors");
  return vector_width_in_bytes(bt)/type2aelembytes(bt);
}

const int Matcher::min_vector_size(const BasicType bt) {
  return max_vector_size(bt); // Same as max.
}

// PPC doesn't support misaligned vectors store/load.
const bool Matcher::misaligned_vectors_ok() {
  return !AlignVector; // can be changed by flag
}

// PPC AES support not yet implemented
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
  // Is the offset within the range of a ppc64 pc relative branch?
  bool b;

  const int safety_zone = 3 * BytesPerInstWord;
  b = Assembler::is_simm((offset<0 ? offset-safety_zone : offset+safety_zone),
                         29 - 16 + 1 + 2);
  return b;
}

const bool Matcher::isSimpleConstant64(jlong value) {
  // Probably always true, even if a temp register is required.
  return true;
}
/* TODO: PPC port
// Make a new machine dependent decode node (with its operands).
MachTypeNode *Matcher::make_decode_node() {
  assert(Universe::narrow_oop_base() == NULL && Universe::narrow_oop_shift() == 0,
         "This method is only implemented for unscaled cOops mode so far");
  MachTypeNode *decode = new decodeN_unscaledNode();
  decode->set_opnd_array(0, new iRegPdstOper());
  decode->set_opnd_array(1, new iRegNsrcOper());
  return decode;
}
*/

// false => size gets scaled to BytesPerLong, ok.
const bool Matcher::init_array_count_is_in_bytes = false;

// Use conditional move (CMOVL) on Power7.
const int Matcher::long_cmove_cost() { return 0; } // this only makes long cmoves more expensive than int cmoves

// Suppress CMOVF. Conditional move available (sort of) on PPC64 only from P7 onwards. Not exploited yet.
// fsel doesn't accept a condition register as input, so this would be slightly different.
const int Matcher::float_cmove_cost() { return ConditionalMoveLimit; }

// Power6 requires postalloc expand (see block.cpp for description of postalloc expand).
const bool Matcher::require_postalloc_expand = true;

// Do we need to mask the count passed to shift instructions or does
// the cpu only look at the lower 5/6 bits anyway?
// PowerPC requires masked shift counts.
const bool Matcher::need_masked_shift_count = true;

// This affects two different things:
//  - how Decode nodes are matched
//  - how ImplicitNullCheck opportunities are recognized
// If true, the matcher will try to remove all Decodes and match them
// (as operands) into nodes. NullChecks are not prepared to deal with
// Decodes by final_graph_reshaping().
// If false, final_graph_reshaping() forces the decode behind the Cmp
// for a NullCheck. The matcher matches the Decode node into a register.
// Implicit_null_check optimization moves the Decode along with the
// memory operation back up before the NullCheck.
bool Matcher::narrow_oop_use_complex_address() {
  // TODO: PPC port if (MatchDecodeNodes) return true;
  return false;
}

bool Matcher::narrow_klass_use_complex_address() {
  NOT_LP64(ShouldNotCallThis());
  assert(UseCompressedClassPointers, "only for compressed klass code");
  // TODO: PPC port if (MatchDecodeNodes) return true;
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
// Intel can load a float constant from a direct address, requiring no
// extra registers. Most RISCs will have to materialize an address into a
// register first, so they would do better to copy the constant from stack.
const bool Matcher::rematerialize_float_constants = false;

// If CPU can load and store mis-aligned doubles directly then no fixup is
// needed. Else we split the double into 2 integer pieces and move it
// piece-by-piece. Only happens when passing doubles into C code as the
// Java calling convention forces doubles to be aligned.
const bool Matcher::misaligned_doubles_ok = true;

void Matcher::pd_implicit_null_fixup(MachNode *node, uint idx) {
 Unimplemented();
}

// Advertise here if the CPU requires explicit rounding operations
// to implement the UseStrictFP mode.
const bool Matcher::strict_fp_requires_explicit_rounding = false;

// Do floats take an entire double register or just half?
//
// A float occupies a ppc64 double register. For the allocator, a
// ppc64 double register appears as a pair of float registers.
bool Matcher::float_in_double() { return true; }

// Do ints take an entire long register or just half?
// The relevant question is how the int is callee-saved:
// the whole long is written but de-opt'ing will have to extract
// the relevant 32 bits.
const bool Matcher::int_in_long = true;

// Constants for c2c and c calling conventions.

const MachRegisterNumbers iarg_reg[8] = {
  R3_num, R4_num, R5_num, R6_num,
  R7_num, R8_num, R9_num, R10_num
};

const MachRegisterNumbers farg_reg[13] = {
  F1_num, F2_num, F3_num, F4_num,
  F5_num, F6_num, F7_num, F8_num,
  F9_num, F10_num, F11_num, F12_num,
  F13_num
};

const MachRegisterNumbers vsarg_reg[64] = {
  VSR0_num, VSR1_num, VSR2_num, VSR3_num,
  VSR4_num, VSR5_num, VSR6_num, VSR7_num,
  VSR8_num, VSR9_num, VSR10_num, VSR11_num,
  VSR12_num, VSR13_num, VSR14_num, VSR15_num,
  VSR16_num, VSR17_num, VSR18_num, VSR19_num,
  VSR20_num, VSR21_num, VSR22_num, VSR23_num,
  VSR24_num, VSR23_num, VSR24_num, VSR25_num,
  VSR28_num, VSR29_num, VSR30_num, VSR31_num,
  VSR32_num, VSR33_num, VSR34_num, VSR35_num,
  VSR36_num, VSR37_num, VSR38_num, VSR39_num,
  VSR40_num, VSR41_num, VSR42_num, VSR43_num,
  VSR44_num, VSR45_num, VSR46_num, VSR47_num,
  VSR48_num, VSR49_num, VSR50_num, VSR51_num,
  VSR52_num, VSR53_num, VSR54_num, VSR55_num,
  VSR56_num, VSR57_num, VSR58_num, VSR59_num,
  VSR60_num, VSR61_num, VSR62_num, VSR63_num
};

const int num_iarg_registers = sizeof(iarg_reg) / sizeof(iarg_reg[0]);

const int num_farg_registers = sizeof(farg_reg) / sizeof(farg_reg[0]);

const int num_vsarg_registers = sizeof(vsarg_reg) / sizeof(vsarg_reg[0]);

// Return whether or not this register is ever used as an argument. This
// function is used on startup to build the trampoline stubs in generateOptoStub.
// Registers not mentioned will be killed by the VM call in the trampoline, and
// arguments in those registers not be available to the callee.
bool Matcher::can_be_java_arg(int reg) {
  // We return true for all registers contained in iarg_reg[] and
  // farg_reg[] and their virtual halves.
  // We must include the virtual halves in order to get STDs and LDs
  // instead of STWs and LWs in the trampoline stubs.

  if (   reg == R3_num  || reg == R3_H_num
      || reg == R4_num  || reg == R4_H_num
      || reg == R5_num  || reg == R5_H_num
      || reg == R6_num  || reg == R6_H_num
      || reg == R7_num  || reg == R7_H_num
      || reg == R8_num  || reg == R8_H_num
      || reg == R9_num  || reg == R9_H_num
      || reg == R10_num || reg == R10_H_num)
    return true;

  if (   reg == F1_num  || reg == F1_H_num
      || reg == F2_num  || reg == F2_H_num
      || reg == F3_num  || reg == F3_H_num
      || reg == F4_num  || reg == F4_H_num
      || reg == F5_num  || reg == F5_H_num
      || reg == F6_num  || reg == F6_H_num
      || reg == F7_num  || reg == F7_H_num
      || reg == F8_num  || reg == F8_H_num
      || reg == F9_num  || reg == F9_H_num
      || reg == F10_num || reg == F10_H_num
      || reg == F11_num || reg == F11_H_num
      || reg == F12_num || reg == F12_H_num
      || reg == F13_num || reg == F13_H_num)
    return true;

  return false;
}

bool Matcher::is_spillable_arg(int reg) {
  return can_be_java_arg(reg);
}

bool Matcher::use_asm_for_ldiv_by_con(jlong divisor) {
  return false;
}

// Register for DIVI projection of divmodI.
RegMask Matcher::divI_proj_mask() {
  ShouldNotReachHere();
  return RegMask();
}

// Register for MODI projection of divmodI.
RegMask Matcher::modI_proj_mask() {
  ShouldNotReachHere();
  return RegMask();
}

// Register for DIVL projection of divmodL.
RegMask Matcher::divL_proj_mask() {
  ShouldNotReachHere();
  return RegMask();
}

// Register for MODL projection of divmodL.
RegMask Matcher::modL_proj_mask() {
  ShouldNotReachHere();
  return RegMask();
}

const RegMask Matcher::method_handle_invoke_SP_save_mask() {
  return RegMask();
}

const bool Matcher::convi2l_type_required = true;


#line 1584 "ad_ppc.cpp"


//SourceForm

#line 2737 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"


typedef struct {
  loadConL_hiNode *_large_hi;
  loadConL_loNode *_large_lo;
  loadConLNode    *_small;
  MachNode        *_last;
} loadConLNodesTuple;

loadConLNodesTuple loadConLNodesTuple_create(PhaseRegAlloc *ra_, Node *toc, immLOper *immSrc,
                                             OptoReg::Name reg_second, OptoReg::Name reg_first) {
  loadConLNodesTuple nodes;

  const bool large_constant_pool = true; // TODO: PPC port C->cfg()->_consts_size > 4000;
  if (large_constant_pool) {
    // Create new nodes.
    loadConL_hiNode *m1 = new loadConL_hiNode();
    loadConL_loNode *m2 = new loadConL_loNode();

    // inputs for new nodes
    m1->add_req(NULL, toc);
    m2->add_req(NULL, m1);

    // operands for new nodes
    m1->_opnds[0] = new iRegLdstOper(); // dst
    m1->_opnds[1] = immSrc;             // src
    m1->_opnds[2] = new iRegPdstOper(); // toc
    m2->_opnds[0] = new iRegLdstOper(); // dst
    m2->_opnds[1] = immSrc;             // src
    m2->_opnds[2] = new iRegLdstOper(); // base

    // Initialize ins_attrib TOC fields.
    m1->_const_toc_offset = -1;
    m2->_const_toc_offset_hi_node = m1;

    // Initialize ins_attrib instruction offset.
    m1->_cbuf_insts_offset = -1;

    // register allocation for new nodes
    ra_->set_pair(m1->_idx, reg_second, reg_first);
    ra_->set_pair(m2->_idx, reg_second, reg_first);

    // Create result.
    nodes._large_hi = m1;
    nodes._large_lo = m2;
    nodes._small = NULL;
    nodes._last = nodes._large_lo;
    assert(m2->bottom_type()->isa_long(), "must be long");
  } else {
    loadConLNode *m2 = new loadConLNode();

    // inputs for new nodes
    m2->add_req(NULL, toc);

    // operands for new nodes
    m2->_opnds[0] = new iRegLdstOper(); // dst
    m2->_opnds[1] = immSrc;             // src
    m2->_opnds[2] = new iRegPdstOper(); // toc

    // Initialize ins_attrib instruction offset.
    m2->_cbuf_insts_offset = -1;

    // register allocation for new nodes
    ra_->set_pair(m2->_idx, reg_second, reg_first);

    // Create result.
    nodes._large_hi = NULL;
    nodes._large_lo = NULL;
    nodes._small = m2;
    nodes._last = nodes._small;
    assert(m2->bottom_type()->isa_long(), "must be long");
  }

  return nodes;
}

typedef struct {
  loadConL_hiNode *_large_hi;
  loadConL_loNode *_large_lo;
  mtvsrdNode      *_moved;
  xxspltdNode     *_replicated;
  loadConLNode    *_small;
  MachNode        *_last;
} loadConLReplicatedNodesTuple;

loadConLReplicatedNodesTuple loadConLReplicatedNodesTuple_create(Compile *C, PhaseRegAlloc *ra_, Node *toc, immLOper *immSrc,
                                                 vecXOper *dst, immI_0Oper *zero,
                                                 OptoReg::Name reg_second, OptoReg::Name reg_first,
                                                 OptoReg::Name reg_vec_second, OptoReg::Name reg_vec_first) {
  loadConLReplicatedNodesTuple nodes;

  const bool large_constant_pool = true; // TODO: PPC port C->cfg()->_consts_size > 4000;
  if (large_constant_pool) {
    // Create new nodes.
    loadConL_hiNode *m1 = new  loadConL_hiNode();
    loadConL_loNode *m2 = new  loadConL_loNode();
    mtvsrdNode *m3 = new  mtvsrdNode();
    xxspltdNode *m4 = new  xxspltdNode();

    // inputs for new nodes
    m1->add_req(NULL, toc);
    m2->add_req(NULL, m1);
    m3->add_req(NULL, m2);
    m4->add_req(NULL, m3);

    // operands for new nodes
    m1->_opnds[0] = new  iRegLdstOper(); // dst
    m1->_opnds[1] = immSrc;              // src
    m1->_opnds[2] = new  iRegPdstOper(); // toc

    m2->_opnds[0] = new  iRegLdstOper(); // dst
    m2->_opnds[1] = immSrc;              // src
    m2->_opnds[2] = new  iRegLdstOper(); // base

    m3->_opnds[0] = new  vecXOper();     // dst
    m3->_opnds[1] = new  iRegLdstOper(); // src

    m4->_opnds[0] = new  vecXOper();     // dst
    m4->_opnds[1] = new  vecXOper();     // src
    m4->_opnds[2] = zero;

    // Initialize ins_attrib TOC fields.
    m1->_const_toc_offset = -1;
    m2->_const_toc_offset_hi_node = m1;

    // Initialize ins_attrib instruction offset.
    m1->_cbuf_insts_offset = -1;

    // register allocation for new nodes
    ra_->set_pair(m1->_idx, reg_second, reg_first);
    ra_->set_pair(m2->_idx, reg_second, reg_first);
    ra_->set1(m3->_idx, reg_second);
    ra_->set2(m3->_idx, reg_vec_first);
    ra_->set_pair(m4->_idx, reg_vec_second, reg_vec_first);

    // Create result.
    nodes._large_hi = m1;
    nodes._large_lo = m2;
    nodes._moved = m3;
    nodes._replicated = m4;
    nodes._small = NULL;
    nodes._last = nodes._replicated;
    assert(m2->bottom_type()->isa_long(), "must be long");
  } else {
    loadConLNode *m2 = new  loadConLNode();
    mtvsrdNode *m3 = new  mtvsrdNode();
    xxspltdNode *m4 = new  xxspltdNode();

    // inputs for new nodes
    m2->add_req(NULL, toc);

    // operands for new nodes
    m2->_opnds[0] = new  iRegLdstOper(); // dst
    m2->_opnds[1] = immSrc;              // src
    m2->_opnds[2] = new  iRegPdstOper(); // toc

    m3->_opnds[0] = new  vecXOper();     // dst
    m3->_opnds[1] = new  iRegLdstOper(); // src

    m4->_opnds[0] = new  vecXOper();     // dst
    m4->_opnds[1] = new  vecXOper();     // src
    m4->_opnds[2] = zero;

    // Initialize ins_attrib instruction offset.
    m2->_cbuf_insts_offset = -1;
    ra_->set1(m3->_idx, reg_second);
    ra_->set2(m3->_idx, reg_vec_first);
    ra_->set_pair(m4->_idx, reg_vec_second, reg_vec_first);

    // register allocation for new nodes
    ra_->set_pair(m2->_idx, reg_second, reg_first);

    // Create result.
    nodes._large_hi = NULL;
    nodes._large_lo = NULL;
    nodes._small = m2;
    nodes._moved = m3;
    nodes._replicated = m4;
    nodes._last = nodes._replicated;
    assert(m2->bottom_type()->isa_long(), "must be long");
  }

  return nodes;
}


#line 1776 "ad_ppc.cpp"


#ifndef PRODUCT
void Compile::adlc_verification() {

  // Following assertions generated from definition section
  assert( DEFAULT_COST_LOW == 30, "Expect (30) to equal 30");
  assert( DEFAULT_COST == 100, "Expect (100) to equal 100");
  assert( HUGE_COST == 1000000, "Expect (1000000) to equal 1000000");
  assert( MEMORY_REF_COST_LOW == 200, "Expect (DEFAULT_COST * 2) to equal 200");
  assert( MEMORY_REF_COST == 300, "Expect (DEFAULT_COST * 3) to equal 300");
  assert( BRANCH_COST == 900, "Expect (DEFAULT_COST * 9) to equal 900");
  assert( CALL_COST == 1300, "Expect (DEFAULT_COST * 13) to equal 1300");
}
#endif

// Map from machine-independent register number to register_save_policy
const        char register_save_policy[] = {
  'C', // R14
  'C', // R14_H
  'C', // R15
  'C', // R15_H
  'C', // R17
  'C', // R17_H
  'C', // R18
  'C', // R18_H
  'C', // R19
  'C', // R19_H
  'C', // R20
  'C', // R20_H
  'C', // R21
  'C', // R21_H
  'C', // R22
  'C', // R22_H
  'C', // R23
  'C', // R23_H
  'C', // R24
  'C', // R24_H
  'C', // R25
  'C', // R25_H
  'C', // R26
  'C', // R26_H
  'C', // R27
  'C', // R27_H
  'C', // R28
  'C', // R28_H
  'C', // R29
  'C', // R29_H
  'C', // R30
  'C', // R30_H
  'C', // R31
  'C', // R31_H
  'C', // R11
  'C', // R11_H
  'C', // R12
  'C', // R12_H
  'C', // R10
  'C', // R10_H
  'C', // R9
  'C', // R9_H
  'C', // R8
  'C', // R8_H
  'C', // R7
  'C', // R7_H
  'C', // R6
  'C', // R6_H
  'C', // R5
  'C', // R5_H
  'C', // R4
  'C', // R4_H
  'C', // R3
  'C', // R3_H
  'C', // R16
  'C', // R16_H
  'N', // R13
  'N', // R13_H
  'C', // R2
  'C', // R2_H
  'N', // R1
  'N', // R1_H
  'C', // R0
  'C', // R0_H
  'C', // F0
  'C', // F0_H
  'C', // F13
  'C', // F13_H
  'C', // F12
  'C', // F12_H
  'C', // F11
  'C', // F11_H
  'C', // F10
  'C', // F10_H
  'C', // F9
  'C', // F9_H
  'C', // F8
  'C', // F8_H
  'C', // F7
  'C', // F7_H
  'C', // F6
  'C', // F6_H
  'C', // F5
  'C', // F5_H
  'C', // F4
  'C', // F4_H
  'C', // F3
  'C', // F3_H
  'C', // F2
  'C', // F2_H
  'C', // F1
  'C', // F1_H
  'C', // F14
  'C', // F14_H
  'C', // F15
  'C', // F15_H
  'C', // F16
  'C', // F16_H
  'C', // F17
  'C', // F17_H
  'C', // F18
  'C', // F18_H
  'C', // F19
  'C', // F19_H
  'C', // F20
  'C', // F20_H
  'C', // F21
  'C', // F21_H
  'C', // F22
  'C', // F22_H
  'C', // F23
  'C', // F23_H
  'C', // F24
  'C', // F24_H
  'C', // F25
  'C', // F25_H
  'C', // F26
  'C', // F26_H
  'C', // F27
  'C', // F27_H
  'C', // F28
  'C', // F28_H
  'C', // F29
  'C', // F29_H
  'C', // F30
  'C', // F30_H
  'C', // F31
  'C', // F31_H
  'C', // CCR0
  'C', // CCR1
  'C', // CCR2
  'C', // CCR3
  'C', // CCR4
  'C', // CCR5
  'C', // CCR6
  'C', // CCR7
  'C', // VSR0
  'C', // VSR1
  'C', // VSR2
  'C', // VSR3
  'C', // VSR4
  'C', // VSR5
  'C', // VSR6
  'C', // VSR7
  'C', // VSR8
  'C', // VSR9
  'C', // VSR10
  'C', // VSR11
  'C', // VSR12
  'C', // VSR13
  'C', // VSR14
  'C', // VSR15
  'C', // VSR16
  'C', // VSR17
  'C', // VSR18
  'C', // VSR19
  'C', // VSR20
  'C', // VSR21
  'C', // VSR22
  'C', // VSR23
  'C', // VSR24
  'C', // VSR25
  'C', // VSR26
  'C', // VSR27
  'C', // VSR28
  'C', // VSR29
  'C', // VSR30
  'C', // VSR31
  'C', // VSR32
  'C', // VSR33
  'C', // VSR34
  'C', // VSR35
  'C', // VSR36
  'C', // VSR37
  'C', // VSR38
  'C', // VSR39
  'C', // VSR40
  'C', // VSR41
  'C', // VSR42
  'C', // VSR43
  'C', // VSR44
  'C', // VSR45
  'C', // VSR46
  'C', // VSR47
  'C', // VSR48
  'C', // VSR49
  'C', // VSR50
  'C', // VSR51
  'C', // VSR52
  'C', // VSR53
  'C', // VSR54
  'C', // VSR55
  'C', // VSR56
  'C', // VSR57
  'C', // VSR58
  'C', // VSR59
  'C', // VSR60
  'C', // VSR61
  'C', // VSR62
  'C', // VSR63
  'C', // SR_XER
  'C', // SR_LR
  'C', // SR_CTR
  'C', // SR_VRSAVE
  'C', // SR_SPEFSCR
  'C' // no trailing comma // SR_PPR
};

// Map from machine-independent register number to c_reg_save_policy
const        char c_reg_save_policy[] = {
  'E', // R14
  'E', // R14_H
  'E', // R15
  'E', // R15_H
  'E', // R17
  'E', // R17_H
  'E', // R18
  'E', // R18_H
  'E', // R19
  'E', // R19_H
  'E', // R20
  'E', // R20_H
  'E', // R21
  'E', // R21_H
  'E', // R22
  'E', // R22_H
  'E', // R23
  'E', // R23_H
  'E', // R24
  'E', // R24_H
  'E', // R25
  'E', // R25_H
  'E', // R26
  'E', // R26_H
  'E', // R27
  'E', // R27_H
  'E', // R28
  'E', // R28_H
  'E', // R29
  'E', // R29_H
  'E', // R30
  'E', // R30_H
  'E', // R31
  'E', // R31_H
  'C', // R11
  'C', // R11_H
  'C', // R12
  'C', // R12_H
  'C', // R10
  'C', // R10_H
  'C', // R9
  'C', // R9_H
  'C', // R8
  'C', // R8_H
  'C', // R7
  'C', // R7_H
  'C', // R6
  'C', // R6_H
  'C', // R5
  'C', // R5_H
  'C', // R4
  'C', // R4_H
  'C', // R3
  'C', // R3_H
  'E', // R16
  'E', // R16_H
  'N', // R13
  'N', // R13_H
  'C', // R2
  'C', // R2_H
  'N', // R1
  'N', // R1_H
  'C', // R0
  'C', // R0_H
  'C', // F0
  'C', // F0_H
  'C', // F13
  'C', // F13_H
  'C', // F12
  'C', // F12_H
  'C', // F11
  'C', // F11_H
  'C', // F10
  'C', // F10_H
  'C', // F9
  'C', // F9_H
  'C', // F8
  'C', // F8_H
  'C', // F7
  'C', // F7_H
  'C', // F6
  'C', // F6_H
  'C', // F5
  'C', // F5_H
  'C', // F4
  'C', // F4_H
  'C', // F3
  'C', // F3_H
  'C', // F2
  'C', // F2_H
  'C', // F1
  'C', // F1_H
  'E', // F14
  'E', // F14_H
  'E', // F15
  'E', // F15_H
  'E', // F16
  'E', // F16_H
  'E', // F17
  'E', // F17_H
  'E', // F18
  'E', // F18_H
  'E', // F19
  'E', // F19_H
  'E', // F20
  'E', // F20_H
  'E', // F21
  'E', // F21_H
  'E', // F22
  'E', // F22_H
  'E', // F23
  'E', // F23_H
  'E', // F24
  'E', // F24_H
  'E', // F25
  'E', // F25_H
  'E', // F26
  'E', // F26_H
  'E', // F27
  'E', // F27_H
  'E', // F28
  'E', // F28_H
  'E', // F29
  'E', // F29_H
  'E', // F30
  'E', // F30_H
  'E', // F31
  'E', // F31_H
  'C', // CCR0
  'C', // CCR1
  'C', // CCR2
  'C', // CCR3
  'C', // CCR4
  'C', // CCR5
  'C', // CCR6
  'C', // CCR7
  'C', // VSR0
  'C', // VSR1
  'C', // VSR2
  'C', // VSR3
  'C', // VSR4
  'C', // VSR5
  'C', // VSR6
  'C', // VSR7
  'C', // VSR8
  'C', // VSR9
  'C', // VSR10
  'C', // VSR11
  'C', // VSR12
  'C', // VSR13
  'C', // VSR14
  'C', // VSR15
  'C', // VSR16
  'C', // VSR17
  'C', // VSR18
  'C', // VSR19
  'C', // VSR20
  'C', // VSR21
  'C', // VSR22
  'C', // VSR23
  'C', // VSR24
  'C', // VSR25
  'C', // VSR26
  'C', // VSR27
  'C', // VSR28
  'C', // VSR29
  'C', // VSR30
  'C', // VSR31
  'C', // VSR32
  'C', // VSR33
  'C', // VSR34
  'C', // VSR35
  'C', // VSR36
  'C', // VSR37
  'C', // VSR38
  'C', // VSR39
  'C', // VSR40
  'C', // VSR41
  'C', // VSR42
  'C', // VSR43
  'C', // VSR44
  'C', // VSR45
  'C', // VSR46
  'C', // VSR47
  'C', // VSR48
  'C', // VSR49
  'C', // VSR50
  'C', // VSR51
  'C', // VSR52
  'C', // VSR53
  'C', // VSR54
  'C', // VSR55
  'C', // VSR56
  'C', // VSR57
  'C', // VSR58
  'C', // VSR59
  'C', // VSR60
  'C', // VSR61
  'C', // VSR62
  'C', // VSR63
  'C', // SR_XER
  'C', // SR_LR
  'C', // SR_CTR
  'C', // SR_VRSAVE
  'C', // SR_SPEFSCR
  'C' // no trailing comma // SR_PPR
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
  Op_RegFlags,
  Op_RegFlags,
  Op_RegFlags,
  Op_RegFlags,
  Op_RegFlags,
  Op_RegFlags,
  Op_RegFlags,
  Op_RegFlags,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_VecX,
  Op_RegP,
  Op_RegP,
  Op_RegP,
  Op_RegP,
  Op_RegP,
  Op_RegP // no trailing comma
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
  /*    9 */  immI_rule,
  /*   10 */  immI8_rule,
  /*   11 */  immI16_rule,
  /*   12 */  immIhi16_rule,
  /*   13 */  immInegpow2_rule,
  /*   14 */  immIpow2minus1_rule,
  /*   15 */  immIpowerOf2_rule,
  /*   16 */  uimmI5_rule,
  /*   17 */  uimmI6_rule,
  /*   18 */  uimmI6_ge32_rule,
  /*   19 */  uimmI15_rule,
  /*   20 */  uimmI16_rule,
  /*   21 */  immI_0_rule,
  /*   22 */  immI_1_rule,
  /*   23 */  immI_minus1_rule,
  /*   24 */  immI_16_rule,
  /*   25 */  immI_24_rule,
  /*   26 */  immN_rule,
  /*   27 */  immN_0_rule,
  /*   28 */  immNKlass_rule,
  /*   29 */  immNKlass_NM_rule,
  /*   30 */  immP_rule,
  /*   31 */  immP_NM_rule,
  /*   32 */  immP_0_rule,
  /*   33 */  immP_0or1_rule,
  /*   34 */  immL_rule,
  /*   35 */  immLmax30_rule,
  /*   36 */  immL16_rule,
  /*   37 */  immL16Alg4_rule,
  /*   38 */  immL32hi16_rule,
  /*   39 */  immL32_rule,
  /*   40 */  immLhighest16_rule,
  /*   41 */  immLnegpow2_rule,
  /*   42 */  immLpow2minus1_rule,
  /*   43 */  immL_0_rule,
  /*   44 */  immL_minus1_rule,
  /*   45 */  immL_32bits_rule,
  /*   46 */  uimmL16_rule,
  /*   47 */  immF_rule,
  /*   48 */  immF_0_rule,
  /*   49 */  immD_rule,
  /*   50 */  iRegIdst_rule,
  /*   51 */  iRegIsrc_rule,
  /*   52 */  rscratch1RegI_rule,
  /*   53 */  rscratch2RegI_rule,
  /*   54 */  rarg1RegI_rule,
  /*   55 */  rarg2RegI_rule,
  /*   56 */  rarg3RegI_rule,
  /*   57 */  rarg4RegI_rule,
  /*   58 */  rarg1RegL_rule,
  /*   59 */  rarg2RegL_rule,
  /*   60 */  rarg3RegL_rule,
  /*   61 */  rarg4RegL_rule,
  /*   62 */  iRegPdst_rule,
  /*   63 */  iRegPdstNoScratch_rule,
  /*   64 */  iRegPsrc_rule,
  /*   65 */  threadRegP_rule,
  /*   66 */  rscratch1RegP_rule,
  /*   67 */  rscratch2RegP_rule,
  /*   68 */  rarg1RegP_rule,
  /*   69 */  rarg2RegP_rule,
  /*   70 */  rarg3RegP_rule,
  /*   71 */  rarg4RegP_rule,
  /*   72 */  iRegNsrc_rule,
  /*   73 */  iRegNdst_rule,
  /*   74 */  iRegLdst_rule,
  /*   75 */  iRegLsrc_rule,
  /*   76 */  iRegL2Isrc_rule,
  /*   77 */  rscratch1RegL_rule,
  /*   78 */  rscratch2RegL_rule,
  /*   79 */  flagsReg_rule,
  /*   80 */  flagsRegSrc_rule,
  /*   81 */  flagsRegCR0_rule,
  /*   82 */  flagsRegCR1_rule,
  /*   83 */  flagsRegCR6_rule,
  /*   84 */  regCTR_rule,
  /*   85 */  regD_rule,
  /*   86 */  regF_rule,
  /*   87 */  inline_cache_regP_rule,
  /*   88 */  compiler_method_oop_regP_rule,
  /*   89 */  interpreter_method_oop_regP_rule,
  /*   90 */  iRegP2N_rule,
  /*   91 */  iRegN2P_rule,
  /*   92 */  iRegN2P_klass_rule,
  /*   93 */  indirect_rule,
  /*   94 */  indOffset16_rule,
  /*   95 */  indOffset16Alg4_rule,
  /*   96 */  indirectNarrow_rule,
  /*   97 */  indirectNarrow_klass_rule,
  /*   98 */  indOffset16Narrow_rule,
  /*   99 */  indOffset16Narrow_klass_rule,
  /*  100 */  indOffset16NarrowAlg4_rule,
  /*  101 */  indOffset16NarrowAlg4_klass_rule,
  /*  102 */  stackSlotI_rule,
  /*  103 */  stackSlotL_rule,
  /*  104 */  stackSlotP_rule,
  /*  105 */  stackSlotF_rule,
  /*  106 */  stackSlotD_rule,
  /*  107 */  cmpOp_rule,
  // last operand
  /*  108 */  memory_rule,
  /*  109 */  memoryAlg4_rule,
  /*  110 */  indirectMemory_rule,
  /*  111 */  iRegIsrc_iRegL2Isrc_rule,
  /*  112 */  iRegN_P2N_rule,
  /*  113 */  iRegP_N2P_rule,
  // last operand class
  /*  114 */  _DecodeN_iRegNsrc__rule,
  /*  115 */  _DecodeNKlass_iRegNsrc__rule,
  /*  116 */  _LoadUB_memory__rule,
  /*  117 */  _LoadUS_memory__rule,
  /*  118 */  _LoadI_memory__rule,
  /*  119 */  _ConvI2L__LoadI_memory___rule,
  /*  120 */  _LoadI_memoryAlg4__rule,
  /*  121 */  _LoadN_memory__rule,
  /*  122 */  _LoadNKlass_memory__rule,
  /*  123 */  _LoadP_memoryAlg4__rule,
  /*  124 */  _AddP_indirectMemory_iRegLsrc_rule,
  /*  125 */  _ConvL2I_iRegLsrc__rule,
  /*  126 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  127 */  _CastP2X__DecodeN_iRegNsrc___rule,
  /*  128 */  _Binary_iRegLsrc_iRegPdst_rule,
  /*  129 */  _Binary_iRegLsrc_iRegPsrc_rule,
  /*  130 */  _Binary_iRegLsrc_iRegNsrc_rule,
  /*  131 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  132 */  _Binary_iRegIdst_iRegIsrc_rule,
  /*  133 */  _Binary_iRegIdst_immI16_rule,
  /*  134 */  _Binary_iRegLdst_iRegLsrc_rule,
  /*  135 */  _Binary_iRegLdst_immL16_rule,
  /*  136 */  _Binary_iRegNdst_iRegNsrc_rule,
  /*  137 */  _Binary_iRegNdst_immN_0_rule,
  /*  138 */  _Binary_iRegPdst_iRegPsrc_rule,
  /*  139 */  _Binary_iRegPdst_iRegP_N2P_rule,
  /*  140 */  _Binary_iRegPdst_immP_0_rule,
  /*  141 */  _Binary_regF_regF_rule,
  /*  142 */  _Binary_regD_regD_rule,
  /*  143 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  144 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  145 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  146 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  147 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  148 */  _AddI_iRegIsrc_iRegIsrc_rule,
  /*  149 */  _AddI__AddI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  150 */  _AddI_iRegIsrc__AddI_iRegIsrc_iRegIsrc_rule,
  /*  151 */  _AddL_iRegLsrc_iRegLsrc_rule,
  /*  152 */  _AddL__AddL_iRegLsrc_iRegLsrc_iRegLsrc_rule,
  /*  153 */  _AddL_iRegLsrc__AddL_iRegLsrc_iRegLsrc_rule,
  /*  154 */  _SubL_iRegLsrc_iRegLsrc_rule,
  /*  155 */  _SubL_immL_0_iRegLsrc_rule,
  /*  156 */  _AndI_iRegIsrc_immInegpow2_rule,
  /*  157 */  _RShiftI_iRegIsrc_uimmI5_rule,
  /*  158 */  _AndI__RShiftI_iRegIsrc_uimmI5_immInegpow2_rule,
  /*  159 */  _ConvI2L_iRegIsrc__rule,
  /*  160 */  _RShiftL_iRegLsrc_immI_rule,
  /*  161 */  _URShiftL_iRegLsrc_immI_rule,
  /*  162 */  _CastP2X_iRegP_N2P__rule,
  /*  163 */  _URShiftI_iRegIsrc_immI_rule,
  /*  164 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  165 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  166 */  _AbsF_regF__rule,
  /*  167 */  _AbsD_regD__rule,
  /*  168 */  _ConvF2D_regF__rule,
  /*  169 */  _SqrtD__ConvF2D_regF___rule,
  /*  170 */  _NegF_regF__rule,
  /*  171 */  _Binary__NegF_regF__regF_rule,
  /*  172 */  _Binary_regF__NegF_regF__rule,
  /*  173 */  _NegD_regD__rule,
  /*  174 */  _Binary__NegD_regD__regD_rule,
  /*  175 */  _Binary_regD__NegD_regD__rule,
  /*  176 */  _AndL_iRegLsrc_immLpow2minus1_rule,
  /*  177 */  _OrI_iRegIsrc_iRegIsrc_rule,
  /*  178 */  _OrI__OrI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  179 */  _OrI_iRegIsrc__OrI_iRegIsrc_iRegIsrc_rule,
  /*  180 */  _OrL_iRegLsrc_iRegLsrc_rule,
  /*  181 */  _XorI_iRegIsrc_iRegIsrc_rule,
  /*  182 */  _XorI__XorI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  183 */  _XorI_iRegIsrc__XorI_iRegIsrc_iRegIsrc_rule,
  /*  184 */  _XorL_iRegLsrc_iRegLsrc_rule,
  /*  185 */  _XorI_iRegIsrc_immI_minus1_rule,
  /*  186 */  _Conv2B_iRegIsrc__rule,
  /*  187 */  _AndI_iRegIsrc_immIpowerOf2_rule,
  /*  188 */  _Conv2B_iRegP_N2P__rule,
  /*  189 */  _LShiftI_iRegIsrc_immI_24_rule,
  /*  190 */  _LShiftI_iRegIsrc_immI_16_rule,
  /*  191 */  _AndI_iRegIsrc_uimmI16_rule,
  /*  192 */  _AndL_iRegLsrc_iRegLsrc_rule,
  /*  193 */  _AndL_iRegLsrc_uimmL16_rule,
  /*  194 */  _CmpU_iRegIsrc_uimmI15_rule,
  /*  195 */  _CmpU_iRegIsrc_iRegIsrc_rule,
  /*  196 */  _CmpN_iRegNsrc_immN_0_rule,
  /*  197 */  _CmpP_iRegP_N2P_immP_0_rule,
  /*  198 */  _CastP2X_iRegPsrc__rule,
  /*  199 */  _AndL__CastP2X_iRegPsrc__immLnegpow2_rule,
  /*  200 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  201 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  202 */  _Binary_rarg1RegP_rarg2RegP_rule,
  /*  203 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  204 */  _AddP_immP_immL_rule,
  /*  205 */  _Binary__AddP_immP_immL_immI_1_rule,
  /*  206 */  _Binary_rscratch2RegP_immI_1_rule,
  /*  207 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  208 */  _Binary_iRegPsrc_uimmI15_rule,
  /*  209 */  _Binary_iRegPsrc_rscratch2RegI_rule,
  /*  210 */  _Binary_rarg2RegP_iRegIsrc_rule,
  /*  211 */  _LoadI_indirect__rule,
  /*  212 */  _LoadL_indirect__rule,
  /*  213 */  _LoadUS_indirect__rule,
  /*  214 */  _LoadS_indirect__rule,
  /*  215 */  _ReverseBytesI_iRegIsrc__rule,
  /*  216 */  _ReverseBytesL_iRegLsrc__rule,
  /*  217 */  _ReverseBytesUS_iRegIsrc__rule,
  /*  218 */  _ReverseBytesS_iRegIsrc__rule,
  // last internally defined operand
  /*  219 */  stackSlotI_rule,
  /*  220 */  stackSlotL_rule,
  /*  221 */  iRegIdst_rule,
  /*  222 */  iRegIdst_rule,
  /*  223 */  iRegIdst_rule,
  /*  224 */  iRegLdst_rule,
  /*  225 */  iRegLdst_rule,
  /*  226 */  iRegLdst_rule,
  /*  227 */  iRegLdst_rule,
  /*  228 */  iRegLdst_rule,
  /*  229 */  iRegNdst_rule,
  /*  230 */  iRegNdst_rule,
  /*  231 */  iRegNdst_rule,
  /*  232 */  iRegNdst_rule,
  /*  233 */  iRegNdst_rule,
  /*  234 */  iRegNdst_rule,
  /*  235 */  iRegPdst_rule,
  /*  236 */  iRegPdst_rule,
  /*  237 */  iRegPdst_rule,
  /*  238 */  iRegPdst_rule,
  /*  239 */  regF_rule,
  /*  240 */  regD_rule,
  /*  241 */  iRegIdst_rule,
  /*  242 */  iRegLdst_rule,
  /*  243 */  0,
  /*  244 */  iRegLdst_rule,
  /*  245 */  0,
  /*  246 */  0,
  /*  247 */  0,
  /*  248 */  flagsReg_rule,
  /*  249 */  flagsRegCR0_rule,
  /*  250 */  0,
  /*  251 */  iRegIdst_rule,
  /*  252 */  0,
  /*  253 */  0,
  /*  254 */  regF_rule,
  /*  255 */  regD_rule,
  /*  256 */  regF_rule,
  /*  257 */  regD_rule,
  /*  258 */  regF_rule,
  /*  259 */  regD_rule,
  /*  260 */  regD_rule,
  /*  261 */  regF_rule,
  /*  262 */  regD_rule,
  /*  263 */  0,
  /*  264 */  iRegIdst_rule,
  /*  265 */  regF_rule,
  /*  266 */  iRegLdst_rule,
  /*  267 */  regD_rule,
  /*  268 */  0,
  /*  269 */  iRegPdst_rule,
  /*  270 */  iRegLdst_rule,
  /*  271 */  iRegPdst_rule,
  /*  272 */  iRegIdst_rule,
  /*  273 */  iRegPdst_rule,
  /*  274 */  iRegIdst_rule,
  /*  275 */  iRegIdst_rule,
  /*  276 */  0,
  /*  277 */  0,
  /*  278 */  0,
  /*  279 */  0,
  /*  280 */  0,
  /*  281 */  0,
  /*  282 */  0,
  /*  283 */  flagsReg_rule,
  /*  284 */  flagsReg_rule,
  /*  285 */  flagsRegCR0_rule,
  /*  286 */  flagsReg_rule,
  /*  287 */  flagsReg_rule,
  /*  288 */  flagsReg_rule,
  /*  289 */  flagsReg_rule,
  /*  290 */  flagsRegCR0_rule,
  /*  291 */  flagsRegCR0_rule,
  /*  292 */  0,
  /*  293 */  0,
  /*  294 */  flagsReg_rule,
  /*  295 */  flagsReg_rule,
  /*  296 */  flagsReg_rule,
  /*  297 */  flagsReg_rule,
  /*  298 */  flagsReg_rule,
  /*  299 */  flagsReg_rule,
  /*  300 */  flagsReg_rule,
  /*  301 */  flagsReg_rule,
  /*  302 */  0,
  /*  303 */  flagsReg_rule,
  /*  304 */  flagsReg_rule,
  /*  305 */  flagsReg_rule,
  /*  306 */  flagsReg_rule,
  /*  307 */  flagsReg_rule,
  /*  308 */  flagsReg_rule,
  /*  309 */  flagsReg_rule,
  /*  310 */  iRegIdst_rule,
  /*  311 */  iRegIdst_rule,
  /*  312 */  iRegIdst_rule,
  /*  313 */  iRegIdst_rule,
  /*  314 */  0,
  /*  315 */  iRegIdst_rule,
  /*  316 */  iRegIdst_rule,
  /*  317 */  0,
  /*  318 */  0,
  /*  319 */  0,
  /*  320 */  0,
  /*  321 */  flagsRegCR0_rule,
  /*  322 */  flagsRegCR0_rule,
  /*  323 */  flagsRegCR0_rule,
  /*  324 */  flagsRegCR0_rule,
  /*  325 */  0,
  /*  326 */  0,
  /*  327 */  threadRegP_rule,
  /*  328 */  iRegIdst_rule,
  /*  329 */  iRegIdst_rule,
  /*  330 */  iRegIdst_rule,
  /*  331 */  iRegIdst_rule,
  /*  332 */  iRegIdst_rule,
  /*  333 */  iRegIdst_rule,
  /*  334 */  iRegIdst_rule,
  /*  335 */  iRegIdst_rule,
  /*  336 */  iRegIdst_rule,
  /*  337 */  iRegIdst_rule,
  /*  338 */  iRegLdst_rule,
  /*  339 */  iRegLdst_rule,
  /*  340 */  iRegIdst_rule,
  /*  341 */  iRegIdst_rule,
  /*  342 */  iRegIdst_rule,
  /*  343 */  iRegIdst_rule,
  /*  344 */  iRegLdst_rule,
  /*  345 */  iRegLdst_rule,
  /*  346 */  iRegIdst_rule,
  /*  347 */  iRegIdst_rule,
  /*  348 */  iRegLdst_rule,
  /*  349 */  iRegLdst_rule,
  /*  350 */  iRegLdst_rule,
  /*  351 */  iRegLdst_rule,
  /*  352 */  iRegLdst_rule,
  /*  353 */  iRegLdst_rule,
  /*  354 */  iRegLdst_rule,
  /*  355 */  vecX_rule,
  /*  356 */  iRegIdst_rule,
  /*  357 */  iRegNdst_rule,
  /*  358 */  iRegNdst_rule,
  /*  359 */  iRegPdst_rule,
  /*  360 */  iRegPdst_rule,
  /*  361 */  iRegPdst_rule,
  /*  362 */  iRegPdst_rule,
  /*  363 */  iRegNdst_rule,
  /*  364 */  iRegPdst_rule,
  /*  365 */  regF_rule,
  /*  366 */  regF_rule,
  /*  367 */  regD_rule,
  /*  368 */  regD_rule,
  /*  369 */  regD_rule,
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
  /*  380 */  0,
  /*  381 */  0,
  /*  382 */  0,
  /*  383 */  0,
  /*  384 */  Universe_rule,
  /*  385 */  Universe_rule,
  /*  386 */  Universe_rule,
  /*  387 */  Universe_rule,
  /*  388 */  Universe_rule,
  /*  389 */  Universe_rule,
  /*  390 */  Universe_rule,
  /*  391 */  Universe_rule,
  /*  392 */  Universe_rule,
  /*  393 */  Universe_rule,
  /*  394 */  Universe_rule,
  /*  395 */  Universe_rule,
  /*  396 */  Universe_rule,
  /*  397 */  Universe_rule,
  /*  398 */  Universe_rule,
  /*  399 */  Universe_rule,
  /*  400 */  Universe_rule,
  /*  401 */  Universe_rule,
  /*  402 */  Universe_rule,
  /*  403 */  iRegNdst_rule,
  /*  404 */  iRegPdst_rule,
  /*  405 */  iRegNdst_rule,
  /*  406 */  iRegNdst_rule,
  /*  407 */  iRegNdst_rule,
  /*  408 */  iRegNdst_rule,
  /*  409 */  iRegNdst_rule,
  /*  410 */  iRegNdst_rule,
  /*  411 */  iRegNdst_rule,
  /*  412 */  iRegPdst_rule,
  /*  413 */  iRegPdst_rule,
  /*  414 */  iRegPdst_rule,
  /*  415 */  iRegPdst_rule,
  /*  416 */  iRegPdst_rule,
  /*  417 */  iRegPdst_rule,
  /*  418 */  iRegPdst_rule,
  /*  419 */  iRegPdst_rule,
  /*  420 */  iRegPdst_rule,
  /*  421 */  iRegPdst_rule,
  /*  422 */  iRegPdst_rule,
  /*  423 */  iRegIdst_rule,
  /*  424 */  iRegNdst_rule,
  /*  425 */  iRegPdst_rule,
  /*  426 */  iRegNdst_rule,
  /*  427 */  iRegNdst_rule,
  /*  428 */  iRegNdst_rule,
  /*  429 */  iRegPdst_rule,
  /*  430 */  iRegPdst_rule,
  /*  431 */  iRegPdst_rule,
  /*  432 */  iRegPdst_rule,
  /*  433 */  Universe_rule,
  /*  434 */  Universe_rule,
  /*  435 */  Universe_rule,
  /*  436 */  Universe_rule,
  /*  437 */  Universe_rule,
  /*  438 */  Universe_rule,
  /*  439 */  Universe_rule,
  /*  440 */  Universe_rule,
  /*  441 */  Universe_rule,
  /*  442 */  iRegIdst_rule,
  /*  443 */  iRegIdst_rule,
  /*  444 */  iRegIdst_rule,
  /*  445 */  iRegLdst_rule,
  /*  446 */  iRegLdst_rule,
  /*  447 */  iRegLdst_rule,
  /*  448 */  iRegNdst_rule,
  /*  449 */  iRegNdst_rule,
  /*  450 */  iRegNdst_rule,
  /*  451 */  iRegPdst_rule,
  /*  452 */  iRegPdst_rule,
  /*  453 */  iRegPdst_rule,
  /*  454 */  regF_rule,
  /*  455 */  regD_rule,
  /*  456 */  iRegPdst_rule,
  /*  457 */  iRegIdst_rule,
  /*  458 */  iRegIdst_rule,
  /*  459 */  iRegIdst_rule,
  /*  460 */  iRegIdst_rule,
  /*  461 */  iRegIdst_rule,
  /*  462 */  iRegIdst_rule,
  /*  463 */  iRegIdst_rule,
  /*  464 */  iRegIdst_rule,
  /*  465 */  iRegIdst_rule,
  /*  466 */  iRegIdst_rule,
  /*  467 */  iRegIdst_rule,
  /*  468 */  iRegIdst_rule,
  /*  469 */  iRegIdst_rule,
  /*  470 */  iRegIdst_rule,
  /*  471 */  iRegIdst_rule,
  /*  472 */  iRegIdst_rule,
  /*  473 */  iRegIdst_rule,
  /*  474 */  iRegIdst_rule,
  /*  475 */  iRegIdst_rule,
  /*  476 */  iRegIdst_rule,
  /*  477 */  iRegIdst_rule,
  /*  478 */  iRegIdst_rule,
  /*  479 */  iRegIdst_rule,
  /*  480 */  iRegIdst_rule,
  /*  481 */  iRegIdst_rule,
  /*  482 */  iRegIdst_rule,
  /*  483 */  iRegIdst_rule,
  /*  484 */  iRegIdst_rule,
  /*  485 */  iRegIdst_rule,
  /*  486 */  iRegIdst_rule,
  /*  487 */  iRegIdst_rule,
  /*  488 */  iRegIdst_rule,
  /*  489 */  iRegIdst_rule,
  /*  490 */  iRegIdst_rule,
  /*  491 */  iRegNdst_rule,
  /*  492 */  iRegNdst_rule,
  /*  493 */  iRegLdst_rule,
  /*  494 */  iRegLdst_rule,
  /*  495 */  iRegPdst_rule,
  /*  496 */  iRegPdst_rule,
  /*  497 */  iRegIdst_rule,
  /*  498 */  iRegIdst_rule,
  /*  499 */  iRegIdst_rule,
  /*  500 */  iRegIdst_rule,
  /*  501 */  iRegIdst_rule,
  /*  502 */  iRegLdst_rule,
  /*  503 */  iRegIdst_rule,
  /*  504 */  iRegIdst_rule,
  /*  505 */  iRegIdst_rule,
  /*  506 */  iRegIdst_rule,
  /*  507 */  iRegIdst_rule,
  /*  508 */  iRegLdst_rule,
  /*  509 */  iRegPdst_rule,
  /*  510 */  iRegNdst_rule,
  /*  511 */  iRegIdst_rule,
  /*  512 */  0,
  /*  513 */  iRegIdst_rule,
  /*  514 */  iRegIdst_rule,
  /*  515 */  iRegIdst_rule,
  /*  516 */  iRegIdst_rule,
  /*  517 */  iRegIdst_rule,
  /*  518 */  iRegIdst_rule,
  /*  519 */  iRegLdst_rule,
  /*  520 */  0,
  /*  521 */  iRegLdst_rule,
  /*  522 */  iRegLdst_rule,
  /*  523 */  iRegLdst_rule,
  /*  524 */  iRegLdst_rule,
  /*  525 */  iRegIdst_rule,
  /*  526 */  iRegLdst_rule,
  /*  527 */  iRegLdst_rule,
  /*  528 */  iRegPdst_rule,
  /*  529 */  iRegPdst_rule,
  /*  530 */  iRegPdst_rule,
  /*  531 */  iRegIdst_rule,
  /*  532 */  iRegIdst_rule,
  /*  533 */  iRegIdst_rule,
  /*  534 */  iRegLdst_rule,
  /*  535 */  iRegIdst_rule,
  /*  536 */  iRegLdst_rule,
  /*  537 */  iRegIdst_rule,
  /*  538 */  iRegIdst_rule,
  /*  539 */  iRegIdst_rule,
  /*  540 */  iRegLdst_rule,
  /*  541 */  iRegLdst_rule,
  /*  542 */  iRegLdst_rule,
  /*  543 */  iRegIdst_rule,
  /*  544 */  iRegIdst_rule,
  /*  545 */  0,
  /*  546 */  iRegIdst_rule,
  /*  547 */  iRegLdst_rule,
  /*  548 */  iRegLdst_rule,
  /*  549 */  0,
  /*  550 */  iRegLdst_rule,
  /*  551 */  iRegIdst_rule,
  /*  552 */  iRegLdst_rule,
  /*  553 */  0,
  /*  554 */  0,
  /*  555 */  iRegIdst_rule,
  /*  556 */  iRegIdst_rule,
  /*  557 */  iRegIdst_rule,
  /*  558 */  iRegIdst_rule,
  /*  559 */  0,
  /*  560 */  iRegLdst_rule,
  /*  561 */  iRegLdst_rule,
  /*  562 */  iRegLdst_rule,
  /*  563 */  iRegLdst_rule,
  /*  564 */  0,
  /*  565 */  iRegIdst_rule,
  /*  566 */  iRegIdst_rule,
  /*  567 */  0,
  /*  568 */  iRegLdst_rule,
  /*  569 */  iRegLdst_rule,
  /*  570 */  iRegIdst_rule,
  /*  571 */  0,
  /*  572 */  iRegIdst_rule,
  /*  573 */  iRegIdst_rule,
  /*  574 */  0,
  /*  575 */  iRegLdst_rule,
  /*  576 */  iRegLdst_rule,
  /*  577 */  iRegIdst_rule,
  /*  578 */  iRegLdst_rule,
  /*  579 */  iRegIdst_rule,
  /*  580 */  iRegLdst_rule,
  /*  581 */  iRegIdst_rule,
  /*  582 */  iRegIdst_rule,
  /*  583 */  iRegIdst_rule,
  /*  584 */  iRegIdst_rule,
  /*  585 */  iRegIdst_rule,
  /*  586 */  regF_rule,
  /*  587 */  regD_rule,
  /*  588 */  regF_rule,
  /*  589 */  regD_rule,
  /*  590 */  regF_rule,
  /*  591 */  regD_rule,
  /*  592 */  regF_rule,
  /*  593 */  regD_rule,
  /*  594 */  regD_rule,
  /*  595 */  regF_rule,
  /*  596 */  regF_rule,
  /*  597 */  regD_rule,
  /*  598 */  regF_rule,
  /*  599 */  regF_rule,
  /*  600 */  regD_rule,
  /*  601 */  regD_rule,
  /*  602 */  regF_rule,
  /*  603 */  regF_rule,
  /*  604 */  regD_rule,
  /*  605 */  regD_rule,
  /*  606 */  regF_rule,
  /*  607 */  regD_rule,
  /*  608 */  iRegIdst_rule,
  /*  609 */  iRegIdst_rule,
  /*  610 */  iRegIdst_rule,
  /*  611 */  iRegIdst_rule,
  /*  612 */  iRegIdst_rule,
  /*  613 */  iRegIdst_rule,
  /*  614 */  iRegLdst_rule,
  /*  615 */  iRegLdst_rule,
  /*  616 */  iRegLdst_rule,
  /*  617 */  iRegLdst_rule,
  /*  618 */  iRegIdst_rule,
  /*  619 */  iRegIdst_rule,
  /*  620 */  0,
  /*  621 */  iRegIdst_rule,
  /*  622 */  iRegIdst_rule,
  /*  623 */  iRegIdst_rule,
  /*  624 */  iRegIdst_rule,
  /*  625 */  iRegIdst_rule,
  /*  626 */  iRegLdst_rule,
  /*  627 */  iRegIdst_rule,
  /*  628 */  iRegLdst_rule,
  /*  629 */  iRegIdst_rule,
  /*  630 */  0,
  /*  631 */  iRegIdst_rule,
  /*  632 */  iRegIdst_rule,
  /*  633 */  iRegIdst_rule,
  /*  634 */  iRegIdst_rule,
  /*  635 */  iRegIdst_rule,
  /*  636 */  iRegLdst_rule,
  /*  637 */  iRegIdst_rule,
  /*  638 */  iRegLdst_rule,
  /*  639 */  iRegIdst_rule,
  /*  640 */  iRegLdst_rule,
  /*  641 */  iRegIdst_rule,
  /*  642 */  iRegIdst_rule,
  /*  643 */  0,
  /*  644 */  stackSlotI_rule,
  /*  645 */  stackSlotF_rule,
  /*  646 */  0,
  /*  647 */  stackSlotL_rule,
  /*  648 */  stackSlotD_rule,
  /*  649 */  iRegIdst_rule,
  /*  650 */  iRegIdst_rule,
  /*  651 */  iRegIdst_rule,
  /*  652 */  iRegIdst_rule,
  /*  653 */  iRegIdst_rule,
  /*  654 */  iRegIdst_rule,
  /*  655 */  iRegIdst_rule,
  /*  656 */  iRegIdst_rule,
  /*  657 */  iRegIdst_rule,
  /*  658 */  iRegIdst_rule,
  /*  659 */  iRegIdst_rule,
  /*  660 */  iRegLdst_rule,
  /*  661 */  iRegIdst_rule,
  /*  662 */  0,
  /*  663 */  0,
  /*  664 */  0,
  /*  665 */  0,
  /*  666 */  iRegIdst_rule,
  /*  667 */  iRegIdst_rule,
  /*  668 */  iRegIdst_rule,
  /*  669 */  iRegIdst_rule,
  /*  670 */  iRegLdst_rule,
  /*  671 */  iRegLdst_rule,
  /*  672 */  iRegLdst_rule,
  /*  673 */  0,
  /*  674 */  0,
  /*  675 */  0,
  /*  676 */  0,
  /*  677 */  iRegLdst_rule,
  /*  678 */  iRegLdst_rule,
  /*  679 */  iRegLdst_rule,
  /*  680 */  iRegLdst_rule,
  /*  681 */  regF_rule,
  /*  682 */  regF_rule,
  /*  683 */  regF_rule,
  /*  684 */  regF_rule,
  /*  685 */  regF_rule,
  /*  686 */  regF_rule,
  /*  687 */  regD_rule,
  /*  688 */  regD_rule,
  /*  689 */  regD_rule,
  /*  690 */  regD_rule,
  /*  691 */  regD_rule,
  /*  692 */  iRegIdst_rule,
  /*  693 */  Universe_rule,
  /*  694 */  Universe_rule,
  /*  695 */  Universe_rule,
  /*  696 */  Universe_rule,
  /*  697 */  Universe_rule,
  /*  698 */  iRegIdst_rule,
  /*  699 */  iRegIdst_rule,
  /*  700 */  Universe_rule,
  /*  701 */  Universe_rule,
  /*  702 */  Universe_rule,
  /*  703 */  Universe_rule,
  /*  704 */  Universe_rule,
  /*  705 */  Universe_rule,
  /*  706 */  Universe_rule,
  /*  707 */  iRegPdst_rule,
  /*  708 */  iRegPdst_rule,
  /*  709 */  iRegLdst_rule,
  /*  710 */  Universe_rule,
  /*  711 */  Universe_rule,
  /*  712 */  Universe_rule,
  /*  713 */  iRegIdst_rule,
  /*  714 */  iRegIdst_rule,
  /*  715 */  iRegIdst_rule,
  /*  716 */  iRegIdst_rule,
  /*  717 */  iRegIdst_rule,
  /*  718 */  iRegIdst_rule,
  /*  719 */  iRegIdst_rule,
  /*  720 */  iRegIdst_rule,
  /*  721 */  iRegIdst_rule,
  /*  722 */  iRegIdst_rule,
  /*  723 */  iRegIdst_rule,
  /*  724 */  iRegIdst_rule,
  /*  725 */  iRegIdst_rule,
  /*  726 */  iRegIdst_rule,
  /*  727 */  iRegIdst_rule,
  /*  728 */  iRegIdst_rule,
  /*  729 */  iRegIdst_rule,
  /*  730 */  iRegIdst_rule,
  /*  731 */  iRegIdst_rule,
  /*  732 */  iRegIdst_rule,
  /*  733 */  iRegIdst_rule,
  /*  734 */  iRegIdst_rule,
  /*  735 */  Universe_rule,
  /*  736 */  iRegIdst_rule,
  /*  737 */  iRegIdst_rule,
  /*  738 */  iRegIdst_rule,
  /*  739 */  iRegIdst_rule,
  /*  740 */  iRegIdst_rule,
  /*  741 */  iRegIdst_rule,
  /*  742 */  0,
  /*  743 */  0,
  /*  744 */  iRegIdst_rule,
  /*  745 */  iRegLdst_rule,
  /*  746 */  iRegIdst_rule,
  /*  747 */  iRegIdst_rule,
  /*  748 */  iRegIdst_rule,
  /*  749 */  iRegLdst_rule,
  /*  750 */  iRegIdst_rule,
  /*  751 */  iRegIdst_rule,
  /*  752 */  Universe_rule,
  /*  753 */  Universe_rule,
  /*  754 */  Universe_rule,
  /*  755 */  Universe_rule,
  /*  756 */  0,
  /*  757 */  iRegLdst_rule,
  /*  758 */  iRegLdst_rule,
  /*  759 */  iRegLdst_rule,
  /*  760 */  vecX_rule,
  /*  761 */  vecX_rule,
  /*  762 */  vecX_rule,
  /*  763 */  iRegLdst_rule,
  /*  764 */  iRegLdst_rule,
  /*  765 */  iRegLdst_rule,
  /*  766 */  vecX_rule,
  /*  767 */  vecX_rule,
  /*  768 */  vecX_rule,
  /*  769 */  iRegLdst_rule,
  /*  770 */  iRegLdst_rule,
  /*  771 */  iRegLdst_rule,
  /*  772 */  vecX_rule,
  /*  773 */  vecX_rule,
  /*  774 */  vecX_rule,
  /*  775 */  iRegLdst_rule,
  /*  776 */  iRegLdst_rule,
  /*  777 */  iRegLdst_rule,
  /*  778 */  vecX_rule,
  /*  779 */  vecX_rule,
  /*  780 */  vecX_rule,
  /*  781 */  vecX_rule,
  /*  782 */  vecX_rule,
  /*  783 */  vecX_rule,
  /*  784 */  0,
  /*  785 */  0,
  /*  786 */  vecX_rule,
  /*  787 */  vecX_rule,
  /*  788 */  vecX_rule,
  /*  789 */  Universe_rule,
  /*  790 */  Universe_rule,
  /*  791 */  Universe_rule,
  /*  792 */  Universe_rule,
  /*  793 */  Universe_rule,
  /*  794 */  Universe_rule,
  /*  795 */  Universe_rule,
  /*  796 */  Universe_rule,
  /*  797 */  Universe_rule,
  /*  798 */  Universe_rule,
  /*  799 */  Universe_rule,
  /*  800 */  Universe_rule,
  /*  801 */  rarg1RegP_rule,
  /*  802 */  Universe_rule,
  /*  803 */  Universe_rule,
  /*  804 */  0,
  /*  805 */  0,
  /*  806 */  0,
  /*  807 */  0,
  /*  808 */  0,
  /*  809 */  0,
  /*  810 */  0,
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
  /*   76 */  iRegLsrc_rule,
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
  /*   90 */  iRegPsrc_rule,
  /*   91 */  iRegNsrc_rule,
  /*   92 */  iRegNsrc_rule,
  /*   93 */  0,
  /*   94 */  iRegPsrc_rule,
  /*   95 */  iRegPsrc_rule,
  /*   96 */  iRegNsrc_rule,
  /*   97 */  iRegNsrc_rule,
  /*   98 */  _DecodeN_iRegNsrc__rule,
  /*   99 */  _DecodeNKlass_iRegNsrc__rule,
  /*  100 */  _DecodeN_iRegNsrc__rule,
  /*  101 */  _DecodeNKlass_iRegNsrc__rule,
  /*  102 */  0,
  /*  103 */  0,
  /*  104 */  0,
  /*  105 */  0,
  /*  106 */  0,
  /*  107 */  0,
  // last operand
  /*  108 */  0,
  /*  109 */  0,
  /*  110 */  0,
  /*  111 */  0,
  /*  112 */  0,
  /*  113 */  0,
  // last operand class
  /*  114 */  iRegNsrc_rule,
  /*  115 */  iRegNsrc_rule,
  /*  116 */  memory_rule,
  /*  117 */  memory_rule,
  /*  118 */  memory_rule,
  /*  119 */  _LoadI_memory__rule,
  /*  120 */  memoryAlg4_rule,
  /*  121 */  memory_rule,
  /*  122 */  memory_rule,
  /*  123 */  memoryAlg4_rule,
  /*  124 */  indirectMemory_rule,
  /*  125 */  iRegLsrc_rule,
  /*  126 */  flagsRegSrc_rule,
  /*  127 */  _DecodeN_iRegNsrc__rule,
  /*  128 */  iRegLsrc_rule,
  /*  129 */  iRegLsrc_rule,
  /*  130 */  iRegLsrc_rule,
  /*  131 */  cmpOp_rule,
  /*  132 */  iRegIdst_rule,
  /*  133 */  iRegIdst_rule,
  /*  134 */  iRegLdst_rule,
  /*  135 */  iRegLdst_rule,
  /*  136 */  iRegNdst_rule,
  /*  137 */  iRegNdst_rule,
  /*  138 */  iRegPdst_rule,
  /*  139 */  iRegPdst_rule,
  /*  140 */  iRegPdst_rule,
  /*  141 */  regF_rule,
  /*  142 */  regD_rule,
  /*  143 */  iRegLsrc_rule,
  /*  144 */  iRegPsrc_rule,
  /*  145 */  iRegIsrc_rule,
  /*  146 */  iRegIsrc_rule,
  /*  147 */  iRegNsrc_rule,
  /*  148 */  iRegIsrc_rule,
  /*  149 */  _AddI_iRegIsrc_iRegIsrc_rule,
  /*  150 */  iRegIsrc_rule,
  /*  151 */  iRegLsrc_rule,
  /*  152 */  _AddL_iRegLsrc_iRegLsrc_rule,
  /*  153 */  iRegLsrc_rule,
  /*  154 */  iRegLsrc_rule,
  /*  155 */  immL_0_rule,
  /*  156 */  iRegIsrc_rule,
  /*  157 */  iRegIsrc_rule,
  /*  158 */  _RShiftI_iRegIsrc_uimmI5_rule,
  /*  159 */  iRegIsrc_rule,
  /*  160 */  iRegLsrc_rule,
  /*  161 */  iRegLsrc_rule,
  /*  162 */  iRegP_N2P_rule,
  /*  163 */  iRegIsrc_rule,
  /*  164 */  iRegIsrc_rule,
  /*  165 */  iRegIsrc_rule,
  /*  166 */  regF_rule,
  /*  167 */  regD_rule,
  /*  168 */  regF_rule,
  /*  169 */  _ConvF2D_regF__rule,
  /*  170 */  regF_rule,
  /*  171 */  _NegF_regF__rule,
  /*  172 */  regF_rule,
  /*  173 */  regD_rule,
  /*  174 */  _NegD_regD__rule,
  /*  175 */  regD_rule,
  /*  176 */  iRegLsrc_rule,
  /*  177 */  iRegIsrc_rule,
  /*  178 */  _OrI_iRegIsrc_iRegIsrc_rule,
  /*  179 */  iRegIsrc_rule,
  /*  180 */  iRegLsrc_rule,
  /*  181 */  iRegIsrc_rule,
  /*  182 */  _XorI_iRegIsrc_iRegIsrc_rule,
  /*  183 */  iRegIsrc_rule,
  /*  184 */  iRegLsrc_rule,
  /*  185 */  iRegIsrc_rule,
  /*  186 */  iRegIsrc_rule,
  /*  187 */  iRegIsrc_rule,
  /*  188 */  iRegP_N2P_rule,
  /*  189 */  iRegIsrc_rule,
  /*  190 */  iRegIsrc_rule,
  /*  191 */  iRegIsrc_rule,
  /*  192 */  iRegLsrc_rule,
  /*  193 */  iRegLsrc_rule,
  /*  194 */  iRegIsrc_rule,
  /*  195 */  iRegIsrc_rule,
  /*  196 */  iRegNsrc_rule,
  /*  197 */  iRegP_N2P_rule,
  /*  198 */  iRegPsrc_rule,
  /*  199 */  _CastP2X_iRegPsrc__rule,
  /*  200 */  rarg1RegP_rule,
  /*  201 */  rarg2RegP_rule,
  /*  202 */  rarg1RegP_rule,
  /*  203 */  iRegPsrc_rule,
  /*  204 */  immP_rule,
  /*  205 */  _AddP_immP_immL_rule,
  /*  206 */  rscratch2RegP_rule,
  /*  207 */  iRegPsrc_rule,
  /*  208 */  iRegPsrc_rule,
  /*  209 */  iRegPsrc_rule,
  /*  210 */  rarg2RegP_rule,
  /*  211 */  indirect_rule,
  /*  212 */  indirect_rule,
  /*  213 */  indirect_rule,
  /*  214 */  indirect_rule,
  /*  215 */  iRegIsrc_rule,
  /*  216 */  iRegLsrc_rule,
  /*  217 */  iRegIsrc_rule,
  /*  218 */  iRegIsrc_rule,
  // last internally defined operand
  /*  219 */  iRegIsrc_rule,
  /*  220 */  iRegLsrc_rule,
  /*  221 */  immI16_rule,
  /*  222 */  immIhi16_rule,
  /*  223 */  immI_rule,
  /*  224 */  immL16_rule,
  /*  225 */  immL32hi16_rule,
  /*  226 */  immL32_rule,
  /*  227 */  immLhighest16_rule,
  /*  228 */  immL_rule,
  /*  229 */  immN_0_rule,
  /*  230 */  immN_rule,
  /*  231 */  immNKlass_NM_rule,
  /*  232 */  immNKlass_NM_rule,
  /*  233 */  immNKlass_NM_rule,
  /*  234 */  immNKlass_rule,
  /*  235 */  immP_0or1_rule,
  /*  236 */  immP_NM_rule,
  /*  237 */  immP_NM_rule,
  /*  238 */  immP_rule,
  /*  239 */  immF_rule,
  /*  240 */  immD_rule,
  /*  241 */  stackSlotI_rule,
  /*  242 */  stackSlotL_rule,
  /*  243 */  0,
  /*  244 */  _LoadP_memoryAlg4__rule,
  /*  245 */  0,
  /*  246 */  0,
  /*  247 */  0,
  /*  248 */  indirect_rule,
  /*  249 */  indirect_rule,
  /*  250 */  0,
  /*  251 */  iRegIsrc_rule,
  /*  252 */  0,
  /*  253 */  0,
  /*  254 */  regF_rule,
  /*  255 */  regD_rule,
  /*  256 */  regF_rule,
  /*  257 */  regD_rule,
  /*  258 */  _AbsF_regF__rule,
  /*  259 */  _AbsD_regD__rule,
  /*  260 */  regD_rule,
  /*  261 */  regF_rule,
  /*  262 */  iRegLsrc_rule,
  /*  263 */  0,
  /*  264 */  stackSlotF_rule,
  /*  265 */  stackSlotI_rule,
  /*  266 */  stackSlotD_rule,
  /*  267 */  stackSlotL_rule,
  /*  268 */  0,
  /*  269 */  iRegLsrc_rule,
  /*  270 */  iRegP_N2P_rule,
  /*  271 */  iRegPdst_rule,
  /*  272 */  iRegIdst_rule,
  /*  273 */  iRegPdst_rule,
  /*  274 */  iRegIsrc_rule,
  /*  275 */  iRegP_N2P_rule,
  /*  276 */  0,
  /*  277 */  0,
  /*  278 */  0,
  /*  279 */  0,
  /*  280 */  0,
  /*  281 */  0,
  /*  282 */  0,
  /*  283 */  iRegIsrc_rule,
  /*  284 */  iRegIsrc_rule,
  /*  285 */  _AndI_iRegIsrc_uimmI16_rule,
  /*  286 */  iRegLsrc_rule,
  /*  287 */  iRegLsrc_rule,
  /*  288 */  iRegLsrc_rule,
  /*  289 */  iRegLsrc_rule,
  /*  290 */  _AndL_iRegLsrc_iRegLsrc_rule,
  /*  291 */  _AndL_iRegLsrc_uimmL16_rule,
  /*  292 */  0,
  /*  293 */  0,
  /*  294 */  iRegIsrc_rule,
  /*  295 */  iRegIsrc_rule,
  /*  296 */  iRegNsrc_rule,
  /*  297 */  iRegNsrc_rule,
  /*  298 */  iRegP_N2P_rule,
  /*  299 */  iRegP_N2P_rule,
  /*  300 */  iRegPsrc_rule,
  /*  301 */  regF_rule,
  /*  302 */  0,
  /*  303 */  regF_rule,
  /*  304 */  regD_rule,
  /*  305 */  regD_rule,
  /*  306 */  iRegPdst_rule,
  /*  307 */  iRegPdst_rule,
  /*  308 */  iRegPdst_rule,
  /*  309 */  iRegPdst_rule,
  /*  310 */  iRegIsrc_rule,
  /*  311 */  iRegLsrc_rule,
  /*  312 */  iRegIsrc_rule,
  /*  313 */  iRegLsrc_rule,
  /*  314 */  0,
  /*  315 */  iRegIsrc_rule,
  /*  316 */  iRegLsrc_rule,
  /*  317 */  0,
  /*  318 */  0,
  /*  319 */  0,
  /*  320 */  0,
  /*  321 */  iRegLsrc_rule,
  /*  322 */  iRegLsrc_rule,
  /*  323 */  immL_0_rule,
  /*  324 */  iRegLsrc_rule,
  /*  325 */  0,
  /*  326 */  0,
  /*  327 */  0,
  /*  328 */  indirectMemory_rule,
  /*  329 */  indirectMemory_rule,
  /*  330 */  indirectMemory_rule,
  /*  331 */  indirectMemory_rule,
  /*  332 */  indOffset16_rule,
  /*  333 */  indOffset16_rule,
  /*  334 */  indOffset16_rule,
  /*  335 */  indOffset16_rule,
  /*  336 */  memory_rule,
  /*  337 */  memory_rule,
  /*  338 */  _LoadUB_memory__rule,
  /*  339 */  _LoadUB_memory__rule,
  /*  340 */  memory_rule,
  /*  341 */  memory_rule,
  /*  342 */  memory_rule,
  /*  343 */  memory_rule,
  /*  344 */  _LoadUS_memory__rule,
  /*  345 */  _LoadUS_memory__rule,
  /*  346 */  memory_rule,
  /*  347 */  memory_rule,
  /*  348 */  _ConvI2L__LoadI_memory___rule,
  /*  349 */  _LoadI_memoryAlg4__rule,
  /*  350 */  _LoadI_memoryAlg4__rule,
  /*  351 */  memoryAlg4_rule,
  /*  352 */  memoryAlg4_rule,
  /*  353 */  memoryAlg4_rule,
  /*  354 */  memoryAlg4_rule,
  /*  355 */  indirect_rule,
  /*  356 */  memory_rule,
  /*  357 */  memory_rule,
  /*  358 */  memory_rule,
  /*  359 */  _LoadN_memory__rule,
  /*  360 */  _LoadNKlass_memory__rule,
  /*  361 */  memoryAlg4_rule,
  /*  362 */  memoryAlg4_rule,
  /*  363 */  memory_rule,
  /*  364 */  memoryAlg4_rule,
  /*  365 */  memory_rule,
  /*  366 */  memory_rule,
  /*  367 */  memory_rule,
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
  /*  380 */  0,
  /*  381 */  0,
  /*  382 */  0,
  /*  383 */  0,
  /*  384 */  _AddP_indirectMemory_iRegLsrc_rule,
  /*  385 */  indirectMemory_rule,
  /*  386 */  _AddP_indirectMemory_iRegLsrc_rule,
  /*  387 */  indirectMemory_rule,
  /*  388 */  memory_rule,
  /*  389 */  memory_rule,
  /*  390 */  memory_rule,
  /*  391 */  memory_rule,
  /*  392 */  memoryAlg4_rule,
  /*  393 */  memoryAlg4_rule,
  /*  394 */  indirect_rule,
  /*  395 */  memory_rule,
  /*  396 */  memory_rule,
  /*  397 */  memoryAlg4_rule,
  /*  398 */  memory_rule,
  /*  399 */  memory_rule,
  /*  400 */  memory_rule,
  /*  401 */  memory_rule,
  /*  402 */  memory_rule,
  /*  403 */  iRegNsrc_rule,
  /*  404 */  iRegPdst_rule,
  /*  405 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  406 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  407 */  iRegPsrc_rule,
  /*  408 */  iRegPsrc_rule,
  /*  409 */  iRegPsrc_rule,
  /*  410 */  iRegPsrc_rule,
  /*  411 */  iRegPsrc_rule,
  /*  412 */  iRegPsrc_rule,
  /*  413 */  iRegPdst_rule,
  /*  414 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  415 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  416 */  iRegNsrc_rule,
  /*  417 */  iRegNsrc_rule,
  /*  418 */  iRegNsrc_rule,
  /*  419 */  iRegNsrc_rule,
  /*  420 */  iRegNsrc_rule,
  /*  421 */  iRegNsrc_rule,
  /*  422 */  iRegNsrc_rule,
  /*  423 */  _CastP2X__DecodeN_iRegNsrc___rule,
  /*  424 */  iRegNsrc_rule,
  /*  425 */  _Binary_iRegLsrc_iRegPdst_rule,
  /*  426 */  iRegPsrc_rule,
  /*  427 */  _Binary_iRegLsrc_iRegPsrc_rule,
  /*  428 */  iRegPsrc_rule,
  /*  429 */  iRegPsrc_rule,
  /*  430 */  _Binary_iRegLsrc_iRegPdst_rule,
  /*  431 */  _Binary_iRegLsrc_iRegNsrc_rule,
  /*  432 */  iRegNsrc_rule,
  /*  433 */  0,
  /*  434 */  0,
  /*  435 */  0,
  /*  436 */  0,
  /*  437 */  0,
  /*  438 */  0,
  /*  439 */  0,
  /*  440 */  0,
  /*  441 */  0,
  /*  442 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  443 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  444 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  445 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  446 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  447 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  448 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  449 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  450 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  451 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  452 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  453 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  454 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  455 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  456 */  memory_rule,
  /*  457 */  iRegPdst_rule,
  /*  458 */  rarg3RegP_rule,
  /*  459 */  iRegPdst_rule,
  /*  460 */  rarg3RegP_rule,
  /*  461 */  iRegPdst_rule,
  /*  462 */  iRegPdst_rule,
  /*  463 */  iRegPdst_rule,
  /*  464 */  iRegPdst_rule,
  /*  465 */  iRegPdst_rule,
  /*  466 */  rarg3RegP_rule,
  /*  467 */  iRegPdst_rule,
  /*  468 */  rarg3RegP_rule,
  /*  469 */  iRegPdst_rule,
  /*  470 */  rarg3RegP_rule,
  /*  471 */  iRegPdst_rule,
  /*  472 */  rarg3RegP_rule,
  /*  473 */  iRegPdst_rule,
  /*  474 */  iRegPdst_rule,
  /*  475 */  iRegPdst_rule,
  /*  476 */  iRegPdst_rule,
  /*  477 */  iRegPdst_rule,
  /*  478 */  iRegPdst_rule,
  /*  479 */  iRegPdst_rule,
  /*  480 */  iRegPdst_rule,
  /*  481 */  iRegPdst_rule,
  /*  482 */  rarg3RegP_rule,
  /*  483 */  iRegPdst_rule,
  /*  484 */  rarg3RegP_rule,
  /*  485 */  iRegPdst_rule,
  /*  486 */  rarg3RegP_rule,
  /*  487 */  iRegPdst_rule,
  /*  488 */  rarg3RegP_rule,
  /*  489 */  iRegPdst_rule,
  /*  490 */  iRegPdst_rule,
  /*  491 */  iRegPdst_rule,
  /*  492 */  iRegPdst_rule,
  /*  493 */  iRegPdst_rule,
  /*  494 */  iRegPdst_rule,
  /*  495 */  iRegPdst_rule,
  /*  496 */  iRegPdst_rule,
  /*  497 */  iRegPdst_rule,
  /*  498 */  rarg3RegP_rule,
  /*  499 */  iRegPdst_rule,
  /*  500 */  rarg3RegP_rule,
  /*  501 */  iRegPdst_rule,
  /*  502 */  iRegPdst_rule,
  /*  503 */  iRegPdst_rule,
  /*  504 */  rarg3RegP_rule,
  /*  505 */  iRegPdst_rule,
  /*  506 */  rarg3RegP_rule,
  /*  507 */  iRegPdst_rule,
  /*  508 */  iRegPdst_rule,
  /*  509 */  iRegPdst_rule,
  /*  510 */  iRegPdst_rule,
  /*  511 */  iRegIsrc_iRegL2Isrc_rule,
  /*  512 */  0,
  /*  513 */  _AddI__AddI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  514 */  iRegIsrc_rule,
  /*  515 */  _AddI_iRegIsrc__AddI_iRegIsrc_iRegIsrc_rule,
  /*  516 */  iRegIsrc_rule,
  /*  517 */  iRegIsrc_rule,
  /*  518 */  iRegIsrc_rule,
  /*  519 */  iRegLsrc_rule,
  /*  520 */  0,
  /*  521 */  _AddL__AddL_iRegLsrc_iRegLsrc_iRegLsrc_rule,
  /*  522 */  iRegLsrc_rule,
  /*  523 */  _AddL_iRegLsrc__AddL_iRegLsrc_iRegLsrc_rule,
  /*  524 */  iRegLsrc_rule,
  /*  525 */  _AddL_iRegLsrc_iRegLsrc_rule,
  /*  526 */  iRegLsrc_rule,
  /*  527 */  iRegLsrc_rule,
  /*  528 */  iRegP_N2P_rule,
  /*  529 */  iRegP_N2P_rule,
  /*  530 */  iRegP_N2P_rule,
  /*  531 */  iRegIsrc_rule,
  /*  532 */  immI16_rule,
  /*  533 */  immI_0_rule,
  /*  534 */  iRegLsrc_rule,
  /*  535 */  _SubL_iRegLsrc_iRegLsrc_rule,
  /*  536 */  immL_0_rule,
  /*  537 */  _SubL_immL_0_iRegLsrc_rule,
  /*  538 */  iRegIsrc_rule,
  /*  539 */  iRegIsrc_rule,
  /*  540 */  iRegLsrc_rule,
  /*  541 */  iRegLsrc_rule,
  /*  542 */  iRegLsrc_rule,
  /*  543 */  iRegIsrc_rule,
  /*  544 */  iRegIsrc_rule,
  /*  545 */  0,
  /*  546 */  iRegIsrc_rule,
  /*  547 */  iRegLsrc_rule,
  /*  548 */  iRegLsrc_rule,
  /*  549 */  0,
  /*  550 */  iRegLsrc_rule,
  /*  551 */  iRegIsrc_rule,
  /*  552 */  iRegLsrc_rule,
  /*  553 */  0,
  /*  554 */  0,
  /*  555 */  iRegIsrc_rule,
  /*  556 */  iRegIsrc_rule,
  /*  557 */  _AndI_iRegIsrc_immInegpow2_rule,
  /*  558 */  _AndI__RShiftI_iRegIsrc_uimmI5_immInegpow2_rule,
  /*  559 */  0,
  /*  560 */  iRegLsrc_rule,
  /*  561 */  iRegLsrc_rule,
  /*  562 */  _ConvI2L_iRegIsrc__rule,
  /*  563 */  _ConvI2L_iRegIsrc__rule,
  /*  564 */  0,
  /*  565 */  iRegIsrc_rule,
  /*  566 */  iRegIsrc_rule,
  /*  567 */  0,
  /*  568 */  iRegLsrc_rule,
  /*  569 */  iRegLsrc_rule,
  /*  570 */  _RShiftL_iRegLsrc_immI_rule,
  /*  571 */  0,
  /*  572 */  iRegIsrc_rule,
  /*  573 */  iRegIsrc_rule,
  /*  574 */  0,
  /*  575 */  iRegLsrc_rule,
  /*  576 */  iRegLsrc_rule,
  /*  577 */  _URShiftL_iRegLsrc_immI_rule,
  /*  578 */  _CastP2X_iRegP_N2P__rule,
  /*  579 */  _URShiftI_iRegIsrc_immI_rule,
  /*  580 */  _URShiftL_iRegLsrc_immI_rule,
  /*  581 */  _ConvI2L_iRegIsrc__rule,
  /*  582 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  583 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  584 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  585 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  586 */  regF_rule,
  /*  587 */  regD_rule,
  /*  588 */  regF_rule,
  /*  589 */  regD_rule,
  /*  590 */  regF_rule,
  /*  591 */  regD_rule,
  /*  592 */  regF_rule,
  /*  593 */  regD_rule,
  /*  594 */  regD_rule,
  /*  595 */  _SqrtD__ConvF2D_regF___rule,
  /*  596 */  regF_rule,
  /*  597 */  regD_rule,
  /*  598 */  regF_rule,
  /*  599 */  regF_rule,
  /*  600 */  regD_rule,
  /*  601 */  regD_rule,
  /*  602 */  _NegF_regF__rule,
  /*  603 */  _NegF_regF__rule,
  /*  604 */  _NegD_regD__rule,
  /*  605 */  _NegD_regD__rule,
  /*  606 */  _NegF_regF__rule,
  /*  607 */  _NegD_regD__rule,
  /*  608 */  iRegIsrc_rule,
  /*  609 */  iRegIsrc_rule,
  /*  610 */  iRegIsrc_rule,
  /*  611 */  iRegIsrc_rule,
  /*  612 */  iRegIsrc_rule,
  /*  613 */  iRegIsrc_rule,
  /*  614 */  iRegLsrc_rule,
  /*  615 */  iRegLsrc_rule,
  /*  616 */  iRegLsrc_rule,
  /*  617 */  iRegLsrc_rule,
  /*  618 */  _AndL_iRegLsrc_immLpow2minus1_rule,
  /*  619 */  iRegIsrc_rule,
  /*  620 */  0,
  /*  621 */  _OrI__OrI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  622 */  iRegIsrc_rule,
  /*  623 */  _OrI_iRegIsrc__OrI_iRegIsrc_iRegIsrc_rule,
  /*  624 */  iRegIsrc_rule,
  /*  625 */  iRegIsrc_rule,
  /*  626 */  iRegLsrc_rule,
  /*  627 */  _OrL_iRegLsrc_iRegLsrc_rule,
  /*  628 */  iRegLsrc_rule,
  /*  629 */  iRegIsrc_rule,
  /*  630 */  0,
  /*  631 */  _XorI__XorI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  632 */  iRegIsrc_rule,
  /*  633 */  _XorI_iRegIsrc__XorI_iRegIsrc_iRegIsrc_rule,
  /*  634 */  iRegIsrc_rule,
  /*  635 */  iRegIsrc_rule,
  /*  636 */  iRegLsrc_rule,
  /*  637 */  _XorL_iRegLsrc_iRegLsrc_rule,
  /*  638 */  iRegLsrc_rule,
  /*  639 */  iRegIsrc_rule,
  /*  640 */  iRegLsrc_rule,
  /*  641 */  _XorI_iRegIsrc_immI_minus1_rule,
  /*  642 */  iRegIsrc_rule,
  /*  643 */  0,
  /*  644 */  regF_rule,
  /*  645 */  iRegIsrc_rule,
  /*  646 */  0,
  /*  647 */  regD_rule,
  /*  648 */  iRegLsrc_rule,
  /*  649 */  iRegIsrc_rule,
  /*  650 */  _Conv2B_iRegIsrc__rule,
  /*  651 */  _Conv2B_iRegIsrc__rule,
  /*  652 */  _AndI_iRegIsrc_immIpowerOf2_rule,
  /*  653 */  iRegP_N2P_rule,
  /*  654 */  _Conv2B_iRegP_N2P__rule,
  /*  655 */  _Conv2B_iRegP_N2P__rule,
  /*  656 */  iRegIsrc_rule,
  /*  657 */  iRegIsrc_rule,
  /*  658 */  _LShiftI_iRegIsrc_immI_24_rule,
  /*  659 */  _LShiftI_iRegIsrc_immI_16_rule,
  /*  660 */  _ConvL2I_iRegLsrc__rule,
  /*  661 */  iRegLsrc_rule,
  /*  662 */  0,
  /*  663 */  0,
  /*  664 */  0,
  /*  665 */  0,
  /*  666 */  regD_rule,
  /*  667 */  regD_rule,
  /*  668 */  regF_rule,
  /*  669 */  regF_rule,
  /*  670 */  iRegIsrc_rule,
  /*  671 */  _ConvI2L_iRegIsrc__rule,
  /*  672 */  iRegLsrc_rule,
  /*  673 */  0,
  /*  674 */  0,
  /*  675 */  0,
  /*  676 */  0,
  /*  677 */  regF_rule,
  /*  678 */  regF_rule,
  /*  679 */  regD_rule,
  /*  680 */  regD_rule,
  /*  681 */  regD_rule,
  /*  682 */  iRegIsrc_rule,
  /*  683 */  iRegIsrc_rule,
  /*  684 */  iRegIsrc_rule,
  /*  685 */  iRegLsrc_rule,
  /*  686 */  iRegLsrc_rule,
  /*  687 */  iRegIsrc_rule,
  /*  688 */  iRegIsrc_rule,
  /*  689 */  stackSlotL_rule,
  /*  690 */  iRegLsrc_rule,
  /*  691 */  regF_rule,
  /*  692 */  iRegLsrc_rule,
  /*  693 */  cmpOp_rule,
  /*  694 */  cmpOp_rule,
  /*  695 */  cmpOp_rule,
  /*  696 */  cmpOp_rule,
  /*  697 */  cmpOp_rule,
  /*  698 */  regF_rule,
  /*  699 */  regD_rule,
  /*  700 */  0,
  /*  701 */  cmpOp_rule,
  /*  702 */  cmpOp_rule,
  /*  703 */  cmpOp_rule,
  /*  704 */  cmpOp_rule,
  /*  705 */  cmpOp_rule,
  /*  706 */  cmpOp_rule,
  /*  707 */  iRegP_N2P_rule,
  /*  708 */  _AndL__CastP2X_iRegPsrc__immLnegpow2_rule,
  /*  709 */  _CastP2X_iRegPsrc__rule,
  /*  710 */  immLmax30_rule,
  /*  711 */  immL_rule,
  /*  712 */  rarg1RegL_rule,
  /*  713 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  714 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  715 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  716 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  717 */  _Binary_rarg1RegP_rarg2RegP_rule,
  /*  718 */  _Binary_rarg1RegP_rarg2RegP_rule,
  /*  719 */  rarg1RegP_rule,
  /*  720 */  rarg1RegP_rule,
  /*  721 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  722 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  723 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  724 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  725 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  726 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  727 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  728 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  729 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  730 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  731 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  732 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  733 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  734 */  rarg1RegP_rule,
  /*  735 */  rarg1RegP_rule,
  /*  736 */  rarg1RegP_rule,
  /*  737 */  rarg1RegP_rule,
  /*  738 */  iRegIsrc_rule,
  /*  739 */  iRegIsrc_rule,
  /*  740 */  iRegIsrc_rule,
  /*  741 */  iRegIsrc_rule,
  /*  742 */  0,
  /*  743 */  0,
  /*  744 */  iRegIsrc_rule,
  /*  745 */  iRegLsrc_rule,
  /*  746 */  iRegIsrc_rule,
  /*  747 */  iRegIsrc_rule,
  /*  748 */  _LoadI_indirect__rule,
  /*  749 */  _LoadL_indirect__rule,
  /*  750 */  _LoadUS_indirect__rule,
  /*  751 */  _LoadS_indirect__rule,
  /*  752 */  indirect_rule,
  /*  753 */  indirect_rule,
  /*  754 */  indirect_rule,
  /*  755 */  indirect_rule,
  /*  756 */  0,
  /*  757 */  iRegIsrc_rule,
  /*  758 */  immI_0_rule,
  /*  759 */  immI_minus1_rule,
  /*  760 */  iRegIsrc_rule,
  /*  761 */  immI_0_rule,
  /*  762 */  immI_minus1_rule,
  /*  763 */  iRegIsrc_rule,
  /*  764 */  immI_0_rule,
  /*  765 */  immI_minus1_rule,
  /*  766 */  iRegIsrc_rule,
  /*  767 */  immI_0_rule,
  /*  768 */  immI_minus1_rule,
  /*  769 */  iRegIsrc_rule,
  /*  770 */  immI_0_rule,
  /*  771 */  immI_minus1_rule,
  /*  772 */  iRegIsrc_rule,
  /*  773 */  immI_0_rule,
  /*  774 */  immI_minus1_rule,
  /*  775 */  regF_rule,
  /*  776 */  immF_rule,
  /*  777 */  immF_0_rule,
  /*  778 */  regF_rule,
  /*  779 */  immF_rule,
  /*  780 */  immF_0_rule,
  /*  781 */  regD_rule,
  /*  782 */  immI_0_rule,
  /*  783 */  immI_minus1_rule,
  /*  784 */  0,
  /*  785 */  0,
  /*  786 */  iRegLsrc_rule,
  /*  787 */  immI_0_rule,
  /*  788 */  immI_minus1_rule,
  /*  789 */  iRegPdst_rule,
  /*  790 */  0,
  /*  791 */  0,
  /*  792 */  0,
  /*  793 */  0,
  /*  794 */  0,
  /*  795 */  0,
  /*  796 */  0,
  /*  797 */  0,
  /*  798 */  iRegPdstNoScratch_rule,
  /*  799 */  0,
  /*  800 */  iRegPdstNoScratch_rule,
  /*  801 */  0,
  /*  802 */  0,
  /*  803 */  0,
  /*  804 */  0,
  /*  805 */  0,
  /*  806 */  0,
  /*  807 */  0,
  /*  808 */  0,
  /*  809 */  0,
  /*  810 */  0,
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
  /*   94 */  immL16_rule,
  /*   95 */  immL16Alg4_rule,
  /*   96 */  0,
  /*   97 */  0,
  /*   98 */  immL16_rule,
  /*   99 */  immL16_rule,
  /*  100 */  immL16Alg4_rule,
  /*  101 */  immL16Alg4_rule,
  /*  102 */  0,
  /*  103 */  0,
  /*  104 */  0,
  /*  105 */  0,
  /*  106 */  0,
  /*  107 */  0,
  // last operand
  /*  108 */  0,
  /*  109 */  0,
  /*  110 */  0,
  /*  111 */  0,
  /*  112 */  0,
  /*  113 */  0,
  // last operand class
  /*  114 */  0,
  /*  115 */  0,
  /*  116 */  0,
  /*  117 */  0,
  /*  118 */  0,
  /*  119 */  0,
  /*  120 */  0,
  /*  121 */  0,
  /*  122 */  0,
  /*  123 */  0,
  /*  124 */  iRegLsrc_rule,
  /*  125 */  0,
  /*  126 */  iRegPsrc_rule,
  /*  127 */  0,
  /*  128 */  iRegPdst_rule,
  /*  129 */  iRegPsrc_rule,
  /*  130 */  iRegNsrc_rule,
  /*  131 */  flagsRegSrc_rule,
  /*  132 */  iRegIsrc_rule,
  /*  133 */  immI16_rule,
  /*  134 */  iRegLsrc_rule,
  /*  135 */  immL16_rule,
  /*  136 */  iRegNsrc_rule,
  /*  137 */  immN_0_rule,
  /*  138 */  iRegPsrc_rule,
  /*  139 */  iRegP_N2P_rule,
  /*  140 */  immP_0_rule,
  /*  141 */  regF_rule,
  /*  142 */  regD_rule,
  /*  143 */  iRegLsrc_rule,
  /*  144 */  iRegPsrc_rule,
  /*  145 */  iRegIsrc_rule,
  /*  146 */  rarg4RegI_rule,
  /*  147 */  iRegNsrc_rule,
  /*  148 */  iRegIsrc_rule,
  /*  149 */  iRegIsrc_rule,
  /*  150 */  _AddI_iRegIsrc_iRegIsrc_rule,
  /*  151 */  iRegLsrc_rule,
  /*  152 */  iRegLsrc_rule,
  /*  153 */  _AddL_iRegLsrc_iRegLsrc_rule,
  /*  154 */  iRegLsrc_rule,
  /*  155 */  iRegLsrc_rule,
  /*  156 */  immInegpow2_rule,
  /*  157 */  uimmI5_rule,
  /*  158 */  immInegpow2_rule,
  /*  159 */  0,
  /*  160 */  immI_rule,
  /*  161 */  immI_rule,
  /*  162 */  0,
  /*  163 */  immI_rule,
  /*  164 */  immI8_rule,
  /*  165 */  immI8_rule,
  /*  166 */  0,
  /*  167 */  0,
  /*  168 */  0,
  /*  169 */  0,
  /*  170 */  0,
  /*  171 */  regF_rule,
  /*  172 */  _NegF_regF__rule,
  /*  173 */  0,
  /*  174 */  regD_rule,
  /*  175 */  _NegD_regD__rule,
  /*  176 */  immLpow2minus1_rule,
  /*  177 */  iRegIsrc_rule,
  /*  178 */  iRegIsrc_rule,
  /*  179 */  _OrI_iRegIsrc_iRegIsrc_rule,
  /*  180 */  iRegLsrc_rule,
  /*  181 */  iRegIsrc_rule,
  /*  182 */  iRegIsrc_rule,
  /*  183 */  _XorI_iRegIsrc_iRegIsrc_rule,
  /*  184 */  iRegLsrc_rule,
  /*  185 */  immI_minus1_rule,
  /*  186 */  0,
  /*  187 */  immIpowerOf2_rule,
  /*  188 */  0,
  /*  189 */  immI_24_rule,
  /*  190 */  immI_16_rule,
  /*  191 */  uimmI16_rule,
  /*  192 */  iRegLsrc_rule,
  /*  193 */  uimmL16_rule,
  /*  194 */  uimmI15_rule,
  /*  195 */  iRegIsrc_rule,
  /*  196 */  immN_0_rule,
  /*  197 */  immP_0_rule,
  /*  198 */  0,
  /*  199 */  immLnegpow2_rule,
  /*  200 */  rarg3RegI_rule,
  /*  201 */  rarg4RegI_rule,
  /*  202 */  rarg2RegP_rule,
  /*  203 */  iRegIsrc_rule,
  /*  204 */  immL_rule,
  /*  205 */  immI_1_rule,
  /*  206 */  immI_1_rule,
  /*  207 */  rscratch1RegI_rule,
  /*  208 */  uimmI15_rule,
  /*  209 */  rscratch2RegI_rule,
  /*  210 */  iRegIsrc_rule,
  /*  211 */  0,
  /*  212 */  0,
  /*  213 */  0,
  /*  214 */  0,
  /*  215 */  0,
  /*  216 */  0,
  /*  217 */  0,
  /*  218 */  0,
  // last internally defined operand
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
  /*  248 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  249 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  250 */  0,
  /*  251 */  0,
  /*  252 */  0,
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
  /*  263 */  0,
  /*  264 */  0,
  /*  265 */  0,
  /*  266 */  0,
  /*  267 */  0,
  /*  268 */  0,
  /*  269 */  0,
  /*  270 */  0,
  /*  271 */  0,
  /*  272 */  0,
  /*  273 */  0,
  /*  274 */  0,
  /*  275 */  0,
  /*  276 */  0,
  /*  277 */  0,
  /*  278 */  0,
  /*  279 */  0,
  /*  280 */  0,
  /*  281 */  0,
  /*  282 */  0,
  /*  283 */  iRegIsrc_rule,
  /*  284 */  immI16_rule,
  /*  285 */  immI_0_rule,
  /*  286 */  iRegLsrc_rule,
  /*  287 */  immL16_rule,
  /*  288 */  iRegLsrc_rule,
  /*  289 */  uimmL16_rule,
  /*  290 */  immL_0_rule,
  /*  291 */  immL_0_rule,
  /*  292 */  0,
  /*  293 */  0,
  /*  294 */  iRegIsrc_rule,
  /*  295 */  uimmI16_rule,
  /*  296 */  iRegNsrc_rule,
  /*  297 */  immN_0_rule,
  /*  298 */  iRegP_N2P_rule,
  /*  299 */  immP_0or1_rule,
  /*  300 */  immL16_rule,
  /*  301 */  regF_rule,
  /*  302 */  0,
  /*  303 */  regF_rule,
  /*  304 */  regD_rule,
  /*  305 */  regD_rule,
  /*  306 */  iRegPdst_rule,
  /*  307 */  rarg2RegP_rule,
  /*  308 */  iRegPdst_rule,
  /*  309 */  iRegPdst_rule,
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
  /*  321 */  iRegLsrc_rule,
  /*  322 */  iRegLsrc_rule,
  /*  323 */  iRegLsrc_rule,
  /*  324 */  iRegLsrc_rule,
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
  /*  348 */  immL_32bits_rule,
  /*  349 */  0,
  /*  350 */  0,
  /*  351 */  0,
  /*  352 */  0,
  /*  353 */  0,
  /*  354 */  0,
  /*  355 */  0,
  /*  356 */  0,
  /*  357 */  0,
  /*  358 */  0,
  /*  359 */  0,
  /*  360 */  0,
  /*  361 */  0,
  /*  362 */  0,
  /*  363 */  0,
  /*  364 */  0,
  /*  365 */  0,
  /*  366 */  0,
  /*  367 */  0,
  /*  368 */  0,
  /*  369 */  0,
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
  /*  380 */  0,
  /*  381 */  0,
  /*  382 */  0,
  /*  383 */  0,
  /*  384 */  0,
  /*  385 */  0,
  /*  386 */  0,
  /*  387 */  0,
  /*  388 */  iRegIsrc_rule,
  /*  389 */  iRegIsrc_rule,
  /*  390 */  iRegIsrc_rule,
  /*  391 */  _ConvL2I_iRegLsrc__rule,
  /*  392 */  iRegLsrc_rule,
  /*  393 */  iRegLsrc_rule,
  /*  394 */  vecX_rule,
  /*  395 */  iRegN_P2N_rule,
  /*  396 */  iRegN_P2N_rule,
  /*  397 */  iRegPsrc_rule,
  /*  398 */  regF_rule,
  /*  399 */  regD_rule,
  /*  400 */  iRegLdst_rule,
  /*  401 */  immI_0_rule,
  /*  402 */  immI_0_rule,
  /*  403 */  0,
  /*  404 */  0,
  /*  405 */  0,
  /*  406 */  0,
  /*  407 */  0,
  /*  408 */  0,
  /*  409 */  0,
  /*  410 */  0,
  /*  411 */  0,
  /*  412 */  0,
  /*  413 */  0,
  /*  414 */  0,
  /*  415 */  0,
  /*  416 */  0,
  /*  417 */  0,
  /*  418 */  0,
  /*  419 */  0,
  /*  420 */  0,
  /*  421 */  0,
  /*  422 */  0,
  /*  423 */  0,
  /*  424 */  0,
  /*  425 */  0,
  /*  426 */  0,
  /*  427 */  0,
  /*  428 */  0,
  /*  429 */  0,
  /*  430 */  0,
  /*  431 */  0,
  /*  432 */  0,
  /*  433 */  0,
  /*  434 */  0,
  /*  435 */  0,
  /*  436 */  0,
  /*  437 */  0,
  /*  438 */  0,
  /*  439 */  0,
  /*  440 */  0,
  /*  441 */  0,
  /*  442 */  _Binary_iRegIdst_iRegIsrc_rule,
  /*  443 */  _Binary_iRegIdst_iRegIsrc_rule,
  /*  444 */  _Binary_iRegIdst_immI16_rule,
  /*  445 */  _Binary_iRegLdst_iRegLsrc_rule,
  /*  446 */  _Binary_iRegLdst_iRegLsrc_rule,
  /*  447 */  _Binary_iRegLdst_immL16_rule,
  /*  448 */  _Binary_iRegNdst_iRegNsrc_rule,
  /*  449 */  _Binary_iRegNdst_iRegNsrc_rule,
  /*  450 */  _Binary_iRegNdst_immN_0_rule,
  /*  451 */  _Binary_iRegPdst_iRegPsrc_rule,
  /*  452 */  _Binary_iRegPdst_iRegP_N2P_rule,
  /*  453 */  _Binary_iRegPdst_immP_0_rule,
  /*  454 */  _Binary_regF_regF_rule,
  /*  455 */  _Binary_regD_regD_rule,
  /*  456 */  0,
  /*  457 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  458 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  459 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  460 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  461 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  462 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  463 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  464 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  465 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  466 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  467 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  468 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  469 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  470 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  471 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  472 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  473 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  474 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  475 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  476 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  477 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  478 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  479 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  480 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  481 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  482 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  483 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  484 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  485 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  486 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  487 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  488 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  489 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  490 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  491 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  492 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  493 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  494 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  495 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  496 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  497 */  iRegIsrc_rule,
  /*  498 */  iRegIsrc_rule,
  /*  499 */  iRegIsrc_rule,
  /*  500 */  iRegIsrc_rule,
  /*  501 */  iRegIsrc_rule,
  /*  502 */  iRegLsrc_rule,
  /*  503 */  iRegIsrc_rule,
  /*  504 */  iRegIsrc_rule,
  /*  505 */  iRegIsrc_rule,
  /*  506 */  iRegIsrc_rule,
  /*  507 */  iRegIsrc_rule,
  /*  508 */  iRegLsrc_rule,
  /*  509 */  iRegPsrc_rule,
  /*  510 */  iRegNsrc_rule,
  /*  511 */  iRegIsrc_iRegL2Isrc_rule,
  /*  512 */  0,
  /*  513 */  iRegIsrc_rule,
  /*  514 */  _AddI__AddI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  515 */  iRegIsrc_rule,
  /*  516 */  _AddI_iRegIsrc__AddI_iRegIsrc_iRegIsrc_rule,
  /*  517 */  immI16_rule,
  /*  518 */  immIhi16_rule,
  /*  519 */  iRegLsrc_rule,
  /*  520 */  0,
  /*  521 */  iRegLsrc_rule,
  /*  522 */  _AddL__AddL_iRegLsrc_iRegLsrc_iRegLsrc_rule,
  /*  523 */  iRegLsrc_rule,
  /*  524 */  _AddL_iRegLsrc__AddL_iRegLsrc_iRegLsrc_rule,
  /*  525 */  0,
  /*  526 */  immL16_rule,
  /*  527 */  immL32hi16_rule,
  /*  528 */  iRegLsrc_rule,
  /*  529 */  immL16_rule,
  /*  530 */  immL32hi16_rule,
  /*  531 */  iRegIsrc_rule,
  /*  532 */  iRegIsrc_rule,
  /*  533 */  iRegIsrc_rule,
  /*  534 */  iRegLsrc_rule,
  /*  535 */  0,
  /*  536 */  iRegLsrc_rule,
  /*  537 */  0,
  /*  538 */  iRegIsrc_rule,
  /*  539 */  immI16_rule,
  /*  540 */  iRegLsrc_rule,
  /*  541 */  iRegLsrc_rule,
  /*  542 */  immL16_rule,
  /*  543 */  immI_minus1_rule,
  /*  544 */  iRegIsrc_rule,
  /*  545 */  0,
  /*  546 */  iRegIsrc_rule,
  /*  547 */  immL_minus1_rule,
  /*  548 */  iRegLsrc_rule,
  /*  549 */  0,
  /*  550 */  iRegLsrc_rule,
  /*  551 */  iRegIsrc_rule,
  /*  552 */  iRegLsrc_rule,
  /*  553 */  0,
  /*  554 */  0,
  /*  555 */  iRegIsrc_rule,
  /*  556 */  immI_rule,
  /*  557 */  uimmI5_rule,
  /*  558 */  uimmI5_rule,
  /*  559 */  0,
  /*  560 */  iRegIsrc_rule,
  /*  561 */  immI_rule,
  /*  562 */  uimmI6_ge32_rule,
  /*  563 */  uimmI6_rule,
  /*  564 */  0,
  /*  565 */  iRegIsrc_rule,
  /*  566 */  immI_rule,
  /*  567 */  0,
  /*  568 */  iRegIsrc_rule,
  /*  569 */  immI_rule,
  /*  570 */  0,
  /*  571 */  0,
  /*  572 */  iRegIsrc_rule,
  /*  573 */  immI_rule,
  /*  574 */  0,
  /*  575 */  iRegIsrc_rule,
  /*  576 */  immI_rule,
  /*  577 */  0,
  /*  578 */  uimmI6_rule,
  /*  579 */  immIpow2minus1_rule,
  /*  580 */  immLpow2minus1_rule,
  /*  581 */  0,
  /*  582 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  583 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  584 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  585 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  586 */  regF_rule,
  /*  587 */  regD_rule,
  /*  588 */  regF_rule,
  /*  589 */  regD_rule,
  /*  590 */  regF_rule,
  /*  591 */  regD_rule,
  /*  592 */  regF_rule,
  /*  593 */  regD_rule,
  /*  594 */  0,
  /*  595 */  0,
  /*  596 */  _Binary_regF_regF_rule,
  /*  597 */  _Binary_regD_regD_rule,
  /*  598 */  _Binary__NegF_regF__regF_rule,
  /*  599 */  _Binary_regF__NegF_regF__rule,
  /*  600 */  _Binary__NegD_regD__regD_rule,
  /*  601 */  _Binary_regD__NegD_regD__rule,
  /*  602 */  _Binary__NegF_regF__regF_rule,
  /*  603 */  _Binary_regF__NegF_regF__rule,
  /*  604 */  _Binary__NegD_regD__regD_rule,
  /*  605 */  _Binary_regD__NegD_regD__rule,
  /*  606 */  _Binary_regF_regF_rule,
  /*  607 */  _Binary_regD_regD_rule,
  /*  608 */  iRegIsrc_rule,
  /*  609 */  immIhi16_rule,
  /*  610 */  uimmI16_rule,
  /*  611 */  immInegpow2_rule,
  /*  612 */  immIpow2minus1_rule,
  /*  613 */  immIpowerOf2_rule,
  /*  614 */  iRegLsrc_rule,
  /*  615 */  uimmL16_rule,
  /*  616 */  immLnegpow2_rule,
  /*  617 */  immLpow2minus1_rule,
  /*  618 */  0,
  /*  619 */  iRegIsrc_rule,
  /*  620 */  0,
  /*  621 */  iRegIsrc_rule,
  /*  622 */  _OrI__OrI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  623 */  iRegIsrc_rule,
  /*  624 */  _OrI_iRegIsrc__OrI_iRegIsrc_iRegIsrc_rule,
  /*  625 */  uimmI16_rule,
  /*  626 */  iRegLsrc_rule,
  /*  627 */  0,
  /*  628 */  uimmL16_rule,
  /*  629 */  iRegIsrc_rule,
  /*  630 */  0,
  /*  631 */  iRegIsrc_rule,
  /*  632 */  _XorI__XorI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  633 */  iRegIsrc_rule,
  /*  634 */  _XorI_iRegIsrc__XorI_iRegIsrc_iRegIsrc_rule,
  /*  635 */  uimmI16_rule,
  /*  636 */  iRegLsrc_rule,
  /*  637 */  0,
  /*  638 */  uimmL16_rule,
  /*  639 */  immI_minus1_rule,
  /*  640 */  immL_minus1_rule,
  /*  641 */  iRegIsrc_rule,
  /*  642 */  _XorI_iRegIsrc_immI_minus1_rule,
  /*  643 */  0,
  /*  644 */  0,
  /*  645 */  0,
  /*  646 */  0,
  /*  647 */  0,
  /*  648 */  0,
  /*  649 */  0,
  /*  650 */  immI_1_rule,
  /*  651 */  immI_1_rule,
  /*  652 */  0,
  /*  653 */  0,
  /*  654 */  immI_1_rule,
  /*  655 */  immI_1_rule,
  /*  656 */  iRegIsrc_rule,
  /*  657 */  immI_0_rule,
  /*  658 */  immI_24_rule,
  /*  659 */  immI_16_rule,
  /*  660 */  0,
  /*  661 */  0,
  /*  662 */  0,
  /*  663 */  0,
  /*  664 */  0,
  /*  665 */  0,
  /*  666 */  0,
  /*  667 */  0,
  /*  668 */  0,
  /*  669 */  0,
  /*  670 */  0,
  /*  671 */  immL_32bits_rule,
  /*  672 */  immL_32bits_rule,
  /*  673 */  0,
  /*  674 */  0,
  /*  675 */  0,
  /*  676 */  0,
  /*  677 */  0,
  /*  678 */  0,
  /*  679 */  0,
  /*  680 */  0,
  /*  681 */  0,
  /*  682 */  0,
  /*  683 */  0,
  /*  684 */  0,
  /*  685 */  0,
  /*  686 */  0,
  /*  687 */  0,
  /*  688 */  0,
  /*  689 */  0,
  /*  690 */  0,
  /*  691 */  0,
  /*  692 */  iRegLsrc_rule,
  /*  693 */  _CmpU_iRegIsrc_uimmI15_rule,
  /*  694 */  _CmpU_iRegIsrc_iRegIsrc_rule,
  /*  695 */  _CmpU_iRegIsrc_uimmI15_rule,
  /*  696 */  _CmpN_iRegNsrc_immN_0_rule,
  /*  697 */  _CmpP_iRegP_N2P_immP_0_rule,
  /*  698 */  regF_rule,
  /*  699 */  regD_rule,
  /*  700 */  0,
  /*  701 */  flagsRegSrc_rule,
  /*  702 */  flagsRegSrc_rule,
  /*  703 */  flagsRegSrc_rule,
  /*  704 */  flagsRegSrc_rule,
  /*  705 */  flagsRegSrc_rule,
  /*  706 */  flagsRegSrc_rule,
  /*  707 */  iRegP_N2P_rule,
  /*  708 */  0,
  /*  709 */  _CastP2X_iRegPsrc__rule,
  /*  710 */  rarg2RegP_rule,
  /*  711 */  rarg2RegP_rule,
  /*  712 */  rarg2RegP_rule,
  /*  713 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  714 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  715 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  716 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  717 */  rarg3RegI_rule,
  /*  718 */  rarg3RegI_rule,
  /*  719 */  rarg2RegP_rule,
  /*  720 */  rarg2RegP_rule,
  /*  721 */  _Binary__AddP_immP_immL_immI_1_rule,
  /*  722 */  _Binary__AddP_immP_immL_immI_1_rule,
  /*  723 */  _Binary__AddP_immP_immL_immI_1_rule,
  /*  724 */  _Binary_rscratch2RegP_immI_1_rule,
  /*  725 */  _Binary_rscratch2RegP_immI_1_rule,
  /*  726 */  _Binary_rscratch2RegP_immI_1_rule,
  /*  727 */  iRegIsrc_rule,
  /*  728 */  _Binary_iRegPsrc_uimmI15_rule,
  /*  729 */  _Binary_iRegPsrc_uimmI15_rule,
  /*  730 */  _Binary_iRegPsrc_uimmI15_rule,
  /*  731 */  _Binary_iRegPsrc_rscratch2RegI_rule,
  /*  732 */  _Binary_iRegPsrc_rscratch2RegI_rule,
  /*  733 */  _Binary_iRegPsrc_rscratch2RegI_rule,
  /*  734 */  _Binary_rarg2RegP_iRegIsrc_rule,
  /*  735 */  _Binary_rarg2RegP_iRegIsrc_rule,
  /*  736 */  iRegIsrc_rule,
  /*  737 */  _Binary_rarg2RegP_iRegIsrc_rule,
  /*  738 */  iRegIsrc_rule,
  /*  739 */  iRegIsrc_rule,
  /*  740 */  iRegIsrc_rule,
  /*  741 */  iRegIsrc_rule,
  /*  742 */  0,
  /*  743 */  0,
  /*  744 */  0,
  /*  745 */  0,
  /*  746 */  0,
  /*  747 */  0,
  /*  748 */  0,
  /*  749 */  0,
  /*  750 */  0,
  /*  751 */  0,
  /*  752 */  _ReverseBytesI_iRegIsrc__rule,
  /*  753 */  _ReverseBytesL_iRegLsrc__rule,
  /*  754 */  _ReverseBytesUS_iRegIsrc__rule,
  /*  755 */  _ReverseBytesS_iRegIsrc__rule,
  /*  756 */  0,
  /*  757 */  0,
  /*  758 */  0,
  /*  759 */  0,
  /*  760 */  0,
  /*  761 */  0,
  /*  762 */  0,
  /*  763 */  0,
  /*  764 */  0,
  /*  765 */  0,
  /*  766 */  0,
  /*  767 */  0,
  /*  768 */  0,
  /*  769 */  0,
  /*  770 */  0,
  /*  771 */  0,
  /*  772 */  0,
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
  /*  785 */  0,
  /*  786 */  0,
  /*  787 */  0,
  /*  788 */  0,
  /*  789 */  0,
  /*  790 */  0,
  /*  791 */  0,
  /*  792 */  0,
  /*  793 */  0,
  /*  794 */  0,
  /*  795 */  0,
  /*  796 */  0,
  /*  797 */  0,
  /*  798 */  inline_cache_regP_rule,
  /*  799 */  0,
  /*  800 */  rarg1RegP_rule,
  /*  801 */  0,
  /*  802 */  0,
  /*  803 */  0,
  /*  804 */  0,
  /*  805 */  0,
  /*  806 */  0,
  /*  807 */  0,
  /*  808 */  0,
  /*  809 */  0,
  /*  810 */  0,
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
  /*    9 */  "IMMI",
  /*   10 */  "IMMI8",
  /*   11 */  "IMMI16",
  /*   12 */  "IMMIHI16",
  /*   13 */  "IMMINEGPOW2",
  /*   14 */  "IMMIPOW2MINUS1",
  /*   15 */  "IMMIPOWEROF2",
  /*   16 */  "UIMMI5",
  /*   17 */  "UIMMI6",
  /*   18 */  "UIMMI6_GE32",
  /*   19 */  "UIMMI15",
  /*   20 */  "UIMMI16",
  /*   21 */  "IMMI_0",
  /*   22 */  "IMMI_1",
  /*   23 */  "IMMI_MINUS1",
  /*   24 */  "IMMI_16",
  /*   25 */  "IMMI_24",
  /*   26 */  "IMMN",
  /*   27 */  "IMMN_0",
  /*   28 */  "IMMNKLASS",
  /*   29 */  "IMMNKLASS_NM",
  /*   30 */  "IMMP",
  /*   31 */  "IMMP_NM",
  /*   32 */  "IMMP_0",
  /*   33 */  "IMMP_0OR1",
  /*   34 */  "IMML",
  /*   35 */  "IMMLMAX30",
  /*   36 */  "IMML16",
  /*   37 */  "IMML16ALG4",
  /*   38 */  "IMML32HI16",
  /*   39 */  "IMML32",
  /*   40 */  "IMMLHIGHEST16",
  /*   41 */  "IMMLNEGPOW2",
  /*   42 */  "IMMLPOW2MINUS1",
  /*   43 */  "IMML_0",
  /*   44 */  "IMML_MINUS1",
  /*   45 */  "IMML_32BITS",
  /*   46 */  "UIMML16",
  /*   47 */  "IMMF",
  /*   48 */  "IMMF_0",
  /*   49 */  "IMMD",
  /*   50 */  "IREGIDST",
  /*   51 */  "IREGISRC",
  /*   52 */  "RSCRATCH1REGI",
  /*   53 */  "RSCRATCH2REGI",
  /*   54 */  "RARG1REGI",
  /*   55 */  "RARG2REGI",
  /*   56 */  "RARG3REGI",
  /*   57 */  "RARG4REGI",
  /*   58 */  "RARG1REGL",
  /*   59 */  "RARG2REGL",
  /*   60 */  "RARG3REGL",
  /*   61 */  "RARG4REGL",
  /*   62 */  "IREGPDST",
  /*   63 */  "IREGPDSTNOSCRATCH",
  /*   64 */  "IREGPSRC",
  /*   65 */  "THREADREGP",
  /*   66 */  "RSCRATCH1REGP",
  /*   67 */  "RSCRATCH2REGP",
  /*   68 */  "RARG1REGP",
  /*   69 */  "RARG2REGP",
  /*   70 */  "RARG3REGP",
  /*   71 */  "RARG4REGP",
  /*   72 */  "IREGNSRC",
  /*   73 */  "IREGNDST",
  /*   74 */  "IREGLDST",
  /*   75 */  "IREGLSRC",
  /*   76 */  "IREGL2ISRC",
  /*   77 */  "RSCRATCH1REGL",
  /*   78 */  "RSCRATCH2REGL",
  /*   79 */  "FLAGSREG",
  /*   80 */  "FLAGSREGSRC",
  /*   81 */  "FLAGSREGCR0",
  /*   82 */  "FLAGSREGCR1",
  /*   83 */  "FLAGSREGCR6",
  /*   84 */  "REGCTR",
  /*   85 */  "REGD",
  /*   86 */  "REGF",
  /*   87 */  "INLINE_CACHE_REGP",
  /*   88 */  "COMPILER_METHOD_OOP_REGP",
  /*   89 */  "INTERPRETER_METHOD_OOP_REGP",
  /*   90 */  "IREGP2N",
  /*   91 */  "IREGN2P",
  /*   92 */  "IREGN2P_KLASS",
  /*   93 */  "INDIRECT",
  /*   94 */  "INDOFFSET16",
  /*   95 */  "INDOFFSET16ALG4",
  /*   96 */  "INDIRECTNARROW",
  /*   97 */  "INDIRECTNARROW_KLASS",
  /*   98 */  "INDOFFSET16NARROW",
  /*   99 */  "INDOFFSET16NARROW_KLASS",
  /*  100 */  "INDOFFSET16NARROWALG4",
  /*  101 */  "INDOFFSET16NARROWALG4_KLASS",
  /*  102 */  "STACKSLOTI",
  /*  103 */  "STACKSLOTL",
  /*  104 */  "STACKSLOTP",
  /*  105 */  "STACKSLOTF",
  /*  106 */  "STACKSLOTD",
  /*  107 */  "CMPOP",
  // last operand
  /*  108 */  "MEMORY",
  /*  109 */  "MEMORYALG4",
  /*  110 */  "INDIRECTMEMORY",
  /*  111 */  "IREGISRC_IREGL2ISRC",
  /*  112 */  "IREGN_P2N",
  /*  113 */  "IREGP_N2P",
  // last operand class
  /*  114 */  "_DecodeN_iRegNsrc_",
  /*  115 */  "_DecodeNKlass_iRegNsrc_",
  /*  116 */  "_LoadUB_memory_",
  /*  117 */  "_LoadUS_memory_",
  /*  118 */  "_LoadI_memory_",
  /*  119 */  "_ConvI2L__LoadI_memory__",
  /*  120 */  "_LoadI_memoryAlg4_",
  /*  121 */  "_LoadN_memory_",
  /*  122 */  "_LoadNKlass_memory_",
  /*  123 */  "_LoadP_memoryAlg4_",
  /*  124 */  "_AddP_indirectMemory_iRegLsrc",
  /*  125 */  "_ConvL2I_iRegLsrc_",
  /*  126 */  "_Binary_flagsRegSrc_iRegPsrc",
  /*  127 */  "_CastP2X__DecodeN_iRegNsrc__",
  /*  128 */  "_Binary_iRegLsrc_iRegPdst",
  /*  129 */  "_Binary_iRegLsrc_iRegPsrc",
  /*  130 */  "_Binary_iRegLsrc_iRegNsrc",
  /*  131 */  "_Binary_cmpOp_flagsRegSrc",
  /*  132 */  "_Binary_iRegIdst_iRegIsrc",
  /*  133 */  "_Binary_iRegIdst_immI16",
  /*  134 */  "_Binary_iRegLdst_iRegLsrc",
  /*  135 */  "_Binary_iRegLdst_immL16",
  /*  136 */  "_Binary_iRegNdst_iRegNsrc",
  /*  137 */  "_Binary_iRegNdst_immN_0",
  /*  138 */  "_Binary_iRegPdst_iRegPsrc",
  /*  139 */  "_Binary_iRegPdst_iRegP_N2P",
  /*  140 */  "_Binary_iRegPdst_immP_0",
  /*  141 */  "_Binary_regF_regF",
  /*  142 */  "_Binary_regD_regD",
  /*  143 */  "_Binary_iRegLsrc_iRegLsrc",
  /*  144 */  "_Binary_iRegPsrc_iRegPsrc",
  /*  145 */  "_Binary_iRegIsrc_iRegIsrc",
  /*  146 */  "_Binary_iRegIsrc_rarg4RegI",
  /*  147 */  "_Binary_iRegNsrc_iRegNsrc",
  /*  148 */  "_AddI_iRegIsrc_iRegIsrc",
  /*  149 */  "_AddI__AddI_iRegIsrc_iRegIsrc_iRegIsrc",
  /*  150 */  "_AddI_iRegIsrc__AddI_iRegIsrc_iRegIsrc",
  /*  151 */  "_AddL_iRegLsrc_iRegLsrc",
  /*  152 */  "_AddL__AddL_iRegLsrc_iRegLsrc_iRegLsrc",
  /*  153 */  "_AddL_iRegLsrc__AddL_iRegLsrc_iRegLsrc",
  /*  154 */  "_SubL_iRegLsrc_iRegLsrc",
  /*  155 */  "_SubL_immL_0_iRegLsrc",
  /*  156 */  "_AndI_iRegIsrc_immInegpow2",
  /*  157 */  "_RShiftI_iRegIsrc_uimmI5",
  /*  158 */  "_AndI__RShiftI_iRegIsrc_uimmI5_immInegpow2",
  /*  159 */  "_ConvI2L_iRegIsrc_",
  /*  160 */  "_RShiftL_iRegLsrc_immI",
  /*  161 */  "_URShiftL_iRegLsrc_immI",
  /*  162 */  "_CastP2X_iRegP_N2P_",
  /*  163 */  "_URShiftI_iRegIsrc_immI",
  /*  164 */  "_LShiftI_iRegIsrc_immI8",
  /*  165 */  "_URShiftI_iRegIsrc_immI8",
  /*  166 */  "_AbsF_regF_",
  /*  167 */  "_AbsD_regD_",
  /*  168 */  "_ConvF2D_regF_",
  /*  169 */  "_SqrtD__ConvF2D_regF__",
  /*  170 */  "_NegF_regF_",
  /*  171 */  "_Binary__NegF_regF__regF",
  /*  172 */  "_Binary_regF__NegF_regF_",
  /*  173 */  "_NegD_regD_",
  /*  174 */  "_Binary__NegD_regD__regD",
  /*  175 */  "_Binary_regD__NegD_regD_",
  /*  176 */  "_AndL_iRegLsrc_immLpow2minus1",
  /*  177 */  "_OrI_iRegIsrc_iRegIsrc",
  /*  178 */  "_OrI__OrI_iRegIsrc_iRegIsrc_iRegIsrc",
  /*  179 */  "_OrI_iRegIsrc__OrI_iRegIsrc_iRegIsrc",
  /*  180 */  "_OrL_iRegLsrc_iRegLsrc",
  /*  181 */  "_XorI_iRegIsrc_iRegIsrc",
  /*  182 */  "_XorI__XorI_iRegIsrc_iRegIsrc_iRegIsrc",
  /*  183 */  "_XorI_iRegIsrc__XorI_iRegIsrc_iRegIsrc",
  /*  184 */  "_XorL_iRegLsrc_iRegLsrc",
  /*  185 */  "_XorI_iRegIsrc_immI_minus1",
  /*  186 */  "_Conv2B_iRegIsrc_",
  /*  187 */  "_AndI_iRegIsrc_immIpowerOf2",
  /*  188 */  "_Conv2B_iRegP_N2P_",
  /*  189 */  "_LShiftI_iRegIsrc_immI_24",
  /*  190 */  "_LShiftI_iRegIsrc_immI_16",
  /*  191 */  "_AndI_iRegIsrc_uimmI16",
  /*  192 */  "_AndL_iRegLsrc_iRegLsrc",
  /*  193 */  "_AndL_iRegLsrc_uimmL16",
  /*  194 */  "_CmpU_iRegIsrc_uimmI15",
  /*  195 */  "_CmpU_iRegIsrc_iRegIsrc",
  /*  196 */  "_CmpN_iRegNsrc_immN_0",
  /*  197 */  "_CmpP_iRegP_N2P_immP_0",
  /*  198 */  "_CastP2X_iRegPsrc_",
  /*  199 */  "_AndL__CastP2X_iRegPsrc__immLnegpow2",
  /*  200 */  "_Binary_rarg1RegP_rarg3RegI",
  /*  201 */  "_Binary_rarg2RegP_rarg4RegI",
  /*  202 */  "_Binary_rarg1RegP_rarg2RegP",
  /*  203 */  "_Binary_iRegPsrc_iRegIsrc",
  /*  204 */  "_AddP_immP_immL",
  /*  205 */  "_Binary__AddP_immP_immL_immI_1",
  /*  206 */  "_Binary_rscratch2RegP_immI_1",
  /*  207 */  "_Binary_iRegPsrc_rscratch1RegI",
  /*  208 */  "_Binary_iRegPsrc_uimmI15",
  /*  209 */  "_Binary_iRegPsrc_rscratch2RegI",
  /*  210 */  "_Binary_rarg2RegP_iRegIsrc",
  /*  211 */  "_LoadI_indirect_",
  /*  212 */  "_LoadL_indirect_",
  /*  213 */  "_LoadUS_indirect_",
  /*  214 */  "_LoadS_indirect_",
  /*  215 */  "_ReverseBytesI_iRegIsrc_",
  /*  216 */  "_ReverseBytesL_iRegLsrc_",
  /*  217 */  "_ReverseBytesUS_iRegIsrc_",
  /*  218 */  "_ReverseBytesS_iRegIsrc_",
  // last internally defined operand
  /*  219 */  "regI_to_stkI",
  /*  220 */  "regL_to_stkL",
  /*  221 */  "loadConI16",
  /*  222 */  "loadConIhi16",
  /*  223 */  "loadConI_Ex",
  /*  224 */  "loadConL16",
  /*  225 */  "loadConL32hi16",
  /*  226 */  "loadConL32_Ex",
  /*  227 */  "loadConLhighest16_Ex",
  /*  228 */  "loadConL_Ex",
  /*  229 */  "loadConN0",
  /*  230 */  "loadConN_Ex",
  /*  231 */  "loadConNKlass_hi",
  /*  232 */  "loadConNKlass_mask",
  /*  233 */  "loadConNKlass_lo",
  /*  234 */  "loadConNKlass_Ex",
  /*  235 */  "loadConP0or1",
  /*  236 */  "loadConP",
  /*  237 */  "loadConP_lo",
  /*  238 */  "loadConP_Ex",
  /*  239 */  "loadConF_Ex",
  /*  240 */  "loadConD_Ex",
  /*  241 */  "stkI_to_regI",
  /*  242 */  "stkL_to_regL",
  /*  243 */  "convB2I_reg_2",
  /*  244 */  "loadP2X",
  /*  245 */  "loadToc_lo",
  /*  246 */  "loadConN_hi",
  /*  247 */  "clearMs32b",
  /*  248 */  "storeLConditional_regP_regL_regL",
  /*  249 */  "storePConditional_regP_regP_regP",
  /*  250 */  "signmask32I_regI",
  /*  251 */  "absI_reg_Ex",
  /*  252 */  "signmask64I_regL",
  /*  253 */  "signmask64L_regL",
  /*  254 */  "absF_reg",
  /*  255 */  "absD_reg",
  /*  256 */  "negF_reg",
  /*  257 */  "negD_reg",
  /*  258 */  "negF_absF_reg",
  /*  259 */  "negD_absD_reg",
  /*  260 */  "roundDouble_nop",
  /*  261 */  "roundFloat_nop",
  /*  262 */  "moveL2D_reg",
  /*  263 */  "moveI2D_reg",
  /*  264 */  "moveF2I_stack_reg",
  /*  265 */  "moveI2F_stack_reg",
  /*  266 */  "moveD2L_stack_reg",
  /*  267 */  "moveL2D_stack_reg",
  /*  268 */  "moveReg",
  /*  269 */  "castX2P",
  /*  270 */  "castP2X",
  /*  271 */  "castPP",
  /*  272 */  "castII",
  /*  273 */  "checkCastPP",
  /*  274 */  "convI2Bool_reg__cntlz_Ex",
  /*  275 */  "convP2Bool_reg__cntlz_Ex",
  /*  276 */  "extsh",
  /*  277 */  "convD2IRaw_regD",
  /*  278 */  "convF2IRaw_regF",
  /*  279 */  "convF2LRaw_regF",
  /*  280 */  "convD2LRaw_regD",
  /*  281 */  "convL2DRaw_regD",
  /*  282 */  "convL2FRaw_regF",
  /*  283 */  "cmpI_reg_reg",
  /*  284 */  "cmpI_reg_imm16",
  /*  285 */  "testI_reg_imm",
  /*  286 */  "cmpL_reg_reg",
  /*  287 */  "cmpL_reg_imm16",
  /*  288 */  "cmpUL_reg_reg",
  /*  289 */  "cmpUL_reg_imm16",
  /*  290 */  "testL_reg_reg",
  /*  291 */  "testL_reg_imm",
  /*  292 */  "cmovI_conIvalueMinus1_conIvalue1",
  /*  293 */  "cmovI_conIvalueMinus1_conIvalue0_conIvalue1_Ex",
  /*  294 */  "compU_reg_reg",
  /*  295 */  "compU_reg_uimm16",
  /*  296 */  "cmpN_reg_reg",
  /*  297 */  "cmpN_reg_imm0",
  /*  298 */  "cmpP_reg_reg",
  /*  299 */  "cmpP_reg_null",
  /*  300 */  "cmpP_reg_imm16",
  /*  301 */  "cmpFUnordered_reg_reg",
  /*  302 */  "cmov_bns_less",
  /*  303 */  "cmpF_reg_reg_Ex",
  /*  304 */  "cmpDUnordered_reg_reg",
  /*  305 */  "cmpD_reg_reg_Ex",
  /*  306 */  "cmpFastLock",
  /*  307 */  "cmpFastLock_tm",
  /*  308 */  "cmpFastUnlock",
  /*  309 */  "cmpFastUnlock_tm",
  /*  310 */  "popCountI",
  /*  311 */  "popCountL",
  /*  312 */  "countLeadingZerosI",
  /*  313 */  "countLeadingZerosL",
  /*  314 */  "countLeadingZerosP",
  /*  315 */  "countTrailingZerosI_Ex",
  /*  316 */  "countTrailingZerosL_Ex",
  /*  317 */  "mtvsrwz",
  /*  318 */  "repl32",
  /*  319 */  "repl48",
  /*  320 */  "repl56",
  /*  321 */  "overflowAddL_reg_reg",
  /*  322 */  "overflowSubL_reg_reg",
  /*  323 */  "overflowNegL_reg",
  /*  324 */  "overflowMulL_reg_reg",
  /*  325 */  "mtvsrd",
  /*  326 */  "CallLeafDirect_mtctr",
  /*  327 */  "tlsLoadP",
  /*  328 */  "loadUB_indirect",
  /*  329 */  "loadUB_indirect_ac",
  /*  330 */  "loadB_indirect_Ex",
  /*  331 */  "loadB_indirect_ac_Ex",
  /*  332 */  "loadUB_indOffset16",
  /*  333 */  "loadUB_indOffset16_ac",
  /*  334 */  "loadB_indOffset16_Ex",
  /*  335 */  "loadB_indOffset16_ac_Ex",
  /*  336 */  "loadUB",
  /*  337 */  "loadUB_ac",
  /*  338 */  "loadUB2L",
  /*  339 */  "loadUB2L_ac",
  /*  340 */  "loadS",
  /*  341 */  "loadS_ac",
  /*  342 */  "loadUS",
  /*  343 */  "loadUS_ac",
  /*  344 */  "loadUS2L",
  /*  345 */  "loadUS2L_ac",
  /*  346 */  "loadI",
  /*  347 */  "loadI_ac",
  /*  348 */  "loadUI2L",
  /*  349 */  "loadI2L",
  /*  350 */  "loadI2L_ac",
  /*  351 */  "loadL",
  /*  352 */  "loadL_ac",
  /*  353 */  "loadL_unaligned",
  /*  354 */  "loadV8",
  /*  355 */  "loadV16",
  /*  356 */  "loadRange",
  /*  357 */  "loadN",
  /*  358 */  "loadN_ac",
  /*  359 */  "loadN2P_unscaled",
  /*  360 */  "loadN2P_klass_unscaled",
  /*  361 */  "loadP",
  /*  362 */  "loadP_ac",
  /*  363 */  "loadNKlass",
  /*  364 */  "loadKlass",
  /*  365 */  "loadF",
  /*  366 */  "loadF_ac",
  /*  367 */  "loadD",
  /*  368 */  "loadD_ac",
  /*  369 */  "loadD_unaligned",
  /*  370 */  "loadToc_hi",
  /*  371 */  "loadConI32_lo16",
  /*  372 */  "loadConL32_lo16",
  /*  373 */  "loadConL",
  /*  374 */  "loadConL_hi",
  /*  375 */  "loadConL_lo",
  /*  376 */  "loadConN_lo",
  /*  377 */  "rldicl",
  /*  378 */  "loadBase",
  /*  379 */  "loadConP_hi",
  /*  380 */  "loadConF",
  /*  381 */  "loadConFComp",
  /*  382 */  "loadConD",
  /*  383 */  "loadConDComp",
  /*  384 */  "prefetch_alloc_zero",
  /*  385 */  "prefetch_alloc_zero_no_offset",
  /*  386 */  "prefetch_alloc",
  /*  387 */  "prefetch_alloc_no_offset",
  /*  388 */  "storeB",
  /*  389 */  "storeC",
  /*  390 */  "storeI",
  /*  391 */  "storeI_convL2I",
  /*  392 */  "storeL",
  /*  393 */  "storeA8B",
  /*  394 */  "storeV16",
  /*  395 */  "storeN",
  /*  396 */  "storeNKlass",
  /*  397 */  "storeP",
  /*  398 */  "storeF",
  /*  399 */  "storeD",
  /*  400 */  "storeCM_CMS",
  /*  401 */  "storeCM_CMS_ExEx",
  /*  402 */  "storeCM_G1",
  /*  403 */  "encodeP_shift",
  /*  404 */  "encodeP_sub",
  /*  405 */  "cond_sub_base",
  /*  406 */  "cond_set_0_oop",
  /*  407 */  "encodeP_Disjoint",
  /*  408 */  "encodeP_Ex",
  /*  409 */  "encodeP_not_null_Ex",
  /*  410 */  "encodeP_not_null_base_null",
  /*  411 */  "encodeP_narrow_oop_shift_0",
  /*  412 */  "decodeN_shift",
  /*  413 */  "decodeN_add",
  /*  414 */  "cond_add_base",
  /*  415 */  "cond_set_0_ptr",
  /*  416 */  "decodeN_Ex",
  /*  417 */  "decodeN_nullBase",
  /*  418 */  "decodeN_mergeDisjoint",
  /*  419 */  "decodeN_Disjoint_notNull_Ex",
  /*  420 */  "decodeN_Disjoint_isel_Ex",
  /*  421 */  "decodeN_notNull_addBase_Ex",
  /*  422 */  "decodeN_unscaled",
  /*  423 */  "decodeN2I_unscaled",
  /*  424 */  "encodePKlass_shift",
  /*  425 */  "encodePKlass_sub_base",
  /*  426 */  "encodePKlass_Disjoint",
  /*  427 */  "encodePKlass_not_null_Ex",
  /*  428 */  "encodePKlass_not_null_ExEx",
  /*  429 */  "decodeNKlass_shift",
  /*  430 */  "decodeNKlass_add_base",
  /*  431 */  "decodeNKlass_notNull_addBase_Ex",
  /*  432 */  "decodeNKlass_notNull_addBase_ExEx",
  /*  433 */  "membar_acquire",
  /*  434 */  "unnecessary_membar_acquire",
  /*  435 */  "membar_acquire_lock",
  /*  436 */  "membar_release",
  /*  437 */  "membar_release_0",
  /*  438 */  "membar_storestore",
  /*  439 */  "membar_release_lock",
  /*  440 */  "membar_volatile",
  /*  441 */  "membar_CPUOrder",
  /*  442 */  "cmovI_reg_isel",
  /*  443 */  "cmovI_reg",
  /*  444 */  "cmovI_imm",
  /*  445 */  "cmovL_reg_isel",
  /*  446 */  "cmovL_reg",
  /*  447 */  "cmovL_imm",
  /*  448 */  "cmovN_reg_isel",
  /*  449 */  "cmovN_reg",
  /*  450 */  "cmovN_imm",
  /*  451 */  "cmovP_reg_isel",
  /*  452 */  "cmovP_reg",
  /*  453 */  "cmovP_imm",
  /*  454 */  "cmovF_reg",
  /*  455 */  "cmovD_reg",
  /*  456 */  "loadPLocked",
  /*  457 */  "compareAndSwapB_regP_regI_regI",
  /*  458 */  "compareAndSwapB4_regP_regI_regI",
  /*  459 */  "compareAndSwapS_regP_regI_regI",
  /*  460 */  "compareAndSwapS4_regP_regI_regI",
  /*  461 */  "compareAndSwapI_regP_regI_regI",
  /*  462 */  "compareAndSwapN_regP_regN_regN",
  /*  463 */  "compareAndSwapL_regP_regL_regL",
  /*  464 */  "compareAndSwapP_regP_regP_regP",
  /*  465 */  "weakCompareAndSwapB_regP_regI_regI",
  /*  466 */  "weakCompareAndSwapB4_regP_regI_regI",
  /*  467 */  "weakCompareAndSwapB_acq_regP_regI_regI",
  /*  468 */  "weakCompareAndSwapB4_acq_regP_regI_regI",
  /*  469 */  "weakCompareAndSwapS_regP_regI_regI",
  /*  470 */  "weakCompareAndSwapS4_regP_regI_regI",
  /*  471 */  "weakCompareAndSwapS_acq_regP_regI_regI",
  /*  472 */  "weakCompareAndSwapS4_acq_regP_regI_regI",
  /*  473 */  "weakCompareAndSwapI_regP_regI_regI",
  /*  474 */  "weakCompareAndSwapI_acq_regP_regI_regI",
  /*  475 */  "weakCompareAndSwapN_regP_regN_regN",
  /*  476 */  "weakCompareAndSwapN_acq_regP_regN_regN",
  /*  477 */  "weakCompareAndSwapL_regP_regL_regL",
  /*  478 */  "weakCompareAndSwapL_acq_regP_regL_regL",
  /*  479 */  "weakCompareAndSwapP_regP_regP_regP",
  /*  480 */  "weakCompareAndSwapP_acq_regP_regP_regP",
  /*  481 */  "compareAndExchangeB_regP_regI_regI",
  /*  482 */  "compareAndExchangeB4_regP_regI_regI",
  /*  483 */  "compareAndExchangeB_acq_regP_regI_regI",
  /*  484 */  "compareAndExchangeB4_acq_regP_regI_regI",
  /*  485 */  "compareAndExchangeS_regP_regI_regI",
  /*  486 */  "compareAndExchangeS4_regP_regI_regI",
  /*  487 */  "compareAndExchangeS_acq_regP_regI_regI",
  /*  488 */  "compareAndExchangeS4_acq_regP_regI_regI",
  /*  489 */  "compareAndExchangeI_regP_regI_regI",
  /*  490 */  "compareAndExchangeI_acq_regP_regI_regI",
  /*  491 */  "compareAndExchangeN_regP_regN_regN",
  /*  492 */  "compareAndExchangeN_acq_regP_regN_regN",
  /*  493 */  "compareAndExchangeL_regP_regL_regL",
  /*  494 */  "compareAndExchangeL_acq_regP_regL_regL",
  /*  495 */  "compareAndExchangeP_regP_regP_regP",
  /*  496 */  "compareAndExchangeP_acq_regP_regP_regP",
  /*  497 */  "getAndAddB",
  /*  498 */  "getAndAddB4",
  /*  499 */  "getAndAddS",
  /*  500 */  "getAndAddS4",
  /*  501 */  "getAndAddI",
  /*  502 */  "getAndAddL",
  /*  503 */  "getAndSetB",
  /*  504 */  "getAndSetB4",
  /*  505 */  "getAndSetS",
  /*  506 */  "getAndSetS4",
  /*  507 */  "getAndSetI",
  /*  508 */  "getAndSetL",
  /*  509 */  "getAndSetP",
  /*  510 */  "getAndSetN",
  /*  511 */  "addI_reg_reg",
  /*  512 */  "addI_reg_reg_2",
  /*  513 */  "tree_addI_addI_addI_reg_reg_Ex",
  /*  514 */  "tree_addI_addI_addI_reg_reg_Ex_1",
  /*  515 */  "tree_addI_addI_addI_reg_reg_Ex_0",
  /*  516 */  "tree_addI_addI_addI_reg_reg_Ex_2",
  /*  517 */  "addI_reg_imm16",
  /*  518 */  "addI_reg_immhi16",
  /*  519 */  "addL_reg_reg",
  /*  520 */  "addL_reg_reg_2",
  /*  521 */  "tree_addL_addL_addL_reg_reg_Ex",
  /*  522 */  "tree_addL_addL_addL_reg_reg_Ex_1",
  /*  523 */  "tree_addL_addL_addL_reg_reg_Ex_0",
  /*  524 */  "tree_addL_addL_addL_reg_reg_Ex_2",
  /*  525 */  "addI_regL_regL",
  /*  526 */  "addL_reg_imm16",
  /*  527 */  "addL_reg_immhi16",
  /*  528 */  "addP_reg_reg",
  /*  529 */  "addP_reg_imm16",
  /*  530 */  "addP_reg_immhi16",
  /*  531 */  "subI_reg_reg",
  /*  532 */  "subI_imm16_reg",
  /*  533 */  "negI_regI",
  /*  534 */  "subL_reg_reg",
  /*  535 */  "subI_regL_regL",
  /*  536 */  "negL_reg_reg",
  /*  537 */  "negI_con0_regL",
  /*  538 */  "mulI_reg_reg",
  /*  539 */  "mulI_reg_imm16",
  /*  540 */  "mulL_reg_reg",
  /*  541 */  "mulHighL_reg_reg",
  /*  542 */  "mulL_reg_imm16",
  /*  543 */  "divI_reg_immIvalueMinus1",
  /*  544 */  "divI_reg_regnotMinus1",
  /*  545 */  "cmovI_bne_negI_reg",
  /*  546 */  "divI_reg_reg_Ex",
  /*  547 */  "divL_reg_immLvalueMinus1",
  /*  548 */  "divL_reg_regnotMinus1",
  /*  549 */  "cmovL_bne_negL_reg",
  /*  550 */  "divL_reg_reg_Ex",
  /*  551 */  "modI_reg_reg_Ex",
  /*  552 */  "modL_reg_reg_Ex",
  /*  553 */  "maskI_reg_imm",
  /*  554 */  "lShiftI_reg_reg",
  /*  555 */  "lShiftI_reg_reg_Ex",
  /*  556 */  "lShiftI_reg_imm",
  /*  557 */  "lShiftI_andI_immInegpow2_imm5",
  /*  558 */  "lShiftI_andI_immInegpow2_rShiftI_imm5",
  /*  559 */  "lShiftL_regL_regI",
  /*  560 */  "lShiftL_regL_regI_Ex",
  /*  561 */  "lshiftL_regL_immI",
  /*  562 */  "lShiftL_regI_immGE32",
  /*  563 */  "scaledPositiveI2L_lShiftL_convI2L_reg_imm6",
  /*  564 */  "arShiftI_reg_reg",
  /*  565 */  "arShiftI_reg_reg_Ex",
  /*  566 */  "arShiftI_reg_imm",
  /*  567 */  "arShiftL_regL_regI",
  /*  568 */  "arShiftL_regL_regI_Ex",
  /*  569 */  "arShiftL_regL_immI",
  /*  570 */  "convL2I_arShiftL_regL_immI",
  /*  571 */  "urShiftI_reg_reg",
  /*  572 */  "urShiftI_reg_reg_Ex",
  /*  573 */  "urShiftI_reg_imm",
  /*  574 */  "urShiftL_regL_regI",
  /*  575 */  "urShiftL_regL_regI_Ex",
  /*  576 */  "urShiftL_regL_immI",
  /*  577 */  "convL2I_urShiftL_regL_immI",
  /*  578 */  "shrP_convP2X_reg_imm6",
  /*  579 */  "andI_urShiftI_regI_immI_immIpow2minus1",
  /*  580 */  "andL_urShiftL_regL_immI_immLpow2minus1",
  /*  581 */  "sxtI_reg",
  /*  582 */  "rotlI_reg_immi8",
  /*  583 */  "rotlI_reg_immi8_0",
  /*  584 */  "rotrI_reg_immi8",
  /*  585 */  "rotrI_reg_immi8_0",
  /*  586 */  "addF_reg_reg",
  /*  587 */  "addD_reg_reg",
  /*  588 */  "subF_reg_reg",
  /*  589 */  "subD_reg_reg",
  /*  590 */  "mulF_reg_reg",
  /*  591 */  "mulD_reg_reg",
  /*  592 */  "divF_reg_reg",
  /*  593 */  "divD_reg_reg",
  /*  594 */  "sqrtD_reg",
  /*  595 */  "sqrtF_reg",
  /*  596 */  "maddF_reg_reg",
  /*  597 */  "maddD_reg_reg",
  /*  598 */  "mnsubF_reg_reg",
  /*  599 */  "mnsubF_reg_reg_0",
  /*  600 */  "mnsubD_reg_reg",
  /*  601 */  "mnsubD_reg_reg_0",
  /*  602 */  "mnaddF_reg_reg",
  /*  603 */  "mnaddF_reg_reg_0",
  /*  604 */  "mnaddD_reg_reg",
  /*  605 */  "mnaddD_reg_reg_0",
  /*  606 */  "msubF_reg_reg",
  /*  607 */  "msubD_reg_reg",
  /*  608 */  "andI_reg_reg",
  /*  609 */  "andI_reg_immIhi16",
  /*  610 */  "andI_reg_uimm16",
  /*  611 */  "andI_reg_immInegpow2",
  /*  612 */  "andI_reg_immIpow2minus1",
  /*  613 */  "andI_reg_immIpowerOf2",
  /*  614 */  "andL_reg_reg",
  /*  615 */  "andL_reg_uimm16",
  /*  616 */  "andL_reg_immLnegpow2",
  /*  617 */  "andL_reg_immLpow2minus1",
  /*  618 */  "convL2I_andL_reg_immLpow2minus1",
  /*  619 */  "orI_reg_reg",
  /*  620 */  "orI_reg_reg_2",
  /*  621 */  "tree_orI_orI_orI_reg_reg_Ex",
  /*  622 */  "tree_orI_orI_orI_reg_reg_Ex_1",
  /*  623 */  "tree_orI_orI_orI_reg_reg_Ex_0",
  /*  624 */  "tree_orI_orI_orI_reg_reg_Ex_2",
  /*  625 */  "orI_reg_uimm16",
  /*  626 */  "orL_reg_reg",
  /*  627 */  "orI_regL_regL",
  /*  628 */  "orL_reg_uimm16",
  /*  629 */  "xorI_reg_reg",
  /*  630 */  "xorI_reg_reg_2",
  /*  631 */  "tree_xorI_xorI_xorI_reg_reg_Ex",
  /*  632 */  "tree_xorI_xorI_xorI_reg_reg_Ex_1",
  /*  633 */  "tree_xorI_xorI_xorI_reg_reg_Ex_0",
  /*  634 */  "tree_xorI_xorI_xorI_reg_reg_Ex_2",
  /*  635 */  "xorI_reg_uimm16",
  /*  636 */  "xorL_reg_reg",
  /*  637 */  "xorI_regL_regL",
  /*  638 */  "xorL_reg_uimm16",
  /*  639 */  "notI_reg",
  /*  640 */  "notL_reg",
  /*  641 */  "andcI_reg_reg",
  /*  642 */  "andcI_reg_reg_0",
  /*  643 */  "andcL_reg_reg",
  /*  644 */  "moveF2I_reg_stack",
  /*  645 */  "moveI2F_reg_stack",
  /*  646 */  "moveF2L_reg_stack",
  /*  647 */  "moveD2L_reg_stack",
  /*  648 */  "moveL2D_reg_stack",
  /*  649 */  "convI2Bool_reg__cmove",
  /*  650 */  "xorI_convI2Bool_reg_immIvalue1__cntlz_Ex",
  /*  651 */  "xorI_convI2Bool_reg_immIvalue1__cmove",
  /*  652 */  "convI2Bool_andI_reg_immIpowerOf2",
  /*  653 */  "convP2Bool_reg__cmove",
  /*  654 */  "xorI_convP2Bool_reg__cntlz_Ex",
  /*  655 */  "xorI_convP2Bool_reg_immIvalue1__cmove",
  /*  656 */  "cmpLTMask_reg_reg_Ex",
  /*  657 */  "cmpLTMask_reg_immI0",
  /*  658 */  "convB2I_reg",
  /*  659 */  "convS2I_reg",
  /*  660 */  "sxtI_L2L_reg",
  /*  661 */  "convL2I_reg",
  /*  662 */  "cmovI_bso_stackSlotL",
  /*  663 */  "cmovI_bso_reg",
  /*  664 */  "cmovI_bso_stackSlotL_conLvalue0_Ex",
  /*  665 */  "cmovI_bso_reg_conLvalue0_Ex",
  /*  666 */  "convD2I_reg_ExEx",
  /*  667 */  "convD2I_reg_mffprd_ExEx",
  /*  668 */  "convF2I_regF_ExEx",
  /*  669 */  "convF2I_regF_mffprd_ExEx",
  /*  670 */  "convI2L_reg",
  /*  671 */  "zeroExtendL_regI",
  /*  672 */  "zeroExtendL_regL",
  /*  673 */  "cmovL_bso_stackSlotL",
  /*  674 */  "cmovL_bso_reg",
  /*  675 */  "cmovL_bso_stackSlotL_conLvalue0_Ex",
  /*  676 */  "cmovL_bso_reg_conLvalue0_Ex",
  /*  677 */  "convF2L_reg_ExEx",
  /*  678 */  "convF2L_reg_mffprd_ExEx",
  /*  679 */  "convD2L_reg_ExEx",
  /*  680 */  "convD2L_reg_mffprd_ExEx",
  /*  681 */  "convD2F_reg",
  /*  682 */  "convI2F_ireg_Ex",
  /*  683 */  "convI2F_ireg_fcfids_Ex",
  /*  684 */  "convI2F_ireg_mtfprd_Ex",
  /*  685 */  "convL2F_ireg_fcfids_Ex",
  /*  686 */  "convL2F_ireg_mtfprd_Ex",
  /*  687 */  "convI2D_reg_Ex",
  /*  688 */  "convI2D_reg_mtfprd_Ex",
  /*  689 */  "convL2D_reg_Ex",
  /*  690 */  "convL2D_reg_mtfprd_Ex",
  /*  691 */  "convF2D_reg",
  /*  692 */  "cmpL3_reg_reg_ExEx",
  /*  693 */  "rangeCheck_iReg_uimm15",
  /*  694 */  "rangeCheck_iReg_iReg",
  /*  695 */  "rangeCheck_uimm15_iReg",
  /*  696 */  "zeroCheckN_iReg_imm0",
  /*  697 */  "zeroCheckP_reg_imm0",
  /*  698 */  "cmpF3_reg_reg_ExEx",
  /*  699 */  "cmpD3_reg_reg_ExEx",
  /*  700 */  "branch",
  /*  701 */  "branchCon",
  /*  702 */  "branchConFar",
  /*  703 */  "branchConSched",
  /*  704 */  "branchLoopEnd",
  /*  705 */  "branchLoopEndFar",
  /*  706 */  "branchLoopEndSched",
  /*  707 */  "partialSubtypeCheck",
  /*  708 */  "align_addr",
  /*  709 */  "array_size",
  /*  710 */  "inlineCallClearArrayShort",
  /*  711 */  "inlineCallClearArrayLarge",
  /*  712 */  "inlineCallClearArray",
  /*  713 */  "string_compareL",
  /*  714 */  "string_compareU",
  /*  715 */  "string_compareLU",
  /*  716 */  "string_compareUL",
  /*  717 */  "string_equalsL",
  /*  718 */  "string_equalsU",
  /*  719 */  "array_equalsB",
  /*  720 */  "array_equalsC",
  /*  721 */  "indexOf_imm1_char_U",
  /*  722 */  "indexOf_imm1_char_L",
  /*  723 */  "indexOf_imm1_char_UL",
  /*  724 */  "indexOf_imm1_U",
  /*  725 */  "indexOf_imm1_L",
  /*  726 */  "indexOf_imm1_UL",
  /*  727 */  "indexOfChar_U",
  /*  728 */  "indexOf_imm_U",
  /*  729 */  "indexOf_imm_L",
  /*  730 */  "indexOf_imm_UL",
  /*  731 */  "indexOf_U",
  /*  732 */  "indexOf_L",
  /*  733 */  "indexOf_UL",
  /*  734 */  "string_compress",
  /*  735 */  "string_inflate",
  /*  736 */  "has_negatives",
  /*  737 */  "encode_iso_array",
  /*  738 */  "minI_reg_reg_Ex",
  /*  739 */  "minI_reg_reg_isel",
  /*  740 */  "maxI_reg_reg_Ex",
  /*  741 */  "maxI_reg_reg_isel",
  /*  742 */  "insrwi_a",
  /*  743 */  "insrwi",
  /*  744 */  "bytes_reverse_int_Ex",
  /*  745 */  "bytes_reverse_long_Ex",
  /*  746 */  "bytes_reverse_ushort_Ex",
  /*  747 */  "bytes_reverse_short_Ex",
  /*  748 */  "loadI_reversed",
  /*  749 */  "loadL_reversed",
  /*  750 */  "loadUS_reversed",
  /*  751 */  "loadS_reversed",
  /*  752 */  "storeI_reversed",
  /*  753 */  "storeL_reversed",
  /*  754 */  "storeUS_reversed",
  /*  755 */  "storeS_reversed",
  /*  756 */  "xxspltw",
  /*  757 */  "repl8B_reg_Ex",
  /*  758 */  "repl8B_immI0",
  /*  759 */  "repl8B_immIminus1",
  /*  760 */  "repl16B_reg_Ex",
  /*  761 */  "repl16B_immI0",
  /*  762 */  "repl16B_immIminus1",
  /*  763 */  "repl4S_reg_Ex",
  /*  764 */  "repl4S_immI0",
  /*  765 */  "repl4S_immIminus1",
  /*  766 */  "repl8S_reg_Ex",
  /*  767 */  "repl8S_immI0",
  /*  768 */  "repl8S_immIminus1",
  /*  769 */  "repl2I_reg_Ex",
  /*  770 */  "repl2I_immI0",
  /*  771 */  "repl2I_immIminus1",
  /*  772 */  "repl4I_reg_Ex",
  /*  773 */  "repl4I_immI0",
  /*  774 */  "repl4I_immIminus1",
  /*  775 */  "repl2F_reg_Ex",
  /*  776 */  "repl2F_immF_Ex",
  /*  777 */  "repl2F_immF0",
  /*  778 */  "repl4F_reg_Ex",
  /*  779 */  "repl4F_immF_Ex",
  /*  780 */  "repl4F_immF0",
  /*  781 */  "repl2D_reg_Ex",
  /*  782 */  "repl2D_immI0",
  /*  783 */  "repl2D_immIminus1",
  /*  784 */  "xxspltd",
  /*  785 */  "xxpermdi",
  /*  786 */  "repl2L_reg_Ex",
  /*  787 */  "repl2L_immI0",
  /*  788 */  "repl2L_immIminus1",
  /*  789 */  "safePoint_poll",
  /*  790 */  "CallStaticJavaDirect",
  /*  791 */  "CallDynamicJavaDirectSched",
  /*  792 */  "CallDynamicJavaDirectSched_Ex",
  /*  793 */  "CallDynamicJavaDirect",
  /*  794 */  "CallRuntimeDirect",
  /*  795 */  "CallLeafDirect",
  /*  796 */  "CallLeafDirect_Ex",
  /*  797 */  "CallLeafNoFPDirect_Ex",
  /*  798 */  "TailCalljmpInd",
  /*  799 */  "Ret",
  /*  800 */  "tailjmpInd",
  /*  801 */  "CreateException",
  /*  802 */  "RethrowException",
  /*  803 */  "ShouldNotReachHere",
  /*  804 */  "endGroup",
  /*  805 */  "fxNop",
  /*  806 */  "fpNop0",
  /*  807 */  "fpNop1",
  /*  808 */  "brNop0",
  /*  809 */  "brNop1",
  /*  810 */  "brNop2",
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
  /*   50 */  false,
  /*   51 */  false,
  /*   52 */  false,
  /*   53 */  false,
  /*   54 */  false,
  /*   55 */  false,
  /*   56 */  false,
  /*   57 */  false,
  /*   58 */  false,
  /*   59 */  false,
  /*   60 */  false,
  /*   61 */  false,
  /*   62 */  false,
  /*   63 */  false,
  /*   64 */  false,
  /*   65 */  false,
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
  /*  107 */  true,
  // last operand
  /*  108 */  false,
  /*  109 */  false,
  /*  110 */  false,
  /*  111 */  false,
  /*  112 */  false,
  /*  113 */  false,
  // last operand class
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
  /*  127 */  false,
  /*  128 */  false,
  /*  129 */  false,
  /*  130 */  false,
  /*  131 */  false,
  /*  132 */  false,
  /*  133 */  false,
  /*  134 */  false,
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
  /*  218 */  false,
  // last internally defined operand
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
  /*  798 */  false,
  /*  799 */  false,
  /*  800 */  false,
  /*  801 */  false,
  /*  802 */  false,
  /*  803 */  false,
  /*  804 */  false,
  /*  805 */  false,
  /*  806 */  false,
  /*  807 */  false,
  /*  808 */  false,
  /*  809 */  false,
  /*  810 */  false,
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



// An array of character pointers to machine register names.
const char *Matcher::regName[REG_COUNT] = {
  "R14",
  "R14_H",
  "R15",
  "R15_H",
  "R17",
  "R17_H",
  "R18",
  "R18_H",
  "R19",
  "R19_H",
  "R20",
  "R20_H",
  "R21",
  "R21_H",
  "R22",
  "R22_H",
  "R23",
  "R23_H",
  "R24",
  "R24_H",
  "R25",
  "R25_H",
  "R26",
  "R26_H",
  "R27",
  "R27_H",
  "R28",
  "R28_H",
  "R29",
  "R29_H",
  "R30",
  "R30_H",
  "R31",
  "R31_H",
  "R11",
  "R11_H",
  "R12",
  "R12_H",
  "R10",
  "R10_H",
  "R9",
  "R9_H",
  "R8",
  "R8_H",
  "R7",
  "R7_H",
  "R6",
  "R6_H",
  "R5",
  "R5_H",
  "R4",
  "R4_H",
  "R3",
  "R3_H",
  "R16",
  "R16_H",
  "R13",
  "R13_H",
  "R2",
  "R2_H",
  "R1",
  "R1_H",
  "R0",
  "R0_H",
  "F0",
  "F0_H",
  "F13",
  "F13_H",
  "F12",
  "F12_H",
  "F11",
  "F11_H",
  "F10",
  "F10_H",
  "F9",
  "F9_H",
  "F8",
  "F8_H",
  "F7",
  "F7_H",
  "F6",
  "F6_H",
  "F5",
  "F5_H",
  "F4",
  "F4_H",
  "F3",
  "F3_H",
  "F2",
  "F2_H",
  "F1",
  "F1_H",
  "F14",
  "F14_H",
  "F15",
  "F15_H",
  "F16",
  "F16_H",
  "F17",
  "F17_H",
  "F18",
  "F18_H",
  "F19",
  "F19_H",
  "F20",
  "F20_H",
  "F21",
  "F21_H",
  "F22",
  "F22_H",
  "F23",
  "F23_H",
  "F24",
  "F24_H",
  "F25",
  "F25_H",
  "F26",
  "F26_H",
  "F27",
  "F27_H",
  "F28",
  "F28_H",
  "F29",
  "F29_H",
  "F30",
  "F30_H",
  "F31",
  "F31_H",
  "CCR0",
  "CCR1",
  "CCR2",
  "CCR3",
  "CCR4",
  "CCR5",
  "CCR6",
  "CCR7",
  "VSR0",
  "VSR1",
  "VSR2",
  "VSR3",
  "VSR4",
  "VSR5",
  "VSR6",
  "VSR7",
  "VSR8",
  "VSR9",
  "VSR10",
  "VSR11",
  "VSR12",
  "VSR13",
  "VSR14",
  "VSR15",
  "VSR16",
  "VSR17",
  "VSR18",
  "VSR19",
  "VSR20",
  "VSR21",
  "VSR22",
  "VSR23",
  "VSR24",
  "VSR25",
  "VSR26",
  "VSR27",
  "VSR28",
  "VSR29",
  "VSR30",
  "VSR31",
  "VSR32",
  "VSR33",
  "VSR34",
  "VSR35",
  "VSR36",
  "VSR37",
  "VSR38",
  "VSR39",
  "VSR40",
  "VSR41",
  "VSR42",
  "VSR43",
  "VSR44",
  "VSR45",
  "VSR46",
  "VSR47",
  "VSR48",
  "VSR49",
  "VSR50",
  "VSR51",
  "VSR52",
  "VSR53",
  "VSR54",
  "VSR55",
  "VSR56",
  "VSR57",
  "VSR58",
  "VSR59",
  "VSR60",
  "VSR61",
  "VSR62",
  "VSR63",
  "SR_XER",
  "SR_LR",
  "SR_CTR",
  "SR_VRSAVE",
  "SR_SPEFSCR",
  "SR_PPR" // no trailing comma
};

// An array of character pointers to machine register names.
const VMReg OptoReg::opto2vm[REG_COUNT] = {
	R14->as_VMReg()        ,
	R14->as_VMReg()->next(),
	R15->as_VMReg()        ,
	R15->as_VMReg()->next(),
	R17->as_VMReg()        ,
	R17->as_VMReg()->next(),
	R18->as_VMReg()        ,
	R18->as_VMReg()->next(),
	R19->as_VMReg()        ,
	R19->as_VMReg()->next(),
	R20->as_VMReg()        ,
	R20->as_VMReg()->next(),
	R21->as_VMReg()        ,
	R21->as_VMReg()->next(),
	R22->as_VMReg()        ,
	R22->as_VMReg()->next(),
	R23->as_VMReg()        ,
	R23->as_VMReg()->next(),
	R24->as_VMReg()        ,
	R24->as_VMReg()->next(),
	R25->as_VMReg()        ,
	R25->as_VMReg()->next(),
	R26->as_VMReg()        ,
	R26->as_VMReg()->next(),
	R27->as_VMReg()        ,
	R27->as_VMReg()->next(),
	R28->as_VMReg()        ,
	R28->as_VMReg()->next(),
	R29->as_VMReg()        ,
	R29->as_VMReg()->next(),
	R30->as_VMReg()        ,
	R30->as_VMReg()->next(),
	R31->as_VMReg()        ,
	R31->as_VMReg()->next(),
	R11->as_VMReg()        ,
	R11->as_VMReg()->next(),
	R12->as_VMReg()        ,
	R12->as_VMReg()->next(),
	R10->as_VMReg()        ,
	R10->as_VMReg()->next(),
	R9->as_VMReg()         ,
	R9->as_VMReg()->next() ,
	R8->as_VMReg()         ,
	R8->as_VMReg()->next() ,
	R7->as_VMReg()         ,
	R7->as_VMReg()->next() ,
	R6->as_VMReg()         ,
	R6->as_VMReg()->next() ,
	R5->as_VMReg()         ,
	R5->as_VMReg()->next() ,
	R4->as_VMReg()         ,
	R4->as_VMReg()->next() ,
	R3->as_VMReg()         ,
	R3->as_VMReg()->next() ,
	R16->as_VMReg()        ,
	R16->as_VMReg()->next(),
	R13->as_VMReg()        ,
	R13->as_VMReg()->next(),
	R2->as_VMReg()         ,
	R2->as_VMReg()->next() ,
	R1->as_VMReg()         ,
	R1->as_VMReg()->next() ,
	R0->as_VMReg()         ,
	R0->as_VMReg()->next() ,
	F0->as_VMReg()         ,
	F0->as_VMReg()->next() ,
	F13->as_VMReg()        ,
	F13->as_VMReg()->next(),
	F12->as_VMReg()        ,
	F12->as_VMReg()->next(),
	F11->as_VMReg()        ,
	F11->as_VMReg()->next(),
	F10->as_VMReg()        ,
	F10->as_VMReg()->next(),
	F9->as_VMReg()         ,
	F9->as_VMReg()->next() ,
	F8->as_VMReg()         ,
	F8->as_VMReg()->next() ,
	F7->as_VMReg()         ,
	F7->as_VMReg()->next() ,
	F6->as_VMReg()         ,
	F6->as_VMReg()->next() ,
	F5->as_VMReg()         ,
	F5->as_VMReg()->next() ,
	F4->as_VMReg()         ,
	F4->as_VMReg()->next() ,
	F3->as_VMReg()         ,
	F3->as_VMReg()->next() ,
	F2->as_VMReg()         ,
	F2->as_VMReg()->next() ,
	F1->as_VMReg()         ,
	F1->as_VMReg()->next() ,
	F14->as_VMReg()        ,
	F14->as_VMReg()->next(),
	F15->as_VMReg()        ,
	F15->as_VMReg()->next(),
	F16->as_VMReg()        ,
	F16->as_VMReg()->next(),
	F17->as_VMReg()        ,
	F17->as_VMReg()->next(),
	F18->as_VMReg()        ,
	F18->as_VMReg()->next(),
	F19->as_VMReg()        ,
	F19->as_VMReg()->next(),
	F20->as_VMReg()        ,
	F20->as_VMReg()->next(),
	F21->as_VMReg()        ,
	F21->as_VMReg()->next(),
	F22->as_VMReg()        ,
	F22->as_VMReg()->next(),
	F23->as_VMReg()        ,
	F23->as_VMReg()->next(),
	F24->as_VMReg()        ,
	F24->as_VMReg()->next(),
	F25->as_VMReg()        ,
	F25->as_VMReg()->next(),
	F26->as_VMReg()        ,
	F26->as_VMReg()->next(),
	F27->as_VMReg()        ,
	F27->as_VMReg()->next(),
	F28->as_VMReg()        ,
	F28->as_VMReg()->next(),
	F29->as_VMReg()        ,
	F29->as_VMReg()->next(),
	F30->as_VMReg()        ,
	F30->as_VMReg()->next(),
	F31->as_VMReg()        ,
	F31->as_VMReg()->next(),
	CCR0->as_VMReg(),
	CCR1->as_VMReg(),
	CCR2->as_VMReg(),
	CCR3->as_VMReg(),
	CCR4->as_VMReg(),
	CCR5->as_VMReg(),
	CCR6->as_VMReg(),
	CCR7->as_VMReg(),
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	SR_XER->as_VMReg(),
	SR_LR->as_VMReg(),
	SR_CTR->as_VMReg(),
	SR_VRSAVE->as_VMReg(),
	SR_SPEFSCR->as_VMReg(),
	SR_PPR->as_VMReg() // no trailing comma
	};

 OptoReg::Name OptoReg::vm2opto[ConcreteRegisterImpl::number_of_registers];

// An array of the machine register encode values
const unsigned char Matcher::_regEncode[REG_COUNT] = {
  (unsigned char)'\xE',  // R14
  (unsigned char)'\x63',  // R14_H
  (unsigned char)'\xF',  // R15
  (unsigned char)'\x63',  // R15_H
  (unsigned char)'\x11',  // R17
  (unsigned char)'\x63',  // R17_H
  (unsigned char)'\x12',  // R18
  (unsigned char)'\x63',  // R18_H
  (unsigned char)'\x13',  // R19
  (unsigned char)'\x63',  // R19_H
  (unsigned char)'\x14',  // R20
  (unsigned char)'\x63',  // R20_H
  (unsigned char)'\x15',  // R21
  (unsigned char)'\x63',  // R21_H
  (unsigned char)'\x16',  // R22
  (unsigned char)'\x63',  // R22_H
  (unsigned char)'\x17',  // R23
  (unsigned char)'\x63',  // R23_H
  (unsigned char)'\x18',  // R24
  (unsigned char)'\x63',  // R24_H
  (unsigned char)'\x19',  // R25
  (unsigned char)'\x63',  // R25_H
  (unsigned char)'\x1A',  // R26
  (unsigned char)'\x63',  // R26_H
  (unsigned char)'\x1B',  // R27
  (unsigned char)'\x63',  // R27_H
  (unsigned char)'\x1C',  // R28
  (unsigned char)'\x63',  // R28_H
  (unsigned char)'\x1D',  // R29
  (unsigned char)'\x63',  // R29_H
  (unsigned char)'\x1E',  // R30
  (unsigned char)'\x63',  // R30_H
  (unsigned char)'\x1F',  // R31
  (unsigned char)'\x63',  // R31_H
  (unsigned char)'\xB',  // R11
  (unsigned char)'\x63',  // R11_H
  (unsigned char)'\xC',  // R12
  (unsigned char)'\x63',  // R12_H
  (unsigned char)'\xA',  // R10
  (unsigned char)'\x63',  // R10_H
  (unsigned char)'\x9',  // R9
  (unsigned char)'\x63',  // R9_H
  (unsigned char)'\x8',  // R8
  (unsigned char)'\x63',  // R8_H
  (unsigned char)'\x7',  // R7
  (unsigned char)'\x63',  // R7_H
  (unsigned char)'\x6',  // R6
  (unsigned char)'\x63',  // R6_H
  (unsigned char)'\x5',  // R5
  (unsigned char)'\x63',  // R5_H
  (unsigned char)'\x4',  // R4
  (unsigned char)'\x63',  // R4_H
  (unsigned char)'\x3',  // R3
  (unsigned char)'\x63',  // R3_H
  (unsigned char)'\x10',  // R16
  (unsigned char)'\x63',  // R16_H
  (unsigned char)'\xD',  // R13
  (unsigned char)'\x63',  // R13_H
  (unsigned char)'\x2',  // R2
  (unsigned char)'\x63',  // R2_H
  (unsigned char)'\x1',  // R1
  (unsigned char)'\x63',  // R1_H
  (unsigned char)'\x0',  // R0
  (unsigned char)'\x63',  // R0_H
  (unsigned char)'\x0',  // F0
  (unsigned char)'\x63',  // F0_H
  (unsigned char)'\xD',  // F13
  (unsigned char)'\x63',  // F13_H
  (unsigned char)'\xC',  // F12
  (unsigned char)'\x63',  // F12_H
  (unsigned char)'\xB',  // F11
  (unsigned char)'\x63',  // F11_H
  (unsigned char)'\xA',  // F10
  (unsigned char)'\x63',  // F10_H
  (unsigned char)'\x9',  // F9
  (unsigned char)'\x63',  // F9_H
  (unsigned char)'\x8',  // F8
  (unsigned char)'\x63',  // F8_H
  (unsigned char)'\x7',  // F7
  (unsigned char)'\x63',  // F7_H
  (unsigned char)'\x6',  // F6
  (unsigned char)'\x63',  // F6_H
  (unsigned char)'\x5',  // F5
  (unsigned char)'\x63',  // F5_H
  (unsigned char)'\x4',  // F4
  (unsigned char)'\x63',  // F4_H
  (unsigned char)'\x3',  // F3
  (unsigned char)'\x63',  // F3_H
  (unsigned char)'\x2',  // F2
  (unsigned char)'\x63',  // F2_H
  (unsigned char)'\x1',  // F1
  (unsigned char)'\x63',  // F1_H
  (unsigned char)'\xE',  // F14
  (unsigned char)'\x63',  // F14_H
  (unsigned char)'\xF',  // F15
  (unsigned char)'\x63',  // F15_H
  (unsigned char)'\x10',  // F16
  (unsigned char)'\x63',  // F16_H
  (unsigned char)'\x11',  // F17
  (unsigned char)'\x63',  // F17_H
  (unsigned char)'\x12',  // F18
  (unsigned char)'\x63',  // F18_H
  (unsigned char)'\x13',  // F19
  (unsigned char)'\x63',  // F19_H
  (unsigned char)'\x14',  // F20
  (unsigned char)'\x63',  // F20_H
  (unsigned char)'\x15',  // F21
  (unsigned char)'\x63',  // F21_H
  (unsigned char)'\x16',  // F22
  (unsigned char)'\x63',  // F22_H
  (unsigned char)'\x17',  // F23
  (unsigned char)'\x63',  // F23_H
  (unsigned char)'\x18',  // F24
  (unsigned char)'\x63',  // F24_H
  (unsigned char)'\x19',  // F25
  (unsigned char)'\x63',  // F25_H
  (unsigned char)'\x1A',  // F26
  (unsigned char)'\x63',  // F26_H
  (unsigned char)'\x1B',  // F27
  (unsigned char)'\x63',  // F27_H
  (unsigned char)'\x1C',  // F28
  (unsigned char)'\x63',  // F28_H
  (unsigned char)'\x1D',  // F29
  (unsigned char)'\x63',  // F29_H
  (unsigned char)'\x1E',  // F30
  (unsigned char)'\x63',  // F30_H
  (unsigned char)'\x1F',  // F31
  (unsigned char)'\x63',  // F31_H
  (unsigned char)'\x0',  // CCR0
  (unsigned char)'\x1',  // CCR1
  (unsigned char)'\x2',  // CCR2
  (unsigned char)'\x3',  // CCR3
  (unsigned char)'\x4',  // CCR4
  (unsigned char)'\x5',  // CCR5
  (unsigned char)'\x6',  // CCR6
  (unsigned char)'\x7',  // CCR7
  (unsigned char)'\x0',  // VSR0
  (unsigned char)'\x1',  // VSR1
  (unsigned char)'\x2',  // VSR2
  (unsigned char)'\x3',  // VSR3
  (unsigned char)'\x4',  // VSR4
  (unsigned char)'\x5',  // VSR5
  (unsigned char)'\x6',  // VSR6
  (unsigned char)'\x7',  // VSR7
  (unsigned char)'\x8',  // VSR8
  (unsigned char)'\x9',  // VSR9
  (unsigned char)'\xA',  // VSR10
  (unsigned char)'\xB',  // VSR11
  (unsigned char)'\xC',  // VSR12
  (unsigned char)'\xD',  // VSR13
  (unsigned char)'\xE',  // VSR14
  (unsigned char)'\xF',  // VSR15
  (unsigned char)'\x10',  // VSR16
  (unsigned char)'\x11',  // VSR17
  (unsigned char)'\x12',  // VSR18
  (unsigned char)'\x13',  // VSR19
  (unsigned char)'\x14',  // VSR20
  (unsigned char)'\x15',  // VSR21
  (unsigned char)'\x16',  // VSR22
  (unsigned char)'\x17',  // VSR23
  (unsigned char)'\x18',  // VSR24
  (unsigned char)'\x19',  // VSR25
  (unsigned char)'\x1A',  // VSR26
  (unsigned char)'\x1B',  // VSR27
  (unsigned char)'\x1C',  // VSR28
  (unsigned char)'\x1D',  // VSR29
  (unsigned char)'\x1E',  // VSR30
  (unsigned char)'\x1F',  // VSR31
  (unsigned char)'\x20',  // VSR32
  (unsigned char)'\x21',  // VSR33
  (unsigned char)'\x22',  // VSR34
  (unsigned char)'\x23',  // VSR35
  (unsigned char)'\x24',  // VSR36
  (unsigned char)'\x25',  // VSR37
  (unsigned char)'\x26',  // VSR38
  (unsigned char)'\x27',  // VSR39
  (unsigned char)'\x28',  // VSR40
  (unsigned char)'\x29',  // VSR41
  (unsigned char)'\x2A',  // VSR42
  (unsigned char)'\x2B',  // VSR43
  (unsigned char)'\x2C',  // VSR44
  (unsigned char)'\x2D',  // VSR45
  (unsigned char)'\x2E',  // VSR46
  (unsigned char)'\x2F',  // VSR47
  (unsigned char)'\x30',  // VSR48
  (unsigned char)'\x31',  // VSR49
  (unsigned char)'\x32',  // VSR50
  (unsigned char)'\x33',  // VSR51
  (unsigned char)'\x34',  // VSR52
  (unsigned char)'\x35',  // VSR53
  (unsigned char)'\x36',  // VSR54
  (unsigned char)'\x37',  // VSR55
  (unsigned char)'\x38',  // VSR56
  (unsigned char)'\x39',  // VSR57
  (unsigned char)'\x3A',  // VSR58
  (unsigned char)'\x3B',  // VSR59
  (unsigned char)'\x3C',  // VSR60
  (unsigned char)'\x3D',  // VSR61
  (unsigned char)'\x3E',  // VSR62
  (unsigned char)'\x3F',  // VSR63
  (unsigned char)'\x0',  // SR_XER
  (unsigned char)'\x1',  // SR_LR
  (unsigned char)'\x2',  // SR_CTR
  (unsigned char)'\x3',  // SR_VRSAVE
  (unsigned char)'\x4',  // SR_SPEFSCR
  (unsigned char)'\x5' // no trailing comma  // SR_PPR
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
  return &VS_REG_mask();
}

const RegMask *iRegIdstOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RW_mask();
}

const RegMask *iRegIsrcOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RO_mask();
}

const RegMask *rscratch1RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RSCRATCH1_BITS32_REG_mask();
}

const RegMask *rscratch2RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RSCRATCH2_BITS32_REG_mask();
}

const RegMask *rarg1RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG1_BITS32_REG_mask();
}

const RegMask *rarg2RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG2_BITS32_REG_mask();
}

const RegMask *rarg3RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG3_BITS32_REG_mask();
}

const RegMask *rarg4RegIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG4_BITS32_REG_mask();
}

const RegMask *rarg1RegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG1_BITS64_REG_mask();
}

const RegMask *rarg2RegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG2_BITS64_REG_mask();
}

const RegMask *rarg3RegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG3_BITS64_REG_mask();
}

const RegMask *rarg4RegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG4_BITS64_REG_mask();
}

const RegMask *iRegPdstOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS64_REG_RW_mask();
}

const RegMask *iRegPdstNoScratchOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS64_REG_LEAF_CALL_mask();
}

const RegMask *iRegPsrcOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS64_REG_RO_mask();
}

const RegMask *threadRegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &THREAD_BITS64_REG_mask();
}

const RegMask *rscratch1RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RSCRATCH1_BITS64_REG_mask();
}

const RegMask *rscratch2RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RSCRATCH2_BITS64_REG_mask();
}

const RegMask *rarg1RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG1_BITS64_REG_mask();
}

const RegMask *rarg2RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG2_BITS64_REG_mask();
}

const RegMask *rarg3RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG3_BITS64_REG_mask();
}

const RegMask *rarg4RegPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RARG4_BITS64_REG_mask();
}

const RegMask *iRegNsrcOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RO_mask();
}

const RegMask *iRegNdstOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RW_mask();
}

const RegMask *iRegLdstOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS64_REG_RW_mask();
}

const RegMask *iRegLsrcOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS64_REG_RO_mask();
}

const RegMask *iRegL2IsrcOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS64_REG_RO_mask();
}

const RegMask *rscratch1RegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RSCRATCH1_BITS64_REG_mask();
}

const RegMask *rscratch2RegLOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RSCRATCH2_BITS64_REG_mask();
}

const RegMask *flagsRegOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &INT_FLAGS_mask();
}

const RegMask *flagsRegSrcOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &INT_FLAGS_RO_mask();
}

const RegMask *flagsRegCR0Oper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &INT_FLAGS_CR0_mask();
}

const RegMask *flagsRegCR1Oper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &INT_FLAGS_CR1_mask();
}

const RegMask *flagsRegCR6Oper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &INT_FLAGS_CR6_mask();
}

const RegMask *regCTROper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &CTR_REG_mask();
}

const RegMask *regDOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &DBL_REG_mask();
}

const RegMask *regFOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &FLT_REG_mask();
}

const RegMask *inline_cache_regPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &R19_BITS64_REG_mask();
}

const RegMask *compiler_method_oop_regPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &RSCRATCH1_BITS64_REG_mask();
}

const RegMask *interpreter_method_oop_regPOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &R19_BITS64_REG_mask();
}

const RegMask *iRegP2NOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS64_REG_RO_mask();
}

const RegMask *iRegN2POper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RO_mask();
}

const RegMask *iRegN2P_klassOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RO_mask();
}

const RegMask *indirectOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS64_REG_RO_mask();
}

const RegMask *indOffset16Oper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS64_REG_RO_mask();
}

const RegMask *indOffset16Alg4Oper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS64_REG_RO_mask();
}

const RegMask *indirectNarrowOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RO_mask();
}

const RegMask *indirectNarrow_klassOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RO_mask();
}

const RegMask *indOffset16NarrowOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RO_mask();
}

const RegMask *indOffset16Narrow_klassOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RO_mask();
}

const RegMask *indOffset16NarrowAlg4Oper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RO_mask();
}

const RegMask *indOffset16NarrowAlg4_klassOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &BITS32_REG_RO_mask();
}

const RegMask *stackSlotIOper::in_RegMask(int index) const {
  assert(0 <= index && index < 1, "index out of range");
  return &(Compile::current()->FIRST_STACK_mask());
}

const RegMask *stackSlotLOper::in_RegMask(int index) const {
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

//------------------Define members for classes derived from MachNode----------
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
MachNode *branchConSchedNode::short_branch_version() {
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
MachNode *branchLoopEndSchedNode::short_branch_version() {
  branchLoopEndNode *node = new branchLoopEndNode();
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

void rangeCheck_iReg_uimm15Node::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void rangeCheck_iReg_uimm15Node::save_label( Label** label, uint* block_num ) {
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
void rangeCheck_uimm15_iRegNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void rangeCheck_uimm15_iRegNode::save_label( Label** label, uint* block_num ) {
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
void zeroCheckP_reg_imm0Node::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(4));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void zeroCheckP_reg_imm0Node::save_label( Label** label, uint* block_num ) {
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
void branchConSchedNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void branchConSchedNode::save_label( Label** label, uint* block_num ) {
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
void branchLoopEndSchedNode::label_set( Label* label, uint block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  oper->_label     = label;
  oper->_block_num = block_num;
}
void branchLoopEndSchedNode::save_label( Label** label, uint* block_num ) {
  labelOper* oper  = (labelOper*)(opnd_array(3));
  *label = oper->_label;
  *block_num = oper->_block_num;
}
void CallStaticJavaDirectNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallDynamicJavaDirectSchedNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallDynamicJavaDirectSched_ExNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallDynamicJavaDirectNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallRuntimeDirectNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallLeafDirectNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallLeafDirect_ExNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

void CallLeafNoFPDirect_ExNode::method_set( intptr_t method ) {
  ((methodOper*)opnd_array(1))->_method = method;
}

int loadUB_indirectNode::reloc() const {
  return 1;
}

int loadUB_indirect_acNode::reloc() const {
  return 1;
}

int loadB_indirect_ExNode::reloc() const {
  return 1;
}

int loadB_indirect_ac_ExNode::reloc() const {
  return 1;
}

int loadUBNode::reloc() const {
  return 1;
}

int loadUB_acNode::reloc() const {
  return 1;
}

int loadUB2LNode::reloc() const {
  return 1;
}

int loadUB2L_acNode::reloc() const {
  return 1;
}

int loadSNode::reloc() const {
  return 1;
}

int loadS_acNode::reloc() const {
  return 1;
}

int loadUSNode::reloc() const {
  return 1;
}

int loadUS_acNode::reloc() const {
  return 1;
}

int loadUS2LNode::reloc() const {
  return 1;
}

int loadUS2L_acNode::reloc() const {
  return 1;
}

int loadINode::reloc() const {
  return 1;
}

int loadI_acNode::reloc() const {
  return 1;
}

int loadUI2LNode::reloc() const {
  return 1;
}

int loadI2LNode::reloc() const {
  return 1;
}

int loadI2L_acNode::reloc() const {
  return 1;
}

int loadLNode::reloc() const {
  return 1;
}

int loadL_acNode::reloc() const {
  return 1;
}

int loadL_unalignedNode::reloc() const {
  return 1;
}

int loadV8Node::reloc() const {
  return 1;
}

int loadRangeNode::reloc() const {
  return 1;
}

int loadNNode::reloc() const {
  return 1;
}

int loadN_acNode::reloc() const {
  return 1;
}

int loadN2P_unscaledNode::reloc() const {
  return 1;
}

int loadN2P_klass_unscaledNode::reloc() const {
  return 1;
}

int loadPNode::reloc() const {
  return 1;
}

int loadP_acNode::reloc() const {
  return 1;
}

int loadP2XNode::reloc() const {
  return 1;
}

int loadNKlassNode::reloc() const {
  return 1;
}

int loadKlassNode::reloc() const {
  return 1;
}

int loadFNode::reloc() const {
  return 1;
}

int loadF_acNode::reloc() const {
  return 1;
}

int loadDNode::reloc() const {
  return 1;
}

int loadD_acNode::reloc() const {
  return 1;
}

int loadD_unalignedNode::reloc() const {
  return 1;
}

int loadConP0or1Node::reloc() const {
  return 1;
}

int loadConPNode::reloc() const {
  return 1;
}

int loadConP_loNode::reloc() const {
  return 1;
}

int loadConP_ExNode::reloc() const {
  return 1;
}

int loadConFNode::reloc() const {
  return 1;
}

int loadConFCompNode::reloc() const {
  return 1;
}

int loadConF_ExNode::reloc() const {
  return 2;
}

int loadConDNode::reloc() const {
  return 1;
}

int loadConDCompNode::reloc() const {
  return 1;
}

int loadConD_ExNode::reloc() const {
  return 2;
}

int prefetch_alloc_zeroNode::reloc() const {
  return 1;
}

int prefetch_alloc_zero_no_offsetNode::reloc() const {
  return 1;
}

int prefetch_allocNode::reloc() const {
  return 1;
}

int prefetch_alloc_no_offsetNode::reloc() const {
  return 1;
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

int storeI_convL2INode::reloc() const {
  return 2;
}

int storeLNode::reloc() const {
  return 2;
}

int storeA8BNode::reloc() const {
  return 2;
}

int storeNNode::reloc() const {
  return 3;
}

int storeNKlassNode::reloc() const {
  return 3;
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

int storeCM_CMSNode::reloc() const {
  return 2;
}

int storeCM_CMS_ExExNode::reloc() const {
  return 2;
}

int storeCM_G1Node::reloc() const {
  return 2;
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

int addI_reg_regNode::reloc() const {
  return 2;
}

int addP_reg_regNode::reloc() const {
  return 1;
}

int addP_reg_imm16Node::reloc() const {
  return 1;
}

int addP_reg_immhi16Node::reloc() const {
  return 1;
}

int shrP_convP2X_reg_imm6Node::reloc() const {
  return 1;
}

int castP2XNode::reloc() const {
  return 1;
}

int convP2Bool_reg__cntlz_ExNode::reloc() const {
  return 1;
}

int convP2Bool_reg__cmoveNode::reloc() const {
  return 1;
}

int xorI_convP2Bool_reg__cntlz_ExNode::reloc() const {
  return 1;
}

int xorI_convP2Bool_reg_immIvalue1__cmoveNode::reloc() const {
  return 1;
}

int zeroCheckP_reg_imm0Node::reloc() const {
  return 2;
}

int cmpP_reg_regNode::reloc() const {
  return 2;
}

int cmpP_reg_nullNode::reloc() const {
  return 2;
}

int partialSubtypeCheckNode::reloc() const {
  return 2;
}

int indexOf_imm1_char_UNode::reloc() const {
  return 1;
}

int indexOf_imm1_char_LNode::reloc() const {
  return 1;
}

int indexOf_imm1_char_ULNode::reloc() const {
  return 1;
}

int repl2F_immF_ExNode::reloc() const {
  return 1;
}

int repl2F_immF0Node::reloc() const {
  return 1;
}

int repl4F_immF_ExNode::reloc() const {
  return 1;
}

int repl4F_immF0Node::reloc() const {
  return 1;
}

int safePoint_pollNode::reloc() const {
  return 1;
}

int CallStaticJavaDirectNode::reloc() const {
  return 1;
}

int CallDynamicJavaDirectSchedNode::reloc() const {
  return 1;
}

int CallDynamicJavaDirectSched_ExNode::reloc() const {
  return 1;
}

int CallDynamicJavaDirectNode::reloc() const {
  return 1;
}

int CallRuntimeDirectNode::reloc() const {
  return 1;
}

int CallLeafDirectNode::reloc() const {
  return 1;
}

int CallLeafDirect_ExNode::reloc() const {
  return 1;
}

int CallLeafNoFPDirect_ExNode::reloc() const {
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


void convB2I_reg_2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 5411 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_extsb);
    __ extsb(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 8489 "ad_ppc.cpp"
  }
}

uint convB2I_reg_2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadUB_indirectNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2601 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lbz);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8512 "ad_ppc.cpp"
  }
}

uint loadUB_indirectNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadUB_indirect_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2609 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 8537 "ad_ppc.cpp"
  }
}

uint loadUB_indirect_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadUB_indOffset16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2601 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lbz);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8560 "ad_ppc.cpp"
  }
}

uint loadUB_indOffset16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadUB_indOffset16_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2609 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 8585 "ad_ppc.cpp"
  }
}

uint loadUB_indOffset16_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadUBNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2601 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lbz);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8608 "ad_ppc.cpp"
  }
}

uint loadUBNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadUB_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2609 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 8633 "ad_ppc.cpp"
  }
}

uint loadUB_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadUB2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2601 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lbz);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8656 "ad_ppc.cpp"
  }
}

uint loadUB2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadUB2L_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2609 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 8681 "ad_ppc.cpp"
  }
}

uint loadUB2L_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadSNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 5569 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lha);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lha(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8704 "ad_ppc.cpp"
  }
}

uint loadSNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadS_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 5586 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lha(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 8729 "ad_ppc.cpp"
  }
}

uint loadS_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadUSNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2618 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lhz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lhz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8753 "ad_ppc.cpp"
  }
}

uint loadUSNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadUS_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2627 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lhz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 8779 "ad_ppc.cpp"
  }
}

uint loadUS_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadUS2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2618 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lhz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lhz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8803 "ad_ppc.cpp"
  }
}

uint loadUS2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadUS2L_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2627 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lhz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 8829 "ad_ppc.cpp"
  }
}

uint loadUS2L_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2637 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8853 "ad_ppc.cpp"
  }
}

uint loadINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadI_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2646 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 8879 "ad_ppc.cpp"
  }
}

uint loadI_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadUI2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {

#line 2637 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8904 "ad_ppc.cpp"
  }
}

uint loadUI2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadI2LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 5693 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwa);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwa(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8927 "ad_ppc.cpp"
  }
}

uint loadI2LNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadI2L_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 5710 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwa);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwa(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 8952 "ad_ppc.cpp"
  }
}

uint loadI2L_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2656 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 8977 "ad_ppc.cpp"
  }
}

uint loadLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadL_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2666 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9004 "ad_ppc.cpp"
  }
}

uint loadL_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadL_unalignedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2656 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9029 "ad_ppc.cpp"
  }
}

uint loadL_unalignedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadV8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2656 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9054 "ad_ppc.cpp"
  }
}

uint loadV8Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadV16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 5779 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ lxvd2x(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 9075 "ad_ppc.cpp"
  }
}

uint loadV16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadRangeNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2637 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9099 "ad_ppc.cpp"
  }
}

uint loadRangeNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2637 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9123 "ad_ppc.cpp"
  }
}

uint loadNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadN_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2646 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9149 "ad_ppc.cpp"
  }
}

uint loadN_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadN2P_unscaledNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2637 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9173 "ad_ppc.cpp"
  }
}

uint loadN2P_unscaledNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadN2P_klass_unscaledNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2637 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9197 "ad_ppc.cpp"
  }
}

uint loadN2P_klass_unscaledNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2656 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9222 "ad_ppc.cpp"
  }
}

uint loadPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadP_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2666 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9249 "ad_ppc.cpp"
  }
}

uint loadP_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadP2XNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2656 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9274 "ad_ppc.cpp"
  }
}

uint loadP2XNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadNKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2637 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9298 "ad_ppc.cpp"
  }
}

uint loadNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2656 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9323 "ad_ppc.cpp"
  }
}

uint loadKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 5912 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lfs);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lfs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9346 "ad_ppc.cpp"
  }
}

uint loadFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadF_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 5932 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    Label next;
    __ lfs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ fcmpu(CCR0, opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(0)->as_FloatRegister(ra_,this)/* dst */);
    __ bne(CCR0, next);
    __ bind(next);
    __ isync();
  
#line 9375 "ad_ppc.cpp"
  }
}

uint loadF_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void loadDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2677 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lfd);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lfd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9398 "ad_ppc.cpp"
  }
}

uint loadDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadD_acNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 5969 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    Label next;
    __ lfd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ fcmpu(CCR0, opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(0)->as_FloatRegister(ra_,this)/* dst */);
    __ bne(CCR0, next);
    __ bind(next);
    __ isync();
  
#line 9427 "ad_ppc.cpp"
  }
}

uint loadD_acNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void loadD_unalignedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {

#line 2677 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lfd);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lfd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9450 "ad_ppc.cpp"
  }
}

uint loadD_unalignedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadToc_hiNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 6004 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addis);
    __ calculate_address_from_global_toc_hi16only(opnd_array(0)->as_Register(ra_,this)/* dst */, __ method_toc());
  
#line 9472 "ad_ppc.cpp"
  }
}

uint loadToc_hiNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadToc_loNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6018 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ori);
    __ calculate_address_from_global_toc_lo16only(opnd_array(0)->as_Register(ra_,this)/* dst */, __ method_toc());
  
#line 9494 "ad_ppc.cpp"
  }
}

uint loadToc_loNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConI16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6031 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 9516 "ad_ppc.cpp"
  }
}

uint loadConI16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConIhi16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6045 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addis);
    // Lis sign extends 16-bit src then shifts it 16 bit to the left.
    __ lis(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)((opnd_array(1)->constant()& 0xFFFF0000) >> 16)));
  
#line 9539 "ad_ppc.cpp"
  }
}

uint loadConIhi16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConI32_lo16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6062 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ori);
    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0xFFFF);
  
#line 9562 "ad_ppc.cpp"
  }
}

uint loadConI32_lo16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConL16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6090 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short) (opnd_array(1)->constantL()& 0xFFFF)));
  
#line 9584 "ad_ppc.cpp"
  }
}

uint loadConL16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConL32hi16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6104 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addis);
    __ lis(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)((opnd_array(1)->constantL()& 0xFFFF0000) >> 16)));
  
#line 9606 "ad_ppc.cpp"
  }
}

uint loadConL32hi16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConL32_lo16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6120 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ori);
    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constantL()) & 0xFFFF);
  
#line 9629 "ad_ppc.cpp"
  }
}

uint loadConL32_lo16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  {

#line 2684 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);

    MacroAssembler _masm(&cbuf);
    int toc_offset = 0;

    address const_toc_addr;
    // Create a non-oop constant, no relocation needed.
    // If it is an IC, it has a virtual_call_Relocation.
    const_toc_addr = __ long_constant((jlong)opnd_array(1)->constantL());
    if (const_toc_addr == NULL) {
      ciEnv::current()->record_out_of_memory_failure();
      return;
    }

    // Get the constant's TOC offset.
    toc_offset = __ offset_to_method_toc(const_toc_addr);

    // Keep the current instruction offset in mind.
    ((loadConLNode*)this)->_cbuf_insts_offset = __ offset();

    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, toc_offset, opnd_array(2)->as_Register(ra_,this,idx2)/* toc */);
  
#line 9670 "ad_ppc.cpp"
  }
}

uint loadConLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConL_hiNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  {

#line 2708 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addis);

    MacroAssembler _masm(&cbuf);

    if (!ra_->C->in_scratch_emit_size()) {
      address const_toc_addr;
      // Create a non-oop constant, no relocation needed.
      // If it is an IC, it has a virtual_call_Relocation.
      const_toc_addr = __ long_constant((jlong)opnd_array(1)->constantL());
      if (const_toc_addr == NULL) {
        ciEnv::current()->record_out_of_memory_failure();
        return;
      }

      // Get the constant's TOC offset.
      const int toc_offset = __ offset_to_method_toc(const_toc_addr);
      // Store the toc offset of the constant.
      ((loadConL_hiNode*)this)->_const_toc_offset = toc_offset;

      // Also keep the current instruction offset in mind.
      ((loadConL_hiNode*)this)->_cbuf_insts_offset = __ offset();
    }

    __ addis(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* toc */, MacroAssembler::largeoffset_si16_si16_hi(_const_toc_offset));
  
#line 9714 "ad_ppc.cpp"
  }
}

uint loadConL_hiNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConL_loNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {
    MacroAssembler _masm(&cbuf);

#line 6200 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    int offset = ra_->C->in_scratch_emit_size() ? 0 : _const_toc_offset_hi_node->_const_toc_offset;
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, MacroAssembler::largeoffset_si16_si16_lo(offset), opnd_array(2)->as_Register(ra_,this,idx2)/* base */);
  
#line 9738 "ad_ppc.cpp"
  }
}

uint loadConL_loNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  loadConL_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegLdst, 	dst
  unsigned idx_src   = idx1; 	// immL, 	src
  unsigned idx_toc   = mach_constant_base_node_input(); 	// iRegLdst, 	constanttablebase
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  Node    *n_toc     = lookup(idx_toc);
  iRegLdstOper *op_dst = (iRegLdstOper *)opnd_array(0);
  immLOper *op_src = (immLOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 2928 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // Create new nodes.
    loadConLNodesTuple loadConLNodes =
      loadConLNodesTuple_create(ra_, n_toc, op_src,
                                ra_->get_reg_second(this), ra_->get_reg_first(this));

    // Push new nodes.
    if (loadConLNodes._large_hi) nodes->push(loadConLNodes._large_hi);
    if (loadConLNodes._last)     nodes->push(loadConLNodes._last);

    // some asserts
    assert(nodes->length() >= 1, "must have created at least 1 node");
    assert(loadConLNodes._last->bottom_type()->isa_long(), "must be long");
  
#line 9778 "ad_ppc.cpp"
  }
}

void loadConL_ExNode::eval_constant(Compile* C) {
  // User did not define an encode section.
}
void loadConN0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6227 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, 0);
  
#line 9798 "ad_ppc.cpp"
  }
}

uint loadConN0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConN_hiNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6241 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addis);
    __ lis(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)(short)((opnd_array(1)->constant()>> 16) & 0xffff));
  
#line 9820 "ad_ppc.cpp"
  }
}

uint loadConN_hiNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConN_loNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6255 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    assert(__ oop_recorder() != NULL, "this assembler needs an OopRecorder");
    int oop_index = __ oop_recorder()->find_index((jobject)opnd_array(2)->constant());
    RelocationHolder rspec = oop_Relocation::spec(oop_index);
    __ relocate(rspec, 1);
    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant()& 0xffff);
  
#line 9847 "ad_ppc.cpp"
  }
}

uint loadConN_loNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rldiclNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask_begin
  {
    MacroAssembler _masm(&cbuf);

#line 6270 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ rldicl(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->constant(), opnd_array(3)->constant());
  
#line 9870 "ad_ppc.cpp"
  }
}

uint rldiclNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void clearMs32bNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6286 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0x20);
  
#line 9892 "ad_ppc.cpp"
  }
}

uint clearMs32bNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadBaseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 6299 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ load_const_optimized(opnd_array(0)->as_Register(ra_,this)/* dst */, Universe::narrow_oop_base(), R0);
  
#line 9914 "ad_ppc.cpp"
  }
}

void  loadConN_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegNdst, 	dst
  unsigned idx_src   = idx1; 	// immN, 	src
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  iRegNdstOper *op_dst = (iRegNdstOper *)opnd_array(0);
  immNOper *op_src = (immNOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 6314 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    MachNode *m1 = new loadConN_hiNode();
    MachNode *m2 = new loadConN_loNode();
    MachNode *m3 = new clearMs32bNode();
    m1->add_req(NULL);
    m2->add_req(NULL, m1);
    m3->add_req(NULL, m2);
    m1->_opnds[0] = op_dst;
    m1->_opnds[1] = op_src;
    m2->_opnds[0] = op_dst;
    m2->_opnds[1] = op_dst;
    m2->_opnds[2] = op_src;
    m3->_opnds[0] = op_dst;
    m3->_opnds[1] = op_dst;
    ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    ra_->set_pair(m3->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    nodes->push(m1);
    nodes->push(m2);
    nodes->push(m3);
  
#line 9954 "ad_ppc.cpp"
  }
}

void loadConNKlass_hiNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6347 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addis);
    intptr_t Csrc = Klass::encode_klass((Klass *)opnd_array(1)->constant());
    __ lis(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)(short)((Csrc >> 16) & 0xffff));
  
#line 9972 "ad_ppc.cpp"
  }
}

uint loadConNKlass_hiNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConNKlass_maskNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6363 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0x20);
  
#line 9995 "ad_ppc.cpp"
  }
}

uint loadConNKlass_maskNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConNKlass_loNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 6379 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ori);
    intptr_t Csrc = Klass::encode_klass((Klass *)opnd_array(1)->constant());
    assert(__ oop_recorder() != NULL, "this assembler needs an OopRecorder");
    int klass_index = __ oop_recorder()->find_index((Klass *)opnd_array(1)->constant());
    RelocationHolder rspec = metadata_Relocation::spec(klass_index);

    __ relocate(rspec, 1);
    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, Csrc & 0xffff);
  
#line 10024 "ad_ppc.cpp"
  }
}

uint loadConNKlass_loNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  loadConNKlass_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegNdst, 	dst
  unsigned idx_src   = idx1; 	// immNKlass, 	src
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  iRegNdstOper *op_dst = (iRegNdstOper *)opnd_array(0);
  immNKlassOper *op_src = (immNKlassOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 6399 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // Load high bits into register. Sign extended.
    MachNode *m1 = new loadConNKlass_hiNode();
    m1->add_req(NULL);
    m1->_opnds[0] = op_dst;
    m1->_opnds[1] = op_src;
    ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    nodes->push(m1);

    MachNode *m2 = m1;
    if (!Assembler::is_uimm((jlong)Klass::encode_klass((Klass *)op_src->constant()), 31)) {
      // Value might be 1-extended. Mask out these bits.
      m2 = new loadConNKlass_maskNode();
      m2->add_req(NULL, m1);
      m2->_opnds[0] = op_dst;
      m2->_opnds[1] = op_src;
      m2->_opnds[2] = op_dst;
      ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
      nodes->push(m2);
    }

    MachNode *m3 = new loadConNKlass_loNode();
    m3->add_req(NULL, m2);
    m3->_opnds[0] = op_dst;
    m3->_opnds[1] = op_src;
    m3->_opnds[2] = op_dst;
    ra_->set_pair(m3->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    nodes->push(m3);
  
#line 10077 "ad_ppc.cpp"
  }
}

void loadConP0or1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6437 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 10094 "ad_ppc.cpp"
  }
}

uint loadConP0or1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  {

#line 2943 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);

    MacroAssembler _masm(&cbuf);
    int toc_offset = 0;

    intptr_t val = opnd_array(1)->constant();
    relocInfo::relocType constant_reloc = opnd_array(1)->constant_reloc();  // src
    address const_toc_addr;
    if (constant_reloc == relocInfo::oop_type) {
      // Create an oop constant and a corresponding relocation.
      AddressLiteral a = __ allocate_oop_address((jobject)val);
      const_toc_addr = __ address_constant((address)a.value(), RelocationHolder::none);
      __ relocate(a.rspec());
    } else if (constant_reloc == relocInfo::metadata_type) {
      AddressLiteral a = __ constant_metadata_address((Metadata *)val);
      const_toc_addr = __ address_constant((address)a.value(), RelocationHolder::none);
      __ relocate(a.rspec());
    } else {
      // Create a non-oop constant, no relocation needed.
      const_toc_addr = __ long_constant((jlong)opnd_array(1)->constant());
    }

    if (const_toc_addr == NULL) {
      ciEnv::current()->record_out_of_memory_failure();
      return;
    }
    // Get the constant's TOC offset.
    toc_offset = __ offset_to_method_toc(const_toc_addr);

    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, toc_offset, opnd_array(2)->as_Register(ra_,this,idx2)/* toc */);
  
#line 10144 "ad_ppc.cpp"
  }
}

uint loadConPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConP_hiNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  {

#line 2976 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addis);

    MacroAssembler _masm(&cbuf);
    if (!ra_->C->in_scratch_emit_size()) {
      intptr_t val = opnd_array(1)->constant();
      relocInfo::relocType constant_reloc = opnd_array(1)->constant_reloc();  // src
      address const_toc_addr;
      if (constant_reloc == relocInfo::oop_type) {
        // Create an oop constant and a corresponding relocation.
        AddressLiteral a = __ allocate_oop_address((jobject)val);
        const_toc_addr = __ address_constant((address)a.value(), RelocationHolder::none);
        __ relocate(a.rspec());
      } else if (constant_reloc == relocInfo::metadata_type) {
        AddressLiteral a = __ constant_metadata_address((Metadata *)val);
        const_toc_addr = __ address_constant((address)a.value(), RelocationHolder::none);
        __ relocate(a.rspec());
      } else {  // non-oop pointers, e.g. card mark base, heap top
        // Create a non-oop constant, no relocation needed.
        const_toc_addr = __ long_constant((jlong)opnd_array(1)->constant());
      }

      if (const_toc_addr == NULL) {
        ciEnv::current()->record_out_of_memory_failure();
        return;
      }
      // Get the constant's TOC offset.
      const int toc_offset = __ offset_to_method_toc(const_toc_addr);
      // Store the toc offset of the constant.
      ((loadConP_hiNode*)this)->_const_toc_offset = toc_offset;
    }

    __ addis(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* toc */, MacroAssembler::largeoffset_si16_si16_hi(_const_toc_offset));
  
#line 10196 "ad_ppc.cpp"
  }
}

uint loadConP_hiNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConP_loNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {
    MacroAssembler _masm(&cbuf);

#line 6485 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    int offset = ra_->C->in_scratch_emit_size() ? 0 : _const_toc_offset_hi_node->_const_toc_offset;
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, MacroAssembler::largeoffset_si16_si16_lo(offset), opnd_array(2)->as_Register(ra_,this,idx2)/* base */);
  
#line 10220 "ad_ppc.cpp"
  }
}

uint loadConP_loNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  loadConP_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegPdst, 	dst
  unsigned idx_src   = idx1; 	// immP, 	src
  unsigned idx_toc   = mach_constant_base_node_input(); 	// iRegLdst, 	constanttablebase
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  Node    *n_toc     = lookup(idx_toc);
  iRegPdstOper *op_dst = (iRegPdstOper *)opnd_array(0);
  immPOper *op_src = (immPOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 3014 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    const bool large_constant_pool = true; // TODO: PPC port C->cfg()->_consts_size > 4000;
    if (large_constant_pool) {
      // Create new nodes.
      loadConP_hiNode *m1 = new loadConP_hiNode();
      loadConP_loNode *m2 = new loadConP_loNode();

      // inputs for new nodes
      m1->add_req(NULL, n_toc);
      m2->add_req(NULL, m1);

      // operands for new nodes
      m1->_opnds[0] = new iRegPdstOper(); // dst
      m1->_opnds[1] = op_src;             // src
      m1->_opnds[2] = new iRegPdstOper(); // toc
      m2->_opnds[0] = new iRegPdstOper(); // dst
      m2->_opnds[1] = op_src;             // src
      m2->_opnds[2] = new iRegLdstOper(); // base

      // Initialize ins_attrib TOC fields.
      m1->_const_toc_offset = -1;
      m2->_const_toc_offset_hi_node = m1;

      // Register allocation for new nodes.
      ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
      ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

      nodes->push(m1);
      nodes->push(m2);
      assert(m2->bottom_type()->isa_ptr(), "must be ptr");
    } else {
      loadConPNode *m2 = new loadConPNode();

      // inputs for new nodes
      m2->add_req(NULL, n_toc);

      // operands for new nodes
      m2->_opnds[0] = new iRegPdstOper(); // dst
      m2->_opnds[1] = op_src;             // src
      m2->_opnds[2] = new iRegPdstOper(); // toc

      // Register allocation for new nodes.
      ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

      nodes->push(m2);
      assert(m2->bottom_type()->isa_ptr(), "must be ptr");
    }
  
#line 10294 "ad_ppc.cpp"
  }
}

void loadConP_ExNode::eval_constant(Compile* C) {
  // User did not define an encode section.
}
void loadConFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  {
    MacroAssembler _masm(&cbuf);

#line 6522 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lfs);
    address float_address = __ float_constant(opnd_array(1)->constantF());
    if (float_address == NULL) {
      ciEnv::current()->record_out_of_memory_failure();
      return;
    }
    __ lfs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, __ offset_to_method_toc(float_address), opnd_array(2)->as_Register(ra_,this,idx2)/* toc */);
  
#line 10320 "ad_ppc.cpp"
  }
}

uint loadConFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConFCompNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  {
    MacroAssembler _masm(&cbuf);

#line 6545 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    FloatRegister Rdst    = opnd_array(0)->as_FloatRegister(ra_,this)/* dst */;
    Register Rtoc         = opnd_array(2)->as_Register(ra_,this,idx2)/* toc */;
    address float_address = __ float_constant(opnd_array(1)->constantF());
    if (float_address == NULL) {
      ciEnv::current()->record_out_of_memory_failure();
      return;
    }
    int offset            = __ offset_to_method_toc(float_address);
    int hi = (offset + (1<<15))>>16;
    int lo = offset - hi * (1<<16);

    __ addis(Rtoc, Rtoc, hi);
    __ lfs(Rdst, lo, Rtoc);
    __ addis(Rtoc, Rtoc, -hi);
  
#line 10356 "ad_ppc.cpp"
  }
}

uint loadConFCompNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void  loadConF_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// regF, 	dst
  unsigned idx_src   = idx1; 	// immF, 	src
  unsigned idx_toc   = mach_constant_base_node_input(); 	// iRegLdst, 	constanttablebase
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  Node    *n_toc     = lookup(idx_toc);
  regFOper *op_dst = (regFOper *)opnd_array(0);
  immFOper *op_src = (immFOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 3065 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    bool large_constant_pool = true; // TODO: PPC port C->cfg()->_consts_size > 4000;

    MachNode *m2;
    if (large_constant_pool) {
      m2 = new loadConFCompNode();
    } else {
      m2 = new loadConFNode();
    }
    // inputs for new nodes
    m2->add_req(NULL, n_toc);

    // operands for new nodes
    m2->_opnds[0] = op_dst;
    m2->_opnds[1] = op_src;
    m2->_opnds[2] = new iRegPdstOper(); // constanttablebase

    // register allocation for new nodes
    ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    nodes->push(m2);
  
#line 10403 "ad_ppc.cpp"
  }
}

void loadConF_ExNode::eval_constant(Compile* C) {
  // User did not define an encode section.
}
void loadConDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  {
    MacroAssembler _masm(&cbuf);

#line 6586 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lfd);
    address float_address = __ double_constant(opnd_array(1)->constantD());
    if (float_address == NULL) {
      ciEnv::current()->record_out_of_memory_failure();
      return;
    }
    int offset =  __ offset_to_method_toc(float_address);
    __ lfd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, offset, opnd_array(2)->as_Register(ra_,this,idx2)/* toc */);
  
#line 10430 "ad_ppc.cpp"
  }
}

uint loadConDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConDCompNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  {
    MacroAssembler _masm(&cbuf);

#line 6610 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    FloatRegister Rdst    = opnd_array(0)->as_FloatRegister(ra_,this)/* dst */;
    Register      Rtoc    = opnd_array(2)->as_Register(ra_,this,idx2)/* toc */;
    address float_address = __ double_constant(opnd_array(1)->constantD());
    if (float_address == NULL) {
      ciEnv::current()->record_out_of_memory_failure();
      return;
    }
    int offset = __ offset_to_method_toc(float_address);
    int hi = (offset + (1<<15))>>16;
    int lo = offset - hi * (1<<16);

    __ addis(Rtoc, Rtoc, hi);
    __ lfd(Rdst, lo, Rtoc);
    __ addis(Rtoc, Rtoc, -hi);
  
#line 10466 "ad_ppc.cpp"
  }
}

uint loadConDCompNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void  loadConD_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// regD, 	dst
  unsigned idx_src   = idx1; 	// immD, 	src
  unsigned idx_toc   = mach_constant_base_node_input(); 	// iRegLdst, 	constanttablebase
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  Node    *n_toc     = lookup(idx_toc);
  regDOper *op_dst = (regDOper *)opnd_array(0);
  immDOper *op_src = (immDOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 3089 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    bool large_constant_pool = true; // TODO: PPC port C->cfg()->_consts_size > 4000;

    MachNode *m2;
    if (large_constant_pool) {
      m2 = new loadConDCompNode();
    } else {
      m2 = new loadConDNode();
    }
    // inputs for new nodes
    m2->add_req(NULL, n_toc);

    // operands for new nodes
    m2->_opnds[0] = op_dst;
    m2->_opnds[1] = op_src;
    m2->_opnds[2] = new iRegPdstOper(); // constanttablebase

    // register allocation for new nodes
    ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    nodes->push(m2);
  
#line 10513 "ad_ppc.cpp"
  }
}

void loadConD_ExNode::eval_constant(Compile* C) {
  // User did not define an encode section.
}
void prefetch_alloc_zeroNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 6653 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_dcbtst);
    __ dcbz(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10534 "ad_ppc.cpp"
  }
}

uint prefetch_alloc_zeroNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void prefetch_alloc_zero_no_offsetNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 6667 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_dcbtst);
    __ dcbz(as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10556 "ad_ppc.cpp"
  }
}

uint prefetch_alloc_zero_no_offsetNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void prefetch_allocNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 6681 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_dcbtst);
    __ dcbtst(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10579 "ad_ppc.cpp"
  }
}

uint prefetch_allocNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void prefetch_alloc_no_offsetNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 6695 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_dcbtst);
    __ dcbtst(as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10601 "ad_ppc.cpp"
  }
}

uint prefetch_alloc_no_offsetNode::size(PhaseRegAlloc *ra_) const {
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
    MacroAssembler _masm(&cbuf);

#line 6711 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stb);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stb(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10625 "ad_ppc.cpp"
  }
}

uint storeBNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6726 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_sth);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ sth(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10649 "ad_ppc.cpp"
  }
}

uint storeCNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3111 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stw);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stw(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10673 "ad_ppc.cpp"
  }
}

uint storeINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeI_convL2INode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3111 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stw);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stw(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10697 "ad_ppc.cpp"
  }
}

uint storeI_convL2INode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3118 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_std);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ std(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10723 "ad_ppc.cpp"
  }
}

uint storeLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeA8BNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3118 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_std);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ std(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10749 "ad_ppc.cpp"
  }
}

uint storeA8BNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeV16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6789 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ stxvd2x(opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 10771 "ad_ppc.cpp"
  }
}

uint storeV16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3111 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stw);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stw(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10795 "ad_ppc.cpp"
  }
}

uint storeNNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeNKlassNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3111 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stw);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stw(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10819 "ad_ppc.cpp"
  }
}

uint storeNKlassNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storePNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3118 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_std);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ std(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10845 "ad_ppc.cpp"
  }
}

uint storePNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3127 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stfs);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stfs(opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10869 "ad_ppc.cpp"
  }
}

uint storeFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3134 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stfd);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stfd(opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10893 "ad_ppc.cpp"
  }
}

uint storeDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeCM_CMSNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// releaseFieldAddr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  {

#line 3143 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // FIXME: Implement this as a cmove and use a fixed condition code
    // register which is written on every transition to compiled code,
    // e.g. in call-stub and when returning from runtime stubs.
    //
    // Proposed code sequence for the cmove implementation:
    //
    // Label skip_release;
    // __ beq(CCRfixed, skip_release);
    // __ release();
    // __ bind(skip_release);
    // __ stb(card mark);

    MacroAssembler _masm(&cbuf);
    Label skip_storestore;

#if 0 // TODO: PPC port
    // Check CMSCollectorCardTableBarrierSetBSExt::_requires_release and do the
    // StoreStore barrier conditionally.
    __ lwz(R0, 0, opnd_array(2)->as_Register(ra_,this,idx2)/* releaseFieldAddr */);
    __ cmpwi(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, R0, 0);
    __ beq_predict_taken(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, skip_storestore);
#endif
    __ li(R0, 0);
    __ membar(Assembler::StoreStore);
#if 0 // TODO: PPC port
    __ bind(skip_storestore);
#endif

    // Do the store.
    if (opnd_array(1)->index(ra_,this,idx1) == 0) {
      __ stb(R0, opnd_array(1)->disp(ra_,this,idx1), as_Register(opnd_array(1)->base(ra_,this,idx1)));
    } else {
      assert(0 == opnd_array(1)->disp(ra_,this,idx1), "no displacement possible with indexed load/stores on ppc");
      __ stbx(R0, as_Register(opnd_array(1)->base(ra_,this,idx1)), as_Register(opnd_array(1)->index(ra_,this,idx1)));
    }
  
#line 10950 "ad_ppc.cpp"
  }
}

void storeCM_G1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 6899 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ li(R0, 0);
    //__ release(); // G1: oops are allowed to get visible after dirty marking
    guarantee(as_Register(opnd_array(1)->base(ra_,this,idx1))!= R1_SP, "use frame_slots_bias");
    __ stb(R0, opnd_array(1)->disp(ra_,this,idx1), as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 10971 "ad_ppc.cpp"
  }
}

uint storeCM_G1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void encodeP_shiftNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6921 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Universe::narrow_oop_shift() & 0x3f);
  
#line 10993 "ad_ppc.cpp"
  }
}

uint encodeP_shiftNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void encodeP_subNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6935 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ sub_const_optimized(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Universe::narrow_oop_base(), R0);
  
#line 11015 "ad_ppc.cpp"
  }
}

void cond_sub_baseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  {
    MacroAssembler _masm(&cbuf);

#line 6951 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Label done;
    __ beq(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ sub_const_optimized(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, Universe::narrow_oop_base(), R0);
    __ bind(done);
  
#line 11036 "ad_ppc.cpp"
  }
}

void cond_set_0_oopNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  {
    MacroAssembler _masm(&cbuf);

#line 6969 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description exists.
    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ isel_0(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, Assembler::equal, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */);
  
#line 11055 "ad_ppc.cpp"
  }
}

uint cond_set_0_oopNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void encodeP_DisjointNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 6984 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ rldicl(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 64-Universe::narrow_oop_shift(), 32);
  
#line 11077 "ad_ppc.cpp"
  }
}

uint encodeP_DisjointNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  encodeP_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegNdst, 	dst
  unsigned idx_src   = idx1; 	// iRegPdst, 	src
  unsigned idx_crx   = idx2; 	// flagsReg, 	crx
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  Node    *n_crx     = lookup(idx_crx);
  iRegNdstOper *op_dst = (iRegNdstOper *)opnd_array(0);
  iRegPdstOper *op_src = (iRegPdstOper *)opnd_array(1);
  flagsRegOper *op_crx = (flagsRegOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 3182 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"


    if (VM_Version::has_isel()) {
      // use isel instruction with Power 7
      cmpP_reg_imm16Node *n_compare  = new cmpP_reg_imm16Node();
      encodeP_subNode    *n_sub_base = new encodeP_subNode();
      encodeP_shiftNode  *n_shift    = new encodeP_shiftNode();
      cond_set_0_oopNode *n_cond_set = new cond_set_0_oopNode();

      n_compare->add_req(n_region, n_src);
      n_compare->_opnds[0] = op_crx;
      n_compare->_opnds[1] = op_src;
      n_compare->_opnds[2] = new immL16Oper(0);

      n_sub_base->add_req(n_region, n_src);
      n_sub_base->_opnds[0] = op_dst;
      n_sub_base->_opnds[1] = op_src;
      n_sub_base->_bottom_type = _bottom_type;

      n_shift->add_req(n_region, n_sub_base);
      n_shift->_opnds[0] = op_dst;
      n_shift->_opnds[1] = op_dst;
      n_shift->_bottom_type = _bottom_type;

      n_cond_set->add_req(n_region, n_compare, n_shift);
      n_cond_set->_opnds[0] = op_dst;
      n_cond_set->_opnds[1] = op_crx;
      n_cond_set->_opnds[2] = op_dst;
      n_cond_set->_bottom_type = _bottom_type;

      ra_->set_pair(n_compare->_idx, ra_->get_reg_second(n_crx), ra_->get_reg_first(n_crx));
      ra_->set_pair(n_sub_base->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
      ra_->set_pair(n_shift->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
      ra_->set_pair(n_cond_set->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

      nodes->push(n_compare);
      nodes->push(n_sub_base);
      nodes->push(n_shift);
      nodes->push(n_cond_set);

    } else {
      // before Power 7
      moveRegNode        *n_move     = new moveRegNode();
      cmpP_reg_imm16Node *n_compare  = new cmpP_reg_imm16Node();
      encodeP_shiftNode  *n_shift    = new encodeP_shiftNode();
      cond_sub_baseNode  *n_sub_base = new cond_sub_baseNode();

      n_move->add_req(n_region, n_src);
      n_move->_opnds[0] = op_dst;
      n_move->_opnds[1] = op_src;
      ra_->set_oop(n_move, true); // Until here, 'n_move' still produces an oop.

      n_compare->add_req(n_region, n_src);
      n_compare->add_prec(n_move);

      n_compare->_opnds[0] = op_crx;
      n_compare->_opnds[1] = op_src;
      n_compare->_opnds[2] = new immL16Oper(0);

      n_sub_base->add_req(n_region, n_compare, n_src);
      n_sub_base->_opnds[0] = op_dst;
      n_sub_base->_opnds[1] = op_crx;
      n_sub_base->_opnds[2] = op_src;
      n_sub_base->_bottom_type = _bottom_type;

      n_shift->add_req(n_region, n_sub_base);
      n_shift->_opnds[0] = op_dst;
      n_shift->_opnds[1] = op_dst;
      n_shift->_bottom_type = _bottom_type;

      ra_->set_pair(n_shift->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
      ra_->set_pair(n_compare->_idx, ra_->get_reg_second(n_crx), ra_->get_reg_first(n_crx));
      ra_->set_pair(n_sub_base->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
      ra_->set_pair(n_move->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

      nodes->push(n_move);
      nodes->push(n_compare);
      nodes->push(n_sub_base);
      nodes->push(n_shift);
    }

    assert(!(ra_->is_oop(this)), "sanity"); // This is not supposed to be GC'ed.
  
#line 11188 "ad_ppc.cpp"
  }
}

void  encodeP_not_null_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegNdst, 	dst
  unsigned idx_src   = idx1; 	// iRegPdst, 	src
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  iRegNdstOper *op_dst = (iRegNdstOper *)opnd_array(0);
  iRegPdstOper *op_src = (iRegPdstOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 3266 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"


    encodeP_subNode *n1 = new encodeP_subNode();
    n1->add_req(n_region, n_src);
    n1->_opnds[0] = op_dst;
    n1->_opnds[1] = op_src;
    n1->_bottom_type = _bottom_type;

    encodeP_shiftNode *n2 = new encodeP_shiftNode();
    n2->add_req(n_region, n1);
    n2->_opnds[0] = op_dst;
    n2->_opnds[1] = op_dst;
    n2->_bottom_type = _bottom_type;
    ra_->set_pair(n1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    ra_->set_pair(n2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

    nodes->push(n1);
    nodes->push(n2);
    assert(!(ra_->is_oop(this)), "sanity"); // This is not supposed to be GC'ed.
  
#line 11227 "ad_ppc.cpp"
  }
}

void encodeP_not_null_base_nullNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7023 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Universe::narrow_oop_shift() & 0x3f);
  
#line 11244 "ad_ppc.cpp"
  }
}

uint encodeP_not_null_base_nullNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void encodeP_narrow_oop_shift_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7038 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 11266 "ad_ppc.cpp"
  }
}

void decodeN_shiftNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7055 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicr);
    __ sldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Universe::narrow_oop_shift());
  
#line 11283 "ad_ppc.cpp"
  }
}

uint decodeN_shiftNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void decodeN_addNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7069 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ add_const_optimized(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Universe::narrow_oop_base(), R0);
  
#line 11305 "ad_ppc.cpp"
  }
}

void cond_add_baseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7088 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Label done;
    __ beq(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ add_const_optimized(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Universe::narrow_oop_base(), R0);
    __ bind(done);
  
#line 11326 "ad_ppc.cpp"
  }
}

void cond_set_0_ptrNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  {
    MacroAssembler _masm(&cbuf);

#line 7108 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description exists.
    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ isel_0(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, Assembler::equal, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */);
  
#line 11345 "ad_ppc.cpp"
  }
}

uint cond_set_0_ptrNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  decodeN_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegPdst, 	dst
  unsigned idx_src   = idx1; 	// iRegNsrc, 	src
  unsigned idx_crx   = idx2; 	// flagsReg, 	crx
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  Node    *n_crx     = lookup(idx_crx);
  iRegPdstOper *op_dst = (iRegPdstOper *)opnd_array(0);
  iRegNsrcOper *op_src = (iRegNsrcOper *)opnd_array(1);
  flagsRegOper *op_crx = (flagsRegOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 3287 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    decodeN_shiftNode *n_shift    = new decodeN_shiftNode();
    cmpN_reg_imm0Node *n_compare  = new cmpN_reg_imm0Node();

    n_compare->add_req(n_region, n_src);
    n_compare->_opnds[0] = op_crx;
    n_compare->_opnds[1] = op_src;
    n_compare->_opnds[2] = new immN_0Oper(TypeNarrowOop::NULL_PTR);

    n_shift->add_req(n_region, n_src);
    n_shift->_opnds[0] = op_dst;
    n_shift->_opnds[1] = op_src;
    n_shift->_bottom_type = _bottom_type;

    if (VM_Version::has_isel()) {
      // use isel instruction with Power 7

      decodeN_addNode *n_add_base = new decodeN_addNode();
      n_add_base->add_req(n_region, n_shift);
      n_add_base->_opnds[0] = op_dst;
      n_add_base->_opnds[1] = op_dst;
      n_add_base->_bottom_type = _bottom_type;

      cond_set_0_ptrNode *n_cond_set = new cond_set_0_ptrNode();
      n_cond_set->add_req(n_region, n_compare, n_add_base);
      n_cond_set->_opnds[0] = op_dst;
      n_cond_set->_opnds[1] = op_crx;
      n_cond_set->_opnds[2] = op_dst;
      n_cond_set->_bottom_type = _bottom_type;

      assert(ra_->is_oop(this) == true, "A decodeN node must produce an oop!");
      ra_->set_oop(n_cond_set, true);

      ra_->set_pair(n_shift->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
      ra_->set_pair(n_compare->_idx, ra_->get_reg_second(n_crx), ra_->get_reg_first(n_crx));
      ra_->set_pair(n_add_base->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
      ra_->set_pair(n_cond_set->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

      nodes->push(n_compare);
      nodes->push(n_shift);
      nodes->push(n_add_base);
      nodes->push(n_cond_set);

    } else {
      // before Power 7
      cond_add_baseNode *n_add_base = new cond_add_baseNode();

      n_add_base->add_req(n_region, n_compare, n_shift);
      n_add_base->_opnds[0] = op_dst;
      n_add_base->_opnds[1] = op_crx;
      n_add_base->_opnds[2] = op_dst;
      n_add_base->_bottom_type = _bottom_type;

      assert(ra_->is_oop(this) == true, "A decodeN node must produce an oop!");
      ra_->set_oop(n_add_base, true);

      ra_->set_pair(n_shift->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
      ra_->set_pair(n_compare->_idx, ra_->get_reg_second(n_crx), ra_->get_reg_first(n_crx));
      ra_->set_pair(n_add_base->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

      nodes->push(n_compare);
      nodes->push(n_shift);
      nodes->push(n_add_base);
    }
  
#line 11438 "ad_ppc.cpp"
  }
}

void decodeN_nullBaseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7138 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicr);
    __ sldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Universe::narrow_oop_shift());
  
#line 11455 "ad_ppc.cpp"
  }
}

uint decodeN_nullBaseNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void decodeN_mergeDisjointNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {
    MacroAssembler _masm(&cbuf);

#line 7155 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldimi);
    __ rldimi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Universe::narrow_oop_shift(), 32-Universe::narrow_oop_shift());
  
#line 11478 "ad_ppc.cpp"
  }
}

uint decodeN_mergeDisjointNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  decodeN_Disjoint_notNull_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx2; 	// iRegPdst, 	dst
  unsigned idx_src   = idx1; 	// iRegNsrc, 	src
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  iRegPdstOper *op_dst = (iRegPdstOper *)opnd_array(2);
  iRegNsrcOper *op_src = (iRegNsrcOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 7176 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    loadBaseNode *n1 = new loadBaseNode();
    n1->add_req(NULL);
    n1->_opnds[0] = op_dst;

    decodeN_mergeDisjointNode *n2 = new decodeN_mergeDisjointNode();
    n2->add_req(n_region, n_src, n1);
    n2->_opnds[0] = op_dst;
    n2->_opnds[1] = op_src;
    n2->_opnds[2] = op_dst;
    n2->_bottom_type = _bottom_type;

    ra_->set_pair(n1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    ra_->set_pair(n2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

    nodes->push(n1);
    nodes->push(n2);
  
#line 11521 "ad_ppc.cpp"
  }
}

void  decodeN_Disjoint_isel_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx2; 	// iRegPdst, 	dst
  unsigned idx_src   = idx1; 	// iRegNsrc, 	src
  unsigned idx_crx   = idx3; 	// flagsReg, 	crx
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  Node    *n_crx     = lookup(idx_crx);
  iRegPdstOper *op_dst = (iRegPdstOper *)opnd_array(2);
  iRegNsrcOper *op_src = (iRegNsrcOper *)opnd_array(1);
  flagsRegOper *op_crx = (flagsRegOper *)opnd_array(3);
  Compile *C = ra_->C;
  {
#line 7205 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    loadBaseNode *n1 = new loadBaseNode();
    n1->add_req(NULL);
    n1->_opnds[0] = op_dst;

    cmpN_reg_imm0Node *n_compare  = new cmpN_reg_imm0Node();
    n_compare->add_req(n_region, n_src);
    n_compare->_opnds[0] = op_crx;
    n_compare->_opnds[1] = op_src;
    n_compare->_opnds[2] = new immN_0Oper(TypeNarrowOop::NULL_PTR);

    decodeN_mergeDisjointNode *n2 = new decodeN_mergeDisjointNode();
    n2->add_req(n_region, n_src, n1);
    n2->_opnds[0] = op_dst;
    n2->_opnds[1] = op_src;
    n2->_opnds[2] = op_dst;
    n2->_bottom_type = _bottom_type;

    cond_set_0_ptrNode *n_cond_set = new cond_set_0_ptrNode();
    n_cond_set->add_req(n_region, n_compare, n2);
    n_cond_set->_opnds[0] = op_dst;
    n_cond_set->_opnds[1] = op_crx;
    n_cond_set->_opnds[2] = op_dst;
    n_cond_set->_bottom_type = _bottom_type;

    assert(ra_->is_oop(this) == true, "A decodeN node must produce an oop!");
    ra_->set_oop(n_cond_set, true);

    ra_->set_pair(n1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    ra_->set_pair(n_compare->_idx, ra_->get_reg_second(n_crx), ra_->get_reg_first(n_crx));
    ra_->set_pair(n2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    ra_->set_pair(n_cond_set->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

    nodes->push(n1);
    nodes->push(n_compare);
    nodes->push(n2);
    nodes->push(n_cond_set);
  
#line 11583 "ad_ppc.cpp"
  }
}

void  decodeN_notNull_addBase_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegPdst, 	dst
  unsigned idx_src   = idx1; 	// iRegNsrc, 	src
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  iRegPdstOper *op_dst = (iRegPdstOper *)opnd_array(0);
  iRegNsrcOper *op_src = (iRegNsrcOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 3353 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    decodeN_shiftNode *n1 = new decodeN_shiftNode();
    n1->add_req(n_region, n_src);
    n1->_opnds[0] = op_dst;
    n1->_opnds[1] = op_src;
    n1->_bottom_type = _bottom_type;

    decodeN_addNode *n2 = new decodeN_addNode();
    n2->add_req(n_region, n1);
    n2->_opnds[0] = op_dst;
    n2->_opnds[1] = op_dst;
    n2->_bottom_type = _bottom_type;
    ra_->set_pair(n1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    ra_->set_pair(n2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

    assert(ra_->is_oop(this) == true, "A decodeN node must produce an oop!");
    ra_->set_oop(n2, true);

    nodes->push(n1);
    nodes->push(n2);
  
#line 11623 "ad_ppc.cpp"
  }
}

void decodeN_unscaledNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7266 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 11640 "ad_ppc.cpp"
  }
}

void decodeN2I_unscaledNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7281 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 11657 "ad_ppc.cpp"
  }
}

void encodePKlass_shiftNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7300 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Universe::narrow_klass_shift());
  
#line 11674 "ad_ppc.cpp"
  }
}

uint encodePKlass_shiftNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void encodePKlass_sub_baseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// base
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7315 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_subf);
    __ subf(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* base */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */);
  
#line 11697 "ad_ppc.cpp"
  }
}

uint encodePKlass_sub_baseNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void encodePKlass_DisjointNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7329 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ rldicl(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 64-Universe::narrow_klass_shift(), 32);
  
#line 11719 "ad_ppc.cpp"
  }
}

uint encodePKlass_DisjointNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  encodePKlass_not_null_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// base
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegNdst, 	dst
  unsigned idx_base  = idx1; 	// iRegLsrc, 	base
  unsigned idx_src   = idx2; 	// iRegPsrc, 	src
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_base    = lookup(idx_base);
  Node    *n_src     = lookup(idx_src);
  iRegNdstOper *op_dst = (iRegNdstOper *)opnd_array(0);
  iRegLsrcOper *op_base = (iRegLsrcOper *)opnd_array(1);
  iRegPsrcOper *op_src = (iRegPsrcOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 7342 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    encodePKlass_sub_baseNode *n1 = new encodePKlass_sub_baseNode();
    n1->add_req(n_region, n_base, n_src);
    n1->_opnds[0] = op_dst;
    n1->_opnds[1] = op_base;
    n1->_opnds[2] = op_src;
    n1->_bottom_type = _bottom_type;

    encodePKlass_shiftNode *n2 = new encodePKlass_shiftNode();
    n2->add_req(n_region, n1);
    n2->_opnds[0] = op_dst;
    n2->_opnds[1] = op_dst;
    n2->_bottom_type = _bottom_type;
    ra_->set_pair(n1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    ra_->set_pair(n2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

    nodes->push(n1);
    nodes->push(n2);
  
#line 11766 "ad_ppc.cpp"
  }
}

void decodeNKlass_shiftNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7389 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicr);
    __ sldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Universe::narrow_klass_shift());
  
#line 11783 "ad_ppc.cpp"
  }
}

uint decodeNKlass_shiftNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void decodeNKlass_add_baseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// base
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7405 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_add);
    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* base */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */);
  
#line 11806 "ad_ppc.cpp"
  }
}

uint decodeNKlass_add_baseNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  decodeNKlass_notNull_addBase_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// base
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegPdst, 	dst
  unsigned idx_base  = idx1; 	// iRegLsrc, 	base
  unsigned idx_src   = idx2; 	// iRegNsrc, 	src
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_base    = lookup(idx_base);
  Node    *n_src     = lookup(idx_src);
  iRegPdstOper *op_dst = (iRegPdstOper *)opnd_array(0);
  iRegLsrcOper *op_base = (iRegLsrcOper *)opnd_array(1);
  iRegNsrcOper *op_src = (iRegNsrcOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 7419 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    decodeNKlass_add_baseNode *n1 = new decodeNKlass_add_baseNode();
    n1->add_req(n_region, n_base, n_src);
    n1->_opnds[0] = op_dst;
    n1->_opnds[1] = op_base;
    n1->_opnds[2] = op_src;
    n1->_bottom_type = _bottom_type;

    decodeNKlass_shiftNode *n2 = new decodeNKlass_shiftNode();
    n2->add_req(n_region, n1);
    n2->_opnds[0] = op_dst;
    n2->_opnds[1] = op_dst;
    n2->_bottom_type = _bottom_type;

    ra_->set_pair(n1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    ra_->set_pair(n2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

    nodes->push(n1);
    nodes->push(n2);
  
#line 11854 "ad_ppc.cpp"
  }
}

void membar_acquireNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 7469 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwsync);
    __ acquire();
  
#line 11871 "ad_ppc.cpp"
  }
}

uint membar_acquireNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void unnecessary_membar_acquireNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint unnecessary_membar_acquireNode::size(PhaseRegAlloc *ra_) const {
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

#line 7503 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwsync);
    __ release();
  
#line 11919 "ad_ppc.cpp"
  }
}

uint membar_releaseNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void membar_release_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 7503 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwsync);
    __ release();
  
#line 11941 "ad_ppc.cpp"
  }
}

uint membar_release_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void membar_storestoreNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 7516 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwsync);
    __ membar(Assembler::StoreStore);
  
#line 11963 "ad_ppc.cpp"
  }
}

uint membar_storestoreNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
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

#line 7539 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_sync);
    __ fence();
  
#line 11998 "ad_ppc.cpp"
  }
}

uint membar_volatileNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void membar_CPUOrderNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // User did not define which encode class to use.
}

uint membar_CPUOrderNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void cmovI_reg_iselNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7596 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description
    // exists. Anyways, the scheduler should be off on Power7.
    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    int cc        = opnd_array(1)->ccode();
    __ isel(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */,
            (Assembler::Condition)(cc & 3), /*invert*/((~cc) & 8), opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
  
#line 12040 "ad_ppc.cpp"
  }
}

uint cmovI_reg_iselNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmovI_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 3375 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    int cc        = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(cc), cc_to_biint(cc, flags_reg), done);
    __ mr(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 12074 "ad_ppc.cpp"
  }
}

uint cmovI_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8);
}

void cmovI_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 3390 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ li(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->constant());
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 12106 "ad_ppc.cpp"
  }
}

uint cmovI_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8);
}

void cmovL_reg_iselNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7642 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description
    // exists. Anyways, the scheduler should be off on Power7.
    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    int cc        = opnd_array(1)->ccode();
    __ isel(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */,
            (Assembler::Condition)(cc & 3), /*invert*/((~cc) & 8), opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
  
#line 12135 "ad_ppc.cpp"
  }
}

uint cmovL_reg_iselNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmovL_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 3375 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    int cc        = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(cc), cc_to_biint(cc, flags_reg), done);
    __ mr(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 12169 "ad_ppc.cpp"
  }
}

uint cmovL_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8);
}

void cmovL_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 3390 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ li(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->constantL());
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 12201 "ad_ppc.cpp"
  }
}

uint cmovL_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8);
}

void cmovN_reg_iselNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7688 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description
    // exists. Anyways, the scheduler should be off on Power7.
    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    int cc        = opnd_array(1)->ccode();
    __ isel(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */,
            (Assembler::Condition)(cc & 3), /*invert*/((~cc) & 8), opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
  
#line 12230 "ad_ppc.cpp"
  }
}

uint cmovN_reg_iselNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmovN_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 3375 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    int cc        = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(cc), cc_to_biint(cc, flags_reg), done);
    __ mr(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 12264 "ad_ppc.cpp"
  }
}

uint cmovN_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8);
}

void cmovN_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 3390 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ li(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->constant());
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 12296 "ad_ppc.cpp"
  }
}

uint cmovN_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8);
}

void cmovP_reg_iselNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7735 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description
    // exists. Anyways, the scheduler should be off on Power7.
    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    int cc        = opnd_array(1)->ccode();
    __ isel(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */,
            (Assembler::Condition)(cc & 3), /*invert*/((~cc) & 8), opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
  
#line 12325 "ad_ppc.cpp"
  }
}

uint cmovP_reg_iselNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmovP_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 3375 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    int cc        = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(cc), cc_to_biint(cc, flags_reg), done);
    __ mr(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 12359 "ad_ppc.cpp"
  }
}

uint cmovP_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8);
}

void cmovP_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {

#line 3390 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ li(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->constant());
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 12391 "ad_ppc.cpp"
  }
}

uint cmovP_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8);
}

void cmovF_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7782 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmovef);
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ fmr(opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */, opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */);
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 12422 "ad_ppc.cpp"
  }
}

uint cmovF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT (InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT (InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8);
}

void cmovD_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 7804 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmovef);
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ fmr(opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */, opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */);
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 12453 "ad_ppc.cpp"
  }
}

uint cmovD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT (InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT (InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8);
}

void storeLConditional_regP_regL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldVal
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newVal
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 7832 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ cmpxchgd(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* oldVal */, opnd_array(3)->as_Register(ra_,this,idx3)/* newVal */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarAcq, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, NULL, true);
  
#line 12480 "ad_ppc.cpp"
  }
}

void storePConditional_regP_regP_regPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldVal
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newVal
  {
    MacroAssembler _masm(&cbuf);

#line 7852 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stdcx_);
    __ stdcx_(opnd_array(3)->as_Register(ra_,this,idx3)/* newVal */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */);
  
#line 12499 "ad_ppc.cpp"
  }
}

void loadPLockedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 7868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ldarx);
    __ ldarx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, MacroAssembler::cmpxchgx_hint_atomic_update());
  
#line 12516 "ad_ppc.cpp"
  }
}

uint loadPLockedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compareAndSwapB_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 7888 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12550 "ad_ppc.cpp"
  }
}

void compareAndSwapB4_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 7908 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12581 "ad_ppc.cpp"
  }
}

void compareAndSwapS_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 7928 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12610 "ad_ppc.cpp"
  }
}

void compareAndSwapS4_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 7948 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12641 "ad_ppc.cpp"
  }
}

void compareAndSwapI_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 7967 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12670 "ad_ppc.cpp"
  }
}

void compareAndSwapN_regP_regN_regNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 7986 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12699 "ad_ppc.cpp"
  }
}

void compareAndSwapL_regP_regL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8005 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12728 "ad_ppc.cpp"
  }
}

void compareAndSwapP_regP_regP_regPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8024 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12757 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapB_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8046 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 12781 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapB4_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8061 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 12807 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapB_acq_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8076 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 12831 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapB4_acq_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8091 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 12857 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapS_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8106 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 12881 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapS4_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8121 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 12907 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapS_acq_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8136 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 12931 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapS4_acq_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8151 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 12957 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapI_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8166 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 12981 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapI_acq_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8181 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    // Acquire only needed in successful case. Weak node is allowed to report unsuccessful in additional rare cases and
    // value is never passed to caller.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13007 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapN_regP_regN_regNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8198 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13031 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapN_acq_regP_regN_regNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8213 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    // Acquire only needed in successful case. Weak node is allowed to report unsuccessful in additional rare cases and
    // value is never passed to caller.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13057 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapL_regP_regL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8230 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    // value is never passed to caller.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true, /*weak*/ true);
  
#line 13082 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapL_acq_regP_regL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8246 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    // Acquire only needed in successful case. Weak node is allowed to report unsuccessful in additional rare cases and
    // value is never passed to caller.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true, /*weak*/ true);
  
#line 13108 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapP_regP_regP_regPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8263 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true, /*weak*/ true);
  
#line 13132 "ad_ppc.cpp"
  }
}

void weakCompareAndSwapP_acq_regP_regP_regPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8278 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    // Acquire only needed in successful case. Weak node is allowed to report unsuccessful in additional rare cases and
    // value is never passed to caller.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true, /*weak*/ true);
  
#line 13158 "ad_ppc.cpp"
  }
}

void compareAndExchangeB_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8297 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13182 "ad_ppc.cpp"
  }
}

void compareAndExchangeB4_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8312 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, R0,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13207 "ad_ppc.cpp"
  }
}

void compareAndExchangeB_acq_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8327 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      // isync would be sufficient in case of CompareAndExchangeAcquire, but we currently don't optimize for that.
      __ sync();
    }
  
#line 13237 "ad_ppc.cpp"
  }
}

void compareAndExchangeB4_acq_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8348 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, R0,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      // isync would be sufficient in case of CompareAndExchangeAcquire, but we currently don't optimize for that.
      __ sync();
    }
  
#line 13268 "ad_ppc.cpp"
  }
}

void compareAndExchangeS_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8369 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13292 "ad_ppc.cpp"
  }
}

void compareAndExchangeS4_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8384 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, R0,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13317 "ad_ppc.cpp"
  }
}

void compareAndExchangeS_acq_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8399 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      // isync would be sufficient in case of CompareAndExchangeAcquire, but we currently don't optimize for that.
      __ sync();
    }
  
#line 13347 "ad_ppc.cpp"
  }
}

void compareAndExchangeS4_acq_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8420 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, R0,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      // isync would be sufficient in case of CompareAndExchangeAcquire, but we currently don't optimize for that.
      __ sync();
    }
  
#line 13378 "ad_ppc.cpp"
  }
}

void compareAndExchangeI_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8441 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13402 "ad_ppc.cpp"
  }
}

void compareAndExchangeI_acq_regP_regI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8456 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      // isync would be sufficient in case of CompareAndExchangeAcquire, but we currently don't optimize for that.
      __ sync();
    }
  
#line 13432 "ad_ppc.cpp"
  }
}

void compareAndExchangeN_regP_regN_regNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8477 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13456 "ad_ppc.cpp"
  }
}

void compareAndExchangeN_acq_regP_regN_regNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8492 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      // isync would be sufficient in case of CompareAndExchangeAcquire, but we currently don't optimize for that.
      __ sync();
    }
  
#line 13486 "ad_ppc.cpp"
  }
}

void compareAndExchangeL_regP_regL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8513 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, NULL, true);
  
#line 13510 "ad_ppc.cpp"
  }
}

void compareAndExchangeL_acq_regP_regL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8528 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, NULL, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      // isync would be sufficient in case of CompareAndExchangeAcquire, but we currently don't optimize for that.
      __ sync();
    }
  
#line 13540 "ad_ppc.cpp"
  }
}

void compareAndExchangeP_regP_regP_regPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8549 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, NULL, true);
  
#line 13564 "ad_ppc.cpp"
  }
}

void compareAndExchangeP_acq_regP_regP_regPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8564 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, NULL, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      // isync would be sufficient in case of CompareAndExchangeAcquire, but we currently don't optimize for that.
      __ sync();
    }
  
#line 13594 "ad_ppc.cpp"
  }
}

void getAndAddBNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8587 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddb(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, noreg, noreg, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13619 "ad_ppc.cpp"
  }
}

void getAndAddB4Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8604 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddb(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13646 "ad_ppc.cpp"
  }
}

void getAndAddSNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8621 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddh(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, noreg, noreg, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13671 "ad_ppc.cpp"
  }
}

void getAndAddS4Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8638 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddh(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13698 "ad_ppc.cpp"
  }
}

void getAndAddINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8654 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddw(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13723 "ad_ppc.cpp"
  }
}

void getAndAddLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8670 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddd(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13748 "ad_ppc.cpp"
  }
}

void getAndSetBNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8687 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetb(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  noreg, noreg, noreg, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13773 "ad_ppc.cpp"
  }
}

void getAndSetB4Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8704 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetb(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13800 "ad_ppc.cpp"
  }
}

void getAndSetSNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8721 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandseth(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  noreg, noreg, noreg, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13825 "ad_ppc.cpp"
  }
}

void getAndSetS4Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8738 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandseth(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13852 "ad_ppc.cpp"
  }
}

void getAndSetINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8754 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetw(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13877 "ad_ppc.cpp"
  }
}

void getAndSetLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8770 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetd(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13902 "ad_ppc.cpp"
  }
}

void getAndSetPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8786 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetd(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13927 "ad_ppc.cpp"
  }
}

void getAndSetNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  {
    MacroAssembler _masm(&cbuf);

#line 8802 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetw(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13952 "ad_ppc.cpp"
  }
}

void addI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8822 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_add);
    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 13970 "ad_ppc.cpp"
  }
}

uint addI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_reg_reg_2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8835 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_add);
    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 13993 "ad_ppc.cpp"
  }
}

uint addI_reg_reg_2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8861 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ addi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 14016 "ad_ppc.cpp"
  }
}

uint addI_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_reg_immhi16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8873 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addis);
    __ addis(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant())>>16);
  
#line 14039 "ad_ppc.cpp"
  }
}

uint addI_reg_immhi16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8885 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_add);
    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14062 "ad_ppc.cpp"
  }
}

uint addL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_reg_2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8898 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_add);
    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14085 "ad_ppc.cpp"
  }
}

uint addL_reg_reg_2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_regL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8925 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_add);
    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14108 "ad_ppc.cpp"
  }
}

uint addI_regL_regLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8938 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ addi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 14131 "ad_ppc.cpp"
  }
}

uint addL_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_immhi16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8952 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addis);
    __ addis(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constantL())>>16);
  
#line 14154 "ad_ppc.cpp"
  }
}

uint addL_reg_immhi16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8964 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_add);
    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14177 "ad_ppc.cpp"
  }
}

uint addP_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8978 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ addi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 14200 "ad_ppc.cpp"
  }
}

uint addP_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_reg_immhi16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 8992 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addis);
    __ addis(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constantL())>>16);
  
#line 14223 "ad_ppc.cpp"
  }
}

uint addP_reg_immhi16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9007 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_subf);
    __ subf(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 14246 "ad_ppc.cpp"
  }
}

uint subI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subI_imm16_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9024 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_subfic);
    __ subfic(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(1)->constant());
  
#line 14269 "ad_ppc.cpp"
  }
}

uint subI_imm16_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void signmask32I_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 9040 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_srawi);
    __ srawi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0x1f);
  
#line 14291 "ad_ppc.cpp"
  }
}

uint signmask32I_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void negI_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9064 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_neg);
    __ neg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14314 "ad_ppc.cpp"
  }
}

uint negI_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9076 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_subf);
    __ subf(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 14337 "ad_ppc.cpp"
  }
}

uint subL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subI_regL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9089 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_subf);
    __ subf(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 14360 "ad_ppc.cpp"
  }
}

uint subI_regL_regLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void signmask64I_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 9105 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_sradi);
    __ sradi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0x3f);
  
#line 14382 "ad_ppc.cpp"
  }
}

uint signmask64I_regLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void signmask64L_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 9121 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_sradi);
    __ sradi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0x3f);
  
#line 14404 "ad_ppc.cpp"
  }
}

uint signmask64L_regLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void negL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9133 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_neg);
    __ neg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14427 "ad_ppc.cpp"
  }
}

uint negL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void negI_con0_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9146 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_neg);
    __ neg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14450 "ad_ppc.cpp"
  }
}

uint negI_con0_regLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9163 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_mullw);
    __ mullw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14473 "ad_ppc.cpp"
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
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9177 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_mulli);
    __ mulli(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 14496 "ad_ppc.cpp"
  }
}

uint mulI_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9190 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_mulld);
    __ mulld(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14519 "ad_ppc.cpp"
  }
}

uint mulL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulHighL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9204 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_mulhd);
    __ mulhd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14542 "ad_ppc.cpp"
  }
}

uint mulHighL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulL_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9218 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_mulli);
    __ mulli(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 14565 "ad_ppc.cpp"
  }
}

uint mulL_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void divI_reg_immIvalueMinus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9232 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_neg);
    __ neg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 14588 "ad_ppc.cpp"
  }
}

uint divI_reg_immIvalueMinus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void divI_reg_regnotMinus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9249 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_divw);
    __ divw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14611 "ad_ppc.cpp"
  }
}

uint divI_reg_regnotMinus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmovI_bne_negI_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 9265 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);
    Label done;
    __ bne(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, done);
    __ neg(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* src1 */);
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 14639 "ad_ppc.cpp"
  }
}

uint cmovI_bne_negI_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT (InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT (InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8);
}

void divL_reg_immLvalueMinus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9297 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_neg);
    __ neg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 14662 "ad_ppc.cpp"
  }
}

uint divL_reg_immLvalueMinus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void divL_reg_regnotMinus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9312 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_divd);
    __ divd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14685 "ad_ppc.cpp"
  }
}

uint divL_reg_regnotMinus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmovL_bne_negL_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 9328 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);
    Label done;
    __ bne(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, done);
    __ neg(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* src1 */);
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 14713 "ad_ppc.cpp"
  }
}

uint cmovL_bne_negL_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT (InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT (InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8);
}

void maskI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {
    MacroAssembler _masm(&cbuf);

#line 9402 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->constant());
  
#line 14736 "ad_ppc.cpp"
  }
}

uint maskI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void lShiftI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9416 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_slw);
    __ slw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14759 "ad_ppc.cpp"
  }
}

uint lShiftI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void lShiftI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9440 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwinm);
    __ slwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x1f);
  
#line 14782 "ad_ppc.cpp"
  }
}

uint lShiftI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void lShiftI_andI_immInegpow2_imm5Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  {
    MacroAssembler _masm(&cbuf);

#line 9454 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwinm); // FIXME: assert that rlwinm is equal to addi
    long src2      = opnd_array(2)->constant();
    long src3      = opnd_array(3)->constant();
    long maskbits  = src3 + log2_long((jlong) (julong) (juint) -src2);
    if (maskbits >= 32) {
      __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, 0); // addi
    } else {
      __ rlwinm(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, src3 & 0x1f, 0, (31-maskbits) & 0x1f);
    }
  
#line 14813 "ad_ppc.cpp"
  }
}

uint lShiftI_andI_immInegpow2_imm5Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void lShiftI_andI_immInegpow2_rShiftI_imm5Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9475 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwinm); // FIXME: assert that rlwinm is equal to addi
    long src2      = opnd_array(3)->constant();
    long src3      = opnd_array(2)->constant();
    long maskbits  = src3 + log2_long((jlong) (julong) (juint) -src2);
    if (maskbits >= 32) {
      __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, 0); // addi
    } else {
      __ rlwinm(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 0, 0, (31-maskbits) & 0x1f);
    }
  
#line 14844 "ad_ppc.cpp"
  }
}

uint lShiftI_andI_immInegpow2_rShiftI_imm5Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void lShiftL_regL_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9496 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_sld);
    __ sld(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14867 "ad_ppc.cpp"
  }
}

uint lShiftL_regL_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void lshiftL_regL_immINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9520 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicr);
    __ sldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 14890 "ad_ppc.cpp"
  }
}

uint lshiftL_regL_immINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void lShiftL_regI_immGE32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9534 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicr);
    __ sldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 14913 "ad_ppc.cpp"
  }
}

uint lShiftL_regI_immGE32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void scaledPositiveI2L_lShiftL_convI2L_reg_imm6Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9549 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldic);
    __ clrlsldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 0x20, opnd_array(2)->constant());
  
#line 14936 "ad_ppc.cpp"
  }
}

uint scaledPositiveI2L_lShiftL_convI2L_reg_imm6Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void arShiftI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9563 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_sraw);
    __ sraw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14959 "ad_ppc.cpp"
  }
}

uint arShiftI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void arShiftI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9588 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_srawi);
    __ srawi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x1f);
  
#line 14982 "ad_ppc.cpp"
  }
}

uint arShiftI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void arShiftL_regL_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9602 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_srad);
    __ srad(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15005 "ad_ppc.cpp"
  }
}

uint arShiftL_regL_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void arShiftL_regL_immINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9628 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_sradi);
    __ sradi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15028 "ad_ppc.cpp"
  }
}

uint arShiftL_regL_immINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convL2I_arShiftL_regL_immINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9641 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_sradi);
    __ sradi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15051 "ad_ppc.cpp"
  }
}

uint convL2I_arShiftL_regL_immINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void urShiftI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9655 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_srw);
    __ srw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15074 "ad_ppc.cpp"
  }
}

uint urShiftI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void urShiftI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9681 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwinm);
    __ srwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x1f);
  
#line 15097 "ad_ppc.cpp"
  }
}

uint urShiftI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void urShiftL_regL_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9695 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_srd);
    __ srd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15120 "ad_ppc.cpp"
  }
}

uint urShiftL_regL_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void urShiftL_regL_immINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9721 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15143 "ad_ppc.cpp"
  }
}

uint urShiftL_regL_immINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convL2I_urShiftL_regL_immINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9734 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15166 "ad_ppc.cpp"
  }
}

uint convL2I_urShiftL_regL_immINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void shrP_convP2X_reg_imm6Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9747 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15189 "ad_ppc.cpp"
  }
}

uint shrP_convP2X_reg_imm6Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andI_urShiftI_regI_immI_immIpow2minus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  {
    MacroAssembler _masm(&cbuf);

#line 9760 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    int rshift = (opnd_array(2)->constant()) & 0x1f;
    int length = log2_long(((jlong) opnd_array(3)->constant()) + 1);
    if (rshift + length > 32) {
      // if necessary, adjust mask to omit rotated bits.
      length = 32 - rshift;
    }
    __ extrdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, length, 64 - (rshift + length));
  
#line 15219 "ad_ppc.cpp"
  }
}

uint andI_urShiftI_regI_immI_immIpow2minus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_urShiftL_regL_immI_immLpow2minus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  {
    MacroAssembler _masm(&cbuf);

#line 9779 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    int rshift  = (opnd_array(2)->constant()) & 0x3f;
    int length = log2_long(((jlong) opnd_array(3)->constantL()) + 1);
    if (rshift + length > 64) {
      // if necessary, adjust mask to omit rotated bits.
      length = 64 - rshift;
    }
    __ extrdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, length, 64 - (rshift + length));
  
#line 15249 "ad_ppc.cpp"
  }
}

uint andL_urShiftL_regL_immI_immLpow2minus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sxtI_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 9797 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_extsw);
    __ extsw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 15271 "ad_ppc.cpp"
  }
}

uint sxtI_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rotlI_reg_immi8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  {
    MacroAssembler _masm(&cbuf);

#line 9813 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwinm);
    __ rotlwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->constant());
  
#line 15295 "ad_ppc.cpp"
  }
}

uint rotlI_reg_immi8Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rotlI_reg_immi8_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  {
    MacroAssembler _masm(&cbuf);

#line 9813 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwinm);
    __ rotlwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(3)->constant());
  
#line 15319 "ad_ppc.cpp"
  }
}

uint rotlI_reg_immi8_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rotrI_reg_immi8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  {
    MacroAssembler _masm(&cbuf);

#line 9827 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwinm);
    __ rotrwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->constant());
  
#line 15343 "ad_ppc.cpp"
  }
}

uint rotrI_reg_immi8Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rotrI_reg_immi8_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  {
    MacroAssembler _masm(&cbuf);

#line 9827 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwinm);
    __ rotrwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(3)->constant());
  
#line 15367 "ad_ppc.cpp"
  }
}

uint rotrI_reg_immi8_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9842 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fadds);
    __ fadds(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15390 "ad_ppc.cpp"
  }
}

uint addF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9855 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fadd);
    __ fadd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15413 "ad_ppc.cpp"
  }
}

uint addD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fsubs);
    __ fsubs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15436 "ad_ppc.cpp"
  }
}

uint subF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void subD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9880 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fsub);
    __ fsub(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15459 "ad_ppc.cpp"
  }
}

uint subD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9892 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fmuls);
    __ fmuls(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15482 "ad_ppc.cpp"
  }
}

uint mulF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mulD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9904 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fmul);
    __ fmul(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15505 "ad_ppc.cpp"
  }
}

uint mulD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void divF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9916 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fdivs);
    __ fdivs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15528 "ad_ppc.cpp"
  }
}

uint divF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void divD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 9928 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fdiv);
    __ fdiv(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15551 "ad_ppc.cpp"
  }
}

uint divD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void absF_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 9940 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fabs);
    __ fabs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15573 "ad_ppc.cpp"
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
    MacroAssembler _masm(&cbuf);

#line 9952 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fabs);
    __ fabs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15595 "ad_ppc.cpp"
  }
}

uint absD_regNode::size(PhaseRegAlloc *ra_) const {
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

#line 9963 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fneg);
    __ fneg(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15617 "ad_ppc.cpp"
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

#line 9974 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fneg);
    __ fneg(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15639 "ad_ppc.cpp"
  }
}

uint negD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void negF_absF_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 9986 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fnabs);
    __ fnabs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15661 "ad_ppc.cpp"
  }
}

uint negF_absF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void negD_absD_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 9998 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fnabs);
    __ fnabs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15683 "ad_ppc.cpp"
  }
}

uint negD_absD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sqrtD_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10011 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fsqrt);
    __ fsqrt(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15705 "ad_ppc.cpp"
  }
}

uint sqrtD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sqrtF_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10026 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fsqrts);
    __ fsqrts(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15727 "ad_ppc.cpp"
  }
}

uint sqrtF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void roundDouble_nopNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint roundDouble_nopNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void roundFloat_nopNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint roundFloat_nopNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void maddF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10063 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fmadds);
    __ fmadds(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 15777 "ad_ppc.cpp"
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
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10076 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fmadd);
    __ fmadd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 15801 "ad_ppc.cpp"
  }
}

uint maddD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mnsubF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10090 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fnmsubs);
    __ fnmsubs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 15825 "ad_ppc.cpp"
  }
}

uint mnsubF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mnsubF_reg_reg_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10090 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fnmsubs);
    __ fnmsubs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 15849 "ad_ppc.cpp"
  }
}

uint mnsubF_reg_reg_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mnsubD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10104 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fnmsub);
    __ fnmsub(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 15873 "ad_ppc.cpp"
  }
}

uint mnsubD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mnsubD_reg_reg_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10104 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fnmsub);
    __ fnmsub(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 15897 "ad_ppc.cpp"
  }
}

uint mnsubD_reg_reg_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mnaddF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10118 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fnmadds);
    __ fnmadds(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 15921 "ad_ppc.cpp"
  }
}

uint mnaddF_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mnaddF_reg_reg_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10118 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fnmadds);
    __ fnmadds(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 15945 "ad_ppc.cpp"
  }
}

uint mnaddF_reg_reg_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mnaddD_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10132 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fnmadd);
    __ fnmadd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 15969 "ad_ppc.cpp"
  }
}

uint mnaddD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mnaddD_reg_reg_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10132 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fnmadd);
    __ fnmadd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 15993 "ad_ppc.cpp"
  }
}

uint mnaddD_reg_reg_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void msubF_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10145 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fmsubs);
    __ fmsubs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16017 "ad_ppc.cpp"
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
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10158 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fmsub);
    __ fmsub(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16041 "ad_ppc.cpp"
  }
}

uint msubD_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10175 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_and);
    __ andr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16064 "ad_ppc.cpp"
  }
}

uint andI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andI_reg_immIhi16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10188 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_andis_);
    __ andis_(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (int)((unsigned short)((opnd_array(2)->constant()& 0xFFFF0000) >> 16)));
  
#line 16087 "ad_ppc.cpp"
  }
}

uint andI_reg_immIhi16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andI_reg_uimm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10202 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_andi_);
    // FIXME: avoid andi_ ?
    __ andi_(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 16111 "ad_ppc.cpp"
  }
}

uint andI_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andI_reg_immInegpow2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10215 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicr);
    __ clrrdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, log2_long((jlong)(julong)(juint)-(opnd_array(2)->constant())));
  
#line 16134 "ad_ppc.cpp"
  }
}

uint andI_reg_immInegpow2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andI_reg_immIpow2minus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10226 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 64-log2_long((((jlong) opnd_array(2)->constant())+1)));
  
#line 16157 "ad_ppc.cpp"
  }
}

uint andI_reg_immIpow2minus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andI_reg_immIpowerOf2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10238 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwinm);
    __ rlwinm(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 0,
              (31-log2_long((jlong) opnd_array(2)->constant())) & 0x1f, (31-log2_long((jlong) opnd_array(2)->constant())) & 0x1f);
  
#line 16181 "ad_ppc.cpp"
  }
}

uint andI_reg_immIpowerOf2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10253 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_and);
    __ andr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16204 "ad_ppc.cpp"
  }
}

uint andL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_uimm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10267 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_andi_);
    // FIXME: avoid andi_ ?
    __ andi_(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 16228 "ad_ppc.cpp"
  }
}

uint andL_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_immLnegpow2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10280 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicr);
    __ clrrdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, log2_long((jlong)-opnd_array(2)->constantL()));
  
#line 16251 "ad_ppc.cpp"
  }
}

uint andL_reg_immLnegpow2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andL_reg_immLpow2minus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10291 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 64-log2_long((((jlong) opnd_array(2)->constantL())+1)));
  
#line 16274 "ad_ppc.cpp"
  }
}

uint andL_reg_immLpow2minus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convL2I_andL_reg_immLpow2minus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10305 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 64-log2_long((((jlong) opnd_array(2)->constantL())+1)));
  
#line 16297 "ad_ppc.cpp"
  }
}

uint convL2I_andL_reg_immLpow2minus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10319 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ or_unchecked(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16320 "ad_ppc.cpp"
  }
}

uint orI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orI_reg_reg_2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10332 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ or_unchecked(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16343 "ad_ppc.cpp"
  }
}

uint orI_reg_reg_2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orI_reg_uimm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10358 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ori);
    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0xFFFF);
  
#line 16366 "ad_ppc.cpp"
  }
}

uint orI_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10372 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ or_unchecked(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16389 "ad_ppc.cpp"
  }
}

uint orL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orI_regL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10386 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ or_unchecked(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16412 "ad_ppc.cpp"
  }
}

uint orI_regL_regLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void orL_reg_uimm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  {
    MacroAssembler _masm(&cbuf);

#line 10400 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ori);
    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constantL()) & 0xFFFF);
  
#line 16435 "ad_ppc.cpp"
  }
}

uint orL_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xorI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10414 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_xor);
    __ xorr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16458 "ad_ppc.cpp"
  }
}

uint xorI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xorI_reg_reg_2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10427 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_xor);
    __ xorr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16481 "ad_ppc.cpp"
  }
}

uint xorI_reg_reg_2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xorI_reg_uimm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10453 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_xori);
    __ xori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 16504 "ad_ppc.cpp"
  }
}

uint xorI_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xorL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10467 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_xor);
    __ xorr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16527 "ad_ppc.cpp"
  }
}

uint xorL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xorI_regL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10481 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_xor);
    __ xorr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16550 "ad_ppc.cpp"
  }
}

uint xorI_regL_regLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xorL_reg_uimm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10495 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_xori);
    __ xori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 16573 "ad_ppc.cpp"
  }
}

uint xorL_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void notI_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10508 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_nor);
    __ nor(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 16596 "ad_ppc.cpp"
  }
}

uint notI_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void notL_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10521 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_nor);
    __ nor(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 16619 "ad_ppc.cpp"
  }
}

uint notL_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andcI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  {

#line 3405 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_andc);
    MacroAssembler _masm(&cbuf);
    __ andc(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* src3 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 16643 "ad_ppc.cpp"
  }
}

uint andcI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andcI_reg_reg_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {

#line 3405 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_andc);
    MacroAssembler _masm(&cbuf);
    __ andc(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src3 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */);
  
#line 16667 "ad_ppc.cpp"
  }
}

uint andcI_reg_reg_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void andcL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 10547 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_andc);
    __ andc(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16690 "ad_ppc.cpp"
  }
}

uint andcL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveL2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10576 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ mtfprd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 16711 "ad_ppc.cpp"
  }
}

uint moveL2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveI2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10589 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ mtfprwa(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 16732 "ad_ppc.cpp"
  }
}

uint moveI2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void stkI_to_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2637 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 16756 "ad_ppc.cpp"
  }
}

uint stkI_to_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void regI_to_stkINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 3111 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stw);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    __ stw(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 16779 "ad_ppc.cpp"
  }
}

uint regI_to_stkINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void stkL_to_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2656 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 16804 "ad_ppc.cpp"
  }
}

uint stkL_to_regLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void regL_to_stkLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 3118 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_std);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ std(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 16829 "ad_ppc.cpp"
  }
}

uint regL_to_stkLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveF2I_stack_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2637 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lwz);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 16853 "ad_ppc.cpp"
  }
}

uint moveF2I_stack_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveF2I_reg_stackNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 3127 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stfs);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    __ stfs(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 16876 "ad_ppc.cpp"
  }
}

uint moveF2I_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveI2F_stack_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10674 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lfs);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lfs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 16899 "ad_ppc.cpp"
  }
}

uint moveI2F_stack_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveI2F_reg_stackNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 3111 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stw);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    __ stw(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 16922 "ad_ppc.cpp"
  }
}

uint moveI2F_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveF2L_reg_stackNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 3134 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stfd);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    __ stfd(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 16945 "ad_ppc.cpp"
  }
}

uint moveF2L_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveD2L_stack_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2656 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 16970 "ad_ppc.cpp"
  }
}

uint moveD2L_stack_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveD2L_reg_stackNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 3134 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_stfd);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    __ stfd(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 16993 "ad_ppc.cpp"
  }
}

uint moveD2L_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveL2D_stack_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 2677 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_lfd);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lfd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 17016 "ad_ppc.cpp"
  }
}

uint moveL2D_stack_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveL2D_reg_stackNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 3118 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_std);
    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ std(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 17041 "ad_ppc.cpp"
  }
}

uint moveL2D_reg_stackNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void moveRegNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10762 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17063 "ad_ppc.cpp"
  }
}

void castX2PNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10777 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17080 "ad_ppc.cpp"
  }
}

void castP2XNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 10790 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17097 "ad_ppc.cpp"
  }
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

void convI2Bool_reg__cmoveNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  {

#line 3411 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);

    MacroAssembler _masm(&cbuf);

    Label done;
    __ cmpwi(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x0));
    __ beq(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, done);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x1));
    __ bind(done);
  
#line 17161 "ad_ppc.cpp"
  }
}

uint convI2Bool_reg__cmoveNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void xorI_convI2Bool_reg_immIvalue1__cmoveNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  {

#line 3411 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);

    MacroAssembler _masm(&cbuf);

    Label done;
    __ cmpwi(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x1));
    __ beq(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, done);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x0));
    __ bind(done);
  
#line 17192 "ad_ppc.cpp"
  }
}

uint xorI_convI2Bool_reg_immIvalue1__cmoveNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void convI2Bool_andI_reg_immIpowerOf2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {
    MacroAssembler _masm(&cbuf);

#line 10905 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwinm);
    __ rlwinm(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, (32-log2_long((jlong)opnd_array(2)->constant())) & 0x1f, 31, 31);
  
#line 17215 "ad_ppc.cpp"
  }
}

uint convI2Bool_andI_reg_immIpowerOf2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convP2Bool_reg__cmoveNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  {

#line 3424 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);

    MacroAssembler _masm(&cbuf);

    Label done;
    __ cmpdi(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x0));
    __ beq(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, done);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x1));
    __ bind(done);
  
#line 17245 "ad_ppc.cpp"
  }
}

uint convP2Bool_reg__cmoveNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void xorI_convP2Bool_reg_immIvalue1__cmoveNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  {

#line 3424 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);

    MacroAssembler _masm(&cbuf);

    Label done;
    __ cmpdi(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x1));
    __ beq(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, done);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x0));
    __ bind(done);
  
#line 17276 "ad_ppc.cpp"
  }
}

uint xorI_convP2Bool_reg_immIvalue1__cmoveNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void cmpLTMask_reg_immI0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 11007 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_srawi);
    __ srawi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 0x1f);
  
#line 17299 "ad_ppc.cpp"
  }
}

uint cmpLTMask_reg_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convB2I_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// amount
  {
    MacroAssembler _masm(&cbuf);

#line 11025 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_extsb);
    __ extsb(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17322 "ad_ppc.cpp"
  }
}

uint convB2I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void extshNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11036 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ extsh(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17343 "ad_ppc.cpp"
  }
}

uint extshNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convS2I_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// amount
  {
    MacroAssembler _masm(&cbuf);

#line 11047 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_extsh);
    __ extsh(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17366 "ad_ppc.cpp"
  }
}

uint convS2I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void sxtI_L2L_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11060 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_extsw);
    __ extsw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17388 "ad_ppc.cpp"
  }
}

uint sxtI_L2L_regNode::size(PhaseRegAlloc *ra_) const {
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

#line 11071 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_or);
    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17410 "ad_ppc.cpp"
  }
}

void convD2IRaw_regDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11085 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fctiwz);;
    __ fctiwz(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 17427 "ad_ppc.cpp"
  }
}

uint convD2IRaw_regDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmovI_bso_stackSlotLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3437 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(2)->disp(ra_,this,idx2) + frame_slots_bias(opnd_array(2)->base(ra_,this,idx2), ra_);
    Label done;
    __ bso(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(2)->base(ra_,this,idx2)));
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 17456 "ad_ppc.cpp"
  }
}

uint cmovI_bso_stackSlotLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT(InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT(InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8);
}

void cmovI_bso_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3449 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    Label done;
    __ bso(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ mffprd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src */);
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 17484 "ad_ppc.cpp"
  }
}

uint cmovI_bso_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT(InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT(InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 12 : 8);
}

void  cmovI_bso_stackSlotL_conLvalue0_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mem
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegIdst, 	dst
  unsigned idx_crx   = idx1; 	// flagsRegSrc, 	crx
  unsigned idx_mem   = idx2; 	// stackSlotL, 	mem
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_crx     = lookup(idx_crx);
  Node    *n_mem     = lookup(idx_mem);
  iRegIdstOper *op_dst = (iRegIdstOper *)opnd_array(0);
  flagsRegSrcOper *op_crx = (flagsRegSrcOper *)opnd_array(1);
  stackSlotLOper *op_mem = (stackSlotLOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 11126 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    //
    // replaces
    //
    //   region  dst  crx  mem
    //    \       |    |   /
    //     dst=cmovI_bso_stackSlotL_conLvalue0
    //
    // with
    //
    //   region  dst
    //    \       /
    //     dst=loadConI16(0)
    //      |
    //      ^  region  dst  crx  mem
    //      |   \       |    |    /
    //      dst=cmovI_bso_stackSlotL
    //

    // Create new nodes.
    MachNode *m1 = new loadConI16Node();
    MachNode *m2 = new cmovI_bso_stackSlotLNode();

    // inputs for new nodes
    m1->add_req(n_region);
    m2->add_req(n_region, n_crx, n_mem);

    // precedences for new nodes
    m2->add_prec(m1);

    // operands for new nodes
    m1->_opnds[0] = op_dst;
    m1->_opnds[1] = new immI16Oper(0);

    m2->_opnds[0] = op_dst;
    m2->_opnds[1] = op_crx;
    m2->_opnds[2] = op_mem;

    // registers for new nodes
    ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // dst
    ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // dst

    // Insert new nodes.
    nodes->push(m1);
    nodes->push(m2);
  
#line 17558 "ad_ppc.cpp"
  }
}

void  cmovI_bso_reg_conLvalue0_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegIdst, 	dst
  unsigned idx_crx   = idx1; 	// flagsRegSrc, 	crx
  unsigned idx_src   = idx2; 	// regD, 	src
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_crx     = lookup(idx_crx);
  Node    *n_src     = lookup(idx_src);
  iRegIdstOper *op_dst = (iRegIdstOper *)opnd_array(0);
  flagsRegSrcOper *op_crx = (flagsRegSrcOper *)opnd_array(1);
  regDOper *op_src = (regDOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 11180 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    //
    // replaces
    //
    //   region  dst  crx  src
    //    \       |    |   /
    //     dst=cmovI_bso_reg_conLvalue0
    //
    // with
    //
    //   region  dst
    //    \       /
    //     dst=loadConI16(0)
    //      |
    //      ^  region  dst  crx  src
    //      |   \       |    |    /
    //      dst=cmovI_bso_reg
    //

    // Create new nodes.
    MachNode *m1 = new loadConI16Node();
    MachNode *m2 = new cmovI_bso_regNode();

    // inputs for new nodes
    m1->add_req(n_region);
    m2->add_req(n_region, n_crx, n_src);

    // precedences for new nodes
    m2->add_prec(m1);

    // operands for new nodes
    m1->_opnds[0] = op_dst;
    m1->_opnds[1] = new immI16Oper(0);

    m2->_opnds[0] = op_dst;
    m2->_opnds[1] = op_crx;
    m2->_opnds[2] = op_src;

    // registers for new nodes
    ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // dst
    ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // dst

    // Insert new nodes.
    nodes->push(m1);
    nodes->push(m2);
  
#line 17627 "ad_ppc.cpp"
  }
}

void convF2IRaw_regFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11267 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fctiwz);
    __ fctiwz(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 17644 "ad_ppc.cpp"
  }
}

uint convF2IRaw_regFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convI2L_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11312 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_extsw);
    __ extsw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17666 "ad_ppc.cpp"
  }
}

uint convI2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void zeroExtendL_regINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {
    MacroAssembler _masm(&cbuf);

#line 11326 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 32);
  
#line 17689 "ad_ppc.cpp"
  }
}

uint zeroExtendL_regINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void zeroExtendL_regLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {
    MacroAssembler _masm(&cbuf);

#line 11340 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicl);
    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 32);
  
#line 17712 "ad_ppc.cpp"
  }
}

uint zeroExtendL_regLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convF2LRaw_regFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11354 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fctiwz);
    __ fctidz(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 17734 "ad_ppc.cpp"
  }
}

uint convF2LRaw_regFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmovL_bso_stackSlotLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3437 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(2)->disp(ra_,this,idx2) + frame_slots_bias(opnd_array(2)->base(ra_,this,idx2), ra_);
    Label done;
    __ bso(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(2)->base(ra_,this,idx2)));
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 17763 "ad_ppc.cpp"
  }
}

uint cmovL_bso_stackSlotLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8);
}

void cmovL_bso_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3449 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);

    MacroAssembler _masm(&cbuf);
    Label done;
    __ bso(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ mffprd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src */);
    // TODO PPC port __ endgroup_if_needed(_size == 12);
    __ bind(done);
  
#line 17791 "ad_ppc.cpp"
  }
}

uint cmovL_bso_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT Compile::current()->do_hb_scheduling()*/ ? 12 : 8);
}

void  cmovL_bso_stackSlotL_conLvalue0_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mem
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegLdst, 	dst
  unsigned idx_crx   = idx1; 	// flagsRegSrc, 	crx
  unsigned idx_mem   = idx2; 	// stackSlotL, 	mem
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_crx     = lookup(idx_crx);
  Node    *n_mem     = lookup(idx_mem);
  iRegLdstOper *op_dst = (iRegLdstOper *)opnd_array(0);
  flagsRegSrcOper *op_crx = (flagsRegSrcOper *)opnd_array(1);
  stackSlotLOper *op_mem = (stackSlotLOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 11395 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    //
    // replaces
    //
    //   region  dst  crx  mem
    //    \       |    |   /
    //     dst=cmovL_bso_stackSlotL_conLvalue0
    //
    // with
    //
    //   region  dst
    //    \       /
    //     dst=loadConL16(0)
    //      |
    //      ^  region  dst  crx  mem
    //      |   \       |    |    /
    //      dst=cmovL_bso_stackSlotL
    //

    // Create new nodes.
    MachNode *m1 = new loadConL16Node();
    MachNode *m2 = new cmovL_bso_stackSlotLNode();

    // inputs for new nodes
    m1->add_req(n_region);
    m2->add_req(n_region, n_crx, n_mem);
    m2->add_prec(m1);

    // operands for new nodes
    m1->_opnds[0] = op_dst;
    m1->_opnds[1] = new immL16Oper(0);
    m2->_opnds[0] = op_dst;
    m2->_opnds[1] = op_crx;
    m2->_opnds[2] = op_mem;

    // registers for new nodes
    ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // dst
    ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // dst

    // Insert new nodes.
    nodes->push(m1);
    nodes->push(m2);
  
#line 17862 "ad_ppc.cpp"
  }
}

void  cmovL_bso_reg_conLvalue0_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegLdst, 	dst
  unsigned idx_crx   = idx1; 	// flagsRegSrc, 	crx
  unsigned idx_src   = idx2; 	// regD, 	src
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_crx     = lookup(idx_crx);
  Node    *n_src     = lookup(idx_src);
  iRegLdstOper *op_dst = (iRegLdstOper *)opnd_array(0);
  flagsRegSrcOper *op_crx = (flagsRegSrcOper *)opnd_array(1);
  regDOper *op_src = (regDOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 11446 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    //
    // replaces
    //
    //   region  dst  crx  src
    //    \       |    |   /
    //     dst=cmovL_bso_reg_conLvalue0
    //
    // with
    //
    //   region  dst
    //    \       /
    //     dst=loadConL16(0)
    //      |
    //      ^  region  dst  crx  src
    //      |   \       |    |    /
    //      dst=cmovL_bso_reg
    //

    // Create new nodes.
    MachNode *m1 = new loadConL16Node();
    MachNode *m2 = new cmovL_bso_regNode();

    // inputs for new nodes
    m1->add_req(n_region);
    m2->add_req(n_region, n_crx, n_src);
    m2->add_prec(m1);

    // operands for new nodes
    m1->_opnds[0] = op_dst;
    m1->_opnds[1] = new immL16Oper(0);
    m2->_opnds[0] = op_dst;
    m2->_opnds[1] = op_crx;
    m2->_opnds[2] = op_src;

    // registers for new nodes
    ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // dst
    ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // dst

    // Insert new nodes.
    nodes->push(m1);
    nodes->push(m2);
  
#line 17928 "ad_ppc.cpp"
  }
}

void convD2LRaw_regDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11530 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fctiwz);
    __ fctidz(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 17945 "ad_ppc.cpp"
  }
}

uint convD2LRaw_regDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convL2DRaw_regDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11579 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fcfid);
    __ fcfid(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 17967 "ad_ppc.cpp"
  }
}

uint convL2DRaw_regDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convD2F_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11591 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_frsp);
    __ frsp(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 17989 "ad_ppc.cpp"
  }
}

uint convD2F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convL2FRaw_regFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11624 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fcfid);
    __ fcfids(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 18011 "ad_ppc.cpp"
  }
}

uint convL2FRaw_regFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void convF2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 11753 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fmr);
    __ fmr_if_needed(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 18033 "ad_ppc.cpp"
  }
}

void cmpI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 11768 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmp);
    __ cmpw(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18051 "ad_ppc.cpp"
  }
}

uint cmpI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpI_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 11779 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpi);
    __ cmpwi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 18074 "ad_ppc.cpp"
  }
}

uint cmpI_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void testI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 11792 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_andi_);
    __ andi_(R0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 18098 "ad_ppc.cpp"
  }
}

uint testI_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 11803 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmp);
    __ cmpd(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18121 "ad_ppc.cpp"
  }
}

uint cmpL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpL_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 11814 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpi);
    __ cmpdi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 18144 "ad_ppc.cpp"
  }
}

uint cmpL_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpUL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 11826 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpl);
    __ cmpld(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18167 "ad_ppc.cpp"
  }
}

uint cmpUL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpUL_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 11837 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpli);
    __ cmpldi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 18190 "ad_ppc.cpp"
  }
}

uint cmpUL_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void testL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 11849 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_and_);
    __ and_(R0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18214 "ad_ppc.cpp"
  }
}

uint testL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void testL_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 11861 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_andi_);
    __ andi_(R0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 18238 "ad_ppc.cpp"
  }
}

uint testL_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmovI_conIvalueMinus1_conIvalue1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  {
    MacroAssembler _masm(&cbuf);

#line 11878 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmove);
    Label done;
    // li(Rdst, 0);              // equal -> 0
    __ beq(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, 1);    // greater -> +1
    __ bgt(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, -1);   // unordered or less -> -1
    // TODO: PPC port__ endgroup_if_needed(_size == 20);
    __ bind(done);
  
#line 18267 "ad_ppc.cpp"
  }
}

uint cmovI_conIvalueMinus1_conIvalue1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORTInsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 20 : 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORTInsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 20 : 16);
}

void  cmovI_conIvalueMinus1_conIvalue0_conIvalue1_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegIdst, 	dst
  unsigned idx_crx   = idx1; 	// flagsRegSrc, 	crx
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_crx     = lookup(idx_crx);
  iRegIdstOper *op_dst = (iRegIdstOper *)opnd_array(0);
  flagsRegSrcOper *op_crx = (flagsRegSrcOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 11898 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    //
    // replaces
    //
    //   region  crx
    //    \       |
    //     dst=cmovI_conIvalueMinus1_conIvalue0_conIvalue1
    //
    // with
    //
    //   region
    //    \
    //     dst=loadConI16(0)
    //      |
    //      ^  region  crx
    //      |   \       |
    //      dst=cmovI_conIvalueMinus1_conIvalue1
    //

    // Create new nodes.
    MachNode *m1 = new loadConI16Node();
    MachNode *m2 = new cmovI_conIvalueMinus1_conIvalue1Node();

    // inputs for new nodes
    m1->add_req(n_region);
    m2->add_req(n_region, n_crx);
    m2->add_prec(m1);

    // operands for new nodes
    m1->_opnds[0] = op_dst;
    m1->_opnds[1] = new immI16Oper(0);
    m2->_opnds[0] = op_dst;
    m2->_opnds[1] = op_crx;

    // registers for new nodes
    ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // dst
    ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // dst

    // Insert new nodes.
    nodes->push(m1);
    nodes->push(m2);
  
#line 18333 "ad_ppc.cpp"
  }
}

void rangeCheck_iReg_uimm15Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src_length
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// index
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 11974 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_twi);
    if (opnd_array(1)->ccode()== 0x1 /* less_equal */) {
      __ trap_range_check_le(opnd_array(2)->as_Register(ra_,this,idx2)/* src_length */, opnd_array(3)->constant());
    } else {
      // Both successors are uncommon traps, probability is 0.
      // Node got flipped during fixup flow.
      assert(opnd_array(1)->ccode()== 0x9, "must be greater");
      __ trap_range_check_g(opnd_array(2)->as_Register(ra_,this,idx2)/* src_length */, opnd_array(3)->constant());
    }
  
#line 18360 "ad_ppc.cpp"
  }
}

uint rangeCheck_iReg_uimm15Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rangeCheck_iReg_iRegNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src_index
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src_length
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 12001 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_tw);
    if (opnd_array(1)->ccode()== 0x0 /* greater_equal */) {
      __ trap_range_check_ge(opnd_array(2)->as_Register(ra_,this,idx2)/* src_index */, opnd_array(3)->as_Register(ra_,this,idx3)/* src_length */);
    } else {
      // Both successors are uncommon traps, probability is 0.
      // Node got flipped during fixup flow.
      assert(opnd_array(1)->ccode()== 0x8, "must be less");
      __ trap_range_check_l(opnd_array(2)->as_Register(ra_,this,idx2)/* src_index */, opnd_array(3)->as_Register(ra_,this,idx3)/* src_length */);
    }
  
#line 18392 "ad_ppc.cpp"
  }
}

uint rangeCheck_iReg_iRegNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void rangeCheck_uimm15_iRegNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src_index
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// length
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 12028 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_twi);
    if (opnd_array(1)->ccode()== 0x0 /* greater_equal */) {
      __ trap_range_check_ge(opnd_array(2)->as_Register(ra_,this,idx2)/* src_index */, opnd_array(3)->constant());
    } else {
      // Both successors are uncommon traps, probability is 0.
      // Node got flipped during fixup flow.
      assert(opnd_array(1)->ccode()== 0x8, "must be less");
      __ trap_range_check_l(opnd_array(2)->as_Register(ra_,this,idx2)/* src_index */, opnd_array(3)->constant());
    }
  
#line 18424 "ad_ppc.cpp"
  }
}

uint rangeCheck_uimm15_iRegNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compU_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 12046 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpl);
    __ cmplw(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18447 "ad_ppc.cpp"
  }
}

uint compU_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void compU_reg_uimm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 12057 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpli);
    __ cmplwi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 18470 "ad_ppc.cpp"
  }
}

uint compU_reg_uimm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
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

#line 12079 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_tdi);
    if (opnd_array(1)->ccode()== 0xA) {
      __ trap_null_check(opnd_array(2)->as_Register(ra_,this,idx2)/* value */);
    } else {
      // Both successors are uncommon traps, probability is 0.
      // Node got flipped during fixup flow.
      assert(opnd_array(1)->ccode()== 0x2 , "must be equal(0xA) or notEqual(0x2)");
      __ trap_null_check(opnd_array(2)->as_Register(ra_,this,idx2)/* value */, Assembler::traptoGreaterThanUnsigned);
    }
  
#line 18502 "ad_ppc.cpp"
  }
}

uint zeroCheckN_iReg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpN_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 12100 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpl);
    __ cmplw(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18525 "ad_ppc.cpp"
  }
}

uint cmpN_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpN_reg_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 12114 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpli);
    __ cmplwi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 18548 "ad_ppc.cpp"
  }
}

uint cmpN_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void zeroCheckP_reg_imm0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// value
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 12136 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_tdi);
    if (opnd_array(1)->ccode()== 0xA) {
      __ trap_null_check(opnd_array(2)->as_Register(ra_,this,idx2)/* value */);
    } else {
      // Both successors are uncommon traps, probability is 0.
      // Node got flipped during fixup flow.
      assert(opnd_array(1)->ccode()== 0x2 , "must be equal(0xA) or notEqual(0x2)");
      __ trap_null_check(opnd_array(2)->as_Register(ra_,this,idx2)/* value */, Assembler::traptoGreaterThanUnsigned);
    }
  
#line 18580 "ad_ppc.cpp"
  }
}

uint zeroCheckP_reg_imm0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpP_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 12155 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpl);
    __ cmpld(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18603 "ad_ppc.cpp"
  }
}

uint cmpP_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpP_reg_nullNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 12166 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpl);
    __ cmpldi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (int)((short)(opnd_array(2)->constant()& 0xFFFF)));
  
#line 18626 "ad_ppc.cpp"
  }
}

uint cmpP_reg_nullNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpP_reg_imm16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 12183 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmpi);
    __ cmpdi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 18649 "ad_ppc.cpp"
  }
}

uint cmpP_reg_imm16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpFUnordered_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 12200 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fcmpu);
    __ fcmpu(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 18672 "ad_ppc.cpp"
  }
}

uint cmpFUnordered_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmov_bns_lessNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 12217 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cmovecr);
    Label done;
    __ bns(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, done);        // not unordered -> keep crx
    __ li(R0, 0);
    __ cmpwi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, R0, 1);     // unordered -> set crx to 'less'
    // TODO PPC port __ endgroup_if_needed(_size == 16);
    __ bind(done);
  
#line 18699 "ad_ppc.cpp"
  }
}

uint cmov_bns_lessNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= false /* TODO: PPC PORT(InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 16 : 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : false /* TODO: PPC PORT(InsertEndGroupPPC64 && Compile::current()->do_hb_scheduling())*/ ? 16 : 12);
}

void  cmpF_reg_reg_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  // Access to ins and operands for postalloc expand.
  unsigned idx_crx   = idx0; 	// flagsReg, 	crx
  unsigned idx_src1  = idx1; 	// regF, 	src1
  unsigned idx_src2  = idx2; 	// regF, 	src2
  Node    *n_region  = lookup(0);
  Node    *n_crx     = lookup(idx_crx);
  Node    *n_src1    = lookup(idx_src1);
  Node    *n_src2    = lookup(idx_src2);
  flagsRegOper *op_crx = (flagsRegOper *)opnd_array(0);
  regFOper *op_src1 = (regFOper *)opnd_array(1);
  regFOper *op_src2 = (regFOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 12246 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    //
    // replaces
    //
    //   region  src1  src2
    //    \       |     |
    //     crx=cmpF_reg_reg
    //
    // with
    //
    //   region  src1  src2
    //    \       |     |
    //     crx=cmpFUnordered_reg_reg
    //      |
    //      ^  region
    //      |   \
    //      crx=cmov_bns_less
    //

    // Create new nodes.
    MachNode *m1 = new cmpFUnordered_reg_regNode();
    MachNode *m2 = new cmov_bns_lessNode();

    // inputs for new nodes
    m1->add_req(n_region, n_src1, n_src2);
    m2->add_req(n_region);
    m2->add_prec(m1);

    // operands for new nodes
    m1->_opnds[0] = op_crx;
    m1->_opnds[1] = op_src1;
    m1->_opnds[2] = op_src2;
    m2->_opnds[0] = op_crx;

    // registers for new nodes
    ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // crx
    ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // crx

    // Insert new nodes.
    nodes->push(m1);
    nodes->push(m2);
  
#line 18769 "ad_ppc.cpp"
  }
}

void cmpDUnordered_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 12315 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fcmpu);
    __ fcmpu(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 18787 "ad_ppc.cpp"
  }
}

uint cmpDUnordered_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  cmpD_reg_reg_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  // Access to ins and operands for postalloc expand.
  unsigned idx_crx   = idx0; 	// flagsReg, 	crx
  unsigned idx_src1  = idx1; 	// regD, 	src1
  unsigned idx_src2  = idx2; 	// regD, 	src2
  Node    *n_region  = lookup(0);
  Node    *n_crx     = lookup(idx_crx);
  Node    *n_src1    = lookup(idx_src1);
  Node    *n_src2    = lookup(idx_src2);
  flagsRegOper *op_crx = (flagsRegOper *)opnd_array(0);
  regDOper *op_src1 = (regDOper *)opnd_array(1);
  regDOper *op_src2 = (regDOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 12327 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    //
    // replaces
    //
    //   region  src1  src2
    //    \       |     |
    //     crx=cmpD_reg_reg
    //
    // with
    //
    //   region  src1  src2
    //    \       |     |
    //     crx=cmpDUnordered_reg_reg
    //      |
    //      ^  region
    //      |   \
    //      crx=cmov_bns_less
    //

    // create new nodes
    MachNode *m1 = new cmpDUnordered_reg_regNode();
    MachNode *m2 = new cmov_bns_lessNode();

    // inputs for new nodes
    m1->add_req(n_region, n_src1, n_src2);
    m2->add_req(n_region);
    m2->add_prec(m1);

    // operands for new nodes
    m1->_opnds[0] = op_crx;
    m1->_opnds[1] = op_src1;
    m1->_opnds[2] = op_src2;
    m2->_opnds[0] = op_crx;

    // registers for new nodes
    ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // crx
    ra_->set_pair(m2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this)); // crx

    // Insert new nodes.
    nodes->push(m1);
    nodes->push(m2);
  
#line 18857 "ad_ppc.cpp"
  }
}

void branchNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 12394 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_b);
     Label d;    // dummy
     __ bind(d);
     Label* p = opnd_array(1)->label();
     // `p' is `NULL' when this encoding class is used only to
     // determine the size of the encoded instruction.
     Label& l = (NULL == p)? d : *(p);
     __ b(l);
  
#line 18880 "ad_ppc.cpp"
  }
}

uint branchNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void branchConNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 3460 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_bc);

    MacroAssembler _masm(&cbuf);
    Label d;   // dummy
    __ bind(d);
    Label* p = (opnd_array(3)->label());
    // `p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    Label& l = (NULL == p)? d : *(p);
    int cc = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    int bhint = Assembler::bhintNoHint;

    if (UseStaticBranchPredictionForUncommonPathsPPC64) {
      if (_prob <= PROB_NEVER) {
        bhint = Assembler::bhintIsNotTaken;
      } else if (_prob >= PROB_ALWAYS) {
        bhint = Assembler::bhintIsTaken;
      }
    }

    __ bc(Assembler::add_bhint_to_boint(bhint, cc_to_boint(cc)),
          cc_to_biint(cc, flags_reg),
          l);
  
#line 18926 "ad_ppc.cpp"
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
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 3488 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // The scheduler doesn't know about branch shortening, so we set the opcode
    // to ppc64Opcode_bc in order to hide this detail from the scheduler.
    // TODO: PPC port $archOpcode(ppc64Opcode_bc);

    MacroAssembler _masm(&cbuf);
    Label d;    // dummy
    __ bind(d);
    Label* p = (opnd_array(3)->label());
    // `p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    Label& l = (NULL == p)? d : *(p);
    int cc = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    int bhint = Assembler::bhintNoHint;

    if (UseStaticBranchPredictionForUncommonPathsPPC64) {
      if (_prob <= PROB_NEVER) {
        bhint = Assembler::bhintIsNotTaken;
      } else if (_prob >= PROB_ALWAYS) {
        bhint = Assembler::bhintIsTaken;
      }
    }

    // Tell the conditional far branch to optimize itself when being relocated.
    __ bc_far(Assembler::add_bhint_to_boint(bhint, cc_to_boint(cc)),
                  cc_to_biint(cc, flags_reg),
                  l,
                  MacroAssembler::bc_far_optimize_on_relocate);
  
#line 18975 "ad_ppc.cpp"
  }
}

uint branchConFarNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void branchConSchedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 3520 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // The scheduler doesn't know about branch shortening, so we set the opcode
    // to ppc64Opcode_bc in order to hide this detail from the scheduler.
    // TODO: PPC port $archOpcode(ppc64Opcode_bc);

    MacroAssembler _masm(&cbuf);
    Label d;   // dummy
    __ bind(d);
    Label* p = (opnd_array(3)->label());
    // `p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    Label& l = (NULL == p)? d : *(p);
    int cc = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    int bhint = Assembler::bhintNoHint;

    if (UseStaticBranchPredictionForUncommonPathsPPC64) {
      if (_prob <= PROB_NEVER) {
        bhint = Assembler::bhintIsNotTaken;
      } else if (_prob >= PROB_ALWAYS) {
        bhint = Assembler::bhintIsTaken;
      }
    }

#if 0 // TODO: PPC port
    if (_size == 8) {
      // Tell the conditional far branch to optimize itself when being relocated.
      __ bc_far(Assembler::add_bhint_to_boint(bhint, cc_to_boint(cc)),
                    cc_to_biint(cc, flags_reg),
                    l,
                    MacroAssembler::bc_far_optimize_on_relocate);
    } else {
      __ bc    (Assembler::add_bhint_to_boint(bhint, cc_to_boint(cc)),
                    cc_to_biint(cc, flags_reg),
                    l);
    }
#endif
    Unimplemented();
  
#line 19033 "ad_ppc.cpp"
  }
}

uint branchConSchedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void branchLoopEndNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 3460 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_bc);

    MacroAssembler _masm(&cbuf);
    Label d;   // dummy
    __ bind(d);
    Label* p = (opnd_array(3)->label());
    // `p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    Label& l = (NULL == p)? d : *(p);
    int cc = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    int bhint = Assembler::bhintNoHint;

    if (UseStaticBranchPredictionForUncommonPathsPPC64) {
      if (_prob <= PROB_NEVER) {
        bhint = Assembler::bhintIsNotTaken;
      } else if (_prob >= PROB_ALWAYS) {
        bhint = Assembler::bhintIsTaken;
      }
    }

    __ bc(Assembler::add_bhint_to_boint(bhint, cc_to_boint(cc)),
          cc_to_biint(cc, flags_reg),
          l);
  
#line 19079 "ad_ppc.cpp"
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
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 3488 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // The scheduler doesn't know about branch shortening, so we set the opcode
    // to ppc64Opcode_bc in order to hide this detail from the scheduler.
    // TODO: PPC port $archOpcode(ppc64Opcode_bc);

    MacroAssembler _masm(&cbuf);
    Label d;    // dummy
    __ bind(d);
    Label* p = (opnd_array(3)->label());
    // `p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    Label& l = (NULL == p)? d : *(p);
    int cc = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    int bhint = Assembler::bhintNoHint;

    if (UseStaticBranchPredictionForUncommonPathsPPC64) {
      if (_prob <= PROB_NEVER) {
        bhint = Assembler::bhintIsNotTaken;
      } else if (_prob >= PROB_ALWAYS) {
        bhint = Assembler::bhintIsTaken;
      }
    }

    // Tell the conditional far branch to optimize itself when being relocated.
    __ bc_far(Assembler::add_bhint_to_boint(bhint, cc_to_boint(cc)),
                  cc_to_biint(cc, flags_reg),
                  l,
                  MacroAssembler::bc_far_optimize_on_relocate);
  
#line 19128 "ad_ppc.cpp"
  }
}

uint branchLoopEndFarNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void branchLoopEndSchedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  {

#line 3520 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // The scheduler doesn't know about branch shortening, so we set the opcode
    // to ppc64Opcode_bc in order to hide this detail from the scheduler.
    // TODO: PPC port $archOpcode(ppc64Opcode_bc);

    MacroAssembler _masm(&cbuf);
    Label d;   // dummy
    __ bind(d);
    Label* p = (opnd_array(3)->label());
    // `p' is `NULL' when this encoding class is used only to
    // determine the size of the encoded instruction.
    Label& l = (NULL == p)? d : *(p);
    int cc = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    int bhint = Assembler::bhintNoHint;

    if (UseStaticBranchPredictionForUncommonPathsPPC64) {
      if (_prob <= PROB_NEVER) {
        bhint = Assembler::bhintIsNotTaken;
      } else if (_prob >= PROB_ALWAYS) {
        bhint = Assembler::bhintIsTaken;
      }
    }

#if 0 // TODO: PPC port
    if (_size == 8) {
      // Tell the conditional far branch to optimize itself when being relocated.
      __ bc_far(Assembler::add_bhint_to_boint(bhint, cc_to_boint(cc)),
                    cc_to_biint(cc, flags_reg),
                    l,
                    MacroAssembler::bc_far_optimize_on_relocate);
    } else {
      __ bc    (Assembler::add_bhint_to_boint(bhint, cc_to_boint(cc)),
                    cc_to_biint(cc, flags_reg),
                    l);
    }
#endif
    Unimplemented();
  
#line 19186 "ad_ppc.cpp"
  }
}

uint branchLoopEndSchedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void partialSubtypeCheckNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// subklass
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// superklass
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp_klass
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp_arrayptr
  {
    MacroAssembler _masm(&cbuf);

#line 12534 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ check_klass_subtype_slow_path(opnd_array(1)->as_Register(ra_,this,idx1)/* subklass */, opnd_array(2)->as_Register(ra_,this,idx2)/* superklass */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp_arrayptr */,
                                     opnd_array(4)->as_Register(ra_,this,idx4)/* tmp_klass */, NULL, opnd_array(3)->as_Register(ra_,this,idx3)/* result */);
  
#line 19213 "ad_ppc.cpp"
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

#line 12550 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ compiler_fast_lock_object(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */,
                                 opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */, /*tmp3*/ R0,
                                 UseBiasedLocking && !UseOptoBiasInlining);
    // If locking was successfull, crx should indicate 'EQ'.
    // The compiler generates a branch to the runtime call to
    // _complete_monitor_locking_Java for the case where crx is 'NE'.
  
#line 19238 "ad_ppc.cpp"
  }
}

void cmpFastLock_tmNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  {
    MacroAssembler _masm(&cbuf);

#line 12569 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ compiler_fast_lock_object(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */,
                                 opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp3 */,
                                 /*Biased Locking*/ false,
                                 _rtm_counters, _stack_rtm_counters,
                                 ((Method*)(ra_->C->method()->constant_encoding()))->method_data(),
                                 /*TM*/ true, ra_->C->profile_rtm());
    // If locking was successfull, crx should indicate 'EQ'.
    // The compiler generates a branch to the runtime call to
    // _complete_monitor_locking_Java for the case where crx is 'NE'.
  
#line 19267 "ad_ppc.cpp"
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
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  {
    MacroAssembler _masm(&cbuf);

#line 12590 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ compiler_fast_unlock_object(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */,
                                   opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp3 */,
                                   UseBiasedLocking && !UseOptoBiasInlining,
                                   false);
    // If unlocking was successfull, crx should indicate 'EQ'.
    // The compiler generates a branch to the runtime call to
    // _complete_monitor_unlocking_Java for the case where crx is 'NE'.
  
#line 19294 "ad_ppc.cpp"
  }
}

void cmpFastUnlock_tmNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  {
    MacroAssembler _masm(&cbuf);

#line 12609 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ compiler_fast_unlock_object(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */,
                                   opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp3 */,
                                   /*Biased Locking*/ false, /*TM*/ true);
    // If unlocking was successfull, crx should indicate 'EQ'.
    // The compiler generates a branch to the runtime call to
    // _complete_monitor_unlocking_Java for the case where crx is 'NE'.
  
#line 19320 "ad_ppc.cpp"
  }
}

void align_addrNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {
    MacroAssembler _masm(&cbuf);

#line 12627 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldicr);
    __ clrrdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, log2_long((jlong)-opnd_array(2)->constantL()));
  
#line 19338 "ad_ppc.cpp"
  }
}

uint align_addrNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void array_sizeNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// end
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// start
  {
    MacroAssembler _masm(&cbuf);

#line 12640 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_subf);
    __ subf(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* start */, opnd_array(1)->as_Register(ra_,this,idx1)/* end */);
  
#line 19361 "ad_ppc.cpp"
  }
}

uint array_sizeNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void inlineCallClearArrayShortNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {
    MacroAssembler _masm(&cbuf);

#line 12654 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ clear_memory_constlen(opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(1)->constantL(), R0); // kills base, R0
  
#line 19384 "ad_ppc.cpp"
  }
}

void inlineCallClearArrayLargeNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 12668 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ clear_memory_doubleword(opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */, R0, opnd_array(1)->constantL()); // kills base, R0
  
#line 19403 "ad_ppc.cpp"
  }
}

void inlineCallClearArrayNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {
    MacroAssembler _masm(&cbuf);

#line 12682 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ clear_memory_doubleword(opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(1)->as_Register(ra_,this,idx1)/* cnt */, R0); // kills cnt, base, R0
  
#line 19421 "ad_ppc.cpp"
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 12696 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::LL);
  
#line 19446 "ad_ppc.cpp"
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 12713 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::UU);
  
#line 19471 "ad_ppc.cpp"
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 12730 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::LU);
  
#line 19496 "ad_ppc.cpp"
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 12747 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ string_compare(opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */,
                      opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */, opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::UL);
  
#line 19521 "ad_ppc.cpp"
  }
}

void string_equalsLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 12764 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ array_equals(false, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* str2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* cnt */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */,
                    opnd_array(4)->as_Register(ra_,this,idx4)/* result */, true /* byte */);
  
#line 19544 "ad_ppc.cpp"
  }
}

void string_equalsUNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  {
    MacroAssembler _masm(&cbuf);

#line 12780 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ array_equals(false, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* str2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* cnt */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */,
                    opnd_array(4)->as_Register(ra_,this,idx4)/* result */, false /* byte */);
  
#line 19567 "ad_ppc.cpp"
  }
}

void array_equalsBNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 12796 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ array_equals(true, opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* ary2 */,
                    opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* result */, true /* byte */);
  
#line 19590 "ad_ppc.cpp"
  }
}

void array_equalsCNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 12812 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ array_equals(true, opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* ary2 */,
                    opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* result */, false /* byte */);
  
#line 19613 "ad_ppc.cpp"
  }
}

void indexOf_imm1_char_UNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needleImm
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// offsetImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// needlecntImm
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 12834 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    immPOper *needleOper = (immPOper *)opnd_array(3);
    const TypeOopPtr *t = needleOper->type()->isa_oopptr();
    ciTypeArray* needle_values = t->const_oop()->as_type_array();  // Pointer to live char *
    jchar chr;
#ifdef VM_LITTLE_ENDIAN
    chr = (((jchar)(unsigned char)needle_values->element_value(1).as_byte()) << 8) |
           ((jchar)(unsigned char)needle_values->element_value(0).as_byte());
#else
    chr = (((jchar)(unsigned char)needle_values->element_value(0).as_byte()) << 8) |
           ((jchar)(unsigned char)needle_values->element_value(1).as_byte());
#endif
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           R0, chr,
                           opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, false /*is_byte*/);
  
#line 19650 "ad_ppc.cpp"
  }
}

void indexOf_imm1_char_LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needleImm
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// offsetImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// needlecntImm
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 12868 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    immPOper *needleOper = (immPOper *)opnd_array(3);
    const TypeOopPtr *t = needleOper->type()->isa_oopptr();
    ciTypeArray* needle_values = t->const_oop()->as_type_array();  // Pointer to live char *
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           R0, chr,
                           opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, true /*is_byte*/);
  
#line 19680 "ad_ppc.cpp"
  }
}

void indexOf_imm1_char_ULNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needleImm
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// offsetImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// needlecntImm
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 12895 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    immPOper *needleOper = (immPOper *)opnd_array(3);
    const TypeOopPtr *t = needleOper->type()->isa_oopptr();
    ciTypeArray* needle_values = t->const_oop()->as_type_array();  // Pointer to live char *
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           R0, chr,
                           opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, false /*is_byte*/);
  
#line 19710 "ad_ppc.cpp"
  }
}

void indexOf_imm1_UNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 12923 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();
    guarantee(needle_values, "sanity");
    jchar chr;
#ifdef VM_LITTLE_ENDIAN
    chr = (((jchar)(unsigned char)needle_values->element_value(1).as_byte()) << 8) |
           ((jchar)(unsigned char)needle_values->element_value(0).as_byte());
#else
    chr = (((jchar)(unsigned char)needle_values->element_value(0).as_byte()) << 8) |
           ((jchar)(unsigned char)needle_values->element_value(1).as_byte());
#endif
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           R0, chr,
                           opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */, false /*is_byte*/);
  
#line 19746 "ad_ppc.cpp"
  }
}

void indexOf_imm1_LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 12958 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();
    guarantee(needle_values, "sanity");
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           R0, chr,
                           opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */, true /*is_byte*/);
  
#line 19775 "ad_ppc.cpp"
  }
}

void indexOf_imm1_ULNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 12986 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();
    guarantee(needle_values, "sanity");
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           R0, chr,
                           opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */, false /*is_byte*/);
  
#line 19804 "ad_ppc.cpp"
  }
}

void indexOfChar_UNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 13009 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           opnd_array(3)->as_Register(ra_,this,idx3)/* ch */, 0 /* this is not used if the character is already in a register */,
                           opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, false /*is_byte*/);
  
#line 19828 "ad_ppc.cpp"
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// tmp5
  {
    MacroAssembler _masm(&cbuf);

#line 13034 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, needle_values, opnd_array(10)->as_Register(ra_,this,idx10)/* tmp5 */, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::UU);
  
#line 19860 "ad_ppc.cpp"
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// tmp5
  {
    MacroAssembler _masm(&cbuf);

#line 13062 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, needle_values, opnd_array(10)->as_Register(ra_,this,idx10)/* tmp5 */, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::LL);
  
#line 19892 "ad_ppc.cpp"
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// tmp5
  {
    MacroAssembler _masm(&cbuf);

#line 13090 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, needle_values, opnd_array(10)->as_Register(ra_,this,idx10)/* tmp5 */, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::UL);
  
#line 19924 "ad_ppc.cpp"
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  {
    MacroAssembler _masm(&cbuf);

#line 13115 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, NULL, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,  // needlecnt not constant.
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::UU);
  
#line 19952 "ad_ppc.cpp"
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  {
    MacroAssembler _masm(&cbuf);

#line 13137 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, NULL, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,  // needlecnt not constant.
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::LL);
  
#line 19980 "ad_ppc.cpp"
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  {
    MacroAssembler _masm(&cbuf);

#line 13159 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, NULL, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,  // needlecnt not constant.
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::UL);
  
#line 20008 "ad_ppc.cpp"
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
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp4
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp5
  {
    MacroAssembler _masm(&cbuf);

#line 13177 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Label Lskip, Ldone;
    __ li(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, 0);
    __ string_compress_16(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                          opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp3 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp4 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp5 */, Ldone);
    __ rldicl_(opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, 0, 64-3); // Remaining characters.
    __ beq(CCR0, Lskip);
    __ string_compress(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */, Ldone);
    __ bind(Lskip);
    __ mr(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */);
    __ bind(Ldone);
  
#line 20042 "ad_ppc.cpp"
  }
}

void string_inflateNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp3
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp4
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp5
  {
    MacroAssembler _masm(&cbuf);

#line 13200 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Label Ldone;
    __ string_inflate_16(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */,
                         opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp3 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp4 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp5 */);
    __ rldicl_(opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, 0, 64-3); // Remaining characters.
    __ beq(CCR0, Ldone);
    __ string_inflate(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */);
    __ bind(Ldone);
  
#line 20072 "ad_ppc.cpp"
  }
}

void has_negativesNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// len
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  {
    MacroAssembler _masm(&cbuf);

#line 13221 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ has_negatives(opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* len */, opnd_array(3)->as_Register(ra_,this,idx3)/* result */,
                     opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */);
  
#line 20094 "ad_ppc.cpp"
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
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp4
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp5
  {
    MacroAssembler _masm(&cbuf);

#line 13237 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    Label Lslow, Lfailure1, Lfailure2, Ldone;
    __ string_compress_16(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */,
                          opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp3 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp4 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp5 */, Lfailure1);
    __ rldicl_(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, 0, 64-3); // Remaining characters.
    __ beq(CCR0, Ldone);
    __ bind(Lslow);
    __ string_compress(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */, Lfailure2);
    __ li(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, 0);
    __ b(Ldone);

    __ bind(Lfailure1);
    __ mr(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */);
    __ mfctr(opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */);
    __ rldimi_(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, 3, 0); // Remaining characters.
    __ beq(CCR0, Ldone);
    __ b(Lslow);

    __ bind(Lfailure2);
    __ mfctr(opnd_array(4)->as_Register(ra_,this,idx4)/* result */); // Remaining characters.

    __ bind(Ldone);
    __ subf(opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(4)->as_Register(ra_,this,idx4)/* result */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */);
  
#line 20140 "ad_ppc.cpp"
  }
}

void minI_reg_reg_iselNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 13294 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ cmpw(CCR0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ isel(opnd_array(0)->as_Register(ra_,this)/* dst */, CCR0, Assembler::less, /*invert*/false, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 20159 "ad_ppc.cpp"
  }
}

void maxI_reg_reg_iselNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    MacroAssembler _masm(&cbuf);

#line 13328 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ cmpw(CCR0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ isel(opnd_array(0)->as_Register(ra_,this)/* dst */, CCR0, Assembler::greater, /*invert*/false, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 20178 "ad_ppc.cpp"
  }
}

void popCountINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13346 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_popcntb);
    __ popcntw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20195 "ad_ppc.cpp"
  }
}

uint popCountINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void popCountLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13361 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_popcntb);
    __ popcntd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20217 "ad_ppc.cpp"
  }
}

uint popCountLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void countLeadingZerosINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13375 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cntlzw);
    __ cntlzw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20239 "ad_ppc.cpp"
  }
}

uint countLeadingZerosINode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void countLeadingZerosLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13389 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cntlzd);
    __ cntlzd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20261 "ad_ppc.cpp"
  }
}

uint countLeadingZerosLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void countLeadingZerosPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13403 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_cntlzd);
    __ cntlzd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20283 "ad_ppc.cpp"
  }
}

uint countLeadingZerosPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void insrwi_aNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pos
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  {
    MacroAssembler _masm(&cbuf);

#line 13454 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwimi);
    __ insrwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(3)->constant(), opnd_array(2)->constant());
  
#line 20307 "ad_ppc.cpp"
  }
}

uint insrwi_aNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void insrwiNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pos
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 13468 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rlwimi);
    __ insrwi(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(4)->constant(), opnd_array(3)->constant());
  
#line 20332 "ad_ppc.cpp"
  }
}

uint insrwiNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadI_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 13573 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ lwbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 20353 "ad_ppc.cpp"
  }
}

uint loadI_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadL_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 13586 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ ldbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 20374 "ad_ppc.cpp"
  }
}

uint loadL_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadUS_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 13598 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ lhbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 20395 "ad_ppc.cpp"
  }
}

uint loadUS_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadS_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    MacroAssembler _masm(&cbuf);

#line 13610 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ lhbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
    __ extsh(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */);
  
#line 20417 "ad_ppc.cpp"
  }
}

uint loadS_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void storeI_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13623 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ stwbrx(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 20439 "ad_ppc.cpp"
  }
}

uint storeI_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeL_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13636 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ stdbrx(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 20461 "ad_ppc.cpp"
  }
}

uint storeL_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeUS_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13648 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ sthbrx(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 20483 "ad_ppc.cpp"
  }
}

uint storeUS_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeS_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13660 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ sthbrx(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 20505 "ad_ppc.cpp"
  }
}

uint storeS_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mtvsrwzNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13670 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ mtvsrwz(opnd_array(0)->as_VectorSRegister(ra_,this)/* temp1 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20526 "ad_ppc.cpp"
  }
}

uint mtvsrwzNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xxspltwNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// imm1
  {
    MacroAssembler _masm(&cbuf);

#line 13680 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxspltw(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */, opnd_array(2)->constant());
  
#line 20548 "ad_ppc.cpp"
  }
}

uint xxspltwNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 13695 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldimi);
    __ insrdi(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 32, 0);
  
#line 20570 "ad_ppc.cpp"
  }
}

uint repl32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl48Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 13709 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldimi);
    __ insrdi(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 48, 0);
  
#line 20592 "ad_ppc.cpp"
  }
}

uint repl48Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl56Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 13723 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_rldimi);
    __ insrdi(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 56, 0);
  
#line 20614 "ad_ppc.cpp"
  }
}

uint repl56Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl8B_immI0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 13746 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 20636 "ad_ppc.cpp"
  }
}

uint repl8B_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl8B_immIminus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13758 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 20658 "ad_ppc.cpp"
  }
}

uint repl8B_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl16B_immI0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 13787 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 20679 "ad_ppc.cpp"
  }
}

uint repl16B_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl16B_immIminus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13799 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxleqv(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 20700 "ad_ppc.cpp"
  }
}

uint repl16B_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl4S_immI0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 13820 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 20722 "ad_ppc.cpp"
  }
}

uint repl4S_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl4S_immIminus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13832 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 20744 "ad_ppc.cpp"
  }
}

uint repl4S_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl8S_immI0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 13861 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 20765 "ad_ppc.cpp"
  }
}

uint repl8S_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl8S_immIminus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13873 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxleqv(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 20786 "ad_ppc.cpp"
  }
}

uint repl8S_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl2I_immI0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 13894 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 20808 "ad_ppc.cpp"
  }
}

uint repl2I_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl2I_immIminus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13906 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 20830 "ad_ppc.cpp"
  }
}

uint repl2I_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl4I_immI0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 13935 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 20851 "ad_ppc.cpp"
  }
}

uint repl4I_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl4I_immIminus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 13947 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxleqv(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 20872 "ad_ppc.cpp"
  }
}

uint repl4I_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  repl2F_immF_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// iRegLdst, 	dst
  unsigned idx_src   = idx1; 	// immF, 	src
  unsigned idx_toc   = mach_constant_base_node_input(); 	// iRegLdst, 	constanttablebase
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  Node    *n_toc     = lookup(idx_toc);
  iRegLdstOper *op_dst = (iRegLdstOper *)opnd_array(0);
  immFOper *op_src = (immFOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 3564 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // Create new nodes.

    // Make an operand with the bit pattern to load as float.
    immLOper *op_repl = new immLOper((jlong)replicate_immF(op_src->constantF()));

    loadConLNodesTuple loadConLNodes =
      loadConLNodesTuple_create(ra_, n_toc, op_repl,
                                ra_->get_reg_second(this), ra_->get_reg_first(this));

    // Push new nodes.
    if (loadConLNodes._large_hi) nodes->push(loadConLNodes._large_hi);
    if (loadConLNodes._last)     nodes->push(loadConLNodes._last);

    assert(nodes->length() >= 1, "must have created at least 1 node");
    assert(loadConLNodes._last->bottom_type()->isa_long(), "must be long");
  
#line 20915 "ad_ppc.cpp"
  }
}

void repl2F_immF_ExNode::eval_constant(Compile* C) {
  // User did not define an encode section.
}
void repl2F_immF0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 13984 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_addi);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, 0x0);
  
#line 20935 "ad_ppc.cpp"
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

#line 14002 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ li(R0, 0);
    __ mtxer(R0); // clear XER.SO
    __ addo_(R0, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 20955 "ad_ppc.cpp"
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

#line 14015 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ li(R0, 0);
    __ mtxer(R0); // clear XER.SO
    __ subfo_(R0, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
  
#line 20975 "ad_ppc.cpp"
  }
}

void overflowNegL_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 14028 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ li(R0, 0);
    __ mtxer(R0); // clear XER.SO
    __ nego_(R0, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 20995 "ad_ppc.cpp"
  }
}

void overflowMulL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    MacroAssembler _masm(&cbuf);

#line 14041 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ li(R0, 0);
    __ mtxer(R0); // clear XER.SO
    __ mulldo_(R0, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 21015 "ad_ppc.cpp"
  }
}

void  repl4F_immF_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  // Access to ins and operands for postalloc expand.
  unsigned idx_dst   = idx0; 	// vecX, 	dst
  unsigned idx_src   = idx1; 	// immF, 	src
  unsigned idx_toc   = mach_constant_base_node_input(); 	// iRegLdst, 	constanttablebase
  unsigned idx_tmp   = idx2; 	// iRegLdst, 	tmp
  Node    *n_region  = lookup(0);
  Node    *n_dst     = lookup(idx_dst);
  Node    *n_src     = lookup(idx_src);
  Node    *n_toc     = lookup(idx_toc);
  Node    *n_tmp     = lookup(idx_tmp);
  vecXOper *op_dst = (vecXOper *)opnd_array(0);
  immFOper *op_src = (immFOper *)opnd_array(1);
  iRegLdstOper *op_tmp = (iRegLdstOper *)opnd_array(2);
  Compile *C = ra_->C;
  {
#line 3582 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // Create new nodes.

    // Make an operand with the bit pattern to load as float.
    immLOper *op_repl = new  immLOper((jlong)replicate_immF(op_src->constantF()));
    immI_0Oper *op_zero = new  immI_0Oper(0);

    loadConLReplicatedNodesTuple loadConLNodes =
      loadConLReplicatedNodesTuple_create(C, ra_, n_toc, op_repl, op_dst, op_zero,
                                ra_->get_reg_second(n_tmp), ra_->get_reg_first(n_tmp),
                                ra_->get_reg_second(this), ra_->get_reg_first(this));

    // Push new nodes.
    if (loadConLNodes._large_hi) { nodes->push(loadConLNodes._large_hi); }
    if (loadConLNodes._large_lo) { nodes->push(loadConLNodes._large_lo); }
    if (loadConLNodes._moved)    { nodes->push(loadConLNodes._moved); }
    if (loadConLNodes._last)     { nodes->push(loadConLNodes._last); }

    assert(nodes->length() >= 1, "must have created at least 1 node");
  
#line 21060 "ad_ppc.cpp"
  }
}

void repl4F_immF_ExNode::eval_constant(Compile* C) {
  // User did not define an encode section.
}
void repl4F_immF0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 14085 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21079 "ad_ppc.cpp"
  }
}

void repl2D_immI0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 14113 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21095 "ad_ppc.cpp"
  }
}

uint repl2D_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl2D_immIminus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 14125 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxleqv(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21116 "ad_ppc.cpp"
  }
}

uint repl2D_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mtvsrdNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 14137 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ mtvsrd(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 21137 "ad_ppc.cpp"
  }
}

uint mtvsrdNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xxspltdNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 14148 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxpermdi(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */, opnd_array(2)->constant());
  
#line 21159 "ad_ppc.cpp"
  }
}

uint xxspltdNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xxpermdiNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 14159 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxpermdi(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */, opnd_array(3)->constant());
  
#line 21182 "ad_ppc.cpp"
  }
}

uint xxpermdiNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl2L_immI0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    MacroAssembler _masm(&cbuf);

#line 14182 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21203 "ad_ppc.cpp"
  }
}

uint repl2L_immI0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl2L_immIminus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    MacroAssembler _masm(&cbuf);

#line 14194 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    __ xxleqv(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21224 "ad_ppc.cpp"
  }
}

uint repl2L_immIminus1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void safePoint_pollNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {

#line 3605 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_ld);
    // Fake operand dst needed for PPC scheduler.
    assert((0x0) == 0x0, "dst must be 0x0");

    MacroAssembler _masm(&cbuf);
    // Mark the code position where the load from the safepoint
    // polling page was emitted as relocInfo::poll_type.
    __ relocate(relocInfo::poll_type);
    __ load_from_polling_page(opnd_array(1)->as_Register(ra_,this,idx1)/* poll */);
  
#line 21252 "ad_ppc.cpp"
  }
}

uint safePoint_pollNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void CallStaticJavaDirectNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 3663 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_bl);

    MacroAssembler _masm(&cbuf);
    address entry_point = (address)opnd_array(1)->method();

    if (!_method) {
      // A call to a runtime wrapper, e.g. new, new_typeArray_Java, uncommon_trap.
      emit_call_with_trampoline_stub(_masm, entry_point, relocInfo::runtime_call_type);
    } else {
      // Remember the offset not the address.
      const int start_offset = __ offset();

      // The trampoline stub.
      // No entry point given, use the current pc.
      // Make sure branch fits into
      if (entry_point == 0) entry_point = __ pc();

      // Put the entry point as a constant into the constant pool.
      const address entry_point_toc_addr = __ address_constant(entry_point, RelocationHolder::none);
      if (entry_point_toc_addr == NULL) {
        ciEnv::current()->record_out_of_memory_failure();
        return;
      }
      const int entry_point_toc_offset = __ offset_to_method_toc(entry_point_toc_addr);

      // Emit the trampoline stub which will be related to the branch-and-link below.
      CallStubImpl::emit_trampoline_stub(_masm, entry_point_toc_offset, start_offset);
      if (ciEnv::current()->failing()) { return; } // Code cache may be full.
      int method_index = resolved_method_index(cbuf);
      __ relocate(_optimized_virtual ? opt_virtual_call_Relocation::spec(method_index)
                  : static_call_Relocation::spec(method_index));

      // The real call.
      // Note: At this point we do not have the address of the trampoline
      // stub, and the entry point might be too far away for bl, so __ pc()
      // serves as dummy and the bl will be patched later.
      cbuf.set_insts_mark();
      __ bl(__ pc());  // Emits a relocation.

      // The stub for call to interpreter.
      address stub = CompiledStaticCall::emit_to_interp_stub(cbuf);
      if (stub == NULL) {
        ciEnv::current()->record_failure("CodeCache is full");
        return;
      }
    }
  
#line 21317 "ad_ppc.cpp"
  }
}

uint CallStaticJavaDirectNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void CallDynamicJavaDirectSchedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 3713 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_bl);

    MacroAssembler _masm(&cbuf);

    if (!ra_->C->in_scratch_emit_size()) {
      // Create a call trampoline stub for the given method.
      const address entry_point = !(opnd_array(1)->method()) ? 0 : (address)opnd_array(1)->method();
      const address entry_point_const = __ address_constant(entry_point, RelocationHolder::none);
      if (entry_point_const == NULL) {
        ciEnv::current()->record_out_of_memory_failure();
        return;
      }
      const int entry_point_const_toc_offset = __ offset_to_method_toc(entry_point_const);
      CallStubImpl::emit_trampoline_stub(_masm, entry_point_const_toc_offset, __ offset());
      if (ra_->C->env()->failing()) { return; } // Code cache may be full.

      // Build relocation at call site with ic position as data.
      assert((_load_ic_hi_node != NULL && _load_ic_node == NULL) ||
             (_load_ic_hi_node == NULL && _load_ic_node != NULL),
             "must have one, but can't have both");
      assert((_load_ic_hi_node != NULL && _load_ic_hi_node->_cbuf_insts_offset != -1) ||
             (_load_ic_node != NULL    && _load_ic_node->_cbuf_insts_offset != -1),
             "must contain instruction offset");
      const int virtual_call_oop_addr_offset = _load_ic_hi_node != NULL
        ? _load_ic_hi_node->_cbuf_insts_offset
        : _load_ic_node->_cbuf_insts_offset;
      const address virtual_call_oop_addr = __ addr_at(virtual_call_oop_addr_offset);
      assert(MacroAssembler::is_load_const_from_method_toc_at(virtual_call_oop_addr),
             "should be load from TOC");
      int method_index = resolved_method_index(cbuf);
      __ relocate(virtual_call_Relocation::spec(virtual_call_oop_addr, method_index));
    }

    // At this point I do not have the address of the trampoline stub,
    // and the entry point might be too far away for bl. Pc() serves
    // as dummy and bl will be patched later.
    __ bl((address) __ pc());
  
#line 21373 "ad_ppc.cpp"
  }
}

uint CallDynamicJavaDirectSchedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  CallDynamicJavaDirectSched_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // Access to ins and operands for postalloc expand.
  unsigned idx_meth  = idx1; 	// method, 	meth
  unsigned idx_toc   = mach_constant_base_node_input(); 	// iRegLdst, 	constanttablebase
  Node    *n_region  = lookup(0);
  Node    *n_meth    = lookup(idx_meth);
  Node    *n_toc     = lookup(idx_toc);
  methodOper *op_meth = (methodOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 3754 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"


    // Create the nodes for loading the IC from the TOC.
    loadConLNodesTuple loadConLNodes_IC =
      loadConLNodesTuple_create(ra_, n_toc, new immLOper((jlong)Universe::non_oop_word()),
                                OptoReg::Name(R19_H_num), OptoReg::Name(R19_num));

    // Create the call node.
    CallDynamicJavaDirectSchedNode *call = new CallDynamicJavaDirectSchedNode();
    call->_method_handle_invoke = _method_handle_invoke;
    call->_vtable_index      = _vtable_index;
    call->_method            = _method;
    call->_bci               = _bci;
    call->_optimized_virtual = _optimized_virtual;
    call->_tf                = _tf;
    call->_entry_point       = _entry_point;
    call->_cnt               = _cnt;
    call->_argsize           = _argsize;
    call->_oop_map           = _oop_map;
    call->_jvms              = _jvms;
    call->_jvmadj            = _jvmadj;
    call->_in_rms            = _in_rms;
    call->_nesting           = _nesting;
    call->_override_symbolic_info = _override_symbolic_info;

    // New call needs all inputs of old call.
    // Req...
    for (uint i = 0; i < req(); ++i) {
      // The expanded node does not need toc any more.
      // Add the inline cache constant here instead. This expresses the
      // register of the inline cache must be live at the call.
      // Else we would have to adapt JVMState by -1.
      if (i == mach_constant_base_node_input()) {
        call->add_req(loadConLNodes_IC._last);
      } else {
        call->add_req(in(i));
      }
    }
    // ...as well as prec
    for (uint i = req(); i < len(); ++i) {
      call->add_prec(in(i));
    }

    // Remember nodes loading the inline cache into r19.
    call->_load_ic_hi_node = loadConLNodes_IC._large_hi;
    call->_load_ic_node    = loadConLNodes_IC._small;

    // Operands for new nodes.
    call->_opnds[0] = _opnds[0];
    call->_opnds[1] = _opnds[1];

    // Only the inline cache is associated with a register.
    assert(Matcher::inline_cache_reg() == OptoReg::Name(R19_num), "ic reg should be R19");

    // Push new nodes.
    if (loadConLNodes_IC._large_hi) nodes->push(loadConLNodes_IC._large_hi);
    if (loadConLNodes_IC._last)     nodes->push(loadConLNodes_IC._last);
    nodes->push(call);
  
#line 21455 "ad_ppc.cpp"
  }
}

void CallDynamicJavaDirectNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 3817 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    MacroAssembler _masm(&cbuf);
    int start_offset = __ offset();

    Register Rtoc = (ra_) ? as_Register(ra_->get_encode(in(mach_constant_base_node_input()))) : R2_TOC;
#if 0
    int vtable_index = this->_vtable_index;
    if (_vtable_index < 0) {
      // Must be invalid_vtable_index, not nonvirtual_vtable_index.
      assert(_vtable_index == Method::invalid_vtable_index, "correct sentinel value");
      Register ic_reg = as_Register(Matcher::inline_cache_reg_encode());

      // Virtual call relocation will point to ic load.
      address virtual_call_meta_addr = __ pc();
      // Load a clear inline cache.
      AddressLiteral empty_ic((address) Universe::non_oop_word());
      bool success = __ load_const_from_method_toc(ic_reg, empty_ic, Rtoc, /*fixed_size*/ true);
      if (!success) {
        ciEnv::current()->record_out_of_memory_failure();
        return;
      }
      // CALL to fixup routine.  Fixup routine uses ScopeDesc info
      // to determine who we intended to call.
      __ relocate(virtual_call_Relocation::spec(virtual_call_meta_addr));
      emit_call_with_trampoline_stub(_masm, (address)opnd_array(1)->method(), relocInfo::none);
      assert(((MachCallDynamicJavaNode*)this)->ret_addr_offset() == __ offset() - start_offset,
             "Fix constant in ret_addr_offset()");
    } else {
      assert(!UseInlineCaches, "expect vtable calls only if not using ICs");
      // Go thru the vtable. Get receiver klass. Receiver already
      // checked for non-null. If we'll go thru a C2I adapter, the
      // interpreter expects method in R19_method.

      __ load_klass(R11_scratch1, R3);

      int entry_offset = in_bytes(Klass::vtable_start_offset()) + _vtable_index * vtableEntry::size_in_bytes();
      int v_off = entry_offset + vtableEntry::method_offset_in_bytes();
      __ li(R19_method, v_off);
      __ ldx(R19_method/*method oop*/, R19_method/*method offset*/, R11_scratch1/*class*/);
      // NOTE: for vtable dispatches, the vtable entry will never be
      // null. However it may very well end up in handle_wrong_method
      // if the method is abstract for the particular class.
      __ ld(R11_scratch1, in_bytes(Method::from_compiled_offset()), R19_method);
      // Call target. Either compiled code or C2I adapter.
      __ mtctr(R11_scratch1);
      __ bctrl();
      if (((MachCallDynamicJavaNode*)this)->ret_addr_offset() != __ offset() - start_offset) {
        tty->print(" %d, %d\n", ((MachCallDynamicJavaNode*)this)->ret_addr_offset(),__ offset() - start_offset);
      }
      assert(((MachCallDynamicJavaNode*)this)->ret_addr_offset() == __ offset() - start_offset,
             "Fix constant in ret_addr_offset()");
    }
#endif
    Unimplemented();  // ret_addr_offset not yet fixed. Depends on compressed oops (load klass!).
  
#line 21523 "ad_ppc.cpp"
  }
}

void CallRuntimeDirectNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 3875 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);

    MacroAssembler _masm(&cbuf);
    const address start_pc = __ pc();

#if defined(ABI_ELFv2)
    address entry= !(opnd_array(1)->method()) ? NULL : (address)opnd_array(1)->method();
    __ call_c(entry, relocInfo::runtime_call_type);
#else
    // The function we're going to call.
    FunctionDescriptor fdtemp;
    const FunctionDescriptor* fd = !(opnd_array(1)->method()) ? &fdtemp : (FunctionDescriptor*)opnd_array(1)->method();

    Register Rtoc = R12_scratch2;
    // Calculate the method's TOC.
    __ calculate_address_from_global_toc(Rtoc, __ method_toc());
    // Put entry, env, toc into the constant pool, this needs up to 3 constant
    // pool entries; call_c_using_toc will optimize the call.
    bool success = __ call_c_using_toc(fd, relocInfo::runtime_call_type, Rtoc);
    if (!success) {
      ciEnv::current()->record_out_of_memory_failure();
      return;
    }
#endif

    // Check the ret_addr_offset.
    assert(((MachCallRuntimeNode*)this)->ret_addr_offset() ==  __ last_calls_return_pc() - start_pc,
           "Fix constant in ret_addr_offset()");
  
#line 21565 "ad_ppc.cpp"
  }
}

void CallLeafDirect_mtctrNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 3909 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_mtctr);
    MacroAssembler _masm(&cbuf);
    __ mtctr(opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 21582 "ad_ppc.cpp"
  }
}

uint CallLeafDirect_mtctrNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void CallLeafDirectNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14330 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_bctrl);
    __ bctrl();
  
#line 21604 "ad_ppc.cpp"
  }
}

uint CallLeafDirectNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void  CallLeafDirect_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // Access to ins and operands for postalloc expand.
  unsigned idx_meth  = idx1; 	// method, 	meth
  unsigned idx_toc   = mach_constant_base_node_input(); 	// iRegLdst, 	constanttablebase
  Node    *n_region  = lookup(0);
  Node    *n_meth    = lookup(idx_meth);
  Node    *n_toc     = lookup(idx_toc);
  methodOper *op_meth = (methodOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 3916 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    loadConLNodesTuple loadConLNodes_Entry;
#if defined(ABI_ELFv2)
    jlong entry_address = (jlong) this->entry_point();
    assert(entry_address, "need address here");
    loadConLNodes_Entry = loadConLNodesTuple_create(ra_, n_toc, new immLOper(entry_address),
                                                    OptoReg::Name(R12_H_num), OptoReg::Name(R12_num));
#else
    // Get the struct that describes the function we are about to call.
    FunctionDescriptor* fd = (FunctionDescriptor*) this->entry_point();
    assert(fd, "need fd here");
    jlong entry_address = (jlong) fd->entry();
    // new nodes
    loadConLNodesTuple loadConLNodes_Env;
    loadConLNodesTuple loadConLNodes_Toc;

    // Create nodes and operands for loading the entry point.
    loadConLNodes_Entry = loadConLNodesTuple_create(ra_, n_toc, new immLOper(entry_address),
                                                    OptoReg::Name(R12_H_num), OptoReg::Name(R12_num));


    // Create nodes and operands for loading the env pointer.
    if (fd->env() != NULL) {
      loadConLNodes_Env = loadConLNodesTuple_create(ra_, n_toc, new immLOper((jlong) fd->env()),
                                                    OptoReg::Name(R11_H_num), OptoReg::Name(R11_num));
    } else {
      loadConLNodes_Env._large_hi = NULL;
      loadConLNodes_Env._large_lo = NULL;
      loadConLNodes_Env._small    = NULL;
      loadConLNodes_Env._last = new loadConL16Node();
      loadConLNodes_Env._last->_opnds[0] = new iRegLdstOper();
      loadConLNodes_Env._last->_opnds[1] = new immL16Oper(0);
      ra_->set_pair(loadConLNodes_Env._last->_idx, OptoReg::Name(R11_H_num), OptoReg::Name(R11_num));
    }

    // Create nodes and operands for loading the Toc point.
    loadConLNodes_Toc = loadConLNodesTuple_create(ra_, n_toc, new immLOper((jlong) fd->toc()),
                                                  OptoReg::Name(R2_H_num), OptoReg::Name(R2_num));
#endif // ABI_ELFv2
    // mtctr node
    MachNode *mtctr = new CallLeafDirect_mtctrNode();

    assert(loadConLNodes_Entry._last != NULL, "entry must exist");
    mtctr->add_req(0, loadConLNodes_Entry._last);

    mtctr->_opnds[0] = new iRegLdstOper();
    mtctr->_opnds[1] = new iRegLdstOper();

    // call node
    MachCallLeafNode *call = new CallLeafDirectNode();

    call->_opnds[0] = _opnds[0];
    call->_opnds[1] = new methodOper((intptr_t) entry_address); // May get set later.

    // Make the new call node look like the old one.
    call->_name        = _name;
    call->_tf          = _tf;
    call->_entry_point = _entry_point;
    call->_cnt         = _cnt;
    call->_argsize     = _argsize;
    call->_oop_map     = _oop_map;
    guarantee(!_jvms, "You must clone the jvms and adapt the offsets by fix_jvms().");
    call->_jvms        = NULL;
    call->_jvmadj      = _jvmadj;
    call->_in_rms      = _in_rms;
    call->_nesting     = _nesting;


    // New call needs all inputs of old call.
    // Req...
    for (uint i = 0; i < req(); ++i) {
      if (i != mach_constant_base_node_input()) {
        call->add_req(in(i));
      }
    }

    // These must be reqired edges, as the registers are live up to
    // the call. Else the constants are handled as kills.
    call->add_req(mtctr);
#if !defined(ABI_ELFv2)
    call->add_req(loadConLNodes_Env._last);
    call->add_req(loadConLNodes_Toc._last);
#endif

    // ...as well as prec
    for (uint i = req(); i < len(); ++i) {
      call->add_prec(in(i));
    }

    // registers
    ra_->set1(mtctr->_idx, OptoReg::Name(SR_CTR_num));

    // Insert the new nodes.
    if (loadConLNodes_Entry._large_hi) nodes->push(loadConLNodes_Entry._large_hi);
    if (loadConLNodes_Entry._last)     nodes->push(loadConLNodes_Entry._last);
#if !defined(ABI_ELFv2)
    if (loadConLNodes_Env._large_hi)   nodes->push(loadConLNodes_Env._large_hi);
    if (loadConLNodes_Env._last)       nodes->push(loadConLNodes_Env._last);
    if (loadConLNodes_Toc._large_hi)   nodes->push(loadConLNodes_Toc._large_hi);
    if (loadConLNodes_Toc._last)       nodes->push(loadConLNodes_Toc._last);
#endif
    nodes->push(mtctr);
    nodes->push(call);
  
#line 21731 "ad_ppc.cpp"
  }
}

void  CallLeafNoFPDirect_ExNode::postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_) {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  // Access to ins and operands for postalloc expand.
  unsigned idx_meth  = idx1; 	// method, 	meth
  unsigned idx_toc   = mach_constant_base_node_input(); 	// iRegLdst, 	constanttablebase
  Node    *n_region  = lookup(0);
  Node    *n_meth    = lookup(idx_meth);
  Node    *n_toc     = lookup(idx_toc);
  methodOper *op_meth = (methodOper *)opnd_array(1);
  Compile *C = ra_->C;
  {
#line 3916 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    loadConLNodesTuple loadConLNodes_Entry;
#if defined(ABI_ELFv2)
    jlong entry_address = (jlong) this->entry_point();
    assert(entry_address, "need address here");
    loadConLNodes_Entry = loadConLNodesTuple_create(ra_, n_toc, new immLOper(entry_address),
                                                    OptoReg::Name(R12_H_num), OptoReg::Name(R12_num));
#else
    // Get the struct that describes the function we are about to call.
    FunctionDescriptor* fd = (FunctionDescriptor*) this->entry_point();
    assert(fd, "need fd here");
    jlong entry_address = (jlong) fd->entry();
    // new nodes
    loadConLNodesTuple loadConLNodes_Env;
    loadConLNodesTuple loadConLNodes_Toc;

    // Create nodes and operands for loading the entry point.
    loadConLNodes_Entry = loadConLNodesTuple_create(ra_, n_toc, new immLOper(entry_address),
                                                    OptoReg::Name(R12_H_num), OptoReg::Name(R12_num));


    // Create nodes and operands for loading the env pointer.
    if (fd->env() != NULL) {
      loadConLNodes_Env = loadConLNodesTuple_create(ra_, n_toc, new immLOper((jlong) fd->env()),
                                                    OptoReg::Name(R11_H_num), OptoReg::Name(R11_num));
    } else {
      loadConLNodes_Env._large_hi = NULL;
      loadConLNodes_Env._large_lo = NULL;
      loadConLNodes_Env._small    = NULL;
      loadConLNodes_Env._last = new loadConL16Node();
      loadConLNodes_Env._last->_opnds[0] = new iRegLdstOper();
      loadConLNodes_Env._last->_opnds[1] = new immL16Oper(0);
      ra_->set_pair(loadConLNodes_Env._last->_idx, OptoReg::Name(R11_H_num), OptoReg::Name(R11_num));
    }

    // Create nodes and operands for loading the Toc point.
    loadConLNodes_Toc = loadConLNodesTuple_create(ra_, n_toc, new immLOper((jlong) fd->toc()),
                                                  OptoReg::Name(R2_H_num), OptoReg::Name(R2_num));
#endif // ABI_ELFv2
    // mtctr node
    MachNode *mtctr = new CallLeafDirect_mtctrNode();

    assert(loadConLNodes_Entry._last != NULL, "entry must exist");
    mtctr->add_req(0, loadConLNodes_Entry._last);

    mtctr->_opnds[0] = new iRegLdstOper();
    mtctr->_opnds[1] = new iRegLdstOper();

    // call node
    MachCallLeafNode *call = new CallLeafDirectNode();

    call->_opnds[0] = _opnds[0];
    call->_opnds[1] = new methodOper((intptr_t) entry_address); // May get set later.

    // Make the new call node look like the old one.
    call->_name        = _name;
    call->_tf          = _tf;
    call->_entry_point = _entry_point;
    call->_cnt         = _cnt;
    call->_argsize     = _argsize;
    call->_oop_map     = _oop_map;
    guarantee(!_jvms, "You must clone the jvms and adapt the offsets by fix_jvms().");
    call->_jvms        = NULL;
    call->_jvmadj      = _jvmadj;
    call->_in_rms      = _in_rms;
    call->_nesting     = _nesting;


    // New call needs all inputs of old call.
    // Req...
    for (uint i = 0; i < req(); ++i) {
      if (i != mach_constant_base_node_input()) {
        call->add_req(in(i));
      }
    }

    // These must be reqired edges, as the registers are live up to
    // the call. Else the constants are handled as kills.
    call->add_req(mtctr);
#if !defined(ABI_ELFv2)
    call->add_req(loadConLNodes_Env._last);
    call->add_req(loadConLNodes_Toc._last);
#endif

    // ...as well as prec
    for (uint i = req(); i < len(); ++i) {
      call->add_prec(in(i));
    }

    // registers
    ra_->set1(mtctr->_idx, OptoReg::Name(SR_CTR_num));

    // Insert the new nodes.
    if (loadConLNodes_Entry._large_hi) nodes->push(loadConLNodes_Entry._large_hi);
    if (loadConLNodes_Entry._last)     nodes->push(loadConLNodes_Entry._last);
#if !defined(ABI_ELFv2)
    if (loadConLNodes_Env._large_hi)   nodes->push(loadConLNodes_Env._large_hi);
    if (loadConLNodes_Env._last)       nodes->push(loadConLNodes_Env._last);
    if (loadConLNodes_Toc._large_hi)   nodes->push(loadConLNodes_Toc._large_hi);
    if (loadConLNodes_Toc._last)       nodes->push(loadConLNodes_Toc._last);
#endif
    nodes->push(mtctr);
    nodes->push(call);
  
#line 21853 "ad_ppc.cpp"
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

#line 14379 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ mtctr(opnd_array(1)->as_Register(ra_,this,idx1)/* jump_target */);
    __ bctr();
  
#line 21872 "ad_ppc.cpp"
  }
}

uint TailCalljmpIndNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void RetNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14392 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_blr);
    // LR is restored in MachEpilogNode. Just do the RET here.
    __ blr();
  
#line 21895 "ad_ppc.cpp"
  }
}

uint RetNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void tailjmpIndNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// ex_oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14414 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    __ ld(R4_ARG2/* issuing pc */, _abi(lr), R1_SP);
    __ mtctr(opnd_array(1)->as_Register(ra_,this,idx1)/* jump_target */);
    __ bctr();
  
#line 21920 "ad_ppc.cpp"
  }
}

uint tailjmpIndNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
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

#line 14443 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_compound);
    cbuf.set_insts_mark();
    __ b64_patchable((address)OptoRuntime::rethrow_stub(), relocInfo::runtime_call_type);
  
#line 21956 "ad_ppc.cpp"
  }
}

void ShouldNotReachHereNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14458 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_tdi);
    __ trap_should_not_reach_here();
  
#line 21973 "ad_ppc.cpp"
  }
}

uint ShouldNotReachHereNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
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

void endGroupNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14491 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_endgroup);
    __ endgroup();
  
#line 22008 "ad_ppc.cpp"
  }
}

uint endGroupNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void fxNopNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14507 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fmr);
    __ nop();
  
#line 22030 "ad_ppc.cpp"
  }
}

uint fxNopNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void fpNop0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14521 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fmr);
    __ fpnop0();
  
#line 22052 "ad_ppc.cpp"
  }
}

uint fpNop0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void fpNop1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14535 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_fmr);
    __ fpnop1();
  
#line 22074 "ad_ppc.cpp"
  }
}

uint fpNop1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void brNop0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14546 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_mcrf);
    __ brnop0();
  
#line 22096 "ad_ppc.cpp"
  }
}

uint brNop0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void brNop1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14561 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_mcrf);
    __ brnop1();
  
#line 22118 "ad_ppc.cpp"
  }
}

uint brNop1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void brNop2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    MacroAssembler _masm(&cbuf);

#line 14575 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // TODO: PPC port $archOpcode(ppc64Opcode_mcrf);
    __ brnop2();
  
#line 22140 "ad_ppc.cpp"
  }
}

uint brNop2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

const MachOper* loadUB_indirectNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUB_indirect_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadB_indirect_ExNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadB_indirect_ac_ExNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUB_indOffset16Node::memory_operand() const { return _opnds[1]; }
const MachOper* loadUB_indOffset16_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadB_indOffset16_ExNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadB_indOffset16_ac_ExNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUBNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUB_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUB2LNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUB2L_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadSNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadS_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUSNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUS_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUS2LNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUS2L_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadINode::memory_operand() const { return _opnds[1]; }
const MachOper* loadI_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUI2LNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadI2LNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadI2L_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadLNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadL_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadL_unalignedNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadV8Node::memory_operand() const { return _opnds[1]; }
const MachOper* loadV16Node::memory_operand() const { return _opnds[1]; }
const MachOper* loadRangeNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadNNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadN_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadN2P_unscaledNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadN2P_klass_unscaledNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadPNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadP_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadP2XNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadNKlassNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadKlassNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadFNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadF_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadDNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadD_acNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadD_unalignedNode::memory_operand() const { return _opnds[1]; }
const MachOper* prefetch_alloc_zeroNode::memory_operand() const { return _opnds[1]; }
const MachOper* prefetch_alloc_zero_no_offsetNode::memory_operand() const { return _opnds[1]; }
const MachOper* prefetch_allocNode::memory_operand() const { return _opnds[1]; }
const MachOper* prefetch_alloc_no_offsetNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeBNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeCNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeINode::memory_operand() const { return _opnds[1]; }
const MachOper* storeI_convL2INode::memory_operand() const { return _opnds[1]; }
const MachOper* storeLNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeA8BNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeV16Node::memory_operand() const { return _opnds[1]; }
const MachOper* storeNNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeNKlassNode::memory_operand() const { return _opnds[1]; }
const MachOper* storePNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeFNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeDNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeCM_CMSNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeCM_CMS_ExExNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeCM_G1Node::memory_operand() const { return _opnds[1]; }
const TypePtr *membar_acquireNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_acquireNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *unnecessary_membar_acquireNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* unnecessary_membar_acquireNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_acquire_lockNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_acquire_lockNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_releaseNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_releaseNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_release_0Node::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_release_0Node::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_storestoreNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_storestoreNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_release_lockNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_release_lockNode::memory_operand() const { return (MachOper*)-1; }
const TypePtr *membar_volatileNode::adr_type() const { return TypePtr::BOTTOM; }
const MachOper* membar_volatileNode::memory_operand() const { return (MachOper*)-1; }
const MachOper* storeLConditional_regP_regL_regLNode::memory_operand() const { return _opnds[1]; }
const MachOper* storePConditional_regP_regP_regPNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadPLockedNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadI_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadL_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUS_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadS_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeI_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeL_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeUS_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeS_reversedNode::memory_operand() const { return _opnds[1]; }


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
    true ,  // ReverseBytesUS
    true ,  // ReverseBytesS
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
    true ,  // CompareAndSwapB
    true ,  // CompareAndSwapS
    true ,  // CompareAndSwapI
    true ,  // CompareAndSwapL
    true ,  // CompareAndSwapP
    true ,  // CompareAndSwapN
    true ,  // WeakCompareAndSwapB
    true ,  // WeakCompareAndSwapS
    true ,  // WeakCompareAndSwapI
    true ,  // WeakCompareAndSwapL
    true ,  // WeakCompareAndSwapP
    true ,  // WeakCompareAndSwapN
    true ,  // CompareAndExchangeB
    true ,  // CompareAndExchangeS
    true ,  // CompareAndExchangeI
    true ,  // CompareAndExchangeL
    true ,  // CompareAndExchangeP
    true ,  // CompareAndExchangeN
    true ,  // GetAndAddB
    true ,  // GetAndAddS
    true ,  // GetAndAddI
    true ,  // GetAndAddL
    true ,  // GetAndSetB
    true ,  // GetAndSetS
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
    false,  // DivModI
    false,  // DivModL
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
    false,  // OverflowAddI
    false,  // OverflowSubI
    false,  // OverflowMulI
    true ,  // OverflowAddL
    true ,  // OverflowSubL
    true ,  // OverflowMulL
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
    true ,  // ReplicateL
    true ,  // ReplicateF
    true ,  // ReplicateD
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

int Compile::sync_stack_slots() const { return (frame::jit_monitor_size / VMRegImpl::stack_slot_size); }

uint Matcher::stack_alignment_in_bytes() { return frame::alignment_in_bytes; }

OptoReg::Name Matcher::return_addr() const { return OptoReg::stack2reg(4); }

uint Compile::in_preserve_stack_slots() { return (frame::jit_in_preserve_size / VMRegImpl::stack_slot_size); }

uint Compile::out_preserve_stack_slots() { return SharedRuntime::out_preserve_stack_slots(); }

uint Compile::varargs_C_out_slots_killed() const { return ((frame::abi_reg_args_size - frame::jit_out_preserve_size) / VMRegImpl::stack_slot_size); }

void Matcher::calling_convention(BasicType *sig_bt, VMRegPair *regs, uint length, bool is_outgoing) {

#line 4099 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // No difference between ingoing/outgoing. Just pass false.
    SharedRuntime::java_calling_convention(sig_bt, regs, length, false);
  
#line 22632 "ad_ppc.cpp"

}

void Matcher::c_calling_convention(BasicType *sig_bt, VMRegPair *regs, uint length) {

#line 4111 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    // This is obviously always outgoing.
    // C argument in register AND stack slot.
    (void) SharedRuntime::c_calling_convention(sig_bt, regs, /*regs2=*/NULL, length);
  
#line 22644 "ad_ppc.cpp"

}

OptoRegPair Matcher::return_value(uint ideal_reg, bool is_outgoing) {

#line 4134 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    assert((ideal_reg >= Op_RegI && ideal_reg <= Op_RegL) ||
            (ideal_reg == Op_RegN && Universe::narrow_oop_base() == NULL && Universe::narrow_oop_shift() == 0),
            "only return normal values");
    // enum names from opcodes.hpp:    Op_Node Op_Set Op_RegN       Op_RegI       Op_RegP       Op_RegF       Op_RegD       Op_RegL
    static int typeToRegLo[Op_RegL+1] = { 0,   0,     R3_num,   R3_num,   R3_num,   F1_num,   F1_num,   R3_num };
    static int typeToRegHi[Op_RegL+1] = { 0,   0,     OptoReg::Bad, R3_H_num, R3_H_num, OptoReg::Bad, F1_H_num, R3_H_num };
    return OptoRegPair(typeToRegHi[ideal_reg], typeToRegLo[ideal_reg]);
  
#line 22660 "ad_ppc.cpp"

}

OptoRegPair Matcher::c_return_value(uint ideal_reg, bool is_outgoing) {

#line 4123 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

    assert((ideal_reg >= Op_RegI && ideal_reg <= Op_RegL) ||
            (ideal_reg == Op_RegN && Universe::narrow_oop_base() == NULL && Universe::narrow_oop_shift() == 0),
            "only return normal values");
    // enum names from opcodes.hpp:    Op_Node Op_Set Op_RegN       Op_RegI       Op_RegP       Op_RegF       Op_RegD       Op_RegL
    static int typeToRegLo[Op_RegL+1] = { 0,   0,     R3_num,   R3_num,   R3_num,   F1_num,   F1_num,   R3_num };
    static int typeToRegHi[Op_RegL+1] = { 0,   0,     OptoReg::Bad, R3_H_num, R3_H_num, OptoReg::Bad, F1_H_num, R3_H_num };
    return OptoRegPair(typeToRegHi[ideal_reg], typeToRegLo[ideal_reg]);
  
#line 22676 "ad_ppc.cpp"

}

OptoReg::Name Matcher::inline_cache_reg() { return OptoReg::Name(R19_num); }

int Matcher::inline_cache_reg_encode() { return _regEncode[inline_cache_reg()]; }

OptoReg::Name Matcher::interpreter_method_oop_reg() { return OptoReg::Name(R19_num); }

int Matcher::interpreter_method_oop_reg_encode() { return _regEncode[interpreter_method_oop_reg()]; }

OptoReg::Name Matcher::interpreter_frame_pointer_reg() { return OptoReg::Name(R14_num); }

OptoReg::Name Matcher::c_frame_pointer() const { return OptoReg::Name(R1_num); }

// Number of callee-save + always-save registers
int  Matcher::number_of_saved_registers() {
  return 0;
};

bool Compile::needs_clone_jvms() { return true; }

// Check consistency of C++ compilation with ADLC options:
// Check adlc -DLINUX=1
#ifndef LINUX
#  error "LINUX must be defined"
#endif // LINUX
// Check adlc -D_GNU_SOURCE=1
#ifndef _GNU_SOURCE
#  error "_GNU_SOURCE must be defined"
#endif // _GNU_SOURCE
// Check adlc -DPPC64=1
#ifndef PPC64
#  error "PPC64 must be defined"
#endif // PPC64
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
