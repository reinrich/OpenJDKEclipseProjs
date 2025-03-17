#line 1 "ad_x86_expand.cpp"
//
// Copyright (c) 2003, 2025, Oracle and/or its affiliates. All rights reserved.
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

#include "adfiles/ad_x86.hpp"
#include "oops/compressedOops.hpp"

// Register masks, one for each register class.
const RegMask _NO_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _ALL_REG_mask( 0xffffffff, 0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _ALL_INT_REG_mask( 0x45555555, 0x15555555, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RAX_REG_mask( 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RBX_REG_mask( 0x3000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RSI_REG_mask( 0xc0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RBP_REG_mask( 0xc00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RDI_REG_mask( 0xc000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RSP_REG_mask( 0x0, 0xc0000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_R15_REG_mask( 0x30000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_RAX_REG_mask( 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_RCX_REG_mask( 0xc00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_RDX_REG_mask( 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_R11_REG_mask( 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_RAX_REG_mask( 0x100000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_RBX_REG_mask( 0x1000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_RCX_REG_mask( 0x400, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_RDX_REG_mask( 0x10000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_RDI_REG_mask( 0x4000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTMASK_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3fff, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTMASK_REG_K1_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTMASK_REG_K2_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc00, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTMASK_REG_K3_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x300, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTMASK_REG_K4_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTMASK_REG_K5_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTMASK_REG_K6_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTMASK_REG_K7_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_FLAGS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4000, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _FLOAT_REG_LEGACY_mask( 0x0, 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_FLOAT_REG_LEGACY_mask( 0x0, 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffff0000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _FLOAT_REG_EVEX_mask( 0x0, 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_FLOAT_REG_EVEX_mask( 0x0, 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0xffff0000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _DOUBLE_REG_LEGACY_mask( 0x0, 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_DOUBLE_REG_LEGACY_mask( 0x0, 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffff0000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _DOUBLE_REG_EVEX_mask( 0x0, 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_DOUBLE_REG_EVEX_mask( 0x0, 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0xffff0000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _VECTORS_REG_LEGACY_mask( 0x0, 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORS_REG_EVEX_mask( 0x0, 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORD_REG_LEGACY_mask( 0x0, 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORD_REG_EVEX_mask( 0x0, 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORX_REG_LEGACY_mask( 0x0, 0x0, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORX_REG_EVEX_mask( 0x0, 0x0, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORY_REG_LEGACY_mask( 0x0, 0x0, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORY_REG_EVEX_mask( 0x0, 0x0, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORZ_REG_EVEX_mask( 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORZ_REG_LEGACY_mask( 0x0, 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _XMM0_REG_mask( 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffff0000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _DYNAMIC_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
MachNode* loadUB2L_immINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadS2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// twentyfour
    unsigned num3 = opnd_array(3)->num_edges(); 	// twentyfour
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

MachNode* loadUS2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// twentyfour
    unsigned num3 = opnd_array(3)->num_edges(); 	// twentyfour
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

MachNode* loadUS2L_immINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadI2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// twentyfour
    unsigned num3 = opnd_array(3)->num_edges(); 	// twentyfour
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

MachNode* loadI2SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// sixteen
    unsigned num3 = opnd_array(3)->num_edges(); 	// sixteen
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

MachNode* loadI2L_immU31Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadNKlassCompactHeadersNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* maxF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);

  return this;
}

MachNode* maxF_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* maxD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);

  return this;
}

MachNode* maxD_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);

  return this;
}

MachNode* minF_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);

  return this;
}

MachNode* minD_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConI0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConL0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConP0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConP31Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* loadConHNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* loadConN0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* bytes_reverse_unsigned_shortNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* bytes_reverse_shortNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosI_bsrNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosL_bsrNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosI_bsfNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosL_bsfNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* bytes_reversebit_intNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* bytes_reversebit_int_gfniNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VLREGF));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VLREGF));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* bytes_reversebit_longNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP rtmp1
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* bytes_reversebit_long_gfniNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VLREGD));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VLREGD));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* popCountINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* popCountI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* popCountLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* popCountL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* membar_volatileNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* encodeHeapOop_not_nullNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeHeapOopNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeHeapOop_not_nullNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encodeKlass_not_nullNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGN));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeKlass_not_nullNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* jumpXtnd_offsetNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dest
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* jumpXtnd_addrNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dest
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* jumpXtndNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dest
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* cmovI_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
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
  MachNode *result = nullptr;

  cmovI_regUNode *n0 = new cmovI_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovI_memUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  if (mem == (Node*)1) {
    idx0--; // Adjust base because memory edge hasn't been inserted yet
  }
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = nullptr;

  cmovI_memUNode *n0 = new cmovI_memUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  if (mem != (Node*)1) {
    n0->add_req(_in[1]);	// Add memory edge
  }
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovN_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
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
  MachNode *result = nullptr;

  cmovN_regUNode *n0 = new cmovN_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGN));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovP_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
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
  MachNode *result = nullptr;

  cmovP_regUNode *n0 = new cmovP_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGP));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovL_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
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
  MachNode *result = nullptr;

  cmovL_regUNode *n0 = new cmovL_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovL_memUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  if (mem == (Node*)1) {
    idx0--; // Adjust base because memory edge hasn't been inserted yet
  }
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = nullptr;

  cmovL_memUNode *n0 = new cmovL_memUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  if (mem != (Node*)1) {
    n0->add_req(_in[1]);	// Add memory edge
  }
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovF_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
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
  MachNode *result = nullptr;

  cmovF_regUNode *n0 = new cmovF_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(REGF));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovD_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
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
  MachNode *result = nullptr;

  cmovD_regUNode *n0 = new cmovD_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(REGD));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* addI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* addI_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* addI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* incI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* incI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* decI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* addL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* addL_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* addL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* incL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* incL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* decL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* addP_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addP_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapP_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapL_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapI_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapB_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapS_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegN );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapN_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegN );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangePNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddB_reg_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddB_imm_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddS_reg_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddS_imm_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddI_reg_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddI_imm_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddL_reg_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddL_imm_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* absI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* absL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subI_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* subL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subL_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* subP_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negI_rReg_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* negL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negL_rReg_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* mulI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulI_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulAddS2I_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
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
  MachNode *result = nullptr;

  mulI_rRegNode *n0 = new mulI_rRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src1
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  mulI_rRegNode *n1 = new mulI_rRegNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n1->set_opnd_array(1, opnd_array(3)->clone()); // src2
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n1->add_req(_in[i + idx3]);
    }
  }
  else n1->add_req(tmp3);
  tmp3 = n1;
  n1->set_opnd_array(2, opnd_array(4)->clone()); // src3
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n1->add_req(_in[i + idx4]);
    }
  }
  else n1->add_req(tmp4);
  result = n1->Expand( state, proj_list, mem );

  addI_rRegNode *n2 = new addI_rRegNode();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n2->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  tmp1 = n2;
  n2->set_opnd_array(2, opnd_array(3)->clone()); // src2
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n2->add_req(_in[i + idx3]);
    }
  }
  else n2->add_req(tmp3);
  result = n2->Expand( state, proj_list, mem );


  return result;
}

MachNode* mulL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulL_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulHiL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* umulHiL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rdx
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rdx
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RDX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* udivI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rdx
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* udivL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rdx
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RDX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divModI_rReg_divmodNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divModL_rReg_divmodNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* udivModI_rReg_divmodNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(NO_RAX_RDX_REGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* udivModL_rReg_divmodNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(NO_RAX_RDX_REGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* modI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* modL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* umodI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* umodL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salI_rReg_immI2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* salI_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salI_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* sarI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* sarI_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarI_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* shrI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* shrI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* shrI_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* shrI_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* salL_rReg_immI2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* salL_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salL_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* sarL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* sarL_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarL_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* shrL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* shrL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* shrL_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* shrL_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
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

MachNode* i2bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// twentyfour
    unsigned num3 = opnd_array(3)->num_edges(); 	// twentyfour
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

MachNode* i2sNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// sixteen
    unsigned num3 = opnd_array(3)->num_edges(); 	// sixteen
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

MachNode* rolI_immI8_legacyNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rolI_rReg_VarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rorI_immI8_legacyNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rorI_rReg_VarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rolL_immI8_legacyNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rolL_rReg_VarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rorL_immI8_legacyNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rorL_rReg_VarNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convI2LAndI_reg_immIbitmaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andB_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* andB_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* andI_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* andI_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* andI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* andnI_rReg_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnI_rReg_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnI_rReg_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnI_rReg_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* blsiI_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// imm_zero
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsiI_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// imm_zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsiI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// imm_zero
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsiI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// imm_zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsmskI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsmskI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
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

MachNode* blsmskI_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsmskI_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
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

MachNode* blsrI_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsrI_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
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

MachNode* blsrI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsrI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
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

MachNode* orI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orB_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* orB_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* orI_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* orI_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* orI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* xorI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorB_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* xorB_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* xorI_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* xorI_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* xorI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* andL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* andL_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* andL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* btrL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// con
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // con
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

MachNode* andnL_rReg_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnL_rReg_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnL_rReg_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnL_rReg_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* blsiL_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// imm_zero
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsiL_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// imm_zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsiL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// imm_zero
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsiL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// imm_zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsmskL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsmskL_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsrL_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsrL_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
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

MachNode* blsrL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
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

MachNode* blsrL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
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

MachNode* orL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_rReg_castP2XNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_rReg_castP2X_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* orL_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
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

MachNode* orL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* btsL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// con
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // con
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

MachNode* xorL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* xorL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
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

MachNode* cmpLTMaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpLTMask0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cadd_cmpLTMaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// p
    unsigned num2 = opnd_array(2)->num_edges(); 	// q
    unsigned num3 = opnd_array(3)->num_edges(); 	// y
    unsigned num4 = opnd_array(4)->num_edges(); 	// p
    unsigned num5 = opnd_array(5)->num_edges(); 	// q
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    for (int i = idx6 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 6 operands.");
  }

  return this;
}

MachNode* cadd_cmpLTMask_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// p
    unsigned num2 = opnd_array(2)->num_edges(); 	// q
    unsigned num3 = opnd_array(3)->num_edges(); 	// p
    unsigned num4 = opnd_array(4)->num_edges(); 	// q
    unsigned num5 = opnd_array(5)->num_edges(); 	// y
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(5)->clone()); // y
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx3, _in[i + idx5]);
    }
    num3 = num5;
    idx4 = idx3 + num3;
    for (int i = idx6 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 6 operands.");
  }

  return this;
}

MachNode* cadd_cmpLTMask_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// y
    unsigned num2 = opnd_array(2)->num_edges(); 	// p
    unsigned num3 = opnd_array(3)->num_edges(); 	// q
    unsigned num4 = opnd_array(4)->num_edges(); 	// p
    unsigned num5 = opnd_array(5)->num_edges(); 	// q
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    for (int i = idx6 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 6 operands.");
  }

  return this;
}

