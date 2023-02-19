#line 1 "ad_ppc_expand.cpp"
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
#include "adfiles/ad_ppc.hpp"
#include "oops/compressedOops.hpp"

// Register masks, one for each register class.
const RegMask _BITS32_REG_RW_mask( 0x45555555, 0x4155555, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _BITS32_REG_RO_mask( 0x45555555, 0x4155555, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RSCRATCH1_BITS32_REG_mask( 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RSCRATCH2_BITS32_REG_mask( 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RARG1_BITS32_REG_mask( 0x0, 0x100000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RARG2_BITS32_REG_mask( 0x0, 0x40000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RARG3_BITS32_REG_mask( 0x0, 0x10000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RARG4_BITS32_REG_mask( 0x0, 0x4000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RSCRATCH1_BITS64_REG_mask( 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RSCRATCH2_BITS64_REG_mask( 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RARG1_BITS64_REG_mask( 0x0, 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RARG2_BITS64_REG_mask( 0x0, 0xc0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RARG3_BITS64_REG_mask( 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _RARG4_BITS64_REG_mask( 0x0, 0xc000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _THREAD_BITS64_REG_mask( 0x0, 0xc00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R19_BITS64_REG_mask( 0x300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _BITS64_REG_RW_mask( 0xcfffffff, 0xc3fffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _BITS64_REG_LEAF_CALL_mask( 0xcfffffff, 0x3fffc3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _BITS64_CONSTANT_TABLE_BASE_mask( 0xcffffcff, 0x3fffc3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _BITS64_REG_RO_mask( 0xcfffffff, 0x3cffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_FLAGS_mask( 0x0, 0x0, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_FLAGS_RO_mask( 0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_FLAGS_CR0_mask( 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_FLAGS_CR1_mask( 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_FLAGS_CR6_mask( 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _CTR_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x400, 0x0, 0x0, 0x0 );
const RegMask _FLT_REG_mask( 0x0, 0x0, 0x55555555, 0x55555555, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _DBL_REG_mask( 0x0, 0x0, 0xffffffff, 0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VS_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0xfffff00, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffff0000, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _DYNAMIC_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
MachNode* loadB_indirect_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  if (mem == (Node*)1) {
    idx0--; // Adjust base because memory edge hasn't been inserted yet
  }
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  loadUB_indirectNode *n0 = new loadUB_indirectNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  if (mem != (Node*)1) {
    n0->add_req(_in[1]);	// Add memory edge
  }
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // mem
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convB2I_reg_2Node *n1 = new convB2I_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmp
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* loadB_indirect_ac_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  if (mem == (Node*)1) {
    idx0--; // Adjust base because memory edge hasn't been inserted yet
  }
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  loadUB_indirect_acNode *n0 = new loadUB_indirect_acNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  if (mem != (Node*)1) {
    n0->add_req(_in[1]);	// Add memory edge
  }
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // mem
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convB2I_reg_2Node *n1 = new convB2I_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmp
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* loadB_indOffset16_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  if (mem == (Node*)1) {
    idx0--; // Adjust base because memory edge hasn't been inserted yet
  }
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  loadUB_indOffset16Node *n0 = new loadUB_indOffset16Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  if (mem != (Node*)1) {
    n0->add_req(_in[1]);	// Add memory edge
  }
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // mem
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convB2I_reg_2Node *n1 = new convB2I_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmp
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* loadB_indOffset16_ac_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  if (mem == (Node*)1) {
    idx0--; // Adjust base because memory edge hasn't been inserted yet
  }
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  loadUB_indOffset16_acNode *n0 = new loadUB_indOffset16_acNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  if (mem != (Node*)1) {
    n0->add_req(_in[1]);	// Add memory edge
  }
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // mem
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convB2I_reg_2Node *n1 = new convB2I_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmp
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* loadF_acNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP cr0
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* loadD_acNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP cr0
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* loadConI_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immI16Oper(
#line 5789 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
_opnds[1]->constant() 
#line 273 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new immIhi16Oper(
#line 5791 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
_opnds[1]->constant() 
#line 278 "ad_ppc_expand.cpp"
);
  MachOper *op2 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  loadConIhi16Node *n0 = new loadConIhi16Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, op1->clone()); // srcHi
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  loadConI32_lo16Node *n1 = new loadConI32_lo16Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op2->clone()); // tmpI
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  n1->set_opnd_array(2, op0->clone()); // srcLo
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* loadConL32_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immL16Oper(
#line 5845 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
_opnds[1]->constant() /*& 0x0000FFFFL */
#line 323 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new immL32hi16Oper(
#line 5847 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
_opnds[1]->constant() /*& 0xFFFF0000L */
#line 328 "ad_ppc_expand.cpp"
);
  MachOper *op2 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  loadConL32hi16Node *n0 = new loadConL32hi16Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp4 = n0;
  n0->set_opnd_array(1, op1->clone()); // srcHi
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  loadConL32_lo16Node *n1 = new loadConL32_lo16Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op2->clone()); // tmpL
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  n1->set_opnd_array(2, op0->clone()); // srcLo
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* loadConLhighest16_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immL32hi16Oper(
#line 5878 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
_opnds[1]->constant() >> 32 /*& 0xFFFF0000L */
#line 373 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new immIOper(
#line 5879 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
32 
#line 378 "ad_ppc_expand.cpp"
);
  MachOper *op2 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  loadConL32hi16Node *n0 = new loadConL32hi16Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp4 = n0;
  n0->set_opnd_array(1, op0->clone()); // srcHi
  if(tmp2 != NULL)
    n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  lshiftL_regL_immINode *n1 = new lshiftL_regL_immINode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op2->clone()); // tmpL
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  n1->set_opnd_array(2, op1->clone()); // shift32
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* loadConL_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* loadConNKlass_maskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src2
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNSRC));
  add_req(def);

  return this;
}

MachNode* loadConNKlass_loNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src2
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNSRC));
  add_req(def);

  return this;
}

MachNode* loadConPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP toc
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);

  return this;
}

MachNode* loadConP_loNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP base
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);

  return this;
}

MachNode* loadConP_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* loadConF_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* loadConD_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* encodeP_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP crx
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* decodeN_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP crx
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* decodeN_mergeDisjointNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP base
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLSRC));
  add_req(def);

  return this;
}

MachNode* decodeN_Disjoint_notNull_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);

  return this;
}

MachNode* decodeN_Disjoint_isel_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP crx
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* encodePKlass_not_null_ExExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immLOper(
#line 7036 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(jlong)(intptr_t)CompressedKlassPointers::base() 
#line 553 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  loadConL_ExNode *n0 = new loadConL_ExNode();
  n0->add_req(_in[0]);
  ((MachTypeNode*)n0)->_bottom_type = bottom_type();
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp3 = n0;
  n0->set_opnd_array(1, op0->clone()); // baseImm
  if(tmp2 != NULL)
    n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  encodePKlass_not_null_ExNode *n1 = new encodePKlass_not_null_ExNode();
  n1->add_req(_in[0]);
  ((MachTypeNode*)n1)->_bottom_type = bottom_type();
  n1->set_opnd_array(0, state->MachOperGenerator(IREGNDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op1->clone()); // base
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* decodeNKlass_notNull_addBase_ExExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immLOper(
#line 7115 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(jlong)((intptr_t)CompressedKlassPointers::base() >> CompressedKlassPointers::shift()) 
#line 603 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  loadConL_ExNode *n0 = new loadConL_ExNode();
  n0->add_req(_in[0]);
  ((MachTypeNode*)n0)->_bottom_type = bottom_type();
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp3 = n0;
  n0->set_opnd_array(1, op0->clone()); // baseImm
  if(tmp2 != NULL)
    n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  decodeNKlass_notNull_addBase_ExNode *n1 = new decodeNKlass_notNull_addBase_ExNode();
  n1->add_req(_in[0]);
  ((MachTypeNode*)n1)->_bottom_type = bottom_type();
  n1->set_opnd_array(0, state->MachOperGenerator(IREGPDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op1->clone()); // base
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* compareAndSwapB_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndSwapB4_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL src2
  kill = new MachProjNode( this, 2, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndSwapS_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndSwapS4_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL src2
  kill = new MachProjNode( this, 2, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndSwapI_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndSwapN_regP_regN_regNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndSwapL_regP_regL_regLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndSwapP_regP_regP_regPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapB_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapB4_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL src2
  kill = new MachProjNode( this, 2, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapB_acq_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapB4_acq_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL src2
  kill = new MachProjNode( this, 2, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapS_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapS4_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL src2
  kill = new MachProjNode( this, 2, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapS_acq_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapS4_acq_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL src2
  kill = new MachProjNode( this, 2, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapI_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapI_acq_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapN_regP_regN_regNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapN_acq_regP_regN_regNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapL_regP_regL_regLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapL_acq_regP_regL_regLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapP_regP_regP_regPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* weakCompareAndSwapP_acq_regP_regP_regPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeB_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeB4_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL src2
  kill = new MachProjNode( this, 2, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeB_acq_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeB4_acq_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL src2
  kill = new MachProjNode( this, 2, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeS_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeS4_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL src2
  kill = new MachProjNode( this, 2, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeS_acq_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeS4_acq_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL src2
  kill = new MachProjNode( this, 2, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeI_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeI_acq_regP_regI_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeN_regP_regN_regNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeN_acq_regP_regN_regNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeL_regP_regL_regLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeL_acq_regP_regL_regLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeP_regP_regP_regPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* compareAndExchangeP_acq_regP_regP_regPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndAddBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndAddB4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndAddSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndAddS4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndAddINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndAddLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndSetBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndSetB4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndSetSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndSetS4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL mem_ptr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG3_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndSetINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndSetLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndSetPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* getAndSetNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP cr0
  def = new MachTempNode(state->MachOperGenerator(FLAGSREGCR0));
  add_req(def);

  return this;
}

MachNode* tree_addI_addI_addI_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  addI_reg_regNode *n0 = new addI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  addI_reg_reg_2Node *n1 = new addI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(3)->clone()); // src3
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n1->add_req(_in[i + idx3]);
    }
  }
  else n1->add_req(tmp3);
  n1->set_opnd_array(2, opnd_array(4)->clone()); // src4
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );

  addI_reg_regNode *n2 = new addI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_addI_addI_addI_reg_reg_Ex_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  addI_reg_regNode *n0 = new addI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src1
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, opnd_array(3)->clone()); // src2
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  addI_reg_reg_2Node *n1 = new addI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(4)->clone()); // src3
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src4
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  addI_reg_regNode *n2 = new addI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_addI_addI_addI_reg_reg_Ex_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  addI_reg_regNode *n0 = new addI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src1
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, opnd_array(3)->clone()); // src2
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  addI_reg_reg_2Node *n1 = new addI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src3
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, opnd_array(4)->clone()); // src4
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );

  addI_reg_regNode *n2 = new addI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_addI_addI_addI_reg_reg_Ex_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  addI_reg_regNode *n0 = new addI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(3)->clone()); // src1
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  n0->set_opnd_array(2, opnd_array(4)->clone()); // src2
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );

  addI_reg_reg_2Node *n1 = new addI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src3
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src4
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  addI_reg_regNode *n2 = new addI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_addL_addL_addL_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  addL_reg_regNode *n0 = new addL_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  addL_reg_reg_2Node *n1 = new addL_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(3)->clone()); // src3
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n1->add_req(_in[i + idx3]);
    }
  }
  else n1->add_req(tmp3);
  n1->set_opnd_array(2, opnd_array(4)->clone()); // src4
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );

  addL_reg_regNode *n2 = new addL_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_addL_addL_addL_reg_reg_Ex_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  addL_reg_regNode *n0 = new addL_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src1
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, opnd_array(3)->clone()); // src2
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  addL_reg_reg_2Node *n1 = new addL_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(4)->clone()); // src3
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src4
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  addL_reg_regNode *n2 = new addL_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_addL_addL_addL_reg_reg_Ex_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  addL_reg_regNode *n0 = new addL_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src1
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, opnd_array(3)->clone()); // src2
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  addL_reg_reg_2Node *n1 = new addL_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src3
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, opnd_array(4)->clone()); // src4
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );

  addL_reg_regNode *n2 = new addL_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_addL_addL_addL_reg_reg_Ex_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  addL_reg_regNode *n0 = new addL_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(3)->clone()); // src1
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  n0->set_opnd_array(2, opnd_array(4)->clone()); // src2
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );

  addL_reg_reg_2Node *n1 = new addL_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src3
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src4
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  addL_reg_regNode *n2 = new addL_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* absI_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  signmask32I_regINode *n0 = new signmask32I_regINode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  xorI_reg_regNode *n1 = new xorI_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp3 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  subI_reg_regNode *n2 = new subI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op1->clone()); // tmp2
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  n2->set_opnd_array(2, op0->clone()); // tmp1
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* absL_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  signmask64L_regLNode *n0 = new signmask64L_regLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  xorL_reg_regNode *n1 = new xorL_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp3 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  subL_reg_regNode *n2 = new subL_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op1->clone()); // tmp2
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  n2->set_opnd_array(2, op0->clone()); // tmp1
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* divI_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immI16Oper(
#line 8870 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)-1 
#line 2327 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new flagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  cmpI_reg_imm16Node *n0 = new cmpI_reg_imm16Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, op0->clone()); // imm
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  divI_reg_regnotMinus1Node *n1 = new divI_reg_regnotMinus1Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  cmovI_bne_negI_regNode *n2 = new cmovI_bne_negI_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  n2->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n2->add_req(_in[i + idx0]);
    }
  }
  else n2->add_req(tmp0);
  tmp0 = n2;
  n2->set_opnd_array(2, op1->clone()); // tmp1
  if(tmp4 != NULL)
    n2->add_req(tmp4);
  n2->set_opnd_array(3, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* divL_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immL16Oper(
#line 8929 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)-1 
#line 2412 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new flagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  cmpL_reg_imm16Node *n0 = new cmpL_reg_imm16Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, op0->clone()); // imm
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  divL_reg_regnotMinus1Node *n1 = new divL_reg_regnotMinus1Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  cmovL_bne_negL_regNode *n2 = new cmovL_bne_negL_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n2->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n2->add_req(_in[i + idx0]);
    }
  }
  else n2->add_req(tmp0);
  tmp0 = n2;
  n2->set_opnd_array(2, op1->clone()); // tmp1
  if(tmp4 != NULL)
    n2->add_req(tmp4);
  n2->set_opnd_array(3, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* modI_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immI16Oper(
#line 8943 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)-1 
#line 2497 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new flagsRegOper();
  MachOper *op2 = new iRegIdstOper();
  MachOper *op3 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  cmpI_reg_imm16Node *n0 = new cmpI_reg_imm16Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, op0->clone()); // imm
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  divI_reg_regnotMinus1Node *n1 = new divI_reg_regnotMinus1Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  cmovI_bne_negI_regNode *n2 = new cmovI_bne_negI_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  n2->set_opnd_array(1, op2->clone()); // tmp2
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  tmp5 = n2;
  n2->set_opnd_array(2, op1->clone()); // tmp1
  if(tmp4 != NULL)
    n2->add_req(tmp4);
  n2->set_opnd_array(3, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  result = n2->Expand( state, proj_list, mem );

  mulI_reg_regNode *n3 = new mulI_reg_regNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n3;
  n3->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n3->add_req(_in[i + idx2]);
    }
  }
  else n3->add_req(tmp2);
  n3->set_opnd_array(2, op2->clone()); // tmp2
  if(tmp5 != NULL)
    n3->add_req(tmp5);
  result = n3->Expand( state, proj_list, mem );

  subI_reg_regNode *n4 = new subI_reg_regNode();
  n4->add_req(_in[0]);
  n4->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n4;
  n4->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n4->add_req(_in[i + idx1]);
    }
  }
  else n4->add_req(tmp1);
  n4->set_opnd_array(2, op3->clone()); // tmp3
  if(tmp6 != NULL)
    n4->add_req(tmp6);
  result = n4->Expand( state, proj_list, mem );


  return result;
}

