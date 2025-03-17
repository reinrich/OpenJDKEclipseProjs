#line 1 "ad_x86_pipeline.cpp"
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

const Pipeline_Use_Element Pipeline_Use::elaborated_elements[11] = {
  Pipeline_Use_Element(0, 0, 0, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 1, 1, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 2, 2, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 3, 3, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 4, 4, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 5, 5, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 6, 6, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 7, 7, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 8, 8, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 9, 9, false, Pipeline_Use_Cycle_Mask(0)),
  Pipeline_Use_Element(0, 10, 10, false, Pipeline_Use_Cycle_Mask(0))
};

const Pipeline_Use Pipeline_Use::elaborated_use(0, 0, 11, (Pipeline_Use_Element *)&elaborated_elements[0]);


// Pipeline Class "ialu_reg"
static const enum machPipelineStages pipeline_reads_001[1] = {
  stage_S3 
};

static const enum machPipelineStages pipeline_res_stages_001[11] = {
  stage_S0,        // D0
  stage_S0,        // D1
  stage_S0,        // D2
  stage_undefined, // MS0
  stage_undefined, // MS1
  stage_undefined, // MS2
  stage_undefined, // BR
  stage_undefined, // FPU
  stage_S3,        // ALU0
  stage_S3,        // ALU1
  stage_S3         // ALU2
};

static const uint pipeline_res_cycles_001[11] = {
  1, // D0
  1, // D1
  1, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  0, // FPU
  1, // ALU0
  1, // ALU1
  1  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_001[2] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x700, 8, 10, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_001((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x707, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "ialu_reg_long"
static const uint pipeline_res_cycles_002[11] = {
  2, // D0
  2, // D1
  2, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  0, // FPU
  2, // ALU0
  2, // ALU1
  2  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_002[2] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000002)),
  Pipeline_Use_Element(0x700, 8, 10, true,  Pipeline_Use_Cycle_Mask(0x0000000c)) 
};

static const Pipeline pipeline_class_002((uint)stage_undefined, 1, false, 0, 2, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_002,
  Pipeline_Use(0x707, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_002[0]));

// Pipeline Class "ialu_reg_fat"
static const enum machPipelineStages pipeline_res_stages_002[11] = {
  stage_S0,        // D0
  stage_undefined, // D1
  stage_undefined, // D2
  stage_undefined, // MS0
  stage_undefined, // MS1
  stage_undefined, // MS2
  stage_undefined, // BR
  stage_undefined, // FPU
  stage_S3,        // ALU0
  stage_S3,        // ALU1
  stage_S3         // ALU2
};

static const uint pipeline_res_cycles_003[11] = {
  1, // D0
  0, // D1
  0, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  0, // FPU
  1, // ALU0
  1, // ALU1
  1  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_003[2] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x700, 8, 10, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_003((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_002,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0x701, 0x1, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "ialu_reg_reg"
static const Pipeline pipeline_class_004((uint)stage_S4, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x707, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "ialu_reg_reg_fat"
static const Pipeline pipeline_class_005((uint)stage_S4, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_002,
  (uint *) pipeline_res_cycles_003,
  Pipeline_Use(0x701, 0x1, 2, (Pipeline_Use_Element *)&pipeline_res_mask_003[0]));

// Pipeline Class "ialu_reg_mem"
static const enum machPipelineStages pipeline_res_stages_003[11] = {
  stage_S0,        // D0
  stage_undefined, // D1
  stage_undefined, // D2
  stage_S3,        // MS0
  stage_S3,        // MS1
  stage_S3,        // MS2
  stage_undefined, // BR
  stage_undefined, // FPU
  stage_S4,        // ALU0
  stage_S4,        // ALU1
  stage_S4         // ALU2
};

static const uint pipeline_res_cycles_004[11] = {
  1, // D0
  0, // D1
  0, // D2
  1, // MS0
  1, // MS1
  1, // MS2
  0, // BR
  0, // FPU
  1, // ALU0
  1, // ALU1
  1  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_004[3] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x700, 8, 10, true,  Pipeline_Use_Cycle_Mask(0x00000008)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_006((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_003,
  (uint *) pipeline_res_cycles_004,
  Pipeline_Use(0x739, 0x1, 3, (Pipeline_Use_Element *)&pipeline_res_mask_004[0]));

// Pipeline Class "ialu_mem"
static const enum machPipelineStages pipeline_res_stages_004[11] = {
  stage_S0,        // D0
  stage_undefined, // D1
  stage_undefined, // D2
  stage_S3,        // MS0
  stage_S3,        // MS1
  stage_S3,        // MS2
  stage_undefined, // BR
  stage_undefined, // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_005[11] = {
  1, // D0
  0, // D1
  0, // D2
  1, // MS0
  1, // MS1
  1, // MS2
  0, // BR
  0, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_005[2] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_007((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_004,
  (uint *) pipeline_res_cycles_005,
  Pipeline_Use(0x39, 0x1, 2, (Pipeline_Use_Element *)&pipeline_res_mask_005[0]));

// Pipeline Class "ialu_mem_reg"
static const enum machPipelineStages pipeline_reads_002[2] = {
  stage_S3,
  stage_S5 
};

static const Pipeline pipeline_class_008((uint)stage_undefined, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_003,
  (uint *) pipeline_res_cycles_004,
  Pipeline_Use(0x739, 0x1, 3, (Pipeline_Use_Element *)&pipeline_res_mask_004[0]));

// Pipeline Class "ialu_mem_imm"
static const Pipeline pipeline_class_009((uint)stage_undefined, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_003,
  (uint *) pipeline_res_cycles_004,
  Pipeline_Use(0x739, 0x1, 3, (Pipeline_Use_Element *)&pipeline_res_mask_004[0]));

// Pipeline Class "ialu_reg_reg_alu0"
static const enum machPipelineStages pipeline_res_stages_005[11] = {
  stage_S0,        // D0
  stage_undefined, // D1
  stage_undefined, // D2
  stage_undefined, // MS0
  stage_undefined, // MS1
  stage_undefined, // MS2
  stage_undefined, // BR
  stage_undefined, // FPU
  stage_S3,        // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_006[11] = {
  1, // D0
  0, // D1
  0, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  0, // FPU
  1, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_006[2] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_010((uint)stage_S4, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_005,
  (uint *) pipeline_res_cycles_006,
  Pipeline_Use(0x101, 0x101, 2, (Pipeline_Use_Element *)&pipeline_res_mask_006[0]));

// Pipeline Class "ialu_reg_mem_alu0"
static const enum machPipelineStages pipeline_res_stages_006[11] = {
  stage_S0,        // D0
  stage_undefined, // D1
  stage_undefined, // D2
  stage_S3,        // MS0
  stage_S3,        // MS1
  stage_S3,        // MS2
  stage_undefined, // BR
  stage_undefined, // FPU
  stage_S4,        // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_007[11] = {
  1, // D0
  0, // D1
  0, // D2
  1, // MS0
  1, // MS1
  1, // MS2
  0, // BR
  0, // FPU
  1, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_007[3] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x100, 8, 8, false, Pipeline_Use_Cycle_Mask(0x00000008)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_011((uint)stage_S5, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_006,
  (uint *) pipeline_res_cycles_007,
  Pipeline_Use(0x139, 0x101, 3, (Pipeline_Use_Element *)&pipeline_res_mask_007[0]));

// Pipeline Class "ialu_cr_reg_reg"
static const enum machPipelineStages pipeline_reads_003[2] = {
  stage_S3,
  stage_S3 
};

static const Pipeline pipeline_class_012((uint)stage_S4, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_003,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x707, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "ialu_cr_reg_imm"
static const Pipeline pipeline_class_013((uint)stage_S4, 1, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_001,
  (uint *) pipeline_res_cycles_001,
  Pipeline_Use(0x707, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_001[0]));

// Pipeline Class "ialu_cr_reg_mem"
static const Pipeline pipeline_class_014((uint)stage_S4, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_003,
   (enum machPipelineStages *) pipeline_res_stages_003,
  (uint *) pipeline_res_cycles_004,
  Pipeline_Use(0x739, 0x1, 3, (Pipeline_Use_Element *)&pipeline_res_mask_004[0]));

// Pipeline Class "pipe_cmplt"
static const enum machPipelineStages pipeline_reads_004[3] = {
  stage_S3,
  stage_S3,
  stage_S4 
};

static const enum machPipelineStages pipeline_res_stages_007[11] = {
  stage_S0,        // D0
  stage_S0,        // D1
  stage_S0,        // D2
  stage_undefined, // MS0
  stage_undefined, // MS1
  stage_undefined, // MS2
  stage_undefined, // BR
  stage_undefined, // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_008[11] = {
  4, // D0
  4, // D1
  4, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  0, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_008[1] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000008)) 
};

static const Pipeline pipeline_class_015((uint)stage_undefined, 3, false, 0, 4, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_004,
   (enum machPipelineStages *) pipeline_res_stages_007,
  (uint *) pipeline_res_cycles_008,
  Pipeline_Use(0x7, 0x0, 1, (Pipeline_Use_Element *)&pipeline_res_mask_008[0]));

// Pipeline Class "pipe_cmov_reg"
static const uint pipeline_res_cycles_009[11] = {
  1, // D0
  1, // D1
  1, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  0, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_009[1] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000001)) 
};

static const Pipeline pipeline_class_016((uint)stage_S4, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_003,
   (enum machPipelineStages *) pipeline_res_stages_007,
  (uint *) pipeline_res_cycles_009,
  Pipeline_Use(0x7, 0x0, 1, (Pipeline_Use_Element *)&pipeline_res_mask_009[0]));

// Pipeline Class "pipe_cmov_mem"
static const enum machPipelineStages pipeline_reads_005[3] = {
  stage_S3,
  stage_S4,
  stage_S3 
};

static const enum machPipelineStages pipeline_res_stages_008[11] = {
  stage_S0,        // D0
  stage_S0,        // D1
  stage_S0,        // D2
  stage_S3,        // MS0
  stage_S3,        // MS1
  stage_S3,        // MS2
  stage_undefined, // BR
  stage_undefined, // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_010[11] = {
  1, // D0
  1, // D1
  1, // D2
  1, // MS0
  1, // MS1
  1, // MS2
  0, // BR
  0, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_010[2] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_017((uint)stage_S4, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_005,
   (enum machPipelineStages *) pipeline_res_stages_008,
  (uint *) pipeline_res_cycles_010,
  Pipeline_Use(0x3f, 0x0, 2, (Pipeline_Use_Element *)&pipeline_res_mask_010[0]));

// Pipeline Class "pipe_cmov_reg_long"
static const uint pipeline_res_cycles_011[11] = {
  2, // D0
  2, // D1
  2, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  0, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_011[1] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000002)) 
};

static const Pipeline pipeline_class_018((uint)stage_S4, 3, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_005,
   (enum machPipelineStages *) pipeline_res_stages_007,
  (uint *) pipeline_res_cycles_011,
  Pipeline_Use(0x7, 0x0, 1, (Pipeline_Use_Element *)&pipeline_res_mask_011[0]));

// Pipeline Class "fpu_reg"
static const enum machPipelineStages pipeline_res_stages_009[11] = {
  stage_S0,        // D0
  stage_S0,        // D1
  stage_S0,        // D2
  stage_undefined, // MS0
  stage_undefined, // MS1
  stage_undefined, // MS2
  stage_undefined, // BR
  stage_S3,        // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_012[11] = {
  2, // D0
  2, // D1
  2, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  1, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_012[2] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000002)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_019((uint)stage_undefined, 1, false, 0, 2, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_009,
  (uint *) pipeline_res_cycles_012,
  Pipeline_Use(0x87, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_012[0]));

// Pipeline Class "fpu_reg_reg"
static const Pipeline pipeline_class_020((uint)stage_S4, 1, false, 0, 2, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_009,
  (uint *) pipeline_res_cycles_012,
  Pipeline_Use(0x87, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_012[0]));

// Pipeline Class "fpu_reg_reg_reg"
static const uint pipeline_res_cycles_013[11] = {
  3, // D0
  3, // D1
  3, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  2, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_013[2] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000004)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x0000000c)) 
};

static const Pipeline pipeline_class_021((uint)stage_S4, 2, false, 0, 3, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_003,
   (enum machPipelineStages *) pipeline_res_stages_009,
  (uint *) pipeline_res_cycles_013,
  Pipeline_Use(0x87, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_013[0]));

// Pipeline Class "fpu_reg_reg_reg_reg"
static const enum machPipelineStages pipeline_reads_006[3] = {
  stage_S3,
  stage_S3,
  stage_S3 
};

static const uint pipeline_res_cycles_014[11] = {
  4, // D0
  4, // D1
  4, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  2, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_014[2] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000008)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x0000000c)) 
};

static const Pipeline pipeline_class_022((uint)stage_S4, 3, false, 0, 4, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_006,
   (enum machPipelineStages *) pipeline_res_stages_009,
  (uint *) pipeline_res_cycles_014,
  Pipeline_Use(0x87, 0x80, 2, (Pipeline_Use_Element *)&pipeline_res_mask_014[0]));

// Pipeline Class "fpu_reg_mem_reg_reg"
static const enum machPipelineStages pipeline_res_stages_010[11] = {
  stage_S1,        // D0
  stage_S1,        // D1
  stage_S1,        // D2
  stage_S3,        // MS0
  stage_S3,        // MS1
  stage_S3,        // MS2
  stage_undefined, // BR
  stage_S3,        // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_015[11] = {
  3, // D0
  3, // D1
  3, // D2
  1, // MS0
  1, // MS1
  1, // MS2
  0, // BR
  2, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_015[4] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x00000007)),
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x0000000c)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_023((uint)stage_S4, 3, false, 0, 4, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_006,
   (enum machPipelineStages *) pipeline_res_stages_010,
  (uint *) pipeline_res_cycles_015,
  Pipeline_Use(0xbf, 0x81, 4, (Pipeline_Use_Element *)&pipeline_res_mask_015[0]));

