#line 1 "ad_ppc_pipeline.cpp"
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
#include "adfiles/ad_ppc.hpp"

//------------------Pipeline Methods-----------------------------------------
#ifndef PRODUCT
const char * Pipeline::stageName(uint s) {
  static const char * const _stage_names[] = {
    "undefined", "PPC_IF", "PPC_IC", "PPC_D0", "PPC_D1", "PPC_D2", "PPC_D3", "PPC_Xfer1", "PPC_GD", "PPC_MP", "PPC_ISS", "PPC_RF", "PPC_EX1", "PPC_EX2", "PPC_EX3", "PPC_EX4", "PPC_EX5", "PPC_EX6", "PPC_WB", "PPC_Xfer2", "PPC_CP"
  };

  return (s <= 20 ? _stage_names[s] : "???");
}
#endif

uint Pipeline::functional_unit_latency(uint start, const Pipeline *pred) const {
  // See if the functional units overlap
  uint mask = resourcesUsedExclusively() & pred->resourcesUsedExclusively();
  if (mask == 0)
    return (start);

  for (uint i = 0; i < pred->resourceUseCount(); i++) {
    const Pipeline_Use_Element *predUse = pred->resourceUseElement(i);
    if (predUse->multiple())
      continue;

    for (uint j = 0; j < resourceUseCount(); j++) {
      const Pipeline_Use_Element *currUse = resourceUseElement(j);
      if (currUse->multiple())
        continue;

      if (predUse->used() & currUse->used()) {
        Pipeline_Use_Cycle_Mask x = predUse->mask();
        Pipeline_Use_Cycle_Mask y = currUse->mask();

        for ( y <<= start; x.overlaps(y); start++ )
          y <<= 1;
      }
    }
  }

  // There is the potential for overlap
  return (start);
}

// The following two routines assume that the root Pipeline_Use entity
// consists of exactly 1 element for each functional unit
// start is relative to the current cycle; used for latency-based info
uint Pipeline_Use::full_latency(uint delay, const Pipeline_Use &pred) const {
  for (uint i = 0; i < pred._count; i++) {
    const Pipeline_Use_Element *predUse = pred.element(i);
    if (predUse->_multiple) {
      uint min_delay = 1;
      // Multiple possible functional units, choose first unused one
      for (uint j = predUse->_lb; j <= predUse->_ub; j++) {
        const Pipeline_Use_Element *currUse = element(j);
        uint curr_delay = delay;
        if (predUse->_used & currUse->_used) {
          Pipeline_Use_Cycle_Mask x = predUse->_mask;
          Pipeline_Use_Cycle_Mask y = currUse->_mask;

          for ( y <<= curr_delay; x.overlaps(y); curr_delay++ )
            y <<= 1;
        }
        if (min_delay > curr_delay)
          min_delay = curr_delay;
      }
      if (delay < min_delay)
      delay = min_delay;
    }
    else {
      for (uint j = predUse->_lb; j <= predUse->_ub; j++) {
        const Pipeline_Use_Element *currUse = element(j);
        if (predUse->_used & currUse->_used) {
          Pipeline_Use_Cycle_Mask x = predUse->_mask;
          Pipeline_Use_Cycle_Mask y = currUse->_mask;

          for ( y <<= delay; x.overlaps(y); delay++ )
            y <<= 1;
        }
      }
    }
  }

  return (delay);
}

void Pipeline_Use::add_usage(const Pipeline_Use &pred) {
  for (uint i = 0; i < pred._count; i++) {
    const Pipeline_Use_Element *predUse = pred.element(i);
    if (predUse->_multiple) {
      // Multiple possible functional units, choose first unused one
      for (uint j = predUse->_lb; j <= predUse->_ub; j++) {
        Pipeline_Use_Element *currUse = element(j);
        if ( !predUse->_mask.overlaps(currUse->_mask) ) {
          currUse->_used |= (1 << j);
          _resources_used |= (1 << j);
          currUse->_mask.Or(predUse->_mask);
          break;
        }
      }
    }
    else {
      for (uint j = predUse->_lb; j <= predUse->_ub; j++) {
        Pipeline_Use_Element *currUse = element(j);
        currUse->_used |= (1 << j);
        _resources_used |= (1 << j);
        currUse->_mask.Or(predUse->_mask);
      }
    }
  }
}

uint Pipeline::operand_latency(uint opnd, const Pipeline *pred) const {
  int const default_latency = 1;

  assert(this, "NULL pipeline info");
  assert(pred, "NULL predecessor pipline info");

  if (pred->hasFixedLatency())
    return (pred->fixedLatency());

  // If this is not an operand, then assume a dependence with 0 latency
  if (opnd > _read_stage_count)
    return (0);

  uint writeStage = pred->_write_stage;
  uint readStage  = _read_stages[opnd-1];

  if (writeStage == stage_undefined || readStage == stage_undefined)
    return (default_latency);

  int delta = writeStage - readStage;
  if (delta < 0) delta = 0;

  return (delta);
}

