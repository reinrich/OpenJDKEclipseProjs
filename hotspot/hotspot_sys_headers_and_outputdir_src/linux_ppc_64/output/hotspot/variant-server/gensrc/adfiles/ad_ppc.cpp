#line 1 "ad_ppc.cpp"
//
// Copyright (c) 2011, 2023, Oracle and/or its affiliates. All rights reserved.
// Copyright (c) 2012, 2022 SAP SE. All rights reserved.
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
#include "code/codeCache.hpp"
#include "code/compiledIC.hpp"
#include "code/nativeInst.hpp"
#include "code/vmreg.inline.hpp"
#include "gc/shared/collectedHeap.inline.hpp"
#include "oops/compiledICHolder.hpp"
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

#line 983 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


#include "opto/c2_CodeStubs.hpp"
#include "oops/klass.inline.hpp"

void PhaseOutput::pd_perform_mach_node_analysis() {
}

int MachNode::pd_alignment_required() const {
  return 1;
}

int MachNode::compute_padding(int current_offset) const {
  return 0;
}

// Should the matcher clone input 'm' of node 'n'?
bool Matcher::pd_clone_node(Node* n, Node* m, Matcher::MStack& mstack) {
  return false;
}

// Should the Matcher clone shifts on addressing modes, expecting them
// to be subsumed into complex addressing expressions or compute them
// into registers?
bool Matcher::pd_clone_address_expressions(AddPNode* m, Matcher::MStack& mstack, VectorSet& address_visited) {
  return clone_base_plus_offset_address(m, mstack, address_visited);
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
  if (UseInlineCaches) return 4;

  int vtable_index = this->_vtable_index;
  if (vtable_index < 0) {
    // Must be invalid_vtable_index, not nonvirtual_vtable_index.
    assert(vtable_index == Method::invalid_vtable_index, "correct sentinel value");
    return 12;
  } else {
    return 24 + MacroAssembler::instr_size_for_decode_klass_not_null();
  }
}

int MachCallRuntimeNode::ret_addr_offset() {
  if (rule() == CallRuntimeDirect_rule) {
    // CallRuntimeDirectNode uses call_c.
#if defined(ABI_ELFv2)
    return 28;
#else
    return 40;
#endif
  }
  assert(rule() == CallLeafDirect_rule, "unexpected node with rule %u", rule());
  // CallLeafDirectNode uses bl.
  return 4;
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

// Add nop if a prefixed (two-word) instruction is going to cross a 64-byte boundary.
// (See Section 1.6 of Power ISA Version 3.1)
static int compute_prefix_padding(int current_offset) {
  assert(PowerArchitecturePPC64 >= 10 && (CodeEntryAlignment & 63) == 0,
         "Code buffer must be aligned to a multiple of 64 bytes");
  if (is_aligned(current_offset + BytesPerInstWord, 64)) {
    return BytesPerInstWord;
  }
  return 0;
}

int loadConI32Node::compute_padding(int current_offset) const {
  return compute_prefix_padding(current_offset);
}

int loadConL34Node::compute_padding(int current_offset) const {
  return compute_prefix_padding(current_offset);
}

int addI_reg_imm32Node::compute_padding(int current_offset) const {
  return compute_prefix_padding(current_offset);
}

int addL_reg_imm34Node::compute_padding(int current_offset) const {
  return compute_prefix_padding(current_offset);
}

int addP_reg_imm34Node::compute_padding(int current_offset) const {
  return compute_prefix_padding(current_offset);
}

int cmprb_Whitespace_reg_reg_prefixedNode::compute_padding(int current_offset) const {
  return compute_prefix_padding(current_offset);
}


//=============================================================================

// Emit an interrupt that is caught by the debugger (for debugging compiler).
void emit_break(CodeBuffer &cbuf) {
  C2_MacroAssembler _masm(&cbuf);
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
  C2_MacroAssembler _masm(&cbuf);
  __ nop();
}

static inline void emit_long(CodeBuffer &cbuf, int value) {
  *((int*)(cbuf.insts_end())) = value;
  cbuf.set_insts_end(cbuf.insts_end() + BytesPerInstWord);
}

//=============================================================================


#line 303 "ad_ppc.cpp"


//SourceForm

#line 1258 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


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

void CallStubImpl::emit_trampoline_stub(C2_MacroAssembler &_masm, int destination_toc_offset, int insts_call_instruction_offset) {
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
EmitCallOffsets emit_call_with_trampoline_stub(C2_MacroAssembler &_masm, address entry_point, relocInfo::relocType rtype) {
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
int ConstantTable::calculate_table_base_offset() const {
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
  const long framesize = C->output()->frame_slots() << LogBytesPerInt;

  st->print("PROLOG\n\t");
  if (C->output()->need_stack_bang(framesize)) {
    st->print("stack_overflow_check\n\t");
  }

  if (!false /* TODO: PPC port C->is_frameless_method()*/) {
    st->print("save return pc\n\t");
    st->print("push frame %ld\n\t", -framesize);
  }

  if (C->stub_function() == NULL) {
    st->print("nmethod entry barrier\n\t");
  }
}
#endif

void MachPrologNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  Compile* C = ra_->C;
  C2_MacroAssembler _masm(&cbuf);

  const long framesize = C->output()->frame_size_in_bytes();
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
    __ nop();
  } else {
    // Get return pc.
    __ mflr(return_pc);
  }

  if (C->clinit_barrier_on_entry()) {
    assert(!C->method()->holder()->is_not_initialized(), "initialization should have been started");

    Label L_skip_barrier;
    Register klass = toc_temp;

    // Notify OOP recorder (don't need the relocation)
    AddressLiteral md = __ constant_metadata_address(C->method()->holder()->constant_encoding());
    __ load_const_optimized(klass, md.value(), R0);
    __ clinit_barrier(klass, R16_thread, &L_skip_barrier /*L_fast_path*/);

    __ load_const_optimized(klass, SharedRuntime::get_handle_wrong_method_stub(), R0);
    __ mtctr(klass);
    __ bctr();

    __ bind(L_skip_barrier);
  }

  // Calls to C2R adapters often do not accept exceptional returns.
  // We require that their callers must bang for them. But be
  // careful, because some VM calls (such as call site linkage) can
  // use several kilobytes of stack. But the stack safety zone should
  // account for that. See bugs 4446381, 4468289, 4497237.

  int bangsize = C->output()->bang_size_in_bytes();
  assert(bangsize >= framesize || bangsize <= 0, "stack bang size incorrect");
  if (C->output()->need_stack_bang(bangsize)) {
    // Unfortunately we cannot use the function provided in
    // assembler.cpp as we have to emulate the pipes. So I had to
    // insert the code of generate_stack_overflow_check(), see
    // assembler.cpp for some illuminative comments.
    const int page_size = os::vm_page_size();
    int bang_end = StackOverflow::stack_shadow_zone_size();

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
          __ ld(R0,  (int)(signed short)stdoffset, R1_SP);
        } else {
          __ std(R0, (int)(signed short)stdoffset, R1_SP);
        }
      } else if (Assembler::is_simm(stdoffset, 31)) {
        // Use largeoffset calculations for addis & ld/std.
        const int hi = MacroAssembler::largeoffset_si16_si16_hi(stdoffset);
        const int lo = MacroAssembler::largeoffset_si16_si16_lo(stdoffset);

        Register tmp = R11;
        __ addis(tmp, R1_SP, hi);
        if (UseLoadInstructionsForStackBangingPPC64) {
          __ ld(R0, lo, tmp);
        } else {
          __ std(R0, lo, tmp);
        }
      } else {
        ShouldNotReachHere();
      }

      bang_offset += page_size;
    }
    // R11 trashed
  } // C->output()->need_stack_bang(framesize)

  unsigned int bytes = (unsigned int)framesize;
  long offset = Assembler::align_addr(bytes, frame::alignment_in_bytes);
  ciMethod *currMethod = C->method();

  if (!method_is_frameless) {
    // Get callers sp.
    __ mr(callers_sp, R1_SP);

    // Push method's frame, modifies SP.
    assert(Assembler::is_uimm(framesize, 32U), "wrong type");
    // The ABI is already accounted for in 'framesize' via the
    // 'out_preserve' area.
    Register tmp = push_frame_temp;
    // Had to insert code of push_frame((unsigned int)framesize, push_frame_temp).
    if (Assembler::is_simm(-offset, 16)) {
      __ stdu(R1_SP, -offset, R1_SP);
    } else {
      long x = -offset;
      // Had to insert load_const(tmp, -offset).
      __ lis( tmp, (int)((signed short)(((x >> 32) & 0xffff0000) >> 16)));
      __ ori( tmp, tmp, ((x >> 32) & 0x0000ffff));
      __ sldi(tmp, tmp, 32);
      __ oris(tmp, tmp, (x & 0xffff0000) >> 16);
      __ ori( tmp, tmp, (x & 0x0000ffff));

      __ stdux(R1_SP, R1_SP, tmp);
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
    __ std(return_pc, _abi0(lr), callers_sp);
  }

  if (C->stub_function() == NULL) {
    BarrierSetAssembler* bs = BarrierSet::barrier_set()->barrier_set_assembler();
    bs->nmethod_entry_barrier(&_masm, push_frame_temp);
  }

  C->output()->set_frame_complete(cbuf.insts_size());
}

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
    st->print("safepoint poll\n\t");
  }
}
#endif

void MachEpilogNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  Compile* C = ra_->C;
  C2_MacroAssembler _masm(&cbuf);

  const long framesize = ((long)C->output()->frame_slots()) << LogBytesPerInt;
  assert(framesize >= 0, "negative frame-size?");

  const bool method_needs_polling = do_polling() && C->is_method_compilation();
  const bool method_is_frameless  = false /* TODO: PPC port C->is_frameless_method()*/;
  const Register return_pc        = R31;  // Must survive C-call to enable_stack_reserved_zone().
  const Register temp             = R12;

  if (!method_is_frameless) {
    // Restore return pc relative to callers' sp.
    __ ld(return_pc, ((int)framesize) + _abi0(lr), R1_SP);
    // Move return pc to LR.
    __ mtlr(return_pc);
    // Pop frame (fixed frame-size).
    __ addi(R1_SP, R1_SP, (int)framesize);
  }

  if (StackReservedPages > 0 && C->has_reserved_stack_access()) {
    __ reserved_stack_check(return_pc);
  }

  if (method_needs_polling) {
    Label dummy_label;
    Label* code_stub = &dummy_label;
    if (!UseSIGTRAP && !C->output()->in_scratch_emit_size()) {
      C2SafepointPollStub* stub = new (C->comp_arena()) C2SafepointPollStub(__ offset());
      C->output()->add_stub(stub);
      code_stub = &stub->entry();
      __ relocate(relocInfo::poll_return_type);
    }
    __ safepoint_poll(*code_stub, temp, true /* at_return */, true /* in_nmethod */);
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
        C2_MacroAssembler _masm(cbuf);
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
        C2_MacroAssembler _masm(cbuf);
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
        C2_MacroAssembler _masm(cbuf);
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
        C2_MacroAssembler _masm(cbuf);
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
        C2_MacroAssembler _masm(cbuf);
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
      C2_MacroAssembler _masm(cbuf);
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

#ifndef PRODUCT
void MachNopNode::format(PhaseRegAlloc *ra_, outputStream *st) const {
  st->print("NOP \t// %d nops to pad for loops or prefixed instructions.", _count);
}
#endif

void MachNopNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *) const {
  C2_MacroAssembler _masm(&cbuf);
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
  ra_->dump_register(this, reg_str, sizeof(reg_str));
  st->print("ADDI    %s, SP, %d \t// box node", reg_str, offset);
}
#endif