// Pipeline Class "fpu_reg_mem"
static const enum machPipelineStages pipeline_res_stages_011[11] = {
  stage_S1,        // D0
  stage_S1,        // D1
  stage_S1,        // D2
  stage_S3,        // MS0
  stage_S3,        // MS1
  stage_S3,        // MS2
  stage_undefined, // BR
  stage_S4,        // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_016[11] = {
  1, // D0
  1, // D1
  1, // D2
  1, // MS0
  1, // MS1
  1, // MS2
  0, // BR
  1, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_016[4] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x00000001)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000008)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_024((uint)stage_S5, 1, false, 0, 2, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_011,
  (uint *) pipeline_res_cycles_016,
  Pipeline_Use(0xbf, 0x81, 4, (Pipeline_Use_Element *)&pipeline_res_mask_016[0]));

// Pipeline Class "fpu_reg_reg_mem"
static const uint pipeline_res_cycles_017[11] = {
  2, // D0
  2, // D1
  2, // D2
  1, // MS0
  1, // MS1
  1, // MS2
  0, // BR
  1, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_017[4] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x00000003)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000008)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_025((uint)stage_S5, 2, false, 0, 3, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_003,
   (enum machPipelineStages *) pipeline_res_stages_011,
  (uint *) pipeline_res_cycles_017,
  Pipeline_Use(0xbf, 0x81, 4, (Pipeline_Use_Element *)&pipeline_res_mask_017[0]));

// Pipeline Class "fpu_mem_reg"
static const enum machPipelineStages pipeline_res_stages_012[11] = {
  stage_S1,        // D0
  stage_S0,        // D1
  stage_S0,        // D2
  stage_S3,        // MS0
  stage_S3,        // MS1
  stage_S3,        // MS2
  stage_undefined, // BR
  stage_S4,        // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_018[4] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x00000001)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000008)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_026((uint)stage_undefined, 2, false, 0, 2, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_002,
   (enum machPipelineStages *) pipeline_res_stages_012,
  (uint *) pipeline_res_cycles_016,
  Pipeline_Use(0xbf, 0x81, 4, (Pipeline_Use_Element *)&pipeline_res_mask_018[0]));

// Pipeline Class "fpu_mem_reg_reg"
static const Pipeline_Use_Element pipeline_res_mask_019[4] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000002)),
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x00000001)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000008)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_027((uint)stage_undefined, 3, false, 0, 3, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_006,
   (enum machPipelineStages *) pipeline_res_stages_012,
  (uint *) pipeline_res_cycles_017,
  Pipeline_Use(0xbf, 0x81, 4, (Pipeline_Use_Element *)&pipeline_res_mask_019[0]));

// Pipeline Class "fpu_mem_reg_mem"
static const enum machPipelineStages pipeline_reads_007[3] = {
  stage_S4,
  stage_S3,
  stage_S3 
};

static const enum machPipelineStages pipeline_res_stages_013[11] = {
  stage_S0,        // D0
  stage_S0,        // D1
  stage_S0,        // D2
  stage_S3,        // MS0
  stage_S3,        // MS1
  stage_S3,        // MS2
  stage_undefined, // BR
  stage_S4,        // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_018[11] = {
  2, // D0
  1, // D1
  1, // D2
  2, // MS0
  2, // MS1
  2, // MS2
  0, // BR
  1, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_020[4] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000001)),
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000002)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000008)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x0000000c)) 
};

static const Pipeline pipeline_class_028((uint)stage_undefined, 3, false, 0, 3, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_007,
   (enum machPipelineStages *) pipeline_res_stages_013,
  (uint *) pipeline_res_cycles_018,
  Pipeline_Use(0xbf, 0x81, 4, (Pipeline_Use_Element *)&pipeline_res_mask_020[0]));

// Pipeline Class "fpu_mem_mem"
static const enum machPipelineStages pipeline_reads_008[2] = {
  stage_S4,
  stage_S3 
};

static const uint pipeline_res_cycles_019[11] = {
  2, // D0
  0, // D1
  0, // D2
  2, // MS0
  2, // MS1
  2, // MS2
  0, // BR
  0, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_021[2] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000002)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x0000000c)) 
};

static const Pipeline pipeline_class_029((uint)stage_undefined, 2, false, 0, 2, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_008,
   (enum machPipelineStages *) pipeline_res_stages_004,
  (uint *) pipeline_res_cycles_019,
  Pipeline_Use(0x39, 0x1, 2, (Pipeline_Use_Element *)&pipeline_res_mask_021[0]));

// Pipeline Class "fpu_mem_mem_mem"
static const enum machPipelineStages pipeline_res_stages_014[11] = {
  stage_S0,        // D0
  stage_undefined, // D1
  stage_undefined, // D2
  stage_S3,        // MS0
  stage_S3,        // MS1
  stage_S3,        // MS2
  stage_undefined, // BR
  stage_S4,        // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_020[11] = {
  3, // D0
  0, // D1
  0, // D2
  3, // MS0
  3, // MS1
  3, // MS2
  0, // BR
  1, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_022[3] = {
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x80000004)),
  Pipeline_Use_Element(0x080, 7, 7, false, Pipeline_Use_Cycle_Mask(0x00000008)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x0000001c)) 
};

static const Pipeline pipeline_class_030((uint)stage_undefined, 3, false, 0, 3, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_007,
   (enum machPipelineStages *) pipeline_res_stages_014,
  (uint *) pipeline_res_cycles_020,
  Pipeline_Use(0xb9, 0x81, 3, (Pipeline_Use_Element *)&pipeline_res_mask_022[0]));

// Pipeline Class "fpu_mem_reg_con"
static const enum machPipelineStages pipeline_reads_009[2] = {
  stage_S4,
  stage_S4 
};

static const Pipeline pipeline_class_031((uint)stage_undefined, 2, false, 0, 3, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_009,
   (enum machPipelineStages *) pipeline_res_stages_013,
  (uint *) pipeline_res_cycles_018,
  Pipeline_Use(0xbf, 0x81, 4, (Pipeline_Use_Element *)&pipeline_res_mask_020[0]));

// Pipeline Class "fpu_reg_con"
static const Pipeline pipeline_class_032((uint)stage_S5, 0, false, 0, 2, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_011,
  (uint *) pipeline_res_cycles_016,
  Pipeline_Use(0xbf, 0x81, 4, (Pipeline_Use_Element *)&pipeline_res_mask_016[0]));

// Pipeline Class "fpu_reg_reg_con"
static const Pipeline pipeline_class_033((uint)stage_S5, 1, false, 0, 3, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_011,
  (uint *) pipeline_res_cycles_017,
  Pipeline_Use(0xbf, 0x81, 4, (Pipeline_Use_Element *)&pipeline_res_mask_017[0]));

// Pipeline Class "pipe_jmp"
static const enum machPipelineStages pipeline_res_stages_015[11] = {
  stage_undefined, // D0
  stage_undefined, // D1
  stage_undefined, // D2
  stage_undefined, // MS0
  stage_undefined, // MS1
  stage_undefined, // MS2
  stage_S3,        // BR
  stage_undefined, // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_021[11] = {
  0, // D0
  0, // D1
  0, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  1, // BR
  0, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_023[1] = {
  Pipeline_Use_Element(0x040, 6, 6, false, Pipeline_Use_Cycle_Mask(0x00000004)) 
};

static const Pipeline pipeline_class_034((uint)stage_undefined, 0, false, 0, 1, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_015,
  (uint *) pipeline_res_cycles_021,
  Pipeline_Use(0x40, 0x40, 1, (Pipeline_Use_Element *)&pipeline_res_mask_023[0]));

// Pipeline Class "pipe_jcc"
static const enum machPipelineStages pipeline_reads_010[2] = {
  stage_S1,
  stage_undefined 
};

static const Pipeline pipeline_class_035((uint)stage_undefined, 2, false, 0, 1, false, false, false, false,

  (enum machPipelineStages *) pipeline_reads_010,
   (enum machPipelineStages *) pipeline_res_stages_015,
  (uint *) pipeline_res_cycles_021,
  Pipeline_Use(0x40, 0x40, 1, (Pipeline_Use_Element *)&pipeline_res_mask_023[0]));

// Pipeline Class "pipe_cmpxchg"
static const enum machPipelineStages pipeline_res_stages_016[11] = {
  stage_S2,        // D0
  stage_S0,        // D1
  stage_S0,        // D2
  stage_S3,        // MS0
  stage_S3,        // MS1
  stage_S3,        // MS2
  stage_S5,        // BR
  stage_undefined, // FPU
  stage_S3,        // ALU0
  stage_S3,        // ALU1
  stage_S3         // ALU2
};

static const uint pipeline_res_cycles_022[11] = {
  3, // D0
  3, // D1
  3, // D2
  1, // MS0
  1, // MS1
  1, // MS2
  1, // BR
  0, // FPU
  2, // ALU0
  2, // ALU1
  2  // ALU2
};

static const Pipeline_Use_Element pipeline_res_mask_024[5] = {
  Pipeline_Use_Element(0x007, 0, 2, true,  Pipeline_Use_Cycle_Mask(0x80000004)),
  Pipeline_Use_Element(0x001, 0, 0, false, Pipeline_Use_Cycle_Mask(0x00000002)),
  Pipeline_Use_Element(0x038, 3, 5, true,  Pipeline_Use_Cycle_Mask(0x00000004)),
  Pipeline_Use_Element(0x700, 8, 10, true,  Pipeline_Use_Cycle_Mask(0x0000000c)),
  Pipeline_Use_Element(0x040, 6, 6, false, Pipeline_Use_Cycle_Mask(0x00000010)) 
};

static const Pipeline pipeline_class_036((uint)stage_S5, 1, true, 6, 1, false, false, true, false,

  (enum machPipelineStages *) pipeline_reads_001,
   (enum machPipelineStages *) pipeline_res_stages_016,
  (uint *) pipeline_res_cycles_022,
  Pipeline_Use(0x77f, 0x41, 5, (Pipeline_Use_Element *)&pipeline_res_mask_024[0]));

// Pipeline Class "pipe_slow"
static const Pipeline pipeline_class_037((uint)stage_undefined, 0, true, 100, 10, false, true, true, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_004,
  (uint *) pipeline_res_cycles_019,
  Pipeline_Use(0x39, 0x1, 2, (Pipeline_Use_Element *)&pipeline_res_mask_021[0]));

// Pipeline Class "empty"
static const enum machPipelineStages pipeline_res_stages_017[11] = {
  stage_undefined, // D0
  stage_undefined, // D1
  stage_undefined, // D2
  stage_undefined, // MS0
  stage_undefined, // MS1
  stage_undefined, // MS2
  stage_undefined, // BR
  stage_undefined, // FPU
  stage_undefined, // ALU0
  stage_undefined, // ALU1
  stage_undefined  // ALU2
};

static const uint pipeline_res_cycles_023[11] = {
  0, // D0
  0, // D1
  0, // D2
  0, // MS0
  0, // MS1
  0, // MS2
  0, // BR
  0, // FPU
  0, // ALU0
  0, // ALU1
  0  // ALU2
};

static const Pipeline pipeline_class_038((uint)stage_undefined, 0, false, 0, 0, false, false, false, false,
 nullptr,  (enum machPipelineStages *) pipeline_res_stages_017,
  (uint *) pipeline_res_cycles_023,
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

  static const char *resource_names[11] = { "D0", "D1", "D2", "MS0", "MS1", "MS2", "BR", "FPU", "ALU0", "ALU1", "ALU2" };

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
    for (uint i = 0; i < 11; i++)
      if ((r & (1 << i)) != 0)
        st->print(" %s", resource_names[i]);
    needs_comma = true;
  };
  st->print("\n");
}
#endif
const Pipeline *                                                   Node::pipeline_class() { return (&pipeline_class_Zero_Instructions); }
const Pipeline *                                                   Node::pipeline() const { return (&pipeline_class_Zero_Instructions); }