MachNode* modL_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immL16Oper(
#line 8961 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)-1 
#line 2614 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new flagsRegOper();
  MachOper *op2 = new iRegLdstOper();
  MachOper *op3 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  cmpL_reg_imm16Node *n0 = new cmpL_reg_imm16Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, op0->clone()); // imm
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  divL_reg_regnotMinus1Node *n1 = new divL_reg_regnotMinus1Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp5 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  cmovL_bne_negL_regNode *n2 = new cmovL_bne_negL_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n2->set_opnd_array(1, op2->clone()); // tmp2
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  tmp5 = n2;
  n2->set_opnd_array(2, op1->clone()); // tmp1
  if(tmp4 != NULL)
    n2->add_req(tmp4);
  n2->set_opnd_array(3, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  result = n2->Expand( state, proj_list, mem );

  mulL_reg_regNode *n3 = new mulL_reg_regNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp6 = n3;
  n3->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n3->add_req(_in[i + idx2]);
    }
  }
  else n3->add_req(tmp2);
  n3->set_opnd_array(2, op2->clone()); // tmp2
  if(tmp5 != NULL)
    n3->add_req(tmp5);
  result = n3->Expand( state, proj_list, mem );

  subL_reg_regNode *n4 = new subL_reg_regNode();
  n4->add_req(_in[0]);
  n4->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n4;
  n4->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n4->add_req(_in[i + idx1]);
    }
  }
  else n4->add_req(tmp1);
  n4->set_opnd_array(2, op3->clone()); // tmp3
  if(tmp6 != NULL)
    n4->add_req(tmp6);
  result = n4->Expand( state, proj_list, mem );


  return result;
}

