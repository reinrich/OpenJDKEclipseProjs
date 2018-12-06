#line 1 "ad_s390_pipeline.cpp"
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

//------------------Pipeline Methods-----------------------------------------
#ifndef PRODUCT
const char * Pipeline::stageName(uint s) {
  static const char * const _stage_names[] = {
    "undefined", "Z_IF", "Z_IC", "Z_D0", "Z_D1", "Z_D2", "Z_D3", "Z_Xfer1", "Z_GD", "Z_MP", "Z_ISS", "Z_RF", "Z_EX1", "Z_EX2", "Z_EX3", "Z_EX4", "Z_EX5", "Z_EX6", "Z_WB", "Z_Xfer2", "Z_CP"
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
      uint min_delay = 12;
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
  Pipeline_Use_Element(0, 0, 0, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 1, 1, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 2, 2, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 3, 3, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 4, 4, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 5, 5, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 6, 6, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 7, 7, false, Pipeline_Use_Cycle_Mask(0))
};

const Pipeline_Use Pipeline_Use::elaborated_use(0, 0, 8, (Pipeline_Use_Element *)&elaborated_elements[0]);


// Pipeline Class "pipe_class_dummy"
static const enum machPipelineStages pipeline_res_stages_001[8] = {
  stage_undefined, // Z_BR
  stage_undefined, // Z_CR
  stage_undefined, // Z_FX1
  stage_undefined, // Z_FX2
  stage_undefined, // Z_LDST1
  stage_undefined, // Z_LDST2
  stage_undefined, // Z_FP1
  stage_undefined  // Z_FP2
};

static const uint pipeline_res_cycles_001[8] = {
  0, // Z_BR
  0, // Z_CR
  0, // Z_FX1
  0, // Z_FX2
  0, // Z_LDST1
  0, // Z_LDST2
  0, // Z_FP1
  0  // Z_FP2
};

static const Pipeline pipeline_class_001((uint)stage_undefined, 0, true, 4, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x00, 0x00, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_trap"
static const Pipeline pipeline_class_002((uint)stage_undefined, 0, false, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x00, 0x00, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_fx_reg_reg"
static const enum machPipelineStages pipeline_reads_001[2] = {
  stage_Z_RF,
  stage_Z_RF 
};

static const enum machPipelineStages pipeline_res_stages_002[8] = {
  stage_undefined, // Z_BR
  stage_undefined, // Z_CR
  stage_Z_RF,      // Z_FX1
  stage_Z_RF,      // Z_FX2
  stage_undefined, // Z_LDST1
  stage_undefined, // Z_LDST2
  stage_undefined, // Z_FP1
  stage_undefined  // Z_FP2
};

static const uint pipeline_res_cycles_002[8] = {
  0, // Z_BR
  0, // Z_CR
  1, // Z_FX1
  1, // Z_FX2
  0, // Z_LDST1
  0, // Z_LDST2
  0, // Z_FP1
  0  // Z_FP2
};

static const Pipeline_Use_Element pipeline_res_mask_002[1] = {
  Pipeline_Use_Element(0x0c,  2,  3, true,  Pipeline_Use_Cycle_Mask(0x00000200)) 
};

static const Pipeline pipeline_class_003((uint)stage_Z_EX1, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_001,
   (enum machPipelineStages * const) pipeline_res_stages_002,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x0c, 0x00, 1, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "pipe_class_ldst"
static const enum machPipelineStages pipeline_reads_002[1] = {
  stage_Z_RF 
};

static const enum machPipelineStages pipeline_res_stages_003[8] = {
  stage_undefined, // Z_BR
  stage_undefined, // Z_CR
  stage_undefined, // Z_FX1
  stage_undefined, // Z_FX2
  stage_Z_RF,      // Z_LDST1
  stage_Z_RF,      // Z_LDST2
  stage_undefined, // Z_FP1
  stage_undefined  // Z_FP2
};

static const uint pipeline_res_cycles_003[8] = {
  0, // Z_BR
  0, // Z_CR
  0, // Z_FX1
  0, // Z_FX2
  1, // Z_LDST1
  1, // Z_LDST2
  0, // Z_FP1
  0  // Z_FP2
};

static const Pipeline_Use_Element pipeline_res_mask_003[1] = {
  Pipeline_Use_Element(0x30,  4,  5, true,  Pipeline_Use_Cycle_Mask(0x00000200)) 
};

static const Pipeline pipeline_class_004((uint)stage_Z_WB, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x30, 0x00, 1, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

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
void Bundle::initialize_nops(MachNode * nop_list[0]) {
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

  static const char *resource_names[8] = { "Z_BR", "Z_CR", "Z_FX1", "Z_FX2", "Z_LDST1", "Z_LDST2", "Z_FP1", "Z_FP2" };

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
const Pipeline *                         Node::pipeline_class() { return (&pipeline_class_Zero_Instructions); }
const Pipeline *                         Node::pipeline() const { return (&pipeline_class_Zero_Instructions); }

const Pipeline *                     MachNode::pipeline_class() { return (&pipeline_class_Unknown_Instructions); }
const Pipeline *                     MachNode::pipeline() const { return pipeline_class(); }

const Pipeline * MachNopNode::pipeline() const { return (&pipeline_class_001); }


const Pipeline *                 stkI_to_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 stkI_to_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 regI_to_stkINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 regI_to_stkINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 stkL_to_regLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 stkL_to_regLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 regL_to_stkLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 regL_to_stkLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 stkP_to_regPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 stkP_to_regPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 regP_to_stkPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 regP_to_stkPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 stkF_to_regFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 stkF_to_regFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 regF_to_stkFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 regF_to_stkFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 stkD_to_regDNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 stkD_to_regDNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 regD_to_stkDNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 regD_to_stkDNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        loadBNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        loadBNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      loadB2LNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      loadB2LNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       loadUBNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       loadUBNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     loadUB2LNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     loadUB2LNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        loadSNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        loadSNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      loadS2LNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      loadS2LNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       loadUSNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       loadUSNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     loadUS2LNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     loadUS2LNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        loadINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        loadINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      loadI2LNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      loadI2LNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     loadUI2LNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     loadUI2LNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    loadRangeNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    loadRangeNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        loadLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        loadLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              loadL_unalignedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              loadL_unalignedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        loadPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        loadPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                castP2X_loadPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                castP2X_loadPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    loadKlassNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    loadKlassNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      loadTOCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      loadTOCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        loadFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        loadFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        loadDNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        loadDNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              loadD_unalignedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              loadD_unalignedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     loadConINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     loadConINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   loadConI16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   loadConI16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   loadConI_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   loadConI_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  loadConUI16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  loadConUI16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            loadConL_pcrelTOCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            loadConL_pcrelTOCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   loadConL32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   loadConL32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   loadConL16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   loadConL16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   loadConL_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   loadConL_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            loadConP_pcrelTOCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            loadConP_pcrelTOCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    loadConP0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    loadConP0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              loadConF_dynTOCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              loadConF_dynTOCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              loadConD_dynTOCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              loadConD_dynTOCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    loadConF0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    loadConF0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    loadConD0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    loadConD0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       storeBNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       storeBNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      storeCMNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      storeCMNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       storeCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       storeCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       storeINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       storeINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       storeLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       storeLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       storePNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       storePNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       storeFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       storeFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       storeDNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       storeDNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                prefetchAllocNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                prefetchAllocNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     memInitBNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     memInitBNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     memInitCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     memInitCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     memInitINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     memInitINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     memInitLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     memInitLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     memInitPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     memInitPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 negL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 negL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                        loadNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                        loadNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   loadNKlassNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   loadNKlassNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     loadConNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     loadConNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    loadConN0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    loadConN0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                loadConNKlassNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                loadConNKlassNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  decodeLoadNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  decodeLoadNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             decodeLoadNKlassNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             decodeLoadNKlassNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          decodeLoadConNKlassNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          decodeLoadConNKlassNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      decodeNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      decodeNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  decodeKlassNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  decodeKlassNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   decodeN_NNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   decodeN_NNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     loadBaseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     loadBaseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 decodeN_baseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 decodeN_baseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              decodeN_NN_baseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              decodeN_NN_baseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      encodePNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      encodePNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  encodeKlassNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  encodeKlassNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   encodeP_NNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   encodeP_NNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 encodeP_baseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 encodeP_baseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              encodeP_NN_baseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              encodeP_NN_baseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       storeNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       storeNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  storeNKlassNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  storeNKlassNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  compN_iRegNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  compN_iRegNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             compN_iRegN_immNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             compN_iRegN_immNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *        compNKlass_iRegN_immNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *        compNKlass_iRegN_immNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            compN_iRegN_immN0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            compN_iRegN_immN0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               membar_acquireNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               membar_acquireNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             membar_acquire_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             membar_acquire_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          membar_acquire_lockNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          membar_acquire_lockNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               membar_releaseNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               membar_releaseNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             membar_release_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             membar_release_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          membar_release_lockNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          membar_release_lockNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              membar_volatileNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              membar_volatileNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *  unnecessary_membar_volatileNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *  unnecessary_membar_volatileNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              membar_CPUOrderNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              membar_CPUOrderNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            membar_storestoreNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            membar_storestoreNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              roundDouble_nopNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              roundDouble_nopNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               roundFloat_nopNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               roundFloat_nopNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      castX2PNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      castX2PNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      castP2XNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      castP2XNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       stfSSDNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       stfSSDNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       stfSSFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       stfSSFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmovN_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmovN_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmovN_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmovN_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmovI_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmovI_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmovI_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmovI_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmovP_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmovP_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmovP_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmovP_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmovF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmovF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmovD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmovD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmovL_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmovL_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmovL_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmovL_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     tlsLoadPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     tlsLoadPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  checkCastPPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  checkCastPPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       castPPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       castPPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       castIINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       castIINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  loadPLockedNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  loadPLockedNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            storePConditionalNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            storePConditionalNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            storeLConditionalNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            storeLConditionalNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         compareAndSwapI_boolNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         compareAndSwapI_boolNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         compareAndSwapL_boolNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         compareAndSwapL_boolNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         compareAndSwapP_boolNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         compareAndSwapP_boolNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         compareAndSwapN_boolNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         compareAndSwapN_boolNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *  addI_mem_imm8_atomic_no_resNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *  addI_mem_imm8_atomic_no_resNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *        addI_mem_imm16_atomicNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *        addI_mem_imm16_atomicNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *        addI_mem_imm32_atomicNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *        addI_mem_imm32_atomicNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          addI_mem_reg_atomicNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          addI_mem_reg_atomicNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *  addL_mem_imm8_atomic_no_resNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *  addL_mem_imm8_atomic_no_resNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *        addL_mem_imm16_atomicNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *        addL_mem_imm16_atomicNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *        addL_mem_imm32_atomicNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *        addL_mem_imm32_atomicNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          addL_mem_reg_atomicNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          addL_mem_reg_atomicNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     addI_mem_reg_atomic_z196Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     addI_mem_reg_atomic_z196Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     addL_mem_reg_atomic_z196Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     addL_mem_reg_atomic_z196Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                xchgI_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                xchgI_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                xchgL_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                xchgL_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                xchgN_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                xchgN_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                xchgP_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                xchgP_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            addI_reg_reg_CISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            addI_reg_reg_CISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            addI_reg_reg_RISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            addI_reg_reg_RISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          addI_reg_imm16_CISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          addI_reg_imm16_CISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          addI_reg_imm16_RISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          addI_reg_imm16_RISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addI_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addI_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addI_reg_imm12Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addI_reg_imm12Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addI_reg_imm20Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addI_reg_imm20Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           addI_reg_reg_imm12Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           addI_reg_reg_imm12Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           addI_reg_reg_imm20Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           addI_reg_reg_imm20Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 addI_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 addI_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addI_Reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addI_Reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 addI_mem_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 addI_mem_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                addL_reg_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                addL_reg_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              addL_reg_regI_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              addL_reg_regI_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            addL_reg_reg_CISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            addL_reg_reg_CISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            addL_reg_reg_RISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            addL_reg_reg_RISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addL_reg_imm12Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addL_reg_imm12Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addL_reg_imm20Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addL_reg_imm20Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addL_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addL_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          addL_reg_imm16_CISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          addL_reg_imm16_CISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          addL_reg_imm16_RISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          addL_reg_imm16_RISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                addL_Reg_memINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                addL_Reg_memINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              addL_Reg_memI_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              addL_Reg_memI_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 addL_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 addL_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addL_Reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addL_Reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           addL_reg_reg_imm12Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           addL_reg_reg_imm12Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           addL_reg_reg_imm20Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           addL_reg_reg_imm20Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 addL_mem_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 addL_mem_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              addP_reg_reg_LANode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              addP_reg_reg_LANode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            addP_reg_reg_CISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            addP_reg_reg_CISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            addP_reg_reg_RISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            addP_reg_reg_RISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addP_reg_imm12Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addP_reg_imm12Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          addP_reg_imm16_CISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          addP_reg_imm16_CISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          addP_reg_imm16_RISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          addP_reg_imm16_RISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addP_reg_imm20Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addP_reg_imm20Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addP_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addP_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           addP_reg_reg_imm12Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           addP_reg_reg_imm12Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          addP_regN_reg_imm12Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          addP_regN_reg_imm12Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           addP_reg_reg_imm20Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           addP_reg_reg_imm20Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          addP_regN_reg_imm20Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          addP_regN_reg_imm20Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 addP_mem_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 addP_mem_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            subI_reg_reg_CISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            subI_reg_reg_CISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            subI_reg_reg_RISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            subI_reg_reg_RISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 subI_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 subI_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                subI_zero_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                subI_zero_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            subL_reg_reg_CISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            subL_reg_reg_CISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            subL_reg_reg_RISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            subL_reg_reg_RISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           subL_reg_regI_CISCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           subL_reg_regI_CISCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                subL_Reg_memINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                subL_Reg_memINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 subL_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 subL_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 mulI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 mulI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               mulI_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               mulI_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               mulI_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               mulI_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 mulI_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 mulI_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               mulI_Reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               mulI_Reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                mulL_reg_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                mulL_reg_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              mulL_reg_regI_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              mulL_reg_regI_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 mulL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 mulL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               mulL_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               mulL_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               mulL_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               mulL_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                mulL_Reg_memINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                mulL_Reg_memINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              mulL_Reg_memI_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              mulL_Reg_memI_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 mulL_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 mulL_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               mulL_Reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               mulL_Reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               mulHiL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               mulHiL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           divModI_reg_divmodNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           divModI_reg_divmodNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 divI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 divI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               divI_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               divI_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           divModL_reg_divmodNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           divModL_reg_divmodNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 divL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 divL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               divL_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               divL_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 modI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 modI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               modI_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               modI_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 modL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 modL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               modL_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               modL_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 sllI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 sllI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 sllI_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 sllI_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               sllI_reg_imm_1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               sllI_reg_imm_1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 sllL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 sllL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 sllL_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 sllL_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               sllL_reg_imm_1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               sllL_reg_imm_1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 sraI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 sraI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 sraI_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 sraI_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 sraL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 sraL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 sraL_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 sraL_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 srlI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 srlI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 srlI_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 srlI_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 srlL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 srlL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 srlL_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 srlL_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 srlP_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 srlP_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              rotlI_reg_immI8Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              rotlI_reg_immI8Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            rotlI_reg_immI8_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            rotlI_reg_immI8_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              rotlL_reg_immI8Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              rotlL_reg_immI8Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            rotlL_reg_immI8_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            rotlL_reg_immI8_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              rotrI_reg_immI8Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              rotrI_reg_immI8Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            rotrI_reg_immI8_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            rotrI_reg_immI8_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              rotrL_reg_immI8Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              rotrL_reg_immI8Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            rotrL_reg_immI8_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            rotrL_reg_immI8_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         overflowAddI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         overflowAddI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         overflowAddI_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         overflowAddI_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         overflowAddL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         overflowAddL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         overflowAddL_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         overflowAddL_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         overflowSubI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         overflowSubI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         overflowSubI_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         overflowSubI_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         overflowSubL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         overflowSubL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         overflowSubL_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         overflowSubL_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            overflowNegI_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            overflowNegI_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            overflowNegL_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            overflowNegL_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 addF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 addF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 addF_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 addF_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addF_reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addF_reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 addD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 addD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 addD_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 addD_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               addD_reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               addD_reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 subF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 subF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 subF_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 subF_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 subD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 subD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 subD_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 subD_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 mulF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 mulF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 mulF_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 mulF_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               mulF_reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               mulF_reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 mulD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 mulD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 mulD_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 mulD_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               mulD_reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               mulD_reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                maddF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                maddF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                maddD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                maddD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                msubF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                msubF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                msubD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                msubD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                maddF_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                maddF_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                maddD_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                maddD_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                msubF_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                msubF_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                msubD_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                msubD_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                maddF_mem_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                maddF_mem_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                maddD_mem_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                maddD_mem_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                msubF_mem_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                msubF_mem_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                msubD_mem_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                msubD_mem_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 divF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 divF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 divF_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 divF_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 divD_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 divD_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 divD_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 divD_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     absF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     absF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     absD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     absD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    nabsF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    nabsF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    nabsD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    nabsD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     negF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     negF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     negD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     negD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    sqrtF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    sqrtF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    sqrtD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    sqrtD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    sqrtF_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    sqrtF_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    sqrtD_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    sqrtD_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 andI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 andI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 andI_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 andI_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               andI_Reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               andI_Reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              andI_reg_uimm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              andI_reg_uimm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           andI_reg_uimmI_LH1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           andI_reg_uimmI_LH1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           andI_reg_uimmI_LL1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           andI_reg_uimmI_LL1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 andL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 andL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 andL_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 andL_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               andL_Reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               andL_Reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           andL_reg_uimmL_LL1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           andL_reg_uimmL_LL1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           andL_reg_uimmL_LH1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           andL_reg_uimmL_LH1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           andL_reg_uimmL_HL1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           andL_reg_uimmL_HL1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           andL_reg_uimmL_HH1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           andL_reg_uimmL_HH1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  orI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  orI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  orI_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  orI_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                orI_Reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                orI_Reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               orI_reg_uimm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               orI_reg_uimm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               orI_reg_uimm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               orI_reg_uimm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  orL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  orL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  orL_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  orL_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                orL_Reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                orL_Reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               orL_reg_uimm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               orL_reg_uimm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               orL_reg_uimm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               orL_reg_uimm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 xorI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 xorI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 xorI_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 xorI_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               xorI_Reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               xorI_Reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              xorI_reg_uimm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              xorI_reg_uimm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 xorL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 xorL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 xorL_Reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 xorL_Reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               xorL_Reg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               xorL_Reg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              xorL_reg_uimm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              xorL_reg_uimm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      convI2BNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      convI2BNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      convP2BNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      convP2BNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            cmpLTMask_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            cmpLTMask_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           cmpLTMask_reg_zeroNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           cmpLTMask_reg_zeroNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convD2F_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convD2F_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convF2I_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convF2I_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convD2I_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convD2I_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convF2L_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convF2L_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convD2L_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convD2L_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convF2D_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convF2D_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convF2D_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convF2D_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convI2D_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convI2D_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 convI2F_iregNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 convI2F_iregNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convI2L_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convI2L_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              convI2L_reg_zexNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              convI2L_reg_zexNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              convI2L_mem_zexNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              convI2L_mem_zexNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              zeroExtend_longNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              zeroExtend_longNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *      rShiftI16_lShiftI16_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *      rShiftI16_lShiftI16_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *      rShiftI24_lShiftI24_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *      rShiftI24_lShiftI24_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            MoveF2I_stack_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            MoveF2I_stack_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            MoveI2F_stack_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            MoveI2F_stack_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            MoveD2L_stack_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            MoveD2L_stack_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            MoveL2D_stack_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            MoveL2D_stack_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            MoveI2F_reg_stackNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            MoveI2F_reg_stackNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            MoveD2L_reg_stackNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            MoveD2L_reg_stackNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            MoveL2D_reg_stackNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            MoveL2D_reg_stackNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convL2F_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convL2F_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convL2D_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convL2D_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  convL2I_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  convL2I_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            shrL_reg_imm6_L2INode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            shrL_reg_imm6_L2INode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *      rangeCheck_iReg_uimmI16Node::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *      rangeCheck_iReg_uimmI16Node::pipeline() const { return (&pipeline_class_002); }

const Pipeline *         rangeCheck_iReg_iRegNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *         rangeCheck_iReg_iRegNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *      rangeCheck_uimmI16_iRegNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *      rangeCheck_uimmI16_iRegNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *         zeroCheckP_iReg_imm0Node::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *         zeroCheckP_iReg_imm0Node::pipeline() const { return (&pipeline_class_002); }

const Pipeline *         zeroCheckN_iReg_imm0Node::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *         zeroCheckN_iReg_imm0Node::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                compI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                compI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                compI_reg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                compI_reg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              compI_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              compI_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               compI_reg_imm0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               compI_reg_imm0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                compI_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                compI_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                compU_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                compU_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               compU_reg_uimmNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               compU_reg_uimmNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                compU_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                compU_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                compL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                compL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               compL_reg_regINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               compL_reg_regINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              compL_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              compL_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              compL_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              compL_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               compL_reg_imm0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               compL_reg_imm0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          compL_conv_reg_imm0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          compL_conv_reg_imm0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                compL_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                compL_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               compL_reg_memINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               compL_reg_memINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               compUL_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               compUL_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             compUL_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             compUL_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                compP_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                compP_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               compP_reg_imm0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               compP_reg_imm0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *        compP_decode_reg_imm0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *        compP_decode_reg_imm0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                compP_reg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                compP_reg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            z196_minI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            z196_minI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             z10_minI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             z10_minI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 minI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 minI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          z196_minI_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          z196_minI_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               minI_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               minI_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          z196_minI_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          z196_minI_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               minI_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               minI_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            z10_minI_reg_imm8Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            z10_minI_reg_imm8Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            z196_maxI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            z196_maxI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             z10_maxI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             z10_maxI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 maxI_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 maxI_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          z196_maxI_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          z196_maxI_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               maxI_reg_imm32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               maxI_reg_imm32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          z196_maxI_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          z196_maxI_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               maxI_reg_imm16Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               maxI_reg_imm16Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            z10_maxI_reg_imm8Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            z10_maxI_reg_imm8Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     absI_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     absI_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  negabsI_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  negabsI_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      cmpF_ccNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      cmpF_ccNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      cmpD_ccNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      cmpD_ccNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  cmpF_cc_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  cmpF_cc_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  cmpD_cc_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  cmpD_cc_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     cmpF0_ccNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     cmpF0_ccNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     cmpD0_ccNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     cmpD0_ccNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     cmpF_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     cmpF_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     cmpD_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     cmpD_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       branchNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       branchNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    branchFarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    branchFarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    branchConNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    branchConNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 branchConFarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 branchConFarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                branchLoopEndNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                branchLoopEndNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             branchLoopEndFarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             branchLoopEndFarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     testAndBranchLoopEnd_RegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     testAndBranchLoopEnd_RegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmpb_RegINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmpb_RegINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   cmpbU_RegINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   cmpbU_RegINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    cmpb_RegLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    cmpb_RegLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   cmpb_RegPPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   cmpb_RegPPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   cmpb_RegNNNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   cmpb_RegNNNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *     testAndBranchLoopEnd_ImmNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *     testAndBranchLoopEnd_ImmNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                cmpb_RegI_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                cmpb_RegI_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               cmpbU_RegI_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               cmpbU_RegI_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                cmpb_RegL_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                cmpb_RegL_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               cmpb_RegP_immPNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               cmpb_RegP_immPNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              cmpb_RegN_immP0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              cmpb_RegN_immP0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                cmpb_RegN_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                cmpb_RegN_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *  testAndBranchLoopEnd_RegFarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *  testAndBranchLoopEnd_RegFarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                cmpb_RegI_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                cmpb_RegI_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               cmpbU_RegI_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               cmpbU_RegI_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                cmpb_RegL_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                cmpb_RegL_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               cmpb_RegPP_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               cmpb_RegPP_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               cmpb_RegNN_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               cmpb_RegNN_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *  testAndBranchLoopEnd_ImmFarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *  testAndBranchLoopEnd_ImmFarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            cmpb_RegI_imm_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            cmpb_RegI_imm_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           cmpbU_RegI_imm_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           cmpbU_RegI_imm_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            cmpb_RegL_imm_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            cmpb_RegL_imm_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           cmpb_RegP_immP_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           cmpb_RegP_immP_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          cmpb_RegN_immP0_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          cmpb_RegN_immP0_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           cmpb_RegN_immN_FarNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           cmpb_RegN_immN_FarNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                cmpL3_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                cmpL3_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    safePointNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    safePointNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               safePoint_pollNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               safePoint_pollNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *  CallStaticJavaDirect_dynTOCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *  CallStaticJavaDirect_dynTOCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline * CallDynamicJavaDirect_dynTOCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline * CallDynamicJavaDirect_dynTOCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            CallRuntimeDirectNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            CallRuntimeDirectNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               CallLeafDirectNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               CallLeafDirectNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           CallLeafNoFPDirectNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           CallLeafNoFPDirectNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               TailCalljmpIndNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               TailCalljmpIndNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                          RetNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                          RetNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   tailjmpIndNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   tailjmpIndNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              CreateExceptionNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              CreateExceptionNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             RethrowExceptionNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             RethrowExceptionNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           ShouldNotReachHereNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           ShouldNotReachHereNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          partialSubtypeCheckNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          partialSubtypeCheckNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *  partialSubtypeCheck_vs_zeroNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *  partialSubtypeCheck_vs_zeroNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  cmpFastLockNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  cmpFastLockNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                cmpFastUnlockNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                cmpFastUnlockNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *    inlineCallClearArrayConstNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *    inlineCallClearArrayConstNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline * inlineCallClearArrayConstBigNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline * inlineCallClearArrayConstBigNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         inlineCallClearArrayNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         inlineCallClearArrayNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               string_equalsLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               string_equalsLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               string_equalsUNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               string_equalsUNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            string_equals_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            string_equals_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           string_equalsC_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           string_equalsC_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                array_equalsBNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                array_equalsBNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                array_equalsCNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                array_equalsCNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              string_compareLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              string_compareLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              string_compareUNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              string_compareUNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             string_compareLUNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             string_compareLUNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             string_compareULNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             string_compareULNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                indexOfChar_UNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                indexOfChar_UNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               indexOf_imm1_UNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               indexOf_imm1_UNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               indexOf_imm1_LNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               indexOf_imm1_LNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              indexOf_imm1_ULNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              indexOf_imm1_ULNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                indexOf_imm_UNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                indexOf_imm_UNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                indexOf_imm_LNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                indexOf_imm_LNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               indexOf_imm_ULNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               indexOf_imm_ULNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    indexOf_UNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    indexOf_UNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    indexOf_LNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    indexOf_LNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   indexOf_ULNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   indexOf_ULNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *              string_compressNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *              string_compressNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *               string_inflateNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *               string_inflateNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *         string_inflate_constNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *         string_inflate_constNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                has_negativesNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                has_negativesNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             encode_iso_arrayNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             encode_iso_arrayNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                expand_storeFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                expand_storeFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *       expand_LoadLogical_I2LNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *       expand_LoadLogical_I2LNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            expand_Repl2I_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            expand_Repl2I_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             Repl8B_reg_risbgNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             Repl8B_reg_risbgNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   Repl8B_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   Repl8B_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  Repl8B_imm0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  Repl8B_imm0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 Repl8B_immm1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 Repl8B_immm1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             Repl4S_reg_risbgNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             Repl4S_reg_risbgNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   Repl4S_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   Repl4S_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  Repl4S_imm0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  Repl4S_imm0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 Repl4S_immm1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 Repl4S_immm1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *             Repl2I_reg_risbgNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *             Repl2I_reg_risbgNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   Repl2I_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   Repl2I_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  Repl2I_imm0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  Repl2I_imm0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                 Repl2I_immm1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                 Repl2I_immm1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            Repl2F_reg_directNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            Repl2F_reg_directNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                   Repl2F_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                   Repl2F_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                  Repl2F_imm0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                  Repl2F_imm0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                     storeA8BNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                     storeA8BNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                       loadV8Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                       loadV8Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *            bytes_reverse_intNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *            bytes_reverse_intNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           bytes_reverse_longNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           bytes_reverse_longNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           countLeadingZerosINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           countLeadingZerosINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *           countLeadingZerosLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *           countLeadingZerosLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          countTrailingZerosINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          countTrailingZerosINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *          countTrailingZerosLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *          countTrailingZerosLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    popCountINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    popCountINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                    popCountLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                    popCountLNode::pipeline() const { return (&pipeline_class_001); }
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
