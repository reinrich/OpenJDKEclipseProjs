#line 1 "ad_ppc_peephole.cpp"
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
int loadINode::peephole(Block* block, int block_index, PhaseCFG* cfg_, PhaseRegAlloc* ra_) {
  bool  matches = true;
  MachNode *inst0 = this;
  MachNode *inst1 = NULL;
  if( ((OptoPeepholeAt == -1) || (OptoPeepholeAt==0)) && ( true ) ) {
    matches = true;
  // Check instruction sub-tree
  // Identify previous instruction if inside this block
  if( block_index - 1 > 0 ) {
    Node *n = block->get_node(block_index - 1);
    inst1 = (n->is_Mach()) ? n->as_Mach() : NULL;
  }
  matches = matches && (inst1 != NULL) && (inst1->rule() == storeI_rule);
    // If instruction subtree matches
    if( matches ) {

      // Check constraints on sub-tree-leaves
      // Build map to register info
  // Start at oper_input_base() and count operands
  unsigned inst0_idx0 = 2;
  unsigned inst0_idx1 = 2; 	// mem
  unsigned inst0_idx2 = inst0->req(); 
  // Start at oper_input_base() and count operands
  unsigned inst1_idx0 = 2;
  unsigned inst1_idx1 = 2; 	// mem
  unsigned inst1_idx2 = inst1_idx1 + inst1->_opnds[1]->num_edges(); 	// src
  unsigned inst1_idx3 = inst1->req(); 
      matches = matches &&
        (inst1->_opnds[2]->reg(ra_,inst1,inst1_idx2)  /* 1.src */ == /* 0.dst */ inst0->_opnds[0]->reg(ra_,inst0))
      && ( 
  (inst1->_opnds[1]->base(ra_,inst1,inst1_idx1)  /* 1.mem$$base */ == /* 0.mem$$base */ inst0->_opnds[1]->base(ra_,inst0,inst0_idx1)) &&
  (inst1->_opnds[1]->index(ra_,inst1,inst1_idx1)  /* 1.mem$$index */ == /* 0.mem$$index */ inst0->_opnds[1]->index(ra_,inst0,inst0_idx1)) &&
  (inst1->_opnds[1]->scale()  /* 1.mem$$scale */ == /* 0.mem$$scale */ inst0->_opnds[1]->scale()) &&
  (inst1->_opnds[1]->disp(ra_,inst1,inst1_idx1)  /* 1.mem$$disp */ == /* 0.mem$$disp */ inst0->_opnds[1]->disp(ra_,inst0,inst0_idx1))
) 
;
      // IF instructions and constraints matched
      if( matches ) {
        // generate the new sub-tree
        assert( true, "Debug stopping point");
        storeINode *root = new storeINode();
        // ----- Initial setup -----
        root->add_req(_in[0]);                // control edge
        root->add_req(inst1->in(1));        // unmatched ideal edge
        root->_bottom_type = inst1->bottom_type();
        ra_->set_oop (root, ra_->is_oop(inst1));
        ra_->set_pair(root->_idx, ra_->get_reg_second(inst1), ra_->get_reg_first(inst1));
        root->_opnds[0] = inst1->_opnds[0]->clone(); // result
        // ----- Done with initial setup -----
        for( unsigned x1 = inst1_idx1; x1 < inst1_idx2; x1++ )
          root->add_req( inst1->in(x1) );
        root->_opnds[1] = inst1->_opnds[1]->clone();
        for( unsigned x2 = inst1_idx2; x2 < inst1_idx3; x2++ )
          root->add_req( inst1->in(x2) );
        root->_opnds[2] = inst1->_opnds[2]->clone();
        inst0->replace_by(root);
        inst0->set_removed();
        cfg_->map_node_to_block(inst0, nullptr);
        inst1->set_removed();
        cfg_->map_node_to_block(inst1, nullptr);
        block->remove_node(block_index - 0);
        block->remove_node(block_index - 1);
        block->insert_node(root, block_index - 1);
        cfg_->map_node_to_block(root, block);
        return 0;  // return the peephole index;
      }
    }
  } // end of peephole rule #0

  return -1;  // No peephole rules matched
}