MachNode* umodI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  udivI_reg_regNode *n0 = new udivI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  mulI_reg_regNode *n1 = new mulI_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, op0->clone()); // tmp1
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );

  subI_reg_regNode *n2 = new subI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp4 != NULL)
    n2->add_req(tmp4);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* umodL_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  udivL_reg_regNode *n0 = new udivL_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  mulL_reg_regNode *n1 = new mulL_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp4 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, op0->clone()); // tmp1
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );

  subL_reg_regNode *n2 = new subL_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n2;
  n2->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp4 != NULL)
    n2->add_req(tmp4);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* lShiftI_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new uimmI6Oper(
#line 9053 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x3b /* clear 59 bits, keep 5 */ 
#line 2879 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  maskI_reg_immNode *n0 = new maskI_reg_immNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, op0->clone()); // mask
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  lShiftI_reg_regNode *n1 = new lShiftI_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op1->clone()); // tmpI
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* lShiftI_andI_immInegpow2_rShiftI_imm5Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src1
    unsigned num2 = opnd_array(2)->num_edges(); 	// src3
    unsigned num3 = opnd_array(3)->num_edges(); 	// src2
    unsigned num4 = opnd_array(4)->num_edges(); 	// src3
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* lShiftL_regL_regI_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new uimmI6Oper(
#line 9128 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x3a /* clear 58 bits, keep 6 */ 
#line 2963 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  maskI_reg_immNode *n0 = new maskI_reg_immNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, op0->clone()); // mask
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  lShiftL_regL_regINode *n1 = new lShiftL_regL_regINode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op1->clone()); // tmpI
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* arShiftI_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new uimmI6Oper(
#line 9191 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x3b /* clear 59 bits, keep 5 */ 
#line 3021 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  maskI_reg_immNode *n0 = new maskI_reg_immNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, op0->clone()); // mask
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  arShiftI_reg_regNode *n1 = new arShiftI_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op1->clone()); // tmpI
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* arShiftL_regL_regI_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new uimmI6Oper(
#line 9229 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x3a /* clear 58 bits, keep 6 */ 
#line 3079 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  maskI_reg_immNode *n0 = new maskI_reg_immNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, op0->clone()); // mask
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  arShiftL_regL_regINode *n1 = new arShiftL_regL_regINode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op1->clone()); // tmpI
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* urShiftI_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new uimmI6Oper(
#line 9279 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x3b /* clear 59 bits, keep 5 */ 
#line 3137 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  maskI_reg_immNode *n0 = new maskI_reg_immNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, op0->clone()); // mask
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  urShiftI_reg_regNode *n1 = new urShiftI_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op1->clone()); // tmpI
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* urShiftL_regL_regI_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new uimmI6Oper(
#line 9317 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x3a /* clear 58 bits, keep 6 */ 
#line 3195 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  maskI_reg_immNode *n0 = new maskI_reg_immNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, op0->clone()); // mask
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  urShiftL_regL_regINode *n1 = new urShiftL_regL_regINode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op1->clone()); // tmpI
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* rotlI_reg_immi8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// lshift
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned num4 = opnd_array(4)->num_edges(); 	// rshift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // rshift
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rotlI_reg_immi8_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// rshift
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned num4 = opnd_array(4)->num_edges(); 	// lshift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // lshift
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rotrI_reg_immi8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// rshift
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned num4 = opnd_array(4)->num_edges(); 	// lshift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // lshift
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rotrI_reg_immi8_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// lshift
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned num4 = opnd_array(4)->num_edges(); 	// rshift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // rshift
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* andI_reg_immIhi16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_reg_uimm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_reg_uimm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* tree_orI_orI_orI_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  orI_reg_regNode *n0 = new orI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  orI_reg_reg_2Node *n1 = new orI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(3)->clone()); // src3
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n1->add_req(_in[i + idx3]);
    }
  }
  else n1->add_req(tmp3);
  n1->set_opnd_array(2, opnd_array(4)->clone()); // src4
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );

  orI_reg_regNode *n2 = new orI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_orI_orI_orI_reg_reg_Ex_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  orI_reg_regNode *n0 = new orI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src1
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, opnd_array(3)->clone()); // src2
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  orI_reg_reg_2Node *n1 = new orI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(4)->clone()); // src3
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src4
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  orI_reg_regNode *n2 = new orI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_orI_orI_orI_reg_reg_Ex_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  orI_reg_regNode *n0 = new orI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src1
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, opnd_array(3)->clone()); // src2
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  orI_reg_reg_2Node *n1 = new orI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src3
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, opnd_array(4)->clone()); // src4
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );

  orI_reg_regNode *n2 = new orI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_orI_orI_orI_reg_reg_Ex_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  orI_reg_regNode *n0 = new orI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(3)->clone()); // src1
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  n0->set_opnd_array(2, opnd_array(4)->clone()); // src2
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );

  orI_reg_reg_2Node *n1 = new orI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src3
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src4
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  orI_reg_regNode *n2 = new orI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_xorI_xorI_xorI_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  xorI_reg_regNode *n0 = new xorI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  xorI_reg_reg_2Node *n1 = new xorI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(3)->clone()); // src3
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n1->add_req(_in[i + idx3]);
    }
  }
  else n1->add_req(tmp3);
  n1->set_opnd_array(2, opnd_array(4)->clone()); // src4
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );

  xorI_reg_regNode *n2 = new xorI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_xorI_xorI_xorI_reg_reg_Ex_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  xorI_reg_regNode *n0 = new xorI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src1
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, opnd_array(3)->clone()); // src2
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  xorI_reg_reg_2Node *n1 = new xorI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(4)->clone()); // src3
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src4
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  xorI_reg_regNode *n2 = new xorI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_xorI_xorI_xorI_reg_reg_Ex_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  xorI_reg_regNode *n0 = new xorI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src1
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(2, opnd_array(3)->clone()); // src2
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  xorI_reg_reg_2Node *n1 = new xorI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src3
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, opnd_array(4)->clone()); // src4
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );

  xorI_reg_regNode *n2 = new xorI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* tree_xorI_xorI_xorI_reg_reg_Ex_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegIdstOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  xorI_reg_regNode *n0 = new xorI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(3)->clone()); // src1
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  n0->set_opnd_array(2, opnd_array(4)->clone()); // src2
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );

  xorI_reg_reg_2Node *n1 = new xorI_reg_reg_2Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src3
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src4
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  xorI_reg_regNode *n2 = new xorI_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmp1
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // tmp2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* convI2Bool_reg__cntlz_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immIOper(
#line 10428 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x5 
#line 4054 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new uimmI16Oper(
#line 10429 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x1 
#line 4059 "ad_ppc_expand.cpp"
);
  MachOper *op2 = new iRegIdstOper();
  MachOper *op3 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  countLeadingZerosINode *n0 = new countLeadingZerosINode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  urShiftI_reg_immNode *n1 = new urShiftI_reg_immNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n1;
  n1->set_opnd_array(1, op2->clone()); // tmp1
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  n1->set_opnd_array(2, op0->clone()); // shiftAmount
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  xorI_reg_uimm16Node *n2 = new xorI_reg_uimm16Node();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op3->clone()); // tmp2
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // mask
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* convI2Bool_reg__cmoveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP crx
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* xorI_convI2Bool_reg_immIvalue1__cntlz_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immIOper(
#line 10461 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x5 
#line 4133 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  countLeadingZerosINode *n0 = new countLeadingZerosINode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  urShiftI_reg_immNode *n1 = new urShiftI_reg_immNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op1->clone()); // tmp1
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  n1->set_opnd_array(2, op0->clone()); // shiftAmount
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* xorI_convI2Bool_reg_immIvalue1__cmoveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP crx
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* convP2Bool_reg__cntlz_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immIOper(
#line 10516 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x6 
#line 4195 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new uimmI16Oper(
#line 10517 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x1 
#line 4200 "ad_ppc_expand.cpp"
);
  MachOper *op2 = new iRegIdstOper();
  MachOper *op3 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  countLeadingZerosPNode *n0 = new countLeadingZerosPNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  urShiftI_reg_immNode *n1 = new urShiftI_reg_immNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n1;
  n1->set_opnd_array(1, op2->clone()); // tmp1
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  n1->set_opnd_array(2, op0->clone()); // shiftAmount
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  xorI_reg_uimm16Node *n2 = new xorI_reg_uimm16Node();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op3->clone()); // tmp2
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(2, op1->clone()); // mask
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* convP2Bool_reg__cmoveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP crx
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* xorI_convP2Bool_reg__cntlz_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immIOper(
#line 10549 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
0x6 
#line 4274 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  countLeadingZerosPNode *n0 = new countLeadingZerosPNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  urShiftI_reg_immNode *n1 = new urShiftI_reg_immNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op1->clone()); // tmp1
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  n1->set_opnd_array(2, op0->clone()); // shiftAmount
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* xorI_convP2Bool_reg_immIvalue1__cmoveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP crx
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* cmpLTMask_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new iRegLdstOper();
  MachOper *op2 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  convI2L_regNode *n0 = new convI2L_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convI2L_regNode *n1 = new convI2L_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp4 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  subL_reg_regNode *n2 = new subL_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp5 = n2;
  n2->set_opnd_array(1, op0->clone()); // src1s
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  n2->set_opnd_array(2, op1->clone()); // src2s
  if(tmp4 != NULL)
    n2->add_req(tmp4);
  result = n2->Expand( state, proj_list, mem );

  signmask64I_regLNode *n3 = new signmask64I_regLNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n3;
  n3->set_opnd_array(1, op2->clone()); // diff
  if(tmp5 != NULL)
    n3->add_req(tmp5);
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* convB2I_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// amount
    unsigned num3 = opnd_array(3)->num_edges(); 	// amount
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* convS2I_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// amount
    unsigned num3 = opnd_array(3)->num_edges(); 	// amount
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* convD2I_reg_ExExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regDOper();
  MachOper *op1 = new stackSlotLOper();
  MachOper *op2 = new flagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  cmpDUnordered_reg_regNode *n0 = new cmpDUnordered_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convD2IRaw_regDNode *n1 = new convD2IRaw_regDNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp2 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  moveD2L_reg_stackNode *n2 = new moveD2L_reg_stackNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(STACKSLOTL));
  tmp3 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmpD
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );

  cmovI_bso_stackSlotL_conLvalue0_ExNode *n3 = new cmovI_bso_stackSlotL_conLvalue0_ExNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n3;
  n3->set_opnd_array(1, op2->clone()); // crx
  if(tmp4 != NULL)
    n3->add_req(tmp4);
  n3->set_opnd_array(2, op1->clone()); // tmpS
  if(tmp3 != NULL)
    n3->add_req(tmp3);
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* convD2I_reg_mffprd_ExExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regDOper();
  MachOper *op1 = new flagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  cmpDUnordered_reg_regNode *n0 = new cmpDUnordered_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convD2IRaw_regDNode *n1 = new convD2IRaw_regDNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp2 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  cmovI_bso_reg_conLvalue0_ExNode *n2 = new cmovI_bso_reg_conLvalue0_ExNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op1->clone()); // crx
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  n2->set_opnd_array(2, op0->clone()); // tmpD
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* convF2I_regF_ExExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regFOper();
  MachOper *op1 = new stackSlotLOper();
  MachOper *op2 = new flagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  cmpFUnordered_reg_regNode *n0 = new cmpFUnordered_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convF2IRaw_regFNode *n1 = new convF2IRaw_regFNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGF));
  tmp2 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  moveF2L_reg_stackNode *n2 = new moveF2L_reg_stackNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(STACKSLOTL));
  tmp3 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmpF
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );

  cmovI_bso_stackSlotL_conLvalue0_ExNode *n3 = new cmovI_bso_stackSlotL_conLvalue0_ExNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n3;
  n3->set_opnd_array(1, op2->clone()); // crx
  if(tmp4 != NULL)
    n3->add_req(tmp4);
  n3->set_opnd_array(2, op1->clone()); // tmpS
  if(tmp3 != NULL)
    n3->add_req(tmp3);
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* convF2I_regF_mffprd_ExExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regFOper();
  MachOper *op1 = new flagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  cmpFUnordered_reg_regNode *n0 = new cmpFUnordered_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convF2IRaw_regFNode *n1 = new convF2IRaw_regFNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGF));
  tmp2 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  cmovI_bso_reg_conLvalue0_ExNode *n2 = new cmovI_bso_reg_conLvalue0_ExNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op1->clone()); // crx
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  n2->set_opnd_array(2, op0->clone()); // tmpF
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* convF2L_reg_ExExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regFOper();
  MachOper *op1 = new stackSlotLOper();
  MachOper *op2 = new flagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  cmpFUnordered_reg_regNode *n0 = new cmpFUnordered_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convF2LRaw_regFNode *n1 = new convF2LRaw_regFNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGF));
  tmp2 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  moveF2L_reg_stackNode *n2 = new moveF2L_reg_stackNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(STACKSLOTL));
  tmp3 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmpF
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );

  cmovL_bso_stackSlotL_conLvalue0_ExNode *n3 = new cmovL_bso_stackSlotL_conLvalue0_ExNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n3;
  n3->set_opnd_array(1, op2->clone()); // crx
  if(tmp4 != NULL)
    n3->add_req(tmp4);
  n3->set_opnd_array(2, op1->clone()); // tmpS
  if(tmp3 != NULL)
    n3->add_req(tmp3);
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* convF2L_reg_mffprd_ExExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regFOper();
  MachOper *op1 = new flagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  cmpFUnordered_reg_regNode *n0 = new cmpFUnordered_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convF2LRaw_regFNode *n1 = new convF2LRaw_regFNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGF));
  tmp2 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  cmovL_bso_reg_conLvalue0_ExNode *n2 = new cmovL_bso_reg_conLvalue0_ExNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op1->clone()); // crx
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  n2->set_opnd_array(2, op0->clone()); // tmpF
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* convD2L_reg_ExExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regDOper();
  MachOper *op1 = new stackSlotLOper();
  MachOper *op2 = new flagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  cmpDUnordered_reg_regNode *n0 = new cmpDUnordered_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convD2LRaw_regDNode *n1 = new convD2LRaw_regDNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp2 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  moveD2L_reg_stackNode *n2 = new moveD2L_reg_stackNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(STACKSLOTL));
  tmp3 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmpD
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );

  cmovL_bso_stackSlotL_conLvalue0_ExNode *n3 = new cmovL_bso_stackSlotL_conLvalue0_ExNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n3;
  n3->set_opnd_array(1, op2->clone()); // crx
  if(tmp4 != NULL)
    n3->add_req(tmp4);
  n3->set_opnd_array(2, op1->clone()); // tmpS
  if(tmp3 != NULL)
    n3->add_req(tmp3);
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* convD2L_reg_mffprd_ExExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regDOper();
  MachOper *op1 = new flagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  cmpDUnordered_reg_regNode *n0 = new cmpDUnordered_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(FLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convD2LRaw_regDNode *n1 = new convD2LRaw_regDNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp2 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  cmovL_bso_reg_conLvalue0_ExNode *n2 = new cmovL_bso_reg_conLvalue0_ExNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op1->clone()); // crx
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  n2->set_opnd_array(2, op0->clone()); // tmpD
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* convI2F_ireg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new stackSlotLOper();
  MachOper *op2 = new regDOper();
  MachOper *op3 = new regDOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  convI2L_regNode *n0 = new convI2L_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  regL_to_stkLNode *n1 = new regL_to_stkLNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(STACKSLOTL));
  tmp3 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  moveL2D_stack_regNode *n2 = new moveL2D_stack_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp4 = n2;
  n2->set_opnd_array(1, op1->clone()); // tmpS
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );

  convL2DRaw_regDNode *n3 = new convL2DRaw_regDNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp5 = n3;
  n3->set_opnd_array(1, op2->clone()); // tmpD
  if(tmp4 != NULL)
    n3->add_req(tmp4);
  result = n3->Expand( state, proj_list, mem );

  convD2F_regNode *n4 = new convD2F_regNode();
  n4->add_req(_in[0]);
  n4->set_opnd_array(0, state->MachOperGenerator(REGF));
  tmp0 = n4;
  n4->set_opnd_array(1, op3->clone()); // tmpD2
  if(tmp5 != NULL)
    n4->add_req(tmp5);
  result = n4->Expand( state, proj_list, mem );


  return result;
}