const Pipeline *                                               MachNode::pipeline_class() { return (&pipeline_class_Unknown_Instructions); }
const Pipeline *                                               MachNode::pipeline() const { return pipeline_class(); }

const Pipeline * MachNopNode::pipeline() const { return (&pipeline_class_038); }


const Pipeline *                                               MoveF2VLNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                               MoveF2VLNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                              MoveF2LEGNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                              MoveF2LEGNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                               MoveVL2FNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                               MoveVL2FNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                              MoveLEG2FNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                              MoveLEG2FNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                               MoveD2VLNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                               MoveD2VLNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                              MoveD2LEGNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                              MoveD2LEGNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                               MoveVL2DNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                               MoveVL2DNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                              MoveLEG2DNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                              MoveLEG2DNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                                  loadBNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                  loadBNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                loadB2LNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                loadB2LNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                 loadUBNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                 loadUBNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                               loadUB2LNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                               loadUB2LNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          loadUB2L_immINode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          loadUB2L_immINode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                  loadSNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                  loadSNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                loadS2BNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                loadS2BNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                loadS2LNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                loadS2LNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                 loadUSNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                 loadUSNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                               loadUS2BNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                               loadUS2BNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                               loadUS2LNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                               loadUS2LNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                      loadUS2L_immI_255Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                      loadUS2L_immI_255Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          loadUS2L_immINode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          loadUS2L_immINode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                  loadINode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                  loadINode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                loadI2BNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                loadI2BNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                               loadI2UBNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                               loadI2UBNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                loadI2SNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                loadI2SNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                               loadI2USNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                               loadI2USNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                loadI2LNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                loadI2LNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                       loadI2L_immI_255Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                       loadI2L_immI_255Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                     loadI2L_immI_65535Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                     loadI2L_immI_65535Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                         loadI2L_immU31Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                         loadI2L_immU31Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                               loadUI2LNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                               loadUI2LNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                  loadLNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                  loadLNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                              loadRangeNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                              loadRangeNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                  loadPNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                  loadPNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                  loadNNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                  loadNNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                              loadKlassNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                              loadKlassNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                             loadNKlassNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                             loadNKlassNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                               loadNKlassCompactHeadersNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                               loadNKlassCompactHeadersNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                  loadFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  loadFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          loadD_partialNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          loadD_partialNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  loadDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  loadDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               maxF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               maxF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     maxF_reduction_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     maxF_reduction_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               maxD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               maxD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     maxD_reduction_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     maxD_reduction_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               minF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               minF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     minF_reduction_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     minF_reduction_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               minD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               minD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     minD_reduction_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     minD_reduction_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  leaP8Node::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                                  leaP8Node::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                                 leaP32Node::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                                 leaP32Node::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                             leaPIdxOffNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                             leaPIdxOffNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                           leaPIdxScaleNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                           leaPIdxScaleNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                        leaPPosIdxScaleNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                        leaPPosIdxScaleNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                        leaPIdxScaleOffNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                        leaPIdxScaleOffNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                          leaPPosIdxOffNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                          leaPPosIdxOffNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     leaPPosIdxScaleOffNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     leaPPosIdxScaleOffNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                leaPCompressedOopOffsetNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                leaPCompressedOopOffsetNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                            leaP8NarrowNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                            leaP8NarrowNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                           leaP32NarrowNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                           leaP32NarrowNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                       leaPIdxOffNarrowNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                       leaPIdxOffNarrowNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                     leaPIdxScaleNarrowNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                     leaPIdxScaleNarrowNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                  leaPIdxScaleOffNarrowNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                  leaPIdxScaleOffNarrowNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                    leaPPosIdxOffNarrowNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                                    leaPPosIdxOffNarrowNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                               leaPPosIdxScaleOffNarrowNode::pipeline_class() { return (&pipeline_class_005); }
const Pipeline *                               leaPPosIdxScaleOffNarrowNode::pipeline() const { return (&pipeline_class_005); }

const Pipeline *                                               loadConINode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                                               loadConINode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                                              loadConI0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              loadConI0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               loadConLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                               loadConLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                              loadConL0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              loadConL0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                            loadConUL32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                            loadConUL32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                             loadConL32Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                             loadConL32Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               loadConPNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                                               loadConPNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                                              loadConP0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              loadConP0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                             loadConP31Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                             loadConP31Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               loadConFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               loadConFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               loadConHNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               loadConHNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              loadConN0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              loadConN0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               loadConNNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                                               loadConNNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                                          loadConNKlassNode::pipeline_class() { return (&pipeline_class_003); }
const Pipeline *                                          loadConNKlassNode::pipeline() const { return (&pipeline_class_003); }

const Pipeline *                                              loadConF0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              loadConF0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               loadConDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               loadConDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              loadConD0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              loadConD0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                loadSSINode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                loadSSINode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                loadSSLNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                loadSSLNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                loadSSPNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                loadSSPNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                loadSSFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                loadSSFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                loadSSDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                loadSSDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          prefetchAllocNode::pipeline_class() { return (&pipeline_class_007); }
const Pipeline *                                          prefetchAllocNode::pipeline() const { return (&pipeline_class_007); }

const Pipeline *                                       prefetchAllocNTANode::pipeline_class() { return (&pipeline_class_007); }
const Pipeline *                                       prefetchAllocNTANode::pipeline() const { return (&pipeline_class_007); }

const Pipeline *                                        prefetchAllocT0Node::pipeline_class() { return (&pipeline_class_007); }
const Pipeline *                                        prefetchAllocT0Node::pipeline() const { return (&pipeline_class_007); }

const Pipeline *                                        prefetchAllocT2Node::pipeline_class() { return (&pipeline_class_007); }
const Pipeline *                                        prefetchAllocT2Node::pipeline() const { return (&pipeline_class_007); }

const Pipeline *                                                 storeBNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                                 storeBNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                                 storeCNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                                 storeCNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                                 storeINode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                                 storeINode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                                 storeLNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                                 storeLNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                                 storePNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                                 storePNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                             storeImmP0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                             storeImmP0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                              storeImmPNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                              storeImmPNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                                 storeNNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                                 storeNNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                            storeNKlassNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                            storeNKlassNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                             storeImmN0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                             storeImmN0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                              storeImmNNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                              storeImmNNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                         storeImmNKlassNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                         storeImmNKlassNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                             storeImmI0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                             storeImmI0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                              storeImmINode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                              storeImmINode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                             storeImmL0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                             storeImmL0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                              storeImmLNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                              storeImmLNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                             storeImmC0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                             storeImmC0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                            storeImmI16Node::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                            storeImmI16Node::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                             storeImmB0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                             storeImmB0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                              storeImmBNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                              storeImmBNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                                 storeFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                 storeFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                storeF0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                                storeF0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                             storeF_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                             storeF_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                                 storeDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                 storeDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            storeD0_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                            storeD0_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                                storeD0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                                storeD0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                               storeSSINode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                               storeSSINode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                               storeSSLNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                               storeSSLNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                               storeSSPNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                               storeSSPNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                               storeSSFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               storeSSFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               storeSSDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               storeSSDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                cacheWBNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                cacheWBNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         cacheWBPreSyncNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         cacheWBPreSyncNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        cacheWBPostSyncNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        cacheWBPostSyncNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      bytes_reverse_intNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      bytes_reverse_intNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     bytes_reverse_longNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     bytes_reverse_longNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                           bytes_reverse_unsigned_shortNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                           bytes_reverse_unsigned_shortNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                    bytes_reverse_shortNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    bytes_reverse_shortNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     countLeadingZerosINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     countLeadingZerosINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 countLeadingZerosI_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                 countLeadingZerosI_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                 countLeadingZerosI_bsrNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 countLeadingZerosI_bsrNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     countLeadingZerosLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     countLeadingZerosLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 countLeadingZerosL_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                 countLeadingZerosL_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                 countLeadingZerosL_bsrNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 countLeadingZerosL_bsrNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                    countTrailingZerosINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    countTrailingZerosINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                countTrailingZerosI_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                countTrailingZerosI_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                countTrailingZerosI_bsfNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                countTrailingZerosI_bsfNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                    countTrailingZerosLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    countTrailingZerosLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                countTrailingZerosL_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                countTrailingZerosL_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                countTrailingZerosL_bsfNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                countTrailingZerosL_bsfNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   bytes_reversebit_intNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   bytes_reversebit_intNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                              bytes_reversebit_int_gfniNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                              bytes_reversebit_int_gfniNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                  bytes_reversebit_longNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                  bytes_reversebit_longNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                             bytes_reversebit_long_gfniNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                             bytes_reversebit_long_gfniNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                              popCountINode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              popCountINode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          popCountI_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          popCountI_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                              popCountLNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              popCountLNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          popCountL_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          popCountL_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                         membar_acquireNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                         membar_acquireNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                       membar_acquire_0Node::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                       membar_acquire_0Node::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                    membar_acquire_lockNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                    membar_acquire_lockNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                         membar_releaseNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                         membar_releaseNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                       membar_release_0Node::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                       membar_release_0Node::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                    membar_release_lockNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                    membar_release_lockNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                        membar_volatileNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        membar_volatileNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            unnecessary_membar_volatileNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                            unnecessary_membar_volatileNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                      membar_storestoreNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                      membar_storestoreNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                    membar_storestore_0Node::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                    membar_storestore_0Node::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                                castX2PNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                                castX2PNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                                castP2XNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                                castP2XNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                                convP2INode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                                convP2INode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                                convN2INode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                                convN2INode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          encodeHeapOopNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                                          encodeHeapOopNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                                 encodeHeapOop_not_nullNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                                 encodeHeapOop_not_nullNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                                          decodeHeapOopNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                                          decodeHeapOopNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                                 decodeHeapOop_not_nullNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                                 decodeHeapOop_not_nullNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                                   encodeKlass_not_nullNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                                   encodeKlass_not_nullNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                                   decodeKlass_not_nullNode::pipeline_class() { return (&pipeline_class_002); }
const Pipeline *                                   decodeKlass_not_nullNode::pipeline() const { return (&pipeline_class_002); }

const Pipeline *                                        jumpXtnd_offsetNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                                        jumpXtnd_offsetNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                                          jumpXtnd_addrNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                                          jumpXtnd_addrNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                                               jumpXtndNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                                               jumpXtndNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                                           cmovI_imm_01Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                           cmovI_imm_01Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                              cmovI_regNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                              cmovI_regNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                          cmovI_imm_01UNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          cmovI_imm_01UNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                             cmovI_regUNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                             cmovI_regUNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                        cmovI_imm_01UCFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                        cmovI_imm_01UCFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                       cmovI_regUCF2_neNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                       cmovI_regUCF2_neNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                       cmovI_regUCF2_eqNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                       cmovI_regUCF2_eqNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                              cmovI_memNode::pipeline_class() { return (&pipeline_class_017); }
const Pipeline *                                              cmovI_memNode::pipeline() const { return (&pipeline_class_017); }

const Pipeline *                                             cmovI_memUNode::pipeline_class() { return (&pipeline_class_017); }
const Pipeline *                                             cmovI_memUNode::pipeline() const { return (&pipeline_class_017); }

const Pipeline *                                              cmovN_regNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                              cmovN_regNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                             cmovN_regUNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                             cmovN_regUNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                       cmovN_regUCF2_neNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                       cmovN_regUCF2_neNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                       cmovN_regUCF2_eqNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                       cmovN_regUCF2_eqNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                              cmovP_regNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                              cmovP_regNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                             cmovP_regUNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                             cmovP_regUNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                       cmovP_regUCF2_neNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                       cmovP_regUCF2_neNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                       cmovP_regUCF2_eqNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                       cmovP_regUCF2_eqNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                           cmovL_imm_01Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                           cmovL_imm_01Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                              cmovL_regNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                              cmovL_regNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                              cmovL_memNode::pipeline_class() { return (&pipeline_class_017); }
const Pipeline *                                              cmovL_memNode::pipeline() const { return (&pipeline_class_017); }

const Pipeline *                                          cmovL_imm_01UNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          cmovL_imm_01UNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                             cmovL_regUNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                             cmovL_regUNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                        cmovL_imm_01UCFNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                        cmovL_imm_01UCFNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                       cmovL_regUCF2_neNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                       cmovL_regUCF2_neNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                       cmovL_regUCF2_eqNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                       cmovL_regUCF2_eqNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                             cmovL_memUNode::pipeline_class() { return (&pipeline_class_017); }
const Pipeline *                                             cmovL_memUNode::pipeline() const { return (&pipeline_class_017); }