MachNode* cadd_cmpLTMask_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// p
    unsigned num2 = opnd_array(2)->num_edges(); 	// q
    unsigned num3 = opnd_array(3)->num_edges(); 	// y
    unsigned num4 = opnd_array(4)->num_edges(); 	// p
    unsigned num5 = opnd_array(5)->num_edges(); 	// q
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    for (int i = idx6 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 6 operands.");
  }

  return this;
}

MachNode* and_cmpLTMaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* and_cmpLTMask_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpF_cc_immCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* cmpD_cc_immCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* cmpF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpF_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* cmpD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpD_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* convF2I_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convF2L_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convD2I_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convD2L_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* round_double_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP rcx
  def = new MachTempNode(state->MachOperGenerator(RCX_REGL));
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
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP rcx
  def = new MachTempNode(state->MachOperGenerator(RCX_REGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rep_stosNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RCX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL base
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL zero
  kill = new MachProjNode( this, 3, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rep_stos_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RCX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL base
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL zero
  kill = new MachProjNode( this, 3, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rep_stos_largeNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RCX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL base
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL zero
  kill = new MachProjNode( this, 3, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rep_stos_large_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RCX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL base
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL zero
  kill = new MachProjNode( this, 3, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rep_stos_imNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP zero
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareL_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareU_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLU_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareUL_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_conLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp_vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_conUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp_vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_conULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp_vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexofLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp_vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexofUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp_vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexofULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp_vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_charNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL ch
  kill = new MachProjNode( this, 3, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp_vec1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec3
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RCX_REGI));
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
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL ch
  kill = new MachProjNode( this, 3, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp_vec1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec3
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RCX_REGI));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equalsNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 2, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt
  kill = new MachProjNode( this, 3, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 4, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equals_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 2, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt
  kill = new MachProjNode( this, 3, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 4, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ary2
  kill = new MachProjNode( this, 2, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 3, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp4
  kill = new MachProjNode( this, 4, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsB_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ary2
  kill = new MachProjNode( this, 2, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 3, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp4
  kill = new MachProjNode( this, 4, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ary2
  kill = new MachProjNode( this, 2, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 3, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp4
  kill = new MachProjNode( this, 4, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsC_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ary2
  kill = new MachProjNode( this, 2, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 3, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp4
  kill = new MachProjNode( this, 4, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* arrays_hashcodeNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp_vec1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec3
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec4
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec5
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec6
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec7
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec8
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec9
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec10
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec11
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec12
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp_vec13
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 3, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* count_positivesNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 3, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* count_positives_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP ktmp2
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 3, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compressNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL tmp5
  kill = new MachProjNode( this, 4, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compress_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP ktmp2
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL tmp5
  kill = new MachProjNode( this, 4, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_inflateNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RCX_REGI));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_inflate_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RCX_REGI));
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
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL tmp5
  kill = new MachProjNode( this, 4, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encode_ascii_arrayNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // DEF/KILL tmp5
  kill = new MachProjNode( this, 4, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* overflowAddI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);

  return this;
}

MachNode* overflowAddI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);

  return this;
}

MachNode* overflowAddL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);

  return this;
}

MachNode* overflowAddL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);

  return this;
}

MachNode* overflowNegI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op2
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);

  return this;
}

MachNode* overflowNegL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op2
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);

  return this;
}

MachNode* overflowMulI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);

  return this;
}