int loadLNode::peephole(Block* block, int block_index, PhaseCFG* cfg_, PhaseRegAlloc* ra_) {
  bool  matches = true;
  MachNode *inst0 = this;
  MachNode *inst1 = NULL;
  if( ((OptoPeepholeAt == -1) || (OptoPeepholeAt==1)) && ( true ) ) {
    matches = true;
  // Check instruction sub-tree
  // Identify previous instruction if inside this block
  if( block_index - 1 > 0 ) {
    Node *n = block->get_node(block_index - 1);
    inst1 = (n->is_Mach()) ? n->as_Mach() : NULL;
  }
  matches = matches && (inst1 != NULL) && (inst1->rule() == storeL_rule);
    // If instruction subtree matches
    if( matches ) {

      // Check constraints on sub-tree-leaves
      // Build map to register info
  // Start at oper_input_base() and count operands
  unsigned inst0_idx0 = 2;
  unsigned inst0_idx1 = 2; 	// mem
  unsigned inst0_idx2 = inst0->req(); 
  // Start at oper_input_base() and count operands
  unsigned inst1_idx0 = 2;
  unsigned inst1_idx1 = 2; 	// mem
  unsigned inst1_idx2 = inst1_idx1 + inst1->_opnds[1]->num_edges(); 	// src
  unsigned inst1_idx3 = inst1->req(); 
      matches = matches &&
        (inst1->_opnds[2]->reg(ra_,inst1,inst1_idx2)  /* 1.src */ == /* 0.dst */ inst0->_opnds[0]->reg(ra_,inst0))
      && ( 
  (inst1->_opnds[1]->base(ra_,inst1,inst1_idx1)  /* 1.mem$$base */ == /* 0.mem$$base */ inst0->_opnds[1]->base(ra_,inst0,inst0_idx1)) &&
  (inst1->_opnds[1]->index(ra_,inst1,inst1_idx1)  /* 1.mem$$index */ == /* 0.mem$$index */ inst0->_opnds[1]->index(ra_,inst0,inst0_idx1)) &&
  (inst1->_opnds[1]->scale()  /* 1.mem$$scale */ == /* 0.mem$$scale */ inst0->_opnds[1]->scale()) &&
  (inst1->_opnds[1]->disp(ra_,inst1,inst1_idx1)  /* 1.mem$$disp */ == /* 0.mem$$disp */ inst0->_opnds[1]->disp(ra_,inst0,inst0_idx1))
) 
;
      // IF instructions and constraints matched
      if( matches ) {
        // generate the new sub-tree
        assert( true, "Debug stopping point");
        storeLNode *root = new storeLNode();
        // ----- Initial setup -----
        root->add_req(_in[0]);                // control edge
        root->add_req(inst1->in(1));        // unmatched ideal edge
        root->_bottom_type = inst1->bottom_type();
        ra_->set_oop (root, ra_->is_oop(inst1));
        ra_->set_pair(root->_idx, ra_->get_reg_second(inst1), ra_->get_reg_first(inst1));
        root->_opnds[0] = inst1->_opnds[0]->clone(); // result
        // ----- Done with initial setup -----
        for( unsigned x1 = inst1_idx1; x1 < inst1_idx2; x1++ )
          root->add_req( inst1->in(x1) );
        root->_opnds[1] = inst1->_opnds[1]->clone();
        for( unsigned x2 = inst1_idx2; x2 < inst1_idx3; x2++ )
          root->add_req( inst1->in(x2) );
        root->_opnds[2] = inst1->_opnds[2]->clone();
        inst0->replace_by(root);
        inst0->set_removed();
        cfg_->map_node_to_block(inst0, nullptr);
        inst1->set_removed();
        cfg_->map_node_to_block(inst1, nullptr);
        block->remove_node(block_index - 0);
        block->remove_node(block_index - 1);
        block->insert_node(root, block_index - 1);
        cfg_->map_node_to_block(root, block);
        return 1;  // return the peephole index;
      }
    }
  } // end of peephole rule #1

  return -1;  // No peephole rules matched
}

