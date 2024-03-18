#line 1 "ad_aarch64_gen.cpp"
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
#include "opto/cfgnode.hpp"
#include "opto/locknode.hpp"
#include "opto/rootnode.hpp"


//------------------------- MachOper Generator ---------------
// A switch statement on the dense-packed user-defined type system
// that invokes 'new' on the corresponding class constructor.

MachOper *State::MachOperGenerator(int opcode){

  switch(opcode) {
  case UNIVERSE:
    return new UniverseOper( );
  case LABEL:
    return new labelOper( );
  case SREGI:
    return new sRegIOper( );
  case SREGP:
    return new sRegPOper( );
  case SREGF:
    return new sRegFOper( );
  case SREGD:
    return new sRegDOper( );
  case SREGL:
    return new sRegLOper( );
  case METHOD:
    return new methodOper( );
  case IMMI:
    return new immIOper(_leaf->get_int() );
  case IMMI0:
    return new immI0Oper(_leaf->get_int() );
  case IMMI_1:
    return new immI_1Oper(_leaf->get_int() );
  case IMMI_M1:
    return new immI_M1Oper(_leaf->get_int() );
  case IMMIEXT:
    return new immIExtOper(_leaf->get_int() );
  case IMMI_GT_1:
    return new immI_gt_1Oper(_leaf->get_int() );
  case IMMI_LE_4:
    return new immI_le_4Oper(_leaf->get_int() );
  case IMMI_16:
    return new immI_16Oper(_leaf->get_int() );
  case IMMI_24:
    return new immI_24Oper(_leaf->get_int() );
  case IMMI_32:
    return new immI_32Oper(_leaf->get_int() );
  case IMMI_48:
    return new immI_48Oper(_leaf->get_int() );
  case IMMI_56:
    return new immI_56Oper(_leaf->get_int() );
  case IMMI_255:
    return new immI_255Oper(_leaf->get_int() );
  case IMMI_65535:
    return new immI_65535Oper(_leaf->get_int() );
  case IMMI_POSITIVE:
    return new immI_positiveOper(_leaf->get_int() );
  case IMMI_CMP_COND:
    return new immI_cmp_condOper(_leaf->get_int() );
  case IMMI_CMPU_COND:
    return new immI_cmpU_condOper(_leaf->get_int() );
  case IMML_255:
    return new immL_255Oper(_leaf->get_long() );
  case IMML_65535:
    return new immL_65535Oper(_leaf->get_long() );
  case IMML_4294967295:
    return new immL_4294967295Oper(_leaf->get_long() );
  case IMML_BITMASK:
    return new immL_bitmaskOper(_leaf->get_long() );
  case IMMI_BITMASK:
    return new immI_bitmaskOper(_leaf->get_int() );
  case IMML_POSITIVE_BITMASKI:
    return new immL_positive_bitmaskIOper(_leaf->get_long() );
  case IMMISCALE:
    return new immIScaleOper(_leaf->get_int() );
  case IMMI5:
    return new immI5Oper(_leaf->get_int() );
  case IMMIU7:
    return new immIU7Oper(_leaf->get_int() );
  case IMMIOFFSET:
    return new immIOffsetOper(_leaf->get_int() );
  case IMMIOFFSET1:
    return new immIOffset1Oper(_leaf->get_int() );
  case IMMIOFFSET2:
    return new immIOffset2Oper(_leaf->get_int() );
  case IMMIOFFSET4:
    return new immIOffset4Oper(_leaf->get_int() );
  case IMMIOFFSET8:
    return new immIOffset8Oper(_leaf->get_int() );
  case IMMIOFFSET16:
    return new immIOffset16Oper(_leaf->get_int() );
  case IMMLOFFSET:
    return new immLoffsetOper(_leaf->get_long() );
  case IMMLOFFSET1:
    return new immLoffset1Oper(_leaf->get_long() );
  case IMMLOFFSET2:
    return new immLoffset2Oper(_leaf->get_long() );
  case IMMLOFFSET4:
    return new immLoffset4Oper(_leaf->get_long() );
  case IMMLOFFSET8:
    return new immLoffset8Oper(_leaf->get_long() );
  case IMMLOFFSET16:
    return new immLoffset16Oper(_leaf->get_long() );
  case IMML5:
    return new immL5Oper(_leaf->get_long() );
  case IMMLU7:
    return new immLU7Oper(_leaf->get_long() );
  case IMMI8:
    return new immI8Oper(_leaf->get_int() );
  case IMMI8_SHIFT8:
    return new immI8_shift8Oper(_leaf->get_int() );
  case IMML8_SHIFT8:
    return new immL8_shift8Oper(_leaf->get_long() );
  case IMMBADDSUBV:
    return new immBAddSubVOper(_leaf->get_int() );
  case IMMIADDSUB:
    return new immIAddSubOper(_leaf->get_int() );
  case IMMIADDSUBV:
    return new immIAddSubVOper(_leaf->get_int() );
  case IMMBLOG:
    return new immBLogOper(_leaf->get_int() );
  case IMMSLOG:
    return new immSLogOper(_leaf->get_int() );
  case IMMILOG:
    return new immILogOper(_leaf->get_int() );
  case IMML:
    return new immLOper(_leaf->get_long() );
  case IMML0:
    return new immL0Oper(_leaf->get_long() );
  case IMML_M1:
    return new immL_M1Oper(_leaf->get_long() );
  case IMMLADDSUB:
    return new immLAddSubOper(_leaf->get_long() );
  case IMMLADDSUBV:
    return new immLAddSubVOper(_leaf->get_long() );
  case IMMLLOG:
    return new immLLogOper(_leaf->get_long() );
  case IMML_32BITS:
    return new immL_32bitsOper(_leaf->get_long() );
  case IMMP:
    return new immPOper(_leaf->bottom_type()->is_ptr() );
  case IMMP0:
    return new immP0Oper(_leaf->bottom_type()->is_ptr() );
  case IMMP_1:
    return new immP_1Oper(_leaf->bottom_type()->is_ptr() );
  case IMMBYTEMAPBASE:
    return new immByteMapBaseOper(_leaf->bottom_type()->is_ptr() );
  case IMMD:
    return new immDOper(_leaf->getd() );
  case IMMD0:
    return new immD0Oper(_leaf->getd() );
  case IMMDPACKED:
    return new immDPackedOper(_leaf->getd() );
  case IMMF:
    return new immFOper(_leaf->getf() );
  case IMMF0:
    return new immF0Oper(_leaf->getf() );
  case IMMFPACKED:
    return new immFPackedOper(_leaf->getf() );
  case IMMN:
    return new immNOper(_leaf->bottom_type()->is_narrowoop() );
  case IMMN0:
    return new immN0Oper(_leaf->bottom_type()->is_narrowoop() );
  case IMMNKLASS:
    return new immNKlassOper(_leaf->bottom_type()->is_narrowklass() );
  case IREGI:
    return new iRegIOper( );
  case IREGINOSP:
    return new iRegINoSpOper( );
  case IREGL:
    return new iRegLOper( );
  case IREGLNOSP:
    return new iRegLNoSpOper( );
  case IREGP:
    return new iRegPOper( );
  case IREGPNOSP:
    return new iRegPNoSpOper( );
  case IREGP_R0:
    return new iRegP_R0Oper( );
  case IREGP_R1:
    return new iRegP_R1Oper( );
  case IREGP_R2:
    return new iRegP_R2Oper( );
  case IREGP_R3:
    return new iRegP_R3Oper( );
  case IREGP_R4:
    return new iRegP_R4Oper( );
  case IREGP_R5:
    return new iRegP_R5Oper( );
  case IREGP_R10:
    return new iRegP_R10Oper( );
  case IREGL_R0:
    return new iRegL_R0Oper( );
  case IREGL_R11:
    return new iRegL_R11Oper( );
  case IREGI_R0:
    return new iRegI_R0Oper( );
  case IREGI_R2:
    return new iRegI_R2Oper( );
  case IREGI_R3:
    return new iRegI_R3Oper( );
  case IREGI_R4:
    return new iRegI_R4Oper( );
  case IREGN:
    return new iRegNOper( );
  case IREGNNOSP:
    return new iRegNNoSpOper( );
  case VREGF:
    return new vRegFOper( );
  case VREGD:
    return new vRegDOper( );
  case VREG:
    return new vRegOper( );
  case VECA:
    return new vecAOper( );
  case VECD:
    return new vecDOper( );
  case VECX:
    return new vecXOper( );
  case VREGD_V0:
    return new vRegD_V0Oper( );
  case VREGD_V1:
    return new vRegD_V1Oper( );
  case VREGD_V2:
    return new vRegD_V2Oper( );
  case VREGD_V3:
    return new vRegD_V3Oper( );
  case VREGD_V4:
    return new vRegD_V4Oper( );
  case VREGD_V5:
    return new vRegD_V5Oper( );
  case VREGD_V6:
    return new vRegD_V6Oper( );
  case VREGD_V7:
    return new vRegD_V7Oper( );
  case PREG:
    return new pRegOper( );
  case PREGGOV:
    return new pRegGovOper( );
  case PREGGOV_P0:
    return new pRegGov_P0Oper( );
  case PREGGOV_P1:
    return new pRegGov_P1Oper( );
  case RFLAGSREG:
    return new rFlagsRegOper( );
  case RFLAGSREGU:
    return new rFlagsRegUOper( );
  case INLINE_CACHE_REGP:
    return new inline_cache_RegPOper( );
  case THREAD_REGP:
    return new thread_RegPOper( );
  case INDIRECT:
    return new indirectOper( );
  case INDINDEXSCALEDI2L:
    return new indIndexScaledI2LOper(_kids[1]->_kids[1]->_leaf->get_int() );
  case INDINDEXSCALED:
    return new indIndexScaledOper(_kids[1]->_kids[1]->_leaf->get_int() );
  case INDINDEXI2L:
    return new indIndexI2LOper( );
  case INDINDEX:
    return new indIndexOper( );
  case INDOFFI1:
    return new indOffI1Oper(_kids[1]->_leaf->get_int() );
  case INDOFFI2:
    return new indOffI2Oper(_kids[1]->_leaf->get_int() );
  case INDOFFI4:
    return new indOffI4Oper(_kids[1]->_leaf->get_int() );
  case INDOFFI8:
    return new indOffI8Oper(_kids[1]->_leaf->get_int() );
  case INDOFFI16:
    return new indOffI16Oper(_kids[1]->_leaf->get_int() );
  case INDOFFL1:
    return new indOffL1Oper(_kids[1]->_leaf->get_long() );
  case INDOFFL2:
    return new indOffL2Oper(_kids[1]->_leaf->get_long() );
  case INDOFFL4:
    return new indOffL4Oper(_kids[1]->_leaf->get_long() );
  case INDOFFL8:
    return new indOffL8Oper(_kids[1]->_leaf->get_long() );
  case INDOFFL16:
    return new indOffL16Oper(_kids[1]->_leaf->get_long() );
  case INDIRECTN:
    return new indirectNOper( );
  case INDINDEXSCALEDI2LN:
    return new indIndexScaledI2LNOper(_kids[1]->_kids[1]->_leaf->get_int() );
  case INDINDEXSCALEDN:
    return new indIndexScaledNOper(_kids[1]->_kids[1]->_leaf->get_int() );
  case INDINDEXI2LN:
    return new indIndexI2LNOper( );
  case INDINDEXN:
    return new indIndexNOper( );
  case INDOFFIN:
    return new indOffINOper(_kids[1]->_leaf->get_int() );
  case INDOFFLN:
    return new indOffLNOper(_kids[1]->_leaf->get_long() );
  case STACKSLOTP:
    return new stackSlotPOper( );
  case STACKSLOTI:
    return new stackSlotIOper( );
  case STACKSLOTF:
    return new stackSlotFOper( );
  case STACKSLOTD:
    return new stackSlotDOper( );
  case STACKSLOTL:
    return new stackSlotLOper( );
  case CMPOP:
    return new cmpOpOper(_leaf->as_Bool()->_test._test );
  case CMPOPU:
    return new cmpOpUOper(_leaf->as_Bool()->_test._test );
  case CMPOPEQNE:
    return new cmpOpEqNeOper(_leaf->as_Bool()->_test._test );
  case CMPOPLTGE:
    return new cmpOpLtGeOper(_leaf->as_Bool()->_test._test );
  case CMPOPUEQNELTGE:
    return new cmpOpUEqNeLtGeOper(_leaf->as_Bool()->_test._test );
  case IREGL2I:
    return new iRegL2IOper( );
  case VMEMA_IMMIOFFSET4:
    return new vmemA_immIOffset4Oper(_leaf->get_int() );
  case VMEMA_IMMLOFFSET4:
    return new vmemA_immLOffset4Oper(_leaf->get_long() );
  case VMEMA_INDOFFI4:
    return new vmemA_indOffI4Oper(_kids[1]->_leaf->get_int() );
  case VMEMA_INDOFFL4:
    return new vmemA_indOffL4Oper(_kids[1]->_leaf->get_long() );
  case _CONVI2L_IREGI_:    return nullptr;
  case _LSHIFTL__CONVI2L_IREGI__IMMISCALE:    return nullptr;
  case _LSHIFTL_IREGL_IMMISCALE:    return nullptr;
  case _DECODEN_IREGN_:    return nullptr;
  case _LOADB_MEMORY1_:    return nullptr;
  case _LOADUB_MEMORY1_:    return nullptr;
  case _LOADS_MEMORY2_:    return nullptr;
  case _LOADUS_MEMORY2_:    return nullptr;
  case _LOADI_MEMORY4_:    return nullptr;
  case _CONVI2L__LOADI_MEMORY4__:    return nullptr;
  case _LOADB_INDIRECT_:    return nullptr;
  case _LOADUB_INDIRECT_:    return nullptr;
  case _LOADUS_INDIRECT_:    return nullptr;
  case _LOADS_INDIRECT_:    return nullptr;
  case _LOADI_INDIRECT_:    return nullptr;
  case _CONVI2L__LOADI_INDIRECT__:    return nullptr;
  case _LOADL_MEMORY8_:    return nullptr;
  case _CASTP2X_IREGP_:    return nullptr;
  case _CASTP2X__DECODEN_IREGN__:    return nullptr;
  case _BINARY_IREGINOSP_IREGINOSP:    return nullptr;
  case _BINARY_IREGLNOSP_IREGLNOSP:    return nullptr;
  case _BINARY_IREGP_IREGP:    return nullptr;
  case _BINARY_IREGNNOSP_IREGNNOSP:    return nullptr;
  case _BINARY_IREGI_IREGI:    return nullptr;
  case _BINARY_IREGL_IREGL:    return nullptr;
  case _BINARY_IREGN_IREGN:    return nullptr;
  case _BINARY_CMPOP_RFLAGSREG:    return nullptr;
  case _BINARY_IREGIORL2I_IREGIORL2I:    return nullptr;
  case _BINARY_CMPOPU_RFLAGSREGU:    return nullptr;
  case _BINARY_IMMI0_IREGIORL2I:    return nullptr;
  case _BINARY_IREGIORL2I_IMMI0:    return nullptr;
  case _BINARY_IMMI_1_IMMI0:    return nullptr;
  case _BINARY_IREGL_IMML0:    return nullptr;
  case _BINARY_IMML0_IREGL:    return nullptr;
  case _BINARY_IREGP_IMMP0:    return nullptr;
  case _BINARY_IMMP0_IREGP:    return nullptr;
  case _BINARY_IREGN_IMMN0:    return nullptr;
  case _BINARY_IMMN0_IREGN:    return nullptr;
  case _BINARY_VREGF_VREGF:    return nullptr;
  case _BINARY_VREGD_VREGD:    return nullptr;
  case _CONVL2I_IREGL_:    return nullptr;
  case _CONVI2L_IREGIORL2I_:    return nullptr;
  case _LSHIFTL__CONVI2L_IREGIORL2I__IMMISCALE:    return nullptr;
  case _MULI_IREGIORL2I_IREGIORL2I:    return nullptr;
  case _SUBI_IMMI0_IREGIORL2I:    return nullptr;
  case _MULL_IREGL_IREGL:    return nullptr;
  case _SUBL_IMML0_IREGL:    return nullptr;
  case _MULL__CONVI2L_IREGIORL2I___CONVI2L_IREGIORL2I_:    return nullptr;
  case _SUBL_IMML0__CONVI2L_IREGIORL2I_:    return nullptr;
  case _URSHIFTI_IREGIORL2I_IMMI:    return nullptr;
  case _RSHIFTI_IREGIORL2I_IMMI:    return nullptr;
  case _LSHIFTI_IREGIORL2I_IMMI:    return nullptr;
  case _URSHIFTL_IREGL_IMMI:    return nullptr;
  case _RSHIFTL_IREGL_IMMI:    return nullptr;
  case _LSHIFTL_IREGL_IMMI:    return nullptr;
  case _XORI_IREGIORL2I_IMMI_M1:    return nullptr;
  case _XORL_IREGL_IMML_M1:    return nullptr;
  case _XORI_IREGIORL2I_IREGIORL2I:    return nullptr;
  case _XORL_IREGL_IREGL:    return nullptr;
  case _XORI__URSHIFTI_IREGIORL2I_IMMI_IMMI_M1:    return nullptr;
  case _XORL__URSHIFTL_IREGL_IMMI_IMML_M1:    return nullptr;
  case _XORI__RSHIFTI_IREGIORL2I_IMMI_IMMI_M1:    return nullptr;
  case _XORL__RSHIFTL_IREGL_IMMI_IMML_M1:    return nullptr;
  case _ROTATERIGHT_IREGIORL2I_IMMI:    return nullptr;
  case _XORI__ROTATERIGHT_IREGIORL2I_IMMI_IMMI_M1:    return nullptr;
  case _ROTATERIGHT_IREGL_IMMI:    return nullptr;
  case _XORL__ROTATERIGHT_IREGL_IMMI_IMML_M1:    return nullptr;
  case _XORI__LSHIFTI_IREGIORL2I_IMMI_IMMI_M1:    return nullptr;
  case _XORL__LSHIFTL_IREGL_IMMI_IMML_M1:    return nullptr;
  case _XORI__URSHIFTI_IREGIORL2I_IMMI_IREGIORL2I:    return nullptr;
  case _XORI_IREGIORL2I__URSHIFTI_IREGIORL2I_IMMI:    return nullptr;
  case _XORL__URSHIFTL_IREGL_IMMI_IREGL:    return nullptr;
  case _XORL_IREGL__URSHIFTL_IREGL_IMMI:    return nullptr;
  case _XORI__RSHIFTI_IREGIORL2I_IMMI_IREGIORL2I:    return nullptr;
  case _XORI_IREGIORL2I__RSHIFTI_IREGIORL2I_IMMI:    return nullptr;
  case _XORL__RSHIFTL_IREGL_IMMI_IREGL:    return nullptr;
  case _XORL_IREGL__RSHIFTL_IREGL_IMMI:    return nullptr;
  case _XORI__ROTATERIGHT_IREGIORL2I_IMMI_IREGIORL2I:    return nullptr;
  case _XORI_IREGIORL2I__ROTATERIGHT_IREGIORL2I_IMMI:    return nullptr;
  case _XORL__ROTATERIGHT_IREGL_IMMI_IREGL:    return nullptr;
  case _XORL_IREGL__ROTATERIGHT_IREGL_IMMI:    return nullptr;
  case _XORI__LSHIFTI_IREGIORL2I_IMMI_IREGIORL2I:    return nullptr;
  case _XORI_IREGIORL2I__LSHIFTI_IREGIORL2I_IMMI:    return nullptr;
  case _XORL__LSHIFTL_IREGL_IMMI_IREGL:    return nullptr;
  case _XORL_IREGL__LSHIFTL_IREGL_IMMI:    return nullptr;
  case _ANDI__URSHIFTI_IREGIORL2I_IMMI_IMMI_BITMASK:    return nullptr;
  case _ANDI_IREGIORL2I_IMMI_BITMASK:    return nullptr;
  case _ANDL_IREGL_IMML_BITMASK:    return nullptr;
  case _LSHIFTI__ANDI_IREGIORL2I_IMMI_BITMASK_IMMI:    return nullptr;
  case _ANDL_IREGL_IMML_POSITIVE_BITMASKI:    return nullptr;
  case _LSHIFTL__ANDL_IREGL_IMML_POSITIVE_BITMASKI_IMMI:    return nullptr;
  case _CONVI2L__ANDI_IREGIORL2I_IMMI_BITMASK_:    return nullptr;
  case _CONVL2I__ANDL_IREGL_IMML_POSITIVE_BITMASKI_:    return nullptr;
  case _ANDI_IREGI_IMMI_BITMASK:    return nullptr;
  case _LSHIFTI_IREGIORL2I_IMMI_16:    return nullptr;
  case _RSHIFTI__LSHIFTI_IREGIORL2I_IMMI_16_IMMI_16:    return nullptr;
  case _LSHIFTI_IREGIORL2I_IMMI_24:    return nullptr;
  case _RSHIFTI__LSHIFTI_IREGIORL2I_IMMI_24_IMMI_24:    return nullptr;
  case _URSHIFTI__LSHIFTI_IREGIORL2I_IMMI_24_IMMI_24:    return nullptr;
  case _LSHIFTL_IREGL_IMMI_48:    return nullptr;
  case _RSHIFTL__LSHIFTL_IREGL_IMMI_48_IMMI_48:    return nullptr;
  case _LSHIFTL_IREGL_IMMI_32:    return nullptr;
  case _RSHIFTL__LSHIFTL_IREGL_IMMI_32_IMMI_32:    return nullptr;
  case _LSHIFTL_IREGL_IMMI_56:    return nullptr;
  case _RSHIFTL__LSHIFTL_IREGL_IMMI_56_IMMI_56:    return nullptr;
  case _URSHIFTL__LSHIFTL_IREGL_IMMI_56_IMMI_56:    return nullptr;
  case _ANDI_IREGIORL2I_IMMI_255:    return nullptr;
  case _ANDI_IREGIORL2I_IMMI_65535:    return nullptr;
  case _ANDL_IREGL_IMML_255:    return nullptr;
  case _ANDL_IREGL_IMML_65535:    return nullptr;
  case _ANDL_IREGL_IMML_4294967295:    return nullptr;
  case _LSHIFTL__RSHIFTL__LSHIFTL_IREGL_IMMI_56_IMMI_56_IMMIEXT:    return nullptr;
  case _LSHIFTL__RSHIFTL__LSHIFTL_IREGL_IMMI_48_IMMI_48_IMMIEXT:    return nullptr;
  case _LSHIFTL__RSHIFTL__LSHIFTL_IREGL_IMMI_32_IMMI_32_IMMIEXT:    return nullptr;
  case _LSHIFTI__RSHIFTI__LSHIFTI_IREGIORL2I_IMMI_24_IMMI_24_IMMIEXT:    return nullptr;
  case _LSHIFTI__RSHIFTI__LSHIFTI_IREGIORL2I_IMMI_16_IMMI_16_IMMIEXT:    return nullptr;
  case _LSHIFTL__CONVI2L_IREGIORL2I__IMMIEXT:    return nullptr;
  case _LSHIFTL__ANDL_IREGL_IMML_255_IMMIEXT:    return nullptr;
  case _LSHIFTL__ANDL_IREGL_IMML_65535_IMMIEXT:    return nullptr;
  case _LSHIFTL__ANDL_IREGL_IMML_4294967295_IMMIEXT:    return nullptr;
  case _LSHIFTI__ANDI_IREGIORL2I_IMMI_255_IMMIEXT:    return nullptr;
  case _LSHIFTI__ANDI_IREGIORL2I_IMMI_65535_IMMIEXT:    return nullptr;
  case _NEGF_VREGF_:    return nullptr;
  case _BINARY_VREGF__NEGF_VREGF_:    return nullptr;
  case _NEGD_VREGD_:    return nullptr;
  case _BINARY_VREGD__NEGD_VREGD_:    return nullptr;
  case _SUBF_VREGF_VREGF:    return nullptr;
  case _SUBD_VREGD_VREGD:    return nullptr;
  case _OVERFLOWMULI_IREGIORL2I_IREGIORL2I:    return nullptr;
  case _OVERFLOWMULL_IREGL_IREGL:    return nullptr;
  case _CMPI_IREGIORL2I_IMMI0:    return nullptr;
  case _CMPL_IREGL_IMML0:    return nullptr;
  case _CMPP_IREGP_IMMP0:    return nullptr;
  case _CMPN_IREGN_IMMN0:    return nullptr;
  case _CMPP__DECODEN_IREGN__IMMP0:    return nullptr;
  case _CMPU_IREGIORL2I_IMMI0:    return nullptr;
  case _CMPUL_IREGL_IMML0:    return nullptr;
  case _ANDL_IREGL_IMML:    return nullptr;
  case _CMPL__ANDL_IREGL_IMML_IMML0:    return nullptr;
  case _ANDI_IREGIORL2I_IMMI:    return nullptr;
  case _CMPI__ANDI_IREGIORL2I_IMMI_IMMI0:    return nullptr;
  case _ANDL_IREGL_IREGL:    return nullptr;
  case _ANDI_IREGIORL2I_IREGIORL2I:    return nullptr;
  case _PARTIALSUBTYPECHECK_IREGP_R4_IREGP_R0:    return nullptr;
  case _BINARY_IREGP_R1_IREGI_R2:    return nullptr;
  case _BINARY_IREGP_R3_IREGI_R4:    return nullptr;
  case _BINARY_IREGP_R1_IREGI_R4:    return nullptr;
  case _BINARY_IREGP_R3_IREGI_R2:    return nullptr;
  case _BINARY_IREGP_R3_IMMI_LE_4:    return nullptr;
  case _BINARY_IREGP_R3_IMMI_1:    return nullptr;
  case _BINARY_IREGP_R1_IREGP_R3:    return nullptr;
  case _BINARY_IREGP_R1_IREGI_R3:    return nullptr;
  case _BINARY_VREG_PREGGOV:    return nullptr;
  case _BINARY_VREG_VREG:    return nullptr;
  case _REPLICATE_IMMBADDSUBV_:    return nullptr;
  case _REPLICATE_IMMIADDSUBV_:    return nullptr;
  case _REPLICATE_IMMLADDSUBV_:    return nullptr;
  case _REPLICATE_IMMBLOG_:    return nullptr;
  case _REPLICATE_IMMSLOG_:    return nullptr;
  case _REPLICATE_IMMILOG_:    return nullptr;
  case _REPLICATE_IMMLLOG_:    return nullptr;
  case _XORV_VREG_VREG:    return nullptr;
  case _REPLICATE_IMMI_M1_:    return nullptr;
  case _REPLICATE_IMML_M1_:    return nullptr;
  case _BINARY_VREG__REPLICATE_IMMI_M1_:    return nullptr;
  case _BINARY_VREG__REPLICATE_IMML_M1_:    return nullptr;
  case _XORV_VREG__REPLICATE_IMMI_M1_:    return nullptr;
  case _XORV__REPLICATE_IMMI_M1__VREG:    return nullptr;
  case _XORV_VREG__REPLICATE_IMML_M1_:    return nullptr;
  case _XORV__REPLICATE_IMML_M1__VREG:    return nullptr;
  case _BINARY_VREG__XORV_VREG__REPLICATE_IMMI_M1_:    return nullptr;
  case _BINARY_VREG__XORV__REPLICATE_IMMI_M1__VREG:    return nullptr;
  case _BINARY_VREG__XORV_VREG__REPLICATE_IMML_M1_:    return nullptr;
  case _BINARY_VREG__XORV__REPLICATE_IMML_M1__VREG:    return nullptr;
  case _SUBVF_VREG_VREG:    return nullptr;
  case _SUBVD_VREG_VREG:    return nullptr;
  case _SUBVF__BINARY_VREG_VREG_PREGGOV:    return nullptr;
  case _SUBVD__BINARY_VREG_VREG_PREGGOV:    return nullptr;
  case _MULVB_VREG_VREG:    return nullptr;
  case _MULVS_VREG_VREG:    return nullptr;
  case _MULVI_VREG_VREG:    return nullptr;
  case _MULVL_VREG_VREG:    return nullptr;
  case _BINARY_VREG__MULVB_VREG_VREG:    return nullptr;
  case _BINARY_VREG__MULVS_VREG_VREG:    return nullptr;
  case _BINARY_VREG__MULVI_VREG_VREG:    return nullptr;
  case _BINARY_VREG__MULVL_VREG_VREG:    return nullptr;
  case _NEGVF_VREG_:    return nullptr;
  case _BINARY_VREG__NEGVF_VREG_:    return nullptr;
  case _NEGVD_VREG_:    return nullptr;
  case _BINARY_VREG__NEGVD_VREG_:    return nullptr;
  case _BINARY__NEGVF_VREG__PREGGOV:    return nullptr;
  case _BINARY__NEGVD_VREG__PREGGOV:    return nullptr;
  case _LSHIFTCNTV_IMMI_:    return nullptr;
  case _RSHIFTCNTV_IMMI_POSITIVE_:    return nullptr;
  case _RSHIFTVB_VREG__RSHIFTCNTV_IMMI_POSITIVE_:    return nullptr;
  case _RSHIFTVS_VREG__RSHIFTCNTV_IMMI_POSITIVE_:    return nullptr;
  case _RSHIFTVI_VREG__RSHIFTCNTV_IMMI_POSITIVE_:    return nullptr;
  case _RSHIFTVL_VREG__RSHIFTCNTV_IMMI_POSITIVE_:    return nullptr;
  case _URSHIFTVB_VREG__RSHIFTCNTV_IMMI_POSITIVE_:    return nullptr;
  case _URSHIFTVS_VREG__RSHIFTCNTV_IMMI_POSITIVE_:    return nullptr;
  case _URSHIFTVI_VREG__RSHIFTCNTV_IMMI_POSITIVE_:    return nullptr;
  case _URSHIFTVL_VREG__RSHIFTCNTV_IMMI_POSITIVE_:    return nullptr;
  case _BINARY_VREG__LSHIFTCNTV_IMMI_:    return nullptr;
  case _BINARY_VREG__RSHIFTCNTV_IMMI_POSITIVE_:    return nullptr;
  case _BINARY_IREGIORL2I_VREG:    return nullptr;
  case _BINARY_IREGL_VREG:    return nullptr;
  case _BINARY_VREGF_VREG:    return nullptr;
  case _BINARY_VREGD_VREG:    return nullptr;
  case _BINARY_VREG_IREGIORL2I:    return nullptr;
  case _BINARY_VREG_IREGL:    return nullptr;
  case _BINARY_VREG_VREGF:    return nullptr;
  case _BINARY_VREG_VREGD:    return nullptr;
  case _LOADVECTOR_INDIRECT_:    return nullptr;
  case _LOADVECTORMASKED_VMEMA_PREGGOV:    return nullptr;
  case _VECTORSTOREMASK_PREG_IMMI_GT_1:    return nullptr;
  case _BINARY__VECTORSTOREMASK_PREG_IMMI_GT_1_PREGGOV:    return nullptr;
  case _MASKALL_IMMI_M1_:    return nullptr;
  case _XORVMASK_PREG__MASKALL_IMMI_M1_:    return nullptr;
  case _MASKALL_IMML_M1_:    return nullptr;
  case _XORVMASK_PREG__MASKALL_IMML_M1_:    return nullptr;
  case _REPLICATE_IMMI0_:    return nullptr;
  case _BINARY_VREG__REPLICATE_IMMI0_:    return nullptr;
  case _REPLICATE_IMML0_:    return nullptr;
  case _BINARY_VREG__REPLICATE_IMML0_:    return nullptr;
  case _REPLICATE_IMMF0_:    return nullptr;
  case _BINARY_VREG__REPLICATE_IMMF0_:    return nullptr;
  case _REPLICATE_IMMD0_:    return nullptr;
  case _BINARY_VREG__REPLICATE_IMMD0_:    return nullptr;
  case _REPLICATE_IMMI5_:    return nullptr;
  case _BINARY_VREG__REPLICATE_IMMI5_:    return nullptr;
  case _REPLICATE_IMMIU7_:    return nullptr;
  case _BINARY_VREG__REPLICATE_IMMIU7_:    return nullptr;
  case _REPLICATE_IMML5_:    return nullptr;
  case _BINARY_VREG__REPLICATE_IMML5_:    return nullptr;
  case _REPLICATE_IMMLU7_:    return nullptr;
  case _BINARY_VREG__REPLICATE_IMMLU7_:    return nullptr;
  case _BINARY_IMMI_PREGGOV:    return nullptr;
  case _VECTORSTOREMASK_VREG_IMMI_GT_1:    return nullptr;
  case _SUBL_IREGL_IREGL:    return nullptr;
  case _BINARY_VREG__BINARY_VREG_PREGGOV:    return nullptr;
  
  default:
    fprintf(stderr, "Default MachOper Generator invoked for: \n");
    fprintf(stderr, "   opcode = %d\n", opcode);
    break;
  }
  return nullptr;
};