MachNode* overflowMulI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* overflowMulL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);

  return this;
}

MachNode* overflowMulL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);

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

MachNode* cmpL3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

MachNode* minI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

  compI_rRegNode *n0 = new compI_rRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_gNode *n1 = new cmovI_reg_gNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n1->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  tmp1 = n1;
  n1->set_opnd_array(2, opnd_array(2)->clone()); // src
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

MachNode* maxI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
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

  compI_rRegNode *n0 = new compI_rRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_lNode *n1 = new cmovI_reg_lNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n1->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  tmp1 = n1;
  n1->set_opnd_array(2, opnd_array(2)->clone()); // src
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

MachNode* partialSubtypeCheckNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rcx
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* partialSubtypeCheckVarSuperNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP temp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RDX_REGL));
  add_req(def);
  // TEMP temp2
  def = new MachTempNode(state->MachOperGenerator(RCX_REGL));
  add_req(def);
  // TEMP temp3
  def = new MachTempNode(state->MachOperGenerator(RBX_REGP));
  add_req(def);
  // TEMP temp4
  def = new MachTempNode(state->MachOperGenerator(R11_REGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* partialSubtypeCheckConstSuperNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP temp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RDX_REGL));
  add_req(def);
  // TEMP temp2
  def = new MachTempNode(state->MachOperGenerator(RCX_REGL));
  add_req(def);
  // TEMP temp3
  def = new MachTempNode(state->MachOperGenerator(RBX_REGP));
  add_req(def);
  // TEMP temp4
  def = new MachTempNode(state->MachOperGenerator(R11_REGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpFastLockNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL box
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RBX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RAX_REGI));
  add_req(def);
  // TEMP scr
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* cmpFastUnlockNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL box
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* cmpFastLockLightweightNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL box
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RBX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP rax_reg
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RAX_REGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* cmpFastUnlockLightweightNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax_reg
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* safePoint_poll_tlsNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mask_all_evexI_GT32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);

  return this;
}

