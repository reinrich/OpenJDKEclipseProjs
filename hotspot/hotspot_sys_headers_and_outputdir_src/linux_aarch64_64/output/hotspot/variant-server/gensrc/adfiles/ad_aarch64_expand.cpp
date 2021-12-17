#line 1 "ad_aarch64_expand.cpp"
//
// Copyright (c) 2003, 2021, Oracle and/or its affiliates. All rights reserved.
// Copyright (c) 2014, 2021, Red Hat, Inc. All rights reserved.
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
#include "adfiles/ad_aarch64.hpp"
#include "oops/compressedOops.hpp"

// Register masks, one for each register class.
const RegMask _ALL_REG32_mask( 0x55555555, 0x5555555, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_R0_REG_mask( 0x40000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_R2_REG_mask( 0x400000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_R3_REG_mask( 0x1000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_R4_REG_mask( 0x4000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_R31_REG_mask( 0x0, 0x4000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _ALL_REG_mask( 0xffffffff, 0xfffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _NON_ALLOCATABLE_REG32_mask( 0x0, 0x5100000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _NON_ALLOCATABLE_REG_mask( 0x0, 0xf300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R0_REG_mask( 0xc0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R1_REG_mask( 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R2_REG_mask( 0xc00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R3_REG_mask( 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R4_REG_mask( 0xc000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R5_REG_mask( 0x30000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R10_REG_mask( 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R11_REG_mask( 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _METHOD_REG_mask( 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _HEAPBASE_REG_mask( 0x0, 0xc0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _THREAD_REG_mask( 0x0, 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _FP_REG_mask( 0x0, 0xc00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LR_REG_mask( 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _SP_REG_mask( 0x0, 0xc000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _FLOAT_REG_mask( 0x0, 0x0, 0x1010101, 0x1010101, 0x1010101, 0x1010101, 0x1010101, 0x1010101, 0x1010101, 0x1010101, 0x0, 0x0, 0x0, 0x0 );
const RegMask _DOUBLE_REG_mask( 0x0, 0x0, 0x3030303, 0x3030303, 0x3030303, 0x3030303, 0x3030303, 0x3030303, 0x3030303, 0x3030303, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORA_REG_mask( 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORD_REG_mask( 0x0, 0x0, 0x3030303, 0x3030303, 0x3030303, 0x3030303, 0x3030303, 0x3030303, 0x3030303, 0x3030303, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORX_REG_mask( 0x0, 0x0, 0xf0f0f0f, 0xf0f0f0f, 0xf0f0f0f, 0xf0f0f0f, 0xf0f0f0f, 0xf0f0f0f, 0xf0f0f0f, 0xf0f0f0f, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V0_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V1_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V2_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V3_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V4_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V5_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V6_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V7_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V8_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V9_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V10_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V11_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V12_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V13_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V14_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V15_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V16_REG_mask( 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V17_REG_mask( 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V18_REG_mask( 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V19_REG_mask( 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V20_REG_mask( 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V21_REG_mask( 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V22_REG_mask( 0x0, 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V23_REG_mask( 0x0, 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V24_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V25_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V26_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V27_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V28_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V29_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V30_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V31_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PR_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff7f, 0x0, 0x0, 0x0 );
const RegMask _GOV_PR_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x0, 0x0, 0x0 );
const RegMask _P0_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0 );
const RegMask _P1_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0 );
const RegMask _INT_FLAGS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10000, 0x0, 0x0, 0x0 );
const RegMask _STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff000000, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _DYNAMIC_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
MachNode* loadConFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* loadConDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* popCountINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* popCountI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* popCountLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* popCountL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* encodeHeapOopNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapBAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapSAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapIAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapLAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapPAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapNAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangePNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeBAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeSAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeIAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeLAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeNAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangePAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapBAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapSAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapIAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapLAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapNAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapPAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpL3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL flags
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpL3_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL flags
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* absI_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* absL_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* copySignD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* copySignF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* signumD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* signumF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* convI2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convP2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* clearArray_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R11_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL base
  kill = new MachProjNode( this, 2, (R10_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* clearArray_imm_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL base
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R10_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP temp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGL_R11));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* overflowMulI_reg_branchNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* overflowMulL_reg_branchNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compF3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compD3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compF3_reg_immF0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compD3_reg_immD0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpLTMask_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpLTMask_reg_zeroNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  compI_reg_regNode *n0 = new compI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
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

  cmovI_reg_reg_ltNode *n1 = new cmovI_reg_reg_ltNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
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
  n1->set_opnd_array(3, op0->clone()); // cr
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* maxI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  compI_reg_regNode *n0 = new compI_reg_regNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
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

  cmovI_reg_reg_gtNode *n1 = new cmovI_reg_reg_gtNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
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
  n1->set_opnd_array(3, op0->clone()); // cr
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmpFastLockNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);

  return this;
}

MachNode* cmpFastUnlockNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);

  return this;
}

MachNode* safePointNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* partialSubtypeCheckNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL temp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R2_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* partialSubtypeCheckVsZeroNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL temp
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R2_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL result
  kill = new MachProjNode( this, 2, (R5_REG_mask()), Op_RegP );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp1
  kill = new MachProjNode( this, 5, (R10_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL tmp2
  kill = new MachProjNode( this, 6, (R11_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 7, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp1
  kill = new MachProjNode( this, 5, (R10_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL tmp2
  kill = new MachProjNode( this, 6, (R11_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 7, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp1
  kill = new MachProjNode( this, 5, (R10_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL tmp2
  kill = new MachProjNode( this, 6, (R11_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL vtmp1
  kill = new MachProjNode( this, 7, (V0_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp2
  kill = new MachProjNode( this, 8, (V1_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp3
  kill = new MachProjNode( this, 9, (V2_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 10, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp1
  kill = new MachProjNode( this, 5, (R10_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL tmp2
  kill = new MachProjNode( this, 6, (R11_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL vtmp1
  kill = new MachProjNode( this, 7, (V0_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp2
  kill = new MachProjNode( this, 8, (V1_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp3
  kill = new MachProjNode( this, 9, (V2_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 10, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexofUUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp6
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexofLLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp6
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexofULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp6
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_conUUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_conLLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_conULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_charNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL ch
  kill = new MachProjNode( this, 3, (INT_R3_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* stringL_indexof_charNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL ch
  kill = new MachProjNode( this, 3, (INT_R3_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equalsLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 2, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt
  kill = new MachProjNode( this, 3, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equalsUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 2, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt
  kill = new MachProjNode( this, 3, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ary2
  kill = new MachProjNode( this, 2, (R2_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGP_R3));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGP_R4));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGP_R5));
  add_req(def);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 3, (R10_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ary2
  kill = new MachProjNode( this, 2, (R2_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGP_R3));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGP_R4));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(IREGP_R5));
  add_req(def);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 3, (R10_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* has_negativesNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compressNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R2_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_R3_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(VREGD_V2));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(VREGD_V3));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_inflateNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R0_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(VREGD_V2));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(IREGP_R3));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encode_iso_arrayNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R2_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_R3_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL Vtmp1
  kill = new MachProjNode( this, 4, (V0_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL Vtmp2
  kill = new MachProjNode( this, 5, (V1_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL Vtmp3
  kill = new MachProjNode( this, 6, (V2_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL Vtmp4
  kill = new MachProjNode( this, 7, (V3_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 8, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vcvt2Dto2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* reduce_add8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* reduce_add16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* reduce_add4SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* reduce_add8SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* reduce_add2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* reduce_mul8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // TEMP itmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_mul16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP itmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_mul4SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // TEMP itmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_mul8SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP itmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_mul2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);

  return this;
}

MachNode* reduce_max8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_max16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_max4SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_max8SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_max4INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_min8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_min16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_min4SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_min8SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_min4INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_max2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_min2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_max2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_min2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_max2FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* reduce_max4FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* reduce_max2DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_min2FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* reduce_min4FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* reduce_min2DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_and8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_orr8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_eor8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_and16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_orr16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_eor16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_and4SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_orr4SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_eor4SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_and8SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_orr8SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_eor8SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_and2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_orr2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_eor2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_and4INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_orr4INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_eor4INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_and2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);

  return this;
}

MachNode* reduce_orr2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);

  return this;
}

MachNode* reduce_eor2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);

  return this;
}

MachNode* insert2FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* insert4FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* insert2DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vmul2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);

  return this;
}

MachNode* vmax2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vmin2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* rearrange8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* rearrange16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* rearrange4SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // TEMP tmp0
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* rearrange8SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP tmp0
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* rearrange4INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP tmp0
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* anytrue_in_mask8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* anytrue_in_mask16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* alltrue_in_mask8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* alltrue_in_mask16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_add2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);
  // TEMP itmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_add4INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP itmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_mul2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_mul4INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP itmp
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_add2FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* reduce_add4FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* reduce_mul2FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* reduce_mul4FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* reduce_add2DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* reduce_mul2DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vmuladdS2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsra8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsra16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsrl8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsrl16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsra4SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsra8SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsrl4SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsrl8SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsra2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsra4INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsrl2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsrl4INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsra2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsrl2LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vmask_truecount8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vmask_truecount16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vmask_firsttrue_LT8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadV_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP pgtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* storeV_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP pgtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadV_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP pgtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* storeV_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP pgtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmaskAllINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmaskAllLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reinterpretResizeNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_reinterpret_diff_esizeNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmaskcmpNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmaskcmp_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vloadmaskBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vloadmask_extendNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vstoremask_narrowNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vloadmask_loadVNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vloadmask_loadV_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* storeV_vstoremaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* storeV_vstoremask_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_addINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_addLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_addI_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_addL_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_addF_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_addD_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_addI_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_addL_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_addI_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_addL_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_addF_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_addD_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_andINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_andLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_andI_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_andL_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_andI_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_andL_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_andI_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_andL_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_orINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_orLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_orI_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_orL_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_orI_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_orL_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_orI_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_orL_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_eorINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_eorLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_eorI_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_eorL_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_eorI_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_eorL_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_eorI_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_eorL_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxI_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxL_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* reduce_maxF_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_maxD_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxI_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxL_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxI_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxL_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxF_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxD_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minI_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minL_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* reduce_minF_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_minD_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minI_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minL_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minI_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minL_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minF_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minD_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vcvtStoBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtItoBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtItoSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtLtoX_narrowNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtLtoFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtFtoX_narrowNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtDtoX_narrowNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtDtoFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* extractBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP pgtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* extractSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP pgtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* extractINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP pgtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* extractLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP pgtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* extractFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP pgtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* extractDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP pgtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vtest_alltrueNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vtest_anytrueNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vtest_alltrue_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vtest_anytrue_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* insertI_smallNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* insertF_smallNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* insertINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* insertLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* insertDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* insertFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* gatherI_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* gatherL_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* gatherI_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* gatherL_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* scatterI_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* scatterL_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* scatterI_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* scatterL_masked_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* stringL_indexof_char_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ztmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP ztmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* stringU_indexof_char_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ztmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP ztmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLL_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGP_R10));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGL_R11));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
  add_req(def);
  // TEMP pgtmp1
  def = new MachTempNode(state->MachOperGenerator(PREGGOV_P0));
  add_req(def);
  // TEMP pgtmp2
  def = new MachTempNode(state->MachOperGenerator(PREGGOV_P1));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLU_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGP_R10));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGL_R11));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
  add_req(def);
  // TEMP pgtmp1
  def = new MachTempNode(state->MachOperGenerator(PREGGOV_P0));
  add_req(def);
  // TEMP pgtmp2
  def = new MachTempNode(state->MachOperGenerator(PREGGOV_P1));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareUL_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGP_R10));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGL_R11));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
  add_req(def);
  // TEMP pgtmp1
  def = new MachTempNode(state->MachOperGenerator(PREGGOV_P0));
  add_req(def);
  // TEMP pgtmp2
  def = new MachTempNode(state->MachOperGenerator(PREGGOV_P1));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareUU_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_R2_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (R3_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_R4_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGP_R10));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(IREGL_R11));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
  add_req(def);
  // TEMP pgtmp1
  def = new MachTempNode(state->MachOperGenerator(PREGGOV_P0));
  add_req(def);
  // TEMP pgtmp2
  def = new MachTempNode(state->MachOperGenerator(PREGGOV_P1));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_firsttrueNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);

  return this;
}

MachNode* vmask_lasttrueNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);

  return this;
}

MachNode* vmask_truecount_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_firsttrue_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);
  // TEMP ptmp2
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_lasttrue_partialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_tolongNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_genNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapP_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapN_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapPAcq_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapNAcq_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeN_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGNNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeP_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeNAcq_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGNNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangePAcq_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapN_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapP_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapNAcq_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGNNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* weakCompareAndSwapPAcq_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zLoadPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zLoadPVolatileNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndSwapPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndSwapP_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndSwapPAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndSwapPAcq_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndExchangePNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndExchangePAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zGetAndSetPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP prev
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zGetAndSetPAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP prev
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
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
// Check adlc -DAARCH64=1
#ifndef AARCH64
#  error "AARCH64 must be defined"
#endif // AARCH64
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