//------------------------- MachNode Generator ---------------
// A switch statement on the dense-packed user-defined type system
// that invokes 'new' on the corresponding class constructor.

MachNode *State::MachNodeGenerator(int opcode){
  switch(opcode) {
  case loadB_rule: {
      loadBNode *node = new loadBNode();
      return node;
    }
  case loadB2L_rule: {
      loadB2LNode *node = new loadB2LNode();
      return node;
    }
  case loadUB_rule: {
      loadUBNode *node = new loadUBNode();
      return node;
    }
  case loadUB2L_rule: {
      loadUB2LNode *node = new loadUB2LNode();
      return node;
    }
  case loadS_rule: {
      loadSNode *node = new loadSNode();
      return node;
    }
  case loadS2L_rule: {
      loadS2LNode *node = new loadS2LNode();
      return node;
    }
  case loadUS_rule: {
      loadUSNode *node = new loadUSNode();
      return node;
    }
  case loadUS2L_rule: {
      loadUS2LNode *node = new loadUS2LNode();
      return node;
    }
  case loadI_rule: {
      loadINode *node = new loadINode();
      return node;
    }
  case loadI2L_rule: {
      loadI2LNode *node = new loadI2LNode();
      return node;
    }
  case loadUI2L_rule: {
      loadUI2LNode *node = new loadUI2LNode();
      return node;
    }
  case loadL_rule: {
      loadLNode *node = new loadLNode();
      return node;
    }
  case loadRange_rule: {
      loadRangeNode *node = new loadRangeNode();
      return node;
    }
  case loadP_rule: {
      loadPNode *node = new loadPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadN_rule: {
      loadNNode *node = new loadNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadKlass_rule: {
      loadKlassNode *node = new loadKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadNKlass_rule: {
      loadNKlassNode *node = new loadNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadF_rule: {
      loadFNode *node = new loadFNode();
      return node;
    }
  case loadD_rule: {
      loadDNode *node = new loadDNode();
      return node;
    }
  case loadConI_rule: {
      loadConINode *node = new loadConINode();
      node->_opnd_array[1] = new immIOper(_leaf->get_int() );
      return node;
    }
  case loadConL_rule: {
      loadConLNode *node = new loadConLNode();
      node->_opnd_array[1] = new immLOper(_leaf->get_long() );
      return node;
    }
  case loadConP_rule: {
      loadConPNode *node = new loadConPNode();
      node->_opnd_array[1] = new immPOper(_leaf->bottom_type()->is_ptr() );
      return node;
    }
  case loadConP0_rule: {
      loadConP0Node *node = new loadConP0Node();
      node->_opnd_array[1] = new immP0Oper(_leaf->bottom_type()->is_ptr() );
      return node;
    }
  case loadConP1_rule: {
      loadConP1Node *node = new loadConP1Node();
      node->_opnd_array[1] = new immP_1Oper(_leaf->bottom_type()->is_ptr() );
      return node;
    }
  case loadByteMapBase_rule: {
      loadByteMapBaseNode *node = new loadByteMapBaseNode();
      node->_opnd_array[1] = new immByteMapBaseOper(_leaf->bottom_type()->is_ptr() );
      return node;
    }
  case loadConN_rule: {
      loadConNNode *node = new loadConNNode();
      node->_opnd_array[1] = new immNOper(_leaf->bottom_type()->is_narrowoop() );
      return node;
    }
  case loadConN0_rule: {
      loadConN0Node *node = new loadConN0Node();
      node->_opnd_array[1] = new immN0Oper(_leaf->bottom_type()->is_narrowoop() );
      return node;
    }
  case loadConNKlass_rule: {
      loadConNKlassNode *node = new loadConNKlassNode();
      node->_opnd_array[1] = new immNKlassOper(_leaf->bottom_type()->is_narrowklass() );
      return node;
    }
  case loadConF_packed_rule: {
      loadConF_packedNode *node = new loadConF_packedNode();
      node->_opnd_array[1] = new immFPackedOper(_leaf->getf() );
      return node;
    }
  case loadConF_rule: {
      loadConFNode *node = new loadConFNode();
      node->_opnd_array[1] = new immFOper(_leaf->getf() );
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConD_packed_rule: {
      loadConD_packedNode *node = new loadConD_packedNode();
      node->_opnd_array[1] = new immDPackedOper(_leaf->getd() );
      return node;
    }
  case loadConD_rule: {
      loadConDNode *node = new loadConDNode();
      node->_opnd_array[1] = new immDOper(_leaf->getd() );
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmCM0_rule: {
      storeimmCM0Node *node = new storeimmCM0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmCM0_ordered_rule: {
      storeimmCM0_orderedNode *node = new storeimmCM0_orderedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeB_rule: {
      storeBNode *node = new storeBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmB0_rule: {
      storeimmB0Node *node = new storeimmB0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeC_rule: {
      storeCNode *node = new storeCNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmC0_rule: {
      storeimmC0Node *node = new storeimmC0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeI_rule: {
      storeINode *node = new storeINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmI0_rule: {
      storeimmI0Node *node = new storeimmI0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeL_rule: {
      storeLNode *node = new storeLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmL0_rule: {
      storeimmL0Node *node = new storeimmL0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeP_rule: {
      storePNode *node = new storePNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmP0_rule: {
      storeimmP0Node *node = new storeimmP0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeN_rule: {
      storeNNode *node = new storeNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmN0_rule: {
      storeImmN0Node *node = new storeImmN0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeF_rule: {
      storeFNode *node = new storeFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeD_rule: {
      storeDNode *node = new storeDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeNKlass_rule: {
      storeNKlassNode *node = new storeNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case prefetchalloc_rule: {
      prefetchallocNode *node = new prefetchallocNode();
      return node;
    }
  case loadB_volatile_rule: {
      loadB_volatileNode *node = new loadB_volatileNode();
      return node;
    }
  case loadB2L_volatile_rule: {
      loadB2L_volatileNode *node = new loadB2L_volatileNode();
      return node;
    }
  case loadUB_volatile_rule: {
      loadUB_volatileNode *node = new loadUB_volatileNode();
      return node;
    }
  case loadUB2L_volatile_rule: {
      loadUB2L_volatileNode *node = new loadUB2L_volatileNode();
      return node;
    }
  case loadS_volatile_rule: {
      loadS_volatileNode *node = new loadS_volatileNode();
      return node;
    }
  case loadUS_volatile_rule: {
      loadUS_volatileNode *node = new loadUS_volatileNode();
      return node;
    }
  case loadUS2L_volatile_rule: {
      loadUS2L_volatileNode *node = new loadUS2L_volatileNode();
      return node;
    }
  case loadS2L_volatile_rule: {
      loadS2L_volatileNode *node = new loadS2L_volatileNode();
      return node;
    }
  case loadI_volatile_rule: {
      loadI_volatileNode *node = new loadI_volatileNode();
      return node;
    }
  case loadUI2L_volatile_rule: {
      loadUI2L_volatileNode *node = new loadUI2L_volatileNode();
      return node;
    }
  case loadL_volatile_rule: {
      loadL_volatileNode *node = new loadL_volatileNode();
      return node;
    }
  case loadP_volatile_rule: {
      loadP_volatileNode *node = new loadP_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadN_volatile_rule: {
      loadN_volatileNode *node = new loadN_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadF_volatile_rule: {
      loadF_volatileNode *node = new loadF_volatileNode();
      return node;
    }
  case loadD_volatile_rule: {
      loadD_volatileNode *node = new loadD_volatileNode();
      return node;
    }
  case storeB_volatile_rule: {
      storeB_volatileNode *node = new storeB_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmB0_volatile_rule: {
      storeimmB0_volatileNode *node = new storeimmB0_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeC_volatile_rule: {
      storeC_volatileNode *node = new storeC_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmC0_volatile_rule: {
      storeimmC0_volatileNode *node = new storeimmC0_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeI_volatile_rule: {
      storeI_volatileNode *node = new storeI_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmI0_volatile_rule: {
      storeimmI0_volatileNode *node = new storeimmI0_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeL_volatile_rule: {
      storeL_volatileNode *node = new storeL_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmL0_volatile_rule: {
      storeimmL0_volatileNode *node = new storeimmL0_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeP_volatile_rule: {
      storeP_volatileNode *node = new storeP_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmP0_volatile_rule: {
      storeimmP0_volatileNode *node = new storeimmP0_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeN_volatile_rule: {
      storeN_volatileNode *node = new storeN_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeimmN0_volatile_rule: {
      storeimmN0_volatileNode *node = new storeimmN0_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeF_volatile_rule: {
      storeF_volatileNode *node = new storeF_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeD_volatile_rule: {
      storeD_volatileNode *node = new storeD_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cacheWB_rule: {
      cacheWBNode *node = new cacheWBNode();
      return node;
    }
  case cacheWBPreSync_rule: {
      cacheWBPreSyncNode *node = new cacheWBPreSyncNode();
      return node;
    }
  case cacheWBPostSync_rule: {
      cacheWBPostSyncNode *node = new cacheWBPostSyncNode();
      return node;
    }
  case bytes_reverse_int_rule: {
      bytes_reverse_intNode *node = new bytes_reverse_intNode();
      return node;
    }
  case bytes_reverse_long_rule: {
      bytes_reverse_longNode *node = new bytes_reverse_longNode();
      return node;
    }
  case bytes_reverse_unsigned_short_rule: {
      bytes_reverse_unsigned_shortNode *node = new bytes_reverse_unsigned_shortNode();
      return node;
    }
  case bytes_reverse_short_rule: {
      bytes_reverse_shortNode *node = new bytes_reverse_shortNode();
      return node;
    }
  case countLeadingZerosI_rule: {
      countLeadingZerosINode *node = new countLeadingZerosINode();
      return node;
    }
  case countLeadingZerosL_rule: {
      countLeadingZerosLNode *node = new countLeadingZerosLNode();
      return node;
    }
  case countTrailingZerosI_rule: {
      countTrailingZerosINode *node = new countTrailingZerosINode();
      return node;
    }
  case countTrailingZerosL_rule: {
      countTrailingZerosLNode *node = new countTrailingZerosLNode();
      return node;
    }
  case popCountI_rule: {
      popCountINode *node = new popCountINode();
      node->set_opnd_array(2, MachOperGenerator(VREGF));
      return node;
    }
  case popCountI_mem_rule: {
      popCountI_memNode *node = new popCountI_memNode();
      node->set_opnd_array(2, MachOperGenerator(VREGF));
      return node;
    }
  case popCountL_rule: {
      popCountLNode *node = new popCountLNode();
      node->set_opnd_array(2, MachOperGenerator(VREGD));
      return node;
    }
  case popCountL_mem_rule: {
      popCountL_memNode *node = new popCountL_memNode();
      node->set_opnd_array(2, MachOperGenerator(VREGD));
      return node;
    }
  case verify_vector_alignment_rule: {
      verify_vector_alignmentNode *node = new verify_vector_alignmentNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case load_fence_rule: {
      load_fenceNode *node = new load_fenceNode();
      return node;
    }
  case unnecessary_membar_acquire_rule: {
      unnecessary_membar_acquireNode *node = new unnecessary_membar_acquireNode();
      return node;
    }
  case membar_acquire_rule: {
      membar_acquireNode *node = new membar_acquireNode();
      return node;
    }
  case membar_acquire_lock_rule: {
      membar_acquire_lockNode *node = new membar_acquire_lockNode();
      return node;
    }
  case store_fence_rule: {
      store_fenceNode *node = new store_fenceNode();
      return node;
    }
  case unnecessary_membar_release_rule: {
      unnecessary_membar_releaseNode *node = new unnecessary_membar_releaseNode();
      return node;
    }
  case membar_release_rule: {
      membar_releaseNode *node = new membar_releaseNode();
      return node;
    }
  case membar_storestore_rule: {
      membar_storestoreNode *node = new membar_storestoreNode();
      return node;
    }
  case membar_storestore_0_rule: {
      membar_storestore_0Node *node = new membar_storestore_0Node();
      return node;
    }
  case membar_release_lock_rule: {
      membar_release_lockNode *node = new membar_release_lockNode();
      return node;
    }
  case unnecessary_membar_volatile_rule: {
      unnecessary_membar_volatileNode *node = new unnecessary_membar_volatileNode();
      return node;
    }
  case membar_volatile_rule: {
      membar_volatileNode *node = new membar_volatileNode();
      return node;
    }
  case castX2P_rule: {
      castX2PNode *node = new castX2PNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castP2X_rule: {
      castP2XNode *node = new castP2XNode();
      return node;
    }
  case convP2I_rule: {
      convP2INode *node = new convP2INode();
      return node;
    }
  case convN2I_rule: {
      convN2INode *node = new convN2INode();
      return node;
    }
  case encodeHeapOop_rule: {
      encodeHeapOopNode *node = new encodeHeapOopNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeHeapOop_not_null_rule: {
      encodeHeapOop_not_nullNode *node = new encodeHeapOop_not_nullNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeHeapOop_rule: {
      decodeHeapOopNode *node = new decodeHeapOopNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeHeapOop_not_null_rule: {
      decodeHeapOop_not_nullNode *node = new decodeHeapOop_not_nullNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeKlass_not_null_rule: {
      encodeKlass_not_nullNode *node = new encodeKlass_not_nullNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeKlass_not_null_rule: {
      decodeKlass_not_nullNode *node = new decodeKlass_not_nullNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case checkCastPP_rule: {
      checkCastPPNode *node = new checkCastPPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castPP_rule: {
      castPPNode *node = new castPPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castII_rule: {
      castIINode *node = new castIINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castLL_rule: {
      castLLNode *node = new castLLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castFF_rule: {
      castFFNode *node = new castFFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castDD_rule: {
      castDDNode *node = new castDDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castVV_rule: {
      castVVNode *node = new castVVNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castVVMask_rule: {
      castVVMaskNode *node = new castVVMaskNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndSwapB_rule: {
      compareAndSwapBNode *node = new compareAndSwapBNode();
      return node;
    }
  case compareAndSwapS_rule: {
      compareAndSwapSNode *node = new compareAndSwapSNode();
      return node;
    }
  case compareAndSwapI_rule: {
      compareAndSwapINode *node = new compareAndSwapINode();
      return node;
    }
  case compareAndSwapL_rule: {
      compareAndSwapLNode *node = new compareAndSwapLNode();
      return node;
    }
  case compareAndSwapP_rule: {
      compareAndSwapPNode *node = new compareAndSwapPNode();
      return node;
    }
  case compareAndSwapN_rule: {
      compareAndSwapNNode *node = new compareAndSwapNNode();
      return node;
    }
  case compareAndSwapBAcq_rule: {
      compareAndSwapBAcqNode *node = new compareAndSwapBAcqNode();
      return node;
    }
  case compareAndSwapSAcq_rule: {
      compareAndSwapSAcqNode *node = new compareAndSwapSAcqNode();
      return node;
    }
  case compareAndSwapIAcq_rule: {
      compareAndSwapIAcqNode *node = new compareAndSwapIAcqNode();
      return node;
    }
  case compareAndSwapLAcq_rule: {
      compareAndSwapLAcqNode *node = new compareAndSwapLAcqNode();
      return node;
    }
  case compareAndSwapPAcq_rule: {
      compareAndSwapPAcqNode *node = new compareAndSwapPAcqNode();
      return node;
    }
  case compareAndSwapNAcq_rule: {
      compareAndSwapNAcqNode *node = new compareAndSwapNAcqNode();
      return node;
    }
  case compareAndExchangeB_rule: {
      compareAndExchangeBNode *node = new compareAndExchangeBNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case compareAndExchangeS_rule: {
      compareAndExchangeSNode *node = new compareAndExchangeSNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case compareAndExchangeI_rule: {
      compareAndExchangeINode *node = new compareAndExchangeINode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case compareAndExchangeL_rule: {
      compareAndExchangeLNode *node = new compareAndExchangeLNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      return node;
    }
  case compareAndExchangeN_rule: {
      compareAndExchangeNNode *node = new compareAndExchangeNNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeP_rule: {
      compareAndExchangePNode *node = new compareAndExchangePNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeBAcq_rule: {
      compareAndExchangeBAcqNode *node = new compareAndExchangeBAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case compareAndExchangeSAcq_rule: {
      compareAndExchangeSAcqNode *node = new compareAndExchangeSAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case compareAndExchangeIAcq_rule: {
      compareAndExchangeIAcqNode *node = new compareAndExchangeIAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case compareAndExchangeLAcq_rule: {
      compareAndExchangeLAcqNode *node = new compareAndExchangeLAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      return node;
    }
  case compareAndExchangeNAcq_rule: {
      compareAndExchangeNAcqNode *node = new compareAndExchangeNAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangePAcq_rule: {
      compareAndExchangePAcqNode *node = new compareAndExchangePAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case weakCompareAndSwapB_rule: {
      weakCompareAndSwapBNode *node = new weakCompareAndSwapBNode();
      return node;
    }
  case weakCompareAndSwapS_rule: {
      weakCompareAndSwapSNode *node = new weakCompareAndSwapSNode();
      return node;
    }
  case weakCompareAndSwapI_rule: {
      weakCompareAndSwapINode *node = new weakCompareAndSwapINode();
      return node;
    }
  case weakCompareAndSwapL_rule: {
      weakCompareAndSwapLNode *node = new weakCompareAndSwapLNode();
      return node;
    }
  case weakCompareAndSwapN_rule: {
      weakCompareAndSwapNNode *node = new weakCompareAndSwapNNode();
      return node;
    }
  case weakCompareAndSwapP_rule: {
      weakCompareAndSwapPNode *node = new weakCompareAndSwapPNode();
      return node;
    }
  case weakCompareAndSwapBAcq_rule: {
      weakCompareAndSwapBAcqNode *node = new weakCompareAndSwapBAcqNode();
      return node;
    }
  case weakCompareAndSwapSAcq_rule: {
      weakCompareAndSwapSAcqNode *node = new weakCompareAndSwapSAcqNode();
      return node;
    }
  case weakCompareAndSwapIAcq_rule: {
      weakCompareAndSwapIAcqNode *node = new weakCompareAndSwapIAcqNode();
      return node;
    }
  case weakCompareAndSwapLAcq_rule: {
      weakCompareAndSwapLAcqNode *node = new weakCompareAndSwapLAcqNode();
      return node;
    }
  case weakCompareAndSwapNAcq_rule: {
      weakCompareAndSwapNAcqNode *node = new weakCompareAndSwapNAcqNode();
      return node;
    }
  case weakCompareAndSwapPAcq_rule: {
      weakCompareAndSwapPAcqNode *node = new weakCompareAndSwapPAcqNode();
      return node;
    }
  case get_and_setI_rule: {
      get_and_setINode *node = new get_and_setINode();
      return node;
    }
  case get_and_setL_rule: {
      get_and_setLNode *node = new get_and_setLNode();
      return node;
    }
  case get_and_setN_rule: {
      get_and_setNNode *node = new get_and_setNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case get_and_setP_rule: {
      get_and_setPNode *node = new get_and_setPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case get_and_setIAcq_rule: {
      get_and_setIAcqNode *node = new get_and_setIAcqNode();
      return node;
    }
  case get_and_setLAcq_rule: {
      get_and_setLAcqNode *node = new get_and_setLAcqNode();
      return node;
    }
  case get_and_setNAcq_rule: {
      get_and_setNAcqNode *node = new get_and_setNAcqNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case get_and_setPAcq_rule: {
      get_and_setPAcqNode *node = new get_and_setPAcqNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case get_and_addL_rule: {
      get_and_addLNode *node = new get_and_addLNode();
      return node;
    }
  case get_and_addL_no_res_rule: {
      get_and_addL_no_resNode *node = new get_and_addL_no_resNode();
      return node;
    }
  case get_and_addLi_rule: {
      get_and_addLiNode *node = new get_and_addLiNode();
      return node;
    }
  case get_and_addLi_no_res_rule: {
      get_and_addLi_no_resNode *node = new get_and_addLi_no_resNode();
      return node;
    }
  case get_and_addI_rule: {
      get_and_addINode *node = new get_and_addINode();
      return node;
    }
  case get_and_addI_no_res_rule: {
      get_and_addI_no_resNode *node = new get_and_addI_no_resNode();
      return node;
    }
  case get_and_addIi_rule: {
      get_and_addIiNode *node = new get_and_addIiNode();
      return node;
    }
  case get_and_addIi_no_res_rule: {
      get_and_addIi_no_resNode *node = new get_and_addIi_no_resNode();
      return node;
    }
  case get_and_addLAcq_rule: {
      get_and_addLAcqNode *node = new get_and_addLAcqNode();
      return node;
    }
  case get_and_addL_no_resAcq_rule: {
      get_and_addL_no_resAcqNode *node = new get_and_addL_no_resAcqNode();
      return node;
    }
  case get_and_addLiAcq_rule: {
      get_and_addLiAcqNode *node = new get_and_addLiAcqNode();
      return node;
    }
  case get_and_addLi_no_resAcq_rule: {
      get_and_addLi_no_resAcqNode *node = new get_and_addLi_no_resAcqNode();
      return node;
    }
  case get_and_addIAcq_rule: {
      get_and_addIAcqNode *node = new get_and_addIAcqNode();
      return node;
    }
  case get_and_addI_no_resAcq_rule: {
      get_and_addI_no_resAcqNode *node = new get_and_addI_no_resAcqNode();
      return node;
    }
  case get_and_addIiAcq_rule: {
      get_and_addIiAcqNode *node = new get_and_addIiAcqNode();
      return node;
    }
  case get_and_addIi_no_resAcq_rule: {
      get_and_addIi_no_resAcqNode *node = new get_and_addIi_no_resAcqNode();
      return node;
    }
  case cmpU3_reg_reg_rule: {
      cmpU3_reg_regNode *node = new cmpU3_reg_regNode();
      return node;
    }
  case cmpU3_reg_imm_rule: {
      cmpU3_reg_immNode *node = new cmpU3_reg_immNode();
      return node;
    }
  case cmpUL3_reg_reg_rule: {
      cmpUL3_reg_regNode *node = new cmpUL3_reg_regNode();
      return node;
    }
  case cmpUL3_reg_imm_rule: {
      cmpUL3_reg_immNode *node = new cmpUL3_reg_immNode();
      return node;
    }
  case cmpL3_reg_reg_rule: {
      cmpL3_reg_regNode *node = new cmpL3_reg_regNode();
      return node;
    }
  case cmpL3_reg_imm_rule: {
      cmpL3_reg_immNode *node = new cmpL3_reg_immNode();
      return node;
    }
  case cmovI_reg_reg_rule: {
      cmovI_reg_regNode *node = new cmovI_reg_regNode();
      return node;
    }
  case cmovUI_reg_reg_rule: {
      cmovUI_reg_regNode *node = new cmovUI_reg_regNode();
      return node;
    }
  case cmovI_zero_reg_rule: {
      cmovI_zero_regNode *node = new cmovI_zero_regNode();
      return node;
    }
  case cmovUI_zero_reg_rule: {
      cmovUI_zero_regNode *node = new cmovUI_zero_regNode();
      return node;
    }
  case cmovI_reg_zero_rule: {
      cmovI_reg_zeroNode *node = new cmovI_reg_zeroNode();
      return node;
    }
  case cmovUI_reg_zero_rule: {
      cmovUI_reg_zeroNode *node = new cmovUI_reg_zeroNode();
      return node;
    }
  case cmovI_reg_zero_one_rule: {
      cmovI_reg_zero_oneNode *node = new cmovI_reg_zero_oneNode();
      return node;
    }
  case cmovUI_reg_zero_one_rule: {
      cmovUI_reg_zero_oneNode *node = new cmovUI_reg_zero_oneNode();
      return node;
    }
  case cmovL_reg_reg_rule: {
      cmovL_reg_regNode *node = new cmovL_reg_regNode();
      return node;
    }
  case cmovUL_reg_reg_rule: {
      cmovUL_reg_regNode *node = new cmovUL_reg_regNode();
      return node;
    }
  case cmovL_reg_zero_rule: {
      cmovL_reg_zeroNode *node = new cmovL_reg_zeroNode();
      return node;
    }
  case cmovUL_reg_zero_rule: {
      cmovUL_reg_zeroNode *node = new cmovUL_reg_zeroNode();
      return node;
    }
  case cmovL_zero_reg_rule: {
      cmovL_zero_regNode *node = new cmovL_zero_regNode();
      return node;
    }
  case cmovUL_zero_reg_rule: {
      cmovUL_zero_regNode *node = new cmovUL_zero_regNode();
      return node;
    }
  case cmovP_reg_reg_rule: {
      cmovP_reg_regNode *node = new cmovP_reg_regNode();
      return node;
    }
  case cmovUP_reg_reg_rule: {
      cmovUP_reg_regNode *node = new cmovUP_reg_regNode();
      return node;
    }
  case cmovP_reg_zero_rule: {
      cmovP_reg_zeroNode *node = new cmovP_reg_zeroNode();
      return node;
    }
  case cmovUP_reg_zero_rule: {
      cmovUP_reg_zeroNode *node = new cmovUP_reg_zeroNode();
      return node;
    }
  case cmovP_zero_reg_rule: {
      cmovP_zero_regNode *node = new cmovP_zero_regNode();
      return node;
    }
  case cmovUP_zero_reg_rule: {
      cmovUP_zero_regNode *node = new cmovUP_zero_regNode();
      return node;
    }
  case cmovN_reg_reg_rule: {
      cmovN_reg_regNode *node = new cmovN_reg_regNode();
      return node;
    }
  case cmovUN_reg_reg_rule: {
      cmovUN_reg_regNode *node = new cmovUN_reg_regNode();
      return node;
    }
  case cmovN_reg_zero_rule: {
      cmovN_reg_zeroNode *node = new cmovN_reg_zeroNode();
      return node;
    }
  case cmovUN_reg_zero_rule: {
      cmovUN_reg_zeroNode *node = new cmovUN_reg_zeroNode();
      return node;
    }
  case cmovN_zero_reg_rule: {
      cmovN_zero_regNode *node = new cmovN_zero_regNode();
      return node;
    }
  case cmovUN_zero_reg_rule: {
      cmovUN_zero_regNode *node = new cmovUN_zero_regNode();
      return node;
    }
  case cmovF_reg_rule: {
      cmovF_regNode *node = new cmovF_regNode();
      return node;
    }
  case cmovUF_reg_rule: {
      cmovUF_regNode *node = new cmovUF_regNode();
      return node;
    }
  case cmovD_reg_rule: {
      cmovD_regNode *node = new cmovD_regNode();
      return node;
    }
  case cmovUD_reg_rule: {
      cmovUD_regNode *node = new cmovUD_regNode();
      return node;
    }
  case addI_reg_reg_rule: {
      addI_reg_regNode *node = new addI_reg_regNode();
      return node;
    }
  case addI_reg_imm_rule: {
      addI_reg_immNode *node = new addI_reg_immNode();
      return node;
    }
  case addI_reg_imm_i2l_rule: {
      addI_reg_imm_i2lNode *node = new addI_reg_imm_i2lNode();
      return node;
    }
  case addP_reg_reg_rule: {
      addP_reg_regNode *node = new addP_reg_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_reg_ext_rule: {
      addP_reg_reg_extNode *node = new addP_reg_reg_extNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_reg_lsl_rule: {
      addP_reg_reg_lslNode *node = new addP_reg_reg_lslNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_reg_ext_shift_rule: {
      addP_reg_reg_ext_shiftNode *node = new addP_reg_reg_ext_shiftNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case lshift_ext_rule: {
      lshift_extNode *node = new lshift_extNode();
      return node;
    }
  case addP_reg_imm_rule: {
      addP_reg_immNode *node = new addP_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addL_reg_reg_rule: {
      addL_reg_regNode *node = new addL_reg_regNode();
      return node;
    }
  case addL_reg_imm_rule: {
      addL_reg_immNode *node = new addL_reg_immNode();
      return node;
    }
  case subI_reg_reg_rule: {
      subI_reg_regNode *node = new subI_reg_regNode();
      return node;
    }
  case subI_reg_imm_rule: {
      subI_reg_immNode *node = new subI_reg_immNode();
      return node;
    }
  case subL_reg_reg_rule: {
      subL_reg_regNode *node = new subL_reg_regNode();
      return node;
    }
  case subL_reg_imm_rule: {
      subL_reg_immNode *node = new subL_reg_immNode();
      return node;
    }
  case negI_reg_rule: {
      negI_regNode *node = new negI_regNode();
      return node;
    }
  case negL_reg_rule: {
      negL_regNode *node = new negL_regNode();
      return node;
    }
  case mulI_rule: {
      mulINode *node = new mulINode();
      return node;
    }
  case smulI_rule: {
      smulINode *node = new smulINode();
      return node;
    }
  case smulI_0_rule: {
      smulI_0Node *node = new smulI_0Node();
      return node;
    }
  case mulL_rule: {
      mulLNode *node = new mulLNode();
      return node;
    }
  case mulHiL_rReg_rule: {
      mulHiL_rRegNode *node = new mulHiL_rRegNode();
      return node;
    }
  case umulHiL_rReg_rule: {
      umulHiL_rRegNode *node = new umulHiL_rRegNode();
      return node;
    }
  case maddI_rule: {
      maddINode *node = new maddINode();
      return node;
    }
  case maddI_0_rule: {
      maddI_0Node *node = new maddI_0Node();
      return node;
    }
  case msubI_rule: {
      msubINode *node = new msubINode();
      return node;
    }
  case mnegI_rule: {
      mnegINode *node = new mnegINode();
      return node;
    }
  case mnegI_0_rule: {
      mnegI_0Node *node = new mnegI_0Node();
      return node;
    }
  case maddL_rule: {
      maddLNode *node = new maddLNode();
      return node;
    }
  case maddL_0_rule: {
      maddL_0Node *node = new maddL_0Node();
      return node;
    }
  case msubL_rule: {
      msubLNode *node = new msubLNode();
      return node;
    }
  case mnegL_rule: {
      mnegLNode *node = new mnegLNode();
      return node;
    }
  case mnegL_0_rule: {
      mnegL_0Node *node = new mnegL_0Node();
      return node;
    }
  case smaddL_rule: {
      smaddLNode *node = new smaddLNode();
      return node;
    }
  case smaddL_1_rule: {
      smaddL_1Node *node = new smaddL_1Node();
      return node;
    }
  case smaddL_0_rule: {
      smaddL_0Node *node = new smaddL_0Node();
      return node;
    }
  case smaddL_2_rule: {
      smaddL_2Node *node = new smaddL_2Node();
      return node;
    }
  case smsubL_rule: {
      smsubLNode *node = new smsubLNode();
      return node;
    }
  case smsubL_0_rule: {
      smsubL_0Node *node = new smsubL_0Node();
      return node;
    }
  case smnegL_rule: {
      smnegLNode *node = new smnegLNode();
      return node;
    }
  case smnegL_0_rule: {
      smnegL_0Node *node = new smnegL_0Node();
      return node;
    }
  case muladdS2I_rule: {
      muladdS2INode *node = new muladdS2INode();
      return node;
    }
  case divI_rule: {
      divINode *node = new divINode();
      return node;
    }
  case divL_rule: {
      divLNode *node = new divLNode();
      return node;
    }
  case modI_rule: {
      modINode *node = new modINode();
      return node;
    }
  case modL_rule: {
      modLNode *node = new modLNode();
      return node;
    }
  case UdivI_reg_reg_rule: {
      UdivI_reg_regNode *node = new UdivI_reg_regNode();
      return node;
    }
  case UdivL_reg_reg_rule: {
      UdivL_reg_regNode *node = new UdivL_reg_regNode();
      return node;
    }
  case UmodI_reg_reg_rule: {
      UmodI_reg_regNode *node = new UmodI_reg_regNode();
      return node;
    }
  case UModL_reg_reg_rule: {
      UModL_reg_regNode *node = new UModL_reg_regNode();
      return node;
    }
  case lShiftI_reg_reg_rule: {
      lShiftI_reg_regNode *node = new lShiftI_reg_regNode();
      return node;
    }
  case lShiftI_reg_imm_rule: {
      lShiftI_reg_immNode *node = new lShiftI_reg_immNode();
      return node;
    }
  case urShiftI_reg_reg_rule: {
      urShiftI_reg_regNode *node = new urShiftI_reg_regNode();
      return node;
    }
  case urShiftI_reg_imm_rule: {
      urShiftI_reg_immNode *node = new urShiftI_reg_immNode();
      return node;
    }
  case rShiftI_reg_reg_rule: {
      rShiftI_reg_regNode *node = new rShiftI_reg_regNode();
      return node;
    }
  case rShiftI_reg_imm_rule: {
      rShiftI_reg_immNode *node = new rShiftI_reg_immNode();
      return node;
    }
  case lShiftL_reg_reg_rule: {
      lShiftL_reg_regNode *node = new lShiftL_reg_regNode();
      return node;
    }
  case lShiftL_reg_imm_rule: {
      lShiftL_reg_immNode *node = new lShiftL_reg_immNode();
      return node;
    }
  case urShiftL_reg_reg_rule: {
      urShiftL_reg_regNode *node = new urShiftL_reg_regNode();
      return node;
    }
  case urShiftL_reg_imm_rule: {
      urShiftL_reg_immNode *node = new urShiftL_reg_immNode();
      return node;
    }
  case urShiftP_reg_imm_rule: {
      urShiftP_reg_immNode *node = new urShiftP_reg_immNode();
      return node;
    }
  case rShiftL_reg_reg_rule: {
      rShiftL_reg_regNode *node = new rShiftL_reg_regNode();
      return node;
    }
  case rShiftL_reg_imm_rule: {
      rShiftL_reg_immNode *node = new rShiftL_reg_immNode();
      return node;
    }
  case regL_not_reg_rule: {
      regL_not_regNode *node = new regL_not_regNode();
      return node;
    }
  case regI_not_reg_rule: {
      regI_not_regNode *node = new regI_not_regNode();
      return node;
    }
  case NegI_reg_URShift_reg_rule: {
      NegI_reg_URShift_regNode *node = new NegI_reg_URShift_regNode();
      return node;
    }
  case NegI_reg_RShift_reg_rule: {
      NegI_reg_RShift_regNode *node = new NegI_reg_RShift_regNode();
      return node;
    }
  case NegI_reg_LShift_reg_rule: {
      NegI_reg_LShift_regNode *node = new NegI_reg_LShift_regNode();
      return node;
    }
  case NegL_reg_URShift_reg_rule: {
      NegL_reg_URShift_regNode *node = new NegL_reg_URShift_regNode();
      return node;
    }
  case NegL_reg_RShift_reg_rule: {
      NegL_reg_RShift_regNode *node = new NegL_reg_RShift_regNode();
      return node;
    }
  case NegL_reg_LShift_reg_rule: {
      NegL_reg_LShift_regNode *node = new NegL_reg_LShift_regNode();
      return node;
    }
  case AndI_reg_not_reg_rule: {
      AndI_reg_not_regNode *node = new AndI_reg_not_regNode();
      return node;
    }
  case AndI_reg_not_reg_0_rule: {
      AndI_reg_not_reg_0Node *node = new AndI_reg_not_reg_0Node();
      return node;
    }
  case AndL_reg_not_reg_rule: {
      AndL_reg_not_regNode *node = new AndL_reg_not_regNode();
      return node;
    }
  case AndL_reg_not_reg_0_rule: {
      AndL_reg_not_reg_0Node *node = new AndL_reg_not_reg_0Node();
      return node;
    }
  case OrI_reg_not_reg_rule: {
      OrI_reg_not_regNode *node = new OrI_reg_not_regNode();
      return node;
    }
  case OrI_reg_not_reg_0_rule: {
      OrI_reg_not_reg_0Node *node = new OrI_reg_not_reg_0Node();
      return node;
    }
  case OrL_reg_not_reg_rule: {
      OrL_reg_not_regNode *node = new OrL_reg_not_regNode();
      return node;
    }
  case OrL_reg_not_reg_0_rule: {
      OrL_reg_not_reg_0Node *node = new OrL_reg_not_reg_0Node();
      return node;
    }
  case XorI_reg_not_reg_rule: {
      XorI_reg_not_regNode *node = new XorI_reg_not_regNode();
      return node;
    }
  case XorI_reg_not_reg_0_rule: {
      XorI_reg_not_reg_0Node *node = new XorI_reg_not_reg_0Node();
      return node;
    }
  case XorL_reg_not_reg_rule: {
      XorL_reg_not_regNode *node = new XorL_reg_not_regNode();
      return node;
    }
  case XorL_reg_not_reg_0_rule: {
      XorL_reg_not_reg_0Node *node = new XorL_reg_not_reg_0Node();
      return node;
    }
  case AndI_reg_URShift_not_reg_rule: {
      AndI_reg_URShift_not_regNode *node = new AndI_reg_URShift_not_regNode();
      return node;
    }
  case AndI_reg_URShift_not_reg_0_rule: {
      AndI_reg_URShift_not_reg_0Node *node = new AndI_reg_URShift_not_reg_0Node();
      return node;
    }
  case AndL_reg_URShift_not_reg_rule: {
      AndL_reg_URShift_not_regNode *node = new AndL_reg_URShift_not_regNode();
      return node;
    }
  case AndL_reg_URShift_not_reg_0_rule: {
      AndL_reg_URShift_not_reg_0Node *node = new AndL_reg_URShift_not_reg_0Node();
      return node;
    }
  case AndI_reg_RShift_not_reg_rule: {
      AndI_reg_RShift_not_regNode *node = new AndI_reg_RShift_not_regNode();
      return node;
    }
  case AndI_reg_RShift_not_reg_0_rule: {
      AndI_reg_RShift_not_reg_0Node *node = new AndI_reg_RShift_not_reg_0Node();
      return node;
    }
  case AndL_reg_RShift_not_reg_rule: {
      AndL_reg_RShift_not_regNode *node = new AndL_reg_RShift_not_regNode();
      return node;
    }
  case AndL_reg_RShift_not_reg_0_rule: {
      AndL_reg_RShift_not_reg_0Node *node = new AndL_reg_RShift_not_reg_0Node();
      return node;
    }
  case AndI_reg_RotateRight_not_reg_rule: {
      AndI_reg_RotateRight_not_regNode *node = new AndI_reg_RotateRight_not_regNode();
      return node;
    }
  case AndI_reg_RotateRight_not_reg_0_rule: {
      AndI_reg_RotateRight_not_reg_0Node *node = new AndI_reg_RotateRight_not_reg_0Node();
      return node;
    }
  case AndL_reg_RotateRight_not_reg_rule: {
      AndL_reg_RotateRight_not_regNode *node = new AndL_reg_RotateRight_not_regNode();
      return node;
    }
  case AndL_reg_RotateRight_not_reg_0_rule: {
      AndL_reg_RotateRight_not_reg_0Node *node = new AndL_reg_RotateRight_not_reg_0Node();
      return node;
    }
  case AndI_reg_LShift_not_reg_rule: {
      AndI_reg_LShift_not_regNode *node = new AndI_reg_LShift_not_regNode();
      return node;
    }
  case AndI_reg_LShift_not_reg_0_rule: {
      AndI_reg_LShift_not_reg_0Node *node = new AndI_reg_LShift_not_reg_0Node();
      return node;
    }
  case AndL_reg_LShift_not_reg_rule: {
      AndL_reg_LShift_not_regNode *node = new AndL_reg_LShift_not_regNode();
      return node;
    }
  case AndL_reg_LShift_not_reg_0_rule: {
      AndL_reg_LShift_not_reg_0Node *node = new AndL_reg_LShift_not_reg_0Node();
      return node;
    }
  case XorI_reg_URShift_not_reg_rule: {
      XorI_reg_URShift_not_regNode *node = new XorI_reg_URShift_not_regNode();
      return node;
    }
  case XorI_reg_URShift_not_reg_1_rule: {
      XorI_reg_URShift_not_reg_1Node *node = new XorI_reg_URShift_not_reg_1Node();
      return node;
    }
  case XorI_reg_URShift_not_reg_0_rule: {
      XorI_reg_URShift_not_reg_0Node *node = new XorI_reg_URShift_not_reg_0Node();
      return node;
    }
  case XorI_reg_URShift_not_reg_2_rule: {
      XorI_reg_URShift_not_reg_2Node *node = new XorI_reg_URShift_not_reg_2Node();
      return node;
    }
  case XorL_reg_URShift_not_reg_rule: {
      XorL_reg_URShift_not_regNode *node = new XorL_reg_URShift_not_regNode();
      return node;
    }
  case XorL_reg_URShift_not_reg_1_rule: {
      XorL_reg_URShift_not_reg_1Node *node = new XorL_reg_URShift_not_reg_1Node();
      return node;
    }
  case XorL_reg_URShift_not_reg_0_rule: {
      XorL_reg_URShift_not_reg_0Node *node = new XorL_reg_URShift_not_reg_0Node();
      return node;
    }
  case XorL_reg_URShift_not_reg_2_rule: {
      XorL_reg_URShift_not_reg_2Node *node = new XorL_reg_URShift_not_reg_2Node();
      return node;
    }
  case XorI_reg_RShift_not_reg_rule: {
      XorI_reg_RShift_not_regNode *node = new XorI_reg_RShift_not_regNode();
      return node;
    }
  case XorI_reg_RShift_not_reg_1_rule: {
      XorI_reg_RShift_not_reg_1Node *node = new XorI_reg_RShift_not_reg_1Node();
      return node;
    }
  case XorI_reg_RShift_not_reg_0_rule: {
      XorI_reg_RShift_not_reg_0Node *node = new XorI_reg_RShift_not_reg_0Node();
      return node;
    }
  case XorI_reg_RShift_not_reg_2_rule: {
      XorI_reg_RShift_not_reg_2Node *node = new XorI_reg_RShift_not_reg_2Node();
      return node;
    }
  case XorL_reg_RShift_not_reg_rule: {
      XorL_reg_RShift_not_regNode *node = new XorL_reg_RShift_not_regNode();
      return node;
    }
  case XorL_reg_RShift_not_reg_1_rule: {
      XorL_reg_RShift_not_reg_1Node *node = new XorL_reg_RShift_not_reg_1Node();
      return node;
    }
  case XorL_reg_RShift_not_reg_0_rule: {
      XorL_reg_RShift_not_reg_0Node *node = new XorL_reg_RShift_not_reg_0Node();
      return node;
    }
  case XorL_reg_RShift_not_reg_2_rule: {
      XorL_reg_RShift_not_reg_2Node *node = new XorL_reg_RShift_not_reg_2Node();
      return node;
    }
  case XorI_reg_RotateRight_not_reg_rule: {
      XorI_reg_RotateRight_not_regNode *node = new XorI_reg_RotateRight_not_regNode();
      return node;
    }
  case XorI_reg_RotateRight_not_reg_1_rule: {
      XorI_reg_RotateRight_not_reg_1Node *node = new XorI_reg_RotateRight_not_reg_1Node();
      return node;
    }
  case XorI_reg_RotateRight_not_reg_0_rule: {
      XorI_reg_RotateRight_not_reg_0Node *node = new XorI_reg_RotateRight_not_reg_0Node();
      return node;
    }
  case XorI_reg_RotateRight_not_reg_2_rule: {
      XorI_reg_RotateRight_not_reg_2Node *node = new XorI_reg_RotateRight_not_reg_2Node();
      return node;
    }
  case XorL_reg_RotateRight_not_reg_rule: {
      XorL_reg_RotateRight_not_regNode *node = new XorL_reg_RotateRight_not_regNode();
      return node;
    }
  case XorL_reg_RotateRight_not_reg_1_rule: {
      XorL_reg_RotateRight_not_reg_1Node *node = new XorL_reg_RotateRight_not_reg_1Node();
      return node;
    }
  case XorL_reg_RotateRight_not_reg_0_rule: {
      XorL_reg_RotateRight_not_reg_0Node *node = new XorL_reg_RotateRight_not_reg_0Node();
      return node;
    }
  case XorL_reg_RotateRight_not_reg_2_rule: {
      XorL_reg_RotateRight_not_reg_2Node *node = new XorL_reg_RotateRight_not_reg_2Node();
      return node;
    }
  case XorI_reg_LShift_not_reg_rule: {
      XorI_reg_LShift_not_regNode *node = new XorI_reg_LShift_not_regNode();
      return node;
    }
  case XorI_reg_LShift_not_reg_1_rule: {
      XorI_reg_LShift_not_reg_1Node *node = new XorI_reg_LShift_not_reg_1Node();
      return node;
    }
  case XorI_reg_LShift_not_reg_0_rule: {
      XorI_reg_LShift_not_reg_0Node *node = new XorI_reg_LShift_not_reg_0Node();
      return node;
    }
  case XorI_reg_LShift_not_reg_2_rule: {
      XorI_reg_LShift_not_reg_2Node *node = new XorI_reg_LShift_not_reg_2Node();
      return node;
    }
  case XorL_reg_LShift_not_reg_rule: {
      XorL_reg_LShift_not_regNode *node = new XorL_reg_LShift_not_regNode();
      return node;
    }
  case XorL_reg_LShift_not_reg_1_rule: {
      XorL_reg_LShift_not_reg_1Node *node = new XorL_reg_LShift_not_reg_1Node();
      return node;
    }
  case XorL_reg_LShift_not_reg_0_rule: {
      XorL_reg_LShift_not_reg_0Node *node = new XorL_reg_LShift_not_reg_0Node();
      return node;
    }
  case XorL_reg_LShift_not_reg_2_rule: {
      XorL_reg_LShift_not_reg_2Node *node = new XorL_reg_LShift_not_reg_2Node();
      return node;
    }
  case OrI_reg_URShift_not_reg_rule: {
      OrI_reg_URShift_not_regNode *node = new OrI_reg_URShift_not_regNode();
      return node;
    }
  case OrI_reg_URShift_not_reg_0_rule: {
      OrI_reg_URShift_not_reg_0Node *node = new OrI_reg_URShift_not_reg_0Node();
      return node;
    }
  case OrL_reg_URShift_not_reg_rule: {
      OrL_reg_URShift_not_regNode *node = new OrL_reg_URShift_not_regNode();
      return node;
    }
  case OrL_reg_URShift_not_reg_0_rule: {
      OrL_reg_URShift_not_reg_0Node *node = new OrL_reg_URShift_not_reg_0Node();
      return node;
    }
  case OrI_reg_RShift_not_reg_rule: {
      OrI_reg_RShift_not_regNode *node = new OrI_reg_RShift_not_regNode();
      return node;
    }
  case OrI_reg_RShift_not_reg_0_rule: {
      OrI_reg_RShift_not_reg_0Node *node = new OrI_reg_RShift_not_reg_0Node();
      return node;
    }
  case OrL_reg_RShift_not_reg_rule: {
      OrL_reg_RShift_not_regNode *node = new OrL_reg_RShift_not_regNode();
      return node;
    }
  case OrL_reg_RShift_not_reg_0_rule: {
      OrL_reg_RShift_not_reg_0Node *node = new OrL_reg_RShift_not_reg_0Node();
      return node;
    }
  case OrI_reg_RotateRight_not_reg_rule: {
      OrI_reg_RotateRight_not_regNode *node = new OrI_reg_RotateRight_not_regNode();
      return node;
    }
  case OrI_reg_RotateRight_not_reg_0_rule: {
      OrI_reg_RotateRight_not_reg_0Node *node = new OrI_reg_RotateRight_not_reg_0Node();
      return node;
    }
  case OrL_reg_RotateRight_not_reg_rule: {
      OrL_reg_RotateRight_not_regNode *node = new OrL_reg_RotateRight_not_regNode();
      return node;
    }
  case OrL_reg_RotateRight_not_reg_0_rule: {
      OrL_reg_RotateRight_not_reg_0Node *node = new OrL_reg_RotateRight_not_reg_0Node();
      return node;
    }
  case OrI_reg_LShift_not_reg_rule: {
      OrI_reg_LShift_not_regNode *node = new OrI_reg_LShift_not_regNode();
      return node;
    }
  case OrI_reg_LShift_not_reg_0_rule: {
      OrI_reg_LShift_not_reg_0Node *node = new OrI_reg_LShift_not_reg_0Node();
      return node;
    }
  case OrL_reg_LShift_not_reg_rule: {
      OrL_reg_LShift_not_regNode *node = new OrL_reg_LShift_not_regNode();
      return node;
    }
  case OrL_reg_LShift_not_reg_0_rule: {
      OrL_reg_LShift_not_reg_0Node *node = new OrL_reg_LShift_not_reg_0Node();
      return node;
    }
  case AndI_reg_URShift_reg_rule: {
      AndI_reg_URShift_regNode *node = new AndI_reg_URShift_regNode();
      return node;
    }
  case AndI_reg_URShift_reg_0_rule: {
      AndI_reg_URShift_reg_0Node *node = new AndI_reg_URShift_reg_0Node();
      return node;
    }
  case AndL_reg_URShift_reg_rule: {
      AndL_reg_URShift_regNode *node = new AndL_reg_URShift_regNode();
      return node;
    }
  case AndL_reg_URShift_reg_0_rule: {
      AndL_reg_URShift_reg_0Node *node = new AndL_reg_URShift_reg_0Node();
      return node;
    }
  case AndI_reg_RShift_reg_rule: {
      AndI_reg_RShift_regNode *node = new AndI_reg_RShift_regNode();
      return node;
    }
  case AndI_reg_RShift_reg_0_rule: {
      AndI_reg_RShift_reg_0Node *node = new AndI_reg_RShift_reg_0Node();
      return node;
    }
  case AndL_reg_RShift_reg_rule: {
      AndL_reg_RShift_regNode *node = new AndL_reg_RShift_regNode();
      return node;
    }
  case AndL_reg_RShift_reg_0_rule: {
      AndL_reg_RShift_reg_0Node *node = new AndL_reg_RShift_reg_0Node();
      return node;
    }
  case AndI_reg_LShift_reg_rule: {
      AndI_reg_LShift_regNode *node = new AndI_reg_LShift_regNode();
      return node;
    }
  case AndI_reg_LShift_reg_0_rule: {
      AndI_reg_LShift_reg_0Node *node = new AndI_reg_LShift_reg_0Node();
      return node;
    }
  case AndL_reg_LShift_reg_rule: {
      AndL_reg_LShift_regNode *node = new AndL_reg_LShift_regNode();
      return node;
    }
  case AndL_reg_LShift_reg_0_rule: {
      AndL_reg_LShift_reg_0Node *node = new AndL_reg_LShift_reg_0Node();
      return node;
    }
  case AndI_reg_RotateRight_reg_rule: {
      AndI_reg_RotateRight_regNode *node = new AndI_reg_RotateRight_regNode();
      return node;
    }
  case AndI_reg_RotateRight_reg_0_rule: {
      AndI_reg_RotateRight_reg_0Node *node = new AndI_reg_RotateRight_reg_0Node();
      return node;
    }
  case AndL_reg_RotateRight_reg_rule: {
      AndL_reg_RotateRight_regNode *node = new AndL_reg_RotateRight_regNode();
      return node;
    }
  case AndL_reg_RotateRight_reg_0_rule: {
      AndL_reg_RotateRight_reg_0Node *node = new AndL_reg_RotateRight_reg_0Node();
      return node;
    }
  case XorI_reg_URShift_reg_rule: {
      XorI_reg_URShift_regNode *node = new XorI_reg_URShift_regNode();
      return node;
    }
  case XorI_reg_URShift_reg_0_rule: {
      XorI_reg_URShift_reg_0Node *node = new XorI_reg_URShift_reg_0Node();
      return node;
    }
  case XorL_reg_URShift_reg_rule: {
      XorL_reg_URShift_regNode *node = new XorL_reg_URShift_regNode();
      return node;
    }
  case XorL_reg_URShift_reg_0_rule: {
      XorL_reg_URShift_reg_0Node *node = new XorL_reg_URShift_reg_0Node();
      return node;
    }
  case XorI_reg_RShift_reg_rule: {
      XorI_reg_RShift_regNode *node = new XorI_reg_RShift_regNode();
      return node;
    }
  case XorI_reg_RShift_reg_0_rule: {
      XorI_reg_RShift_reg_0Node *node = new XorI_reg_RShift_reg_0Node();
      return node;
    }
  case XorL_reg_RShift_reg_rule: {
      XorL_reg_RShift_regNode *node = new XorL_reg_RShift_regNode();
      return node;
    }
  case XorL_reg_RShift_reg_0_rule: {
      XorL_reg_RShift_reg_0Node *node = new XorL_reg_RShift_reg_0Node();
      return node;
    }
  case XorI_reg_LShift_reg_rule: {
      XorI_reg_LShift_regNode *node = new XorI_reg_LShift_regNode();
      return node;
    }
  case XorI_reg_LShift_reg_0_rule: {
      XorI_reg_LShift_reg_0Node *node = new XorI_reg_LShift_reg_0Node();
      return node;
    }
  case XorL_reg_LShift_reg_rule: {
      XorL_reg_LShift_regNode *node = new XorL_reg_LShift_regNode();
      return node;
    }
  case XorL_reg_LShift_reg_0_rule: {
      XorL_reg_LShift_reg_0Node *node = new XorL_reg_LShift_reg_0Node();
      return node;
    }
  case XorI_reg_RotateRight_reg_rule: {
      XorI_reg_RotateRight_regNode *node = new XorI_reg_RotateRight_regNode();
      return node;
    }
  case XorI_reg_RotateRight_reg_0_rule: {
      XorI_reg_RotateRight_reg_0Node *node = new XorI_reg_RotateRight_reg_0Node();
      return node;
    }
  case XorL_reg_RotateRight_reg_rule: {
      XorL_reg_RotateRight_regNode *node = new XorL_reg_RotateRight_regNode();
      return node;
    }
  case XorL_reg_RotateRight_reg_0_rule: {
      XorL_reg_RotateRight_reg_0Node *node = new XorL_reg_RotateRight_reg_0Node();
      return node;
    }
  case OrI_reg_URShift_reg_rule: {
      OrI_reg_URShift_regNode *node = new OrI_reg_URShift_regNode();
      return node;
    }
  case OrI_reg_URShift_reg_0_rule: {
      OrI_reg_URShift_reg_0Node *node = new OrI_reg_URShift_reg_0Node();
      return node;
    }
  case OrL_reg_URShift_reg_rule: {
      OrL_reg_URShift_regNode *node = new OrL_reg_URShift_regNode();
      return node;
    }
  case OrL_reg_URShift_reg_0_rule: {
      OrL_reg_URShift_reg_0Node *node = new OrL_reg_URShift_reg_0Node();
      return node;
    }
  case OrI_reg_RShift_reg_rule: {
      OrI_reg_RShift_regNode *node = new OrI_reg_RShift_regNode();
      return node;
    }
  case OrI_reg_RShift_reg_0_rule: {
      OrI_reg_RShift_reg_0Node *node = new OrI_reg_RShift_reg_0Node();
      return node;
    }
  case OrL_reg_RShift_reg_rule: {
      OrL_reg_RShift_regNode *node = new OrL_reg_RShift_regNode();
      return node;
    }
  case OrL_reg_RShift_reg_0_rule: {
      OrL_reg_RShift_reg_0Node *node = new OrL_reg_RShift_reg_0Node();
      return node;
    }
  case OrI_reg_LShift_reg_rule: {
      OrI_reg_LShift_regNode *node = new OrI_reg_LShift_regNode();
      return node;
    }
  case OrI_reg_LShift_reg_0_rule: {
      OrI_reg_LShift_reg_0Node *node = new OrI_reg_LShift_reg_0Node();
      return node;
    }
  case OrL_reg_LShift_reg_rule: {
      OrL_reg_LShift_regNode *node = new OrL_reg_LShift_regNode();
      return node;
    }
  case OrL_reg_LShift_reg_0_rule: {
      OrL_reg_LShift_reg_0Node *node = new OrL_reg_LShift_reg_0Node();
      return node;
    }
  case OrI_reg_RotateRight_reg_rule: {
      OrI_reg_RotateRight_regNode *node = new OrI_reg_RotateRight_regNode();
      return node;
    }
  case OrI_reg_RotateRight_reg_0_rule: {
      OrI_reg_RotateRight_reg_0Node *node = new OrI_reg_RotateRight_reg_0Node();
      return node;
    }
  case OrL_reg_RotateRight_reg_rule: {
      OrL_reg_RotateRight_regNode *node = new OrL_reg_RotateRight_regNode();
      return node;
    }
  case OrL_reg_RotateRight_reg_0_rule: {
      OrL_reg_RotateRight_reg_0Node *node = new OrL_reg_RotateRight_reg_0Node();
      return node;
    }
  case AddI_reg_URShift_reg_rule: {
      AddI_reg_URShift_regNode *node = new AddI_reg_URShift_regNode();
      return node;
    }
  case AddI_reg_URShift_reg_0_rule: {
      AddI_reg_URShift_reg_0Node *node = new AddI_reg_URShift_reg_0Node();
      return node;
    }
  case AddL_reg_URShift_reg_rule: {
      AddL_reg_URShift_regNode *node = new AddL_reg_URShift_regNode();
      return node;
    }
  case AddL_reg_URShift_reg_0_rule: {
      AddL_reg_URShift_reg_0Node *node = new AddL_reg_URShift_reg_0Node();
      return node;
    }
  case AddI_reg_RShift_reg_rule: {
      AddI_reg_RShift_regNode *node = new AddI_reg_RShift_regNode();
      return node;
    }
  case AddI_reg_RShift_reg_0_rule: {
      AddI_reg_RShift_reg_0Node *node = new AddI_reg_RShift_reg_0Node();
      return node;
    }
  case AddL_reg_RShift_reg_rule: {
      AddL_reg_RShift_regNode *node = new AddL_reg_RShift_regNode();
      return node;
    }
  case AddL_reg_RShift_reg_0_rule: {
      AddL_reg_RShift_reg_0Node *node = new AddL_reg_RShift_reg_0Node();
      return node;
    }
  case AddI_reg_LShift_reg_rule: {
      AddI_reg_LShift_regNode *node = new AddI_reg_LShift_regNode();
      return node;
    }
  case AddI_reg_LShift_reg_0_rule: {
      AddI_reg_LShift_reg_0Node *node = new AddI_reg_LShift_reg_0Node();
      return node;
    }
  case AddL_reg_LShift_reg_rule: {
      AddL_reg_LShift_regNode *node = new AddL_reg_LShift_regNode();
      return node;
    }
  case AddL_reg_LShift_reg_0_rule: {
      AddL_reg_LShift_reg_0Node *node = new AddL_reg_LShift_reg_0Node();
      return node;
    }
  case SubI_reg_URShift_reg_rule: {
      SubI_reg_URShift_regNode *node = new SubI_reg_URShift_regNode();
      return node;
    }
  case SubL_reg_URShift_reg_rule: {
      SubL_reg_URShift_regNode *node = new SubL_reg_URShift_regNode();
      return node;
    }
  case SubI_reg_RShift_reg_rule: {
      SubI_reg_RShift_regNode *node = new SubI_reg_RShift_regNode();
      return node;
    }
  case SubL_reg_RShift_reg_rule: {
      SubL_reg_RShift_regNode *node = new SubL_reg_RShift_regNode();
      return node;
    }
  case SubI_reg_LShift_reg_rule: {
      SubI_reg_LShift_regNode *node = new SubI_reg_LShift_regNode();
      return node;
    }
  case SubL_reg_LShift_reg_rule: {
      SubL_reg_LShift_regNode *node = new SubL_reg_LShift_regNode();
      return node;
    }
  case sbfmL_rule: {
      sbfmLNode *node = new sbfmLNode();
      return node;
    }
  case sbfmwI_rule: {
      sbfmwINode *node = new sbfmwINode();
      return node;
    }
  case ubfmL_rule: {
      ubfmLNode *node = new ubfmLNode();
      return node;
    }
  case ubfmwI_rule: {
      ubfmwINode *node = new ubfmwINode();
      return node;
    }
  case ubfxwI_rule: {
      ubfxwINode *node = new ubfxwINode();
      return node;
    }
  case ubfxL_rule: {
      ubfxLNode *node = new ubfxLNode();
      return node;
    }
  case ubfxIConvI2L_rule: {
      ubfxIConvI2LNode *node = new ubfxIConvI2LNode();
      return node;
    }
  case ubfizwI_rule: {
      ubfizwINode *node = new ubfizwINode();
      return node;
    }
  case ubfizL_rule: {
      ubfizLNode *node = new ubfizLNode();
      return node;
    }
  case ubfizwIConvI2L_rule: {
      ubfizwIConvI2LNode *node = new ubfizwIConvI2LNode();
      return node;
    }
  case ubfizLConvL2I_rule: {
      ubfizLConvL2INode *node = new ubfizLConvL2INode();
      return node;
    }
  case ubfizIConvI2L_rule: {
      ubfizIConvI2LNode *node = new ubfizIConvI2LNode();
      return node;
    }
  case ubfizLConvL2Ix_rule: {
      ubfizLConvL2IxNode *node = new ubfizLConvL2IxNode();
      return node;
    }
  case ubfizIConvI2LAndI_rule: {
      ubfizIConvI2LAndINode *node = new ubfizIConvI2LAndINode();
      return node;
    }
  case extrOrL_rule: {
      extrOrLNode *node = new extrOrLNode();
      return node;
    }
  case extrOrL_0_rule: {
      extrOrL_0Node *node = new extrOrL_0Node();
      return node;
    }
  case extrOrI_rule: {
      extrOrINode *node = new extrOrINode();
      return node;
    }
  case extrOrI_0_rule: {
      extrOrI_0Node *node = new extrOrI_0Node();
      return node;
    }
  case extrAddL_rule: {
      extrAddLNode *node = new extrAddLNode();
      return node;
    }
  case extrAddL_0_rule: {
      extrAddL_0Node *node = new extrAddL_0Node();
      return node;
    }
  case extrAddI_rule: {
      extrAddINode *node = new extrAddINode();
      return node;
    }
  case extrAddI_0_rule: {
      extrAddI_0Node *node = new extrAddI_0Node();
      return node;
    }
  case rorI_imm_rule: {
      rorI_immNode *node = new rorI_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorL_imm_rule: {
      rorL_immNode *node = new rorL_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorI_reg_rule: {
      rorI_regNode *node = new rorI_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorL_reg_rule: {
      rorL_regNode *node = new rorL_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rolI_reg_rule: {
      rolI_regNode *node = new rolI_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rolL_reg_rule: {
      rolL_regNode *node = new rolL_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case AddExtI_rule: {
      AddExtINode *node = new AddExtINode();
      return node;
    }
  case AddExtI_0_rule: {
      AddExtI_0Node *node = new AddExtI_0Node();
      return node;
    }
  case SubExtI_rule: {
      SubExtINode *node = new SubExtINode();
      return node;
    }
  case AddExtI_sxth_rule: {
      AddExtI_sxthNode *node = new AddExtI_sxthNode();
      return node;
    }
  case AddExtI_sxth_0_rule: {
      AddExtI_sxth_0Node *node = new AddExtI_sxth_0Node();
      return node;
    }
  case AddExtI_sxtb_rule: {
      AddExtI_sxtbNode *node = new AddExtI_sxtbNode();
      return node;
    }
  case AddExtI_sxtb_0_rule: {
      AddExtI_sxtb_0Node *node = new AddExtI_sxtb_0Node();
      return node;
    }
  case AddExtI_uxtb_rule: {
      AddExtI_uxtbNode *node = new AddExtI_uxtbNode();
      return node;
    }
  case AddExtI_uxtb_0_rule: {
      AddExtI_uxtb_0Node *node = new AddExtI_uxtb_0Node();
      return node;
    }
  case AddExtL_sxth_rule: {
      AddExtL_sxthNode *node = new AddExtL_sxthNode();
      return node;
    }
  case AddExtL_sxth_0_rule: {
      AddExtL_sxth_0Node *node = new AddExtL_sxth_0Node();
      return node;
    }
  case AddExtL_sxtw_rule: {
      AddExtL_sxtwNode *node = new AddExtL_sxtwNode();
      return node;
    }
  case AddExtL_sxtw_0_rule: {
      AddExtL_sxtw_0Node *node = new AddExtL_sxtw_0Node();
      return node;
    }
  case AddExtL_sxtb_rule: {
      AddExtL_sxtbNode *node = new AddExtL_sxtbNode();
      return node;
    }
  case AddExtL_sxtb_0_rule: {
      AddExtL_sxtb_0Node *node = new AddExtL_sxtb_0Node();
      return node;
    }
  case AddExtL_uxtb_rule: {
      AddExtL_uxtbNode *node = new AddExtL_uxtbNode();
      return node;
    }
  case AddExtL_uxtb_0_rule: {
      AddExtL_uxtb_0Node *node = new AddExtL_uxtb_0Node();
      return node;
    }
  case AddExtI_uxtb_and_rule: {
      AddExtI_uxtb_andNode *node = new AddExtI_uxtb_andNode();
      return node;
    }
  case AddExtI_uxtb_and_0_rule: {
      AddExtI_uxtb_and_0Node *node = new AddExtI_uxtb_and_0Node();
      return node;
    }
  case AddExtI_uxth_and_rule: {
      AddExtI_uxth_andNode *node = new AddExtI_uxth_andNode();
      return node;
    }
  case AddExtI_uxth_and_0_rule: {
      AddExtI_uxth_and_0Node *node = new AddExtI_uxth_and_0Node();
      return node;
    }
  case AddExtL_uxtb_and_rule: {
      AddExtL_uxtb_andNode *node = new AddExtL_uxtb_andNode();
      return node;
    }
  case AddExtL_uxtb_and_0_rule: {
      AddExtL_uxtb_and_0Node *node = new AddExtL_uxtb_and_0Node();
      return node;
    }
  case AddExtL_uxth_and_rule: {
      AddExtL_uxth_andNode *node = new AddExtL_uxth_andNode();
      return node;
    }
  case AddExtL_uxth_and_0_rule: {
      AddExtL_uxth_and_0Node *node = new AddExtL_uxth_and_0Node();
      return node;
    }
  case AddExtL_uxtw_and_rule: {
      AddExtL_uxtw_andNode *node = new AddExtL_uxtw_andNode();
      return node;
    }
  case AddExtL_uxtw_and_0_rule: {
      AddExtL_uxtw_and_0Node *node = new AddExtL_uxtw_and_0Node();
      return node;
    }
  case SubExtI_uxtb_and_rule: {
      SubExtI_uxtb_andNode *node = new SubExtI_uxtb_andNode();
      return node;
    }
  case SubExtI_uxth_and_rule: {
      SubExtI_uxth_andNode *node = new SubExtI_uxth_andNode();
      return node;
    }
  case SubExtL_uxtb_and_rule: {
      SubExtL_uxtb_andNode *node = new SubExtL_uxtb_andNode();
      return node;
    }
  case SubExtL_uxth_and_rule: {
      SubExtL_uxth_andNode *node = new SubExtL_uxth_andNode();
      return node;
    }
  case SubExtL_uxtw_and_rule: {
      SubExtL_uxtw_andNode *node = new SubExtL_uxtw_andNode();
      return node;
    }
  case AddExtL_sxtb_shift_rule: {
      AddExtL_sxtb_shiftNode *node = new AddExtL_sxtb_shiftNode();
      return node;
    }
  case AddExtL_sxtb_shift_0_rule: {
      AddExtL_sxtb_shift_0Node *node = new AddExtL_sxtb_shift_0Node();
      return node;
    }
  case AddExtL_sxth_shift_rule: {
      AddExtL_sxth_shiftNode *node = new AddExtL_sxth_shiftNode();
      return node;
    }
  case AddExtL_sxth_shift_0_rule: {
      AddExtL_sxth_shift_0Node *node = new AddExtL_sxth_shift_0Node();
      return node;
    }
  case AddExtL_sxtw_shift_rule: {
      AddExtL_sxtw_shiftNode *node = new AddExtL_sxtw_shiftNode();
      return node;
    }
  case AddExtL_sxtw_shift_0_rule: {
      AddExtL_sxtw_shift_0Node *node = new AddExtL_sxtw_shift_0Node();
      return node;
    }
  case SubExtL_sxtb_shift_rule: {
      SubExtL_sxtb_shiftNode *node = new SubExtL_sxtb_shiftNode();
      return node;
    }
  case SubExtL_sxth_shift_rule: {
      SubExtL_sxth_shiftNode *node = new SubExtL_sxth_shiftNode();
      return node;
    }
  case SubExtL_sxtw_shift_rule: {
      SubExtL_sxtw_shiftNode *node = new SubExtL_sxtw_shiftNode();
      return node;
    }
  case AddExtI_sxtb_shift_rule: {
      AddExtI_sxtb_shiftNode *node = new AddExtI_sxtb_shiftNode();
      return node;
    }
  case AddExtI_sxtb_shift_0_rule: {
      AddExtI_sxtb_shift_0Node *node = new AddExtI_sxtb_shift_0Node();
      return node;
    }
  case AddExtI_sxth_shift_rule: {
      AddExtI_sxth_shiftNode *node = new AddExtI_sxth_shiftNode();
      return node;
    }
  case AddExtI_sxth_shift_0_rule: {
      AddExtI_sxth_shift_0Node *node = new AddExtI_sxth_shift_0Node();
      return node;
    }
  case SubExtI_sxtb_shift_rule: {
      SubExtI_sxtb_shiftNode *node = new SubExtI_sxtb_shiftNode();
      return node;
    }
  case SubExtI_sxth_shift_rule: {
      SubExtI_sxth_shiftNode *node = new SubExtI_sxth_shiftNode();
      return node;
    }
  case AddExtI_shift_rule: {
      AddExtI_shiftNode *node = new AddExtI_shiftNode();
      return node;
    }
  case AddExtI_shift_0_rule: {
      AddExtI_shift_0Node *node = new AddExtI_shift_0Node();
      return node;
    }
  case SubExtI_shift_rule: {
      SubExtI_shiftNode *node = new SubExtI_shiftNode();
      return node;
    }
  case AddExtL_uxtb_and_shift_rule: {
      AddExtL_uxtb_and_shiftNode *node = new AddExtL_uxtb_and_shiftNode();
      return node;
    }
  case AddExtL_uxtb_and_shift_0_rule: {
      AddExtL_uxtb_and_shift_0Node *node = new AddExtL_uxtb_and_shift_0Node();
      return node;
    }
  case AddExtL_uxth_and_shift_rule: {
      AddExtL_uxth_and_shiftNode *node = new AddExtL_uxth_and_shiftNode();
      return node;
    }
  case AddExtL_uxth_and_shift_0_rule: {
      AddExtL_uxth_and_shift_0Node *node = new AddExtL_uxth_and_shift_0Node();
      return node;
    }
  case AddExtL_uxtw_and_shift_rule: {
      AddExtL_uxtw_and_shiftNode *node = new AddExtL_uxtw_and_shiftNode();
      return node;
    }
  case AddExtL_uxtw_and_shift_0_rule: {
      AddExtL_uxtw_and_shift_0Node *node = new AddExtL_uxtw_and_shift_0Node();
      return node;
    }
  case SubExtL_uxtb_and_shift_rule: {
      SubExtL_uxtb_and_shiftNode *node = new SubExtL_uxtb_and_shiftNode();
      return node;
    }
  case SubExtL_uxth_and_shift_rule: {
      SubExtL_uxth_and_shiftNode *node = new SubExtL_uxth_and_shiftNode();
      return node;
    }
  case SubExtL_uxtw_and_shift_rule: {
      SubExtL_uxtw_and_shiftNode *node = new SubExtL_uxtw_and_shiftNode();
      return node;
    }
  case AddExtI_uxtb_and_shift_rule: {
      AddExtI_uxtb_and_shiftNode *node = new AddExtI_uxtb_and_shiftNode();
      return node;
    }
  case AddExtI_uxtb_and_shift_0_rule: {
      AddExtI_uxtb_and_shift_0Node *node = new AddExtI_uxtb_and_shift_0Node();
      return node;
    }
  case AddExtI_uxth_and_shift_rule: {
      AddExtI_uxth_and_shiftNode *node = new AddExtI_uxth_and_shiftNode();
      return node;
    }
  case AddExtI_uxth_and_shift_0_rule: {
      AddExtI_uxth_and_shift_0Node *node = new AddExtI_uxth_and_shift_0Node();
      return node;
    }
  case SubExtI_uxtb_and_shift_rule: {
      SubExtI_uxtb_and_shiftNode *node = new SubExtI_uxtb_and_shiftNode();
      return node;
    }
  case SubExtI_uxth_and_shift_rule: {
      SubExtI_uxth_and_shiftNode *node = new SubExtI_uxth_and_shiftNode();
      return node;
    }
  case minI_reg_imm0_rule: {
      minI_reg_imm0Node *node = new minI_reg_imm0Node();
      return node;
    }
  case minI_imm0_reg_rule: {
      minI_imm0_regNode *node = new minI_imm0_regNode();
      return node;
    }
  case minI_reg_imm1_rule: {
      minI_reg_imm1Node *node = new minI_reg_imm1Node();
      return node;
    }
  case minI_imm1_reg_rule: {
      minI_imm1_regNode *node = new minI_imm1_regNode();
      return node;
    }
  case minI_reg_immM1_rule: {
      minI_reg_immM1Node *node = new minI_reg_immM1Node();
      return node;
    }
  case minI_immM1_reg_rule: {
      minI_immM1_regNode *node = new minI_immM1_regNode();
      return node;
    }
  case maxI_reg_imm0_rule: {
      maxI_reg_imm0Node *node = new maxI_reg_imm0Node();
      return node;
    }
  case maxI_imm0_reg_rule: {
      maxI_imm0_regNode *node = new maxI_imm0_regNode();
      return node;
    }
  case maxI_reg_imm1_rule: {
      maxI_reg_imm1Node *node = new maxI_reg_imm1Node();
      return node;
    }
  case maxI_imm1_reg_rule: {
      maxI_imm1_regNode *node = new maxI_imm1_regNode();
      return node;
    }
  case maxI_reg_immM1_rule: {
      maxI_reg_immM1Node *node = new maxI_reg_immM1Node();
      return node;
    }
  case maxI_immM1_reg_rule: {
      maxI_immM1_regNode *node = new maxI_immM1_regNode();
      return node;
    }
  case bits_reverse_I_rule: {
      bits_reverse_INode *node = new bits_reverse_INode();
      return node;
    }
  case bits_reverse_L_rule: {
      bits_reverse_LNode *node = new bits_reverse_LNode();
      return node;
    }
  case addF_reg_reg_rule: {
      addF_reg_regNode *node = new addF_reg_regNode();
      return node;
    }
  case addD_reg_reg_rule: {
      addD_reg_regNode *node = new addD_reg_regNode();
      return node;
    }
  case subF_reg_reg_rule: {
      subF_reg_regNode *node = new subF_reg_regNode();
      return node;
    }
  case subD_reg_reg_rule: {
      subD_reg_regNode *node = new subD_reg_regNode();
      return node;
    }
  case mulF_reg_reg_rule: {
      mulF_reg_regNode *node = new mulF_reg_regNode();
      return node;
    }
  case mulD_reg_reg_rule: {
      mulD_reg_regNode *node = new mulD_reg_regNode();
      return node;
    }
  case maddF_reg_reg_rule: {
      maddF_reg_regNode *node = new maddF_reg_regNode();
      return node;
    }
  case maddD_reg_reg_rule: {
      maddD_reg_regNode *node = new maddD_reg_regNode();
      return node;
    }
  case msubF_reg_reg_rule: {
      msubF_reg_regNode *node = new msubF_reg_regNode();
      return node;
    }
  case msubD_reg_reg_rule: {
      msubD_reg_regNode *node = new msubD_reg_regNode();
      return node;
    }
  case mnaddF_reg_reg_rule: {
      mnaddF_reg_regNode *node = new mnaddF_reg_regNode();
      return node;
    }
  case mnaddD_reg_reg_rule: {
      mnaddD_reg_regNode *node = new mnaddD_reg_regNode();
      return node;
    }
  case mnsubF_reg_reg_rule: {
      mnsubF_reg_regNode *node = new mnsubF_reg_regNode();
      return node;
    }
  case mnsubD_reg_reg_rule: {
      mnsubD_reg_regNode *node = new mnsubD_reg_regNode();
      return node;
    }
  case maxF_reg_reg_rule: {
      maxF_reg_regNode *node = new maxF_reg_regNode();
      return node;
    }
  case minF_reg_reg_rule: {
      minF_reg_regNode *node = new minF_reg_regNode();
      return node;
    }
  case maxD_reg_reg_rule: {
      maxD_reg_regNode *node = new maxD_reg_regNode();
      return node;
    }
  case minD_reg_reg_rule: {
      minD_reg_regNode *node = new minD_reg_regNode();
      return node;
    }
  case divF_reg_reg_rule: {
      divF_reg_regNode *node = new divF_reg_regNode();
      return node;
    }
  case divD_reg_reg_rule: {
      divD_reg_regNode *node = new divD_reg_regNode();
      return node;
    }
  case negF_reg_reg_rule: {
      negF_reg_regNode *node = new negF_reg_regNode();
      return node;
    }
  case negD_reg_reg_rule: {
      negD_reg_regNode *node = new negD_reg_regNode();
      return node;
    }
  case absI_reg_rule: {
      absI_regNode *node = new absI_regNode();
      return node;
    }
  case absL_reg_rule: {
      absL_regNode *node = new absL_regNode();
      return node;
    }
  case absF_reg_rule: {
      absF_regNode *node = new absF_regNode();
      return node;
    }
  case absD_reg_rule: {
      absD_regNode *node = new absD_regNode();
      return node;
    }
  case absdF_reg_rule: {
      absdF_regNode *node = new absdF_regNode();
      return node;
    }
  case absdD_reg_rule: {
      absdD_regNode *node = new absdD_regNode();
      return node;
    }
  case sqrtD_reg_rule: {
      sqrtD_regNode *node = new sqrtD_regNode();
      return node;
    }
  case sqrtF_reg_rule: {
      sqrtF_regNode *node = new sqrtF_regNode();
      return node;
    }
  case roundD_reg_rule: {
      roundD_regNode *node = new roundD_regNode();
      return node;
    }
  case copySignD_reg_rule: {
      copySignD_regNode *node = new copySignD_regNode();
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      return node;
    }
  case copySignF_reg_rule: {
      copySignF_regNode *node = new copySignF_regNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      return node;
    }
  case signumD_reg_rule: {
      signumD_regNode *node = new signumD_regNode();
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      return node;
    }
  case signumF_reg_rule: {
      signumF_regNode *node = new signumF_regNode();
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      return node;
    }
  case onspinwait_rule: {
      onspinwaitNode *node = new onspinwaitNode();
      return node;
    }
  case andI_reg_reg_rule: {
      andI_reg_regNode *node = new andI_reg_regNode();
      return node;
    }
  case andI_reg_imm_rule: {
      andI_reg_immNode *node = new andI_reg_immNode();
      return node;
    }
  case orI_reg_reg_rule: {
      orI_reg_regNode *node = new orI_reg_regNode();
      return node;
    }
  case orI_reg_imm_rule: {
      orI_reg_immNode *node = new orI_reg_immNode();
      return node;
    }
  case xorI_reg_reg_rule: {
      xorI_reg_regNode *node = new xorI_reg_regNode();
      return node;
    }
  case xorI_reg_imm_rule: {
      xorI_reg_immNode *node = new xorI_reg_immNode();
      return node;
    }
  case andL_reg_reg_rule: {
      andL_reg_regNode *node = new andL_reg_regNode();
      return node;
    }
  case andL_reg_imm_rule: {
      andL_reg_immNode *node = new andL_reg_immNode();
      return node;
    }
  case orL_reg_reg_rule: {
      orL_reg_regNode *node = new orL_reg_regNode();
      return node;
    }
  case orL_reg_imm_rule: {
      orL_reg_immNode *node = new orL_reg_immNode();
      return node;
    }
  case xorL_reg_reg_rule: {
      xorL_reg_regNode *node = new xorL_reg_regNode();
      return node;
    }
  case xorL_reg_imm_rule: {
      xorL_reg_immNode *node = new xorL_reg_immNode();
      return node;
    }
  case convI2L_reg_reg_rule: {
      convI2L_reg_regNode *node = new convI2L_reg_regNode();
      return node;
    }
  case convUI2L_reg_reg_rule: {
      convUI2L_reg_regNode *node = new convUI2L_reg_regNode();
      return node;
    }
  case convL2I_reg_rule: {
      convL2I_regNode *node = new convL2I_regNode();
      return node;
    }
  case convD2F_reg_rule: {
      convD2F_regNode *node = new convD2F_regNode();
      return node;
    }
  case convF2D_reg_rule: {
      convF2D_regNode *node = new convF2D_regNode();
      return node;
    }
  case convF2I_reg_reg_rule: {
      convF2I_reg_regNode *node = new convF2I_reg_regNode();
      return node;
    }
  case convF2L_reg_reg_rule: {
      convF2L_reg_regNode *node = new convF2L_reg_regNode();
      return node;
    }
  case convF2HF_reg_reg_rule: {
      convF2HF_reg_regNode *node = new convF2HF_reg_regNode();
      node->set_opnd_array(2, MachOperGenerator(VREGF));
      return node;
    }
  case convHF2F_reg_reg_rule: {
      convHF2F_reg_regNode *node = new convHF2F_reg_regNode();
      node->set_opnd_array(2, MachOperGenerator(VREGF));
      return node;
    }
  case convI2F_reg_reg_rule: {
      convI2F_reg_regNode *node = new convI2F_reg_regNode();
      return node;
    }
  case convL2F_reg_reg_rule: {
      convL2F_reg_regNode *node = new convL2F_reg_regNode();
      return node;
    }
  case convD2I_reg_reg_rule: {
      convD2I_reg_regNode *node = new convD2I_reg_regNode();
      return node;
    }
  case convD2L_reg_reg_rule: {
      convD2L_reg_regNode *node = new convD2L_reg_regNode();
      return node;
    }
  case convI2D_reg_reg_rule: {
      convI2D_reg_regNode *node = new convI2D_reg_regNode();
      return node;
    }
  case convL2D_reg_reg_rule: {
      convL2D_reg_regNode *node = new convL2D_reg_regNode();
      return node;
    }
  case round_double_reg_rule: {
      round_double_regNode *node = new round_double_regNode();
      node->set_opnd_array(2, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      return node;
    }
  case round_float_reg_rule: {
      round_float_regNode *node = new round_float_regNode();
      node->set_opnd_array(2, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      return node;
    }
  case MoveF2I_stack_reg_rule: {
      MoveF2I_stack_regNode *node = new MoveF2I_stack_regNode();
      return node;
    }
  case MoveI2F_stack_reg_rule: {
      MoveI2F_stack_regNode *node = new MoveI2F_stack_regNode();
      return node;
    }
  case MoveD2L_stack_reg_rule: {
      MoveD2L_stack_regNode *node = new MoveD2L_stack_regNode();
      return node;
    }
  case MoveL2D_stack_reg_rule: {
      MoveL2D_stack_regNode *node = new MoveL2D_stack_regNode();
      return node;
    }
  case MoveF2I_reg_stack_rule: {
      MoveF2I_reg_stackNode *node = new MoveF2I_reg_stackNode();
      return node;
    }
  case MoveI2F_reg_stack_rule: {
      MoveI2F_reg_stackNode *node = new MoveI2F_reg_stackNode();
      return node;
    }
  case MoveD2L_reg_stack_rule: {
      MoveD2L_reg_stackNode *node = new MoveD2L_reg_stackNode();
      return node;
    }
  case MoveL2D_reg_stack_rule: {
      MoveL2D_reg_stackNode *node = new MoveL2D_reg_stackNode();
      return node;
    }
  case MoveF2I_reg_reg_rule: {
      MoveF2I_reg_regNode *node = new MoveF2I_reg_regNode();
      return node;
    }
  case MoveI2F_reg_reg_rule: {
      MoveI2F_reg_regNode *node = new MoveI2F_reg_regNode();
      return node;
    }
  case MoveD2L_reg_reg_rule: {
      MoveD2L_reg_regNode *node = new MoveD2L_reg_regNode();
      return node;
    }
  case MoveL2D_reg_reg_rule: {
      MoveL2D_reg_regNode *node = new MoveL2D_reg_regNode();
      return node;
    }
  case clearArray_reg_reg_rule: {
      clearArray_reg_regNode *node = new clearArray_reg_regNode();
      return node;
    }
  case clearArray_imm_reg_rule: {
      clearArray_imm_regNode *node = new clearArray_imm_regNode();
      node->set_opnd_array(3, MachOperGenerator(IREGL_R11));
      return node;
    }
  case overflowAddI_reg_reg_rule: {
      overflowAddI_reg_regNode *node = new overflowAddI_reg_regNode();
      return node;
    }
  case overflowAddI_reg_imm_rule: {
      overflowAddI_reg_immNode *node = new overflowAddI_reg_immNode();
      return node;
    }
  case overflowAddL_reg_reg_rule: {
      overflowAddL_reg_regNode *node = new overflowAddL_reg_regNode();
      return node;
    }
  case overflowAddL_reg_imm_rule: {
      overflowAddL_reg_immNode *node = new overflowAddL_reg_immNode();
      return node;
    }
  case overflowSubI_reg_reg_rule: {
      overflowSubI_reg_regNode *node = new overflowSubI_reg_regNode();
      return node;
    }
  case overflowSubI_reg_imm_rule: {
      overflowSubI_reg_immNode *node = new overflowSubI_reg_immNode();
      return node;
    }
  case overflowSubL_reg_reg_rule: {
      overflowSubL_reg_regNode *node = new overflowSubL_reg_regNode();
      return node;
    }
  case overflowSubL_reg_imm_rule: {
      overflowSubL_reg_immNode *node = new overflowSubL_reg_immNode();
      return node;
    }
  case overflowNegI_reg_rule: {
      overflowNegI_regNode *node = new overflowNegI_regNode();
      return node;
    }
  case overflowNegL_reg_rule: {
      overflowNegL_regNode *node = new overflowNegL_regNode();
      return node;
    }
  case overflowMulI_reg_rule: {
      overflowMulI_regNode *node = new overflowMulI_regNode();
      return node;
    }
  case overflowMulI_reg_branch_rule: {
      overflowMulI_reg_branchNode *node = new overflowMulI_reg_branchNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case overflowMulL_reg_rule: {
      overflowMulL_regNode *node = new overflowMulL_regNode();
      return node;
    }
  case overflowMulL_reg_branch_rule: {
      overflowMulL_reg_branchNode *node = new overflowMulL_reg_branchNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case compI_reg_reg_rule: {
      compI_reg_regNode *node = new compI_reg_regNode();
      return node;
    }
  case compI_reg_immI0_rule: {
      compI_reg_immI0Node *node = new compI_reg_immI0Node();
      return node;
    }
  case compI_reg_immIAddSub_rule: {
      compI_reg_immIAddSubNode *node = new compI_reg_immIAddSubNode();
      return node;
    }
  case compI_reg_immI_rule: {
      compI_reg_immINode *node = new compI_reg_immINode();
      return node;
    }
  case compU_reg_reg_rule: {
      compU_reg_regNode *node = new compU_reg_regNode();
      return node;
    }
  case compU_reg_immI0_rule: {
      compU_reg_immI0Node *node = new compU_reg_immI0Node();
      return node;
    }
  case compU_reg_immIAddSub_rule: {
      compU_reg_immIAddSubNode *node = new compU_reg_immIAddSubNode();
      return node;
    }
  case compU_reg_immI_rule: {
      compU_reg_immINode *node = new compU_reg_immINode();
      return node;
    }
  case compL_reg_reg_rule: {
      compL_reg_regNode *node = new compL_reg_regNode();
      return node;
    }
  case compL_reg_immL0_rule: {
      compL_reg_immL0Node *node = new compL_reg_immL0Node();
      return node;
    }
  case compL_reg_immLAddSub_rule: {
      compL_reg_immLAddSubNode *node = new compL_reg_immLAddSubNode();
      return node;
    }
  case compL_reg_immL_rule: {
      compL_reg_immLNode *node = new compL_reg_immLNode();
      return node;
    }
  case compUL_reg_reg_rule: {
      compUL_reg_regNode *node = new compUL_reg_regNode();
      return node;
    }
  case compUL_reg_immL0_rule: {
      compUL_reg_immL0Node *node = new compUL_reg_immL0Node();
      return node;
    }
  case compUL_reg_immLAddSub_rule: {
      compUL_reg_immLAddSubNode *node = new compUL_reg_immLAddSubNode();
      return node;
    }
  case compUL_reg_immL_rule: {
      compUL_reg_immLNode *node = new compUL_reg_immLNode();
      return node;
    }
  case compP_reg_reg_rule: {
      compP_reg_regNode *node = new compP_reg_regNode();
      return node;
    }
  case compN_reg_reg_rule: {
      compN_reg_regNode *node = new compN_reg_regNode();
      return node;
    }
  case testP_reg_rule: {
      testP_regNode *node = new testP_regNode();
      return node;
    }
  case testN_reg_rule: {
      testN_regNode *node = new testN_regNode();
      return node;
    }
  case compF_reg_reg_rule: {
      compF_reg_regNode *node = new compF_reg_regNode();
      return node;
    }
  case compF_reg_zero_rule: {
      compF_reg_zeroNode *node = new compF_reg_zeroNode();
      return node;
    }
  case compD_reg_reg_rule: {
      compD_reg_regNode *node = new compD_reg_regNode();
      return node;
    }
  case compD_reg_zero_rule: {
      compD_reg_zeroNode *node = new compD_reg_zeroNode();
      return node;
    }
  case compF3_reg_reg_rule: {
      compF3_reg_regNode *node = new compF3_reg_regNode();
      return node;
    }
  case compD3_reg_reg_rule: {
      compD3_reg_regNode *node = new compD3_reg_regNode();
      return node;
    }
  case compF3_reg_immF0_rule: {
      compF3_reg_immF0Node *node = new compF3_reg_immF0Node();
      return node;
    }
  case compD3_reg_immD0_rule: {
      compD3_reg_immD0Node *node = new compD3_reg_immD0Node();
      return node;
    }
  case cmpLTMask_reg_reg_rule: {
      cmpLTMask_reg_regNode *node = new cmpLTMask_reg_regNode();
      return node;
    }
  case cmpLTMask_reg_zero_rule: {
      cmpLTMask_reg_zeroNode *node = new cmpLTMask_reg_zeroNode();
      return node;
    }
  case minI_reg_reg_rule: {
      minI_reg_regNode *node = new minI_reg_regNode();
      return node;
    }
  case maxI_reg_reg_rule: {
      maxI_reg_regNode *node = new maxI_reg_regNode();
      return node;
    }
  case branch_rule: {
      branchNode *node = new branchNode();
      node->set_opnd_array(1, MachOperGenerator(LABEL));
      return node;
    }
  case branchCon_rule: {
      branchConNode *node = new branchConNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case branchConU_rule: {
      branchConUNode *node = new branchConUNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpI_imm0_branch_rule: {
      cmpI_imm0_branchNode *node = new cmpI_imm0_branchNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpL_imm0_branch_rule: {
      cmpL_imm0_branchNode *node = new cmpL_imm0_branchNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpP_imm0_branch_rule: {
      cmpP_imm0_branchNode *node = new cmpP_imm0_branchNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpN_imm0_branch_rule: {
      cmpN_imm0_branchNode *node = new cmpN_imm0_branchNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpP_narrowOop_imm0_branch_rule: {
      cmpP_narrowOop_imm0_branchNode *node = new cmpP_narrowOop_imm0_branchNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpUI_imm0_branch_rule: {
      cmpUI_imm0_branchNode *node = new cmpUI_imm0_branchNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpUL_imm0_branch_rule: {
      cmpUL_imm0_branchNode *node = new cmpUL_imm0_branchNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpL_branch_sign_rule: {
      cmpL_branch_signNode *node = new cmpL_branch_signNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpI_branch_sign_rule: {
      cmpI_branch_signNode *node = new cmpI_branch_signNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpL_branch_bit_rule: {
      cmpL_branch_bitNode *node = new cmpL_branch_bitNode();
      node->set_opnd_array(5, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpI_branch_bit_rule: {
      cmpI_branch_bitNode *node = new cmpI_branch_bitNode();
      node->set_opnd_array(5, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case far_cmpL_branch_sign_rule: {
      far_cmpL_branch_signNode *node = new far_cmpL_branch_signNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case far_cmpI_branch_sign_rule: {
      far_cmpI_branch_signNode *node = new far_cmpI_branch_signNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case far_cmpL_branch_bit_rule: {
      far_cmpL_branch_bitNode *node = new far_cmpL_branch_bitNode();
      node->set_opnd_array(5, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case far_cmpI_branch_bit_rule: {
      far_cmpI_branch_bitNode *node = new far_cmpI_branch_bitNode();
      node->set_opnd_array(5, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpL_and_rule: {
      cmpL_andNode *node = new cmpL_andNode();
      return node;
    }
  case cmpI_and_rule: {
      cmpI_andNode *node = new cmpI_andNode();
      return node;
    }
  case cmpL_and_reg_rule: {
      cmpL_and_regNode *node = new cmpL_and_regNode();
      return node;
    }
  case cmpI_and_reg_rule: {
      cmpI_and_regNode *node = new cmpI_and_regNode();
      return node;
    }
  case branchLoopEnd_rule: {
      branchLoopEndNode *node = new branchLoopEndNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpFastLock_rule: {
      cmpFastLockNode *node = new cmpFastLockNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGPNOSP));
      node->_rtm_counters = _leaf->as_FastLock()->rtm_counters();
      node->_stack_rtm_counters = _leaf->as_FastLock()->stack_rtm_counters();
      return node;
    }
  case cmpFastUnlock_rule: {
      cmpFastUnlockNode *node = new cmpFastUnlockNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      return node;
    }
  case cmpFastLockLightweight_rule: {
      cmpFastLockLightweightNode *node = new cmpFastLockLightweightNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->_rtm_counters = _leaf->as_FastLock()->rtm_counters();
      node->_stack_rtm_counters = _leaf->as_FastLock()->stack_rtm_counters();
      return node;
    }
  case cmpFastUnlockLightweight_rule: {
      cmpFastUnlockLightweightNode *node = new cmpFastUnlockLightweightNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      return node;
    }
  case safePoint_rule: {
      safePointNode *node = new safePointNode();
      return node;
    }
  case CallStaticJavaDirect_rule: {
      CallStaticJavaDirectNode *node = new CallStaticJavaDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallDynamicJavaDirect_rule: {
      CallDynamicJavaDirectNode *node = new CallDynamicJavaDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallRuntimeDirect_rule: {
      CallRuntimeDirectNode *node = new CallRuntimeDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallLeafDirect_rule: {
      CallLeafDirectNode *node = new CallLeafDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallLeafNoFPDirect_rule: {
      CallLeafNoFPDirectNode *node = new CallLeafNoFPDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case TailCalljmpInd_rule: {
      TailCalljmpIndNode *node = new TailCalljmpIndNode();
      return node;
    }
  case TailjmpInd_rule: {
      TailjmpIndNode *node = new TailjmpIndNode();
      return node;
    }
  case CreateException_rule: {
      CreateExceptionNode *node = new CreateExceptionNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case RethrowException_rule: {
      RethrowExceptionNode *node = new RethrowExceptionNode();
      return node;
    }
  case Ret_rule: {
      RetNode *node = new RetNode();
      return node;
    }
  case ShouldNotReachHere_rule: {
      ShouldNotReachHereNode *node = new ShouldNotReachHereNode();
      node->_halt_reason = _leaf->as_Halt()->_halt_reason;
      node->_reachable   = _leaf->as_Halt()->_reachable;
      return node;
    }
  case partialSubtypeCheck_rule: {
      partialSubtypeCheckNode *node = new partialSubtypeCheckNode();
      return node;
    }
  case partialSubtypeCheckVsZero_rule: {
      partialSubtypeCheckVsZeroNode *node = new partialSubtypeCheckVsZeroNode();
      return node;
    }
  case string_compareU_rule: {
      string_compareUNode *node = new string_compareUNode();
      return node;
    }
  case string_compareL_rule: {
      string_compareLNode *node = new string_compareLNode();
      return node;
    }
  case string_compareUL_rule: {
      string_compareULNode *node = new string_compareULNode();
      return node;
    }
  case string_compareLU_rule: {
      string_compareLUNode *node = new string_compareLUNode();
      return node;
    }
  case string_compareLL_sve_rule: {
      string_compareLL_sveNode *node = new string_compareLL_sveNode();
      node->set_opnd_array(5, MachOperGenerator(IREGP_R10));
      node->set_opnd_array(6, MachOperGenerator(IREGL_R11));
      node->set_opnd_array(7, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(8, MachOperGenerator(VREGD_V1));
      node->set_opnd_array(9, MachOperGenerator(PREGGOV_P0));
      node->set_opnd_array(10, MachOperGenerator(PREGGOV_P1));
      return node;
    }
  case string_compareLU_sve_rule: {
      string_compareLU_sveNode *node = new string_compareLU_sveNode();
      node->set_opnd_array(5, MachOperGenerator(IREGP_R10));
      node->set_opnd_array(6, MachOperGenerator(IREGL_R11));
      node->set_opnd_array(7, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(8, MachOperGenerator(VREGD_V1));
      node->set_opnd_array(9, MachOperGenerator(PREGGOV_P0));
      node->set_opnd_array(10, MachOperGenerator(PREGGOV_P1));
      return node;
    }
  case string_compareUL_sve_rule: {
      string_compareUL_sveNode *node = new string_compareUL_sveNode();
      node->set_opnd_array(5, MachOperGenerator(IREGP_R10));
      node->set_opnd_array(6, MachOperGenerator(IREGL_R11));
      node->set_opnd_array(7, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(8, MachOperGenerator(VREGD_V1));
      node->set_opnd_array(9, MachOperGenerator(PREGGOV_P0));
      node->set_opnd_array(10, MachOperGenerator(PREGGOV_P1));
      return node;
    }
  case string_compareUU_sve_rule: {
      string_compareUU_sveNode *node = new string_compareUU_sveNode();
      node->set_opnd_array(5, MachOperGenerator(IREGP_R10));
      node->set_opnd_array(6, MachOperGenerator(IREGL_R11));
      node->set_opnd_array(7, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(8, MachOperGenerator(VREGD_V1));
      node->set_opnd_array(9, MachOperGenerator(PREGGOV_P0));
      node->set_opnd_array(10, MachOperGenerator(PREGGOV_P1));
      return node;
    }
  case string_indexofUU_rule: {
      string_indexofUUNode *node = new string_indexofUUNode();
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(7, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(8, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(9, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(10, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(11, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(12, MachOperGenerator(VREGD_V1));
      return node;
    }
  case string_indexofLL_rule: {
      string_indexofLLNode *node = new string_indexofLLNode();
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(7, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(8, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(9, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(10, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(11, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(12, MachOperGenerator(VREGD_V1));
      return node;
    }
  case string_indexofUL_rule: {
      string_indexofULNode *node = new string_indexofULNode();
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(7, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(8, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(9, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(10, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(11, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(12, MachOperGenerator(VREGD_V1));
      return node;
    }
  case string_indexof_conUU_rule: {
      string_indexof_conUUNode *node = new string_indexof_conUUNode();
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(7, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(8, MachOperGenerator(IREGINOSP));
      return node;
    }
  case string_indexof_conLL_rule: {
      string_indexof_conLLNode *node = new string_indexof_conLLNode();
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(7, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(8, MachOperGenerator(IREGINOSP));
      return node;
    }
  case string_indexof_conUL_rule: {
      string_indexof_conULNode *node = new string_indexof_conULNode();
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(7, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(8, MachOperGenerator(IREGINOSP));
      return node;
    }
  case string_indexof_char_rule: {
      string_indexof_charNode *node = new string_indexof_charNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      return node;
    }
  case stringL_indexof_char_rule: {
      stringL_indexof_charNode *node = new stringL_indexof_charNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      return node;
    }
  case stringL_indexof_char_sve_rule: {
      stringL_indexof_char_sveNode *node = new stringL_indexof_char_sveNode();
      node->set_opnd_array(4, MachOperGenerator(VECA));
      node->set_opnd_array(5, MachOperGenerator(VECA));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->set_opnd_array(7, MachOperGenerator(PREG));
      return node;
    }
  case stringU_indexof_char_sve_rule: {
      stringU_indexof_char_sveNode *node = new stringU_indexof_char_sveNode();
      node->set_opnd_array(4, MachOperGenerator(VECA));
      node->set_opnd_array(5, MachOperGenerator(VECA));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->set_opnd_array(7, MachOperGenerator(PREG));
      return node;
    }
  case string_equalsL_rule: {
      string_equalsLNode *node = new string_equalsLNode();
      return node;
    }
  case array_equalsB_rule: {
      array_equalsBNode *node = new array_equalsBNode();
      node->set_opnd_array(3, MachOperGenerator(IREGP_R3));
      node->set_opnd_array(4, MachOperGenerator(IREGP_R4));
      node->set_opnd_array(5, MachOperGenerator(IREGP_R5));
      node->set_opnd_array(6, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(7, MachOperGenerator(VREGD_V1));
      node->set_opnd_array(8, MachOperGenerator(VREGD_V2));
      node->set_opnd_array(9, MachOperGenerator(VREGD_V3));
      node->set_opnd_array(10, MachOperGenerator(VREGD_V4));
      node->set_opnd_array(11, MachOperGenerator(VREGD_V5));
      node->set_opnd_array(12, MachOperGenerator(VREGD_V6));
      node->set_opnd_array(13, MachOperGenerator(VREGD_V7));
      return node;
    }
  case array_equalsC_rule: {
      array_equalsCNode *node = new array_equalsCNode();
      node->set_opnd_array(3, MachOperGenerator(IREGP_R3));
      node->set_opnd_array(4, MachOperGenerator(IREGP_R4));
      node->set_opnd_array(5, MachOperGenerator(IREGP_R5));
      node->set_opnd_array(6, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(7, MachOperGenerator(VREGD_V1));
      node->set_opnd_array(8, MachOperGenerator(VREGD_V2));
      node->set_opnd_array(9, MachOperGenerator(VREGD_V3));
      node->set_opnd_array(10, MachOperGenerator(VREGD_V4));
      node->set_opnd_array(11, MachOperGenerator(VREGD_V5));
      node->set_opnd_array(12, MachOperGenerator(VREGD_V6));
      node->set_opnd_array(13, MachOperGenerator(VREGD_V7));
      return node;
    }
  case count_positives_rule: {
      count_positivesNode *node = new count_positivesNode();
      return node;
    }
  case string_compress_rule: {
      string_compressNode *node = new string_compressNode();
      node->set_opnd_array(4, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(5, MachOperGenerator(VREGD_V1));
      node->set_opnd_array(6, MachOperGenerator(VREGD_V2));
      node->set_opnd_array(7, MachOperGenerator(VREGD_V3));
      node->set_opnd_array(8, MachOperGenerator(VREGD_V4));
      node->set_opnd_array(9, MachOperGenerator(VREGD_V5));
      return node;
    }
  case string_inflate_rule: {
      string_inflateNode *node = new string_inflateNode();
      node->set_opnd_array(4, MachOperGenerator(IREGP_R3));
      node->set_opnd_array(5, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(6, MachOperGenerator(VREGD_V1));
      node->set_opnd_array(7, MachOperGenerator(VREGD_V2));
      node->set_opnd_array(8, MachOperGenerator(VREGD_V3));
      node->set_opnd_array(9, MachOperGenerator(VREGD_V4));
      node->set_opnd_array(10, MachOperGenerator(VREGD_V5));
      node->set_opnd_array(11, MachOperGenerator(VREGD_V6));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encode_iso_array_rule: {
      encode_iso_arrayNode *node = new encode_iso_arrayNode();
      return node;
    }
  case encode_ascii_array_rule: {
      encode_ascii_arrayNode *node = new encode_ascii_arrayNode();
      return node;
    }
  case compressBitsI_reg_rule: {
      compressBitsI_regNode *node = new compressBitsI_regNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      node->set_opnd_array(5, MachOperGenerator(VREGF));
      return node;
    }
  case compressBitsI_memcon_rule: {
      compressBitsI_memconNode *node = new compressBitsI_memconNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      node->set_opnd_array(5, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compressBitsL_reg_rule: {
      compressBitsL_regNode *node = new compressBitsL_regNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      return node;
    }
  case compressBitsL_memcon_rule: {
      compressBitsL_memconNode *node = new compressBitsL_memconNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      node->set_opnd_array(5, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case expandBitsI_reg_rule: {
      expandBitsI_regNode *node = new expandBitsI_regNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      node->set_opnd_array(5, MachOperGenerator(VREGF));
      return node;
    }
  case expandBitsI_memcon_rule: {
      expandBitsI_memconNode *node = new expandBitsI_memconNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      node->set_opnd_array(5, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case expandBitsL_reg_rule: {
      expandBitsL_regNode *node = new expandBitsL_regNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      return node;
    }
  case expandBitsL_memcon_rule: {
      expandBitsL_memconNode *node = new expandBitsL_memconNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      node->set_opnd_array(5, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case tlsLoadP_rule: {
      tlsLoadPNode *node = new tlsLoadPNode();
      return node;
    }
  case loadV2_rule: {
      loadV2Node *node = new loadV2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV2_rule: {
      storeV2Node *node = new storeV2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV4_rule: {
      loadV4Node *node = new loadV4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV4_rule: {
      storeV4Node *node = new storeV4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV8_rule: {
      loadV8Node *node = new loadV8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV8_rule: {
      storeV8Node *node = new storeV8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV16_rule: {
      loadV16Node *node = new loadV16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV16_rule: {
      storeV16Node *node = new storeV16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV_rule: {
      loadVNode *node = new loadVNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV_rule: {
      storeVNode *node = new storeVNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV_masked_rule: {
      loadV_maskedNode *node = new loadV_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV_masked_rule: {
      storeV_maskedNode *node = new storeV_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadcon_rule: {
      vloadconNode *node = new vloadconNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddB_rule: {
      vaddBNode *node = new vaddBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddS_rule: {
      vaddSNode *node = new vaddSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddI_rule: {
      vaddINode *node = new vaddINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddL_rule: {
      vaddLNode *node = new vaddLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddF_rule: {
      vaddFNode *node = new vaddFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddD_rule: {
      vaddDNode *node = new vaddDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddB_masked_rule: {
      vaddB_maskedNode *node = new vaddB_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddS_masked_rule: {
      vaddS_maskedNode *node = new vaddS_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddI_masked_rule: {
      vaddI_maskedNode *node = new vaddI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddL_masked_rule: {
      vaddL_maskedNode *node = new vaddL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddF_masked_rule: {
      vaddF_maskedNode *node = new vaddF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddD_masked_rule: {
      vaddD_maskedNode *node = new vaddD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddImmB_rule: {
      vaddImmBNode *node = new vaddImmBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddImmB_0_rule: {
      vaddImmB_0Node *node = new vaddImmB_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddImmS_rule: {
      vaddImmSNode *node = new vaddImmSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddImmS_0_rule: {
      vaddImmS_0Node *node = new vaddImmS_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddImmI_rule: {
      vaddImmINode *node = new vaddImmINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddImmI_0_rule: {
      vaddImmI_0Node *node = new vaddImmI_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddImmL_rule: {
      vaddImmLNode *node = new vaddImmLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddImmL_0_rule: {
      vaddImmL_0Node *node = new vaddImmL_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubB_rule: {
      vsubBNode *node = new vsubBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubS_rule: {
      vsubSNode *node = new vsubSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubI_rule: {
      vsubINode *node = new vsubINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubL_rule: {
      vsubLNode *node = new vsubLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubF_rule: {
      vsubFNode *node = new vsubFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubD_rule: {
      vsubDNode *node = new vsubDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubB_masked_rule: {
      vsubB_maskedNode *node = new vsubB_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubS_masked_rule: {
      vsubS_maskedNode *node = new vsubS_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubI_masked_rule: {
      vsubI_maskedNode *node = new vsubI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubL_masked_rule: {
      vsubL_maskedNode *node = new vsubL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubF_masked_rule: {
      vsubF_maskedNode *node = new vsubF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubD_masked_rule: {
      vsubD_maskedNode *node = new vsubD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulB_neon_rule: {
      vmulB_neonNode *node = new vmulB_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulB_sve_rule: {
      vmulB_sveNode *node = new vmulB_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulS_neon_rule: {
      vmulS_neonNode *node = new vmulS_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulS_sve_rule: {
      vmulS_sveNode *node = new vmulS_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulI_neon_rule: {
      vmulI_neonNode *node = new vmulI_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulI_sve_rule: {
      vmulI_sveNode *node = new vmulI_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulL_neon_rule: {
      vmulL_neonNode *node = new vmulL_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulL_sve_rule: {
      vmulL_sveNode *node = new vmulL_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulF_rule: {
      vmulFNode *node = new vmulFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulD_rule: {
      vmulDNode *node = new vmulDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulB_masked_rule: {
      vmulB_maskedNode *node = new vmulB_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulS_masked_rule: {
      vmulS_maskedNode *node = new vmulS_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulI_masked_rule: {
      vmulI_maskedNode *node = new vmulI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulL_masked_rule: {
      vmulL_maskedNode *node = new vmulL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulF_masked_rule: {
      vmulF_maskedNode *node = new vmulF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulD_masked_rule: {
      vmulD_maskedNode *node = new vmulD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivF_neon_rule: {
      vdivF_neonNode *node = new vdivF_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivF_sve_rule: {
      vdivF_sveNode *node = new vdivF_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivD_neon_rule: {
      vdivD_neonNode *node = new vdivD_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivD_sve_rule: {
      vdivD_sveNode *node = new vdivD_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivF_masked_rule: {
      vdivF_maskedNode *node = new vdivF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivD_masked_rule: {
      vdivD_maskedNode *node = new vdivD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_rule: {
      vandNode *node = new vandNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_masked_rule: {
      vand_maskedNode *node = new vand_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandImmB_rule: {
      vandImmBNode *node = new vandImmBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandImmB_0_rule: {
      vandImmB_0Node *node = new vandImmB_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandImmS_rule: {
      vandImmSNode *node = new vandImmSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandImmS_0_rule: {
      vandImmS_0Node *node = new vandImmS_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandImmI_rule: {
      vandImmINode *node = new vandImmINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandImmI_0_rule: {
      vandImmI_0Node *node = new vandImmI_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandImmL_rule: {
      vandImmLNode *node = new vandImmLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandImmL_0_rule: {
      vandImmL_0Node *node = new vandImmL_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor_rule: {
      vorNode *node = new vorNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor_masked_rule: {
      vor_maskedNode *node = new vor_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorImmB_rule: {
      vorImmBNode *node = new vorImmBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorImmB_0_rule: {
      vorImmB_0Node *node = new vorImmB_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorImmS_rule: {
      vorImmSNode *node = new vorImmSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorImmS_0_rule: {
      vorImmS_0Node *node = new vorImmS_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorImmI_rule: {
      vorImmINode *node = new vorImmINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorImmI_0_rule: {
      vorImmI_0Node *node = new vorImmI_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorImmL_rule: {
      vorImmLNode *node = new vorImmLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorImmL_0_rule: {
      vorImmL_0Node *node = new vorImmL_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor_rule: {
      vxorNode *node = new vxorNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor_masked_rule: {
      vxor_maskedNode *node = new vxor_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorImmB_rule: {
      vxorImmBNode *node = new vxorImmBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorImmB_0_rule: {
      vxorImmB_0Node *node = new vxorImmB_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorImmS_rule: {
      vxorImmSNode *node = new vxorImmSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorImmS_0_rule: {
      vxorImmS_0Node *node = new vxorImmS_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorImmI_rule: {
      vxorImmINode *node = new vxorImmINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorImmI_0_rule: {
      vxorImmI_0Node *node = new vxorImmI_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorImmL_rule: {
      vxorImmLNode *node = new vxorImmLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorImmL_0_rule: {
      vxorImmL_0Node *node = new vxorImmL_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case veor3_neon_rule: {
      veor3_neonNode *node = new veor3_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case veor3_neon_0_rule: {
      veor3_neon_0Node *node = new veor3_neon_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case veor3_sve_rule: {
      veor3_sveNode *node = new veor3_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case veor3_sve_0_rule: {
      veor3_sve_0Node *node = new veor3_sve_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnotI_rule: {
      vnotINode *node = new vnotINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnotI_0_rule: {
      vnotI_0Node *node = new vnotI_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnotL_rule: {
      vnotLNode *node = new vnotLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnotL_0_rule: {
      vnotL_0Node *node = new vnotL_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnotI_masked_rule: {
      vnotI_maskedNode *node = new vnotI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnotL_masked_rule: {
      vnotL_maskedNode *node = new vnotL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_rule: {
      vand_notINode *node = new vand_notINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_1_rule: {
      vand_notI_1Node *node = new vand_notI_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_0_rule: {
      vand_notI_0Node *node = new vand_notI_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_2_rule: {
      vand_notI_2Node *node = new vand_notI_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notL_rule: {
      vand_notLNode *node = new vand_notLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notL_1_rule: {
      vand_notL_1Node *node = new vand_notL_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notL_0_rule: {
      vand_notL_0Node *node = new vand_notL_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notL_2_rule: {
      vand_notL_2Node *node = new vand_notL_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_masked_rule: {
      vand_notI_maskedNode *node = new vand_notI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_masked_0_rule: {
      vand_notI_masked_0Node *node = new vand_notI_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notL_masked_rule: {
      vand_notL_maskedNode *node = new vand_notL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notL_masked_0_rule: {
      vand_notL_masked_0Node *node = new vand_notL_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsB_rule: {
      vabsBNode *node = new vabsBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsS_rule: {
      vabsSNode *node = new vabsSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsI_rule: {
      vabsINode *node = new vabsINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsL_rule: {
      vabsLNode *node = new vabsLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsF_rule: {
      vabsFNode *node = new vabsFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsD_rule: {
      vabsDNode *node = new vabsDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsB_masked_rule: {
      vabsB_maskedNode *node = new vabsB_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsS_masked_rule: {
      vabsS_maskedNode *node = new vabsS_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsI_masked_rule: {
      vabsI_maskedNode *node = new vabsI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsL_masked_rule: {
      vabsL_maskedNode *node = new vabsL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsF_masked_rule: {
      vabsF_maskedNode *node = new vabsF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsD_masked_rule: {
      vabsD_maskedNode *node = new vabsD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfabd_neon_rule: {
      vfabd_neonNode *node = new vfabd_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfabd_neon_0_rule: {
      vfabd_neon_0Node *node = new vfabd_neon_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfabd_sve_rule: {
      vfabd_sveNode *node = new vfabd_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfabd_sve_0_rule: {
      vfabd_sve_0Node *node = new vfabd_sve_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfabd_masked_rule: {
      vfabd_maskedNode *node = new vfabd_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfabd_masked_0_rule: {
      vfabd_masked_0Node *node = new vfabd_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnegI_rule: {
      vnegINode *node = new vnegINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnegL_rule: {
      vnegLNode *node = new vnegLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnegF_rule: {
      vnegFNode *node = new vnegFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnegD_rule: {
      vnegDNode *node = new vnegDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnegI_masked_rule: {
      vnegI_maskedNode *node = new vnegI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnegL_masked_rule: {
      vnegL_maskedNode *node = new vnegL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnegF_masked_rule: {
      vnegF_maskedNode *node = new vnegF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnegD_masked_rule: {
      vnegD_maskedNode *node = new vnegD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrtF_rule: {
      vsqrtFNode *node = new vsqrtFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrtD_rule: {
      vsqrtDNode *node = new vsqrtDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrtF_masked_rule: {
      vsqrtF_maskedNode *node = new vsqrtF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrtD_masked_rule: {
      vsqrtD_maskedNode *node = new vsqrtD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vminL_neon_rule: {
      vminL_neonNode *node = new vminL_neonNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vminL_sve_rule: {
      vminL_sveNode *node = new vminL_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin_neon_rule: {
      vmin_neonNode *node = new vmin_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin_sve_rule: {
      vmin_sveNode *node = new vmin_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin_masked_rule: {
      vmin_maskedNode *node = new vmin_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaxL_neon_rule: {
      vmaxL_neonNode *node = new vmaxL_neonNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaxL_sve_rule: {
      vmaxL_sveNode *node = new vmaxL_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax_neon_rule: {
      vmax_neonNode *node = new vmax_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax_sve_rule: {
      vmax_sveNode *node = new vmax_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax_masked_rule: {
      vmax_maskedNode *node = new vmax_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla_rule: {
      vmlaNode *node = new vmlaNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla_0_rule: {
      vmla_0Node *node = new vmla_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla_1_rule: {
      vmla_1Node *node = new vmla_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla_2_rule: {
      vmla_2Node *node = new vmla_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla_3_rule: {
      vmla_3Node *node = new vmla_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla_4_rule: {
      vmla_4Node *node = new vmla_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlaL_rule: {
      vmlaLNode *node = new vmlaLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlaL_0_rule: {
      vmlaL_0Node *node = new vmlaL_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla_masked_rule: {
      vmla_maskedNode *node = new vmla_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla_masked_0_rule: {
      vmla_masked_0Node *node = new vmla_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla_masked_1_rule: {
      vmla_masked_1Node *node = new vmla_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla_masked_2_rule: {
      vmla_masked_2Node *node = new vmla_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmla_rule: {
      vfmlaNode *node = new vfmlaNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmla_0_rule: {
      vfmla_0Node *node = new vfmla_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmad_masked_rule: {
      vfmad_maskedNode *node = new vfmad_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmad_masked_0_rule: {
      vfmad_masked_0Node *node = new vfmad_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls_rule: {
      vmlsNode *node = new vmlsNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls_0_rule: {
      vmls_0Node *node = new vmls_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls_1_rule: {
      vmls_1Node *node = new vmls_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlsL_rule: {
      vmlsLNode *node = new vmlsLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls_masked_rule: {
      vmls_maskedNode *node = new vmls_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls_masked_0_rule: {
      vmls_masked_0Node *node = new vmls_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls_masked_1_rule: {
      vmls_masked_1Node *node = new vmls_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls_masked_2_rule: {
      vmls_masked_2Node *node = new vmls_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmls_rule: {
      vfmlsNode *node = new vfmlsNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmls_0_rule: {
      vfmls_0Node *node = new vfmls_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmsb_masked_rule: {
      vfmsb_maskedNode *node = new vfmsb_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmsb_masked_0_rule: {
      vfmsb_masked_0Node *node = new vfmsb_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmla_rule: {
      vfnmlaNode *node = new vfnmlaNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmla_0_rule: {
      vfnmla_0Node *node = new vfnmla_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmad_masked_rule: {
      vfnmad_maskedNode *node = new vfnmad_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmad_masked_0_rule: {
      vfnmad_masked_0Node *node = new vfnmad_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmls_rule: {
      vfnmlsNode *node = new vfnmlsNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmls_0_rule: {
      vfnmls_0Node *node = new vfnmls_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmsb_masked_rule: {
      vfnmsb_maskedNode *node = new vfnmsb_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmsb_masked_0_rule: {
      vfnmsb_masked_0Node *node = new vfnmsb_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmuladdS2I_rule: {
      vmuladdS2INode *node = new vmuladdS2INode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcntL_rule: {
      vshiftcntLNode *node = new vshiftcntLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcntR_rule: {
      vshiftcntRNode *node = new vshiftcntRNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_neon_rule: {
      vlsl_neonNode *node = new vlsl_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_neon_0_rule: {
      vlsl_neon_0Node *node = new vlsl_neon_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_neon_1_rule: {
      vlsl_neon_1Node *node = new vlsl_neon_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_neon_2_rule: {
      vlsl_neon_2Node *node = new vlsl_neon_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_sve_rule: {
      vlsl_sveNode *node = new vlsl_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_sve_0_rule: {
      vlsl_sve_0Node *node = new vlsl_sve_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_sve_1_rule: {
      vlsl_sve_1Node *node = new vlsl_sve_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_sve_2_rule: {
      vlsl_sve_2Node *node = new vlsl_sve_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_neon_rule: {
      vasr_neonNode *node = new vasr_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_neon_0_rule: {
      vasr_neon_0Node *node = new vasr_neon_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_neon_1_rule: {
      vasr_neon_1Node *node = new vasr_neon_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_neon_2_rule: {
      vasr_neon_2Node *node = new vasr_neon_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_neon_var_rule: {
      vasr_neon_varNode *node = new vasr_neon_varNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_neon_var_0_rule: {
      vasr_neon_var_0Node *node = new vasr_neon_var_0Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_neon_var_1_rule: {
      vasr_neon_var_1Node *node = new vasr_neon_var_1Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_neon_var_2_rule: {
      vasr_neon_var_2Node *node = new vasr_neon_var_2Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_sve_rule: {
      vasr_sveNode *node = new vasr_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_sve_0_rule: {
      vasr_sve_0Node *node = new vasr_sve_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_sve_1_rule: {
      vasr_sve_1Node *node = new vasr_sve_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_sve_2_rule: {
      vasr_sve_2Node *node = new vasr_sve_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_neon_rule: {
      vlsr_neonNode *node = new vlsr_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_neon_0_rule: {
      vlsr_neon_0Node *node = new vlsr_neon_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_neon_1_rule: {
      vlsr_neon_1Node *node = new vlsr_neon_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_neon_2_rule: {
      vlsr_neon_2Node *node = new vlsr_neon_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_neon_var_rule: {
      vlsr_neon_varNode *node = new vlsr_neon_varNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_neon_var_0_rule: {
      vlsr_neon_var_0Node *node = new vlsr_neon_var_0Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_neon_var_1_rule: {
      vlsr_neon_var_1Node *node = new vlsr_neon_var_1Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_neon_var_2_rule: {
      vlsr_neon_var_2Node *node = new vlsr_neon_var_2Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_sve_rule: {
      vlsr_sveNode *node = new vlsr_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_sve_0_rule: {
      vlsr_sve_0Node *node = new vlsr_sve_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_sve_1_rule: {
      vlsr_sve_1Node *node = new vlsr_sve_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_sve_2_rule: {
      vlsr_sve_2Node *node = new vlsr_sve_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_imm_rule: {
      vlsl_immNode *node = new vlsl_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_imm_0_rule: {
      vlsl_imm_0Node *node = new vlsl_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_imm_1_rule: {
      vlsl_imm_1Node *node = new vlsl_imm_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_imm_2_rule: {
      vlsl_imm_2Node *node = new vlsl_imm_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_imm_rule: {
      vasr_immNode *node = new vasr_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_imm_0_rule: {
      vasr_imm_0Node *node = new vasr_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_imm_1_rule: {
      vasr_imm_1Node *node = new vasr_imm_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_imm_2_rule: {
      vasr_imm_2Node *node = new vasr_imm_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_imm_rule: {
      vlsr_immNode *node = new vlsr_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_imm_0_rule: {
      vlsr_imm_0Node *node = new vlsr_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_imm_1_rule: {
      vlsr_imm_1Node *node = new vlsr_imm_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_imm_2_rule: {
      vlsr_imm_2Node *node = new vlsr_imm_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasra_imm_rule: {
      vasra_immNode *node = new vasra_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasra_imm_0_rule: {
      vasra_imm_0Node *node = new vasra_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasra_imm_1_rule: {
      vasra_imm_1Node *node = new vasra_imm_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasra_imm_2_rule: {
      vasra_imm_2Node *node = new vasra_imm_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasra_imm_3_rule: {
      vasra_imm_3Node *node = new vasra_imm_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasra_imm_4_rule: {
      vasra_imm_4Node *node = new vasra_imm_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasra_imm_5_rule: {
      vasra_imm_5Node *node = new vasra_imm_5Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasra_imm_6_rule: {
      vasra_imm_6Node *node = new vasra_imm_6Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsra_imm_rule: {
      vlsra_immNode *node = new vlsra_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsra_imm_0_rule: {
      vlsra_imm_0Node *node = new vlsra_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsra_imm_1_rule: {
      vlsra_imm_1Node *node = new vlsra_imm_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsra_imm_2_rule: {
      vlsra_imm_2Node *node = new vlsra_imm_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsra_imm_3_rule: {
      vlsra_imm_3Node *node = new vlsra_imm_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsra_imm_4_rule: {
      vlsra_imm_4Node *node = new vlsra_imm_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsra_imm_5_rule: {
      vlsra_imm_5Node *node = new vlsra_imm_5Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsra_imm_6_rule: {
      vlsra_imm_6Node *node = new vlsra_imm_6Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_masked_rule: {
      vlsl_maskedNode *node = new vlsl_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_masked_0_rule: {
      vlsl_masked_0Node *node = new vlsl_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_masked_1_rule: {
      vlsl_masked_1Node *node = new vlsl_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_masked_2_rule: {
      vlsl_masked_2Node *node = new vlsl_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_masked_rule: {
      vasr_maskedNode *node = new vasr_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_masked_0_rule: {
      vasr_masked_0Node *node = new vasr_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_masked_1_rule: {
      vasr_masked_1Node *node = new vasr_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_masked_2_rule: {
      vasr_masked_2Node *node = new vasr_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_masked_rule: {
      vlsr_maskedNode *node = new vlsr_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_masked_0_rule: {
      vlsr_masked_0Node *node = new vlsr_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_masked_1_rule: {
      vlsr_masked_1Node *node = new vlsr_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_masked_2_rule: {
      vlsr_masked_2Node *node = new vlsr_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_imm_masked_rule: {
      vlsl_imm_maskedNode *node = new vlsl_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_imm_masked_0_rule: {
      vlsl_imm_masked_0Node *node = new vlsl_imm_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_imm_masked_1_rule: {
      vlsl_imm_masked_1Node *node = new vlsl_imm_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsl_imm_masked_2_rule: {
      vlsl_imm_masked_2Node *node = new vlsl_imm_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_imm_masked_rule: {
      vasr_imm_maskedNode *node = new vasr_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_imm_masked_0_rule: {
      vasr_imm_masked_0Node *node = new vasr_imm_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_imm_masked_1_rule: {
      vasr_imm_masked_1Node *node = new vasr_imm_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasr_imm_masked_2_rule: {
      vasr_imm_masked_2Node *node = new vasr_imm_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_imm_masked_rule: {
      vlsr_imm_maskedNode *node = new vlsr_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_imm_masked_0_rule: {
      vlsr_imm_masked_0Node *node = new vlsr_imm_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_imm_masked_1_rule: {
      vlsr_imm_masked_1Node *node = new vlsr_imm_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsr_imm_masked_2_rule: {
      vlsr_imm_masked_2Node *node = new vlsr_imm_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addI_neon_rule: {
      reduce_addI_neonNode *node = new reduce_addI_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addI_sve_rule: {
      reduce_addI_sveNode *node = new reduce_addI_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addL_neon_rule: {
      reduce_addL_neonNode *node = new reduce_addL_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addL_sve_rule: {
      reduce_addL_sveNode *node = new reduce_addL_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add2F_neon_rule: {
      reduce_add2F_neonNode *node = new reduce_add2F_neonNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add4F_neon_rule: {
      reduce_add4F_neonNode *node = new reduce_add4F_neonNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addF_sve_rule: {
      reduce_addF_sveNode *node = new reduce_addF_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addD_neon_rule: {
      reduce_addD_neonNode *node = new reduce_addD_neonNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addD_sve_rule: {
      reduce_addD_sveNode *node = new reduce_addD_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addI_masked_rule: {
      reduce_addI_maskedNode *node = new reduce_addI_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addL_masked_rule: {
      reduce_addL_maskedNode *node = new reduce_addL_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addF_masked_rule: {
      reduce_addF_maskedNode *node = new reduce_addF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addD_masked_rule: {
      reduce_addD_maskedNode *node = new reduce_addD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mulI_rule: {
      reduce_mulINode *node = new reduce_mulINode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mulL_rule: {
      reduce_mulLNode *node = new reduce_mulLNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mulF_rule: {
      reduce_mulFNode *node = new reduce_mulFNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mulD_rule: {
      reduce_mulDNode *node = new reduce_mulDNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andI_neon_rule: {
      reduce_andI_neonNode *node = new reduce_andI_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andI_sve_rule: {
      reduce_andI_sveNode *node = new reduce_andI_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andL_neon_rule: {
      reduce_andL_neonNode *node = new reduce_andL_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andL_sve_rule: {
      reduce_andL_sveNode *node = new reduce_andL_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andI_masked_rule: {
      reduce_andI_maskedNode *node = new reduce_andI_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andL_masked_rule: {
      reduce_andL_maskedNode *node = new reduce_andL_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orI_neon_rule: {
      reduce_orI_neonNode *node = new reduce_orI_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orI_sve_rule: {
      reduce_orI_sveNode *node = new reduce_orI_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orL_neon_rule: {
      reduce_orL_neonNode *node = new reduce_orL_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orL_sve_rule: {
      reduce_orL_sveNode *node = new reduce_orL_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orI_masked_rule: {
      reduce_orI_maskedNode *node = new reduce_orI_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orL_masked_rule: {
      reduce_orL_maskedNode *node = new reduce_orL_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_xorI_neon_rule: {
      reduce_xorI_neonNode *node = new reduce_xorI_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_xorI_sve_rule: {
      reduce_xorI_sveNode *node = new reduce_xorI_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_xorL_neon_rule: {
      reduce_xorL_neonNode *node = new reduce_xorL_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_xorL_sve_rule: {
      reduce_xorL_sveNode *node = new reduce_xorL_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_xorI_masked_rule: {
      reduce_xorI_maskedNode *node = new reduce_xorI_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_xorL_masked_rule: {
      reduce_xorL_maskedNode *node = new reduce_xorL_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxI_neon_rule: {
      reduce_maxI_neonNode *node = new reduce_maxI_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxI_sve_rule: {
      reduce_maxI_sveNode *node = new reduce_maxI_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxL_neon_rule: {
      reduce_maxL_neonNode *node = new reduce_maxL_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxL_sve_rule: {
      reduce_maxL_sveNode *node = new reduce_maxL_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxF_rule: {
      reduce_maxFNode *node = new reduce_maxFNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxD_rule: {
      reduce_maxDNode *node = new reduce_maxDNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxI_masked_rule: {
      reduce_maxI_maskedNode *node = new reduce_maxI_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxL_masked_rule: {
      reduce_maxL_maskedNode *node = new reduce_maxL_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxF_masked_rule: {
      reduce_maxF_maskedNode *node = new reduce_maxF_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxD_masked_rule: {
      reduce_maxD_maskedNode *node = new reduce_maxD_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minI_neon_rule: {
      reduce_minI_neonNode *node = new reduce_minI_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minI_sve_rule: {
      reduce_minI_sveNode *node = new reduce_minI_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minL_neon_rule: {
      reduce_minL_neonNode *node = new reduce_minL_neonNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minL_sve_rule: {
      reduce_minL_sveNode *node = new reduce_minL_sveNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minF_rule: {
      reduce_minFNode *node = new reduce_minFNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minD_rule: {
      reduce_minDNode *node = new reduce_minDNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minI_masked_rule: {
      reduce_minI_maskedNode *node = new reduce_minI_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minL_masked_rule: {
      reduce_minL_maskedNode *node = new reduce_minL_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minF_masked_rule: {
      reduce_minF_maskedNode *node = new reduce_minF_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minD_masked_rule: {
      reduce_minD_maskedNode *node = new reduce_minD_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpret_same_size_rule: {
      reinterpret_same_sizeNode *node = new reinterpret_same_sizeNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpret_resize_le128b_rule: {
      reinterpret_resize_le128bNode *node = new reinterpret_resize_le128bNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpret_resize_gt128b_rule: {
      reinterpret_resize_gt128bNode *node = new reinterpret_resize_gt128bNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(PREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vzeroExtBtoX_rule: {
      vzeroExtBtoXNode *node = new vzeroExtBtoXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vzeroExtStoX_rule: {
      vzeroExtStoXNode *node = new vzeroExtStoXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vzeroExtItoX_rule: {
      vzeroExtItoXNode *node = new vzeroExtItoXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtBtoX_rule: {
      vcvtBtoXNode *node = new vcvtBtoXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtStoB_neon_rule: {
      vcvtStoB_neonNode *node = new vcvtStoB_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtStoB_sve_rule: {
      vcvtStoB_sveNode *node = new vcvtStoB_sveNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtStoX_extend_rule: {
      vcvtStoX_extendNode *node = new vcvtStoX_extendNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtItoX_narrow_neon_rule: {
      vcvtItoX_narrow_neonNode *node = new vcvtItoX_narrow_neonNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtItoX_narrow_sve_rule: {
      vcvtItoX_narrow_sveNode *node = new vcvtItoX_narrow_sveNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtItoX_rule: {
      vcvtItoXNode *node = new vcvtItoXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtLtoI_neon_rule: {
      vcvtLtoI_neonNode *node = new vcvtLtoI_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtLtoI_sve_rule: {
      vcvtLtoI_sveNode *node = new vcvtLtoI_sveNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtLtoF_neon_rule: {
      vcvtLtoF_neonNode *node = new vcvtLtoF_neonNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtLtoF_sve_rule: {
      vcvtLtoF_sveNode *node = new vcvtLtoF_sveNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtLtoD_rule: {
      vcvtLtoDNode *node = new vcvtLtoDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtFtoX_narrow_neon_rule: {
      vcvtFtoX_narrow_neonNode *node = new vcvtFtoX_narrow_neonNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtFtoX_narrow_sve_rule: {
      vcvtFtoX_narrow_sveNode *node = new vcvtFtoX_narrow_sveNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtFtoX_rule: {
      vcvtFtoXNode *node = new vcvtFtoXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtDtoI_neon_rule: {
      vcvtDtoI_neonNode *node = new vcvtDtoI_neonNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtDtoI_sve_rule: {
      vcvtDtoI_sveNode *node = new vcvtDtoI_sveNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtDtoL_rule: {
      vcvtDtoLNode *node = new vcvtDtoLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtDtoF_64b_rule: {
      vcvtDtoF_64bNode *node = new vcvtDtoF_64bNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtDtoF_gt64b_rule: {
      vcvtDtoF_gt64bNode *node = new vcvtDtoF_gt64bNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtHFtoF_rule: {
      vcvtHFtoFNode *node = new vcvtHFtoFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtFtoHF_neon_rule: {
      vcvtFtoHF_neonNode *node = new vcvtFtoHF_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtFtoHF_sve_rule: {
      vcvtFtoHF_sveNode *node = new vcvtFtoHF_sveNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateI_rule: {
      replicateINode *node = new replicateINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateL_rule: {
      replicateLNode *node = new replicateLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateF_rule: {
      replicateFNode *node = new replicateFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateD_rule: {
      replicateDNode *node = new replicateDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateI_imm_le128b_rule: {
      replicateI_imm_le128bNode *node = new replicateI_imm_le128bNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateB_imm8_gt128b_rule: {
      replicateB_imm8_gt128bNode *node = new replicateB_imm8_gt128bNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateI_imm8_gt128b_rule: {
      replicateI_imm8_gt128bNode *node = new replicateI_imm8_gt128bNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateL_imm_128b_rule: {
      replicateL_imm_128bNode *node = new replicateL_imm_128bNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateL_imm8_gt128b_rule: {
      replicateL_imm8_gt128bNode *node = new replicateL_imm8_gt128bNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertI_le128b_rule: {
      insertI_le128bNode *node = new insertI_le128bNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertI_index_lt32_rule: {
      insertI_index_lt32Node *node = new insertI_index_lt32Node();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertI_index_ge32_rule: {
      insertI_index_ge32Node *node = new insertI_index_ge32Node();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertL_128b_rule: {
      insertL_128bNode *node = new insertL_128bNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertL_gt128b_rule: {
      insertL_gt128bNode *node = new insertL_gt128bNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertF_le128b_rule: {
      insertF_le128bNode *node = new insertF_le128bNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertF_index_lt32_rule: {
      insertF_index_lt32Node *node = new insertF_index_lt32Node();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertF_index_ge32_rule: {
      insertF_index_ge32Node *node = new insertF_index_ge32Node();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertD_128b_rule: {
      insertD_128bNode *node = new insertD_128bNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertD_gt128b_rule: {
      insertD_gt128bNode *node = new insertD_gt128bNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractUB_ireg_rule: {
      extractUB_iregNode *node = new extractUB_iregNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractUB_index_lt16_rule: {
      extractUB_index_lt16Node *node = new extractUB_index_lt16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractUB_index_ge16_rule: {
      extractUB_index_ge16Node *node = new extractUB_index_ge16Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractB_index_lt16_rule: {
      extractB_index_lt16Node *node = new extractB_index_lt16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractB_index_ge16_rule: {
      extractB_index_ge16Node *node = new extractB_index_ge16Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractS_index_lt8_rule: {
      extractS_index_lt8Node *node = new extractS_index_lt8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractS_index_ge8_rule: {
      extractS_index_ge8Node *node = new extractS_index_ge8Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractI_index_lt4_rule: {
      extractI_index_lt4Node *node = new extractI_index_lt4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractI_index_ge4_rule: {
      extractI_index_ge4Node *node = new extractI_index_ge4Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractL_index_lt2_rule: {
      extractL_index_lt2Node *node = new extractL_index_lt2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractL_index_ge2_rule: {
      extractL_index_ge2Node *node = new extractL_index_ge2Node();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractF_rule: {
      extractFNode *node = new extractFNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractD_rule: {
      extractDNode *node = new extractDNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmask_neon_rule: {
      vloadmask_neonNode *node = new vloadmask_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmaskB_sve_rule: {
      vloadmaskB_sveNode *node = new vloadmaskB_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmask_extend_sve_rule: {
      vloadmask_extend_sveNode *node = new vloadmask_extend_sveNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmaskB_masked_rule: {
      vloadmaskB_maskedNode *node = new vloadmaskB_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmask_extend_masked_rule: {
      vloadmask_extend_maskedNode *node = new vloadmask_extend_maskedNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoremaskB_neon_rule: {
      vstoremaskB_neonNode *node = new vstoremaskB_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoremask_narrow_neon_rule: {
      vstoremask_narrow_neonNode *node = new vstoremask_narrow_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoremaskB_sve_rule: {
      vstoremaskB_sveNode *node = new vstoremaskB_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoremask_narrow_sve_rule: {
      vstoremask_narrow_sveNode *node = new vstoremask_narrow_sveNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmask_loadV_rule: {
      vloadmask_loadVNode *node = new vloadmask_loadVNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmask_loadV_masked_rule: {
      vloadmask_loadV_maskedNode *node = new vloadmask_loadV_maskedNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmask_loadVMasked_rule: {
      vloadmask_loadVMaskedNode *node = new vloadmask_loadVMaskedNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmask_loadVMasked_masked_rule: {
      vloadmask_loadVMasked_maskedNode *node = new vloadmask_loadVMasked_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV_vstoremask_rule: {
      storeV_vstoremaskNode *node = new storeV_vstoremaskNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV_vstoremask_masked_rule: {
      storeV_vstoremask_maskedNode *node = new storeV_vstoremask_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeVMasked_vstoremask_rule: {
      storeVMasked_vstoremaskNode *node = new storeVMasked_vstoremaskNode();
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeVMasked_vstoremask_masked_rule: {
      storeVMasked_vstoremask_maskedNode *node = new storeVMasked_vstoremask_maskedNode();
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_and_rule: {
      vmask_andNode *node = new vmask_andNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_or_rule: {
      vmask_orNode *node = new vmask_orNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_xor_rule: {
      vmask_xorNode *node = new vmask_xorNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_and_notI_rule: {
      vmask_and_notINode *node = new vmask_and_notINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_and_notL_rule: {
      vmask_and_notLNode *node = new vmask_and_notLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_neon_rule: {
      vmaskcmp_neonNode *node = new vmaskcmp_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_zeroI_neon_rule: {
      vmaskcmp_zeroI_neonNode *node = new vmaskcmp_zeroI_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_zeroL_neon_rule: {
      vmaskcmp_zeroL_neonNode *node = new vmaskcmp_zeroL_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_zeroF_neon_rule: {
      vmaskcmp_zeroF_neonNode *node = new vmaskcmp_zeroF_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_zeroD_neon_rule: {
      vmaskcmp_zeroD_neonNode *node = new vmaskcmp_zeroD_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_sve_rule: {
      vmaskcmp_sveNode *node = new vmaskcmp_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_immI_sve_rule: {
      vmaskcmp_immI_sveNode *node = new vmaskcmp_immI_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmpU_immI_sve_rule: {
      vmaskcmpU_immI_sveNode *node = new vmaskcmpU_immI_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_immL_sve_rule: {
      vmaskcmp_immL_sveNode *node = new vmaskcmp_immL_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmpU_immL_sve_rule: {
      vmaskcmpU_immL_sveNode *node = new vmaskcmpU_immL_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_masked_rule: {
      vmaskcmp_maskedNode *node = new vmaskcmp_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_same_esize_neon_rule: {
      vmaskcast_same_esize_neonNode *node = new vmaskcast_same_esize_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_extend_neon_rule: {
      vmaskcast_extend_neonNode *node = new vmaskcast_extend_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_narrow_neon_rule: {
      vmaskcast_narrow_neonNode *node = new vmaskcast_narrow_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_same_esize_sve_rule: {
      vmaskcast_same_esize_sveNode *node = new vmaskcast_same_esize_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_extend_sve_rule: {
      vmaskcast_extend_sveNode *node = new vmaskcast_extend_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_narrow_sve_rule: {
      vmaskcast_narrow_sveNode *node = new vmaskcast_narrow_sveNode();
      node->set_opnd_array(2, MachOperGenerator(PREG));
      node->set_opnd_array(3, MachOperGenerator(PREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_reinterpret_same_esize_rule: {
      vmask_reinterpret_same_esizeNode *node = new vmask_reinterpret_same_esizeNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_reinterpret_diff_esize_rule: {
      vmask_reinterpret_diff_esizeNode *node = new vmask_reinterpret_diff_esizeNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_truecount_neon_rule: {
      vmask_truecount_neonNode *node = new vmask_truecount_neonNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      return node;
    }
  case vmask_truecount_sve_rule: {
      vmask_truecount_sveNode *node = new vmask_truecount_sveNode();
      return node;
    }
  case vstoremask_truecount_neon_rule: {
      vstoremask_truecount_neonNode *node = new vstoremask_truecount_neonNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      return node;
    }
  case vmask_firsttrue_neon_rule: {
      vmask_firsttrue_neonNode *node = new vmask_firsttrue_neonNode();
      return node;
    }
  case vmask_firsttrue_sve_rule: {
      vmask_firsttrue_sveNode *node = new vmask_firsttrue_sveNode();
      node->set_opnd_array(2, MachOperGenerator(PREG));
      return node;
    }
  case vmask_firsttrue_masked_rule: {
      vmask_firsttrue_maskedNode *node = new vmask_firsttrue_maskedNode();
      node->set_opnd_array(3, MachOperGenerator(PREG));
      return node;
    }
  case vmask_lasttrue_neon_rule: {
      vmask_lasttrue_neonNode *node = new vmask_lasttrue_neonNode();
      return node;
    }
  case vmask_lasttrue_sve_rule: {
      vmask_lasttrue_sveNode *node = new vmask_lasttrue_sveNode();
      node->set_opnd_array(2, MachOperGenerator(PREG));
      return node;
    }
  case vmask_tolong_neon_rule: {
      vmask_tolong_neonNode *node = new vmask_tolong_neonNode();
      return node;
    }
  case vmask_tolong_sve_rule: {
      vmask_tolong_sveNode *node = new vmask_tolong_sveNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      return node;
    }
  case vmask_fromlong_rule: {
      vmask_fromlongNode *node = new vmask_fromlongNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskAll_immI_rule: {
      vmaskAll_immINode *node = new vmaskAll_immINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskAllI_rule: {
      vmaskAllINode *node = new vmaskAllINode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskAllI_masked_rule: {
      vmaskAllI_maskedNode *node = new vmaskAllI_maskedNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskAll_immL_rule: {
      vmaskAll_immLNode *node = new vmaskAll_immLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskAllL_rule: {
      vmaskAllLNode *node = new vmaskAllLNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskAllL_masked_rule: {
      vmaskAllL_maskedNode *node = new vmaskAllL_maskedNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_gen_I_rule: {
      vmask_gen_INode *node = new vmask_gen_INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_gen_L_rule: {
      vmask_gen_LNode *node = new vmask_gen_LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_gen_imm_rule: {
      vmask_gen_immNode *node = new vmask_gen_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_gen_sub_rule: {
      vmask_gen_subNode *node = new vmask_gen_subNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcountI_rule: {
      vpopcountINode *node = new vpopcountINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcountL_rule: {
      vpopcountLNode *node = new vpopcountLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcountI_masked_rule: {
      vpopcountI_maskedNode *node = new vpopcountI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcountL_masked_rule: {
      vpopcountL_maskedNode *node = new vpopcountL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vblend_neon_rule: {
      vblend_neonNode *node = new vblend_neonNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vblend_sve_rule: {
      vblend_sveNode *node = new vblend_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vround_le128b_rule: {
      vround_le128bNode *node = new vround_le128bNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vround_le128b_0_rule: {
      vround_le128b_0Node *node = new vround_le128b_0Node();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vround_gt128b_rule: {
      vround_gt128bNode *node = new vround_gt128bNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vround_gt128b_0_rule: {
      vround_gt128b_0Node *node = new vround_gt128b_0Node();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vroundD_rule: {
      vroundDNode *node = new vroundDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vtest_anytrue_neon_rule: {
      vtest_anytrue_neonNode *node = new vtest_anytrue_neonNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vtest_anytrue_sve_rule: {
      vtest_anytrue_sveNode *node = new vtest_anytrue_sveNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vtest_alltrue_neon_rule: {
      vtest_alltrue_neonNode *node = new vtest_alltrue_neonNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vtest_alltrue_sve_rule: {
      vtest_alltrue_sveNode *node = new vtest_alltrue_sveNode();
      node->set_opnd_array(3, MachOperGenerator(PREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadshuffle_rule: {
      loadshuffleNode *node = new loadshuffleNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrange_HS_neon_rule: {
      rearrange_HS_neonNode *node = new rearrange_HS_neonNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrange_rule: {
      rearrangeNode *node = new rearrangeNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gather_loadS_rule: {
      gather_loadSNode *node = new gather_loadSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gather_loadD_rule: {
      gather_loadDNode *node = new gather_loadDNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gather_loadS_masked_rule: {
      gather_loadS_maskedNode *node = new gather_loadS_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gather_loadD_masked_rule: {
      gather_loadD_maskedNode *node = new gather_loadD_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatter_storeS_rule: {
      scatter_storeSNode *node = new scatter_storeSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatter_storeD_rule: {
      scatter_storeDNode *node = new scatter_storeDNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatter_storeS_masked_rule: {
      scatter_storeS_maskedNode *node = new scatter_storeS_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatter_storeD_masked_rule: {
      scatter_storeD_maskedNode *node = new scatter_storeD_maskedNode();
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcountLeadingZeros_rule: {
      vcountLeadingZerosNode *node = new vcountLeadingZerosNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcountLeadingZeros_masked_rule: {
      vcountLeadingZeros_maskedNode *node = new vcountLeadingZeros_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcountTrailingZeros_rule: {
      vcountTrailingZerosNode *node = new vcountTrailingZerosNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcountTrailingZeros_masked_rule: {
      vcountTrailingZeros_maskedNode *node = new vcountTrailingZeros_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vreverse_rule: {
      vreverseNode *node = new vreverseNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vreverse_masked_rule: {
      vreverse_maskedNode *node = new vreverse_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vreverseBytes_rule: {
      vreverseBytesNode *node = new vreverseBytesNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vreverseBytes_masked_rule: {
      vreverseBytes_maskedNode *node = new vreverseBytes_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case populateindex_rule: {
      populateindexNode *node = new populateindexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mcompress_rule: {
      mcompressNode *node = new mcompressNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcompress_rule: {
      vcompressNode *node = new vcompressNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcompressB_rule: {
      vcompressBNode *node = new vcompressBNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(VREG));
      node->set_opnd_array(7, MachOperGenerator(VREG));
      node->set_opnd_array(8, MachOperGenerator(PREG));
      node->set_opnd_array(9, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcompressS_rule: {
      vcompressSNode *node = new vcompressSNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vexpand_rule: {
      vexpandNode *node = new vexpandNode();
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsignum_le128b_rule: {
      vsignum_le128bNode *node = new vsignum_le128bNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsignum_le128b_0_rule: {
      vsignum_le128b_0Node *node = new vsignum_le128b_0Node();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsignum_gt128b_rule: {
      vsignum_gt128bNode *node = new vsignum_gt128bNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsignum_gt128b_0_rule: {
      vsignum_gt128b_0Node *node = new vsignum_gt128b_0Node();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcompressBits_rule: {
      vcompressBitsNode *node = new vcompressBitsNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vexpandBits_rule: {
      vexpandBitsNode *node = new vexpandBitsNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndSwapP_shenandoah_rule: {
      compareAndSwapP_shenandoahNode *node = new compareAndSwapP_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      return node;
    }
  case compareAndSwapN_shenandoah_rule: {
      compareAndSwapN_shenandoahNode *node = new compareAndSwapN_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNNOSP));
      return node;
    }
  case compareAndSwapPAcq_shenandoah_rule: {
      compareAndSwapPAcq_shenandoahNode *node = new compareAndSwapPAcq_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      return node;
    }
  case compareAndSwapNAcq_shenandoah_rule: {
      compareAndSwapNAcq_shenandoahNode *node = new compareAndSwapNAcq_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNNOSP));
      return node;
    }
  case compareAndExchangeN_shenandoah_rule: {
      compareAndExchangeN_shenandoahNode *node = new compareAndExchangeN_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNNOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGNNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeP_shenandoah_rule: {
      compareAndExchangeP_shenandoahNode *node = new compareAndExchangeP_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeNAcq_shenandoah_rule: {
      compareAndExchangeNAcq_shenandoahNode *node = new compareAndExchangeNAcq_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNNOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGNNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangePAcq_shenandoah_rule: {
      compareAndExchangePAcq_shenandoahNode *node = new compareAndExchangePAcq_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case weakCompareAndSwapN_shenandoah_rule: {
      weakCompareAndSwapN_shenandoahNode *node = new weakCompareAndSwapN_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNNOSP));
      return node;
    }
  case weakCompareAndSwapP_shenandoah_rule: {
      weakCompareAndSwapP_shenandoahNode *node = new weakCompareAndSwapP_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      return node;
    }
  case weakCompareAndSwapNAcq_shenandoah_rule: {
      weakCompareAndSwapNAcq_shenandoahNode *node = new weakCompareAndSwapNAcq_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNNOSP));
      return node;
    }
  case weakCompareAndSwapPAcq_shenandoah_rule: {
      weakCompareAndSwapPAcq_shenandoahNode *node = new weakCompareAndSwapPAcq_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      return node;
    }
  case xLoadP_rule: {
      xLoadPNode *node = new xLoadPNode();
      node->set_opnd_array(2, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xLoadPVolatile_rule: {
      xLoadPVolatileNode *node = new xLoadPVolatileNode();
      node->set_opnd_array(2, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xCompareAndSwapP_rule: {
      xCompareAndSwapPNode *node = new xCompareAndSwapPNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case xCompareAndSwapP_0_rule: {
      xCompareAndSwapP_0Node *node = new xCompareAndSwapP_0Node();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case xCompareAndSwapPAcq_rule: {
      xCompareAndSwapPAcqNode *node = new xCompareAndSwapPAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case xCompareAndSwapPAcq_0_rule: {
      xCompareAndSwapPAcq_0Node *node = new xCompareAndSwapPAcq_0Node();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case xCompareAndExchangeP_rule: {
      xCompareAndExchangePNode *node = new xCompareAndExchangePNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xCompareAndExchangePAcq_rule: {
      xCompareAndExchangePAcqNode *node = new xCompareAndExchangePAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xGetAndSetP_rule: {
      xGetAndSetPNode *node = new xGetAndSetPNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xGetAndSetPAcq_rule: {
      xGetAndSetPAcqNode *node = new xGetAndSetPAcqNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zLoadP_rule: {
      zLoadPNode *node = new zLoadPNode();
      node->set_opnd_array(2, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zLoadPVolatile_rule: {
      zLoadPVolatileNode *node = new zLoadPVolatileNode();
      node->set_opnd_array(2, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zStoreP_rule: {
      zStorePNode *node = new zStorePNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zStorePVolatile_rule: {
      zStorePVolatileNode *node = new zStorePVolatileNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zCompareAndSwapP_rule: {
      zCompareAndSwapPNode *node = new zCompareAndSwapPNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGPNOSP));
      return node;
    }
  case zCompareAndSwapP_0_rule: {
      zCompareAndSwapP_0Node *node = new zCompareAndSwapP_0Node();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGPNOSP));
      return node;
    }
  case zCompareAndSwapPAcq_rule: {
      zCompareAndSwapPAcqNode *node = new zCompareAndSwapPAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGPNOSP));
      return node;
    }
  case zCompareAndSwapPAcq_0_rule: {
      zCompareAndSwapPAcq_0Node *node = new zCompareAndSwapPAcq_0Node();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGPNOSP));
      return node;
    }
  case zCompareAndExchangeP_rule: {
      zCompareAndExchangePNode *node = new zCompareAndExchangePNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zCompareAndExchangePAcq_rule: {
      zCompareAndExchangePAcqNode *node = new zCompareAndExchangePAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(5, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zGetAndSetP_rule: {
      zGetAndSetPNode *node = new zGetAndSetPNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zGetAndSetPAcq_rule: {
      zGetAndSetPAcqNode *node = new zGetAndSetPAcqNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  
  default:
    fprintf(stderr, "Default MachNode Generator invoked for: \n");
    fprintf(stderr, "   opcode = %d\n", opcode);
    break;
  };
  return nullptr;
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