MachNode* addF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* addF_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* addD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* addD_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* subF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* subF_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* subD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* subD_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* mulF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* mulF_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* mulD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* mulD_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* divF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* divF_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* divD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* divD_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* convF2HF_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VLREGF));
  add_req(def);

  return this;
}

MachNode* convF2HF_mem_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ktmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* reinterpret_mask_W2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reinterpret_mask_D2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reinterpret_mask_Q2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reinterpret_expandNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* roundD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* gatherNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP mask
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* evgatherNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* evgather_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* vgather_subwordLE8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* vgather_subwordGT8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP idx_base_temp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP length
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vgather_subwordLE8B_offNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vgather_subwordGT8B_offNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP idx_base_temp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP length
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vgather_masked_subwordLE8B_avx3Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP mask_idx
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vgather_masked_subwordGT8B_avx3Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP idx_base_temp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP mask_idx
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP length
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vgather_masked_subwordLE8B_off_avx3Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP mask_idx
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vgather_masked_subwordGT8B_off_avx3Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP idx_base_temp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP mask_idx
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP length
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vgather_masked_subwordLE8B_avx2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP mask_idx
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vgather_masked_subwordGT8B_avx2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP idx_base_temp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP mask_idx
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP length
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vgather_masked_subwordLE8B_off_avx2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP mask_idx
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vgather_masked_subwordGT8B_off_avx2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP idx_base_temp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP mask_idx
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP length
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* scatterNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* scatter_maskedNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ktmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* ReplHF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP rtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* ReplHF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP rtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* ReplI_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* ReplL_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* ReplF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* ReplD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* insert32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* insert64Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* insert4LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* insert8LNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* vinsertFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* insert2DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);

  return this;
}

MachNode* insert4DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* insert8DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionI_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionI_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionI_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionI_3Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionI_4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionI_5Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionL_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionL_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionL_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionL_3Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionL_4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionL_5Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionL_avx512dqNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionL_avx512dq_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionL_avx512dq_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionL_avx512dq_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionL_avx512dq_3Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionL_avx512dq_4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionL_avx512dq_5Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionF128Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp
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