const Pipeline *                                              cmovF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              cmovF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             cmovF_regUNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             cmovF_regUNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              cmovD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              cmovD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             cmovD_regUNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             cmovD_regUNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              addI_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              addI_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          addI_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          addI_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          addI_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          addI_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                        addI_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                        addI_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          addI_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                          addI_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                        addI_mem_rReg_0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                        addI_mem_rReg_0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                           addI_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           addI_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                              incI_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              incI_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               incI_memNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                               incI_memNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                              decI_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              decI_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               decI_memNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                               decI_memNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                   leaI_rReg_immI2_immINode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                   leaI_rReg_immI2_immINode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                    leaI_rReg_rReg_immINode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                    leaI_rReg_rReg_immINode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                   leaI_rReg_rReg_immI2Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                   leaI_rReg_rReg_immI2Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                 leaI_rReg_rReg_immI2_0Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                 leaI_rReg_rReg_immI2_0Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                              leaI_rReg_rReg_immI2_immINode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                              leaI_rReg_rReg_immI2_immINode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                            leaI_rReg_rReg_immI2_immI_0Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                            leaI_rReg_rReg_immI2_immI_0Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                              addL_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              addL_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          addL_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          addL_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          addL_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          addL_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                        addL_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                        addL_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          addL_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                          addL_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                        addL_mem_rReg_0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                        addL_mem_rReg_0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                           addL_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           addL_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                              incL_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              incL_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               incL_memNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                               incL_memNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                              decL_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              decL_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               decL_memNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                               decL_memNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                 leaL_rReg_immI2_immL32Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                 leaL_rReg_immI2_immL32Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                  leaL_rReg_rReg_immL32Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                  leaL_rReg_rReg_immL32Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                   leaL_rReg_rReg_immI2Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                   leaL_rReg_rReg_immI2Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                 leaL_rReg_rReg_immI2_0Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                 leaL_rReg_rReg_immI2_0Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                            leaL_rReg_rReg_immI2_immL32Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                            leaL_rReg_rReg_immI2_immL32Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                          leaL_rReg_rReg_immI2_immL32_0Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                          leaL_rReg_rReg_immI2_immL32_0Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                              addP_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              addP_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          addP_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          addP_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                            checkCastPPNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                            checkCastPPNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                                 castPPNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                                 castPPNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                                 castIINode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                                 castIINode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                                 castLLNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                                 castLLNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                                 castFFNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                                 castFFNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                                 castHHNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                                 castHHNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                                 castDDNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                                 castDDNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                        compareAndSwapPNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                        compareAndSwapPNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                      compareAndSwapP_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                      compareAndSwapP_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                        compareAndSwapLNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                        compareAndSwapLNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                      compareAndSwapL_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                      compareAndSwapL_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                        compareAndSwapINode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                        compareAndSwapINode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                      compareAndSwapI_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                      compareAndSwapI_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                        compareAndSwapBNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                        compareAndSwapBNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                      compareAndSwapB_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                      compareAndSwapB_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                        compareAndSwapSNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                        compareAndSwapSNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                      compareAndSwapS_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                      compareAndSwapS_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                        compareAndSwapNNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                        compareAndSwapNNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                      compareAndSwapN_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                      compareAndSwapN_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                    compareAndExchangeBNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                    compareAndExchangeBNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                    compareAndExchangeSNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                    compareAndExchangeSNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                    compareAndExchangeINode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                    compareAndExchangeINode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                    compareAndExchangeLNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                    compareAndExchangeLNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                    compareAndExchangeNNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                    compareAndExchangeNNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                    compareAndExchangePNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                    compareAndExchangePNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                       xaddB_reg_no_resNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                       xaddB_reg_no_resNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                       xaddB_imm_no_resNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                       xaddB_imm_no_resNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                  xaddBNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                  xaddBNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                       xaddS_reg_no_resNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                       xaddS_reg_no_resNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                       xaddS_imm_no_resNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                       xaddS_imm_no_resNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                  xaddSNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                  xaddSNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                       xaddI_reg_no_resNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                       xaddI_reg_no_resNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                       xaddI_imm_no_resNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                       xaddI_imm_no_resNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                  xaddINode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                  xaddINode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                       xaddL_reg_no_resNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                       xaddL_reg_no_resNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                       xaddL_imm_no_resNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                       xaddL_imm_no_resNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                  xaddLNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                  xaddLNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                  xchgBNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                  xchgBNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                  xchgSNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                  xchgSNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                  xchgINode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                  xchgINode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                  xchgLNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                  xchgLNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                  xchgPNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                  xchgPNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                  xchgNNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                  xchgNNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                              absI_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              absI_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                              absL_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              absL_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                              subI_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              subI_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          subI_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          subI_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          subI_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                          subI_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                              subL_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              subL_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          subL_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          subL_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          subL_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                          subL_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                              subP_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              subP_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                              negI_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              negI_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                            negI_rReg_2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                            negI_rReg_2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               negI_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                               negI_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                              negL_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                              negL_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                            negL_rReg_2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                            negL_rReg_2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               negL_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                               negL_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                              mulI_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                              mulI_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                          mulI_rReg_immNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                          mulI_rReg_immNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                               mulI_memNode::pipeline_class() { return (&pipeline_class_011); }
const Pipeline *                                               mulI_memNode::pipeline() const { return (&pipeline_class_011); }

const Pipeline *                                             mulI_mem_0Node::pipeline_class() { return (&pipeline_class_011); }
const Pipeline *                                             mulI_mem_0Node::pipeline() const { return (&pipeline_class_011); }

const Pipeline *                                           mulI_mem_immNode::pipeline_class() { return (&pipeline_class_011); }
const Pipeline *                                           mulI_mem_immNode::pipeline() const { return (&pipeline_class_011); }

const Pipeline *                                              mulL_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                              mulL_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                          mulL_rReg_immNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                          mulL_rReg_immNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                               mulL_memNode::pipeline_class() { return (&pipeline_class_011); }
const Pipeline *                                               mulL_memNode::pipeline() const { return (&pipeline_class_011); }

const Pipeline *                                             mulL_mem_0Node::pipeline_class() { return (&pipeline_class_011); }
const Pipeline *                                             mulL_mem_0Node::pipeline() const { return (&pipeline_class_011); }

const Pipeline *                                           mulL_mem_immNode::pipeline_class() { return (&pipeline_class_011); }
const Pipeline *                                           mulL_mem_immNode::pipeline() const { return (&pipeline_class_011); }

const Pipeline *                                            mulHiL_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                            mulHiL_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                           umulHiL_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                           umulHiL_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                              divI_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                              divI_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                              divL_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                              divL_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                             udivI_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                             udivI_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                             udivL_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                             udivL_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                    divModI_rReg_divmodNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    divModI_rReg_divmodNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    divModL_rReg_divmodNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    divModL_rReg_divmodNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   udivModI_rReg_divmodNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   udivModI_rReg_divmodNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   udivModL_rReg_divmodNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   udivModL_rReg_divmodNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              modI_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                              modI_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                              modL_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                              modL_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                             umodI_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                             umodI_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                             umodL_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                             umodL_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                        salI_rReg_immI2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                        salI_rReg_immI2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          salI_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          salI_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                           salI_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           salI_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                           salI_rReg_CLNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                           salI_rReg_CLNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                            salI_mem_CLNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                            salI_mem_CLNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                         salI_rReg_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                         salI_rReg_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          salI_mem_rRegNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          salI_mem_rRegNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          sarI_rReg_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                          sarI_rReg_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                           sarI_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           sarI_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                           sarI_rReg_CLNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                           sarI_rReg_CLNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                            sarI_mem_CLNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                            sarI_mem_CLNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                         sarI_rReg_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                         sarI_rReg_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          sarI_mem_rRegNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          sarI_mem_rRegNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          shrI_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          shrI_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                           shrI_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           shrI_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                           shrI_rReg_CLNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                           shrI_rReg_CLNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                            shrI_mem_CLNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                            shrI_mem_CLNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                         shrI_rReg_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                         shrI_rReg_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          shrI_mem_rRegNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          shrI_mem_rRegNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                        salL_rReg_immI2Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                        salL_rReg_immI2Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          salL_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          salL_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                           salL_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           salL_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                           salL_rReg_CLNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                           salL_rReg_CLNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                            salL_mem_CLNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                            salL_mem_CLNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                         salL_rReg_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                         salL_rReg_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          salL_mem_rRegNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          salL_mem_rRegNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          sarL_rReg_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                          sarL_rReg_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                           sarL_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           sarL_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                           sarL_rReg_CLNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                           sarL_rReg_CLNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                            sarL_mem_CLNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                            sarL_mem_CLNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                         sarL_rReg_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                         sarL_rReg_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          sarL_mem_rRegNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          sarL_mem_rRegNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          shrL_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          shrL_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                           shrL_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           shrL_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                           shrL_rReg_CLNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                           shrL_rReg_CLNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                            shrL_mem_CLNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                            shrL_mem_CLNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                         shrL_rReg_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                         shrL_rReg_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          shrL_mem_rRegNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          shrL_mem_rRegNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                    i2bNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                                    i2bNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                                    i2sNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                                    i2sNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      rolI_immI8_legacyNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      rolI_immI8_legacyNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                             rolI_immI8Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                             rolI_immI8Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                         rolI_mem_immI8Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                         rolI_mem_immI8Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          rolI_rReg_VarNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                          rolI_rReg_VarNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      rorI_immI8_legacyNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      rorI_immI8_legacyNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                             rorI_immI8Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                             rorI_immI8Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                         rorI_mem_immI8Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                         rorI_mem_immI8Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          rorI_rReg_VarNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                          rorI_rReg_VarNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      rolL_immI8_legacyNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      rolL_immI8_legacyNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                             rolL_immI8Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                             rolL_immI8Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                         rolL_mem_immI8Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                         rolL_mem_immI8Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          rolL_rReg_VarNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                          rolL_rReg_VarNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      rorL_immI8_legacyNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      rorL_immI8_legacyNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                             rorL_immI8Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                             rorL_immI8Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                         rorL_mem_immI8Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                         rorL_mem_immI8Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          rorL_rReg_VarNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                          rorL_rReg_VarNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      compressBitsL_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      compressBitsL_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        expandBitsL_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        expandBitsL_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      compressBitsL_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      compressBitsL_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        expandBitsL_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        expandBitsL_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              andI_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              andI_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                       andI_rReg_imm255Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                       andI_rReg_imm255Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     andI2L_rReg_imm255Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     andI2L_rReg_imm255Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     andI_rReg_imm65535Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     andI_rReg_imm65535Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                   andI2L_rReg_imm65535Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   andI2L_rReg_imm65535Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                            convI2LAndI_reg_immIbitmaskNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                            convI2LAndI_reg_immIbitmaskNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          andI_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          andI_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          andI_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          andI_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                        andI_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                        andI_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          andB_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                          andB_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                        andB_mem_rReg_0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                        andB_mem_rReg_0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                          andI_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                          andI_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                        andI_mem_rReg_0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                        andI_mem_rReg_0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                           andI_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           andI_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                    andnI_rReg_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                    andnI_rReg_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                  andnI_rReg_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                  andnI_rReg_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                   andnI_rReg_rReg_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                   andnI_rReg_rReg_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                 andnI_rReg_rReg_rReg_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                 andnI_rReg_rReg_rReg_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                        blsiI_rReg_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                        blsiI_rReg_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                      blsiI_rReg_rReg_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      blsiI_rReg_rReg_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                         blsiI_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                         blsiI_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                       blsiI_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                       blsiI_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                       blsmskI_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                       blsmskI_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                     blsmskI_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                     blsmskI_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                      blsmskI_rReg_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      blsmskI_rReg_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                    blsmskI_rReg_rReg_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                    blsmskI_rReg_rReg_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                        blsrI_rReg_rRegNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                        blsrI_rReg_rRegNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                      blsrI_rReg_rReg_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                      blsrI_rReg_rReg_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                         blsrI_rReg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                         blsrI_rReg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                       blsrI_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                       blsrI_rReg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               orI_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                               orI_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                           orI_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                           orI_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                           orI_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                           orI_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                         orI_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                         orI_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                           orB_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                           orB_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                         orB_mem_rReg_0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                         orB_mem_rReg_0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                           orI_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                           orI_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                         orI_mem_rReg_0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                         orI_mem_rReg_0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                            orI_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                            orI_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                              xorI_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              xorI_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          xorI_rReg_im1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          xorI_rReg_im1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          xorI_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          xorI_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          xorI_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          xorI_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                        xorI_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                        xorI_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          xorB_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                          xorB_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                        xorB_mem_rReg_0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                        xorB_mem_rReg_0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                          xorI_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                          xorI_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                        xorI_mem_rReg_0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                        xorI_mem_rReg_0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                           xorI_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           xorI_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                              andL_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              andL_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                       andL_rReg_imm255Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                       andL_rReg_imm255Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                     andL_rReg_imm65535Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                     andL_rReg_imm65535Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          andL_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          andL_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          andL_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          andL_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                        andL_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                        andL_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          andL_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                          andL_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                        andL_mem_rReg_0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                        andL_mem_rReg_0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                           andL_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           andL_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                           btrL_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           btrL_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                    andnL_rReg_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                    andnL_rReg_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                  andnL_rReg_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                  andnL_rReg_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                   andnL_rReg_rReg_rRegNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                   andnL_rReg_rReg_rRegNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                 andnL_rReg_rReg_rReg_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                 andnL_rReg_rReg_rReg_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                        blsiL_rReg_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                        blsiL_rReg_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                      blsiL_rReg_rReg_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      blsiL_rReg_rReg_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                         blsiL_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                         blsiL_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                       blsiL_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                       blsiL_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                       blsmskL_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                       blsmskL_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                      blsmskL_rReg_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      blsmskL_rReg_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                        blsrL_rReg_rRegNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                        blsrL_rReg_rRegNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                      blsrL_rReg_rReg_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                      blsrL_rReg_rReg_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                         blsrL_rReg_memNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                         blsrL_rReg_memNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                       blsrL_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                       blsrL_rReg_mem_0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                               orL_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                               orL_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                       orL_rReg_castP2XNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                       orL_rReg_castP2XNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                     orL_rReg_castP2X_0Node::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                     orL_rReg_castP2X_0Node::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                           orL_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                           orL_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                           orL_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                           orL_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                         orL_rReg_mem_0Node::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                         orL_rReg_mem_0Node::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                           orL_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                           orL_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                         orL_mem_rReg_0Node::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                         orL_mem_rReg_0Node::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                            orL_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                            orL_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                           btsL_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           btsL_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                              xorL_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                              xorL_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                          xorL_rReg_im1Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          xorL_rReg_im1Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          xorL_rReg_immNode::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                          xorL_rReg_immNode::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                          xorL_rReg_memNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                          xorL_rReg_memNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                          xorL_mem_rRegNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                          xorL_mem_rRegNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                           xorL_mem_immNode::pipeline_class() { return (&pipeline_class_009); }
const Pipeline *                                           xorL_mem_immNode::pipeline() const { return (&pipeline_class_009); }