void BoxLockNode::emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const {
  C2_MacroAssembler _masm(&cbuf);

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
  C2_MacroAssembler _masm(&cbuf);

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

uint MachUEPNode::size(PhaseRegAlloc *ra_) const {
  // Variable size. Determine dynamically.
  return MachNode::size(ra_);
}

//=============================================================================


#line 1079 "ad_ppc.cpp"


//SourceForm

#line 2059 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


int HandlerImpl::emit_exception_handler(CodeBuffer &cbuf) {
  C2_MacroAssembler _masm(&cbuf);

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
  C2_MacroAssembler _masm(&cbuf);

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
  if (!has_match_rule(opcode)) {
    return false; // no match rule present
  }

  switch (opcode) {
    case Op_SqrtD:
      return VM_Version::has_fsqrt();
    case Op_RoundDoubleMode:
      return VM_Version::has_vsx();
    case Op_CountLeadingZerosI:
    case Op_CountLeadingZerosL:
      return UseCountLeadingZerosInstructionsPPC64;
    case Op_CountTrailingZerosI:
    case Op_CountTrailingZerosL:
      return (UseCountLeadingZerosInstructionsPPC64 || UseCountTrailingZerosInstructionsPPC64);
    case Op_PopCountI:
    case Op_PopCountL:
      return (UsePopCountInstruction && VM_Version::has_popcntw());

    case Op_AddVB:
    case Op_AddVS:
    case Op_AddVI:
    case Op_AddVF:
    case Op_AddVD:
    case Op_SubVB:
    case Op_SubVS:
    case Op_SubVI:
    case Op_SubVF:
    case Op_SubVD:
    case Op_MulVS:
    case Op_MulVF:
    case Op_MulVD:
    case Op_DivVF:
    case Op_DivVD:
    case Op_AbsVF:
    case Op_AbsVD:
    case Op_NegVF:
    case Op_NegVD:
    case Op_SqrtVF:
    case Op_SqrtVD:
    case Op_AddVL:
    case Op_SubVL:
    case Op_MulVI:
    case Op_RoundDoubleModeV:
      return SuperwordUseVSX;
    case Op_PopCountVI:
      return (SuperwordUseVSX && UsePopCountInstruction);
    case Op_FmaVF:
    case Op_FmaVD:
      return (SuperwordUseVSX && UseFMA);

    case Op_Digit:
      return vmIntrinsics::is_intrinsic_available(vmIntrinsics::_isDigit);
    case Op_LowerCase:
      return vmIntrinsics::is_intrinsic_available(vmIntrinsics::_isLowerCase);
    case Op_UpperCase:
      return vmIntrinsics::is_intrinsic_available(vmIntrinsics::_isUpperCase);
    case Op_Whitespace:
      return vmIntrinsics::is_intrinsic_available(vmIntrinsics::_isWhitespace);

    case Op_CacheWB:
    case Op_CacheWBPreSync:
    case Op_CacheWBPostSync:
      return VM_Version::supports_data_cache_line_flush();
  }

  return true; // Per default match rules are supported.
}

const bool Matcher::match_rule_supported_superword(int opcode, int vlen, BasicType bt) {
  return match_rule_supported_vector(opcode, vlen, bt);
}

const bool Matcher::match_rule_supported_vector(int opcode, int vlen, BasicType bt) {
  if (!match_rule_supported(opcode) || !vector_size_supported(bt, vlen)) {
    return false;
  }
  return true; // Per default match rules are supported.
}

const bool Matcher::match_rule_supported_vector_masked(int opcode, int vlen, BasicType bt) {
  return false;
}

const bool Matcher::vector_needs_partial_operations(Node* node, const TypeVect* vt) {
  return false;
}

const RegMask* Matcher::predicate_reg_mask(void) {
  return NULL;
}

const TypeVectMask* Matcher::predicate_reg_type(const Type* elemTy, int length) {
  return NULL;
}

// Vector calling convention not yet implemented.
const bool Matcher::supports_vector_calling_convention(void) {
  return false;
}

OptoRegPair Matcher::vector_return_value(uint ideal_reg) {
  Unimplemented();
  return OptoRegPair(0, 0);
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

// Limits on vector size (number of elements) loaded into vector.
const int Matcher::max_vector_size(const BasicType bt) {
  assert(is_java_primitive(bt), "only primitive type vectors");
  return vector_width_in_bytes(bt)/type2aelembytes(bt);
}

const int Matcher::min_vector_size(const BasicType bt) {
  return max_vector_size(bt); // Same as max.
}

const int Matcher::scalable_vector_reg_size(const BasicType bt) {
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
  // Is the offset within the range of a ppc64 pc relative branch?
  bool b;

  const int safety_zone = 3 * BytesPerInstWord;
  b = Assembler::is_simm((offset<0 ? offset-safety_zone : offset+safety_zone),
                         29 - 16 + 1 + 2);
  return b;
}

/* TODO: PPC port
// Make a new machine dependent decode node (with its operands).
MachTypeNode *Matcher::make_decode_node() {
  assert(CompressedOops::base() == NULL && CompressedOops::shift() == 0,
         "This method is only implemented for unscaled cOops mode so far");
  MachTypeNode *decode = new decodeN_unscaledNode();
  decode->set_opnd_array(0, new iRegPdstOper());
  decode->set_opnd_array(1, new iRegNsrcOper());
  return decode;
}
*/

MachOper* Matcher::pd_specialize_generic_vector_operand(MachOper* original_opnd, uint ideal_reg, bool is_temp) {
  ShouldNotReachHere(); // generic vector operands not supported
  return NULL;
}

bool Matcher::is_reg2reg_move(MachNode* m) {
  ShouldNotReachHere();  // generic vector operands not supported
  return false;
}

bool Matcher::is_generic_vector(MachOper* opnd)  {
  ShouldNotReachHere();  // generic vector operands not supported
  return false;
}

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

uint Matcher::int_pressure_limit()
{
  return (INTPRESSURE == -1) ? 26 : INTPRESSURE;
}

uint Matcher::float_pressure_limit()
{
  return (FLOATPRESSURE == -1) ? 28 : FLOATPRESSURE;
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


#line 1445 "ad_ppc.cpp"


//SourceForm

#line 2583 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


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


#line 1637 "ad_ppc.cpp"


//SourceForm

#line 14381 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


#include "runtime/continuation.hpp"


#line 1648 "ad_ppc.cpp"


//SourceForm

#line 33 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/z/z_ppc.ad"


static void z_load_barrier(MacroAssembler& _masm, const MachNode* node, Address ref_addr, Register ref,
                           Register tmp, uint8_t barrier_data) {
  if (barrier_data == ZLoadBarrierElided) {
    return;
  }

  ZLoadBarrierStubC2* const stub = ZLoadBarrierStubC2::create(node, ref_addr, ref, tmp, barrier_data);
  __ ld(tmp, in_bytes(ZThreadLocalData::address_bad_mask_offset()), R16_thread);
  __ and_(tmp, tmp, ref);
  __ bne_far(CCR0, *stub->entry(), MacroAssembler::bc_far_optimize_on_relocate);
  __ bind(*stub->continuation());
}

static void z_load_barrier_slow_path(MacroAssembler& _masm, const MachNode* node, Address ref_addr, Register ref,
                                     Register tmp) {
  ZLoadBarrierStubC2* const stub = ZLoadBarrierStubC2::create(node, ref_addr, ref, tmp, ZLoadBarrierStrong);
  __ b(*stub->entry());
  __ bind(*stub->continuation());
}

static void z_compare_and_swap(MacroAssembler& _masm, const MachNode* node,
                              Register res, Register mem, Register oldval, Register newval,
                              Register tmp_xchg, Register tmp_mask,
                              bool weak, bool acquire) {
  // z-specific load barrier requires strong CAS operations.
  // Weak CAS operations are thus only emitted if the barrier is elided.
  __ cmpxchgd(CCR0, tmp_xchg, oldval, newval, mem,
              MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(), res, NULL, true,
              weak && node->barrier_data() == ZLoadBarrierElided);

  if (node->barrier_data() != ZLoadBarrierElided) {
    Label skip_barrier;

    __ ld(tmp_mask, in_bytes(ZThreadLocalData::address_bad_mask_offset()), R16_thread);
    __ and_(tmp_mask, tmp_mask, tmp_xchg);
    __ beq(CCR0, skip_barrier);

    // CAS must have failed because pointer in memory is bad.
    z_load_barrier_slow_path(_masm, node, Address(mem), tmp_xchg, res /* used as tmp */);

    __ cmpxchgd(CCR0, tmp_xchg, oldval, newval, mem,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(), res, NULL, true, weak);

    __ bind(skip_barrier);
  }

  if (acquire) {
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      // Uses the isync instruction as an acquire barrier.
      // This exploits the compare and the branch in the z load barrier (load, compare and branch, isync).
      __ isync();
    } else {
      __ sync();
    }
  }
}

static void z_compare_and_exchange(MacroAssembler& _masm, const MachNode* node,
                                   Register res, Register mem, Register oldval, Register newval, Register tmp,
                                   bool weak, bool acquire) {
  // z-specific load barrier requires strong CAS operations.
  // Weak CAS operations are thus only emitted if the barrier is elided.
  __ cmpxchgd(CCR0, res, oldval, newval, mem,
              MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(), noreg, NULL, true,
              weak && node->barrier_data() == ZLoadBarrierElided);

  if (node->barrier_data() != ZLoadBarrierElided) {
    Label skip_barrier;
    __ ld(tmp, in_bytes(ZThreadLocalData::address_bad_mask_offset()), R16_thread);
    __ and_(tmp, tmp, res);
    __ beq(CCR0, skip_barrier);

    z_load_barrier_slow_path(_masm, node, Address(mem), res, tmp);

    __ cmpxchgd(CCR0, res, oldval, newval, mem,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(), noreg, NULL, true, weak);

    __ bind(skip_barrier);
  }

  if (acquire) {
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      // Uses the isync instruction as an acquire barrier.
      // This exploits the compare and the branch in the z load barrier (load, compare and branch, isync).
      __ isync();
    } else {
      __ sync();
    }
  }
}


#line 1748 "ad_ppc.cpp"


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
  'E', // VSR14
  'E', // VSR15
  'E', // VSR16
  'E', // VSR17
  'E', // VSR18
  'E', // VSR19
  'E', // VSR20
  'E', // VSR21
  'E', // VSR22
  'E', // VSR23
  'E', // VSR24
  'E', // VSR25
  'E', // VSR26
  'E', // VSR27
  'E', // VSR28
  'E', // VSR29
  'E', // VSR30
  'E', // VSR31
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
  'E', // VSR52
  'E', // VSR53
  'E', // VSR54
  'E', // VSR55
  'E', // VSR56
  'E', // VSR57
  'E', // VSR58
  'E', // VSR59
  'E', // VSR60
  'E', // VSR61
  'E', // VSR62
  'E', // VSR63
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
  /*   13 */  immI32_rule,
  /*   14 */  immInegpow2_rule,
  /*   15 */  immIpow2minus1_rule,
  /*   16 */  immIpowerOf2_rule,
  /*   17 */  uimmI5_rule,
  /*   18 */  uimmI6_rule,
  /*   19 */  uimmI6_ge32_rule,
  /*   20 */  uimmI15_rule,
  /*   21 */  uimmI16_rule,
  /*   22 */  immI_0_rule,
  /*   23 */  immI_1_rule,
  /*   24 */  immI_minus1_rule,
  /*   25 */  immI_16_rule,
  /*   26 */  immI_24_rule,
  /*   27 */  immN_rule,
  /*   28 */  immN_0_rule,
  /*   29 */  immNKlass_rule,
  /*   30 */  immNKlass_NM_rule,
  /*   31 */  immP_rule,
  /*   32 */  immP_NM_rule,
  /*   33 */  immP_0_rule,
  /*   34 */  immP_0or1_rule,
  /*   35 */  immL_rule,
  /*   36 */  immLmax30_rule,
  /*   37 */  immL16_rule,
  /*   38 */  immL16Alg4_rule,
  /*   39 */  immL32hi16_rule,
  /*   40 */  immL32_rule,
  /*   41 */  immL34_rule,
  /*   42 */  immLhighest16_rule,
  /*   43 */  immLnegpow2_rule,
  /*   44 */  immLpow2minus1_rule,
  /*   45 */  immL_0_rule,
  /*   46 */  immL_minus1_rule,
  /*   47 */  immL_32bits_rule,
  /*   48 */  uimmL16_rule,
  /*   49 */  immF_rule,
  /*   50 */  immF_0_rule,
  /*   51 */  immD_rule,
  /*   52 */  immD_0_rule,
  /*   53 */  iRegIdst_rule,
  /*   54 */  iRegIsrc_rule,
  /*   55 */  rscratch1RegI_rule,
  /*   56 */  rscratch2RegI_rule,
  /*   57 */  rarg1RegI_rule,
  /*   58 */  rarg2RegI_rule,
  /*   59 */  rarg3RegI_rule,
  /*   60 */  rarg4RegI_rule,
  /*   61 */  rarg1RegL_rule,
  /*   62 */  rarg2RegL_rule,
  /*   63 */  rarg3RegL_rule,
  /*   64 */  rarg4RegL_rule,
  /*   65 */  iRegPdst_rule,
  /*   66 */  iRegPdstNoScratch_rule,
  /*   67 */  iRegPsrc_rule,
  /*   68 */  threadRegP_rule,
  /*   69 */  rscratch1RegP_rule,
  /*   70 */  rscratch2RegP_rule,
  /*   71 */  rarg1RegP_rule,
  /*   72 */  rarg2RegP_rule,
  /*   73 */  rarg3RegP_rule,
  /*   74 */  rarg4RegP_rule,
  /*   75 */  iRegNsrc_rule,
  /*   76 */  iRegNdst_rule,
  /*   77 */  iRegLdst_rule,
  /*   78 */  iRegLsrc_rule,
  /*   79 */  iRegL2Isrc_rule,
  /*   80 */  rscratch1RegL_rule,
  /*   81 */  rscratch2RegL_rule,
  /*   82 */  flagsReg_rule,
  /*   83 */  flagsRegSrc_rule,
  /*   84 */  flagsRegCR0_rule,
  /*   85 */  flagsRegCR1_rule,
  /*   86 */  flagsRegCR6_rule,
  /*   87 */  regCTR_rule,
  /*   88 */  regD_rule,
  /*   89 */  regF_rule,
  /*   90 */  inline_cache_regP_rule,
  /*   91 */  iRegP2N_rule,
  /*   92 */  iRegN2P_rule,
  /*   93 */  iRegN2P_klass_rule,
  /*   94 */  indirect_rule,
  /*   95 */  indOffset16_rule,
  /*   96 */  indOffset16Alg4_rule,
  /*   97 */  indirectNarrow_rule,
  /*   98 */  indirectNarrow_klass_rule,
  /*   99 */  indOffset16Narrow_rule,
  /*  100 */  indOffset16Narrow_klass_rule,
  /*  101 */  indOffset16NarrowAlg4_rule,
  /*  102 */  indOffset16NarrowAlg4_klass_rule,
  /*  103 */  stackSlotI_rule,
  /*  104 */  stackSlotL_rule,
  /*  105 */  stackSlotP_rule,
  /*  106 */  stackSlotF_rule,
  /*  107 */  stackSlotD_rule,
  /*  108 */  cmpOp_rule,
  // last operand
  /*  109 */  memory_rule,
  /*  110 */  memoryAlg4_rule,
  /*  111 */  indirectMemory_rule,
  /*  112 */  iRegIsrc_iRegL2Isrc_rule,
  /*  113 */  iRegN_P2N_rule,
  /*  114 */  iRegP_N2P_rule,
  // last operand class
  /*  115 */  _DecodeN_iRegNsrc__rule,
  /*  116 */  _DecodeNKlass_iRegNsrc__rule,
  /*  117 */  _LoadUB_memory__rule,
  /*  118 */  _LoadUS_memory__rule,
  /*  119 */  _LoadI_memory__rule,
  /*  120 */  _ConvI2L__LoadI_memory___rule,
  /*  121 */  _LoadI_memoryAlg4__rule,
  /*  122 */  _LoadN_memory__rule,
  /*  123 */  _LoadNKlass_memory__rule,
  /*  124 */  _LoadP_memoryAlg4__rule,
  /*  125 */  _AddP_indirectMemory_iRegLsrc_rule,
  /*  126 */  _ConvL2I_iRegLsrc__rule,
  /*  127 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  128 */  _CastP2X__DecodeN_iRegNsrc___rule,
  /*  129 */  _Binary_iRegLsrc_iRegPdst_rule,
  /*  130 */  _Binary_iRegLsrc_iRegPsrc_rule,
  /*  131 */  _Binary_iRegLsrc_iRegNsrc_rule,
  /*  132 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  133 */  _Binary_iRegIdst_iRegIsrc_rule,
  /*  134 */  _Binary_iRegIdst_immI16_rule,
  /*  135 */  _Binary_iRegLdst_iRegLsrc_rule,
  /*  136 */  _Binary_iRegLdst_immL16_rule,
  /*  137 */  _Binary_iRegNdst_iRegNsrc_rule,
  /*  138 */  _Binary_iRegNdst_immN_0_rule,
  /*  139 */  _Binary_iRegPdst_iRegPsrc_rule,
  /*  140 */  _Binary_iRegPdst_iRegP_N2P_rule,
  /*  141 */  _Binary_iRegPdst_immP_0_rule,
  /*  142 */  _Binary_regF_regF_rule,
  /*  143 */  _Binary_regD_regD_rule,
  /*  144 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  145 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  146 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  147 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  148 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  149 */  _AddI_iRegIsrc_iRegIsrc_rule,
  /*  150 */  _AddI__AddI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  151 */  _AddI_iRegIsrc__AddI_iRegIsrc_iRegIsrc_rule,
  /*  152 */  _AddL_iRegLsrc_iRegLsrc_rule,
  /*  153 */  _AddL__AddL_iRegLsrc_iRegLsrc_iRegLsrc_rule,
  /*  154 */  _AddL_iRegLsrc__AddL_iRegLsrc_iRegLsrc_rule,
  /*  155 */  _SubL_iRegLsrc_iRegLsrc_rule,
  /*  156 */  _SubL_immL_0_iRegLsrc_rule,
  /*  157 */  _AndI_iRegIsrc_immInegpow2_rule,
  /*  158 */  _RShiftI_iRegIsrc_uimmI5_rule,
  /*  159 */  _AndI__RShiftI_iRegIsrc_uimmI5_immInegpow2_rule,
  /*  160 */  _ConvI2L_iRegIsrc__rule,
  /*  161 */  _RShiftL_iRegLsrc_immI_rule,
  /*  162 */  _URShiftL_iRegLsrc_immI_rule,
  /*  163 */  _CastP2X_iRegP_N2P__rule,
  /*  164 */  _URShiftI_iRegIsrc_immI_rule,
  /*  165 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  166 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  167 */  _AbsF_regF__rule,
  /*  168 */  _AbsD_regD__rule,
  /*  169 */  _NegF_regF__rule,
  /*  170 */  _Binary__NegF_regF__regF_rule,
  /*  171 */  _Binary_regF__NegF_regF__rule,
  /*  172 */  _NegD_regD__rule,
  /*  173 */  _Binary__NegD_regD__regD_rule,
  /*  174 */  _Binary_regD__NegD_regD__rule,
  /*  175 */  _AndL_iRegLsrc_immLpow2minus1_rule,
  /*  176 */  _OrI_iRegIsrc_iRegIsrc_rule,
  /*  177 */  _OrI__OrI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  178 */  _OrI_iRegIsrc__OrI_iRegIsrc_iRegIsrc_rule,
  /*  179 */  _OrL_iRegLsrc_iRegLsrc_rule,
  /*  180 */  _XorI_iRegIsrc_iRegIsrc_rule,
  /*  181 */  _XorI__XorI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  182 */  _XorI_iRegIsrc__XorI_iRegIsrc_iRegIsrc_rule,
  /*  183 */  _XorL_iRegLsrc_iRegLsrc_rule,
  /*  184 */  _XorI_iRegIsrc_immI_minus1_rule,
  /*  185 */  _Conv2B_iRegIsrc__rule,
  /*  186 */  _AndI_iRegIsrc_immIpowerOf2_rule,
  /*  187 */  _Conv2B_iRegP_N2P__rule,
  /*  188 */  _LShiftI_iRegIsrc_immI_24_rule,
  /*  189 */  _LShiftI_iRegIsrc_immI_16_rule,
  /*  190 */  _AndI_iRegIsrc_uimmI16_rule,
  /*  191 */  _AndL_iRegLsrc_iRegLsrc_rule,
  /*  192 */  _AndL_iRegLsrc_uimmL16_rule,
  /*  193 */  _CmpU_iRegIsrc_uimmI15_rule,
  /*  194 */  _CmpU_iRegIsrc_iRegIsrc_rule,
  /*  195 */  _CmpN_iRegNsrc_immN_0_rule,
  /*  196 */  _CmpP_iRegP_N2P_immP_0_rule,
  /*  197 */  _CastP2X_iRegPsrc__rule,
  /*  198 */  _AndL__CastP2X_iRegPsrc__immLnegpow2_rule,
  /*  199 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  200 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  201 */  _Binary_rarg1RegP_rarg2RegP_rule,
  /*  202 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  203 */  _AddP_immP_immL_rule,
  /*  204 */  _Binary__AddP_immP_immL_immI_1_rule,
  /*  205 */  _Binary_rscratch2RegP_immI_1_rule,
  /*  206 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  207 */  _Binary_iRegPsrc_uimmI15_rule,
  /*  208 */  _Binary_iRegPsrc_rscratch2RegI_rule,
  /*  209 */  _Binary_rarg2RegP_iRegIsrc_rule,
  /*  210 */  _LoadI_indirect__rule,
  /*  211 */  _LoadL_indirect__rule,
  /*  212 */  _LoadUS_indirect__rule,
  /*  213 */  _LoadS_indirect__rule,
  /*  214 */  _ReverseBytesI_iRegIsrc__rule,
  /*  215 */  _ReverseBytesL_iRegLsrc__rule,
  /*  216 */  _ReverseBytesUS_iRegIsrc__rule,
  /*  217 */  _ReverseBytesS_iRegIsrc__rule,
  /*  218 */  _Binary_vecX_vecX_rule,
  /*  219 */  _NegVF_vecX__rule,
  /*  220 */  _Binary__NegVF_vecX__vecX_rule,
  /*  221 */  _Binary_vecX__NegVF_vecX__rule,
  /*  222 */  _NegVD_vecX__rule,
  /*  223 */  _Binary__NegVD_vecX__vecX_rule,
  /*  224 */  _Binary_vecX__NegVD_vecX__rule,
  // last internally defined operand
  /*  225 */  stackSlotI_rule,
  /*  226 */  stackSlotL_rule,
  /*  227 */  iRegIdst_rule,
  /*  228 */  iRegIdst_rule,
  /*  229 */  iRegIdst_rule,
  /*  230 */  iRegIdst_rule,
  /*  231 */  iRegLdst_rule,
  /*  232 */  iRegLdst_rule,
  /*  233 */  iRegLdst_rule,
  /*  234 */  iRegLdst_rule,
  /*  235 */  iRegLdst_rule,
  /*  236 */  iRegLdst_rule,
  /*  237 */  iRegNdst_rule,
  /*  238 */  iRegNdst_rule,
  /*  239 */  iRegNdst_rule,
  /*  240 */  iRegNdst_rule,
  /*  241 */  iRegNdst_rule,
  /*  242 */  iRegNdst_rule,
  /*  243 */  iRegPdst_rule,
  /*  244 */  iRegPdst_rule,
  /*  245 */  iRegPdst_rule,
  /*  246 */  iRegPdst_rule,
  /*  247 */  regF_rule,
  /*  248 */  regD_rule,
  /*  249 */  iRegIdst_rule,
  /*  250 */  iRegLdst_rule,
  /*  251 */  0,
  /*  252 */  iRegLdst_rule,
  /*  253 */  0,
  /*  254 */  0,
  /*  255 */  0,
  /*  256 */  iRegLdst_rule,
  /*  257 */  vecX_rule,
  /*  258 */  0,
  /*  259 */  iRegIdst_rule,
  /*  260 */  0,
  /*  261 */  0,
  /*  262 */  iRegLdst_rule,
  /*  263 */  regF_rule,
  /*  264 */  regD_rule,
  /*  265 */  regF_rule,
  /*  266 */  regD_rule,
  /*  267 */  regF_rule,
  /*  268 */  regD_rule,
  /*  269 */  regD_rule,
  /*  270 */  regF_rule,
  /*  271 */  regD_rule,
  /*  272 */  0,
  /*  273 */  iRegIdst_rule,
  /*  274 */  regF_rule,
  /*  275 */  iRegLdst_rule,
  /*  276 */  regD_rule,
  /*  277 */  0,
  /*  278 */  iRegPdst_rule,
  /*  279 */  iRegLdst_rule,
  /*  280 */  iRegPdst_rule,
  /*  281 */  iRegIdst_rule,
  /*  282 */  iRegLdst_rule,
  /*  283 */  regF_rule,
  /*  284 */  regD_rule,
  /*  285 */  iRegLdst_rule,
  /*  286 */  vecX_rule,
  /*  287 */  iRegPdst_rule,
  /*  288 */  iRegIdst_rule,
  /*  289 */  iRegIdst_rule,
  /*  290 */  0,
  /*  291 */  0,
  /*  292 */  0,
  /*  293 */  0,
  /*  294 */  0,
  /*  295 */  0,
  /*  296 */  0,
  /*  297 */  flagsReg_rule,
  /*  298 */  flagsReg_rule,
  /*  299 */  flagsRegCR0_rule,
  /*  300 */  flagsReg_rule,
  /*  301 */  flagsReg_rule,
  /*  302 */  flagsReg_rule,
  /*  303 */  flagsReg_rule,
  /*  304 */  flagsRegCR0_rule,
  /*  305 */  flagsRegCR0_rule,
  /*  306 */  flagsReg_rule,
  /*  307 */  flagsReg_rule,
  /*  308 */  flagsReg_rule,
  /*  309 */  flagsReg_rule,
  /*  310 */  flagsReg_rule,
  /*  311 */  flagsReg_rule,
  /*  312 */  flagsReg_rule,
  /*  313 */  flagsReg_rule,
  /*  314 */  0,
  /*  315 */  flagsReg_rule,
  /*  316 */  flagsReg_rule,
  /*  317 */  flagsReg_rule,
  /*  318 */  flagsReg_rule,
  /*  319 */  flagsReg_rule,
  /*  320 */  flagsReg_rule,
  /*  321 */  flagsReg_rule,
  /*  322 */  iRegIdst_rule,
  /*  323 */  iRegIdst_rule,
  /*  324 */  iRegIdst_rule,
  /*  325 */  iRegIdst_rule,
  /*  326 */  0,
  /*  327 */  iRegIdst_rule,
  /*  328 */  iRegIdst_rule,
  /*  329 */  iRegIdst_rule,
  /*  330 */  iRegIdst_rule,
  /*  331 */  0,
  /*  332 */  0,
  /*  333 */  0,
  /*  334 */  0,
  /*  335 */  0,
  /*  336 */  iRegLdst_rule,
  /*  337 */  iRegLdst_rule,
  /*  338 */  iRegLdst_rule,
  /*  339 */  vecX_rule,
  /*  340 */  vecX_rule,
  /*  341 */  vecX_rule,
  /*  342 */  iRegLdst_rule,
  /*  343 */  iRegLdst_rule,
  /*  344 */  iRegLdst_rule,
  /*  345 */  vecX_rule,
  /*  346 */  vecX_rule,
  /*  347 */  vecX_rule,
  /*  348 */  iRegLdst_rule,
  /*  349 */  iRegLdst_rule,
  /*  350 */  iRegLdst_rule,
  /*  351 */  vecX_rule,
  /*  352 */  vecX_rule,
  /*  353 */  vecX_rule,
  /*  354 */  iRegLdst_rule,
  /*  355 */  iRegLdst_rule,
  /*  356 */  iRegLdst_rule,
  /*  357 */  vecX_rule,
  /*  358 */  vecX_rule,
  /*  359 */  vecX_rule,
  /*  360 */  vecX_rule,
  /*  361 */  vecX_rule,
  /*  362 */  vecX_rule,
  /*  363 */  vecX_rule,
  /*  364 */  flagsRegCR0_rule,
  /*  365 */  flagsRegCR0_rule,
  /*  366 */  flagsRegCR0_rule,
  /*  367 */  flagsRegCR0_rule,
  /*  368 */  vecX_rule,
  /*  369 */  vecX_rule,
  /*  370 */  vecX_rule,
  /*  371 */  vecX_rule,
  /*  372 */  0,
  /*  373 */  vecX_rule,
  /*  374 */  vecX_rule,
  /*  375 */  vecX_rule,
  /*  376 */  0,
  /*  377 */  threadRegP_rule,
  /*  378 */  iRegIdst_rule,
  /*  379 */  iRegIdst_rule,
  /*  380 */  iRegIdst_rule,
  /*  381 */  iRegIdst_rule,
  /*  382 */  iRegIdst_rule,
  /*  383 */  iRegIdst_rule,
  /*  384 */  iRegIdst_rule,
  /*  385 */  iRegIdst_rule,
  /*  386 */  iRegIdst_rule,
  /*  387 */  iRegIdst_rule,
  /*  388 */  iRegLdst_rule,
  /*  389 */  iRegLdst_rule,
  /*  390 */  iRegIdst_rule,
  /*  391 */  iRegIdst_rule,
  /*  392 */  iRegIdst_rule,
  /*  393 */  iRegIdst_rule,
  /*  394 */  iRegLdst_rule,
  /*  395 */  iRegLdst_rule,
  /*  396 */  iRegIdst_rule,
  /*  397 */  iRegIdst_rule,
  /*  398 */  iRegLdst_rule,
  /*  399 */  iRegLdst_rule,
  /*  400 */  iRegLdst_rule,
  /*  401 */  iRegLdst_rule,
  /*  402 */  iRegLdst_rule,
  /*  403 */  iRegLdst_rule,
  /*  404 */  iRegLdst_rule,
  /*  405 */  vecX_rule,
  /*  406 */  iRegIdst_rule,
  /*  407 */  iRegNdst_rule,
  /*  408 */  iRegNdst_rule,
  /*  409 */  iRegPdst_rule,
  /*  410 */  iRegPdst_rule,
  /*  411 */  iRegPdst_rule,
  /*  412 */  iRegPdst_rule,
  /*  413 */  iRegNdst_rule,
  /*  414 */  iRegPdst_rule,
  /*  415 */  regF_rule,
  /*  416 */  regF_rule,
  /*  417 */  regD_rule,
  /*  418 */  regD_rule,
  /*  419 */  regD_rule,
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
  /*  434 */  Universe_rule,
  /*  435 */  Universe_rule,
  /*  436 */  Universe_rule,
  /*  437 */  Universe_rule,
  /*  438 */  Universe_rule,
  /*  439 */  Universe_rule,
  /*  440 */  Universe_rule,
  /*  441 */  Universe_rule,
  /*  442 */  Universe_rule,
  /*  443 */  Universe_rule,
  /*  444 */  Universe_rule,
  /*  445 */  Universe_rule,
  /*  446 */  Universe_rule,
  /*  447 */  Universe_rule,
  /*  448 */  Universe_rule,
  /*  449 */  Universe_rule,
  /*  450 */  Universe_rule,
  /*  451 */  iRegNdst_rule,
  /*  452 */  iRegPdst_rule,
  /*  453 */  iRegNdst_rule,
  /*  454 */  iRegNdst_rule,
  /*  455 */  iRegNdst_rule,
  /*  456 */  iRegNdst_rule,
  /*  457 */  iRegNdst_rule,
  /*  458 */  iRegNdst_rule,
  /*  459 */  iRegNdst_rule,
  /*  460 */  iRegPdst_rule,
  /*  461 */  iRegPdst_rule,
  /*  462 */  iRegPdst_rule,
  /*  463 */  iRegPdst_rule,
  /*  464 */  iRegPdst_rule,
  /*  465 */  iRegPdst_rule,
  /*  466 */  iRegPdst_rule,
  /*  467 */  iRegPdst_rule,
  /*  468 */  iRegPdst_rule,
  /*  469 */  iRegPdst_rule,
  /*  470 */  iRegPdst_rule,
  /*  471 */  iRegIdst_rule,
  /*  472 */  iRegNdst_rule,
  /*  473 */  iRegPdst_rule,
  /*  474 */  iRegNdst_rule,
  /*  475 */  iRegNdst_rule,
  /*  476 */  iRegNdst_rule,
  /*  477 */  iRegPdst_rule,
  /*  478 */  iRegPdst_rule,
  /*  479 */  iRegPdst_rule,
  /*  480 */  iRegPdst_rule,
  /*  481 */  Universe_rule,
  /*  482 */  Universe_rule,
  /*  483 */  Universe_rule,
  /*  484 */  Universe_rule,
  /*  485 */  Universe_rule,
  /*  486 */  Universe_rule,
  /*  487 */  Universe_rule,
  /*  488 */  Universe_rule,
  /*  489 */  Universe_rule,
  /*  490 */  Universe_rule,
  /*  491 */  iRegIdst_rule,
  /*  492 */  iRegIdst_rule,
  /*  493 */  iRegIdst_rule,
  /*  494 */  iRegLdst_rule,
  /*  495 */  iRegLdst_rule,
  /*  496 */  iRegLdst_rule,
  /*  497 */  iRegNdst_rule,
  /*  498 */  iRegNdst_rule,
  /*  499 */  iRegNdst_rule,
  /*  500 */  iRegPdst_rule,
  /*  501 */  iRegPdst_rule,
  /*  502 */  iRegPdst_rule,
  /*  503 */  regF_rule,
  /*  504 */  regD_rule,
  /*  505 */  iRegIdst_rule,
  /*  506 */  iRegIdst_rule,
  /*  507 */  iRegIdst_rule,
  /*  508 */  iRegIdst_rule,
  /*  509 */  iRegIdst_rule,
  /*  510 */  iRegIdst_rule,
  /*  511 */  iRegIdst_rule,
  /*  512 */  iRegIdst_rule,
  /*  513 */  iRegIdst_rule,
  /*  514 */  iRegIdst_rule,
  /*  515 */  iRegIdst_rule,
  /*  516 */  iRegIdst_rule,
  /*  517 */  iRegIdst_rule,
  /*  518 */  iRegIdst_rule,
  /*  519 */  iRegIdst_rule,
  /*  520 */  iRegIdst_rule,
  /*  521 */  iRegIdst_rule,
  /*  522 */  iRegIdst_rule,
  /*  523 */  iRegIdst_rule,
  /*  524 */  iRegIdst_rule,
  /*  525 */  iRegIdst_rule,
  /*  526 */  iRegIdst_rule,
  /*  527 */  iRegIdst_rule,
  /*  528 */  iRegIdst_rule,
  /*  529 */  iRegIdst_rule,
  /*  530 */  iRegIdst_rule,
  /*  531 */  iRegIdst_rule,
  /*  532 */  iRegIdst_rule,
  /*  533 */  iRegIdst_rule,
  /*  534 */  iRegIdst_rule,
  /*  535 */  iRegIdst_rule,
  /*  536 */  iRegIdst_rule,
  /*  537 */  iRegIdst_rule,
  /*  538 */  iRegIdst_rule,
  /*  539 */  iRegNdst_rule,
  /*  540 */  iRegNdst_rule,
  /*  541 */  iRegLdst_rule,
  /*  542 */  iRegLdst_rule,
  /*  543 */  iRegPdst_rule,
  /*  544 */  iRegPdst_rule,
  /*  545 */  iRegIdst_rule,
  /*  546 */  iRegIdst_rule,
  /*  547 */  iRegIdst_rule,
  /*  548 */  iRegIdst_rule,
  /*  549 */  iRegIdst_rule,
  /*  550 */  iRegLdst_rule,
  /*  551 */  iRegIdst_rule,
  /*  552 */  iRegIdst_rule,
  /*  553 */  iRegIdst_rule,
  /*  554 */  iRegIdst_rule,
  /*  555 */  iRegIdst_rule,
  /*  556 */  iRegLdst_rule,
  /*  557 */  iRegPdst_rule,
  /*  558 */  iRegNdst_rule,
  /*  559 */  iRegIdst_rule,
  /*  560 */  0,
  /*  561 */  iRegIdst_rule,
  /*  562 */  iRegIdst_rule,
  /*  563 */  iRegIdst_rule,
  /*  564 */  iRegIdst_rule,
  /*  565 */  iRegIdst_rule,
  /*  566 */  iRegIdst_rule,
  /*  567 */  iRegIdst_rule,
  /*  568 */  iRegLdst_rule,
  /*  569 */  0,
  /*  570 */  iRegLdst_rule,
  /*  571 */  iRegLdst_rule,
  /*  572 */  iRegLdst_rule,
  /*  573 */  iRegLdst_rule,
  /*  574 */  iRegIdst_rule,
  /*  575 */  iRegLdst_rule,
  /*  576 */  iRegLdst_rule,
  /*  577 */  iRegLdst_rule,
  /*  578 */  iRegPdst_rule,
  /*  579 */  iRegPdst_rule,
  /*  580 */  iRegPdst_rule,
  /*  581 */  iRegPdst_rule,
  /*  582 */  iRegIdst_rule,
  /*  583 */  iRegIdst_rule,
  /*  584 */  iRegIdst_rule,
  /*  585 */  iRegLdst_rule,
  /*  586 */  iRegIdst_rule,
  /*  587 */  iRegLdst_rule,
  /*  588 */  iRegIdst_rule,
  /*  589 */  iRegIdst_rule,
  /*  590 */  iRegIdst_rule,
  /*  591 */  iRegLdst_rule,
  /*  592 */  iRegLdst_rule,
  /*  593 */  iRegLdst_rule,
  /*  594 */  iRegIdst_rule,
  /*  595 */  iRegIdst_rule,
  /*  596 */  0,
  /*  597 */  iRegIdst_rule,
  /*  598 */  iRegLdst_rule,
  /*  599 */  iRegLdst_rule,
  /*  600 */  0,
  /*  601 */  iRegLdst_rule,
  /*  602 */  iRegIdst_rule,
  /*  603 */  iRegLdst_rule,
  /*  604 */  iRegIdst_rule,
  /*  605 */  iRegIdst_rule,
  /*  606 */  iRegLdst_rule,
  /*  607 */  iRegLdst_rule,
  /*  608 */  0,
  /*  609 */  0,
  /*  610 */  iRegIdst_rule,
  /*  611 */  iRegIdst_rule,
  /*  612 */  iRegIdst_rule,
  /*  613 */  iRegIdst_rule,
  /*  614 */  0,
  /*  615 */  iRegLdst_rule,
  /*  616 */  iRegLdst_rule,
  /*  617 */  iRegLdst_rule,
  /*  618 */  iRegLdst_rule,
  /*  619 */  0,
  /*  620 */  iRegIdst_rule,
  /*  621 */  iRegIdst_rule,
  /*  622 */  0,
  /*  623 */  iRegLdst_rule,
  /*  624 */  iRegLdst_rule,
  /*  625 */  iRegIdst_rule,
  /*  626 */  0,
  /*  627 */  iRegIdst_rule,
  /*  628 */  iRegIdst_rule,
  /*  629 */  0,
  /*  630 */  iRegLdst_rule,
  /*  631 */  iRegLdst_rule,
  /*  632 */  iRegIdst_rule,
  /*  633 */  iRegLdst_rule,
  /*  634 */  iRegIdst_rule,
  /*  635 */  iRegLdst_rule,
  /*  636 */  iRegIdst_rule,
  /*  637 */  iRegIdst_rule,
  /*  638 */  iRegIdst_rule,
  /*  639 */  iRegIdst_rule,
  /*  640 */  iRegIdst_rule,
  /*  641 */  regF_rule,
  /*  642 */  regD_rule,
  /*  643 */  regF_rule,
  /*  644 */  regD_rule,
  /*  645 */  regF_rule,
  /*  646 */  regD_rule,
  /*  647 */  regF_rule,
  /*  648 */  regD_rule,
  /*  649 */  regD_rule,
  /*  650 */  regF_rule,
  /*  651 */  regF_rule,
  /*  652 */  regD_rule,
  /*  653 */  regF_rule,
  /*  654 */  regF_rule,
  /*  655 */  regD_rule,
  /*  656 */  regD_rule,
  /*  657 */  regF_rule,
  /*  658 */  regF_rule,
  /*  659 */  regD_rule,
  /*  660 */  regD_rule,
  /*  661 */  regF_rule,
  /*  662 */  regD_rule,
  /*  663 */  iRegIdst_rule,
  /*  664 */  iRegIdst_rule,
  /*  665 */  iRegIdst_rule,
  /*  666 */  iRegIdst_rule,
  /*  667 */  iRegIdst_rule,
  /*  668 */  iRegIdst_rule,
  /*  669 */  iRegLdst_rule,
  /*  670 */  iRegLdst_rule,
  /*  671 */  iRegLdst_rule,
  /*  672 */  iRegLdst_rule,
  /*  673 */  iRegIdst_rule,
  /*  674 */  iRegIdst_rule,
  /*  675 */  0,
  /*  676 */  iRegIdst_rule,
  /*  677 */  iRegIdst_rule,
  /*  678 */  iRegIdst_rule,
  /*  679 */  iRegIdst_rule,
  /*  680 */  iRegIdst_rule,
  /*  681 */  iRegLdst_rule,
  /*  682 */  iRegIdst_rule,
  /*  683 */  iRegLdst_rule,
  /*  684 */  iRegIdst_rule,
  /*  685 */  0,
  /*  686 */  iRegIdst_rule,
  /*  687 */  iRegIdst_rule,
  /*  688 */  iRegIdst_rule,
  /*  689 */  iRegIdst_rule,
  /*  690 */  iRegIdst_rule,
  /*  691 */  iRegLdst_rule,
  /*  692 */  iRegIdst_rule,
  /*  693 */  iRegLdst_rule,
  /*  694 */  iRegIdst_rule,
  /*  695 */  iRegLdst_rule,
  /*  696 */  iRegIdst_rule,
  /*  697 */  iRegIdst_rule,
  /*  698 */  0,
  /*  699 */  stackSlotI_rule,
  /*  700 */  stackSlotF_rule,
  /*  701 */  0,
  /*  702 */  stackSlotL_rule,
  /*  703 */  stackSlotD_rule,
  /*  704 */  iRegIdst_rule,
  /*  705 */  iRegIdst_rule,
  /*  706 */  iRegIdst_rule,
  /*  707 */  iRegIdst_rule,
  /*  708 */  iRegIdst_rule,
  /*  709 */  iRegIdst_rule,
  /*  710 */  iRegIdst_rule,
  /*  711 */  iRegIdst_rule,
  /*  712 */  iRegIdst_rule,
  /*  713 */  iRegIdst_rule,
  /*  714 */  iRegIdst_rule,
  /*  715 */  iRegLdst_rule,
  /*  716 */  iRegIdst_rule,
  /*  717 */  0,
  /*  718 */  0,
  /*  719 */  0,
  /*  720 */  0,
  /*  721 */  iRegIdst_rule,
  /*  722 */  iRegIdst_rule,
  /*  723 */  iRegIdst_rule,
  /*  724 */  iRegIdst_rule,
  /*  725 */  iRegLdst_rule,
  /*  726 */  iRegLdst_rule,
  /*  727 */  iRegLdst_rule,
  /*  728 */  0,
  /*  729 */  0,
  /*  730 */  0,
  /*  731 */  0,
  /*  732 */  iRegLdst_rule,
  /*  733 */  iRegLdst_rule,
  /*  734 */  iRegLdst_rule,
  /*  735 */  iRegLdst_rule,
  /*  736 */  regF_rule,
  /*  737 */  regF_rule,
  /*  738 */  regF_rule,
  /*  739 */  regF_rule,
  /*  740 */  regF_rule,
  /*  741 */  regF_rule,
  /*  742 */  regD_rule,
  /*  743 */  regD_rule,
  /*  744 */  regD_rule,
  /*  745 */  regD_rule,
  /*  746 */  regD_rule,
  /*  747 */  iRegIdst_rule,
  /*  748 */  Universe_rule,
  /*  749 */  Universe_rule,
  /*  750 */  Universe_rule,
  /*  751 */  Universe_rule,
  /*  752 */  Universe_rule,
  /*  753 */  iRegIdst_rule,
  /*  754 */  iRegIdst_rule,
  /*  755 */  iRegIdst_rule,
  /*  756 */  iRegIdst_rule,
  /*  757 */  iRegIdst_rule,
  /*  758 */  iRegIdst_rule,
  /*  759 */  iRegIdst_rule,
  /*  760 */  Universe_rule,
  /*  761 */  Universe_rule,
  /*  762 */  Universe_rule,
  /*  763 */  Universe_rule,
  /*  764 */  Universe_rule,
  /*  765 */  iRegPdst_rule,
  /*  766 */  iRegPdst_rule,
  /*  767 */  iRegLdst_rule,
  /*  768 */  Universe_rule,
  /*  769 */  Universe_rule,
  /*  770 */  Universe_rule,
  /*  771 */  iRegIdst_rule,
  /*  772 */  iRegIdst_rule,
  /*  773 */  iRegIdst_rule,
  /*  774 */  iRegIdst_rule,
  /*  775 */  iRegIdst_rule,
  /*  776 */  iRegIdst_rule,
  /*  777 */  iRegIdst_rule,
  /*  778 */  iRegIdst_rule,
  /*  779 */  iRegIdst_rule,
  /*  780 */  iRegIdst_rule,
  /*  781 */  iRegIdst_rule,
  /*  782 */  iRegIdst_rule,
  /*  783 */  iRegIdst_rule,
  /*  784 */  iRegIdst_rule,
  /*  785 */  iRegIdst_rule,
  /*  786 */  iRegIdst_rule,
  /*  787 */  iRegIdst_rule,
  /*  788 */  iRegIdst_rule,
  /*  789 */  iRegIdst_rule,
  /*  790 */  iRegIdst_rule,
  /*  791 */  iRegIdst_rule,
  /*  792 */  iRegIdst_rule,
  /*  793 */  iRegIdst_rule,
  /*  794 */  Universe_rule,
  /*  795 */  iRegIdst_rule,
  /*  796 */  iRegIdst_rule,
  /*  797 */  iRegIdst_rule,
  /*  798 */  iRegIdst_rule,
  /*  799 */  iRegIdst_rule,
  /*  800 */  iRegIdst_rule,
  /*  801 */  iRegIdst_rule,
  /*  802 */  0,
  /*  803 */  0,
  /*  804 */  iRegIdst_rule,
  /*  805 */  iRegIdst_rule,
  /*  806 */  iRegIdst_rule,
  /*  807 */  iRegLdst_rule,
  /*  808 */  iRegLdst_rule,
  /*  809 */  iRegLdst_rule,
  /*  810 */  iRegIdst_rule,
  /*  811 */  iRegIdst_rule,
  /*  812 */  iRegIdst_rule,
  /*  813 */  iRegIdst_rule,
  /*  814 */  iRegIdst_rule,
  /*  815 */  iRegIdst_rule,
  /*  816 */  iRegLdst_rule,
  /*  817 */  iRegLdst_rule,
  /*  818 */  iRegIdst_rule,
  /*  819 */  iRegIdst_rule,
  /*  820 */  iRegIdst_rule,
  /*  821 */  iRegIdst_rule,
  /*  822 */  Universe_rule,
  /*  823 */  Universe_rule,
  /*  824 */  Universe_rule,
  /*  825 */  Universe_rule,
  /*  826 */  0,
  /*  827 */  vecX_rule,
  /*  828 */  vecX_rule,
  /*  829 */  vecX_rule,
  /*  830 */  vecX_rule,
  /*  831 */  vecX_rule,
  /*  832 */  vecX_rule,
  /*  833 */  vecX_rule,
  /*  834 */  vecX_rule,
  /*  835 */  vecX_rule,
  /*  836 */  vecX_rule,
  /*  837 */  vecX_rule,
  /*  838 */  vecX_rule,
  /*  839 */  vecX_rule,
  /*  840 */  vecX_rule,
  /*  841 */  vecX_rule,
  /*  842 */  vecX_rule,
  /*  843 */  vecX_rule,
  /*  844 */  vecX_rule,
  /*  845 */  regD_rule,
  /*  846 */  vecX_rule,
  /*  847 */  vecX_rule,
  /*  848 */  vecX_rule,
  /*  849 */  vecX_rule,
  /*  850 */  vecX_rule,
  /*  851 */  vecX_rule,
  /*  852 */  vecX_rule,
  /*  853 */  vecX_rule,
  /*  854 */  vecX_rule,
  /*  855 */  vecX_rule,
  /*  856 */  0,
  /*  857 */  0,
  /*  858 */  Universe_rule,
  /*  859 */  Universe_rule,
  /*  860 */  Universe_rule,
  /*  861 */  Universe_rule,
  /*  862 */  Universe_rule,
  /*  863 */  Universe_rule,
  /*  864 */  Universe_rule,
  /*  865 */  Universe_rule,
  /*  866 */  Universe_rule,
  /*  867 */  Universe_rule,
  /*  868 */  Universe_rule,
  /*  869 */  Universe_rule,
  /*  870 */  rarg1RegP_rule,
  /*  871 */  Universe_rule,
  /*  872 */  Universe_rule,
  /*  873 */  0,
  /*  874 */  0,
  /*  875 */  0,
  /*  876 */  0,
  /*  877 */  0,
  /*  878 */  0,
  /*  879 */  0,
  /*  880 */  Universe_rule,
  /*  881 */  Universe_rule,
  /*  882 */  Universe_rule,
  /*  883 */  iRegIdst_rule,
  /*  884 */  iRegIdst_rule,
  /*  885 */  iRegIdst_rule,
  /*  886 */  iRegIdst_rule,
  /*  887 */  iRegIdst_rule,
  /*  888 */  iRegIdst_rule,
  /*  889 */  iRegIdst_rule,
  /*  890 */  iRegIdst_rule,
  /*  891 */  iRegPdst_rule,
  /*  892 */  iRegNdst_rule,
  /*  893 */  iRegPdst_rule,
  /*  894 */  iRegNdst_rule,
  /*  895 */  iRegPdst_rule,
  /*  896 */  iRegPdst_rule,
  /*  897 */  iRegIdst_rule,
  /*  898 */  iRegIdst_rule,
  /*  899 */  iRegIdst_rule,
  /*  900 */  iRegIdst_rule,
  /*  901 */  iRegPdst_rule,
  /*  902 */  iRegPdst_rule,
  /*  903 */  iRegPdst_rule,
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
  /*   79 */  iRegLsrc_rule,
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
  /*   91 */  iRegPsrc_rule,
  /*   92 */  iRegNsrc_rule,
  /*   93 */  iRegNsrc_rule,
  /*   94 */  0,
  /*   95 */  iRegPsrc_rule,
  /*   96 */  iRegPsrc_rule,
  /*   97 */  iRegNsrc_rule,
  /*   98 */  iRegNsrc_rule,
  /*   99 */  _DecodeN_iRegNsrc__rule,
  /*  100 */  _DecodeNKlass_iRegNsrc__rule,
  /*  101 */  _DecodeN_iRegNsrc__rule,
  /*  102 */  _DecodeNKlass_iRegNsrc__rule,
  /*  103 */  0,
  /*  104 */  0,
  /*  105 */  0,
  /*  106 */  0,
  /*  107 */  0,
  /*  108 */  0,
  // last operand
  /*  109 */  0,
  /*  110 */  0,
  /*  111 */  0,
  /*  112 */  0,
  /*  113 */  0,
  /*  114 */  0,
  // last operand class
  /*  115 */  iRegNsrc_rule,
  /*  116 */  iRegNsrc_rule,
  /*  117 */  memory_rule,
  /*  118 */  memory_rule,
  /*  119 */  memory_rule,
  /*  120 */  _LoadI_memory__rule,
  /*  121 */  memoryAlg4_rule,
  /*  122 */  memory_rule,
  /*  123 */  memory_rule,
  /*  124 */  memoryAlg4_rule,
  /*  125 */  indirectMemory_rule,
  /*  126 */  iRegLsrc_rule,
  /*  127 */  flagsRegSrc_rule,
  /*  128 */  _DecodeN_iRegNsrc__rule,
  /*  129 */  iRegLsrc_rule,
  /*  130 */  iRegLsrc_rule,
  /*  131 */  iRegLsrc_rule,
  /*  132 */  cmpOp_rule,
  /*  133 */  iRegIdst_rule,
  /*  134 */  iRegIdst_rule,
  /*  135 */  iRegLdst_rule,
  /*  136 */  iRegLdst_rule,
  /*  137 */  iRegNdst_rule,
  /*  138 */  iRegNdst_rule,
  /*  139 */  iRegPdst_rule,
  /*  140 */  iRegPdst_rule,
  /*  141 */  iRegPdst_rule,
  /*  142 */  regF_rule,
  /*  143 */  regD_rule,
  /*  144 */  iRegIsrc_rule,
  /*  145 */  iRegIsrc_rule,
  /*  146 */  iRegNsrc_rule,
  /*  147 */  iRegLsrc_rule,
  /*  148 */  iRegPsrc_rule,
  /*  149 */  iRegIsrc_rule,
  /*  150 */  _AddI_iRegIsrc_iRegIsrc_rule,
  /*  151 */  iRegIsrc_rule,
  /*  152 */  iRegLsrc_rule,
  /*  153 */  _AddL_iRegLsrc_iRegLsrc_rule,
  /*  154 */  iRegLsrc_rule,
  /*  155 */  iRegLsrc_rule,
  /*  156 */  immL_0_rule,
  /*  157 */  iRegIsrc_rule,
  /*  158 */  iRegIsrc_rule,
  /*  159 */  _RShiftI_iRegIsrc_uimmI5_rule,
  /*  160 */  iRegIsrc_rule,
  /*  161 */  iRegLsrc_rule,
  /*  162 */  iRegLsrc_rule,
  /*  163 */  iRegP_N2P_rule,
  /*  164 */  iRegIsrc_rule,
  /*  165 */  iRegIsrc_rule,
  /*  166 */  iRegIsrc_rule,
  /*  167 */  regF_rule,
  /*  168 */  regD_rule,
  /*  169 */  regF_rule,
  /*  170 */  _NegF_regF__rule,
  /*  171 */  regF_rule,
  /*  172 */  regD_rule,
  /*  173 */  _NegD_regD__rule,
  /*  174 */  regD_rule,
  /*  175 */  iRegLsrc_rule,
  /*  176 */  iRegIsrc_rule,
  /*  177 */  _OrI_iRegIsrc_iRegIsrc_rule,
  /*  178 */  iRegIsrc_rule,
  /*  179 */  iRegLsrc_rule,
  /*  180 */  iRegIsrc_rule,
  /*  181 */  _XorI_iRegIsrc_iRegIsrc_rule,
  /*  182 */  iRegIsrc_rule,
  /*  183 */  iRegLsrc_rule,
  /*  184 */  iRegIsrc_rule,
  /*  185 */  iRegIsrc_rule,
  /*  186 */  iRegIsrc_rule,
  /*  187 */  iRegP_N2P_rule,
  /*  188 */  iRegIsrc_rule,
  /*  189 */  iRegIsrc_rule,
  /*  190 */  iRegIsrc_rule,
  /*  191 */  iRegLsrc_rule,
  /*  192 */  iRegLsrc_rule,
  /*  193 */  iRegIsrc_rule,
  /*  194 */  iRegIsrc_rule,
  /*  195 */  iRegNsrc_rule,
  /*  196 */  iRegP_N2P_rule,
  /*  197 */  iRegPsrc_rule,
  /*  198 */  _CastP2X_iRegPsrc__rule,
  /*  199 */  rarg1RegP_rule,
  /*  200 */  rarg2RegP_rule,
  /*  201 */  rarg1RegP_rule,
  /*  202 */  iRegPsrc_rule,
  /*  203 */  immP_rule,
  /*  204 */  _AddP_immP_immL_rule,
  /*  205 */  rscratch2RegP_rule,
  /*  206 */  iRegPsrc_rule,
  /*  207 */  iRegPsrc_rule,
  /*  208 */  iRegPsrc_rule,
  /*  209 */  rarg2RegP_rule,
  /*  210 */  indirect_rule,
  /*  211 */  indirect_rule,
  /*  212 */  indirect_rule,
  /*  213 */  indirect_rule,
  /*  214 */  iRegIsrc_rule,
  /*  215 */  iRegLsrc_rule,
  /*  216 */  iRegIsrc_rule,
  /*  217 */  iRegIsrc_rule,
  /*  218 */  vecX_rule,
  /*  219 */  vecX_rule,
  /*  220 */  _NegVF_vecX__rule,
  /*  221 */  vecX_rule,
  /*  222 */  vecX_rule,
  /*  223 */  _NegVD_vecX__rule,
  /*  224 */  vecX_rule,
  // last internally defined operand
  /*  225 */  iRegIsrc_rule,
  /*  226 */  iRegLsrc_rule,
  /*  227 */  immI16_rule,
  /*  228 */  immIhi16_rule,
  /*  229 */  immI32_rule,
  /*  230 */  immI_rule,
  /*  231 */  immL16_rule,
  /*  232 */  immL32hi16_rule,
  /*  233 */  immL32_rule,
  /*  234 */  immL34_rule,
  /*  235 */  immLhighest16_rule,
  /*  236 */  immL_rule,
  /*  237 */  immN_0_rule,
  /*  238 */  immN_rule,
  /*  239 */  immNKlass_NM_rule,
  /*  240 */  immNKlass_NM_rule,
  /*  241 */  immNKlass_NM_rule,
  /*  242 */  immNKlass_rule,
  /*  243 */  immP_0or1_rule,
  /*  244 */  immP_NM_rule,
  /*  245 */  immP_NM_rule,
  /*  246 */  immP_rule,
  /*  247 */  immF_rule,
  /*  248 */  immD_rule,
  /*  249 */  stackSlotI_rule,
  /*  250 */  stackSlotL_rule,
  /*  251 */  0,
  /*  252 */  _LoadP_memoryAlg4__rule,
  /*  253 */  0,
  /*  254 */  0,
  /*  255 */  0,
  /*  256 */  iRegLdst_rule,
  /*  257 */  vecX_rule,
  /*  258 */  0,
  /*  259 */  iRegIsrc_rule,
  /*  260 */  0,
  /*  261 */  0,
  /*  262 */  iRegLsrc_rule,
  /*  263 */  regF_rule,
  /*  264 */  regD_rule,
  /*  265 */  regF_rule,
  /*  266 */  regD_rule,
  /*  267 */  _AbsF_regF__rule,
  /*  268 */  _AbsD_regD__rule,
  /*  269 */  regD_rule,
  /*  270 */  regF_rule,
  /*  271 */  iRegLsrc_rule,
  /*  272 */  0,
  /*  273 */  stackSlotF_rule,
  /*  274 */  stackSlotI_rule,
  /*  275 */  stackSlotD_rule,
  /*  276 */  stackSlotL_rule,
  /*  277 */  0,
  /*  278 */  iRegLsrc_rule,
  /*  279 */  iRegP_N2P_rule,
  /*  280 */  iRegPdst_rule,
  /*  281 */  iRegIdst_rule,
  /*  282 */  iRegLdst_rule,
  /*  283 */  regF_rule,
  /*  284 */  regD_rule,
  /*  285 */  iRegLdst_rule,
  /*  286 */  vecX_rule,
  /*  287 */  iRegPdst_rule,
  /*  288 */  iRegIsrc_rule,
  /*  289 */  iRegP_N2P_rule,
  /*  290 */  0,
  /*  291 */  0,
  /*  292 */  0,
  /*  293 */  0,
  /*  294 */  0,
  /*  295 */  0,
  /*  296 */  0,
  /*  297 */  iRegIsrc_rule,
  /*  298 */  iRegIsrc_rule,
  /*  299 */  _AndI_iRegIsrc_uimmI16_rule,
  /*  300 */  iRegLsrc_rule,
  /*  301 */  iRegLsrc_rule,
  /*  302 */  iRegLsrc_rule,
  /*  303 */  iRegLsrc_rule,
  /*  304 */  _AndL_iRegLsrc_iRegLsrc_rule,
  /*  305 */  _AndL_iRegLsrc_uimmL16_rule,
  /*  306 */  iRegIsrc_rule,
  /*  307 */  iRegIsrc_rule,
  /*  308 */  iRegNsrc_rule,
  /*  309 */  iRegNsrc_rule,
  /*  310 */  iRegP_N2P_rule,
  /*  311 */  iRegP_N2P_rule,
  /*  312 */  iRegPsrc_rule,
  /*  313 */  regF_rule,
  /*  314 */  0,
  /*  315 */  regF_rule,
  /*  316 */  regD_rule,
  /*  317 */  regD_rule,
  /*  318 */  iRegPdst_rule,
  /*  319 */  iRegPdst_rule,
  /*  320 */  iRegPdst_rule,
  /*  321 */  iRegPdst_rule,
  /*  322 */  iRegIsrc_rule,
  /*  323 */  iRegLsrc_rule,
  /*  324 */  iRegIsrc_rule,
  /*  325 */  iRegLsrc_rule,
  /*  326 */  0,
  /*  327 */  iRegIsrc_rule,
  /*  328 */  iRegIsrc_rule,
  /*  329 */  iRegLsrc_rule,
  /*  330 */  iRegLsrc_rule,
  /*  331 */  0,
  /*  332 */  0,
  /*  333 */  0,
  /*  334 */  0,
  /*  335 */  0,
  /*  336 */  iRegIsrc_rule,
  /*  337 */  immI_0_rule,
  /*  338 */  immI_minus1_rule,
  /*  339 */  iRegIsrc_rule,
  /*  340 */  immI_0_rule,
  /*  341 */  immI_minus1_rule,
  /*  342 */  iRegIsrc_rule,
  /*  343 */  immI_0_rule,
  /*  344 */  immI_minus1_rule,
  /*  345 */  iRegIsrc_rule,
  /*  346 */  immI_0_rule,
  /*  347 */  immI_minus1_rule,
  /*  348 */  iRegIsrc_rule,
  /*  349 */  immI_0_rule,
  /*  350 */  immI_minus1_rule,
  /*  351 */  iRegIsrc_rule,
  /*  352 */  immI_0_rule,
  /*  353 */  immI_minus1_rule,
  /*  354 */  regF_rule,
  /*  355 */  immF_rule,
  /*  356 */  immF_0_rule,
  /*  357 */  vecX_rule,
  /*  358 */  vecX_rule,
  /*  359 */  vecX_rule,
  /*  360 */  vecX_rule,
  /*  361 */  vecX_rule,
  /*  362 */  vecX_rule,
  /*  363 */  vecX_rule,
  /*  364 */  iRegLsrc_rule,
  /*  365 */  iRegLsrc_rule,
  /*  366 */  immL_0_rule,
  /*  367 */  iRegLsrc_rule,
  /*  368 */  regF_rule,
  /*  369 */  immF_0_rule,
  /*  370 */  regD_rule,
  /*  371 */  immD_0_rule,
  /*  372 */  0,
  /*  373 */  iRegLsrc_rule,
  /*  374 */  immI_0_rule,
  /*  375 */  immI_minus1_rule,
  /*  376 */  0,
  /*  377 */  0,
  /*  378 */  indirectMemory_rule,
  /*  379 */  indirectMemory_rule,
  /*  380 */  indirectMemory_rule,
  /*  381 */  indirectMemory_rule,
  /*  382 */  indOffset16_rule,
  /*  383 */  indOffset16_rule,
  /*  384 */  indOffset16_rule,
  /*  385 */  indOffset16_rule,
  /*  386 */  memory_rule,
  /*  387 */  memory_rule,
  /*  388 */  _LoadUB_memory__rule,
  /*  389 */  _LoadUB_memory__rule,
  /*  390 */  memory_rule,
  /*  391 */  memory_rule,
  /*  392 */  memory_rule,
  /*  393 */  memory_rule,
  /*  394 */  _LoadUS_memory__rule,
  /*  395 */  _LoadUS_memory__rule,
  /*  396 */  memory_rule,
  /*  397 */  memory_rule,
  /*  398 */  _ConvI2L__LoadI_memory___rule,
  /*  399 */  _LoadI_memoryAlg4__rule,
  /*  400 */  _LoadI_memoryAlg4__rule,
  /*  401 */  memoryAlg4_rule,
  /*  402 */  memoryAlg4_rule,
  /*  403 */  memoryAlg4_rule,
  /*  404 */  memoryAlg4_rule,
  /*  405 */  indirect_rule,
  /*  406 */  memory_rule,
  /*  407 */  memory_rule,
  /*  408 */  memory_rule,
  /*  409 */  _LoadN_memory__rule,
  /*  410 */  _LoadNKlass_memory__rule,
  /*  411 */  memoryAlg4_rule,
  /*  412 */  memoryAlg4_rule,
  /*  413 */  memory_rule,
  /*  414 */  memoryAlg4_rule,
  /*  415 */  memory_rule,
  /*  416 */  memory_rule,
  /*  417 */  memory_rule,
  /*  418 */  memory_rule,
  /*  419 */  memory_rule,
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
  /*  434 */  _AddP_indirectMemory_iRegLsrc_rule,
  /*  435 */  indirectMemory_rule,
  /*  436 */  _AddP_indirectMemory_iRegLsrc_rule,
  /*  437 */  indirectMemory_rule,
  /*  438 */  memory_rule,
  /*  439 */  memory_rule,
  /*  440 */  memory_rule,
  /*  441 */  memory_rule,
  /*  442 */  memoryAlg4_rule,
  /*  443 */  memoryAlg4_rule,
  /*  444 */  indirect_rule,
  /*  445 */  memory_rule,
  /*  446 */  memory_rule,
  /*  447 */  memoryAlg4_rule,
  /*  448 */  memory_rule,
  /*  449 */  memory_rule,
  /*  450 */  memory_rule,
  /*  451 */  iRegNsrc_rule,
  /*  452 */  iRegPdst_rule,
  /*  453 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  454 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  455 */  iRegPsrc_rule,
  /*  456 */  iRegPsrc_rule,
  /*  457 */  iRegPsrc_rule,
  /*  458 */  iRegPsrc_rule,
  /*  459 */  iRegPsrc_rule,
  /*  460 */  iRegPsrc_rule,
  /*  461 */  iRegPdst_rule,
  /*  462 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  463 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  464 */  iRegNsrc_rule,
  /*  465 */  iRegNsrc_rule,
  /*  466 */  iRegNsrc_rule,
  /*  467 */  iRegNsrc_rule,
  /*  468 */  iRegNsrc_rule,
  /*  469 */  iRegNsrc_rule,
  /*  470 */  iRegNsrc_rule,
  /*  471 */  _CastP2X__DecodeN_iRegNsrc___rule,
  /*  472 */  iRegNsrc_rule,
  /*  473 */  _Binary_iRegLsrc_iRegPdst_rule,
  /*  474 */  iRegPsrc_rule,
  /*  475 */  _Binary_iRegLsrc_iRegPsrc_rule,
  /*  476 */  iRegPsrc_rule,
  /*  477 */  iRegPsrc_rule,
  /*  478 */  _Binary_iRegLsrc_iRegPdst_rule,
  /*  479 */  _Binary_iRegLsrc_iRegNsrc_rule,
  /*  480 */  iRegNsrc_rule,
  /*  481 */  0,
  /*  482 */  0,
  /*  483 */  0,
  /*  484 */  0,
  /*  485 */  0,
  /*  486 */  0,
  /*  487 */  0,
  /*  488 */  0,
  /*  489 */  0,
  /*  490 */  0,
  /*  491 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  492 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  493 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  494 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  495 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  496 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  497 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  498 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  499 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  500 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  501 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  502 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  503 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  504 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  505 */  iRegPdst_rule,
  /*  506 */  rarg3RegP_rule,
  /*  507 */  iRegPdst_rule,
  /*  508 */  rarg3RegP_rule,
  /*  509 */  iRegPdst_rule,
  /*  510 */  iRegPdst_rule,
  /*  511 */  iRegPdst_rule,
  /*  512 */  iRegPdst_rule,
  /*  513 */  iRegPdst_rule,
  /*  514 */  rarg3RegP_rule,
  /*  515 */  iRegPdst_rule,
  /*  516 */  rarg3RegP_rule,
  /*  517 */  iRegPdst_rule,
  /*  518 */  rarg3RegP_rule,
  /*  519 */  iRegPdst_rule,
  /*  520 */  rarg3RegP_rule,
  /*  521 */  iRegPdst_rule,
  /*  522 */  iRegPdst_rule,
  /*  523 */  iRegPdst_rule,
  /*  524 */  iRegPdst_rule,
  /*  525 */  iRegPdst_rule,
  /*  526 */  iRegPdst_rule,
  /*  527 */  iRegPdst_rule,
  /*  528 */  iRegPdst_rule,
  /*  529 */  iRegPdst_rule,
  /*  530 */  rarg3RegP_rule,
  /*  531 */  iRegPdst_rule,
  /*  532 */  rarg3RegP_rule,
  /*  533 */  iRegPdst_rule,
  /*  534 */  rarg3RegP_rule,
  /*  535 */  iRegPdst_rule,
  /*  536 */  rarg3RegP_rule,
  /*  537 */  iRegPdst_rule,
  /*  538 */  iRegPdst_rule,
  /*  539 */  iRegPdst_rule,
  /*  540 */  iRegPdst_rule,
  /*  541 */  iRegPdst_rule,
  /*  542 */  iRegPdst_rule,
  /*  543 */  iRegPdst_rule,
  /*  544 */  iRegPdst_rule,
  /*  545 */  iRegPdst_rule,
  /*  546 */  rarg3RegP_rule,
  /*  547 */  iRegPdst_rule,
  /*  548 */  rarg3RegP_rule,
  /*  549 */  iRegPdst_rule,
  /*  550 */  iRegPdst_rule,
  /*  551 */  iRegPdst_rule,
  /*  552 */  rarg3RegP_rule,
  /*  553 */  iRegPdst_rule,
  /*  554 */  rarg3RegP_rule,
  /*  555 */  iRegPdst_rule,
  /*  556 */  iRegPdst_rule,
  /*  557 */  iRegPdst_rule,
  /*  558 */  iRegPdst_rule,
  /*  559 */  iRegIsrc_iRegL2Isrc_rule,
  /*  560 */  0,
  /*  561 */  _AddI__AddI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  562 */  iRegIsrc_rule,
  /*  563 */  _AddI_iRegIsrc__AddI_iRegIsrc_iRegIsrc_rule,
  /*  564 */  iRegIsrc_rule,
  /*  565 */  iRegIsrc_rule,
  /*  566 */  iRegIsrc_rule,
  /*  567 */  iRegIsrc_rule,
  /*  568 */  iRegLsrc_rule,
  /*  569 */  0,
  /*  570 */  _AddL__AddL_iRegLsrc_iRegLsrc_iRegLsrc_rule,
  /*  571 */  iRegLsrc_rule,
  /*  572 */  _AddL_iRegLsrc__AddL_iRegLsrc_iRegLsrc_rule,
  /*  573 */  iRegLsrc_rule,
  /*  574 */  _AddL_iRegLsrc_iRegLsrc_rule,
  /*  575 */  iRegLsrc_rule,
  /*  576 */  iRegLsrc_rule,
  /*  577 */  iRegLsrc_rule,
  /*  578 */  iRegP_N2P_rule,
  /*  579 */  iRegP_N2P_rule,
  /*  580 */  iRegP_N2P_rule,
  /*  581 */  iRegP_N2P_rule,
  /*  582 */  iRegIsrc_rule,
  /*  583 */  immI16_rule,
  /*  584 */  immI_0_rule,
  /*  585 */  iRegLsrc_rule,
  /*  586 */  _SubL_iRegLsrc_iRegLsrc_rule,
  /*  587 */  immL_0_rule,
  /*  588 */  _SubL_immL_0_iRegLsrc_rule,
  /*  589 */  iRegIsrc_rule,
  /*  590 */  iRegIsrc_rule,
  /*  591 */  iRegLsrc_rule,
  /*  592 */  iRegLsrc_rule,
  /*  593 */  iRegLsrc_rule,
  /*  594 */  iRegIsrc_rule,
  /*  595 */  iRegIsrc_rule,
  /*  596 */  0,
  /*  597 */  iRegIsrc_rule,
  /*  598 */  iRegLsrc_rule,
  /*  599 */  iRegLsrc_rule,
  /*  600 */  0,
  /*  601 */  iRegLsrc_rule,
  /*  602 */  iRegIsrc_rule,
  /*  603 */  iRegLsrc_rule,
  /*  604 */  iRegIsrc_rule,
  /*  605 */  iRegIsrc_rule,
  /*  606 */  iRegLsrc_rule,
  /*  607 */  iRegLsrc_rule,
  /*  608 */  0,
  /*  609 */  0,
  /*  610 */  iRegIsrc_rule,
  /*  611 */  iRegIsrc_rule,
  /*  612 */  _AndI_iRegIsrc_immInegpow2_rule,
  /*  613 */  _AndI__RShiftI_iRegIsrc_uimmI5_immInegpow2_rule,
  /*  614 */  0,
  /*  615 */  iRegLsrc_rule,
  /*  616 */  iRegLsrc_rule,
  /*  617 */  _ConvI2L_iRegIsrc__rule,
  /*  618 */  _ConvI2L_iRegIsrc__rule,
  /*  619 */  0,
  /*  620 */  iRegIsrc_rule,
  /*  621 */  iRegIsrc_rule,
  /*  622 */  0,
  /*  623 */  iRegLsrc_rule,
  /*  624 */  iRegLsrc_rule,
  /*  625 */  _RShiftL_iRegLsrc_immI_rule,
  /*  626 */  0,
  /*  627 */  iRegIsrc_rule,
  /*  628 */  iRegIsrc_rule,
  /*  629 */  0,
  /*  630 */  iRegLsrc_rule,
  /*  631 */  iRegLsrc_rule,
  /*  632 */  _URShiftL_iRegLsrc_immI_rule,
  /*  633 */  _CastP2X_iRegP_N2P__rule,
  /*  634 */  _URShiftI_iRegIsrc_immI_rule,
  /*  635 */  _URShiftL_iRegLsrc_immI_rule,
  /*  636 */  _ConvI2L_iRegIsrc__rule,
  /*  637 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  638 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  639 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  640 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  641 */  regF_rule,
  /*  642 */  regD_rule,
  /*  643 */  regF_rule,
  /*  644 */  regD_rule,
  /*  645 */  regF_rule,
  /*  646 */  regD_rule,
  /*  647 */  regF_rule,
  /*  648 */  regD_rule,
  /*  649 */  regD_rule,
  /*  650 */  regF_rule,
  /*  651 */  regF_rule,
  /*  652 */  regD_rule,
  /*  653 */  regF_rule,
  /*  654 */  regF_rule,
  /*  655 */  regD_rule,
  /*  656 */  regD_rule,
  /*  657 */  _NegF_regF__rule,
  /*  658 */  _NegF_regF__rule,
  /*  659 */  _NegD_regD__rule,
  /*  660 */  _NegD_regD__rule,
  /*  661 */  _NegF_regF__rule,
  /*  662 */  _NegD_regD__rule,
  /*  663 */  iRegIsrc_rule,
  /*  664 */  iRegIsrc_rule,
  /*  665 */  iRegIsrc_rule,
  /*  666 */  iRegIsrc_rule,
  /*  667 */  iRegIsrc_rule,
  /*  668 */  iRegIsrc_rule,
  /*  669 */  iRegLsrc_rule,
  /*  670 */  iRegLsrc_rule,
  /*  671 */  iRegLsrc_rule,
  /*  672 */  iRegLsrc_rule,
  /*  673 */  _AndL_iRegLsrc_immLpow2minus1_rule,
  /*  674 */  iRegIsrc_rule,
  /*  675 */  0,
  /*  676 */  _OrI__OrI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  677 */  iRegIsrc_rule,
  /*  678 */  _OrI_iRegIsrc__OrI_iRegIsrc_iRegIsrc_rule,
  /*  679 */  iRegIsrc_rule,
  /*  680 */  iRegIsrc_rule,
  /*  681 */  iRegLsrc_rule,
  /*  682 */  _OrL_iRegLsrc_iRegLsrc_rule,
  /*  683 */  iRegLsrc_rule,
  /*  684 */  iRegIsrc_rule,
  /*  685 */  0,
  /*  686 */  _XorI__XorI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  687 */  iRegIsrc_rule,
  /*  688 */  _XorI_iRegIsrc__XorI_iRegIsrc_iRegIsrc_rule,
  /*  689 */  iRegIsrc_rule,
  /*  690 */  iRegIsrc_rule,
  /*  691 */  iRegLsrc_rule,
  /*  692 */  _XorL_iRegLsrc_iRegLsrc_rule,
  /*  693 */  iRegLsrc_rule,
  /*  694 */  iRegIsrc_rule,
  /*  695 */  iRegLsrc_rule,
  /*  696 */  _XorI_iRegIsrc_immI_minus1_rule,
  /*  697 */  iRegIsrc_rule,
  /*  698 */  0,
  /*  699 */  regF_rule,
  /*  700 */  iRegIsrc_rule,
  /*  701 */  0,
  /*  702 */  regD_rule,
  /*  703 */  iRegLsrc_rule,
  /*  704 */  iRegIsrc_rule,
  /*  705 */  _Conv2B_iRegIsrc__rule,
  /*  706 */  _Conv2B_iRegIsrc__rule,
  /*  707 */  _AndI_iRegIsrc_immIpowerOf2_rule,
  /*  708 */  iRegP_N2P_rule,
  /*  709 */  _Conv2B_iRegP_N2P__rule,
  /*  710 */  _Conv2B_iRegP_N2P__rule,
  /*  711 */  iRegIsrc_rule,
  /*  712 */  iRegIsrc_rule,
  /*  713 */  _LShiftI_iRegIsrc_immI_24_rule,
  /*  714 */  _LShiftI_iRegIsrc_immI_16_rule,
  /*  715 */  _ConvL2I_iRegLsrc__rule,
  /*  716 */  iRegLsrc_rule,
  /*  717 */  0,
  /*  718 */  0,
  /*  719 */  0,
  /*  720 */  0,
  /*  721 */  regD_rule,
  /*  722 */  regD_rule,
  /*  723 */  regF_rule,
  /*  724 */  regF_rule,
  /*  725 */  iRegIsrc_rule,
  /*  726 */  _ConvI2L_iRegIsrc__rule,
  /*  727 */  iRegLsrc_rule,
  /*  728 */  0,
  /*  729 */  0,
  /*  730 */  0,
  /*  731 */  0,
  /*  732 */  regF_rule,
  /*  733 */  regF_rule,
  /*  734 */  regD_rule,
  /*  735 */  regD_rule,
  /*  736 */  regD_rule,
  /*  737 */  iRegIsrc_rule,
  /*  738 */  iRegIsrc_rule,
  /*  739 */  iRegIsrc_rule,
  /*  740 */  iRegLsrc_rule,
  /*  741 */  iRegLsrc_rule,
  /*  742 */  iRegIsrc_rule,
  /*  743 */  iRegIsrc_rule,
  /*  744 */  stackSlotL_rule,
  /*  745 */  iRegLsrc_rule,
  /*  746 */  regF_rule,
  /*  747 */  iRegLsrc_rule,
  /*  748 */  cmpOp_rule,
  /*  749 */  cmpOp_rule,
  /*  750 */  cmpOp_rule,
  /*  751 */  cmpOp_rule,
  /*  752 */  cmpOp_rule,
  /*  753 */  regF_rule,
  /*  754 */  regD_rule,
  /*  755 */  iRegIsrc_rule,
  /*  756 */  iRegIsrc_rule,
  /*  757 */  iRegIsrc_rule,
  /*  758 */  iRegIsrc_rule,
  /*  759 */  iRegIsrc_rule,
  /*  760 */  0,
  /*  761 */  cmpOp_rule,
  /*  762 */  cmpOp_rule,
  /*  763 */  cmpOp_rule,
  /*  764 */  cmpOp_rule,
  /*  765 */  iRegP_N2P_rule,
  /*  766 */  _AndL__CastP2X_iRegPsrc__immLnegpow2_rule,
  /*  767 */  _CastP2X_iRegPsrc__rule,
  /*  768 */  immLmax30_rule,
  /*  769 */  immL_rule,
  /*  770 */  rarg1RegL_rule,
  /*  771 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  772 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  773 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  774 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  775 */  _Binary_rarg1RegP_rarg2RegP_rule,
  /*  776 */  _Binary_rarg1RegP_rarg2RegP_rule,
  /*  777 */  rarg1RegP_rule,
  /*  778 */  rarg1RegP_rule,
  /*  779 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  780 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  781 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  782 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  783 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  784 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  785 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  786 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  787 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  788 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  789 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  790 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  791 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  792 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  793 */  rarg1RegP_rule,
  /*  794 */  rarg1RegP_rule,
  /*  795 */  iRegPsrc_rule,
  /*  796 */  rarg1RegP_rule,
  /*  797 */  rarg1RegP_rule,
  /*  798 */  iRegIsrc_rule,
  /*  799 */  iRegIsrc_rule,
  /*  800 */  iRegIsrc_rule,
  /*  801 */  iRegIsrc_rule,
  /*  802 */  0,
  /*  803 */  0,
  /*  804 */  iRegIsrc_rule,
  /*  805 */  iRegIsrc_rule,
  /*  806 */  iRegIsrc_rule,
  /*  807 */  iRegLsrc_rule,
  /*  808 */  iRegLsrc_rule,
  /*  809 */  iRegLsrc_rule,
  /*  810 */  iRegIsrc_rule,
  /*  811 */  iRegIsrc_rule,
  /*  812 */  iRegIsrc_rule,
  /*  813 */  iRegIsrc_rule,
  /*  814 */  _LoadI_indirect__rule,
  /*  815 */  _LoadI_indirect__rule,
  /*  816 */  _LoadL_indirect__rule,
  /*  817 */  _LoadL_indirect__rule,
  /*  818 */  _LoadUS_indirect__rule,
  /*  819 */  _LoadUS_indirect__rule,
  /*  820 */  _LoadS_indirect__rule,
  /*  821 */  _LoadS_indirect__rule,
  /*  822 */  indirect_rule,
  /*  823 */  indirect_rule,
  /*  824 */  indirect_rule,
  /*  825 */  indirect_rule,
  /*  826 */  0,
  /*  827 */  vecX_rule,
  /*  828 */  vecX_rule,
  /*  829 */  vecX_rule,
  /*  830 */  vecX_rule,
  /*  831 */  vecX_rule,
  /*  832 */  vecX_rule,
  /*  833 */  vecX_rule,
  /*  834 */  vecX_rule,
  /*  835 */  vecX_rule,
  /*  836 */  vecX_rule,
  /*  837 */  vecX_rule,
  /*  838 */  vecX_rule,
  /*  839 */  vecX_rule,
  /*  840 */  vecX_rule,
  /*  841 */  vecX_rule,
  /*  842 */  vecX_rule,
  /*  843 */  vecX_rule,
  /*  844 */  vecX_rule,
  /*  845 */  regD_rule,
  /*  846 */  vecX_rule,
  /*  847 */  vecX_rule,
  /*  848 */  vecX_rule,
  /*  849 */  vecX_rule,
  /*  850 */  _NegVF_vecX__rule,
  /*  851 */  vecX_rule,
  /*  852 */  vecX_rule,
  /*  853 */  vecX_rule,
  /*  854 */  _NegVD_vecX__rule,
  /*  855 */  immF_rule,
  /*  856 */  0,
  /*  857 */  0,
  /*  858 */  iRegPdst_rule,
  /*  859 */  0,
  /*  860 */  0,
  /*  861 */  0,
  /*  862 */  0,
  /*  863 */  0,
  /*  864 */  0,
  /*  865 */  0,
  /*  866 */  0,
  /*  867 */  iRegPdstNoScratch_rule,
  /*  868 */  0,
  /*  869 */  iRegPdstNoScratch_rule,
  /*  870 */  0,
  /*  871 */  0,
  /*  872 */  0,
  /*  873 */  0,
  /*  874 */  0,
  /*  875 */  0,
  /*  876 */  0,
  /*  877 */  0,
  /*  878 */  0,
  /*  879 */  0,
  /*  880 */  indirect_rule,
  /*  881 */  0,
  /*  882 */  0,
  /*  883 */  indirect_rule,
  /*  884 */  indirect_rule,
  /*  885 */  indirect_rule,
  /*  886 */  indirect_rule,
  /*  887 */  indirect_rule,
  /*  888 */  indirect_rule,
  /*  889 */  indirect_rule,
  /*  890 */  indirect_rule,
  /*  891 */  indirect_rule,
  /*  892 */  indirect_rule,
  /*  893 */  indirect_rule,
  /*  894 */  indirect_rule,
  /*  895 */  memoryAlg4_rule,
  /*  896 */  memoryAlg4_rule,
  /*  897 */  iRegPdst_rule,
  /*  898 */  iRegPdst_rule,
  /*  899 */  iRegPdst_rule,
  /*  900 */  iRegPdst_rule,
  /*  901 */  iRegPdst_rule,
  /*  902 */  iRegPdst_rule,
  /*  903 */  iRegPdst_rule,
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
  /*   95 */  immL16_rule,
  /*   96 */  immL16Alg4_rule,
  /*   97 */  0,
  /*   98 */  0,
  /*   99 */  immL16_rule,
  /*  100 */  immL16_rule,
  /*  101 */  immL16Alg4_rule,
  /*  102 */  immL16Alg4_rule,
  /*  103 */  0,
  /*  104 */  0,
  /*  105 */  0,
  /*  106 */  0,
  /*  107 */  0,
  /*  108 */  0,
  // last operand
  /*  109 */  0,
  /*  110 */  0,
  /*  111 */  0,
  /*  112 */  0,
  /*  113 */  0,
  /*  114 */  0,
  // last operand class
  /*  115 */  0,
  /*  116 */  0,
  /*  117 */  0,
  /*  118 */  0,
  /*  119 */  0,
  /*  120 */  0,
  /*  121 */  0,
  /*  122 */  0,
  /*  123 */  0,
  /*  124 */  0,
  /*  125 */  iRegLsrc_rule,
  /*  126 */  0,
  /*  127 */  iRegPsrc_rule,
  /*  128 */  0,
  /*  129 */  iRegPdst_rule,
  /*  130 */  iRegPsrc_rule,
  /*  131 */  iRegNsrc_rule,
  /*  132 */  flagsRegSrc_rule,
  /*  133 */  iRegIsrc_rule,
  /*  134 */  immI16_rule,
  /*  135 */  iRegLsrc_rule,
  /*  136 */  immL16_rule,
  /*  137 */  iRegNsrc_rule,
  /*  138 */  immN_0_rule,
  /*  139 */  iRegPsrc_rule,
  /*  140 */  iRegP_N2P_rule,
  /*  141 */  immP_0_rule,
  /*  142 */  regF_rule,
  /*  143 */  regD_rule,
  /*  144 */  iRegIsrc_rule,
  /*  145 */  rarg4RegI_rule,
  /*  146 */  iRegNsrc_rule,
  /*  147 */  iRegLsrc_rule,
  /*  148 */  iRegPsrc_rule,
  /*  149 */  iRegIsrc_rule,
  /*  150 */  iRegIsrc_rule,
  /*  151 */  _AddI_iRegIsrc_iRegIsrc_rule,
  /*  152 */  iRegLsrc_rule,
  /*  153 */  iRegLsrc_rule,
  /*  154 */  _AddL_iRegLsrc_iRegLsrc_rule,
  /*  155 */  iRegLsrc_rule,
  /*  156 */  iRegLsrc_rule,
  /*  157 */  immInegpow2_rule,
  /*  158 */  uimmI5_rule,
  /*  159 */  immInegpow2_rule,
  /*  160 */  0,
  /*  161 */  immI_rule,
  /*  162 */  immI_rule,
  /*  163 */  0,
  /*  164 */  immI_rule,
  /*  165 */  immI8_rule,
  /*  166 */  immI8_rule,
  /*  167 */  0,
  /*  168 */  0,
  /*  169 */  0,
  /*  170 */  regF_rule,
  /*  171 */  _NegF_regF__rule,
  /*  172 */  0,
  /*  173 */  regD_rule,
  /*  174 */  _NegD_regD__rule,
  /*  175 */  immLpow2minus1_rule,
  /*  176 */  iRegIsrc_rule,
  /*  177 */  iRegIsrc_rule,
  /*  178 */  _OrI_iRegIsrc_iRegIsrc_rule,
  /*  179 */  iRegLsrc_rule,
  /*  180 */  iRegIsrc_rule,
  /*  181 */  iRegIsrc_rule,
  /*  182 */  _XorI_iRegIsrc_iRegIsrc_rule,
  /*  183 */  iRegLsrc_rule,
  /*  184 */  immI_minus1_rule,
  /*  185 */  0,
  /*  186 */  immIpowerOf2_rule,
  /*  187 */  0,
  /*  188 */  immI_24_rule,
  /*  189 */  immI_16_rule,
  /*  190 */  uimmI16_rule,
  /*  191 */  iRegLsrc_rule,
  /*  192 */  uimmL16_rule,
  /*  193 */  uimmI15_rule,
  /*  194 */  iRegIsrc_rule,
  /*  195 */  immN_0_rule,
  /*  196 */  immP_0_rule,
  /*  197 */  0,
  /*  198 */  immLnegpow2_rule,
  /*  199 */  rarg3RegI_rule,
  /*  200 */  rarg4RegI_rule,
  /*  201 */  rarg2RegP_rule,
  /*  202 */  iRegIsrc_rule,
  /*  203 */  immL_rule,
  /*  204 */  immI_1_rule,
  /*  205 */  immI_1_rule,
  /*  206 */  rscratch1RegI_rule,
  /*  207 */  uimmI15_rule,
  /*  208 */  rscratch2RegI_rule,
  /*  209 */  iRegIsrc_rule,
  /*  210 */  0,
  /*  211 */  0,
  /*  212 */  0,
  /*  213 */  0,
  /*  214 */  0,
  /*  215 */  0,
  /*  216 */  0,
  /*  217 */  0,
  /*  218 */  vecX_rule,
  /*  219 */  0,
  /*  220 */  vecX_rule,
  /*  221 */  _NegVF_vecX__rule,
  /*  222 */  0,
  /*  223 */  vecX_rule,
  /*  224 */  _NegVD_vecX__rule,
  // last internally defined operand
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
  /*  283 */  0,
  /*  284 */  0,
  /*  285 */  0,
  /*  286 */  0,
  /*  287 */  0,
  /*  288 */  0,
  /*  289 */  0,
  /*  290 */  0,
  /*  291 */  0,
  /*  292 */  0,
  /*  293 */  0,
  /*  294 */  0,
  /*  295 */  0,
  /*  296 */  0,
  /*  297 */  iRegIsrc_rule,
  /*  298 */  immI16_rule,
  /*  299 */  immI_0_rule,
  /*  300 */  iRegLsrc_rule,
  /*  301 */  immL16_rule,
  /*  302 */  iRegLsrc_rule,
  /*  303 */  uimmL16_rule,
  /*  304 */  immL_0_rule,
  /*  305 */  immL_0_rule,
  /*  306 */  iRegIsrc_rule,
  /*  307 */  uimmI16_rule,
  /*  308 */  iRegNsrc_rule,
  /*  309 */  immN_0_rule,
  /*  310 */  iRegP_N2P_rule,
  /*  311 */  immP_0or1_rule,
  /*  312 */  immL16_rule,
  /*  313 */  regF_rule,
  /*  314 */  0,
  /*  315 */  regF_rule,
  /*  316 */  regD_rule,
  /*  317 */  regD_rule,
  /*  318 */  iRegPdst_rule,
  /*  319 */  rarg2RegP_rule,
  /*  320 */  iRegPdst_rule,
  /*  321 */  iRegPdst_rule,
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
  /*  364 */  iRegLsrc_rule,
  /*  365 */  iRegLsrc_rule,
  /*  366 */  iRegLsrc_rule,
  /*  367 */  iRegLsrc_rule,
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
  /*  388 */  0,
  /*  389 */  0,
  /*  390 */  0,
  /*  391 */  0,
  /*  392 */  0,
  /*  393 */  0,
  /*  394 */  0,
  /*  395 */  0,
  /*  396 */  0,
  /*  397 */  0,
  /*  398 */  immL_32bits_rule,
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
  /*  438 */  iRegIsrc_rule,
  /*  439 */  iRegIsrc_rule,
  /*  440 */  iRegIsrc_rule,
  /*  441 */  _ConvL2I_iRegLsrc__rule,
  /*  442 */  iRegLsrc_rule,
  /*  443 */  iRegLsrc_rule,
  /*  444 */  vecX_rule,
  /*  445 */  iRegN_P2N_rule,
  /*  446 */  iRegN_P2N_rule,
  /*  447 */  iRegPsrc_rule,
  /*  448 */  regF_rule,
  /*  449 */  regD_rule,
  /*  450 */  immI_0_rule,
  /*  451 */  0,
  /*  452 */  0,
  /*  453 */  0,
  /*  454 */  0,
  /*  455 */  0,
  /*  456 */  0,
  /*  457 */  0,
  /*  458 */  0,
  /*  459 */  0,
  /*  460 */  0,
  /*  461 */  0,
  /*  462 */  0,
  /*  463 */  0,
  /*  464 */  0,
  /*  465 */  0,
  /*  466 */  0,
  /*  467 */  0,
  /*  468 */  0,
  /*  469 */  0,
  /*  470 */  0,
  /*  471 */  0,
  /*  472 */  0,
  /*  473 */  0,
  /*  474 */  0,
  /*  475 */  0,
  /*  476 */  0,
  /*  477 */  0,
  /*  478 */  0,
  /*  479 */  0,
  /*  480 */  0,
  /*  481 */  0,
  /*  482 */  0,
  /*  483 */  0,
  /*  484 */  0,
  /*  485 */  0,
  /*  486 */  0,
  /*  487 */  0,
  /*  488 */  0,
  /*  489 */  0,
  /*  490 */  0,
  /*  491 */  _Binary_iRegIdst_iRegIsrc_rule,
  /*  492 */  _Binary_iRegIdst_iRegIsrc_rule,
  /*  493 */  _Binary_iRegIdst_immI16_rule,
  /*  494 */  _Binary_iRegLdst_iRegLsrc_rule,
  /*  495 */  _Binary_iRegLdst_iRegLsrc_rule,
  /*  496 */  _Binary_iRegLdst_immL16_rule,
  /*  497 */  _Binary_iRegNdst_iRegNsrc_rule,
  /*  498 */  _Binary_iRegNdst_iRegNsrc_rule,
  /*  499 */  _Binary_iRegNdst_immN_0_rule,
  /*  500 */  _Binary_iRegPdst_iRegPsrc_rule,
  /*  501 */  _Binary_iRegPdst_iRegP_N2P_rule,
  /*  502 */  _Binary_iRegPdst_immP_0_rule,
  /*  503 */  _Binary_regF_regF_rule,
  /*  504 */  _Binary_regD_regD_rule,
  /*  505 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  506 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  507 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  508 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  509 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  510 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  511 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  512 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  513 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  514 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  515 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  516 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  517 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  518 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  519 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  520 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  521 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  522 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  523 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  524 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  525 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  526 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  527 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  528 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  529 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  530 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  531 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  532 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  533 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  534 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  535 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  536 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  537 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  538 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  539 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  540 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  541 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  542 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  543 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  544 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  545 */  iRegIsrc_rule,
  /*  546 */  iRegIsrc_rule,
  /*  547 */  iRegIsrc_rule,
  /*  548 */  iRegIsrc_rule,
  /*  549 */  iRegIsrc_rule,
  /*  550 */  iRegLsrc_rule,
  /*  551 */  iRegIsrc_rule,
  /*  552 */  iRegIsrc_rule,
  /*  553 */  iRegIsrc_rule,
  /*  554 */  iRegIsrc_rule,
  /*  555 */  iRegIsrc_rule,
  /*  556 */  iRegLsrc_rule,
  /*  557 */  iRegPsrc_rule,
  /*  558 */  iRegNsrc_rule,
  /*  559 */  iRegIsrc_iRegL2Isrc_rule,
  /*  560 */  0,
  /*  561 */  iRegIsrc_rule,
  /*  562 */  _AddI__AddI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  563 */  iRegIsrc_rule,
  /*  564 */  _AddI_iRegIsrc__AddI_iRegIsrc_iRegIsrc_rule,
  /*  565 */  immI16_rule,
  /*  566 */  immIhi16_rule,
  /*  567 */  immI32_rule,
  /*  568 */  iRegLsrc_rule,
  /*  569 */  0,
  /*  570 */  iRegLsrc_rule,
  /*  571 */  _AddL__AddL_iRegLsrc_iRegLsrc_iRegLsrc_rule,
  /*  572 */  iRegLsrc_rule,
  /*  573 */  _AddL_iRegLsrc__AddL_iRegLsrc_iRegLsrc_rule,
  /*  574 */  0,
  /*  575 */  immL16_rule,
  /*  576 */  immL32hi16_rule,
  /*  577 */  immL34_rule,
  /*  578 */  iRegLsrc_rule,
  /*  579 */  immL16_rule,
  /*  580 */  immL32hi16_rule,
  /*  581 */  immL34_rule,
  /*  582 */  iRegIsrc_rule,
  /*  583 */  iRegIsrc_rule,
  /*  584 */  iRegIsrc_rule,
  /*  585 */  iRegLsrc_rule,
  /*  586 */  0,
  /*  587 */  iRegLsrc_rule,
  /*  588 */  0,
  /*  589 */  iRegIsrc_rule,
  /*  590 */  immI16_rule,
  /*  591 */  iRegLsrc_rule,
  /*  592 */  iRegLsrc_rule,
  /*  593 */  immL16_rule,
  /*  594 */  immI_minus1_rule,
  /*  595 */  iRegIsrc_rule,
  /*  596 */  0,
  /*  597 */  iRegIsrc_rule,
  /*  598 */  immL_minus1_rule,
  /*  599 */  iRegLsrc_rule,
  /*  600 */  0,
  /*  601 */  iRegLsrc_rule,
  /*  602 */  iRegIsrc_rule,
  /*  603 */  iRegLsrc_rule,
  /*  604 */  iRegIsrc_rule,
  /*  605 */  iRegIsrc_rule,
  /*  606 */  iRegLsrc_rule,
  /*  607 */  iRegLsrc_rule,
  /*  608 */  0,
  /*  609 */  0,
  /*  610 */  iRegIsrc_rule,
  /*  611 */  immI_rule,
  /*  612 */  uimmI5_rule,
  /*  613 */  uimmI5_rule,
  /*  614 */  0,
  /*  615 */  iRegIsrc_rule,
  /*  616 */  immI_rule,
  /*  617 */  uimmI6_ge32_rule,
  /*  618 */  uimmI6_rule,
  /*  619 */  0,
  /*  620 */  iRegIsrc_rule,
  /*  621 */  immI_rule,
  /*  622 */  0,
  /*  623 */  iRegIsrc_rule,
  /*  624 */  immI_rule,
  /*  625 */  0,
  /*  626 */  0,
  /*  627 */  iRegIsrc_rule,
  /*  628 */  immI_rule,
  /*  629 */  0,
  /*  630 */  iRegIsrc_rule,
  /*  631 */  immI_rule,
  /*  632 */  0,
  /*  633 */  uimmI6_rule,
  /*  634 */  immIpow2minus1_rule,
  /*  635 */  immLpow2minus1_rule,
  /*  636 */  0,
  /*  637 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  638 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  639 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  640 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  641 */  regF_rule,
  /*  642 */  regD_rule,
  /*  643 */  regF_rule,
  /*  644 */  regD_rule,
  /*  645 */  regF_rule,
  /*  646 */  regD_rule,
  /*  647 */  regF_rule,
  /*  648 */  regD_rule,
  /*  649 */  0,
  /*  650 */  0,
  /*  651 */  _Binary_regF_regF_rule,
  /*  652 */  _Binary_regD_regD_rule,
  /*  653 */  _Binary__NegF_regF__regF_rule,
  /*  654 */  _Binary_regF__NegF_regF__rule,
  /*  655 */  _Binary__NegD_regD__regD_rule,
  /*  656 */  _Binary_regD__NegD_regD__rule,
  /*  657 */  _Binary__NegF_regF__regF_rule,
  /*  658 */  _Binary_regF__NegF_regF__rule,
  /*  659 */  _Binary__NegD_regD__regD_rule,
  /*  660 */  _Binary_regD__NegD_regD__rule,
  /*  661 */  _Binary_regF_regF_rule,
  /*  662 */  _Binary_regD_regD_rule,
  /*  663 */  iRegIsrc_rule,
  /*  664 */  immIhi16_rule,
  /*  665 */  uimmI16_rule,
  /*  666 */  immInegpow2_rule,
  /*  667 */  immIpow2minus1_rule,
  /*  668 */  immIpowerOf2_rule,
  /*  669 */  iRegLsrc_rule,
  /*  670 */  uimmL16_rule,
  /*  671 */  immLnegpow2_rule,
  /*  672 */  immLpow2minus1_rule,
  /*  673 */  0,
  /*  674 */  iRegIsrc_rule,
  /*  675 */  0,
  /*  676 */  iRegIsrc_rule,
  /*  677 */  _OrI__OrI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  678 */  iRegIsrc_rule,
  /*  679 */  _OrI_iRegIsrc__OrI_iRegIsrc_iRegIsrc_rule,
  /*  680 */  uimmI16_rule,
  /*  681 */  iRegLsrc_rule,
  /*  682 */  0,
  /*  683 */  uimmL16_rule,
  /*  684 */  iRegIsrc_rule,
  /*  685 */  0,
  /*  686 */  iRegIsrc_rule,
  /*  687 */  _XorI__XorI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  688 */  iRegIsrc_rule,
  /*  689 */  _XorI_iRegIsrc__XorI_iRegIsrc_iRegIsrc_rule,
  /*  690 */  uimmI16_rule,
  /*  691 */  iRegLsrc_rule,
  /*  692 */  0,
  /*  693 */  uimmL16_rule,
  /*  694 */  immI_minus1_rule,
  /*  695 */  immL_minus1_rule,
  /*  696 */  iRegIsrc_rule,
  /*  697 */  _XorI_iRegIsrc_immI_minus1_rule,
  /*  698 */  0,
  /*  699 */  0,
  /*  700 */  0,
  /*  701 */  0,
  /*  702 */  0,
  /*  703 */  0,
  /*  704 */  0,
  /*  705 */  immI_1_rule,
  /*  706 */  immI_1_rule,
  /*  707 */  0,
  /*  708 */  0,
  /*  709 */  immI_1_rule,
  /*  710 */  immI_1_rule,
  /*  711 */  iRegIsrc_rule,
  /*  712 */  immI_0_rule,
  /*  713 */  immI_24_rule,
  /*  714 */  immI_16_rule,
  /*  715 */  0,
  /*  716 */  0,
  /*  717 */  0,
  /*  718 */  0,
  /*  719 */  0,
  /*  720 */  0,
  /*  721 */  0,
  /*  722 */  0,
  /*  723 */  0,
  /*  724 */  0,
  /*  725 */  0,
  /*  726 */  immL_32bits_rule,
  /*  727 */  immL_32bits_rule,
  /*  728 */  0,
  /*  729 */  0,
  /*  730 */  0,
  /*  731 */  0,
  /*  732 */  0,
  /*  733 */  0,
  /*  734 */  0,
  /*  735 */  0,
  /*  736 */  0,
  /*  737 */  0,
  /*  738 */  0,
  /*  739 */  0,
  /*  740 */  0,
  /*  741 */  0,
  /*  742 */  0,
  /*  743 */  0,
  /*  744 */  0,
  /*  745 */  0,
  /*  746 */  0,
  /*  747 */  iRegLsrc_rule,
  /*  748 */  _CmpU_iRegIsrc_uimmI15_rule,
  /*  749 */  _CmpU_iRegIsrc_iRegIsrc_rule,
  /*  750 */  _CmpU_iRegIsrc_uimmI15_rule,
  /*  751 */  _CmpN_iRegNsrc_immN_0_rule,
  /*  752 */  _CmpP_iRegP_N2P_immP_0_rule,
  /*  753 */  regF_rule,
  /*  754 */  regD_rule,
  /*  755 */  0,
  /*  756 */  0,
  /*  757 */  0,
  /*  758 */  0,
  /*  759 */  0,
  /*  760 */  0,
  /*  761 */  flagsRegSrc_rule,
  /*  762 */  flagsRegSrc_rule,
  /*  763 */  flagsRegSrc_rule,
  /*  764 */  flagsRegSrc_rule,
  /*  765 */  iRegP_N2P_rule,
  /*  766 */  0,
  /*  767 */  _CastP2X_iRegPsrc__rule,
  /*  768 */  rarg2RegP_rule,
  /*  769 */  rarg2RegP_rule,
  /*  770 */  rarg2RegP_rule,
  /*  771 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  772 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  773 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  774 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  775 */  rarg3RegI_rule,
  /*  776 */  rarg3RegI_rule,
  /*  777 */  rarg2RegP_rule,
  /*  778 */  rarg2RegP_rule,
  /*  779 */  _Binary__AddP_immP_immL_immI_1_rule,
  /*  780 */  _Binary__AddP_immP_immL_immI_1_rule,
  /*  781 */  _Binary__AddP_immP_immL_immI_1_rule,
  /*  782 */  _Binary_rscratch2RegP_immI_1_rule,
  /*  783 */  _Binary_rscratch2RegP_immI_1_rule,
  /*  784 */  _Binary_rscratch2RegP_immI_1_rule,
  /*  785 */  iRegIsrc_rule,
  /*  786 */  iRegIsrc_rule,
  /*  787 */  _Binary_iRegPsrc_uimmI15_rule,
  /*  788 */  _Binary_iRegPsrc_uimmI15_rule,
  /*  789 */  _Binary_iRegPsrc_uimmI15_rule,
  /*  790 */  _Binary_iRegPsrc_rscratch2RegI_rule,
  /*  791 */  _Binary_iRegPsrc_rscratch2RegI_rule,
  /*  792 */  _Binary_iRegPsrc_rscratch2RegI_rule,
  /*  793 */  _Binary_rarg2RegP_iRegIsrc_rule,
  /*  794 */  _Binary_rarg2RegP_iRegIsrc_rule,
  /*  795 */  iRegIsrc_rule,
  /*  796 */  _Binary_rarg2RegP_iRegIsrc_rule,
  /*  797 */  _Binary_rarg2RegP_iRegIsrc_rule,
  /*  798 */  iRegIsrc_rule,
  /*  799 */  iRegIsrc_rule,
  /*  800 */  iRegIsrc_rule,
  /*  801 */  iRegIsrc_rule,
  /*  802 */  0,
  /*  803 */  0,
  /*  804 */  0,
  /*  805 */  0,
  /*  806 */  0,
  /*  807 */  0,
  /*  808 */  0,
  /*  809 */  0,
  /*  810 */  0,
  /*  811 */  0,
  /*  812 */  0,
  /*  813 */  0,
  /*  814 */  0,
  /*  815 */  0,
  /*  816 */  0,
  /*  817 */  0,
  /*  818 */  0,
  /*  819 */  0,
  /*  820 */  0,
  /*  821 */  0,
  /*  822 */  _ReverseBytesI_iRegIsrc__rule,
  /*  823 */  _ReverseBytesL_iRegLsrc__rule,
  /*  824 */  _ReverseBytesUS_iRegIsrc__rule,
  /*  825 */  _ReverseBytesS_iRegIsrc__rule,
  /*  826 */  0,
  /*  827 */  vecX_rule,
  /*  828 */  vecX_rule,
  /*  829 */  vecX_rule,
  /*  830 */  vecX_rule,
  /*  831 */  vecX_rule,
  /*  832 */  vecX_rule,
  /*  833 */  vecX_rule,
  /*  834 */  vecX_rule,
  /*  835 */  vecX_rule,
  /*  836 */  vecX_rule,
  /*  837 */  vecX_rule,
  /*  838 */  vecX_rule,
  /*  839 */  vecX_rule,
  /*  840 */  vecX_rule,
  /*  841 */  vecX_rule,
  /*  842 */  vecX_rule,
  /*  843 */  vecX_rule,
  /*  844 */  vecX_rule,
  /*  845 */  immI8_rule,
  /*  846 */  immI8_rule,
  /*  847 */  _Binary_vecX_vecX_rule,
  /*  848 */  _Binary__NegVF_vecX__vecX_rule,
  /*  849 */  _Binary_vecX__NegVF_vecX__rule,
  /*  850 */  _Binary_vecX_vecX_rule,
  /*  851 */  _Binary_vecX_vecX_rule,
  /*  852 */  _Binary__NegVD_vecX__vecX_rule,
  /*  853 */  _Binary_vecX__NegVD_vecX__rule,
  /*  854 */  _Binary_vecX_vecX_rule,
  /*  855 */  0,
  /*  856 */  0,
  /*  857 */  0,
  /*  858 */  0,
  /*  859 */  0,
  /*  860 */  0,
  /*  861 */  0,
  /*  862 */  0,
  /*  863 */  0,
  /*  864 */  0,
  /*  865 */  0,
  /*  866 */  0,
  /*  867 */  inline_cache_regP_rule,
  /*  868 */  0,
  /*  869 */  rarg1RegP_rule,
  /*  870 */  0,
  /*  871 */  0,
  /*  872 */  0,
  /*  873 */  0,
  /*  874 */  0,
  /*  875 */  0,
  /*  876 */  0,
  /*  877 */  0,
  /*  878 */  0,
  /*  879 */  0,
  /*  880 */  0,
  /*  881 */  0,
  /*  882 */  0,
  /*  883 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  884 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  885 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  886 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  887 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  888 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  889 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  890 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  891 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  892 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  893 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  894 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  895 */  0,
  /*  896 */  0,
  /*  897 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  898 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  899 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  900 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  901 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  902 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  903 */  iRegPsrc_rule,
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
  /*   13 */  "IMMI32",
  /*   14 */  "IMMINEGPOW2",
  /*   15 */  "IMMIPOW2MINUS1",
  /*   16 */  "IMMIPOWEROF2",
  /*   17 */  "UIMMI5",
  /*   18 */  "UIMMI6",
  /*   19 */  "UIMMI6_GE32",
  /*   20 */  "UIMMI15",
  /*   21 */  "UIMMI16",
  /*   22 */  "IMMI_0",
  /*   23 */  "IMMI_1",
  /*   24 */  "IMMI_MINUS1",
  /*   25 */  "IMMI_16",
  /*   26 */  "IMMI_24",
  /*   27 */  "IMMN",
  /*   28 */  "IMMN_0",
  /*   29 */  "IMMNKLASS",
  /*   30 */  "IMMNKLASS_NM",
  /*   31 */  "IMMP",
  /*   32 */  "IMMP_NM",
  /*   33 */  "IMMP_0",
  /*   34 */  "IMMP_0OR1",
  /*   35 */  "IMML",
  /*   36 */  "IMMLMAX30",
  /*   37 */  "IMML16",
  /*   38 */  "IMML16ALG4",
  /*   39 */  "IMML32HI16",
  /*   40 */  "IMML32",
  /*   41 */  "IMML34",
  /*   42 */  "IMMLHIGHEST16",
  /*   43 */  "IMMLNEGPOW2",
  /*   44 */  "IMMLPOW2MINUS1",
  /*   45 */  "IMML_0",
  /*   46 */  "IMML_MINUS1",
  /*   47 */  "IMML_32BITS",
  /*   48 */  "UIMML16",
  /*   49 */  "IMMF",
  /*   50 */  "IMMF_0",
  /*   51 */  "IMMD",
  /*   52 */  "IMMD_0",
  /*   53 */  "IREGIDST",
  /*   54 */  "IREGISRC",
  /*   55 */  "RSCRATCH1REGI",
  /*   56 */  "RSCRATCH2REGI",
  /*   57 */  "RARG1REGI",
  /*   58 */  "RARG2REGI",
  /*   59 */  "RARG3REGI",
  /*   60 */  "RARG4REGI",
  /*   61 */  "RARG1REGL",
  /*   62 */  "RARG2REGL",
  /*   63 */  "RARG3REGL",
  /*   64 */  "RARG4REGL",
  /*   65 */  "IREGPDST",
  /*   66 */  "IREGPDSTNOSCRATCH",
  /*   67 */  "IREGPSRC",
  /*   68 */  "THREADREGP",
  /*   69 */  "RSCRATCH1REGP",
  /*   70 */  "RSCRATCH2REGP",
  /*   71 */  "RARG1REGP",
  /*   72 */  "RARG2REGP",
  /*   73 */  "RARG3REGP",
  /*   74 */  "RARG4REGP",
  /*   75 */  "IREGNSRC",
  /*   76 */  "IREGNDST",
  /*   77 */  "IREGLDST",
  /*   78 */  "IREGLSRC",
  /*   79 */  "IREGL2ISRC",
  /*   80 */  "RSCRATCH1REGL",
  /*   81 */  "RSCRATCH2REGL",
  /*   82 */  "FLAGSREG",
  /*   83 */  "FLAGSREGSRC",
  /*   84 */  "FLAGSREGCR0",
  /*   85 */  "FLAGSREGCR1",
  /*   86 */  "FLAGSREGCR6",
  /*   87 */  "REGCTR",
  /*   88 */  "REGD",
  /*   89 */  "REGF",
  /*   90 */  "INLINE_CACHE_REGP",
  /*   91 */  "IREGP2N",
  /*   92 */  "IREGN2P",
  /*   93 */  "IREGN2P_KLASS",
  /*   94 */  "INDIRECT",
  /*   95 */  "INDOFFSET16",
  /*   96 */  "INDOFFSET16ALG4",
  /*   97 */  "INDIRECTNARROW",
  /*   98 */  "INDIRECTNARROW_KLASS",
  /*   99 */  "INDOFFSET16NARROW",
  /*  100 */  "INDOFFSET16NARROW_KLASS",
  /*  101 */  "INDOFFSET16NARROWALG4",
  /*  102 */  "INDOFFSET16NARROWALG4_KLASS",
  /*  103 */  "STACKSLOTI",
  /*  104 */  "STACKSLOTL",
  /*  105 */  "STACKSLOTP",
  /*  106 */  "STACKSLOTF",
  /*  107 */  "STACKSLOTD",
  /*  108 */  "CMPOP",
  // last operand
  /*  109 */  "MEMORY",
  /*  110 */  "MEMORYALG4",
  /*  111 */  "INDIRECTMEMORY",
  /*  112 */  "IREGISRC_IREGL2ISRC",
  /*  113 */  "IREGN_P2N",
  /*  114 */  "IREGP_N2P",
  // last operand class
  /*  115 */  "_DecodeN_iRegNsrc_",
  /*  116 */  "_DecodeNKlass_iRegNsrc_",
  /*  117 */  "_LoadUB_memory_",
  /*  118 */  "_LoadUS_memory_",
  /*  119 */  "_LoadI_memory_",
  /*  120 */  "_ConvI2L__LoadI_memory__",
  /*  121 */  "_LoadI_memoryAlg4_",
  /*  122 */  "_LoadN_memory_",
  /*  123 */  "_LoadNKlass_memory_",
  /*  124 */  "_LoadP_memoryAlg4_",
  /*  125 */  "_AddP_indirectMemory_iRegLsrc",
  /*  126 */  "_ConvL2I_iRegLsrc_",
  /*  127 */  "_Binary_flagsRegSrc_iRegPsrc",
  /*  128 */  "_CastP2X__DecodeN_iRegNsrc__",
  /*  129 */  "_Binary_iRegLsrc_iRegPdst",
  /*  130 */  "_Binary_iRegLsrc_iRegPsrc",
  /*  131 */  "_Binary_iRegLsrc_iRegNsrc",
  /*  132 */  "_Binary_cmpOp_flagsRegSrc",
  /*  133 */  "_Binary_iRegIdst_iRegIsrc",
  /*  134 */  "_Binary_iRegIdst_immI16",
  /*  135 */  "_Binary_iRegLdst_iRegLsrc",
  /*  136 */  "_Binary_iRegLdst_immL16",
  /*  137 */  "_Binary_iRegNdst_iRegNsrc",
  /*  138 */  "_Binary_iRegNdst_immN_0",
  /*  139 */  "_Binary_iRegPdst_iRegPsrc",
  /*  140 */  "_Binary_iRegPdst_iRegP_N2P",
  /*  141 */  "_Binary_iRegPdst_immP_0",
  /*  142 */  "_Binary_regF_regF",
  /*  143 */  "_Binary_regD_regD",
  /*  144 */  "_Binary_iRegIsrc_iRegIsrc",
  /*  145 */  "_Binary_iRegIsrc_rarg4RegI",
  /*  146 */  "_Binary_iRegNsrc_iRegNsrc",
  /*  147 */  "_Binary_iRegLsrc_iRegLsrc",
  /*  148 */  "_Binary_iRegPsrc_iRegPsrc",
  /*  149 */  "_AddI_iRegIsrc_iRegIsrc",
  /*  150 */  "_AddI__AddI_iRegIsrc_iRegIsrc_iRegIsrc",
  /*  151 */  "_AddI_iRegIsrc__AddI_iRegIsrc_iRegIsrc",
  /*  152 */  "_AddL_iRegLsrc_iRegLsrc",
  /*  153 */  "_AddL__AddL_iRegLsrc_iRegLsrc_iRegLsrc",
  /*  154 */  "_AddL_iRegLsrc__AddL_iRegLsrc_iRegLsrc",
  /*  155 */  "_SubL_iRegLsrc_iRegLsrc",
  /*  156 */  "_SubL_immL_0_iRegLsrc",
  /*  157 */  "_AndI_iRegIsrc_immInegpow2",
  /*  158 */  "_RShiftI_iRegIsrc_uimmI5",
  /*  159 */  "_AndI__RShiftI_iRegIsrc_uimmI5_immInegpow2",
  /*  160 */  "_ConvI2L_iRegIsrc_",
  /*  161 */  "_RShiftL_iRegLsrc_immI",
  /*  162 */  "_URShiftL_iRegLsrc_immI",
  /*  163 */  "_CastP2X_iRegP_N2P_",
  /*  164 */  "_URShiftI_iRegIsrc_immI",
  /*  165 */  "_LShiftI_iRegIsrc_immI8",
  /*  166 */  "_URShiftI_iRegIsrc_immI8",
  /*  167 */  "_AbsF_regF_",
  /*  168 */  "_AbsD_regD_",
  /*  169 */  "_NegF_regF_",
  /*  170 */  "_Binary__NegF_regF__regF",
  /*  171 */  "_Binary_regF__NegF_regF_",
  /*  172 */  "_NegD_regD_",
  /*  173 */  "_Binary__NegD_regD__regD",
  /*  174 */  "_Binary_regD__NegD_regD_",
  /*  175 */  "_AndL_iRegLsrc_immLpow2minus1",
  /*  176 */  "_OrI_iRegIsrc_iRegIsrc",
  /*  177 */  "_OrI__OrI_iRegIsrc_iRegIsrc_iRegIsrc",
  /*  178 */  "_OrI_iRegIsrc__OrI_iRegIsrc_iRegIsrc",
  /*  179 */  "_OrL_iRegLsrc_iRegLsrc",
  /*  180 */  "_XorI_iRegIsrc_iRegIsrc",
  /*  181 */  "_XorI__XorI_iRegIsrc_iRegIsrc_iRegIsrc",
  /*  182 */  "_XorI_iRegIsrc__XorI_iRegIsrc_iRegIsrc",
  /*  183 */  "_XorL_iRegLsrc_iRegLsrc",
  /*  184 */  "_XorI_iRegIsrc_immI_minus1",
  /*  185 */  "_Conv2B_iRegIsrc_",
  /*  186 */  "_AndI_iRegIsrc_immIpowerOf2",
  /*  187 */  "_Conv2B_iRegP_N2P_",
  /*  188 */  "_LShiftI_iRegIsrc_immI_24",
  /*  189 */  "_LShiftI_iRegIsrc_immI_16",
  /*  190 */  "_AndI_iRegIsrc_uimmI16",
  /*  191 */  "_AndL_iRegLsrc_iRegLsrc",
  /*  192 */  "_AndL_iRegLsrc_uimmL16",
  /*  193 */  "_CmpU_iRegIsrc_uimmI15",
  /*  194 */  "_CmpU_iRegIsrc_iRegIsrc",
  /*  195 */  "_CmpN_iRegNsrc_immN_0",
  /*  196 */  "_CmpP_iRegP_N2P_immP_0",
  /*  197 */  "_CastP2X_iRegPsrc_",
  /*  198 */  "_AndL__CastP2X_iRegPsrc__immLnegpow2",
  /*  199 */  "_Binary_rarg1RegP_rarg3RegI",
  /*  200 */  "_Binary_rarg2RegP_rarg4RegI",
  /*  201 */  "_Binary_rarg1RegP_rarg2RegP",
  /*  202 */  "_Binary_iRegPsrc_iRegIsrc",
  /*  203 */  "_AddP_immP_immL",
  /*  204 */  "_Binary__AddP_immP_immL_immI_1",
  /*  205 */  "_Binary_rscratch2RegP_immI_1",
  /*  206 */  "_Binary_iRegPsrc_rscratch1RegI",
  /*  207 */  "_Binary_iRegPsrc_uimmI15",
  /*  208 */  "_Binary_iRegPsrc_rscratch2RegI",
  /*  209 */  "_Binary_rarg2RegP_iRegIsrc",
  /*  210 */  "_LoadI_indirect_",
  /*  211 */  "_LoadL_indirect_",
  /*  212 */  "_LoadUS_indirect_",
  /*  213 */  "_LoadS_indirect_",
  /*  214 */  "_ReverseBytesI_iRegIsrc_",
  /*  215 */  "_ReverseBytesL_iRegLsrc_",
  /*  216 */  "_ReverseBytesUS_iRegIsrc_",
  /*  217 */  "_ReverseBytesS_iRegIsrc_",
  /*  218 */  "_Binary_vecX_vecX",
  /*  219 */  "_NegVF_vecX_",
  /*  220 */  "_Binary__NegVF_vecX__vecX",
  /*  221 */  "_Binary_vecX__NegVF_vecX_",
  /*  222 */  "_NegVD_vecX_",
  /*  223 */  "_Binary__NegVD_vecX__vecX",
  /*  224 */  "_Binary_vecX__NegVD_vecX_",
  // last internally defined operand
  /*  225 */  "regI_to_stkI",
  /*  226 */  "regL_to_stkL",
  /*  227 */  "loadConI16",
  /*  228 */  "loadConIhi16",
  /*  229 */  "loadConI32",
  /*  230 */  "loadConI_Ex",
  /*  231 */  "loadConL16",
  /*  232 */  "loadConL32hi16",
  /*  233 */  "loadConL32_Ex",
  /*  234 */  "loadConL34",
  /*  235 */  "loadConLhighest16_Ex",
  /*  236 */  "loadConL_Ex",
  /*  237 */  "loadConN0",
  /*  238 */  "loadConN_Ex",
  /*  239 */  "loadConNKlass_hi",
  /*  240 */  "loadConNKlass_mask",
  /*  241 */  "loadConNKlass_lo",
  /*  242 */  "loadConNKlass_Ex",
  /*  243 */  "loadConP0or1",
  /*  244 */  "loadConP",
  /*  245 */  "loadConP_lo",
  /*  246 */  "loadConP_Ex",
  /*  247 */  "loadConF_Ex",
  /*  248 */  "loadConD_Ex",
  /*  249 */  "stkI_to_regI",
  /*  250 */  "stkL_to_regL",
  /*  251 */  "convB2I_reg_2",
  /*  252 */  "loadP2X",
  /*  253 */  "loadToc_lo",
  /*  254 */  "loadConN_hi",
  /*  255 */  "clearMs32b",
  /*  256 */  "reinterpretL",
  /*  257 */  "reinterpretX",
  /*  258 */  "signmask32I_regI",
  /*  259 */  "absI_reg_Ex",
  /*  260 */  "signmask64I_regL",
  /*  261 */  "signmask64L_regL",
  /*  262 */  "absL_reg_Ex",
  /*  263 */  "absF_reg",
  /*  264 */  "absD_reg",
  /*  265 */  "negF_reg",
  /*  266 */  "negD_reg",
  /*  267 */  "negF_absF_reg",
  /*  268 */  "negD_absD_reg",
  /*  269 */  "roundDouble_nop",
  /*  270 */  "roundFloat_nop",
  /*  271 */  "moveL2D_reg",
  /*  272 */  "moveI2D_reg",
  /*  273 */  "moveF2I_stack_reg",
  /*  274 */  "moveI2F_stack_reg",
  /*  275 */  "moveD2L_stack_reg",
  /*  276 */  "moveL2D_stack_reg",
  /*  277 */  "moveReg",
  /*  278 */  "castX2P",
  /*  279 */  "castP2X",
  /*  280 */  "castPP",
  /*  281 */  "castII",
  /*  282 */  "castLL",
  /*  283 */  "castFF",
  /*  284 */  "castDD",
  /*  285 */  "castVV8",
  /*  286 */  "castVV16",
  /*  287 */  "checkCastPP",
  /*  288 */  "convI2Bool_reg__cntlz_Ex",
  /*  289 */  "convP2Bool_reg__cntlz_Ex",
  /*  290 */  "extsh",
  /*  291 */  "convD2IRaw_regD",
  /*  292 */  "convF2IRaw_regF",
  /*  293 */  "convF2LRaw_regF",
  /*  294 */  "convD2LRaw_regD",
  /*  295 */  "convL2DRaw_regD",
  /*  296 */  "convL2FRaw_regF",
  /*  297 */  "cmpI_reg_reg",
  /*  298 */  "cmpI_reg_imm16",
  /*  299 */  "testI_reg_imm",
  /*  300 */  "cmpL_reg_reg",
  /*  301 */  "cmpL_reg_imm16",
  /*  302 */  "cmpUL_reg_reg",
  /*  303 */  "cmpUL_reg_imm16",
  /*  304 */  "testL_reg_reg",
  /*  305 */  "testL_reg_imm",
  /*  306 */  "compU_reg_reg",
  /*  307 */  "compU_reg_uimm16",
  /*  308 */  "cmpN_reg_reg",
  /*  309 */  "cmpN_reg_imm0",
  /*  310 */  "cmpP_reg_reg",
  /*  311 */  "cmpP_reg_null",
  /*  312 */  "cmpP_reg_imm16",
  /*  313 */  "cmpFUnordered_reg_reg",
  /*  314 */  "cmov_bns_less",
  /*  315 */  "cmpF_reg_reg_Ex",
  /*  316 */  "cmpDUnordered_reg_reg",
  /*  317 */  "cmpD_reg_reg_Ex",
  /*  318 */  "cmpFastLock",
  /*  319 */  "cmpFastLock_tm",
  /*  320 */  "cmpFastUnlock",
  /*  321 */  "cmpFastUnlock_tm",
  /*  322 */  "popCountI",
  /*  323 */  "popCountL",
  /*  324 */  "countLeadingZerosI",
  /*  325 */  "countLeadingZerosL",
  /*  326 */  "countLeadingZerosP",
  /*  327 */  "countTrailingZerosI_Ex",
  /*  328 */  "countTrailingZerosI_cnttzw",
  /*  329 */  "countTrailingZerosL_Ex",
  /*  330 */  "countTrailingZerosL_cnttzd",
  /*  331 */  "mtvsrwz",
  /*  332 */  "xscvdpspn_regF",
  /*  333 */  "repl32",
  /*  334 */  "repl48",
  /*  335 */  "repl56",
  /*  336 */  "repl8B_reg_Ex",
  /*  337 */  "repl8B_immI0",
  /*  338 */  "repl8B_immIminus1",
  /*  339 */  "repl16B_reg_Ex",
  /*  340 */  "repl16B_immI0",
  /*  341 */  "repl16B_immIminus1",
  /*  342 */  "repl4S_reg_Ex",
  /*  343 */  "repl4S_immI0",
  /*  344 */  "repl4S_immIminus1",
  /*  345 */  "repl8S_reg_Ex",
  /*  346 */  "repl8S_immI0",
  /*  347 */  "repl8S_immIminus1",
  /*  348 */  "repl2I_reg_Ex",
  /*  349 */  "repl2I_immI0",
  /*  350 */  "repl2I_immIminus1",
  /*  351 */  "repl4I_reg_Ex",
  /*  352 */  "repl4I_immI0",
  /*  353 */  "repl4I_immIminus1",
  /*  354 */  "repl2F_reg_Ex",
  /*  355 */  "repl2F_immF_Ex",
  /*  356 */  "repl2F_immF0",
  /*  357 */  "vabs4F_reg",
  /*  358 */  "vabs2D_reg",
  /*  359 */  "vneg4F_reg",
  /*  360 */  "vneg2D_reg",
  /*  361 */  "vsqrt4F_reg",
  /*  362 */  "vsqrt2D_reg",
  /*  363 */  "vpopcnt_reg",
  /*  364 */  "overflowAddL_reg_reg",
  /*  365 */  "overflowSubL_reg_reg",
  /*  366 */  "overflowNegL_reg",
  /*  367 */  "overflowMulL_reg_reg",
  /*  368 */  "repl4F_reg_Ex",
  /*  369 */  "repl4F_immF0",
  /*  370 */  "repl2D_reg_Ex",
  /*  371 */  "repl2D_immD0",
  /*  372 */  "mtvsrd",
  /*  373 */  "repl2L_reg_Ex",
  /*  374 */  "repl2L_immI0",
  /*  375 */  "repl2L_immIminus1",
  /*  376 */  "CallLeafDirect_mtctr",
  /*  377 */  "tlsLoadP",
  /*  378 */  "loadUB_indirect",
  /*  379 */  "loadUB_indirect_ac",
  /*  380 */  "loadB_indirect_Ex",
  /*  381 */  "loadB_indirect_ac_Ex",
  /*  382 */  "loadUB_indOffset16",
  /*  383 */  "loadUB_indOffset16_ac",
  /*  384 */  "loadB_indOffset16_Ex",
  /*  385 */  "loadB_indOffset16_ac_Ex",
  /*  386 */  "loadUB",
  /*  387 */  "loadUB_ac",
  /*  388 */  "loadUB2L",
  /*  389 */  "loadUB2L_ac",
  /*  390 */  "loadS",
  /*  391 */  "loadS_ac",
  /*  392 */  "loadUS",
  /*  393 */  "loadUS_ac",
  /*  394 */  "loadUS2L",
  /*  395 */  "loadUS2L_ac",
  /*  396 */  "loadI",
  /*  397 */  "loadI_ac",
  /*  398 */  "loadUI2L",
  /*  399 */  "loadI2L",
  /*  400 */  "loadI2L_ac",
  /*  401 */  "loadL",
  /*  402 */  "loadL_ac",
  /*  403 */  "loadL_unaligned",
  /*  404 */  "loadV8",
  /*  405 */  "loadV16",
  /*  406 */  "loadRange",
  /*  407 */  "loadN",
  /*  408 */  "loadN_ac",
  /*  409 */  "loadN2P_unscaled",
  /*  410 */  "loadN2P_klass_unscaled",
  /*  411 */  "loadP",
  /*  412 */  "loadP_ac",
  /*  413 */  "loadNKlass",
  /*  414 */  "loadKlass",
  /*  415 */  "loadF",
  /*  416 */  "loadF_ac",
  /*  417 */  "loadD",
  /*  418 */  "loadD_ac",
  /*  419 */  "loadD_unaligned",
  /*  420 */  "loadToc_hi",
  /*  421 */  "loadConI32_lo16",
  /*  422 */  "loadConL32_lo16",
  /*  423 */  "loadConL",
  /*  424 */  "loadConL_hi",
  /*  425 */  "loadConL_lo",
  /*  426 */  "loadConN_lo",
  /*  427 */  "rldicl",
  /*  428 */  "loadBase",
  /*  429 */  "loadConP_hi",
  /*  430 */  "loadConF",
  /*  431 */  "loadConFComp",
  /*  432 */  "loadConD",
  /*  433 */  "loadConDComp",
  /*  434 */  "prefetch_alloc_zero",
  /*  435 */  "prefetch_alloc_zero_no_offset",
  /*  436 */  "prefetch_alloc",
  /*  437 */  "prefetch_alloc_no_offset",
  /*  438 */  "storeB",
  /*  439 */  "storeC",
  /*  440 */  "storeI",
  /*  441 */  "storeI_convL2I",
  /*  442 */  "storeL",
  /*  443 */  "storeA8B",
  /*  444 */  "storeV16",
  /*  445 */  "storeN",
  /*  446 */  "storeNKlass",
  /*  447 */  "storeP",
  /*  448 */  "storeF",
  /*  449 */  "storeD",
  /*  450 */  "storeCM",
  /*  451 */  "encodeP_shift",
  /*  452 */  "encodeP_sub",
  /*  453 */  "cond_sub_base",
  /*  454 */  "cond_set_0_oop",
  /*  455 */  "encodeP_Disjoint",
  /*  456 */  "encodeP_Ex",
  /*  457 */  "encodeP_not_null_Ex",
  /*  458 */  "encodeP_not_null_base_null",
  /*  459 */  "encodeP_narrow_oop_shift_0",
  /*  460 */  "decodeN_shift",
  /*  461 */  "decodeN_add",
  /*  462 */  "cond_add_base",
  /*  463 */  "cond_set_0_ptr",
  /*  464 */  "decodeN_Ex",
  /*  465 */  "decodeN_nullBase",
  /*  466 */  "decodeN_mergeDisjoint",
  /*  467 */  "decodeN_Disjoint_notNull_Ex",
  /*  468 */  "decodeN_Disjoint_isel_Ex",
  /*  469 */  "decodeN_notNull_addBase_Ex",
  /*  470 */  "decodeN_unscaled",
  /*  471 */  "decodeN2I_unscaled",
  /*  472 */  "encodePKlass_shift",
  /*  473 */  "encodePKlass_sub_base",
  /*  474 */  "encodePKlass_Disjoint",
  /*  475 */  "encodePKlass_not_null_Ex",
  /*  476 */  "encodePKlass_not_null_ExEx",
  /*  477 */  "decodeNKlass_shift",
  /*  478 */  "decodeNKlass_add_base",
  /*  479 */  "decodeNKlass_notNull_addBase_Ex",
  /*  480 */  "decodeNKlass_notNull_addBase_ExEx",
  /*  481 */  "membar_acquire",
  /*  482 */  "unnecessary_membar_acquire",
  /*  483 */  "membar_acquire_lock",
  /*  484 */  "membar_release",
  /*  485 */  "membar_release_0",
  /*  486 */  "membar_storestore",
  /*  487 */  "membar_storestore_0",
  /*  488 */  "membar_release_lock",
  /*  489 */  "membar_volatile",
  /*  490 */  "membar_CPUOrder",
  /*  491 */  "cmovI_reg_isel",
  /*  492 */  "cmovI_reg",
  /*  493 */  "cmovI_imm",
  /*  494 */  "cmovL_reg_isel",
  /*  495 */  "cmovL_reg",
  /*  496 */  "cmovL_imm",
  /*  497 */  "cmovN_reg_isel",
  /*  498 */  "cmovN_reg",
  /*  499 */  "cmovN_imm",
  /*  500 */  "cmovP_reg_isel",
  /*  501 */  "cmovP_reg",
  /*  502 */  "cmovP_imm",
  /*  503 */  "cmovF_reg",
  /*  504 */  "cmovD_reg",
  /*  505 */  "compareAndSwapB_regP_regI_regI",
  /*  506 */  "compareAndSwapB4_regP_regI_regI",
  /*  507 */  "compareAndSwapS_regP_regI_regI",
  /*  508 */  "compareAndSwapS4_regP_regI_regI",
  /*  509 */  "compareAndSwapI_regP_regI_regI",
  /*  510 */  "compareAndSwapN_regP_regN_regN",
  /*  511 */  "compareAndSwapL_regP_regL_regL",
  /*  512 */  "compareAndSwapP_regP_regP_regP",
  /*  513 */  "weakCompareAndSwapB_regP_regI_regI",
  /*  514 */  "weakCompareAndSwapB4_regP_regI_regI",
  /*  515 */  "weakCompareAndSwapB_acq_regP_regI_regI",
  /*  516 */  "weakCompareAndSwapB4_acq_regP_regI_regI",
  /*  517 */  "weakCompareAndSwapS_regP_regI_regI",
  /*  518 */  "weakCompareAndSwapS4_regP_regI_regI",
  /*  519 */  "weakCompareAndSwapS_acq_regP_regI_regI",
  /*  520 */  "weakCompareAndSwapS4_acq_regP_regI_regI",
  /*  521 */  "weakCompareAndSwapI_regP_regI_regI",
  /*  522 */  "weakCompareAndSwapI_acq_regP_regI_regI",
  /*  523 */  "weakCompareAndSwapN_regP_regN_regN",
  /*  524 */  "weakCompareAndSwapN_acq_regP_regN_regN",
  /*  525 */  "weakCompareAndSwapL_regP_regL_regL",
  /*  526 */  "weakCompareAndSwapL_acq_regP_regL_regL",
  /*  527 */  "weakCompareAndSwapP_regP_regP_regP",
  /*  528 */  "weakCompareAndSwapP_acq_regP_regP_regP",
  /*  529 */  "compareAndExchangeB_regP_regI_regI",
  /*  530 */  "compareAndExchangeB4_regP_regI_regI",
  /*  531 */  "compareAndExchangeB_acq_regP_regI_regI",
  /*  532 */  "compareAndExchangeB4_acq_regP_regI_regI",
  /*  533 */  "compareAndExchangeS_regP_regI_regI",
  /*  534 */  "compareAndExchangeS4_regP_regI_regI",
  /*  535 */  "compareAndExchangeS_acq_regP_regI_regI",
  /*  536 */  "compareAndExchangeS4_acq_regP_regI_regI",
  /*  537 */  "compareAndExchangeI_regP_regI_regI",
  /*  538 */  "compareAndExchangeI_acq_regP_regI_regI",
  /*  539 */  "compareAndExchangeN_regP_regN_regN",
  /*  540 */  "compareAndExchangeN_acq_regP_regN_regN",
  /*  541 */  "compareAndExchangeL_regP_regL_regL",
  /*  542 */  "compareAndExchangeL_acq_regP_regL_regL",
  /*  543 */  "compareAndExchangeP_regP_regP_regP",
  /*  544 */  "compareAndExchangeP_acq_regP_regP_regP",
  /*  545 */  "getAndAddB",
  /*  546 */  "getAndAddB4",
  /*  547 */  "getAndAddS",
  /*  548 */  "getAndAddS4",
  /*  549 */  "getAndAddI",
  /*  550 */  "getAndAddL",
  /*  551 */  "getAndSetB",
  /*  552 */  "getAndSetB4",
  /*  553 */  "getAndSetS",
  /*  554 */  "getAndSetS4",
  /*  555 */  "getAndSetI",
  /*  556 */  "getAndSetL",
  /*  557 */  "getAndSetP",
  /*  558 */  "getAndSetN",
  /*  559 */  "addI_reg_reg",
  /*  560 */  "addI_reg_reg_2",
  /*  561 */  "tree_addI_addI_addI_reg_reg_Ex",
  /*  562 */  "tree_addI_addI_addI_reg_reg_Ex_1",
  /*  563 */  "tree_addI_addI_addI_reg_reg_Ex_0",
  /*  564 */  "tree_addI_addI_addI_reg_reg_Ex_2",
  /*  565 */  "addI_reg_imm16",
  /*  566 */  "addI_reg_immhi16",
  /*  567 */  "addI_reg_imm32",
  /*  568 */  "addL_reg_reg",
  /*  569 */  "addL_reg_reg_2",
  /*  570 */  "tree_addL_addL_addL_reg_reg_Ex",
  /*  571 */  "tree_addL_addL_addL_reg_reg_Ex_1",
  /*  572 */  "tree_addL_addL_addL_reg_reg_Ex_0",
  /*  573 */  "tree_addL_addL_addL_reg_reg_Ex_2",
  /*  574 */  "addI_regL_regL",
  /*  575 */  "addL_reg_imm16",
  /*  576 */  "addL_reg_immhi16",
  /*  577 */  "addL_reg_imm34",
  /*  578 */  "addP_reg_reg",
  /*  579 */  "addP_reg_imm16",
  /*  580 */  "addP_reg_immhi16",
  /*  581 */  "addP_reg_imm34",
  /*  582 */  "subI_reg_reg",
  /*  583 */  "subI_imm16_reg",
  /*  584 */  "negI_regI",
  /*  585 */  "subL_reg_reg",
  /*  586 */  "subI_regL_regL",
  /*  587 */  "negL_reg_reg",
  /*  588 */  "negI_con0_regL",
  /*  589 */  "mulI_reg_reg",
  /*  590 */  "mulI_reg_imm16",
  /*  591 */  "mulL_reg_reg",
  /*  592 */  "mulHighL_reg_reg",
  /*  593 */  "mulL_reg_imm16",
  /*  594 */  "divI_reg_immIvalueMinus1",
  /*  595 */  "divI_reg_regnotMinus1",
  /*  596 */  "cmovI_bne_negI_reg",
  /*  597 */  "divI_reg_reg_Ex",
  /*  598 */  "divL_reg_immLvalueMinus1",
  /*  599 */  "divL_reg_regnotMinus1",
  /*  600 */  "cmovL_bne_negL_reg",
  /*  601 */  "divL_reg_reg_Ex",
  /*  602 */  "modI_reg_reg_Ex",
  /*  603 */  "modL_reg_reg_Ex",
  /*  604 */  "udivI_reg_reg",
  /*  605 */  "umodI_reg_reg",
  /*  606 */  "udivL_reg_reg",
  /*  607 */  "umodL_reg_reg",
  /*  608 */  "maskI_reg_imm",
  /*  609 */  "lShiftI_reg_reg",
  /*  610 */  "lShiftI_reg_reg_Ex",
  /*  611 */  "lShiftI_reg_imm",
  /*  612 */  "lShiftI_andI_immInegpow2_imm5",
  /*  613 */  "lShiftI_andI_immInegpow2_rShiftI_imm5",
  /*  614 */  "lShiftL_regL_regI",
  /*  615 */  "lShiftL_regL_regI_Ex",
  /*  616 */  "lshiftL_regL_immI",
  /*  617 */  "lShiftL_regI_immGE32",
  /*  618 */  "scaledPositiveI2L_lShiftL_convI2L_reg_imm6",
  /*  619 */  "arShiftI_reg_reg",
  /*  620 */  "arShiftI_reg_reg_Ex",
  /*  621 */  "arShiftI_reg_imm",
  /*  622 */  "arShiftL_regL_regI",
  /*  623 */  "arShiftL_regL_regI_Ex",
  /*  624 */  "arShiftL_regL_immI",
  /*  625 */  "convL2I_arShiftL_regL_immI",
  /*  626 */  "urShiftI_reg_reg",
  /*  627 */  "urShiftI_reg_reg_Ex",
  /*  628 */  "urShiftI_reg_imm",
  /*  629 */  "urShiftL_regL_regI",
  /*  630 */  "urShiftL_regL_regI_Ex",
  /*  631 */  "urShiftL_regL_immI",
  /*  632 */  "convL2I_urShiftL_regL_immI",
  /*  633 */  "shrP_convP2X_reg_imm6",
  /*  634 */  "andI_urShiftI_regI_immI_immIpow2minus1",
  /*  635 */  "andL_urShiftL_regL_immI_immLpow2minus1",
  /*  636 */  "sxtI_reg",
  /*  637 */  "rotlI_reg_immi8",
  /*  638 */  "rotlI_reg_immi8_0",
  /*  639 */  "rotrI_reg_immi8",
  /*  640 */  "rotrI_reg_immi8_0",
  /*  641 */  "addF_reg_reg",
  /*  642 */  "addD_reg_reg",
  /*  643 */  "subF_reg_reg",
  /*  644 */  "subD_reg_reg",
  /*  645 */  "mulF_reg_reg",
  /*  646 */  "mulD_reg_reg",
  /*  647 */  "divF_reg_reg",
  /*  648 */  "divD_reg_reg",
  /*  649 */  "sqrtD_reg",
  /*  650 */  "sqrtF_reg",
  /*  651 */  "maddF_reg_reg",
  /*  652 */  "maddD_reg_reg",
  /*  653 */  "mnsubF_reg_reg",
  /*  654 */  "mnsubF_reg_reg_0",
  /*  655 */  "mnsubD_reg_reg",
  /*  656 */  "mnsubD_reg_reg_0",
  /*  657 */  "mnaddF_reg_reg",
  /*  658 */  "mnaddF_reg_reg_0",
  /*  659 */  "mnaddD_reg_reg",
  /*  660 */  "mnaddD_reg_reg_0",
  /*  661 */  "msubF_reg_reg",
  /*  662 */  "msubD_reg_reg",
  /*  663 */  "andI_reg_reg",
  /*  664 */  "andI_reg_immIhi16",
  /*  665 */  "andI_reg_uimm16",
  /*  666 */  "andI_reg_immInegpow2",
  /*  667 */  "andI_reg_immIpow2minus1",
  /*  668 */  "andI_reg_immIpowerOf2",
  /*  669 */  "andL_reg_reg",
  /*  670 */  "andL_reg_uimm16",
  /*  671 */  "andL_reg_immLnegpow2",
  /*  672 */  "andL_reg_immLpow2minus1",
  /*  673 */  "convL2I_andL_reg_immLpow2minus1",
  /*  674 */  "orI_reg_reg",
  /*  675 */  "orI_reg_reg_2",
  /*  676 */  "tree_orI_orI_orI_reg_reg_Ex",
  /*  677 */  "tree_orI_orI_orI_reg_reg_Ex_1",
  /*  678 */  "tree_orI_orI_orI_reg_reg_Ex_0",
  /*  679 */  "tree_orI_orI_orI_reg_reg_Ex_2",
  /*  680 */  "orI_reg_uimm16",
  /*  681 */  "orL_reg_reg",
  /*  682 */  "orI_regL_regL",
  /*  683 */  "orL_reg_uimm16",
  /*  684 */  "xorI_reg_reg",
  /*  685 */  "xorI_reg_reg_2",
  /*  686 */  "tree_xorI_xorI_xorI_reg_reg_Ex",
  /*  687 */  "tree_xorI_xorI_xorI_reg_reg_Ex_1",
  /*  688 */  "tree_xorI_xorI_xorI_reg_reg_Ex_0",
  /*  689 */  "tree_xorI_xorI_xorI_reg_reg_Ex_2",
  /*  690 */  "xorI_reg_uimm16",
  /*  691 */  "xorL_reg_reg",
  /*  692 */  "xorI_regL_regL",
  /*  693 */  "xorL_reg_uimm16",
  /*  694 */  "notI_reg",
  /*  695 */  "notL_reg",
  /*  696 */  "andcI_reg_reg",
  /*  697 */  "andcI_reg_reg_0",
  /*  698 */  "andcL_reg_reg",
  /*  699 */  "moveF2I_reg_stack",
  /*  700 */  "moveI2F_reg_stack",
  /*  701 */  "moveF2L_reg_stack",
  /*  702 */  "moveD2L_reg_stack",
  /*  703 */  "moveL2D_reg_stack",
  /*  704 */  "convI2Bool_reg__cmove",
  /*  705 */  "xorI_convI2Bool_reg_immIvalue1__cntlz_Ex",
  /*  706 */  "xorI_convI2Bool_reg_immIvalue1__cmove",
  /*  707 */  "convI2Bool_andI_reg_immIpowerOf2",
  /*  708 */  "convP2Bool_reg__cmove",
  /*  709 */  "xorI_convP2Bool_reg__cntlz_Ex",
  /*  710 */  "xorI_convP2Bool_reg_immIvalue1__cmove",
  /*  711 */  "cmpLTMask_reg_reg_Ex",
  /*  712 */  "cmpLTMask_reg_immI0",
  /*  713 */  "convB2I_reg",
  /*  714 */  "convS2I_reg",
  /*  715 */  "sxtI_L2L_reg",
  /*  716 */  "convL2I_reg",
  /*  717 */  "cmovI_bso_stackSlotL",
  /*  718 */  "cmovI_bso_reg",
  /*  719 */  "cmovI_bso_stackSlotL_conLvalue0_Ex",
  /*  720 */  "cmovI_bso_reg_conLvalue0_Ex",
  /*  721 */  "convD2I_reg_ExEx",
  /*  722 */  "convD2I_reg_mffprd_ExEx",
  /*  723 */  "convF2I_regF_ExEx",
  /*  724 */  "convF2I_regF_mffprd_ExEx",
  /*  725 */  "convI2L_reg",
  /*  726 */  "zeroExtendL_regI",
  /*  727 */  "zeroExtendL_regL",
  /*  728 */  "cmovL_bso_stackSlotL",
  /*  729 */  "cmovL_bso_reg",
  /*  730 */  "cmovL_bso_stackSlotL_conLvalue0_Ex",
  /*  731 */  "cmovL_bso_reg_conLvalue0_Ex",
  /*  732 */  "convF2L_reg_ExEx",
  /*  733 */  "convF2L_reg_mffprd_ExEx",
  /*  734 */  "convD2L_reg_ExEx",
  /*  735 */  "convD2L_reg_mffprd_ExEx",
  /*  736 */  "convD2F_reg",
  /*  737 */  "convI2F_ireg_Ex",
  /*  738 */  "convI2F_ireg_fcfids_Ex",
  /*  739 */  "convI2F_ireg_mtfprd_Ex",
  /*  740 */  "convL2F_ireg_fcfids_Ex",
  /*  741 */  "convL2F_ireg_mtfprd_Ex",
  /*  742 */  "convI2D_reg_Ex",
  /*  743 */  "convI2D_reg_mtfprd_Ex",
  /*  744 */  "convL2D_reg_Ex",
  /*  745 */  "convL2D_reg_mtfprd_Ex",
  /*  746 */  "convF2D_reg",
  /*  747 */  "cmpL3_reg_reg",
  /*  748 */  "rangeCheck_iReg_uimm15",
  /*  749 */  "rangeCheck_iReg_iReg",
  /*  750 */  "rangeCheck_uimm15_iReg",
  /*  751 */  "zeroCheckN_iReg_imm0",
  /*  752 */  "zeroCheckP_reg_imm0",
  /*  753 */  "cmpF3_reg_reg",
  /*  754 */  "cmpD3_reg_reg",
  /*  755 */  "cmprb_Digit_reg_reg",
  /*  756 */  "cmprb_LowerCase_reg_reg",
  /*  757 */  "cmprb_UpperCase_reg_reg",
  /*  758 */  "cmprb_Whitespace_reg_reg",
  /*  759 */  "cmprb_Whitespace_reg_reg_prefixed",
  /*  760 */  "branch",
  /*  761 */  "branchCon",
  /*  762 */  "branchConFar",
  /*  763 */  "branchLoopEnd",
  /*  764 */  "branchLoopEndFar",
  /*  765 */  "partialSubtypeCheck",
  /*  766 */  "align_addr",
  /*  767 */  "array_size",
  /*  768 */  "inlineCallClearArrayShort",
  /*  769 */  "inlineCallClearArrayLarge",
  /*  770 */  "inlineCallClearArray",
  /*  771 */  "string_compareL",
  /*  772 */  "string_compareU",
  /*  773 */  "string_compareLU",
  /*  774 */  "string_compareUL",
  /*  775 */  "string_equalsL",
  /*  776 */  "string_equalsU",
  /*  777 */  "array_equalsB",
  /*  778 */  "array_equalsC",
  /*  779 */  "indexOf_imm1_char_U",
  /*  780 */  "indexOf_imm1_char_L",
  /*  781 */  "indexOf_imm1_char_UL",
  /*  782 */  "indexOf_imm1_U",
  /*  783 */  "indexOf_imm1_L",
  /*  784 */  "indexOf_imm1_UL",
  /*  785 */  "indexOfChar_U",
  /*  786 */  "indexOfChar_L",
  /*  787 */  "indexOf_imm_U",
  /*  788 */  "indexOf_imm_L",
  /*  789 */  "indexOf_imm_UL",
  /*  790 */  "indexOf_U",
  /*  791 */  "indexOf_L",
  /*  792 */  "indexOf_UL",
  /*  793 */  "string_compress",
  /*  794 */  "string_inflate",
  /*  795 */  "count_positives",
  /*  796 */  "encode_iso_array",
  /*  797 */  "encode_ascii_array",
  /*  798 */  "minI_reg_reg_Ex",
  /*  799 */  "minI_reg_reg_isel",
  /*  800 */  "maxI_reg_reg_Ex",
  /*  801 */  "maxI_reg_reg_isel",
  /*  802 */  "insrwi_a",
  /*  803 */  "insrwi",
  /*  804 */  "bytes_reverse_int_Ex",
  /*  805 */  "bytes_reverse_int_vec",
  /*  806 */  "bytes_reverse_int",
  /*  807 */  "bytes_reverse_long_Ex",
  /*  808 */  "bytes_reverse_long_vec",
  /*  809 */  "bytes_reverse_long",
  /*  810 */  "bytes_reverse_ushort_Ex",
  /*  811 */  "bytes_reverse_ushort",
  /*  812 */  "bytes_reverse_short_Ex",
  /*  813 */  "bytes_reverse_short",
  /*  814 */  "loadI_reversed",
  /*  815 */  "loadI_reversed_acquire",
  /*  816 */  "loadL_reversed",
  /*  817 */  "loadL_reversed_acquire",
  /*  818 */  "loadUS_reversed",
  /*  819 */  "loadUS_reversed_acquire",
  /*  820 */  "loadS_reversed",
  /*  821 */  "loadS_reversed_acquire",
  /*  822 */  "storeI_reversed",
  /*  823 */  "storeL_reversed",
  /*  824 */  "storeUS_reversed",
  /*  825 */  "storeS_reversed",
  /*  826 */  "xxspltw",
  /*  827 */  "vadd16B_reg",
  /*  828 */  "vadd8S_reg",
  /*  829 */  "vadd4I_reg",
  /*  830 */  "vadd4F_reg",
  /*  831 */  "vadd2L_reg",
  /*  832 */  "vadd2D_reg",
  /*  833 */  "vsub16B_reg",
  /*  834 */  "vsub8S_reg",
  /*  835 */  "vsub4I_reg",
  /*  836 */  "vsub4F_reg",
  /*  837 */  "vsub2L_reg",
  /*  838 */  "vsub2D_reg",
  /*  839 */  "vmul8S_reg",
  /*  840 */  "vmul4I_reg",
  /*  841 */  "vmul4F_reg",
  /*  842 */  "vmul2D_reg",
  /*  843 */  "vdiv4F_reg",
  /*  844 */  "vdiv2D_reg",
  /*  845 */  "roundD_reg",
  /*  846 */  "vround2D_reg",
  /*  847 */  "vfma4F",
  /*  848 */  "vfma4F_neg1",
  /*  849 */  "vfma4F_neg1_0",
  /*  850 */  "vfma4F_neg2",
  /*  851 */  "vfma2D",
  /*  852 */  "vfma2D_neg1",
  /*  853 */  "vfma2D_neg1_0",
  /*  854 */  "vfma2D_neg2",
  /*  855 */  "repl4F_immF_Ex",
  /*  856 */  "xxspltd",
  /*  857 */  "xxpermdi",
  /*  858 */  "safePoint_poll",
  /*  859 */  "CallStaticJavaDirect",
  /*  860 */  "CallDynamicJavaDirectSched",
  /*  861 */  "CallDynamicJavaDirectSched_Ex",
  /*  862 */  "CallDynamicJavaDirect",
  /*  863 */  "CallRuntimeDirect",
  /*  864 */  "CallLeafDirect",
  /*  865 */  "CallLeafDirect_Ex",
  /*  866 */  "CallLeafNoFPDirect_Ex",
  /*  867 */  "TailCalljmpInd",
  /*  868 */  "Ret",
  /*  869 */  "tailjmpInd",
  /*  870 */  "CreateException",
  /*  871 */  "RethrowException",
  /*  872 */  "ShouldNotReachHere",
  /*  873 */  "endGroup",
  /*  874 */  "fxNop",
  /*  875 */  "fpNop0",
  /*  876 */  "fpNop1",
  /*  877 */  "brNop0",
  /*  878 */  "brNop1",
  /*  879 */  "brNop2",
  /*  880 */  "cacheWB",
  /*  881 */  "cacheWBPreSync",
  /*  882 */  "cacheWBPostSync",
  /*  883 */  "compareAndSwapP_shenandoah",
  /*  884 */  "compareAndSwapP_shenandoah_0",
  /*  885 */  "compareAndSwapN_shenandoah",
  /*  886 */  "compareAndSwapN_shenandoah_0",
  /*  887 */  "compareAndSwapP_acq_shenandoah",
  /*  888 */  "compareAndSwapP_acq_shenandoah_0",
  /*  889 */  "compareAndSwapN_acq_shenandoah",
  /*  890 */  "compareAndSwapN_acq_shenandoah_0",
  /*  891 */  "compareAndExchangeP_shenandoah",
  /*  892 */  "compareAndExchangeN_shenandoah",
  /*  893 */  "compareAndExchangePAcq_shenandoah",
  /*  894 */  "compareAndExchangeNAcq_shenandoah",
  /*  895 */  "zLoadP",
  /*  896 */  "zLoadP_acq",
  /*  897 */  "zCompareAndSwapP",
  /*  898 */  "zCompareAndSwapP_acq",
  /*  899 */  "zCompareAndSwapPWeak",
  /*  900 */  "zCompareAndSwapPWeak_acq",
  /*  901 */  "zCompareAndExchangeP",
  /*  902 */  "zCompareAndExchangeP_acq",
  /*  903 */  "zGetAndSetP",
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
  /*   50 */  true,
  /*   51 */  true,
  /*   52 */  true,
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
  /*  107 */  false,
  /*  108 */  true,
  // last operand
  /*  109 */  false,
  /*  110 */  false,
  /*  111 */  false,
  /*  112 */  false,
  /*  113 */  false,
  /*  114 */  false,
  // last operand class
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
  /*  219 */  false,
  /*  220 */  false,
  /*  221 */  false,
  /*  222 */  false,
  /*  223 */  false,
  /*  224 */  false,
  // last internally defined operand
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
  /*  811 */  false,
  /*  812 */  false,
  /*  813 */  false,
  /*  814 */  false,
  /*  815 */  false,
  /*  816 */  false,
  /*  817 */  false,
  /*  818 */  false,
  /*  819 */  false,
  /*  820 */  false,
  /*  821 */  false,
  /*  822 */  false,
  /*  823 */  false,
  /*  824 */  false,
  /*  825 */  false,
  /*  826 */  false,
  /*  827 */  false,
  /*  828 */  false,
  /*  829 */  false,
  /*  830 */  false,
  /*  831 */  false,
  /*  832 */  false,
  /*  833 */  false,
  /*  834 */  false,
  /*  835 */  false,
  /*  836 */  false,
  /*  837 */  false,
  /*  838 */  false,
  /*  839 */  false,
  /*  840 */  false,
  /*  841 */  false,
  /*  842 */  false,
  /*  843 */  false,
  /*  844 */  false,
  /*  845 */  false,
  /*  846 */  false,
  /*  847 */  false,
  /*  848 */  false,
  /*  849 */  false,
  /*  850 */  false,
  /*  851 */  false,
  /*  852 */  false,
  /*  853 */  false,
  /*  854 */  false,
  /*  855 */  false,
  /*  856 */  false,
  /*  857 */  false,
  /*  858 */  false,
  /*  859 */  false,
  /*  860 */  false,
  /*  861 */  false,
  /*  862 */  false,
  /*  863 */  false,
  /*  864 */  false,
  /*  865 */  false,
  /*  866 */  false,
  /*  867 */  false,
  /*  868 */  false,
  /*  869 */  false,
  /*  870 */  false,
  /*  871 */  false,
  /*  872 */  false,
  /*  873 */  false,
  /*  874 */  false,
  /*  875 */  false,
  /*  876 */  false,
  /*  877 */  false,
  /*  878 */  false,
  /*  879 */  false,
  /*  880 */  false,
  /*  881 */  false,
  /*  882 */  false,
  /*  883 */  false,
  /*  884 */  false,
  /*  885 */  false,
  /*  886 */  false,
  /*  887 */  false,
  /*  888 */  false,
  /*  889 */  false,
  /*  890 */  false,
  /*  891 */  false,
  /*  892 */  false,
  /*  893 */  false,
  /*  894 */  false,
  /*  895 */  false,
  /*  896 */  false,
  /*  897 */  false,
  /*  898 */  false,
  /*  899 */  false,
  /*  900 */  false,
  /*  901 */  false,
  /*  902 */  false,
  /*  903 */  false,
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
  0, // Allocate: 26
  0, // AllocateArray: 27
  0, // AndI: 28
  0, // AndL: 29
  0, // ArrayCopy: 30
  0, // AryEq: 31
  0, // AtanD: 32
  1, // Binary: 33
  0, // Blackhole: 34
  1, // Bool: 35
  0, // BoxLock: 36
  0, // ReverseBytesI: 37
  0, // ReverseBytesL: 38
  0, // ReverseBytesUS: 39
  0, // ReverseBytesS: 40
  0, // ReverseBytesV: 41
  0, // CProj: 42
  0, // CacheWB: 43
  0, // CacheWBPreSync: 44
  0, // CacheWBPostSync: 45
  0, // CallDynamicJava: 46
  0, // CallJava: 47
  0, // CallLeaf: 48
  0, // CallLeafNoFP: 49
  0, // CallLeafVector: 50
  0, // CallRuntime: 51
  0, // CallStaticJava: 52
  0, // CastDD: 53
  0, // CastFF: 54
  0, // CastII: 55
  0, // CastLL: 56
  0, // CastVV: 57
  0, // CastX2P: 58
  0, // CastP2X: 59
  0, // CastPP: 60
  0, // Catch: 61
  0, // CatchProj: 62
  0, // CheckCastPP: 63
  0, // ClearArray: 64
  0, // CompressBits: 65
  0, // ExpandBits: 66
  0, // ConstraintCast: 67
  0, // CMoveD: 68
  0, // CMoveVD: 69
  0, // CMoveF: 70
  0, // CMoveVF: 71
  0, // CMoveI: 72
  0, // CMoveL: 73
  0, // CMoveP: 74
  0, // CMoveN: 75
  1, // CmpN: 76
  1, // CmpD: 77
  0, // CmpD3: 78
  1, // CmpF: 79
  0, // CmpF3: 80
  1, // CmpI: 81
  1, // CmpL: 82
  0, // CmpL3: 83
  0, // CmpLTMask: 84
  1, // CmpP: 85
  1, // CmpU: 86
  0, // CmpU3: 87
  1, // CmpUL: 88
  0, // CmpUL3: 89
  0, // CompareAndSwapB: 90
  0, // CompareAndSwapS: 91
  0, // CompareAndSwapI: 92
  0, // CompareAndSwapL: 93
  0, // CompareAndSwapP: 94
  0, // CompareAndSwapN: 95
  0, // WeakCompareAndSwapB: 96
  0, // WeakCompareAndSwapS: 97
  0, // WeakCompareAndSwapI: 98
  0, // WeakCompareAndSwapL: 99
  0, // WeakCompareAndSwapP: 100
  0, // WeakCompareAndSwapN: 101
  0, // CompareAndExchangeB: 102
  0, // CompareAndExchangeS: 103
  0, // CompareAndExchangeI: 104
  0, // CompareAndExchangeL: 105
  0, // CompareAndExchangeP: 106
  0, // CompareAndExchangeN: 107
  0, // GetAndAddB: 108
  0, // GetAndAddS: 109
  0, // GetAndAddI: 110
  0, // GetAndAddL: 111
  0, // GetAndSetB: 112
  0, // GetAndSetS: 113
  0, // GetAndSetI: 114
  0, // GetAndSetL: 115
  0, // GetAndSetP: 116
  0, // GetAndSetN: 117
  0, // Con: 118
  0, // ConN: 119
  0, // ConNKlass: 120
  0, // ConD: 121
  0, // ConF: 122
  0, // ConI: 123
  0, // ConL: 124
  0, // ConP: 125
  0, // Conv2B: 126
  0, // ConvD2F: 127
  0, // ConvD2I: 128
  0, // ConvD2L: 129
  0, // ConvF2D: 130
  0, // ConvF2I: 131
  0, // ConvF2L: 132
  0, // ConvI2D: 133
  0, // ConvI2F: 134
  0, // ConvI2L: 135
  0, // ConvL2D: 136
  0, // ConvL2F: 137
  0, // ConvL2I: 138
  0, // ConvF2HF: 139
  0, // ConvHF2F: 140
  0, // CountedLoop: 141
  0, // CountedLoopEnd: 142
  0, // OuterStripMinedLoop: 143
  0, // OuterStripMinedLoopEnd: 144
  0, // LongCountedLoop: 145
  0, // LongCountedLoopEnd: 146
  0, // CountLeadingZerosI: 147
  0, // CountLeadingZerosL: 148
  0, // CountLeadingZerosV: 149
  0, // CountTrailingZerosI: 150
  0, // CountTrailingZerosL: 151
  0, // CountTrailingZerosV: 152
  0, // CreateEx: 153
  0, // DecodeN: 154
  0, // DecodeNKlass: 155
  0, // DivD: 156
  0, // DivF: 157
  0, // DivI: 158
  0, // DivL: 159
  0, // UDivI: 160
  0, // UDivL: 161
  0, // DivMod: 162
  0, // DivModI: 163
  0, // DivModL: 164
  0, // UDivModI: 165
  0, // UDivModL: 166
  0, // EncodeISOArray: 167
  0, // EncodeP: 168
  0, // EncodePKlass: 169
  1, // FastLock: 170
  1, // FastUnlock: 171
  0, // FmaD: 172
  0, // FmaF: 173
  0, // Goto: 174
  0, // Halt: 175
  0, // CountPositives: 176
  0, // If: 177
  0, // RangeCheck: 178
  0, // IfFalse: 179
  0, // IfTrue: 180
  0, // Initialize: 181
  0, // JProj: 182
  0, // Jump: 183
  0, // JumpProj: 184
  0, // LShiftI: 185
  0, // LShiftL: 186
  0, // LoadB: 187
  0, // LoadUB: 188
  0, // LoadUS: 189
  0, // LoadD: 190
  0, // LoadD_unaligned: 191
  0, // LoadF: 192
  0, // LoadI: 193
  0, // LoadKlass: 194
  0, // LoadNKlass: 195
  0, // LoadL: 196
  0, // LoadL_unaligned: 197
  0, // LoadP: 198
  0, // LoadN: 199
  0, // LoadRange: 200
  0, // LoadS: 201
  0, // Lock: 202
  0, // Loop: 203
  0, // LoopLimit: 204
  0, // Mach: 205
  0, // MachNullCheck: 206
  0, // MachProj: 207
  0, // MulAddS2I: 208
  0, // MaxI: 209
  0, // MaxL: 210
  0, // MaxD: 211
  0, // MaxF: 212
  0, // MemBarAcquire: 213
  0, // LoadFence: 214
  0, // MemBarAcquireLock: 215
  0, // MemBarCPUOrder: 216
  0, // MemBarRelease: 217
  0, // StoreFence: 218
  0, // StoreStoreFence: 219
  0, // MemBarReleaseLock: 220
  0, // MemBarVolatile: 221
  0, // MemBarStoreStore: 222
  0, // MergeMem: 223
  0, // MinI: 224
  0, // MinL: 225
  0, // MinF: 226
  0, // MinD: 227
  0, // ModD: 228
  0, // ModF: 229
  0, // ModI: 230
  0, // ModL: 231
  0, // UModI: 232
  0, // UModL: 233
  0, // MoveI2F: 234
  0, // MoveF2I: 235
  0, // MoveL2D: 236
  0, // MoveD2L: 237
  0, // IsInfiniteF: 238
  0, // IsFiniteF: 239
  0, // IsInfiniteD: 240
  0, // IsFiniteD: 241
  0, // MulD: 242
  0, // MulF: 243
  0, // MulHiL: 244
  0, // UMulHiL: 245
  0, // MulI: 246
  0, // MulL: 247
  0, // Multi: 248
  0, // NegI: 249
  0, // NegL: 250
  0, // NegD: 251
  0, // NegF: 252
  0, // NeverBranch: 253
  0, // OnSpinWait: 254
  0, // Opaque1: 255
  0, // OpaqueLoopInit: 256
  0, // OpaqueLoopStride: 257
  0, // OpaqueZeroTripGuard: 258
  0, // Opaque3: 259
  0, // Opaque4: 260
  0, // ProfileBoolean: 261
  0, // OrI: 262
  0, // OrL: 263
  1, // OverflowAddI: 264
  1, // OverflowSubI: 265
  1, // OverflowMulI: 266
  1, // OverflowAddL: 267
  1, // OverflowSubL: 268
  1, // OverflowMulL: 269
  0, // PCTable: 270
  0, // Parm: 271
  0, // PartialSubtypeCheck: 272
  0, // SubTypeCheck: 273
  0, // Phi: 274
  0, // PopCountI: 275
  0, // PopCountL: 276
  0, // PopCountVI: 277
  0, // PopCountVL: 278
  0, // PopulateIndex: 279
  0, // PrefetchAllocation: 280
  0, // Proj: 281
  0, // RShiftI: 282
  0, // RShiftL: 283
  0, // Region: 284
  0, // Rethrow: 285
  0, // Return: 286
  0, // ReverseI: 287
  0, // ReverseL: 288
  0, // ReverseV: 289
  0, // Root: 290
  0, // RoundDouble: 291
  0, // RoundDoubleMode: 292
  0, // RoundDoubleModeV: 293
  0, // RoundFloat: 294
  0, // RotateLeft: 295
  0, // RotateLeftV: 296
  0, // RotateRight: 297
  0, // RotateRightV: 298
  0, // SafePoint: 299
  0, // SafePointScalarObject: 300
  0, // ShenandoahCompareAndExchangeP: 301
  0, // ShenandoahCompareAndExchangeN: 302
  0, // ShenandoahCompareAndSwapN: 303
  0, // ShenandoahCompareAndSwapP: 304
  0, // ShenandoahWeakCompareAndSwapN: 305
  0, // ShenandoahWeakCompareAndSwapP: 306
  0, // ShenandoahIUBarrier: 307
  0, // ShenandoahLoadReferenceBarrier: 308
  0, // SCMemProj: 309
  0, // CopySignD: 310
  0, // CopySignF: 311
  0, // SignumD: 312
  0, // SignumF: 313
  0, // SignumVF: 314
  0, // SignumVD: 315
  0, // SqrtD: 316
  0, // SqrtF: 317
  0, // RoundF: 318
  0, // RoundD: 319
  0, // Start: 320
  0, // StartOSR: 321
  0, // StoreB: 322
  0, // StoreC: 323
  0, // StoreCM: 324
  0, // StoreD: 325
  0, // StoreF: 326
  0, // StoreI: 327
  0, // StoreL: 328
  0, // StoreP: 329
  0, // StoreN: 330
  0, // StoreNKlass: 331
  0, // StrComp: 332
  0, // StrCompressedCopy: 333
  0, // StrEquals: 334
  0, // StrIndexOf: 335
  0, // StrIndexOfChar: 336
  0, // StrInflatedCopy: 337
  0, // SubD: 338
  0, // SubF: 339
  0, // SubI: 340
  0, // SubL: 341
  0, // TailCall: 342
  0, // TailJump: 343
  0, // MacroLogicV: 344
  0, // ThreadLocal: 345
  0, // Unlock: 346
  0, // URShiftB: 347
  0, // URShiftS: 348
  0, // URShiftI: 349
  0, // URShiftL: 350
  0, // XorI: 351
  0, // XorL: 352
  0, // Vector: 353
  0, // AddVB: 354
  0, // AddVS: 355
  0, // AddVI: 356
  0, // AddReductionVI: 357
  0, // AddVL: 358
  0, // AddReductionVL: 359
  0, // AddVF: 360
  0, // AddReductionVF: 361
  0, // AddVD: 362
  0, // AddReductionVD: 363
  0, // SubVB: 364
  0, // SubVS: 365
  0, // SubVI: 366
  0, // SubVL: 367
  0, // SubVF: 368
  0, // SubVD: 369
  0, // MulVB: 370
  0, // MulVS: 371
  0, // MulVI: 372
  0, // MulReductionVI: 373
  0, // MulVL: 374
  0, // MulReductionVL: 375
  0, // MulVF: 376
  0, // MulReductionVF: 377
  0, // MulVD: 378
  0, // MulReductionVD: 379
  0, // MulAddVS2VI: 380
  0, // FmaVD: 381
  0, // FmaVF: 382
  0, // DivVF: 383
  0, // DivVD: 384
  0, // AbsVB: 385
  0, // AbsVS: 386
  0, // AbsVI: 387
  0, // AbsVL: 388
  0, // AbsVF: 389
  0, // AbsVD: 390
  0, // NegVI: 391
  0, // NegVL: 392
  0, // NegVF: 393
  0, // NegVD: 394
  0, // SqrtVD: 395
  0, // SqrtVF: 396
  0, // LShiftCntV: 397
  0, // RShiftCntV: 398
  0, // LShiftVB: 399
  0, // LShiftVS: 400
  0, // LShiftVI: 401
  0, // LShiftVL: 402
  0, // RShiftVB: 403
  0, // RShiftVS: 404
  0, // RShiftVI: 405
  0, // RShiftVL: 406
  0, // URShiftVB: 407
  0, // URShiftVS: 408
  0, // URShiftVI: 409
  0, // URShiftVL: 410
  0, // AndV: 411
  0, // AndReductionV: 412
  0, // OrV: 413
  0, // OrReductionV: 414
  0, // XorV: 415
  0, // XorReductionV: 416
  0, // MinV: 417
  0, // MaxV: 418
  0, // MinReductionV: 419
  0, // MaxReductionV: 420
  0, // CompressV: 421
  0, // CompressM: 422
  0, // ExpandV: 423
  0, // LoadVector: 424
  0, // LoadVectorGather: 425
  0, // LoadVectorGatherMasked: 426
  0, // StoreVector: 427
  0, // StoreVectorScatter: 428
  0, // StoreVectorScatterMasked: 429
  0, // LoadVectorMasked: 430
  0, // StoreVectorMasked: 431
  0, // VectorCmpMasked: 432
  0, // VectorMaskGen: 433
  0, // VectorMaskOp: 434
  0, // VectorMaskTrueCount: 435
  0, // VectorMaskFirstTrue: 436
  0, // VectorMaskLastTrue: 437
  0, // VectorMaskToLong: 438
  0, // VectorLongToMask: 439
  0, // Pack: 440
  0, // PackB: 441
  0, // PackS: 442
  0, // PackI: 443
  0, // PackL: 444
  0, // PackF: 445
  0, // PackD: 446
  0, // Pack2L: 447
  0, // Pack2D: 448
  0, // ReplicateB: 449
  0, // ReplicateS: 450
  0, // ReplicateI: 451
  0, // ReplicateL: 452
  0, // ReplicateF: 453
  0, // ReplicateD: 454
  0, // RoundVF: 455
  0, // RoundVD: 456
  0, // Extract: 457
  0, // ExtractB: 458
  0, // ExtractUB: 459
  0, // ExtractC: 460
  0, // ExtractS: 461
  0, // ExtractI: 462
  0, // ExtractL: 463
  0, // ExtractF: 464
  0, // ExtractD: 465
  0, // Digit: 466
  0, // LowerCase: 467
  0, // UpperCase: 468
  0, // Whitespace: 469
  0, // VectorBox: 470
  0, // VectorBoxAllocate: 471
  0, // VectorUnbox: 472
  0, // VectorMaskWrapper: 473
  0, // VectorMaskCmp: 474
  0, // VectorMaskCast: 475
  0, // VectorTest: 476
  0, // VectorBlend: 477
  0, // VectorRearrange: 478
  0, // VectorLoadMask: 479
  0, // VectorLoadShuffle: 480
  0, // VectorLoadConst: 481
  0, // VectorStoreMask: 482
  0, // VectorReinterpret: 483
  0, // VectorCast: 484
  0, // VectorCastB2X: 485
  0, // VectorCastS2X: 486
  0, // VectorCastI2X: 487
  0, // VectorCastL2X: 488
  0, // VectorCastF2X: 489
  0, // VectorCastD2X: 490
  0, // VectorCastF2HF: 491
  0, // VectorCastHF2F: 492
  0, // VectorUCastB2X: 493
  0, // VectorUCastS2X: 494
  0, // VectorUCastI2X: 495
  0, // VectorizedHashCode: 496
  0, // VectorInsert: 497
  0, // MaskAll: 498
  0, // AndVMask: 499
  0, // OrVMask: 500
  0 // no trailing comma // XorVMask: 501
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
	VSR32->as_VMReg(),
	VSR33->as_VMReg(),
	VSR34->as_VMReg(),
	VSR35->as_VMReg(),
	VSR36->as_VMReg(),
	VSR37->as_VMReg(),
	VSR38->as_VMReg(),
	VSR39->as_VMReg(),
	VSR40->as_VMReg(),
	VSR41->as_VMReg(),
	VSR42->as_VMReg(),
	VSR43->as_VMReg(),
	VSR44->as_VMReg(),
	VSR45->as_VMReg(),
	VSR46->as_VMReg(),
	VSR47->as_VMReg(),
	VSR48->as_VMReg(),
	VSR49->as_VMReg(),
	VSR50->as_VMReg(),
	VSR51->as_VMReg(),
	VSR52->as_VMReg(),
	VSR53->as_VMReg(),
	VSR54->as_VMReg(),
	VSR55->as_VMReg(),
	VSR56->as_VMReg(),
	VSR57->as_VMReg(),
	VSR58->as_VMReg(),
	VSR59->as_VMReg(),
	VSR60->as_VMReg(),
	VSR61->as_VMReg(),
	VSR62->as_VMReg(),
	VSR63->as_VMReg(),
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
MachNode *branchLoopEndFarNode::short_branch_version() {
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

int storeCMNode::reloc() const {
  return 2;
}

int cmovP_regNode::reloc() const {
  return 1;
}

int cmovP_immNode::reloc() const {
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

int addP_reg_imm34Node::reloc() const {
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

int repl2D_immD0Node::reloc() const {
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

int zLoadPNode::reloc() const {
  return 1;
}

int zLoadP_acqNode::reloc() const {
  return 1;
}


void convB2I_reg_2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 5119 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ extsb(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 9017 "ad_ppc.cpp"
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

#line 2458 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9039 "ad_ppc.cpp"
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

#line 2465 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9063 "ad_ppc.cpp"
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

#line 2458 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9085 "ad_ppc.cpp"
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

#line 2465 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9109 "ad_ppc.cpp"
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

#line 2458 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9131 "ad_ppc.cpp"
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

#line 2465 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9155 "ad_ppc.cpp"
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

#line 2458 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9177 "ad_ppc.cpp"
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

#line 2465 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lbz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9201 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5276 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lha(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9223 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5292 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lha(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9247 "ad_ppc.cpp"
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

#line 2473 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lhz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9270 "ad_ppc.cpp"
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

#line 2481 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lhz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9295 "ad_ppc.cpp"
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

#line 2473 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lhz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9318 "ad_ppc.cpp"
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

#line 2481 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lhz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9343 "ad_ppc.cpp"
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

#line 2490 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9366 "ad_ppc.cpp"
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

#line 2498 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9391 "ad_ppc.cpp"
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

#line 2490 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9415 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5398 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwa(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9437 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5414 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwa(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9461 "ad_ppc.cpp"
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

#line 2507 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9485 "ad_ppc.cpp"
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

#line 2516 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9511 "ad_ppc.cpp"
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

#line 2507 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9535 "ad_ppc.cpp"
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

#line 2507 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9559 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5482 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ lxvd2x(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 9580 "ad_ppc.cpp"
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

#line 2490 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9603 "ad_ppc.cpp"
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

#line 2490 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9626 "ad_ppc.cpp"
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

#line 2498 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9651 "ad_ppc.cpp"
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

#line 2490 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9674 "ad_ppc.cpp"
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

#line 2490 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9697 "ad_ppc.cpp"
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

#line 2507 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9721 "ad_ppc.cpp"
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

#line 2516 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 9747 "ad_ppc.cpp"
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

#line 2507 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9771 "ad_ppc.cpp"
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

#line 2490 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9794 "ad_ppc.cpp"
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

#line 2507 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9818 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5617 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lfs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9840 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5636 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    Label next;
    __ lfs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ fcmpu(CCR0, opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(0)->as_FloatRegister(ra_,this)/* dst */);
    __ bne(CCR0, next);
    __ bind(next);
    __ isync();
  
#line 9868 "ad_ppc.cpp"
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

#line 2526 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lfd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9890 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5672 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    Label next;
    __ lfd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
    __ fcmpu(CCR0, opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(0)->as_FloatRegister(ra_,this)/* dst */);
    __ bne(CCR0, next);
    __ bind(next);
    __ isync();
  
#line 9918 "ad_ppc.cpp"
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

#line 2526 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lfd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 9940 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5706 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ calculate_address_from_global_toc_hi16only(opnd_array(0)->as_Register(ra_,this)/* dst */, __ method_toc());
  
#line 9961 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5719 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ calculate_address_from_global_toc_lo16only(opnd_array(0)->as_Register(ra_,this)/* dst */, __ method_toc());
  
#line 9982 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5731 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 10003 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5744 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // Lis sign extends 16-bit src then shifts it 16 bit to the left.
    __ lis(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)((opnd_array(1)->constant()& 0xFFFF0000) >> 16)));
  
#line 10025 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5760 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0xFFFF);
  
#line 10047 "ad_ppc.cpp"
  }
}

uint loadConI32_lo16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConI32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 5775 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    assert( ((intptr_t)(__ pc()) & 0x3c) != 0x3c, "Bad alignment for prefixed instruction at " INTPTR_FORMAT, (intptr_t)(__ pc()));
    __ pli(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constant());
  
#line 10069 "ad_ppc.cpp"
  }
}