MachNode* reductionF128_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp
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

MachNode* reduction8FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// vtmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // vtmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* reduction8F_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// vtmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // vtmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* reduction16FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// vtmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // vtmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* reduction16F_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// vtmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // vtmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* unordered_reduction2FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* unordered_reduction2F_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* unordered_reduction4FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* unordered_reduction4F_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* unordered_reduction8FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* unordered_reduction8F_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* unordered_reduction16FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* unordered_reduction16F_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reduction2DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp
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

MachNode* reduction2D_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp
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

MachNode* reduction4DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// vtmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // vtmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* reduction4D_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// vtmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // vtmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* reduction8DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// vtmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // vtmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* reduction8D_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// vtmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// vtmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // vtmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // vtmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* unordered_reduction2DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);

  return this;
}

MachNode* unordered_reduction2D_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);

  return this;
}

MachNode* unordered_reduction4DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* unordered_reduction4D_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* unordered_reduction8DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* unordered_reduction8D_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionB_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionB_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionB_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionB_3Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionB_4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionB_avx512bwNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionB_avx512bw_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionB_avx512bw_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionB_avx512bw_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionB_avx512bw_3Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionB_avx512bw_4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* reductionSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionS_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionS_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionS_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionS_3Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionS_4Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* reductionS_5Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* mul_reductionBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* mul_reduction64BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* minmax_reduction2FNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minmax_reduction2F_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minmax_reductionFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_0
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minmax_reductionF_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_0
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minmax_reduction2F_avNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 8) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// atmp
    unsigned num6 = opnd_array(6)->num_edges(); 	// btmp
    unsigned num7 = opnd_array(7)->num_edges(); 	// xmm_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    unsigned idx7 = idx6 + num6;
    unsigned idx8 = idx7 + num7;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // atmp
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    set_opnd_array(5, opnd_array(6)->clone()); // btmp
    for (unsigned i = 0; i < num6; i++) {
      set_req(i + idx5, _in[i + idx6]);
    }
    num5 = num6;
    idx6 = idx5 + num5;
    set_opnd_array(6, opnd_array(7)->clone()); // xmm_1
    for (unsigned i = 0; i < num7; i++) {
      set_req(i + idx6, _in[i + idx7]);
    }
    num6 = num7;
    idx7 = idx6 + num6;
    for (int i = idx8 - 1; i >= (int)idx7; i--) {
      del_req(i);
    }
    _num_opnds = 7;
  } else {
    assert(_num_opnds == 7, "There should be either 7 or 8 operands.");
  }

  return this;
}

MachNode* minmax_reduction2F_av_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 8) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// atmp
    unsigned num6 = opnd_array(6)->num_edges(); 	// btmp
    unsigned num7 = opnd_array(7)->num_edges(); 	// xmm_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    unsigned idx7 = idx6 + num6;
    unsigned idx8 = idx7 + num7;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // atmp
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    set_opnd_array(5, opnd_array(6)->clone()); // btmp
    for (unsigned i = 0; i < num6; i++) {
      set_req(i + idx5, _in[i + idx6]);
    }
    num5 = num6;
    idx6 = idx5 + num5;
    set_opnd_array(6, opnd_array(7)->clone()); // xmm_1
    for (unsigned i = 0; i < num7; i++) {
      set_req(i + idx6, _in[i + idx7]);
    }
    num6 = num7;
    idx7 = idx6 + num6;
    for (int i = idx8 - 1; i >= (int)idx7; i--) {
      del_req(i);
    }
    _num_opnds = 7;
  } else {
    assert(_num_opnds == 7, "There should be either 7 or 8 operands.");
  }

  return this;
}

MachNode* minmax_reductionF_avNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_0
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 9) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// atmp
    unsigned num6 = opnd_array(6)->num_edges(); 	// btmp
    unsigned num7 = opnd_array(7)->num_edges(); 	// xmm_0
    unsigned num8 = opnd_array(8)->num_edges(); 	// xmm_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    unsigned idx7 = idx6 + num6;
    unsigned idx8 = idx7 + num7;
    unsigned idx9 = idx8 + num8;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // atmp
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    set_opnd_array(5, opnd_array(6)->clone()); // btmp
    for (unsigned i = 0; i < num6; i++) {
      set_req(i + idx5, _in[i + idx6]);
    }
    num5 = num6;
    idx6 = idx5 + num5;
    set_opnd_array(6, opnd_array(7)->clone()); // xmm_0
    for (unsigned i = 0; i < num7; i++) {
      set_req(i + idx6, _in[i + idx7]);
    }
    num6 = num7;
    idx7 = idx6 + num6;
    set_opnd_array(7, opnd_array(8)->clone()); // xmm_1
    for (unsigned i = 0; i < num8; i++) {
      set_req(i + idx7, _in[i + idx8]);
    }
    num7 = num8;
    idx8 = idx7 + num7;
    for (int i = idx9 - 1; i >= (int)idx8; i--) {
      del_req(i);
    }
    _num_opnds = 8;
  } else {
    assert(_num_opnds == 8, "There should be either 8 or 9 operands.");
  }

  return this;
}