MachNode* convI2F_ireg_fcfids_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new stackSlotLOper();
  MachOper *op2 = new regDOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  convI2L_regNode *n0 = new convI2L_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  regL_to_stkLNode *n1 = new regL_to_stkLNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(STACKSLOTL));
  tmp3 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  moveL2D_stack_regNode *n2 = new moveL2D_stack_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp4 = n2;
  n2->set_opnd_array(1, op1->clone()); // tmpS
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );

  convL2FRaw_regFNode *n3 = new convL2FRaw_regFNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(REGF));
  tmp0 = n3;
  n3->set_opnd_array(1, op2->clone()); // tmpD
  if(tmp4 != NULL)
    n3->add_req(tmp4);
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* convI2F_ireg_mtfprd_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regDOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveI2D_regNode *n0 = new moveI2D_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convL2FRaw_regFNode *n1 = new convL2FRaw_regFNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGF));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpD
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* convL2F_ireg_fcfids_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new stackSlotLOper();
  MachOper *op1 = new regDOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  regL_to_stkLNode *n0 = new regL_to_stkLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(STACKSLOTL));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  moveL2D_stack_regNode *n1 = new moveL2D_stack_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp3 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpS
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  convL2FRaw_regFNode *n2 = new convL2FRaw_regFNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(REGF));
  tmp0 = n2;
  n2->set_opnd_array(1, op1->clone()); // tmpD
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* convL2F_ireg_mtfprd_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regDOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveL2D_regNode *n0 = new moveL2D_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convL2FRaw_regFNode *n1 = new convL2FRaw_regFNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGF));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpD
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* convI2D_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new stackSlotLOper();
  MachOper *op2 = new regDOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  convI2L_regNode *n0 = new convI2L_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  regL_to_stkLNode *n1 = new regL_to_stkLNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(STACKSLOTL));
  tmp3 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  moveL2D_stack_regNode *n2 = new moveL2D_stack_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp4 = n2;
  n2->set_opnd_array(1, op1->clone()); // tmpS
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );

  convL2DRaw_regDNode *n3 = new convL2DRaw_regDNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp0 = n3;
  n3->set_opnd_array(1, op2->clone()); // tmpD
  if(tmp4 != NULL)
    n3->add_req(tmp4);
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* convI2D_reg_mtfprd_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regDOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveI2D_regNode *n0 = new moveI2D_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convL2DRaw_regDNode *n1 = new convL2DRaw_regDNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpD
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* convL2D_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regDOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveL2D_stack_regNode *n0 = new moveL2D_stack_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convL2DRaw_regDNode *n1 = new convL2DRaw_regDNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpD
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* convL2D_reg_mtfprd_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new regDOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveL2D_regNode *n0 = new moveL2D_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convL2DRaw_regDNode *n1 = new convL2DRaw_regDNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(REGD));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpD
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmpL3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpF3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpD3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmprb_Digit_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src2
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP crx
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* cmprb_LowerCase_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src2
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP crx
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* cmprb_UpperCase_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src2
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP crx
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* cmprb_Whitespace_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src2
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP crx
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* cmprb_Whitespace_reg_reg_prefixedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src2
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGISRC));
  add_req(def);
  // TEMP crx
  def = new MachTempNode(state->MachOperGenerator(FLAGSREG));
  add_req(def);

  return this;
}