uint loadConI32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void loadConL16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 5804 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short) (opnd_array(1)->constantL()& 0xFFFF)));
  
#line 10090 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5817 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ lis(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)((opnd_array(1)->constantL()& 0xFFFF0000) >> 16)));
  
#line 10111 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5832 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constantL()) & 0xFFFF);
  
#line 10133 "ad_ppc.cpp"
  }
}

uint loadConL32_lo16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadConL34Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 5864 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    assert( ((intptr_t)(__ pc()) & 0x3c) != 0x3c, "Bad alignment for prefixed instruction at " INTPTR_FORMAT, (intptr_t)(__ pc()));
    __ pli(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->constantL());
  
#line 10155 "ad_ppc.cpp"
  }
}

uint loadConL34Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void loadConLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  {

#line 2532 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
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
  
#line 10195 "ad_ppc.cpp"
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

#line 2555 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);

    if (!ra_->C->output()->in_scratch_emit_size()) {
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
  
#line 10238 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5929 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int offset = ra_->C->output()->in_scratch_emit_size() ? 0 : _const_toc_offset_hi_node->_const_toc_offset;
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, MacroAssembler::largeoffset_si16_si16_lo(offset), opnd_array(2)->as_Register(ra_,this,idx2)/* base */);
  
#line 10261 "ad_ppc.cpp"
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
#line 2774 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 10301 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5955 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, 0);
  
#line 10320 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5968 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ lis(opnd_array(0)->as_Register(ra_,this)/* dst */, 0); // Will get patched.
  
#line 10341 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5981 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    AddressLiteral addrlit = __ constant_oop_address((jobject)opnd_array(2)->constant());
    __ relocate(addrlit.rspec(), /*compressed format*/ 1);
    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 0); // Will get patched.
  
