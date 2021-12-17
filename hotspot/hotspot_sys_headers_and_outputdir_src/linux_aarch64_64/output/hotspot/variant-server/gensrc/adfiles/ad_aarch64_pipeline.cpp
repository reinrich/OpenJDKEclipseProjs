#line 1 "ad_aarch64_pipeline.cpp"
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
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_S5         // BRANCH
};

static const uint pipeline_res_cycles_001[9] = {
  1, // INS0
  1, // INS1
  0, // INS01
  0, // ALU0
  0, // ALU1
  0, // ALU
  0, // MAC
  0, // DIV
  1  // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_001[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000010)) 
};

static const Pipeline pipeline_class_001((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_001,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_dop_reg_reg_d"
static const Pipeline pipeline_class_002((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_001,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_uop_s"
static const enum machPipelineStages pipeline_reads_002[1] = {
  stage_S1 
};

static const Pipeline pipeline_class_003((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_uop_d"
static const Pipeline pipeline_class_004((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_d2f"
static const Pipeline pipeline_class_005((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_f2d"
static const Pipeline pipeline_class_006((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_f2i"
static const Pipeline pipeline_class_007((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_f2l"
static const Pipeline pipeline_class_008((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_i2f"
static const Pipeline pipeline_class_009((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_l2f"
static const Pipeline pipeline_class_010((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_d2i"
static const Pipeline pipeline_class_011((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_d2l"
static const Pipeline pipeline_class_012((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_i2d"
static const Pipeline pipeline_class_013((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_l2d"
static const Pipeline pipeline_class_014((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "fp_div_s"
static const enum machPipelineStages pipeline_res_stages_002[9] = {
  stage_S0,        // INS0
  stage_undefined, // INS1
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_S5         // BRANCH
};

static const uint pipeline_res_cycles_002[9] = {
  1, // INS0
  0, // INS1
  0, // INS01
  0, // ALU0
  0, // ALU1
  0, // ALU
  0, // MAC
  0, // DIV
  1  // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_002[2] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000010)) 
};

static const Pipeline pipeline_class_015((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_001,
   (enum machPipelineStages * const) pipeline_res_stages_002,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "fp_div_d"
static const Pipeline pipeline_class_016((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_001,
   (enum machPipelineStages * const) pipeline_res_stages_002,
  (uint * const) pipeline_res_cycles_002,
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
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_S3         // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_003[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_017((uint)stage_S3, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_003,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "fp_cond_reg_reg_d"
static const Pipeline pipeline_class_018((uint)stage_S3, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_003,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "fp_imm_s"
static const Pipeline pipeline_class_019((uint)stage_S3, 0, false, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "fp_imm_d"
static const Pipeline pipeline_class_020((uint)stage_S3, 0, false, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "fp_load_constant_s"
static const enum machPipelineStages pipeline_res_stages_004[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_S4         // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_004[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000008)) 
};

static const Pipeline pipeline_class_021((uint)stage_S4, 0, false, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_004,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_004[0]));

// Pipeline Class "fp_load_constant_d"
static const Pipeline pipeline_class_022((uint)stage_S4, 0, false, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_004,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_004[0]));

// Pipeline Class "vmul64"
static const enum machPipelineStages pipeline_reads_004[2] = {
  stage_S1,
  stage_S1 
};

static const Pipeline pipeline_class_023((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "vmul128"
static const Pipeline pipeline_class_024((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_002,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "vmla64"
static const Pipeline pipeline_class_025((uint)stage_undefined, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_003,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "vmla128"
static const Pipeline pipeline_class_026((uint)stage_undefined, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_003,
   (enum machPipelineStages * const) pipeline_res_stages_002,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "vdop64"
static const enum machPipelineStages pipeline_reads_005[2] = {
  stage_S2,
  stage_S2 
};

static const Pipeline pipeline_class_027((uint)stage_S4, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_005,
   (enum machPipelineStages * const) pipeline_res_stages_004,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_004[0]));

// Pipeline Class "vdop128"
static const enum machPipelineStages pipeline_res_stages_005[9] = {
  stage_S0,        // INS0
  stage_undefined, // INS1
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_S4         // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_005[2] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000008)) 
};

static const Pipeline pipeline_class_028((uint)stage_S4, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_005,
   (enum machPipelineStages * const) pipeline_res_stages_005,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "vlogical64"
static const Pipeline pipeline_class_029((uint)stage_S3, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_005,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vlogical128"
static const enum machPipelineStages pipeline_res_stages_006[9] = {
  stage_S0,        // INS0
  stage_undefined, // INS1
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_S3         // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_006[2] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_030((uint)stage_S3, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_005,
   (enum machPipelineStages * const) pipeline_res_stages_006,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_006[0]));

// Pipeline Class "vshift64"
static const Pipeline pipeline_class_031((uint)stage_S3, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vshift128"
static const Pipeline pipeline_class_032((uint)stage_S3, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_006,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_006[0]));

// Pipeline Class "vshift64_imm"
static const enum machPipelineStages pipeline_reads_006[2] = {
  stage_S1,
  stage_undefined 
};

static const Pipeline pipeline_class_033((uint)stage_S3, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_006,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vshift128_imm"
static const Pipeline pipeline_class_034((uint)stage_S3, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_006,
   (enum machPipelineStages * const) pipeline_res_stages_006,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_006[0]));

// Pipeline Class "vdop_fp64"
static const Pipeline pipeline_class_035((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "vdop_fp128"
static const Pipeline pipeline_class_036((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_002,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "vmuldiv_fp64"
static const Pipeline pipeline_class_037((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_002,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "vmuldiv_fp128"
static const Pipeline pipeline_class_038((uint)stage_S5, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_002,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "vsqrt_fp128"
static const Pipeline pipeline_class_039((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_002,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "vunop_fp64"
static const Pipeline pipeline_class_040((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_001,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "vunop_fp128"
static const Pipeline pipeline_class_041((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_002,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "vdup_reg_reg64"
static const Pipeline pipeline_class_042((uint)stage_S3, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vdup_reg_reg128"
static const Pipeline pipeline_class_043((uint)stage_S3, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vdup_reg_freg64"
static const Pipeline pipeline_class_044((uint)stage_S3, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vdup_reg_freg128"
static const Pipeline pipeline_class_045((uint)stage_S3, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vdup_reg_dreg128"
static const Pipeline pipeline_class_046((uint)stage_S3, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vmovi_reg_imm64"
static const Pipeline pipeline_class_047((uint)stage_S3, 0, false, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vmovi_reg_imm128"
static const Pipeline pipeline_class_048((uint)stage_S3, 0, false, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_006,
  (uint * const) pipeline_res_cycles_002,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_006[0]));

// Pipeline Class "vload_reg_mem64"
static const enum machPipelineStages pipeline_reads_007[1] = {
  stage_S0 
};

static const Pipeline pipeline_class_049((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_007,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vload_reg_mem128"
static const Pipeline pipeline_class_050((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_007,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vstore_reg_mem64"
static const enum machPipelineStages pipeline_reads_008[2] = {
  stage_S2,
  stage_S0 
};

static const Pipeline pipeline_class_051((uint)stage_undefined, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_008,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "vstore_reg_mem128"
static const Pipeline pipeline_class_052((uint)stage_undefined, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_008,
   (enum machPipelineStages * const) pipeline_res_stages_003,
  (uint * const) pipeline_res_cycles_001,
  Pipeline_Use(0x103, 0x100, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "ialu_reg_reg"
static const enum machPipelineStages pipeline_res_stages_007[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_S2,        // INS01
  stage_S2,        // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined  // BRANCH
};

static const uint pipeline_res_cycles_003[9] = {
  1, // INS0
  1, // INS1
  1, // INS01
  1, // ALU0
  0, // ALU1
  0, // ALU
  0, // MAC
  0, // DIV
  0  // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_007[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x00c, 2, 3, true,  Pipeline_Use_Cycle_Mask(0x00000002)) 
};

static const Pipeline pipeline_class_053((uint)stage_S2, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_007,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "ialu_reg_reg_shift"
static const enum machPipelineStages pipeline_reads_009[3] = {
  stage_S1,
  stage_S0,
  stage_undefined 
};

static const Pipeline pipeline_class_054((uint)stage_S2, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_009,
   (enum machPipelineStages * const) pipeline_res_stages_007,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "ialu_reg_shift"
static const Pipeline pipeline_class_055((uint)stage_S2, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_007,
   (enum machPipelineStages * const) pipeline_res_stages_007,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "ialu_reg_reg_vshift"
static const enum machPipelineStages pipeline_reads_010[2] = {
  stage_S0,
  stage_S0 
};

static const enum machPipelineStages pipeline_res_stages_008[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_S1,        // INS01
  stage_S1,        // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined  // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_008[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x00c, 2, 3, true,  Pipeline_Use_Cycle_Mask(0x00000001)) 
};

static const Pipeline pipeline_class_056((uint)stage_S1, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_010,
   (enum machPipelineStages * const) pipeline_res_stages_008,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_008[0]));

// Pipeline Class "ialu_reg_reg_extr"
static const enum machPipelineStages pipeline_res_stages_009[9] = {
  stage_undefined, // INS0
  stage_S0,        // INS1
  stage_S1,        // INS01
  stage_S1,        // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined  // BRANCH
};

static const uint pipeline_res_cycles_004[9] = {
  0, // INS0
  1, // INS1
  1, // INS01
  1, // ALU0
  0, // ALU1
  0, // ALU
  0, // MAC
  0, // DIV
  0  // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_009[2] = {
  Pipeline_Use_Element(0x002, 1, 1, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x00c, 2, 3, true,  Pipeline_Use_Cycle_Mask(0x00000001)) 
};

static const Pipeline pipeline_class_057((uint)stage_S2, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_010,
   (enum machPipelineStages * const) pipeline_res_stages_009,
  (uint * const) pipeline_res_cycles_004,
  Pipeline_Use(0x00e, 0x002, 2, (Pipeline_Use_Element *)&pipeline_res_mask_009[0]));

// Pipeline Class "ialu_reg"
static const Pipeline pipeline_class_058((uint)stage_S2, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_007,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "ialu_reg_imm"
static const Pipeline pipeline_class_059((uint)stage_S2, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_007,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "ialu_imm"
static const Pipeline pipeline_class_060((uint)stage_S1, 0, false, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_008,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_008[0]));

// Pipeline Class "icmp_reg_reg"
static const Pipeline pipeline_class_061((uint)stage_S2, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_007,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "icmp_reg_imm"
static const Pipeline pipeline_class_062((uint)stage_S2, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_007,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "icond_none"
static const Pipeline pipeline_class_063((uint)stage_S2, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_007,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "icond_reg_reg"
static const Pipeline pipeline_class_064((uint)stage_S2, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_003,
   (enum machPipelineStages * const) pipeline_res_stages_007,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "icond_reg"
static const Pipeline pipeline_class_065((uint)stage_S2, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_004,
   (enum machPipelineStages * const) pipeline_res_stages_007,
  (uint * const) pipeline_res_cycles_003,
  Pipeline_Use(0x00f, 0x000, 2, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "imul_reg_reg"
static const enum machPipelineStages pipeline_res_stages_010[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_S3,        // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined  // BRANCH
};

static const uint pipeline_res_cycles_005[9] = {
  1, // INS0
  1, // INS1
  0, // INS01
  0, // ALU0
  1, // ALU1
  0, // ALU
  0, // MAC
  0, // DIV
  0  // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_010[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x010, 4, 4, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_066((uint)stage_S3, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_010,
   (enum machPipelineStages * const) pipeline_res_stages_010,
  (uint * const) pipeline_res_cycles_005,
  Pipeline_Use(0x013, 0x010, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "imac_reg_reg"
static const enum machPipelineStages pipeline_reads_011[3] = {
  stage_S0,
  stage_S0,
  stage_S0 
};

static const Pipeline pipeline_class_067((uint)stage_S3, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_011,
   (enum machPipelineStages * const) pipeline_res_stages_010,
  (uint * const) pipeline_res_cycles_005,
  Pipeline_Use(0x013, 0x010, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "lmul_reg_reg"
static const Pipeline pipeline_class_068((uint)stage_S3, 2, true, 3, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_010,
   (enum machPipelineStages * const) pipeline_res_stages_010,
  (uint * const) pipeline_res_cycles_005,
  Pipeline_Use(0x013, 0x010, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "lmac_reg_reg"
static const Pipeline pipeline_class_069((uint)stage_S3, 3, true, 3, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_011,
   (enum machPipelineStages * const) pipeline_res_stages_010,
  (uint * const) pipeline_res_cycles_005,
  Pipeline_Use(0x013, 0x010, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "idiv_reg_reg"
static const enum machPipelineStages pipeline_res_stages_011[9] = {
  stage_S0,        // INS0
  stage_undefined, // INS1
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_S3,        // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined  // BRANCH
};

static const uint pipeline_res_cycles_006[9] = {
  1, // INS0
  0, // INS1
  0, // INS01
  0, // ALU0
  0, // ALU1
  1, // ALU
  0, // MAC
  0, // DIV
  0  // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_011[2] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x020, 5, 5, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_070((uint)stage_S3, 2, true, 8, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_010,
   (enum machPipelineStages * const) pipeline_res_stages_011,
  (uint * const) pipeline_res_cycles_006,
  Pipeline_Use(0x021, 0x021, 2, (Pipeline_Use_Element *)&pipeline_res_mask_011[0]));

// Pipeline Class "ldiv_reg_reg"
static const Pipeline pipeline_class_071((uint)stage_S3, 2, true, 16, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_010,
   (enum machPipelineStages * const) pipeline_res_stages_011,
  (uint * const) pipeline_res_cycles_006,
  Pipeline_Use(0x021, 0x021, 2, (Pipeline_Use_Element *)&pipeline_res_mask_011[0]));

// Pipeline Class "iload_prefetch"
static const enum machPipelineStages pipeline_res_stages_012[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_S3,        // DIV
  stage_undefined  // BRANCH
};

static const uint pipeline_res_cycles_007[9] = {
  1, // INS0
  1, // INS1
  0, // INS01
  0, // ALU0
  0, // ALU1
  0, // ALU
  0, // MAC
  1, // DIV
  0  // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_012[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_072((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_007,
   (enum machPipelineStages * const) pipeline_res_stages_012,
  (uint * const) pipeline_res_cycles_007,
  Pipeline_Use(0x083, 0x080, 2, (Pipeline_Use_Element *)&pipeline_res_mask_012[0]));

// Pipeline Class "iload_reg_mem"
static const Pipeline pipeline_class_073((uint)stage_S3, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_007,
   (enum machPipelineStages * const) pipeline_res_stages_012,
  (uint * const) pipeline_res_cycles_007,
  Pipeline_Use(0x083, 0x080, 2, (Pipeline_Use_Element *)&pipeline_res_mask_012[0]));

// Pipeline Class "iload_reg_reg"
static const Pipeline pipeline_class_074((uint)stage_S3, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_007,
   (enum machPipelineStages * const) pipeline_res_stages_012,
  (uint * const) pipeline_res_cycles_007,
  Pipeline_Use(0x083, 0x080, 2, (Pipeline_Use_Element *)&pipeline_res_mask_012[0]));

// Pipeline Class "istore_mem"
static const Pipeline pipeline_class_075((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_007,
   (enum machPipelineStages * const) pipeline_res_stages_012,
  (uint * const) pipeline_res_cycles_007,
  Pipeline_Use(0x083, 0x080, 2, (Pipeline_Use_Element *)&pipeline_res_mask_012[0]));

// Pipeline Class "istore_reg_mem"
static const Pipeline pipeline_class_076((uint)stage_undefined, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_008,
   (enum machPipelineStages * const) pipeline_res_stages_012,
  (uint * const) pipeline_res_cycles_007,
  Pipeline_Use(0x083, 0x080, 2, (Pipeline_Use_Element *)&pipeline_res_mask_012[0]));

// Pipeline Class "istore_reg_reg"
static const enum machPipelineStages pipeline_reads_012[2] = {
  stage_S0,
  stage_S2 
};

static const Pipeline pipeline_class_077((uint)stage_undefined, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_012,
   (enum machPipelineStages * const) pipeline_res_stages_012,
  (uint * const) pipeline_res_cycles_007,
  Pipeline_Use(0x083, 0x080, 2, (Pipeline_Use_Element *)&pipeline_res_mask_012[0]));

// Pipeline Class "pipe_branch"
static const enum machPipelineStages pipeline_res_stages_013[9] = {
  stage_S0,        // INS0
  stage_S0,        // INS1
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_S1,        // MAC
  stage_undefined, // DIV
  stage_undefined  // BRANCH
};

static const uint pipeline_res_cycles_008[9] = {
  1, // INS0
  1, // INS1
  0, // INS01
  0, // ALU0
  0, // ALU1
  0, // ALU
  1, // MAC
  0, // DIV
  0  // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_013[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x040, 6, 6, false, Pipeline_Use_Cycle_Mask(0x00000001)) 
};

static const Pipeline pipeline_class_078((uint)stage_undefined, 0, false, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_013,
  (uint * const) pipeline_res_cycles_008,
  Pipeline_Use(0x043, 0x040, 2, (Pipeline_Use_Element *)&pipeline_res_mask_013[0]));

// Pipeline Class "pipe_branch_cond"
static const Pipeline pipeline_class_079((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_013,
  (uint * const) pipeline_res_cycles_008,
  Pipeline_Use(0x043, 0x040, 2, (Pipeline_Use_Element *)&pipeline_res_mask_013[0]));

// Pipeline Class "pipe_cmp_branch"
static const Pipeline pipeline_class_080((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages * const) pipeline_reads_002,
   (enum machPipelineStages * const) pipeline_res_stages_013,
  (uint * const) pipeline_res_cycles_008,
  Pipeline_Use(0x043, 0x040, 2, (Pipeline_Use_Element *)&pipeline_res_mask_013[0]));

// Pipeline Class "pipe_serial"
static const uint pipeline_res_cycles_009[9] = {
  2, // INS0
  2, // INS1
  0, // INS01
  0, // ALU0
  0, // ALU1
  0, // ALU
  0, // MAC
  1, // DIV
  0  // BRANCH
};

static const Pipeline_Use_Element pipeline_res_mask_014[2] = {
  Pipeline_Use_Element(0x003, 0, 1, true,  Pipeline_Use_Cycle_Mask(0x80000002)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_081((uint)stage_undefined, 0, true, 16, 1, false, false, true, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_012,
  (uint * const) pipeline_res_cycles_009,
  Pipeline_Use(0x083, 0x080, 2, (Pipeline_Use_Element *)&pipeline_res_mask_014[0]));

// Pipeline Class "pipe_slow"
static const Pipeline pipeline_class_082((uint)stage_undefined, 0, true, 16, 10, false, true, true, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_012,
  (uint * const) pipeline_res_cycles_009,
  Pipeline_Use(0x083, 0x080, 2, (Pipeline_Use_Element *)&pipeline_res_mask_014[0]));

// Pipeline Class "pipe_class_empty"
static const enum machPipelineStages pipeline_res_stages_014[9] = {
  stage_undefined, // INS0
  stage_undefined, // INS1
  stage_undefined, // INS01
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined, // ALU
  stage_undefined, // MAC
  stage_undefined, // DIV
  stage_undefined  // BRANCH
};

static const uint pipeline_res_cycles_010[9] = {
  0, // INS0
  0, // INS1
  0, // INS01
  0, // ALU0
  0, // ALU1
  0, // ALU
  0, // MAC
  0, // DIV
  0  // BRANCH
};

static const Pipeline pipeline_class_083((uint)stage_undefined, 0, true, 0, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_014,
  (uint * const) pipeline_res_cycles_010,
  Pipeline_Use(0x000, 0x000, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_default"
static const Pipeline pipeline_class_084((uint)stage_undefined, 0, true, 2, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_014,
  (uint * const) pipeline_res_cycles_010,
  Pipeline_Use(0x000, 0x000, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_compare"
static const Pipeline pipeline_class_085((uint)stage_undefined, 0, true, 16, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_014,
  (uint * const) pipeline_res_cycles_010,
  Pipeline_Use(0x000, 0x000, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_memory"
static const Pipeline pipeline_class_086((uint)stage_undefined, 0, true, 16, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_014,
  (uint * const) pipeline_res_cycles_010,
  Pipeline_Use(0x000, 0x000, 0, (Pipeline_Use_Element *)NULL));

// Pipeline Class "pipe_class_call"
static const Pipeline pipeline_class_087((uint)stage_undefined, 0, true, 100, 1, false, false, false, false,
 NULL,  (enum machPipelineStages * const) pipeline_res_stages_014,
  (uint * const) pipeline_res_cycles_010,
  Pipeline_Use(0x000, 0x000, 0, (Pipeline_Use_Element *)NULL));

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

  static const char *resource_names[9] = { "INS0", "INS1", "INS01", "ALU0", "ALU1", "ALU", "MAC", "DIV", "BRANCH" };

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

const Pipeline * MachNopNode::pipeline() const { return (&pipeline_class_083); }


const Pipeline *                             loadBNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                             loadBNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                           loadB2LNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                           loadB2LNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                            loadUBNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                            loadUBNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                          loadUB2LNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                          loadUB2LNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                             loadSNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                             loadSNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                           loadS2LNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                           loadS2LNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                            loadUSNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                            loadUSNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                          loadUS2LNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                          loadUS2LNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                             loadINode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                             loadINode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                           loadI2LNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                           loadI2LNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                          loadUI2LNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                          loadUI2LNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                             loadLNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                             loadLNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                         loadRangeNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                         loadRangeNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                             loadPNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                             loadPNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                             loadNNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                             loadNNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                         loadKlassNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                         loadKlassNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                        loadNKlassNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                        loadNKlassNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                             loadFNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                             loadFNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                             loadDNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                             loadDNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                          loadConINode::pipeline_class() { return (&pipeline_class_060); }
const Pipeline *                          loadConINode::pipeline() const { return (&pipeline_class_060); }

const Pipeline *                          loadConLNode::pipeline_class() { return (&pipeline_class_060); }
const Pipeline *                          loadConLNode::pipeline() const { return (&pipeline_class_060); }

const Pipeline *                          loadConPNode::pipeline_class() { return (&pipeline_class_060); }
const Pipeline *                          loadConPNode::pipeline() const { return (&pipeline_class_060); }

const Pipeline *                         loadConP0Node::pipeline_class() { return (&pipeline_class_060); }
const Pipeline *                         loadConP0Node::pipeline() const { return (&pipeline_class_060); }

const Pipeline *                         loadConP1Node::pipeline_class() { return (&pipeline_class_060); }
const Pipeline *                         loadConP1Node::pipeline() const { return (&pipeline_class_060); }

const Pipeline *                   loadByteMapBaseNode::pipeline_class() { return (&pipeline_class_060); }
const Pipeline *                   loadByteMapBaseNode::pipeline() const { return (&pipeline_class_060); }

const Pipeline *                          loadConNNode::pipeline_class() { return (&pipeline_class_060); }
const Pipeline *                          loadConNNode::pipeline() const { return (&pipeline_class_060); }

const Pipeline *                         loadConN0Node::pipeline_class() { return (&pipeline_class_060); }
const Pipeline *                         loadConN0Node::pipeline() const { return (&pipeline_class_060); }

const Pipeline *                     loadConNKlassNode::pipeline_class() { return (&pipeline_class_060); }
const Pipeline *                     loadConNKlassNode::pipeline() const { return (&pipeline_class_060); }

const Pipeline *                   loadConF_packedNode::pipeline_class() { return (&pipeline_class_019); }
const Pipeline *                   loadConF_packedNode::pipeline() const { return (&pipeline_class_019); }

const Pipeline *                          loadConFNode::pipeline_class() { return (&pipeline_class_021); }
const Pipeline *                          loadConFNode::pipeline() const { return (&pipeline_class_021); }

const Pipeline *                   loadConD_packedNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                   loadConD_packedNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                          loadConDNode::pipeline_class() { return (&pipeline_class_022); }
const Pipeline *                          loadConDNode::pipeline() const { return (&pipeline_class_022); }

const Pipeline *                       storeimmCM0Node::pipeline_class() { return (&pipeline_class_075); }
const Pipeline *                       storeimmCM0Node::pipeline() const { return (&pipeline_class_075); }

const Pipeline *               storeimmCM0_orderedNode::pipeline_class() { return (&pipeline_class_075); }
const Pipeline *               storeimmCM0_orderedNode::pipeline() const { return (&pipeline_class_075); }

const Pipeline *                            storeBNode::pipeline_class() { return (&pipeline_class_076); }
const Pipeline *                            storeBNode::pipeline() const { return (&pipeline_class_076); }

const Pipeline *                        storeimmB0Node::pipeline_class() { return (&pipeline_class_075); }
const Pipeline *                        storeimmB0Node::pipeline() const { return (&pipeline_class_075); }

const Pipeline *                            storeCNode::pipeline_class() { return (&pipeline_class_076); }
const Pipeline *                            storeCNode::pipeline() const { return (&pipeline_class_076); }

const Pipeline *                        storeimmC0Node::pipeline_class() { return (&pipeline_class_075); }
const Pipeline *                        storeimmC0Node::pipeline() const { return (&pipeline_class_075); }

const Pipeline *                            storeINode::pipeline_class() { return (&pipeline_class_076); }
const Pipeline *                            storeINode::pipeline() const { return (&pipeline_class_076); }

const Pipeline *                        storeimmI0Node::pipeline_class() { return (&pipeline_class_075); }
const Pipeline *                        storeimmI0Node::pipeline() const { return (&pipeline_class_075); }

const Pipeline *                            storeLNode::pipeline_class() { return (&pipeline_class_076); }
const Pipeline *                            storeLNode::pipeline() const { return (&pipeline_class_076); }

const Pipeline *                        storeimmL0Node::pipeline_class() { return (&pipeline_class_075); }
const Pipeline *                        storeimmL0Node::pipeline() const { return (&pipeline_class_075); }

const Pipeline *                            storePNode::pipeline_class() { return (&pipeline_class_076); }
const Pipeline *                            storePNode::pipeline() const { return (&pipeline_class_076); }

const Pipeline *                        storeimmP0Node::pipeline_class() { return (&pipeline_class_075); }
const Pipeline *                        storeimmP0Node::pipeline() const { return (&pipeline_class_075); }

const Pipeline *                            storeNNode::pipeline_class() { return (&pipeline_class_076); }
const Pipeline *                            storeNNode::pipeline() const { return (&pipeline_class_076); }

const Pipeline *                        storeImmN0Node::pipeline_class() { return (&pipeline_class_075); }
const Pipeline *                        storeImmN0Node::pipeline() const { return (&pipeline_class_075); }

const Pipeline *                            storeFNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                            storeFNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                            storeDNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                            storeDNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                       storeNKlassNode::pipeline_class() { return (&pipeline_class_076); }
const Pipeline *                       storeNKlassNode::pipeline() const { return (&pipeline_class_076); }

const Pipeline *                     prefetchallocNode::pipeline_class() { return (&pipeline_class_072); }
const Pipeline *                     prefetchallocNode::pipeline() const { return (&pipeline_class_072); }

const Pipeline *                    loadB_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    loadB_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                  loadB2L_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                  loadB2L_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                   loadUB_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                   loadUB_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                 loadUB2L_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                 loadUB2L_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                    loadS_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    loadS_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                   loadUS_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                   loadUS_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                 loadUS2L_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                 loadUS2L_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                  loadS2L_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                  loadS2L_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                    loadI_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    loadI_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                 loadUI2L_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                 loadUI2L_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                    loadL_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    loadL_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                    loadP_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    loadP_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                    loadN_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    loadN_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                    loadF_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    loadF_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                    loadD_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    loadD_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                   storeB_volatileNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                   storeB_volatileNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                   storeC_volatileNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                   storeC_volatileNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                   storeI_volatileNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                   storeI_volatileNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                   storeL_volatileNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                   storeL_volatileNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                   storeP_volatileNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                   storeP_volatileNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                   storeN_volatileNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                   storeN_volatileNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                   storeF_volatileNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                   storeF_volatileNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                   storeD_volatileNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                   storeD_volatileNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                           cacheWBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           cacheWBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    cacheWBPreSyncNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    cacheWBPreSyncNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   cacheWBPostSyncNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   cacheWBPostSyncNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                 bytes_reverse_intNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                 bytes_reverse_intNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                bytes_reverse_longNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                bytes_reverse_longNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *      bytes_reverse_unsigned_shortNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *      bytes_reverse_unsigned_shortNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *               bytes_reverse_shortNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *               bytes_reverse_shortNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                countLeadingZerosINode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                countLeadingZerosINode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                countLeadingZerosLNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                countLeadingZerosLNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *               countTrailingZerosINode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *               countTrailingZerosINode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *               countTrailingZerosLNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *               countTrailingZerosLNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                         popCountINode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         popCountINode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     popCountI_memNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     popCountI_memNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                         popCountLNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         popCountLNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     popCountL_memNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     popCountL_memNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        load_fenceNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                        load_fenceNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *        unnecessary_membar_acquireNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *        unnecessary_membar_acquireNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                    membar_acquireNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    membar_acquireNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *               membar_acquire_lockNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *               membar_acquire_lockNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                       store_fenceNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                       store_fenceNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *        unnecessary_membar_releaseNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *        unnecessary_membar_releaseNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                    membar_releaseNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    membar_releaseNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                 membar_storestoreNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                 membar_storestoreNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *               membar_storestore_0Node::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *               membar_storestore_0Node::pipeline() const { return (&pipeline_class_081); }

const Pipeline *               membar_release_lockNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *               membar_release_lockNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *       unnecessary_membar_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *       unnecessary_membar_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                   membar_volatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                   membar_volatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                           castX2PNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                           castX2PNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                           castP2XNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                           castP2XNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                           convP2INode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                           convP2INode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                           convN2INode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                           convN2INode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                     encodeHeapOopNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                     encodeHeapOopNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *            encodeHeapOop_not_nullNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *            encodeHeapOop_not_nullNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                     decodeHeapOopNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                     decodeHeapOopNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *            decodeHeapOop_not_nullNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *            decodeHeapOop_not_nullNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *              encodeKlass_not_nullNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *              encodeKlass_not_nullNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *              decodeKlass_not_nullNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *              decodeKlass_not_nullNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                       checkCastPPNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                       checkCastPPNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                            castPPNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                            castPPNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                            castIINode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                            castIINode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                            castLLNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                            castLLNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                            castFFNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                            castFFNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                            castDDNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                            castDDNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                           castVVDNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                           castVVDNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                           castVVXNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                           castVVXNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                            castVVNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                            castVVNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                        castVVMaskNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                        castVVMaskNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                       loadPLockedNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                       loadPLockedNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                 storePConditionalNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                 storePConditionalNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                 storeLConditionalNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 storeLConditionalNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                 storeIConditionalNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 storeIConditionalNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   compareAndSwapBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   compareAndSwapBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   compareAndSwapSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   compareAndSwapSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   compareAndSwapINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   compareAndSwapINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   compareAndSwapLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   compareAndSwapLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   compareAndSwapPNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   compareAndSwapPNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   compareAndSwapNNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   compareAndSwapNNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                compareAndSwapBAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                compareAndSwapBAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                compareAndSwapSAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                compareAndSwapSAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                compareAndSwapIAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                compareAndSwapIAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                compareAndSwapLAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                compareAndSwapLAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                compareAndSwapPAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                compareAndSwapPAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                compareAndSwapNAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                compareAndSwapNAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               compareAndExchangeBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               compareAndExchangeBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               compareAndExchangeSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               compareAndExchangeSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               compareAndExchangeINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               compareAndExchangeINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               compareAndExchangeLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               compareAndExchangeLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               compareAndExchangeNNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               compareAndExchangeNNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               compareAndExchangePNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               compareAndExchangePNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            compareAndExchangeBAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            compareAndExchangeBAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            compareAndExchangeSAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            compareAndExchangeSAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            compareAndExchangeIAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            compareAndExchangeIAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            compareAndExchangeLAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            compareAndExchangeLAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            compareAndExchangeNAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            compareAndExchangeNAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            compareAndExchangePAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            compareAndExchangePAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               weakCompareAndSwapBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               weakCompareAndSwapBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               weakCompareAndSwapSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               weakCompareAndSwapSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               weakCompareAndSwapINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               weakCompareAndSwapINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               weakCompareAndSwapLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               weakCompareAndSwapLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               weakCompareAndSwapNNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               weakCompareAndSwapNNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               weakCompareAndSwapPNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               weakCompareAndSwapPNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            weakCompareAndSwapBAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            weakCompareAndSwapBAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            weakCompareAndSwapSAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            weakCompareAndSwapSAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            weakCompareAndSwapIAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            weakCompareAndSwapIAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            weakCompareAndSwapLAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            weakCompareAndSwapLAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            weakCompareAndSwapNAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            weakCompareAndSwapNAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            weakCompareAndSwapPAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            weakCompareAndSwapPAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      get_and_setINode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                      get_and_setINode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                      get_and_setLNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                      get_and_setLNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                      get_and_setNNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                      get_and_setNNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                      get_and_setPNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                      get_and_setPNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                   get_and_setIAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                   get_and_setIAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                   get_and_setLAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                   get_and_setLAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                   get_and_setNAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                   get_and_setNAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                   get_and_setPAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                   get_and_setPAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                      get_and_addLNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                      get_and_addLNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *               get_and_addL_no_resNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *               get_and_addL_no_resNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                     get_and_addLiNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                     get_and_addLiNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *              get_and_addLi_no_resNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *              get_and_addLi_no_resNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                      get_and_addINode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                      get_and_addINode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *               get_and_addI_no_resNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *               get_and_addI_no_resNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                     get_and_addIiNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                     get_and_addIiNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *              get_and_addIi_no_resNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *              get_and_addIi_no_resNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                   get_and_addLAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                   get_and_addLAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *            get_and_addL_no_resAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *            get_and_addL_no_resAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                  get_and_addLiAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                  get_and_addLiAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *           get_and_addLi_no_resAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *           get_and_addLi_no_resAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                   get_and_addIAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                   get_and_addIAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *            get_and_addI_no_resAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *            get_and_addI_no_resAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                  get_and_addIiAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                  get_and_addIiAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *           get_and_addIi_no_resAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *           get_and_addIi_no_resAcqNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                     cmpL3_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     cmpL3_reg_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     cmpL3_reg_immNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     cmpL3_reg_immNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     cmovI_reg_regNode::pipeline_class() { return (&pipeline_class_064); }
const Pipeline *                     cmovI_reg_regNode::pipeline() const { return (&pipeline_class_064); }

const Pipeline *                    cmovUI_reg_regNode::pipeline_class() { return (&pipeline_class_064); }
const Pipeline *                    cmovUI_reg_regNode::pipeline() const { return (&pipeline_class_064); }

const Pipeline *                    cmovI_zero_regNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                    cmovI_zero_regNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                   cmovUI_zero_regNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                   cmovUI_zero_regNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                    cmovI_reg_zeroNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                    cmovI_reg_zeroNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                   cmovUI_reg_zeroNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                   cmovUI_reg_zeroNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                cmovI_reg_zero_oneNode::pipeline_class() { return (&pipeline_class_063); }
const Pipeline *                cmovI_reg_zero_oneNode::pipeline() const { return (&pipeline_class_063); }

const Pipeline *               cmovUI_reg_zero_oneNode::pipeline_class() { return (&pipeline_class_063); }
const Pipeline *               cmovUI_reg_zero_oneNode::pipeline() const { return (&pipeline_class_063); }

const Pipeline *                     cmovL_reg_regNode::pipeline_class() { return (&pipeline_class_064); }
const Pipeline *                     cmovL_reg_regNode::pipeline() const { return (&pipeline_class_064); }

const Pipeline *                    cmovUL_reg_regNode::pipeline_class() { return (&pipeline_class_064); }
const Pipeline *                    cmovUL_reg_regNode::pipeline() const { return (&pipeline_class_064); }

const Pipeline *                    cmovL_reg_zeroNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                    cmovL_reg_zeroNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                   cmovUL_reg_zeroNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                   cmovUL_reg_zeroNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                    cmovL_zero_regNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                    cmovL_zero_regNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                   cmovUL_zero_regNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                   cmovUL_zero_regNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                     cmovP_reg_regNode::pipeline_class() { return (&pipeline_class_064); }
const Pipeline *                     cmovP_reg_regNode::pipeline() const { return (&pipeline_class_064); }

const Pipeline *                    cmovUP_reg_regNode::pipeline_class() { return (&pipeline_class_064); }
const Pipeline *                    cmovUP_reg_regNode::pipeline() const { return (&pipeline_class_064); }

const Pipeline *                    cmovP_reg_zeroNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                    cmovP_reg_zeroNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                   cmovUP_reg_zeroNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                   cmovUP_reg_zeroNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                    cmovP_zero_regNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                    cmovP_zero_regNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                   cmovUP_zero_regNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                   cmovUP_zero_regNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                     cmovN_reg_regNode::pipeline_class() { return (&pipeline_class_064); }
const Pipeline *                     cmovN_reg_regNode::pipeline() const { return (&pipeline_class_064); }

const Pipeline *                    cmovUN_reg_regNode::pipeline_class() { return (&pipeline_class_064); }
const Pipeline *                    cmovUN_reg_regNode::pipeline() const { return (&pipeline_class_064); }

const Pipeline *                    cmovN_reg_zeroNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                    cmovN_reg_zeroNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                   cmovUN_reg_zeroNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                   cmovUN_reg_zeroNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                    cmovN_zero_regNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                    cmovN_zero_regNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                   cmovUN_zero_regNode::pipeline_class() { return (&pipeline_class_065); }
const Pipeline *                   cmovUN_zero_regNode::pipeline() const { return (&pipeline_class_065); }

const Pipeline *                         cmovF_regNode::pipeline_class() { return (&pipeline_class_017); }
const Pipeline *                         cmovF_regNode::pipeline() const { return (&pipeline_class_017); }

const Pipeline *                        cmovUF_regNode::pipeline_class() { return (&pipeline_class_017); }
const Pipeline *                        cmovUF_regNode::pipeline() const { return (&pipeline_class_017); }

const Pipeline *                         cmovD_regNode::pipeline_class() { return (&pipeline_class_018); }
const Pipeline *                         cmovD_regNode::pipeline() const { return (&pipeline_class_018); }

const Pipeline *                        cmovUD_regNode::pipeline_class() { return (&pipeline_class_018); }
const Pipeline *                        cmovUD_regNode::pipeline() const { return (&pipeline_class_018); }

const Pipeline *                      addI_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      addI_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      addI_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                      addI_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                  addI_reg_imm_i2lNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                  addI_reg_imm_i2lNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                      addP_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      addP_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  addP_reg_reg_extNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  addP_reg_reg_extNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  addP_reg_reg_lslNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                  addP_reg_reg_lslNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            addP_reg_reg_ext_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            addP_reg_reg_ext_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                        lshift_extNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                        lshift_extNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                      addP_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                      addP_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                      addL_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      addL_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      addL_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                      addL_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                      subI_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      subI_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      subI_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                      subI_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                      subL_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      subL_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      subL_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                      subL_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                          negI_regNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                          negI_regNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                          negL_regNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                          negL_regNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                              mulINode::pipeline_class() { return (&pipeline_class_066); }
const Pipeline *                              mulINode::pipeline() const { return (&pipeline_class_066); }

const Pipeline *                             smulINode::pipeline_class() { return (&pipeline_class_066); }
const Pipeline *                             smulINode::pipeline() const { return (&pipeline_class_066); }

const Pipeline *                           smulI_0Node::pipeline_class() { return (&pipeline_class_066); }
const Pipeline *                           smulI_0Node::pipeline() const { return (&pipeline_class_066); }

const Pipeline *                              mulLNode::pipeline_class() { return (&pipeline_class_068); }
const Pipeline *                              mulLNode::pipeline() const { return (&pipeline_class_068); }

const Pipeline *                       mulHiL_rRegNode::pipeline_class() { return (&pipeline_class_068); }
const Pipeline *                       mulHiL_rRegNode::pipeline() const { return (&pipeline_class_068); }

const Pipeline *                             maddINode::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                             maddINode::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                           maddI_0Node::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                           maddI_0Node::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                             msubINode::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                             msubINode::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                             mnegINode::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                             mnegINode::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                           mnegI_0Node::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                           mnegI_0Node::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                             maddLNode::pipeline_class() { return (&pipeline_class_069); }
const Pipeline *                             maddLNode::pipeline() const { return (&pipeline_class_069); }

const Pipeline *                           maddL_0Node::pipeline_class() { return (&pipeline_class_069); }
const Pipeline *                           maddL_0Node::pipeline() const { return (&pipeline_class_069); }

const Pipeline *                             msubLNode::pipeline_class() { return (&pipeline_class_069); }
const Pipeline *                             msubLNode::pipeline() const { return (&pipeline_class_069); }

const Pipeline *                             mnegLNode::pipeline_class() { return (&pipeline_class_069); }
const Pipeline *                             mnegLNode::pipeline() const { return (&pipeline_class_069); }

const Pipeline *                           mnegL_0Node::pipeline_class() { return (&pipeline_class_069); }
const Pipeline *                           mnegL_0Node::pipeline() const { return (&pipeline_class_069); }

const Pipeline *                            smaddLNode::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                            smaddLNode::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                          smaddL_1Node::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                          smaddL_1Node::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                          smaddL_0Node::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                          smaddL_0Node::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                          smaddL_2Node::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                          smaddL_2Node::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                            smsubLNode::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                            smsubLNode::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                          smsubL_0Node::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                          smsubL_0Node::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                            smnegLNode::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                            smnegLNode::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                          smnegL_0Node::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                          smnegL_0Node::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                         muladdS2INode::pipeline_class() { return (&pipeline_class_067); }
const Pipeline *                         muladdS2INode::pipeline() const { return (&pipeline_class_067); }

const Pipeline *                              divINode::pipeline_class() { return (&pipeline_class_070); }
const Pipeline *                              divINode::pipeline() const { return (&pipeline_class_070); }

const Pipeline *                              divLNode::pipeline_class() { return (&pipeline_class_071); }
const Pipeline *                              divLNode::pipeline() const { return (&pipeline_class_071); }

const Pipeline *                              modINode::pipeline_class() { return (&pipeline_class_070); }
const Pipeline *                              modINode::pipeline() const { return (&pipeline_class_070); }

const Pipeline *                              modLNode::pipeline_class() { return (&pipeline_class_071); }
const Pipeline *                              modLNode::pipeline() const { return (&pipeline_class_071); }

const Pipeline *                   lShiftI_reg_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   lShiftI_reg_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   lShiftI_reg_immNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                   lShiftI_reg_immNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                  urShiftI_reg_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                  urShiftI_reg_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                  urShiftI_reg_immNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                  urShiftI_reg_immNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                   rShiftI_reg_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   rShiftI_reg_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   rShiftI_reg_immNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                   rShiftI_reg_immNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                   lShiftL_reg_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   lShiftL_reg_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   lShiftL_reg_immNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                   lShiftL_reg_immNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                  urShiftL_reg_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                  urShiftL_reg_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                  urShiftL_reg_immNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                  urShiftL_reg_immNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                  urShiftP_reg_immNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                  urShiftP_reg_immNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                   rShiftL_reg_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                   rShiftL_reg_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                   rShiftL_reg_immNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                   rShiftL_reg_immNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                      regL_not_regNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                      regL_not_regNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                      regI_not_regNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                      regI_not_regNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                  AndI_reg_not_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  AndI_reg_not_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                AndI_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                AndI_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  AndL_reg_not_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  AndL_reg_not_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                AndL_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                AndL_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                   OrI_reg_not_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                   OrI_reg_not_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                 OrI_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                 OrI_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                   OrL_reg_not_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                   OrL_reg_not_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                 OrL_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                 OrL_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  XorI_reg_not_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  XorI_reg_not_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                XorI_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                XorI_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  XorL_reg_not_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  XorL_reg_not_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                XorL_reg_not_reg_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                XorL_reg_not_reg_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *          AndI_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          AndI_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        AndI_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        AndI_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          AndL_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          AndL_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        AndL_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        AndL_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           AndI_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           AndI_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         AndI_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         AndI_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           AndL_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           AndL_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         AndL_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         AndL_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *      AndI_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *      AndI_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *    AndI_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *    AndI_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *      AndL_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *      AndL_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *    AndL_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *    AndL_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           AndI_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           AndI_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         AndI_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         AndI_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           AndL_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           AndL_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         AndL_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         AndL_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          XorI_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          XorI_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        XorI_reg_URShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        XorI_reg_URShift_not_reg_1Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        XorI_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        XorI_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        XorI_reg_URShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        XorI_reg_URShift_not_reg_2Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          XorL_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          XorL_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        XorL_reg_URShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        XorL_reg_URShift_not_reg_1Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        XorL_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        XorL_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        XorL_reg_URShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        XorL_reg_URShift_not_reg_2Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           XorI_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           XorI_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorI_reg_RShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorI_reg_RShift_not_reg_1Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorI_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorI_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorI_reg_RShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorI_reg_RShift_not_reg_2Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           XorL_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           XorL_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorL_reg_RShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorL_reg_RShift_not_reg_1Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorL_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorL_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorL_reg_RShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorL_reg_RShift_not_reg_2Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *      XorI_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *      XorI_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *    XorI_reg_RotateRight_not_reg_1Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *    XorI_reg_RotateRight_not_reg_1Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *    XorI_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *    XorI_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *    XorI_reg_RotateRight_not_reg_2Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *    XorI_reg_RotateRight_not_reg_2Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *      XorL_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *      XorL_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *    XorL_reg_RotateRight_not_reg_1Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *    XorL_reg_RotateRight_not_reg_1Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *    XorL_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *    XorL_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *    XorL_reg_RotateRight_not_reg_2Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *    XorL_reg_RotateRight_not_reg_2Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           XorI_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           XorI_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorI_reg_LShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorI_reg_LShift_not_reg_1Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorI_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorI_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorI_reg_LShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorI_reg_LShift_not_reg_2Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           XorL_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           XorL_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorL_reg_LShift_not_reg_1Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorL_reg_LShift_not_reg_1Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorL_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorL_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         XorL_reg_LShift_not_reg_2Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         XorL_reg_LShift_not_reg_2Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           OrI_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           OrI_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         OrI_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         OrI_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           OrL_reg_URShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           OrL_reg_URShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         OrL_reg_URShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         OrL_reg_URShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            OrI_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            OrI_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          OrI_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          OrI_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            OrL_reg_RShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            OrL_reg_RShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          OrL_reg_RShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          OrL_reg_RShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *       OrI_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *       OrI_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *     OrI_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *     OrI_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *       OrL_reg_RotateRight_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *       OrL_reg_RotateRight_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *     OrL_reg_RotateRight_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *     OrL_reg_RotateRight_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            OrI_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            OrI_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          OrI_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          OrI_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            OrL_reg_LShift_not_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            OrL_reg_LShift_not_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          OrL_reg_LShift_not_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          OrL_reg_LShift_not_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              AndI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              AndI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            AndI_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            AndI_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              AndL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              AndL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            AndL_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            AndL_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               AndI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               AndI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             AndI_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             AndI_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               AndL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               AndL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             AndL_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             AndL_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               AndI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               AndI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             AndI_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             AndI_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               AndL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               AndL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             AndL_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             AndL_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          AndI_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          AndI_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        AndI_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        AndI_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          AndL_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          AndL_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        AndL_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        AndL_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              XorI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              XorI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            XorI_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            XorI_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              XorL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              XorL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            XorL_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            XorL_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               XorI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               XorI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             XorI_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             XorI_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               XorL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               XorL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             XorL_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             XorL_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               XorI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               XorI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             XorI_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             XorI_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               XorL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               XorL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             XorL_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             XorL_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          XorI_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          XorI_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        XorI_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        XorI_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          XorL_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          XorL_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *        XorL_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *        XorL_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               OrI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               OrI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             OrI_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             OrI_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               OrL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               OrL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             OrL_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             OrL_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                OrI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                OrI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              OrI_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              OrI_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                OrL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                OrL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              OrL_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              OrL_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                OrI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                OrI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              OrI_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              OrI_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                OrL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                OrL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              OrL_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              OrL_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           OrI_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           OrI_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         OrI_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         OrI_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *           OrL_reg_RotateRight_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *           OrL_reg_RotateRight_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *         OrL_reg_RotateRight_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *         OrL_reg_RotateRight_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              AddI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              AddI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            AddI_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            AddI_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              AddL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              AddL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            AddL_reg_URShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            AddL_reg_URShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               AddI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               AddI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             AddI_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             AddI_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               AddL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               AddL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             AddL_reg_RShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             AddL_reg_RShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               AddI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               AddI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             AddI_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             AddI_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               AddL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               AddL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *             AddL_reg_LShift_reg_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *             AddL_reg_LShift_reg_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              SubI_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              SubI_reg_URShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              SubL_reg_URShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              SubL_reg_URShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               SubI_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               SubI_reg_RShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               SubL_reg_RShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               SubL_reg_RShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               SubI_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               SubI_reg_LShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *               SubL_reg_LShift_regNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *               SubL_reg_LShift_regNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                             sbfmLNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                             sbfmLNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                            sbfmwINode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                            sbfmwINode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                             ubfmLNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                             ubfmLNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                            ubfmwINode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                            ubfmwINode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                            ubfxwINode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                            ubfxwINode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                             ubfxLNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                             ubfxLNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                      ubfxIConvI2LNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                      ubfxIConvI2LNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                           ubfizwINode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                           ubfizwINode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                            ubfizLNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                            ubfizLNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                    ubfizwIConvI2LNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                    ubfizwIConvI2LNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                     ubfizLConvL2INode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                     ubfizLConvL2INode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                     ubfizIConvI2LNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                     ubfizIConvI2LNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                    ubfizLConvL2IxNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                    ubfizLConvL2IxNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                 ubfizIConvI2LAndINode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                 ubfizIConvI2LAndINode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                           extrOrLNode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                           extrOrLNode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                         extrOrL_0Node::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                         extrOrL_0Node::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                           extrOrINode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                           extrOrINode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                         extrOrI_0Node::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                         extrOrI_0Node::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                          extrAddLNode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                          extrAddLNode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                        extrAddL_0Node::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                        extrAddL_0Node::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                          extrAddINode::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                          extrAddINode::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                        extrAddI_0Node::pipeline_class() { return (&pipeline_class_057); }
const Pipeline *                        extrAddI_0Node::pipeline() const { return (&pipeline_class_057); }

const Pipeline *                          rorI_immNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                          rorI_immNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                          rorL_immNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                          rorL_immNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                          rorI_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                          rorI_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                          rorL_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                          rorL_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                          rolI_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                          rolI_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                          rolL_regNode::pipeline_class() { return (&pipeline_class_056); }
const Pipeline *                          rolL_regNode::pipeline() const { return (&pipeline_class_056); }

const Pipeline *                           AddExtINode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                           AddExtINode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                         AddExtI_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                         AddExtI_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                           SubExtINode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                           SubExtINode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      AddExtI_sxthNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      AddExtI_sxthNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                    AddExtI_sxth_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                    AddExtI_sxth_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      AddExtI_sxtbNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      AddExtI_sxtbNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                    AddExtI_sxtb_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                    AddExtI_sxtb_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      AddExtI_uxtbNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      AddExtI_uxtbNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                    AddExtI_uxtb_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                    AddExtI_uxtb_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      AddExtL_sxthNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      AddExtL_sxthNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                    AddExtL_sxth_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                    AddExtL_sxth_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      AddExtL_sxtwNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      AddExtL_sxtwNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                    AddExtL_sxtw_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                    AddExtL_sxtw_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      AddExtL_sxtbNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      AddExtL_sxtbNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                    AddExtL_sxtb_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                    AddExtL_sxtb_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      AddExtL_uxtbNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      AddExtL_uxtbNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                    AddExtL_uxtb_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                    AddExtL_uxtb_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  AddExtI_uxtb_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  AddExtI_uxtb_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                AddExtI_uxtb_and_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                AddExtI_uxtb_and_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  AddExtI_uxth_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  AddExtI_uxth_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                AddExtI_uxth_and_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                AddExtI_uxth_and_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  AddExtL_uxtb_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  AddExtL_uxtb_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                AddExtL_uxtb_and_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                AddExtL_uxtb_and_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  AddExtL_uxth_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  AddExtL_uxth_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                AddExtL_uxth_and_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                AddExtL_uxth_and_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  AddExtL_uxtw_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  AddExtL_uxtw_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                AddExtL_uxtw_and_0Node::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                AddExtL_uxtw_and_0Node::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  SubExtI_uxtb_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  SubExtI_uxtb_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  SubExtI_uxth_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  SubExtI_uxth_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  SubExtL_uxtb_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  SubExtL_uxtb_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  SubExtL_uxth_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  SubExtL_uxth_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                  SubExtL_uxtw_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                  SubExtL_uxtw_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                AddExtL_sxtb_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                AddExtL_sxtb_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              AddExtL_sxtb_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              AddExtL_sxtb_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                AddExtL_sxth_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                AddExtL_sxth_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              AddExtL_sxth_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              AddExtL_sxth_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                AddExtL_sxtw_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                AddExtL_sxtw_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              AddExtL_sxtw_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              AddExtL_sxtw_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                SubExtL_sxtb_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                SubExtL_sxtb_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                SubExtL_sxth_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                SubExtL_sxth_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                SubExtL_sxtw_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                SubExtL_sxtw_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                AddExtI_sxtb_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                AddExtI_sxtb_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              AddExtI_sxtb_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              AddExtI_sxtb_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                AddExtI_sxth_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                AddExtI_sxth_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *              AddExtI_sxth_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *              AddExtI_sxth_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                SubExtI_sxtb_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                SubExtI_sxtb_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                SubExtI_sxth_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                SubExtI_sxth_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     AddExtI_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     AddExtI_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                   AddExtI_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                   AddExtI_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *                     SubExtI_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *                     SubExtI_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            AddExtL_uxtb_and_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            AddExtL_uxtb_and_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          AddExtL_uxtb_and_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          AddExtL_uxtb_and_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            AddExtL_uxth_and_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            AddExtL_uxth_and_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          AddExtL_uxth_and_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          AddExtL_uxth_and_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            AddExtL_uxtw_and_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            AddExtL_uxtw_and_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          AddExtL_uxtw_and_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          AddExtL_uxtw_and_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            SubExtL_uxtb_and_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            SubExtL_uxtb_and_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            SubExtL_uxth_and_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            SubExtL_uxth_and_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            SubExtL_uxtw_and_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            SubExtL_uxtw_and_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            AddExtI_uxtb_and_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            AddExtI_uxtb_and_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          AddExtI_uxtb_and_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          AddExtI_uxtb_and_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            AddExtI_uxth_and_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            AddExtI_uxth_and_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *          AddExtI_uxth_and_shift_0Node::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *          AddExtI_uxth_and_shift_0Node::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            SubExtI_uxtb_and_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            SubExtI_uxtb_and_shiftNode::pipeline() const { return (&pipeline_class_054); }

const Pipeline *            SubExtI_uxth_and_shiftNode::pipeline_class() { return (&pipeline_class_054); }
const Pipeline *            SubExtI_uxth_and_shiftNode::pipeline() const { return (&pipeline_class_054); }

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

const Pipeline *                     maddF_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     maddF_reg_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     maddD_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     maddD_reg_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     msubF_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     msubF_reg_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                   msubF_reg_reg_0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                   msubF_reg_reg_0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     msubD_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     msubD_reg_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                   msubD_reg_reg_0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                   msubD_reg_reg_0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                    mnaddF_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                    mnaddF_reg_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                  mnaddF_reg_reg_0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                  mnaddF_reg_reg_0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                    mnaddD_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                    mnaddD_reg_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                  mnaddD_reg_reg_0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                  mnaddD_reg_reg_0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                    mnsubF_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                    mnsubF_reg_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                    mnsubD_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                    mnsubD_reg_regNode::pipeline() const { return (&pipeline_class_084); }

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

const Pipeline *                          absI_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          absI_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          absL_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          absL_regNode::pipeline() const { return (&pipeline_class_084); }

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

const Pipeline *                        onspinwaitNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                        onspinwaitNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                      andI_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      andI_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      andI_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                      andI_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                       orI_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                       orI_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                       orI_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                       orI_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                      xorI_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      xorI_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      xorI_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                      xorI_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                      andL_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      andL_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      andL_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                      andL_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                       orL_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                       orL_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                       orL_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                       orL_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                      xorL_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      xorL_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      xorL_reg_immNode::pipeline_class() { return (&pipeline_class_059); }
const Pipeline *                      xorL_reg_immNode::pipeline() const { return (&pipeline_class_059); }

const Pipeline *                   convI2L_reg_regNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                   convI2L_reg_regNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                  convUI2L_reg_regNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                  convUI2L_reg_regNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                       convL2I_regNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                       convL2I_regNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                           convI2BNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                           convI2BNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                           convP2BNode::pipeline_class() { return (&pipeline_class_058); }
const Pipeline *                           convP2BNode::pipeline() const { return (&pipeline_class_058); }

const Pipeline *                       convD2F_regNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                       convD2F_regNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                       convF2D_regNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                       convF2D_regNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                   convF2I_reg_regNode::pipeline_class() { return (&pipeline_class_007); }
const Pipeline *                   convF2I_reg_regNode::pipeline() const { return (&pipeline_class_007); }

const Pipeline *                   convF2L_reg_regNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                   convF2L_reg_regNode::pipeline() const { return (&pipeline_class_008); }

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

const Pipeline *                 MoveF2I_stack_regNode::pipeline_class() { return (&pipeline_class_074); }
const Pipeline *                 MoveF2I_stack_regNode::pipeline() const { return (&pipeline_class_074); }

const Pipeline *                 MoveI2F_stack_regNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                 MoveI2F_stack_regNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                 MoveD2L_stack_regNode::pipeline_class() { return (&pipeline_class_074); }
const Pipeline *                 MoveD2L_stack_regNode::pipeline() const { return (&pipeline_class_074); }

const Pipeline *                 MoveL2D_stack_regNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                 MoveL2D_stack_regNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                 MoveF2I_reg_stackNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                 MoveF2I_reg_stackNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                 MoveI2F_reg_stackNode::pipeline_class() { return (&pipeline_class_077); }
const Pipeline *                 MoveI2F_reg_stackNode::pipeline() const { return (&pipeline_class_077); }

const Pipeline *                 MoveD2L_reg_stackNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                 MoveD2L_reg_stackNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                 MoveL2D_reg_stackNode::pipeline_class() { return (&pipeline_class_077); }
const Pipeline *                 MoveL2D_reg_stackNode::pipeline() const { return (&pipeline_class_077); }

const Pipeline *                   MoveF2I_reg_regNode::pipeline_class() { return (&pipeline_class_007); }
const Pipeline *                   MoveF2I_reg_regNode::pipeline() const { return (&pipeline_class_007); }

const Pipeline *                   MoveI2F_reg_regNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                   MoveI2F_reg_regNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                   MoveD2L_reg_regNode::pipeline_class() { return (&pipeline_class_012); }
const Pipeline *                   MoveD2L_reg_regNode::pipeline() const { return (&pipeline_class_012); }

const Pipeline *                   MoveL2D_reg_regNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                   MoveL2D_reg_regNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                clearArray_reg_regNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                clearArray_reg_regNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                clearArray_imm_regNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                clearArray_imm_regNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *              overflowAddI_reg_regNode::pipeline_class() { return (&pipeline_class_061); }
const Pipeline *              overflowAddI_reg_regNode::pipeline() const { return (&pipeline_class_061); }

const Pipeline *              overflowAddI_reg_immNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *              overflowAddI_reg_immNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *              overflowAddL_reg_regNode::pipeline_class() { return (&pipeline_class_061); }
const Pipeline *              overflowAddL_reg_regNode::pipeline() const { return (&pipeline_class_061); }

const Pipeline *              overflowAddL_reg_immNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *              overflowAddL_reg_immNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *              overflowSubI_reg_regNode::pipeline_class() { return (&pipeline_class_061); }
const Pipeline *              overflowSubI_reg_regNode::pipeline() const { return (&pipeline_class_061); }

const Pipeline *              overflowSubI_reg_immNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *              overflowSubI_reg_immNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *              overflowSubL_reg_regNode::pipeline_class() { return (&pipeline_class_061); }
const Pipeline *              overflowSubL_reg_regNode::pipeline() const { return (&pipeline_class_061); }

const Pipeline *              overflowSubL_reg_immNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *              overflowSubL_reg_immNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                  overflowNegI_regNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                  overflowNegI_regNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                  overflowNegL_regNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                  overflowNegL_regNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                  overflowMulI_regNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  overflowMulI_regNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *           overflowMulI_reg_branchNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *           overflowMulI_reg_branchNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                  overflowMulL_regNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  overflowMulL_regNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *           overflowMulL_reg_branchNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *           overflowMulL_reg_branchNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                     compI_reg_regNode::pipeline_class() { return (&pipeline_class_061); }
const Pipeline *                     compI_reg_regNode::pipeline() const { return (&pipeline_class_061); }

const Pipeline *                   compI_reg_immI0Node::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                   compI_reg_immI0Node::pipeline() const { return (&pipeline_class_062); }

const Pipeline *              compI_reg_immIAddSubNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *              compI_reg_immIAddSubNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                    compI_reg_immINode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                    compI_reg_immINode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                     compU_reg_regNode::pipeline_class() { return (&pipeline_class_061); }
const Pipeline *                     compU_reg_regNode::pipeline() const { return (&pipeline_class_061); }

const Pipeline *                   compU_reg_immI0Node::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                   compU_reg_immI0Node::pipeline() const { return (&pipeline_class_062); }

const Pipeline *              compU_reg_immIAddSubNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *              compU_reg_immIAddSubNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                    compU_reg_immINode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                    compU_reg_immINode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                     compL_reg_regNode::pipeline_class() { return (&pipeline_class_061); }
const Pipeline *                     compL_reg_regNode::pipeline() const { return (&pipeline_class_061); }

const Pipeline *                   compL_reg_immL0Node::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                   compL_reg_immL0Node::pipeline() const { return (&pipeline_class_062); }

const Pipeline *              compL_reg_immLAddSubNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *              compL_reg_immLAddSubNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                    compL_reg_immLNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                    compL_reg_immLNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                    compUL_reg_regNode::pipeline_class() { return (&pipeline_class_061); }
const Pipeline *                    compUL_reg_regNode::pipeline() const { return (&pipeline_class_061); }

const Pipeline *                  compUL_reg_immL0Node::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                  compUL_reg_immL0Node::pipeline() const { return (&pipeline_class_062); }

const Pipeline *             compUL_reg_immLAddSubNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *             compUL_reg_immLAddSubNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                   compUL_reg_immLNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                   compUL_reg_immLNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                     compP_reg_regNode::pipeline_class() { return (&pipeline_class_061); }
const Pipeline *                     compP_reg_regNode::pipeline() const { return (&pipeline_class_061); }

const Pipeline *                     compN_reg_regNode::pipeline_class() { return (&pipeline_class_061); }
const Pipeline *                     compN_reg_regNode::pipeline() const { return (&pipeline_class_061); }

const Pipeline *                         testP_regNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                         testP_regNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                         testN_regNode::pipeline_class() { return (&pipeline_class_062); }
const Pipeline *                         testN_regNode::pipeline() const { return (&pipeline_class_062); }

const Pipeline *                     compF_reg_regNode::pipeline_class() { return (&pipeline_class_085); }
const Pipeline *                     compF_reg_regNode::pipeline() const { return (&pipeline_class_085); }

const Pipeline *                    compF_reg_zeroNode::pipeline_class() { return (&pipeline_class_085); }
const Pipeline *                    compF_reg_zeroNode::pipeline() const { return (&pipeline_class_085); }

const Pipeline *                     compD_reg_regNode::pipeline_class() { return (&pipeline_class_085); }
const Pipeline *                     compD_reg_regNode::pipeline() const { return (&pipeline_class_085); }

const Pipeline *                    compD_reg_zeroNode::pipeline_class() { return (&pipeline_class_085); }
const Pipeline *                    compD_reg_zeroNode::pipeline() const { return (&pipeline_class_085); }

const Pipeline *                    compF3_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                    compF3_reg_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                    compD3_reg_regNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                    compD3_reg_regNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                  compF3_reg_immF0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                  compF3_reg_immF0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                  compD3_reg_immD0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                  compD3_reg_immD0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                 cmpLTMask_reg_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                 cmpLTMask_reg_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                cmpLTMask_reg_zeroNode::pipeline_class() { return (&pipeline_class_055); }
const Pipeline *                cmpLTMask_reg_zeroNode::pipeline() const { return (&pipeline_class_055); }

const Pipeline *                  cmovI_reg_reg_ltNode::pipeline_class() { return (&pipeline_class_064); }
const Pipeline *                  cmovI_reg_reg_ltNode::pipeline() const { return (&pipeline_class_064); }

const Pipeline *                  cmovI_reg_reg_gtNode::pipeline_class() { return (&pipeline_class_064); }
const Pipeline *                  cmovI_reg_reg_gtNode::pipeline() const { return (&pipeline_class_064); }

const Pipeline *                            branchNode::pipeline_class() { return (&pipeline_class_078); }
const Pipeline *                            branchNode::pipeline() const { return (&pipeline_class_078); }

const Pipeline *                         branchConNode::pipeline_class() { return (&pipeline_class_079); }
const Pipeline *                         branchConNode::pipeline() const { return (&pipeline_class_079); }

const Pipeline *                        branchConUNode::pipeline_class() { return (&pipeline_class_079); }
const Pipeline *                        branchConUNode::pipeline() const { return (&pipeline_class_079); }

const Pipeline *                  cmpI_imm0_branchNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *                  cmpI_imm0_branchNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *                  cmpL_imm0_branchNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *                  cmpL_imm0_branchNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *                  cmpP_imm0_branchNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *                  cmpP_imm0_branchNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *                  cmpN_imm0_branchNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *                  cmpN_imm0_branchNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *        cmpP_narrowOop_imm0_branchNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *        cmpP_narrowOop_imm0_branchNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *                 cmpUI_imm0_branchNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *                 cmpUI_imm0_branchNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *                 cmpUL_imm0_branchNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *                 cmpUL_imm0_branchNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *                  cmpL_branch_signNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *                  cmpL_branch_signNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *                  cmpI_branch_signNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *                  cmpI_branch_signNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *                   cmpL_branch_bitNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *                   cmpL_branch_bitNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *                   cmpI_branch_bitNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *                   cmpI_branch_bitNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *              far_cmpL_branch_signNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *              far_cmpL_branch_signNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *              far_cmpI_branch_signNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *              far_cmpI_branch_signNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *               far_cmpL_branch_bitNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *               far_cmpL_branch_bitNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *               far_cmpI_branch_bitNode::pipeline_class() { return (&pipeline_class_080); }
const Pipeline *               far_cmpI_branch_bitNode::pipeline() const { return (&pipeline_class_080); }

const Pipeline *                          cmpL_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                          cmpL_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                          cmpI_andNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                          cmpI_andNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      cmpL_and_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      cmpL_and_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                      cmpI_and_regNode::pipeline_class() { return (&pipeline_class_053); }
const Pipeline *                      cmpI_and_regNode::pipeline() const { return (&pipeline_class_053); }

const Pipeline *                     branchLoopEndNode::pipeline_class() { return (&pipeline_class_078); }
const Pipeline *                     branchLoopEndNode::pipeline() const { return (&pipeline_class_078); }

const Pipeline *                    branchLoopEndUNode::pipeline_class() { return (&pipeline_class_078); }
const Pipeline *                    branchLoopEndUNode::pipeline() const { return (&pipeline_class_078); }

const Pipeline *                       cmpFastLockNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                       cmpFastLockNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                     cmpFastUnlockNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                     cmpFastUnlockNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                         safePointNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                         safePointNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *              CallStaticJavaDirectNode::pipeline_class() { return (&pipeline_class_087); }
const Pipeline *              CallStaticJavaDirectNode::pipeline() const { return (&pipeline_class_087); }

const Pipeline *             CallDynamicJavaDirectNode::pipeline_class() { return (&pipeline_class_087); }
const Pipeline *             CallDynamicJavaDirectNode::pipeline() const { return (&pipeline_class_087); }

const Pipeline *                 CallRuntimeDirectNode::pipeline_class() { return (&pipeline_class_087); }
const Pipeline *                 CallRuntimeDirectNode::pipeline() const { return (&pipeline_class_087); }

const Pipeline *                    CallLeafDirectNode::pipeline_class() { return (&pipeline_class_087); }
const Pipeline *                    CallLeafDirectNode::pipeline() const { return (&pipeline_class_087); }

const Pipeline *                CallLeafNoFPDirectNode::pipeline_class() { return (&pipeline_class_087); }
const Pipeline *                CallLeafNoFPDirectNode::pipeline() const { return (&pipeline_class_087); }

const Pipeline *                  CallNativeDirectNode::pipeline_class() { return (&pipeline_class_087); }
const Pipeline *                  CallNativeDirectNode::pipeline() const { return (&pipeline_class_087); }

const Pipeline *                    TailCalljmpIndNode::pipeline_class() { return (&pipeline_class_087); }
const Pipeline *                    TailCalljmpIndNode::pipeline() const { return (&pipeline_class_087); }

const Pipeline *                        TailjmpIndNode::pipeline_class() { return (&pipeline_class_087); }
const Pipeline *                        TailjmpIndNode::pipeline() const { return (&pipeline_class_087); }

const Pipeline *                   CreateExceptionNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                   CreateExceptionNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                  RethrowExceptionNode::pipeline_class() { return (&pipeline_class_087); }
const Pipeline *                  RethrowExceptionNode::pipeline() const { return (&pipeline_class_087); }

const Pipeline *                               RetNode::pipeline_class() { return (&pipeline_class_078); }
const Pipeline *                               RetNode::pipeline() const { return (&pipeline_class_078); }

const Pipeline *                ShouldNotReachHereNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                ShouldNotReachHereNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *               partialSubtypeCheckNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *               partialSubtypeCheckNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *         partialSubtypeCheckVsZeroNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *         partialSubtypeCheckVsZeroNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                   string_compareUNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                   string_compareUNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                   string_compareLNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                   string_compareLNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                  string_compareULNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                  string_compareULNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                  string_compareLUNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                  string_compareLUNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                  string_indexofUUNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                  string_indexofUUNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                  string_indexofLLNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                  string_indexofLLNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                  string_indexofULNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                  string_indexofULNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *              string_indexof_conUUNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *              string_indexof_conUUNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *              string_indexof_conLLNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *              string_indexof_conLLNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *              string_indexof_conULNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *              string_indexof_conULNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *               string_indexof_charNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *               string_indexof_charNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *              stringL_indexof_charNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *              stringL_indexof_charNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                    string_equalsLNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                    string_equalsLNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                    string_equalsUNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                    string_equalsUNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                     array_equalsBNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                     array_equalsBNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                     array_equalsCNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                     array_equalsCNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                     has_negativesNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     has_negativesNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   string_compressNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   string_compressNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    string_inflateNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                    string_inflateNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                  encode_iso_arrayNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                  encode_iso_arrayNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                          tlsLoadPNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                          tlsLoadPNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                            loadV2Node::pipeline_class() { return (&pipeline_class_049); }
const Pipeline *                            loadV2Node::pipeline() const { return (&pipeline_class_049); }

const Pipeline *                            loadV4Node::pipeline_class() { return (&pipeline_class_049); }
const Pipeline *                            loadV4Node::pipeline() const { return (&pipeline_class_049); }

const Pipeline *                            loadV8Node::pipeline_class() { return (&pipeline_class_049); }
const Pipeline *                            loadV8Node::pipeline() const { return (&pipeline_class_049); }

const Pipeline *                           loadV16Node::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                           loadV16Node::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                           storeV2Node::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                           storeV2Node::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                           storeV4Node::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                           storeV4Node::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                           storeV8Node::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                           storeV8Node::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                          storeV16Node::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                          storeV16Node::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                      reinterpretDNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                      reinterpretDNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                      reinterpretXNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                      reinterpretXNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                    reinterpretD2XNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                    reinterpretD2XNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                    reinterpretX2DNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                    reinterpretX2DNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                    reinterpretS2XNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    reinterpretS2XNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    reinterpretX2SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    reinterpretX2SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    reinterpretS2DNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    reinterpretS2DNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    reinterpretD2SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    reinterpretD2SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vcvt8Bto8SNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt8Bto8SNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt4Bto4SNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt4Bto4SNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt8Sto8BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt8Sto8BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt4Sto4BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt4Sto4BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt4Sto4INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt4Sto4INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt4Ito4SNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt4Ito4SNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt2Ito2LNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt2Ito2LNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt2Lto2INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt2Lto2INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt4Ito4BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt4Ito4BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt4Bto4INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt4Bto4INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt2Lto2FNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vcvt2Lto2FNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vcvt2Ito2FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt2Ito2FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt4Ito4FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt4Ito4FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt2Lto2DNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt2Lto2DNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt4Sto4FNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vcvt4Sto4FNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vcvt2Ito2DNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vcvt2Ito2DNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vcvt4Bto4FNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vcvt4Bto4FNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vcvt2Fto2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vcvt2Fto2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vcvt2Fto2INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt2Fto2INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt4Fto4INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt4Fto4INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt2Dto2LNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt2Dto2LNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt4Fto4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vcvt4Fto4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vcvt2Dto2INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vcvt2Dto2INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vcvt4Fto4BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vcvt4Fto4BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vcvt2Fto2DNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt2Fto2DNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vcvt2Dto2FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vcvt2Dto2FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_add8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_add8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     reduce_add16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     reduce_add16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_add4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_add4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_add8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_add8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_add2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_add2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_mul8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_mul8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     reduce_mul16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     reduce_mul16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_mul4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_mul4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_mul8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_mul8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_mul2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_mul2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_max8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_max8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     reduce_max16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     reduce_max16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_max4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_max4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_max8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_max8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_max4INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_max4INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_min8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_min8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     reduce_min16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     reduce_min16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_min4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_min4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_min8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_min8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_min4INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_min4INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_max2INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_max2INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_min2INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_min2INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_max2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_max2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_min2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_min2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_max2FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_max2FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_max4FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_max4FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_max2DNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_max2DNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_min2FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_min2FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_min4FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_min4FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_min2DNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_min2DNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_and8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_and8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_orr8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_orr8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_eor8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_eor8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     reduce_and16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     reduce_and16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     reduce_orr16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     reduce_orr16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     reduce_eor16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     reduce_eor16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_and4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_and4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_orr4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_orr4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_eor4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_eor4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_and8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_and8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_orr8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_orr8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_eor8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_eor8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_and2INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_and2INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_orr2INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_orr2INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_eor2INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_eor2INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_and4INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_and4INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_orr4INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_orr4INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_eor4INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_eor4INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_and2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_and2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_orr2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_orr2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      reduce_eor2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      reduce_eor2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          insert8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          insert8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         insert16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         insert16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          insert4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          insert4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          insert8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          insert8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          insert2INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          insert2INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          insert4INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          insert4INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          insert2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          insert2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          insert2FNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          insert2FNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          insert4FNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          insert4FNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          insert2DNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          insert2DNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         extract8BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         extract8BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        extract16BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        extract16BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                         extract4SNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         extract4SNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                         extract8SNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         extract8SNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                         extract2INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         extract2INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                         extract4INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         extract4INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                         extract2LNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         extract2LNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                         extract2FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         extract2FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                         extract4FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         extract4FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                         extract2DNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                         extract2DNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                             vcmpDNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                             vcmpDNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                             vcmpXNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                             vcmpXNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vmul2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vmul2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vnot2INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                            vnot2INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot2I_0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot2I_0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot2I_1Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot2I_1Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot2I_2Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot2I_2Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot2I_3Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot2I_3Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot2I_4Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot2I_4Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                            vnot4INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                            vnot4INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot4I_0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot4I_0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot4I_1Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot4I_1Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot4I_2Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot4I_2Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot4I_3Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot4I_3Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot4I_4Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot4I_4Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                            vnot2LNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                            vnot2LNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                          vnot2L_0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                          vnot2L_0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vand_not2INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vand_not2INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2I_1Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2I_1Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2I_0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2I_0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2I_2Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2I_2Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2I_3Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2I_3Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2I_5Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2I_5Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2I_4Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2I_4Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2I_6Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2I_6Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2I_7Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2I_7Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2I_9Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2I_9Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2I_8Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2I_8Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     vand_not2I_10Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     vand_not2I_10Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vand_not4INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vand_not4INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not4I_1Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not4I_1Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not4I_0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not4I_0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not4I_2Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not4I_2Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not4I_3Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not4I_3Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not4I_5Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not4I_5Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not4I_4Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not4I_4Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not4I_6Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not4I_6Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not4I_7Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not4I_7Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not4I_9Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not4I_9Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not4I_8Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not4I_8Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     vand_not4I_10Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     vand_not4I_10Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        vand_not2LNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        vand_not2LNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2L_1Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2L_1Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2L_0Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2L_0Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      vand_not2L_2Node::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      vand_not2L_2Node::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                            vmax8BNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vmax8BNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                           vmax16BNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                           vmax16BNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vmax4SNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vmax4SNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                            vmax8SNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vmax8SNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vmax2INode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vmax2INode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                            vmax4INode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vmax4INode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vmin8BNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vmin8BNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                           vmin16BNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                           vmin16BNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vmin4SNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vmin4SNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                            vmin8SNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vmin8SNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vmin2INode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vmin2INode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                            vmin4INode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vmin4INode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vmax2LNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vmax2LNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vmin2LNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vmin2LNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vbsl8BNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                            vbsl8BNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                           vbsl16BNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                           vbsl16BNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                        loadmask8BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                        loadmask8BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                       loadmask16BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                       loadmask16BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                       storemask8BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                       storemask8BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      storemask16BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      storemask16BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                        loadmask4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        loadmask4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        loadmask8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        loadmask8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       storemask4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       storemask4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       storemask8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       storemask8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        loadmask2INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        loadmask2INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        loadmask4INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        loadmask4INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       storemask2INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       storemask2INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       storemask4INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       storemask4INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        loadmask2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        loadmask2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       storemask2LNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       storemask2LNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vmaskcastDNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                        vmaskcastDNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                        vmaskcastXNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                        vmaskcastXNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                         loadcon8BNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                         loadcon8BNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                        loadcon16BNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *                        loadcon16BNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                     loadshuffle8BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     loadshuffle8BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                    loadshuffle16BNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                    loadshuffle16BNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     loadshuffle4SNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     loadshuffle4SNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     loadshuffle8SNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                     loadshuffle8SNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                     loadshuffle4INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     loadshuffle4INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       rearrange8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       rearrange8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      rearrange16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      rearrange16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       rearrange4SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       rearrange4SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       rearrange8SNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       rearrange8SNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       rearrange4INode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       rearrange4INode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                 anytrue_in_mask8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 anytrue_in_mask8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                anytrue_in_mask16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                anytrue_in_mask16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                 alltrue_in_mask8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 alltrue_in_mask8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                alltrue_in_mask16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                alltrue_in_mask16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vabs8BNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                            vabs8BNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                           vabs16BNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                           vabs16BNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                            vabs4SNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                            vabs4SNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                            vabs8SNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                            vabs8SNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                            vabs2INode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                            vabs2INode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                            vabs4INode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                            vabs4INode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                            vabs2LNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                            vabs2LNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                            vabs2FNode::pipeline_class() { return (&pipeline_class_040); }
const Pipeline *                            vabs2FNode::pipeline() const { return (&pipeline_class_040); }

const Pipeline *                            vabs4FNode::pipeline_class() { return (&pipeline_class_041); }
const Pipeline *                            vabs4FNode::pipeline() const { return (&pipeline_class_041); }

const Pipeline *                            vabs2DNode::pipeline_class() { return (&pipeline_class_041); }
const Pipeline *                            vabs2DNode::pipeline() const { return (&pipeline_class_041); }

const Pipeline *                            vabd2FNode::pipeline_class() { return (&pipeline_class_040); }
const Pipeline *                            vabd2FNode::pipeline() const { return (&pipeline_class_040); }

const Pipeline *                            vabd4FNode::pipeline_class() { return (&pipeline_class_041); }
const Pipeline *                            vabd4FNode::pipeline() const { return (&pipeline_class_041); }

const Pipeline *                            vabd2DNode::pipeline_class() { return (&pipeline_class_041); }
const Pipeline *                            vabd2DNode::pipeline() const { return (&pipeline_class_041); }

const Pipeline *                       replicate8BNode::pipeline_class() { return (&pipeline_class_042); }
const Pipeline *                       replicate8BNode::pipeline() const { return (&pipeline_class_042); }

const Pipeline *                      replicate16BNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                      replicate16BNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                   replicate8B_immNode::pipeline_class() { return (&pipeline_class_047); }
const Pipeline *                   replicate8B_immNode::pipeline() const { return (&pipeline_class_047); }

const Pipeline *                  replicate16B_immNode::pipeline_class() { return (&pipeline_class_048); }
const Pipeline *                  replicate16B_immNode::pipeline() const { return (&pipeline_class_048); }

const Pipeline *                       replicate4SNode::pipeline_class() { return (&pipeline_class_042); }
const Pipeline *                       replicate4SNode::pipeline() const { return (&pipeline_class_042); }

const Pipeline *                       replicate8SNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                       replicate8SNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                   replicate4S_immNode::pipeline_class() { return (&pipeline_class_047); }
const Pipeline *                   replicate4S_immNode::pipeline() const { return (&pipeline_class_047); }

const Pipeline *                   replicate8S_immNode::pipeline_class() { return (&pipeline_class_048); }
const Pipeline *                   replicate8S_immNode::pipeline() const { return (&pipeline_class_048); }

const Pipeline *                       replicate2INode::pipeline_class() { return (&pipeline_class_042); }
const Pipeline *                       replicate2INode::pipeline() const { return (&pipeline_class_042); }

const Pipeline *                       replicate4INode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                       replicate4INode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                   replicate2I_immNode::pipeline_class() { return (&pipeline_class_047); }
const Pipeline *                   replicate2I_immNode::pipeline() const { return (&pipeline_class_047); }

const Pipeline *                   replicate4I_immNode::pipeline_class() { return (&pipeline_class_048); }
const Pipeline *                   replicate4I_immNode::pipeline() const { return (&pipeline_class_048); }

const Pipeline *                       replicate2LNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                       replicate2LNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                  replicate2L_zeroNode::pipeline_class() { return (&pipeline_class_048); }
const Pipeline *                  replicate2L_zeroNode::pipeline() const { return (&pipeline_class_048); }

const Pipeline *                       replicate2FNode::pipeline_class() { return (&pipeline_class_044); }
const Pipeline *                       replicate2FNode::pipeline() const { return (&pipeline_class_044); }

const Pipeline *                       replicate4FNode::pipeline_class() { return (&pipeline_class_045); }
const Pipeline *                       replicate4FNode::pipeline() const { return (&pipeline_class_045); }

const Pipeline *                       replicate2DNode::pipeline_class() { return (&pipeline_class_046); }
const Pipeline *                       replicate2DNode::pipeline() const { return (&pipeline_class_046); }

const Pipeline *                      reduce_add2INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_add2INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_add4INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_add4INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_mul2INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_mul2INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_mul4INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_mul4INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_add2FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_add2FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_add4FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_add4FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_mul2FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_mul2FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_mul4FNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_mul4FNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_add2DNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_add2DNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                      reduce_mul2DNode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                      reduce_mul2DNode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                            vadd8BNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vadd8BNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                           vadd16BNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                           vadd16BNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vadd4SNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vadd4SNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                            vadd8SNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vadd8SNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vadd2INode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vadd2INode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                            vadd4INode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vadd4INode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vadd2LNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vadd2LNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vadd2FNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                            vadd2FNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                            vadd4FNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                            vadd4FNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                            vadd2DNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                            vadd2DNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                            vsub8BNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vsub8BNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                           vsub16BNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                           vsub16BNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vsub4SNode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vsub4SNode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                            vsub8SNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vsub8SNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vsub2INode::pipeline_class() { return (&pipeline_class_027); }
const Pipeline *                            vsub2INode::pipeline() const { return (&pipeline_class_027); }

const Pipeline *                            vsub4INode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vsub4INode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vsub2LNode::pipeline_class() { return (&pipeline_class_028); }
const Pipeline *                            vsub2LNode::pipeline() const { return (&pipeline_class_028); }

const Pipeline *                            vsub2FNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                            vsub2FNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                            vsub4FNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                            vsub4FNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                            vsub2DNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                            vsub2DNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                            vmul8BNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                            vmul8BNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                           vmul16BNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                           vmul16BNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                            vmul4SNode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                            vmul4SNode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                            vmul8SNode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                            vmul8SNode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                            vmul2INode::pipeline_class() { return (&pipeline_class_023); }
const Pipeline *                            vmul2INode::pipeline() const { return (&pipeline_class_023); }

const Pipeline *                            vmul4INode::pipeline_class() { return (&pipeline_class_024); }
const Pipeline *                            vmul4INode::pipeline() const { return (&pipeline_class_024); }

const Pipeline *                            vmul2FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            vmul2FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            vmul4FNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                            vmul4FNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                            vmul2DNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                            vmul2DNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                            vmla4SNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                            vmla4SNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                          vmla4S_0Node::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                          vmla4S_0Node::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                            vmla8SNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                            vmla8SNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                          vmla8S_0Node::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                          vmla8S_0Node::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                            vmla2INode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                            vmla2INode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                          vmla2I_0Node::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                          vmla2I_0Node::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                            vmla4INode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                            vmla4INode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                          vmla4I_0Node::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                          vmla4I_0Node::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                            vmla2FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            vmla2FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            vmla4FNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                            vmla4FNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                            vmla2DNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                            vmla2DNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                            vmls4SNode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                            vmls4SNode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                            vmls8SNode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                            vmls8SNode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                            vmls2INode::pipeline_class() { return (&pipeline_class_025); }
const Pipeline *                            vmls2INode::pipeline() const { return (&pipeline_class_025); }

const Pipeline *                            vmls4INode::pipeline_class() { return (&pipeline_class_026); }
const Pipeline *                            vmls4INode::pipeline() const { return (&pipeline_class_026); }

const Pipeline *                            vmls2FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            vmls2FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          vmls2F_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          vmls2F_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            vmls4FNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                            vmls4FNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                          vmls4F_0Node::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                          vmls4F_0Node::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                            vmls2DNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                            vmls2DNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                          vmls2D_0Node::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                          vmls2D_0Node::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                        vmuladdS2INode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                        vmuladdS2INode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                            vdiv2FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            vdiv2FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            vdiv4FNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                            vdiv4FNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                            vdiv2DNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                            vdiv2DNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                           vsqrt2FNode::pipeline_class() { return (&pipeline_class_040); }
const Pipeline *                           vsqrt2FNode::pipeline() const { return (&pipeline_class_040); }

const Pipeline *                           vsqrt4FNode::pipeline_class() { return (&pipeline_class_039); }
const Pipeline *                           vsqrt4FNode::pipeline() const { return (&pipeline_class_039); }

const Pipeline *                           vsqrt2DNode::pipeline_class() { return (&pipeline_class_039); }
const Pipeline *                           vsqrt2DNode::pipeline() const { return (&pipeline_class_039); }

const Pipeline *                            vneg2FNode::pipeline_class() { return (&pipeline_class_040); }
const Pipeline *                            vneg2FNode::pipeline() const { return (&pipeline_class_040); }

const Pipeline *                            vneg4FNode::pipeline_class() { return (&pipeline_class_041); }
const Pipeline *                            vneg4FNode::pipeline() const { return (&pipeline_class_041); }

const Pipeline *                            vneg2DNode::pipeline_class() { return (&pipeline_class_041); }
const Pipeline *                            vneg2DNode::pipeline() const { return (&pipeline_class_041); }

const Pipeline *                            vand8BNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                            vand8BNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                           vand16BNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                           vand16BNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                             vor8BNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                             vor8BNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                            vor16BNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                            vor16BNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                            vxor8BNode::pipeline_class() { return (&pipeline_class_029); }
const Pipeline *                            vxor8BNode::pipeline() const { return (&pipeline_class_029); }

const Pipeline *                           vxor16BNode::pipeline_class() { return (&pipeline_class_030); }
const Pipeline *                           vxor16BNode::pipeline() const { return (&pipeline_class_030); }

const Pipeline *                       vshiftcnt8BNode::pipeline_class() { return (&pipeline_class_042); }
const Pipeline *                       vshiftcnt8BNode::pipeline() const { return (&pipeline_class_042); }

const Pipeline *                     vshiftcnt8B_0Node::pipeline_class() { return (&pipeline_class_042); }
const Pipeline *                     vshiftcnt8B_0Node::pipeline() const { return (&pipeline_class_042); }

const Pipeline *                      vshiftcnt16BNode::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                      vshiftcnt16BNode::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                    vshiftcnt16B_0Node::pipeline_class() { return (&pipeline_class_043); }
const Pipeline *                    vshiftcnt16B_0Node::pipeline() const { return (&pipeline_class_043); }

const Pipeline *                            vsll8BNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                            vsll8BNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                           vsll16BNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                           vsll16BNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                            vsra8BNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                            vsra8BNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                           vsra16BNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                           vsra16BNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                            vsrl8BNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                            vsrl8BNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                           vsrl16BNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                           vsrl16BNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                        vsll8B_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                        vsll8B_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                       vsll16B_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                       vsll16B_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                        vsra8B_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                        vsra8B_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                       vsra16B_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                       vsra16B_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                        vsrl8B_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                        vsrl8B_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                       vsrl16B_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                       vsrl16B_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                            vsll4SNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                            vsll4SNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                            vsll8SNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                            vsll8SNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                            vsra4SNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                            vsra4SNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                            vsra8SNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                            vsra8SNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                            vsrl4SNode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                            vsrl4SNode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                            vsrl8SNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                            vsrl8SNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                        vsll4S_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                        vsll4S_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                        vsll8S_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                        vsll8S_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                        vsra4S_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                        vsra4S_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                        vsra8S_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                        vsra8S_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                        vsrl4S_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                        vsrl4S_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                        vsrl8S_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                        vsrl8S_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                            vsll2INode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                            vsll2INode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                            vsll4INode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                            vsll4INode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                            vsra2INode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                            vsra2INode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                            vsra4INode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                            vsra4INode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                            vsrl2INode::pipeline_class() { return (&pipeline_class_031); }
const Pipeline *                            vsrl2INode::pipeline() const { return (&pipeline_class_031); }

const Pipeline *                            vsrl4INode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                            vsrl4INode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                        vsll2I_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                        vsll2I_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                        vsll4I_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                        vsll4I_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                        vsra2I_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                        vsra2I_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                        vsra4I_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                        vsra4I_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                        vsrl2I_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                        vsrl2I_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                        vsrl4I_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                        vsrl4I_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                            vsll2LNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                            vsll2LNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                            vsra2LNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                            vsra2LNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                            vsrl2LNode::pipeline_class() { return (&pipeline_class_032); }
const Pipeline *                            vsrl2LNode::pipeline() const { return (&pipeline_class_032); }

const Pipeline *                        vsll2L_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                        vsll2L_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                        vsra2L_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                        vsra2L_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                        vsrl2L_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                        vsrl2L_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                       vsraa8B_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                       vsraa8B_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                     vsraa8B_imm_0Node::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                     vsraa8B_imm_0Node::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                      vsraa16B_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                      vsraa16B_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                    vsraa16B_imm_0Node::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                    vsraa16B_imm_0Node::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                       vsraa4S_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                       vsraa4S_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                     vsraa4S_imm_0Node::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                     vsraa4S_imm_0Node::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                       vsraa8S_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                       vsraa8S_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                     vsraa8S_imm_0Node::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                     vsraa8S_imm_0Node::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                       vsraa2I_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                       vsraa2I_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                     vsraa2I_imm_0Node::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                     vsraa2I_imm_0Node::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                       vsraa4I_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                       vsraa4I_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                     vsraa4I_imm_0Node::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                     vsraa4I_imm_0Node::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                       vsraa2L_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                       vsraa2L_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                     vsraa2L_imm_0Node::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                     vsraa2L_imm_0Node::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                       vsrla8B_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                       vsrla8B_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                     vsrla8B_imm_0Node::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                     vsrla8B_imm_0Node::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                      vsrla16B_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                      vsrla16B_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                    vsrla16B_imm_0Node::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                    vsrla16B_imm_0Node::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                       vsrla4S_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                       vsrla4S_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                     vsrla4S_imm_0Node::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                     vsrla4S_imm_0Node::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                       vsrla8S_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                       vsrla8S_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                     vsrla8S_imm_0Node::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                     vsrla8S_imm_0Node::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                       vsrla2I_immNode::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                       vsrla2I_immNode::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                     vsrla2I_imm_0Node::pipeline_class() { return (&pipeline_class_033); }
const Pipeline *                     vsrla2I_imm_0Node::pipeline() const { return (&pipeline_class_033); }

const Pipeline *                       vsrla4I_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                       vsrla4I_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                     vsrla4I_imm_0Node::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                     vsrla4I_imm_0Node::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                       vsrla2L_immNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                       vsrla2L_immNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                     vsrla2L_imm_0Node::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                     vsrla2L_imm_0Node::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                            vmax2FNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                            vmax2FNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                            vmax4FNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                            vmax4FNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                            vmax2DNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                            vmax2DNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                            vmin2FNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                            vmin2FNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                            vmin4FNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                            vmin4FNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                            vmin2DNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                            vmin2DNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                      vround2D_regNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                      vround2D_regNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                       vpopcount4INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                       vpopcount4INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                       vpopcount2INode::pipeline_class() { return (&pipeline_class_084); }
const Pipeline *                       vpopcount2INode::pipeline() const { return (&pipeline_class_084); }

const Pipeline *                 vmask_truecount8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 vmask_truecount8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                vmask_truecount16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                vmask_truecount16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *              vmask_firsttrue_LT8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *              vmask_firsttrue_LT8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                 vmask_firsttrue8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 vmask_firsttrue8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                vmask_firsttrue16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                vmask_firsttrue16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vmask_lasttrue8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vmask_lasttrue8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                 vmask_lasttrue16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 vmask_lasttrue16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    vmask_tolong8BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    vmask_tolong8BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   vmask_tolong16BNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   vmask_tolong16BNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             loadVNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             loadVNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            storeVNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            storeVNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       loadV2_vregNode::pipeline_class() { return (&pipeline_class_049); }
const Pipeline *                       loadV2_vregNode::pipeline() const { return (&pipeline_class_049); }

const Pipeline *                      storeV2_vregNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                      storeV2_vregNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                       loadV4_vregNode::pipeline_class() { return (&pipeline_class_049); }
const Pipeline *                       loadV4_vregNode::pipeline() const { return (&pipeline_class_049); }

const Pipeline *                      storeV4_vregNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                      storeV4_vregNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                       loadV8_vregNode::pipeline_class() { return (&pipeline_class_049); }
const Pipeline *                       loadV8_vregNode::pipeline() const { return (&pipeline_class_049); }

const Pipeline *                      storeV8_vregNode::pipeline_class() { return (&pipeline_class_051); }
const Pipeline *                      storeV8_vregNode::pipeline() const { return (&pipeline_class_051); }

const Pipeline *                      loadV16_vregNode::pipeline_class() { return (&pipeline_class_050); }
const Pipeline *                      loadV16_vregNode::pipeline() const { return (&pipeline_class_050); }

const Pipeline *                     storeV16_vregNode::pipeline_class() { return (&pipeline_class_052); }
const Pipeline *                     storeV16_vregNode::pipeline() const { return (&pipeline_class_052); }

const Pipeline *                     loadV_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     loadV_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    storeV_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    storeV_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      loadV_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      loadV_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *              loadV_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *              loadV_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     storeV_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     storeV_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *             storeV_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *             storeV_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     vmaskAll_immINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     vmaskAll_immINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vmaskAllINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vmaskAllINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     vmaskAll_immLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     vmaskAll_immLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vmaskAllLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vmaskAllLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vmask_andNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vmask_andNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vmask_orNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vmask_orNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vmask_xorNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vmask_xorNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    vmask_and_notINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    vmask_and_notINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    vmask_and_notLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    vmask_and_notLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reinterpretNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                       reinterpretNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                 reinterpretResizeNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 reinterpretResizeNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *      vmask_reinterpret_same_esizeNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *      vmask_reinterpret_same_esizeNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *      vmask_reinterpret_diff_esizeNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *      vmask_reinterpret_diff_esizeNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vabsBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vabsBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vabsSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vabsSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vabsINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vabsINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vabsLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vabsLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vabsFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vabsFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vabsDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vabsDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vabsB_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vabsB_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vabsS_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vabsS_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vabsI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vabsI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vabsL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vabsL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vabsF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vabsF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vabsD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vabsD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vaddBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vaddBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vaddSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vaddSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vaddINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vaddINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vaddLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vaddLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vaddFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vaddFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vaddDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vaddDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vaddB_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vaddB_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vaddS_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vaddS_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vaddI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vaddI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vaddL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vaddL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vaddF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vaddF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vaddD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vaddD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vaddImmBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vaddImmBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vaddImmB_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vaddImmB_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vaddImmSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vaddImmSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vaddImmS_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vaddImmS_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vaddImmINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vaddImmINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vaddImmI_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vaddImmI_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vaddImmLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vaddImmLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vaddImmL_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vaddImmL_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vandBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vandBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vandB_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vandB_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vandHNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vandHNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vandH_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vandH_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vandSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vandSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vandS_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vandS_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vandDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vandDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vandD_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vandD_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                              vorBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                              vorBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vorB_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vorB_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                              vorHNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                              vorHNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vorH_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vorH_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                              vorSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                              vorSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vorS_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vorS_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                              vorDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                              vorDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vorD_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vorD_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vxorBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vxorBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vxorB_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vxorB_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vxorHNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vxorHNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vxorH_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vxorH_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vxorSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vxorSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vxorS_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vxorS_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vxorDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vxorDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vxorD_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vxorD_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                              vandNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                              vandNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                               vorNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                               vorNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                              vxorNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                              vxorNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vor_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vor_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vxor_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vxor_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vnotINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vnotINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vnotI_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vnotI_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vnotI_1Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vnotI_1Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vnotI_2Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vnotI_2Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vnotI_3Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vnotI_3Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vnotI_4Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vnotI_4Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vnotLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vnotLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vnotL_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vnotL_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vand_notINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vand_notINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notI_1Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notI_1Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notI_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notI_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notI_2Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notI_2Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notI_3Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notI_3Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notI_5Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notI_5Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notI_4Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notI_4Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notI_6Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notI_6Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notI_7Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notI_7Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notI_9Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notI_9Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notI_8Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notI_8Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vand_notI_10Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vand_notI_10Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vand_notLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vand_notLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notL_1Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notL_1Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notL_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notL_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vand_notL_2Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vand_notL_2Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vdivFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vdivFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vdivDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vdivDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     vfdivF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     vfdivF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     vfdivD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     vfdivD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                              vminNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                              vminNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                              vmaxNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                              vmaxNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vmin_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vmin_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vmax_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vmax_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vfmlaFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vfmlaFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vfmlaDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vfmlaDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     vfmlaF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     vfmlaF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     vfmlaD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     vfmlaD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vfmlsFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vfmlsFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vfmlsF_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vfmlsF_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vfmlsDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vfmlsDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vfmlsD_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vfmlsD_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vfnmlaFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vfnmlaFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vfnmlaF_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vfnmlaF_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vfnmlaDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vfnmlaDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vfnmlaD_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vfnmlaD_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vfnmlsFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vfnmlsFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vfnmlsDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vfnmlsDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmlaBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmlaBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vmlaB_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vmlaB_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmlaSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmlaSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vmlaS_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vmlaS_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmlaINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmlaINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vmlaI_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vmlaI_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmlaLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmlaLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vmlaL_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vmlaL_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmlsBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmlsBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmlsSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmlsSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmlsINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmlsINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmlsLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmlsLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmulBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmulBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmulSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmulSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmulINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmulINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmulLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmulLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmulFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmulFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vmulDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vmulDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vmulB_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vmulB_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vmulS_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vmulS_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vmulI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vmulI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vmulL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vmulL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vmulF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vmulF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vmulD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vmulD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vnegFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vnegFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vnegDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vnegDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vnegF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vnegF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vnegD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vnegD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vpopcountINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vpopcountINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vmaskcmpNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vmaskcmpNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   vmaskcmp_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   vmaskcmp_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vblendNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vblendNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vloadmaskBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vloadmaskBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vloadmask_extendNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vloadmask_extendNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       vstoremaskBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       vstoremaskBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                 vstoremask_narrowNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 vstoremask_narrowNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   vloadmask_loadVNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   vloadmask_loadVNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *           vloadmask_loadV_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *           vloadmask_loadV_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                 storeV_vstoremaskNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 storeV_vstoremaskNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *         storeV_vstoremask_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *         storeV_vstoremask_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_addINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_addINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_addLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_addLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_addFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_addFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_addDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_addDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_addI_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_addI_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_addL_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_addL_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_addF_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_addF_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_addD_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_addD_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_addI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_addI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_addL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_addL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_addF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_addF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_addD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_addD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_addI_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_addI_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_addL_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_addL_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_addF_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_addF_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_addD_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_addD_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_andINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_andINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_andLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_andLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_andI_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_andI_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_andL_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_andL_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_andI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_andI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_andL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_andL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_andI_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_andI_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_andL_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_andL_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        reduce_orINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        reduce_orINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        reduce_orLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        reduce_orLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_orI_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_orI_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_orL_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_orL_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                 reduce_orI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 reduce_orI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                 reduce_orL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                 reduce_orL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *         reduce_orI_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *         reduce_orI_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *         reduce_orL_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *         reduce_orL_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_eorINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_eorINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_eorLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_eorLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_eorI_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_eorI_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_eorL_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_eorL_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_eorI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_eorI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_eorL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_eorL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_eorI_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_eorI_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_eorL_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_eorL_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_maxINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_maxINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_maxLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_maxLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_maxI_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_maxI_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_maxL_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_maxL_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_maxFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_maxFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_maxF_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_maxF_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_maxDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_maxDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_maxD_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_maxD_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_maxI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_maxI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_maxL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_maxL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_maxI_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_maxI_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_maxL_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_maxL_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_maxF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_maxF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_maxD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_maxD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_maxF_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_maxF_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_maxD_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_maxD_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_minINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_minINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_minLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_minLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_minI_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_minI_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_minL_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_minL_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_minFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_minFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_minF_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_minF_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       reduce_minDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       reduce_minDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               reduce_minD_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               reduce_minD_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_minI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_minI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_minL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_minL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_minI_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_minI_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_minL_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_minL_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_minF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_minF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                reduce_minD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                reduce_minD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_minF_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_minF_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        reduce_minD_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        reduce_minD_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           vroundDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           vroundDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        replicateBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        replicateBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        replicateSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        replicateSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        replicateINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        replicateINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        replicateLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        replicateLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   replicateB_imm8Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   replicateB_imm8Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   replicateS_imm8Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   replicateS_imm8Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   replicateI_imm8Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   replicateI_imm8Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   replicateL_imm8Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   replicateL_imm8Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        replicateFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        replicateFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        replicateDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        replicateDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vasrBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vasrBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vasrSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vasrSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vasrINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vasrINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vasrLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vasrLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vlslBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vlslBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vlslSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vlslSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vlslINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vlslINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vlslLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vlslLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vlsrBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vlsrBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vlsrSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vlsrSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vlsrINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vlsrINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vlsrLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vlsrLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vasrB_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vasrB_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vasrS_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vasrS_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vasrI_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vasrI_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vasrL_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vasrL_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vlsrB_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vlsrB_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vlsrS_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vlsrS_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vlsrI_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vlsrI_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vlsrL_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vlsrL_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vlslB_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vlslB_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vlslS_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vlslS_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vlslI_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vlslI_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vlslL_immNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vlslL_immNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vshiftcntBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vshiftcntBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vshiftcntB_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vshiftcntB_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vshiftcntSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vshiftcntSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vshiftcntS_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vshiftcntS_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vshiftcntINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vshiftcntINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vshiftcntI_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vshiftcntI_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                        vshiftcntLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                        vshiftcntLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vshiftcntL_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vshiftcntL_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vasrB_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vasrB_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vasrS_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vasrS_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vasrI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vasrI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vasrL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vasrL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vlslB_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vlslB_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vlslS_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vlslS_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vlslI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vlslI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vlslL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vlslL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vlsrB_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vlsrB_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vlsrS_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vlsrS_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vlsrI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vlsrI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vlsrL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vlsrL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vasrB_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vasrB_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vasrS_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vasrS_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vasrI_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vasrI_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vasrL_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vasrL_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vlsrB_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vlsrB_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vlsrS_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vlsrS_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vlsrI_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vlsrI_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vlsrL_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vlsrL_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vlslB_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vlslB_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vlslS_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vlslS_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vlslI_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vlslI_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vlslL_imm_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vlslL_imm_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vsqrtFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vsqrtFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            vsqrtDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                            vsqrtDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     vsqrtF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     vsqrtF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     vsqrtD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     vsqrtD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vsubBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vsubBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vsubSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vsubSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vsubINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vsubINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vsubLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vsubLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vsubFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vsubFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                             vsubDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                             vsubDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vsubB_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vsubB_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vsubS_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vsubS_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vsubI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vsubI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vsubL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vsubL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vsubF_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vsubF_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vsubD_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vsubD_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vmaskcastNode::pipeline_class() { return (&pipeline_class_083); }
const Pipeline *                         vmaskcastNode::pipeline() const { return (&pipeline_class_083); }

const Pipeline *                  vmaskcast_extendNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vmaskcast_extendNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  vmaskcast_narrowNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  vmaskcast_narrowNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   vcvtBtoX_extendNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   vcvtBtoX_extendNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtStoBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtStoBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   vcvtStoX_extendNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   vcvtStoX_extendNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtItoBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtItoBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtItoSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtItoSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtItoLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtItoLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtItoFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtItoFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtItoDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtItoDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   vcvtLtoX_narrowNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   vcvtLtoX_narrowNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtLtoFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtLtoFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtLtoDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtLtoDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   vcvtFtoX_narrowNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   vcvtFtoX_narrowNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtFtoINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtFtoINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtFtoLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtFtoLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtFtoDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtFtoDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   vcvtDtoX_narrowNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   vcvtDtoX_narrowNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtDtoLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtDtoLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          vcvtDtoFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          vcvtDtoFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          extractBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          extractBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          extractSNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          extractSNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          extractINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          extractINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          extractLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          extractLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          extractFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          extractFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          extractDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          extractDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     vtest_alltrueNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     vtest_alltrueNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     vtest_anytrueNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     vtest_anytrueNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *             vtest_alltrue_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *             vtest_alltrue_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *             vtest_anytrue_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *             vtest_anytrue_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     insertI_smallNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     insertI_smallNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                     insertF_smallNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                     insertF_smallNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           insertINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           insertINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           insertLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           insertLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           insertDNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           insertDNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           insertFNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           insertFNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       loadshuffleNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                       loadshuffleNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         rearrangeNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         rearrangeNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           gatherINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           gatherINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                           gatherLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                           gatherLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   gatherI_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   gatherI_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   gatherL_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   gatherL_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    gatherI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    gatherI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    gatherL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    gatherL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            gatherI_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            gatherI_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            gatherL_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            gatherL_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          scatterINode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          scatterINode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          scatterLNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          scatterLNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  scatterI_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  scatterI_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                  scatterL_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  scatterL_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   scatterI_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   scatterI_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   scatterL_maskedNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   scatterL_maskedNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *           scatterI_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *           scatterI_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *           scatterL_masked_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *           scatterL_masked_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                          loadconBNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                          loadconBNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *          stringL_indexof_char_sveNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *          stringL_indexof_char_sveNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *          stringU_indexof_char_sveNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *          stringU_indexof_char_sveNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *              string_compareLL_sveNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *              string_compareLL_sveNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *              string_compareLU_sveNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *              string_compareLU_sveNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *              string_compareUL_sveNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *              string_compareUL_sveNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *              string_compareUU_sveNode::pipeline_class() { return (&pipeline_class_086); }
const Pipeline *              string_compareUU_sveNode::pipeline() const { return (&pipeline_class_086); }

const Pipeline *                   vmask_truecountNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   vmask_truecountNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                   vmask_firsttrueNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                   vmask_firsttrueNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                    vmask_lasttrueNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                    vmask_lasttrueNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *           vmask_truecount_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *           vmask_truecount_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *           vmask_firsttrue_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *           vmask_firsttrue_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *            vmask_lasttrue_partialNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *            vmask_lasttrue_partialNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                      vmask_tolongNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                      vmask_tolongNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                         vmask_genNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                         vmask_genNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        compareAndSwapP_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        compareAndSwapP_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *        compareAndSwapN_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *        compareAndSwapN_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *     compareAndSwapPAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *     compareAndSwapPAcq_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *     compareAndSwapNAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *     compareAndSwapNAcq_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *    compareAndExchangeN_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *    compareAndExchangeN_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *    compareAndExchangeP_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *    compareAndExchangeP_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline * compareAndExchangeNAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline * compareAndExchangeNAcq_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline * compareAndExchangePAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline * compareAndExchangePAcq_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *    weakCompareAndSwapN_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *    weakCompareAndSwapN_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *    weakCompareAndSwapP_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *    weakCompareAndSwapP_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline * weakCompareAndSwapNAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline * weakCompareAndSwapNAcq_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline * weakCompareAndSwapPAcq_shenandoahNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline * weakCompareAndSwapPAcq_shenandoahNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                            zLoadPNode::pipeline_class() { return (&pipeline_class_073); }
const Pipeline *                            zLoadPNode::pipeline() const { return (&pipeline_class_073); }

const Pipeline *                    zLoadPVolatileNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    zLoadPVolatileNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                  zCompareAndSwapPNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                  zCompareAndSwapPNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                zCompareAndSwapP_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *                zCompareAndSwapP_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *               zCompareAndSwapPAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *               zCompareAndSwapPAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *             zCompareAndSwapPAcq_0Node::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *             zCompareAndSwapPAcq_0Node::pipeline() const { return (&pipeline_class_082); }

const Pipeline *              zCompareAndExchangePNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *              zCompareAndExchangePNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *           zCompareAndExchangePAcqNode::pipeline_class() { return (&pipeline_class_082); }
const Pipeline *           zCompareAndExchangePAcqNode::pipeline() const { return (&pipeline_class_082); }

const Pipeline *                       zGetAndSetPNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                       zGetAndSetPNode::pipeline() const { return (&pipeline_class_081); }

const Pipeline *                    zGetAndSetPAcqNode::pipeline_class() { return (&pipeline_class_081); }
const Pipeline *                    zGetAndSetPAcqNode::pipeline() const { return (&pipeline_class_081); }
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
