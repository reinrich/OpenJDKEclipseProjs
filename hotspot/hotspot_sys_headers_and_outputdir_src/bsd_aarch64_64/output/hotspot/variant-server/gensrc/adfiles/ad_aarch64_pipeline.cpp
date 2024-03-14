#line 1 "ad_aarch64_pipeline.cpp"
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

//------------------Pipeline Methods-----------------------------------------
#ifndef PRODUCT
const char * Pipeline::stageName(uint s) {
  static const char * const _stage_names[] = {
    "undefined", "S0", "S1", "S2", "S3", "S4", "S5"
  };

  return (s <= 6 ? _stage_names[s] : "???");
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
      uint min_delay = 7;
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

  assert(pred, "null predecessor pipline info");

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

static const Pipeline pipeline_class_Zero_Instructions(0, 0, true, 0, 0, false, false, false, false, nullptr, nullptr, nullptr, Pipeline_Use(0, 0, 0, nullptr));

static const Pipeline pipeline_class_Unknown_Instructions(0, 0, true, 0, 0, false, true, true, false, nullptr, nullptr, nullptr, Pipeline_Use(0, 0, 0, nullptr));

const Pipeline_Use_Element Pipeline_Use::elaborated_elements[9] = {
  Pipeline_Use_Element(0, 0, 0, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 1, 1, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 2, 2, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 3, 3, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 4, 4, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 5, 5, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 6, 6, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 7, 7, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 8, 8, false, Pipeline_Use_Cycle_Mask(0))
};

const Pipeline_Use Pipeline_Use::elaborated_use(0, 0, 9, (Pipeline_Use_Element *)&elaborated_elements[0]);


// Pipeline Class "fp_dop_reg_reg_s"
static const enum machPipelineStages pipeline_reads_001[2] = {
  stage_S1,
  stage_S2 
};

static const enum machPipelineStages pipeline_res_stages_001[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined, // BRANCH
  stage_undefined, // LDST
  stage_S5         // NEON_FP
};

static const uint pipeline_res_cycles_001[9] = {
  1, // INS0
  1, // INS1
  0, // ALU0
  0, // ALU1
  0, // MAC
  0, // DIV
  0, // BRANCH
  0, // LDST
  1  // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_001[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000010)) 
};

static const Pipeline pipeline_class_001((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_dop_reg_reg_d"
static const Pipeline pipeline_class_002((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_uop_s"
static const enum machPipelineStages pipeline_reads_002[1] = {
  stage_S1 
};

static const Pipeline pipeline_class_003((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_uop_d"
static const Pipeline pipeline_class_004((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_d2f"
static const Pipeline pipeline_class_005((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_f2d"
static const Pipeline pipeline_class_006((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_f2i"
static const Pipeline pipeline_class_007((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_f2l"
static const Pipeline pipeline_class_008((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_i2f"
static const Pipeline pipeline_class_009((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_l2f"
static const Pipeline pipeline_class_010((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_d2i"
static const Pipeline pipeline_class_011((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_d2l"
static const Pipeline pipeline_class_012((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_i2d"
static const Pipeline pipeline_class_013((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_l2d"
static const Pipeline pipeline_class_014((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_div_s"
static const enum machPipelineStages pipeline_res_stages_002[9] = {
  stage_S0,        // INS0
  stage_undefined, // INS1
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined, // BRANCH
  stage_undefined, // LDST
  stage_S5         // NEON_FP
};

static const uint pipeline_res_cycles_002[9] = {
  1, // INS0
  0, // INS1
  0, // ALU0
  0, // ALU1
  0, // MAC
  0, // DIV
  0, // BRANCH
  0, // LDST
  1  // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_002[2] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000010)) 
};

static const Pipeline pipeline_class_015((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_002,
  (uint *) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "fp_div_d"
static const Pipeline pipeline_class_016((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_002,
  (uint *) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "fp_cond_reg_reg_s"
static const enum machPipelineStages pipeline_reads_003[3] = {
  stage_S1,
  stage_S1,
  stage_S1 
};

static const enum machPipelineStages pipeline_res_stages_003[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined, // BRANCH
  stage_undefined, // LDST
  stage_S3         // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_003[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_017((uint)stage_S3, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_003,
   (enum machPipelineStages *) pipeline_res_stages_003,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "fp_cond_reg_reg_d"
static const Pipeline pipeline_class_018((uint)stage_S3, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_003,
   (enum machPipelineStages *) pipeline_res_stages_003,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "fp_imm_s"
static const Pipeline pipeline_class_019((uint)stage_S3, 0, false, 0, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_003,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "fp_imm_d"
static const Pipeline pipeline_class_020((uint)stage_S3, 0, false, 0, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_003,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "fp_load_constant_s"
static const enum machPipelineStages pipeline_res_stages_004[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined, // BRANCH
  stage_undefined, // LDST
  stage_S4         // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_004[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000008)) 
};

static const Pipeline pipeline_class_021((uint)stage_S4, 0, false, 0, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_004,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_004[0]));

// Pipeline Class "fp_load_constant_d"
static const Pipeline pipeline_class_022((uint)stage_S4, 0, false, 0, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_004,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_004[0]));

// Pipeline Class "ialu_reg_reg"
static const enum machPipelineStages pipeline_reads_004[2] = {
  stage_S1,
  stage_S1 
};

static const enum machPipelineStages pipeline_res_stages_005[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_S2,        // ALU0
  stage_S2,        // ALU1
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined, // BRANCH
  stage_undefined, // LDST
  stage_undefined  // NEON_FP
};

static const uint pipeline_res_cycles_003[9] = {
  1, // INS0
  1, // INS1
  1, // ALU0
  1, // ALU1
  0, // MAC
  0, // DIV
  0, // BRANCH
  0, // LDST
  0  // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_005[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x00c, 2, 3, true,  Pipeline_Use_Cycle_Mask(0x00000002)) 
};

static const Pipeline pipeline_class_023((uint)stage_S2, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_004,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "ialu_reg_reg_shift"
static const enum machPipelineStages pipeline_reads_005[3] = {
  stage_S1,
  stage_S0,
  stage_undefined 
};

static const Pipeline pipeline_class_024((uint)stage_S2, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_005,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "ialu_reg_shift"
static const enum machPipelineStages pipeline_reads_006[1] = {
  stage_S0 
};

static const Pipeline pipeline_class_025((uint)stage_S2, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_006,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "ialu_reg_reg_vshift"
static const enum machPipelineStages pipeline_reads_007[2] = {
  stage_S0,
  stage_S0 
};

static const enum machPipelineStages pipeline_res_stages_006[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_S1,        // ALU0
  stage_S1,        // ALU1
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined, // BRANCH
  stage_undefined, // LDST
  stage_undefined  // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_006[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x00c, 2, 3, true,  Pipeline_Use_Cycle_Mask(0x00000001)) 
};

static const Pipeline pipeline_class_026((uint)stage_S1, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_007,
   (enum machPipelineStages *) pipeline_res_stages_006,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_006[0]));

// Pipeline Class "ialu_reg_reg_extr"
static const enum machPipelineStages pipeline_res_stages_007[9] = {
  stage_undefined, // INS0
  stage_S0,        // INS1
  stage_S1,        // ALU0
  stage_S1,        // ALU1
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined, // BRANCH
  stage_undefined, // LDST
  stage_undefined  // NEON_FP
};

static const uint pipeline_res_cycles_004[9] = {
  0, // INS0
  1, // INS1
  1, // ALU0
  1, // ALU1
  0, // MAC
  0, // DIV
  0, // BRANCH
  0, // LDST
  0  // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_007[2] = {
  Pipeline_Use_Element(0x002, 1, 1, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x00c, 2, 3, true,  Pipeline_Use_Cycle_Mask(0x00000001)) 
};

static const Pipeline pipeline_class_027((uint)stage_S2, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_007,
   (enum machPipelineStages *) pipeline_res_stages_007,
  (uint *) pipeline_res_cycles_004,
  Pipeline_Use(0xe, 0x2, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "ialu_reg"
static const Pipeline pipeline_class_028((uint)stage_S2, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "ialu_reg_imm"
static const Pipeline pipeline_class_029((uint)stage_S2, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "ialu_imm"
static const Pipeline pipeline_class_030((uint)stage_S1, 0, false, 0, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_006,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_006[0]));

// Pipeline Class "icmp_reg_reg"
static const Pipeline pipeline_class_031((uint)stage_S2, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_004,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "icmp_reg_imm"
static const Pipeline pipeline_class_032((uint)stage_S2, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "icond_none"
static const Pipeline pipeline_class_033((uint)stage_S2, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "icond_reg_reg"
static const Pipeline pipeline_class_034((uint)stage_S2, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_003,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "icond_reg"
static const Pipeline pipeline_class_035((uint)stage_S2, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_004,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0xf, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "imul_reg_reg"
static const enum machPipelineStages pipeline_res_stages_008[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_S3,        // MAC
  stage_undefined, // DIV
  stage_undefined, // BRANCH
  stage_undefined, // LDST
  stage_undefined  // NEON_FP
};

static const uint pipeline_res_cycles_005[9] = {
  1, // INS0
  1, // INS1
  0, // ALU0
  0, // ALU1
  1, // MAC
  0, // DIV
  0, // BRANCH
  0, // LDST
  0  // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_008[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x010, 4, 4, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_036((uint)stage_S3, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_007,
   (enum machPipelineStages *) pipeline_res_stages_008,
  (uint *) pipeline_res_cycles_005,
  Pipeline_Use(0x13, 0x10, 2, (Pipeline_Use_Element *)&pipeline_res_mask_008[0]));

// Pipeline Class "imac_reg_reg"
static const enum machPipelineStages pipeline_reads_008[3] = {
  stage_S0,
  stage_S0,
  stage_S0 
};

static const Pipeline pipeline_class_037((uint)stage_S3, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_008,
   (enum machPipelineStages *) pipeline_res_stages_008,
  (uint *) pipeline_res_cycles_005,
  Pipeline_Use(0x13, 0x10, 2, (Pipeline_Use_Element *)&pipeline_res_mask_008[0]));

// Pipeline Class "lmul_reg_reg"
static const Pipeline pipeline_class_038((uint)stage_S3, 2, true, 3, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_007,
   (enum machPipelineStages *) pipeline_res_stages_008,
  (uint *) pipeline_res_cycles_005,
  Pipeline_Use(0x13, 0x10, 2, (Pipeline_Use_Element *)&pipeline_res_mask_008[0]));

// Pipeline Class "lmac_reg_reg"
static const Pipeline pipeline_class_039((uint)stage_S3, 3, true, 3, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_008,
   (enum machPipelineStages *) pipeline_res_stages_008,
  (uint *) pipeline_res_cycles_005,
  Pipeline_Use(0x13, 0x10, 2, (Pipeline_Use_Element *)&pipeline_res_mask_008[0]));

// Pipeline Class "idiv_reg_reg"
static const enum machPipelineStages pipeline_res_stages_009[9] = {
  stage_S0,        // INS0
  stage_undefined, // INS1
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // MAC
  stage_S3,        // DIV
  stage_undefined, // BRANCH
  stage_undefined, // LDST
  stage_undefined  // NEON_FP
};

static const uint pipeline_res_cycles_006[9] = {
  1, // INS0
  0, // INS1
  0, // ALU0
  0, // ALU1
  0, // MAC
  1, // DIV
  0, // BRANCH
  0, // LDST
  0  // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_009[2] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x020, 5, 5, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_040((uint)stage_S3, 2, true, 8, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_007,
   (enum machPipelineStages *) pipeline_res_stages_009,
  (uint *) pipeline_res_cycles_006,
  Pipeline_Use(0x21, 0x21, 2, (Pipeline_Use_Element *)&pipeline_res_mask_009[0]));

// Pipeline Class "ldiv_reg_reg"
static const Pipeline pipeline_class_041((uint)stage_S3, 2, true, 16, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_007,
   (enum machPipelineStages *) pipeline_res_stages_009,
  (uint *) pipeline_res_cycles_006,
  Pipeline_Use(0x21, 0x21, 2, (Pipeline_Use_Element *)&pipeline_res_mask_009[0]));

// Pipeline Class "iload_prefetch"
static const enum machPipelineStages pipeline_res_stages_010[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined, // BRANCH
  stage_S3,        // LDST
  stage_undefined  // NEON_FP
};

static const uint pipeline_res_cycles_007[9] = {
  1, // INS0
  1, // INS1
  0, // ALU0
  0, // ALU1
  0, // MAC
  0, // DIV
  0, // BRANCH
  1, // LDST
  0  // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_010[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_042((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_006,
   (enum machPipelineStages *) pipeline_res_stages_010,
  (uint *) pipeline_res_cycles_007,
  Pipeline_Use(0x83, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "iload_reg_mem"
static const Pipeline pipeline_class_043((uint)stage_S3, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_006,
   (enum machPipelineStages *) pipeline_res_stages_010,
  (uint *) pipeline_res_cycles_007,
  Pipeline_Use(0x83, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "iload_reg_reg"
static const Pipeline pipeline_class_044((uint)stage_S3, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_006,
   (enum machPipelineStages *) pipeline_res_stages_010,
  (uint *) pipeline_res_cycles_007,
  Pipeline_Use(0x83, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "istore_mem"
static const Pipeline pipeline_class_045((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_006,
   (enum machPipelineStages *) pipeline_res_stages_010,
  (uint *) pipeline_res_cycles_007,
  Pipeline_Use(0x83, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "istore_reg_mem"
static const enum machPipelineStages pipeline_reads_009[2] = {
  stage_S2,
  stage_S0 
};

static const Pipeline pipeline_class_046((uint)stage_undefined, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_009,
   (enum machPipelineStages *) pipeline_res_stages_010,
  (uint *) pipeline_res_cycles_007,
  Pipeline_Use(0x83, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "istore_reg_reg"
static const enum machPipelineStages pipeline_reads_010[2] = {
  stage_S0,
  stage_S2 
};

static const Pipeline pipeline_class_047((uint)stage_undefined, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_010,
   (enum machPipelineStages *) pipeline_res_stages_010,
  (uint *) pipeline_res_cycles_007,
  Pipeline_Use(0x83, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "pipe_branch"
static const enum machPipelineStages pipeline_res_stages_011[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_S1,        // BRANCH
  stage_undefined, // LDST
  stage_undefined  // NEON_FP
};

static const uint pipeline_res_cycles_008[9] = {
  1, // INS0
  1, // INS1
  0, // ALU0
  0, // ALU1
  0, // MAC
  0, // DIV
  1, // BRANCH
  0, // LDST
  0  // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_011[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x040, 6, 6, false, Pipeline_Use_Cycle_Mask(0x00000001)) 
};

static const Pipeline pipeline_class_048((uint)stage_undefined, 0, false, 0, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_011,
  (uint *) pipeline_res_cycles_008,
  Pipeline_Use(0x43, 0x40, 2, (Pipeline_Use_Element *)&pipeline_res_mask_011[0]));

// Pipeline Class "pipe_branch_cond"
static const Pipeline pipeline_class_049((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_011,
  (uint *) pipeline_res_cycles_008,
  Pipeline_Use(0x43, 0x40, 2, (Pipeline_Use_Element *)&pipeline_res_mask_011[0]));

// Pipeline Class "pipe_cmp_branch"
static const Pipeline pipeline_class_050((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_011,
  (uint *) pipeline_res_cycles_008,
  Pipeline_Use(0x43, 0x40, 2, (Pipeline_Use_Element *)&pipeline_res_mask_011[0]));

// Pipeline Class "pipe_serial"
static const uint pipeline_res_cycles_009[9] = {
  2, // INS0
  2, // INS1
  0, // ALU0
  0, // ALU1
  0, // MAC
  0, // DIV
  0, // BRANCH
  1, // LDST
  0  // NEON_FP
};

static const Pipeline_Use_Element pipeline_res_mask_012[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000002)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_051((uint)stage_undefined, 0, true, 16, 1, false, false, true, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_010,
  (uint *) pipeline_res_cycles_009,
  Pipeline_Use(0x83, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_012[0]));

// Pipeline Class "pipe_slow"
static const Pipeline pipeline_class_052((uint)stage_undefined, 0, true, 16, 10, false, true, true, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_010,
  (uint *) pipeline_res_cycles_009,
  Pipeline_Use(0x83, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_012[0]));

// Pipeline Class "pipe_class_empty"
static const enum machPipelineStages pipeline_res_stages_012[9] = {
  stage_undefined, // INS0
  stage_undefined, // INS1
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined, // BRANCH
  stage_undefined, // LDST
  stage_undefined  // NEON_FP
};

static const uint pipeline_res_cycles_010[9] = {
  0, // INS0
  0, // INS1
  0, // ALU0
  0, // ALU1
  0, // MAC
  0, // DIV
  0, // BRANCH
  0, // LDST
  0  // NEON_FP
};

static const Pipeline pipeline_class_053((uint)stage_undefined, 0, true, 0, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_012,
  (uint *) pipeline_res_cycles_010,
  Pipeline_Use(0x0, 0x0, 0, (Pipeline_Use_Element *)nullptr));

// Pipeline Class "pipe_class_default"
static const Pipeline pipeline_class_054((uint)stage_undefined, 0, true, 2, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_012,
  (uint *) pipeline_res_cycles_010,
  Pipeline_Use(0x0, 0x0, 0, (Pipeline_Use_Element *)nullptr));

// Pipeline Class "pipe_class_compare"
static const Pipeline pipeline_class_055((uint)stage_undefined, 0, true, 16, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_012,
  (uint *) pipeline_res_cycles_010,
  Pipeline_Use(0x0, 0x0, 0, (Pipeline_Use_Element *)nullptr));

// Pipeline Class "pipe_class_memory"
static const Pipeline pipeline_class_056((uint)stage_undefined, 0, true, 16, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_012,
  (uint *) pipeline_res_cycles_010,
  Pipeline_Use(0x0, 0x0, 0, (Pipeline_Use_Element *)nullptr));

// Pipeline Class "pipe_class_call"
static const Pipeline pipeline_class_057((uint)stage_undefined, 0, true, 100, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_012,
  (uint *) pipeline_res_cycles_010,
  Pipeline_Use(0x0, 0x0, 0, (Pipeline_Use_Element *)nullptr));

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
  nop_list[0] = (MachNode *) new MachNopNode();
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

  static const char *resource_names[9] = { "INS0", "INS1", "ALU0", "ALU1", "MAC", "DIV", "BRANCH", "LDST", "NEON_FP" };

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
    for (uint i = 0; i < 9; i++)
      if ((r & (1 << i)) != 0)
        st->print(" %s", resource_names[i]);
    needs_comma = true;
  };
  st->print("\n");
}
#endif
const Pipeline *                              Node::pipeline_class() { return (&pipeline_class_Zero_Instructions); }
const Pipeline *                              Node::pipeline() const { return (&pipeline_class_Zero_Instructions); }

const Pipeline *                          MachNode::pipeline_class() { return (&pipeline_class_Unknown_Instructions); }
const Pipeline *                          MachNode::pipeline() const { return pipeline_class(); }

const Pipeline * MachNopNode::pipeline() const { return (&pipeline_class_053); }


const Pipeline *                             loadBNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                             loadBNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                           loadB2LNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                           loadB2LNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                            loadUBNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                            loadUBNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                          loadUB2LNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                          loadUB2LNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                             loadSNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                             loadSNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                           loadS2LNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                           loadS2LNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                            loadUSNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                            loadUSNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                          loadUS2LNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                          loadUS2LNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                             loadINode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                             loadINode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                           loadI2LNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                           loadI2LNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                          loadUI2LNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                          loadUI2LNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                             loadLNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                             loadLNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                         loadRangeNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                         loadRangeNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                             loadPNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                             loadPNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                             loadNNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                             loadNNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                         loadKlassNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                         loadKlassNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                        loadNKlassNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                        loadNKlassNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                             loadFNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                             loadFNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                             loadDNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                             loadDNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                          loadConINode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                          loadConINode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                          loadConLNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                          loadConLNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                          loadConPNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                          loadConPNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                         loadConP0Node::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                         loadConP0Node::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                         loadConP1Node::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                         loadConP1Node::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                   loadByteMapBaseNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                   loadByteMapBaseNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                          loadConNNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                          loadConNNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                         loadConN0Node::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                         loadConN0Node::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                     loadConNKlassNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                     loadConNKlassNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                   loadConF_packedNode::pipeline_class() { return (&pipeline_class_019); }
const Pipeline *                   loadConF_packedNode::pipeline() const { return (&pipeline_class_019); }

const Pipeline *                          loadConFNode::pipeline_class() { return (&pipeline_class_021); }
const Pipeline *                          loadConFNode::pipeline() const { return (&pipeline_class_021); }

const Pipeline *                   loadConD_packedNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                   loadConD_packedNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                          loadConDNode::pipeline_class() { return (&pipeline_class_022); }
const Pipeline *                          loadConDNode::pipeline() const { return (&pipeline_class_022); }

const Pipeline *                       storeimmCM0Node::pipeline_class() { return (&pipeline_class_045); }
const Pipeline *                       storeimmCM0Node::pipeline() const { return (&pipeline_class_045); }

const Pipeline *               storeimmCM0_orderedNode::pipeline_class() { return (&pipeline_class_045); }
const Pipeline *               storeimmCM0_orderedNode::pipeline() const { return (&pipeline_class_045); }

const Pipeline *                            storeBNode::pipeline_class() { return (&pipeline_class_046); }
const Pipeline *                            storeBNode::pipeline() const { return (&pipeline_class_046); }

const Pipeline *                        storeimmB0Node::pipeline_class() { return (&pipeline_class_045); }
const Pipeline *                        storeimmB0Node::pipeline() const { return (&pipeline_class_045); }

const Pipeline *                            storeCNode::pipeline_class() { return (&pipeline_class_046); }
const Pipeline *                            storeCNode::pipeline() const { return (&pipeline_class_046); }

const Pipeline *                        storeimmC0Node::pipeline_class() { return (&pipeline_class_045); }
const Pipeline *                        storeimmC0Node::pipeline() const { return (&pipeline_class_045); }

const Pipeline *                            storeINode::pipeline_class() { return (&pipeline_class_046); }
const Pipeline *                            storeINode::pipeline() const { return (&pipeline_class_046); }

const Pipeline *                        storeimmI0Node::pipeline_class() { return (&pipeline_class_045); }
const Pipeline *                        storeimmI0Node::pipeline() const { return (&pipeline_class_045); }

const Pipeline *                            storeLNode::pipeline_class() { return (&pipeline_class_046); }
const Pipeline *                            storeLNode::pipeline() const { return (&pipeline_class_046); }

const Pipeline *                        storeimmL0Node::pipeline_class() { return (&pipeline_class_045); }
const Pipeline *                        storeimmL0Node::pipeline() const { return (&pipeline_class_045); }

const Pipeline *                            storePNode::pipeline_class() { return (&pipeline_class_046); }
const Pipeline *                            storePNode::pipeline() const { return (&pipeline_class_046); }

const Pipeline *                        storeimmP0Node::pipeline_class() { return (&pipeline_class_045); }
const Pipeline *                        storeimmP0Node::pipeline() const { return (&pipeline_class_045); }

const Pipeline *                            storeNNode::pipeline_class() { return (&pipeline_class_046); }
const Pipeline *                            storeNNode::pipeline() const { return (&pipeline_class_046); }

const Pipeline *                        storeImmN0Node::pipeline_class() { return (&pipeline_class_045); }
const Pipeline *                        storeImmN0Node::pipeline() const { return (&pipeline_class_045); }

const Pipeline *                            storeFNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                            storeFNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                            storeDNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                            storeDNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                       storeNKlassNode::pipeline_class() { return (&pipeline_class_046); }
const Pipeline *                       storeNKlassNode::pipeline() const { return (&pipeline_class_046); }

const Pipeline *                     prefetchallocNode::pipeline_class() { return (&pipeline_class_042); }
const Pipeline *                     prefetchallocNode::pipeline() const { return (&pipeline_class_042); }

const Pipeline *                    loadB_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    loadB_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                  loadB2L_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                  loadB2L_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   loadUB_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                   loadUB_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                 loadUB2L_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                 loadUB2L_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                    loadS_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    loadS_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   loadUS_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                   loadUS_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                 loadUS2L_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                 loadUS2L_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                  loadS2L_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                  loadS2L_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                    loadI_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    loadI_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                 loadUI2L_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                 loadUI2L_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                    loadL_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    loadL_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                    loadP_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    loadP_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                    loadN_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    loadN_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                    loadF_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    loadF_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                    loadD_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    loadD_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   storeB_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   storeB_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *               storeimmB0_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *               storeimmB0_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   storeC_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   storeC_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *               storeimmC0_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *               storeimmC0_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   storeI_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   storeI_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *               storeimmI0_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *               storeimmI0_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   storeL_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   storeL_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *               storeimmL0_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *               storeimmL0_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   storeP_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   storeP_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *               storeimmP0_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *               storeimmP0_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   storeN_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   storeN_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *               storeimmN0_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *               storeimmN0_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   storeF_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   storeF_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   storeD_volatileNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   storeD_volatileNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                           cacheWBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           cacheWBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    cacheWBPreSyncNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    cacheWBPreSyncNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   cacheWBPostSyncNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   cacheWBPostSyncNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 bytes_reverse_intNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                 bytes_reverse_intNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                bytes_reverse_longNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                bytes_reverse_longNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *      bytes_reverse_unsigned_shortNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *      bytes_reverse_unsigned_shortNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *               bytes_reverse_shortNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *               bytes_reverse_shortNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                countLeadingZerosINode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                countLeadingZerosINode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                countLeadingZerosLNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                countLeadingZerosLNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *               countTrailingZerosINode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *               countTrailingZerosINode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *               countTrailingZerosLNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *               countTrailingZerosLNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                         popCountINode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                         popCountINode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     popCountI_memNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     popCountI_memNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                         popCountLNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                         popCountLNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     popCountL_memNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     popCountL_memNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           verify_vector_alignmentNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *           verify_vector_alignmentNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        load_fenceNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                        load_fenceNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *        unnecessary_membar_acquireNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *        unnecessary_membar_acquireNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                    membar_acquireNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    membar_acquireNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *               membar_acquire_lockNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *               membar_acquire_lockNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                       store_fenceNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                       store_fenceNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *        unnecessary_membar_releaseNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *        unnecessary_membar_releaseNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                    membar_releaseNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    membar_releaseNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                 membar_storestoreNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                 membar_storestoreNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *               membar_storestore_0Node::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *               membar_storestore_0Node::pipeline() const { return (&pipeline_class_051); }

const Pipeline *               membar_release_lockNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *               membar_release_lockNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *       unnecessary_membar_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *       unnecessary_membar_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   membar_volatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                   membar_volatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                           castX2PNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                           castX2PNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                           castP2XNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                           castP2XNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                           convP2INode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                           convP2INode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                           convN2INode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                           convN2INode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                     encodeHeapOopNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                     encodeHeapOopNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *            encodeHeapOop_not_nullNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *            encodeHeapOop_not_nullNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                     decodeHeapOopNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                     decodeHeapOopNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *            decodeHeapOop_not_nullNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *            decodeHeapOop_not_nullNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *              encodeKlass_not_nullNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *              encodeKlass_not_nullNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *              decodeKlass_not_nullNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *              decodeKlass_not_nullNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                       checkCastPPNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                       checkCastPPNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                            castPPNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                            castPPNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                            castIINode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                            castIINode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                            castLLNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                            castLLNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                            castFFNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                            castFFNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                            castDDNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                            castDDNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                            castVVNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                            castVVNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                        castVVMaskNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                        castVVMaskNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                   compareAndSwapBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   compareAndSwapBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   compareAndSwapSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   compareAndSwapSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   compareAndSwapINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   compareAndSwapINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   compareAndSwapLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   compareAndSwapLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   compareAndSwapPNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   compareAndSwapPNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   compareAndSwapNNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   compareAndSwapNNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                compareAndSwapBAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                compareAndSwapBAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                compareAndSwapSAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                compareAndSwapSAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                compareAndSwapIAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                compareAndSwapIAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                compareAndSwapLAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                compareAndSwapLAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                compareAndSwapPAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                compareAndSwapPAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                compareAndSwapNAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                compareAndSwapNAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               compareAndExchangeBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               compareAndExchangeBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               compareAndExchangeSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               compareAndExchangeSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               compareAndExchangeINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               compareAndExchangeINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               compareAndExchangeLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               compareAndExchangeLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               compareAndExchangeNNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               compareAndExchangeNNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               compareAndExchangePNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               compareAndExchangePNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            compareAndExchangeBAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            compareAndExchangeBAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            compareAndExchangeSAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            compareAndExchangeSAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            compareAndExchangeIAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            compareAndExchangeIAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            compareAndExchangeLAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            compareAndExchangeLAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            compareAndExchangeNAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            compareAndExchangeNAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            compareAndExchangePAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            compareAndExchangePAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               weakCompareAndSwapBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               weakCompareAndSwapBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               weakCompareAndSwapSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               weakCompareAndSwapSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               weakCompareAndSwapINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               weakCompareAndSwapINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               weakCompareAndSwapLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               weakCompareAndSwapLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               weakCompareAndSwapNNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               weakCompareAndSwapNNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               weakCompareAndSwapPNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               weakCompareAndSwapPNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            weakCompareAndSwapBAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            weakCompareAndSwapBAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            weakCompareAndSwapSAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            weakCompareAndSwapSAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            weakCompareAndSwapIAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            weakCompareAndSwapIAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            weakCompareAndSwapLAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            weakCompareAndSwapLAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            weakCompareAndSwapNAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            weakCompareAndSwapNAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            weakCompareAndSwapPAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            weakCompareAndSwapPAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      get_and_setINode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                      get_and_setINode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                      get_and_setLNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                      get_and_setLNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                      get_and_setNNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                      get_and_setNNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                      get_and_setPNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                      get_and_setPNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   get_and_setIAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                   get_and_setIAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   get_and_setLAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                   get_and_setLAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   get_and_setNAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                   get_and_setNAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   get_and_setPAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                   get_and_setPAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                      get_and_addLNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                      get_and_addLNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *               get_and_addL_no_resNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *               get_and_addL_no_resNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                     get_and_addLiNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                     get_and_addLiNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *              get_and_addLi_no_resNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *              get_and_addLi_no_resNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                      get_and_addINode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                      get_and_addINode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *               get_and_addI_no_resNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *               get_and_addI_no_resNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                     get_and_addIiNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                     get_and_addIiNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *              get_and_addIi_no_resNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *              get_and_addIi_no_resNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   get_and_addLAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                   get_and_addLAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *            get_and_addL_no_resAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *            get_and_addL_no_resAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                  get_and_addLiAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                  get_and_addLiAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *           get_and_addLi_no_resAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *           get_and_addLi_no_resAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   get_and_addIAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                   get_and_addIAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *            get_and_addI_no_resAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *            get_and_addI_no_resAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                  get_and_addIiAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                  get_and_addIiAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *           get_and_addIi_no_resAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *           get_and_addIi_no_resAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                     cmpU3_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     cmpU3_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     cmpU3_reg_immNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     cmpU3_reg_immNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                    cmpUL3_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                    cmpUL3_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                    cmpUL3_reg_immNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                    cmpUL3_reg_immNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     cmpL3_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     cmpL3_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     cmpL3_reg_immNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     cmpL3_reg_immNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     cmovI_reg_regNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                     cmovI_reg_regNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                    cmovUI_reg_regNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                    cmovUI_reg_regNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                    cmovI_zero_regNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                    cmovI_zero_regNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                   cmovUI_zero_regNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                   cmovUI_zero_regNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                    cmovI_reg_zeroNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                    cmovI_reg_zeroNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                   cmovUI_reg_zeroNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                   cmovUI_reg_zeroNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                cmovI_reg_zero_oneNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                cmovI_reg_zero_oneNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *               cmovUI_reg_zero_oneNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *               cmovUI_reg_zero_oneNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                     cmovL_reg_regNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                     cmovL_reg_regNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                    cmovUL_reg_regNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                    cmovUL_reg_regNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                    cmovL_reg_zeroNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                    cmovL_reg_zeroNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                   cmovUL_reg_zeroNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                   cmovUL_reg_zeroNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                    cmovL_zero_regNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                    cmovL_zero_regNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                   cmovUL_zero_regNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                   cmovUL_zero_regNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                     cmovP_reg_regNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                     cmovP_reg_regNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                    cmovUP_reg_regNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                    cmovUP_reg_regNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                    cmovP_reg_zeroNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                    cmovP_reg_zeroNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                   cmovUP_reg_zeroNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                   cmovUP_reg_zeroNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                    cmovP_zero_regNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                    cmovP_zero_regNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                   cmovUP_zero_regNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                   cmovUP_zero_regNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                     cmovN_reg_regNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                     cmovN_reg_regNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                    cmovUN_reg_regNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                    cmovUN_reg_regNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                    cmovN_reg_zeroNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                    cmovN_reg_zeroNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                   cmovUN_reg_zeroNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                   cmovUN_reg_zeroNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                    cmovN_zero_regNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                    cmovN_zero_regNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                   cmovUN_zero_regNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                   cmovUN_zero_regNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                         cmovF_regNode::pipeline_class() { return (&pipeline_class_017); }
const Pipeline *                         cmovF_regNode::pipeline() const { return (&pipeline_class_017); }

const Pipeline *                        cmovUF_regNode::pipeline_class() { return (&pipeline_class_017); }
const Pipeline *                        cmovUF_regNode::pipeline() const { return (&pipeline_class_017); }

const Pipeline *                         cmovD_regNode::pipeline_class() { return (&pipeline_class_018); }
const Pipeline *                         cmovD_regNode::pipeline() const { return (&pipeline_class_018); }

const Pipeline *                        cmovUD_regNode::pipeline_class() { return (&pipeline_class_018); }
const Pipeline *                        cmovUD_regNode::pipeline() const { return (&pipeline_class_018); }

const Pipeline *                      addI_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      addI_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      addI_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                      addI_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                  addI_reg_imm_i2lNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                  addI_reg_imm_i2lNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                      addP_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      addP_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  addP_reg_reg_extNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  addP_reg_reg_extNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  addP_reg_reg_lslNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                  addP_reg_reg_lslNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            addP_reg_reg_ext_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            addP_reg_reg_ext_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                        lshift_extNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                        lshift_extNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                      addP_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                      addP_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                      addL_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      addL_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      addL_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                      addL_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                      subI_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      subI_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      subI_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                      subI_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                      subL_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      subL_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      subL_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                      subL_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                          negI_regNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                          negI_regNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                          negL_regNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                          negL_regNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                              mulINode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                              mulINode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                             smulINode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                             smulINode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                           smulI_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                           smulI_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                              mulLNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                              mulLNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                       mulHiL_rRegNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                       mulHiL_rRegNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                      umulHiL_rRegNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                      umulHiL_rRegNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                             maddINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                             maddINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                           maddI_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                           maddI_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                             msubINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                             msubINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                             mnegINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                             mnegINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                           mnegI_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                           mnegI_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                             maddLNode::pipeline_class() { return (&pipeline_class_039); }
const Pipeline *                             maddLNode::pipeline() const { return (&pipeline_class_039); }

const Pipeline *                           maddL_0Node::pipeline_class() { return (&pipeline_class_039); }
const Pipeline *                           maddL_0Node::pipeline() const { return (&pipeline_class_039); }

const Pipeline *                             msubLNode::pipeline_class() { return (&pipeline_class_039); }
const Pipeline *                             msubLNode::pipeline() const { return (&pipeline_class_039); }

const Pipeline *                             mnegLNode::pipeline_class() { return (&pipeline_class_039); }
const Pipeline *                             mnegLNode::pipeline() const { return (&pipeline_class_039); }

const Pipeline *                           mnegL_0Node::pipeline_class() { return (&pipeline_class_039); }
const Pipeline *                           mnegL_0Node::pipeline() const { return (&pipeline_class_039); }

const Pipeline *                            smaddLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            smaddLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          smaddL_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          smaddL_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          smaddL_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          smaddL_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          smaddL_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          smaddL_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            smsubLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            smsubLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          smsubL_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          smsubL_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            smnegLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            smnegLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          smnegL_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          smnegL_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                         muladdS2INode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                         muladdS2INode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                              divINode::pipeline_class() { return (&pipeline_class_040); }
const Pipeline *                              divINode::pipeline() const { return (&pipeline_class_040); }

const Pipeline *                              divLNode::pipeline_class() { return (&pipeline_class_041); }
const Pipeline *                              divLNode::pipeline() const { return (&pipeline_class_041); }

const Pipeline *                              modINode::pipeline_class() { return (&pipeline_class_040); }
const Pipeline *                              modINode::pipeline() const { return (&pipeline_class_040); }

const Pipeline *                              modLNode::pipeline_class() { return (&pipeline_class_041); }
const Pipeline *                              modLNode::pipeline() const { return (&pipeline_class_041); }

const Pipeline *                     UdivI_reg_regNode::pipeline_class() { return (&pipeline_class_040); }
const Pipeline *                     UdivI_reg_regNode::pipeline() const { return (&pipeline_class_040); }

const Pipeline *                     UdivL_reg_regNode::pipeline_class() { return (&pipeline_class_041); }
const Pipeline *                     UdivL_reg_regNode::pipeline() const { return (&pipeline_class_041); }

const Pipeline *                     UmodI_reg_regNode::pipeline_class() { return (&pipeline_class_040); }
const Pipeline *                     UmodI_reg_regNode::pipeline() const { return (&pipeline_class_040); }

const Pipeline *                     UModL_reg_regNode::pipeline_class() { return (&pipeline_class_041); }
const Pipeline *                     UModL_reg_regNode::pipeline() const { return (&pipeline_class_041); }

const Pipeline *                   lShiftI_reg_regNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                   lShiftI_reg_regNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                   lShiftI_reg_immNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                   lShiftI_reg_immNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                  urShiftI_reg_regNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                  urShiftI_reg_regNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                  urShiftI_reg_immNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                  urShiftI_reg_immNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                   rShiftI_reg_regNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                   rShiftI_reg_regNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                   rShiftI_reg_immNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                   rShiftI_reg_immNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                   lShiftL_reg_regNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                   lShiftL_reg_regNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                   lShiftL_reg_immNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                   lShiftL_reg_immNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                  urShiftL_reg_regNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                  urShiftL_reg_regNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                  urShiftL_reg_immNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                  urShiftL_reg_immNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                  urShiftP_reg_immNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                  urShiftP_reg_immNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                   rShiftL_reg_regNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                   rShiftL_reg_regNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                   rShiftL_reg_immNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                   rShiftL_reg_immNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                      regL_not_regNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                      regL_not_regNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                      regI_not_regNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                      regI_not_regNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *              NegI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *              NegI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *               NegI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *               NegI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *               NegI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *               NegI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *              NegL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *              NegL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *               NegL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *               NegL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *               NegL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *               NegL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                  AndI_reg_not_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  AndI_reg_not_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                AndI_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                AndI_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  AndL_reg_not_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  AndL_reg_not_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                AndL_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                AndL_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                   OrI_reg_not_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                   OrI_reg_not_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                 OrI_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                 OrI_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                   OrL_reg_not_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                   OrL_reg_not_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                 OrL_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                 OrL_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  XorI_reg_not_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  XorI_reg_not_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                XorI_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                XorI_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  XorL_reg_not_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  XorL_reg_not_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                XorL_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                XorL_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *          AndI_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          AndI_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        AndI_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        AndI_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          AndL_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          AndL_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        AndL_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        AndL_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           AndI_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           AndI_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         AndI_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         AndI_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           AndL_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           AndL_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         AndL_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         AndL_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *      AndI_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *      AndI_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *    AndI_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *    AndI_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *      AndL_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *      AndL_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *    AndL_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *    AndL_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           AndI_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           AndI_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         AndI_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         AndI_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           AndL_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           AndL_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         AndL_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         AndL_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          XorI_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          XorI_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        XorI_reg_URShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        XorI_reg_URShift_not_reg_1Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        XorI_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        XorI_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        XorI_reg_URShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        XorI_reg_URShift_not_reg_2Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          XorL_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          XorL_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        XorL_reg_URShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        XorL_reg_URShift_not_reg_1Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        XorL_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        XorL_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        XorL_reg_URShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        XorL_reg_URShift_not_reg_2Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           XorI_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           XorI_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorI_reg_RShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorI_reg_RShift_not_reg_1Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorI_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorI_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorI_reg_RShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorI_reg_RShift_not_reg_2Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           XorL_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           XorL_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorL_reg_RShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorL_reg_RShift_not_reg_1Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorL_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorL_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorL_reg_RShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorL_reg_RShift_not_reg_2Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *      XorI_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *      XorI_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *    XorI_reg_RotateRight_not_reg_1Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *    XorI_reg_RotateRight_not_reg_1Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *    XorI_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *    XorI_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *    XorI_reg_RotateRight_not_reg_2Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *    XorI_reg_RotateRight_not_reg_2Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *      XorL_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *      XorL_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *    XorL_reg_RotateRight_not_reg_1Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *    XorL_reg_RotateRight_not_reg_1Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *    XorL_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *    XorL_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *    XorL_reg_RotateRight_not_reg_2Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *    XorL_reg_RotateRight_not_reg_2Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           XorI_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           XorI_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorI_reg_LShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorI_reg_LShift_not_reg_1Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorI_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorI_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorI_reg_LShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorI_reg_LShift_not_reg_2Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           XorL_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           XorL_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorL_reg_LShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorL_reg_LShift_not_reg_1Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorL_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorL_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         XorL_reg_LShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         XorL_reg_LShift_not_reg_2Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           OrI_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           OrI_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         OrI_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         OrI_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           OrL_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           OrL_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         OrL_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         OrL_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            OrI_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            OrI_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          OrI_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          OrI_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            OrL_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            OrL_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          OrL_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          OrL_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *       OrI_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *       OrI_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *     OrI_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *     OrI_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *       OrL_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *       OrL_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *     OrL_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *     OrL_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            OrI_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            OrI_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          OrI_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          OrI_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            OrL_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            OrL_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          OrL_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          OrL_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              AndI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              AndI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            AndI_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            AndI_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              AndL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              AndL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            AndL_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            AndL_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               AndI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               AndI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             AndI_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             AndI_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               AndL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               AndL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             AndL_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             AndL_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               AndI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               AndI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             AndI_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             AndI_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               AndL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               AndL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             AndL_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             AndL_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          AndI_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          AndI_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        AndI_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        AndI_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          AndL_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          AndL_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        AndL_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        AndL_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              XorI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              XorI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            XorI_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            XorI_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              XorL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              XorL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            XorL_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            XorL_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               XorI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               XorI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             XorI_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             XorI_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               XorL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               XorL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             XorL_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             XorL_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               XorI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               XorI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             XorI_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             XorI_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               XorL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               XorL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             XorL_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             XorL_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          XorI_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          XorI_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        XorI_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        XorI_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          XorL_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          XorL_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *        XorL_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *        XorL_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               OrI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               OrI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             OrI_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             OrI_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               OrL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               OrL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             OrL_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             OrL_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                OrI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                OrI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              OrI_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              OrI_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                OrL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                OrL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              OrL_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              OrL_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                OrI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                OrI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              OrI_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              OrI_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                OrL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                OrL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              OrL_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              OrL_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           OrI_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           OrI_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         OrI_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         OrI_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *           OrL_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *           OrL_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *         OrL_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *         OrL_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              AddI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              AddI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            AddI_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            AddI_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              AddL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              AddL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            AddL_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            AddL_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               AddI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               AddI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             AddI_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             AddI_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               AddL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               AddL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             AddL_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             AddL_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               AddI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               AddI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             AddI_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             AddI_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               AddL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               AddL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *             AddL_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *             AddL_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              SubI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              SubI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              SubL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              SubL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               SubI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               SubI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               SubL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               SubL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               SubI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               SubI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *               SubL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *               SubL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                             sbfmLNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                             sbfmLNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                            sbfmwINode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                            sbfmwINode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                             ubfmLNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                             ubfmLNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                            ubfmwINode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                            ubfmwINode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                            ubfxwINode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                            ubfxwINode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                             ubfxLNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                             ubfxLNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                      ubfxIConvI2LNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                      ubfxIConvI2LNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                           ubfizwINode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                           ubfizwINode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                            ubfizLNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                            ubfizLNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                    ubfizwIConvI2LNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                    ubfizwIConvI2LNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                     ubfizLConvL2INode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                     ubfizLConvL2INode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                     ubfizIConvI2LNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                     ubfizIConvI2LNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                    ubfizLConvL2IxNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                    ubfizLConvL2IxNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                 ubfizIConvI2LAndINode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                 ubfizIConvI2LAndINode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                           extrOrLNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                           extrOrLNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                         extrOrL_0Node::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                         extrOrL_0Node::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                           extrOrINode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                           extrOrINode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                         extrOrI_0Node::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                         extrOrI_0Node::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                          extrAddLNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                          extrAddLNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                        extrAddL_0Node::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                        extrAddL_0Node::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                          extrAddINode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                          extrAddINode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                        extrAddI_0Node::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                        extrAddI_0Node::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                          rorI_immNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                          rorI_immNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                          rorL_immNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                          rorL_immNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                          rorI_regNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                          rorI_regNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                          rorL_regNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                          rorL_regNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                          rolI_regNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                          rolI_regNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                          rolL_regNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                          rolL_regNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                           AddExtINode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                           AddExtINode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                         AddExtI_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                         AddExtI_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                           SubExtINode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                           SubExtINode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      AddExtI_sxthNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      AddExtI_sxthNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                    AddExtI_sxth_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                    AddExtI_sxth_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      AddExtI_sxtbNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      AddExtI_sxtbNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                    AddExtI_sxtb_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                    AddExtI_sxtb_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      AddExtI_uxtbNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      AddExtI_uxtbNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                    AddExtI_uxtb_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                    AddExtI_uxtb_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      AddExtL_sxthNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      AddExtL_sxthNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                    AddExtL_sxth_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                    AddExtL_sxth_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      AddExtL_sxtwNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      AddExtL_sxtwNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                    AddExtL_sxtw_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                    AddExtL_sxtw_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      AddExtL_sxtbNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      AddExtL_sxtbNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                    AddExtL_sxtb_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                    AddExtL_sxtb_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      AddExtL_uxtbNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      AddExtL_uxtbNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                    AddExtL_uxtb_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                    AddExtL_uxtb_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  AddExtI_uxtb_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  AddExtI_uxtb_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                AddExtI_uxtb_and_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                AddExtI_uxtb_and_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  AddExtI_uxth_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  AddExtI_uxth_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                AddExtI_uxth_and_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                AddExtI_uxth_and_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  AddExtL_uxtb_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  AddExtL_uxtb_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                AddExtL_uxtb_and_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                AddExtL_uxtb_and_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  AddExtL_uxth_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  AddExtL_uxth_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                AddExtL_uxth_and_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                AddExtL_uxth_and_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  AddExtL_uxtw_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  AddExtL_uxtw_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                AddExtL_uxtw_and_0Node::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                AddExtL_uxtw_and_0Node::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  SubExtI_uxtb_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  SubExtI_uxtb_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  SubExtI_uxth_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  SubExtI_uxth_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  SubExtL_uxtb_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  SubExtL_uxtb_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  SubExtL_uxth_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  SubExtL_uxth_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                  SubExtL_uxtw_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                  SubExtL_uxtw_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                AddExtL_sxtb_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                AddExtL_sxtb_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              AddExtL_sxtb_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              AddExtL_sxtb_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                AddExtL_sxth_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                AddExtL_sxth_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              AddExtL_sxth_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              AddExtL_sxth_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                AddExtL_sxtw_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                AddExtL_sxtw_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              AddExtL_sxtw_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              AddExtL_sxtw_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                SubExtL_sxtb_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                SubExtL_sxtb_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                SubExtL_sxth_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                SubExtL_sxth_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                SubExtL_sxtw_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                SubExtL_sxtw_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                AddExtI_sxtb_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                AddExtI_sxtb_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              AddExtI_sxtb_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              AddExtI_sxtb_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                AddExtI_sxth_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                AddExtI_sxth_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *              AddExtI_sxth_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *              AddExtI_sxth_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                SubExtI_sxtb_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                SubExtI_sxtb_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                SubExtI_sxth_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                SubExtI_sxth_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                     AddExtI_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                     AddExtI_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                   AddExtI_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                   AddExtI_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                     SubExtI_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                     SubExtI_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            AddExtL_uxtb_and_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            AddExtL_uxtb_and_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          AddExtL_uxtb_and_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          AddExtL_uxtb_and_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            AddExtL_uxth_and_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            AddExtL_uxth_and_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          AddExtL_uxth_and_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          AddExtL_uxth_and_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            AddExtL_uxtw_and_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            AddExtL_uxtw_and_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          AddExtL_uxtw_and_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          AddExtL_uxtw_and_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            SubExtL_uxtb_and_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            SubExtL_uxtb_and_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            SubExtL_uxth_and_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            SubExtL_uxth_and_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            SubExtL_uxtw_and_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            SubExtL_uxtw_and_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            AddExtI_uxtb_and_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            AddExtI_uxtb_and_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          AddExtI_uxtb_and_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          AddExtI_uxtb_and_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            AddExtI_uxth_and_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            AddExtI_uxth_and_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *          AddExtI_uxth_and_shift_0Node::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *          AddExtI_uxth_and_shift_0Node::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            SubExtI_uxtb_and_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            SubExtI_uxtb_and_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *            SubExtI_uxth_and_shiftNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *            SubExtI_uxth_and_shiftNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                  cmovI_reg_reg_ltNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                  cmovI_reg_reg_ltNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                  cmovI_reg_reg_gtNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                  cmovI_reg_reg_gtNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                 cmovI_reg_imm0_ltNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                 cmovI_reg_imm0_ltNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                 cmovI_reg_imm0_gtNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                 cmovI_reg_imm0_gtNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                 cmovI_reg_imm1_leNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                 cmovI_reg_imm1_leNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                 cmovI_reg_imm1_gtNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                 cmovI_reg_imm1_gtNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                cmovI_reg_immM1_ltNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                cmovI_reg_immM1_ltNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                cmovI_reg_immM1_geNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                cmovI_reg_immM1_geNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                    bits_reverse_INode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                    bits_reverse_INode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                    bits_reverse_LNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                    bits_reverse_LNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                      addF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      addF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      addD_reg_regNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                      addD_reg_regNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                      subF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      subF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      subD_reg_regNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                      subD_reg_regNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                      mulF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      mulF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      mulD_reg_regNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                      mulD_reg_regNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                     maddF_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     maddF_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     maddD_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     maddD_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     msubF_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     msubF_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     msubD_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     msubD_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                    mnaddF_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                    mnaddF_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                    mnaddD_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                    mnaddD_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                    mnsubF_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                    mnsubF_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                    mnsubD_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                    mnsubD_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                      maxF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      maxF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      minF_reg_regNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                      minF_reg_regNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                      maxD_reg_regNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                      maxD_reg_regNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                      minD_reg_regNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                      minD_reg_regNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                      divF_reg_regNode::pipeline_class() { return (&pipeline_class_015); }
const Pipeline *                      divF_reg_regNode::pipeline() const { return (&pipeline_class_015); }

const Pipeline *                      divD_reg_regNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                      divD_reg_regNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                      negF_reg_regNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                      negF_reg_regNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                      negD_reg_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                      negD_reg_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                          absI_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                          absI_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                          absL_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                          absL_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                          absF_regNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                          absF_regNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                          absD_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                          absD_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                         absdF_regNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                         absdF_regNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                         absdD_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                         absdD_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                         sqrtD_regNode::pipeline_class() { return (&pipeline_class_015); }
const Pipeline *                         sqrtD_regNode::pipeline() const { return (&pipeline_class_015); }

const Pipeline *                         sqrtF_regNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                         sqrtF_regNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                        roundD_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                        roundD_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                     copySignD_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                     copySignD_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                     copySignF_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                     copySignF_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                       signumD_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                       signumD_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                       signumF_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                       signumF_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                        onspinwaitNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                        onspinwaitNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      andI_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      andI_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      andI_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                      andI_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                       orI_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                       orI_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                       orI_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                       orI_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                      xorI_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      xorI_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      xorI_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                      xorI_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                      andL_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      andL_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      andL_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                      andL_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                       orL_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                       orL_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                       orL_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                       orL_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                      xorL_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      xorL_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      xorL_reg_immNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                      xorL_reg_immNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                   convI2L_reg_regNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                   convI2L_reg_regNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                  convUI2L_reg_regNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                  convUI2L_reg_regNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                       convL2I_regNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                       convL2I_regNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                       convD2F_regNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                       convD2F_regNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                       convF2D_regNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                       convF2D_regNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                   convF2I_reg_regNode::pipeline_class() { return (&pipeline_class_007); }
const Pipeline *                   convF2I_reg_regNode::pipeline() const { return (&pipeline_class_007); }

const Pipeline *                   convF2L_reg_regNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                   convF2L_reg_regNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                  convF2HF_reg_regNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  convF2HF_reg_regNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  convHF2F_reg_regNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  convHF2F_reg_regNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   convI2F_reg_regNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                   convI2F_reg_regNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                   convL2F_reg_regNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                   convL2F_reg_regNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                   convD2I_reg_regNode::pipeline_class() { return (&pipeline_class_011); }
const Pipeline *                   convD2I_reg_regNode::pipeline() const { return (&pipeline_class_011); }

const Pipeline *                   convD2L_reg_regNode::pipeline_class() { return (&pipeline_class_012); }
const Pipeline *                   convD2L_reg_regNode::pipeline() const { return (&pipeline_class_012); }

const Pipeline *                   convI2D_reg_regNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                   convI2D_reg_regNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                   convL2D_reg_regNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                   convL2D_reg_regNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                  round_double_regNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  round_double_regNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   round_float_regNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   round_float_regNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 MoveF2I_stack_regNode::pipeline_class() { return (&pipeline_class_044); }
const Pipeline *                 MoveF2I_stack_regNode::pipeline() const { return (&pipeline_class_044); }

const Pipeline *                 MoveI2F_stack_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                 MoveI2F_stack_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                 MoveD2L_stack_regNode::pipeline_class() { return (&pipeline_class_044); }
const Pipeline *                 MoveD2L_stack_regNode::pipeline() const { return (&pipeline_class_044); }

const Pipeline *                 MoveL2D_stack_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                 MoveL2D_stack_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                 MoveF2I_reg_stackNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                 MoveF2I_reg_stackNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                 MoveI2F_reg_stackNode::pipeline_class() { return (&pipeline_class_047); }
const Pipeline *                 MoveI2F_reg_stackNode::pipeline() const { return (&pipeline_class_047); }

const Pipeline *                 MoveD2L_reg_stackNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                 MoveD2L_reg_stackNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                 MoveL2D_reg_stackNode::pipeline_class() { return (&pipeline_class_047); }
const Pipeline *                 MoveL2D_reg_stackNode::pipeline() const { return (&pipeline_class_047); }

const Pipeline *                   MoveF2I_reg_regNode::pipeline_class() { return (&pipeline_class_007); }
const Pipeline *                   MoveF2I_reg_regNode::pipeline() const { return (&pipeline_class_007); }

const Pipeline *                   MoveI2F_reg_regNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                   MoveI2F_reg_regNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                   MoveD2L_reg_regNode::pipeline_class() { return (&pipeline_class_012); }
const Pipeline *                   MoveD2L_reg_regNode::pipeline() const { return (&pipeline_class_012); }

const Pipeline *                   MoveL2D_reg_regNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                   MoveL2D_reg_regNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                clearArray_reg_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                clearArray_reg_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                clearArray_imm_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                clearArray_imm_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *              overflowAddI_reg_regNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *              overflowAddI_reg_regNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *              overflowAddI_reg_immNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *              overflowAddI_reg_immNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *              overflowAddL_reg_regNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *              overflowAddL_reg_regNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *              overflowAddL_reg_immNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *              overflowAddL_reg_immNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *              overflowSubI_reg_regNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *              overflowSubI_reg_regNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *              overflowSubI_reg_immNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *              overflowSubI_reg_immNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *              overflowSubL_reg_regNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *              overflowSubL_reg_regNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *              overflowSubL_reg_immNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *              overflowSubL_reg_immNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                  overflowNegI_regNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                  overflowNegI_regNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                  overflowNegL_regNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                  overflowNegL_regNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                  overflowMulI_regNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  overflowMulI_regNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *           overflowMulI_reg_branchNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *           overflowMulI_reg_branchNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                  overflowMulL_regNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  overflowMulL_regNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *           overflowMulL_reg_branchNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *           overflowMulL_reg_branchNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                     compI_reg_regNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                     compI_reg_regNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                   compI_reg_immI0Node::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                   compI_reg_immI0Node::pipeline() const { return (&pipeline_class_032); }

const Pipeline *              compI_reg_immIAddSubNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *              compI_reg_immIAddSubNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                    compI_reg_immINode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                    compI_reg_immINode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                     compU_reg_regNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                     compU_reg_regNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                   compU_reg_immI0Node::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                   compU_reg_immI0Node::pipeline() const { return (&pipeline_class_032); }

const Pipeline *              compU_reg_immIAddSubNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *              compU_reg_immIAddSubNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                    compU_reg_immINode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                    compU_reg_immINode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                     compL_reg_regNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                     compL_reg_regNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                   compL_reg_immL0Node::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                   compL_reg_immL0Node::pipeline() const { return (&pipeline_class_032); }

const Pipeline *              compL_reg_immLAddSubNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *              compL_reg_immLAddSubNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                    compL_reg_immLNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                    compL_reg_immLNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                    compUL_reg_regNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                    compUL_reg_regNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                  compUL_reg_immL0Node::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                  compUL_reg_immL0Node::pipeline() const { return (&pipeline_class_032); }

const Pipeline *             compUL_reg_immLAddSubNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *             compUL_reg_immLAddSubNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                   compUL_reg_immLNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                   compUL_reg_immLNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                     compP_reg_regNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                     compP_reg_regNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                     compN_reg_regNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                     compN_reg_regNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                         testP_regNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                         testP_regNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                         testN_regNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                         testN_regNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                     compF_reg_regNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                     compF_reg_regNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                    compF_reg_zeroNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                    compF_reg_zeroNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                     compD_reg_regNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                     compD_reg_regNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                    compD_reg_zeroNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                    compD_reg_zeroNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                    compF3_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                    compF3_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                    compD3_reg_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                    compD3_reg_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                  compF3_reg_immF0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                  compF3_reg_immF0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                  compD3_reg_immD0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                  compD3_reg_immD0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                 cmpLTMask_reg_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                 cmpLTMask_reg_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                cmpLTMask_reg_zeroNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                cmpLTMask_reg_zeroNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                    compI_reg_imm0Node::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                    compI_reg_imm0Node::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                            branchNode::pipeline_class() { return (&pipeline_class_048); }
const Pipeline *                            branchNode::pipeline() const { return (&pipeline_class_048); }

const Pipeline *                         branchConNode::pipeline_class() { return (&pipeline_class_049); }
const Pipeline *                         branchConNode::pipeline() const { return (&pipeline_class_049); }

const Pipeline *                        branchConUNode::pipeline_class() { return (&pipeline_class_049); }
const Pipeline *                        branchConUNode::pipeline() const { return (&pipeline_class_049); }

const Pipeline *                  cmpI_imm0_branchNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                  cmpI_imm0_branchNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                  cmpL_imm0_branchNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                  cmpL_imm0_branchNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                  cmpP_imm0_branchNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                  cmpP_imm0_branchNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                  cmpN_imm0_branchNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                  cmpN_imm0_branchNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *        cmpP_narrowOop_imm0_branchNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *        cmpP_narrowOop_imm0_branchNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                 cmpUI_imm0_branchNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                 cmpUI_imm0_branchNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                 cmpUL_imm0_branchNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                 cmpUL_imm0_branchNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                  cmpL_branch_signNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                  cmpL_branch_signNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                  cmpI_branch_signNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                  cmpI_branch_signNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                   cmpL_branch_bitNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                   cmpL_branch_bitNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                   cmpI_branch_bitNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                   cmpI_branch_bitNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *              far_cmpL_branch_signNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *              far_cmpL_branch_signNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *              far_cmpI_branch_signNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *              far_cmpI_branch_signNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *               far_cmpL_branch_bitNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *               far_cmpL_branch_bitNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *               far_cmpI_branch_bitNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *               far_cmpI_branch_bitNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                          cmpL_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                          cmpL_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                          cmpI_andNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                          cmpI_andNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      cmpL_and_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      cmpL_and_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                      cmpI_and_regNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                      cmpI_and_regNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                     branchLoopEndNode::pipeline_class() { return (&pipeline_class_048); }
const Pipeline *                     branchLoopEndNode::pipeline() const { return (&pipeline_class_048); }

const Pipeline *                       cmpFastLockNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                       cmpFastLockNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                     cmpFastUnlockNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                     cmpFastUnlockNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *            cmpFastLockLightweightNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *            cmpFastLockLightweightNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *          cmpFastUnlockLightweightNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *          cmpFastUnlockLightweightNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                         safePointNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                         safePointNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *              CallStaticJavaDirectNode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *              CallStaticJavaDirectNode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *             CallDynamicJavaDirectNode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *             CallDynamicJavaDirectNode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                 CallRuntimeDirectNode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                 CallRuntimeDirectNode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                    CallLeafDirectNode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                    CallLeafDirectNode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                CallLeafNoFPDirectNode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                CallLeafNoFPDirectNode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                    TailCalljmpIndNode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                    TailCalljmpIndNode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                        TailjmpIndNode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                        TailjmpIndNode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                   CreateExceptionNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                   CreateExceptionNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  RethrowExceptionNode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                  RethrowExceptionNode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                               RetNode::pipeline_class() { return (&pipeline_class_048); }
const Pipeline *                               RetNode::pipeline() const { return (&pipeline_class_048); }

const Pipeline *                ShouldNotReachHereNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                ShouldNotReachHereNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               partialSubtypeCheckNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *               partialSubtypeCheckNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *         partialSubtypeCheckVsZeroNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *         partialSubtypeCheckVsZeroNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   string_compareUNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   string_compareUNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   string_compareLNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   string_compareLNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                  string_compareULNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                  string_compareULNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                  string_compareLUNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                  string_compareLUNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *              string_compareLL_sveNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *              string_compareLL_sveNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *              string_compareLU_sveNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *              string_compareLU_sveNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *              string_compareUL_sveNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *              string_compareUL_sveNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *              string_compareUU_sveNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *              string_compareUU_sveNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                  string_indexofUUNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                  string_indexofUUNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                  string_indexofLLNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                  string_indexofLLNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                  string_indexofULNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                  string_indexofULNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *              string_indexof_conUUNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *              string_indexof_conUUNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *              string_indexof_conLLNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *              string_indexof_conLLNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *              string_indexof_conULNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *              string_indexof_conULNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *               string_indexof_charNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *               string_indexof_charNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *              stringL_indexof_charNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *              stringL_indexof_charNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *          stringL_indexof_char_sveNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *          stringL_indexof_char_sveNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *          stringU_indexof_char_sveNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *          stringU_indexof_char_sveNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                    string_equalsLNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                    string_equalsLNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                     array_equalsBNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                     array_equalsBNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                     array_equalsCNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                     array_equalsCNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   count_positivesNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   count_positivesNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   string_compressNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   string_compressNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    string_inflateNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                    string_inflateNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                  encode_iso_arrayNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                  encode_iso_arrayNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                encode_ascii_arrayNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                encode_ascii_arrayNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                 compressBitsI_regNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 compressBitsI_regNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              compressBitsI_memconNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              compressBitsI_memconNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 compressBitsL_regNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 compressBitsL_regNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              compressBitsL_memconNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              compressBitsL_memconNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   expandBitsI_regNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   expandBitsI_regNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                expandBitsI_memconNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                expandBitsI_memconNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   expandBitsL_regNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   expandBitsL_regNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                expandBitsL_memconNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                expandBitsL_memconNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          tlsLoadPNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                          tlsLoadPNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                            loadV2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            loadV2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           storeV2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           storeV2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            loadV4Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            loadV4Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           storeV4Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           storeV4Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            loadV8Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            loadV8Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           storeV8Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           storeV8Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           loadV16Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           loadV16Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          storeV16Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          storeV16Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             loadVNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             loadVNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            storeVNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            storeVNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      loadV_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      loadV_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     storeV_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     storeV_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vloadconNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vloadconNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vaddBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vaddBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vaddSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vaddSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vaddINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vaddINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vaddLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vaddLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vaddFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vaddFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vaddDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vaddDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vaddB_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vaddB_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vaddS_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vaddS_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vaddI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vaddI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vaddL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vaddL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vaddF_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vaddF_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vaddD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vaddD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vaddImmBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vaddImmBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vaddImmB_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vaddImmB_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vaddImmSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vaddImmSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vaddImmS_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vaddImmS_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vaddImmINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vaddImmINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vaddImmI_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vaddImmI_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vaddImmLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vaddImmLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vaddImmL_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vaddImmL_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vsubBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vsubBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vsubSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vsubSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vsubINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vsubINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vsubLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vsubLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vsubFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vsubFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vsubDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vsubDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vsubB_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vsubB_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vsubS_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vsubS_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vsubI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vsubI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vsubL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vsubL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vsubF_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vsubF_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vsubD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vsubD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vmulB_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vmulB_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmulB_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmulB_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vmulS_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vmulS_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmulS_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmulS_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vmulI_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vmulI_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmulI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmulI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vmulL_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vmulL_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmulL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmulL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vmulFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vmulFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vmulDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vmulDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vmulB_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vmulB_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vmulS_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vmulS_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vmulI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vmulI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vmulL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vmulL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vmulF_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vmulF_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vmulD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vmulD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vdivF_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vdivF_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vdivF_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vdivF_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vdivD_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vdivD_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vdivD_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vdivD_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vdivF_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vdivF_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vdivD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vdivD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                              vandNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                              vandNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vand_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vand_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vandImmBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vandImmBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vandImmB_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vandImmB_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vandImmSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vandImmSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vandImmS_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vandImmS_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vandImmINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vandImmINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vandImmI_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vandImmI_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vandImmLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vandImmLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vandImmL_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vandImmL_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                               vorNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                               vorNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vor_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vor_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vorImmBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vorImmBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vorImmB_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vorImmB_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vorImmSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vorImmSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vorImmS_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vorImmS_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vorImmINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vorImmINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vorImmI_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vorImmI_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vorImmLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vorImmLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vorImmL_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vorImmL_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                              vxorNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                              vxorNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vxor_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vxor_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vxorImmBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vxorImmBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vxorImmB_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vxorImmB_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vxorImmSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vxorImmSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vxorImmS_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vxorImmS_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vxorImmINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vxorImmINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vxorImmI_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vxorImmI_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vxorImmLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vxorImmLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vxorImmL_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vxorImmL_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        veor3_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        veor3_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      veor3_neon_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      veor3_neon_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         veor3_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         veor3_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       veor3_sve_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       veor3_sve_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vnotINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vnotINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vnotI_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vnotI_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vnotLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vnotLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vnotL_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vnotL_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vnotI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vnotI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vnotL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vnotL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vand_notINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vand_notINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vand_notI_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vand_notI_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vand_notI_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vand_notI_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vand_notI_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vand_notI_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vand_notLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vand_notLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vand_notL_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vand_notL_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vand_notL_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vand_notL_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vand_notL_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vand_notL_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  vand_notI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  vand_notI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                vand_notI_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                vand_notI_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  vand_notL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  vand_notL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                vand_notL_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                vand_notL_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vabsBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vabsBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vabsSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vabsSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vabsINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vabsINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vabsLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vabsLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vabsFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vabsFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vabsDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vabsDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vabsB_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vabsB_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vabsS_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vabsS_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vabsI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vabsI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vabsL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vabsL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vabsF_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vabsF_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vabsD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vabsD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vfabd_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vfabd_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vfabd_neon_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vfabd_neon_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vfabd_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vfabd_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vfabd_sve_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vfabd_sve_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vfabd_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vfabd_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vfabd_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vfabd_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vnegINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vnegINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vnegLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vnegLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vnegFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vnegFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vnegDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vnegDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vnegI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vnegI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vnegL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vnegL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vnegF_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vnegF_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vnegD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vnegD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vsqrtFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vsqrtFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vsqrtDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vsqrtDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vsqrtF_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vsqrtF_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vsqrtD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vsqrtD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vminL_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vminL_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vminL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vminL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmin_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmin_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vmin_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vmin_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vmin_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vmin_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vmaxL_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vmaxL_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmaxL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmaxL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmax_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmax_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vmax_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vmax_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vmax_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vmax_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                              vmlaNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                              vmlaNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vmla_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vmla_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vmla_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vmla_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vmla_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vmla_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vmla_3Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vmla_3Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vmla_4Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vmla_4Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vmlaLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vmlaLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vmlaL_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vmlaL_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vmla_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vmla_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmla_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmla_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmla_masked_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmla_masked_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmla_masked_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmla_masked_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vfmlaNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vfmlaNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vfmla_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vfmla_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vfmad_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vfmad_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vfmad_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vfmad_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                              vmlsNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                              vmlsNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vmls_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vmls_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vmls_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vmls_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vmlsLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vmlsLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vmls_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vmls_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmls_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmls_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmls_masked_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmls_masked_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmls_masked_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmls_masked_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                             vfmlsNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                             vfmlsNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vfmls_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vfmls_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vfmsb_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vfmsb_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vfmsb_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vfmsb_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vfnmlaNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vfnmlaNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vfnmla_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vfnmla_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vfnmad_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vfnmad_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vfnmad_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vfnmad_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            vfnmlsNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                            vfnmlsNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vfnmls_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vfnmls_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vfnmsb_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vfnmsb_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vfnmsb_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vfnmsb_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vmuladdS2INode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vmuladdS2INode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vshiftcntLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vshiftcntLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vshiftcntRNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vshiftcntRNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vlsl_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vlsl_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsl_neon_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsl_neon_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsl_neon_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsl_neon_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsl_neon_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsl_neon_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vlsl_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vlsl_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsl_sve_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsl_sve_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsl_sve_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsl_sve_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsl_sve_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsl_sve_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vasr_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vasr_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasr_neon_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasr_neon_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasr_neon_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasr_neon_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasr_neon_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasr_neon_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vasr_neon_varNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vasr_neon_varNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vasr_neon_var_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vasr_neon_var_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vasr_neon_var_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vasr_neon_var_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vasr_neon_var_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vasr_neon_var_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vasr_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vasr_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vasr_sve_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vasr_sve_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vasr_sve_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vasr_sve_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vasr_sve_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vasr_sve_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vlsr_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vlsr_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsr_neon_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsr_neon_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsr_neon_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsr_neon_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsr_neon_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsr_neon_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vlsr_neon_varNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vlsr_neon_varNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vlsr_neon_var_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vlsr_neon_var_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vlsr_neon_var_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vlsr_neon_var_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vlsr_neon_var_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vlsr_neon_var_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vlsr_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vlsr_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsr_sve_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsr_sve_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsr_sve_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsr_sve_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsr_sve_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsr_sve_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vlsl_immNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vlsl_immNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsl_imm_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsl_imm_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsl_imm_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsl_imm_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsl_imm_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsl_imm_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vasr_immNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vasr_immNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vasr_imm_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vasr_imm_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vasr_imm_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vasr_imm_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vasr_imm_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vasr_imm_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vlsr_immNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vlsr_immNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsr_imm_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsr_imm_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsr_imm_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsr_imm_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vlsr_imm_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vlsr_imm_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vasra_immNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vasra_immNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasra_imm_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasra_imm_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasra_imm_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasra_imm_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasra_imm_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasra_imm_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasra_imm_3Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasra_imm_3Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasra_imm_4Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasra_imm_4Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasra_imm_5Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasra_imm_5Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasra_imm_6Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasra_imm_6Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vlsra_immNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vlsra_immNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsra_imm_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsra_imm_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsra_imm_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsra_imm_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsra_imm_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsra_imm_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsra_imm_3Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsra_imm_3Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsra_imm_4Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsra_imm_4Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsra_imm_5Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsra_imm_5Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsra_imm_6Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsra_imm_6Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsl_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsl_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vlsl_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vlsl_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vlsl_masked_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vlsl_masked_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vlsl_masked_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vlsl_masked_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vasr_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vasr_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vasr_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vasr_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vasr_masked_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vasr_masked_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vasr_masked_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vasr_masked_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vlsr_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vlsr_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vlsr_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vlsr_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vlsr_masked_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vlsr_masked_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vlsr_masked_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vlsr_masked_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vlsl_imm_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vlsl_imm_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vlsl_imm_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vlsl_imm_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vlsl_imm_masked_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vlsl_imm_masked_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vlsl_imm_masked_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vlsl_imm_masked_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vasr_imm_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vasr_imm_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vasr_imm_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vasr_imm_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vasr_imm_masked_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vasr_imm_masked_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vasr_imm_masked_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vasr_imm_masked_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vlsr_imm_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vlsr_imm_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vlsr_imm_masked_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vlsr_imm_masked_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vlsr_imm_masked_1Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vlsr_imm_masked_1Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vlsr_imm_masked_2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vlsr_imm_masked_2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_addI_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_addI_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_addI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_addI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_addL_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_addL_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_addL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_addL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 reduce_add2F_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 reduce_add2F_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 reduce_add4F_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 reduce_add4F_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_addF_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_addF_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_addD_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_addD_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_addD_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_addD_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_addI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_addI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_addL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_addL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_addF_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_addF_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_addD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_addD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       reduce_mulINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       reduce_mulINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       reduce_mulLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       reduce_mulLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       reduce_mulFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       reduce_mulFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       reduce_mulDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       reduce_mulDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_andI_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_andI_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_andI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_andI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_andL_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_andL_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_andL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_andL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_andI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_andI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_andL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_andL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_orI_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_orI_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    reduce_orI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    reduce_orI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_orL_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_orL_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    reduce_orL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    reduce_orL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 reduce_orI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 reduce_orI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 reduce_orL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 reduce_orL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_xorI_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_xorI_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_xorI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_xorI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_xorL_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_xorL_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_xorL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_xorL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_xorI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_xorI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_xorL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_xorL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_maxI_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_maxI_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_maxI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_maxI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_maxL_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_maxL_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_maxL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_maxL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       reduce_maxFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       reduce_maxFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       reduce_maxDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       reduce_maxDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_maxI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_maxI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_maxL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_maxL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_maxF_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_maxF_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_maxD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_maxD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_minI_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_minI_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_minI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_minI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  reduce_minL_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  reduce_minL_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   reduce_minL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   reduce_minL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       reduce_minFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       reduce_minFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       reduce_minDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       reduce_minDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_minI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_minI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_minL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_minL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_minF_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_minF_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                reduce_minD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                reduce_minD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *             reinterpret_same_sizeNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *             reinterpret_same_sizeNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *         reinterpret_resize_le128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *         reinterpret_resize_le128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *         reinterpret_resize_gt128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *         reinterpret_resize_gt128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vzeroExtBtoXNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vzeroExtBtoXNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vzeroExtStoXNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vzeroExtStoXNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vzeroExtItoXNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vzeroExtItoXNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vcvtBtoXNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vcvtBtoXNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vcvtStoB_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vcvtStoB_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vcvtStoB_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vcvtStoB_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vcvtStoX_extendNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vcvtStoX_extendNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              vcvtItoX_narrow_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              vcvtItoX_narrow_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               vcvtItoX_narrow_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               vcvtItoX_narrow_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vcvtItoXNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vcvtItoXNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vcvtLtoI_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vcvtLtoI_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vcvtLtoI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vcvtLtoI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vcvtLtoF_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vcvtLtoF_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vcvtLtoF_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vcvtLtoF_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vcvtLtoDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vcvtLtoDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              vcvtFtoX_narrow_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              vcvtFtoX_narrow_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               vcvtFtoX_narrow_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               vcvtFtoX_narrow_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vcvtFtoXNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vcvtFtoXNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vcvtDtoI_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vcvtDtoI_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vcvtDtoI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vcvtDtoI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vcvtDtoLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vcvtDtoLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vcvtDtoF_64bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vcvtDtoF_64bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vcvtDtoF_gt64bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vcvtDtoF_gt64bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vcvtHFtoFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vcvtHFtoFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vcvtFtoHF_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vcvtFtoHF_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vcvtFtoHF_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vcvtFtoHF_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        replicateINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        replicateINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        replicateLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        replicateLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        replicateFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        replicateFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        replicateDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        replicateDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *             replicateI_imm_le128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *             replicateI_imm_le128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            replicateB_imm8_gt128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            replicateB_imm8_gt128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            replicateI_imm8_gt128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            replicateI_imm8_gt128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               replicateL_imm_128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               replicateL_imm_128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            replicateL_imm8_gt128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            replicateL_imm8_gt128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    insertI_le128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    insertI_le128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                insertI_index_lt32Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                insertI_index_lt32Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                insertI_index_ge32Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                insertI_index_ge32Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      insertL_128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      insertL_128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    insertL_gt128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    insertL_gt128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    insertF_le128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    insertF_le128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                insertF_index_lt32Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                insertF_index_lt32Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                insertF_index_ge32Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                insertF_index_ge32Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      insertD_128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      insertD_128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    insertD_gt128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    insertD_gt128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    extractUB_iregNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    extractUB_iregNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              extractUB_index_lt16Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              extractUB_index_lt16Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              extractUB_index_ge16Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              extractUB_index_ge16Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               extractB_index_lt16Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               extractB_index_lt16Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               extractB_index_ge16Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               extractB_index_ge16Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                extractS_index_lt8Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                extractS_index_lt8Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                extractS_index_ge8Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                extractS_index_ge8Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                extractI_index_lt4Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                extractI_index_lt4Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                extractI_index_ge4Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                extractI_index_ge4Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                extractL_index_lt2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                extractL_index_lt2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                extractL_index_ge2Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                extractL_index_ge2Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          extractFNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          extractFNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          extractDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          extractDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vloadmask_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vloadmask_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vloadmaskB_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vloadmaskB_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              vloadmask_extend_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              vloadmask_extend_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vloadmaskB_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vloadmaskB_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *           vloadmask_extend_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *           vloadmask_extend_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  vstoremaskB_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  vstoremaskB_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            vstoremask_narrow_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            vstoremask_narrow_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vstoremaskB_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vstoremaskB_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *             vstoremask_narrow_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *             vstoremask_narrow_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vloadmask_loadVNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vloadmask_loadVNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            vloadmask_loadV_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            vloadmask_loadV_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *             vloadmask_loadVMaskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *             vloadmask_loadVMaskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *      vloadmask_loadVMasked_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *      vloadmask_loadVMasked_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 storeV_vstoremaskNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 storeV_vstoremaskNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *          storeV_vstoremask_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *          storeV_vstoremask_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *           storeVMasked_vstoremaskNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *           storeVMasked_vstoremaskNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *    storeVMasked_vstoremask_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *    storeVMasked_vstoremask_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmask_andNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmask_andNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vmask_orNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vmask_orNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmask_xorNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmask_xorNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vmask_and_notINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vmask_and_notINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vmask_and_notLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vmask_and_notLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmaskcmp_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmaskcmp_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               vmaskcmp_zeroI_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               vmaskcmp_zeroI_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               vmaskcmp_zeroL_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               vmaskcmp_zeroL_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               vmaskcmp_zeroF_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               vmaskcmp_zeroF_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               vmaskcmp_zeroD_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               vmaskcmp_zeroD_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      vmaskcmp_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      vmaskcmp_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vmaskcmp_immI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vmaskcmp_immI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                vmaskcmpU_immI_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                vmaskcmpU_immI_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vmaskcmp_immL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vmaskcmp_immL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                vmaskcmpU_immL_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                vmaskcmpU_immL_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vmaskcmp_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vmaskcmp_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *         vmaskcast_same_esize_neonNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *         vmaskcast_same_esize_neonNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *             vmaskcast_extend_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *             vmaskcast_extend_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *             vmaskcast_narrow_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *             vmaskcast_narrow_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *          vmaskcast_same_esize_sveNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *          vmaskcast_same_esize_sveNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *              vmaskcast_extend_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              vmaskcast_extend_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              vmaskcast_narrow_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              vmaskcast_narrow_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *      vmask_reinterpret_same_esizeNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *      vmask_reinterpret_same_esizeNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *      vmask_reinterpret_diff_esizeNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *      vmask_reinterpret_diff_esizeNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              vmask_truecount_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              vmask_truecount_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               vmask_truecount_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               vmask_truecount_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *         vstoremask_truecount_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *         vstoremask_truecount_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              vmask_firsttrue_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              vmask_firsttrue_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               vmask_firsttrue_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               vmask_firsttrue_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *            vmask_firsttrue_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *            vmask_firsttrue_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               vmask_lasttrue_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               vmask_lasttrue_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                vmask_lasttrue_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                vmask_lasttrue_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vmask_tolong_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vmask_tolong_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  vmask_tolong_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  vmask_tolong_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vmask_fromlongNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vmask_fromlongNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmaskAll_immINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmaskAll_immINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmaskAllINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmaskAllINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  vmaskAllI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  vmaskAllI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmaskAll_immLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmaskAll_immLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vmaskAllLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vmaskAllLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  vmaskAllL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  vmaskAllL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vmask_gen_INode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                       vmask_gen_INode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                       vmask_gen_LNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vmask_gen_LNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmask_gen_immNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmask_gen_immNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vmask_gen_subNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vmask_gen_subNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vpopcountINode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vpopcountINode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vpopcountLNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vpopcountLNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vpopcountI_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vpopcountI_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vpopcountL_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vpopcountL_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vblend_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vblend_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vblend_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vblend_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vround_le128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vround_le128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vround_le128b_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vround_le128b_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vround_gt128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vround_gt128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vround_gt128b_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vround_gt128b_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vroundDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vroundDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                vtest_anytrue_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                vtest_anytrue_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vtest_anytrue_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vtest_anytrue_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                vtest_alltrue_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                vtest_alltrue_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 vtest_alltrue_sveNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 vtest_alltrue_sveNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       loadshuffleNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       loadshuffleNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                 rearrange_HS_neonNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                 rearrange_HS_neonNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         rearrangeNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         rearrangeNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      gather_loadSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      gather_loadSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      gather_loadDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                      gather_loadDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               gather_loadS_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               gather_loadS_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               gather_loadD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               gather_loadD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    scatter_storeSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    scatter_storeSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    scatter_storeDNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    scatter_storeDNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *             scatter_storeS_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *             scatter_storeS_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *             scatter_storeD_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *             scatter_storeD_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                vcountLeadingZerosNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                vcountLeadingZerosNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *         vcountLeadingZeros_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *         vcountLeadingZeros_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               vcountTrailingZerosNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               vcountTrailingZerosNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *        vcountTrailingZeros_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *        vcountTrailingZeros_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                          vreverseNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          vreverseNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                   vreverse_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                   vreverse_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vreverseBytesNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vreverseBytesNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              vreverseBytes_maskedNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              vreverseBytes_maskedNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     populateindexNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     populateindexNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         mcompressNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         mcompressNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                         vcompressNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                         vcompressNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vcompressBNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vcompressBNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                        vcompressSNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                        vcompressSNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                           vexpandNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                           vexpandNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vsignum_le128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vsignum_le128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  vsignum_le128b_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  vsignum_le128b_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                    vsignum_gt128bNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                    vsignum_gt128bNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                  vsignum_gt128b_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  vsignum_gt128b_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     vcompressBitsNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     vcompressBitsNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       vexpandBitsNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                       vexpandBitsNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *        compareAndSwapP_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *        compareAndSwapP_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *        compareAndSwapN_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *        compareAndSwapN_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *     compareAndSwapPAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *     compareAndSwapPAcq_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *     compareAndSwapNAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *     compareAndSwapNAcq_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *    compareAndExchangeN_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *    compareAndExchangeN_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *    compareAndExchangeP_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *    compareAndExchangeP_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline * compareAndExchangeNAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline * compareAndExchangeNAcq_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline * compareAndExchangePAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline * compareAndExchangePAcq_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *    weakCompareAndSwapN_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *    weakCompareAndSwapN_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *    weakCompareAndSwapP_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *    weakCompareAndSwapP_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline * weakCompareAndSwapNAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline * weakCompareAndSwapNAcq_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline * weakCompareAndSwapPAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline * weakCompareAndSwapPAcq_shenandoahNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                            xLoadPNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                            xLoadPNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                    xLoadPVolatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    xLoadPVolatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                  xCompareAndSwapPNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  xCompareAndSwapPNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                xCompareAndSwapP_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                xCompareAndSwapP_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               xCompareAndSwapPAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               xCompareAndSwapPAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *             xCompareAndSwapPAcq_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *             xCompareAndSwapPAcq_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              xCompareAndExchangePNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              xCompareAndExchangePNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *           xCompareAndExchangePAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *           xCompareAndExchangePAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       xGetAndSetPNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                       xGetAndSetPNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                    xGetAndSetPAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    xGetAndSetPAcqNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                            zLoadPNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                            zLoadPNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                    zLoadPVolatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    zLoadPVolatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                           zStorePNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                           zStorePNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                   zStorePVolatileNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                   zStorePVolatileNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                  zCompareAndSwapPNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                  zCompareAndSwapPNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                zCompareAndSwapP_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                zCompareAndSwapP_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *               zCompareAndSwapPAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *               zCompareAndSwapPAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *             zCompareAndSwapPAcq_0Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *             zCompareAndSwapPAcq_0Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *              zCompareAndExchangePNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *              zCompareAndExchangePNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *           zCompareAndExchangePAcqNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *           zCompareAndExchangePAcqNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                       zGetAndSetPNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                       zGetAndSetPNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                    zGetAndSetPAcqNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                    zGetAndSetPAcqNode::pipeline() const { return (&pipeline_class_051); }
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