#line 10365 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 5993 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ rldicl(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->constant(), opnd_array(3)->constant());
  
#line 10388 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6009 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0x20);
  
#line 10409 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6021 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ load_const_optimized(opnd_array(0)->as_Register(ra_,this)/* dst */, CompressedOops::base(), R0);
  
#line 10430 "ad_ppc.cpp"
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
#line 6035 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 10470 "ad_ppc.cpp"
  }
}

void loadConNKlass_hiNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6068 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    intptr_t Csrc = CompressedKlassPointers::encode((Klass *)opnd_array(1)->constant());
    __ lis(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)(short)((Csrc >> 16) & 0xffff));
  
#line 10487 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6083 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0x20);
  
#line 10509 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6098 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // Notify OOP recorder (don't need the relocation)
    AddressLiteral md = __ constant_metadata_address((Klass*)opnd_array(1)->constant());
    intptr_t Csrc = CompressedKlassPointers::encode((Klass*)md.value());
    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, Csrc & 0xffff);
  
#line 10534 "ad_ppc.cpp"
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
#line 6114 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // Load high bits into register. Sign extended.
    MachNode *m1 = new loadConNKlass_hiNode();
    m1->add_req(NULL);
    m1->_opnds[0] = op_dst;
    m1->_opnds[1] = op_src;
    ra_->set_pair(m1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    nodes->push(m1);

    MachNode *m2 = m1;
    if (!Assembler::is_uimm((jlong)CompressedKlassPointers::encode((Klass *)op_src->constant()), 31)) {
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
  
#line 10587 "ad_ppc.cpp"
  }
}