Pipeline_Use_Cycle_Mask operator&(const Pipeline_Use_Cycle_Mask &in1, const Pipeline_Use_Cycle_Mask &in2) {
  return Pipeline_Use_Cycle_Mask(in1._mask & in2._mask);
}

Pipeline_Use_Cycle_Mask operator|(const Pipeline_Use_Cycle_Mask &in1, const Pipeline_Use_Cycle_Mask &in2) {
  return Pipeline_Use_Cycle_Mask(in1._mask | in2._mask);
}

static const Pipeline pipeline_class_Zero_Instructions(0, 0, true, 0, 0, false, false, false, false, NULL, NULL, NULL, Pipeline_Use(0, 0, 0, NULL));

static const Pipeline pipeline_class_Unknown_Instructions(0, 0, true, 0, 0, false, true, true, false, NULL, NULL, NULL, Pipeline_Use(0, 0, 0, NULL));

const Pipeline_Use_Element Pipeline_Use::elaborated_elements[8] = {
  Pipeline_Use_Element(0, 0, 0, false, Pipeline_Use_Cycle_Mask()),
  Pipeline_Use_Element(0, 1, 1, false, Pipeline_Use_Cycle_Mask()),
  Pipeline_Use_Element(0, 2, 2, false, Pipeline_Use_Cycle_Mask()),
  Pipeline_Use_Element(0, 3, 3, false, Pipeline_Use_Cycle_Mask()),
  Pipeline_Use_Element(0, 4, 4, false, Pipeline_Use_Cycle_Mask()),
  Pipeline_Use_Element(0, 5, 5, false, Pipeline_Use_Cycle_Mask()),
  Pipeline_Use_Element(0, 6, 6, false, Pipeline_Use_Cycle_Mask()),
  Pipeline_Use_Element(0, 7, 7, false, Pipeline_Use_Cycle_Mask())
};

const Pipeline_Use Pipeline_Use::elaborated_use(0, 0, 8, (Pipeline_Use_Element *)&elaborated_elements[0]);


// Pipeline Class "pipe_class_default"
static const enum machPipelineStages pipeline_res_stages_001[8] = {
  stage_undefined, // PPC_BR
  stage_undefined, // PPC_CR
  stage_undefined, // PPC_FX1
  stage_undefined, // PPC_FX2
  stage_undefined, // PPC_LDST1
  stage_undefined, // PPC_LDST2
  stage_undefined, // PPC_FP1
  stage_undefined  // PPC_FP2
};

static const uint pipeline_res_cycles_001[8] = {
  0, // PPC_BR
  0, // PPC_CR
  0, // PPC_FX1
  0, // PPC_FX2
  0, // PPC_LDST1
  0, // PPC_LDST2
  0, // PPC_FP1
  0  // PPC_FP2
};

