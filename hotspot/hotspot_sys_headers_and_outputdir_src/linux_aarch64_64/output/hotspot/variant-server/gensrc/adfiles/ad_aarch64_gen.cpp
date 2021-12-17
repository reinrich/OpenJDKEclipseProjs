#line 1 "ad_aarch64_gen.cpp"
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
  case IMMI_31:
    return new immI_31Oper(_leaf->get_int() );
  case IMMI_2:
    return new immI_2Oper(_leaf->get_int() );
  case IMMI_4:
    return new immI_4Oper(_leaf->get_int() );
  case IMMI_8:
    return new immI_8Oper(_leaf->get_int() );
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
  case IMMI_63:
    return new immI_63Oper(_leaf->get_int() );
  case IMMI_64:
    return new immI_64Oper(_leaf->get_int() );
  case IMMI_255:
    return new immI_255Oper(_leaf->get_int() );
  case IMMI_65535:
    return new immI_65535Oper(_leaf->get_int() );
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
  case IMMI26:
    return new immI26Oper(_leaf->get_int() );
  case IMMI19:
    return new immI19Oper(_leaf->get_int() );
  case IMMIU12:
    return new immIU12Oper(_leaf->get_int() );
  case IMMLU12:
    return new immLU12Oper(_leaf->get_long() );
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
  case IMML_1:
    return new immL_1Oper(_leaf->get_long() );
  case IMML_M1:
    return new immL_M1Oper(_leaf->get_long() );
  case IMML_PC_OFF:
    return new immL_pc_offOper(_leaf->get_long() );
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
  case IMMP_M1:
    return new immP_M1Oper(_leaf->bottom_type()->is_ptr() );
  case IMMP_M2:
    return new immP_M2Oper(_leaf->bottom_type()->is_ptr() );
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
  case IREGL_R2:
    return new iRegL_R2Oper( );
  case IREGL_R3:
    return new iRegL_R3Oper( );
  case IREGL_R11:
    return new iRegL_R11Oper( );
  case IREGP_FP:
    return new iRegP_FPOper( );
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
  case IREGN_R0:
    return new iRegN_R0Oper( );
  case IREGN_R2:
    return new iRegN_R2Oper( );
  case IREGN_R3:
    return new iRegN_R3Oper( );
  case IREGNNOSP:
    return new iRegNNoSpOper( );
  case IREGIHEAPBASE:
    return new iRegIHeapbaseOper( );
  case VREGF:
    return new vRegFOper( );
  case VREGD:
    return new vRegDOper( );
  case VREG:
    return new vRegOper( );
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
  case VREGD_V8:
    return new vRegD_V8Oper( );
  case VREGD_V9:
    return new vRegD_V9Oper( );
  case VREGD_V10:
    return new vRegD_V10Oper( );
  case VREGD_V11:
    return new vRegD_V11Oper( );
  case VREGD_V12:
    return new vRegD_V12Oper( );
  case VREGD_V13:
    return new vRegD_V13Oper( );
  case VREGD_V14:
    return new vRegD_V14Oper( );
  case VREGD_V15:
    return new vRegD_V15Oper( );
  case VREGD_V16:
    return new vRegD_V16Oper( );
  case VREGD_V17:
    return new vRegD_V17Oper( );
  case VREGD_V18:
    return new vRegD_V18Oper( );
  case VREGD_V19:
    return new vRegD_V19Oper( );
  case VREGD_V20:
    return new vRegD_V20Oper( );
  case VREGD_V21:
    return new vRegD_V21Oper( );
  case VREGD_V22:
    return new vRegD_V22Oper( );
  case VREGD_V23:
    return new vRegD_V23Oper( );
  case VREGD_V24:
    return new vRegD_V24Oper( );
  case VREGD_V25:
    return new vRegD_V25Oper( );
  case VREGD_V26:
    return new vRegD_V26Oper( );
  case VREGD_V27:
    return new vRegD_V27Oper( );
  case VREGD_V28:
    return new vRegD_V28Oper( );
  case VREGD_V29:
    return new vRegD_V29Oper( );
  case VREGD_V30:
    return new vRegD_V30Oper( );
  case VREGD_V31:
    return new vRegD_V31Oper( );
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
  case LR_REGP:
    return new lr_RegPOper( );
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
  case INDOFFI:
    return new indOffIOper(_kids[1]->_leaf->get_int() );
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
  case INDOFFL:
    return new indOffLOper(_kids[1]->_leaf->get_long() );
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
  case THREAD_ANCHOR_PC:
    return new thread_anchor_pcOper(_kids[1]->_leaf->get_long() );
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
  case _CONVI2L_IREGI_:    return NULL;
  case _LSHIFTL__CONVI2L_IREGI__IMMISCALE:    return NULL;
  case _LSHIFTL_IREGL_IMMISCALE:    return NULL;
  case _DECODEN_IREGN_:    return NULL;
  case _LOADB_MEMORY1_:    return NULL;
  case _LOADUB_MEMORY1_:    return NULL;
  case _LOADS_MEMORY2_:    return NULL;
  case _LOADUS_MEMORY2_:    return NULL;
  case _LOADI_MEMORY4_:    return NULL;
  case _CONVI2L__LOADI_MEMORY4__:    return NULL;
  case _LOADB_INDIRECT_:    return NULL;
  case _LOADUB_INDIRECT_:    return NULL;
  case _LOADUS_INDIRECT_:    return NULL;
  case _LOADS_INDIRECT_:    return NULL;
  case _LOADI_INDIRECT_:    return NULL;
  case _CONVI2L__LOADI_INDIRECT__:    return NULL;
  case _LOADL_MEMORY8_:    return NULL;
  case _CASTP2X_IREGP_:    return NULL;
  case _CASTP2X__DECODEN_IREGN__:    return NULL;
  case _BINARY_IREGP_IREGP:    return NULL;
  case _BINARY_IREGLNOSP_IREGLNOSP:    return NULL;
  case _BINARY_IREGINOSP_IREGINOSP:    return NULL;
  case _BINARY_IREGNNOSP_IREGNNOSP:    return NULL;
  case _BINARY_IREGI_IREGI:    return NULL;
  case _BINARY_IREGL_IREGL:    return NULL;
  case _BINARY_IREGN_IREGN:    return NULL;
  case _BINARY_CMPOP_RFLAGSREG:    return NULL;
  case _BINARY_IREGIORL2I_IREGIORL2I:    return NULL;
  case _BINARY_CMPOPU_RFLAGSREGU:    return NULL;
  case _BINARY_IMMI0_IREGIORL2I:    return NULL;
  case _BINARY_IREGIORL2I_IMMI0:    return NULL;
  case _BINARY_IMMI_1_IMMI0:    return NULL;
  case _BINARY_IREGL_IMML0:    return NULL;
  case _BINARY_IMML0_IREGL:    return NULL;
  case _BINARY_IREGP_IMMP0:    return NULL;
  case _BINARY_IMMP0_IREGP:    return NULL;
  case _BINARY_IREGN_IMMN0:    return NULL;
  case _BINARY_IMMN0_IREGN:    return NULL;
  case _BINARY_VREGF_VREGF:    return NULL;
  case _BINARY_VREGD_VREGD:    return NULL;
  case _CONVL2I_IREGL_:    return NULL;
  case _CONVI2L_IREGIORL2I_:    return NULL;
  case _LSHIFTL__CONVI2L_IREGIORL2I__IMMISCALE:    return NULL;
  case _MULI_IREGIORL2I_IREGIORL2I:    return NULL;
  case _SUBI_IMMI0_IREGIORL2I:    return NULL;
  case _MULL_IREGL_IREGL:    return NULL;
  case _SUBL_IMML0_IREGL:    return NULL;
  case _MULL__CONVI2L_IREGIORL2I___CONVI2L_IREGIORL2I_:    return NULL;
  case _SUBL_IMML0__CONVI2L_IREGIORL2I_:    return NULL;
  case _XORI_IREGIORL2I_IMMI_M1:    return NULL;
  case _XORL_IREGL_IMML_M1:    return NULL;
  case _XORI_IREGIORL2I_IREGIORL2I:    return NULL;
  case _XORL_IREGL_IREGL:    return NULL;
  case _URSHIFTI_IREGIORL2I_IMMI:    return NULL;
  case _XORI__URSHIFTI_IREGIORL2I_IMMI_IMMI_M1:    return NULL;
  case _URSHIFTL_IREGL_IMMI:    return NULL;
  case _XORL__URSHIFTL_IREGL_IMMI_IMML_M1:    return NULL;
  case _RSHIFTI_IREGIORL2I_IMMI:    return NULL;
  case _XORI__RSHIFTI_IREGIORL2I_IMMI_IMMI_M1:    return NULL;
  case _RSHIFTL_IREGL_IMMI:    return NULL;
  case _XORL__RSHIFTL_IREGL_IMMI_IMML_M1:    return NULL;
  case _ROTATERIGHT_IREGIORL2I_IMMI:    return NULL;
  case _XORI__ROTATERIGHT_IREGIORL2I_IMMI_IMMI_M1:    return NULL;
  case _ROTATERIGHT_IREGL_IMMI:    return NULL;
  case _XORL__ROTATERIGHT_IREGL_IMMI_IMML_M1:    return NULL;
  case _LSHIFTI_IREGIORL2I_IMMI:    return NULL;
  case _XORI__LSHIFTI_IREGIORL2I_IMMI_IMMI_M1:    return NULL;
  case _LSHIFTL_IREGL_IMMI:    return NULL;
  case _XORL__LSHIFTL_IREGL_IMMI_IMML_M1:    return NULL;
  case _XORI__URSHIFTI_IREGIORL2I_IMMI_IREGIORL2I:    return NULL;
  case _XORI_IREGIORL2I__URSHIFTI_IREGIORL2I_IMMI:    return NULL;
  case _XORL__URSHIFTL_IREGL_IMMI_IREGL:    return NULL;
  case _XORL_IREGL__URSHIFTL_IREGL_IMMI:    return NULL;
  case _XORI__RSHIFTI_IREGIORL2I_IMMI_IREGIORL2I:    return NULL;
  case _XORI_IREGIORL2I__RSHIFTI_IREGIORL2I_IMMI:    return NULL;
  case _XORL__RSHIFTL_IREGL_IMMI_IREGL:    return NULL;
  case _XORL_IREGL__RSHIFTL_IREGL_IMMI:    return NULL;
  case _XORI__ROTATERIGHT_IREGIORL2I_IMMI_IREGIORL2I:    return NULL;
  case _XORI_IREGIORL2I__ROTATERIGHT_IREGIORL2I_IMMI:    return NULL;
  case _XORL__ROTATERIGHT_IREGL_IMMI_IREGL:    return NULL;
  case _XORL_IREGL__ROTATERIGHT_IREGL_IMMI:    return NULL;
  case _XORI__LSHIFTI_IREGIORL2I_IMMI_IREGIORL2I:    return NULL;
  case _XORI_IREGIORL2I__LSHIFTI_IREGIORL2I_IMMI:    return NULL;
  case _XORL__LSHIFTL_IREGL_IMMI_IREGL:    return NULL;
  case _XORL_IREGL__LSHIFTL_IREGL_IMMI:    return NULL;
  case _ANDI__URSHIFTI_IREGIORL2I_IMMI_IMMI_BITMASK:    return NULL;
  case _ANDI_IREGIORL2I_IMMI_BITMASK:    return NULL;
  case _ANDL_IREGL_IMML_BITMASK:    return NULL;
  case _LSHIFTI__ANDI_IREGIORL2I_IMMI_BITMASK_IMMI:    return NULL;
  case _ANDL_IREGL_IMML_POSITIVE_BITMASKI:    return NULL;
  case _LSHIFTL__ANDL_IREGL_IMML_POSITIVE_BITMASKI_IMMI:    return NULL;
  case _CONVI2L__ANDI_IREGIORL2I_IMMI_BITMASK_:    return NULL;
  case _CONVL2I__ANDL_IREGL_IMML_POSITIVE_BITMASKI_:    return NULL;
  case _ANDI_IREGI_IMMI_BITMASK:    return NULL;
  case _LSHIFTI_IREGIORL2I_IMMI_16:    return NULL;
  case _RSHIFTI__LSHIFTI_IREGIORL2I_IMMI_16_IMMI_16:    return NULL;
  case _LSHIFTI_IREGIORL2I_IMMI_24:    return NULL;
  case _RSHIFTI__LSHIFTI_IREGIORL2I_IMMI_24_IMMI_24:    return NULL;
  case _URSHIFTI__LSHIFTI_IREGIORL2I_IMMI_24_IMMI_24:    return NULL;
  case _LSHIFTL_IREGL_IMMI_48:    return NULL;
  case _RSHIFTL__LSHIFTL_IREGL_IMMI_48_IMMI_48:    return NULL;
  case _LSHIFTL_IREGL_IMMI_32:    return NULL;
  case _RSHIFTL__LSHIFTL_IREGL_IMMI_32_IMMI_32:    return NULL;
  case _LSHIFTL_IREGL_IMMI_56:    return NULL;
  case _RSHIFTL__LSHIFTL_IREGL_IMMI_56_IMMI_56:    return NULL;
  case _URSHIFTL__LSHIFTL_IREGL_IMMI_56_IMMI_56:    return NULL;
  case _ANDI_IREGIORL2I_IMMI_255:    return NULL;
  case _ANDI_IREGIORL2I_IMMI_65535:    return NULL;
  case _ANDL_IREGL_IMML_255:    return NULL;
  case _ANDL_IREGL_IMML_65535:    return NULL;
  case _ANDL_IREGL_IMML_4294967295:    return NULL;
  case _LSHIFTL__RSHIFTL__LSHIFTL_IREGL_IMMI_56_IMMI_56_IMMIEXT:    return NULL;
  case _LSHIFTL__RSHIFTL__LSHIFTL_IREGL_IMMI_48_IMMI_48_IMMIEXT:    return NULL;
  case _LSHIFTL__RSHIFTL__LSHIFTL_IREGL_IMMI_32_IMMI_32_IMMIEXT:    return NULL;
  case _LSHIFTI__RSHIFTI__LSHIFTI_IREGIORL2I_IMMI_24_IMMI_24_IMMIEXT:    return NULL;
  case _LSHIFTI__RSHIFTI__LSHIFTI_IREGIORL2I_IMMI_16_IMMI_16_IMMIEXT:    return NULL;
  case _LSHIFTL__CONVI2L_IREGIORL2I__IMMIEXT:    return NULL;
  case _LSHIFTL__ANDL_IREGL_IMML_255_IMMIEXT:    return NULL;
  case _LSHIFTL__ANDL_IREGL_IMML_65535_IMMIEXT:    return NULL;
  case _LSHIFTL__ANDL_IREGL_IMML_4294967295_IMMIEXT:    return NULL;
  case _LSHIFTI__ANDI_IREGIORL2I_IMMI_255_IMMIEXT:    return NULL;
  case _LSHIFTI__ANDI_IREGIORL2I_IMMI_65535_IMMIEXT:    return NULL;
  case _NEGF_VREGF_:    return NULL;
  case _BINARY__NEGF_VREGF__VREGF:    return NULL;
  case _BINARY_VREGF__NEGF_VREGF_:    return NULL;
  case _NEGD_VREGD_:    return NULL;
  case _BINARY__NEGD_VREGD__VREGD:    return NULL;
  case _BINARY_VREGD__NEGD_VREGD_:    return NULL;
  case _SUBF_VREGF_VREGF:    return NULL;
  case _SUBD_VREGD_VREGD:    return NULL;
  case _OVERFLOWMULI_IREGIORL2I_IREGIORL2I:    return NULL;
  case _OVERFLOWMULL_IREGL_IREGL:    return NULL;
  case _CMPI_IREGIORL2I_IMMI0:    return NULL;
  case _CMPL_IREGL_IMML0:    return NULL;
  case _CMPP_IREGP_IMMP0:    return NULL;
  case _CMPN_IREGN_IMMN0:    return NULL;
  case _CMPP__DECODEN_IREGN__IMMP0:    return NULL;
  case _CMPU_IREGIORL2I_IMMI0:    return NULL;
  case _CMPUL_IREGL_IMML0:    return NULL;
  case _ANDL_IREGL_IMML:    return NULL;
  case _CMPL__ANDL_IREGL_IMML_IMML0:    return NULL;
  case _ANDI_IREGIORL2I_IMMI:    return NULL;
  case _CMPI__ANDI_IREGIORL2I_IMMI_IMMI0:    return NULL;
  case _ANDL_IREGL_IREGL:    return NULL;
  case _ANDI_IREGIORL2I_IREGIORL2I:    return NULL;
  case _PARTIALSUBTYPECHECK_IREGP_R4_IREGP_R0:    return NULL;
  case _BINARY_IREGP_R1_IREGI_R2:    return NULL;
  case _BINARY_IREGP_R3_IREGI_R4:    return NULL;
  case _BINARY_IREGP_R1_IREGI_R4:    return NULL;
  case _BINARY_IREGP_R3_IREGI_R2:    return NULL;
  case _BINARY_IREGP_R3_IMMI_LE_4:    return NULL;
  case _BINARY_IREGP_R3_IMMI_1:    return NULL;
  case _BINARY_IREGP_R1_IREGP_R3:    return NULL;
  case _BINARY_IREGP_R1_IREGI_R3:    return NULL;
  case _BINARY_VECD_IREGIORL2I:    return NULL;
  case _BINARY_VECX_IREGIORL2I:    return NULL;
  case _BINARY_VECX_IREGL:    return NULL;
  case _BINARY_VECD_VREGF:    return NULL;
  case _BINARY_VECX_VREGF:    return NULL;
  case _BINARY_VECX_VREGD:    return NULL;
  case _BINARY_VECD_VECD:    return NULL;
  case _BINARY_VECX_VECX:    return NULL;
  case _REPLICATEB_IMMI_M1_:    return NULL;
  case _REPLICATES_IMMI_M1_:    return NULL;
  case _REPLICATEI_IMMI_M1_:    return NULL;
  case _REPLICATEL_IMML_M1_:    return NULL;
  case _XORV_VECD__REPLICATEB_IMMI_M1_:    return NULL;
  case _XORV__REPLICATEB_IMMI_M1__VECD:    return NULL;
  case _XORV_VECD__REPLICATES_IMMI_M1_:    return NULL;
  case _XORV__REPLICATES_IMMI_M1__VECD:    return NULL;
  case _XORV_VECD__REPLICATEI_IMMI_M1_:    return NULL;
  case _XORV__REPLICATEI_IMMI_M1__VECD:    return NULL;
  case _XORV_VECX__REPLICATEB_IMMI_M1_:    return NULL;
  case _XORV__REPLICATEB_IMMI_M1__VECX:    return NULL;
  case _XORV_VECX__REPLICATES_IMMI_M1_:    return NULL;
  case _XORV__REPLICATES_IMMI_M1__VECX:    return NULL;
  case _XORV_VECX__REPLICATEI_IMMI_M1_:    return NULL;
  case _XORV__REPLICATEI_IMMI_M1__VECX:    return NULL;
  case _XORV_VECX__REPLICATEL_IMML_M1_:    return NULL;
  case _XORV__REPLICATEL_IMML_M1__VECX:    return NULL;
  case _SUBVF_VECD_VECD:    return NULL;
  case _SUBVF_VECX_VECX:    return NULL;
  case _SUBVD_VECX_VECX:    return NULL;
  case _MULVS_VECD_VECD:    return NULL;
  case _MULVS_VECX_VECX:    return NULL;
  case _MULVI_VECD_VECD:    return NULL;
  case _MULVI_VECX_VECX:    return NULL;
  case _NEGVF_VECD_:    return NULL;
  case _BINARY__NEGVF_VECD__VECD:    return NULL;
  case _BINARY_VECD__NEGVF_VECD_:    return NULL;
  case _NEGVF_VECX_:    return NULL;
  case _BINARY__NEGVF_VECX__VECX:    return NULL;
  case _BINARY_VECX__NEGVF_VECX_:    return NULL;
  case _NEGVD_VECX_:    return NULL;
  case _BINARY__NEGVD_VECX__VECX:    return NULL;
  case _BINARY_VECX__NEGVD_VECX_:    return NULL;
  case _LSHIFTCNTV_IMMI_:    return NULL;
  case _RSHIFTCNTV_IMMI_:    return NULL;
  case _RSHIFTVB_VECD__RSHIFTCNTV_IMMI_:    return NULL;
  case _RSHIFTVB_VECX__RSHIFTCNTV_IMMI_:    return NULL;
  case _RSHIFTVS_VECD__RSHIFTCNTV_IMMI_:    return NULL;
  case _RSHIFTVS_VECX__RSHIFTCNTV_IMMI_:    return NULL;
  case _RSHIFTVI_VECD__RSHIFTCNTV_IMMI_:    return NULL;
  case _RSHIFTVI_VECX__RSHIFTCNTV_IMMI_:    return NULL;
  case _RSHIFTVL_VECX__RSHIFTCNTV_IMMI_:    return NULL;
  case _URSHIFTVB_VECD__RSHIFTCNTV_IMMI_:    return NULL;
  case _URSHIFTVB_VECX__RSHIFTCNTV_IMMI_:    return NULL;
  case _URSHIFTVS_VECD__RSHIFTCNTV_IMMI_:    return NULL;
  case _URSHIFTVS_VECX__RSHIFTCNTV_IMMI_:    return NULL;
  case _URSHIFTVI_VECD__RSHIFTCNTV_IMMI_:    return NULL;
  case _URSHIFTVI_VECX__RSHIFTCNTV_IMMI_:    return NULL;
  case _URSHIFTVL_VECX__RSHIFTCNTV_IMMI_:    return NULL;
  case _BINARY_VREG_PREGGOV:    return NULL;
  case _MASKALL_IMMI_M1_:    return NULL;
  case _XORVMASK_PREGGOV__MASKALL_IMMI_M1_:    return NULL;
  case _MASKALL_IMML_M1_:    return NULL;
  case _XORVMASK_PREGGOV__MASKALL_IMML_M1_:    return NULL;
  case _BINARY_VREG_VREG:    return NULL;
  case _REPLICATEB_IMMBADDSUBV_:    return NULL;
  case _REPLICATES_IMMIADDSUBV_:    return NULL;
  case _REPLICATEI_IMMIADDSUBV_:    return NULL;
  case _REPLICATEL_IMMLADDSUBV_:    return NULL;
  case _REPLICATEB_IMMBLOG_:    return NULL;
  case _REPLICATES_IMMSLOG_:    return NULL;
  case _REPLICATEI_IMMILOG_:    return NULL;
  case _REPLICATEL_IMMLLOG_:    return NULL;
  case _XORV_VREG__REPLICATEB_IMMI_M1_:    return NULL;
  case _XORV__REPLICATEB_IMMI_M1__VREG:    return NULL;
  case _XORV_VREG__REPLICATES_IMMI_M1_:    return NULL;
  case _XORV__REPLICATES_IMMI_M1__VREG:    return NULL;
  case _XORV_VREG__REPLICATEI_IMMI_M1_:    return NULL;
  case _XORV__REPLICATEI_IMMI_M1__VREG:    return NULL;
  case _XORV_VREG__REPLICATEL_IMML_M1_:    return NULL;
  case _XORV__REPLICATEL_IMML_M1__VREG:    return NULL;
  case _NEGVF_VREG_:    return NULL;
  case _BINARY__NEGVF_VREG__VREG:    return NULL;
  case _BINARY_VREG__NEGVF_VREG_:    return NULL;
  case _NEGVD_VREG_:    return NULL;
  case _BINARY__NEGVD_VREG__VREG:    return NULL;
  case _BINARY_VREG__NEGVD_VREG_:    return NULL;
  case _MULVB_VREG_VREG:    return NULL;
  case _MULVS_VREG_VREG:    return NULL;
  case _MULVI_VREG_VREG:    return NULL;
  case _MULVL_VREG_VREG:    return NULL;
  case _BINARY_IMMI_PREGGOV:    return NULL;
  case _LOADVECTOR_INDIRECT_:    return NULL;
  case _VECTORSTOREMASK_PREGGOV_IMMI_GT_1:    return NULL;
  case _BINARY_IREGIORL2I_VREG:    return NULL;
  case _BINARY_IREGL_VREG:    return NULL;
  case _BINARY_VREGF_VREG:    return NULL;
  case _BINARY_VREGD_VREG:    return NULL;
  case _BINARY_VREG__RSHIFTCNTV_IMMI_:    return NULL;
  case _BINARY_VREG__LSHIFTCNTV_IMMI_:    return NULL;
  case _BINARY_VREG_IREGIORL2I:    return NULL;
  case _BINARY_VREG_VREGF:    return NULL;
  case _BINARY_VREG_IREGL:    return NULL;
  case _BINARY_VREG_VREGD:    return NULL;
  case _BINARY_VREG__BINARY_VREG_PREGGOV:    return NULL;
  
  default:
    fprintf(stderr, "Default MachOper Generator invoked for: \n");
    fprintf(stderr, "   opcode = %d\n", opcode);
    break;
  }
  return NULL;
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
  case storeC_volatile_rule: {
      storeC_volatileNode *node = new storeC_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeI_volatile_rule: {
      storeI_volatileNode *node = new storeI_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeL_volatile_rule: {
      storeL_volatileNode *node = new storeL_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeP_volatile_rule: {
      storeP_volatileNode *node = new storeP_volatileNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeN_volatile_rule: {
      storeN_volatileNode *node = new storeN_volatileNode();
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
  case castVVD_rule: {
      castVVDNode *node = new castVVDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castVVX_rule: {
      castVVXNode *node = new castVVXNode();
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
  case loadPLocked_rule: {
      loadPLockedNode *node = new loadPLockedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storePConditional_rule: {
      storePConditionalNode *node = new storePConditionalNode();
      return node;
    }
  case storeLConditional_rule: {
      storeLConditionalNode *node = new storeLConditionalNode();
      return node;
    }
  case storeIConditional_rule: {
      storeIConditionalNode *node = new storeIConditionalNode();
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
  case msubF_reg_reg_0_rule: {
      msubF_reg_reg_0Node *node = new msubF_reg_reg_0Node();
      return node;
    }
  case msubD_reg_reg_rule: {
      msubD_reg_regNode *node = new msubD_reg_regNode();
      return node;
    }
  case msubD_reg_reg_0_rule: {
      msubD_reg_reg_0Node *node = new msubD_reg_reg_0Node();
      return node;
    }
  case mnaddF_reg_reg_rule: {
      mnaddF_reg_regNode *node = new mnaddF_reg_regNode();
      return node;
    }
  case mnaddF_reg_reg_0_rule: {
      mnaddF_reg_reg_0Node *node = new mnaddF_reg_reg_0Node();
      return node;
    }
  case mnaddD_reg_reg_rule: {
      mnaddD_reg_regNode *node = new mnaddD_reg_regNode();
      return node;
    }
  case mnaddD_reg_reg_0_rule: {
      mnaddD_reg_reg_0Node *node = new mnaddD_reg_reg_0Node();
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
  case convI2B_rule: {
      convI2BNode *node = new convI2BNode();
      return node;
    }
  case convP2B_rule: {
      convP2BNode *node = new convP2BNode();
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
  case minI_rReg_rule: {
      minI_rRegNode *node = new minI_rRegNode();
      return node;
    }
  case maxI_rReg_rule: {
      maxI_rRegNode *node = new maxI_rRegNode();
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
  case branchLoopEndU_rule: {
      branchLoopEndUNode *node = new branchLoopEndUNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpFastLock_rule: {
      cmpFastLockNode *node = new cmpFastLockNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
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
  case CallNativeDirect_rule: {
      CallNativeDirectNode *node = new CallNativeDirectNode();
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
  case string_indexofUU_rule: {
      string_indexofUUNode *node = new string_indexofUUNode();
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(7, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(8, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(9, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(10, MachOperGenerator(IREGINOSP));
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
  case string_equalsL_rule: {
      string_equalsLNode *node = new string_equalsLNode();
      return node;
    }
  case string_equalsU_rule: {
      string_equalsUNode *node = new string_equalsUNode();
      return node;
    }
  case array_equalsB_rule: {
      array_equalsBNode *node = new array_equalsBNode();
      node->set_opnd_array(3, MachOperGenerator(IREGP_R3));
      node->set_opnd_array(4, MachOperGenerator(IREGP_R4));
      node->set_opnd_array(5, MachOperGenerator(IREGP_R5));
      return node;
    }
  case array_equalsC_rule: {
      array_equalsCNode *node = new array_equalsCNode();
      node->set_opnd_array(3, MachOperGenerator(IREGP_R3));
      node->set_opnd_array(4, MachOperGenerator(IREGP_R4));
      node->set_opnd_array(5, MachOperGenerator(IREGP_R5));
      return node;
    }
  case has_negatives_rule: {
      has_negativesNode *node = new has_negativesNode();
      return node;
    }
  case string_compress_rule: {
      string_compressNode *node = new string_compressNode();
      node->set_opnd_array(4, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(5, MachOperGenerator(VREGD_V1));
      node->set_opnd_array(6, MachOperGenerator(VREGD_V2));
      node->set_opnd_array(7, MachOperGenerator(VREGD_V3));
      return node;
    }
  case string_inflate_rule: {
      string_inflateNode *node = new string_inflateNode();
      node->set_opnd_array(4, MachOperGenerator(VREGD_V0));
      node->set_opnd_array(5, MachOperGenerator(VREGD_V1));
      node->set_opnd_array(6, MachOperGenerator(VREGD_V2));
      node->set_opnd_array(7, MachOperGenerator(IREGP_R3));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encode_iso_array_rule: {
      encode_iso_arrayNode *node = new encode_iso_arrayNode();
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
  case loadV4_rule: {
      loadV4Node *node = new loadV4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV8_rule: {
      loadV8Node *node = new loadV8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV16_rule: {
      loadV16Node *node = new loadV16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV2_rule: {
      storeV2Node *node = new storeV2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV4_rule: {
      storeV4Node *node = new storeV4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV8_rule: {
      storeV8Node *node = new storeV8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV16_rule: {
      storeV16Node *node = new storeV16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretD_rule: {
      reinterpretDNode *node = new reinterpretDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretX_rule: {
      reinterpretXNode *node = new reinterpretXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretD2X_rule: {
      reinterpretD2XNode *node = new reinterpretD2XNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretX2D_rule: {
      reinterpretX2DNode *node = new reinterpretX2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretS2X_rule: {
      reinterpretS2XNode *node = new reinterpretS2XNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretX2S_rule: {
      reinterpretX2SNode *node = new reinterpretX2SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretS2D_rule: {
      reinterpretS2DNode *node = new reinterpretS2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretD2S_rule: {
      reinterpretD2SNode *node = new reinterpretD2SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt8Bto8S_rule: {
      vcvt8Bto8SNode *node = new vcvt8Bto8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Bto4S_rule: {
      vcvt4Bto4SNode *node = new vcvt4Bto4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt8Sto8B_rule: {
      vcvt8Sto8BNode *node = new vcvt8Sto8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Sto4B_rule: {
      vcvt4Sto4BNode *node = new vcvt4Sto4BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Sto4I_rule: {
      vcvt4Sto4INode *node = new vcvt4Sto4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Ito4S_rule: {
      vcvt4Ito4SNode *node = new vcvt4Ito4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Ito2L_rule: {
      vcvt2Ito2LNode *node = new vcvt2Ito2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Lto2I_rule: {
      vcvt2Lto2INode *node = new vcvt2Lto2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Ito4B_rule: {
      vcvt4Ito4BNode *node = new vcvt4Ito4BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Bto4I_rule: {
      vcvt4Bto4INode *node = new vcvt4Bto4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Lto2F_rule: {
      vcvt2Lto2FNode *node = new vcvt2Lto2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Ito2F_rule: {
      vcvt2Ito2FNode *node = new vcvt2Ito2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Ito4F_rule: {
      vcvt4Ito4FNode *node = new vcvt4Ito4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Lto2D_rule: {
      vcvt2Lto2DNode *node = new vcvt2Lto2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Sto4F_rule: {
      vcvt4Sto4FNode *node = new vcvt4Sto4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Ito2D_rule: {
      vcvt2Ito2DNode *node = new vcvt2Ito2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Bto4F_rule: {
      vcvt4Bto4FNode *node = new vcvt4Bto4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Fto2L_rule: {
      vcvt2Fto2LNode *node = new vcvt2Fto2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Fto2I_rule: {
      vcvt2Fto2INode *node = new vcvt2Fto2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Fto4I_rule: {
      vcvt4Fto4INode *node = new vcvt4Fto4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Dto2L_rule: {
      vcvt2Dto2LNode *node = new vcvt2Dto2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Fto4S_rule: {
      vcvt4Fto4SNode *node = new vcvt4Fto4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Dto2I_rule: {
      vcvt2Dto2INode *node = new vcvt2Dto2INode();
      node->set_opnd_array(2, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt4Fto4B_rule: {
      vcvt4Fto4BNode *node = new vcvt4Fto4BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Fto2D_rule: {
      vcvt2Fto2DNode *node = new vcvt2Fto2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvt2Dto2F_rule: {
      vcvt2Dto2FNode *node = new vcvt2Dto2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add8B_rule: {
      reduce_add8BNode *node = new reduce_add8BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add16B_rule: {
      reduce_add16BNode *node = new reduce_add16BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add4S_rule: {
      reduce_add4SNode *node = new reduce_add4SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add8S_rule: {
      reduce_add8SNode *node = new reduce_add8SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add2L_rule: {
      reduce_add2LNode *node = new reduce_add2LNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mul8B_rule: {
      reduce_mul8BNode *node = new reduce_mul8BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->set_opnd_array(5, MachOperGenerator(VECD));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mul16B_rule: {
      reduce_mul16BNode *node = new reduce_mul16BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->set_opnd_array(5, MachOperGenerator(VECX));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mul4S_rule: {
      reduce_mul4SNode *node = new reduce_mul4SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mul8S_rule: {
      reduce_mul8SNode *node = new reduce_mul8SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->set_opnd_array(5, MachOperGenerator(VECX));
      node->set_opnd_array(6, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mul2L_rule: {
      reduce_mul2LNode *node = new reduce_mul2LNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_max8B_rule: {
      reduce_max8BNode *node = new reduce_max8BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_max16B_rule: {
      reduce_max16BNode *node = new reduce_max16BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_max4S_rule: {
      reduce_max4SNode *node = new reduce_max4SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_max8S_rule: {
      reduce_max8SNode *node = new reduce_max8SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_max4I_rule: {
      reduce_max4INode *node = new reduce_max4INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_min8B_rule: {
      reduce_min8BNode *node = new reduce_min8BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_min16B_rule: {
      reduce_min16BNode *node = new reduce_min16BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_min4S_rule: {
      reduce_min4SNode *node = new reduce_min4SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_min8S_rule: {
      reduce_min8SNode *node = new reduce_min8SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_min4I_rule: {
      reduce_min4INode *node = new reduce_min4INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_max2I_rule: {
      reduce_max2INode *node = new reduce_max2INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_min2I_rule: {
      reduce_min2INode *node = new reduce_min2INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_max2L_rule: {
      reduce_max2LNode *node = new reduce_max2LNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_min2L_rule: {
      reduce_min2LNode *node = new reduce_min2LNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_max2F_rule: {
      reduce_max2FNode *node = new reduce_max2FNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_max4F_rule: {
      reduce_max4FNode *node = new reduce_max4FNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_max2D_rule: {
      reduce_max2DNode *node = new reduce_max2DNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_min2F_rule: {
      reduce_min2FNode *node = new reduce_min2FNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_min4F_rule: {
      reduce_min4FNode *node = new reduce_min4FNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_min2D_rule: {
      reduce_min2DNode *node = new reduce_min2DNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_and8B_rule: {
      reduce_and8BNode *node = new reduce_and8BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orr8B_rule: {
      reduce_orr8BNode *node = new reduce_orr8BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eor8B_rule: {
      reduce_eor8BNode *node = new reduce_eor8BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_and16B_rule: {
      reduce_and16BNode *node = new reduce_and16BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orr16B_rule: {
      reduce_orr16BNode *node = new reduce_orr16BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eor16B_rule: {
      reduce_eor16BNode *node = new reduce_eor16BNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_and4S_rule: {
      reduce_and4SNode *node = new reduce_and4SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orr4S_rule: {
      reduce_orr4SNode *node = new reduce_orr4SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eor4S_rule: {
      reduce_eor4SNode *node = new reduce_eor4SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_and8S_rule: {
      reduce_and8SNode *node = new reduce_and8SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orr8S_rule: {
      reduce_orr8SNode *node = new reduce_orr8SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eor8S_rule: {
      reduce_eor8SNode *node = new reduce_eor8SNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_and2I_rule: {
      reduce_and2INode *node = new reduce_and2INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orr2I_rule: {
      reduce_orr2INode *node = new reduce_orr2INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eor2I_rule: {
      reduce_eor2INode *node = new reduce_eor2INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_and4I_rule: {
      reduce_and4INode *node = new reduce_and4INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orr4I_rule: {
      reduce_orr4INode *node = new reduce_orr4INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eor4I_rule: {
      reduce_eor4INode *node = new reduce_eor4INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_and2L_rule: {
      reduce_and2LNode *node = new reduce_and2LNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orr2L_rule: {
      reduce_orr2LNode *node = new reduce_orr2LNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eor2L_rule: {
      reduce_eor2LNode *node = new reduce_eor2LNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert8B_rule: {
      insert8BNode *node = new insert8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert16B_rule: {
      insert16BNode *node = new insert16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert4S_rule: {
      insert4SNode *node = new insert4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert8S_rule: {
      insert8SNode *node = new insert8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert2I_rule: {
      insert2INode *node = new insert2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert4I_rule: {
      insert4INode *node = new insert4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert2L_rule: {
      insert2LNode *node = new insert2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert2F_rule: {
      insert2FNode *node = new insert2FNode();
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert4F_rule: {
      insert4FNode *node = new insert4FNode();
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert2D_rule: {
      insert2DNode *node = new insert2DNode();
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extract8B_rule: {
      extract8BNode *node = new extract8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extract16B_rule: {
      extract16BNode *node = new extract16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extract4S_rule: {
      extract4SNode *node = new extract4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extract8S_rule: {
      extract8SNode *node = new extract8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extract2I_rule: {
      extract2INode *node = new extract2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extract4I_rule: {
      extract4INode *node = new extract4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extract2L_rule: {
      extract2LNode *node = new extract2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extract2F_rule: {
      extract2FNode *node = new extract2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extract4F_rule: {
      extract4FNode *node = new extract4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extract2D_rule: {
      extract2DNode *node = new extract2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcmpD_rule: {
      vcmpDNode *node = new vcmpDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcmpX_rule: {
      vcmpXNode *node = new vcmpXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2L_rule: {
      vmul2LNode *node = new vmul2LNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot2I_rule: {
      vnot2INode *node = new vnot2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot2I_0_rule: {
      vnot2I_0Node *node = new vnot2I_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot2I_1_rule: {
      vnot2I_1Node *node = new vnot2I_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot2I_2_rule: {
      vnot2I_2Node *node = new vnot2I_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot2I_3_rule: {
      vnot2I_3Node *node = new vnot2I_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot2I_4_rule: {
      vnot2I_4Node *node = new vnot2I_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot4I_rule: {
      vnot4INode *node = new vnot4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot4I_0_rule: {
      vnot4I_0Node *node = new vnot4I_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot4I_1_rule: {
      vnot4I_1Node *node = new vnot4I_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot4I_2_rule: {
      vnot4I_2Node *node = new vnot4I_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot4I_3_rule: {
      vnot4I_3Node *node = new vnot4I_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot4I_4_rule: {
      vnot4I_4Node *node = new vnot4I_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot2L_rule: {
      vnot2LNode *node = new vnot2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnot2L_0_rule: {
      vnot2L_0Node *node = new vnot2L_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_rule: {
      vand_not2INode *node = new vand_not2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_1_rule: {
      vand_not2I_1Node *node = new vand_not2I_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_0_rule: {
      vand_not2I_0Node *node = new vand_not2I_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_2_rule: {
      vand_not2I_2Node *node = new vand_not2I_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_3_rule: {
      vand_not2I_3Node *node = new vand_not2I_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_5_rule: {
      vand_not2I_5Node *node = new vand_not2I_5Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_4_rule: {
      vand_not2I_4Node *node = new vand_not2I_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_6_rule: {
      vand_not2I_6Node *node = new vand_not2I_6Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_7_rule: {
      vand_not2I_7Node *node = new vand_not2I_7Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_9_rule: {
      vand_not2I_9Node *node = new vand_not2I_9Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_8_rule: {
      vand_not2I_8Node *node = new vand_not2I_8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2I_10_rule: {
      vand_not2I_10Node *node = new vand_not2I_10Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_rule: {
      vand_not4INode *node = new vand_not4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_1_rule: {
      vand_not4I_1Node *node = new vand_not4I_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_0_rule: {
      vand_not4I_0Node *node = new vand_not4I_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_2_rule: {
      vand_not4I_2Node *node = new vand_not4I_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_3_rule: {
      vand_not4I_3Node *node = new vand_not4I_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_5_rule: {
      vand_not4I_5Node *node = new vand_not4I_5Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_4_rule: {
      vand_not4I_4Node *node = new vand_not4I_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_6_rule: {
      vand_not4I_6Node *node = new vand_not4I_6Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_7_rule: {
      vand_not4I_7Node *node = new vand_not4I_7Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_9_rule: {
      vand_not4I_9Node *node = new vand_not4I_9Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_8_rule: {
      vand_not4I_8Node *node = new vand_not4I_8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not4I_10_rule: {
      vand_not4I_10Node *node = new vand_not4I_10Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2L_rule: {
      vand_not2LNode *node = new vand_not2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2L_1_rule: {
      vand_not2L_1Node *node = new vand_not2L_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2L_0_rule: {
      vand_not2L_0Node *node = new vand_not2L_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_not2L_2_rule: {
      vand_not2L_2Node *node = new vand_not2L_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax8B_rule: {
      vmax8BNode *node = new vmax8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax16B_rule: {
      vmax16BNode *node = new vmax16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax4S_rule: {
      vmax4SNode *node = new vmax4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax8S_rule: {
      vmax8SNode *node = new vmax8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax2I_rule: {
      vmax2INode *node = new vmax2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax4I_rule: {
      vmax4INode *node = new vmax4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin8B_rule: {
      vmin8BNode *node = new vmin8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin16B_rule: {
      vmin16BNode *node = new vmin16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin4S_rule: {
      vmin4SNode *node = new vmin4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin8S_rule: {
      vmin8SNode *node = new vmin8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin2I_rule: {
      vmin2INode *node = new vmin2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin4I_rule: {
      vmin4INode *node = new vmin4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax2L_rule: {
      vmax2LNode *node = new vmax2LNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin2L_rule: {
      vmin2LNode *node = new vmin2LNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vbsl8B_rule: {
      vbsl8BNode *node = new vbsl8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vbsl16B_rule: {
      vbsl16BNode *node = new vbsl16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadmask8B_rule: {
      loadmask8BNode *node = new loadmask8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadmask16B_rule: {
      loadmask16BNode *node = new loadmask16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storemask8B_rule: {
      storemask8BNode *node = new storemask8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storemask16B_rule: {
      storemask16BNode *node = new storemask16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadmask4S_rule: {
      loadmask4SNode *node = new loadmask4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadmask8S_rule: {
      loadmask8SNode *node = new loadmask8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storemask4S_rule: {
      storemask4SNode *node = new storemask4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storemask8S_rule: {
      storemask8SNode *node = new storemask8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadmask2I_rule: {
      loadmask2INode *node = new loadmask2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadmask4I_rule: {
      loadmask4INode *node = new loadmask4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storemask2I_rule: {
      storemask2INode *node = new storemask2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storemask4I_rule: {
      storemask4INode *node = new storemask4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadmask2L_rule: {
      loadmask2LNode *node = new loadmask2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storemask2L_rule: {
      storemask2LNode *node = new storemask2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcastD_rule: {
      vmaskcastDNode *node = new vmaskcastDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcastX_rule: {
      vmaskcastXNode *node = new vmaskcastXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadcon8B_rule: {
      loadcon8BNode *node = new loadcon8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadcon16B_rule: {
      loadcon16BNode *node = new loadcon16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadshuffle8B_rule: {
      loadshuffle8BNode *node = new loadshuffle8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadshuffle16B_rule: {
      loadshuffle16BNode *node = new loadshuffle16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadshuffle4S_rule: {
      loadshuffle4SNode *node = new loadshuffle4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadshuffle8S_rule: {
      loadshuffle8SNode *node = new loadshuffle8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadshuffle4I_rule: {
      loadshuffle4INode *node = new loadshuffle4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrange8B_rule: {
      rearrange8BNode *node = new rearrange8BNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrange16B_rule: {
      rearrange16BNode *node = new rearrange16BNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrange4S_rule: {
      rearrange4SNode *node = new rearrange4SNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->set_opnd_array(5, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrange8S_rule: {
      rearrange8SNode *node = new rearrange8SNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->set_opnd_array(5, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrange4I_rule: {
      rearrange4INode *node = new rearrange4INode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->set_opnd_array(5, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case anytrue_in_mask8B_rule: {
      anytrue_in_mask8BNode *node = new anytrue_in_mask8BNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case anytrue_in_mask16B_rule: {
      anytrue_in_mask16BNode *node = new anytrue_in_mask16BNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case alltrue_in_mask8B_rule: {
      alltrue_in_mask8BNode *node = new alltrue_in_mask8BNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case alltrue_in_mask16B_rule: {
      alltrue_in_mask16BNode *node = new alltrue_in_mask16BNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs8B_rule: {
      vabs8BNode *node = new vabs8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs16B_rule: {
      vabs16BNode *node = new vabs16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs4S_rule: {
      vabs4SNode *node = new vabs4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs8S_rule: {
      vabs8SNode *node = new vabs8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs2I_rule: {
      vabs2INode *node = new vabs2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs4I_rule: {
      vabs4INode *node = new vabs4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs2L_rule: {
      vabs2LNode *node = new vabs2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs2F_rule: {
      vabs2FNode *node = new vabs2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs4F_rule: {
      vabs4FNode *node = new vabs4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs2D_rule: {
      vabs2DNode *node = new vabs2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabd2F_rule: {
      vabd2FNode *node = new vabd2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabd4F_rule: {
      vabd4FNode *node = new vabd4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabd2D_rule: {
      vabd2DNode *node = new vabd2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate8B_rule: {
      replicate8BNode *node = new replicate8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate16B_rule: {
      replicate16BNode *node = new replicate16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate8B_imm_rule: {
      replicate8B_immNode *node = new replicate8B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate16B_imm_rule: {
      replicate16B_immNode *node = new replicate16B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate4S_rule: {
      replicate4SNode *node = new replicate4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate8S_rule: {
      replicate8SNode *node = new replicate8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate4S_imm_rule: {
      replicate4S_immNode *node = new replicate4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate8S_imm_rule: {
      replicate8S_immNode *node = new replicate8S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate2I_rule: {
      replicate2INode *node = new replicate2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate4I_rule: {
      replicate4INode *node = new replicate4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate2I_imm_rule: {
      replicate2I_immNode *node = new replicate2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate4I_imm_rule: {
      replicate4I_immNode *node = new replicate4I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate2L_rule: {
      replicate2LNode *node = new replicate2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate2L_zero_rule: {
      replicate2L_zeroNode *node = new replicate2L_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate2F_rule: {
      replicate2FNode *node = new replicate2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate4F_rule: {
      replicate4FNode *node = new replicate4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicate2D_rule: {
      replicate2DNode *node = new replicate2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add2I_rule: {
      reduce_add2INode *node = new reduce_add2INode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add4I_rule: {
      reduce_add4INode *node = new reduce_add4INode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mul2I_rule: {
      reduce_mul2INode *node = new reduce_mul2INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mul4I_rule: {
      reduce_mul4INode *node = new reduce_mul4INode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->set_opnd_array(5, MachOperGenerator(IREGINOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add2F_rule: {
      reduce_add2FNode *node = new reduce_add2FNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add4F_rule: {
      reduce_add4FNode *node = new reduce_add4FNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mul2F_rule: {
      reduce_mul2FNode *node = new reduce_mul2FNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mul4F_rule: {
      reduce_mul4FNode *node = new reduce_mul4FNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_add2D_rule: {
      reduce_add2DNode *node = new reduce_add2DNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_mul2D_rule: {
      reduce_mul2DNode *node = new reduce_mul2DNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8B_rule: {
      vadd8BNode *node = new vadd8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16B_rule: {
      vadd16BNode *node = new vadd16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4S_rule: {
      vadd4SNode *node = new vadd4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8S_rule: {
      vadd8SNode *node = new vadd8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2I_rule: {
      vadd2INode *node = new vadd2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4I_rule: {
      vadd4INode *node = new vadd4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2L_rule: {
      vadd2LNode *node = new vadd2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2F_rule: {
      vadd2FNode *node = new vadd2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4F_rule: {
      vadd4FNode *node = new vadd4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2D_rule: {
      vadd2DNode *node = new vadd2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8B_rule: {
      vsub8BNode *node = new vsub8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16B_rule: {
      vsub16BNode *node = new vsub16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4S_rule: {
      vsub4SNode *node = new vsub4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8S_rule: {
      vsub8SNode *node = new vsub8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2I_rule: {
      vsub2INode *node = new vsub2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4I_rule: {
      vsub4INode *node = new vsub4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2L_rule: {
      vsub2LNode *node = new vsub2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2F_rule: {
      vsub2FNode *node = new vsub2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4F_rule: {
      vsub4FNode *node = new vsub4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2D_rule: {
      vsub2DNode *node = new vsub2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8B_rule: {
      vmul8BNode *node = new vmul8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16B_rule: {
      vmul16BNode *node = new vmul16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4S_rule: {
      vmul4SNode *node = new vmul4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8S_rule: {
      vmul8SNode *node = new vmul8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2I_rule: {
      vmul2INode *node = new vmul2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4I_rule: {
      vmul4INode *node = new vmul4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2F_rule: {
      vmul2FNode *node = new vmul2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4F_rule: {
      vmul4FNode *node = new vmul4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2D_rule: {
      vmul2DNode *node = new vmul2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla4S_rule: {
      vmla4SNode *node = new vmla4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla4S_0_rule: {
      vmla4S_0Node *node = new vmla4S_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla8S_rule: {
      vmla8SNode *node = new vmla8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla8S_0_rule: {
      vmla8S_0Node *node = new vmla8S_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla2I_rule: {
      vmla2INode *node = new vmla2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla2I_0_rule: {
      vmla2I_0Node *node = new vmla2I_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla4I_rule: {
      vmla4INode *node = new vmla4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla4I_0_rule: {
      vmla4I_0Node *node = new vmla4I_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla2F_rule: {
      vmla2FNode *node = new vmla2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla4F_rule: {
      vmla4FNode *node = new vmla4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmla2D_rule: {
      vmla2DNode *node = new vmla2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls4S_rule: {
      vmls4SNode *node = new vmls4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls8S_rule: {
      vmls8SNode *node = new vmls8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls2I_rule: {
      vmls2INode *node = new vmls2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls4I_rule: {
      vmls4INode *node = new vmls4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls2F_rule: {
      vmls2FNode *node = new vmls2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls2F_0_rule: {
      vmls2F_0Node *node = new vmls2F_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls4F_rule: {
      vmls4FNode *node = new vmls4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls4F_0_rule: {
      vmls4F_0Node *node = new vmls4F_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls2D_rule: {
      vmls2DNode *node = new vmls2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmls2D_0_rule: {
      vmls2D_0Node *node = new vmls2D_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmuladdS2I_rule: {
      vmuladdS2INode *node = new vmuladdS2INode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->set_opnd_array(4, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv2F_rule: {
      vdiv2FNode *node = new vdiv2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv4F_rule: {
      vdiv4FNode *node = new vdiv4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv2D_rule: {
      vdiv2DNode *node = new vdiv2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt2F_rule: {
      vsqrt2FNode *node = new vsqrt2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt4F_rule: {
      vsqrt4FNode *node = new vsqrt4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt2D_rule: {
      vsqrt2DNode *node = new vsqrt2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vneg2F_rule: {
      vneg2FNode *node = new vneg2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vneg4F_rule: {
      vneg4FNode *node = new vneg4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vneg2D_rule: {
      vneg2DNode *node = new vneg2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand8B_rule: {
      vand8BNode *node = new vand8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand16B_rule: {
      vand16BNode *node = new vand16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor8B_rule: {
      vor8BNode *node = new vor8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor16B_rule: {
      vor16BNode *node = new vor16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor8B_rule: {
      vxor8BNode *node = new vxor8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor16B_rule: {
      vxor16BNode *node = new vxor16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcnt8B_rule: {
      vshiftcnt8BNode *node = new vshiftcnt8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcnt8B_0_rule: {
      vshiftcnt8B_0Node *node = new vshiftcnt8B_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcnt16B_rule: {
      vshiftcnt16BNode *node = new vshiftcnt16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcnt16B_0_rule: {
      vshiftcnt16B_0Node *node = new vshiftcnt16B_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8B_rule: {
      vsll8BNode *node = new vsll8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll16B_rule: {
      vsll16BNode *node = new vsll16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8B_rule: {
      vsra8BNode *node = new vsra8BNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra16B_rule: {
      vsra16BNode *node = new vsra16BNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8B_rule: {
      vsrl8BNode *node = new vsrl8BNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl16B_rule: {
      vsrl16BNode *node = new vsrl16BNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8B_imm_rule: {
      vsll8B_immNode *node = new vsll8B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll16B_imm_rule: {
      vsll16B_immNode *node = new vsll16B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8B_imm_rule: {
      vsra8B_immNode *node = new vsra8B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra16B_imm_rule: {
      vsra16B_immNode *node = new vsra16B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8B_imm_rule: {
      vsrl8B_immNode *node = new vsrl8B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl16B_imm_rule: {
      vsrl16B_immNode *node = new vsrl16B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4S_rule: {
      vsll4SNode *node = new vsll4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8S_rule: {
      vsll8SNode *node = new vsll8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4S_rule: {
      vsra4SNode *node = new vsra4SNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8S_rule: {
      vsra8SNode *node = new vsra8SNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4S_rule: {
      vsrl4SNode *node = new vsrl4SNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8S_rule: {
      vsrl8SNode *node = new vsrl8SNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4S_imm_rule: {
      vsll4S_immNode *node = new vsll4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8S_imm_rule: {
      vsll8S_immNode *node = new vsll8S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4S_imm_rule: {
      vsra4S_immNode *node = new vsra4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8S_imm_rule: {
      vsra8S_immNode *node = new vsra8S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4S_imm_rule: {
      vsrl4S_immNode *node = new vsrl4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8S_imm_rule: {
      vsrl8S_immNode *node = new vsrl8S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2I_rule: {
      vsll2INode *node = new vsll2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4I_rule: {
      vsll4INode *node = new vsll4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2I_rule: {
      vsra2INode *node = new vsra2INode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4I_rule: {
      vsra4INode *node = new vsra4INode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2I_rule: {
      vsrl2INode *node = new vsrl2INode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4I_rule: {
      vsrl4INode *node = new vsrl4INode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2I_imm_rule: {
      vsll2I_immNode *node = new vsll2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4I_imm_rule: {
      vsll4I_immNode *node = new vsll4I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2I_imm_rule: {
      vsra2I_immNode *node = new vsra2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4I_imm_rule: {
      vsra4I_immNode *node = new vsra4I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2I_imm_rule: {
      vsrl2I_immNode *node = new vsrl2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4I_imm_rule: {
      vsrl4I_immNode *node = new vsrl4I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2L_rule: {
      vsll2LNode *node = new vsll2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2L_rule: {
      vsra2LNode *node = new vsra2LNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2L_rule: {
      vsrl2LNode *node = new vsrl2LNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2L_imm_rule: {
      vsll2L_immNode *node = new vsll2L_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2L_imm_rule: {
      vsra2L_immNode *node = new vsra2L_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2L_imm_rule: {
      vsrl2L_immNode *node = new vsrl2L_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa8B_imm_rule: {
      vsraa8B_immNode *node = new vsraa8B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa8B_imm_0_rule: {
      vsraa8B_imm_0Node *node = new vsraa8B_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa16B_imm_rule: {
      vsraa16B_immNode *node = new vsraa16B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa16B_imm_0_rule: {
      vsraa16B_imm_0Node *node = new vsraa16B_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa4S_imm_rule: {
      vsraa4S_immNode *node = new vsraa4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa4S_imm_0_rule: {
      vsraa4S_imm_0Node *node = new vsraa4S_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa8S_imm_rule: {
      vsraa8S_immNode *node = new vsraa8S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa8S_imm_0_rule: {
      vsraa8S_imm_0Node *node = new vsraa8S_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa2I_imm_rule: {
      vsraa2I_immNode *node = new vsraa2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa2I_imm_0_rule: {
      vsraa2I_imm_0Node *node = new vsraa2I_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa4I_imm_rule: {
      vsraa4I_immNode *node = new vsraa4I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa4I_imm_0_rule: {
      vsraa4I_imm_0Node *node = new vsraa4I_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa2L_imm_rule: {
      vsraa2L_immNode *node = new vsraa2L_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsraa2L_imm_0_rule: {
      vsraa2L_imm_0Node *node = new vsraa2L_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla8B_imm_rule: {
      vsrla8B_immNode *node = new vsrla8B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla8B_imm_0_rule: {
      vsrla8B_imm_0Node *node = new vsrla8B_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla16B_imm_rule: {
      vsrla16B_immNode *node = new vsrla16B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla16B_imm_0_rule: {
      vsrla16B_imm_0Node *node = new vsrla16B_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla4S_imm_rule: {
      vsrla4S_immNode *node = new vsrla4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla4S_imm_0_rule: {
      vsrla4S_imm_0Node *node = new vsrla4S_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla8S_imm_rule: {
      vsrla8S_immNode *node = new vsrla8S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla8S_imm_0_rule: {
      vsrla8S_imm_0Node *node = new vsrla8S_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla2I_imm_rule: {
      vsrla2I_immNode *node = new vsrla2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla2I_imm_0_rule: {
      vsrla2I_imm_0Node *node = new vsrla2I_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla4I_imm_rule: {
      vsrla4I_immNode *node = new vsrla4I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla4I_imm_0_rule: {
      vsrla4I_imm_0Node *node = new vsrla4I_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla2L_imm_rule: {
      vsrla2L_immNode *node = new vsrla2L_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrla2L_imm_0_rule: {
      vsrla2L_imm_0Node *node = new vsrla2L_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax2F_rule: {
      vmax2FNode *node = new vmax2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax4F_rule: {
      vmax4FNode *node = new vmax4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax2D_rule: {
      vmax2DNode *node = new vmax2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin2F_rule: {
      vmin2FNode *node = new vmin2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin4F_rule: {
      vmin4FNode *node = new vmin4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin2D_rule: {
      vmin2DNode *node = new vmin2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vround2D_reg_rule: {
      vround2D_regNode *node = new vround2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcount4I_rule: {
      vpopcount4INode *node = new vpopcount4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcount2I_rule: {
      vpopcount2INode *node = new vpopcount2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_truecount8B_rule: {
      vmask_truecount8BNode *node = new vmask_truecount8BNode();
      node->set_opnd_array(2, MachOperGenerator(VECD));
      return node;
    }
  case vmask_truecount16B_rule: {
      vmask_truecount16BNode *node = new vmask_truecount16BNode();
      node->set_opnd_array(2, MachOperGenerator(VECX));
      return node;
    }
  case vmask_firsttrue_LT8B_rule: {
      vmask_firsttrue_LT8BNode *node = new vmask_firsttrue_LT8BNode();
      return node;
    }
  case vmask_firsttrue8B_rule: {
      vmask_firsttrue8BNode *node = new vmask_firsttrue8BNode();
      return node;
    }
  case vmask_firsttrue16B_rule: {
      vmask_firsttrue16BNode *node = new vmask_firsttrue16BNode();
      return node;
    }
  case vmask_lasttrue8B_rule: {
      vmask_lasttrue8BNode *node = new vmask_lasttrue8BNode();
      return node;
    }
  case vmask_lasttrue16B_rule: {
      vmask_lasttrue16BNode *node = new vmask_lasttrue16BNode();
      return node;
    }
  case vmask_tolong8B_rule: {
      vmask_tolong8BNode *node = new vmask_tolong8BNode();
      return node;
    }
  case vmask_tolong16B_rule: {
      vmask_tolong16BNode *node = new vmask_tolong16BNode();
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
  case loadV2_vreg_rule: {
      loadV2_vregNode *node = new loadV2_vregNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV2_vreg_rule: {
      storeV2_vregNode *node = new storeV2_vregNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV4_vreg_rule: {
      loadV4_vregNode *node = new loadV4_vregNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV4_vreg_rule: {
      storeV4_vregNode *node = new storeV4_vregNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV8_vreg_rule: {
      loadV8_vregNode *node = new loadV8_vregNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV8_vreg_rule: {
      storeV8_vregNode *node = new storeV8_vregNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV16_vreg_rule: {
      loadV16_vregNode *node = new loadV16_vregNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV16_vreg_rule: {
      storeV16_vregNode *node = new storeV16_vregNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV_partial_rule: {
      loadV_partialNode *node = new loadV_partialNode();
      node->set_opnd_array(2, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV_partial_rule: {
      storeV_partialNode *node = new storeV_partialNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV_masked_rule: {
      loadV_maskedNode *node = new loadV_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV_masked_partial_rule: {
      loadV_masked_partialNode *node = new loadV_masked_partialNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV_masked_rule: {
      storeV_maskedNode *node = new storeV_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV_masked_partial_rule: {
      storeV_masked_partialNode *node = new storeV_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
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
  case reinterpret_rule: {
      reinterpretNode *node = new reinterpretNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretResize_rule: {
      reinterpretResizeNode *node = new reinterpretResizeNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
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
  case vandB_rule: {
      vandBNode *node = new vandBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandB_0_rule: {
      vandB_0Node *node = new vandB_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandH_rule: {
      vandHNode *node = new vandHNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandH_0_rule: {
      vandH_0Node *node = new vandH_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandS_rule: {
      vandSNode *node = new vandSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandS_0_rule: {
      vandS_0Node *node = new vandS_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandD_rule: {
      vandDNode *node = new vandDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vandD_0_rule: {
      vandD_0Node *node = new vandD_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorB_rule: {
      vorBNode *node = new vorBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorB_0_rule: {
      vorB_0Node *node = new vorB_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorH_rule: {
      vorHNode *node = new vorHNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorH_0_rule: {
      vorH_0Node *node = new vorH_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorS_rule: {
      vorSNode *node = new vorSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorS_0_rule: {
      vorS_0Node *node = new vorS_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorD_rule: {
      vorDNode *node = new vorDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vorD_0_rule: {
      vorD_0Node *node = new vorD_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorB_rule: {
      vxorBNode *node = new vxorBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorB_0_rule: {
      vxorB_0Node *node = new vxorB_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorH_rule: {
      vxorHNode *node = new vxorHNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorH_0_rule: {
      vxorH_0Node *node = new vxorH_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorS_rule: {
      vxorSNode *node = new vxorSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorS_0_rule: {
      vxorS_0Node *node = new vxorS_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorD_rule: {
      vxorDNode *node = new vxorDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxorD_0_rule: {
      vxorD_0Node *node = new vxorD_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_rule: {
      vandNode *node = new vandNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor_rule: {
      vorNode *node = new vorNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor_rule: {
      vxorNode *node = new vxorNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_masked_rule: {
      vand_maskedNode *node = new vand_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor_masked_rule: {
      vor_maskedNode *node = new vor_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor_masked_rule: {
      vxor_maskedNode *node = new vxor_maskedNode();
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
  case vnotI_1_rule: {
      vnotI_1Node *node = new vnotI_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnotI_2_rule: {
      vnotI_2Node *node = new vnotI_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnotI_3_rule: {
      vnotI_3Node *node = new vnotI_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vnotI_4_rule: {
      vnotI_4Node *node = new vnotI_4Node();
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
  case vand_notI_3_rule: {
      vand_notI_3Node *node = new vand_notI_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_5_rule: {
      vand_notI_5Node *node = new vand_notI_5Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_4_rule: {
      vand_notI_4Node *node = new vand_notI_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_6_rule: {
      vand_notI_6Node *node = new vand_notI_6Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_7_rule: {
      vand_notI_7Node *node = new vand_notI_7Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_9_rule: {
      vand_notI_9Node *node = new vand_notI_9Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_8_rule: {
      vand_notI_8Node *node = new vand_notI_8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_notI_10_rule: {
      vand_notI_10Node *node = new vand_notI_10Node();
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
  case vdivF_rule: {
      vdivFNode *node = new vdivFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivD_rule: {
      vdivDNode *node = new vdivDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfdivF_masked_rule: {
      vfdivF_maskedNode *node = new vfdivF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfdivD_masked_rule: {
      vfdivD_maskedNode *node = new vfdivD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin_rule: {
      vminNode *node = new vminNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax_rule: {
      vmaxNode *node = new vmaxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmin_masked_rule: {
      vmin_maskedNode *node = new vmin_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmax_masked_rule: {
      vmax_maskedNode *node = new vmax_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmlaF_rule: {
      vfmlaFNode *node = new vfmlaFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmlaD_rule: {
      vfmlaDNode *node = new vfmlaDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmlaF_masked_rule: {
      vfmlaF_maskedNode *node = new vfmlaF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmlaD_masked_rule: {
      vfmlaD_maskedNode *node = new vfmlaD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmlsF_rule: {
      vfmlsFNode *node = new vfmlsFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmlsF_0_rule: {
      vfmlsF_0Node *node = new vfmlsF_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmlsD_rule: {
      vfmlsDNode *node = new vfmlsDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmlsD_0_rule: {
      vfmlsD_0Node *node = new vfmlsD_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmlaF_rule: {
      vfnmlaFNode *node = new vfnmlaFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmlaF_0_rule: {
      vfnmlaF_0Node *node = new vfnmlaF_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmlaD_rule: {
      vfnmlaDNode *node = new vfnmlaDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmlaD_0_rule: {
      vfnmlaD_0Node *node = new vfnmlaD_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmlsF_rule: {
      vfnmlsFNode *node = new vfnmlsFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfnmlsD_rule: {
      vfnmlsDNode *node = new vfnmlsDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlaB_rule: {
      vmlaBNode *node = new vmlaBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlaB_0_rule: {
      vmlaB_0Node *node = new vmlaB_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlaS_rule: {
      vmlaSNode *node = new vmlaSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlaS_0_rule: {
      vmlaS_0Node *node = new vmlaS_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlaI_rule: {
      vmlaINode *node = new vmlaINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlaI_0_rule: {
      vmlaI_0Node *node = new vmlaI_0Node();
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
  case vmlsB_rule: {
      vmlsBNode *node = new vmlsBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlsS_rule: {
      vmlsSNode *node = new vmlsSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlsI_rule: {
      vmlsINode *node = new vmlsINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmlsL_rule: {
      vmlsLNode *node = new vmlsLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulB_rule: {
      vmulBNode *node = new vmulBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulS_rule: {
      vmulSNode *node = new vmulSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulI_rule: {
      vmulINode *node = new vmulINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulL_rule: {
      vmulLNode *node = new vmulLNode();
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
  case vpopcountI_rule: {
      vpopcountINode *node = new vpopcountINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_rule: {
      vmaskcmpNode *node = new vmaskcmpNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcmp_masked_rule: {
      vmaskcmp_maskedNode *node = new vmaskcmp_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vblend_rule: {
      vblendNode *node = new vblendNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmaskB_rule: {
      vloadmaskBNode *node = new vloadmaskBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vloadmask_extend_rule: {
      vloadmask_extendNode *node = new vloadmask_extendNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoremaskB_rule: {
      vstoremaskBNode *node = new vstoremaskBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoremask_narrow_rule: {
      vstoremask_narrowNode *node = new vstoremask_narrowNode();
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
  case vloadmask_loadV_partial_rule: {
      vloadmask_loadV_partialNode *node = new vloadmask_loadV_partialNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV_vstoremask_rule: {
      storeV_vstoremaskNode *node = new storeV_vstoremaskNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV_vstoremask_partial_rule: {
      storeV_vstoremask_partialNode *node = new storeV_vstoremask_partialNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addI_rule: {
      reduce_addINode *node = new reduce_addINode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addL_rule: {
      reduce_addLNode *node = new reduce_addLNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addF_rule: {
      reduce_addFNode *node = new reduce_addFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addD_rule: {
      reduce_addDNode *node = new reduce_addDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addI_partial_rule: {
      reduce_addI_partialNode *node = new reduce_addI_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addL_partial_rule: {
      reduce_addL_partialNode *node = new reduce_addL_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addF_partial_rule: {
      reduce_addF_partialNode *node = new reduce_addF_partialNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addD_partial_rule: {
      reduce_addD_partialNode *node = new reduce_addD_partialNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
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
  case reduce_addI_masked_partial_rule: {
      reduce_addI_masked_partialNode *node = new reduce_addI_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addL_masked_partial_rule: {
      reduce_addL_masked_partialNode *node = new reduce_addL_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addF_masked_partial_rule: {
      reduce_addF_masked_partialNode *node = new reduce_addF_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_addD_masked_partial_rule: {
      reduce_addD_masked_partialNode *node = new reduce_addD_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andI_rule: {
      reduce_andINode *node = new reduce_andINode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andL_rule: {
      reduce_andLNode *node = new reduce_andLNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andI_partial_rule: {
      reduce_andI_partialNode *node = new reduce_andI_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andL_partial_rule: {
      reduce_andL_partialNode *node = new reduce_andL_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
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
  case reduce_andI_masked_partial_rule: {
      reduce_andI_masked_partialNode *node = new reduce_andI_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_andL_masked_partial_rule: {
      reduce_andL_masked_partialNode *node = new reduce_andL_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orI_rule: {
      reduce_orINode *node = new reduce_orINode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orL_rule: {
      reduce_orLNode *node = new reduce_orLNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orI_partial_rule: {
      reduce_orI_partialNode *node = new reduce_orI_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orL_partial_rule: {
      reduce_orL_partialNode *node = new reduce_orL_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
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
  case reduce_orI_masked_partial_rule: {
      reduce_orI_masked_partialNode *node = new reduce_orI_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_orL_masked_partial_rule: {
      reduce_orL_masked_partialNode *node = new reduce_orL_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eorI_rule: {
      reduce_eorINode *node = new reduce_eorINode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eorL_rule: {
      reduce_eorLNode *node = new reduce_eorLNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eorI_partial_rule: {
      reduce_eorI_partialNode *node = new reduce_eorI_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eorL_partial_rule: {
      reduce_eorL_partialNode *node = new reduce_eorL_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eorI_masked_rule: {
      reduce_eorI_maskedNode *node = new reduce_eorI_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eorL_masked_rule: {
      reduce_eorL_maskedNode *node = new reduce_eorL_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eorI_masked_partial_rule: {
      reduce_eorI_masked_partialNode *node = new reduce_eorI_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_eorL_masked_partial_rule: {
      reduce_eorL_masked_partialNode *node = new reduce_eorL_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxI_rule: {
      reduce_maxINode *node = new reduce_maxINode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxL_rule: {
      reduce_maxLNode *node = new reduce_maxLNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxI_partial_rule: {
      reduce_maxI_partialNode *node = new reduce_maxI_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxL_partial_rule: {
      reduce_maxL_partialNode *node = new reduce_maxL_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxF_rule: {
      reduce_maxFNode *node = new reduce_maxFNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxF_partial_rule: {
      reduce_maxF_partialNode *node = new reduce_maxF_partialNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxD_rule: {
      reduce_maxDNode *node = new reduce_maxDNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxD_partial_rule: {
      reduce_maxD_partialNode *node = new reduce_maxD_partialNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
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
  case reduce_maxI_masked_partial_rule: {
      reduce_maxI_masked_partialNode *node = new reduce_maxI_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxL_masked_partial_rule: {
      reduce_maxL_masked_partialNode *node = new reduce_maxL_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxF_masked_rule: {
      reduce_maxF_maskedNode *node = new reduce_maxF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxD_masked_rule: {
      reduce_maxD_maskedNode *node = new reduce_maxD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxF_masked_partial_rule: {
      reduce_maxF_masked_partialNode *node = new reduce_maxF_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_maxD_masked_partial_rule: {
      reduce_maxD_masked_partialNode *node = new reduce_maxD_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minI_rule: {
      reduce_minINode *node = new reduce_minINode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minL_rule: {
      reduce_minLNode *node = new reduce_minLNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minI_partial_rule: {
      reduce_minI_partialNode *node = new reduce_minI_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minL_partial_rule: {
      reduce_minL_partialNode *node = new reduce_minL_partialNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minF_rule: {
      reduce_minFNode *node = new reduce_minFNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minF_partial_rule: {
      reduce_minF_partialNode *node = new reduce_minF_partialNode();
      node->set_opnd_array(3, MachOperGenerator(VREGF));
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minD_rule: {
      reduce_minDNode *node = new reduce_minDNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minD_partial_rule: {
      reduce_minD_partialNode *node = new reduce_minD_partialNode();
      node->set_opnd_array(3, MachOperGenerator(VREGD));
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
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
  case reduce_minI_masked_partial_rule: {
      reduce_minI_masked_partialNode *node = new reduce_minI_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minL_masked_partial_rule: {
      reduce_minL_masked_partialNode *node = new reduce_minL_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLNOSP));
      node->set_opnd_array(5, MachOperGenerator(VREGD));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minF_masked_rule: {
      reduce_minF_maskedNode *node = new reduce_minF_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minD_masked_rule: {
      reduce_minD_maskedNode *node = new reduce_minD_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minF_masked_partial_rule: {
      reduce_minF_masked_partialNode *node = new reduce_minF_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(VREGF));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduce_minD_masked_partial_rule: {
      reduce_minD_masked_partialNode *node = new reduce_minD_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(VREGD));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vroundD_rule: {
      vroundDNode *node = new vroundDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateB_rule: {
      replicateBNode *node = new replicateBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateS_rule: {
      replicateSNode *node = new replicateSNode();
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
  case replicateB_imm8_rule: {
      replicateB_imm8Node *node = new replicateB_imm8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateS_imm8_rule: {
      replicateS_imm8Node *node = new replicateS_imm8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateI_imm8_rule: {
      replicateI_imm8Node *node = new replicateI_imm8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case replicateL_imm8_rule: {
      replicateL_imm8Node *node = new replicateL_imm8Node();
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
  case vasrB_rule: {
      vasrBNode *node = new vasrBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrS_rule: {
      vasrSNode *node = new vasrSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrI_rule: {
      vasrINode *node = new vasrINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrL_rule: {
      vasrLNode *node = new vasrLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslB_rule: {
      vlslBNode *node = new vlslBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslS_rule: {
      vlslSNode *node = new vlslSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslI_rule: {
      vlslINode *node = new vlslINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslL_rule: {
      vlslLNode *node = new vlslLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrB_rule: {
      vlsrBNode *node = new vlsrBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrS_rule: {
      vlsrSNode *node = new vlsrSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrI_rule: {
      vlsrINode *node = new vlsrINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrL_rule: {
      vlsrLNode *node = new vlsrLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrB_imm_rule: {
      vasrB_immNode *node = new vasrB_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrS_imm_rule: {
      vasrS_immNode *node = new vasrS_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrI_imm_rule: {
      vasrI_immNode *node = new vasrI_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrL_imm_rule: {
      vasrL_immNode *node = new vasrL_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrB_imm_rule: {
      vlsrB_immNode *node = new vlsrB_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrS_imm_rule: {
      vlsrS_immNode *node = new vlsrS_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrI_imm_rule: {
      vlsrI_immNode *node = new vlsrI_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrL_imm_rule: {
      vlsrL_immNode *node = new vlsrL_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslB_imm_rule: {
      vlslB_immNode *node = new vlslB_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslS_imm_rule: {
      vlslS_immNode *node = new vlslS_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslI_imm_rule: {
      vlslI_immNode *node = new vlslI_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslL_imm_rule: {
      vlslL_immNode *node = new vlslL_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcntB_rule: {
      vshiftcntBNode *node = new vshiftcntBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcntB_0_rule: {
      vshiftcntB_0Node *node = new vshiftcntB_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcntS_rule: {
      vshiftcntSNode *node = new vshiftcntSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcntS_0_rule: {
      vshiftcntS_0Node *node = new vshiftcntS_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcntI_rule: {
      vshiftcntINode *node = new vshiftcntINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcntI_0_rule: {
      vshiftcntI_0Node *node = new vshiftcntI_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcntL_rule: {
      vshiftcntLNode *node = new vshiftcntLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcntL_0_rule: {
      vshiftcntL_0Node *node = new vshiftcntL_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrB_masked_rule: {
      vasrB_maskedNode *node = new vasrB_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrS_masked_rule: {
      vasrS_maskedNode *node = new vasrS_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrI_masked_rule: {
      vasrI_maskedNode *node = new vasrI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrL_masked_rule: {
      vasrL_maskedNode *node = new vasrL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslB_masked_rule: {
      vlslB_maskedNode *node = new vlslB_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslS_masked_rule: {
      vlslS_maskedNode *node = new vlslS_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslI_masked_rule: {
      vlslI_maskedNode *node = new vlslI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslL_masked_rule: {
      vlslL_maskedNode *node = new vlslL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrB_masked_rule: {
      vlsrB_maskedNode *node = new vlsrB_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrS_masked_rule: {
      vlsrS_maskedNode *node = new vlsrS_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrI_masked_rule: {
      vlsrI_maskedNode *node = new vlsrI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrL_masked_rule: {
      vlsrL_maskedNode *node = new vlsrL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrB_imm_masked_rule: {
      vasrB_imm_maskedNode *node = new vasrB_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrS_imm_masked_rule: {
      vasrS_imm_maskedNode *node = new vasrS_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrI_imm_masked_rule: {
      vasrI_imm_maskedNode *node = new vasrI_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vasrL_imm_masked_rule: {
      vasrL_imm_maskedNode *node = new vasrL_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrB_imm_masked_rule: {
      vlsrB_imm_maskedNode *node = new vlsrB_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrS_imm_masked_rule: {
      vlsrS_imm_maskedNode *node = new vlsrS_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrI_imm_masked_rule: {
      vlsrI_imm_maskedNode *node = new vlsrI_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlsrL_imm_masked_rule: {
      vlsrL_imm_maskedNode *node = new vlsrL_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslB_imm_masked_rule: {
      vlslB_imm_maskedNode *node = new vlslB_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslS_imm_masked_rule: {
      vlslS_imm_maskedNode *node = new vlslS_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslI_imm_masked_rule: {
      vlslI_imm_maskedNode *node = new vlslI_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlslL_imm_masked_rule: {
      vlslL_imm_maskedNode *node = new vlslL_imm_maskedNode();
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
  case vmaskcast_rule: {
      vmaskcastNode *node = new vmaskcastNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_extend_rule: {
      vmaskcast_extendNode *node = new vmaskcast_extendNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_narrow_rule: {
      vmaskcast_narrowNode *node = new vmaskcast_narrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtBtoX_extend_rule: {
      vcvtBtoX_extendNode *node = new vcvtBtoX_extendNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtStoB_rule: {
      vcvtStoBNode *node = new vcvtStoBNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtStoX_extend_rule: {
      vcvtStoX_extendNode *node = new vcvtStoX_extendNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtItoB_rule: {
      vcvtItoBNode *node = new vcvtItoBNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtItoS_rule: {
      vcvtItoSNode *node = new vcvtItoSNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtItoL_rule: {
      vcvtItoLNode *node = new vcvtItoLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtItoF_rule: {
      vcvtItoFNode *node = new vcvtItoFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtItoD_rule: {
      vcvtItoDNode *node = new vcvtItoDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtLtoX_narrow_rule: {
      vcvtLtoX_narrowNode *node = new vcvtLtoX_narrowNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtLtoF_rule: {
      vcvtLtoFNode *node = new vcvtLtoFNode();
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
  case vcvtFtoX_narrow_rule: {
      vcvtFtoX_narrowNode *node = new vcvtFtoX_narrowNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtFtoI_rule: {
      vcvtFtoINode *node = new vcvtFtoINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtFtoL_rule: {
      vcvtFtoLNode *node = new vcvtFtoLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtFtoD_rule: {
      vcvtFtoDNode *node = new vcvtFtoDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcvtDtoX_narrow_rule: {
      vcvtDtoX_narrowNode *node = new vcvtDtoX_narrowNode();
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
  case vcvtDtoF_rule: {
      vcvtDtoFNode *node = new vcvtDtoFNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractB_rule: {
      extractBNode *node = new extractBNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractS_rule: {
      extractSNode *node = new extractSNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractI_rule: {
      extractINode *node = new extractINode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractL_rule: {
      extractLNode *node = new extractLNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractF_rule: {
      extractFNode *node = new extractFNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractD_rule: {
      extractDNode *node = new extractDNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vtest_alltrue_rule: {
      vtest_alltrueNode *node = new vtest_alltrueNode();
      node->set_opnd_array(3, MachOperGenerator(PREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vtest_anytrue_rule: {
      vtest_anytrueNode *node = new vtest_anytrueNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vtest_alltrue_partial_rule: {
      vtest_alltrue_partialNode *node = new vtest_alltrue_partialNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vtest_anytrue_partial_rule: {
      vtest_anytrue_partialNode *node = new vtest_anytrue_partialNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertI_small_rule: {
      insertI_smallNode *node = new insertI_smallNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertF_small_rule: {
      insertF_smallNode *node = new insertF_smallNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertI_rule: {
      insertINode *node = new insertINode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertL_rule: {
      insertLNode *node = new insertLNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertD_rule: {
      insertDNode *node = new insertDNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertF_rule: {
      insertFNode *node = new insertFNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadshuffle_rule: {
      loadshuffleNode *node = new loadshuffleNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrange_rule: {
      rearrangeNode *node = new rearrangeNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gatherI_rule: {
      gatherINode *node = new gatherINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gatherL_rule: {
      gatherLNode *node = new gatherLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gatherI_partial_rule: {
      gatherI_partialNode *node = new gatherI_partialNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gatherL_partial_rule: {
      gatherL_partialNode *node = new gatherL_partialNode();
      node->set_opnd_array(3, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gatherI_masked_rule: {
      gatherI_maskedNode *node = new gatherI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gatherL_masked_rule: {
      gatherL_maskedNode *node = new gatherL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gatherI_masked_partial_rule: {
      gatherI_masked_partialNode *node = new gatherI_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case gatherL_masked_partial_rule: {
      gatherL_masked_partialNode *node = new gatherL_masked_partialNode();
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatterI_rule: {
      scatterINode *node = new scatterINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatterL_rule: {
      scatterLNode *node = new scatterLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatterI_partial_rule: {
      scatterI_partialNode *node = new scatterI_partialNode();
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatterL_partial_rule: {
      scatterL_partialNode *node = new scatterL_partialNode();
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatterI_masked_rule: {
      scatterI_maskedNode *node = new scatterI_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatterL_masked_rule: {
      scatterL_maskedNode *node = new scatterL_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatterI_masked_partial_rule: {
      scatterI_masked_partialNode *node = new scatterI_masked_partialNode();
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatterL_masked_partial_rule: {
      scatterL_masked_partialNode *node = new scatterL_masked_partialNode();
      node->set_opnd_array(5, MachOperGenerator(PREGGOV));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadconB_rule: {
      loadconBNode *node = new loadconBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case stringL_indexof_char_sve_rule: {
      stringL_indexof_char_sveNode *node = new stringL_indexof_char_sveNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->set_opnd_array(7, MachOperGenerator(PREG));
      return node;
    }
  case stringU_indexof_char_sve_rule: {
      stringU_indexof_char_sveNode *node = new stringU_indexof_char_sveNode();
      node->set_opnd_array(4, MachOperGenerator(VREG));
      node->set_opnd_array(5, MachOperGenerator(VREG));
      node->set_opnd_array(6, MachOperGenerator(PREGGOV));
      node->set_opnd_array(7, MachOperGenerator(PREG));
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
  case vmask_truecount_rule: {
      vmask_truecountNode *node = new vmask_truecountNode();
      return node;
    }
  case vmask_firsttrue_rule: {
      vmask_firsttrueNode *node = new vmask_firsttrueNode();
      node->set_opnd_array(2, MachOperGenerator(PREG));
      return node;
    }
  case vmask_lasttrue_rule: {
      vmask_lasttrueNode *node = new vmask_lasttrueNode();
      node->set_opnd_array(2, MachOperGenerator(PREG));
      return node;
    }
  case vmask_truecount_partial_rule: {
      vmask_truecount_partialNode *node = new vmask_truecount_partialNode();
      node->set_opnd_array(2, MachOperGenerator(PREG));
      return node;
    }
  case vmask_firsttrue_partial_rule: {
      vmask_firsttrue_partialNode *node = new vmask_firsttrue_partialNode();
      node->set_opnd_array(2, MachOperGenerator(PREG));
      node->set_opnd_array(3, MachOperGenerator(PREG));
      return node;
    }
  case vmask_lasttrue_partial_rule: {
      vmask_lasttrue_partialNode *node = new vmask_lasttrue_partialNode();
      node->set_opnd_array(2, MachOperGenerator(PREG));
      return node;
    }
  case vmask_tolong_rule: {
      vmask_tolongNode *node = new vmask_tolongNode();
      node->set_opnd_array(2, MachOperGenerator(VREG));
      node->set_opnd_array(3, MachOperGenerator(VREG));
      node->set_opnd_array(4, MachOperGenerator(PREGGOV));
      return node;
    }
  case vmask_gen_rule: {
      vmask_genNode *node = new vmask_genNode();
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
  case zCompareAndSwapP_rule: {
      zCompareAndSwapPNode *node = new zCompareAndSwapPNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case zCompareAndSwapP_0_rule: {
      zCompareAndSwapP_0Node *node = new zCompareAndSwapP_0Node();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case zCompareAndSwapPAcq_rule: {
      zCompareAndSwapPAcqNode *node = new zCompareAndSwapPAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case zCompareAndSwapPAcq_0_rule: {
      zCompareAndSwapPAcq_0Node *node = new zCompareAndSwapPAcq_0Node();
      node->set_opnd_array(4, MachOperGenerator(IREGINOSP));
      return node;
    }
  case zCompareAndExchangeP_rule: {
      zCompareAndExchangePNode *node = new zCompareAndExchangePNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zCompareAndExchangePAcq_rule: {
      zCompareAndExchangePAcqNode *node = new zCompareAndExchangePAcqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPNOSP));
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
  return NULL;
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