void loadConP0or1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6152 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 10603 "ad_ppc.cpp"
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

#line 2789 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
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
  
#line 10652 "ad_ppc.cpp"
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

#line 2821 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    if (!ra_->C->output()->in_scratch_emit_size()) {
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
  
#line 10703 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6199 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int offset = ra_->C->output()->in_scratch_emit_size() ? 0 : _const_toc_offset_hi_node->_const_toc_offset;
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, MacroAssembler::largeoffset_si16_si16_lo(offset), opnd_array(2)->as_Register(ra_,this,idx2)/* base */);
  
#line 10726 "ad_ppc.cpp"
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
#line 2858 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 10800 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6235 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    address float_address = __ float_constant(opnd_array(1)->constantF());
    if (float_address == NULL) {
      ciEnv::current()->record_out_of_memory_failure();
      return;
    }
    __ lfs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, __ offset_to_method_toc(float_address), opnd_array(2)->as_Register(ra_,this,idx2)/* toc */);
  
#line 10825 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6257 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 10860 "ad_ppc.cpp"
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
#line 2909 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 10907 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6297 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    address float_address = __ double_constant(opnd_array(1)->constantD());
    if (float_address == NULL) {
      ciEnv::current()->record_out_of_memory_failure();
      return;
    }
    int offset =  __ offset_to_method_toc(float_address);
    __ lfd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, offset, opnd_array(2)->as_Register(ra_,this,idx2)/* toc */);
  