MachNode* partialSubtypeCheckNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp_klass
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp_arrayptr
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);

  return this;
}

MachNode* cmpFastLockNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);

  return this;
}

MachNode* cmpFastLock_tmNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL box
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);

  return this;
}

MachNode* cmpFastUnlockNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);

  return this;
}

MachNode* cmpFastUnlock_tmNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);

  return this;
}

MachNode* inlineCallClearArrayShortNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL base
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 2, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* inlineCallClearArrayLargeNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL base
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 2, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* inlineCallClearArrayNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL base
  kill = new MachProjNode( this, 2, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (RARG3_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 5, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 6, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (RARG3_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 5, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 6, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (RARG3_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 5, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 6, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (RARG3_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (RARG4_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 5, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 6, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equalsLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 2, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt
  kill = new MachProjNode( this, 3, (RARG3_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 4, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 5, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equalsUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 2, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt
  kill = new MachProjNode( this, 3, (RARG3_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 4, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 5, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ary2
  kill = new MachProjNode( this, 2, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 5, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ary2
  kill = new MachProjNode( this, 2, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 5, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm1_char_UNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm1_char_LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm1_char_ULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm1_UNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL needle
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RSCRATCH2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 3, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 4, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm1_LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL needle
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RSCRATCH2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 3, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 4, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm1_ULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL needle
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RSCRATCH2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 3, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 4, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOfChar_UNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOfChar_LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm_UNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RSCRATCH1_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 3, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr6
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR6_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 5, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm_LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RSCRATCH1_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 3, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr6
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR6_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 5, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm_ULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RSCRATCH1_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 3, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr6
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR6_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 5, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_UNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RSCRATCH1_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL needlecnt
  kill = new MachProjNode( this, 2, (RSCRATCH2_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 3, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr6
  kill = new MachProjNode( this, 5, (INT_FLAGS_CR6_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 6, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RSCRATCH1_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL needlecnt
  kill = new MachProjNode( this, 2, (RSCRATCH2_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 3, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr6
  kill = new MachProjNode( this, 5, (INT_FLAGS_CR6_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 6, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_ULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RSCRATCH1_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL needlecnt
  kill = new MachProjNode( this, 2, (RSCRATCH2_BITS32_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 3, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr1
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR1_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr6
  kill = new MachProjNode( this, 5, (INT_FLAGS_CR6_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 6, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compressNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_inflateNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* count_positivesNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // DEF/KILL ctr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 2, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encode_iso_arrayNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encode_ascii_arrayNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (RARG1_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (RARG2_BITS64_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  // DEF/KILL ctr
  kill = new MachProjNode( this, 3, (CTR_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL cr0
  kill = new MachProjNode( this, 4, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minI_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new iRegLdstOper();
  MachOper *op2 = new iRegLdstOper();
  MachOper *op3 = new iRegLdstOper();
  MachOper *op4 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  MachNode *tmp7 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  convI2L_regNode *n0 = new convI2L_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convI2L_regNode *n1 = new convI2L_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp4 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  subL_reg_regNode *n2 = new subL_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp5 = n2;
  n2->set_opnd_array(1, op1->clone()); // src2s
  if(tmp4 != NULL)
    n2->add_req(tmp4);
  n2->set_opnd_array(2, op0->clone()); // src1s
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );

  signmask64L_regLNode *n3 = new signmask64L_regLNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp6 = n3;
  n3->set_opnd_array(1, op2->clone()); // diff
  if(tmp5 != NULL)
    n3->add_req(tmp5);
  result = n3->Expand( state, proj_list, mem );

  andL_reg_regNode *n4 = new andL_reg_regNode();
  n4->add_req(_in[0]);
  n4->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp7 = n4;
  n4->set_opnd_array(1, op2->clone()); // diff
  if(tmp5 != NULL)
    n4->add_req(tmp5);
  n4->set_opnd_array(2, op3->clone()); // sm
  if(tmp6 != NULL)
    n4->add_req(tmp6);
  result = n4->Expand( state, proj_list, mem );

  addI_regL_regLNode *n5 = new addI_regL_regLNode();
  n5->add_req(_in[0]);
  n5->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n5;
  n5->set_opnd_array(1, op4->clone()); // doz
  if(tmp7 != NULL)
    n5->add_req(tmp7);
  n5->set_opnd_array(2, op0->clone()); // src1s
  if(tmp3 != NULL)
    n5->add_req(tmp3);
  result = n5->Expand( state, proj_list, mem );


  return result;
}

MachNode* minI_reg_reg_iselNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* maxI_reg_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new iRegLdstOper();
  MachOper *op2 = new iRegLdstOper();
  MachOper *op3 = new iRegLdstOper();
  MachOper *op4 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  MachNode *tmp7 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  convI2L_regNode *n0 = new convI2L_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src1
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  convI2L_regNode *n1 = new convI2L_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp4 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src2
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  subL_reg_regNode *n2 = new subL_reg_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp5 = n2;
  n2->set_opnd_array(1, op1->clone()); // src2s
  if(tmp4 != NULL)
    n2->add_req(tmp4);
  n2->set_opnd_array(2, op0->clone()); // src1s
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );

  signmask64L_regLNode *n3 = new signmask64L_regLNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp6 = n3;
  n3->set_opnd_array(1, op2->clone()); // diff
  if(tmp5 != NULL)
    n3->add_req(tmp5);
  result = n3->Expand( state, proj_list, mem );

  andcL_reg_regNode *n4 = new andcL_reg_regNode();
  n4->add_req(_in[0]);
  n4->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp7 = n4;
  n4->set_opnd_array(1, op2->clone()); // diff
  if(tmp5 != NULL)
    n4->add_req(tmp5);
  n4->set_opnd_array(2, op3->clone()); // sm
  if(tmp6 != NULL)
    n4->add_req(tmp6);
  result = n4->Expand( state, proj_list, mem );

  addI_regL_regLNode *n5 = new addI_regL_regLNode();
  n5->add_req(_in[0]);
  n5->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n5;
  n5->set_opnd_array(1, op4->clone()); // doz
  if(tmp7 != NULL)
    n5->add_req(tmp7);
  n5->set_opnd_array(2, op0->clone()); // src1s
  if(tmp3 != NULL)
    n5->add_req(tmp3);
  result = n5->Expand( state, proj_list, mem );


  return result;
}

MachNode* maxI_reg_reg_iselNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosI_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immI16Oper(
#line 12977 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)-1 
#line 6796 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new immI16Oper(
#line 12978 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)32 
#line 6801 "ad_ppc_expand.cpp"
);
  MachOper *op2 = new immI_minus1Oper(
#line 12979 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
-1 
#line 6806 "ad_ppc_expand.cpp"
);
  MachOper *op3 = new iRegIdstOper();
  MachOper *op4 = new iRegIdstOper();
  MachOper *op5 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  MachNode *tmp7 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  addI_reg_imm16Node *n0 = new addI_reg_imm16Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp5 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, op0->clone()); // imm1
  if(tmp2 != NULL)
    n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  andcI_reg_regNode *n1 = new andcI_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op2->clone()); // m1
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  n1->set_opnd_array(3, op3->clone()); // tmpI1
  if(tmp5 != NULL)
    n1->add_req(tmp5);
  result = n1->Expand( state, proj_list, mem );

  countLeadingZerosINode *n2 = new countLeadingZerosINode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp7 = n2;
  n2->set_opnd_array(1, op4->clone()); // tmpI2
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  result = n2->Expand( state, proj_list, mem );

  subI_imm16_regNode *n3 = new subI_imm16_regNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n3;
  n3->set_opnd_array(1, op1->clone()); // imm2
  if(tmp3 != NULL)
    n3->add_req(tmp3);
  n3->set_opnd_array(2, op5->clone()); // tmpI3
  if(tmp7 != NULL)
    n3->add_req(tmp7);
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* countTrailingZerosL_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immL16Oper(
#line 13009 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(long)-1 
#line 6891 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new immI16Oper(
#line 13010 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)64 
#line 6896 "ad_ppc_expand.cpp"
);
  MachOper *op2 = new iRegLdstOper();
  MachOper *op3 = new iRegLdstOper();
  MachOper *op4 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  addL_reg_imm16Node *n0 = new addL_reg_imm16Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, op0->clone()); // imm1
  if(tmp2 != NULL)
    n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  andcL_reg_regNode *n1 = new andcL_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp5 = n1;
  n1->set_opnd_array(1, op2->clone()); // tmpL1
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  result = n1->Expand( state, proj_list, mem );

  countLeadingZerosLNode *n2 = new countLeadingZerosLNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp6 = n2;
  n2->set_opnd_array(1, op3->clone()); // tmpL2
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  result = n2->Expand( state, proj_list, mem );

  subI_imm16_regNode *n3 = new subI_imm16_regNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n3;
  n3->set_opnd_array(1, op1->clone()); // imm2
  if(tmp3 != NULL)
    n3->add_req(tmp3);
  n3->set_opnd_array(2, op4->clone()); // tmpL3
  if(tmp6 != NULL)
    n3->add_req(tmp6);
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* bytes_reverse_int_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immI16Oper(
#line 13067 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int) 24 
#line 6977 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new immI16Oper(
#line 13068 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int) 16 
#line 6982 "ad_ppc_expand.cpp"
);
  MachOper *op2 = new immI16Oper(
#line 13069 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  8 
#line 6987 "ad_ppc_expand.cpp"
);
  MachOper *op3 = new immI16Oper(
#line 13070 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  4 
#line 6992 "ad_ppc_expand.cpp"
);
  MachOper *op4 = new immI16Oper(
#line 13071 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  0 
#line 6997 "ad_ppc_expand.cpp"
);
  MachOper *op5 = new iRegLdstOper();
  MachOper *op6 = new iRegLdstOper();
  MachOper *op7 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  MachNode *tmp7 = NULL;
  MachNode *tmp8 = NULL;
  MachNode *tmp9 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  urShiftI_reg_immNode *n0 = new urShiftI_reg_immNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp7 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, op0->clone()); // imm24
  if(tmp2 != NULL)
    n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  insrwi_aNode *n1 = new insrwi_aNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n1;
  n1->set_opnd_array(1, op5->clone()); // tmpI1
  if(tmp7 != NULL)
    n1->add_req(tmp7);
  n1->set_opnd_array(2, op0->clone()); // imm24
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  n1->set_opnd_array(3, op2->clone()); // imm8
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );

  urShiftI_reg_immNode *n2 = new urShiftI_reg_immNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp8 = n2;
  n2->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  n2->set_opnd_array(2, op1->clone()); // imm16
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );

  insrwiNode *n3 = new insrwiNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  n3->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n3->add_req(_in[i + idx0]);
    }
  }
  else n3->add_req(tmp0);
  tmp0 = n3;
  n3->set_opnd_array(2, op6->clone()); // tmpI2
  if(tmp8 != NULL)
    n3->add_req(tmp8);
  n3->set_opnd_array(3, op2->clone()); // imm8
  if(tmp4 != NULL)
    n3->add_req(tmp4);
  n3->set_opnd_array(4, op1->clone()); // imm16
  if(tmp3 != NULL)
    n3->add_req(tmp3);
  result = n3->Expand( state, proj_list, mem );

  urShiftI_reg_immNode *n4 = new urShiftI_reg_immNode();
  n4->add_req(_in[0]);
  n4->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp9 = n4;
  n4->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n4->add_req(_in[i + idx1]);
    }
  }
  else n4->add_req(tmp1);
  n4->set_opnd_array(2, op2->clone()); // imm8
  if(tmp4 != NULL)
    n4->add_req(tmp4);
  result = n4->Expand( state, proj_list, mem );

  insrwiNode *n5 = new insrwiNode();
  n5->add_req(_in[0]);
  n5->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  n5->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n5->add_req(_in[i + idx0]);
    }
  }
  else n5->add_req(tmp0);
  tmp0 = n5;
  n5->set_opnd_array(2, op7->clone()); // tmpI3
  if(tmp9 != NULL)
    n5->add_req(tmp9);
  n5->set_opnd_array(3, op2->clone()); // imm8
  if(tmp4 != NULL)
    n5->add_req(tmp4);
  n5->set_opnd_array(4, op2->clone()); // imm8
  if(tmp4 != NULL)
    n5->add_req(tmp4);
  result = n5->Expand( state, proj_list, mem );

  insrwiNode *n6 = new insrwiNode();
  n6->add_req(_in[0]);
  n6->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  n6->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n6->add_req(_in[i + idx0]);
    }
  }
  else n6->add_req(tmp0);
  tmp0 = n6;
  n6->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n6->add_req(_in[i + idx1]);
    }
  }
  else n6->add_req(tmp1);
  n6->set_opnd_array(3, op4->clone()); // imm0
  if(tmp6 != NULL)
    n6->add_req(tmp6);
  n6->set_opnd_array(4, op2->clone()); // imm8
  if(tmp4 != NULL)
    n6->add_req(tmp4);
  result = n6->Expand( state, proj_list, mem );


  return result;
}

MachNode* bytes_reverse_int_vecNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmpV
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* bytes_reverse_long_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immI16Oper(
#line 13124 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int) 56 
#line 7172 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new immI16Oper(
#line 13125 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int) 48 
#line 7177 "ad_ppc_expand.cpp"
);
  MachOper *op2 = new immI16Oper(
#line 13126 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int) 40 
#line 7182 "ad_ppc_expand.cpp"
);
  MachOper *op3 = new immI16Oper(
#line 13127 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int) 32 
#line 7187 "ad_ppc_expand.cpp"
);
  MachOper *op4 = new immI16Oper(
#line 13128 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int) 24 
#line 7192 "ad_ppc_expand.cpp"
);
  MachOper *op5 = new immI16Oper(
#line 13129 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int) 16 
#line 7197 "ad_ppc_expand.cpp"
);
  MachOper *op6 = new immI16Oper(
#line 13130 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  8 
#line 7202 "ad_ppc_expand.cpp"
);
  MachOper *op7 = new immI16Oper(
#line 13131 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  0 
#line 7207 "ad_ppc_expand.cpp"
);
  MachOper *op8 = new iRegLdstOper();
  MachOper *op9 = new iRegLdstOper();
  MachOper *op10 = new iRegLdstOper();
  MachOper *op11 = new iRegLdstOper();
  MachOper *op12 = new iRegLdstOper();
  MachOper *op13 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  MachNode *tmp5 = NULL;
  MachNode *tmp6 = NULL;
  MachNode *tmp7 = NULL;
  MachNode *tmp8 = NULL;
  MachNode *tmp9 = NULL;
  MachNode *tmp10 = NULL;
  MachNode *tmp11 = NULL;
  MachNode *tmp12 = NULL;
  MachNode *tmp13 = NULL;
  MachNode *tmp14 = NULL;
  MachNode *tmp15 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  rldiclNode *n0 = new rldiclNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp10 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, op6->clone()); // imm8
  if(tmp8 != NULL)
    n0->add_req(tmp8);
  n0->set_opnd_array(3, op4->clone()); // imm24
  if(tmp6 != NULL)
    n0->add_req(tmp6);
  result = n0->Expand( state, proj_list, mem );

  rldiclNode *n1 = new rldiclNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp11 = n1;
  n1->set_opnd_array(1, op8->clone()); // tmpL1
  if(tmp10 != NULL)
    n1->add_req(tmp10);
  n1->set_opnd_array(2, op3->clone()); // imm32
  if(tmp5 != NULL)
    n1->add_req(tmp5);
  n1->set_opnd_array(3, op4->clone()); // imm24
  if(tmp6 != NULL)
    n1->add_req(tmp6);
  result = n1->Expand( state, proj_list, mem );

  rldiclNode *n2 = new rldiclNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp12 = n2;
  n2->set_opnd_array(1, op9->clone()); // tmpL2
  if(tmp11 != NULL)
    n2->add_req(tmp11);
  n2->set_opnd_array(2, op3->clone()); // imm32
  if(tmp5 != NULL)
    n2->add_req(tmp5);
  n2->set_opnd_array(3, op7->clone()); // imm0
  if(tmp9 != NULL)
    n2->add_req(tmp9);
  result = n2->Expand( state, proj_list, mem );

  rldiclNode *n3 = new rldiclNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp10 = n3;
  n3->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n3->add_req(_in[i + idx1]);
    }
  }
  else n3->add_req(tmp1);
  n3->set_opnd_array(2, op5->clone()); // imm16
  if(tmp7 != NULL)
    n3->add_req(tmp7);
  n3->set_opnd_array(3, op4->clone()); // imm24
  if(tmp6 != NULL)
    n3->add_req(tmp6);
  result = n3->Expand( state, proj_list, mem );

  rldiclNode *n4 = new rldiclNode();
  n4->add_req(_in[0]);
  n4->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp11 = n4;
  n4->set_opnd_array(1, op8->clone()); // tmpL1
  if(tmp10 != NULL)
    n4->add_req(tmp10);
  n4->set_opnd_array(2, op3->clone()); // imm32
  if(tmp5 != NULL)
    n4->add_req(tmp5);
  n4->set_opnd_array(3, op4->clone()); // imm24
  if(tmp6 != NULL)
    n4->add_req(tmp6);
  result = n4->Expand( state, proj_list, mem );

  rldiclNode *n5 = new rldiclNode();
  n5->add_req(_in[0]);
  n5->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp13 = n5;
  n5->set_opnd_array(1, op9->clone()); // tmpL2
  if(tmp11 != NULL)
    n5->add_req(tmp11);
  n5->set_opnd_array(2, op2->clone()); // imm40
  if(tmp4 != NULL)
    n5->add_req(tmp4);
  n5->set_opnd_array(3, op7->clone()); // imm0
  if(tmp9 != NULL)
    n5->add_req(tmp9);
  result = n5->Expand( state, proj_list, mem );

  orL_reg_regNode *n6 = new orL_reg_regNode();
  n6->add_req(_in[0]);
  n6->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp14 = n6;
  n6->set_opnd_array(1, op10->clone()); // tmpL3
  if(tmp12 != NULL)
    n6->add_req(tmp12);
  n6->set_opnd_array(2, op11->clone()); // tmpL4
  if(tmp13 != NULL)
    n6->add_req(tmp13);
  result = n6->Expand( state, proj_list, mem );

  rldiclNode *n7 = new rldiclNode();
  n7->add_req(_in[0]);
  n7->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp10 = n7;
  n7->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n7->add_req(_in[i + idx1]);
    }
  }
  else n7->add_req(tmp1);
  n7->set_opnd_array(2, op4->clone()); // imm24
  if(tmp6 != NULL)
    n7->add_req(tmp6);
  n7->set_opnd_array(3, op4->clone()); // imm24
  if(tmp6 != NULL)
    n7->add_req(tmp6);
  result = n7->Expand( state, proj_list, mem );

  rldiclNode *n8 = new rldiclNode();
  n8->add_req(_in[0]);
  n8->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp11 = n8;
  n8->set_opnd_array(1, op8->clone()); // tmpL1
  if(tmp10 != NULL)
    n8->add_req(tmp10);
  n8->set_opnd_array(2, op3->clone()); // imm32
  if(tmp5 != NULL)
    n8->add_req(tmp5);
  n8->set_opnd_array(3, op4->clone()); // imm24
  if(tmp6 != NULL)
    n8->add_req(tmp6);
  result = n8->Expand( state, proj_list, mem );

  rldiclNode *n9 = new rldiclNode();
  n9->add_req(_in[0]);
  n9->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp12 = n9;
  n9->set_opnd_array(1, op9->clone()); // tmpL2
  if(tmp11 != NULL)
    n9->add_req(tmp11);
  n9->set_opnd_array(2, op1->clone()); // imm48
  if(tmp3 != NULL)
    n9->add_req(tmp3);
  n9->set_opnd_array(3, op7->clone()); // imm0
  if(tmp9 != NULL)
    n9->add_req(tmp9);
  result = n9->Expand( state, proj_list, mem );

  rldiclNode *n10 = new rldiclNode();
  n10->add_req(_in[0]);
  n10->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp10 = n10;
  n10->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n10->add_req(_in[i + idx1]);
    }
  }
  else n10->add_req(tmp1);
  n10->set_opnd_array(2, op3->clone()); // imm32
  if(tmp5 != NULL)
    n10->add_req(tmp5);
  n10->set_opnd_array(3, op4->clone()); // imm24
  if(tmp6 != NULL)
    n10->add_req(tmp6);
  result = n10->Expand( state, proj_list, mem );

  rldiclNode *n11 = new rldiclNode();
  n11->add_req(_in[0]);
  n11->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp11 = n11;
  n11->set_opnd_array(1, op8->clone()); // tmpL1
  if(tmp10 != NULL)
    n11->add_req(tmp10);
  n11->set_opnd_array(2, op3->clone()); // imm32
  if(tmp5 != NULL)
    n11->add_req(tmp5);
  n11->set_opnd_array(3, op4->clone()); // imm24
  if(tmp6 != NULL)
    n11->add_req(tmp6);
  result = n11->Expand( state, proj_list, mem );

  rldiclNode *n12 = new rldiclNode();
  n12->add_req(_in[0]);
  n12->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp13 = n12;
  n12->set_opnd_array(1, op9->clone()); // tmpL2
  if(tmp11 != NULL)
    n12->add_req(tmp11);
  n12->set_opnd_array(2, op0->clone()); // imm56
  if(tmp2 != NULL)
    n12->add_req(tmp2);
  n12->set_opnd_array(3, op7->clone()); // imm0
  if(tmp9 != NULL)
    n12->add_req(tmp9);
  result = n12->Expand( state, proj_list, mem );

  orL_reg_regNode *n13 = new orL_reg_regNode();
  n13->add_req(_in[0]);
  n13->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp15 = n13;
  n13->set_opnd_array(1, op10->clone()); // tmpL3
  if(tmp12 != NULL)
    n13->add_req(tmp12);
  n13->set_opnd_array(2, op11->clone()); // tmpL4
  if(tmp13 != NULL)
    n13->add_req(tmp13);
  result = n13->Expand( state, proj_list, mem );

  orL_reg_regNode *n14 = new orL_reg_regNode();
  n14->add_req(_in[0]);
  n14->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n14;
  n14->set_opnd_array(1, op12->clone()); // tmpL5
  if(tmp14 != NULL)
    n14->add_req(tmp14);
  n14->set_opnd_array(2, op13->clone()); // tmpL6
  if(tmp15 != NULL)
    n14->add_req(tmp15);
  result = n14->Expand( state, proj_list, mem );


  return result;
}

