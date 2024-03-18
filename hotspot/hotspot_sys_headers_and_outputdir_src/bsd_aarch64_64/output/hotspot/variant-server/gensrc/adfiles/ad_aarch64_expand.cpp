#line 1 "ad_aarch64_expand.cpp"
//
// Copyright (c) 2003, 2024, Oracle and/or its affiliates. All rights reserved.
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
const RegMask _ALL_REG32_mask( 0x55555555, 0x5555555, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_R0_REG_mask( 0x40000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_R2_REG_mask( 0x400000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_R3_REG_mask( 0x1000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_R4_REG_mask( 0x4000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_R31_REG_mask( 0x0, 0x4000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _ALL_REG_mask( 0xffffffff, 0xfffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _NON_ALLOCATABLE_REG32_mask( 0x10000, 0x5100000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _NON_ALLOCATABLE_REG_mask( 0x30000, 0xf300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R0_REG_mask( 0xc0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R1_REG_mask( 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R2_REG_mask( 0xc00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R3_REG_mask( 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R4_REG_mask( 0xc000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R5_REG_mask( 0x30000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R10_REG_mask( 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _R11_REG_mask( 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _METHOD_REG_mask( 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _THREAD_REG_mask( 0x0, 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _FP_REG_mask( 0x0, 0xc00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LR_REG_mask( 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _SP_REG_mask( 0x0, 0xc000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _FLOAT_REG_mask( 0x0, 0x0, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x0, 0x0, 0x0, 0x0 );
const RegMask _DOUBLE_REG_mask( 0x0, 0x0, 0x33333333, 0x33333333, 0x33333333, 0x33333333, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORA_REG_mask( 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORD_REG_mask( 0x0, 0x0, 0x33333333, 0x33333333, 0x33333333, 0x33333333, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORX_REG_mask( 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V0_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V1_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V2_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V3_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x3000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V4_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V5_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V6_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V7_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x30000000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V8_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V9_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V10_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V11_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x3000, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V12_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V13_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x300000, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V14_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V15_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x30000000, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V16_REG_mask( 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V17_REG_mask( 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V18_REG_mask( 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V19_REG_mask( 0x0, 0x0, 0x3000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V20_REG_mask( 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V21_REG_mask( 0x0, 0x0, 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V22_REG_mask( 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V23_REG_mask( 0x0, 0x0, 0x30000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V24_REG_mask( 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V25_REG_mask( 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V26_REG_mask( 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V27_REG_mask( 0x0, 0x0, 0x0, 0x3000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V28_REG_mask( 0x0, 0x0, 0x0, 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V29_REG_mask( 0x0, 0x0, 0x0, 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V30_REG_mask( 0x0, 0x0, 0x0, 0x3000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _V31_REG_mask( 0x0, 0x0, 0x0, 0x30000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PR_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7fff, 0x0, 0x0, 0x0 );
const RegMask _GOV_PR_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x0, 0x0, 0x0 );
const RegMask _P0_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0 );
const RegMask _P1_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0 );
const RegMask _INT_FLAGS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10000, 0x0, 0x0, 0x0 );
const RegMask _STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff000000, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _DYNAMIC_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
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

MachNode* verify_vector_alignmentNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

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

MachNode* cmpU3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL flags
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpU3_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL flags
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpUL3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL flags
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpUL3_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL flags
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

MachNode* minI_reg_imm0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_imm0_ltNode *n1 = new cmovI_reg_imm0_ltNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* minI_imm0_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_imm0_ltNode *n1 = new cmovI_reg_imm0_ltNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* minI_reg_imm1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_imm1_leNode *n1 = new cmovI_reg_imm1_leNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* minI_imm1_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_imm1_leNode *n1 = new cmovI_reg_imm1_leNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* minI_reg_immM1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_immM1_ltNode *n1 = new cmovI_reg_immM1_ltNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* minI_immM1_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_immM1_ltNode *n1 = new cmovI_reg_immM1_ltNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* maxI_reg_imm0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_imm0_gtNode *n1 = new cmovI_reg_imm0_gtNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* maxI_imm0_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_imm0_gtNode *n1 = new cmovI_reg_imm0_gtNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* maxI_reg_imm1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_imm1_gtNode *n1 = new cmovI_reg_imm1_gtNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* maxI_imm1_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_imm1_gtNode *n1 = new cmovI_reg_imm1_gtNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* maxI_reg_immM1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_immM1_geNode *n1 = new cmovI_reg_immM1_geNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* maxI_immM1_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

  compI_reg_imm0Node *n0 = new compI_reg_imm0Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_immM1_geNode *n1 = new cmovI_reg_immM1_geNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(IREGINOSP));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(2, op0->clone()); // cr
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
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

MachNode* convF2HF_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* convHF2F_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* round_double_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP ftmp
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* round_float_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP ftmp
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
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

MachNode* minI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

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
  if(tmp3 != nullptr)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* maxI_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = nullptr;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = nullptr;

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
  if(tmp3 != nullptr)
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
  // TEMP tmp3
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

MachNode* cmpFastLockLightweightNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* cmpFastUnlockLightweightNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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
  // TEMP vtmp0
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
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
  // TEMP vtmp0
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
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
  // TEMP vtmp0
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
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

MachNode* stringL_indexof_char_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ztmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECA));
  add_req(def);
  // TEMP ztmp2
  def = new MachTempNode(state->MachOperGenerator(VECA));
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
  def = new MachTempNode(state->MachOperGenerator(VECA));
  add_req(def);
  // TEMP ztmp2
  def = new MachTempNode(state->MachOperGenerator(VECA));
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
  // TEMP vtmp0
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VREGD_V2));
  add_req(def);
  // TEMP vtmp3
  def = new MachTempNode(state->MachOperGenerator(VREGD_V3));
  add_req(def);
  // TEMP vtmp4
  def = new MachTempNode(state->MachOperGenerator(VREGD_V4));
  add_req(def);
  // TEMP vtmp5
  def = new MachTempNode(state->MachOperGenerator(VREGD_V5));
  add_req(def);
  // TEMP vtmp6
  def = new MachTempNode(state->MachOperGenerator(VREGD_V6));
  add_req(def);
  // TEMP vtmp7
  def = new MachTempNode(state->MachOperGenerator(VREGD_V7));
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
  // TEMP vtmp0
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VREGD_V2));
  add_req(def);
  // TEMP vtmp3
  def = new MachTempNode(state->MachOperGenerator(VREGD_V3));
  add_req(def);
  // TEMP vtmp4
  def = new MachTempNode(state->MachOperGenerator(VREGD_V4));
  add_req(def);
  // TEMP vtmp5
  def = new MachTempNode(state->MachOperGenerator(VREGD_V5));
  add_req(def);
  // TEMP vtmp6
  def = new MachTempNode(state->MachOperGenerator(VREGD_V6));
  add_req(def);
  // TEMP vtmp7
  def = new MachTempNode(state->MachOperGenerator(VREGD_V7));
  add_req(def);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 3, (R10_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* count_positivesNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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
  // TEMP vtmp0
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VREGD_V2));
  add_req(def);
  // TEMP vtmp3
  def = new MachTempNode(state->MachOperGenerator(VREGD_V3));
  add_req(def);
  // TEMP vtmp4
  def = new MachTempNode(state->MachOperGenerator(VREGD_V4));
  add_req(def);
  // TEMP vtmp5
  def = new MachTempNode(state->MachOperGenerator(VREGD_V5));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (INT_FLAGS_mask()), Op_RegFlags );
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
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGP_R3));
  add_req(def);
  // TEMP vtmp0
  def = new MachTempNode(state->MachOperGenerator(VREGD_V0));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VREGD_V1));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VREGD_V2));
  add_req(def);
  // TEMP vtmp3
  def = new MachTempNode(state->MachOperGenerator(VREGD_V3));
  add_req(def);
  // TEMP vtmp4
  def = new MachTempNode(state->MachOperGenerator(VREGD_V4));
  add_req(def);
  // TEMP vtmp5
  def = new MachTempNode(state->MachOperGenerator(VREGD_V5));
  add_req(def);
  // TEMP vtmp6
  def = new MachTempNode(state->MachOperGenerator(VREGD_V6));
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
  // DEF/KILL vtmp0
  kill = new MachProjNode( this, 3, (V0_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp1
  kill = new MachProjNode( this, 4, (V1_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp2
  kill = new MachProjNode( this, 5, (V2_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp3
  kill = new MachProjNode( this, 6, (V3_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp4
  kill = new MachProjNode( this, 7, (V4_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp5
  kill = new MachProjNode( this, 8, (V5_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 9, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encode_ascii_arrayNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (R2_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (R1_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL vtmp0
  kill = new MachProjNode( this, 3, (V0_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp1
  kill = new MachProjNode( this, 4, (V1_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp2
  kill = new MachProjNode( this, 5, (V2_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp3
  kill = new MachProjNode( this, 6, (V3_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp4
  kill = new MachProjNode( this, 7, (V4_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL vtmp5
  kill = new MachProjNode( this, 8, (V5_REG_mask()), Op_RegD );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 9, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compressBitsI_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tdst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tsrc
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmask
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* compressBitsI_memconNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tdst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tsrc
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmask
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* compressBitsL_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tdst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP tsrc
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP tmask
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* compressBitsL_memconNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tdst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tsrc
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmask
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* expandBitsI_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tdst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tsrc
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmask
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* expandBitsI_memconNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tdst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tsrc
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmask
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* expandBitsL_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tdst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP tsrc
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP tmask
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* expandBitsL_memconNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tdst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tsrc
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmask
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* vfabd_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst_src1
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// pg
    unsigned num4 = opnd_array(4)->num_edges(); 	// pg
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

MachNode* vfabd_masked_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst_src1
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// pg
    unsigned num4 = opnd_array(4)->num_edges(); 	// pg
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

MachNode* vminL_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vmaxL_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vmuladdS2INode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vasr_neon_varNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vasr_neon_var_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vasr_neon_var_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vasr_neon_var_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vlsr_neon_varNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vlsr_neon_var_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vlsr_neon_var_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vlsr_neon_var_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* reduce_addI_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* reduce_addI_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_addL_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* reduce_addL_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_add2F_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* reduce_add4F_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* reduce_addD_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

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

MachNode* reduce_mulINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* reduce_mulLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);

  return this;
}

MachNode* reduce_mulFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* reduce_mulDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* reduce_andI_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_andI_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_andL_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);

  return this;
}

MachNode* reduce_andL_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_orI_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_orI_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_orL_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);

  return this;
}

MachNode* reduce_orL_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_xorI_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);

  return this;
}

MachNode* reduce_xorI_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_xorL_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);

  return this;
}

MachNode* reduce_xorL_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_xorI_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_xorL_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_maxI_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxI_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_maxL_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_maxL_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_maxFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

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

MachNode* reduce_maxF_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* reduce_maxD_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reduce_minI_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minI_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_minL_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGLNOSP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* reduce_minL_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* reduce_minFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

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

MachNode* reduce_minF_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* reduce_minD_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* reinterpret_resize_gt128bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
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

MachNode* vcvtStoB_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtItoX_narrow_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtItoX_narrow_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vcvtLtoI_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vcvtLtoF_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* vcvtLtoF_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vcvtFtoX_narrow_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtFtoX_narrow_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vcvtDtoI_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vcvtDtoI_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vcvtDtoF_gt64bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vcvtFtoHF_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* insertI_index_lt32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
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

MachNode* insertI_index_ge32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
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

MachNode* insertL_gt128bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
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

MachNode* insertF_le128bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* insertF_index_lt32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* insertF_index_ge32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
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

MachNode* insertD_128bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* insertD_gt128bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* extractUB_iregNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* extractUB_index_ge16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* extractB_index_ge16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* extractS_index_ge8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* extractI_index_ge4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* extractL_index_ge2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* extractFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGF));
  add_req(def);

  return this;
}

MachNode* extractDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREGD));
  add_req(def);

  return this;
}

MachNode* vloadmaskB_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vloadmask_extend_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vloadmaskB_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vloadmask_extend_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vstoremask_narrow_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vloadmask_loadV_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vloadmask_loadVMaskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vloadmask_loadVMasked_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* storeV_vstoremaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* storeV_vstoremask_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
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

MachNode* storeVMasked_vstoremaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* storeVMasked_vstoremask_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
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

MachNode* vmaskcmp_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmaskcmp_immI_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmaskcmpU_immI_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmaskcmp_immL_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmaskcmpU_immL_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vmaskcast_narrow_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);

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

MachNode* vmask_truecount_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vstoremask_truecount_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vmask_firsttrue_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);

  return this;
}

MachNode* vmask_firsttrue_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);

  return this;
}

MachNode* vmask_lasttrue_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);

  return this;
}

MachNode* vmask_tolong_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vmask_fromlongNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vmaskAll_immINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
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

MachNode* vmaskAllI_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vmaskAll_immLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
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

MachNode* vmaskAllL_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* vmask_gen_INode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_gen_LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_gen_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_gen_subNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vround_le128bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vround_le128b_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vround_gt128bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
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

MachNode* vround_gt128b_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
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

MachNode* vtest_anytrue_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vtest_alltrue_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vtest_alltrue_sveNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ptmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);

  return this;
}

MachNode* rearrange_HS_neonNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* gather_loadDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* gather_loadD_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* scatter_storeDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* scatter_storeD_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* mcompressNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vcompressBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP ptmp
  def = new MachTempNode(state->MachOperGenerator(PREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);

  return this;
}

MachNode* vcompressSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);

  return this;
}

MachNode* vexpandNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vsignum_le128bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vsignum_le128b_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);

  return this;
}

MachNode* vsignum_gt128bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);

  return this;
}

MachNode* vsignum_gt128b_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VREG));
  add_req(def);
  // TEMP pgtmp
  def = new MachTempNode(state->MachOperGenerator(PREGGOV));
  add_req(def);

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

MachNode* xLoadPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* xLoadPVolatileNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* xCompareAndSwapPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* xCompareAndSwapP_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* xCompareAndSwapPAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* xCompareAndSwapPAcq_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* xCompareAndExchangePNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* xCompareAndExchangePAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* xGetAndSetPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* xGetAndSetPAcqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* zStorePNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* zStorePVolatileNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* zCompareAndSwapPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(IREGINOSP));
  add_req(def);
  // TEMP oldval_tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // TEMP newval_tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
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
  // TEMP oldval_tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // TEMP newval_tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
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
  // TEMP oldval_tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // TEMP newval_tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
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
  // TEMP oldval_tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // TEMP newval_tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
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
  // TEMP oldval_tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // TEMP newval_tmp
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
  // TEMP oldval_tmp
  def = new MachTempNode(state->MachOperGenerator(IREGPNOSP));
  add_req(def);
  // TEMP newval_tmp
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
// Check adlc -D_ALLBSD_SOURCE=1
#ifndef _ALLBSD_SOURCE
#  error "_ALLBSD_SOURCE must be defined"
#endif // _ALLBSD_SOURCE
// Check adlc -D_GNU_SOURCE=1
#ifndef _GNU_SOURCE
#  error "_GNU_SOURCE must be defined"
#endif // _GNU_SOURCE
// Check adlc -DR18_RESERVED=1
#ifndef R18_RESERVED
#  error "R18_RESERVED must be defined"
#endif // R18_RESERVED
// Check adlc -DAARCH64=1
#ifndef AARCH64
#  error "AARCH64 must be defined"
#endif // AARCH64
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
// Check adlc -DASSERT=1
#ifndef ASSERT
#  error "ASSERT must be defined"
#endif // ASSERT