const Pipeline *                                              cmpLTMaskNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              cmpLTMaskNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             cmpLTMask0Node::pipeline_class() { return (&pipeline_class_001); }
const Pipeline *                                             cmpLTMask0Node::pipeline() const { return (&pipeline_class_001); }

const Pipeline *                                         cadd_cmpLTMaskNode::pipeline_class() { return (&pipeline_class_015); }
const Pipeline *                                         cadd_cmpLTMaskNode::pipeline() const { return (&pipeline_class_015); }

const Pipeline *                                       cadd_cmpLTMask_1Node::pipeline_class() { return (&pipeline_class_015); }
const Pipeline *                                       cadd_cmpLTMask_1Node::pipeline() const { return (&pipeline_class_015); }

const Pipeline *                                       cadd_cmpLTMask_0Node::pipeline_class() { return (&pipeline_class_015); }
const Pipeline *                                       cadd_cmpLTMask_0Node::pipeline() const { return (&pipeline_class_015); }

const Pipeline *                                       cadd_cmpLTMask_2Node::pipeline_class() { return (&pipeline_class_015); }
const Pipeline *                                       cadd_cmpLTMask_2Node::pipeline() const { return (&pipeline_class_015); }

const Pipeline *                                          and_cmpLTMaskNode::pipeline_class() { return (&pipeline_class_015); }
const Pipeline *                                          and_cmpLTMaskNode::pipeline() const { return (&pipeline_class_015); }

const Pipeline *                                        and_cmpLTMask_0Node::pipeline_class() { return (&pipeline_class_015); }
const Pipeline *                                        and_cmpLTMask_0Node::pipeline() const { return (&pipeline_class_015); }

const Pipeline *                                            cmpF_cc_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            cmpF_cc_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         cmpF_cc_reg_CFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         cmpF_cc_reg_CFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          cmpF_cc_memCFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          cmpF_cc_memCFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          cmpF_cc_immCFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          cmpF_cc_immCFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            cmpD_cc_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            cmpD_cc_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         cmpD_cc_reg_CFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         cmpD_cc_reg_CFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          cmpD_cc_memCFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          cmpD_cc_memCFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          cmpD_cc_immCFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          cmpD_cc_immCFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               cmpF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               cmpF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               cmpF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               cmpF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               cmpF_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               cmpF_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               cmpD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               cmpD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               cmpD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               cmpD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               cmpD_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               cmpD_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convF2D_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convF2D_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convF2D_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convF2D_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convD2F_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convD2F_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convD2F_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convD2F_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convF2I_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convF2I_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convF2L_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convF2L_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convD2I_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convD2I_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convD2L_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convD2L_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       round_double_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       round_double_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        round_float_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        round_float_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convI2F_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convI2F_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convI2F_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convI2F_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convI2D_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convI2D_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convI2D_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convI2D_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           convXI2F_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           convXI2F_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           convXI2D_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           convXI2D_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convL2F_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convL2F_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convL2F_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convL2F_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convL2D_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convL2D_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convL2D_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convL2D_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convI2L_reg_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                        convI2L_reg_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                    convI2L_reg_reg_zexNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                    convI2L_reg_reg_zexNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                    convI2L_reg_mem_zexNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                    convI2L_reg_mem_zexNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                     zerox_long_reg_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                     zerox_long_reg_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                        convL2I_reg_regNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                        convL2I_reg_regNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      MoveF2I_stack_regNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                      MoveF2I_stack_regNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                      MoveI2F_stack_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      MoveI2F_stack_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      MoveD2L_stack_regNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                      MoveD2L_stack_regNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                              MoveL2D_stack_reg_partialNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                              MoveL2D_stack_reg_partialNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      MoveL2D_stack_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      MoveL2D_stack_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      MoveF2I_reg_stackNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      MoveF2I_reg_stackNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      MoveI2F_reg_stackNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                      MoveI2F_reg_stackNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                      MoveD2L_reg_stackNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      MoveD2L_reg_stackNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      MoveL2D_reg_stackNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                      MoveL2D_reg_stackNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                        MoveF2I_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        MoveF2I_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        MoveD2L_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        MoveD2L_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        MoveI2F_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        MoveI2F_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        MoveL2D_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        MoveL2D_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               rep_stosNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               rep_stosNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          rep_stos_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          rep_stos_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         rep_stos_largeNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         rep_stos_largeNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    rep_stos_large_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    rep_stos_large_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            rep_stos_imNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            rep_stos_imNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        string_compareLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        string_compareLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   string_compareL_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   string_compareL_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        string_compareUNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        string_compareUNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   string_compareU_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   string_compareU_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       string_compareLUNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       string_compareLUNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  string_compareLU_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  string_compareLU_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       string_compareULNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       string_compareULNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  string_compareUL_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  string_compareUL_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    string_indexof_conLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    string_indexof_conLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    string_indexof_conUNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    string_indexof_conUNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   string_indexof_conULNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   string_indexof_conULNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        string_indexofLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        string_indexofLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        string_indexofUNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        string_indexofUNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       string_indexofULNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       string_indexofULNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    string_indexof_charNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    string_indexof_charNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   stringL_indexof_charNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   stringL_indexof_charNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          string_equalsNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          string_equalsNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     string_equals_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     string_equals_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          array_equalsBNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          array_equalsBNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     array_equalsB_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     array_equalsB_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          array_equalsCNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          array_equalsCNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     array_equalsC_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     array_equalsC_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        arrays_hashcodeNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        arrays_hashcodeNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        count_positivesNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        count_positivesNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   count_positives_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   count_positives_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        string_compressNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        string_compressNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   string_compress_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   string_compress_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         string_inflateNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         string_inflateNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    string_inflate_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    string_inflate_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       encode_iso_arrayNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       encode_iso_arrayNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     encode_ascii_arrayNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     encode_ascii_arrayNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      overflowAddI_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                      overflowAddI_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                  overflowAddI_rReg_immNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                  overflowAddI_rReg_immNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      overflowAddL_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                      overflowAddL_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                  overflowAddL_rReg_immNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                  overflowAddL_rReg_immNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      overflowSubI_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                      overflowSubI_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                  overflowSubI_rReg_immNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                  overflowSubI_rReg_immNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      overflowSubL_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                      overflowSubL_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                  overflowSubL_rReg_immNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                  overflowSubL_rReg_immNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      overflowNegI_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                      overflowNegI_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      overflowNegL_rRegNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                      overflowNegL_rRegNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                      overflowMulI_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                      overflowMulI_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                  overflowMulI_rReg_immNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                  overflowMulI_rReg_immNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                      overflowMulL_rRegNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                      overflowMulL_rRegNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                  overflowMulL_rReg_immNode::pipeline_class() { return (&pipeline_class_010); }
const Pipeline *                                  overflowMulL_rReg_immNode::pipeline() const { return (&pipeline_class_010); }

const Pipeline *                                             compI_rRegNode::pipeline_class() { return (&pipeline_class_012); }
const Pipeline *                                             compI_rRegNode::pipeline() const { return (&pipeline_class_012); }

const Pipeline *                                         compI_rReg_immNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                         compI_rReg_immNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                         compI_rReg_memNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                         compI_rReg_memNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                              testI_regNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                              testI_regNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                          testI_reg_immNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                          testI_reg_immNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                          testI_reg_regNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                          testI_reg_regNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                          testI_reg_memNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                          testI_reg_memNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                        testI_reg_mem_0Node::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                        testI_reg_mem_0Node::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                             compU_rRegNode::pipeline_class() { return (&pipeline_class_012); }
const Pipeline *                                             compU_rRegNode::pipeline() const { return (&pipeline_class_012); }

const Pipeline *                                         compU_rReg_immNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                         compU_rReg_immNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                         compU_rReg_memNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                         compU_rReg_memNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                              testU_regNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                              testU_regNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                             compP_rRegNode::pipeline_class() { return (&pipeline_class_012); }
const Pipeline *                                             compP_rRegNode::pipeline() const { return (&pipeline_class_012); }

const Pipeline *                                         compP_rReg_memNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                         compP_rReg_memNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                         compP_mem_rRegNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                         compP_mem_rRegNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                              testP_regNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                              testP_regNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                              testP_memNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                              testP_memNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                         testP_mem_reg0Node::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                         testP_mem_reg0Node::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                             compN_rRegNode::pipeline_class() { return (&pipeline_class_012); }
const Pipeline *                                             compN_rRegNode::pipeline() const { return (&pipeline_class_012); }

const Pipeline *                                         compN_rReg_memNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                         compN_rReg_memNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                         compN_rReg_immNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                         compN_rReg_immNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                          compN_mem_immNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                          compN_mem_immNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                   compN_rReg_imm_klassNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                   compN_rReg_imm_klassNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                    compN_mem_imm_klassNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                    compN_mem_imm_klassNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                              testN_regNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                              testN_regNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                              testN_memNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                              testN_memNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                         testN_mem_reg0Node::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                         testN_mem_reg0Node::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                             compL_rRegNode::pipeline_class() { return (&pipeline_class_012); }
const Pipeline *                                             compL_rRegNode::pipeline() const { return (&pipeline_class_012); }

const Pipeline *                                         compL_rReg_immNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                         compL_rReg_immNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                         compL_rReg_memNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                         compL_rReg_memNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                              testL_regNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                              testL_regNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                          testL_reg_immNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                          testL_reg_immNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                          testL_reg_regNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                          testL_reg_regNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                          testL_reg_memNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                          testL_reg_memNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                        testL_reg_mem_0Node::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                        testL_reg_mem_0Node::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                         testL_reg_mem2Node::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                         testL_reg_mem2Node::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                       testL_reg_mem2_0Node::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                       testL_reg_mem2_0Node::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                          cmpU3_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          cmpU3_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          cmpL3_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          cmpL3_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         cmpUL3_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         cmpUL3_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            compUL_rRegNode::pipeline_class() { return (&pipeline_class_012); }
const Pipeline *                                            compUL_rRegNode::pipeline() const { return (&pipeline_class_012); }

const Pipeline *                                        compUL_rReg_immNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                        compUL_rReg_immNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                        compUL_rReg_memNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                        compUL_rReg_memNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                             testUL_regNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                             testUL_regNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                          compB_mem_immNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                          compB_mem_immNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                         testUB_mem_immNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                         testUB_mem_immNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                          testB_mem_immNode::pipeline_class() { return (&pipeline_class_014); }
const Pipeline *                                          testB_mem_immNode::pipeline() const { return (&pipeline_class_014); }

const Pipeline *                                            cmovI_reg_gNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                            cmovI_reg_gNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                            cmovI_reg_lNode::pipeline_class() { return (&pipeline_class_016); }
const Pipeline *                                            cmovI_reg_lNode::pipeline() const { return (&pipeline_class_016); }