#line 10933 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6320 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 10968 "ad_ppc.cpp"
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
#line 2933 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 11015 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6362 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ dcbz(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11035 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6375 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ dcbz(as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11056 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6388 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ dcbtst(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11078 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6401 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ dcbtst(as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11099 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6416 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stb(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11122 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6430 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ sth(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11145 "ad_ppc.cpp"
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

#line 2955 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stw(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11168 "ad_ppc.cpp"
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

#line 2955 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stw(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11191 "ad_ppc.cpp"
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

#line 2961 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ std(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11216 "ad_ppc.cpp"
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

#line 2961 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ std(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11241 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6492 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ stxvd2x(opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 11263 "ad_ppc.cpp"
  }
}

uint storeV16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void reinterpretLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

void reinterpretXNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

void storeNNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 2955 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stw(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11302 "ad_ppc.cpp"
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

#line 2955 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stw(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11325 "ad_ppc.cpp"
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

#line 2961 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ std(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11350 "ad_ppc.cpp"
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

#line 2969 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stfs(opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11373 "ad_ppc.cpp"
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

#line 2975 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ stfd(opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11396 "ad_ppc.cpp"
  }
}

uint storeDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void storeCMNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6579 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(R0, 0);
    // No release barrier: Oops are allowed to get visible after marking.
    guarantee(as_Register(opnd_array(1)->base(ra_,this,idx1))!= R1_SP, "use frame_slots_bias");
    __ stb(R0, opnd_array(1)->disp(ra_,this,idx1), as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 11421 "ad_ppc.cpp"
  }
}

uint storeCMNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void encodeP_shiftNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6600 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, CompressedOops::shift() & 0x3f);
  
#line 11442 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6613 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sub_const_optimized(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, CompressedOops::base(), R0);
  
#line 11463 "ad_ppc.cpp"
  }
}

void cond_sub_baseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6628 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Label done;
    __ beq(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ sub_const_optimized(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, CompressedOops::base(), R0);
    __ bind(done);
  
#line 11483 "ad_ppc.cpp"
  }
}

void cond_set_0_oopNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6645 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description exists.
    __ isel_0(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, Assembler::equal, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */);
  
#line 11501 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6659 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ rldicl(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 64-CompressedOops::shift(), 32);
  
#line 11522 "ad_ppc.cpp"
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
#line 2981 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


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
  
#line 11633 "ad_ppc.cpp"
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
#line 3065 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


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
  
#line 11672 "ad_ppc.cpp"
  }
}

void encodeP_not_null_base_nullNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6697 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, CompressedOops::shift() & 0x3f);
  
#line 11688 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6711 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 11709 "ad_ppc.cpp"
  }
}

void decodeN_shiftNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6727 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, CompressedOops::shift());
  
#line 11725 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6740 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ add_const_optimized(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, CompressedOops::base(), R0);
  
#line 11746 "ad_ppc.cpp"
  }
}

void cond_add_baseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6758 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Label done;
    __ beq(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ add_const_optimized(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, CompressedOops::base(), R0);
    __ bind(done);
  
#line 11766 "ad_ppc.cpp"
  }
}

void cond_set_0_ptrNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6777 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description exists.
    __ isel_0(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, Assembler::equal, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */);
  
#line 11784 "ad_ppc.cpp"
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
#line 3086 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 11877 "ad_ppc.cpp"
  }
}

void decodeN_nullBaseNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6806 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, CompressedOops::shift());
  
#line 11893 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6822 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ rldimi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, CompressedOops::shift(), 32-CompressedOops::shift());
  
#line 11915 "ad_ppc.cpp"
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
#line 6842 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    loadBaseNode *n1 = new loadBaseNode();
    n1->add_req(NULL);
    n1->_opnds[0] = op_dst;

    decodeN_mergeDisjointNode *n2 = new decodeN_mergeDisjointNode();
    n2->add_req(n_region, n_src, n1);
    n2->_opnds[0] = op_dst;
    n2->_opnds[1] = op_src;
    n2->_opnds[2] = op_dst;
    n2->_bottom_type = _bottom_type;

    assert(ra_->is_oop(this) == true, "A decodeN node must produce an oop!");
    ra_->set_oop(n2, true);

    ra_->set_pair(n1->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));
    ra_->set_pair(n2->_idx, ra_->get_reg_second(this), ra_->get_reg_first(this));

    nodes->push(n1);
    nodes->push(n2);
  
#line 11961 "ad_ppc.cpp"
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
#line 6874 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 12023 "ad_ppc.cpp"
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
#line 3152 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 12063 "ad_ppc.cpp"
  }
}

void decodeN_unscaledNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6935 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 12079 "ad_ppc.cpp"
  }
}

void decodeN2I_unscaledNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6949 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 12095 "ad_ppc.cpp"
  }
}

void encodePKlass_shiftNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 6967 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, CompressedKlassPointers::shift());
  
#line 12111 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6981 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ subf(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* base */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */);
  
#line 12133 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 6994 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ rldicl(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 64-CompressedKlassPointers::shift(), 32);
  
#line 12154 "ad_ppc.cpp"
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
#line 7006 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 12201 "ad_ppc.cpp"
  }
}

void decodeNKlass_shiftNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 7053 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, CompressedKlassPointers::shift());
  
#line 12217 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7068 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* base */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */);
  
#line 12239 "ad_ppc.cpp"
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
#line 7081 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 12287 "ad_ppc.cpp"
  }
}

void membar_acquireNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    C2_MacroAssembler _masm(&cbuf);

#line 7131 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ acquire();
  
#line 12303 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7164 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ release();
  
#line 12350 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7164 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ release();
  
#line 12371 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7177 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ membar(Assembler::StoreStore);
  
#line 12392 "ad_ppc.cpp"
  }
}

uint membar_storestoreNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void membar_storestore_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    C2_MacroAssembler _masm(&cbuf);

#line 7177 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ membar(Assembler::StoreStore);
  
#line 12413 "ad_ppc.cpp"
  }
}

uint membar_storestore_0Node::size(PhaseRegAlloc *ra_) const {
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
    C2_MacroAssembler _masm(&cbuf);

#line 7199 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fence();
  
#line 12447 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7255 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description
    // exists. Anyways, the scheduler should be off on Power7.
    int cc        = opnd_array(1)->ccode();
    __ isel(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */,
            (Assembler::Condition)(cc & 3), /*invert*/((~cc) & 8), opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
  
#line 12488 "ad_ppc.cpp"
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

#line 3174 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int cc        = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(cc), cc_to_biint(cc, flags_reg), done);
    __ mr(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
    __ bind(done);
  
#line 12520 "ad_ppc.cpp"
  }
}

uint cmovI_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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

#line 3187 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ li(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->constant());
    __ bind(done);
  
#line 12550 "ad_ppc.cpp"
  }
}

uint cmovI_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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
    C2_MacroAssembler _masm(&cbuf);

#line 7300 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description
    // exists. Anyways, the scheduler should be off on Power7.
    int cc        = opnd_array(1)->ccode();
    __ isel(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */,
            (Assembler::Condition)(cc & 3), /*invert*/((~cc) & 8), opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
  
#line 12578 "ad_ppc.cpp"
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

#line 3174 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int cc        = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(cc), cc_to_biint(cc, flags_reg), done);
    __ mr(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
    __ bind(done);
  
#line 12610 "ad_ppc.cpp"
  }
}

uint cmovL_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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

#line 3187 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ li(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->constantL());
    __ bind(done);
  
#line 12640 "ad_ppc.cpp"
  }
}

uint cmovL_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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
    C2_MacroAssembler _masm(&cbuf);

#line 7345 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description
    // exists. Anyways, the scheduler should be off on Power7.
    int cc        = opnd_array(1)->ccode();
    __ isel(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */,
            (Assembler::Condition)(cc & 3), /*invert*/((~cc) & 8), opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
  
#line 12668 "ad_ppc.cpp"
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

#line 3174 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int cc        = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(cc), cc_to_biint(cc, flags_reg), done);
    __ mr(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
    __ bind(done);
  
#line 12700 "ad_ppc.cpp"
  }
}

uint cmovN_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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

#line 3187 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ li(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->constant());
    __ bind(done);
  
#line 12730 "ad_ppc.cpp"
  }
}

uint cmovN_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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
    C2_MacroAssembler _masm(&cbuf);

#line 7391 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // This is a Power7 instruction for which no machine description
    // exists. Anyways, the scheduler should be off on Power7.
    int cc        = opnd_array(1)->ccode();
    __ isel(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */,
            (Assembler::Condition)(cc & 3), /*invert*/((~cc) & 8), opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
  
#line 12758 "ad_ppc.cpp"
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

#line 3174 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int cc        = opnd_array(1)->ccode();
    int flags_reg = opnd_array(2)->reg(ra_,this,idx2)/* crx */;
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(cc), cc_to_biint(cc, flags_reg), done);
    __ mr(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* src */);
    __ bind(done);
  
#line 12790 "ad_ppc.cpp"
  }
}

uint cmovP_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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

#line 3187 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ li(opnd_array(3)->as_Register(ra_,this,idx3)/* dst */, opnd_array(4)->constant());
    __ bind(done);
  
#line 12820 "ad_ppc.cpp"
  }
}

uint cmovP_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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
    C2_MacroAssembler _masm(&cbuf);

#line 7437 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ fmr(opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */, opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */);
    __ bind(done);
  
#line 12849 "ad_ppc.cpp"
  }
}

uint cmovF_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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
    C2_MacroAssembler _masm(&cbuf);

#line 7457 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Label done;
    assert((Assembler::bcondCRbiIs1 & ~Assembler::bcondCRbiIs0) == 8, "check encoding");
    // Branch if not (cmp crx).
    __ bc(cc_to_inverse_boint(opnd_array(1)->ccode()), cc_to_biint(opnd_array(1)->ccode(), opnd_array(2)->reg(ra_,this,idx2)/* crx */), done);
    __ fmr(opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* dst */, opnd_array(4)->as_FloatRegister(ra_,this,idx4)/* src */);
    __ bind(done);
  
#line 12878 "ad_ppc.cpp"
  }
}

uint cmovD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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
    C2_MacroAssembler _masm(&cbuf);

#line 7481 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12911 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7500 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12941 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7519 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12969 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7538 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 12999 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7556 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13027 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7574 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13055 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7592 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13083 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7611 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13111 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7632 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13134 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7646 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13159 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7660 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13182 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7674 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13207 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7688 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13230 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7702 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13255 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7716 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13278 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7730 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13303 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7744 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13326 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7758 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    // Acquire only needed in successful case. Weak node is allowed to report unsuccessful in additional rare cases and
    // value is never passed to caller.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13351 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7774 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13374 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7788 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    // Acquire only needed in successful case. Weak node is allowed to report unsuccessful in additional rare cases and
    // value is never passed to caller.
    __ cmpxchgw(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, true, /*weak*/ true);
  
#line 13399 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7804 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    // value is never passed to caller.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true, /*weak*/ true);
  
#line 13423 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7819 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    // Acquire only needed in successful case. Weak node is allowed to report unsuccessful in additional rare cases and
    // value is never passed to caller.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true, /*weak*/ true);
  
#line 13448 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7835 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true, /*weak*/ true);
  
#line 13471 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7849 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    // Acquire only needed in successful case. Weak node is allowed to report unsuccessful in additional rare cases and
    // value is never passed to caller.
    __ cmpxchgd(CCR0, R0, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                support_IRIW_for_not_multiple_copy_atomic_cpu ? MacroAssembler::MemBarAcq : MacroAssembler::MemBarFenceAfter,
                MacroAssembler::cmpxchgx_hint_atomic_update(), opnd_array(4)->as_Register(ra_,this,idx4)/* res */, NULL, true, /*weak*/ true);
  
#line 13496 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7867 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13519 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7881 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgb(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, R0,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13543 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7895 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 13572 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7915 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 13602 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7935 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, noreg, noreg,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13625 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7949 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgh(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, R0,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13649 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7963 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 13678 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 7983 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 13708 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8003 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13731 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8017 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 13760 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8037 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgw(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, true);
  
#line 13783 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8051 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 13812 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8071 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, NULL, true);
  
#line 13835 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8085 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 13864 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8106 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // CmpxchgX sets CCR0 to cmpX(src1, src2) and Rres to 'true'/'false'.
    __ cmpxchgd(CCR0, opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                MacroAssembler::MemBarNone, MacroAssembler::cmpxchgx_hint_atomic_update(),
                noreg, NULL, true);
  