MachNode* bytes_reverse_long_vecNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmpV
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* bytes_reverse_ushort_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immI16Oper(
#line 13196 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int) 16 
#line 7490 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new immI16Oper(
#line 13197 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  8 
#line 7495 "ad_ppc_expand.cpp"
);
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  urShiftI_reg_immNode *n0 = new urShiftI_reg_immNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, op1->clone()); // imm8
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  insrwiNode *n1 = new insrwiNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  n1->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n1->add_req(_in[i + idx0]);
    }
  }
  else n1->add_req(tmp0);
  tmp0 = n1;
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(3, op0->clone()); // imm16
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  n1->set_opnd_array(4, op1->clone()); // imm8
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* bytes_reverse_short_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immI16Oper(
#line 13224 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int) 16 
#line 7559 "ad_ppc_expand.cpp"
);
  MachOper *op1 = new immI16Oper(
#line 13225 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  8 
#line 7564 "ad_ppc_expand.cpp"
);
  MachOper *op2 = new iRegLdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  urShiftI_reg_immNode *n0 = new urShiftI_reg_immNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp4 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, op1->clone()); // imm8
  if(tmp3 != NULL)
    n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );

  insrwiNode *n1 = new insrwiNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  n1->set_opnd_array(1, op2->clone()); // tmpI1
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  tmp4 = n1;
  n1->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(3, op0->clone()); // imm16
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  n1->set_opnd_array(4, op1->clone()); // imm8
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );

  extshNode *n2 = new extshNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op2->clone()); // tmpI1
  if(tmp4 != NULL)
    n2->add_req(tmp4);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* repl8B_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveRegNode *n0 = new moveRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  repl56Node *n1 = new repl56Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n1->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n1->add_req(_in[i + idx0]);
    }
  }
  else n1->add_req(tmp0);
  tmp0 = n1;
  result = n1->Expand( state, proj_list, mem );

  repl48Node *n2 = new repl48Node();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n2->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n2->add_req(_in[i + idx0]);
    }
  }
  else n2->add_req(tmp0);
  tmp0 = n2;
  result = n2->Expand( state, proj_list, mem );

  repl32Node *n3 = new repl32Node();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n3->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n3->add_req(_in[i + idx0]);
    }
  }
  else n3->add_req(tmp0);
  tmp0 = n3;
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* repl16B_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new vecXOper();
  MachOper *op2 = new immI8Oper(
#line 13520 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  1 
#line 7704 "ad_ppc_expand.cpp"
);
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveRegNode *n0 = new moveRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  repl56Node *n1 = new repl56Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n1->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  tmp2 = n1;
  result = n1->Expand( state, proj_list, mem );

  repl48Node *n2 = new repl48Node();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n2->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  tmp2 = n2;
  result = n2->Expand( state, proj_list, mem );

  mtvsrwzNode *n3 = new mtvsrwzNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(VECX));
  tmp3 = n3;
  n3->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n3->add_req(tmp2);
  result = n3->Expand( state, proj_list, mem );

  xxspltwNode *n4 = new xxspltwNode();
  n4->add_req(_in[0]);
  n4->set_opnd_array(0, state->MachOperGenerator(VECX));
  tmp0 = n4;
  n4->set_opnd_array(1, op1->clone()); // tmpV
  if(tmp3 != NULL)
    n4->add_req(tmp3);
  n4->set_opnd_array(2, op2->clone()); // imm1
  if(tmp4 != NULL)
    n4->add_req(tmp4);
  result = n4->Expand( state, proj_list, mem );


  return result;
}