const Pipeline *                                                 jmpDirNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                                                 jmpDirNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                                                 jmpConNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                                                 jmpConNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                                             jmpLoopEndNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                                             jmpLoopEndNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                                                jmpConUNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                                                jmpConUNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                                              jmpConUCFNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                                              jmpConUCFNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                                             jmpConUCF2Node::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                                             jmpConUCF2Node::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                                    partialSubtypeCheckNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    partialSubtypeCheckNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            partialSubtypeCheckVarSuperNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            partialSubtypeCheckVarSuperNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          partialSubtypeCheckConstSuperNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          partialSubtypeCheckConstSuperNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           jmpDir_shortNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                                           jmpDir_shortNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                                           jmpCon_shortNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                                           jmpCon_shortNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                                       jmpLoopEnd_shortNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                                       jmpLoopEnd_shortNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                                          jmpConU_shortNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                                          jmpConU_shortNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                                        jmpConUCF_shortNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                                        jmpConUCF_shortNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                                       jmpConUCF2_shortNode::pipeline_class() { return (&pipeline_class_035); }
const Pipeline *                                       jmpConUCF2_shortNode::pipeline() const { return (&pipeline_class_035); }

const Pipeline *                                            cmpFastLockNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            cmpFastLockNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          cmpFastUnlockNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          cmpFastUnlockNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 cmpFastLockLightweightNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 cmpFastLockLightweightNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                               cmpFastUnlockLightweightNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                               cmpFastUnlockLightweightNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     safePoint_poll_tlsNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                     safePoint_poll_tlsNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                         mask_all_evexLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         mask_all_evexLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    mask_all_evexI_GT32Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    mask_all_evexI_GT32Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   CallStaticJavaDirectNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   CallStaticJavaDirectNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  CallDynamicJavaDirectNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  CallDynamicJavaDirectNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      CallRuntimeDirectNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      CallRuntimeDirectNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         CallLeafDirectNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         CallLeafDirectNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   CallLeafDirectVectorNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   CallLeafDirectVectorNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     CallLeafNoFPDirectNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     CallLeafNoFPDirectNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                    RetNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                                                    RetNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                                         TailCalljmpIndNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                                         TailCalljmpIndNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                                             tailjmpIndNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                                             tailjmpIndNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                                    ForwardExceptionjmpNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                                    ForwardExceptionjmpNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                                        CreateExceptionNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                        CreateExceptionNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                       RethrowExceptionNode::pipeline_class() { return (&pipeline_class_034); }
const Pipeline *                                       RethrowExceptionNode::pipeline() const { return (&pipeline_class_034); }

const Pipeline *                                               tlsLoadPNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                               tlsLoadPNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                    leaI_rReg_rReg_peepNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                    leaI_rReg_rReg_peepNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                    leaI_rReg_immI_peepNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                    leaI_rReg_immI_peepNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                   leaI_rReg_immI2_peepNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                   leaI_rReg_immI2_peepNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                    leaL_rReg_rReg_peepNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                    leaL_rReg_rReg_peepNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                  leaL_rReg_immL32_peepNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                  leaL_rReg_immL32_peepNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                   leaL_rReg_immI2_peepNode::pipeline_class() { return (&pipeline_class_004); }
const Pipeline *                                   leaL_rReg_immI2_peepNode::pipeline() const { return (&pipeline_class_004); }

const Pipeline *                                     ShouldNotReachHereNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     ShouldNotReachHereNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               addF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               addF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               addF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               addF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             addF_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             addF_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               addF_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               addF_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           addF_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           addF_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           addF_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           addF_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         addF_reg_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         addF_reg_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           addF_reg_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           addF_reg_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               addD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               addD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               addD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               addD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             addD_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             addD_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               addD_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               addD_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           addD_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           addD_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           addD_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           addD_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         addD_reg_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         addD_reg_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           addD_reg_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           addD_reg_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               subF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               subF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               subF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               subF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               subF_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               subF_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           subF_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           subF_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           subF_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           subF_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           subF_reg_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           subF_reg_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               subD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               subD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               subD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               subD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               subD_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               subD_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           subD_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           subD_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           subD_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           subD_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           subD_reg_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           subD_reg_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               mulF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               mulF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               mulF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               mulF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             mulF_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             mulF_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               mulF_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               mulF_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           mulF_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           mulF_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           mulF_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           mulF_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         mulF_reg_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         mulF_reg_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           mulF_reg_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           mulF_reg_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               mulD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               mulD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               mulD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               mulD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             mulD_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             mulD_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               mulD_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               mulD_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           mulD_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           mulD_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           mulD_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           mulD_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         mulD_reg_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         mulD_reg_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           mulD_reg_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           mulD_reg_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               divF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               divF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               divF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               divF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               divF_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               divF_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           divF_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           divF_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           divF_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           divF_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           divF_reg_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           divF_reg_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               divD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               divD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               divD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               divD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               divD_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               divD_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           divD_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           divD_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           divD_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           divD_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           divD_reg_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           divD_reg_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               absF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               absF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           absF_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           absF_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               absD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               absD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           absD_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           absD_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               negF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               negF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           negF_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           negF_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               negD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               negD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           negD_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           negD_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              sqrtF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              sqrtF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              sqrtD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              sqrtD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       convF2HF_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       convF2HF_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       convF2HF_mem_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       convF2HF_mem_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vconvF2HFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vconvF2HFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vconvF2HF_mem_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vconvF2HF_mem_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       convHF2F_reg_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       convHF2F_reg_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vconvHF2F_reg_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vconvHF2F_reg_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vconvHF2FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vconvHF2FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       reinterpret_maskNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       reinterpret_maskNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   reinterpret_mask_W2BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   reinterpret_mask_W2BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   reinterpret_mask_D2BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   reinterpret_mask_D2BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   reinterpret_mask_Q2BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   reinterpret_mask_Q2BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            reinterpretNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            reinterpretNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     reinterpret_expandNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     reinterpret_expandNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vreinterpret_expand4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vreinterpret_expand4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vreinterpret_expandNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vreinterpret_expandNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     reinterpret_shrinkNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     reinterpret_shrinkNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             roundD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             roundD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             roundD_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             roundD_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vroundD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vroundD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           vround8D_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           vround8D_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vroundD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vroundD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           vround8D_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           vround8D_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             onspinwaitNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             onspinwaitNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               fmaD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               fmaD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               fmaF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               fmaF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            MoveVec2LegNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                            MoveVec2LegNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                            MoveLeg2VecNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                            MoveLeg2VecNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                                  loadVNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  loadVNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                 storeVNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                 storeVNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                 gatherNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                 gatherNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               evgatherNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               evgatherNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        evgather_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        evgather_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vgather_subwordLE8BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vgather_subwordLE8BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vgather_subwordGT8BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vgather_subwordGT8BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                vgather_subwordLE8B_offNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                vgather_subwordLE8B_offNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                vgather_subwordGT8B_offNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                vgather_subwordGT8B_offNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                        vgather_masked_subwordLE8B_avx3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                        vgather_masked_subwordLE8B_avx3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                        vgather_masked_subwordGT8B_avx3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                        vgather_masked_subwordGT8B_avx3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                    vgather_masked_subwordLE8B_off_avx3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                    vgather_masked_subwordLE8B_off_avx3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                    vgather_masked_subwordGT8B_off_avx3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                    vgather_masked_subwordGT8B_off_avx3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                        vgather_masked_subwordLE8B_avx2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                        vgather_masked_subwordLE8B_avx2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                        vgather_masked_subwordGT8B_avx2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                        vgather_masked_subwordGT8B_avx2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                    vgather_masked_subwordLE8B_off_avx2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                    vgather_masked_subwordLE8B_off_avx2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                    vgather_masked_subwordGT8B_off_avx2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                    vgather_masked_subwordGT8B_off_avx2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                scatterNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                scatterNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         scatter_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         scatter_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vReplB_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vReplB_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplB_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplB_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vReplS_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vReplS_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             ReplHF_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             ReplHF_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             ReplHF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             ReplHF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplS_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplS_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplI_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplI_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplI_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplI_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplI_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplI_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             ReplI_zeroNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                             ReplI_zeroNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                               ReplI_M1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               ReplI_M1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplL_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplL_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplL_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplL_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplL_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplL_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             ReplL_zeroNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                             ReplL_zeroNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                               ReplL_M1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               ReplL_M1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vReplF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vReplF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplF_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplF_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             ReplF_zeroNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                             ReplF_zeroNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                             vReplD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vReplD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ReplD_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ReplD_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             ReplD_zeroNode::pipeline_class() { return (&pipeline_class_020); }
const Pipeline *                                             ReplD_zeroNode::pipeline() const { return (&pipeline_class_020); }