MachNode* minmax_reductionF_av_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_0
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xmm_1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 9) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// atmp
    unsigned num6 = opnd_array(6)->num_edges(); 	// btmp
    unsigned num7 = opnd_array(7)->num_edges(); 	// xmm_0
    unsigned num8 = opnd_array(8)->num_edges(); 	// xmm_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    unsigned idx7 = idx6 + num6;
    unsigned idx8 = idx7 + num7;
    unsigned idx9 = idx8 + num8;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // atmp
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    set_opnd_array(5, opnd_array(6)->clone()); // btmp
    for (unsigned i = 0; i < num6; i++) {
      set_req(i + idx5, _in[i + idx6]);
    }
    num5 = num6;
    idx6 = idx5 + num5;
    set_opnd_array(6, opnd_array(7)->clone()); // xmm_0
    for (unsigned i = 0; i < num7; i++) {
      set_req(i + idx6, _in[i + idx7]);
    }
    num6 = num7;
    idx7 = idx6 + num6;
    set_opnd_array(7, opnd_array(8)->clone()); // xmm_1
    for (unsigned i = 0; i < num8; i++) {
      set_req(i + idx7, _in[i + idx8]);
    }
    num7 = num8;
    idx8 = idx7 + num7;
    for (int i = idx9 - 1; i >= (int)idx8; i--) {
      del_req(i);
    }
    _num_opnds = 8;
  } else {
    assert(_num_opnds == 8, "There should be either 8 or 9 operands.");
  }

  return this;
}

MachNode* minmax_reduction2DNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minmax_reduction2D_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minmax_reductionDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minmax_reductionD_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minmax_reduction2D_avNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 8) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned num6 = opnd_array(6)->num_edges(); 	// tmp3
    unsigned num7 = opnd_array(7)->num_edges(); 	// tmp4
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    unsigned idx7 = idx6 + num6;
    unsigned idx8 = idx7 + num7;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    set_opnd_array(5, opnd_array(6)->clone()); // tmp3
    for (unsigned i = 0; i < num6; i++) {
      set_req(i + idx5, _in[i + idx6]);
    }
    num5 = num6;
    idx6 = idx5 + num5;
    set_opnd_array(6, opnd_array(7)->clone()); // tmp4
    for (unsigned i = 0; i < num7; i++) {
      set_req(i + idx6, _in[i + idx7]);
    }
    num6 = num7;
    idx7 = idx6 + num6;
    for (int i = idx8 - 1; i >= (int)idx7; i--) {
      del_req(i);
    }
    _num_opnds = 7;
  } else {
    assert(_num_opnds == 7, "There should be either 7 or 8 operands.");
  }

  return this;
}

MachNode* minmax_reduction2D_av_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 8) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned num6 = opnd_array(6)->num_edges(); 	// tmp3
    unsigned num7 = opnd_array(7)->num_edges(); 	// tmp4
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    unsigned idx7 = idx6 + num6;
    unsigned idx8 = idx7 + num7;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    set_opnd_array(5, opnd_array(6)->clone()); // tmp3
    for (unsigned i = 0; i < num6; i++) {
      set_req(i + idx5, _in[i + idx6]);
    }
    num5 = num6;
    idx6 = idx5 + num5;
    set_opnd_array(6, opnd_array(7)->clone()); // tmp4
    for (unsigned i = 0; i < num7; i++) {
      set_req(i + idx6, _in[i + idx7]);
    }
    num6 = num7;
    idx7 = idx6 + num6;
    for (int i = idx8 - 1; i >= (int)idx7; i--) {
      del_req(i);
    }
    _num_opnds = 7;
  } else {
    assert(_num_opnds == 7, "There should be either 7 or 8 operands.");
  }

  return this;
}

