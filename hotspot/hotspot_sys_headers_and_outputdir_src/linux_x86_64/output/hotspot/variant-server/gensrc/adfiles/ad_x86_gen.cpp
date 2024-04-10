#line 1 "ad_x86_gen.cpp"
//
// Copyright (c) 2003, 2024, Oracle and/or its affiliates. All rights reserved.
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
#include "adfiles/ad_x86.hpp"
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
  case IMMI_0:
    return new immI_0Oper(_leaf->get_int() );
  case IMMI_1:
    return new immI_1Oper(_leaf->get_int() );
  case IMMI_M1:
    return new immI_M1Oper(_leaf->get_int() );
  case IMMI_2:
    return new immI_2Oper(_leaf->get_int() );
  case IMMI_4:
    return new immI_4Oper(_leaf->get_int() );
  case IMMI_8:
    return new immI_8Oper(_leaf->get_int() );
  case IMMI2:
    return new immI2Oper(_leaf->get_int() );
  case IMMU7:
    return new immU7Oper(_leaf->get_int() );
  case IMMI8:
    return new immI8Oper(_leaf->get_int() );
  case IMMU8:
    return new immU8Oper(_leaf->get_int() );
  case IMMI16:
    return new immI16Oper(_leaf->get_int() );
  case IMMU31:
    return new immU31Oper(_leaf->get_int() );
  case IMMP:
    return new immPOper(_leaf->bottom_type()->is_ptr() );
  case IMMP0:
    return new immP0Oper(_leaf->bottom_type()->is_ptr() );
  case IMMN:
    return new immNOper(_leaf->bottom_type()->is_narrowoop() );
  case IMMNKLASS:
    return new immNKlassOper(_leaf->bottom_type()->is_narrowklass() );
  case IMMN0:
    return new immN0Oper(_leaf->bottom_type()->is_narrowoop() );
  case IMMP31:
    return new immP31Oper(_leaf->bottom_type()->is_ptr() );
  case IMML:
    return new immLOper(_leaf->get_long() );
  case IMML8:
    return new immL8Oper(_leaf->get_long() );
  case IMMUL32:
    return new immUL32Oper(_leaf->get_long() );
  case IMML32:
    return new immL32Oper(_leaf->get_long() );
  case IMML_POW2:
    return new immL_Pow2Oper(_leaf->get_long() );
  case IMML_NOTPOW2:
    return new immL_NotPow2Oper(_leaf->get_long() );
  case IMML0:
    return new immL0Oper(_leaf->get_long() );
  case IMML1:
    return new immL1Oper(_leaf->get_long() );
  case IMML_M1:
    return new immL_M1Oper(_leaf->get_long() );
  case IMML_32BITS:
    return new immL_32bitsOper(_leaf->get_long() );
  case IMMI_POW2M1:
    return new immI_Pow2M1Oper(_leaf->get_int() );
  case IMMF0:
    return new immF0Oper(_leaf->getf() );
  case IMMF:
    return new immFOper(_leaf->getf() );
  case IMMD0:
    return new immD0Oper(_leaf->getd() );
  case IMMD:
    return new immDOper(_leaf->getd() );
  case IMMI_16:
    return new immI_16Oper(_leaf->get_int() );
  case IMMI_24:
    return new immI_24Oper(_leaf->get_int() );
  case IMMI_255:
    return new immI_255Oper(_leaf->get_int() );
  case IMMI_65535:
    return new immI_65535Oper(_leaf->get_int() );
  case IMML_255:
    return new immL_255Oper(_leaf->get_long() );
  case IMML_65535:
    return new immL_65535Oper(_leaf->get_long() );
  case KREG:
    return new kRegOper( );
  case RREGI:
    return new rRegIOper( );
  case RAX_REGI:
    return new rax_RegIOper( );
  case RBX_REGI:
    return new rbx_RegIOper( );
  case RCX_REGI:
    return new rcx_RegIOper( );
  case RDX_REGI:
    return new rdx_RegIOper( );
  case RDI_REGI:
    return new rdi_RegIOper( );
  case NO_RAX_RDX_REGI:
    return new no_rax_rdx_RegIOper( );
  case NO_RBP_R13_REGI:
    return new no_rbp_r13_RegIOper( );
  case ANY_REGP:
    return new any_RegPOper( );
  case RREGP:
    return new rRegPOper( );
  case RREGN:
    return new rRegNOper( );
  case NO_RBP_REGP:
    return new no_rbp_RegPOper( );
  case RAX_REGP:
    return new rax_RegPOper( );
  case RAX_REGN:
    return new rax_RegNOper( );
  case RBX_REGP:
    return new rbx_RegPOper( );
  case RSI_REGP:
    return new rsi_RegPOper( );
  case RBP_REGP:
    return new rbp_RegPOper( );
  case RDI_REGP:
    return new rdi_RegPOper( );
  case R15_REGP:
    return new r15_RegPOper( );
  case RREGL:
    return new rRegLOper( );
  case NO_RAX_RDX_REGL:
    return new no_rax_rdx_RegLOper( );
  case RAX_REGL:
    return new rax_RegLOper( );
  case RCX_REGL:
    return new rcx_RegLOper( );
  case RDX_REGL:
    return new rdx_RegLOper( );
  case NO_RBP_R13_REGL:
    return new no_rbp_r13_RegLOper( );
  case RFLAGSREG:
    return new rFlagsRegOper( );
  case RFLAGSREGU:
    return new rFlagsRegUOper( );
  case RFLAGSREGUCF:
    return new rFlagsRegUCFOper( );
  case REGF:
    return new regFOper( );
  case LEGREGF:
    return new legRegFOper( );
  case VLREGF:
    return new vlRegFOper( );
  case REGD:
    return new regDOper( );
  case LEGREGD:
    return new legRegDOper( );
  case VLREGD:
    return new vlRegDOper( );
  case INDIRECT:
    return new indirectOper( );
  case INDOFFSET8:
    return new indOffset8Oper(_kids[1]->_leaf->get_long() );
  case INDOFFSET32:
    return new indOffset32Oper(_kids[1]->_leaf->get_long() );
  case INDINDEXOFFSET:
    return new indIndexOffsetOper(_kids[1]->_leaf->get_long() );
  case INDINDEX:
    return new indIndexOper( );
  case INDINDEXSCALE:
    return new indIndexScaleOper(_kids[1]->_kids[1]->_leaf->get_int() );
  case INDPOSINDEXSCALE:
    return new indPosIndexScaleOper(_kids[1]->_kids[1]->_leaf->get_int() );
  case INDINDEXSCALEOFFSET:
    return new indIndexScaleOffsetOper(_kids[0]->_kids[1]->_kids[1]->_leaf->get_int(), _kids[1]->_leaf->get_long() );
  case INDPOSINDEXOFFSET:
    return new indPosIndexOffsetOper(_kids[1]->_leaf->get_long() );
  case INDPOSINDEXSCALEOFFSET:
    return new indPosIndexScaleOffsetOper(_kids[0]->_kids[1]->_kids[1]->_leaf->get_int(), _kids[1]->_leaf->get_long() );
  case INDCOMPRESSEDOOPOFFSET:
    return new indCompressedOopOffsetOper(_kids[1]->_leaf->get_long() );
  case INDIRECTNARROW:
    return new indirectNarrowOper( );
  case INDOFFSET8NARROW:
    return new indOffset8NarrowOper(_kids[1]->_leaf->get_long() );
  case INDOFFSET32NARROW:
    return new indOffset32NarrowOper(_kids[1]->_leaf->get_long() );
  case INDINDEXOFFSETNARROW:
    return new indIndexOffsetNarrowOper(_kids[1]->_leaf->get_long() );
  case INDINDEXNARROW:
    return new indIndexNarrowOper( );
  case INDINDEXSCALENARROW:
    return new indIndexScaleNarrowOper(_kids[1]->_kids[1]->_leaf->get_int() );
  case INDINDEXSCALEOFFSETNARROW:
    return new indIndexScaleOffsetNarrowOper(_kids[0]->_kids[1]->_kids[1]->_leaf->get_int(), _kids[1]->_leaf->get_long() );
  case INDPOSINDEXOFFSETNARROW:
    return new indPosIndexOffsetNarrowOper(_kids[1]->_leaf->get_long() );
  case INDPOSINDEXSCALEOFFSETNARROW:
    return new indPosIndexScaleOffsetNarrowOper(_kids[0]->_kids[1]->_kids[1]->_leaf->get_int(), _kids[1]->_leaf->get_long() );
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
  case CMPOPUCF:
    return new cmpOpUCFOper(_leaf->as_Bool()->_test._test );
  case CMPOPUCF2:
    return new cmpOpUCF2Oper(_leaf->as_Bool()->_test._test );
  case RXMM0:
    return new rxmm0Oper( );
  case VEC:
    return new vecOper( );
  case LEGVEC:
    return new legVecOper( );
  case VECS:
    return new vecSOper( );
  case LEGVECS:
    return new legVecSOper( );
  case VECD:
    return new vecDOper( );
  case LEGVECD:
    return new legVecDOper( );
  case VECX:
    return new vecXOper( );
  case LEGVECX:
    return new legVecXOper( );
  case VECY:
    return new vecYOper( );
  case LEGVECY:
    return new legVecYOper( );
  case VECZ:
    return new vecZOper( );
  case LEGVECZ:
    return new legVecZOper( );
  case NO_RAX_REGP:
    return new no_rax_RegPOper( );
  case _ADDP_ANY_REGP_RREGL:    return nullptr;
  case _LSHIFTL_RREGL_IMMI2:    return nullptr;
  case _CONVI2L_RREGI_:    return nullptr;
  case _LSHIFTL__CONVI2L_RREGI__IMMI2:    return nullptr;
  case _ADDP_ANY_REGP__LSHIFTL_RREGL_IMMI2:    return nullptr;
  case _ADDP_ANY_REGP__CONVI2L_RREGI_:    return nullptr;
  case _ADDP_ANY_REGP__LSHIFTL__CONVI2L_RREGI__IMMI2:    return nullptr;
  case _DECODEN_RREGN_:    return nullptr;
  case _ADDP__DECODEN_RREGN__RREGL:    return nullptr;
  case _ADDP__DECODEN_RREGN___LSHIFTL_RREGL_IMMI2:    return nullptr;
  case _ADDP__DECODEN_RREGN___CONVI2L_RREGI_:    return nullptr;
  case _ADDP__DECODEN_RREGN___LSHIFTL__CONVI2L_RREGI__IMMI2:    return nullptr;
  case _LOADB_MEMORY_:    return nullptr;
  case _LOADUB_MEMORY_:    return nullptr;
  case _ANDI__LOADUB_MEMORY__IMMI:    return nullptr;
  case _LOADS_MEMORY_:    return nullptr;
  case _LSHIFTI__LOADS_MEMORY__IMMI_24:    return nullptr;
  case _LOADUS_MEMORY_:    return nullptr;
  case _LSHIFTI__LOADUS_MEMORY__IMMI_24:    return nullptr;
  case _ANDI__LOADUS_MEMORY__IMMI_255:    return nullptr;
  case _ANDI__LOADUS_MEMORY__IMMI:    return nullptr;
  case _LOADI_MEMORY_:    return nullptr;
  case _LSHIFTI__LOADI_MEMORY__IMMI_24:    return nullptr;
  case _LSHIFTI__LOADI_MEMORY__IMMI_16:    return nullptr;
  case _ANDI__LOADI_MEMORY__IMMI_255:    return nullptr;
  case _ANDI__LOADI_MEMORY__IMMI_65535:    return nullptr;
  case _ANDI__LOADI_MEMORY__IMMU31:    return nullptr;
  case _CONVI2L__LOADI_MEMORY__:    return nullptr;
  case _LOADL_MEMORY_:    return nullptr;
  case _CASTP2X_RREGP_:    return nullptr;
  case _CASTP2X__DECODEN_RREGN__:    return nullptr;
  case _ADDL__LSHIFTL_RREGL_IMMI2_IMML32:    return nullptr;
  case _BINARY_CMPOP_RFLAGSREG:    return nullptr;
  case _BINARY_IMMI_1_RREGI:    return nullptr;
  case _BINARY_RREGI_RREGI:    return nullptr;
  case _BINARY_CMPOPU_RFLAGSREGU:    return nullptr;
  case _BINARY_CMPOPUCF_RFLAGSREGUCF:    return nullptr;
  case _BINARY_CMPOPUCF2_RFLAGSREGUCF:    return nullptr;
  case _BINARY_RREGI__LOADI_MEMORY_:    return nullptr;
  case _BINARY_RREGN_RREGN:    return nullptr;
  case _BINARY_RREGP_RREGP:    return nullptr;
  case _BINARY_IMMI_1_RREGL:    return nullptr;
  case _BINARY_RREGL_RREGL:    return nullptr;
  case _BINARY_RREGL__LOADL_MEMORY_:    return nullptr;
  case _BINARY_REGF_REGF:    return nullptr;
  case _BINARY_REGD_REGD:    return nullptr;
  case _ADDI__LOADI_MEMORY__RREGI:    return nullptr;
  case _ADDI_RREGI__LOADI_MEMORY_:    return nullptr;
  case _ADDI__LOADI_MEMORY__IMMI:    return nullptr;
  case _ADDI__LOADI_MEMORY__IMMI_1:    return nullptr;
  case _ADDI__LOADI_MEMORY__IMMI_M1:    return nullptr;
  case _LSHIFTI_RREGI_IMMI2:    return nullptr;
  case _ADDI_RREGI_RREGI:    return nullptr;
  case _ADDI_RREGI__LSHIFTI_RREGI_IMMI2:    return nullptr;
  case _ADDI__LSHIFTI_RREGI_IMMI2_RREGI:    return nullptr;
  case _ADDL__LOADL_MEMORY__RREGL:    return nullptr;
  case _ADDL_RREGL__LOADL_MEMORY_:    return nullptr;
  case _ADDL__LOADL_MEMORY__IMML32:    return nullptr;
  case _ADDL__LOADL_MEMORY__IMML1:    return nullptr;
  case _ADDL__LOADL_MEMORY__IMML_M1:    return nullptr;
  case _ADDL_RREGL_RREGL:    return nullptr;
  case _ADDL_RREGL__LSHIFTL_RREGL_IMMI2:    return nullptr;
  case _ADDL__LSHIFTL_RREGL_IMMI2_RREGL:    return nullptr;
  case _BINARY_RAX_REGP_RREGP:    return nullptr;
  case _BINARY_RAX_REGL_RREGL:    return nullptr;
  case _BINARY_RAX_REGI_RREGI:    return nullptr;
  case _BINARY_RAX_REGN_RREGN:    return nullptr;
  case _SUBI__LOADI_MEMORY__RREGI:    return nullptr;
  case _SUBL__LOADL_MEMORY__RREGL:    return nullptr;
  case _SUBI_IMMI_0_RREGI:    return nullptr;
  case _SUBI_IMMI_0__LOADI_MEMORY_:    return nullptr;
  case _SUBL_IMML0__LOADL_MEMORY_:    return nullptr;
  case _LSHIFTI__LOADI_MEMORY__IMMI8:    return nullptr;
  case _LSHIFTI__LOADI_MEMORY__RCX_REGI:    return nullptr;
  case _RSHIFTI__LOADI_MEMORY__IMMI8:    return nullptr;
  case _RSHIFTI__LOADI_MEMORY__RCX_REGI:    return nullptr;
  case _URSHIFTI__LOADI_MEMORY__IMMI8:    return nullptr;
  case _URSHIFTI__LOADI_MEMORY__RCX_REGI:    return nullptr;
  case _LSHIFTL__LOADL_MEMORY__IMMI8:    return nullptr;
  case _LSHIFTL__LOADL_MEMORY__RCX_REGI:    return nullptr;
  case _RSHIFTL__LOADL_MEMORY__IMMI:    return nullptr;
  case _RSHIFTL__LOADL_MEMORY__RCX_REGI:    return nullptr;
  case _URSHIFTL__LOADL_MEMORY__IMMI8:    return nullptr;
  case _URSHIFTL__LOADL_MEMORY__RCX_REGI:    return nullptr;
  case _LSHIFTI_RREGI_IMMI_24:    return nullptr;
  case _LSHIFTI_RREGI_IMMI_16:    return nullptr;
  case _ANDI_RREGI_IMMI_255:    return nullptr;
  case _ANDI_RREGI_IMMI_65535:    return nullptr;
  case _ANDI_RREGI_IMMI_POW2M1:    return nullptr;
  case _ANDI__LOADB_MEMORY__RREGI:    return nullptr;
  case _ANDI_RREGI__LOADB_MEMORY_:    return nullptr;
  case _ANDI__LOADI_MEMORY__RREGI:    return nullptr;
  case _ANDI_RREGI__LOADI_MEMORY_:    return nullptr;
  case _ANDI__LOADI_MEMORY__IMMI:    return nullptr;
  case _XORI_RREGI_IMMI_M1:    return nullptr;
  case _ADDI_RREGI_IMMI_M1:    return nullptr;
  case _ORI__LOADB_MEMORY__RREGI:    return nullptr;
  case _ORI_RREGI__LOADB_MEMORY_:    return nullptr;
  case _ORI__LOADI_MEMORY__RREGI:    return nullptr;
  case _ORI_RREGI__LOADI_MEMORY_:    return nullptr;
  case _ORI__LOADI_MEMORY__IMMI:    return nullptr;
  case _XORI__LOADB_MEMORY__RREGI:    return nullptr;
  case _XORI_RREGI__LOADB_MEMORY_:    return nullptr;
  case _XORI__LOADI_MEMORY__RREGI:    return nullptr;
  case _XORI_RREGI__LOADI_MEMORY_:    return nullptr;
  case _XORI__LOADI_MEMORY__IMMI:    return nullptr;
  case _ANDL__LOADL_MEMORY__RREGL:    return nullptr;
  case _ANDL_RREGL__LOADL_MEMORY_:    return nullptr;
  case _ANDL__LOADL_MEMORY__IMML32:    return nullptr;
  case _ANDL__LOADL_MEMORY__IMML_NOTPOW2:    return nullptr;
  case _XORL_RREGL_IMML_M1:    return nullptr;
  case _SUBL_IMML0_RREGL:    return nullptr;
  case _ADDL_RREGL_IMML_M1:    return nullptr;
  case _CASTP2X_ANY_REGP_:    return nullptr;
  case _ORL__LOADL_MEMORY__RREGL:    return nullptr;
  case _ORL_RREGL__LOADL_MEMORY_:    return nullptr;
  case _ORL__LOADL_MEMORY__IMML32:    return nullptr;
  case _ORL__LOADL_MEMORY__IMML_POW2:    return nullptr;
  case _XORL__LOADL_MEMORY__RREGL:    return nullptr;
  case _XORL_RREGL__LOADL_MEMORY_:    return nullptr;
  case _XORL__LOADL_MEMORY__IMML32:    return nullptr;
  case _CMPLTMASK_RREGI_RREGI:    return nullptr;
  case _ANDI__CMPLTMASK_RREGI_RREGI_RREGI:    return nullptr;
  case _SUBI_RREGI_RREGI:    return nullptr;
  case _ANDI_RREGI__CMPLTMASK_RREGI_RREGI:    return nullptr;
  case _LOADF_MEMORY_:    return nullptr;
  case _LOADD_MEMORY_:    return nullptr;
  case _BINARY_RDI_REGP_RCX_REGI:    return nullptr;
  case _BINARY_RSI_REGP_RDX_REGI:    return nullptr;
  case _BINARY_RDI_REGP_RDX_REGI:    return nullptr;
  case _BINARY_RSI_REGP_IMMI:    return nullptr;
  case _BINARY_RSI_REGP_RAX_REGI:    return nullptr;
  case _BINARY_RDI_REGP_RSI_REGP:    return nullptr;
  case _BINARY_RBX_REGI_IMMU8:    return nullptr;
  case _ANDI_RREGI_IMMI:    return nullptr;
  case _ANDI_RREGI_RREGI:    return nullptr;
  case _LOADP_MEMORY_:    return nullptr;
  case _LOADN_MEMORY_:    return nullptr;
  case _LOADNKLASS_MEMORY_:    return nullptr;
  case _ANDL_RREGL_IMML32:    return nullptr;
  case _ANDL_RREGL_RREGL:    return nullptr;
  case _ANDL__CASTP2X_RREGP___LOADL_MEMORY_:    return nullptr;
  case _ANDL__LOADL_MEMORY___CASTP2X_RREGP_:    return nullptr;
  case _ANDI__LOADUB_MEMORY__IMMU7:    return nullptr;
  case _ANDI__LOADB_MEMORY__IMMI8:    return nullptr;
  case _PARTIALSUBTYPECHECK_RSI_REGP_RAX_REGP:    return nullptr;
  case _CONVF2HF_REGF_:    return nullptr;
  case _VECTORCASTF2HF_VEC_:    return nullptr;
  case _LOADVECTOR_MEMORY_:    return nullptr;
  case _BINARY_VEC_KREG:    return nullptr;
  case _BINARY_VEC_VEC:    return nullptr;
  case _BINARY_VEC__BINARY_VEC_KREG:    return nullptr;
  case _BINARY_VEC_RREGI:    return nullptr;
  case _BINARY_VEC_RREGL:    return nullptr;
  case _BINARY_VEC_REGF:    return nullptr;
  case _BINARY_VEC_REGD:    return nullptr;
  case _BINARY_REGD_IMMD:    return nullptr;
  case _LSHIFTCNTV_IMMI8_:    return nullptr;
  case _RSHIFTCNTV_IMMI8_:    return nullptr;
  case _BINARY_LEGVEC_LEGVEC:    return nullptr;
  case _BINARY_VEC__LOADVECTOR_MEMORY_:    return nullptr;
  case _MULADDVS2VI_VEC_VEC:    return nullptr;
  case _BINARY_VEC_IMMU8:    return nullptr;
  case _BINARY__LOADVECTOR_MEMORY__IMMU8:    return nullptr;
  case _VECTORSTOREMASK_VEC_IMMI:    return nullptr;
  case _BINARY_VEC_IMMI8:    return nullptr;
  case _BINARY_VEC__LSHIFTCNTV_IMMI8_:    return nullptr;
  case _BINARY_VEC__RSHIFTCNTV_IMMI8_:    return nullptr;
  case _BINARY__LOADVECTOR_MEMORY__KREG:    return nullptr;
  case _BINARY_IMMI8_KREG:    return nullptr;
  case _MASKALL_IMMI_M1_:    return nullptr;
  case _BINARY_IMMU8_KREG:    return nullptr;
  case _BINARY_VEC__BINARY_IMMU8_KREG:    return nullptr;
  case _BINARY_VEC__BINARY_VEC__BINARY_IMMU8_KREG:    return nullptr;
  case _BINARY_MEMORY__BINARY_IMMU8_KREG:    return nullptr;
  case _BINARY_VEC__BINARY_MEMORY__BINARY_IMMU8_KREG:    return nullptr;
  case _BINARY_RAX_REGP_NO_RAX_REGP:    return nullptr;
  
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
  case MoveF2VL_rule: {
      MoveF2VLNode *node = new MoveF2VLNode();
      return node;
    }
  case MoveF2LEG_rule: {
      MoveF2LEGNode *node = new MoveF2LEGNode();
      return node;
    }
  case MoveVL2F_rule: {
      MoveVL2FNode *node = new MoveVL2FNode();
      return node;
    }
  case MoveLEG2F_rule: {
      MoveLEG2FNode *node = new MoveLEG2FNode();
      return node;
    }
  case MoveD2VL_rule: {
      MoveD2VLNode *node = new MoveD2VLNode();
      return node;
    }
  case MoveD2LEG_rule: {
      MoveD2LEGNode *node = new MoveD2LEGNode();
      return node;
    }
  case MoveVL2D_rule: {
      MoveVL2DNode *node = new MoveVL2DNode();
      return node;
    }
  case MoveLEG2D_rule: {
      MoveLEG2DNode *node = new MoveLEG2DNode();
      return node;
    }
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
  case loadUB2L_immI_rule: {
      loadUB2L_immINode *node = new loadUB2L_immINode();
      return node;
    }
  case loadS_rule: {
      loadSNode *node = new loadSNode();
      return node;
    }
  case loadS2B_rule: {
      loadS2BNode *node = new loadS2BNode();
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
  case loadUS2B_rule: {
      loadUS2BNode *node = new loadUS2BNode();
      return node;
    }
  case loadUS2L_rule: {
      loadUS2LNode *node = new loadUS2LNode();
      return node;
    }
  case loadUS2L_immI_255_rule: {
      loadUS2L_immI_255Node *node = new loadUS2L_immI_255Node();
      return node;
    }
  case loadUS2L_immI_rule: {
      loadUS2L_immINode *node = new loadUS2L_immINode();
      return node;
    }
  case loadI_rule: {
      loadINode *node = new loadINode();
      return node;
    }
  case loadI2B_rule: {
      loadI2BNode *node = new loadI2BNode();
      return node;
    }
  case loadI2UB_rule: {
      loadI2UBNode *node = new loadI2UBNode();
      return node;
    }
  case loadI2S_rule: {
      loadI2SNode *node = new loadI2SNode();
      return node;
    }
  case loadI2US_rule: {
      loadI2USNode *node = new loadI2USNode();
      return node;
    }
  case loadI2L_rule: {
      loadI2LNode *node = new loadI2LNode();
      return node;
    }
  case loadI2L_immI_255_rule: {
      loadI2L_immI_255Node *node = new loadI2L_immI_255Node();
      return node;
    }
  case loadI2L_immI_65535_rule: {
      loadI2L_immI_65535Node *node = new loadI2L_immI_65535Node();
      return node;
    }
  case loadI2L_immU31_rule: {
      loadI2L_immU31Node *node = new loadI2L_immU31Node();
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
  case loadD_partial_rule: {
      loadD_partialNode *node = new loadD_partialNode();
      return node;
    }
  case loadD_rule: {
      loadDNode *node = new loadDNode();
      return node;
    }
  case maxF_reg_rule: {
      maxF_regNode *node = new maxF_regNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGREGF));
      node->set_opnd_array(5, MachOperGenerator(LEGREGF));
      return node;
    }
  case maxF_reduction_reg_rule: {
      maxF_reduction_regNode *node = new maxF_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      return node;
    }
  case maxD_reg_rule: {
      maxD_regNode *node = new maxD_regNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case maxD_reduction_reg_rule: {
      maxD_reduction_regNode *node = new maxD_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      return node;
    }
  case minF_reg_rule: {
      minF_regNode *node = new minF_regNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGREGF));
      node->set_opnd_array(5, MachOperGenerator(LEGREGF));
      return node;
    }
  case minF_reduction_reg_rule: {
      minF_reduction_regNode *node = new minF_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      return node;
    }
  case minD_reg_rule: {
      minD_regNode *node = new minD_regNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case minD_reduction_reg_rule: {
      minD_reduction_regNode *node = new minD_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      return node;
    }
  case leaP8_rule: {
      leaP8Node *node = new leaP8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaP32_rule: {
      leaP32Node *node = new leaP32Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxOff_rule: {
      leaPIdxOffNode *node = new leaPIdxOffNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxScale_rule: {
      leaPIdxScaleNode *node = new leaPIdxScaleNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPPosIdxScale_rule: {
      leaPPosIdxScaleNode *node = new leaPPosIdxScaleNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxScaleOff_rule: {
      leaPIdxScaleOffNode *node = new leaPIdxScaleOffNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPPosIdxOff_rule: {
      leaPPosIdxOffNode *node = new leaPPosIdxOffNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPPosIdxScaleOff_rule: {
      leaPPosIdxScaleOffNode *node = new leaPPosIdxScaleOffNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPCompressedOopOffset_rule: {
      leaPCompressedOopOffsetNode *node = new leaPCompressedOopOffsetNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaP8Narrow_rule: {
      leaP8NarrowNode *node = new leaP8NarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaP32Narrow_rule: {
      leaP32NarrowNode *node = new leaP32NarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxOffNarrow_rule: {
      leaPIdxOffNarrowNode *node = new leaPIdxOffNarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxScaleNarrow_rule: {
      leaPIdxScaleNarrowNode *node = new leaPIdxScaleNarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxScaleOffNarrow_rule: {
      leaPIdxScaleOffNarrowNode *node = new leaPIdxScaleOffNarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPPosIdxOffNarrow_rule: {
      leaPPosIdxOffNarrowNode *node = new leaPPosIdxOffNarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPPosIdxScaleOffNarrow_rule: {
      leaPPosIdxScaleOffNarrowNode *node = new leaPPosIdxScaleOffNarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConI_rule: {
      loadConINode *node = new loadConINode();
      node->_opnd_array[1] = new immIOper(_leaf->get_int() );
      return node;
    }
  case loadConI0_rule: {
      loadConI0Node *node = new loadConI0Node();
      return node;
    }
  case loadConL_rule: {
      loadConLNode *node = new loadConLNode();
      node->_opnd_array[1] = new immLOper(_leaf->get_long() );
      return node;
    }
  case loadConL0_rule: {
      loadConL0Node *node = new loadConL0Node();
      return node;
    }
  case loadConUL32_rule: {
      loadConUL32Node *node = new loadConUL32Node();
      node->_opnd_array[1] = new immUL32Oper(_leaf->get_long() );
      return node;
    }
  case loadConL32_rule: {
      loadConL32Node *node = new loadConL32Node();
      node->_opnd_array[1] = new immL32Oper(_leaf->get_long() );
      return node;
    }
  case loadConP_rule: {
      loadConPNode *node = new loadConPNode();
      node->_opnd_array[1] = new immPOper(_leaf->bottom_type()->is_ptr() );
      return node;
    }
  case loadConP0_rule: {
      loadConP0Node *node = new loadConP0Node();
      return node;
    }
  case loadConP31_rule: {
      loadConP31Node *node = new loadConP31Node();
      return node;
    }
  case loadConF_rule: {
      loadConFNode *node = new loadConFNode();
      node->_opnd_array[1] = new immFOper(_leaf->getf() );
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConN0_rule: {
      loadConN0Node *node = new loadConN0Node();
      return node;
    }
  case loadConN_rule: {
      loadConNNode *node = new loadConNNode();
      node->_opnd_array[1] = new immNOper(_leaf->bottom_type()->is_narrowoop() );
      return node;
    }
  case loadConNKlass_rule: {
      loadConNKlassNode *node = new loadConNKlassNode();
      node->_opnd_array[1] = new immNKlassOper(_leaf->bottom_type()->is_narrowklass() );
      return node;
    }
  case loadConF0_rule: {
      loadConF0Node *node = new loadConF0Node();
      node->_opnd_array[1] = new immF0Oper(_leaf->getf() );
      return node;
    }
  case loadConD_rule: {
      loadConDNode *node = new loadConDNode();
      node->_opnd_array[1] = new immDOper(_leaf->getd() );
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConD0_rule: {
      loadConD0Node *node = new loadConD0Node();
      node->_opnd_array[1] = new immD0Oper(_leaf->getd() );
      return node;
    }
  case loadSSI_rule: {
      loadSSINode *node = new loadSSINode();
      return node;
    }
  case loadSSL_rule: {
      loadSSLNode *node = new loadSSLNode();
      return node;
    }
  case loadSSP_rule: {
      loadSSPNode *node = new loadSSPNode();
      return node;
    }
  case loadSSF_rule: {
      loadSSFNode *node = new loadSSFNode();
      return node;
    }
  case loadSSD_rule: {
      loadSSDNode *node = new loadSSDNode();
      return node;
    }
  case prefetchAlloc_rule: {
      prefetchAllocNode *node = new prefetchAllocNode();
      return node;
    }
  case prefetchAllocNTA_rule: {
      prefetchAllocNTANode *node = new prefetchAllocNTANode();
      return node;
    }
  case prefetchAllocT0_rule: {
      prefetchAllocT0Node *node = new prefetchAllocT0Node();
      return node;
    }
  case prefetchAllocT2_rule: {
      prefetchAllocT2Node *node = new prefetchAllocT2Node();
      return node;
    }
  case storeB_rule: {
      storeBNode *node = new storeBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeC_rule: {
      storeCNode *node = new storeCNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeI_rule: {
      storeINode *node = new storeINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeL_rule: {
      storeLNode *node = new storeLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeP_rule: {
      storePNode *node = new storePNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmP0_rule: {
      storeImmP0Node *node = new storeImmP0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmP_rule: {
      storeImmPNode *node = new storeImmPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeN_rule: {
      storeNNode *node = new storeNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeNKlass_rule: {
      storeNKlassNode *node = new storeNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmN0_rule: {
      storeImmN0Node *node = new storeImmN0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmN_rule: {
      storeImmNNode *node = new storeImmNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmNKlass_rule: {
      storeImmNKlassNode *node = new storeImmNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmI0_rule: {
      storeImmI0Node *node = new storeImmI0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmI_rule: {
      storeImmINode *node = new storeImmINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmL0_rule: {
      storeImmL0Node *node = new storeImmL0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmL_rule: {
      storeImmLNode *node = new storeImmLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmC0_rule: {
      storeImmC0Node *node = new storeImmC0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmI16_rule: {
      storeImmI16Node *node = new storeImmI16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmB0_rule: {
      storeImmB0Node *node = new storeImmB0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmB_rule: {
      storeImmBNode *node = new storeImmBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmCM0_reg_rule: {
      storeImmCM0_regNode *node = new storeImmCM0_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmCM0_rule: {
      storeImmCM0Node *node = new storeImmCM0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeF_rule: {
      storeFNode *node = new storeFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeF0_rule: {
      storeF0Node *node = new storeF0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeF_imm_rule: {
      storeF_immNode *node = new storeF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeD_rule: {
      storeDNode *node = new storeDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeD0_imm_rule: {
      storeD0_immNode *node = new storeD0_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeD0_rule: {
      storeD0Node *node = new storeD0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeSSI_rule: {
      storeSSINode *node = new storeSSINode();
      return node;
    }
  case storeSSL_rule: {
      storeSSLNode *node = new storeSSLNode();
      return node;
    }
  case storeSSP_rule: {
      storeSSPNode *node = new storeSSPNode();
      return node;
    }
  case storeSSF_rule: {
      storeSSFNode *node = new storeSSFNode();
      return node;
    }
  case storeSSD_rule: {
      storeSSDNode *node = new storeSSDNode();
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
  case countLeadingZerosI_mem_rule: {
      countLeadingZerosI_memNode *node = new countLeadingZerosI_memNode();
      return node;
    }
  case countLeadingZerosI_bsr_rule: {
      countLeadingZerosI_bsrNode *node = new countLeadingZerosI_bsrNode();
      return node;
    }
  case countLeadingZerosL_rule: {
      countLeadingZerosLNode *node = new countLeadingZerosLNode();
      return node;
    }
  case countLeadingZerosL_mem_rule: {
      countLeadingZerosL_memNode *node = new countLeadingZerosL_memNode();
      return node;
    }
  case countLeadingZerosL_bsr_rule: {
      countLeadingZerosL_bsrNode *node = new countLeadingZerosL_bsrNode();
      return node;
    }
  case countTrailingZerosI_rule: {
      countTrailingZerosINode *node = new countTrailingZerosINode();
      return node;
    }
  case countTrailingZerosI_mem_rule: {
      countTrailingZerosI_memNode *node = new countTrailingZerosI_memNode();
      return node;
    }
  case countTrailingZerosI_bsf_rule: {
      countTrailingZerosI_bsfNode *node = new countTrailingZerosI_bsfNode();
      return node;
    }
  case countTrailingZerosL_rule: {
      countTrailingZerosLNode *node = new countTrailingZerosLNode();
      return node;
    }
  case countTrailingZerosL_mem_rule: {
      countTrailingZerosL_memNode *node = new countTrailingZerosL_memNode();
      return node;
    }
  case countTrailingZerosL_bsf_rule: {
      countTrailingZerosL_bsfNode *node = new countTrailingZerosL_bsfNode();
      return node;
    }
  case bytes_reversebit_int_rule: {
      bytes_reversebit_intNode *node = new bytes_reversebit_intNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      return node;
    }
  case bytes_reversebit_int_gfni_rule: {
      bytes_reversebit_int_gfniNode *node = new bytes_reversebit_int_gfniNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->set_opnd_array(5, MachOperGenerator(RREGL));
      return node;
    }
  case bytes_reversebit_long_rule: {
      bytes_reversebit_longNode *node = new bytes_reversebit_longNode();
      node->set_opnd_array(2, MachOperGenerator(RREGL));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      return node;
    }
  case bytes_reversebit_long_gfni_rule: {
      bytes_reversebit_long_gfniNode *node = new bytes_reversebit_long_gfniNode();
      node->set_opnd_array(2, MachOperGenerator(RREGL));
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(RREGL));
      return node;
    }
  case popCountI_rule: {
      popCountINode *node = new popCountINode();
      return node;
    }
  case popCountI_mem_rule: {
      popCountI_memNode *node = new popCountI_memNode();
      return node;
    }
  case popCountL_rule: {
      popCountLNode *node = new popCountLNode();
      return node;
    }
  case popCountL_mem_rule: {
      popCountL_memNode *node = new popCountL_memNode();
      return node;
    }
  case membar_acquire_rule: {
      membar_acquireNode *node = new membar_acquireNode();
      return node;
    }
  case membar_acquire_0_rule: {
      membar_acquire_0Node *node = new membar_acquire_0Node();
      return node;
    }
  case membar_acquire_lock_rule: {
      membar_acquire_lockNode *node = new membar_acquire_lockNode();
      return node;
    }
  case membar_release_rule: {
      membar_releaseNode *node = new membar_releaseNode();
      return node;
    }
  case membar_release_0_rule: {
      membar_release_0Node *node = new membar_release_0Node();
      return node;
    }
  case membar_release_lock_rule: {
      membar_release_lockNode *node = new membar_release_lockNode();
      return node;
    }
  case membar_volatile_rule: {
      membar_volatileNode *node = new membar_volatileNode();
      node->set_opnd_array(1, MachOperGenerator(RFLAGSREG));
      return node;
    }
  case unnecessary_membar_volatile_rule: {
      unnecessary_membar_volatileNode *node = new unnecessary_membar_volatileNode();
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
      node->set_opnd_array(2, MachOperGenerator(RREGN));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeKlass_not_null_rule: {
      decodeKlass_not_nullNode *node = new decodeKlass_not_nullNode();
      node->set_opnd_array(2, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case jumpXtnd_offset_rule: {
      jumpXtnd_offsetNode *node = new jumpXtnd_offsetNode();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      node->_probs = _leaf->as_Jump()->_probs;
      return node;
    }
  case jumpXtnd_addr_rule: {
      jumpXtnd_addrNode *node = new jumpXtnd_addrNode();
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      node->_probs = _leaf->as_Jump()->_probs;
      return node;
    }
  case jumpXtnd_rule: {
      jumpXtndNode *node = new jumpXtndNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      node->_probs = _leaf->as_Jump()->_probs;
      return node;
    }
  case cmovI_imm_01_rule: {
      cmovI_imm_01Node *node = new cmovI_imm_01Node();
      return node;
    }
  case cmovI_reg_rule: {
      cmovI_regNode *node = new cmovI_regNode();
      return node;
    }
  case cmovI_imm_01U_rule: {
      cmovI_imm_01UNode *node = new cmovI_imm_01UNode();
      return node;
    }
  case cmovI_regU_rule: {
      cmovI_regUNode *node = new cmovI_regUNode();
      return node;
    }
  case cmovI_imm_01UCF_rule: {
      cmovI_imm_01UCFNode *node = new cmovI_imm_01UCFNode();
      return node;
    }
  case cmovI_regUCF_rule: {
      cmovI_regUCFNode *node = new cmovI_regUCFNode();
      return node;
    }
  case cmovI_regUCF2_ne_rule: {
      cmovI_regUCF2_neNode *node = new cmovI_regUCF2_neNode();
      return node;
    }
  case cmovI_regUCF2_eq_rule: {
      cmovI_regUCF2_eqNode *node = new cmovI_regUCF2_eqNode();
      return node;
    }
  case cmovI_mem_rule: {
      cmovI_memNode *node = new cmovI_memNode();
      return node;
    }
  case cmovI_memU_rule: {
      cmovI_memUNode *node = new cmovI_memUNode();
      return node;
    }
  case cmovI_memUCF_rule: {
      cmovI_memUCFNode *node = new cmovI_memUCFNode();
      return node;
    }
  case cmovN_reg_rule: {
      cmovN_regNode *node = new cmovN_regNode();
      return node;
    }
  case cmovN_regU_rule: {
      cmovN_regUNode *node = new cmovN_regUNode();
      return node;
    }
  case cmovN_regUCF_rule: {
      cmovN_regUCFNode *node = new cmovN_regUCFNode();
      return node;
    }
  case cmovN_regUCF2_ne_rule: {
      cmovN_regUCF2_neNode *node = new cmovN_regUCF2_neNode();
      return node;
    }
  case cmovN_regUCF2_eq_rule: {
      cmovN_regUCF2_eqNode *node = new cmovN_regUCF2_eqNode();
      return node;
    }
  case cmovP_reg_rule: {
      cmovP_regNode *node = new cmovP_regNode();
      return node;
    }
  case cmovP_regU_rule: {
      cmovP_regUNode *node = new cmovP_regUNode();
      return node;
    }
  case cmovP_regUCF_rule: {
      cmovP_regUCFNode *node = new cmovP_regUCFNode();
      return node;
    }
  case cmovP_regUCF2_ne_rule: {
      cmovP_regUCF2_neNode *node = new cmovP_regUCF2_neNode();
      return node;
    }
  case cmovP_regUCF2_eq_rule: {
      cmovP_regUCF2_eqNode *node = new cmovP_regUCF2_eqNode();
      return node;
    }
  case cmovL_imm_01_rule: {
      cmovL_imm_01Node *node = new cmovL_imm_01Node();
      return node;
    }
  case cmovL_reg_rule: {
      cmovL_regNode *node = new cmovL_regNode();
      return node;
    }
  case cmovL_mem_rule: {
      cmovL_memNode *node = new cmovL_memNode();
      return node;
    }
  case cmovL_imm_01U_rule: {
      cmovL_imm_01UNode *node = new cmovL_imm_01UNode();
      return node;
    }
  case cmovL_regU_rule: {
      cmovL_regUNode *node = new cmovL_regUNode();
      return node;
    }
  case cmovL_imm_01UCF_rule: {
      cmovL_imm_01UCFNode *node = new cmovL_imm_01UCFNode();
      return node;
    }
  case cmovL_regUCF_rule: {
      cmovL_regUCFNode *node = new cmovL_regUCFNode();
      return node;
    }
  case cmovL_regUCF2_ne_rule: {
      cmovL_regUCF2_neNode *node = new cmovL_regUCF2_neNode();
      return node;
    }
  case cmovL_regUCF2_eq_rule: {
      cmovL_regUCF2_eqNode *node = new cmovL_regUCF2_eqNode();
      return node;
    }
  case cmovL_memU_rule: {
      cmovL_memUNode *node = new cmovL_memUNode();
      return node;
    }
  case cmovL_memUCF_rule: {
      cmovL_memUCFNode *node = new cmovL_memUCFNode();
      return node;
    }
  case cmovF_reg_rule: {
      cmovF_regNode *node = new cmovF_regNode();
      return node;
    }
  case cmovF_regU_rule: {
      cmovF_regUNode *node = new cmovF_regUNode();
      return node;
    }
  case cmovF_regUCF_rule: {
      cmovF_regUCFNode *node = new cmovF_regUCFNode();
      return node;
    }
  case cmovD_reg_rule: {
      cmovD_regNode *node = new cmovD_regNode();
      return node;
    }
  case cmovD_regU_rule: {
      cmovD_regUNode *node = new cmovD_regUNode();
      return node;
    }
  case cmovD_regUCF_rule: {
      cmovD_regUCFNode *node = new cmovD_regUCFNode();
      return node;
    }
  case addI_rReg_rule: {
      addI_rRegNode *node = new addI_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case addI_rReg_imm_rule: {
      addI_rReg_immNode *node = new addI_rReg_immNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case addI_rReg_mem_rule: {
      addI_rReg_memNode *node = new addI_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case addI_rReg_mem_0_rule: {
      addI_rReg_mem_0Node *node = new addI_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case addI_mem_rReg_rule: {
      addI_mem_rRegNode *node = new addI_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addI_mem_rReg_0_rule: {
      addI_mem_rReg_0Node *node = new addI_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addI_mem_imm_rule: {
      addI_mem_immNode *node = new addI_mem_immNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case incI_rReg_rule: {
      incI_rRegNode *node = new incI_rRegNode();
      return node;
    }
  case incI_mem_rule: {
      incI_memNode *node = new incI_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decI_rReg_rule: {
      decI_rRegNode *node = new decI_rRegNode();
      return node;
    }
  case decI_mem_rule: {
      decI_memNode *node = new decI_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaI_rReg_immI2_immI_rule: {
      leaI_rReg_immI2_immINode *node = new leaI_rReg_immI2_immINode();
      return node;
    }
  case leaI_rReg_rReg_immI_rule: {
      leaI_rReg_rReg_immINode *node = new leaI_rReg_rReg_immINode();
      return node;
    }
  case leaI_rReg_rReg_immI2_rule: {
      leaI_rReg_rReg_immI2Node *node = new leaI_rReg_rReg_immI2Node();
      return node;
    }
  case leaI_rReg_rReg_immI2_0_rule: {
      leaI_rReg_rReg_immI2_0Node *node = new leaI_rReg_rReg_immI2_0Node();
      return node;
    }
  case leaI_rReg_rReg_immI2_immI_rule: {
      leaI_rReg_rReg_immI2_immINode *node = new leaI_rReg_rReg_immI2_immINode();
      return node;
    }
  case leaI_rReg_rReg_immI2_immI_0_rule: {
      leaI_rReg_rReg_immI2_immI_0Node *node = new leaI_rReg_rReg_immI2_immI_0Node();
      return node;
    }
  case addL_rReg_rule: {
      addL_rRegNode *node = new addL_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case addL_rReg_imm_rule: {
      addL_rReg_immNode *node = new addL_rReg_immNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case addL_rReg_mem_rule: {
      addL_rReg_memNode *node = new addL_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case addL_rReg_mem_0_rule: {
      addL_rReg_mem_0Node *node = new addL_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case addL_mem_rReg_rule: {
      addL_mem_rRegNode *node = new addL_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addL_mem_rReg_0_rule: {
      addL_mem_rReg_0Node *node = new addL_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addL_mem_imm_rule: {
      addL_mem_immNode *node = new addL_mem_immNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case incL_rReg_rule: {
      incL_rRegNode *node = new incL_rRegNode();
      return node;
    }
  case incL_mem_rule: {
      incL_memNode *node = new incL_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decL_rReg_rule: {
      decL_rRegNode *node = new decL_rRegNode();
      return node;
    }
  case decL_mem_rule: {
      decL_memNode *node = new decL_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaL_rReg_immI2_immL32_rule: {
      leaL_rReg_immI2_immL32Node *node = new leaL_rReg_immI2_immL32Node();
      return node;
    }
  case leaL_rReg_rReg_immL32_rule: {
      leaL_rReg_rReg_immL32Node *node = new leaL_rReg_rReg_immL32Node();
      return node;
    }
  case leaL_rReg_rReg_immI2_rule: {
      leaL_rReg_rReg_immI2Node *node = new leaL_rReg_rReg_immI2Node();
      return node;
    }
  case leaL_rReg_rReg_immI2_0_rule: {
      leaL_rReg_rReg_immI2_0Node *node = new leaL_rReg_rReg_immI2_0Node();
      return node;
    }
  case leaL_rReg_rReg_immI2_immL32_rule: {
      leaL_rReg_rReg_immI2_immL32Node *node = new leaL_rReg_rReg_immI2_immL32Node();
      return node;
    }
  case leaL_rReg_rReg_immI2_immL32_0_rule: {
      leaL_rReg_rReg_immI2_immL32_0Node *node = new leaL_rReg_rReg_immI2_immL32_0Node();
      return node;
    }
  case addP_rReg_rule: {
      addP_rRegNode *node = new addP_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_rReg_imm_rule: {
      addP_rReg_immNode *node = new addP_rReg_immNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
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
  case compareAndSwapP_rule: {
      compareAndSwapPNode *node = new compareAndSwapPNode();
      return node;
    }
  case compareAndSwapP_0_rule: {
      compareAndSwapP_0Node *node = new compareAndSwapP_0Node();
      return node;
    }
  case compareAndSwapL_rule: {
      compareAndSwapLNode *node = new compareAndSwapLNode();
      return node;
    }
  case compareAndSwapL_0_rule: {
      compareAndSwapL_0Node *node = new compareAndSwapL_0Node();
      return node;
    }
  case compareAndSwapI_rule: {
      compareAndSwapINode *node = new compareAndSwapINode();
      return node;
    }
  case compareAndSwapI_0_rule: {
      compareAndSwapI_0Node *node = new compareAndSwapI_0Node();
      return node;
    }
  case compareAndSwapB_rule: {
      compareAndSwapBNode *node = new compareAndSwapBNode();
      return node;
    }
  case compareAndSwapB_0_rule: {
      compareAndSwapB_0Node *node = new compareAndSwapB_0Node();
      return node;
    }
  case compareAndSwapS_rule: {
      compareAndSwapSNode *node = new compareAndSwapSNode();
      return node;
    }
  case compareAndSwapS_0_rule: {
      compareAndSwapS_0Node *node = new compareAndSwapS_0Node();
      return node;
    }
  case compareAndSwapN_rule: {
      compareAndSwapNNode *node = new compareAndSwapNNode();
      return node;
    }
  case compareAndSwapN_0_rule: {
      compareAndSwapN_0Node *node = new compareAndSwapN_0Node();
      return node;
    }
  case compareAndExchangeB_rule: {
      compareAndExchangeBNode *node = new compareAndExchangeBNode();
      return node;
    }
  case compareAndExchangeS_rule: {
      compareAndExchangeSNode *node = new compareAndExchangeSNode();
      return node;
    }
  case compareAndExchangeI_rule: {
      compareAndExchangeINode *node = new compareAndExchangeINode();
      return node;
    }
  case compareAndExchangeL_rule: {
      compareAndExchangeLNode *node = new compareAndExchangeLNode();
      return node;
    }
  case compareAndExchangeN_rule: {
      compareAndExchangeNNode *node = new compareAndExchangeNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeP_rule: {
      compareAndExchangePNode *node = new compareAndExchangePNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xaddB_reg_no_res_rule: {
      xaddB_reg_no_resNode *node = new xaddB_reg_no_resNode();
      return node;
    }
  case xaddB_imm_no_res_rule: {
      xaddB_imm_no_resNode *node = new xaddB_imm_no_resNode();
      return node;
    }
  case xaddB_rule: {
      xaddBNode *node = new xaddBNode();
      return node;
    }
  case xaddS_reg_no_res_rule: {
      xaddS_reg_no_resNode *node = new xaddS_reg_no_resNode();
      return node;
    }
  case xaddS_imm_no_res_rule: {
      xaddS_imm_no_resNode *node = new xaddS_imm_no_resNode();
      return node;
    }
  case xaddS_rule: {
      xaddSNode *node = new xaddSNode();
      return node;
    }
  case xaddI_reg_no_res_rule: {
      xaddI_reg_no_resNode *node = new xaddI_reg_no_resNode();
      return node;
    }
  case xaddI_imm_no_res_rule: {
      xaddI_imm_no_resNode *node = new xaddI_imm_no_resNode();
      return node;
    }
  case xaddI_rule: {
      xaddINode *node = new xaddINode();
      return node;
    }
  case xaddL_reg_no_res_rule: {
      xaddL_reg_no_resNode *node = new xaddL_reg_no_resNode();
      return node;
    }
  case xaddL_imm_no_res_rule: {
      xaddL_imm_no_resNode *node = new xaddL_imm_no_resNode();
      return node;
    }
  case xaddL_rule: {
      xaddLNode *node = new xaddLNode();
      return node;
    }
  case xchgB_rule: {
      xchgBNode *node = new xchgBNode();
      return node;
    }
  case xchgS_rule: {
      xchgSNode *node = new xchgSNode();
      return node;
    }
  case xchgI_rule: {
      xchgINode *node = new xchgINode();
      return node;
    }
  case xchgL_rule: {
      xchgLNode *node = new xchgLNode();
      return node;
    }
  case xchgP_rule: {
      xchgPNode *node = new xchgPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xchgN_rule: {
      xchgNNode *node = new xchgNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case absI_rReg_rule: {
      absI_rRegNode *node = new absI_rRegNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      return node;
    }
  case absL_rReg_rule: {
      absL_rRegNode *node = new absL_rRegNode();
      node->set_opnd_array(2, MachOperGenerator(RREGL));
      return node;
    }
  case subI_rReg_rule: {
      subI_rRegNode *node = new subI_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case subI_rReg_mem_rule: {
      subI_rReg_memNode *node = new subI_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case subI_mem_rReg_rule: {
      subI_mem_rRegNode *node = new subI_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subL_rReg_rule: {
      subL_rRegNode *node = new subL_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case subL_rReg_mem_rule: {
      subL_rReg_memNode *node = new subL_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case subL_mem_rReg_rule: {
      subL_mem_rRegNode *node = new subL_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_carry_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subP_rReg_rule: {
      subP_rRegNode *node = new subP_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case negI_rReg_rule: {
      negI_rRegNode *node = new negI_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case negI_rReg_2_rule: {
      negI_rReg_2Node *node = new negI_rReg_2Node();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case negI_mem_rule: {
      negI_memNode *node = new negI_memNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case negL_rReg_rule: {
      negL_rRegNode *node = new negL_rRegNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case negL_rReg_2_rule: {
      negL_rReg_2Node *node = new negL_rReg_2Node();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag);
      return node;
    }
  case negL_mem_rule: {
      negL_memNode *node = new negL_memNode();
      node->add_flag(Node::PD::Flag_sets_overflow_flag | Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mulI_rReg_rule: {
      mulI_rRegNode *node = new mulI_rRegNode();
      return node;
    }
  case mulI_rReg_imm_rule: {
      mulI_rReg_immNode *node = new mulI_rReg_immNode();
      return node;
    }
  case mulI_mem_rule: {
      mulI_memNode *node = new mulI_memNode();
      return node;
    }
  case mulI_mem_0_rule: {
      mulI_mem_0Node *node = new mulI_mem_0Node();
      return node;
    }
  case mulI_mem_imm_rule: {
      mulI_mem_immNode *node = new mulI_mem_immNode();
      return node;
    }
  case mulAddS2I_rReg_rule: {
      mulAddS2I_rRegNode *node = new mulAddS2I_rRegNode();
      return node;
    }
  case mulL_rReg_rule: {
      mulL_rRegNode *node = new mulL_rRegNode();
      return node;
    }
  case mulL_rReg_imm_rule: {
      mulL_rReg_immNode *node = new mulL_rReg_immNode();
      return node;
    }
  case mulL_mem_rule: {
      mulL_memNode *node = new mulL_memNode();
      return node;
    }
  case mulL_mem_0_rule: {
      mulL_mem_0Node *node = new mulL_mem_0Node();
      return node;
    }
  case mulL_mem_imm_rule: {
      mulL_mem_immNode *node = new mulL_mem_immNode();
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
  case divI_rReg_rule: {
      divI_rRegNode *node = new divI_rRegNode();
      return node;
    }
  case divL_rReg_rule: {
      divL_rRegNode *node = new divL_rRegNode();
      return node;
    }
  case udivI_rReg_rule: {
      udivI_rRegNode *node = new udivI_rRegNode();
      return node;
    }
  case udivL_rReg_rule: {
      udivL_rRegNode *node = new udivL_rRegNode();
      return node;
    }
  case divModI_rReg_divmod_rule: {
      divModI_rReg_divmodNode *node = new divModI_rReg_divmodNode();
      return node;
    }
  case divModL_rReg_divmod_rule: {
      divModL_rReg_divmodNode *node = new divModL_rReg_divmodNode();
      return node;
    }
  case udivModI_rReg_divmod_rule: {
      udivModI_rReg_divmodNode *node = new udivModI_rReg_divmodNode();
      node->set_opnd_array(3, MachOperGenerator(NO_RAX_RDX_REGI));
      return node;
    }
  case udivModL_rReg_divmod_rule: {
      udivModL_rReg_divmodNode *node = new udivModL_rReg_divmodNode();
      node->set_opnd_array(3, MachOperGenerator(NO_RAX_RDX_REGL));
      return node;
    }
  case modI_rReg_rule: {
      modI_rRegNode *node = new modI_rRegNode();
      return node;
    }
  case modL_rReg_rule: {
      modL_rRegNode *node = new modL_rRegNode();
      return node;
    }
  case umodI_rReg_rule: {
      umodI_rRegNode *node = new umodI_rRegNode();
      return node;
    }
  case umodL_rReg_rule: {
      umodL_rRegNode *node = new umodL_rRegNode();
      return node;
    }
  case salI_rReg_immI2_rule: {
      salI_rReg_immI2Node *node = new salI_rReg_immI2Node();
      return node;
    }
  case salI_rReg_imm_rule: {
      salI_rReg_immNode *node = new salI_rReg_immNode();
      return node;
    }
  case salI_mem_imm_rule: {
      salI_mem_immNode *node = new salI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case salI_rReg_CL_rule: {
      salI_rReg_CLNode *node = new salI_rReg_CLNode();
      return node;
    }
  case salI_mem_CL_rule: {
      salI_mem_CLNode *node = new salI_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case salI_rReg_rReg_rule: {
      salI_rReg_rRegNode *node = new salI_rReg_rRegNode();
      return node;
    }
  case salI_mem_rReg_rule: {
      salI_mem_rRegNode *node = new salI_mem_rRegNode();
      return node;
    }
  case sarI_rReg_imm_rule: {
      sarI_rReg_immNode *node = new sarI_rReg_immNode();
      return node;
    }
  case sarI_mem_imm_rule: {
      sarI_mem_immNode *node = new sarI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sarI_rReg_CL_rule: {
      sarI_rReg_CLNode *node = new sarI_rReg_CLNode();
      return node;
    }
  case sarI_mem_CL_rule: {
      sarI_mem_CLNode *node = new sarI_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sarI_rReg_rReg_rule: {
      sarI_rReg_rRegNode *node = new sarI_rReg_rRegNode();
      return node;
    }
  case sarI_mem_rReg_rule: {
      sarI_mem_rRegNode *node = new sarI_mem_rRegNode();
      return node;
    }
  case shrI_rReg_imm_rule: {
      shrI_rReg_immNode *node = new shrI_rReg_immNode();
      return node;
    }
  case shrI_mem_imm_rule: {
      shrI_mem_immNode *node = new shrI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case shrI_rReg_CL_rule: {
      shrI_rReg_CLNode *node = new shrI_rReg_CLNode();
      return node;
    }
  case shrI_mem_CL_rule: {
      shrI_mem_CLNode *node = new shrI_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case shrI_rReg_rReg_rule: {
      shrI_rReg_rRegNode *node = new shrI_rReg_rRegNode();
      return node;
    }
  case shrI_mem_rReg_rule: {
      shrI_mem_rRegNode *node = new shrI_mem_rRegNode();
      return node;
    }
  case salL_rReg_immI2_rule: {
      salL_rReg_immI2Node *node = new salL_rReg_immI2Node();
      return node;
    }
  case salL_rReg_imm_rule: {
      salL_rReg_immNode *node = new salL_rReg_immNode();
      return node;
    }
  case salL_mem_imm_rule: {
      salL_mem_immNode *node = new salL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case salL_rReg_CL_rule: {
      salL_rReg_CLNode *node = new salL_rReg_CLNode();
      return node;
    }
  case salL_mem_CL_rule: {
      salL_mem_CLNode *node = new salL_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case salL_rReg_rReg_rule: {
      salL_rReg_rRegNode *node = new salL_rReg_rRegNode();
      return node;
    }
  case salL_mem_rReg_rule: {
      salL_mem_rRegNode *node = new salL_mem_rRegNode();
      return node;
    }
  case sarL_rReg_imm_rule: {
      sarL_rReg_immNode *node = new sarL_rReg_immNode();
      return node;
    }
  case sarL_mem_imm_rule: {
      sarL_mem_immNode *node = new sarL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sarL_rReg_CL_rule: {
      sarL_rReg_CLNode *node = new sarL_rReg_CLNode();
      return node;
    }
  case sarL_mem_CL_rule: {
      sarL_mem_CLNode *node = new sarL_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sarL_rReg_rReg_rule: {
      sarL_rReg_rRegNode *node = new sarL_rReg_rRegNode();
      return node;
    }
  case sarL_mem_rReg_rule: {
      sarL_mem_rRegNode *node = new sarL_mem_rRegNode();
      return node;
    }
  case shrL_rReg_imm_rule: {
      shrL_rReg_immNode *node = new shrL_rReg_immNode();
      return node;
    }
  case shrL_mem_imm_rule: {
      shrL_mem_immNode *node = new shrL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case shrL_rReg_CL_rule: {
      shrL_rReg_CLNode *node = new shrL_rReg_CLNode();
      return node;
    }
  case shrL_mem_CL_rule: {
      shrL_mem_CLNode *node = new shrL_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case shrL_rReg_rReg_rule: {
      shrL_rReg_rRegNode *node = new shrL_rReg_rRegNode();
      return node;
    }
  case shrL_mem_rReg_rule: {
      shrL_mem_rRegNode *node = new shrL_mem_rRegNode();
      return node;
    }
  case i2b_rule: {
      i2bNode *node = new i2bNode();
      return node;
    }
  case i2s_rule: {
      i2sNode *node = new i2sNode();
      return node;
    }
  case rolI_immI8_legacy_rule: {
      rolI_immI8_legacyNode *node = new rolI_immI8_legacyNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rolI_immI8_rule: {
      rolI_immI8Node *node = new rolI_immI8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rolI_mem_immI8_rule: {
      rolI_mem_immI8Node *node = new rolI_mem_immI8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rolI_rReg_Var_rule: {
      rolI_rReg_VarNode *node = new rolI_rReg_VarNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorI_immI8_legacy_rule: {
      rorI_immI8_legacyNode *node = new rorI_immI8_legacyNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorI_immI8_rule: {
      rorI_immI8Node *node = new rorI_immI8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorI_mem_immI8_rule: {
      rorI_mem_immI8Node *node = new rorI_mem_immI8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorI_rReg_Var_rule: {
      rorI_rReg_VarNode *node = new rorI_rReg_VarNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rolL_immI8_legacy_rule: {
      rolL_immI8_legacyNode *node = new rolL_immI8_legacyNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rolL_immI8_rule: {
      rolL_immI8Node *node = new rolL_immI8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rolL_mem_immI8_rule: {
      rolL_mem_immI8Node *node = new rolL_mem_immI8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rolL_rReg_Var_rule: {
      rolL_rReg_VarNode *node = new rolL_rReg_VarNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorL_immI8_legacy_rule: {
      rorL_immI8_legacyNode *node = new rorL_immI8_legacyNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorL_immI8_rule: {
      rorL_immI8Node *node = new rorL_immI8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorL_mem_immI8_rule: {
      rorL_mem_immI8Node *node = new rorL_mem_immI8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rorL_rReg_Var_rule: {
      rorL_rReg_VarNode *node = new rorL_rReg_VarNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compressBitsL_reg_rule: {
      compressBitsL_regNode *node = new compressBitsL_regNode();
      return node;
    }
  case expandBitsL_reg_rule: {
      expandBitsL_regNode *node = new expandBitsL_regNode();
      return node;
    }
  case compressBitsL_mem_rule: {
      compressBitsL_memNode *node = new compressBitsL_memNode();
      return node;
    }
  case expandBitsL_mem_rule: {
      expandBitsL_memNode *node = new expandBitsL_memNode();
      return node;
    }
  case andI_rReg_rule: {
      andI_rRegNode *node = new andI_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andI_rReg_imm255_rule: {
      andI_rReg_imm255Node *node = new andI_rReg_imm255Node();
      return node;
    }
  case andI2L_rReg_imm255_rule: {
      andI2L_rReg_imm255Node *node = new andI2L_rReg_imm255Node();
      return node;
    }
  case andI_rReg_imm65535_rule: {
      andI_rReg_imm65535Node *node = new andI_rReg_imm65535Node();
      return node;
    }
  case andI2L_rReg_imm65535_rule: {
      andI2L_rReg_imm65535Node *node = new andI2L_rReg_imm65535Node();
      return node;
    }
  case convI2LAndI_reg_immIbitmask_rule: {
      convI2LAndI_reg_immIbitmaskNode *node = new convI2LAndI_reg_immIbitmaskNode();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      return node;
    }
  case andI_rReg_imm_rule: {
      andI_rReg_immNode *node = new andI_rReg_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andI_rReg_mem_rule: {
      andI_rReg_memNode *node = new andI_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andI_rReg_mem_0_rule: {
      andI_rReg_mem_0Node *node = new andI_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andB_mem_rReg_rule: {
      andB_mem_rRegNode *node = new andB_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andB_mem_rReg_0_rule: {
      andB_mem_rReg_0Node *node = new andB_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andI_mem_rReg_rule: {
      andI_mem_rRegNode *node = new andI_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andI_mem_rReg_0_rule: {
      andI_mem_rReg_0Node *node = new andI_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andI_mem_imm_rule: {
      andI_mem_immNode *node = new andI_mem_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andnI_rReg_rReg_mem_rule: {
      andnI_rReg_rReg_memNode *node = new andnI_rReg_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andnI_rReg_rReg_mem_0_rule: {
      andnI_rReg_rReg_mem_0Node *node = new andnI_rReg_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andnI_rReg_rReg_rReg_rule: {
      andnI_rReg_rReg_rRegNode *node = new andnI_rReg_rReg_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andnI_rReg_rReg_rReg_0_rule: {
      andnI_rReg_rReg_rReg_0Node *node = new andnI_rReg_rReg_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case blsiI_rReg_rReg_rule: {
      blsiI_rReg_rRegNode *node = new blsiI_rReg_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsiI_rReg_rReg_0_rule: {
      blsiI_rReg_rReg_0Node *node = new blsiI_rReg_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsiI_rReg_mem_rule: {
      blsiI_rReg_memNode *node = new blsiI_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsiI_rReg_mem_0_rule: {
      blsiI_rReg_mem_0Node *node = new blsiI_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsmskI_rReg_mem_rule: {
      blsmskI_rReg_memNode *node = new blsmskI_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_clears_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsmskI_rReg_mem_0_rule: {
      blsmskI_rReg_mem_0Node *node = new blsmskI_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_clears_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsmskI_rReg_rReg_rule: {
      blsmskI_rReg_rRegNode *node = new blsmskI_rReg_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_clears_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsmskI_rReg_rReg_0_rule: {
      blsmskI_rReg_rReg_0Node *node = new blsmskI_rReg_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_clears_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsrI_rReg_rReg_rule: {
      blsrI_rReg_rRegNode *node = new blsrI_rReg_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsrI_rReg_rReg_0_rule: {
      blsrI_rReg_rReg_0Node *node = new blsrI_rReg_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsrI_rReg_mem_rule: {
      blsrI_rReg_memNode *node = new blsrI_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsrI_rReg_mem_0_rule: {
      blsrI_rReg_mem_0Node *node = new blsrI_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case orI_rReg_rule: {
      orI_rRegNode *node = new orI_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case orI_rReg_imm_rule: {
      orI_rReg_immNode *node = new orI_rReg_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case orI_rReg_mem_rule: {
      orI_rReg_memNode *node = new orI_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case orI_rReg_mem_0_rule: {
      orI_rReg_mem_0Node *node = new orI_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case orB_mem_rReg_rule: {
      orB_mem_rRegNode *node = new orB_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case orB_mem_rReg_0_rule: {
      orB_mem_rReg_0Node *node = new orB_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case orI_mem_rReg_rule: {
      orI_mem_rRegNode *node = new orI_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case orI_mem_rReg_0_rule: {
      orI_mem_rReg_0Node *node = new orI_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case orI_mem_imm_rule: {
      orI_mem_immNode *node = new orI_mem_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorI_rReg_rule: {
      xorI_rRegNode *node = new xorI_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case xorI_rReg_im1_rule: {
      xorI_rReg_im1Node *node = new xorI_rReg_im1Node();
      return node;
    }
  case xorI_rReg_imm_rule: {
      xorI_rReg_immNode *node = new xorI_rReg_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case xorI_rReg_mem_rule: {
      xorI_rReg_memNode *node = new xorI_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case xorI_rReg_mem_0_rule: {
      xorI_rReg_mem_0Node *node = new xorI_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case xorB_mem_rReg_rule: {
      xorB_mem_rRegNode *node = new xorB_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorB_mem_rReg_0_rule: {
      xorB_mem_rReg_0Node *node = new xorB_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorI_mem_rReg_rule: {
      xorI_mem_rRegNode *node = new xorI_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorI_mem_rReg_0_rule: {
      xorI_mem_rReg_0Node *node = new xorI_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorI_mem_imm_rule: {
      xorI_mem_immNode *node = new xorI_mem_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andL_rReg_rule: {
      andL_rRegNode *node = new andL_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andL_rReg_imm255_rule: {
      andL_rReg_imm255Node *node = new andL_rReg_imm255Node();
      return node;
    }
  case andL_rReg_imm65535_rule: {
      andL_rReg_imm65535Node *node = new andL_rReg_imm65535Node();
      return node;
    }
  case andL_rReg_imm_rule: {
      andL_rReg_immNode *node = new andL_rReg_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andL_rReg_mem_rule: {
      andL_rReg_memNode *node = new andL_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andL_rReg_mem_0_rule: {
      andL_rReg_mem_0Node *node = new andL_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andL_mem_rReg_rule: {
      andL_mem_rRegNode *node = new andL_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andL_mem_rReg_0_rule: {
      andL_mem_rReg_0Node *node = new andL_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andL_mem_imm_rule: {
      andL_mem_immNode *node = new andL_mem_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case btrL_mem_imm_rule: {
      btrL_mem_immNode *node = new btrL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andnL_rReg_rReg_mem_rule: {
      andnL_rReg_rReg_memNode *node = new andnL_rReg_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andnL_rReg_rReg_mem_0_rule: {
      andnL_rReg_rReg_mem_0Node *node = new andnL_rReg_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andnL_rReg_rReg_rReg_rule: {
      andnL_rReg_rReg_rRegNode *node = new andnL_rReg_rReg_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case andnL_rReg_rReg_rReg_0_rule: {
      andnL_rReg_rReg_rReg_0Node *node = new andnL_rReg_rReg_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case blsiL_rReg_rReg_rule: {
      blsiL_rReg_rRegNode *node = new blsiL_rReg_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsiL_rReg_rReg_0_rule: {
      blsiL_rReg_rReg_0Node *node = new blsiL_rReg_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsiL_rReg_mem_rule: {
      blsiL_rReg_memNode *node = new blsiL_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsiL_rReg_mem_0_rule: {
      blsiL_rReg_mem_0Node *node = new blsiL_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsmskL_rReg_mem_rule: {
      blsmskL_rReg_memNode *node = new blsmskL_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_clears_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsmskL_rReg_mem_0_rule: {
      blsmskL_rReg_mem_0Node *node = new blsmskL_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_clears_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsmskL_rReg_rReg_rule: {
      blsmskL_rReg_rRegNode *node = new blsmskL_rReg_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_clears_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsmskL_rReg_rReg_0_rule: {
      blsmskL_rReg_rReg_0Node *node = new blsmskL_rReg_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_clears_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsrL_rReg_rReg_rule: {
      blsrL_rReg_rRegNode *node = new blsrL_rReg_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsrL_rReg_rReg_0_rule: {
      blsrL_rReg_rReg_0Node *node = new blsrL_rReg_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsrL_rReg_mem_rule: {
      blsrL_rReg_memNode *node = new blsrL_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case blsrL_rReg_mem_0_rule: {
      blsrL_rReg_mem_0Node *node = new blsrL_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_clears_overflow_flag);
      return node;
    }
  case orL_rReg_rule: {
      orL_rRegNode *node = new orL_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case orL_rReg_castP2X_rule: {
      orL_rReg_castP2XNode *node = new orL_rReg_castP2XNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case orL_rReg_castP2X_0_rule: {
      orL_rReg_castP2X_0Node *node = new orL_rReg_castP2X_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case orL_rReg_imm_rule: {
      orL_rReg_immNode *node = new orL_rReg_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case orL_rReg_mem_rule: {
      orL_rReg_memNode *node = new orL_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case orL_rReg_mem_0_rule: {
      orL_rReg_mem_0Node *node = new orL_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case orL_mem_rReg_rule: {
      orL_mem_rRegNode *node = new orL_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case orL_mem_rReg_0_rule: {
      orL_mem_rReg_0Node *node = new orL_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case orL_mem_imm_rule: {
      orL_mem_immNode *node = new orL_mem_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case btsL_mem_imm_rule: {
      btsL_mem_immNode *node = new btsL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorL_rReg_rule: {
      xorL_rRegNode *node = new xorL_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case xorL_rReg_im1_rule: {
      xorL_rReg_im1Node *node = new xorL_rReg_im1Node();
      return node;
    }
  case xorL_rReg_imm_rule: {
      xorL_rReg_immNode *node = new xorL_rReg_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case xorL_rReg_mem_rule: {
      xorL_rReg_memNode *node = new xorL_rReg_memNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case xorL_rReg_mem_0_rule: {
      xorL_rReg_mem_0Node *node = new xorL_rReg_mem_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      return node;
    }
  case xorL_mem_rReg_rule: {
      xorL_mem_rRegNode *node = new xorL_mem_rRegNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorL_mem_rReg_0_rule: {
      xorL_mem_rReg_0Node *node = new xorL_mem_rReg_0Node();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorL_mem_imm_rule: {
      xorL_mem_immNode *node = new xorL_mem_immNode();
      node->add_flag(Node::PD::Flag_sets_sign_flag | Node::PD::Flag_sets_zero_flag | Node::PD::Flag_sets_parity_flag | Node::PD::Flag_clears_overflow_flag | Node::PD::Flag_clears_carry_flag);
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cmpLTMask_rule: {
      cmpLTMaskNode *node = new cmpLTMaskNode();
      return node;
    }
  case cmpLTMask0_rule: {
      cmpLTMask0Node *node = new cmpLTMask0Node();
      return node;
    }
  case cadd_cmpLTMask_rule: {
      cadd_cmpLTMaskNode *node = new cadd_cmpLTMaskNode();
      return node;
    }
  case cadd_cmpLTMask_1_rule: {
      cadd_cmpLTMask_1Node *node = new cadd_cmpLTMask_1Node();
      return node;
    }
  case cadd_cmpLTMask_0_rule: {
      cadd_cmpLTMask_0Node *node = new cadd_cmpLTMask_0Node();
      return node;
    }
  case cadd_cmpLTMask_2_rule: {
      cadd_cmpLTMask_2Node *node = new cadd_cmpLTMask_2Node();
      return node;
    }
  case and_cmpLTMask_rule: {
      and_cmpLTMaskNode *node = new and_cmpLTMaskNode();
      return node;
    }
  case and_cmpLTMask_0_rule: {
      and_cmpLTMask_0Node *node = new and_cmpLTMask_0Node();
      return node;
    }
  case cmpF_cc_reg_rule: {
      cmpF_cc_regNode *node = new cmpF_cc_regNode();
      return node;
    }
  case cmpF_cc_reg_CF_rule: {
      cmpF_cc_reg_CFNode *node = new cmpF_cc_reg_CFNode();
      return node;
    }
  case cmpF_cc_memCF_rule: {
      cmpF_cc_memCFNode *node = new cmpF_cc_memCFNode();
      return node;
    }
  case cmpF_cc_immCF_rule: {
      cmpF_cc_immCFNode *node = new cmpF_cc_immCFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cmpD_cc_reg_rule: {
      cmpD_cc_regNode *node = new cmpD_cc_regNode();
      return node;
    }
  case cmpD_cc_reg_CF_rule: {
      cmpD_cc_reg_CFNode *node = new cmpD_cc_reg_CFNode();
      return node;
    }
  case cmpD_cc_memCF_rule: {
      cmpD_cc_memCFNode *node = new cmpD_cc_memCFNode();
      return node;
    }
  case cmpD_cc_immCF_rule: {
      cmpD_cc_immCFNode *node = new cmpD_cc_immCFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cmpF_reg_rule: {
      cmpF_regNode *node = new cmpF_regNode();
      return node;
    }
  case cmpF_mem_rule: {
      cmpF_memNode *node = new cmpF_memNode();
      return node;
    }
  case cmpF_imm_rule: {
      cmpF_immNode *node = new cmpF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cmpD_reg_rule: {
      cmpD_regNode *node = new cmpD_regNode();
      return node;
    }
  case cmpD_mem_rule: {
      cmpD_memNode *node = new cmpD_memNode();
      return node;
    }
  case cmpD_imm_rule: {
      cmpD_immNode *node = new cmpD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case convF2D_reg_reg_rule: {
      convF2D_reg_regNode *node = new convF2D_reg_regNode();
      return node;
    }
  case convF2D_reg_mem_rule: {
      convF2D_reg_memNode *node = new convF2D_reg_memNode();
      return node;
    }
  case convD2F_reg_reg_rule: {
      convD2F_reg_regNode *node = new convD2F_reg_regNode();
      return node;
    }
  case convD2F_reg_mem_rule: {
      convD2F_reg_memNode *node = new convD2F_reg_memNode();
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
  case convD2I_reg_reg_rule: {
      convD2I_reg_regNode *node = new convD2I_reg_regNode();
      return node;
    }
  case convD2L_reg_reg_rule: {
      convD2L_reg_regNode *node = new convD2L_reg_regNode();
      return node;
    }
  case round_double_reg_rule: {
      round_double_regNode *node = new round_double_regNode();
      node->set_opnd_array(2, MachOperGenerator(RREGL));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      node->set_opnd_array(4, MachOperGenerator(RCX_REGL));
      return node;
    }
  case round_float_reg_rule: {
      round_float_regNode *node = new round_float_regNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      node->set_opnd_array(4, MachOperGenerator(RCX_REGL));
      return node;
    }
  case convI2F_reg_reg_rule: {
      convI2F_reg_regNode *node = new convI2F_reg_regNode();
      return node;
    }
  case convI2F_reg_mem_rule: {
      convI2F_reg_memNode *node = new convI2F_reg_memNode();
      return node;
    }
  case convI2D_reg_reg_rule: {
      convI2D_reg_regNode *node = new convI2D_reg_regNode();
      return node;
    }
  case convI2D_reg_mem_rule: {
      convI2D_reg_memNode *node = new convI2D_reg_memNode();
      return node;
    }
  case convXI2F_reg_rule: {
      convXI2F_regNode *node = new convXI2F_regNode();
      return node;
    }
  case convXI2D_reg_rule: {
      convXI2D_regNode *node = new convXI2D_regNode();
      return node;
    }
  case convL2F_reg_reg_rule: {
      convL2F_reg_regNode *node = new convL2F_reg_regNode();
      return node;
    }
  case convL2F_reg_mem_rule: {
      convL2F_reg_memNode *node = new convL2F_reg_memNode();
      return node;
    }
  case convL2D_reg_reg_rule: {
      convL2D_reg_regNode *node = new convL2D_reg_regNode();
      return node;
    }
  case convL2D_reg_mem_rule: {
      convL2D_reg_memNode *node = new convL2D_reg_memNode();
      return node;
    }
  case convI2L_reg_reg_rule: {
      convI2L_reg_regNode *node = new convI2L_reg_regNode();
      return node;
    }
  case convI2L_reg_reg_zex_rule: {
      convI2L_reg_reg_zexNode *node = new convI2L_reg_reg_zexNode();
      return node;
    }
  case convI2L_reg_mem_zex_rule: {
      convI2L_reg_mem_zexNode *node = new convI2L_reg_mem_zexNode();
      return node;
    }
  case zerox_long_reg_reg_rule: {
      zerox_long_reg_regNode *node = new zerox_long_reg_regNode();
      return node;
    }
  case convL2I_reg_reg_rule: {
      convL2I_reg_regNode *node = new convL2I_reg_regNode();
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
  case MoveL2D_stack_reg_partial_rule: {
      MoveL2D_stack_reg_partialNode *node = new MoveL2D_stack_reg_partialNode();
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
  case MoveD2L_reg_reg_rule: {
      MoveD2L_reg_regNode *node = new MoveD2L_reg_regNode();
      return node;
    }
  case MoveI2F_reg_reg_rule: {
      MoveI2F_reg_regNode *node = new MoveI2F_reg_regNode();
      return node;
    }
  case MoveL2D_reg_reg_rule: {
      MoveL2D_reg_regNode *node = new MoveL2D_reg_regNode();
      return node;
    }
  case rep_stos_rule: {
      rep_stosNode *node = new rep_stosNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      return node;
    }
  case rep_stos_evex_rule: {
      rep_stos_evexNode *node = new rep_stos_evexNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(KREG));
      return node;
    }
  case rep_stos_large_rule: {
      rep_stos_largeNode *node = new rep_stos_largeNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      return node;
    }
  case rep_stos_large_evex_rule: {
      rep_stos_large_evexNode *node = new rep_stos_large_evexNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(KREG));
      return node;
    }
  case rep_stos_im_rule: {
      rep_stos_imNode *node = new rep_stos_imNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      return node;
    }
  case string_compareL_rule: {
      string_compareLNode *node = new string_compareLNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_compareL_evex_rule: {
      string_compareL_evexNode *node = new string_compareL_evexNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      return node;
    }
  case string_compareU_rule: {
      string_compareUNode *node = new string_compareUNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_compareU_evex_rule: {
      string_compareU_evexNode *node = new string_compareU_evexNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      return node;
    }
  case string_compareLU_rule: {
      string_compareLUNode *node = new string_compareLUNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_compareLU_evex_rule: {
      string_compareLU_evexNode *node = new string_compareLU_evexNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      return node;
    }
  case string_compareUL_rule: {
      string_compareULNode *node = new string_compareULNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_compareUL_evex_rule: {
      string_compareUL_evexNode *node = new string_compareUL_evexNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      return node;
    }
  case string_indexof_conL_rule: {
      string_indexof_conLNode *node = new string_indexof_conLNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_indexof_conU_rule: {
      string_indexof_conUNode *node = new string_indexof_conUNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_indexof_conUL_rule: {
      string_indexof_conULNode *node = new string_indexof_conULNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_indexofL_rule: {
      string_indexofLNode *node = new string_indexofLNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_indexofU_rule: {
      string_indexofUNode *node = new string_indexofUNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_indexofUL_rule: {
      string_indexofULNode *node = new string_indexofULNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_indexof_char_rule: {
      string_indexof_charNode *node = new string_indexof_charNode();
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(LEGREGD));
      node->set_opnd_array(7, MachOperGenerator(RCX_REGI));
      return node;
    }
  case stringL_indexof_char_rule: {
      stringL_indexof_charNode *node = new stringL_indexof_charNode();
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(LEGREGD));
      node->set_opnd_array(7, MachOperGenerator(RCX_REGI));
      return node;
    }
  case string_equals_rule: {
      string_equalsNode *node = new string_equalsNode();
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_equals_evex_rule: {
      string_equals_evexNode *node = new string_equals_evexNode();
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      return node;
    }
  case array_equalsB_rule: {
      array_equalsBNode *node = new array_equalsBNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      return node;
    }
  case array_equalsB_evex_rule: {
      array_equalsB_evexNode *node = new array_equalsB_evexNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      return node;
    }
  case array_equalsC_rule: {
      array_equalsCNode *node = new array_equalsCNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      return node;
    }
  case array_equalsC_evex_rule: {
      array_equalsC_evexNode *node = new array_equalsC_evexNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      return node;
    }
  case arrays_hashcode_rule: {
      arrays_hashcodeNode *node = new arrays_hashcodeNode();
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(LEGREGD));
      node->set_opnd_array(7, MachOperGenerator(LEGREGD));
      node->set_opnd_array(8, MachOperGenerator(LEGREGD));
      node->set_opnd_array(9, MachOperGenerator(LEGREGD));
      node->set_opnd_array(10, MachOperGenerator(LEGREGD));
      node->set_opnd_array(11, MachOperGenerator(LEGREGD));
      node->set_opnd_array(12, MachOperGenerator(LEGREGD));
      node->set_opnd_array(13, MachOperGenerator(LEGREGD));
      node->set_opnd_array(14, MachOperGenerator(LEGREGD));
      node->set_opnd_array(15, MachOperGenerator(LEGREGD));
      node->set_opnd_array(16, MachOperGenerator(LEGREGD));
      node->set_opnd_array(17, MachOperGenerator(LEGREGD));
      node->set_opnd_array(18, MachOperGenerator(RREGI));
      node->set_opnd_array(19, MachOperGenerator(RREGI));
      node->set_opnd_array(20, MachOperGenerator(RREGI));
      return node;
    }
  case count_positives_rule: {
      count_positivesNode *node = new count_positivesNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      return node;
    }
  case count_positives_evex_rule: {
      count_positives_evexNode *node = new count_positives_evexNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      return node;
    }
  case string_compress_rule: {
      string_compressNode *node = new string_compressNode();
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(LEGREGD));
      node->set_opnd_array(7, MachOperGenerator(LEGREGD));
      return node;
    }
  case string_compress_evex_rule: {
      string_compress_evexNode *node = new string_compress_evexNode();
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(LEGREGD));
      node->set_opnd_array(7, MachOperGenerator(LEGREGD));
      node->set_opnd_array(8, MachOperGenerator(KREG));
      node->set_opnd_array(9, MachOperGenerator(KREG));
      return node;
    }
  case string_inflate_rule: {
      string_inflateNode *node = new string_inflateNode();
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(RCX_REGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case string_inflate_evex_rule: {
      string_inflate_evexNode *node = new string_inflate_evexNode();
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->set_opnd_array(6, MachOperGenerator(RCX_REGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encode_iso_array_rule: {
      encode_iso_arrayNode *node = new encode_iso_arrayNode();
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(LEGREGD));
      node->set_opnd_array(7, MachOperGenerator(LEGREGD));
      return node;
    }
  case encode_ascii_array_rule: {
      encode_ascii_arrayNode *node = new encode_ascii_arrayNode();
      node->set_opnd_array(4, MachOperGenerator(LEGREGD));
      node->set_opnd_array(5, MachOperGenerator(LEGREGD));
      node->set_opnd_array(6, MachOperGenerator(LEGREGD));
      node->set_opnd_array(7, MachOperGenerator(LEGREGD));
      return node;
    }
  case overflowAddI_rReg_rule: {
      overflowAddI_rRegNode *node = new overflowAddI_rRegNode();
      return node;
    }
  case overflowAddI_rReg_imm_rule: {
      overflowAddI_rReg_immNode *node = new overflowAddI_rReg_immNode();
      return node;
    }
  case overflowAddL_rReg_rule: {
      overflowAddL_rRegNode *node = new overflowAddL_rRegNode();
      return node;
    }
  case overflowAddL_rReg_imm_rule: {
      overflowAddL_rReg_immNode *node = new overflowAddL_rReg_immNode();
      return node;
    }
  case overflowSubI_rReg_rule: {
      overflowSubI_rRegNode *node = new overflowSubI_rRegNode();
      return node;
    }
  case overflowSubI_rReg_imm_rule: {
      overflowSubI_rReg_immNode *node = new overflowSubI_rReg_immNode();
      return node;
    }
  case overflowSubL_rReg_rule: {
      overflowSubL_rRegNode *node = new overflowSubL_rRegNode();
      return node;
    }
  case overflowSubL_rReg_imm_rule: {
      overflowSubL_rReg_immNode *node = new overflowSubL_rReg_immNode();
      return node;
    }
  case overflowNegI_rReg_rule: {
      overflowNegI_rRegNode *node = new overflowNegI_rRegNode();
      return node;
    }
  case overflowNegL_rReg_rule: {
      overflowNegL_rRegNode *node = new overflowNegL_rRegNode();
      return node;
    }
  case overflowMulI_rReg_rule: {
      overflowMulI_rRegNode *node = new overflowMulI_rRegNode();
      return node;
    }
  case overflowMulI_rReg_imm_rule: {
      overflowMulI_rReg_immNode *node = new overflowMulI_rReg_immNode();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      return node;
    }
  case overflowMulL_rReg_rule: {
      overflowMulL_rRegNode *node = new overflowMulL_rRegNode();
      return node;
    }
  case overflowMulL_rReg_imm_rule: {
      overflowMulL_rReg_immNode *node = new overflowMulL_rReg_immNode();
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      return node;
    }
  case compI_rReg_rule: {
      compI_rRegNode *node = new compI_rRegNode();
      return node;
    }
  case compI_rReg_imm_rule: {
      compI_rReg_immNode *node = new compI_rReg_immNode();
      return node;
    }
  case compI_rReg_mem_rule: {
      compI_rReg_memNode *node = new compI_rReg_memNode();
      return node;
    }
  case testI_reg_rule: {
      testI_regNode *node = new testI_regNode();
      return node;
    }
  case testI_reg_imm_rule: {
      testI_reg_immNode *node = new testI_reg_immNode();
      return node;
    }
  case testI_reg_reg_rule: {
      testI_reg_regNode *node = new testI_reg_regNode();
      return node;
    }
  case testI_reg_mem_rule: {
      testI_reg_memNode *node = new testI_reg_memNode();
      return node;
    }
  case testI_reg_mem_0_rule: {
      testI_reg_mem_0Node *node = new testI_reg_mem_0Node();
      return node;
    }
  case compU_rReg_rule: {
      compU_rRegNode *node = new compU_rRegNode();
      return node;
    }
  case compU_rReg_imm_rule: {
      compU_rReg_immNode *node = new compU_rReg_immNode();
      return node;
    }
  case compU_rReg_mem_rule: {
      compU_rReg_memNode *node = new compU_rReg_memNode();
      return node;
    }
  case testU_reg_rule: {
      testU_regNode *node = new testU_regNode();
      return node;
    }
  case compP_rReg_rule: {
      compP_rRegNode *node = new compP_rRegNode();
      return node;
    }
  case compP_rReg_mem_rule: {
      compP_rReg_memNode *node = new compP_rReg_memNode();
      return node;
    }
  case compP_mem_rReg_rule: {
      compP_mem_rRegNode *node = new compP_mem_rRegNode();
      return node;
    }
  case testP_reg_rule: {
      testP_regNode *node = new testP_regNode();
      return node;
    }
  case testP_mem_rule: {
      testP_memNode *node = new testP_memNode();
      return node;
    }
  case testP_mem_reg0_rule: {
      testP_mem_reg0Node *node = new testP_mem_reg0Node();
      return node;
    }
  case compN_rReg_rule: {
      compN_rRegNode *node = new compN_rRegNode();
      return node;
    }
  case compN_rReg_mem_rule: {
      compN_rReg_memNode *node = new compN_rReg_memNode();
      return node;
    }
  case compN_rReg_imm_rule: {
      compN_rReg_immNode *node = new compN_rReg_immNode();
      return node;
    }
  case compN_mem_imm_rule: {
      compN_mem_immNode *node = new compN_mem_immNode();
      return node;
    }
  case compN_rReg_imm_klass_rule: {
      compN_rReg_imm_klassNode *node = new compN_rReg_imm_klassNode();
      return node;
    }
  case compN_mem_imm_klass_rule: {
      compN_mem_imm_klassNode *node = new compN_mem_imm_klassNode();
      return node;
    }
  case testN_reg_rule: {
      testN_regNode *node = new testN_regNode();
      return node;
    }
  case testN_mem_rule: {
      testN_memNode *node = new testN_memNode();
      return node;
    }
  case testN_mem_reg0_rule: {
      testN_mem_reg0Node *node = new testN_mem_reg0Node();
      return node;
    }
  case compL_rReg_rule: {
      compL_rRegNode *node = new compL_rRegNode();
      return node;
    }
  case compL_rReg_imm_rule: {
      compL_rReg_immNode *node = new compL_rReg_immNode();
      return node;
    }
  case compL_rReg_mem_rule: {
      compL_rReg_memNode *node = new compL_rReg_memNode();
      return node;
    }
  case testL_reg_rule: {
      testL_regNode *node = new testL_regNode();
      return node;
    }
  case testL_reg_imm_rule: {
      testL_reg_immNode *node = new testL_reg_immNode();
      return node;
    }
  case testL_reg_reg_rule: {
      testL_reg_regNode *node = new testL_reg_regNode();
      return node;
    }
  case testL_reg_mem_rule: {
      testL_reg_memNode *node = new testL_reg_memNode();
      return node;
    }
  case testL_reg_mem_0_rule: {
      testL_reg_mem_0Node *node = new testL_reg_mem_0Node();
      return node;
    }
  case testL_reg_mem2_rule: {
      testL_reg_mem2Node *node = new testL_reg_mem2Node();
      return node;
    }
  case testL_reg_mem2_0_rule: {
      testL_reg_mem2_0Node *node = new testL_reg_mem2_0Node();
      return node;
    }
  case cmpU3_reg_reg_rule: {
      cmpU3_reg_regNode *node = new cmpU3_reg_regNode();
      return node;
    }
  case cmpL3_reg_reg_rule: {
      cmpL3_reg_regNode *node = new cmpL3_reg_regNode();
      return node;
    }
  case cmpUL3_reg_reg_rule: {
      cmpUL3_reg_regNode *node = new cmpUL3_reg_regNode();
      return node;
    }
  case compUL_rReg_rule: {
      compUL_rRegNode *node = new compUL_rRegNode();
      return node;
    }
  case compUL_rReg_imm_rule: {
      compUL_rReg_immNode *node = new compUL_rReg_immNode();
      return node;
    }
  case compUL_rReg_mem_rule: {
      compUL_rReg_memNode *node = new compUL_rReg_memNode();
      return node;
    }
  case testUL_reg_rule: {
      testUL_regNode *node = new testUL_regNode();
      return node;
    }
  case compB_mem_imm_rule: {
      compB_mem_immNode *node = new compB_mem_immNode();
      return node;
    }
  case testUB_mem_imm_rule: {
      testUB_mem_immNode *node = new testUB_mem_immNode();
      return node;
    }
  case testB_mem_imm_rule: {
      testB_mem_immNode *node = new testB_mem_immNode();
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
  case jmpDir_rule: {
      jmpDirNode *node = new jmpDirNode();
      node->set_opnd_array(1, MachOperGenerator(LABEL));
      return node;
    }
  case jmpCon_rule: {
      jmpConNode *node = new jmpConNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEnd_rule: {
      jmpLoopEndNode *node = new jmpLoopEndNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConU_rule: {
      jmpConUNode *node = new jmpConUNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConUCF_rule: {
      jmpConUCFNode *node = new jmpConUCFNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConUCF2_rule: {
      jmpConUCF2Node *node = new jmpConUCF2Node();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case partialSubtypeCheck_rule: {
      partialSubtypeCheckNode *node = new partialSubtypeCheckNode();
      return node;
    }
  case partialSubtypeCheck_vs_Zero_rule: {
      partialSubtypeCheck_vs_ZeroNode *node = new partialSubtypeCheck_vs_ZeroNode();
      return node;
    }
  case jmpDir_short_rule: {
      jmpDir_shortNode *node = new jmpDir_shortNode();
      node->set_opnd_array(1, MachOperGenerator(LABEL));
      return node;
    }
  case jmpCon_short_rule: {
      jmpCon_shortNode *node = new jmpCon_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEnd_short_rule: {
      jmpLoopEnd_shortNode *node = new jmpLoopEnd_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConU_short_rule: {
      jmpConU_shortNode *node = new jmpConU_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConUCF_short_rule: {
      jmpConUCF_shortNode *node = new jmpConUCF_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConUCF2_short_rule: {
      jmpConUCF2_shortNode *node = new jmpConUCF2_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpFastLockRTM_rule: {
      cmpFastLockRTMNode *node = new cmpFastLockRTMNode();
      node->set_opnd_array(3, MachOperGenerator(RAX_REGI));
      node->set_opnd_array(4, MachOperGenerator(RDX_REGI));
      node->set_opnd_array(5, MachOperGenerator(RREGI));
      node->set_opnd_array(6, MachOperGenerator(RREGI));
      node->_rtm_counters = _leaf->as_FastLock()->rtm_counters();
      node->_stack_rtm_counters = _leaf->as_FastLock()->stack_rtm_counters();
      return node;
    }
  case cmpFastLock_rule: {
      cmpFastLockNode *node = new cmpFastLockNode();
      node->set_opnd_array(3, MachOperGenerator(RAX_REGI));
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->_rtm_counters = _leaf->as_FastLock()->rtm_counters();
      node->_stack_rtm_counters = _leaf->as_FastLock()->stack_rtm_counters();
      return node;
    }
  case cmpFastUnlock_rule: {
      cmpFastUnlockNode *node = new cmpFastUnlockNode();
      node->set_opnd_array(3, MachOperGenerator(RREGP));
      return node;
    }
  case cmpFastLockLightweight_rule: {
      cmpFastLockLightweightNode *node = new cmpFastLockLightweightNode();
      node->set_opnd_array(3, MachOperGenerator(RAX_REGI));
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->_rtm_counters = _leaf->as_FastLock()->rtm_counters();
      node->_stack_rtm_counters = _leaf->as_FastLock()->stack_rtm_counters();
      return node;
    }
  case cmpFastUnlockLightweight_rule: {
      cmpFastUnlockLightweightNode *node = new cmpFastUnlockLightweightNode();
      node->set_opnd_array(3, MachOperGenerator(RREGP));
      return node;
    }
  case safePoint_poll_tls_rule: {
      safePoint_poll_tlsNode *node = new safePoint_poll_tlsNode();
      return node;
    }
  case mask_all_evexL_rule: {
      mask_all_evexLNode *node = new mask_all_evexLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mask_all_evexI_GT32_rule: {
      mask_all_evexI_GT32Node *node = new mask_all_evexI_GT32Node();
      node->set_opnd_array(2, MachOperGenerator(RREGL));
      node->_bottom_type = _leaf->bottom_type();
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
  case CallLeafDirectVector_rule: {
      CallLeafDirectVectorNode *node = new CallLeafDirectVectorNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallLeafNoFPDirect_rule: {
      CallLeafNoFPDirectNode *node = new CallLeafNoFPDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case Ret_rule: {
      RetNode *node = new RetNode();
      return node;
    }
  case TailCalljmpInd_rule: {
      TailCalljmpIndNode *node = new TailCalljmpIndNode();
      return node;
    }
  case tailjmpInd_rule: {
      tailjmpIndNode *node = new tailjmpIndNode();
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
  case tlsLoadP_rule: {
      tlsLoadPNode *node = new tlsLoadPNode();
      return node;
    }
  case leaI_rReg_rReg_peep_rule: {
      leaI_rReg_rReg_peepNode *node = new leaI_rReg_rReg_peepNode();
      return node;
    }
  case leaI_rReg_immI_peep_rule: {
      leaI_rReg_immI_peepNode *node = new leaI_rReg_immI_peepNode();
      return node;
    }
  case leaI_rReg_immI2_peep_rule: {
      leaI_rReg_immI2_peepNode *node = new leaI_rReg_immI2_peepNode();
      return node;
    }
  case leaL_rReg_rReg_peep_rule: {
      leaL_rReg_rReg_peepNode *node = new leaL_rReg_rReg_peepNode();
      return node;
    }
  case leaL_rReg_immL32_peep_rule: {
      leaL_rReg_immL32_peepNode *node = new leaL_rReg_immL32_peepNode();
      return node;
    }
  case leaL_rReg_immI2_peep_rule: {
      leaL_rReg_immI2_peepNode *node = new leaL_rReg_immI2_peepNode();
      return node;
    }
  case ShouldNotReachHere_rule: {
      ShouldNotReachHereNode *node = new ShouldNotReachHereNode();
      node->_halt_reason = _leaf->as_Halt()->_halt_reason;
      node->_reachable   = _leaf->as_Halt()->_reachable;
      return node;
    }
  case addF_reg_rule: {
      addF_regNode *node = new addF_regNode();
      return node;
    }
  case addF_mem_rule: {
      addF_memNode *node = new addF_memNode();
      return node;
    }
  case addF_mem_0_rule: {
      addF_mem_0Node *node = new addF_mem_0Node();
      return node;
    }
  case addF_imm_rule: {
      addF_immNode *node = new addF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addF_reg_reg_rule: {
      addF_reg_regNode *node = new addF_reg_regNode();
      return node;
    }
  case addF_reg_mem_rule: {
      addF_reg_memNode *node = new addF_reg_memNode();
      return node;
    }
  case addF_reg_mem_0_rule: {
      addF_reg_mem_0Node *node = new addF_reg_mem_0Node();
      return node;
    }
  case addF_reg_imm_rule: {
      addF_reg_immNode *node = new addF_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addD_reg_rule: {
      addD_regNode *node = new addD_regNode();
      return node;
    }
  case addD_mem_rule: {
      addD_memNode *node = new addD_memNode();
      return node;
    }
  case addD_mem_0_rule: {
      addD_mem_0Node *node = new addD_mem_0Node();
      return node;
    }
  case addD_imm_rule: {
      addD_immNode *node = new addD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addD_reg_reg_rule: {
      addD_reg_regNode *node = new addD_reg_regNode();
      return node;
    }
  case addD_reg_mem_rule: {
      addD_reg_memNode *node = new addD_reg_memNode();
      return node;
    }
  case addD_reg_mem_0_rule: {
      addD_reg_mem_0Node *node = new addD_reg_mem_0Node();
      return node;
    }
  case addD_reg_imm_rule: {
      addD_reg_immNode *node = new addD_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subF_reg_rule: {
      subF_regNode *node = new subF_regNode();
      return node;
    }
  case subF_mem_rule: {
      subF_memNode *node = new subF_memNode();
      return node;
    }
  case subF_imm_rule: {
      subF_immNode *node = new subF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subF_reg_reg_rule: {
      subF_reg_regNode *node = new subF_reg_regNode();
      return node;
    }
  case subF_reg_mem_rule: {
      subF_reg_memNode *node = new subF_reg_memNode();
      return node;
    }
  case subF_reg_imm_rule: {
      subF_reg_immNode *node = new subF_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subD_reg_rule: {
      subD_regNode *node = new subD_regNode();
      return node;
    }
  case subD_mem_rule: {
      subD_memNode *node = new subD_memNode();
      return node;
    }
  case subD_imm_rule: {
      subD_immNode *node = new subD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subD_reg_reg_rule: {
      subD_reg_regNode *node = new subD_reg_regNode();
      return node;
    }
  case subD_reg_mem_rule: {
      subD_reg_memNode *node = new subD_reg_memNode();
      return node;
    }
  case subD_reg_imm_rule: {
      subD_reg_immNode *node = new subD_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mulF_reg_rule: {
      mulF_regNode *node = new mulF_regNode();
      return node;
    }
  case mulF_mem_rule: {
      mulF_memNode *node = new mulF_memNode();
      return node;
    }
  case mulF_mem_0_rule: {
      mulF_mem_0Node *node = new mulF_mem_0Node();
      return node;
    }
  case mulF_imm_rule: {
      mulF_immNode *node = new mulF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mulF_reg_reg_rule: {
      mulF_reg_regNode *node = new mulF_reg_regNode();
      return node;
    }
  case mulF_reg_mem_rule: {
      mulF_reg_memNode *node = new mulF_reg_memNode();
      return node;
    }
  case mulF_reg_mem_0_rule: {
      mulF_reg_mem_0Node *node = new mulF_reg_mem_0Node();
      return node;
    }
  case mulF_reg_imm_rule: {
      mulF_reg_immNode *node = new mulF_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mulD_reg_rule: {
      mulD_regNode *node = new mulD_regNode();
      return node;
    }
  case mulD_mem_rule: {
      mulD_memNode *node = new mulD_memNode();
      return node;
    }
  case mulD_mem_0_rule: {
      mulD_mem_0Node *node = new mulD_mem_0Node();
      return node;
    }
  case mulD_imm_rule: {
      mulD_immNode *node = new mulD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mulD_reg_reg_rule: {
      mulD_reg_regNode *node = new mulD_reg_regNode();
      return node;
    }
  case mulD_reg_mem_rule: {
      mulD_reg_memNode *node = new mulD_reg_memNode();
      return node;
    }
  case mulD_reg_mem_0_rule: {
      mulD_reg_mem_0Node *node = new mulD_reg_mem_0Node();
      return node;
    }
  case mulD_reg_imm_rule: {
      mulD_reg_immNode *node = new mulD_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case divF_reg_rule: {
      divF_regNode *node = new divF_regNode();
      return node;
    }
  case divF_mem_rule: {
      divF_memNode *node = new divF_memNode();
      return node;
    }
  case divF_imm_rule: {
      divF_immNode *node = new divF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case divF_reg_reg_rule: {
      divF_reg_regNode *node = new divF_reg_regNode();
      return node;
    }
  case divF_reg_mem_rule: {
      divF_reg_memNode *node = new divF_reg_memNode();
      return node;
    }
  case divF_reg_imm_rule: {
      divF_reg_immNode *node = new divF_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case divD_reg_rule: {
      divD_regNode *node = new divD_regNode();
      return node;
    }
  case divD_mem_rule: {
      divD_memNode *node = new divD_memNode();
      return node;
    }
  case divD_imm_rule: {
      divD_immNode *node = new divD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case divD_reg_reg_rule: {
      divD_reg_regNode *node = new divD_reg_regNode();
      return node;
    }
  case divD_reg_mem_rule: {
      divD_reg_memNode *node = new divD_reg_memNode();
      return node;
    }
  case divD_reg_imm_rule: {
      divD_reg_immNode *node = new divD_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case absF_reg_rule: {
      absF_regNode *node = new absF_regNode();
      return node;
    }
  case absF_reg_reg_rule: {
      absF_reg_regNode *node = new absF_reg_regNode();
      return node;
    }
  case absD_reg_rule: {
      absD_regNode *node = new absD_regNode();
      return node;
    }
  case absD_reg_reg_rule: {
      absD_reg_regNode *node = new absD_reg_regNode();
      return node;
    }
  case negF_reg_rule: {
      negF_regNode *node = new negF_regNode();
      return node;
    }
  case negF_reg_reg_rule: {
      negF_reg_regNode *node = new negF_reg_regNode();
      return node;
    }
  case negD_reg_rule: {
      negD_regNode *node = new negD_regNode();
      return node;
    }
  case negD_reg_reg_rule: {
      negD_reg_regNode *node = new negD_reg_regNode();
      return node;
    }
  case sqrtF_reg_rule: {
      sqrtF_regNode *node = new sqrtF_regNode();
      return node;
    }
  case sqrtD_reg_rule: {
      sqrtD_regNode *node = new sqrtD_regNode();
      return node;
    }
  case convF2HF_reg_reg_rule: {
      convF2HF_reg_regNode *node = new convF2HF_reg_regNode();
      node->set_opnd_array(2, MachOperGenerator(VLREGF));
      return node;
    }
  case convF2HF_mem_reg_rule: {
      convF2HF_mem_regNode *node = new convF2HF_mem_regNode();
      node->set_opnd_array(3, MachOperGenerator(KREG));
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vconvF2HF_rule: {
      vconvF2HFNode *node = new vconvF2HFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vconvF2HF_mem_reg_rule: {
      vconvF2HF_mem_regNode *node = new vconvF2HF_mem_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case convHF2F_reg_reg_rule: {
      convHF2F_reg_regNode *node = new convHF2F_reg_regNode();
      return node;
    }
  case vconvHF2F_reg_mem_rule: {
      vconvHF2F_reg_memNode *node = new vconvHF2F_reg_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vconvHF2F_rule: {
      vconvHF2FNode *node = new vconvHF2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpret_mask_rule: {
      reinterpret_maskNode *node = new reinterpret_maskNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpret_mask_W2B_rule: {
      reinterpret_mask_W2BNode *node = new reinterpret_mask_W2BNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpret_mask_D2B_rule: {
      reinterpret_mask_D2BNode *node = new reinterpret_mask_D2BNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpret_mask_Q2B_rule: {
      reinterpret_mask_Q2BNode *node = new reinterpret_mask_Q2BNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpret_rule: {
      reinterpretNode *node = new reinterpretNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpret_expand_rule: {
      reinterpret_expandNode *node = new reinterpret_expandNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vreinterpret_expand4_rule: {
      vreinterpret_expand4Node *node = new vreinterpret_expand4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vreinterpret_expand_rule: {
      vreinterpret_expandNode *node = new vreinterpret_expandNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpret_shrink_rule: {
      reinterpret_shrinkNode *node = new reinterpret_shrinkNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case roundD_reg_rule: {
      roundD_regNode *node = new roundD_regNode();
      return node;
    }
  case roundD_imm_rule: {
      roundD_immNode *node = new roundD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vroundD_reg_rule: {
      vroundD_regNode *node = new vroundD_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vround8D_reg_rule: {
      vround8D_regNode *node = new vround8D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vroundD_mem_rule: {
      vroundD_memNode *node = new vroundD_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vround8D_mem_rule: {
      vround8D_memNode *node = new vround8D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case onspinwait_rule: {
      onspinwaitNode *node = new onspinwaitNode();
      return node;
    }
  case fmaD_reg_rule: {
      fmaD_regNode *node = new fmaD_regNode();
      return node;
    }
  case fmaF_reg_rule: {
      fmaF_regNode *node = new fmaF_regNode();
      return node;
    }
  case MoveVec2Leg_rule: {
      MoveVec2LegNode *node = new MoveVec2LegNode();
      return node;
    }
  case MoveLeg2Vec_rule: {
      MoveLeg2VecNode *node = new MoveLeg2VecNode();
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
  case gather_rule: {
      gatherNode *node = new gatherNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evgather_rule: {
      evgatherNode *node = new evgatherNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evgather_masked_rule: {
      evgather_maskedNode *node = new evgather_maskedNode();
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->set_opnd_array(6, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatter_rule: {
      scatterNode *node = new scatterNode();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case scatter_masked_rule: {
      scatter_maskedNode *node = new scatter_maskedNode();
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->set_opnd_array(6, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vReplB_reg_rule: {
      vReplB_regNode *node = new vReplB_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplB_mem_rule: {
      ReplB_memNode *node = new ReplB_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vReplS_reg_rule: {
      vReplS_regNode *node = new vReplS_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplS_mem_rule: {
      ReplS_memNode *node = new ReplS_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplI_reg_rule: {
      ReplI_regNode *node = new ReplI_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplI_mem_rule: {
      ReplI_memNode *node = new ReplI_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplI_imm_rule: {
      ReplI_immNode *node = new ReplI_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplI_zero_rule: {
      ReplI_zeroNode *node = new ReplI_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplI_M1_rule: {
      ReplI_M1Node *node = new ReplI_M1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplL_reg_rule: {
      ReplL_regNode *node = new ReplL_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplL_mem_rule: {
      ReplL_memNode *node = new ReplL_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplL_imm_rule: {
      ReplL_immNode *node = new ReplL_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplL_zero_rule: {
      ReplL_zeroNode *node = new ReplL_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplL_M1_rule: {
      ReplL_M1Node *node = new ReplL_M1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vReplF_reg_rule: {
      vReplF_regNode *node = new vReplF_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplF_reg_rule: {
      ReplF_regNode *node = new ReplF_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplF_mem_rule: {
      ReplF_memNode *node = new ReplF_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplF_imm_rule: {
      ReplF_immNode *node = new ReplF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplF_zero_rule: {
      ReplF_zeroNode *node = new ReplF_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vReplD_reg_rule: {
      vReplD_regNode *node = new vReplD_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplD_reg_rule: {
      ReplD_regNode *node = new ReplD_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplD_mem_rule: {
      ReplD_memNode *node = new ReplD_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplD_imm_rule: {
      ReplD_immNode *node = new ReplD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ReplD_zero_rule: {
      ReplD_zeroNode *node = new ReplD_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert_rule: {
      insertNode *node = new insertNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert32_rule: {
      insert32Node *node = new insert32Node();
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert64_rule: {
      insert64Node *node = new insert64Node();
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert2L_rule: {
      insert2LNode *node = new insert2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert4L_rule: {
      insert4LNode *node = new insert4LNode();
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert8L_rule: {
      insert8LNode *node = new insert8LNode();
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insertF_rule: {
      insertFNode *node = new insertFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vinsertF_rule: {
      vinsertFNode *node = new vinsertFNode();
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert2D_rule: {
      insert2DNode *node = new insert2DNode();
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert4D_rule: {
      insert4DNode *node = new insert4DNode();
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case insert8D_rule: {
      insert8DNode *node = new insert8DNode();
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionI_rule: {
      reductionINode *node = new reductionINode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionI_0_rule: {
      reductionI_0Node *node = new reductionI_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionI_1_rule: {
      reductionI_1Node *node = new reductionI_1Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionI_2_rule: {
      reductionI_2Node *node = new reductionI_2Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionI_3_rule: {
      reductionI_3Node *node = new reductionI_3Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionI_4_rule: {
      reductionI_4Node *node = new reductionI_4Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionI_5_rule: {
      reductionI_5Node *node = new reductionI_5Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_rule: {
      reductionLNode *node = new reductionLNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_0_rule: {
      reductionL_0Node *node = new reductionL_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_1_rule: {
      reductionL_1Node *node = new reductionL_1Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_2_rule: {
      reductionL_2Node *node = new reductionL_2Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_3_rule: {
      reductionL_3Node *node = new reductionL_3Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_4_rule: {
      reductionL_4Node *node = new reductionL_4Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_5_rule: {
      reductionL_5Node *node = new reductionL_5Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_avx512dq_rule: {
      reductionL_avx512dqNode *node = new reductionL_avx512dqNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_avx512dq_0_rule: {
      reductionL_avx512dq_0Node *node = new reductionL_avx512dq_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_avx512dq_1_rule: {
      reductionL_avx512dq_1Node *node = new reductionL_avx512dq_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_avx512dq_2_rule: {
      reductionL_avx512dq_2Node *node = new reductionL_avx512dq_2Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_avx512dq_3_rule: {
      reductionL_avx512dq_3Node *node = new reductionL_avx512dq_3Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_avx512dq_4_rule: {
      reductionL_avx512dq_4Node *node = new reductionL_avx512dq_4Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionL_avx512dq_5_rule: {
      reductionL_avx512dq_5Node *node = new reductionL_avx512dq_5Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionF128_rule: {
      reductionF128Node *node = new reductionF128Node();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionF128_0_rule: {
      reductionF128_0Node *node = new reductionF128_0Node();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduction8F_rule: {
      reduction8FNode *node = new reduction8FNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduction8F_0_rule: {
      reduction8F_0Node *node = new reduction8F_0Node();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduction16F_rule: {
      reduction16FNode *node = new reduction16FNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduction16F_0_rule: {
      reduction16F_0Node *node = new reduction16F_0Node();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduction2D_rule: {
      reduction2DNode *node = new reduction2DNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduction2D_0_rule: {
      reduction2D_0Node *node = new reduction2D_0Node();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduction4D_rule: {
      reduction4DNode *node = new reduction4DNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduction4D_0_rule: {
      reduction4D_0Node *node = new reduction4D_0Node();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduction8D_rule: {
      reduction8DNode *node = new reduction8DNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reduction8D_0_rule: {
      reduction8D_0Node *node = new reduction8D_0Node();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_rule: {
      reductionBNode *node = new reductionBNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_0_rule: {
      reductionB_0Node *node = new reductionB_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_1_rule: {
      reductionB_1Node *node = new reductionB_1Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_2_rule: {
      reductionB_2Node *node = new reductionB_2Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_3_rule: {
      reductionB_3Node *node = new reductionB_3Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_4_rule: {
      reductionB_4Node *node = new reductionB_4Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_avx512bw_rule: {
      reductionB_avx512bwNode *node = new reductionB_avx512bwNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_avx512bw_0_rule: {
      reductionB_avx512bw_0Node *node = new reductionB_avx512bw_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_avx512bw_1_rule: {
      reductionB_avx512bw_1Node *node = new reductionB_avx512bw_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_avx512bw_2_rule: {
      reductionB_avx512bw_2Node *node = new reductionB_avx512bw_2Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_avx512bw_3_rule: {
      reductionB_avx512bw_3Node *node = new reductionB_avx512bw_3Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionB_avx512bw_4_rule: {
      reductionB_avx512bw_4Node *node = new reductionB_avx512bw_4Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionS_rule: {
      reductionSNode *node = new reductionSNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionS_0_rule: {
      reductionS_0Node *node = new reductionS_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionS_1_rule: {
      reductionS_1Node *node = new reductionS_1Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionS_2_rule: {
      reductionS_2Node *node = new reductionS_2Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionS_3_rule: {
      reductionS_3Node *node = new reductionS_3Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionS_4_rule: {
      reductionS_4Node *node = new reductionS_4Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reductionS_5_rule: {
      reductionS_5Node *node = new reductionS_5Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mul_reductionB_rule: {
      mul_reductionBNode *node = new mul_reductionBNode();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mul_reduction64B_rule: {
      mul_reduction64BNode *node = new mul_reduction64BNode();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reduction2F_rule: {
      minmax_reduction2FNode *node = new minmax_reduction2FNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reduction2F_0_rule: {
      minmax_reduction2F_0Node *node = new minmax_reduction2F_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reductionF_rule: {
      minmax_reductionFNode *node = new minmax_reductionFNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->set_opnd_array(8, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reductionF_0_rule: {
      minmax_reductionF_0Node *node = new minmax_reductionF_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->set_opnd_array(8, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reduction2F_av_rule: {
      minmax_reduction2F_avNode *node = new minmax_reduction2F_avNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reduction2F_av_0_rule: {
      minmax_reduction2F_av_0Node *node = new minmax_reduction2F_av_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reductionF_av_rule: {
      minmax_reductionF_avNode *node = new minmax_reductionF_avNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->set_opnd_array(8, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reductionF_av_0_rule: {
      minmax_reductionF_av_0Node *node = new minmax_reductionF_av_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->set_opnd_array(8, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reduction2D_rule: {
      minmax_reduction2DNode *node = new minmax_reduction2DNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reduction2D_0_rule: {
      minmax_reduction2D_0Node *node = new minmax_reduction2D_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reductionD_rule: {
      minmax_reductionDNode *node = new minmax_reductionDNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->set_opnd_array(8, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reductionD_0_rule: {
      minmax_reductionD_0Node *node = new minmax_reductionD_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->set_opnd_array(8, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reduction2D_av_rule: {
      minmax_reduction2D_avNode *node = new minmax_reduction2D_avNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reduction2D_av_0_rule: {
      minmax_reduction2D_av_0Node *node = new minmax_reduction2D_av_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reductionD_av_rule: {
      minmax_reductionD_avNode *node = new minmax_reductionD_avNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->set_opnd_array(8, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reductionD_av_0_rule: {
      minmax_reductionD_av_0Node *node = new minmax_reductionD_av_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGREGD));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->set_opnd_array(6, MachOperGenerator(LEGVEC));
      node->set_opnd_array(7, MachOperGenerator(LEGVEC));
      node->set_opnd_array(8, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddB_rule: {
      vaddBNode *node = new vaddBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddB_reg_rule: {
      vaddB_regNode *node = new vaddB_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddB_mem_rule: {
      vaddB_memNode *node = new vaddB_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddB_mem_0_rule: {
      vaddB_mem_0Node *node = new vaddB_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddS_rule: {
      vaddSNode *node = new vaddSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddS_reg_rule: {
      vaddS_regNode *node = new vaddS_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddS_mem_rule: {
      vaddS_memNode *node = new vaddS_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddS_mem_0_rule: {
      vaddS_mem_0Node *node = new vaddS_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddI_rule: {
      vaddINode *node = new vaddINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddI_reg_rule: {
      vaddI_regNode *node = new vaddI_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddI_mem_rule: {
      vaddI_memNode *node = new vaddI_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddI_mem_0_rule: {
      vaddI_mem_0Node *node = new vaddI_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddL_rule: {
      vaddLNode *node = new vaddLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddL_reg_rule: {
      vaddL_regNode *node = new vaddL_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddL_mem_rule: {
      vaddL_memNode *node = new vaddL_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddL_mem_0_rule: {
      vaddL_mem_0Node *node = new vaddL_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddF_rule: {
      vaddFNode *node = new vaddFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddF_reg_rule: {
      vaddF_regNode *node = new vaddF_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddF_mem_rule: {
      vaddF_memNode *node = new vaddF_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddF_mem_0_rule: {
      vaddF_mem_0Node *node = new vaddF_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddD_rule: {
      vaddDNode *node = new vaddDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddD_reg_rule: {
      vaddD_regNode *node = new vaddD_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddD_mem_rule: {
      vaddD_memNode *node = new vaddD_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vaddD_mem_0_rule: {
      vaddD_mem_0Node *node = new vaddD_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubB_rule: {
      vsubBNode *node = new vsubBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubB_reg_rule: {
      vsubB_regNode *node = new vsubB_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubB_mem_rule: {
      vsubB_memNode *node = new vsubB_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubS_rule: {
      vsubSNode *node = new vsubSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubS_reg_rule: {
      vsubS_regNode *node = new vsubS_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubS_mem_rule: {
      vsubS_memNode *node = new vsubS_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubI_rule: {
      vsubINode *node = new vsubINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubI_reg_rule: {
      vsubI_regNode *node = new vsubI_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubI_mem_rule: {
      vsubI_memNode *node = new vsubI_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubL_rule: {
      vsubLNode *node = new vsubLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubL_reg_rule: {
      vsubL_regNode *node = new vsubL_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubL_mem_rule: {
      vsubL_memNode *node = new vsubL_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubF_rule: {
      vsubFNode *node = new vsubFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubF_reg_rule: {
      vsubF_regNode *node = new vsubF_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubF_mem_rule: {
      vsubF_memNode *node = new vsubF_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubD_rule: {
      vsubDNode *node = new vsubDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubD_reg_rule: {
      vsubD_regNode *node = new vsubD_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsubD_mem_rule: {
      vsubD_memNode *node = new vsubD_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8B_rule: {
      vmul8BNode *node = new vmul8BNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulB_rule: {
      vmulBNode *node = new vmulBNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulB_reg_rule: {
      vmulB_regNode *node = new vmulB_regNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulS_rule: {
      vmulSNode *node = new vmulSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulS_reg_rule: {
      vmulS_regNode *node = new vmulS_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulS_mem_rule: {
      vmulS_memNode *node = new vmulS_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulS_mem_0_rule: {
      vmulS_mem_0Node *node = new vmulS_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulI_rule: {
      vmulINode *node = new vmulINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulI_reg_rule: {
      vmulI_regNode *node = new vmulI_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulI_mem_rule: {
      vmulI_memNode *node = new vmulI_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulI_mem_0_rule: {
      vmulI_mem_0Node *node = new vmulI_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evmulL_reg_rule: {
      evmulL_regNode *node = new evmulL_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evmulL_mem_rule: {
      evmulL_memNode *node = new evmulL_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evmulL_mem_0_rule: {
      evmulL_mem_0Node *node = new evmulL_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulL_rule: {
      vmulLNode *node = new vmulLNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulL_reg_rule: {
      vmulL_regNode *node = new vmulL_regNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulF_rule: {
      vmulFNode *node = new vmulFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulF_reg_rule: {
      vmulF_regNode *node = new vmulF_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulF_mem_rule: {
      vmulF_memNode *node = new vmulF_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulF_mem_0_rule: {
      vmulF_mem_0Node *node = new vmulF_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulD_rule: {
      vmulDNode *node = new vmulDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulD_reg_rule: {
      vmulD_regNode *node = new vmulD_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulD_mem_rule: {
      vmulD_memNode *node = new vmulD_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmulD_mem_0_rule: {
      vmulD_mem_0Node *node = new vmulD_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivF_rule: {
      vdivFNode *node = new vdivFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivF_reg_rule: {
      vdivF_regNode *node = new vdivF_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivF_mem_rule: {
      vdivF_memNode *node = new vdivF_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivD_rule: {
      vdivDNode *node = new vdivDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivD_reg_rule: {
      vdivD_regNode *node = new vdivD_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdivD_mem_rule: {
      vdivD_memNode *node = new vdivD_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reg_sse_rule: {
      minmax_reg_sseNode *node = new minmax_reg_sseNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmax_reg_sse_0_rule: {
      minmax_reg_sse_0Node *node = new minmax_reg_sse_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vminmax_reg_rule: {
      vminmax_regNode *node = new vminmax_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vminmax_reg_0_rule: {
      vminmax_reg_0Node *node = new vminmax_reg_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmaxL_reg_sse_rule: {
      minmaxL_reg_sseNode *node = new minmaxL_reg_sseNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(RXMM0));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmaxL_reg_sse_0_rule: {
      minmaxL_reg_sse_0Node *node = new minmaxL_reg_sse_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(RXMM0));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vminmaxL_reg_avx_rule: {
      vminmaxL_reg_avxNode *node = new vminmaxL_reg_avxNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vminmaxL_reg_avx_0_rule: {
      vminmaxL_reg_avx_0Node *node = new vminmaxL_reg_avx_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vminmaxL_reg_evex_rule: {
      vminmaxL_reg_evexNode *node = new vminmaxL_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vminmaxL_reg_evex_0_rule: {
      vminmaxL_reg_evex_0Node *node = new vminmaxL_reg_evex_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmaxFP_reg_rule: {
      minmaxFP_regNode *node = new minmaxFP_regNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case minmaxFP_reg_0_rule: {
      minmaxFP_reg_0Node *node = new minmaxFP_reg_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evminmaxFP_reg_eavx_rule: {
      evminmaxFP_reg_eavxNode *node = new evminmaxFP_reg_eavxNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evminmaxFP_reg_eavx_0_rule: {
      evminmaxFP_reg_eavx_0Node *node = new evminmaxFP_reg_eavx_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case signumF_reg_rule: {
      signumF_regNode *node = new signumF_regNode();
      return node;
    }
  case signumD_reg_rule: {
      signumD_regNode *node = new signumD_regNode();
      return node;
    }
  case signumV_reg_avx_rule: {
      signumV_reg_avxNode *node = new signumV_reg_avxNode();
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case signumV_reg_avx_0_rule: {
      signumV_reg_avx_0Node *node = new signumV_reg_avx_0Node();
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case signumV_reg_evex_rule: {
      signumV_reg_evexNode *node = new signumV_reg_evexNode();
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case signumV_reg_evex_0_rule: {
      signumV_reg_evex_0Node *node = new signumV_reg_evex_0Node();
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case copySignF_reg_rule: {
      copySignF_regNode *node = new copySignF_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      return node;
    }
  case copySignD_imm_rule: {
      copySignD_immNode *node = new copySignD_immNode();
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(RREGL));
      return node;
    }
  case compressBitsI_reg_rule: {
      compressBitsI_regNode *node = new compressBitsI_regNode();
      return node;
    }
  case expandBitsI_reg_rule: {
      expandBitsI_regNode *node = new expandBitsI_regNode();
      return node;
    }
  case compressBitsI_mem_rule: {
      compressBitsI_memNode *node = new compressBitsI_memNode();
      return node;
    }
  case expandBitsI_mem_rule: {
      expandBitsI_memNode *node = new expandBitsI_memNode();
      return node;
    }
  case vsqrtF_reg_rule: {
      vsqrtF_regNode *node = new vsqrtF_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrtF_mem_rule: {
      vsqrtF_memNode *node = new vsqrtF_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrtD_reg_rule: {
      vsqrtD_regNode *node = new vsqrtD_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrtD_mem_rule: {
      vsqrtD_memNode *node = new vsqrtD_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcnt_rule: {
      vshiftcntNode *node = new vshiftcntNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcnt_0_rule: {
      vshiftcnt_0Node *node = new vshiftcnt_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftB_rule: {
      vshiftBNode *node = new vshiftBNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftB_0_rule: {
      vshiftB_0Node *node = new vshiftB_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftB_1_rule: {
      vshiftB_1Node *node = new vshiftB_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16B_rule: {
      vshift16BNode *node = new vshift16BNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16B_0_rule: {
      vshift16B_0Node *node = new vshift16B_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16B_1_rule: {
      vshift16B_1Node *node = new vshift16B_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16B_avx_rule: {
      vshift16B_avxNode *node = new vshift16B_avxNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16B_avx_0_rule: {
      vshift16B_avx_0Node *node = new vshift16B_avx_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16B_avx_1_rule: {
      vshift16B_avx_1Node *node = new vshift16B_avx_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift32B_avx_rule: {
      vshift32B_avxNode *node = new vshift32B_avxNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift32B_avx_0_rule: {
      vshift32B_avx_0Node *node = new vshift32B_avx_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift32B_avx_1_rule: {
      vshift32B_avx_1Node *node = new vshift32B_avx_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift64B_avx_rule: {
      vshift64B_avxNode *node = new vshift64B_avxNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift64B_avx_0_rule: {
      vshift64B_avx_0Node *node = new vshift64B_avx_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift64B_avx_1_rule: {
      vshift64B_avx_1Node *node = new vshift64B_avx_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftS_rule: {
      vshiftSNode *node = new vshiftSNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftS_0_rule: {
      vshiftS_0Node *node = new vshiftS_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftS_1_rule: {
      vshiftS_1Node *node = new vshiftS_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftI_rule: {
      vshiftINode *node = new vshiftINode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftI_0_rule: {
      vshiftI_0Node *node = new vshiftI_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftI_1_rule: {
      vshiftI_1Node *node = new vshiftI_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftI_imm_rule: {
      vshiftI_immNode *node = new vshiftI_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftI_imm_0_rule: {
      vshiftI_imm_0Node *node = new vshiftI_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftI_imm_1_rule: {
      vshiftI_imm_1Node *node = new vshiftI_imm_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftL_rule: {
      vshiftLNode *node = new vshiftLNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftL_0_rule: {
      vshiftL_0Node *node = new vshiftL_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftL_imm_rule: {
      vshiftL_immNode *node = new vshiftL_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftL_imm_0_rule: {
      vshiftL_imm_0Node *node = new vshiftL_imm_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftL_arith_reg_rule: {
      vshiftL_arith_regNode *node = new vshiftL_arith_regNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftL_arith_reg_evex_rule: {
      vshiftL_arith_reg_evexNode *node = new vshiftL_arith_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift8B_var_nobw_rule: {
      vshift8B_var_nobwNode *node = new vshift8B_var_nobwNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift8B_var_nobw_0_rule: {
      vshift8B_var_nobw_0Node *node = new vshift8B_var_nobw_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift8B_var_nobw_1_rule: {
      vshift8B_var_nobw_1Node *node = new vshift8B_var_nobw_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16B_var_nobw_rule: {
      vshift16B_var_nobwNode *node = new vshift16B_var_nobwNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16B_var_nobw_0_rule: {
      vshift16B_var_nobw_0Node *node = new vshift16B_var_nobw_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16B_var_nobw_1_rule: {
      vshift16B_var_nobw_1Node *node = new vshift16B_var_nobw_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift32B_var_nobw_rule: {
      vshift32B_var_nobwNode *node = new vshift32B_var_nobwNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(VEC));
      node->set_opnd_array(7, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift32B_var_nobw_0_rule: {
      vshift32B_var_nobw_0Node *node = new vshift32B_var_nobw_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(VEC));
      node->set_opnd_array(7, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift32B_var_nobw_1_rule: {
      vshift32B_var_nobw_1Node *node = new vshift32B_var_nobw_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(VEC));
      node->set_opnd_array(7, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftB_var_evex_bw_rule: {
      vshiftB_var_evex_bwNode *node = new vshiftB_var_evex_bwNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftB_var_evex_bw_0_rule: {
      vshiftB_var_evex_bw_0Node *node = new vshiftB_var_evex_bw_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftB_var_evex_bw_1_rule: {
      vshiftB_var_evex_bw_1Node *node = new vshiftB_var_evex_bw_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift64B_var_evex_bw_rule: {
      vshift64B_var_evex_bwNode *node = new vshift64B_var_evex_bwNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift64B_var_evex_bw_0_rule: {
      vshift64B_var_evex_bw_0Node *node = new vshift64B_var_evex_bw_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift64B_var_evex_bw_1_rule: {
      vshift64B_var_evex_bw_1Node *node = new vshift64B_var_evex_bw_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift8S_var_nobw_rule: {
      vshift8S_var_nobwNode *node = new vshift8S_var_nobwNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift8S_var_nobw_0_rule: {
      vshift8S_var_nobw_0Node *node = new vshift8S_var_nobw_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift8S_var_nobw_1_rule: {
      vshift8S_var_nobw_1Node *node = new vshift8S_var_nobw_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16S_var_nobw_rule: {
      vshift16S_var_nobwNode *node = new vshift16S_var_nobwNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16S_var_nobw_0_rule: {
      vshift16S_var_nobw_0Node *node = new vshift16S_var_nobw_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16S_var_nobw_1_rule: {
      vshift16S_var_nobw_1Node *node = new vshift16S_var_nobw_1Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16S_var_evex_bw_rule: {
      vshift16S_var_evex_bwNode *node = new vshift16S_var_evex_bwNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16S_var_evex_bw_0_rule: {
      vshift16S_var_evex_bw_0Node *node = new vshift16S_var_evex_bw_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshift16S_var_evex_bw_1_rule: {
      vshift16S_var_evex_bw_1Node *node = new vshift16S_var_evex_bw_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftI_var_rule: {
      vshiftI_varNode *node = new vshiftI_varNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftI_var_0_rule: {
      vshiftI_var_0Node *node = new vshiftI_var_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftI_var_1_rule: {
      vshiftI_var_1Node *node = new vshiftI_var_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftL_var_rule: {
      vshiftL_varNode *node = new vshiftL_varNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftL_var_0_rule: {
      vshiftL_var_0Node *node = new vshiftL_var_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftL_arith_var_rule: {
      vshiftL_arith_varNode *node = new vshiftL_arith_varNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftL_arith_var_evex_rule: {
      vshiftL_arith_var_evexNode *node = new vshiftL_arith_var_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_rule: {
      vandNode *node = new vandNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_reg_rule: {
      vand_regNode *node = new vand_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_mem_rule: {
      vand_memNode *node = new vand_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_mem_0_rule: {
      vand_mem_0Node *node = new vand_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor_rule: {
      vorNode *node = new vorNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor_reg_rule: {
      vor_regNode *node = new vor_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor_mem_rule: {
      vor_memNode *node = new vor_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor_mem_0_rule: {
      vor_mem_0Node *node = new vor_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor_rule: {
      vxorNode *node = new vxorNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor_reg_rule: {
      vxor_regNode *node = new vxor_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor_mem_rule: {
      vxor_memNode *node = new vxor_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor_mem_0_rule: {
      vxor_mem_0Node *node = new vxor_mem_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcastBtoX_rule: {
      vcastBtoXNode *node = new vcastBtoXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castStoX_rule: {
      castStoXNode *node = new castStoXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcastStoX_rule: {
      vcastStoXNode *node = new vcastStoXNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcastStoX_evex_rule: {
      vcastStoX_evexNode *node = new vcastStoX_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castItoX_rule: {
      castItoXNode *node = new castItoXNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcastItoX_rule: {
      vcastItoXNode *node = new vcastItoXNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcastItoX_evex_rule: {
      vcastItoX_evexNode *node = new vcastItoX_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcastLtoBS_rule: {
      vcastLtoBSNode *node = new vcastLtoBSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcastLtoX_evex_rule: {
      vcastLtoX_evexNode *node = new vcastLtoX_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcastFtoD_reg_rule: {
      vcastFtoD_regNode *node = new vcastFtoD_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castFtoX_reg_avx_rule: {
      castFtoX_reg_avxNode *node = new castFtoX_reg_avxNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castFtoX_reg_evex_rule: {
      castFtoX_reg_evexNode *node = new castFtoX_reg_evexNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcastDtoF_reg_rule: {
      vcastDtoF_regNode *node = new vcastDtoF_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castDtoX_reg_avx_rule: {
      castDtoX_reg_avxNode *node = new castDtoX_reg_avxNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(VEC));
      node->set_opnd_array(7, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castDtoX_reg_evex_rule: {
      castDtoX_reg_evexNode *node = new castDtoX_reg_evexNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vucast_rule: {
      vucastNode *node = new vucastNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vucast_0_rule: {
      vucast_0Node *node = new vucast_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vucast_1_rule: {
      vucast_1Node *node = new vucast_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vround_float_avx_rule: {
      vround_float_avxNode *node = new vround_float_avxNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(RREGP));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(VEC));
      node->set_opnd_array(7, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vround_float_evex_rule: {
      vround_float_evexNode *node = new vround_float_evexNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(RREGP));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      node->set_opnd_array(7, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vround_reg_evex_rule: {
      vround_reg_evexNode *node = new vround_reg_evexNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(RREGP));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      node->set_opnd_array(7, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcmpFD_rule: {
      vcmpFDNode *node = new vcmpFDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evcmpFD64_rule: {
      evcmpFD64Node *node = new evcmpFD64Node();
      node->set_opnd_array(4, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evcmpFD_rule: {
      evcmpFDNode *node = new evcmpFDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcmp_direct_rule: {
      vcmp_directNode *node = new vcmp_directNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcmp_negate_rule: {
      vcmp_negateNode *node = new vcmp_negateNode();
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcmpu_rule: {
      vcmpuNode *node = new vcmpuNode();
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcmp64_rule: {
      vcmp64Node *node = new vcmp64Node();
      node->set_opnd_array(4, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evcmp_rule: {
      evcmpNode *node = new evcmpNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractI_rule: {
      extractINode *node = new extractINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractI_0_rule: {
      extractI_0Node *node = new extractI_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractI_1_rule: {
      extractI_1Node *node = new extractI_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vextractI_rule: {
      vextractINode *node = new vextractINode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vextractI_0_rule: {
      vextractI_0Node *node = new vextractI_0Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vextractI_1_rule: {
      vextractI_1Node *node = new vextractI_1Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractL_rule: {
      extractLNode *node = new extractLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vextractL_rule: {
      vextractLNode *node = new vextractLNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractF_rule: {
      extractFNode *node = new extractFNode();
      node->set_opnd_array(3, MachOperGenerator(LEGREGF));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vextractF_rule: {
      vextractFNode *node = new vextractFNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case extractD_rule: {
      extractDNode *node = new extractDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vextractD_rule: {
      vextractDNode *node = new vextractDNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case blendvp_rule: {
      blendvpNode *node = new blendvpNode();
      node->set_opnd_array(4, MachOperGenerator(RXMM0));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vblendvpI_rule: {
      vblendvpINode *node = new vblendvpINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vblendvpFD_rule: {
      vblendvpFDNode *node = new vblendvpFDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vblendvp_rule: {
      vblendvpNode *node = new vblendvpNode();
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evblendvp64_rule: {
      evblendvp64Node *node = new evblendvp64Node();
      node->set_opnd_array(4, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evblendvp64_masked_rule: {
      evblendvp64_maskedNode *node = new evblendvp64_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsB_reg_rule: {
      vabsB_regNode *node = new vabsB_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsS_reg_rule: {
      vabsS_regNode *node = new vabsS_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsI_reg_rule: {
      vabsI_regNode *node = new vabsI_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsL_reg_rule: {
      vabsL_regNode *node = new vabsL_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsnegF_rule: {
      vabsnegFNode *node = new vabsnegFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsnegF_0_rule: {
      vabsnegF_0Node *node = new vabsnegF_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsneg4F_rule: {
      vabsneg4FNode *node = new vabsneg4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsneg4F_0_rule: {
      vabsneg4F_0Node *node = new vabsneg4F_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsnegD_rule: {
      vabsnegDNode *node = new vabsnegDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabsnegD_0_rule: {
      vabsnegD_0Node *node = new vabsnegD_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vptest_lt16_rule: {
      vptest_lt16Node *node = new vptest_lt16Node();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vptest_ge16_rule: {
      vptest_ge16Node *node = new vptest_ge16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ktest_alltrue_le8_rule: {
      ktest_alltrue_le8Node *node = new ktest_alltrue_le8Node();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ktest_anytrue_le8_rule: {
      ktest_anytrue_le8Node *node = new ktest_anytrue_le8Node();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case ktest_ge8_rule: {
      ktest_ge8Node *node = new ktest_ge8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadMask_rule: {
      loadMaskNode *node = new loadMaskNode();
      node->set_opnd_array(2, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadMask64_rule: {
      loadMask64Node *node = new loadMask64Node();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadMask_evex_rule: {
      loadMask_evexNode *node = new loadMask_evexNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoreMask1B_rule: {
      vstoreMask1BNode *node = new vstoreMask1BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoreMask2B_rule: {
      vstoreMask2BNode *node = new vstoreMask2BNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoreMask4B_rule: {
      vstoreMask4BNode *node = new vstoreMask4BNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeMask8B_rule: {
      storeMask8BNode *node = new storeMask8BNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeMask8B_avx_rule: {
      storeMask8B_avxNode *node = new storeMask8B_avxNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoreMask4B_evex_novectmask_rule: {
      vstoreMask4B_evex_novectmaskNode *node = new vstoreMask4B_evex_novectmaskNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoreMask8B_evex_novectmask_rule: {
      vstoreMask8B_evex_novectmaskNode *node = new vstoreMask8B_evex_novectmaskNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoreMask_evex_vectmask_rule: {
      vstoreMask_evex_vectmaskNode *node = new vstoreMask_evex_vectmaskNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vstoreMask_evex_rule: {
      vstoreMask_evexNode *node = new vstoreMask_evexNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_evex_rule: {
      vmaskcast_evexNode *node = new vmaskcast_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_rule: {
      vmaskcastNode *node = new vmaskcastNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaskcast_avx_rule: {
      vmaskcast_avxNode *node = new vmaskcast_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadIotaIndices_rule: {
      loadIotaIndicesNode *node = new loadIotaIndicesNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case VectorPopulateIndex_rule: {
      VectorPopulateIndexNode *node = new VectorPopulateIndexNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case VectorPopulateLIndex_rule: {
      VectorPopulateLIndexNode *node = new VectorPopulateLIndexNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadShuffleB_rule: {
      loadShuffleBNode *node = new loadShuffleBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeB_rule: {
      rearrangeBNode *node = new rearrangeBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeB_avx_rule: {
      rearrangeB_avxNode *node = new rearrangeB_avxNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeB_evex_rule: {
      rearrangeB_evexNode *node = new rearrangeB_evexNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(VEC));
      node->set_opnd_array(7, MachOperGenerator(KREG));
      node->set_opnd_array(8, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeB_evex_vbmi_rule: {
      rearrangeB_evex_vbmiNode *node = new rearrangeB_evex_vbmiNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadShuffleS_rule: {
      loadShuffleSNode *node = new loadShuffleSNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeS_rule: {
      rearrangeSNode *node = new rearrangeSNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeS_avx_rule: {
      rearrangeS_avxNode *node = new rearrangeS_avxNode();
      node->set_opnd_array(3, MachOperGenerator(LEGVEC));
      node->set_opnd_array(4, MachOperGenerator(LEGVEC));
      node->set_opnd_array(5, MachOperGenerator(LEGVEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadShuffleS_evex_rule: {
      loadShuffleS_evexNode *node = new loadShuffleS_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeS_evex_rule: {
      rearrangeS_evexNode *node = new rearrangeS_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadShuffleI_rule: {
      loadShuffleINode *node = new loadShuffleINode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeI_rule: {
      rearrangeINode *node = new rearrangeINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadShuffleI_avx_rule: {
      loadShuffleI_avxNode *node = new loadShuffleI_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeI_avx_rule: {
      rearrangeI_avxNode *node = new rearrangeI_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadShuffleL_rule: {
      loadShuffleLNode *node = new loadShuffleLNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeL_rule: {
      rearrangeLNode *node = new rearrangeLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadShuffleL_evex_rule: {
      loadShuffleL_evexNode *node = new loadShuffleL_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rearrangeL_evex_rule: {
      rearrangeL_evexNode *node = new rearrangeL_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmaF_reg_rule: {
      vfmaF_regNode *node = new vfmaF_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmaF_mem_rule: {
      vfmaF_memNode *node = new vfmaF_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmaD_reg_rule: {
      vfmaD_regNode *node = new vfmaD_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfmaD_mem_rule: {
      vfmaD_memNode *node = new vfmaD_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmuladdS2I_reg_sse_rule: {
      vmuladdS2I_reg_sseNode *node = new vmuladdS2I_reg_sseNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmuladdS2I_reg_avx_rule: {
      vmuladdS2I_reg_avxNode *node = new vmuladdS2I_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmuladdaddS2I_reg_rule: {
      vmuladdaddS2I_regNode *node = new vmuladdaddS2I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmuladdaddS2I_reg_0_rule: {
      vmuladdaddS2I_reg_0Node *node = new vmuladdaddS2I_reg_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcount_integral_reg_evex_rule: {
      vpopcount_integral_reg_evexNode *node = new vpopcount_integral_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcount_integral_reg_evex_0_rule: {
      vpopcount_integral_reg_evex_0Node *node = new vpopcount_integral_reg_evex_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcount_integral_reg_evex_masked_rule: {
      vpopcount_integral_reg_evex_maskedNode *node = new vpopcount_integral_reg_evex_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcount_integral_reg_evex_masked_0_rule: {
      vpopcount_integral_reg_evex_masked_0Node *node = new vpopcount_integral_reg_evex_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcount_avx_reg_rule: {
      vpopcount_avx_regNode *node = new vpopcount_avx_regNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcount_avx_reg_0_rule: {
      vpopcount_avx_reg_0Node *node = new vpopcount_avx_reg_0Node();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcount_trailing_zeros_reg_evex_rule: {
      vcount_trailing_zeros_reg_evexNode *node = new vcount_trailing_zeros_reg_evexNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcount_trailing_zeros_short_reg_evex_rule: {
      vcount_trailing_zeros_short_reg_evexNode *node = new vcount_trailing_zeros_short_reg_evexNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcount_trailing_zeros_byte_reg_evex_rule: {
      vcount_trailing_zeros_byte_reg_evexNode *node = new vcount_trailing_zeros_byte_reg_evexNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(VEC));
      node->set_opnd_array(7, MachOperGenerator(KREG));
      node->set_opnd_array(8, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcount_trailing_zeros_reg_avx_rule: {
      vcount_trailing_zeros_reg_avxNode *node = new vcount_trailing_zeros_reg_avxNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpternlog_rule: {
      vpternlogNode *node = new vpternlogNode();
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpternlog_mem_rule: {
      vpternlog_memNode *node = new vpternlog_memNode();
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vprotate_immI8_rule: {
      vprotate_immI8Node *node = new vprotate_immI8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vprotate_immI8_0_rule: {
      vprotate_immI8_0Node *node = new vprotate_immI8_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vprorate_rule: {
      vprorateNode *node = new vprorateNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vprorate_0_rule: {
      vprorate_0Node *node = new vprorate_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmasked_load_avx_non_subword_rule: {
      vmasked_load_avx_non_subwordNode *node = new vmasked_load_avx_non_subwordNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmasked_load_evex_rule: {
      vmasked_load_evexNode *node = new vmasked_load_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmasked_store_avx_non_subword_rule: {
      vmasked_store_avx_non_subwordNode *node = new vmasked_store_avx_non_subwordNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmasked_store_evex_rule: {
      vmasked_store_evexNode *node = new vmasked_store_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case verify_vector_alignment_rule: {
      verify_vector_alignmentNode *node = new verify_vector_alignmentNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_cmp_node_rule: {
      vmask_cmp_nodeNode *node = new vmask_cmp_nodeNode();
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_gen_rule: {
      vmask_genNode *node = new vmask_genNode();
      node->set_opnd_array(2, MachOperGenerator(RREGL));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_gen_imm_rule: {
      vmask_gen_immNode *node = new vmask_gen_immNode();
      node->set_opnd_array(2, MachOperGenerator(RREGL));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmask_tolong_evex_rule: {
      vmask_tolong_evexNode *node = new vmask_tolong_evexNode();
      node->set_opnd_array(2, MachOperGenerator(RREGL));
      return node;
    }
  case vmask_tolong_bool_rule: {
      vmask_tolong_boolNode *node = new vmask_tolong_boolNode();
      node->set_opnd_array(2, MachOperGenerator(RREGL));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      return node;
    }
  case vmask_tolong_avx_rule: {
      vmask_tolong_avxNode *node = new vmask_tolong_avxNode();
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      return node;
    }
  case vmask_truecount_evex_rule: {
      vmask_truecount_evexNode *node = new vmask_truecount_evexNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      return node;
    }
  case vmask_truecount_bool_rule: {
      vmask_truecount_boolNode *node = new vmask_truecount_boolNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      return node;
    }
  case vmask_truecount_avx_rule: {
      vmask_truecount_avxNode *node = new vmask_truecount_avxNode();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      return node;
    }
  case vmask_first_or_last_true_evex_rule: {
      vmask_first_or_last_true_evexNode *node = new vmask_first_or_last_true_evexNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      return node;
    }
  case vmask_first_or_last_true_evex_0_rule: {
      vmask_first_or_last_true_evex_0Node *node = new vmask_first_or_last_true_evex_0Node();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      return node;
    }
  case vmask_first_or_last_true_bool_rule: {
      vmask_first_or_last_true_boolNode *node = new vmask_first_or_last_true_boolNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      return node;
    }
  case vmask_first_or_last_true_bool_0_rule: {
      vmask_first_or_last_true_bool_0Node *node = new vmask_first_or_last_true_bool_0Node();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      return node;
    }
  case vmask_first_or_last_true_avx_rule: {
      vmask_first_or_last_true_avxNode *node = new vmask_first_or_last_true_avxNode();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      return node;
    }
  case vmask_first_or_last_true_avx_0_rule: {
      vmask_first_or_last_true_avx_0Node *node = new vmask_first_or_last_true_avx_0Node();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      return node;
    }
  case vcompress_reg_avx_rule: {
      vcompress_reg_avxNode *node = new vcompress_reg_avxNode();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      node->set_opnd_array(5, MachOperGenerator(RREGL));
      node->set_opnd_array(6, MachOperGenerator(VEC));
      node->set_opnd_array(7, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcompress_reg_avx_0_rule: {
      vcompress_reg_avx_0Node *node = new vcompress_reg_avx_0Node();
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      node->set_opnd_array(5, MachOperGenerator(RREGL));
      node->set_opnd_array(6, MachOperGenerator(VEC));
      node->set_opnd_array(7, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcompress_expand_reg_evex_rule: {
      vcompress_expand_reg_evexNode *node = new vcompress_expand_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcompress_expand_reg_evex_0_rule: {
      vcompress_expand_reg_evex_0Node *node = new vcompress_expand_reg_evex_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcompress_mask_reg_evex_rule: {
      vcompress_mask_reg_evexNode *node = new vcompress_mask_reg_evexNode();
      node->set_opnd_array(2, MachOperGenerator(RREGL));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vreverse_reg_rule: {
      vreverse_regNode *node = new vreverse_regNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vreverse_reg_gfni_rule: {
      vreverse_reg_gfniNode *node = new vreverse_reg_gfniNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vreverse_byte_reg_rule: {
      vreverse_byte_regNode *node = new vreverse_byte_regNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vreverse_byte64_reg_rule: {
      vreverse_byte64_regNode *node = new vreverse_byte64_regNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcount_leading_zeros_IL_reg_evex_rule: {
      vcount_leading_zeros_IL_reg_evexNode *node = new vcount_leading_zeros_IL_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcount_leading_zeros_IL_reg_evex_masked_rule: {
      vcount_leading_zeros_IL_reg_evex_maskedNode *node = new vcount_leading_zeros_IL_reg_evex_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcount_leading_zeros_short_reg_evex_rule: {
      vcount_leading_zeros_short_reg_evexNode *node = new vcount_leading_zeros_short_reg_evexNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcount_leading_zeros_byte_reg_evex_rule: {
      vcount_leading_zeros_byte_reg_evexNode *node = new vcount_leading_zeros_byte_reg_evexNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(KREG));
      node->set_opnd_array(7, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcount_leading_zeros_int_reg_avx_rule: {
      vcount_leading_zeros_int_reg_avxNode *node = new vcount_leading_zeros_int_reg_avxNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcount_leading_zeros_reg_avx_rule: {
      vcount_leading_zeros_reg_avxNode *node = new vcount_leading_zeros_reg_avxNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(VEC));
      node->set_opnd_array(4, MachOperGenerator(VEC));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->set_opnd_array(6, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_reg_masked_rule: {
      vadd_reg_maskedNode *node = new vadd_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_reg_masked_0_rule: {
      vadd_reg_masked_0Node *node = new vadd_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_reg_masked_1_rule: {
      vadd_reg_masked_1Node *node = new vadd_reg_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_reg_masked_2_rule: {
      vadd_reg_masked_2Node *node = new vadd_reg_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_reg_masked_3_rule: {
      vadd_reg_masked_3Node *node = new vadd_reg_masked_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_reg_masked_4_rule: {
      vadd_reg_masked_4Node *node = new vadd_reg_masked_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_mem_masked_rule: {
      vadd_mem_maskedNode *node = new vadd_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_mem_masked_0_rule: {
      vadd_mem_masked_0Node *node = new vadd_mem_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_mem_masked_1_rule: {
      vadd_mem_masked_1Node *node = new vadd_mem_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_mem_masked_2_rule: {
      vadd_mem_masked_2Node *node = new vadd_mem_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_mem_masked_3_rule: {
      vadd_mem_masked_3Node *node = new vadd_mem_masked_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd_mem_masked_4_rule: {
      vadd_mem_masked_4Node *node = new vadd_mem_masked_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor_reg_masked_rule: {
      vxor_reg_maskedNode *node = new vxor_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor_mem_masked_rule: {
      vxor_mem_maskedNode *node = new vxor_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor_reg_masked_rule: {
      vor_reg_maskedNode *node = new vor_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor_mem_masked_rule: {
      vor_mem_maskedNode *node = new vor_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_reg_masked_rule: {
      vand_reg_maskedNode *node = new vand_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand_mem_masked_rule: {
      vand_mem_maskedNode *node = new vand_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_reg_masked_rule: {
      vsub_reg_maskedNode *node = new vsub_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_reg_masked_0_rule: {
      vsub_reg_masked_0Node *node = new vsub_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_reg_masked_1_rule: {
      vsub_reg_masked_1Node *node = new vsub_reg_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_reg_masked_2_rule: {
      vsub_reg_masked_2Node *node = new vsub_reg_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_reg_masked_3_rule: {
      vsub_reg_masked_3Node *node = new vsub_reg_masked_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_reg_masked_4_rule: {
      vsub_reg_masked_4Node *node = new vsub_reg_masked_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_mem_masked_rule: {
      vsub_mem_maskedNode *node = new vsub_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_mem_masked_0_rule: {
      vsub_mem_masked_0Node *node = new vsub_mem_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_mem_masked_1_rule: {
      vsub_mem_masked_1Node *node = new vsub_mem_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_mem_masked_2_rule: {
      vsub_mem_masked_2Node *node = new vsub_mem_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_mem_masked_3_rule: {
      vsub_mem_masked_3Node *node = new vsub_mem_masked_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub_mem_masked_4_rule: {
      vsub_mem_masked_4Node *node = new vsub_mem_masked_4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul_reg_masked_rule: {
      vmul_reg_maskedNode *node = new vmul_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul_reg_masked_0_rule: {
      vmul_reg_masked_0Node *node = new vmul_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul_reg_masked_1_rule: {
      vmul_reg_masked_1Node *node = new vmul_reg_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul_reg_masked_2_rule: {
      vmul_reg_masked_2Node *node = new vmul_reg_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul_reg_masked_3_rule: {
      vmul_reg_masked_3Node *node = new vmul_reg_masked_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul_mem_masked_rule: {
      vmul_mem_maskedNode *node = new vmul_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul_mem_masked_0_rule: {
      vmul_mem_masked_0Node *node = new vmul_mem_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul_mem_masked_1_rule: {
      vmul_mem_masked_1Node *node = new vmul_mem_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul_mem_masked_2_rule: {
      vmul_mem_masked_2Node *node = new vmul_mem_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul_mem_masked_3_rule: {
      vmul_mem_masked_3Node *node = new vmul_mem_masked_3Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt_reg_masked_rule: {
      vsqrt_reg_maskedNode *node = new vsqrt_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt_reg_masked_0_rule: {
      vsqrt_reg_masked_0Node *node = new vsqrt_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv_reg_masked_rule: {
      vdiv_reg_maskedNode *node = new vdiv_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv_reg_masked_0_rule: {
      vdiv_reg_masked_0Node *node = new vdiv_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv_mem_masked_rule: {
      vdiv_mem_maskedNode *node = new vdiv_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv_mem_masked_0_rule: {
      vdiv_mem_masked_0Node *node = new vdiv_mem_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrol_imm_masked_rule: {
      vrol_imm_maskedNode *node = new vrol_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrol_imm_masked_0_rule: {
      vrol_imm_masked_0Node *node = new vrol_imm_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrol_reg_masked_rule: {
      vrol_reg_maskedNode *node = new vrol_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrol_reg_masked_0_rule: {
      vrol_reg_masked_0Node *node = new vrol_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlshift_imm_masked_rule: {
      vlshift_imm_maskedNode *node = new vlshift_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlshift_imm_masked_0_rule: {
      vlshift_imm_masked_0Node *node = new vlshift_imm_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlshift_imm_masked_1_rule: {
      vlshift_imm_masked_1Node *node = new vlshift_imm_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlshift_reg_masked_rule: {
      vlshift_reg_maskedNode *node = new vlshift_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlshift_reg_masked_0_rule: {
      vlshift_reg_masked_0Node *node = new vlshift_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlshift_reg_masked_1_rule: {
      vlshift_reg_masked_1Node *node = new vlshift_reg_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlshiftv_reg_masked_rule: {
      vlshiftv_reg_maskedNode *node = new vlshiftv_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlshiftv_reg_masked_0_rule: {
      vlshiftv_reg_masked_0Node *node = new vlshiftv_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vlshiftv_reg_masked_1_rule: {
      vlshiftv_reg_masked_1Node *node = new vlshiftv_reg_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrshift_imm_masked_rule: {
      vrshift_imm_maskedNode *node = new vrshift_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrshift_imm_masked_0_rule: {
      vrshift_imm_masked_0Node *node = new vrshift_imm_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrshift_imm_masked_1_rule: {
      vrshift_imm_masked_1Node *node = new vrshift_imm_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrshift_reg_masked_rule: {
      vrshift_reg_maskedNode *node = new vrshift_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrshift_reg_masked_0_rule: {
      vrshift_reg_masked_0Node *node = new vrshift_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrshift_reg_masked_1_rule: {
      vrshift_reg_masked_1Node *node = new vrshift_reg_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrshiftv_reg_masked_rule: {
      vrshiftv_reg_maskedNode *node = new vrshiftv_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrshiftv_reg_masked_0_rule: {
      vrshiftv_reg_masked_0Node *node = new vrshiftv_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrshiftv_reg_masked_1_rule: {
      vrshiftv_reg_masked_1Node *node = new vrshiftv_reg_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vurshift_imm_masked_rule: {
      vurshift_imm_maskedNode *node = new vurshift_imm_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vurshift_imm_masked_0_rule: {
      vurshift_imm_masked_0Node *node = new vurshift_imm_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vurshift_imm_masked_1_rule: {
      vurshift_imm_masked_1Node *node = new vurshift_imm_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vurshift_reg_masked_rule: {
      vurshift_reg_maskedNode *node = new vurshift_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vurshift_reg_masked_0_rule: {
      vurshift_reg_masked_0Node *node = new vurshift_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vurshift_reg_masked_1_rule: {
      vurshift_reg_masked_1Node *node = new vurshift_reg_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vurshiftv_reg_masked_rule: {
      vurshiftv_reg_maskedNode *node = new vurshiftv_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vurshiftv_reg_masked_0_rule: {
      vurshiftv_reg_masked_0Node *node = new vurshiftv_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vurshiftv_reg_masked_1_rule: {
      vurshiftv_reg_masked_1Node *node = new vurshiftv_reg_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaxv_reg_masked_rule: {
      vmaxv_reg_maskedNode *node = new vmaxv_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmaxv_mem_masked_rule: {
      vmaxv_mem_maskedNode *node = new vmaxv_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vminv_reg_masked_rule: {
      vminv_reg_maskedNode *node = new vminv_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vminv_mem_masked_rule: {
      vminv_mem_maskedNode *node = new vminv_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vrearrangev_reg_masked_rule: {
      vrearrangev_reg_maskedNode *node = new vrearrangev_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs_masked_rule: {
      vabs_maskedNode *node = new vabs_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs_masked_0_rule: {
      vabs_masked_0Node *node = new vabs_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs_masked_1_rule: {
      vabs_masked_1Node *node = new vabs_masked_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs_masked_2_rule: {
      vabs_masked_2Node *node = new vabs_masked_2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma_reg_masked_rule: {
      vfma_reg_maskedNode *node = new vfma_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma_reg_masked_0_rule: {
      vfma_reg_masked_0Node *node = new vfma_reg_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma_mem_masked_rule: {
      vfma_mem_maskedNode *node = new vfma_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma_mem_masked_0_rule: {
      vfma_mem_masked_0Node *node = new vfma_mem_masked_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case evcmp_masked_rule: {
      evcmp_maskedNode *node = new evcmp_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mask_all_evexI_LE32_rule: {
      mask_all_evexI_LE32Node *node = new mask_all_evexI_LE32Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mask_not_immLT8_rule: {
      mask_not_immLT8Node *node = new mask_not_immLT8Node();
      node->set_opnd_array(3, MachOperGenerator(KREG));
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      node->set_opnd_array(5, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mask_not_imm_rule: {
      mask_not_immNode *node = new mask_not_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case long_to_maskLE8_avx_rule: {
      long_to_maskLE8_avxNode *node = new long_to_maskLE8_avxNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case long_to_maskGT8_avx_rule: {
      long_to_maskGT8_avxNode *node = new long_to_maskGT8_avxNode();
      node->set_opnd_array(2, MachOperGenerator(VEC));
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      node->set_opnd_array(4, MachOperGenerator(RREGL));
      node->set_opnd_array(5, MachOperGenerator(VEC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case long_to_mask_evex_rule: {
      long_to_mask_evexNode *node = new long_to_mask_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mask_opers_evex_rule: {
      mask_opers_evexNode *node = new mask_opers_evexNode();
      node->set_opnd_array(3, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mask_opers_evex_0_rule: {
      mask_opers_evex_0Node *node = new mask_opers_evex_0Node();
      node->set_opnd_array(3, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mask_opers_evex_1_rule: {
      mask_opers_evex_1Node *node = new mask_opers_evex_1Node();
      node->set_opnd_array(3, MachOperGenerator(KREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vternlog_reg_masked_rule: {
      vternlog_reg_maskedNode *node = new vternlog_reg_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vternlogd_mem_masked_rule: {
      vternlogd_mem_maskedNode *node = new vternlogd_mem_maskedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castMM_rule: {
      castMMNode *node = new castMMNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castVV_rule: {
      castVVNode *node = new castVVNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castVVLeg_rule: {
      castVVLegNode *node = new castVVLegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case FloatClassCheck_reg_reg_vfpclass_rule: {
      FloatClassCheck_reg_reg_vfpclassNode *node = new FloatClassCheck_reg_reg_vfpclassNode();
      node->set_opnd_array(2, MachOperGenerator(KREG));
      return node;
    }
  case DoubleClassCheck_reg_reg_vfpclass_rule: {
      DoubleClassCheck_reg_reg_vfpclassNode *node = new DoubleClassCheck_reg_reg_vfpclassNode();
      node->set_opnd_array(2, MachOperGenerator(KREG));
      return node;
    }
  case compareAndSwapP_shenandoah_rule: {
      compareAndSwapP_shenandoahNode *node = new compareAndSwapP_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->set_opnd_array(5, MachOperGenerator(RREGP));
      return node;
    }
  case compareAndSwapP_shenandoah_0_rule: {
      compareAndSwapP_shenandoah_0Node *node = new compareAndSwapP_shenandoah_0Node();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->set_opnd_array(5, MachOperGenerator(RREGP));
      return node;
    }
  case compareAndSwapN_shenandoah_rule: {
      compareAndSwapN_shenandoahNode *node = new compareAndSwapN_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->set_opnd_array(5, MachOperGenerator(RREGP));
      return node;
    }
  case compareAndSwapN_shenandoah_0_rule: {
      compareAndSwapN_shenandoah_0Node *node = new compareAndSwapN_shenandoah_0Node();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->set_opnd_array(5, MachOperGenerator(RREGP));
      return node;
    }
  case compareAndExchangeN_shenandoah_rule: {
      compareAndExchangeN_shenandoahNode *node = new compareAndExchangeN_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->set_opnd_array(5, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeP_shenandoah_rule: {
      compareAndExchangeP_shenandoahNode *node = new compareAndExchangeP_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->set_opnd_array(5, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xLoadP_rule: {
      xLoadPNode *node = new xLoadPNode();
      node->set_opnd_array(2, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xCompareAndExchangeP_rule: {
      xCompareAndExchangePNode *node = new xCompareAndExchangePNode();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xCompareAndSwapP_rule: {
      xCompareAndSwapPNode *node = new xCompareAndSwapPNode();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      return node;
    }
  case xCompareAndSwapP_0_rule: {
      xCompareAndSwapP_0Node *node = new xCompareAndSwapP_0Node();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      return node;
    }
  case xXChgP_rule: {
      xXChgPNode *node = new xXChgPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zLoadP_rule: {
      zLoadPNode *node = new zLoadPNode();
      node->set_opnd_array(2, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zLoadPNullCheck_rule: {
      zLoadPNullCheckNode *node = new zLoadPNullCheckNode();
      return node;
    }
  case zStoreP_rule: {
      zStorePNode *node = new zStorePNode();
      node->set_opnd_array(3, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zStorePNull_rule: {
      zStorePNullNode *node = new zStorePNullNode();
      node->set_opnd_array(3, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zCompareAndExchangeP_rule: {
      zCompareAndExchangePNode *node = new zCompareAndExchangePNode();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zCompareAndSwapP_rule: {
      zCompareAndSwapPNode *node = new zCompareAndSwapPNode();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      return node;
    }
  case zCompareAndSwapP_0_rule: {
      zCompareAndSwapP_0Node *node = new zCompareAndSwapP_0Node();
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      return node;
    }
  case zXChgP_rule: {
      zXChgPNode *node = new zXChgPNode();
      node->set_opnd_array(3, MachOperGenerator(RREGP));
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