const Pipeline *                                                 insertNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                 insertNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               insert32Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               insert32Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               insert64Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               insert64Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               insert2LNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               insert2LNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               insert4LNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               insert4LNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               insert8LNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               insert8LNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                insertFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                insertFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vinsertFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vinsertFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               insert2DNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               insert2DNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               insert4DNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               insert4DNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               insert8DNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               insert8DNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             reductionINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             reductionINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionI_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionI_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionI_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionI_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionI_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionI_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionI_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionI_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionI_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionI_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionI_5Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionI_5Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             reductionLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             reductionLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionL_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionL_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionL_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionL_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionL_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionL_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionL_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionL_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionL_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionL_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionL_5Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionL_5Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    reductionL_avx512dqNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    reductionL_avx512dqNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionL_avx512dq_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionL_avx512dq_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionL_avx512dq_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionL_avx512dq_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionL_avx512dq_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionL_avx512dq_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionL_avx512dq_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionL_avx512dq_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionL_avx512dq_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionL_avx512dq_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionL_avx512dq_5Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionL_avx512dq_5Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          reductionF128Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          reductionF128Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        reductionF128_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        reductionF128_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            reduction8FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            reduction8FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          reduction8F_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          reduction8F_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reduction16FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reduction16FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         reduction16F_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         reduction16F_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  unordered_reduction2FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  unordered_reduction2FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                unordered_reduction2F_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                unordered_reduction2F_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  unordered_reduction4FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  unordered_reduction4FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                unordered_reduction4F_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                unordered_reduction4F_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  unordered_reduction8FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  unordered_reduction8FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                unordered_reduction8F_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                unordered_reduction8F_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 unordered_reduction16FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 unordered_reduction16FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                               unordered_reduction16F_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                               unordered_reduction16F_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            reduction2DNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            reduction2DNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          reduction2D_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          reduction2D_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            reduction4DNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            reduction4DNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          reduction4D_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          reduction4D_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            reduction8DNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            reduction8DNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          reduction8D_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          reduction8D_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  unordered_reduction2DNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  unordered_reduction2DNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                unordered_reduction2D_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                unordered_reduction2D_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  unordered_reduction4DNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  unordered_reduction4DNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                unordered_reduction4D_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                unordered_reduction4D_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  unordered_reduction8DNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  unordered_reduction8DNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                unordered_reduction8D_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                unordered_reduction8D_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             reductionBNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             reductionBNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionB_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionB_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionB_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionB_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionB_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionB_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionB_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionB_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionB_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionB_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    reductionB_avx512bwNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    reductionB_avx512bwNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionB_avx512bw_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionB_avx512bw_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionB_avx512bw_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionB_avx512bw_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionB_avx512bw_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionB_avx512bw_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionB_avx512bw_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionB_avx512bw_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  reductionB_avx512bw_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  reductionB_avx512bw_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             reductionSNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             reductionSNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionS_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionS_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionS_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionS_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionS_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionS_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionS_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionS_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionS_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionS_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           reductionS_5Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           reductionS_5Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         mul_reductionBNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         mul_reductionBNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       mul_reduction64BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       mul_reduction64BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     minmax_reduction2FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     minmax_reduction2FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   minmax_reduction2F_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   minmax_reduction2F_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      minmax_reductionFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      minmax_reductionFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    minmax_reductionF_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    minmax_reductionF_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  minmax_reduction2F_avNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  minmax_reduction2F_avNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                minmax_reduction2F_av_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                minmax_reduction2F_av_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   minmax_reductionF_avNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   minmax_reductionF_avNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 minmax_reductionF_av_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 minmax_reductionF_av_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     minmax_reduction2DNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     minmax_reduction2DNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   minmax_reduction2D_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   minmax_reduction2D_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      minmax_reductionDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      minmax_reductionDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    minmax_reductionD_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    minmax_reductionD_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  minmax_reduction2D_avNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  minmax_reduction2D_avNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                minmax_reduction2D_av_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                minmax_reduction2D_av_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   minmax_reductionD_avNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   minmax_reductionD_avNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 minmax_reductionD_av_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 minmax_reductionD_av_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vaddBNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vaddBNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddB_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddB_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddB_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddB_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vaddB_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vaddB_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vaddSNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vaddSNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddS_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddS_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddS_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddS_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vaddS_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vaddS_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vaddINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vaddINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddI_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddI_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddI_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddI_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vaddI_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vaddI_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vaddLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vaddLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddL_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddL_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddL_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddL_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vaddL_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vaddL_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vaddFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vaddFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vaddF_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vaddF_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vaddDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vaddDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vaddD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vaddD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vaddD_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vaddD_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vsubBNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vsubBNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubB_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubB_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubB_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubB_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vsubSNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vsubSNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubS_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubS_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubS_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubS_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vsubINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vsubINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubI_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubI_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubI_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubI_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vsubLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vsubLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubL_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubL_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubL_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubL_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vsubFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vsubFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vsubDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vsubDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vsubD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vsubD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                 vmul8BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                 vmul8BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vmulBNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vmulBNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmulB_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmulB_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vmulSNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vmulSNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmulS_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmulS_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmulS_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmulS_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vmulS_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vmulS_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vmulINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vmulINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmulI_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmulI_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmulI_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmulI_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vmulI_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vmulI_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             evmulL_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             evmulL_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             evmulL_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             evmulL_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           evmulL_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           evmulL_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vmulLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vmulLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmulL_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmulL_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vmuludq_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vmuludq_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vmuldq_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vmuldq_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vmulFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vmulFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmulF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmulF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmulF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmulF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vmulF_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vmulF_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vmulDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vmulDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmulD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmulD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmulD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmulD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vmulD_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vmulD_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vdivFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vdivFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vdivF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vdivF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vdivF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vdivF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vdivDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vdivDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vdivD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vdivD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vdivD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vdivD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         minmax_reg_sseNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         minmax_reg_sseNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       minmax_reg_sse_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       minmax_reg_sse_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vminmax_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vminmax_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vminmax_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vminmax_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        minmaxL_reg_sseNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        minmaxL_reg_sseNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      minmaxL_reg_sse_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      minmaxL_reg_sse_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       vminmaxL_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       vminmaxL_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vminmaxL_reg_avx_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vminmaxL_reg_avx_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vminmaxL_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vminmaxL_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vminmaxL_reg_evex_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vminmaxL_reg_evex_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           minmaxFP_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           minmaxFP_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         minmaxFP_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         minmaxFP_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    evminmaxFP_reg_eavxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    evminmaxFP_reg_eavxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  evminmaxFP_reg_eavx_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  evminmaxFP_reg_eavx_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vector_uminmax_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vector_uminmax_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vector_uminmax_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vector_uminmax_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vector_uminmax_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vector_uminmax_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vector_uminmax_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vector_uminmax_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vector_uminmaxq_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vector_uminmaxq_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vector_uminmaxq_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vector_uminmaxq_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                              vector_uminmax_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                              vector_uminmax_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            vector_uminmax_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            vector_uminmax_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                              vector_uminmax_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                              vector_uminmax_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            vector_uminmax_mem_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            vector_uminmax_mem_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            signumF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            signumF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            signumD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            signumD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        signumV_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        signumV_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      signumV_reg_avx_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      signumV_reg_avx_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       signumV_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       signumV_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     signumV_reg_evex_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     signumV_reg_evex_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          copySignF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          copySignF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          copySignD_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          copySignD_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      compressBitsI_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      compressBitsI_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        expandBitsI_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        expandBitsI_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      compressBitsI_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      compressBitsI_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        expandBitsI_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        expandBitsI_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vsqrtF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vsqrtF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vsqrtF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vsqrtF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vsqrtD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vsqrtD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vsqrtD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vsqrtD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vshiftcntNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vshiftcntNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vshiftcnt_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vshiftcnt_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                vshiftBNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                vshiftBNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vshiftB_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vshiftB_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vshiftB_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vshiftB_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vshift16BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vshift16BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vshift16B_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vshift16B_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vshift16B_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vshift16B_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vshift16B_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vshift16B_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vshift16B_avx_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vshift16B_avx_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vshift16B_avx_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vshift16B_avx_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vshift32B_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vshift32B_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vshift32B_avx_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vshift32B_avx_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vshift32B_avx_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vshift32B_avx_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vshift64B_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vshift64B_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vshift64B_avx_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vshift64B_avx_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vshift64B_avx_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vshift64B_avx_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                vshiftSNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                vshiftSNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vshiftS_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vshiftS_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vshiftS_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vshiftS_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                vshiftINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                vshiftINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vshiftI_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vshiftI_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vshiftI_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vshiftI_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vshiftI_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vshiftI_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vshiftI_imm_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vshiftI_imm_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vshiftI_imm_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vshiftI_imm_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                vshiftLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                vshiftLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vshiftL_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vshiftL_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vshiftL_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vshiftL_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vshiftL_imm_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vshiftL_imm_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vshiftL_arith_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vshiftL_arith_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 vshiftL_arith_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 vshiftL_arith_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vshift8B_var_nobwNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vshift8B_var_nobwNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vshift8B_var_nobw_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vshift8B_var_nobw_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vshift8B_var_nobw_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vshift8B_var_nobw_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vshift16B_var_nobwNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vshift16B_var_nobwNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vshift16B_var_nobw_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vshift16B_var_nobw_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vshift16B_var_nobw_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vshift16B_var_nobw_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vshift32B_var_nobwNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vshift32B_var_nobwNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vshift32B_var_nobw_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vshift32B_var_nobw_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vshift32B_var_nobw_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vshift32B_var_nobw_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vshiftB_var_evex_bwNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vshiftB_var_evex_bwNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vshiftB_var_evex_bw_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vshiftB_var_evex_bw_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vshiftB_var_evex_bw_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vshiftB_var_evex_bw_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vshift64B_var_evex_bwNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vshift64B_var_evex_bwNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                vshift64B_var_evex_bw_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                vshift64B_var_evex_bw_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                vshift64B_var_evex_bw_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                vshift64B_var_evex_bw_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vshift8S_var_nobwNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vshift8S_var_nobwNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vshift8S_var_nobw_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vshift8S_var_nobw_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vshift8S_var_nobw_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vshift8S_var_nobw_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vshift16S_var_nobwNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vshift16S_var_nobwNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vshift16S_var_nobw_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vshift16S_var_nobw_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vshift16S_var_nobw_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vshift16S_var_nobw_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vshift16S_var_evex_bwNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vshift16S_var_evex_bwNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                vshift16S_var_evex_bw_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                vshift16S_var_evex_bw_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                vshift16S_var_evex_bw_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                vshift16S_var_evex_bw_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vshiftI_varNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vshiftI_varNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vshiftI_var_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vshiftI_var_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vshiftI_var_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vshiftI_var_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vshiftL_varNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vshiftL_varNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vshiftL_var_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vshiftL_var_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vshiftL_arith_varNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vshiftL_arith_varNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 vshiftL_arith_var_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 vshiftL_arith_var_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                   vandNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                   vandNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vand_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vand_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vand_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vand_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vand_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vand_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                    vorNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                    vorNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                vor_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                vor_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                vor_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                vor_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vor_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vor_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                   vxorNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                   vxorNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vxor_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vxor_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vxor_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vxor_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vxor_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vxor_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vcastBtoXNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vcastBtoXNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vcastBtoDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vcastBtoDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               castStoXNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               castStoXNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vcastStoXNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vcastStoXNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         vcastStoX_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         vcastStoX_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               castItoXNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               castItoXNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vcastItoXNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vcastItoXNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         vcastItoX_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         vcastItoX_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vcastLtoBSNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vcastLtoBSNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         vcastLtoX_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         vcastLtoX_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vcastFtoD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vcastFtoD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       castFtoX_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       castFtoX_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      castFtoX_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      castFtoX_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vcastDtoF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vcastDtoF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       castDtoX_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       castDtoX_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      castDtoX_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      castDtoX_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                 vucastNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                 vucastNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vucast_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vucast_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vucast_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vucast_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       vround_float_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       vround_float_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vround_float_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vround_float_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vround_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vround_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                 vcmpFDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                 vcmpFDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              evcmpFD64Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              evcmpFD64Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                evcmpFDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                evcmpFDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vcmp_directNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vcmp_directNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vcmp_negateNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vcmp_negateNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  vcmpuNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  vcmpuNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                 vcmp64Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                 vcmp64Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                  evcmpNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                  evcmpNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               extractINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               extractINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             extractI_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             extractI_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             extractI_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             extractI_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vextractINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vextractINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vextractI_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vextractI_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vextractI_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vextractI_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               extractLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               extractLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vextractLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vextractLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               extractFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               extractFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vextractFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vextractFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               extractDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               extractDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vextractDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vextractDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                blendvpNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                                blendvpNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vblendvpINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vblendvpINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vblendvpFDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vblendvpFDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vblendvpNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vblendvpNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            evblendvp64Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            evblendvp64Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     evblendvp64_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     evblendvp64_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vabsB_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vabsB_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vabsS_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vabsS_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vabsI_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vabsI_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vabsL_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vabsL_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vabsnegFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vabsnegFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vabsnegF_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vabsnegF_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vabsneg4FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vabsneg4FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vabsneg4F_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vabsneg4F_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vabsnegDNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vabsnegDNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vabsnegD_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vabsnegD_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vptest_lt16Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vptest_lt16Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vptest_ge16Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vptest_ge16Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      ktest_alltrue_le8Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      ktest_alltrue_le8Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      ktest_anytrue_le8Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      ktest_anytrue_le8Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              ktest_ge8Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              ktest_ge8Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               loadMaskNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               loadMaskNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             loadMask64Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             loadMask64Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          loadMask_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          loadMask_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           vstoreMask1BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           vstoreMask1BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           vstoreMask2BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           vstoreMask2BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           vstoreMask4BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           vstoreMask4BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            storeMask8BNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            storeMask8BNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        storeMask8B_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        storeMask8B_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                           vstoreMask4B_evex_novectmaskNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                           vstoreMask4B_evex_novectmaskNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                           vstoreMask8B_evex_novectmaskNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                           vstoreMask8B_evex_novectmaskNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                               vstoreMask_evex_vectmaskNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                               vstoreMask_evex_vectmaskNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vstoreMask_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vstoreMask_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         vmaskcast_evexNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                         vmaskcast_evexNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                              vmaskcastNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                              vmaskcastNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                          vmaskcast_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vmaskcast_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        loadIotaIndicesNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        loadIotaIndicesNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    VectorPopulateIndexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    VectorPopulateIndexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   VectorPopulateLIndexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   VectorPopulateLIndexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             rearrangeBNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             rearrangeBNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         rearrangeB_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         rearrangeB_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        rearrangeB_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        rearrangeB_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   rearrangeB_evex_vbmiNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   rearrangeB_evex_vbmiNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           loadShuffleSNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           loadShuffleSNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             rearrangeSNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             rearrangeSNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         rearrangeS_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         rearrangeS_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        rearrangeS_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        rearrangeS_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           loadShuffleINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           loadShuffleINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             rearrangeINode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             rearrangeINode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         rearrangeI_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         rearrangeI_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           loadShuffleLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           loadShuffleLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             rearrangeLNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             rearrangeLNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        rearrangeL_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        rearrangeL_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vfmaF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vfmaF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vfmaF_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vfmaF_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vfmaD_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vfmaD_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vfmaD_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vfmaD_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vmuladdS2I_reg_sseNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vmuladdS2I_reg_sseNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vmuladdS2I_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vmuladdS2I_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmuladdaddS2I_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmuladdaddS2I_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vmuladdaddS2I_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vmuladdaddS2I_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            vpopcount_integral_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            vpopcount_integral_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          vpopcount_integral_reg_evex_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          vpopcount_integral_reg_evex_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                     vpopcount_integral_reg_evex_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                     vpopcount_integral_reg_evex_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                   vpopcount_integral_reg_evex_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                   vpopcount_integral_reg_evex_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vpopcount_avx_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vpopcount_avx_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vpopcount_avx_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vpopcount_avx_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                         vcount_trailing_zeros_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                         vcount_trailing_zeros_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                   vcount_trailing_zeros_short_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                   vcount_trailing_zeros_short_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                    vcount_trailing_zeros_byte_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                    vcount_trailing_zeros_byte_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          vcount_trailing_zeros_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          vcount_trailing_zeros_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vpternlogNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vpternlogNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vpternlog_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vpternlog_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         vprotate_immI8Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         vprotate_immI8Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       vprotate_immI8_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       vprotate_immI8_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                               vprorateNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                               vprorateNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                             vprorate_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                             vprorate_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                           vmasked_load_avx_non_subwordNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                           vmasked_load_avx_non_subwordNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmasked_load_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmasked_load_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          vmasked_store_avx_non_subwordNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          vmasked_store_avx_non_subwordNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vmasked_store_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vmasked_store_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                verify_vector_alignmentNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                verify_vector_alignmentNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         vmask_cmp_nodeNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         vmask_cmp_nodeNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                              vmask_genNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                              vmask_genNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vmask_gen_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vmask_gen_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmask_tolong_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmask_tolong_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmask_tolong_boolNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmask_tolong_boolNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       vmask_tolong_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       vmask_tolong_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vmask_truecount_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vmask_truecount_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vmask_truecount_boolNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vmask_truecount_boolNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vmask_truecount_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vmask_truecount_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          vmask_first_or_last_true_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          vmask_first_or_last_true_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                        vmask_first_or_last_true_evex_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                        vmask_first_or_last_true_evex_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                          vmask_first_or_last_true_boolNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                          vmask_first_or_last_true_boolNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                        vmask_first_or_last_true_bool_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                        vmask_first_or_last_true_bool_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                           vmask_first_or_last_true_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                           vmask_first_or_last_true_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                         vmask_first_or_last_true_avx_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                         vmask_first_or_last_true_avx_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vcompress_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vcompress_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vcompress_reg_avx_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vcompress_reg_avx_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                              vcompress_expand_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                              vcompress_expand_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                            vcompress_expand_reg_evex_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                            vcompress_expand_reg_evex_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                vcompress_mask_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                vcompress_mask_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           vreverse_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           vreverse_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vreverse_reg_gfniNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vreverse_reg_gfniNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vreverse_byte_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vreverse_byte_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vreverse_byte64_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vreverse_byte64_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                       vcount_leading_zeros_IL_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                       vcount_leading_zeros_IL_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                vcount_leading_zeros_IL_reg_evex_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                vcount_leading_zeros_IL_reg_evex_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                    vcount_leading_zeros_short_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                    vcount_leading_zeros_short_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                     vcount_leading_zeros_byte_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                     vcount_leading_zeros_byte_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                       vcount_leading_zeros_int_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                       vcount_leading_zeros_int_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                           vcount_leading_zeros_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                           vcount_leading_zeros_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vadd_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vadd_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vadd_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vadd_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vadd_reg_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vadd_reg_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vadd_reg_masked_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vadd_reg_masked_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vadd_reg_masked_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vadd_reg_masked_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vadd_reg_masked_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vadd_reg_masked_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vadd_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vadd_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vadd_mem_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vadd_mem_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vadd_mem_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vadd_mem_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vadd_mem_masked_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vadd_mem_masked_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vadd_mem_masked_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vadd_mem_masked_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vadd_mem_masked_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vadd_mem_masked_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vxor_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vxor_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vxor_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vxor_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         vor_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         vor_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                         vor_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                         vor_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vand_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vand_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vand_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vand_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vsub_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vsub_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vsub_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vsub_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vsub_reg_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vsub_reg_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vsub_reg_masked_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vsub_reg_masked_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vsub_reg_masked_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vsub_reg_masked_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vsub_reg_masked_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vsub_reg_masked_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vsub_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vsub_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vsub_mem_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vsub_mem_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vsub_mem_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vsub_mem_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vsub_mem_masked_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vsub_mem_masked_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vsub_mem_masked_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vsub_mem_masked_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vsub_mem_masked_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vsub_mem_masked_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vmul_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vmul_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmul_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmul_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmul_reg_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmul_reg_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmul_reg_masked_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmul_reg_masked_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmul_reg_masked_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmul_reg_masked_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vmul_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vmul_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmul_mem_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmul_mem_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmul_mem_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmul_mem_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmul_mem_masked_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmul_mem_masked_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vmul_mem_masked_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vmul_mem_masked_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       vsqrt_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       vsqrt_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vsqrt_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vsqrt_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vdiv_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vdiv_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vdiv_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vdiv_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vdiv_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vdiv_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vdiv_mem_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vdiv_mem_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vrol_imm_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vrol_imm_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vrol_imm_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vrol_imm_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vrol_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vrol_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vrol_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vrol_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vlshift_imm_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vlshift_imm_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vlshift_imm_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vlshift_imm_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vlshift_imm_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vlshift_imm_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vlshift_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vlshift_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vlshift_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vlshift_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vlshift_reg_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vlshift_reg_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vlshiftv_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vlshiftv_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vlshiftv_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vlshiftv_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vlshiftv_reg_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vlshiftv_reg_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vrshift_imm_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vrshift_imm_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vrshift_imm_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vrshift_imm_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vrshift_imm_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vrshift_imm_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     vrshift_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     vrshift_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vrshift_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vrshift_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vrshift_reg_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vrshift_reg_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vrshiftv_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vrshiftv_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vrshiftv_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vrshiftv_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vrshiftv_reg_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vrshiftv_reg_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vurshift_imm_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vurshift_imm_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vurshift_imm_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vurshift_imm_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vurshift_imm_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vurshift_imm_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vurshift_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vurshift_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vurshift_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vurshift_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                  vurshift_reg_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                  vurshift_reg_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vurshiftv_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vurshiftv_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 vurshiftv_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 vurshiftv_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 vurshiftv_reg_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 vurshiftv_reg_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       vmaxv_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       vmaxv_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       vmaxv_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       vmaxv_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       vminv_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       vminv_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                       vminv_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                       vminv_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 vrearrangev_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 vrearrangev_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                            vabs_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                            vabs_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vabs_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vabs_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vabs_masked_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vabs_masked_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                          vabs_masked_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                          vabs_masked_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vfma_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vfma_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vfma_reg_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vfma_reg_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        vfma_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        vfma_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      vfma_mem_masked_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      vfma_mem_masked_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           evcmp_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           evcmp_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    mask_all_evexI_LE32Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    mask_all_evexI_LE32Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        mask_not_immLT8Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        mask_not_immLT8Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                           mask_not_immNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                           mask_not_immNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    long_to_maskLE8_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    long_to_maskLE8_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    long_to_maskGT8_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    long_to_maskGT8_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      long_to_mask_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      long_to_mask_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        mask_opers_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        mask_opers_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      mask_opers_evex_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      mask_opers_evex_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      mask_opers_evex_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      mask_opers_evex_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                    vternlog_reg_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                    vternlog_reg_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   vternlogd_mem_maskedNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   vternlogd_mem_maskedNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                                 castMMNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                                 castMMNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                                 castVVNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                                 castVVNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                                              castVVLegNode::pipeline_class() { return (&pipeline_class_038); }
const Pipeline *                                              castVVLegNode::pipeline() const { return (&pipeline_class_038); }

