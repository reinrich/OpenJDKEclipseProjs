#line 1 "ad_s390_expand.cpp"
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
#include "adfiles/ad_s390.hpp"

// Register masks, one for each register class.
const RegMask _Z_INT_REG_mask( 0x5541155, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_Z_INT_REG_mask( 0x5541155, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _Z_NO_ODD_INT_REG_mask( 0x5441155, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_NO_ARG_INT_REG_mask( 0x1155, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG1_INT_REG_mask( 0x4000000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG2_INT_REG_mask( 0x1000000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG3_INT_REG_mask( 0x400000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG4_INT_REG_mask( 0x100000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG5_INT_REG_mask( 0x40000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG5_PTRN_REG_mask( 0x40000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG1_PTR_REG_mask( 0xc000000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG2_PTR_REG_mask( 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG3_PTR_REG_mask( 0xc00000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG4_PTR_REG_mask( 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG5_PTR_REG_mask( 0xc0000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_THREAD_PTR_REG_mask( 0xc00, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_PTR_REG_mask( 0xffc33ff, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_LOCK_PTR_REG_mask( 0xfc033ff, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_NO_ARG_PTR_REG_mask( 0x33ff, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_MEMORY_PTR_REG_mask( 0xffc3fff, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_R1_REGP_mask( 0xc000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_R9_REGP_mask( 0x300, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG1_LONG_REG_mask( 0xc000000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG2_LONG_REG_mask( 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG3_LONG_REG_mask( 0xc00000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG4_LONG_REG_mask( 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_RARG5_LONG_REG_mask( 0xc0000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_LONG_REG_mask( 0xffc33ff, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_Z_LONG_REG_mask( 0xffc33ff, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _Z_CONDITION_REG_mask( 0x0, 0x0, 0x1, 0x0, 0x0, 0x0 );
const RegMask _Z_RSCRATCH2_BITS64_REG_mask( 0xc000000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_FLT_REG_mask( 0x0, 0x55155555, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_Z_FLT_REG_mask( 0x0, 0x55155555, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _Z_RSCRATCH1_FLT_REG_mask( 0x0, 0x400000, 0x0, 0x0, 0x0, 0x0 );
const RegMask _Z_DBL_REG_mask( 0x0, 0xff3fffff, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_Z_DBL_REG_mask( 0x0, 0xff3fffff, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _Z_RSCRATCH1_DBL_REG_mask( 0x0, 0xc00000, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_STACK_SLOTS_mask( 0x0, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff );
MachNode* loadConI_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConL_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConP0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConF_dynTOCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* loadConD_dynTOCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* negL_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConN0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeKlassNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeN_NNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeN_baseNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeN_NN_baseNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeN_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immLOper(
#line 4883 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
(jlong)(intptr_t)Universe::narrow_oop_base() 
#line 210 "ad_s390_expand.cpp"
);
  MachOper *op1 = new iRegLOper();
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

  loadBaseNode *n0 = new loadBaseNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGL));
  tmp3 = n0;
  n0->set_opnd_array(1, op0->clone()); // baseImm
  if(tmp2 != NULL)
    n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  decodeN_baseNode *n1 = new decodeN_baseNode();
  n1->add_req(_in[0]);
  ((MachTypeNode*)n1)->_bottom_type = bottom_type();
  n1->set_opnd_array(0, state->MachOperGenerator(IREGP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op1->clone()); // base
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* decodeN_NN_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immLOper(
#line 4899 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
(jlong)(intptr_t)Universe::narrow_oop_base() 
#line 259 "ad_s390_expand.cpp"
);
  MachOper *op1 = new iRegLOper();
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

  loadBaseNode *n0 = new loadBaseNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGL));
  tmp3 = n0;
  n0->set_opnd_array(1, op0->clone()); // baseImm
  if(tmp2 != NULL)
    n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  decodeN_NN_baseNode *n1 = new decodeN_NN_baseNode();
  n1->add_req(_in[0]);
  ((MachTypeNode*)n1)->_bottom_type = bottom_type();
  n1->set_opnd_array(0, state->MachOperGenerator(IREGP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op1->clone()); // base
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* encodePNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encodeKlassNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encodeP_NNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encodeP_baseNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGN));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// base
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// dst
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

MachNode* encodeP_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immLOper(
#line 4983 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
((jlong)(intptr_t)Universe::narrow_oop_base()) >> Universe::narrow_oop_shift() 
#line 372 "ad_s390_expand.cpp"
);
  MachOper *op1 = new immL_0Oper(
#line 4984 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
(0) 
#line 377 "ad_s390_expand.cpp"
);
  MachOper *op2 = new flagsRegOper();
  MachOper *op3 = new iRegLOper();
  MachOper *op4 = new iRegLOper();
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

  loadBaseNode *n0 = new loadBaseNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGL));
  tmp5 = n0;
  n0->set_opnd_array(1, op0->clone()); // baseImm
  if(tmp2 != NULL)
    n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  negL_reg_regNode *n1 = new negL_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGL));
  tmp6 = n1;
  n1->set_opnd_array(1, op1->clone()); // zero
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  n1->set_opnd_array(2, op3->clone()); // base
  if(tmp5 != NULL)
    n1->add_req(tmp5);
  result = n1->Expand( state, proj_list, mem );

  encodeP_baseNode *n2 = new encodeP_baseNode();
  n2->add_req(_in[0]);
  ((MachTypeNode*)n2)->_bottom_type = bottom_type();
  n2->set_opnd_array(0, state->MachOperGenerator(IREGN));
  n2->set_opnd_array(3, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n2->add_req(_in[i + idx0]);
    }
  }
  else n2->add_req(tmp0);
  tmp0 = n2;
  n2->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  n2->set_opnd_array(2, op4->clone()); // negBase
  if(tmp6 != NULL)
    n2->add_req(tmp6);
  n2->_num_opnds = 4; // Only unique opnds generated.
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* encodeP_NN_ExNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new immLOper(
#line 5003 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
(jlong)(intptr_t)Universe::narrow_oop_base() 
#line 451 "ad_s390_expand.cpp"
);
  MachOper *op1 = new immLOper(
#line 5004 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
-(jlong)MacroAssembler::get_oop_base_pow2_offset(((uint64_t)(intptr_t)Universe::narrow_oop_base())) 
#line 456 "ad_s390_expand.cpp"
);
  MachOper *op2 = new immL_0Oper(
#line 5005 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/s390/s390.ad"
0 
#line 461 "ad_s390_expand.cpp"
);
  MachOper *op3 = new flagsRegOper();
  MachOper *op4 = new iRegLOper();
  MachOper *op5 = new iRegLOper();
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

  loadBaseNode *n0 = new loadBaseNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(IREGL));
  tmp6 = n0;
  n0->set_opnd_array(1, op0->clone()); // baseImm
  if(tmp2 != NULL)
    n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  negL_reg_regNode *n1 = new negL_reg_regNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGL));
  tmp7 = n1;
  n1->set_opnd_array(1, op2->clone()); // zero
  if(tmp4 != NULL)
    n1->add_req(tmp4);
  n1->set_opnd_array(2, op4->clone()); // base
  if(tmp6 != NULL)
    n1->add_req(tmp6);
  result = n1->Expand( state, proj_list, mem );

  encodeP_NN_baseNode *n2 = new encodeP_NN_baseNode();
  n2->add_req(_in[0]);
  ((MachTypeNode*)n2)->_bottom_type = bottom_type();
  n2->set_opnd_array(0, state->MachOperGenerator(IREGN));
  tmp0 = n2;
  n2->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  n2->set_opnd_array(2, op5->clone()); // negBase
  if(tmp7 != NULL)
    n2->add_req(tmp7);
  n2->set_opnd_array(3, op1->clone()); // pow2_offset
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* storePConditionalNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG5_PTR_REG_mask()), Op_RegP );
  proj_list.push(kill);

  return this;
}

MachNode* storeLConditionalNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG5_LONG_REG_mask()), Op_RegL );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapI_boolNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG5_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapL_boolNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG5_LONG_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapP_boolNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG5_PTR_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapN_boolNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG5_PTRN_REG_mask()), Op_RegN );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_mem_imm8_atomic_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_mem_imm16_atomicNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_mem_imm32_atomicNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_mem_reg_atomicNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_mem_imm8_atomic_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_mem_imm16_atomicNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGL));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_mem_imm32_atomicNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGL));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_mem_reg_atomicNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGL));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xchgI_reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xchgL_reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xchgN_reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xchgP_reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_reg_reg_CISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_reg_reg_RISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_reg_imm16_CISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_reg_imm16_RISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_reg_imm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_Reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_Reg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// mem
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* addL_reg_regINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_reg_regI_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_reg_reg_CISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_reg_reg_RISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_reg_imm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_reg_imm16_CISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_reg_imm16_RISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_Reg_memINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_Reg_memI_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_Reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_Reg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// mem
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* addP_reg_reg_CISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addP_reg_reg_RISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addP_reg_imm16_CISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addP_reg_imm16_RISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addP_reg_imm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addP_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// mem
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* subI_reg_reg_CISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subI_reg_reg_RISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subI_Reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subI_zero_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subL_reg_reg_CISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subL_reg_reg_RISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subL_reg_regI_CISCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subL_Reg_memINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subL_Reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulHiL_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL Rsrc1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG4_LONG_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // TEMP Rdst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // TEMP Rtmp1
  def = new MachTempNode(state->MachOperGenerator(IREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divModI_reg_divmodNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL tmp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG3_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divI_reg_imm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL tmp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG3_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divModL_reg_divmodNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divL_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL tmp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG3_LONG_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divL_reg_imm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL tmp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG3_LONG_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* modI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL tmp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG4_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* modI_reg_imm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL tmp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG4_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* modL_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG4_LONG_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* modL_reg_imm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL tmp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG4_LONG_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sllI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sraI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sraI_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sraL_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sraL_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* srlI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rotlI_reg_immI8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* rotlI_reg_immI8_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* rotlL_reg_immI8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* rotlL_reg_immI8_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* rotrI_reg_immI8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* rotrI_reg_immI8_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* rotrL_reg_immI8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* rotrL_reg_immI8_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* addF_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addF_reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addF_reg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addD_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addD_reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addD_reg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subF_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subF_reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subD_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subD_reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* absF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* absD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* nabsF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* nabsD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_Reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_Reg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_reg_uimm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_reg_uimmI_LH1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_reg_uimmI_LL1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_Reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_Reg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_reg_uimmL_LL1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_reg_uimmL_LH1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_reg_uimmL_HL1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_reg_uimmL_HH1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_Reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_Reg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_reg_uimm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_reg_uimm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_Reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_Reg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_reg_uimm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_reg_uimm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_Reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_Reg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_reg_uimm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_Reg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_Reg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_reg_uimm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convI2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convP2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpLTMask_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpLTMask_reg_zeroNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convF2I_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convD2I_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convF2L_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convD2L_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rShiftI16_lShiftI16_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* rShiftI24_lShiftI24_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* shrL_reg_imm6_L2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rangeCheck_iReg_iRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* z196_minI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* z10_minI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* z196_minI_reg_imm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minI_reg_imm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* z196_minI_reg_imm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minI_reg_imm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* z10_minI_reg_imm8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* z196_maxI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* z10_maxI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* maxI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* z196_maxI_reg_imm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* maxI_reg_imm32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* z196_maxI_reg_imm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* maxI_reg_imm16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* z10_maxI_reg_imm8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* absI_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negabsI_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* testAndBranchLoopEnd_RegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpbU_RegINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegPPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegNNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* testAndBranchLoopEnd_ImmNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegI_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpbU_RegI_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegL_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegP_immPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegN_immP0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegN_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* testAndBranchLoopEnd_RegFarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegI_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpbU_RegI_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegL_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegPP_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegNN_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* testAndBranchLoopEnd_ImmFarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegI_imm_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpbU_RegI_imm_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegL_imm_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegP_immP_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegN_immP0_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpb_RegN_immN_FarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpL3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* safePoint_pollNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* partialSubtypeCheckNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL pcc
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);
  // DEF/KILL scratch1
  kill = new MachProjNode( this, 2, (Z_RARG4_PTR_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL scratch2
  kill = new MachProjNode( this, 3, (Z_RARG5_PTR_REG_mask()), Op_RegP );
  proj_list.push(kill);

  return this;
}

MachNode* partialSubtypeCheck_vs_zeroNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL index
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG1_PTR_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL scratch1
  kill = new MachProjNode( this, 2, (Z_RARG4_PTR_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL scratch2
  kill = new MachProjNode( this, 3, (Z_RARG5_PTR_REG_mask()), Op_RegP );
  proj_list.push(kill);

  return this;
}

MachNode* cmpFastLockNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGP));
  add_req(def);

  return this;
}

MachNode* cmpFastUnlockNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGP));
  add_req(def);

  return this;
}

MachNode* inlineCallClearArrayConstNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* inlineCallClearArrayConstBigNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP srcA
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // TEMP srcL
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* inlineCallClearArrayNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP srcA
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // TEMP srcL
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equalsLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP oddReg
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equalsUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP oddReg
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equals_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equalsC_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP oddReg
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP oddReg
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG2_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 2, (Z_RARG5_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG2_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 2, (Z_RARG5_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG2_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 2, (Z_RARG5_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG2_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 2, (Z_RARG5_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOfChar_UNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm1_UNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm1_LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm1_ULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm_UNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG2_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm_LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG2_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_imm_ULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG2_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_UNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG2_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL needlecnt
  kill = new MachProjNode( this, 2, (Z_RARG5_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG2_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL needlecnt
  kill = new MachProjNode( this, 2, (Z_RARG5_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* indexOf_ULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL haycnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG2_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL needlecnt
  kill = new MachProjNode( this, 2, (Z_RARG5_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGL));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGL));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compressNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_inflateNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_inflate_constNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* has_negativesNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG5_PTR_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP oddReg
  def = new MachTempNode(state->MachOperGenerator(RODDREGI));
  add_req(def);
  // TEMP evenReg
  def = new MachTempNode(state->MachOperGenerator(REVENREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encode_iso_arrayNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP result
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* Repl8B_reg_risbgNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* Repl4S_reg_risbgNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* Repl2I_reg_risbgNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* Repl2F_reg_indirectNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new stackSlotFOper();
  MachOper *op1 = new iRegLOper();
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

  expand_storeFNode *n0 = new expand_storeFNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(STACKSLOTF));
  tmp2 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  expand_LoadLogical_I2LNode *n1 = new expand_LoadLogical_I2LNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGL));
  tmp3 = n1;
  n1->set_opnd_array(1, op0->clone()); // tmp
  if(tmp2 != NULL)
    n1->add_req(tmp2);
  result = n1->Expand( state, proj_list, mem );

  expand_Repl2I_regNode *n2 = new expand_Repl2I_regNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(IREGL));
  tmp0 = n2;
  n2->set_opnd_array(1, op1->clone()); // tmp2
  if(tmp3 != NULL)
    n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* Repl2F_reg_directNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL tmp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG4_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL tmp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG4_INT_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REVENREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RODDREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REVENREGI));
  add_req(def);
  // DEF/KILL tmp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_RARG4_LONG_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* popCountINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* popCountLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (Z_CONDITION_REG_mask()), Op_RegFlags );
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
// Check adlc -DS390=1
#ifndef S390
#  error "S390 must be defined"
#endif // S390
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