MachNode* minmax_reductionD_avNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 9) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned num6 = opnd_array(6)->num_edges(); 	// tmp3
    unsigned num7 = opnd_array(7)->num_edges(); 	// tmp4
    unsigned num8 = opnd_array(8)->num_edges(); 	// tmp5
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    unsigned idx7 = idx6 + num6;
    unsigned idx8 = idx7 + num7;
    unsigned idx9 = idx8 + num8;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    set_opnd_array(5, opnd_array(6)->clone()); // tmp3
    for (unsigned i = 0; i < num6; i++) {
      set_req(i + idx5, _in[i + idx6]);
    }
    num5 = num6;
    idx6 = idx5 + num5;
    set_opnd_array(6, opnd_array(7)->clone()); // tmp4
    for (unsigned i = 0; i < num7; i++) {
      set_req(i + idx6, _in[i + idx7]);
    }
    num6 = num7;
    idx7 = idx6 + num6;
    set_opnd_array(7, opnd_array(8)->clone()); // tmp5
    for (unsigned i = 0; i < num8; i++) {
      set_req(i + idx7, _in[i + idx8]);
    }
    num7 = num8;
    idx8 = idx7 + num7;
    for (int i = idx9 - 1; i >= (int)idx8; i--) {
      del_req(i);
    }
    _num_opnds = 8;
  } else {
    assert(_num_opnds == 8, "There should be either 8 or 9 operands.");
  }

  return this;
}

MachNode* minmax_reductionD_av_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGD));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP tmp5
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 9) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp1
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned num6 = opnd_array(6)->num_edges(); 	// tmp3
    unsigned num7 = opnd_array(7)->num_edges(); 	// tmp4
    unsigned num8 = opnd_array(8)->num_edges(); 	// tmp5
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    unsigned idx7 = idx6 + num6;
    unsigned idx8 = idx7 + num7;
    unsigned idx9 = idx8 + num8;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp1
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    set_opnd_array(5, opnd_array(6)->clone()); // tmp3
    for (unsigned i = 0; i < num6; i++) {
      set_req(i + idx5, _in[i + idx6]);
    }
    num5 = num6;
    idx6 = idx5 + num5;
    set_opnd_array(6, opnd_array(7)->clone()); // tmp4
    for (unsigned i = 0; i < num7; i++) {
      set_req(i + idx6, _in[i + idx7]);
    }
    num6 = num7;
    idx7 = idx6 + num6;
    set_opnd_array(7, opnd_array(8)->clone()); // tmp5
    for (unsigned i = 0; i < num8; i++) {
      set_req(i + idx7, _in[i + idx8]);
    }
    num7 = num8;
    idx8 = idx7 + num7;
    for (int i = idx9 - 1; i >= (int)idx8; i--) {
      del_req(i);
    }
    _num_opnds = 8;
  } else {
    assert(_num_opnds == 8, "There should be either 8 or 9 operands.");
  }

  return this;
}

MachNode* vmul8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vmulBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vmulB_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vmulLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vmulL_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* minmaxL_reg_sseNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RXMM0));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
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

MachNode* minmaxL_reg_sse_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RXMM0));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
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

MachNode* vminmaxL_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* vminmaxL_reg_avx_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* minmaxFP_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* minmaxFP_reg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* evminmaxFP_reg_eavxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* evminmaxFP_reg_eavx_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP atmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP btmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* vector_uminmaxq_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vector_uminmaxq_reg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* signumF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* signumD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* signumV_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* signumV_reg_avx_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* signumV_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* signumV_reg_evex_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* copySignF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* copySignD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);

  return this;
}

MachNode* vshiftBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftB_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftB_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16B_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16B_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16B_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16B_avx_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16B_avx_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift32B_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift32B_avx_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift32B_avx_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift64B_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift64B_avx_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift64B_avx_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftS_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftS_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftI_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftI_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftL_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftL_arith_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift8B_var_nobwNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift8B_var_nobw_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift8B_var_nobw_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16B_var_nobwNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16B_var_nobw_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16B_var_nobw_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift32B_var_nobwNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp4
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift32B_var_nobw_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp4
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift32B_var_nobw_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp4
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftB_var_evex_bwNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftB_var_evex_bw_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftB_var_evex_bw_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift64B_var_evex_bwNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift64B_var_evex_bw_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift64B_var_evex_bw_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift8S_var_nobwNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift8S_var_nobw_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift8S_var_nobw_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16S_var_nobwNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16S_var_nobw_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshift16S_var_nobw_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vshiftL_arith_varNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vcastStoXNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vcastItoXNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* castFtoX_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp4
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* castFtoX_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP ktmp2
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* castDtoX_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp4
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp5
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* castDtoX_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP ktmp2
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vround_float_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp4
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* vround_float_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP ktmp2
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* vround_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP ktmp2
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* evcmpFD64Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ktmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* vcmp_negateNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* vcmpuNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* vcmp64Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ktmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* vextractINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* vextractI_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* vextractI_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* vextractLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* extractFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGREGF));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* vextractFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* vextractDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* blendvpNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RXMM0));
  add_req(def);

  return this;
}