#line 13887 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8121 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 13916 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8143 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddb(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, noreg, noreg, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13941 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8160 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddb(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13968 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8177 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddh(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, noreg, noreg, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 13993 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8194 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddh(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14020 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8210 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddw(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14045 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8226 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandaddd(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14070 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8243 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetb(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  noreg, noreg, noreg, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14095 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8260 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetb(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14122 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8277 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandseth(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  noreg, noreg, noreg, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14147 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8294 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandseth(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  R0, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14174 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8310 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetw(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14199 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8326 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetd(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14224 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8343 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetd(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14249 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8359 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ getandsetw(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem_ptr */,
                  MacroAssembler::cmpxchgx_hint_atomic_update());
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 14274 "ad_ppc.cpp"
  }
}

void addI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 8379 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14291 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8391 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14313 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8416 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ addi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 14335 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8427 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ addis(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant())>>16);
  
#line 14357 "ad_ppc.cpp"
  }
}

uint addI_reg_immhi16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addI_reg_imm32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 8440 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    assert( ((intptr_t)(__ pc()) & 0x3c) != 0x3c, "Bad alignment for prefixed instruction at " INTPTR_FORMAT, (intptr_t)(__ pc()));
    __ paddi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 14380 "ad_ppc.cpp"
  }
}

uint addI_reg_imm32Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void addL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 8453 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14402 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8465 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14424 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8491 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14446 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8503 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ addi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 14468 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8516 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ addis(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constantL())>>16);
  
#line 14490 "ad_ppc.cpp"
  }
}

uint addL_reg_immhi16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addL_reg_imm34Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 8531 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    assert( ((intptr_t)(__ pc()) & 0x3c) != 0x3c, "Bad alignment for prefixed instruction at " INTPTR_FORMAT, (intptr_t)(__ pc()));
    __ paddi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 14513 "ad_ppc.cpp"
  }
}

uint addL_reg_imm34Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void addP_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 8544 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ add(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14535 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8557 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ addi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 14557 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8570 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ addis(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constantL())>>16);
  
#line 14579 "ad_ppc.cpp"
  }
}

uint addP_reg_immhi16Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void addP_reg_imm34Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 8585 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    assert( ((intptr_t)(__ pc()) & 0x3c) != 0x3c, "Bad alignment for prefixed instruction at " INTPTR_FORMAT, (intptr_t)(__ pc()));
    __ paddi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 14602 "ad_ppc.cpp"
  }
}

uint addP_reg_imm34Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void subI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 8601 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ subf(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 14624 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8617 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ subfic(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(1)->constant());
  
#line 14646 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8632 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srawi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0x1f);
  
#line 14667 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8655 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ neg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14689 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8666 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ subf(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 14711 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8678 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ subf(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 14733 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8693 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sradi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0x3f);
  
#line 14754 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8708 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sradi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0x3f);
  
#line 14775 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8732 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ neg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14797 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8744 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ neg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14819 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8760 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mullw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14841 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8773 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mulli(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 14863 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8785 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mulld(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14885 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8798 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mulhd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14907 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8811 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mulli(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 14929 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8824 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ neg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 14951 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8840 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ divw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 14973 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8855 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Label done;
    __ bne(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, done);
    __ neg(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* src1 */);
    __ bind(done);
  
#line 14999 "ad_ppc.cpp"
  }
}

uint cmovI_bne_negI_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void divL_reg_immLvalueMinus1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 8885 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ neg(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 15021 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8899 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ divd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15043 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 8914 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Label done;
    __ bne(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, done);
    __ neg(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* src1 */);
    __ bind(done);
  
#line 15069 "ad_ppc.cpp"
  }
}

uint cmovL_bne_negL_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void udivI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 8977 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ divwu(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15091 "ad_ppc.cpp"
  }
}

uint udivI_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void udivL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 9000 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ divdu(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15113 "ad_ppc.cpp"
  }
}

uint udivL_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void maskI_reg_immNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {
    C2_MacroAssembler _masm(&cbuf);

#line 9030 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->constant());
  
#line 15135 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9043 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ slw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15157 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9066 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ slwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x1f);
  
#line 15179 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9079 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    long src3      = opnd_array(3)->constant();
    long maskbits  = src3 + log2i_exact(-(juint)opnd_array(2)->constant());
    if (maskbits >= 32) {
      __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, 0); // addi
    } else {
      __ rlwinm(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, src3 & 0x1f, 0, (31-maskbits) & 0x1f);
    }
  
#line 15208 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9098 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    long src3      = opnd_array(2)->constant();
    long maskbits  = src3 + log2i_exact(-(juint)opnd_array(3)->constant());
    if (maskbits >= 32) {
      __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, 0); // addi
    } else {
      __ rlwinm(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 0, 0, (31-maskbits) & 0x1f);
    }
  
#line 15237 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9117 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sld(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15259 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9140 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15281 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9153 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15303 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9167 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrlsldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 0x20, opnd_array(2)->constant());
  
#line 15325 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9180 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sraw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15347 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9204 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srawi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x1f);
  
#line 15369 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9217 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srad(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15391 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9242 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sradi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15413 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9254 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sradi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15435 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9267 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15457 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9292 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x1f);
  
#line 15479 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9305 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 15501 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9330 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15523 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9342 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15545 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9354 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0x3f);
  
#line 15567 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9366 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int rshift = (opnd_array(2)->constant()) & 0x1f;
    int length = log2i_exact((juint)opnd_array(3)->constant()+ 1u);
    if (rshift + length > 32) {
      // if necessary, adjust mask to omit rotated bits.
      length = 32 - rshift;
    }
    __ extrdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, length, 64 - (rshift + length));
  
#line 15596 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9384 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int rshift  = (opnd_array(2)->constant()) & 0x3f;
    int length = log2i_exact((julong)opnd_array(3)->constantL()+ 1ull);
    if (rshift + length > 64) {
      // if necessary, adjust mask to omit rotated bits.
      length = 64 - rshift;
    }
    __ extrdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, length, 64 - (rshift + length));
  
#line 15625 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9401 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ extsw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 15646 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9416 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ rotlwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->constant());
  
#line 15669 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9416 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ rotlwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(3)->constant());
  
#line 15692 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9429 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ rotrwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->constant());
  
#line 15715 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9429 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ rotrwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(3)->constant());
  
#line 15738 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9443 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fadds(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15760 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9455 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fadd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15782 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9467 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fsubs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15804 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9478 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fsub(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15826 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9489 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fmuls(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15848 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9500 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fmul(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15870 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9511 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fdivs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15892 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9522 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fdiv(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 15914 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9533 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fabs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15935 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9544 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fabs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15956 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9554 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fneg(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15977 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9564 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fneg(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 15998 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9575 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fnabs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 16019 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9586 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fnabs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 16040 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9598 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fsqrt(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 16061 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9612 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fsqrts(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 16082 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9648 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fmadds(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16131 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9660 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fmadd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16154 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9673 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fnmsubs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16177 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9673 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fnmsubs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16200 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9686 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fnmsub(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16223 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9686 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fnmsub(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16246 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9699 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fnmadds(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16269 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9699 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fnmadds(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16292 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9712 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fnmadd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16315 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9712 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fnmadd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16338 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9724 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fmsubs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16361 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9736 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fmsub(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_FloatRegister(ra_,this,idx3)/* src2 */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src3 */);
  
#line 16384 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9752 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ andr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16406 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9764 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ andis_(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (int)((unsigned short)((opnd_array(2)->constant()& 0xFFFF0000) >> 16)));
  
#line 16428 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9777 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // FIXME: avoid andi_ ?
    __ andi_(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 16451 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9789 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrrdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, log2i_exact(-(juint)opnd_array(2)->constant()));
  
#line 16473 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9799 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 64 - log2i_exact((juint)opnd_array(2)->constant()+ 1u));
  
#line 16495 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9810 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int bitpos = 31 - log2i_exact((juint)opnd_array(2)->constant());
    __ rlwinm(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 0, bitpos, bitpos);
  
#line 16518 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9824 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ andr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16540 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9837 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // FIXME: avoid andi_ ?
    __ andi_(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 16563 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9849 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrrdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, log2i_exact(-(julong)opnd_array(2)->constantL()));
  
#line 16585 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9859 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 64 - log2i_exact((julong)opnd_array(2)->constantL()+ 1ull));
  
#line 16607 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9872 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 64 - log2i_exact((julong)opnd_array(2)->constantL()+ 1ull));
  
#line 16629 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9885 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ or_unchecked(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16651 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9897 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ or_unchecked(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16673 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9922 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constant()) & 0xFFFF);
  
#line 16695 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9935 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ or_unchecked(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16717 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9948 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ or_unchecked(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16739 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9961 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ ori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (opnd_array(2)->constantL()) & 0xFFFF);
  
#line 16761 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9974 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xorr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16783 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 9986 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xorr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16805 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10011 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 16827 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10024 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xorr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16849 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10037 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xorr(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 16871 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10050 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xori(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 16893 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10062 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ nor(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 16915 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10074 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ nor(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 16937 "ad_ppc.cpp"
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

#line 3200 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    __ andc(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* src3 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */);
  
#line 16960 "ad_ppc.cpp"
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

#line 3200 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    __ andc(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src3 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src1 */);
  
#line 16983 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10099 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ andc(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 17005 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10127 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mtfprd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17026 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10140 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mtfprwa(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17047 "ad_ppc.cpp"
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

#line 2490 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 17070 "ad_ppc.cpp"
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

#line 2955 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    __ stw(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 17092 "ad_ppc.cpp"
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

#line 2507 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 17116 "ad_ppc.cpp"
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

#line 2961 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ std(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 17140 "ad_ppc.cpp"
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

#line 2490 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lwz(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 17163 "ad_ppc.cpp"
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

#line 2969 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    __ stfs(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 17185 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10225 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    int Idisp = opnd_array(1)->disp(ra_,this,idx1)+ frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lfs(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 17207 "ad_ppc.cpp"
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

#line 2955 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    __ stw(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 17229 "ad_ppc.cpp"
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

#line 2975 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    __ stfd(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 17251 "ad_ppc.cpp"
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

#line 2507 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 17275 "ad_ppc.cpp"
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

#line 2975 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    __ stfd(opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 17297 "ad_ppc.cpp"
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

#line 2526 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(1)->disp(ra_,this,idx1) + frame_slots_bias(opnd_array(1)->base(ra_,this,idx1), ra_);
    __ lfd(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, Idisp, as_Register(opnd_array(1)->base(ra_,this,idx1)));
  
#line 17319 "ad_ppc.cpp"
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

#line 2961 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(0)->disp(ra_,this,0) + frame_slots_bias(opnd_array(0)->base(ra_,this,idx0), ra_);
    // Operand 'ds' requires 4-alignment.
    assert((Idisp & 0x3) == 0, "unaligned offset");
    __ std(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, Idisp, as_Register(opnd_array(0)->base(ra_,this,idx0)));
  
#line 17343 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10312 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17364 "ad_ppc.cpp"
  }
}

void castX2PNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 10326 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17380 "ad_ppc.cpp"
  }
}

void castP2XNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 10338 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17396 "ad_ppc.cpp"
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

void castLLNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castLLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castFFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castFFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castDDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castDDNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castVV8Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castVV8Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 0, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 0);
}

void castVV16Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  // User did not define which encode class to use.
}

uint castVV16Node::size(PhaseRegAlloc *ra_) const {
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

#line 3205 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);

    Label done;
    __ cmpwi(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x0));
    __ beq(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, done);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x1));
    __ bind(done);
  
#line 17524 "ad_ppc.cpp"
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

#line 3205 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);

    Label done;
    __ cmpwi(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x1));
    __ beq(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, done);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x0));
    __ bind(done);
  
#line 17554 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10492 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ rlwinm(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 32 - log2i_exact((juint)(opnd_array(2)->constant())), 31, 31);
  
#line 17576 "ad_ppc.cpp"
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

#line 3217 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);

    Label done;
    __ cmpdi(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x0));
    __ beq(opnd_array(2)->as_ConditionRegister(ra_,this,idx2)/* crx */, done);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x1));
    __ bind(done);
  
#line 17605 "ad_ppc.cpp"
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

#line 3217 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);

    Label done;
    __ cmpdi(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 0);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x1));
    __ beq(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, done);
    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (0x0));
    __ bind(done);
  
#line 17635 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10593 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ srawi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, 0x1f);
  
#line 17657 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10610 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ extsb(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17679 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10620 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ extsh(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17700 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10631 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ extsh(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17722 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10643 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ extsw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17743 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10653 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mr_if_needed(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 17764 "ad_ppc.cpp"
  }
}

void convD2IRaw_regDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 10666 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fctiwz(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 17780 "ad_ppc.cpp"
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

#line 3229 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(2)->disp(ra_,this,idx2) + frame_slots_bias(opnd_array(2)->base(ra_,this,idx2), ra_);
    Label done;
    __ bso(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(2)->base(ra_,this,idx2)));
    __ bind(done);
  
#line 17807 "ad_ppc.cpp"
  }
}

uint cmovI_bso_stackSlotLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void cmovI_bso_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3239 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    Label done;
    __ bso(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ mffprd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src */);
    __ bind(done);
  
#line 17833 "ad_ppc.cpp"
  }
}

uint cmovI_bso_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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
#line 10706 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 17907 "ad_ppc.cpp"
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
#line 10760 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 17976 "ad_ppc.cpp"
  }
}

void convF2IRaw_regFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 10847 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fctiwz(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 17992 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10891 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ extsw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 18013 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10904 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 32);
  
#line 18035 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10917 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrldi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, 32);
  
#line 18057 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 10930 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fctidz(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 18078 "ad_ppc.cpp"
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

#line 3229 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    int Idisp = opnd_array(2)->disp(ra_,this,idx2) + frame_slots_bias(opnd_array(2)->base(ra_,this,idx2), ra_);
    Label done;
    __ bso(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ ld(opnd_array(0)->as_Register(ra_,this)/* dst */, Idisp, as_Register(opnd_array(2)->base(ra_,this,idx2)));
    __ bind(done);
  
#line 18105 "ad_ppc.cpp"
  }
}

uint cmovL_bso_stackSlotLNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void cmovL_bso_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {

#line 3239 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    Label done;
    __ bso(opnd_array(1)->as_ConditionRegister(ra_,this,idx1)/* crx */, done);
    __ mffprd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src */);
    __ bind(done);
  
#line 18131 "ad_ppc.cpp"
  }
}

uint cmovL_bso_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
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
#line 10970 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 18202 "ad_ppc.cpp"
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
#line 11021 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 18268 "ad_ppc.cpp"
  }
}

void convD2LRaw_regDNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 11105 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fctidz(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 18284 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11153 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fcfid(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 18305 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11164 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ frsp(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 18326 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11196 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fcfids(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 18347 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11324 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fmr_if_needed(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
  
#line 18368 "ad_ppc.cpp"
  }
}

void cmpI_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 11338 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpw(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18385 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11348 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpwi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 18407 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11360 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ andi_(R0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 18430 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11370 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpd(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18452 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11380 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpdi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 18474 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11391 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpld(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18496 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11401 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpldi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 18518 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11412 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ and_(R0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18541 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11423 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ andi_(R0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 18564 "ad_ppc.cpp"
  }
}

uint testL_reg_immNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cmpL3_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 11438 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpd(CCR0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ set_cmp3(opnd_array(0)->as_Register(ra_,this)/* dst */);
  
#line 18587 "ad_ppc.cpp"
  }
}

uint cmpL3_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= VM_Version::has_brw() ? 16 : 20, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : VM_Version::has_brw() ? 16 : 20);
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
    C2_MacroAssembler _masm(&cbuf);

#line 11463 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    if (opnd_array(1)->ccode()== 0x1 /* less_equal */) {
      __ trap_range_check_le(opnd_array(2)->as_Register(ra_,this,idx2)/* src_length */, opnd_array(3)->constant());
    } else {
      // Both successors are uncommon traps, probability is 0.
      // Node got flipped during fixup flow.
      assert(opnd_array(1)->ccode()== 0x9, "must be greater");
      __ trap_range_check_g(opnd_array(2)->as_Register(ra_,this,idx2)/* src_length */, opnd_array(3)->constant());
    }
  
#line 18618 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11489 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    if (opnd_array(1)->ccode()== 0x0 /* greater_equal */) {
      __ trap_range_check_ge(opnd_array(2)->as_Register(ra_,this,idx2)/* src_index */, opnd_array(3)->as_Register(ra_,this,idx3)/* src_length */);
    } else {
      // Both successors are uncommon traps, probability is 0.
      // Node got flipped during fixup flow.
      assert(opnd_array(1)->ccode()== 0x8, "must be less");
      __ trap_range_check_l(opnd_array(2)->as_Register(ra_,this,idx2)/* src_index */, opnd_array(3)->as_Register(ra_,this,idx3)/* src_length */);
    }
  
#line 18649 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11515 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    if (opnd_array(1)->ccode()== 0x0 /* greater_equal */) {
      __ trap_range_check_ge(opnd_array(2)->as_Register(ra_,this,idx2)/* src_index */, opnd_array(3)->constant());
    } else {
      // Both successors are uncommon traps, probability is 0.
      // Node got flipped during fixup flow.
      assert(opnd_array(1)->ccode()== 0x8, "must be less");
      __ trap_range_check_l(opnd_array(2)->as_Register(ra_,this,idx2)/* src_index */, opnd_array(3)->constant());
    }
  
#line 18680 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11532 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmplw(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18702 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11542 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmplwi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 18724 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11563 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    if (opnd_array(1)->ccode()== 0xA) {
      __ trap_null_check(opnd_array(2)->as_Register(ra_,this,idx2)/* value */);
    } else {
      // Both successors are uncommon traps, probability is 0.
      // Node got flipped during fixup flow.
      assert(opnd_array(1)->ccode()== 0x2 , "must be equal(0xA) or notEqual(0x2)");
      __ trap_null_check(opnd_array(2)->as_Register(ra_,this,idx2)/* value */, Assembler::traptoGreaterThanUnsigned);
    }
  
#line 18755 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11583 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmplw(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18777 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11596 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmplwi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constant());
  
#line 18799 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11617 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    if (opnd_array(1)->ccode()== 0xA) {
      __ trap_null_check(opnd_array(2)->as_Register(ra_,this,idx2)/* value */);
    } else {
      // Both successors are uncommon traps, probability is 0.
      // Node got flipped during fixup flow.
      assert(opnd_array(1)->ccode()== 0x2 , "must be equal(0xA) or notEqual(0x2)");
      __ trap_null_check(opnd_array(2)->as_Register(ra_,this,idx2)/* value */, Assembler::traptoGreaterThanUnsigned);
    }
  
#line 18830 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11635 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpld(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 18852 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11645 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpldi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, (int)((short)(opnd_array(2)->constant()& 0xFFFF)));
  
#line 18874 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11661 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpdi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->constantL());
  
#line 18896 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11677 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fcmpu(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 18918 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 11693 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Label done;
    __ bns(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, done);        // not unordered -> keep crx
    __ li(R0, 0);
    __ cmpwi(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, R0, 1);     // unordered -> set crx to 'less'
    __ bind(done);
  
#line 18943 "ad_ppc.cpp"
  }
}

uint cmov_bns_lessNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
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
#line 11720 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 19013 "ad_ppc.cpp"
  }
}

void cmpF3_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 11773 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fcmpu(CCR0, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
    __ set_cmpu3(opnd_array(0)->as_Register(ra_,this)/* dst */, true); // C2 requires unordered to get treated like less
  
#line 19031 "ad_ppc.cpp"
  }
}

uint cmpF3_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= VM_Version::has_brw() ? 20 : 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : VM_Version::has_brw() ? 20 : 24);
}

void cmpDUnordered_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 11793 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fcmpu(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
  
#line 19053 "ad_ppc.cpp"
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
#line 11804 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 19123 "ad_ppc.cpp"
  }
}

void cmpD3_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 11857 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fcmpu(CCR0, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_FloatRegister(ra_,this,idx2)/* src2 */);
    __ set_cmpu3(opnd_array(0)->as_Register(ra_,this)/* dst */, true); // C2 requires unordered to get treated like less
  
#line 19141 "ad_ppc.cpp"
  }
}

uint cmpD3_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= VM_Version::has_brw() ? 20 : 24, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : VM_Version::has_brw() ? 20 : 24);
}

void cmprb_Digit_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  {
    C2_MacroAssembler _masm(&cbuf);

#line 11874 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // 0x30: 0, 0x39: 9
    __ li(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0x3930);
    // compare src1 with ranges 0x30 to 0x39
    __ cmprb(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, 0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ setb(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */);
  
#line 19168 "ad_ppc.cpp"
  }
}

uint cmprb_Digit_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void cmprb_LowerCase_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  {
    C2_MacroAssembler _masm(&cbuf);

#line 11904 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Label done;
    // 0x61: a, 0x7A: z
    __ li(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0x7A61);
    // compare src1 with ranges 0x61 to 0x7A
    __ cmprb(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, 0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ bgt(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, done);

    // 0xDF: sharp s, 0xFF: y with diaeresis, 0xF7 is not the lower case
    __ lis(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, (signed short)0xF6DF);
    __ ori(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0xFFF8);
    // compare src1 with ranges 0xDF to 0xF6 and 0xF8 to 0xFF
    __ cmprb(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, 1, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ bgt(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, done);

    // 0xAA: feminine ordinal indicator
    // 0xB5: micro sign
    // 0xBA: masculine ordinal indicator
    __ lis(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, (signed short)0xAAB5);
    __ ori(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0xBABA);
    __ insrdi(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 32, 0);
    // compare src1 with 0xAA, 0xB5, and 0xBA
    __ cmpeqb(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);

    __ bind(done);
    __ setb(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */);
  
#line 19215 "ad_ppc.cpp"
  }
}

uint cmprb_LowerCase_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 48, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 48);
}

void cmprb_UpperCase_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  {
    C2_MacroAssembler _masm(&cbuf);

#line 11949 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Label done;
    // 0x41: A, 0x5A: Z
    __ li(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0x5A41);
    // compare src1 with a range 0x41 to 0x5A
    __ cmprb(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, 0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ bgt(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, done);

    // 0xC0: a with grave, 0xDE: thorn, 0xD7 is not the upper case
    __ lis(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, (signed short)0xD6C0);
    __ ori(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0xDED8);
    // compare src1 with ranges 0xC0 to 0xD6 and 0xD8 to 0xDE
    __ cmprb(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, 1, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);

    __ bind(done);
    __ setb(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */);
  
#line 19252 "ad_ppc.cpp"
  }
}

uint cmprb_UpperCase_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 28, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 28);
}

void cmprb_Whitespace_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  {
    C2_MacroAssembler _masm(&cbuf);

#line 11980 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // 0x09 to 0x0D, 0x1C to 0x20
    __ li(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0x0D09);
    __ addis(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0x0201C);
    // compare src with ranges 0x09 to 0x0D and 0x1C to 0x20
    __ cmprb(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, 1, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ setb(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */);
  
#line 19280 "ad_ppc.cpp"
  }
}

uint cmprb_Whitespace_reg_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void cmprb_Whitespace_reg_reg_prefixedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  {
    C2_MacroAssembler _masm(&cbuf);

#line 12002 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // 0x09 to 0x0D, 0x1C to 0x20
    assert( ((intptr_t)(__ pc()) & 0x3c) != 0x3c, "Bad alignment for prefixed instruction at " INTPTR_FORMAT, (intptr_t)(__ pc()));
    __ pli(opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */, 0x201C0D09);
    // compare src with ranges 0x09 to 0x0D and 0x1C to 0x20
    __ cmprb(opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */, 1, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ setb(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(3)->as_ConditionRegister(ra_,this,idx3)/* crx */);
  
#line 19308 "ad_ppc.cpp"
  }
}

uint cmprb_Whitespace_reg_reg_prefixedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void branchNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    C2_MacroAssembler _masm(&cbuf);

#line 12025 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

     Label d;    // dummy
     __ bind(d);
     Label* p = opnd_array(1)->label();
     // `p' is `NULL' when this encoding class is used only to
     // determine the size of the encoded instruction.
     Label& l = (NULL == p)? d : *(p);
     __ b(l);
  
#line 19335 "ad_ppc.cpp"
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

#line 3248 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
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
  
#line 19380 "ad_ppc.cpp"
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

#line 3275 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // The scheduler doesn't know about branch shortening, so we set the opcode
    // to ppc64Opcode_bc in order to hide this detail from the scheduler.

    C2_MacroAssembler _masm(&cbuf);
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
  
#line 19428 "ad_ppc.cpp"
  }
}

uint branchConFarNode::size(PhaseRegAlloc *ra_) const {
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

#line 3248 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
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
  
#line 19473 "ad_ppc.cpp"
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

#line 3275 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // The scheduler doesn't know about branch shortening, so we set the opcode
    // to ppc64Opcode_bc in order to hide this detail from the scheduler.

    C2_MacroAssembler _masm(&cbuf);
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
  
#line 19521 "ad_ppc.cpp"
  }
}

uint branchLoopEndFarNode::size(PhaseRegAlloc *ra_) const {
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
    C2_MacroAssembler _masm(&cbuf);

#line 12123 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ check_klass_subtype_slow_path(opnd_array(1)->as_Register(ra_,this,idx1)/* subklass */, opnd_array(2)->as_Register(ra_,this,idx2)/* superklass */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp_arrayptr */,
                                     opnd_array(4)->as_Register(ra_,this,idx4)/* tmp_klass */, NULL, opnd_array(3)->as_Register(ra_,this,idx3)/* result */);
  
#line 19547 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12138 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ compiler_fast_lock_object(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */,
                                 opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */, /*tmp3*/ R0);
    // If locking was successful, crx should indicate 'EQ'.
    // The compiler generates a branch to the runtime call to
    // _complete_monitor_locking_Java for the case where crx is 'NE'.
  
#line 19570 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12155 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ compiler_fast_lock_object(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */,
                                 opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp3 */,
                                 _rtm_counters, _stack_rtm_counters,
                                 ((Method*)(ra_->C->method()->constant_encoding()))->method_data(),
                                 /*RTM*/ true, ra_->C->profile_rtm());
    // If locking was successful, crx should indicate 'EQ'.
    // The compiler generates a branch to the runtime call to
    // _complete_monitor_locking_Java for the case where crx is 'NE'.
  
#line 19597 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12174 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ compiler_fast_unlock_object(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */,
                                   opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp3 */,
                                   false);
    // If unlocking was successful, crx should indicate 'EQ'.
    // The compiler generates a branch to the runtime call to
    // _complete_monitor_unlocking_Java for the case where crx is 'NE'.
  
#line 19622 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12191 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ compiler_fast_unlock_object(opnd_array(0)->as_ConditionRegister(ra_,this)/* crx */, opnd_array(1)->as_Register(ra_,this,idx1)/* oop */, opnd_array(2)->as_Register(ra_,this,idx2)/* box */,
                                   opnd_array(3)->as_Register(ra_,this,idx3)/* tmp1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp2 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp3 */,
                                   /*RTM*/ true);
    // If unlocking was successful, crx should indicate 'EQ'.
    // The compiler generates a branch to the runtime call to
    // _complete_monitor_unlocking_Java for the case where crx is 'NE'.
  
#line 19647 "ad_ppc.cpp"
  }
}

void align_addrNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  {
    C2_MacroAssembler _masm(&cbuf);

#line 12208 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clrrdi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, log2i_exact(-(julong)opnd_array(2)->constantL()));
  
#line 19664 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12220 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ subf(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* start */, opnd_array(1)->as_Register(ra_,this,idx1)/* end */);
  
#line 19686 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12233 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clear_memory_constlen(opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(1)->constantL(), R0); // kills base, R0
  
#line 19708 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12246 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clear_memory_doubleword(opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */, R0, opnd_array(1)->constantL()); // kills base, R0
  
#line 19726 "ad_ppc.cpp"
  }
}

void inlineCallClearArrayNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  {
    C2_MacroAssembler _masm(&cbuf);

#line 12259 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ clear_memory_doubleword(opnd_array(2)->as_Register(ra_,this,idx2)/* base */, opnd_array(1)->as_Register(ra_,this,idx1)/* cnt */, R0); // kills cnt, base, R0
  
#line 19743 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12272 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::LL);
  
#line 19767 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12288 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::UU);
  
#line 19791 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12304 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ string_compare(opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */,
                      opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */, opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::LU);
  
#line 19815 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12320 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ string_compare(opnd_array(3)->as_Register(ra_,this,idx3)/* str2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */,
                      opnd_array(4)->as_Register(ra_,this,idx4)/* cnt2 */, opnd_array(2)->as_Register(ra_,this,idx2)/* cnt1 */,
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp */,
                      opnd_array(5)->as_Register(ra_,this,idx5)/* result */, StrIntrinsicNode::UL);
  
#line 19839 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12336 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ array_equals(false, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* str2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* cnt */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */,
                    opnd_array(4)->as_Register(ra_,this,idx4)/* result */, true /* byte */);
  
#line 19861 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12351 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ array_equals(false, opnd_array(1)->as_Register(ra_,this,idx1)/* str1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* str2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* cnt */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */,
                    opnd_array(4)->as_Register(ra_,this,idx4)/* result */, false /* byte */);
  
#line 19883 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12366 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ array_equals(true, opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* ary2 */,
                    opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* result */, true /* byte */);
  
#line 19905 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12381 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ array_equals(true, opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* ary2 */,
                    opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */,
                    opnd_array(3)->as_Register(ra_,this,idx3)/* result */, false /* byte */);
  
#line 19927 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12402 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 19963 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12435 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    immPOper *needleOper = (immPOper *)opnd_array(3);
    const TypeOopPtr *t = needleOper->type()->isa_oopptr();
    ciTypeArray* needle_values = t->const_oop()->as_type_array();  // Pointer to live char *
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           R0, chr,
                           opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, true /*is_byte*/);
  
#line 19992 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12461 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    immPOper *needleOper = (immPOper *)opnd_array(3);
    const TypeOopPtr *t = needleOper->type()->isa_oopptr();
    ciTypeArray* needle_values = t->const_oop()->as_type_array();  // Pointer to live char *
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           R0, chr,
                           opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, false /*is_byte*/);
  
#line 20021 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12488 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 20056 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12522 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();
    guarantee(needle_values, "sanity");
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           R0, chr,
                           opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */, true /*is_byte*/);
  
#line 20084 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12549 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();
    guarantee(needle_values, "sanity");
    jchar chr = (jchar)needle_values->element_value(0).as_byte();
    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           R0, chr,
                           opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */, false /*is_byte*/);
  
#line 20112 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12572 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           opnd_array(3)->as_Register(ra_,this,idx3)/* ch */, 0 /* this is not used if the character is already in a register */,
                           opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, false /*is_byte*/);
  
#line 20135 "ad_ppc.cpp"
  }
}

void indexOfChar_LNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 12591 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ string_indexof_char(opnd_array(0)->as_Register(ra_,this)/* result */,
                           opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                           opnd_array(3)->as_Register(ra_,this,idx3)/* ch */, 0 /* this is not used if the character is already in a register */,
                           opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, true /*is_byte*/);
  
#line 20158 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12615 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, needle_values, opnd_array(10)->as_Register(ra_,this,idx10)/* tmp5 */, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::UU);
  
#line 20189 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12642 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, needle_values, opnd_array(10)->as_Register(ra_,this,idx10)/* tmp5 */, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::LL);
  
#line 20220 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12669 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Node *ndl = in(operand_index(opnd_array(3)));  // The node that defines needle.
    ciTypeArray* needle_values = ndl->bottom_type()->is_aryptr()->const_oop()->as_type_array();

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, needle_values, opnd_array(10)->as_Register(ra_,this,idx10)/* tmp5 */, opnd_array(4)->constant(),
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::UL);
  
#line 20251 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12693 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, NULL, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,  // needlecnt not constant.
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::UU);
  
#line 20278 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12714 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, NULL, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,  // needlecnt not constant.
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::LL);
  
#line 20305 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12735 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ string_indexof(opnd_array(5)->as_Register(ra_,this,idx5)/* result */,
                      opnd_array(1)->as_Register(ra_,this,idx1)/* haystack */, opnd_array(2)->as_Register(ra_,this,idx2)/* haycnt */,
                      opnd_array(3)->as_Register(ra_,this,idx3)/* needle */, NULL, opnd_array(4)->as_Register(ra_,this,idx4)/* needlecnt */, 0,  // needlecnt not constant.
                      opnd_array(6)->as_Register(ra_,this,idx6)/* tmp1 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp2 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp3 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp4 */, StrIntrinsicNode::UL);
  
#line 20332 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12752 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 20365 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12774 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    Label Ldone;
    __ string_inflate_16(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */,
                         opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp3 */, opnd_array(7)->as_Register(ra_,this,idx7)/* tmp4 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp5 */);
    __ rldicl_(opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, 0, 64-3); // Remaining characters.
    __ beq(CCR0, Ldone);
    __ string_inflate(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */);
    __ bind(Ldone);
  
#line 20394 "ad_ppc.cpp"
  }
}

void count_positivesNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// len
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 12794 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ count_positives(opnd_array(1)->as_Register(ra_,this,idx1)/* ary1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* len */, opnd_array(3)->as_Register(ra_,this,idx3)/* result */,
                       opnd_array(4)->as_Register(ra_,this,idx4)/* tmp1 */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp2 */);
  
#line 20415 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12810 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ encode_iso_array(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                        opnd_array(7)->as_Register(ra_,this,idx7)/* tmp3 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp4 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp5 */, opnd_array(4)->as_Register(ra_,this,idx4)/* result */, false);
  
#line 20440 "ad_ppc.cpp"
  }
}

void encode_ascii_arrayNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
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
    C2_MacroAssembler _masm(&cbuf);

#line 12826 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ encode_iso_array(opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* len */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
                        opnd_array(7)->as_Register(ra_,this,idx7)/* tmp3 */, opnd_array(8)->as_Register(ra_,this,idx8)/* tmp4 */, opnd_array(9)->as_Register(ra_,this,idx9)/* tmp5 */, opnd_array(4)->as_Register(ra_,this,idx4)/* result */, true);
  
#line 20465 "ad_ppc.cpp"
  }
}

void minI_reg_reg_iselNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 12862 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpw(CCR0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ isel(opnd_array(0)->as_Register(ra_,this)/* dst */, CCR0, Assembler::less, /*invert*/false, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 20483 "ad_ppc.cpp"
  }
}

void maxI_reg_reg_iselNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 12895 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cmpw(CCR0, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
    __ isel(opnd_array(0)->as_Register(ra_,this)/* dst */, CCR0, Assembler::greater, /*invert*/false, opnd_array(1)->as_Register(ra_,this,idx1)/* src1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* src2 */);
  
#line 20501 "ad_ppc.cpp"
  }
}

void popCountINode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 12912 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ popcntw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20517 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12926 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ popcntd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20538 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12939 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cntlzw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20559 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12952 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cntlzd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20580 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 12965 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cntlzd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20601 "ad_ppc.cpp"
  }
}

uint countLeadingZerosPNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void countTrailingZerosI_cnttzwNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 12997 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cnttzw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20622 "ad_ppc.cpp"
  }
}

uint countTrailingZerosI_cnttzwNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void countTrailingZerosL_cnttzdNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13028 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cnttzd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20643 "ad_ppc.cpp"
  }
}

uint countTrailingZerosL_cnttzdNode::size(PhaseRegAlloc *ra_) const {
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
    C2_MacroAssembler _masm(&cbuf);

#line 13041 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ insrwi(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */, opnd_array(3)->constant(), opnd_array(2)->constant());
  
#line 20666 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13054 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ insrwi(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(4)->constant(), opnd_array(3)->constant());
  
#line 20690 "ad_ppc.cpp"
  }
}