const Pipeline *                       FloatClassCheck_reg_reg_vfpclassNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                       FloatClassCheck_reg_reg_vfpclassNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                      DoubleClassCheck_reg_reg_vfpclassNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                      DoubleClassCheck_reg_reg_vfpclassNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                   vector_addsub_saturating_subword_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                   vector_addsub_saturating_subword_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                 vector_addsub_saturating_subword_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                 vector_addsub_saturating_subword_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *          vector_addsub_saturating_unsigned_subword_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *          vector_addsub_saturating_unsigned_subword_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *        vector_addsub_saturating_unsigned_subword_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *        vector_addsub_saturating_unsigned_subword_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                      vector_addsub_saturating_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                      vector_addsub_saturating_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                    vector_addsub_saturating_reg_evex_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                    vector_addsub_saturating_reg_evex_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                       vector_addsub_saturating_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                       vector_addsub_saturating_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                     vector_addsub_saturating_reg_avx_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                     vector_addsub_saturating_reg_avx_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                vector_add_saturating_unsigned_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                vector_add_saturating_unsigned_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                 vector_add_saturating_unsigned_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                 vector_add_saturating_unsigned_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                vector_sub_saturating_unsigned_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                vector_sub_saturating_unsigned_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                 vector_sub_saturating_unsigned_reg_avxNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                 vector_sub_saturating_unsigned_reg_avxNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                   vector_addsub_saturating_subword_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                   vector_addsub_saturating_subword_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                 vector_addsub_saturating_subword_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                 vector_addsub_saturating_subword_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *          vector_addsub_saturating_unsigned_subword_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *          vector_addsub_saturating_unsigned_subword_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *        vector_addsub_saturating_unsigned_subword_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *        vector_addsub_saturating_unsigned_subword_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *            vector_addsub_saturating_subword_masked_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *            vector_addsub_saturating_subword_masked_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *          vector_addsub_saturating_subword_masked_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *          vector_addsub_saturating_subword_masked_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *   vector_addsub_saturating_unsigned_subword_masked_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *   vector_addsub_saturating_unsigned_subword_masked_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline * vector_addsub_saturating_unsigned_subword_masked_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline * vector_addsub_saturating_unsigned_subword_masked_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *            vector_addsub_saturating_subword_masked_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *            vector_addsub_saturating_subword_masked_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *          vector_addsub_saturating_subword_masked_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *          vector_addsub_saturating_subword_masked_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *   vector_addsub_saturating_unsigned_subword_masked_memNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *   vector_addsub_saturating_unsigned_subword_masked_memNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline * vector_addsub_saturating_unsigned_subword_masked_mem_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline * vector_addsub_saturating_unsigned_subword_masked_mem_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                  vector_selectfrom_twovectors_reg_evexNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                  vector_selectfrom_twovectors_reg_evexNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        reinterpretS2HFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        reinterpretS2HFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convF2HFAndS2HFNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convF2HFAndS2HFNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        convHF2SAndHF2FNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        convHF2SAndHF2FNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                        reinterpretHF2SNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                        reinterpretHF2SNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                     scalar_sqrt_HF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                     scalar_sqrt_HF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                   scalar_binOps_HF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                   scalar_binOps_HF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 scalar_binOps_HF_reg_0Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 scalar_binOps_HF_reg_0Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 scalar_binOps_HF_reg_1Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 scalar_binOps_HF_reg_1Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 scalar_binOps_HF_reg_2Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 scalar_binOps_HF_reg_2Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 scalar_binOps_HF_reg_3Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 scalar_binOps_HF_reg_3Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                 scalar_binOps_HF_reg_4Node::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                 scalar_binOps_HF_reg_4Node::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                                      scalar_fma_HF_regNode::pipeline_class() { return (&pipeline_class_037); }
const Pipeline *                                      scalar_fma_HF_regNode::pipeline() const { return (&pipeline_class_037); }

const Pipeline *                             compareAndSwapP_shenandoahNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                             compareAndSwapP_shenandoahNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                           compareAndSwapP_shenandoah_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                           compareAndSwapP_shenandoah_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                             compareAndSwapN_shenandoahNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                             compareAndSwapN_shenandoahNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                           compareAndSwapN_shenandoah_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                           compareAndSwapN_shenandoah_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                         compareAndExchangeN_shenandoahNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                         compareAndExchangeN_shenandoahNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                         compareAndExchangeP_shenandoahNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                         compareAndExchangeP_shenandoahNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                 zLoadPNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                 zLoadPNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                        zLoadPNullCheckNode::pipeline_class() { return (&pipeline_class_013); }
const Pipeline *                                        zLoadPNullCheckNode::pipeline() const { return (&pipeline_class_013); }

const Pipeline *                                                zStorePNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                                zStorePNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                            zStorePNullNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                            zStorePNullNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                   zCompareAndExchangePNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                   zCompareAndExchangePNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                       zCompareAndSwapPNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                       zCompareAndSwapPNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                     zCompareAndSwapP_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                     zCompareAndSwapP_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                 zXChgPNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                                 zXChgPNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                               g1StorePNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                               g1StorePNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                               g1StoreNNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                               g1StoreNNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                     g1EncodePAndStoreNNode::pipeline_class() { return (&pipeline_class_008); }
const Pipeline *                                     g1EncodePAndStoreNNode::pipeline() const { return (&pipeline_class_008); }

const Pipeline *                                  g1CompareAndExchangePNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                  g1CompareAndExchangePNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                  g1CompareAndExchangeNNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                  g1CompareAndExchangeNNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                      g1CompareAndSwapPNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                      g1CompareAndSwapPNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                    g1CompareAndSwapP_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                    g1CompareAndSwapP_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                      g1CompareAndSwapNNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                      g1CompareAndSwapNNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                    g1CompareAndSwapN_0Node::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                    g1CompareAndSwapN_0Node::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                           g1GetAndSetPNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                           g1GetAndSetPNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                           g1GetAndSetNNode::pipeline_class() { return (&pipeline_class_036); }
const Pipeline *                                           g1GetAndSetNNode::pipeline() const { return (&pipeline_class_036); }

const Pipeline *                                                g1LoadPNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                g1LoadPNode::pipeline() const { return (&pipeline_class_006); }

const Pipeline *                                                g1LoadNNode::pipeline_class() { return (&pipeline_class_006); }
const Pipeline *                                                g1LoadNNode::pipeline() const { return (&pipeline_class_006); }
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