static const Pipeline pipeline_class_001((uint)stage_undefined, 0, true, 2, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x00, 0x00, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_empty"
static const Pipeline pipeline_class_002((uint)stage_undefined, 0, true, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x00, 0x00, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_compare"
static const Pipeline pipeline_class_003((uint)stage_undefined, 0, true, 16, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x00, 0x00, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_trap"
static const Pipeline pipeline_class_004((uint)stage_undefined, 0, true, 100, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x00, 0x00, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_memory"
static const Pipeline pipeline_class_005((uint)stage_undefined, 0, true, 16, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x00, 0x00, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_call"
static const Pipeline pipeline_class_006((uint)stage_undefined, 0, true, 100, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x00, 0x00, 0, (Pipeline_Use_Element *)NULL));

//------------------Inter-Instruction Latency--------------------------------
uint Node::latency(uint i) {
  uint j;
  // verify in legal range for inputs
  assert(i < len(), "index not in range");

  // verify input is not null
  Node *pred = in(i);
  if (!pred)
    return 0;

  if (pred->is_Proj())
    pred = pred->in(0);

  // if either node does not have pipeline info, use default
  const Pipeline *predpipe = pred->pipeline();
  assert(predpipe, "no predecessor pipeline info");

  if (predpipe->hasFixedLatency())
    return predpipe->fixedLatency();

  const Pipeline *currpipe = pipeline();
  assert(currpipe, "no pipeline info");

  if (!is_Mach())
    return 0;

  const MachNode *m = as_Mach();
  j = m->oper_input_base();
  if (i < j)
    return currpipe->functional_unit_latency(0, predpipe);

  // determine which operand this is in
  uint n = m->num_opnds();
  int delta = 0;

  uint k;
  for (k = 1; k < n; k++) {
    j += m->_opnds[k]->num_edges();
    if (i < j)
      break;
  }
  if (k < n)
    delta = currpipe->operand_latency(k,predpipe);

  return currpipe->functional_unit_latency(delta, predpipe);
}

// Descriptions for emitting different functional unit nops
void Bundle::initialize_nops(MachNode * nop_list[1]) {
  nop_list[0] = (MachNode *) new fxNopNode();
};

#ifndef PRODUCT
void Bundle::dump(outputStream *st) const {
  static const char * bundle_flags[] = {
    "",
    "use nop delay",
    "use unconditional delay",
    "use conditional delay",
    "used in conditional delay",
    "used in unconditional delay",
    "used in all conditional delays",
  };

  static const char *resource_names[8] = { "PPC_BR", "PPC_CR", "PPC_FX1", "PPC_FX2", "PPC_LDST1", "PPC_LDST2", "PPC_FP1", "PPC_FP2" };

  bool needs_comma = false;

  if (_flags) {
    st->print("%s", bundle_flags[_flags]);
    needs_comma = true;
  };
  if (instr_count()) {
    st->print("%s%d instr%s", needs_comma ? ", " : "", instr_count(), instr_count() != 1 ? "s" : "");
    needs_comma = true;
  };
  uint r = resources_used();
  if (r) {
    st->print("%sresource%s:", needs_comma ? ", " : "", (r & (r-1)) != 0 ? "s" : "");
    for (uint i = 0; i < 8; i++)
      if ((r & (1 << i)) != 0)
        st->print(" %s", resource_names[i]);
    needs_comma = true;
  };
  st->print("\n");
}
#endif
const Pipeline *                                       Node::pipeline_class() { return (&pipeline_class_Zero_Instructions); }
const Pipeline *                                       Node::pipeline() const { return (&pipeline_class_Zero_Instructions); }

const Pipeline *                                   MachNode::pipeline_class() { return (&pipeline_class_Unknown_Instructions); }
const Pipeline *                                   MachNode::pipeline() const { return pipeline_class(); }

const Pipeline * MachNopNode::pipeline() const { return (&pipeline_class_001); }


const Pipeline *                              convB2I_reg_2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              convB2I_reg_2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            loadUB_indirectNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                            loadUB_indirectNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                         loadUB_indirect_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                         loadUB_indirect_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                         loadUB_indOffset16Node::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                         loadUB_indOffset16Node::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                      loadUB_indOffset16_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                      loadUB_indOffset16_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     loadUBNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     loadUBNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                  loadUB_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                  loadUB_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadUB2LNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadUB2LNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                loadUB2L_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                loadUB2L_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                      loadSNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                      loadSNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadS_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadS_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     loadUSNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     loadUSNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                  loadUS_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                  loadUS_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadUS2LNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadUS2LNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                loadUS2L_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                loadUS2L_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                      loadINode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                      loadINode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadI_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadI_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadUI2LNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadUI2LNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                    loadI2LNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                    loadI2LNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                 loadI2L_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                 loadI2L_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                      loadLNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                      loadLNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadL_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadL_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                            loadL_unalignedNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                            loadL_unalignedNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     loadV8Node::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     loadV8Node::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                    loadV16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    loadV16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  loadRangeNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                  loadRangeNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                      loadNNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                      loadNNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadN_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadN_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                           loadN2P_unscaledNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                           loadN2P_unscaledNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                     loadN2P_klass_unscaledNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                     loadN2P_klass_unscaledNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                      loadPNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                      loadPNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadP_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadP_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                    loadP2XNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                    loadP2XNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                 loadNKlassNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                 loadNKlassNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                  loadKlassNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                  loadKlassNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                      loadFNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                      loadFNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadF_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadF_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                      loadDNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                      loadDNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadD_acNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadD_acNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                            loadD_unalignedNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                            loadD_unalignedNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                 loadToc_hiNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 loadToc_hiNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 loadToc_loNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 loadToc_loNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 loadConI16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 loadConI16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               loadConIhi16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               loadConIhi16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            loadConI32_lo16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            loadConI32_lo16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 loadConL16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 loadConL16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             loadConL32hi16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             loadConL32hi16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            loadConL32_lo16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            loadConL32_lo16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   loadConLNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadConLNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                loadConL_hiNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                loadConL_hiNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                loadConL_loNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                loadConL_loNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                  loadConN0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  loadConN0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                loadConN_hiNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                loadConN_hiNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                loadConN_loNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                loadConN_loNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     rldiclNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     rldiclNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 clearMs32bNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 clearMs32bNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   loadBaseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   loadBaseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           loadConNKlass_hiNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           loadConNKlass_hiNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         loadConNKlass_maskNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         loadConNKlass_maskNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           loadConNKlass_loNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           loadConNKlass_loNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               loadConP0or1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               loadConP0or1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   loadConPNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadConPNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                loadConP_hiNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                loadConP_hiNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                loadConP_loNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                loadConP_loNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadConFNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadConFNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                               loadConFCompNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                               loadConFCompNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   loadConDNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   loadConDNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                               loadConDCompNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                               loadConDCompNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                        prefetch_alloc_zeroNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                        prefetch_alloc_zeroNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *              prefetch_alloc_zero_no_offsetNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *              prefetch_alloc_zero_no_offsetNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                             prefetch_allocNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                             prefetch_allocNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                   prefetch_alloc_no_offsetNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                   prefetch_alloc_no_offsetNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     storeBNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     storeBNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     storeCNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     storeCNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     storeINode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     storeINode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                             storeI_convL2INode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                             storeI_convL2INode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     storeLNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     storeLNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   storeA8BNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                   storeA8BNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                   storeV16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   storeV16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     storeNNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     storeNNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                storeNKlassNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                storeNKlassNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     storePNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     storePNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     storeFNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     storeFNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     storeDNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     storeDNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                storeCM_CMSNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                storeCM_CMSNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                 storeCM_G1Node::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                 storeCM_G1Node::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                              encodeP_shiftNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              encodeP_shiftNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                encodeP_subNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                encodeP_subNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              cond_sub_baseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              cond_sub_baseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             cond_set_0_oopNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             cond_set_0_oopNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           encodeP_DisjointNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           encodeP_DisjointNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 encodeP_not_null_base_nullNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 encodeP_not_null_base_nullNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 encodeP_narrow_oop_shift_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 encodeP_narrow_oop_shift_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              decodeN_shiftNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              decodeN_shiftNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                decodeN_addNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                decodeN_addNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              cond_add_baseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              cond_add_baseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             cond_set_0_ptrNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             cond_set_0_ptrNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           decodeN_nullBaseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           decodeN_nullBaseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      decodeN_mergeDisjointNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      decodeN_mergeDisjointNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           decodeN_unscaledNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           decodeN_unscaledNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         decodeN2I_unscaledNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         decodeN2I_unscaledNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         encodePKlass_shiftNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         encodePKlass_shiftNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      encodePKlass_sub_baseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      encodePKlass_sub_baseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      encodePKlass_DisjointNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      encodePKlass_DisjointNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         decodeNKlass_shiftNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         decodeNKlass_shiftNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      decodeNKlass_add_baseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      decodeNKlass_add_baseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             membar_acquireNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             membar_acquireNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 unnecessary_membar_acquireNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 unnecessary_membar_acquireNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        membar_acquire_lockNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        membar_acquire_lockNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             membar_releaseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             membar_releaseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           membar_release_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           membar_release_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          membar_storestoreNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          membar_storestoreNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        membar_release_lockNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        membar_release_lockNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            membar_volatileNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            membar_volatileNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            membar_CPUOrderNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            membar_CPUOrderNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             cmovI_reg_iselNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             cmovI_reg_iselNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  cmovI_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  cmovI_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  cmovI_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  cmovI_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             cmovL_reg_iselNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             cmovL_reg_iselNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  cmovL_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  cmovL_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  cmovL_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  cmovL_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             cmovN_reg_iselNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             cmovN_reg_iselNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  cmovN_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  cmovN_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  cmovN_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  cmovN_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             cmovP_reg_iselNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             cmovP_reg_iselNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  cmovP_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  cmovP_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  cmovP_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  cmovP_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  cmovF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  cmovF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  cmovD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  cmovD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           storeLConditional_regP_regL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           storeLConditional_regP_regL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           storePConditional_regP_regP_regPNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *           storePConditional_regP_regP_regPNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                loadPLockedNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                loadPLockedNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *             compareAndSwapB_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             compareAndSwapB_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            compareAndSwapB4_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            compareAndSwapB4_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             compareAndSwapS_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             compareAndSwapS_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            compareAndSwapS4_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            compareAndSwapS4_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             compareAndSwapI_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             compareAndSwapI_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             compareAndSwapN_regP_regN_regNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             compareAndSwapN_regP_regN_regNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             compareAndSwapL_regP_regL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             compareAndSwapL_regP_regL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             compareAndSwapP_regP_regP_regPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             compareAndSwapP_regP_regP_regPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         weakCompareAndSwapB_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         weakCompareAndSwapB_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *        weakCompareAndSwapB4_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *        weakCompareAndSwapB4_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     weakCompareAndSwapB_acq_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     weakCompareAndSwapB_acq_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *    weakCompareAndSwapB4_acq_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *    weakCompareAndSwapB4_acq_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         weakCompareAndSwapS_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         weakCompareAndSwapS_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *        weakCompareAndSwapS4_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *        weakCompareAndSwapS4_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     weakCompareAndSwapS_acq_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     weakCompareAndSwapS_acq_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *    weakCompareAndSwapS4_acq_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *    weakCompareAndSwapS4_acq_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         weakCompareAndSwapI_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         weakCompareAndSwapI_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     weakCompareAndSwapI_acq_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     weakCompareAndSwapI_acq_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         weakCompareAndSwapN_regP_regN_regNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         weakCompareAndSwapN_regP_regN_regNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     weakCompareAndSwapN_acq_regP_regN_regNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     weakCompareAndSwapN_acq_regP_regN_regNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         weakCompareAndSwapL_regP_regL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         weakCompareAndSwapL_regP_regL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     weakCompareAndSwapL_acq_regP_regL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     weakCompareAndSwapL_acq_regP_regL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         weakCompareAndSwapP_regP_regP_regPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         weakCompareAndSwapP_regP_regP_regPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     weakCompareAndSwapP_acq_regP_regP_regPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     weakCompareAndSwapP_acq_regP_regP_regPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         compareAndExchangeB_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         compareAndExchangeB_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *        compareAndExchangeB4_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *        compareAndExchangeB4_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     compareAndExchangeB_acq_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     compareAndExchangeB_acq_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *    compareAndExchangeB4_acq_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *    compareAndExchangeB4_acq_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         compareAndExchangeS_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         compareAndExchangeS_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *        compareAndExchangeS4_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *        compareAndExchangeS4_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     compareAndExchangeS_acq_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     compareAndExchangeS_acq_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *    compareAndExchangeS4_acq_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *    compareAndExchangeS4_acq_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         compareAndExchangeI_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         compareAndExchangeI_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     compareAndExchangeI_acq_regP_regI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     compareAndExchangeI_acq_regP_regI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         compareAndExchangeN_regP_regN_regNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         compareAndExchangeN_regP_regN_regNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     compareAndExchangeN_acq_regP_regN_regNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     compareAndExchangeN_acq_regP_regN_regNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         compareAndExchangeL_regP_regL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         compareAndExchangeL_regP_regL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     compareAndExchangeL_acq_regP_regL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     compareAndExchangeL_acq_regP_regL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         compareAndExchangeP_regP_regP_regPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         compareAndExchangeP_regP_regP_regPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     compareAndExchangeP_acq_regP_regP_regPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     compareAndExchangeP_acq_regP_regP_regPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 getAndAddBNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 getAndAddBNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                getAndAddB4Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                getAndAddB4Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 getAndAddSNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 getAndAddSNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                getAndAddS4Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                getAndAddS4Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 getAndAddINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 getAndAddINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 getAndAddLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 getAndAddLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 getAndSetBNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 getAndSetBNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                getAndSetB4Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                getAndSetB4Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 getAndSetSNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 getAndSetSNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                getAndSetS4Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                getAndSetS4Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 getAndSetINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 getAndSetINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 getAndSetLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 getAndSetLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 getAndSetPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 getAndSetPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 getAndSetNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 getAndSetNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               addI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               addI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             addI_reg_reg_2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             addI_reg_reg_2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             addI_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             addI_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           addI_reg_immhi16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           addI_reg_immhi16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               addL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               addL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             addL_reg_reg_2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             addL_reg_reg_2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             addI_regL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             addI_regL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             addL_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             addL_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           addL_reg_immhi16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           addL_reg_immhi16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               addP_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               addP_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             addP_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             addP_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           addP_reg_immhi16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           addP_reg_immhi16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               subI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               subI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             subI_imm16_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             subI_imm16_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           signmask32I_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           signmask32I_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  negI_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  negI_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               subL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               subL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             subI_regL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             subI_regL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           signmask64I_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           signmask64I_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           signmask64L_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           signmask64L_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               negL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               negL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             negI_con0_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             negI_con0_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               mulI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               mulI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             mulI_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             mulI_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               mulL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               mulL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           mulHighL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           mulHighL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             mulL_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             mulL_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   divI_reg_immIvalueMinus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   divI_reg_immIvalueMinus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      divI_reg_regnotMinus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      divI_reg_regnotMinus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         cmovI_bne_negI_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         cmovI_bne_negI_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   divL_reg_immLvalueMinus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   divL_reg_immLvalueMinus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      divL_reg_regnotMinus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      divL_reg_regnotMinus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         cmovL_bne_negL_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         cmovL_bne_negL_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              maskI_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              maskI_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            lShiftI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            lShiftI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            lShiftI_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            lShiftI_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              lShiftI_andI_immInegpow2_imm5Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              lShiftI_andI_immInegpow2_imm5Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *      lShiftI_andI_immInegpow2_rShiftI_imm5Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *      lShiftI_andI_immInegpow2_rShiftI_imm5Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          lShiftL_regL_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          lShiftL_regL_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          lshiftL_regL_immINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          lshiftL_regL_immINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       lShiftL_regI_immGE32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       lShiftL_regI_immGE32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline * scaledPositiveI2L_lShiftL_convI2L_reg_imm6Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline * scaledPositiveI2L_lShiftL_convI2L_reg_imm6Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           arShiftI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           arShiftI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           arShiftI_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           arShiftI_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         arShiftL_regL_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         arShiftL_regL_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         arShiftL_regL_immINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         arShiftL_regL_immINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 convL2I_arShiftL_regL_immINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 convL2I_arShiftL_regL_immINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           urShiftI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           urShiftI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           urShiftI_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           urShiftI_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         urShiftL_regL_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         urShiftL_regL_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         urShiftL_regL_immINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         urShiftL_regL_immINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 convL2I_urShiftL_regL_immINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 convL2I_urShiftL_regL_immINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      shrP_convP2X_reg_imm6Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      shrP_convP2X_reg_imm6Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     andI_urShiftI_regI_immI_immIpow2minus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     andI_urShiftI_regI_immI_immIpow2minus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     andL_urShiftL_regL_immI_immLpow2minus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     andL_urShiftL_regL_immI_immLpow2minus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   sxtI_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   sxtI_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            rotlI_reg_immi8Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            rotlI_reg_immi8Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          rotlI_reg_immi8_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          rotlI_reg_immi8_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            rotrI_reg_immi8Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            rotrI_reg_immi8Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          rotrI_reg_immi8_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          rotrI_reg_immi8_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               addF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               addF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               addD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               addD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               subF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               subF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               subD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               subD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               mulF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               mulF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               mulD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               mulD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               divF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               divF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               divD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               divD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   absF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   absF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   absD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   absD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   negF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   negF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   negD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   negD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              negF_absF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              negF_absF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              negD_absD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              negD_absD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  sqrtD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  sqrtD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  sqrtF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  sqrtF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            roundDouble_nopNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            roundDouble_nopNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             roundFloat_nopNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             roundFloat_nopNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              maddF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              maddF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              maddD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              maddD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             mnsubF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             mnsubF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           mnsubF_reg_reg_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           mnsubF_reg_reg_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             mnsubD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             mnsubD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           mnsubD_reg_reg_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           mnsubD_reg_reg_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             mnaddF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             mnaddF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           mnaddF_reg_reg_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           mnaddF_reg_reg_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             mnaddD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             mnaddD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           mnaddD_reg_reg_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           mnaddD_reg_reg_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              msubF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              msubF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              msubD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              msubD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               andI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               andI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          andI_reg_immIhi16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          andI_reg_immIhi16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            andI_reg_uimm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            andI_reg_uimm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       andI_reg_immInegpow2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       andI_reg_immInegpow2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    andI_reg_immIpow2minus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    andI_reg_immIpow2minus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      andI_reg_immIpowerOf2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      andI_reg_immIpowerOf2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               andL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               andL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            andL_reg_uimm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            andL_reg_uimm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       andL_reg_immLnegpow2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       andL_reg_immLnegpow2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    andL_reg_immLpow2minus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    andL_reg_immLpow2minus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            convL2I_andL_reg_immLpow2minus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            convL2I_andL_reg_immLpow2minus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                orI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                orI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              orI_reg_reg_2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              orI_reg_reg_2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             orI_reg_uimm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             orI_reg_uimm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                orL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                orL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              orI_regL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              orI_regL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             orL_reg_uimm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             orL_reg_uimm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               xorI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               xorI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             xorI_reg_reg_2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             xorI_reg_reg_2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            xorI_reg_uimm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            xorI_reg_uimm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               xorL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               xorL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             xorI_regL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             xorI_regL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            xorL_reg_uimm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            xorL_reg_uimm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   notI_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   notI_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   notL_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   notL_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              andcI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              andcI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            andcI_reg_reg_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            andcI_reg_reg_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              andcL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              andcL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                moveL2D_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                moveL2D_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                moveI2D_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                moveI2D_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               stkI_to_regINode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                               stkI_to_regINode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                               regI_to_stkINode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                               regI_to_stkINode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                               stkL_to_regLNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                               stkL_to_regLNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                               regL_to_stkLNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                               regL_to_stkLNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                          moveF2I_stack_regNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                          moveF2I_stack_regNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                          moveF2I_reg_stackNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                          moveF2I_reg_stackNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                          moveI2F_stack_regNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                          moveI2F_stack_regNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                          moveI2F_reg_stackNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                          moveI2F_reg_stackNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                          moveF2L_reg_stackNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          moveF2L_reg_stackNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          moveD2L_stack_regNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                          moveD2L_stack_regNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                          moveD2L_reg_stackNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                          moveD2L_reg_stackNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                          moveL2D_stack_regNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                          moveL2D_stack_regNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                          moveL2D_reg_stackNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                          moveL2D_reg_stackNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                    moveRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    moveRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                    castX2PNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    castX2PNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                    castP2XNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    castP2XNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     castPPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     castPPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     castIINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     castIINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                checkCastPPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                checkCastPPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      convI2Bool_reg__cmoveNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                      convI2Bool_reg__cmoveNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *      xorI_convI2Bool_reg_immIvalue1__cmoveNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *      xorI_convI2Bool_reg_immIvalue1__cmoveNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *           convI2Bool_andI_reg_immIpowerOf2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           convI2Bool_andI_reg_immIpowerOf2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      convP2Bool_reg__cmoveNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                      convP2Bool_reg__cmoveNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *      xorI_convP2Bool_reg_immIvalue1__cmoveNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *      xorI_convP2Bool_reg_immIvalue1__cmoveNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                        cmpLTMask_reg_immI0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        cmpLTMask_reg_immI0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                convB2I_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                convB2I_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                      extshNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      extshNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                convS2I_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                convS2I_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               sxtI_L2L_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               sxtI_L2L_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                convL2I_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                convL2I_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            convD2IRaw_regDNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            convD2IRaw_regDNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       cmovI_bso_stackSlotLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       cmovI_bso_stackSlotLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              cmovI_bso_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              cmovI_bso_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            convF2IRaw_regFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            convF2IRaw_regFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                convI2L_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                convI2L_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           zeroExtendL_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           zeroExtendL_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           zeroExtendL_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           zeroExtendL_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            convF2LRaw_regFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            convF2LRaw_regFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       cmovL_bso_stackSlotLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       cmovL_bso_stackSlotLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              cmovL_bso_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              cmovL_bso_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            convD2LRaw_regDNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            convD2LRaw_regDNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            convL2DRaw_regDNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            convL2DRaw_regDNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                convD2F_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                convD2F_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            convL2FRaw_regFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            convL2FRaw_regFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                convF2D_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                convF2D_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               cmpI_reg_regNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                               cmpI_reg_regNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                             cmpI_reg_imm16Node::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                             cmpI_reg_imm16Node::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                              testI_reg_immNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              testI_reg_immNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                               cmpL_reg_regNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                               cmpL_reg_regNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                             cmpL_reg_imm16Node::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                             cmpL_reg_imm16Node::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                              cmpUL_reg_regNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              cmpUL_reg_regNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                            cmpUL_reg_imm16Node::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                            cmpUL_reg_imm16Node::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                              testL_reg_regNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              testL_reg_regNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                              testL_reg_immNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              testL_reg_immNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *           cmovI_conIvalueMinus1_conIvalue1Node::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *           cmovI_conIvalueMinus1_conIvalue1Node::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                     rangeCheck_iReg_uimm15Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                     rangeCheck_iReg_uimm15Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                       rangeCheck_iReg_iRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                       rangeCheck_iReg_iRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                     rangeCheck_uimm15_iRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                     rangeCheck_uimm15_iRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                              compU_reg_regNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              compU_reg_regNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                           compU_reg_uimm16Node::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                           compU_reg_uimm16Node::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                       zeroCheckN_iReg_imm0Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                       zeroCheckN_iReg_imm0Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                               cmpN_reg_regNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                               cmpN_reg_regNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                              cmpN_reg_imm0Node::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              cmpN_reg_imm0Node::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                        zeroCheckP_reg_imm0Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                        zeroCheckP_reg_imm0Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                               cmpP_reg_regNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                               cmpP_reg_regNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                              cmpP_reg_nullNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              cmpP_reg_nullNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                             cmpP_reg_imm16Node::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                             cmpP_reg_imm16Node::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                      cmpFUnordered_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      cmpFUnordered_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              cmov_bns_lessNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              cmov_bns_lessNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      cmpDUnordered_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      cmpDUnordered_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     branchNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     branchNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  branchConNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  branchConNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               branchConFarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               branchConFarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             branchConSchedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             branchConSchedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              branchLoopEndNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              branchLoopEndNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           branchLoopEndFarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           branchLoopEndFarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         branchLoopEndSchedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         branchLoopEndSchedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        partialSubtypeCheckNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        partialSubtypeCheckNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                cmpFastLockNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                                cmpFastLockNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                             cmpFastLock_tmNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                             cmpFastLock_tmNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                              cmpFastUnlockNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              cmpFastUnlockNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                           cmpFastUnlock_tmNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                           cmpFastUnlock_tmNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                                 align_addrNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 align_addrNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 array_sizeNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 array_sizeNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  inlineCallClearArrayShortNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  inlineCallClearArrayShortNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  inlineCallClearArrayLargeNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  inlineCallClearArrayLargeNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       inlineCallClearArrayNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       inlineCallClearArrayNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            string_compareLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            string_compareLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            string_compareUNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            string_compareUNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           string_compareLUNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           string_compareLUNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           string_compareULNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           string_compareULNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             string_equalsLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             string_equalsLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             string_equalsUNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             string_equalsUNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              array_equalsBNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              array_equalsBNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              array_equalsCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              array_equalsCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        indexOf_imm1_char_UNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                        indexOf_imm1_char_UNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                        indexOf_imm1_char_LNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                        indexOf_imm1_char_LNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                       indexOf_imm1_char_ULNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                       indexOf_imm1_char_ULNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                             indexOf_imm1_UNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                             indexOf_imm1_UNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                             indexOf_imm1_LNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                             indexOf_imm1_LNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                            indexOf_imm1_ULNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                            indexOf_imm1_ULNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                              indexOfChar_UNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              indexOfChar_UNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                              indexOf_imm_UNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              indexOf_imm_UNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                              indexOf_imm_LNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                              indexOf_imm_LNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                             indexOf_imm_ULNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                             indexOf_imm_ULNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                                  indexOf_UNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                                  indexOf_UNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                                  indexOf_LNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                                  indexOf_LNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                                 indexOf_ULNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                                 indexOf_ULNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                            string_compressNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            string_compressNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             string_inflateNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             string_inflateNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              has_negativesNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              has_negativesNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           encode_iso_arrayNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           encode_iso_arrayNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          minI_reg_reg_iselNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          minI_reg_reg_iselNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          maxI_reg_reg_iselNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          maxI_reg_reg_iselNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  popCountINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  popCountINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  popCountLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  popCountLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         countLeadingZerosINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         countLeadingZerosINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         countLeadingZerosLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         countLeadingZerosLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         countLeadingZerosPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         countLeadingZerosPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   insrwi_aNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   insrwi_aNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     insrwiNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     insrwiNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             loadI_reversedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             loadI_reversedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             loadL_reversedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             loadL_reversedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            loadUS_reversedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            loadUS_reversedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             loadS_reversedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             loadS_reversedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            storeI_reversedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            storeI_reversedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            storeL_reversedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            storeL_reversedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           storeUS_reversedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           storeUS_reversedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            storeS_reversedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            storeS_reversedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                    mtvsrwzNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    mtvsrwzNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                    xxspltwNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    xxspltwNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     repl32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     repl32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     repl48Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     repl48Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     repl56Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     repl56Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               repl8B_immI0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               repl8B_immI0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          repl8B_immIminus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          repl8B_immIminus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              repl16B_immI0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              repl16B_immI0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                         repl16B_immIminus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         repl16B_immIminus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               repl4S_immI0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               repl4S_immI0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          repl4S_immIminus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          repl4S_immIminus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               repl8S_immI0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               repl8S_immI0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          repl8S_immIminus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          repl8S_immIminus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               repl2I_immI0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               repl2I_immI0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          repl2I_immIminus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          repl2I_immIminus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               repl4I_immI0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               repl4I_immI0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          repl4I_immIminus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          repl4I_immIminus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               repl2F_immF0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               repl2F_immF0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       overflowAddL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       overflowAddL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       overflowSubL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       overflowSubL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           overflowNegL_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           overflowNegL_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       overflowMulL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       overflowMulL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               repl4F_immF0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               repl4F_immF0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               repl2D_immI0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               repl2D_immI0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          repl2D_immIminus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          repl2D_immIminus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     mtvsrdNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     mtvsrdNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                    xxspltdNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    xxspltdNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   xxpermdiNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   xxpermdiNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                               repl2L_immI0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                               repl2L_immI0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          repl2L_immIminus1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          repl2L_immIminus1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             safePoint_pollNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             safePoint_pollNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       CallStaticJavaDirectNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                       CallStaticJavaDirectNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                 CallDynamicJavaDirectSchedNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                 CallDynamicJavaDirectSchedNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                      CallDynamicJavaDirectNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                      CallDynamicJavaDirectNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                          CallRuntimeDirectNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                          CallRuntimeDirectNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                       CallLeafDirect_mtctrNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       CallLeafDirect_mtctrNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             CallLeafDirectNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                             CallLeafDirectNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                             TailCalljmpIndNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                             TailCalljmpIndNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                        RetNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                        RetNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 tailjmpIndNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                 tailjmpIndNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                            CreateExceptionNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                            CreateExceptionNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           RethrowExceptionNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                           RethrowExceptionNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                         ShouldNotReachHereNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                         ShouldNotReachHereNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   tlsLoadPNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                                   tlsLoadPNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                                   endGroupNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   endGroupNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                      fxNopNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      fxNopNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     fpNop0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     fpNop0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     fpNop1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     fpNop1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     brNop0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     brNop0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     brNop1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     brNop1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     brNop2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     brNop2Node::pipeline() const { return (&pipeline_class_001); }
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