MachNode* repl4S_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveRegNode *n0 = new moveRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  repl48Node *n1 = new repl48Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n1->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n1->add_req(_in[i + idx0]);
    }
  }
  else n1->add_req(tmp0);
  tmp0 = n1;
  result = n1->Expand( state, proj_list, mem );

  repl32Node *n2 = new repl32Node();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n2->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n2->add_req(_in[i + idx0]);
    }
  }
  else n2->add_req(tmp0);
  tmp0 = n2;
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* repl8S_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new vecXOper();
  MachOper *op2 = new immI8Oper(
#line 13592 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  0 
#line 7835 "ad_ppc_expand.cpp"
);
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveRegNode *n0 = new moveRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  repl48Node *n1 = new repl48Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n1->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  tmp2 = n1;
  result = n1->Expand( state, proj_list, mem );

  repl32Node *n2 = new repl32Node();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n2->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  tmp2 = n2;
  result = n2->Expand( state, proj_list, mem );

  mtvsrdNode *n3 = new mtvsrdNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(VECX));
  tmp3 = n3;
  n3->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n3->add_req(tmp2);
  result = n3->Expand( state, proj_list, mem );

  xxpermdiNode *n4 = new xxpermdiNode();
  n4->add_req(_in[0]);
  n4->set_opnd_array(0, state->MachOperGenerator(VECX));
  tmp0 = n4;
  n4->set_opnd_array(1, op1->clone()); // tmpV
  if(tmp3 != NULL)
    n4->add_req(tmp3);
  n4->set_opnd_array(2, op1->clone()); // tmpV
  if(tmp3 != NULL)
    n4->add_req(tmp3);
  n4->set_opnd_array(3, op2->clone()); // zero
  if(tmp4 != NULL)
    n4->add_req(tmp4);
  result = n4->Expand( state, proj_list, mem );


  return result;
}