MachNode* vblendvpNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* evblendvp64Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ktmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* vptest_lt16Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP vtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* ktest_alltrue_le8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* ktest_anytrue_le8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* loadMaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* loadMask64Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* loadMask_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP xtmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vstoreMask2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vstoreMask4BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* storeMask8BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* storeMask8B_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vstoreMask_evex_vectmaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vstoreMask_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* VectorPopulateIndexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* VectorPopulateLIndexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* rearrangeB_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* rearrangeB_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* loadShuffleSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* rearrangeS_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp1
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);
  // TEMP vtmp2
  def = new MachTempNode(state->MachOperGenerator(LEGVEC));
  add_req(def);

  return this;
}

MachNode* loadShuffleINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* loadShuffleLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP vtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vpopcount_avx_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* vpopcount_avx_reg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* vcount_trailing_zeros_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* vcount_trailing_zeros_short_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* vcount_trailing_zeros_byte_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp4
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* vcount_trailing_zeros_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* vpternlogNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// src3
    unsigned num4 = opnd_array(4)->num_edges(); 	// func
    unsigned num5 = opnd_array(5)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* vpternlog_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// src3
    unsigned num4 = opnd_array(4)->num_edges(); 	// func
    unsigned num5 = opnd_array(5)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

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

MachNode* vmask_cmp_nodeNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP ktmp2
  def = new MachTempNode(state->MachOperGenerator(KREG));
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
  // TEMP temp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_gen_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP temp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);

  return this;
}

MachNode* vmask_tolong_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_tolong_boolNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_tolong_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_truecount_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_truecount_boolNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_truecount_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_first_or_last_true_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_first_or_last_true_evex_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_first_or_last_true_boolNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_first_or_last_true_bool_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_first_or_last_true_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vmask_first_or_last_true_avx_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vcompress_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rscratch
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP perm
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vcompress_reg_avx_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP rscratch
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP perm
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vcompress_mask_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP rtmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vreverse_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* vreverse_reg_gfniNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* vreverse_byte_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vreverse_byte64_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* vcount_leading_zeros_short_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vcount_leading_zeros_byte_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* vcount_leading_zeros_int_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vcount_leading_zeros_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* mask_not_immLT8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP rtmp
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* long_to_maskLE8_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp1
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* long_to_maskGT8_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP rtmp1
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP rtmp2
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mask_opers_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP kscratch
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* mask_opers_evex_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP kscratch
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* mask_opers_evex_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP kscratch
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* FloatClassCheck_reg_reg_vfpclassNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ktmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* DoubleClassCheck_reg_reg_vfpclassNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ktmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* vector_addsub_saturating_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP ktmp2
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* vector_addsub_saturating_reg_evex_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp1
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);
  // TEMP ktmp2
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* vector_addsub_saturating_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp4
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vector_addsub_saturating_reg_avx_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp4
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vector_add_saturating_unsigned_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP ktmp
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* vector_add_saturating_unsigned_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp3
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* vector_sub_saturating_unsigned_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP ktmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(KREG));
  add_req(def);

  return this;
}

MachNode* vector_sub_saturating_unsigned_reg_avxNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp1
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);
  // TEMP xtmp2
  def = new MachTempNode(state->MachOperGenerator(VEC));
  add_req(def);

  return this;
}

MachNode* compareAndSwapP_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapP_shenandoah_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapN_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegN );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapN_shenandoah_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegN );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeN_shenandoahNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
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
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
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
  def = new MachTempNode(state->MachOperGenerator(RREGP));
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
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zStorePNullNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
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
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
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
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zCompareAndSwapP_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* zXChgPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1StorePNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1StoreNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1EncodePAndStoreNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1CompareAndExchangePNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1CompareAndExchangeNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1CompareAndSwapPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1CompareAndSwapP_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1CompareAndSwapNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegN );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1CompareAndSwapN_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegN );
  proj_list.push(kill);
  // TEMP res
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1GetAndSetPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1GetAndSetNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1LoadPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* g1LoadNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGN));
  add_req(def);
  // TEMP tmp1
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RREGP));
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
// Check adlc -DAMD64=1
#ifndef AMD64
#  error "AMD64 must be defined"
#endif // AMD64
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
// Check adlc -DASSERT=1
#ifndef ASSERT
#  error "ASSERT must be defined"
#endif // ASSERT