int loadPNode::peephole(Block* block, int block_index, PhaseCFG* cfg_, PhaseRegAlloc* ra_) {
  bool  matches = true;
  MachNode *inst0 = this;
  MachNode *inst1 = NULL;
  if( ((OptoPeepholeAt == -1) || (OptoPeepholeAt==2)) && ( true ) ) {
    matches = true;
  // Check instruction sub-tree
  // Identify previous instruction if inside this block
  if( block_index - 1 > 0 ) {
    Node *n = block->get_node(block_index - 1);
    inst1 = (n->is_Mach()) ? n->as_Mach() : NULL;
  }
  matches = matches && (inst1 != NULL) && (inst1->rule() == storeP_rule);
    // If instruction subtree matches
    if( matches ) {

      // Check constraints on sub-tree-leaves
      // Build map to register info
  // Start at oper_input_base() and count operands
  unsigned inst0_idx0 = 2;
  unsigned inst0_idx1 = 2; 	// mem
  unsigned inst0_idx2 = inst0->req(); 
  // Start at oper_input_base() and count operands
  unsigned inst1_idx0 = 2;
  unsigned inst1_idx1 = 2; 	// dst
  unsigned inst1_idx2 = inst1_idx1 + inst1->_opnds[1]->num_edges(); 	// src
  unsigned inst1_idx3 = inst1->req(); 
      matches = matches &&
        (inst1->_opnds[2]->reg(ra_,inst1,inst1_idx2)  /* 1.src */ == /* 0.dst */ inst0->_opnds[0]->reg(ra_,inst0))
      && ( 
  (inst1->_opnds[1]->base(ra_,inst1,inst1_idx1)  /* 1.dst$$base */ == /* 0.mem$$base */ inst0->_opnds[1]->base(ra_,inst0,inst0_idx1)) &&
  (inst1->_opnds[1]->index(ra_,inst1,inst1_idx1)  /* 1.dst$$index */ == /* 0.mem$$index */ inst0->_opnds[1]->index(ra_,inst0,inst0_idx1)) &&
  (inst1->_opnds[1]->scale()  /* 1.dst$$scale */ == /* 0.mem$$scale */ inst0->_opnds[1]->scale()) &&
  (inst1->_opnds[1]->disp(ra_,inst1,inst1_idx1)  /* 1.dst$$disp */ == /* 0.mem$$disp */ inst0->_opnds[1]->disp(ra_,inst0,inst0_idx1))
) 
;
      // IF instructions and constraints matched
      if( matches ) {
        // generate the new sub-tree
        assert( true, "Debug stopping point");
        storePNode *root = new storePNode();
        // ----- Initial setup -----
        root->add_req(_in[0]);                // control edge
        root->add_req(inst1->in(1));        // unmatched ideal edge
        root->_bottom_type = inst1->bottom_type();
        ra_->set_oop (root, ra_->is_oop(inst1));
        ra_->set_pair(root->_idx, ra_->get_reg_second(inst1), ra_->get_reg_first(inst1));
        root->_opnds[0] = inst1->_opnds[0]->clone(); // result
        // ----- Done with initial setup -----
        for( unsigned x1 = inst1_idx1; x1 < inst1_idx2; x1++ )
          root->add_req( inst1->in(x1) );
        root->_opnds[1] = inst1->_opnds[1]->clone();
        for( unsigned x2 = inst1_idx2; x2 < inst1_idx3; x2++ )
          root->add_req( inst1->in(x2) );
        root->_opnds[2] = inst1->_opnds[2]->clone();
        inst0->replace_by(root);
        inst0->set_removed();
        cfg_->map_node_to_block(inst0, nullptr);
        inst1->set_removed();
        cfg_->map_node_to_block(inst1, nullptr);
        block->remove_node(block_index - 0);
        block->remove_node(block_index - 1);
        block->insert_node(root, block_index - 1);
        cfg_->map_node_to_block(root, block);
        return 2;  // return the peephole index;
      }
    }
  } // end of peephole rule #2

  return -1;  // No peephole rules matched
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