MachNode* repl2I_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveRegNode *n0 = new moveRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  repl32Node *n1 = new repl32Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n1->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n1->add_req(_in[i + idx0]);
    }
  }
  else n1->add_req(tmp0);
  tmp0 = n1;
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* repl4I_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new iRegLdstOper();
  MachOper *op1 = new vecXOper();
  MachOper *op2 = new immI8Oper(
#line 13665 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  0 
#line 7956 "ad_ppc_expand.cpp"
);
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveRegNode *n0 = new moveRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  repl32Node *n1 = new repl32Node();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n1->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  tmp2 = n1;
  result = n1->Expand( state, proj_list, mem );

  mtvsrdNode *n2 = new mtvsrdNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(VECX));
  tmp3 = n2;
  n2->set_opnd_array(1, op0->clone()); // tmpL
  if(tmp2 != NULL)
    n2->add_req(tmp2);
  result = n2->Expand( state, proj_list, mem );

  xxpermdiNode *n3 = new xxpermdiNode();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(VECX));
  tmp0 = n3;
  n3->set_opnd_array(1, op1->clone()); // tmpV
  if(tmp3 != NULL)
    n3->add_req(tmp3);
  n3->set_opnd_array(2, op1->clone()); // tmpV
  if(tmp3 != NULL)
    n3->add_req(tmp3);
  n3->set_opnd_array(3, op2->clone()); // zero
  if(tmp4 != NULL)
    n3->add_req(tmp4);
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* repl2F_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new stackSlotLOper();
  MachOper *op1 = new iRegIdstOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  moveF2I_reg_stackNode *n0 = new moveF2I_reg_stackNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(STACKSLOTI));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  moveF2I_stack_regNode *n1 = new moveF2I_stack_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGIDST));
  tmp3 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpS
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  moveRegNode *n2 = new moveRegNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  tmp0 = n2;
  n2->set_opnd_array(1, op1->clone()); // tmpI
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );

  repl32Node *n3 = new repl32Node();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(IREGLDST));
  n3->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n3->add_req(_in[i + idx0]);
    }
  }
  else n3->add_req(tmp0);
  tmp0 = n3;
  result = n3->Expand( state, proj_list, mem );


  return result;
}

MachNode* repl2F_immF_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* vmul8S_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* repl4F_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new vecXOper();
  MachOper *op1 = new immI8Oper(
#line 14240 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  0 
#line 8107 "ad_ppc_expand.cpp"
);
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  xscvdpspn_regFNode *n0 = new xscvdpspn_regFNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(VECX));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  xxspltwNode *n1 = new xxspltwNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(VECX));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpV
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  n1->set_opnd_array(2, op1->clone()); // zero
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* repl4F_immF_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLDST));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* repl2L_reg_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new vecXOper();
  MachOper *op1 = new immI8Oper(
#line 14330 "/priv/d038402/git/reinrich/jdk3/src/hotspot/cpu/ppc/ppc.ad"
(int)  0 
#line 8167 "ad_ppc_expand.cpp"
);
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = NULL;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  MachNode *result = NULL;

  mtvsrdNode *n0 = new mtvsrdNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(VECX));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  xxpermdiNode *n1 = new xxpermdiNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(VECX));
  tmp0 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmpV
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  n1->set_opnd_array(2, op0->clone()); // tmpV
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  n1->set_opnd_array(3, op1->clone()); // zero
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* CallDynamicJavaDirectSched_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // MachConstantBaseNode added in matcher.

  return this;
}

MachNode* CallDynamicJavaDirectNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // MachConstantBaseNode added in matcher.

  return this;
}

MachNode* CallLeafDirect_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* CallLeafNoFPDirect_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* compareAndSwapP_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapP_shenandoah_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapN_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapN_shenandoah_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapP_acq_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapP_acq_shenandoah_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapN_acq_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapN_acq_shenandoah_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeP_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeN_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangePAcq_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeNAcq_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGNDST));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zLoadPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zLoadP_acqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndSwapPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp_xchg
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp_mask
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndSwapP_acqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp_xchg
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp_mask
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndSwapPWeakNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp_xchg
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp_mask
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndSwapPWeak_acqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGIDST));
  add_req(def);
  // TEMP tmp_xchg
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp_mask
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndExchangePNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndExchangeP_acqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zGetAndSetPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPDST));
  add_req(def);
  // DEF/KILL cr0
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_CR0_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

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