uint insrwiNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void bytes_reverse_int_vecNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmpV
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13096 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mtvsrwz(opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* tmpV */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    __ xxbrw(opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* tmpV */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* tmpV */);
    __ mfvsrwz(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* tmpV */);
  
#line 20714 "ad_ppc.cpp"
  }
}

uint bytes_reverse_int_vecNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void bytes_reverse_intNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13112 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ brw(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20735 "ad_ppc.cpp"
  }
}

uint bytes_reverse_intNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void bytes_reverse_long_vecNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmpV
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13168 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mtvsrd(opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* tmpV */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    __ xxbrd(opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* tmpV */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* tmpV */);
    __ mfvsrd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* tmpV */);
  
#line 20759 "ad_ppc.cpp"
  }
}

uint bytes_reverse_long_vecNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void bytes_reverse_longNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13184 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ brd(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20780 "ad_ppc.cpp"
  }
}

uint bytes_reverse_longNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void bytes_reverse_ushortNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13212 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ brh(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 20801 "ad_ppc.cpp"
  }
}

uint bytes_reverse_ushortNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void bytes_reverse_shortNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13243 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ brh(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
    __ extsh(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */);
  
#line 20823 "ad_ppc.cpp"
  }
}

uint bytes_reverse_shortNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void loadI_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13257 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ lwbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 20844 "ad_ppc.cpp"
  }
}

uint loadI_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadI_reversed_acquireNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13268 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ lwbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 20867 "ad_ppc.cpp"
  }
}

uint loadI_reversed_acquireNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadL_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13283 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ ldbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 20888 "ad_ppc.cpp"
  }
}

uint loadL_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadL_reversed_acquireNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13295 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ ldbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 20911 "ad_ppc.cpp"
  }
}

uint loadL_reversed_acquireNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadUS_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13310 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ lhbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 20932 "ad_ppc.cpp"
  }
}

uint loadUS_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void loadUS_reversed_acquireNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13321 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ lhbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 20955 "ad_ppc.cpp"
  }
}

uint loadUS_reversed_acquireNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 12, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 12);
}

void loadS_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13336 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ lhbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
    __ extsh(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */);
  
#line 20977 "ad_ppc.cpp"
  }
}

uint loadS_reversedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void loadS_reversed_acquireNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13348 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ lhbrx(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
    __ twi_0(opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ extsh(opnd_array(0)->as_Register(ra_,this)/* dst */, opnd_array(0)->as_Register(ra_,this)/* dst */);
    __ isync();
  
#line 21001 "ad_ppc.cpp"
  }
}

uint loadS_reversed_acquireNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 16, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 16);
}

void storeI_reversedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13363 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ stwbrx(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 21023 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13376 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ stdbrx(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 21045 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13388 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sthbrx(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 21067 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13400 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ sthbrx(opnd_array(2)->as_Register(ra_,this,idx2)/* src */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */);
  
#line 21089 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13411 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mtvsrwz(opnd_array(0)->as_VectorSRegister(ra_,this)/* temp1 */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 21110 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13422 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxspltw(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */, opnd_array(2)->constant());
  
#line 21132 "ad_ppc.cpp"
  }
}

uint xxspltwNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void xscvdpspn_regFNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13433 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xscvdpspn(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */->to_vsr());
  
#line 21153 "ad_ppc.cpp"
  }
}

uint xscvdpspn_regFNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl32Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13448 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ insrdi(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 32, 0);
  
#line 21174 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13461 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ insrdi(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 48, 0);
  
#line 21195 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13474 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ insrdi(opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* dst */, 56, 0);
  
#line 21216 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13496 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 21237 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13507 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 21258 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13535 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21279 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13547 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxleqv(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21300 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13568 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 21321 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13579 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 21342 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13607 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21363 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13619 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxleqv(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21384 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13640 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 21405 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13651 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, (int)((short)(opnd_array(1)->constant()& 0xFFFF)));
  
#line 21426 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13679 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21447 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13691 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxleqv(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 21468 "ad_ppc.cpp"
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
#line 3309 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 21511 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 13728 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(opnd_array(0)->as_Register(ra_,this)/* dst */, 0x0);
  
#line 21530 "ad_ppc.cpp"
  }
}

void vadd16B_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13744 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vaddubm(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21547 "ad_ppc.cpp"
  }
}

uint vadd16B_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vadd8S_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13755 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vadduhm(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21569 "ad_ppc.cpp"
  }
}

uint vadd8S_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vadd4I_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13766 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vadduwm(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21591 "ad_ppc.cpp"
  }
}

uint vadd4I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vadd4F_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13777 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vaddfp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21613 "ad_ppc.cpp"
  }
}

uint vadd4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vadd2L_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13788 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vaddudm(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21635 "ad_ppc.cpp"
  }
}

uint vadd2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vadd2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13799 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvadddp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */);
  
#line 21657 "ad_ppc.cpp"
  }
}

uint vadd2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vsub16B_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13812 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vsububm(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21679 "ad_ppc.cpp"
  }
}

uint vsub16B_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vsub8S_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13823 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vsubuhm(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21701 "ad_ppc.cpp"
  }
}

uint vsub8S_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vsub4I_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13834 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vsubuwm(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21723 "ad_ppc.cpp"
  }
}

uint vsub4I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vsub4F_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13845 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vsubfp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21745 "ad_ppc.cpp"
  }
}

uint vsub4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vsub2L_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13856 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vsubudm(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21767 "ad_ppc.cpp"
  }
}

uint vsub2L_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vsub2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13867 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvsubdp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */);
  
#line 21789 "ad_ppc.cpp"
  }
}

uint vsub2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vmul8S_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13882 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vspltish(opnd_array(3)->as_VectorSRegister(ra_,this,idx3)/* tmp */->to_vr(), 0);
    __ vmladduhm(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr(), opnd_array(3)->as_VectorSRegister(ra_,this,idx3)/* tmp */->to_vr());
  
#line 21813 "ad_ppc.cpp"
  }
}

uint vmul8S_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 8, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 8);
}

void vmul4I_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13894 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ vmuluwm(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */->to_vr(), opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */->to_vr());
  
#line 21835 "ad_ppc.cpp"
  }
}

uint vmul4I_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vmul4F_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13905 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvmulsp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */);
  
#line 21857 "ad_ppc.cpp"
  }
}

uint vmul4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vmul2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13916 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvmuldp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */);
  
#line 21879 "ad_ppc.cpp"
  }
}

uint vmul2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vdiv4F_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13929 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvdivsp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */);
  
#line 21901 "ad_ppc.cpp"
  }
}

uint vdiv4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vdiv2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13940 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvdivdp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */);
  
#line 21923 "ad_ppc.cpp"
  }
}

uint vdiv2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vabs4F_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13953 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvabssp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */);
  
#line 21944 "ad_ppc.cpp"
  }
}

uint vabs4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vabs2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13964 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvabsdp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */);
  
#line 21965 "ad_ppc.cpp"
  }
}

uint vabs2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void roundD_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rmode
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13975 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    switch (opnd_array(2)->constant()) {
      case RoundDoubleModeNode::rmode_rint:
        __ xvrdpic(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */->to_vsr(), opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */->to_vsr());
        break;
      case RoundDoubleModeNode::rmode_floor:
        __ frim(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
        break;
      case RoundDoubleModeNode::rmode_ceil:
        __ frip(opnd_array(0)->as_FloatRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */);
        break;
      default:
        ShouldNotReachHere();
    }
  
#line 21999 "ad_ppc.cpp"
  }
}

uint roundD_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vround2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rmode
  {
    C2_MacroAssembler _masm(&cbuf);

#line 13999 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    switch (opnd_array(2)->constant()) {
      case RoundDoubleModeNode::rmode_rint:
        __ xvrdpic(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */);
        break;
      case RoundDoubleModeNode::rmode_floor:
        __ xvrdpim(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */);
        break;
      case RoundDoubleModeNode::rmode_ceil:
        __ xvrdpip(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */);
        break;
      default:
        ShouldNotReachHere();
    }
  
#line 22033 "ad_ppc.cpp"
  }
}

uint vround2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vneg4F_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14024 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvnegsp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */);
  
#line 22054 "ad_ppc.cpp"
  }
}

uint vneg4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vneg2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14035 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvnegdp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */);
  
#line 22075 "ad_ppc.cpp"
  }
}

uint vneg2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vsqrt4F_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14048 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvsqrtsp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */);
  
#line 22096 "ad_ppc.cpp"
  }
}

uint vsqrt4F_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vsqrt2D_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14059 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvsqrtdp(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */);
  
#line 22117 "ad_ppc.cpp"
  }
}

uint vsqrt2D_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vpopcnt_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14071 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    BasicType bt = Matcher::vector_element_basic_type(this);
    switch (bt) {
      case T_BYTE:
        __ vpopcntb(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */->to_vr());
        break;
      case T_SHORT:
        __ vpopcnth(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */->to_vr());
        break;
      case T_INT:
        __ vpopcntw(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */->to_vr());
        break;
      case T_LONG:
        __ vpopcntd(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */->to_vr(), opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */->to_vr());
        break;
      default:
        ShouldNotReachHere();
    }
  
#line 22154 "ad_ppc.cpp"
  }
}

uint vpopcnt_regNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vfma4FNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14102 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvmaddasp(opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_VectorSRegister(ra_,this,idx3)/* src2 */);
  
#line 22177 "ad_ppc.cpp"
  }
}

uint vfma4FNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vfma4F_neg1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14117 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvnmsubasp(opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_VectorSRegister(ra_,this,idx3)/* src2 */);
  
#line 22200 "ad_ppc.cpp"
  }
}

uint vfma4F_neg1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vfma4F_neg1_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14117 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvnmsubasp(opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_VectorSRegister(ra_,this,idx3)/* src2 */);
  
#line 22223 "ad_ppc.cpp"
  }
}

uint vfma4F_neg1_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vfma4F_neg2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14131 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvmsubasp(opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_VectorSRegister(ra_,this,idx3)/* src2 */);
  
#line 22246 "ad_ppc.cpp"
  }
}

uint vfma4F_neg2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vfma2DNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14145 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvmaddadp(opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_VectorSRegister(ra_,this,idx3)/* src2 */);
  
#line 22269 "ad_ppc.cpp"
  }
}

uint vfma2DNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vfma2D_neg1Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14160 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvnmsubadp(opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_VectorSRegister(ra_,this,idx3)/* src2 */);
  
#line 22292 "ad_ppc.cpp"
  }
}

uint vfma2D_neg1Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vfma2D_neg1_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14160 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvnmsubadp(opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_VectorSRegister(ra_,this,idx3)/* src2 */);
  
#line 22315 "ad_ppc.cpp"
  }
}

uint vfma2D_neg1_0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void vfma2D_neg2Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14174 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xvmsubadp(opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* dst */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src1 */, opnd_array(3)->as_VectorSRegister(ra_,this,idx3)/* src2 */);
  
#line 22338 "ad_ppc.cpp"
  }
}

uint vfma2D_neg2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void overflowAddL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14190 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(R0, 0);
    __ mtxer(R0); // clear XER.SO
    __ addo_(R0, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 22362 "ad_ppc.cpp"
  }
}

void overflowSubL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14202 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(R0, 0);
    __ mtxer(R0); // clear XER.SO
    __ subfo_(R0, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */);
  
#line 22381 "ad_ppc.cpp"
  }
}

void overflowNegL_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14214 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(R0, 0);
    __ mtxer(R0); // clear XER.SO
    __ nego_(R0, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 22400 "ad_ppc.cpp"
  }
}

void overflowMulL_reg_regNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14226 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ li(R0, 0);
    __ mtxer(R0); // clear XER.SO
    __ mulldo_(R0, opnd_array(1)->as_Register(ra_,this,idx1)/* op1 */, opnd_array(2)->as_Register(ra_,this,idx2)/* op2 */);
  
#line 22419 "ad_ppc.cpp"
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
#line 3327 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
  
#line 22464 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14261 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 22483 "ad_ppc.cpp"
  }
}

void repl2D_reg_ExNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14273 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxpermdi(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */->to_vsr(), opnd_array(1)->as_FloatRegister(ra_,this,idx1)/* src */->to_vsr(), 0);
  
#line 22499 "ad_ppc.cpp"
  }
}

uint repl2D_reg_ExNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void repl2D_immD0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14285 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 22520 "ad_ppc.cpp"
  }
}

uint repl2D_immD0Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void mtvsrdNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14297 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mtvsrd(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 22541 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14308 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxpermdi(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src */, opnd_array(2)->constant());
  
#line 22563 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14319 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxpermdi(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(1)->as_VectorSRegister(ra_,this,idx1)/* src1 */, opnd_array(2)->as_VectorSRegister(ra_,this,idx2)/* src2 */, opnd_array(3)->constant());
  
#line 22586 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14342 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxlxor(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 22607 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14354 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ xxleqv(opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */, opnd_array(0)->as_VectorSRegister(ra_,this)/* dst */);
  
#line 22628 "ad_ppc.cpp"
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

#line 3350 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // Fake operand dst needed for PPC scheduler.
    assert((0x0) == 0x0, "dst must be 0x0");

    C2_MacroAssembler _masm(&cbuf);
    // Mark the code position where the load from the safepoint
    // polling page was emitted as relocInfo::poll_type.
    __ relocate(relocInfo::poll_type);
    __ load_from_polling_page(opnd_array(1)->as_Register(ra_,this,idx1)/* poll */);
  
#line 22655 "ad_ppc.cpp"
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

#line 3407 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
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
    __ post_call_nop();
  
#line 22720 "ad_ppc.cpp"
  }
}

uint CallStaticJavaDirectNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= (Continuations::enabled() ? 8 : 4), "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : (Continuations::enabled() ? 8 : 4));
}

void CallDynamicJavaDirectSchedNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 3457 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);

    if (!ra_->C->output()->in_scratch_emit_size()) {
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
    __ post_call_nop();
  
#line 22776 "ad_ppc.cpp"
  }
}

uint CallDynamicJavaDirectSchedNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= (Continuations::enabled() ? 8 : 4), "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : (Continuations::enabled() ? 8 : 4));
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
#line 3498 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    // Create the nodes for loading the IC from the TOC.
    loadConLNodesTuple loadConLNodes_IC =
      loadConLNodesTuple_create(ra_, n_toc, new immLOper((jlong)Universe::non_oop_word()),
                                OptoReg::Name(R19_H_num), OptoReg::Name(R19_num));

    // Create the call node.
    CallDynamicJavaDirectSchedNode *call = new CallDynamicJavaDirectSchedNode();
    call->_method_handle_invoke = _method_handle_invoke;
    call->_vtable_index      = _vtable_index;
    call->_method            = _method;
    call->_optimized_virtual = _optimized_virtual;
    call->_tf                = _tf;
    call->_entry_point       = _entry_point;
    call->_cnt               = _cnt;
    call->_guaranteed_safepoint = true;
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
  
#line 22857 "ad_ppc.cpp"
  }
}

void CallDynamicJavaDirectNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 3560 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    int start_offset = __ offset();

    Register Rtoc = (ra_) ? as_Register(ra_->get_encode(in(mach_constant_base_node_input()))) : R2_TOC;

    int vtable_index = this->_vtable_index;
    if (vtable_index < 0) {
      // Must be invalid_vtable_index, not nonvirtual_vtable_index.
      assert(vtable_index == Method::invalid_vtable_index, "correct sentinel value");
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
             "Fix constant in ret_addr_offset(), expected %d", __ offset() - start_offset);
    } else {
      assert(!UseInlineCaches, "expect vtable calls only if not using ICs");
      // Go thru the vtable. Get receiver klass. Receiver already
      // checked for non-null. If we'll go thru a C2I adapter, the
      // interpreter expects method in R19_method.

      __ load_klass(R11_scratch1, R3);

      int entry_offset = in_bytes(Klass::vtable_start_offset()) + vtable_index * vtableEntry::size_in_bytes();
      int v_off = entry_offset + vtableEntry::method_offset_in_bytes();
      __ li(R19_method, v_off);
      __ ldx(R19_method/*method*/, R19_method/*method offset*/, R11_scratch1/*class*/);
      // NOTE: for vtable dispatches, the vtable entry will never be
      // null. However it may very well end up in handle_wrong_method
      // if the method is abstract for the particular class.
      __ ld(R11_scratch1, in_bytes(Method::from_compiled_offset()), R19_method);
      // Call target. Either compiled code or C2I adapter.
      __ mtctr(R11_scratch1);
      __ bctrl();
      assert(((MachCallDynamicJavaNode*)this)->ret_addr_offset() == __ offset() - start_offset,
             "Fix constant in ret_addr_offset(), expected %d", __ offset() - start_offset);
    }
    __ post_call_nop();
  
#line 22920 "ad_ppc.cpp"
  }
}

void CallRuntimeDirectNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {

#line 3613 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"


    C2_MacroAssembler _masm(&cbuf);
    const address start_pc = __ pc();

#if defined(ABI_ELFv2)
    address entry= !(opnd_array(1)->method()) ? NULL : (address)opnd_array(1)->method();
    __ call_c(entry, relocInfo::runtime_call_type);
    __ post_call_nop();
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
    __ post_call_nop();
#endif

    // Check the ret_addr_offset.
    assert(((MachCallRuntimeNode*)this)->ret_addr_offset() ==  __ last_calls_return_pc() - start_pc,
           "Fix constant in ret_addr_offset()");
  
#line 22963 "ad_ppc.cpp"
  }
}

void CallLeafDirect_mtctrNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  {

#line 3648 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    C2_MacroAssembler _masm(&cbuf);
    __ mtctr(opnd_array(1)->as_Register(ra_,this,idx1)/* src */);
  
#line 22979 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14496 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ bctrl();
    __ post_call_nop();
  
#line 23001 "ad_ppc.cpp"
  }
}

uint CallLeafDirectNode::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= (Continuations::enabled() ? 8 : 4), "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : (Continuations::enabled() ? 8 : 4));
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
#line 3654 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
    call->_guaranteed_safepoint = false;
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
  
#line 23127 "ad_ppc.cpp"
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
#line 3654 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

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
    call->_guaranteed_safepoint = false;
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
  
#line 23248 "ad_ppc.cpp"
  }
}

void TailCalljmpIndNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// method_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14545 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ mtctr(opnd_array(1)->as_Register(ra_,this,idx1)/* jump_target */);
    __ bctr();
  
#line 23266 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14557 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    // LR is restored in MachEpilogNode. Just do the RET here.
    __ blr();
  
#line 23288 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14578 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ ld(R4_ARG2/* issuing pc */, _abi0(lr), R1_SP);
    __ mtctr(opnd_array(1)->as_Register(ra_,this,idx1)/* jump_target */);
    __ bctr();
  
#line 23312 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14606 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    cbuf.set_insts_mark();
    __ b64_patchable((address)OptoRuntime::rethrow_stub(), relocInfo::runtime_call_type);
  
#line 23347 "ad_ppc.cpp"
  }
}

void ShouldNotReachHereNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14619 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    if (is_reachable()) {
      __ stop(_halt_reason);
    }
  
#line 23365 "ad_ppc.cpp"
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

void endGroupNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14653 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ endgroup();
  
#line 23394 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14668 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ nop();
  
#line 23415 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14681 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fpnop0();
  
#line 23436 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14694 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ fpnop1();
  
#line 23457 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14704 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ brnop0();
  
#line 23478 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14718 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ brnop1();
  
#line 23499 "ad_ppc.cpp"
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
    C2_MacroAssembler _masm(&cbuf);

#line 14731 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ brnop2();
  
#line 23520 "ad_ppc.cpp"
  }
}

uint brNop2Node::size(PhaseRegAlloc *ra_) const {
  assert(VerifyOops || MachNode::size(ra_) <= 4, "bad fixed size");
  return (VerifyOops ? MachNode::size(ra_) : 4);
}

void cacheWBNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14743 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    assert(opnd_array(1)->index_position() < 0, "should be");
    assert(opnd_array(1)->disp(ra_,this,idx1)== 0, "should be");
    __ cache_wb(Address(as_Register(opnd_array(1)->base(ra_,this,idx1))));
  
#line 23543 "ad_ppc.cpp"
  }
}

void cacheWBPreSyncNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14757 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cache_wbsync(true);
  
#line 23559 "ad_ppc.cpp"
  }
}

void cacheWBPostSyncNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  {
    C2_MacroAssembler _masm(&cbuf);

#line 14769 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    __ cache_wbsync(false);
  
#line 23575 "ad_ppc.cpp"
  }
}

void compareAndSwapP_shenandoahNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 45 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        false, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
  
#line 23600 "ad_ppc.cpp"
  }
}

void compareAndSwapP_shenandoah_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 45 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        false, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
  
#line 23625 "ad_ppc.cpp"
  }
}

void compareAndSwapN_shenandoahNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 66 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        false, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
  
#line 23650 "ad_ppc.cpp"
  }
}

void compareAndSwapN_shenandoah_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 66 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        false, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
  
#line 23675 "ad_ppc.cpp"
  }
}

void compareAndSwapP_acq_shenandoahNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 87 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        false, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 23705 "ad_ppc.cpp"
  }
}

void compareAndSwapP_acq_shenandoah_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 87 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        false, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 23735 "ad_ppc.cpp"
  }
}

void compareAndSwapN_acq_shenandoahNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 113 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        false, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 23765 "ad_ppc.cpp"
  }
}

void compareAndSwapN_acq_shenandoah_0Node::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 113 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        false, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 23795 "ad_ppc.cpp"
  }
}

void compareAndExchangeP_shenandoahNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 138 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        true, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
  
#line 23820 "ad_ppc.cpp"
  }
}

void compareAndExchangeN_shenandoahNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 158 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        true, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
  
#line 23845 "ad_ppc.cpp"
  }
}

void compareAndExchangePAcq_shenandoahNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 178 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        true, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 23875 "ad_ppc.cpp"
  }
}

void compareAndExchangeNAcq_shenandoahNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  {
    C2_MacroAssembler _masm(&cbuf);

#line 203 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/shenandoah/shenandoah_ppc.ad"

    ShenandoahBarrierSet::assembler()->cmpxchg_oop(
        &_masm,
        opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
        opnd_array(5)->as_Register(ra_,this,idx5)/* tmp1 */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp2 */,
        true, opnd_array(4)->as_Register(ra_,this,idx4)/* res */);
    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 23905 "ad_ppc.cpp"
  }
}

void zLoadPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {
    C2_MacroAssembler _masm(&cbuf);

#line 138 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/z/z_ppc.ad"

    assert(opnd_array(1)->index(ra_,this,idx1)== 0, "sanity");
    __ ld(opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(1)->disp(ra_,this,idx1), as_Register(opnd_array(1)->base(ra_,this,idx1)));
    z_load_barrier(_masm, this, Address(as_Register(opnd_array(1)->base(ra_,this,idx1)), opnd_array(1)->disp(ra_,this,idx1)), opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */, barrier_data());
  
#line 23925 "ad_ppc.cpp"
  }
}

void zLoadP_acqNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  {
    C2_MacroAssembler _masm(&cbuf);

#line 157 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/z/z_ppc.ad"

    __ ld(opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(1)->disp(ra_,this,idx1), as_Register(opnd_array(1)->base(ra_,this,idx1)));
    z_load_barrier(_masm, this, Address(as_Register(opnd_array(1)->base(ra_,this,idx1)), opnd_array(1)->disp(ra_,this,idx1)), opnd_array(2)->as_Register(ra_,this,idx2)/* dst */, opnd_array(3)->as_Register(ra_,this,idx3)/* tmp */, barrier_data());

    // Uses the isync instruction as an acquire barrier.
    // This exploits the compare and the branch in the z load barrier (load, compare and branch, isync).
    __ isync();
  
#line 23948 "ad_ppc.cpp"
  }
}

void zCompareAndSwapPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp_xchg
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp_mask
  {
    C2_MacroAssembler _masm(&cbuf);

#line 177 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/z/z_ppc.ad"

    z_compare_and_swap(_masm, this,
                       opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp_xchg */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp_mask */,
                       false /* weak */, false /* acquire */);
  
#line 23972 "ad_ppc.cpp"
  }
}

void zCompareAndSwapP_acqNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp_xchg
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp_mask
  {
    C2_MacroAssembler _masm(&cbuf);

#line 195 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/z/z_ppc.ad"

    z_compare_and_swap(_masm, this,
                       opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp_xchg */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp_mask */,
                       false /* weak */, true /* acquire */);
  
#line 23996 "ad_ppc.cpp"
  }
}

void zCompareAndSwapPWeakNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp_xchg
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp_mask
  {
    C2_MacroAssembler _masm(&cbuf);

#line 213 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/z/z_ppc.ad"

    z_compare_and_swap(_masm, this,
                       opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp_xchg */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp_mask */,
                       true /* weak */, false /* acquire */);
  
#line 24020 "ad_ppc.cpp"
  }
}

void zCompareAndSwapPWeak_acqNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp_xchg
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp_mask
  {
    C2_MacroAssembler _masm(&cbuf);

#line 231 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/z/z_ppc.ad"

    z_compare_and_swap(_masm, this,
                       opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */,
                       opnd_array(5)->as_Register(ra_,this,idx5)/* tmp_xchg */, opnd_array(6)->as_Register(ra_,this,idx6)/* tmp_mask */,
                       true /* weak */, true /* acquire */);
  
#line 24044 "ad_ppc.cpp"
  }
}

void zCompareAndExchangePNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  {
    C2_MacroAssembler _masm(&cbuf);

#line 252 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/z/z_ppc.ad"

    z_compare_and_exchange(_masm, this,
                           opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */,
                           false /* weak */, false /* acquire */);
  
#line 24066 "ad_ppc.cpp"
  }
}

void zCompareAndExchangeP_acqNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  {
    C2_MacroAssembler _masm(&cbuf);

#line 272 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/z/z_ppc.ad"

    z_compare_and_exchange(_masm, this,
                           opnd_array(4)->as_Register(ra_,this,idx4)/* res */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, opnd_array(2)->as_Register(ra_,this,idx2)/* oldval */, opnd_array(3)->as_Register(ra_,this,idx3)/* newval */, opnd_array(5)->as_Register(ra_,this,idx5)/* tmp */,
                           false /* weak */, true /* acquire */);
  
#line 24088 "ad_ppc.cpp"
  }
}

void zGetAndSetPNode::emit(CodeBuffer& cbuf, PhaseRegAlloc* ra_) const {
  cbuf.set_insts_mark();
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  {
    C2_MacroAssembler _masm(&cbuf);

#line 287 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/gc/z/z_ppc.ad"

    __ getandsetd(opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(2)->as_Register(ra_,this,idx2)/* newval */, opnd_array(1)->as_Register(ra_,this,idx1)/* mem */, MacroAssembler::cmpxchgx_hint_atomic_update());
    z_load_barrier(_masm, this, Address(noreg, (intptr_t) 0), opnd_array(3)->as_Register(ra_,this,idx3)/* res */, opnd_array(4)->as_Register(ra_,this,idx4)/* tmp */, barrier_data());

    if (support_IRIW_for_not_multiple_copy_atomic_cpu) {
      __ isync();
    } else {
      __ sync();
    }
  
#line 24114 "ad_ppc.cpp"
  }
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
const MachOper* storeCMNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadI_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadI_reversed_acquireNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadL_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadL_reversed_acquireNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUS_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadUS_reversed_acquireNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadS_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* loadS_reversed_acquireNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeI_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeL_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeUS_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* storeS_reversedNode::memory_operand() const { return _opnds[1]; }
const MachOper* cacheWBNode::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndSwapP_shenandoahNode::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndSwapP_shenandoah_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndSwapN_shenandoahNode::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndSwapN_shenandoah_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndSwapP_acq_shenandoahNode::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndSwapP_acq_shenandoah_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndSwapN_acq_shenandoahNode::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndSwapN_acq_shenandoah_0Node::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndExchangeP_shenandoahNode::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndExchangeN_shenandoahNode::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndExchangePAcq_shenandoahNode::memory_operand() const { return _opnds[1]; }
const MachOper* compareAndExchangeNAcq_shenandoahNode::memory_operand() const { return _opnds[1]; }
const MachOper* zLoadPNode::memory_operand() const { return _opnds[1]; }
const MachOper* zLoadP_acqNode::memory_operand() const { return _opnds[1]; }


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
    true ,  // CacheWB
    true ,  // CacheWBPreSync
    true ,  // CacheWBPostSync
    true ,  // CallDynamicJava
    false,  // CallJava
    true ,  // CallLeaf
    true ,  // CallLeafNoFP
    false,  // CallLeafVector
    true ,  // CallRuntime
    true ,  // CallStaticJava
    true ,  // CastDD
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
    false,  // CmpU3
    true ,  // CmpUL
    false,  // CmpUL3
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
    true ,  // DivD
    true ,  // DivF
    true ,  // DivI
    true ,  // DivL
    true ,  // UDivI
    true ,  // UDivL
    false,  // DivMod
    false,  // DivModI
    false,  // DivModL
    false,  // UDivModI
    false,  // UDivModL
    true ,  // EncodeISOArray
    true ,  // EncodeP
    true ,  // EncodePKlass
    true ,  // FastLock
    true ,  // FastUnlock
    true ,  // FmaD
    true ,  // FmaF
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
    true ,  // MemBarVolatile
    true ,  // MemBarStoreStore
    false,  // MergeMem
    true ,  // MinI
    false,  // MinL
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
    false,  // OnSpinWait
    false,  // Opaque1
    false,  // OpaqueLoopInit
    false,  // OpaqueLoopStride
    false,  // OpaqueZeroTripGuard
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
    true ,  // RoundDouble
    true ,  // RoundDoubleMode
    true ,  // RoundDoubleModeV
    true ,  // RoundFloat
    false,  // RotateLeft
    false,  // RotateLeftV
    false,  // RotateRight
    false,  // RotateRightV
    true ,  // SafePoint
    false,  // SafePointScalarObject
    true ,  // ShenandoahCompareAndExchangeP
    true ,  // ShenandoahCompareAndExchangeN
    true ,  // ShenandoahCompareAndSwapN
    true ,  // ShenandoahCompareAndSwapP
    true ,  // ShenandoahWeakCompareAndSwapN
    true ,  // ShenandoahWeakCompareAndSwapP
    false,  // ShenandoahIUBarrier
    false,  // ShenandoahLoadReferenceBarrier
    false,  // SCMemProj
    false,  // CopySignD
    false,  // CopySignF
    false,  // SignumD
    false,  // SignumF
    false,  // SignumVF
    false,  // SignumVD
    true ,  // SqrtD
    true ,  // SqrtF
    false,  // RoundF
    false,  // RoundD
    false,  // Start
    false,  // StartOSR
    true ,  // StoreB
    true ,  // StoreC
    true ,  // StoreCM
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
    false,  // AddReductionVF
    true ,  // AddVD
    false,  // AddReductionVD
    true ,  // SubVB
    true ,  // SubVS
    true ,  // SubVI
    true ,  // SubVL
    true ,  // SubVF
    true ,  // SubVD
    false,  // MulVB
    true ,  // MulVS
    true ,  // MulVI
    false,  // MulReductionVI
    false,  // MulVL
    false,  // MulReductionVL
    true ,  // MulVF
    false,  // MulReductionVF
    true ,  // MulVD
    false,  // MulReductionVD
    false,  // MulAddVS2VI
    true ,  // FmaVD
    true ,  // FmaVF
    true ,  // DivVF
    true ,  // DivVD
    false,  // AbsVB
    false,  // AbsVS
    false,  // AbsVI
    false,  // AbsVL
    true ,  // AbsVF
    true ,  // AbsVD
    false,  // NegVI
    false,  // NegVL
    true ,  // NegVF
    true ,  // NegVD
    true ,  // SqrtVD
    true ,  // SqrtVF
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
    false,  // MinReductionV
    false,  // MaxReductionV
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
    true ,  // ReplicateB
    true ,  // ReplicateS
    true ,  // ReplicateI
    true ,  // ReplicateL
    true ,  // ReplicateF
    true ,  // ReplicateD
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
    true ,  // Digit
    true ,  // LowerCase
    true ,  // UpperCase
    true ,  // Whitespace
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


int Compile::sync_stack_slots() const { return (frame::jit_monitor_size / VMRegImpl::stack_slot_size); }

uint Matcher::stack_alignment_in_bytes() { return frame::alignment_in_bytes; }

OptoReg::Name Matcher::return_addr() const { return OptoReg::stack2reg(4); }

uint Compile::varargs_C_out_slots_killed() const { return ((frame::abi_reg_args_size - frame::jit_out_preserve_size) / VMRegImpl::stack_slot_size); }

OptoRegPair Matcher::return_value(uint ideal_reg) {

#line 3829 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    assert((ideal_reg >= Op_RegI && ideal_reg <= Op_RegL) ||
            (ideal_reg == Op_RegN && CompressedOops::base() == NULL && CompressedOops::shift() == 0),
            "only return normal values");
    // enum names from opcodes.hpp:    Op_Node Op_Set Op_RegN       Op_RegI       Op_RegP       Op_RegF       Op_RegD       Op_RegL
    static int typeToRegLo[Op_RegL+1] = { 0,   0,     R3_num,   R3_num,   R3_num,   F1_num,   F1_num,   R3_num };
    static int typeToRegHi[Op_RegL+1] = { 0,   0,     OptoReg::Bad, R3_H_num, R3_H_num, OptoReg::Bad, F1_H_num, R3_H_num };
    return OptoRegPair(typeToRegHi[ideal_reg], typeToRegLo[ideal_reg]);
  
#line 24738 "ad_ppc.cpp"

}

OptoRegPair Matcher::c_return_value(uint ideal_reg) {

#line 3818 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"

    assert((ideal_reg >= Op_RegI && ideal_reg <= Op_RegL) ||
            (ideal_reg == Op_RegN && CompressedOops::base() == NULL && CompressedOops::shift() == 0),
            "only return normal values");
    // enum names from opcodes.hpp:    Op_Node Op_Set Op_RegN       Op_RegI       Op_RegP       Op_RegF       Op_RegD       Op_RegL
    static int typeToRegLo[Op_RegL+1] = { 0,   0,     R3_num,   R3_num,   R3_num,   F1_num,   F1_num,   R3_num };
    static int typeToRegHi[Op_RegL+1] = { 0,   0,     OptoReg::Bad, R3_H_num, R3_H_num, OptoReg::Bad, F1_H_num, R3_H_num };
    return OptoRegPair(typeToRegHi[ideal_reg], typeToRegLo[ideal_reg]);
  
#line 24754 "ad_ppc.cpp"

}

OptoReg::Name Matcher::inline_cache_reg() { return OptoReg::Name(R19_num); }

int Matcher::inline_cache_reg_encode() { return _regEncode[inline_cache_reg()]; }

OptoReg::Name Matcher::interpreter_frame_pointer_reg() { return OptoReg::Name(R14_num); }

OptoReg::Name Matcher::c_frame_pointer() const { return OptoReg::Name(R1_num); }

// Number of callee-save + always-save registers
int  Matcher::number_of_saved_registers() {
  return 0;
};

bool Compile::needs_deep_clone_jvms() { return true; }

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
