#line 1 "ad_ppc_gen.cpp"
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
  case VECX:
    return new vecXOper( );
  case IMMI:
    return new immIOper(_leaf->get_int() );
  case IMMI8:
    return new immI8Oper(_leaf->get_int() );
  case IMMI16:
    return new immI16Oper(_leaf->get_int() );
  case IMMIHI16:
    return new immIhi16Oper(_leaf->get_int() );
  case IMMI32:
    return new immI32Oper(_leaf->get_int() );
  case IMMINEGPOW2:
    return new immInegpow2Oper(_leaf->get_int() );
  case IMMIPOW2MINUS1:
    return new immIpow2minus1Oper(_leaf->get_int() );
  case IMMIPOWEROF2:
    return new immIpowerOf2Oper(_leaf->get_int() );
  case UIMMI5:
    return new uimmI5Oper(_leaf->get_int() );
  case UIMMI6:
    return new uimmI6Oper(_leaf->get_int() );
  case UIMMI6_GE32:
    return new uimmI6_ge32Oper(_leaf->get_int() );
  case UIMMI15:
    return new uimmI15Oper(_leaf->get_int() );
  case UIMMI16:
    return new uimmI16Oper(_leaf->get_int() );
  case IMMI_0:
    return new immI_0Oper(_leaf->get_int() );
  case IMMI_1:
    return new immI_1Oper(_leaf->get_int() );
  case IMMI_MINUS1:
    return new immI_minus1Oper(_leaf->get_int() );
  case IMMI_16:
    return new immI_16Oper(_leaf->get_int() );
  case IMMI_24:
    return new immI_24Oper(_leaf->get_int() );
  case IMMN:
    return new immNOper(_leaf->bottom_type()->is_narrowoop() );
  case IMMN_0:
    return new immN_0Oper(_leaf->bottom_type()->is_narrowoop() );
  case IMMNKLASS:
    return new immNKlassOper(_leaf->bottom_type()->is_narrowklass() );
  case IMMNKLASS_NM:
    return new immNKlass_NMOper(_leaf->bottom_type()->is_narrowklass() );
  case IMMP:
    return new immPOper(_leaf->bottom_type()->is_ptr() );
  case IMMP_NM:
    return new immP_NMOper(_leaf->bottom_type()->is_ptr() );
  case IMMP_0:
    return new immP_0Oper(_leaf->bottom_type()->is_ptr() );
  case IMMP_0OR1:
    return new immP_0or1Oper(_leaf->bottom_type()->is_ptr() );
  case IMML:
    return new immLOper(_leaf->get_long() );
  case IMMLMAX30:
    return new immLmax30Oper(_leaf->get_long() );
  case IMML16:
    return new immL16Oper(_leaf->get_long() );
  case IMML16ALG4:
    return new immL16Alg4Oper(_leaf->get_long() );
  case IMML32HI16:
    return new immL32hi16Oper(_leaf->get_long() );
  case IMML32:
    return new immL32Oper(_leaf->get_long() );
  case IMML34:
    return new immL34Oper(_leaf->get_long() );
  case IMMLHIGHEST16:
    return new immLhighest16Oper(_leaf->get_long() );
  case IMMLNEGPOW2:
    return new immLnegpow2Oper(_leaf->get_long() );
  case IMMLPOW2MINUS1:
    return new immLpow2minus1Oper(_leaf->get_long() );
  case IMML_0:
    return new immL_0Oper(_leaf->get_long() );
  case IMML_MINUS1:
    return new immL_minus1Oper(_leaf->get_long() );
  case IMML_32BITS:
    return new immL_32bitsOper(_leaf->get_long() );
  case UIMML16:
    return new uimmL16Oper(_leaf->get_long() );
  case IMMF:
    return new immFOper(_leaf->getf() );
  case IMMF_0:
    return new immF_0Oper(_leaf->getf() );
  case IMMD:
    return new immDOper(_leaf->getd() );
  case IMMD_0:
    return new immD_0Oper(_leaf->getd() );
  case IREGIDST:
    return new iRegIdstOper( );
  case IREGISRC:
    return new iRegIsrcOper( );
  case RSCRATCH1REGI:
    return new rscratch1RegIOper( );
  case RSCRATCH2REGI:
    return new rscratch2RegIOper( );
  case RARG1REGI:
    return new rarg1RegIOper( );
  case RARG2REGI:
    return new rarg2RegIOper( );
  case RARG3REGI:
    return new rarg3RegIOper( );
  case RARG4REGI:
    return new rarg4RegIOper( );
  case RARG1REGL:
    return new rarg1RegLOper( );
  case RARG2REGL:
    return new rarg2RegLOper( );
  case RARG3REGL:
    return new rarg3RegLOper( );
  case RARG4REGL:
    return new rarg4RegLOper( );
  case IREGPDST:
    return new iRegPdstOper( );
  case IREGPDSTNOSCRATCH:
    return new iRegPdstNoScratchOper( );
  case IREGPSRC:
    return new iRegPsrcOper( );
  case THREADREGP:
    return new threadRegPOper( );
  case RSCRATCH1REGP:
    return new rscratch1RegPOper( );
  case RSCRATCH2REGP:
    return new rscratch2RegPOper( );
  case RARG1REGP:
    return new rarg1RegPOper( );
  case RARG2REGP:
    return new rarg2RegPOper( );
  case RARG3REGP:
    return new rarg3RegPOper( );
  case RARG4REGP:
    return new rarg4RegPOper( );
  case IREGNSRC:
    return new iRegNsrcOper( );
  case IREGNDST:
    return new iRegNdstOper( );
  case IREGLDST:
    return new iRegLdstOper( );
  case IREGLSRC:
    return new iRegLsrcOper( );
  case IREGL2ISRC:
    return new iRegL2IsrcOper( );
  case RSCRATCH1REGL:
    return new rscratch1RegLOper( );
  case RSCRATCH2REGL:
    return new rscratch2RegLOper( );
  case FLAGSREG:
    return new flagsRegOper( );
  case FLAGSREGSRC:
    return new flagsRegSrcOper( );
  case FLAGSREGCR0:
    return new flagsRegCR0Oper( );
  case FLAGSREGCR1:
    return new flagsRegCR1Oper( );
  case FLAGSREGCR6:
    return new flagsRegCR6Oper( );
  case REGCTR:
    return new regCTROper( );
  case REGD:
    return new regDOper( );
  case REGF:
    return new regFOper( );
  case INLINE_CACHE_REGP:
    return new inline_cache_regPOper( );
  case IREGP2N:
    return new iRegP2NOper( );
  case IREGN2P:
    return new iRegN2POper( );
  case IREGN2P_KLASS:
    return new iRegN2P_klassOper( );
  case INDIRECT:
    return new indirectOper( );
  case INDOFFSET16:
    return new indOffset16Oper(_kids[1]->_leaf->get_long() );
  case INDOFFSET16ALG4:
    return new indOffset16Alg4Oper(_kids[1]->_leaf->get_long() );
  case INDIRECTNARROW:
    return new indirectNarrowOper( );
  case INDIRECTNARROW_KLASS:
    return new indirectNarrow_klassOper( );
  case INDOFFSET16NARROW:
    return new indOffset16NarrowOper(_kids[1]->_leaf->get_long() );
  case INDOFFSET16NARROW_KLASS:
    return new indOffset16Narrow_klassOper(_kids[1]->_leaf->get_long() );
  case INDOFFSET16NARROWALG4:
    return new indOffset16NarrowAlg4Oper(_kids[1]->_leaf->get_long() );
  case INDOFFSET16NARROWALG4_KLASS:
    return new indOffset16NarrowAlg4_klassOper(_kids[1]->_leaf->get_long() );
  case STACKSLOTI:
    return new stackSlotIOper( );
  case STACKSLOTL:
    return new stackSlotLOper( );
  case STACKSLOTP:
    return new stackSlotPOper( );
  case STACKSLOTF:
    return new stackSlotFOper( );
  case STACKSLOTD:
    return new stackSlotDOper( );
  case CMPOP:
    return new cmpOpOper(_leaf->as_Bool()->_test._test );
  case _DECODEN_IREGNSRC_:    return NULL;
  case _DECODENKLASS_IREGNSRC_:    return NULL;
  case _LOADUB_MEMORY_:    return NULL;
  case _LOADUS_MEMORY_:    return NULL;
  case _LOADI_MEMORY_:    return NULL;
  case _CONVI2L__LOADI_MEMORY__:    return NULL;
  case _LOADI_MEMORYALG4_:    return NULL;
  case _LOADN_MEMORY_:    return NULL;
  case _LOADNKLASS_MEMORY_:    return NULL;
  case _LOADP_MEMORYALG4_:    return NULL;
  case _ADDP_INDIRECTMEMORY_IREGLSRC:    return NULL;
  case _CONVL2I_IREGLSRC_:    return NULL;
  case _BINARY_FLAGSREGSRC_IREGPSRC:    return NULL;
  case _CASTP2X__DECODEN_IREGNSRC__:    return NULL;
  case _BINARY_IREGLSRC_IREGPDST:    return NULL;
  case _BINARY_IREGLSRC_IREGPSRC:    return NULL;
  case _BINARY_IREGLSRC_IREGNSRC:    return NULL;
  case _BINARY_CMPOP_FLAGSREGSRC:    return NULL;
  case _BINARY_IREGIDST_IREGISRC:    return NULL;
  case _BINARY_IREGIDST_IMMI16:    return NULL;
  case _BINARY_IREGLDST_IREGLSRC:    return NULL;
  case _BINARY_IREGLDST_IMML16:    return NULL;
  case _BINARY_IREGNDST_IREGNSRC:    return NULL;
  case _BINARY_IREGNDST_IMMN_0:    return NULL;
  case _BINARY_IREGPDST_IREGPSRC:    return NULL;
  case _BINARY_IREGPDST_IREGP_N2P:    return NULL;
  case _BINARY_IREGPDST_IMMP_0:    return NULL;
  case _BINARY_REGF_REGF:    return NULL;
  case _BINARY_REGD_REGD:    return NULL;
  case _BINARY_IREGISRC_IREGISRC:    return NULL;
  case _BINARY_IREGISRC_RARG4REGI:    return NULL;
  case _BINARY_IREGNSRC_IREGNSRC:    return NULL;
  case _BINARY_IREGLSRC_IREGLSRC:    return NULL;
  case _BINARY_IREGPSRC_IREGPSRC:    return NULL;
  case _ADDI_IREGISRC_IREGISRC:    return NULL;
  case _ADDI__ADDI_IREGISRC_IREGISRC_IREGISRC:    return NULL;
  case _ADDI_IREGISRC__ADDI_IREGISRC_IREGISRC:    return NULL;
  case _ADDL_IREGLSRC_IREGLSRC:    return NULL;
  case _ADDL__ADDL_IREGLSRC_IREGLSRC_IREGLSRC:    return NULL;
  case _ADDL_IREGLSRC__ADDL_IREGLSRC_IREGLSRC:    return NULL;
  case _SUBL_IREGLSRC_IREGLSRC:    return NULL;
  case _SUBL_IMML_0_IREGLSRC:    return NULL;
  case _ANDI_IREGISRC_IMMINEGPOW2:    return NULL;
  case _RSHIFTI_IREGISRC_UIMMI5:    return NULL;
  case _ANDI__RSHIFTI_IREGISRC_UIMMI5_IMMINEGPOW2:    return NULL;
  case _CONVI2L_IREGISRC_:    return NULL;
  case _RSHIFTL_IREGLSRC_IMMI:    return NULL;
  case _URSHIFTL_IREGLSRC_IMMI:    return NULL;
  case _CASTP2X_IREGP_N2P_:    return NULL;
  case _URSHIFTI_IREGISRC_IMMI:    return NULL;
  case _LSHIFTI_IREGISRC_IMMI8:    return NULL;
  case _URSHIFTI_IREGISRC_IMMI8:    return NULL;
  case _ABSF_REGF_:    return NULL;
  case _ABSD_REGD_:    return NULL;
  case _NEGF_REGF_:    return NULL;
  case _BINARY__NEGF_REGF__REGF:    return NULL;
  case _BINARY_REGF__NEGF_REGF_:    return NULL;
  case _NEGD_REGD_:    return NULL;
  case _BINARY__NEGD_REGD__REGD:    return NULL;
  case _BINARY_REGD__NEGD_REGD_:    return NULL;
  case _ANDL_IREGLSRC_IMMLPOW2MINUS1:    return NULL;
  case _ORI_IREGISRC_IREGISRC:    return NULL;
  case _ORI__ORI_IREGISRC_IREGISRC_IREGISRC:    return NULL;
  case _ORI_IREGISRC__ORI_IREGISRC_IREGISRC:    return NULL;
  case _ORL_IREGLSRC_IREGLSRC:    return NULL;
  case _XORI_IREGISRC_IREGISRC:    return NULL;
  case _XORI__XORI_IREGISRC_IREGISRC_IREGISRC:    return NULL;
  case _XORI_IREGISRC__XORI_IREGISRC_IREGISRC:    return NULL;
  case _XORL_IREGLSRC_IREGLSRC:    return NULL;
  case _XORI_IREGISRC_IMMI_MINUS1:    return NULL;
  case _CONV2B_IREGISRC_:    return NULL;
  case _ANDI_IREGISRC_IMMIPOWEROF2:    return NULL;
  case _CONV2B_IREGP_N2P_:    return NULL;
  case _LSHIFTI_IREGISRC_IMMI_24:    return NULL;
  case _LSHIFTI_IREGISRC_IMMI_16:    return NULL;
  case _ANDI_IREGISRC_UIMMI16:    return NULL;
  case _ANDL_IREGLSRC_IREGLSRC:    return NULL;
  case _ANDL_IREGLSRC_UIMML16:    return NULL;
  case _CMPU_IREGISRC_UIMMI15:    return NULL;
  case _CMPU_IREGISRC_IREGISRC:    return NULL;
  case _CMPN_IREGNSRC_IMMN_0:    return NULL;
  case _CMPP_IREGP_N2P_IMMP_0:    return NULL;
  case _CASTP2X_IREGPSRC_:    return NULL;
  case _ANDL__CASTP2X_IREGPSRC__IMMLNEGPOW2:    return NULL;
  case _BINARY_RARG1REGP_RARG3REGI:    return NULL;
  case _BINARY_RARG2REGP_RARG4REGI:    return NULL;
  case _BINARY_RARG1REGP_RARG2REGP:    return NULL;
  case _BINARY_IREGPSRC_IREGISRC:    return NULL;
  case _ADDP_IMMP_IMML:    return NULL;
  case _BINARY__ADDP_IMMP_IMML_IMMI_1:    return NULL;
  case _BINARY_RSCRATCH2REGP_IMMI_1:    return NULL;
  case _BINARY_IREGPSRC_RSCRATCH1REGI:    return NULL;
  case _BINARY_IREGPSRC_UIMMI15:    return NULL;
  case _BINARY_IREGPSRC_RSCRATCH2REGI:    return NULL;
  case _BINARY_RARG2REGP_IREGISRC:    return NULL;
  case _LOADI_INDIRECT_:    return NULL;
  case _LOADL_INDIRECT_:    return NULL;
  case _LOADUS_INDIRECT_:    return NULL;
  case _LOADS_INDIRECT_:    return NULL;
  case _REVERSEBYTESI_IREGISRC_:    return NULL;
  case _REVERSEBYTESL_IREGLSRC_:    return NULL;
  case _REVERSEBYTESUS_IREGISRC_:    return NULL;
  case _REVERSEBYTESS_IREGISRC_:    return NULL;
  case _BINARY_VECX_VECX:    return NULL;
  case _NEGVF_VECX_:    return NULL;
  case _BINARY__NEGVF_VECX__VECX:    return NULL;
  case _BINARY_VECX__NEGVF_VECX_:    return NULL;
  case _NEGVD_VECX_:    return NULL;
  case _BINARY__NEGVD_VECX__VECX:    return NULL;
  case _BINARY_VECX__NEGVD_VECX_:    return NULL;
  
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
  case loadUB_indirect_rule: {
      loadUB_indirectNode *node = new loadUB_indirectNode();
      return node;
    }
  case loadUB_indirect_ac_rule: {
      loadUB_indirect_acNode *node = new loadUB_indirect_acNode();
      return node;
    }
  case loadB_indirect_Ex_rule: {
      loadB_indirect_ExNode *node = new loadB_indirect_ExNode();
      return node;
    }
  case loadB_indirect_ac_Ex_rule: {
      loadB_indirect_ac_ExNode *node = new loadB_indirect_ac_ExNode();
      return node;
    }
  case loadUB_indOffset16_rule: {
      loadUB_indOffset16Node *node = new loadUB_indOffset16Node();
      return node;
    }
  case loadUB_indOffset16_ac_rule: {
      loadUB_indOffset16_acNode *node = new loadUB_indOffset16_acNode();
      return node;
    }
  case loadB_indOffset16_Ex_rule: {
      loadB_indOffset16_ExNode *node = new loadB_indOffset16_ExNode();
      return node;
    }
  case loadB_indOffset16_ac_Ex_rule: {
      loadB_indOffset16_ac_ExNode *node = new loadB_indOffset16_ac_ExNode();
      return node;
    }
  case loadUB_rule: {
      loadUBNode *node = new loadUBNode();
      return node;
    }
  case loadUB_ac_rule: {
      loadUB_acNode *node = new loadUB_acNode();
      return node;
    }
  case loadUB2L_rule: {
      loadUB2LNode *node = new loadUB2LNode();
      return node;
    }
  case loadUB2L_ac_rule: {
      loadUB2L_acNode *node = new loadUB2L_acNode();
      return node;
    }
  case loadS_rule: {
      loadSNode *node = new loadSNode();
      return node;
    }
  case loadS_ac_rule: {
      loadS_acNode *node = new loadS_acNode();
      return node;
    }
  case loadUS_rule: {
      loadUSNode *node = new loadUSNode();
      return node;
    }
  case loadUS_ac_rule: {
      loadUS_acNode *node = new loadUS_acNode();
      return node;
    }
  case loadUS2L_rule: {
      loadUS2LNode *node = new loadUS2LNode();
      return node;
    }
  case loadUS2L_ac_rule: {
      loadUS2L_acNode *node = new loadUS2L_acNode();
      return node;
    }
  case loadI_rule: {
      loadINode *node = new loadINode();
      return node;
    }
  case loadI_ac_rule: {
      loadI_acNode *node = new loadI_acNode();
      return node;
    }
  case loadUI2L_rule: {
      loadUI2LNode *node = new loadUI2LNode();
      return node;
    }
  case loadI2L_rule: {
      loadI2LNode *node = new loadI2LNode();
      return node;
    }
  case loadI2L_ac_rule: {
      loadI2L_acNode *node = new loadI2L_acNode();
      return node;
    }
  case loadL_rule: {
      loadLNode *node = new loadLNode();
      return node;
    }
  case loadL_ac_rule: {
      loadL_acNode *node = new loadL_acNode();
      return node;
    }
  case loadL_unaligned_rule: {
      loadL_unalignedNode *node = new loadL_unalignedNode();
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
  case loadRange_rule: {
      loadRangeNode *node = new loadRangeNode();
      return node;
    }
  case loadN_rule: {
      loadNNode *node = new loadNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadN_ac_rule: {
      loadN_acNode *node = new loadN_acNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadN2P_unscaled_rule: {
      loadN2P_unscaledNode *node = new loadN2P_unscaledNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadN2P_klass_unscaled_rule: {
      loadN2P_klass_unscaledNode *node = new loadN2P_klass_unscaledNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadP_rule: {
      loadPNode *node = new loadPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadP_ac_rule: {
      loadP_acNode *node = new loadP_acNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadP2X_rule: {
      loadP2XNode *node = new loadP2XNode();
      return node;
    }
  case loadNKlass_rule: {
      loadNKlassNode *node = new loadNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadKlass_rule: {
      loadKlassNode *node = new loadKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadF_rule: {
      loadFNode *node = new loadFNode();
      return node;
    }
  case loadF_ac_rule: {
      loadF_acNode *node = new loadF_acNode();
      node->set_opnd_array(2, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case loadD_rule: {
      loadDNode *node = new loadDNode();
      return node;
    }
  case loadD_ac_rule: {
      loadD_acNode *node = new loadD_acNode();
      node->set_opnd_array(2, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case loadD_unaligned_rule: {
      loadD_unalignedNode *node = new loadD_unalignedNode();
      return node;
    }
  case loadConI16_rule: {
      loadConI16Node *node = new loadConI16Node();
      node->_opnd_array[1] = new immI16Oper(_leaf->get_int() );
      return node;
    }
  case loadConIhi16_rule: {
      loadConIhi16Node *node = new loadConIhi16Node();
      node->_opnd_array[1] = new immIhi16Oper(_leaf->get_int() );
      return node;
    }
  case loadConI32_rule: {
      loadConI32Node *node = new loadConI32Node();
      node->_opnd_array[1] = new immI32Oper(_leaf->get_int() );
      return node;
    }
  case loadConI_Ex_rule: {
      loadConI_ExNode *node = new loadConI_ExNode();
      node->_opnd_array[1] = new immIOper(_leaf->get_int() );
      return node;
    }
  case loadConL16_rule: {
      loadConL16Node *node = new loadConL16Node();
      node->_opnd_array[1] = new immL16Oper(_leaf->get_long() );
      return node;
    }
  case loadConL32hi16_rule: {
      loadConL32hi16Node *node = new loadConL32hi16Node();
      node->_opnd_array[1] = new immL32hi16Oper(_leaf->get_long() );
      return node;
    }
  case loadConL32_Ex_rule: {
      loadConL32_ExNode *node = new loadConL32_ExNode();
      node->_opnd_array[1] = new immL32Oper(_leaf->get_long() );
      return node;
    }
  case loadConL34_rule: {
      loadConL34Node *node = new loadConL34Node();
      node->_opnd_array[1] = new immL34Oper(_leaf->get_long() );
      return node;
    }
  case loadConLhighest16_Ex_rule: {
      loadConLhighest16_ExNode *node = new loadConLhighest16_ExNode();
      node->_opnd_array[1] = new immLhighest16Oper(_leaf->get_long() );
      return node;
    }
  case loadConL_Ex_rule: {
      loadConL_ExNode *node = new loadConL_ExNode();
      node->_opnd_array[1] = new immLOper(_leaf->get_long() );
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConN0_rule: {
      loadConN0Node *node = new loadConN0Node();
      node->_opnd_array[1] = new immN_0Oper(_leaf->bottom_type()->is_narrowoop() );
      return node;
    }
  case loadConN_Ex_rule: {
      loadConN_ExNode *node = new loadConN_ExNode();
      node->_opnd_array[1] = new immNOper(_leaf->bottom_type()->is_narrowoop() );
      return node;
    }
  case loadConNKlass_hi_rule: {
      loadConNKlass_hiNode *node = new loadConNKlass_hiNode();
      node->_opnd_array[1] = new immNKlass_NMOper(_leaf->bottom_type()->is_narrowklass() );
      return node;
    }
  case loadConNKlass_mask_rule: {
      loadConNKlass_maskNode *node = new loadConNKlass_maskNode();
      node->set_opnd_array(2, MachOperGenerator(IREGNSRC));
      return node;
    }
  case loadConNKlass_lo_rule: {
      loadConNKlass_loNode *node = new loadConNKlass_loNode();
      node->set_opnd_array(2, MachOperGenerator(IREGNSRC));
      return node;
    }
  case loadConNKlass_Ex_rule: {
      loadConNKlass_ExNode *node = new loadConNKlass_ExNode();
      node->_opnd_array[1] = new immNKlassOper(_leaf->bottom_type()->is_narrowklass() );
      return node;
    }
  case loadConP0or1_rule: {
      loadConP0or1Node *node = new loadConP0or1Node();
      node->_opnd_array[1] = new immP_0or1Oper(_leaf->bottom_type()->is_ptr() );
      return node;
    }
  case loadConP_rule: {
      loadConPNode *node = new loadConPNode();
      node->set_opnd_array(2, MachOperGenerator(IREGLDST));
      return node;
    }
  case loadConP_lo_rule: {
      loadConP_loNode *node = new loadConP_loNode();
      node->set_opnd_array(2, MachOperGenerator(IREGLDST));
      return node;
    }
  case loadConP_Ex_rule: {
      loadConP_ExNode *node = new loadConP_ExNode();
      node->_opnd_array[1] = new immPOper(_leaf->bottom_type()->is_ptr() );
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConF_Ex_rule: {
      loadConF_ExNode *node = new loadConF_ExNode();
      node->_opnd_array[1] = new immFOper(_leaf->getf() );
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConD_Ex_rule: {
      loadConD_ExNode *node = new loadConD_ExNode();
      node->_opnd_array[1] = new immDOper(_leaf->getd() );
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case prefetch_alloc_zero_rule: {
      prefetch_alloc_zeroNode *node = new prefetch_alloc_zeroNode();
      return node;
    }
  case prefetch_alloc_zero_no_offset_rule: {
      prefetch_alloc_zero_no_offsetNode *node = new prefetch_alloc_zero_no_offsetNode();
      return node;
    }
  case prefetch_alloc_rule: {
      prefetch_allocNode *node = new prefetch_allocNode();
      return node;
    }
  case prefetch_alloc_no_offset_rule: {
      prefetch_alloc_no_offsetNode *node = new prefetch_alloc_no_offsetNode();
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
  case storeI_convL2I_rule: {
      storeI_convL2INode *node = new storeI_convL2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeL_rule: {
      storeLNode *node = new storeLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeA8B_rule: {
      storeA8BNode *node = new storeA8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV16_rule: {
      storeV16Node *node = new storeV16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretL_rule: {
      reinterpretLNode *node = new reinterpretLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case reinterpretX_rule: {
      reinterpretXNode *node = new reinterpretXNode();
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
  case storeP_rule: {
      storePNode *node = new storePNode();
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
  case storeCM_rule: {
      storeCMNode *node = new storeCMNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_shift_rule: {
      encodeP_shiftNode *node = new encodeP_shiftNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_sub_rule: {
      encodeP_subNode *node = new encodeP_subNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cond_sub_base_rule: {
      cond_sub_baseNode *node = new cond_sub_baseNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cond_set_0_oop_rule: {
      cond_set_0_oopNode *node = new cond_set_0_oopNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_Disjoint_rule: {
      encodeP_DisjointNode *node = new encodeP_DisjointNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_Ex_rule: {
      encodeP_ExNode *node = new encodeP_ExNode();
      node->set_opnd_array(2, MachOperGenerator(FLAGSREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_not_null_Ex_rule: {
      encodeP_not_null_ExNode *node = new encodeP_not_null_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_not_null_base_null_rule: {
      encodeP_not_null_base_nullNode *node = new encodeP_not_null_base_nullNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_narrow_oop_shift_0_rule: {
      encodeP_narrow_oop_shift_0Node *node = new encodeP_narrow_oop_shift_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_shift_rule: {
      decodeN_shiftNode *node = new decodeN_shiftNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_add_rule: {
      decodeN_addNode *node = new decodeN_addNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cond_add_base_rule: {
      cond_add_baseNode *node = new cond_add_baseNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cond_set_0_ptr_rule: {
      cond_set_0_ptrNode *node = new cond_set_0_ptrNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_Ex_rule: {
      decodeN_ExNode *node = new decodeN_ExNode();
      node->set_opnd_array(2, MachOperGenerator(FLAGSREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_nullBase_rule: {
      decodeN_nullBaseNode *node = new decodeN_nullBaseNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_mergeDisjoint_rule: {
      decodeN_mergeDisjointNode *node = new decodeN_mergeDisjointNode();
      node->set_opnd_array(2, MachOperGenerator(IREGLSRC));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_Disjoint_notNull_Ex_rule: {
      decodeN_Disjoint_notNull_ExNode *node = new decodeN_Disjoint_notNull_ExNode();
      node->set_opnd_array(2, MachOperGenerator(IREGPDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_Disjoint_isel_Ex_rule: {
      decodeN_Disjoint_isel_ExNode *node = new decodeN_Disjoint_isel_ExNode();
      node->set_opnd_array(2, MachOperGenerator(IREGPDST));
      node->set_opnd_array(3, MachOperGenerator(FLAGSREG));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_notNull_addBase_Ex_rule: {
      decodeN_notNull_addBase_ExNode *node = new decodeN_notNull_addBase_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_unscaled_rule: {
      decodeN_unscaledNode *node = new decodeN_unscaledNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN2I_unscaled_rule: {
      decodeN2I_unscaledNode *node = new decodeN2I_unscaledNode();
      return node;
    }
  case encodePKlass_shift_rule: {
      encodePKlass_shiftNode *node = new encodePKlass_shiftNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodePKlass_sub_base_rule: {
      encodePKlass_sub_baseNode *node = new encodePKlass_sub_baseNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodePKlass_Disjoint_rule: {
      encodePKlass_DisjointNode *node = new encodePKlass_DisjointNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodePKlass_not_null_Ex_rule: {
      encodePKlass_not_null_ExNode *node = new encodePKlass_not_null_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodePKlass_not_null_ExEx_rule: {
      encodePKlass_not_null_ExExNode *node = new encodePKlass_not_null_ExExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeNKlass_shift_rule: {
      decodeNKlass_shiftNode *node = new decodeNKlass_shiftNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeNKlass_add_base_rule: {
      decodeNKlass_add_baseNode *node = new decodeNKlass_add_baseNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeNKlass_notNull_addBase_Ex_rule: {
      decodeNKlass_notNull_addBase_ExNode *node = new decodeNKlass_notNull_addBase_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeNKlass_notNull_addBase_ExEx_rule: {
      decodeNKlass_notNull_addBase_ExExNode *node = new decodeNKlass_notNull_addBase_ExExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case membar_acquire_rule: {
      membar_acquireNode *node = new membar_acquireNode();
      return node;
    }
  case unnecessary_membar_acquire_rule: {
      unnecessary_membar_acquireNode *node = new unnecessary_membar_acquireNode();
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
  case membar_volatile_rule: {
      membar_volatileNode *node = new membar_volatileNode();
      return node;
    }
  case membar_CPUOrder_rule: {
      membar_CPUOrderNode *node = new membar_CPUOrderNode();
      return node;
    }
  case cmovI_reg_isel_rule: {
      cmovI_reg_iselNode *node = new cmovI_reg_iselNode();
      return node;
    }
  case cmovI_reg_rule: {
      cmovI_regNode *node = new cmovI_regNode();
      return node;
    }
  case cmovI_imm_rule: {
      cmovI_immNode *node = new cmovI_immNode();
      return node;
    }
  case cmovL_reg_isel_rule: {
      cmovL_reg_iselNode *node = new cmovL_reg_iselNode();
      return node;
    }
  case cmovL_reg_rule: {
      cmovL_regNode *node = new cmovL_regNode();
      return node;
    }
  case cmovL_imm_rule: {
      cmovL_immNode *node = new cmovL_immNode();
      return node;
    }
  case cmovN_reg_isel_rule: {
      cmovN_reg_iselNode *node = new cmovN_reg_iselNode();
      return node;
    }
  case cmovN_reg_rule: {
      cmovN_regNode *node = new cmovN_regNode();
      return node;
    }
  case cmovN_imm_rule: {
      cmovN_immNode *node = new cmovN_immNode();
      return node;
    }
  case cmovP_reg_isel_rule: {
      cmovP_reg_iselNode *node = new cmovP_reg_iselNode();
      return node;
    }
  case cmovP_reg_rule: {
      cmovP_regNode *node = new cmovP_regNode();
      return node;
    }
  case cmovP_imm_rule: {
      cmovP_immNode *node = new cmovP_immNode();
      return node;
    }
  case cmovF_reg_rule: {
      cmovF_regNode *node = new cmovF_regNode();
      return node;
    }
  case cmovD_reg_rule: {
      cmovD_regNode *node = new cmovD_regNode();
      return node;
    }
  case compareAndSwapB_regP_regI_regI_rule: {
      compareAndSwapB_regP_regI_regINode *node = new compareAndSwapB_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndSwapB4_regP_regI_regI_rule: {
      compareAndSwapB4_regP_regI_regINode *node = new compareAndSwapB4_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndSwapS_regP_regI_regI_rule: {
      compareAndSwapS_regP_regI_regINode *node = new compareAndSwapS_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndSwapS4_regP_regI_regI_rule: {
      compareAndSwapS4_regP_regI_regINode *node = new compareAndSwapS4_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndSwapI_regP_regI_regI_rule: {
      compareAndSwapI_regP_regI_regINode *node = new compareAndSwapI_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndSwapN_regP_regN_regN_rule: {
      compareAndSwapN_regP_regN_regNNode *node = new compareAndSwapN_regP_regN_regNNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndSwapL_regP_regL_regL_rule: {
      compareAndSwapL_regP_regL_regLNode *node = new compareAndSwapL_regP_regL_regLNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndSwapP_regP_regP_regP_rule: {
      compareAndSwapP_regP_regP_regPNode *node = new compareAndSwapP_regP_regP_regPNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapB_regP_regI_regI_rule: {
      weakCompareAndSwapB_regP_regI_regINode *node = new weakCompareAndSwapB_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapB4_regP_regI_regI_rule: {
      weakCompareAndSwapB4_regP_regI_regINode *node = new weakCompareAndSwapB4_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapB_acq_regP_regI_regI_rule: {
      weakCompareAndSwapB_acq_regP_regI_regINode *node = new weakCompareAndSwapB_acq_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapB4_acq_regP_regI_regI_rule: {
      weakCompareAndSwapB4_acq_regP_regI_regINode *node = new weakCompareAndSwapB4_acq_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapS_regP_regI_regI_rule: {
      weakCompareAndSwapS_regP_regI_regINode *node = new weakCompareAndSwapS_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapS4_regP_regI_regI_rule: {
      weakCompareAndSwapS4_regP_regI_regINode *node = new weakCompareAndSwapS4_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapS_acq_regP_regI_regI_rule: {
      weakCompareAndSwapS_acq_regP_regI_regINode *node = new weakCompareAndSwapS_acq_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapS4_acq_regP_regI_regI_rule: {
      weakCompareAndSwapS4_acq_regP_regI_regINode *node = new weakCompareAndSwapS4_acq_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapI_regP_regI_regI_rule: {
      weakCompareAndSwapI_regP_regI_regINode *node = new weakCompareAndSwapI_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapI_acq_regP_regI_regI_rule: {
      weakCompareAndSwapI_acq_regP_regI_regINode *node = new weakCompareAndSwapI_acq_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapN_regP_regN_regN_rule: {
      weakCompareAndSwapN_regP_regN_regNNode *node = new weakCompareAndSwapN_regP_regN_regNNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapN_acq_regP_regN_regN_rule: {
      weakCompareAndSwapN_acq_regP_regN_regNNode *node = new weakCompareAndSwapN_acq_regP_regN_regNNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapL_regP_regL_regL_rule: {
      weakCompareAndSwapL_regP_regL_regLNode *node = new weakCompareAndSwapL_regP_regL_regLNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapL_acq_regP_regL_regL_rule: {
      weakCompareAndSwapL_acq_regP_regL_regLNode *node = new weakCompareAndSwapL_acq_regP_regL_regLNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapP_regP_regP_regP_rule: {
      weakCompareAndSwapP_regP_regP_regPNode *node = new weakCompareAndSwapP_regP_regP_regPNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case weakCompareAndSwapP_acq_regP_regP_regP_rule: {
      weakCompareAndSwapP_acq_regP_regP_regPNode *node = new weakCompareAndSwapP_acq_regP_regP_regPNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeB_regP_regI_regI_rule: {
      compareAndExchangeB_regP_regI_regINode *node = new compareAndExchangeB_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeB4_regP_regI_regI_rule: {
      compareAndExchangeB4_regP_regI_regINode *node = new compareAndExchangeB4_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeB_acq_regP_regI_regI_rule: {
      compareAndExchangeB_acq_regP_regI_regINode *node = new compareAndExchangeB_acq_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeB4_acq_regP_regI_regI_rule: {
      compareAndExchangeB4_acq_regP_regI_regINode *node = new compareAndExchangeB4_acq_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeS_regP_regI_regI_rule: {
      compareAndExchangeS_regP_regI_regINode *node = new compareAndExchangeS_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeS4_regP_regI_regI_rule: {
      compareAndExchangeS4_regP_regI_regINode *node = new compareAndExchangeS4_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeS_acq_regP_regI_regI_rule: {
      compareAndExchangeS_acq_regP_regI_regINode *node = new compareAndExchangeS_acq_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeS4_acq_regP_regI_regI_rule: {
      compareAndExchangeS4_acq_regP_regI_regINode *node = new compareAndExchangeS4_acq_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeI_regP_regI_regI_rule: {
      compareAndExchangeI_regP_regI_regINode *node = new compareAndExchangeI_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeI_acq_regP_regI_regI_rule: {
      compareAndExchangeI_acq_regP_regI_regINode *node = new compareAndExchangeI_acq_regP_regI_regINode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeN_regP_regN_regN_rule: {
      compareAndExchangeN_regP_regN_regNNode *node = new compareAndExchangeN_regP_regN_regNNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeN_acq_regP_regN_regN_rule: {
      compareAndExchangeN_acq_regP_regN_regNNode *node = new compareAndExchangeN_acq_regP_regN_regNNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeL_regP_regL_regL_rule: {
      compareAndExchangeL_regP_regL_regLNode *node = new compareAndExchangeL_regP_regL_regLNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeL_acq_regP_regL_regL_rule: {
      compareAndExchangeL_acq_regP_regL_regLNode *node = new compareAndExchangeL_acq_regP_regL_regLNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case compareAndExchangeP_regP_regP_regP_rule: {
      compareAndExchangeP_regP_regP_regPNode *node = new compareAndExchangeP_regP_regP_regPNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeP_acq_regP_regP_regP_rule: {
      compareAndExchangeP_acq_regP_regP_regPNode *node = new compareAndExchangeP_acq_regP_regP_regPNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->set_opnd_array(5, MachOperGenerator(FLAGSREGCR0));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case getAndAddB_rule: {
      getAndAddBNode *node = new getAndAddBNode();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndAddB4_rule: {
      getAndAddB4Node *node = new getAndAddB4Node();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(IREGISRC));
      node->set_opnd_array(5, MachOperGenerator(IREGISRC));
      node->set_opnd_array(6, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndAddS_rule: {
      getAndAddSNode *node = new getAndAddSNode();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndAddS4_rule: {
      getAndAddS4Node *node = new getAndAddS4Node();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(IREGISRC));
      node->set_opnd_array(5, MachOperGenerator(IREGISRC));
      node->set_opnd_array(6, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndAddI_rule: {
      getAndAddINode *node = new getAndAddINode();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndAddL_rule: {
      getAndAddLNode *node = new getAndAddLNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLDST));
      node->set_opnd_array(4, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndSetB_rule: {
      getAndSetBNode *node = new getAndSetBNode();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndSetB4_rule: {
      getAndSetB4Node *node = new getAndSetB4Node();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(IREGISRC));
      node->set_opnd_array(5, MachOperGenerator(IREGISRC));
      node->set_opnd_array(6, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndSetS_rule: {
      getAndSetSNode *node = new getAndSetSNode();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndSetS4_rule: {
      getAndSetS4Node *node = new getAndSetS4Node();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(IREGISRC));
      node->set_opnd_array(5, MachOperGenerator(IREGISRC));
      node->set_opnd_array(6, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndSetI_rule: {
      getAndSetINode *node = new getAndSetINode();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndSetL_rule: {
      getAndSetLNode *node = new getAndSetLNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLDST));
      node->set_opnd_array(4, MachOperGenerator(FLAGSREGCR0));
      return node;
    }
  case getAndSetP_rule: {
      getAndSetPNode *node = new getAndSetPNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPDST));
      node->set_opnd_array(4, MachOperGenerator(FLAGSREGCR0));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case getAndSetN_rule: {
      getAndSetNNode *node = new getAndSetNNode();
      node->set_opnd_array(3, MachOperGenerator(IREGNDST));
      node->set_opnd_array(4, MachOperGenerator(FLAGSREGCR0));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addI_reg_reg_rule: {
      addI_reg_regNode *node = new addI_reg_regNode();
      return node;
    }
  case tree_addI_addI_addI_reg_reg_Ex_rule: {
      tree_addI_addI_addI_reg_reg_ExNode *node = new tree_addI_addI_addI_reg_reg_ExNode();
      return node;
    }
  case tree_addI_addI_addI_reg_reg_Ex_1_rule: {
      tree_addI_addI_addI_reg_reg_Ex_1Node *node = new tree_addI_addI_addI_reg_reg_Ex_1Node();
      return node;
    }
  case tree_addI_addI_addI_reg_reg_Ex_0_rule: {
      tree_addI_addI_addI_reg_reg_Ex_0Node *node = new tree_addI_addI_addI_reg_reg_Ex_0Node();
      return node;
    }
  case tree_addI_addI_addI_reg_reg_Ex_2_rule: {
      tree_addI_addI_addI_reg_reg_Ex_2Node *node = new tree_addI_addI_addI_reg_reg_Ex_2Node();
      return node;
    }
  case addI_reg_imm16_rule: {
      addI_reg_imm16Node *node = new addI_reg_imm16Node();
      return node;
    }
  case addI_reg_immhi16_rule: {
      addI_reg_immhi16Node *node = new addI_reg_immhi16Node();
      return node;
    }
  case addI_reg_imm32_rule: {
      addI_reg_imm32Node *node = new addI_reg_imm32Node();
      return node;
    }
  case addL_reg_reg_rule: {
      addL_reg_regNode *node = new addL_reg_regNode();
      return node;
    }
  case tree_addL_addL_addL_reg_reg_Ex_rule: {
      tree_addL_addL_addL_reg_reg_ExNode *node = new tree_addL_addL_addL_reg_reg_ExNode();
      return node;
    }
  case tree_addL_addL_addL_reg_reg_Ex_1_rule: {
      tree_addL_addL_addL_reg_reg_Ex_1Node *node = new tree_addL_addL_addL_reg_reg_Ex_1Node();
      return node;
    }
  case tree_addL_addL_addL_reg_reg_Ex_0_rule: {
      tree_addL_addL_addL_reg_reg_Ex_0Node *node = new tree_addL_addL_addL_reg_reg_Ex_0Node();
      return node;
    }
  case tree_addL_addL_addL_reg_reg_Ex_2_rule: {
      tree_addL_addL_addL_reg_reg_Ex_2Node *node = new tree_addL_addL_addL_reg_reg_Ex_2Node();
      return node;
    }
  case addI_regL_regL_rule: {
      addI_regL_regLNode *node = new addI_regL_regLNode();
      return node;
    }
  case addL_reg_imm16_rule: {
      addL_reg_imm16Node *node = new addL_reg_imm16Node();
      return node;
    }
  case addL_reg_immhi16_rule: {
      addL_reg_immhi16Node *node = new addL_reg_immhi16Node();
      return node;
    }
  case addL_reg_imm34_rule: {
      addL_reg_imm34Node *node = new addL_reg_imm34Node();
      return node;
    }
  case addP_reg_reg_rule: {
      addP_reg_regNode *node = new addP_reg_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_imm16_rule: {
      addP_reg_imm16Node *node = new addP_reg_imm16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_immhi16_rule: {
      addP_reg_immhi16Node *node = new addP_reg_immhi16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_imm34_rule: {
      addP_reg_imm34Node *node = new addP_reg_imm34Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subI_reg_reg_rule: {
      subI_reg_regNode *node = new subI_reg_regNode();
      return node;
    }
  case subI_imm16_reg_rule: {
      subI_imm16_regNode *node = new subI_imm16_regNode();
      return node;
    }
  case absI_reg_Ex_rule: {
      absI_reg_ExNode *node = new absI_reg_ExNode();
      return node;
    }
  case negI_regI_rule: {
      negI_regINode *node = new negI_regINode();
      return node;
    }
  case subL_reg_reg_rule: {
      subL_reg_regNode *node = new subL_reg_regNode();
      return node;
    }
  case subI_regL_regL_rule: {
      subI_regL_regLNode *node = new subI_regL_regLNode();
      return node;
    }
  case absL_reg_Ex_rule: {
      absL_reg_ExNode *node = new absL_reg_ExNode();
      return node;
    }
  case negL_reg_reg_rule: {
      negL_reg_regNode *node = new negL_reg_regNode();
      return node;
    }
  case negI_con0_regL_rule: {
      negI_con0_regLNode *node = new negI_con0_regLNode();
      return node;
    }
  case mulI_reg_reg_rule: {
      mulI_reg_regNode *node = new mulI_reg_regNode();
      return node;
    }
  case mulI_reg_imm16_rule: {
      mulI_reg_imm16Node *node = new mulI_reg_imm16Node();
      return node;
    }
  case mulL_reg_reg_rule: {
      mulL_reg_regNode *node = new mulL_reg_regNode();
      return node;
    }
  case mulHighL_reg_reg_rule: {
      mulHighL_reg_regNode *node = new mulHighL_reg_regNode();
      return node;
    }
  case mulL_reg_imm16_rule: {
      mulL_reg_imm16Node *node = new mulL_reg_imm16Node();
      return node;
    }
  case divI_reg_immIvalueMinus1_rule: {
      divI_reg_immIvalueMinus1Node *node = new divI_reg_immIvalueMinus1Node();
      return node;
    }
  case divI_reg_regnotMinus1_rule: {
      divI_reg_regnotMinus1Node *node = new divI_reg_regnotMinus1Node();
      return node;
    }
  case divI_reg_reg_Ex_rule: {
      divI_reg_reg_ExNode *node = new divI_reg_reg_ExNode();
      return node;
    }
  case divL_reg_immLvalueMinus1_rule: {
      divL_reg_immLvalueMinus1Node *node = new divL_reg_immLvalueMinus1Node();
      return node;
    }
  case divL_reg_regnotMinus1_rule: {
      divL_reg_regnotMinus1Node *node = new divL_reg_regnotMinus1Node();
      return node;
    }
  case divL_reg_reg_Ex_rule: {
      divL_reg_reg_ExNode *node = new divL_reg_reg_ExNode();
      return node;
    }
  case modI_reg_reg_Ex_rule: {
      modI_reg_reg_ExNode *node = new modI_reg_reg_ExNode();
      return node;
    }
  case modL_reg_reg_Ex_rule: {
      modL_reg_reg_ExNode *node = new modL_reg_reg_ExNode();
      return node;
    }
  case udivI_reg_reg_rule: {
      udivI_reg_regNode *node = new udivI_reg_regNode();
      return node;
    }
  case umodI_reg_reg_rule: {
      umodI_reg_regNode *node = new umodI_reg_regNode();
      return node;
    }
  case udivL_reg_reg_rule: {
      udivL_reg_regNode *node = new udivL_reg_regNode();
      return node;
    }
  case umodL_reg_reg_rule: {
      umodL_reg_regNode *node = new umodL_reg_regNode();
      return node;
    }
  case lShiftI_reg_reg_Ex_rule: {
      lShiftI_reg_reg_ExNode *node = new lShiftI_reg_reg_ExNode();
      return node;
    }
  case lShiftI_reg_imm_rule: {
      lShiftI_reg_immNode *node = new lShiftI_reg_immNode();
      return node;
    }
  case lShiftI_andI_immInegpow2_imm5_rule: {
      lShiftI_andI_immInegpow2_imm5Node *node = new lShiftI_andI_immInegpow2_imm5Node();
      return node;
    }
  case lShiftI_andI_immInegpow2_rShiftI_imm5_rule: {
      lShiftI_andI_immInegpow2_rShiftI_imm5Node *node = new lShiftI_andI_immInegpow2_rShiftI_imm5Node();
      return node;
    }
  case lShiftL_regL_regI_Ex_rule: {
      lShiftL_regL_regI_ExNode *node = new lShiftL_regL_regI_ExNode();
      return node;
    }
  case lshiftL_regL_immI_rule: {
      lshiftL_regL_immINode *node = new lshiftL_regL_immINode();
      return node;
    }
  case lShiftL_regI_immGE32_rule: {
      lShiftL_regI_immGE32Node *node = new lShiftL_regI_immGE32Node();
      return node;
    }
  case scaledPositiveI2L_lShiftL_convI2L_reg_imm6_rule: {
      scaledPositiveI2L_lShiftL_convI2L_reg_imm6Node *node = new scaledPositiveI2L_lShiftL_convI2L_reg_imm6Node();
      return node;
    }
  case arShiftI_reg_reg_Ex_rule: {
      arShiftI_reg_reg_ExNode *node = new arShiftI_reg_reg_ExNode();
      return node;
    }
  case arShiftI_reg_imm_rule: {
      arShiftI_reg_immNode *node = new arShiftI_reg_immNode();
      return node;
    }
  case arShiftL_regL_regI_Ex_rule: {
      arShiftL_regL_regI_ExNode *node = new arShiftL_regL_regI_ExNode();
      return node;
    }
  case arShiftL_regL_immI_rule: {
      arShiftL_regL_immINode *node = new arShiftL_regL_immINode();
      return node;
    }
  case convL2I_arShiftL_regL_immI_rule: {
      convL2I_arShiftL_regL_immINode *node = new convL2I_arShiftL_regL_immINode();
      return node;
    }
  case urShiftI_reg_reg_Ex_rule: {
      urShiftI_reg_reg_ExNode *node = new urShiftI_reg_reg_ExNode();
      return node;
    }
  case urShiftI_reg_imm_rule: {
      urShiftI_reg_immNode *node = new urShiftI_reg_immNode();
      return node;
    }
  case urShiftL_regL_regI_Ex_rule: {
      urShiftL_regL_regI_ExNode *node = new urShiftL_regL_regI_ExNode();
      return node;
    }
  case urShiftL_regL_immI_rule: {
      urShiftL_regL_immINode *node = new urShiftL_regL_immINode();
      return node;
    }
  case convL2I_urShiftL_regL_immI_rule: {
      convL2I_urShiftL_regL_immINode *node = new convL2I_urShiftL_regL_immINode();
      return node;
    }
  case shrP_convP2X_reg_imm6_rule: {
      shrP_convP2X_reg_imm6Node *node = new shrP_convP2X_reg_imm6Node();
      return node;
    }
  case andI_urShiftI_regI_immI_immIpow2minus1_rule: {
      andI_urShiftI_regI_immI_immIpow2minus1Node *node = new andI_urShiftI_regI_immI_immIpow2minus1Node();
      return node;
    }
  case andL_urShiftL_regL_immI_immLpow2minus1_rule: {
      andL_urShiftL_regL_immI_immLpow2minus1Node *node = new andL_urShiftL_regL_immI_immLpow2minus1Node();
      return node;
    }
  case sxtI_reg_rule: {
      sxtI_regNode *node = new sxtI_regNode();
      return node;
    }
  case rotlI_reg_immi8_rule: {
      rotlI_reg_immi8Node *node = new rotlI_reg_immi8Node();
      return node;
    }
  case rotlI_reg_immi8_0_rule: {
      rotlI_reg_immi8_0Node *node = new rotlI_reg_immi8_0Node();
      return node;
    }
  case rotrI_reg_immi8_rule: {
      rotrI_reg_immi8Node *node = new rotrI_reg_immi8Node();
      return node;
    }
  case rotrI_reg_immi8_0_rule: {
      rotrI_reg_immi8_0Node *node = new rotrI_reg_immi8_0Node();
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
  case divF_reg_reg_rule: {
      divF_reg_regNode *node = new divF_reg_regNode();
      return node;
    }
  case divD_reg_reg_rule: {
      divD_reg_regNode *node = new divD_reg_regNode();
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
  case negF_reg_rule: {
      negF_regNode *node = new negF_regNode();
      return node;
    }
  case negD_reg_rule: {
      negD_regNode *node = new negD_regNode();
      return node;
    }
  case negF_absF_reg_rule: {
      negF_absF_regNode *node = new negF_absF_regNode();
      return node;
    }
  case negD_absD_reg_rule: {
      negD_absD_regNode *node = new negD_absD_regNode();
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
  case roundDouble_nop_rule: {
      roundDouble_nopNode *node = new roundDouble_nopNode();
      return node;
    }
  case roundFloat_nop_rule: {
      roundFloat_nopNode *node = new roundFloat_nopNode();
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
  case mnsubF_reg_reg_rule: {
      mnsubF_reg_regNode *node = new mnsubF_reg_regNode();
      return node;
    }
  case mnsubF_reg_reg_0_rule: {
      mnsubF_reg_reg_0Node *node = new mnsubF_reg_reg_0Node();
      return node;
    }
  case mnsubD_reg_reg_rule: {
      mnsubD_reg_regNode *node = new mnsubD_reg_regNode();
      return node;
    }
  case mnsubD_reg_reg_0_rule: {
      mnsubD_reg_reg_0Node *node = new mnsubD_reg_reg_0Node();
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
  case msubF_reg_reg_rule: {
      msubF_reg_regNode *node = new msubF_reg_regNode();
      return node;
    }
  case msubD_reg_reg_rule: {
      msubD_reg_regNode *node = new msubD_reg_regNode();
      return node;
    }
  case andI_reg_reg_rule: {
      andI_reg_regNode *node = new andI_reg_regNode();
      return node;
    }
  case andI_reg_immIhi16_rule: {
      andI_reg_immIhi16Node *node = new andI_reg_immIhi16Node();
      return node;
    }
  case andI_reg_uimm16_rule: {
      andI_reg_uimm16Node *node = new andI_reg_uimm16Node();
      return node;
    }
  case andI_reg_immInegpow2_rule: {
      andI_reg_immInegpow2Node *node = new andI_reg_immInegpow2Node();
      return node;
    }
  case andI_reg_immIpow2minus1_rule: {
      andI_reg_immIpow2minus1Node *node = new andI_reg_immIpow2minus1Node();
      return node;
    }
  case andI_reg_immIpowerOf2_rule: {
      andI_reg_immIpowerOf2Node *node = new andI_reg_immIpowerOf2Node();
      return node;
    }
  case andL_reg_reg_rule: {
      andL_reg_regNode *node = new andL_reg_regNode();
      return node;
    }
  case andL_reg_uimm16_rule: {
      andL_reg_uimm16Node *node = new andL_reg_uimm16Node();
      return node;
    }
  case andL_reg_immLnegpow2_rule: {
      andL_reg_immLnegpow2Node *node = new andL_reg_immLnegpow2Node();
      return node;
    }
  case andL_reg_immLpow2minus1_rule: {
      andL_reg_immLpow2minus1Node *node = new andL_reg_immLpow2minus1Node();
      return node;
    }
  case convL2I_andL_reg_immLpow2minus1_rule: {
      convL2I_andL_reg_immLpow2minus1Node *node = new convL2I_andL_reg_immLpow2minus1Node();
      return node;
    }
  case orI_reg_reg_rule: {
      orI_reg_regNode *node = new orI_reg_regNode();
      return node;
    }
  case tree_orI_orI_orI_reg_reg_Ex_rule: {
      tree_orI_orI_orI_reg_reg_ExNode *node = new tree_orI_orI_orI_reg_reg_ExNode();
      return node;
    }
  case tree_orI_orI_orI_reg_reg_Ex_1_rule: {
      tree_orI_orI_orI_reg_reg_Ex_1Node *node = new tree_orI_orI_orI_reg_reg_Ex_1Node();
      return node;
    }
  case tree_orI_orI_orI_reg_reg_Ex_0_rule: {
      tree_orI_orI_orI_reg_reg_Ex_0Node *node = new tree_orI_orI_orI_reg_reg_Ex_0Node();
      return node;
    }
  case tree_orI_orI_orI_reg_reg_Ex_2_rule: {
      tree_orI_orI_orI_reg_reg_Ex_2Node *node = new tree_orI_orI_orI_reg_reg_Ex_2Node();
      return node;
    }
  case orI_reg_uimm16_rule: {
      orI_reg_uimm16Node *node = new orI_reg_uimm16Node();
      return node;
    }
  case orL_reg_reg_rule: {
      orL_reg_regNode *node = new orL_reg_regNode();
      return node;
    }
  case orI_regL_regL_rule: {
      orI_regL_regLNode *node = new orI_regL_regLNode();
      return node;
    }
  case orL_reg_uimm16_rule: {
      orL_reg_uimm16Node *node = new orL_reg_uimm16Node();
      return node;
    }
  case xorI_reg_reg_rule: {
      xorI_reg_regNode *node = new xorI_reg_regNode();
      return node;
    }
  case tree_xorI_xorI_xorI_reg_reg_Ex_rule: {
      tree_xorI_xorI_xorI_reg_reg_ExNode *node = new tree_xorI_xorI_xorI_reg_reg_ExNode();
      return node;
    }
  case tree_xorI_xorI_xorI_reg_reg_Ex_1_rule: {
      tree_xorI_xorI_xorI_reg_reg_Ex_1Node *node = new tree_xorI_xorI_xorI_reg_reg_Ex_1Node();
      return node;
    }
  case tree_xorI_xorI_xorI_reg_reg_Ex_0_rule: {
      tree_xorI_xorI_xorI_reg_reg_Ex_0Node *node = new tree_xorI_xorI_xorI_reg_reg_Ex_0Node();
      return node;
    }
  case tree_xorI_xorI_xorI_reg_reg_Ex_2_rule: {
      tree_xorI_xorI_xorI_reg_reg_Ex_2Node *node = new tree_xorI_xorI_xorI_reg_reg_Ex_2Node();
      return node;
    }
  case xorI_reg_uimm16_rule: {
      xorI_reg_uimm16Node *node = new xorI_reg_uimm16Node();
      return node;
    }
  case xorL_reg_reg_rule: {
      xorL_reg_regNode *node = new xorL_reg_regNode();
      return node;
    }
  case xorI_regL_regL_rule: {
      xorI_regL_regLNode *node = new xorI_regL_regLNode();
      return node;
    }
  case xorL_reg_uimm16_rule: {
      xorL_reg_uimm16Node *node = new xorL_reg_uimm16Node();
      return node;
    }
  case notI_reg_rule: {
      notI_regNode *node = new notI_regNode();
      return node;
    }
  case notL_reg_rule: {
      notL_regNode *node = new notL_regNode();
      return node;
    }
  case andcI_reg_reg_rule: {
      andcI_reg_regNode *node = new andcI_reg_regNode();
      return node;
    }
  case andcI_reg_reg_0_rule: {
      andcI_reg_reg_0Node *node = new andcI_reg_reg_0Node();
      return node;
    }
  case moveL2D_reg_rule: {
      moveL2D_regNode *node = new moveL2D_regNode();
      return node;
    }
  case stkI_to_regI_rule: {
      stkI_to_regINode *node = new stkI_to_regINode();
      return node;
    }
  case regI_to_stkI_rule: {
      regI_to_stkINode *node = new regI_to_stkINode();
      return node;
    }
  case stkL_to_regL_rule: {
      stkL_to_regLNode *node = new stkL_to_regLNode();
      return node;
    }
  case regL_to_stkL_rule: {
      regL_to_stkLNode *node = new regL_to_stkLNode();
      return node;
    }
  case moveF2I_stack_reg_rule: {
      moveF2I_stack_regNode *node = new moveF2I_stack_regNode();
      return node;
    }
  case moveF2I_reg_stack_rule: {
      moveF2I_reg_stackNode *node = new moveF2I_reg_stackNode();
      return node;
    }
  case moveI2F_stack_reg_rule: {
      moveI2F_stack_regNode *node = new moveI2F_stack_regNode();
      return node;
    }
  case moveI2F_reg_stack_rule: {
      moveI2F_reg_stackNode *node = new moveI2F_reg_stackNode();
      return node;
    }
  case moveD2L_stack_reg_rule: {
      moveD2L_stack_regNode *node = new moveD2L_stack_regNode();
      return node;
    }
  case moveD2L_reg_stack_rule: {
      moveD2L_reg_stackNode *node = new moveD2L_reg_stackNode();
      return node;
    }
  case moveL2D_stack_reg_rule: {
      moveL2D_stack_regNode *node = new moveL2D_stack_regNode();
      return node;
    }
  case moveL2D_reg_stack_rule: {
      moveL2D_reg_stackNode *node = new moveL2D_reg_stackNode();
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
  case castVV8_rule: {
      castVV8Node *node = new castVV8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castVV16_rule: {
      castVV16Node *node = new castVV16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case checkCastPP_rule: {
      checkCastPPNode *node = new checkCastPPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case convI2Bool_reg__cntlz_Ex_rule: {
      convI2Bool_reg__cntlz_ExNode *node = new convI2Bool_reg__cntlz_ExNode();
      return node;
    }
  case convI2Bool_reg__cmove_rule: {
      convI2Bool_reg__cmoveNode *node = new convI2Bool_reg__cmoveNode();
      node->set_opnd_array(2, MachOperGenerator(FLAGSREG));
      return node;
    }
  case xorI_convI2Bool_reg_immIvalue1__cntlz_Ex_rule: {
      xorI_convI2Bool_reg_immIvalue1__cntlz_ExNode *node = new xorI_convI2Bool_reg_immIvalue1__cntlz_ExNode();
      return node;
    }
  case xorI_convI2Bool_reg_immIvalue1__cmove_rule: {
      xorI_convI2Bool_reg_immIvalue1__cmoveNode *node = new xorI_convI2Bool_reg_immIvalue1__cmoveNode();
      node->set_opnd_array(3, MachOperGenerator(FLAGSREG));
      return node;
    }
  case convI2Bool_andI_reg_immIpowerOf2_rule: {
      convI2Bool_andI_reg_immIpowerOf2Node *node = new convI2Bool_andI_reg_immIpowerOf2Node();
      return node;
    }
  case convP2Bool_reg__cntlz_Ex_rule: {
      convP2Bool_reg__cntlz_ExNode *node = new convP2Bool_reg__cntlz_ExNode();
      return node;
    }
  case convP2Bool_reg__cmove_rule: {
      convP2Bool_reg__cmoveNode *node = new convP2Bool_reg__cmoveNode();
      node->set_opnd_array(2, MachOperGenerator(FLAGSREG));
      return node;
    }
  case xorI_convP2Bool_reg__cntlz_Ex_rule: {
      xorI_convP2Bool_reg__cntlz_ExNode *node = new xorI_convP2Bool_reg__cntlz_ExNode();
      return node;
    }
  case xorI_convP2Bool_reg_immIvalue1__cmove_rule: {
      xorI_convP2Bool_reg_immIvalue1__cmoveNode *node = new xorI_convP2Bool_reg_immIvalue1__cmoveNode();
      node->set_opnd_array(3, MachOperGenerator(FLAGSREG));
      return node;
    }
  case cmpLTMask_reg_reg_Ex_rule: {
      cmpLTMask_reg_reg_ExNode *node = new cmpLTMask_reg_reg_ExNode();
      return node;
    }
  case cmpLTMask_reg_immI0_rule: {
      cmpLTMask_reg_immI0Node *node = new cmpLTMask_reg_immI0Node();
      return node;
    }
  case convB2I_reg_rule: {
      convB2I_regNode *node = new convB2I_regNode();
      return node;
    }
  case convS2I_reg_rule: {
      convS2I_regNode *node = new convS2I_regNode();
      return node;
    }
  case sxtI_L2L_reg_rule: {
      sxtI_L2L_regNode *node = new sxtI_L2L_regNode();
      return node;
    }
  case convL2I_reg_rule: {
      convL2I_regNode *node = new convL2I_regNode();
      return node;
    }
  case convD2I_reg_ExEx_rule: {
      convD2I_reg_ExExNode *node = new convD2I_reg_ExExNode();
      return node;
    }
  case convD2I_reg_mffprd_ExEx_rule: {
      convD2I_reg_mffprd_ExExNode *node = new convD2I_reg_mffprd_ExExNode();
      return node;
    }
  case convF2I_regF_ExEx_rule: {
      convF2I_regF_ExExNode *node = new convF2I_regF_ExExNode();
      return node;
    }
  case convF2I_regF_mffprd_ExEx_rule: {
      convF2I_regF_mffprd_ExExNode *node = new convF2I_regF_mffprd_ExExNode();
      return node;
    }
  case convI2L_reg_rule: {
      convI2L_regNode *node = new convI2L_regNode();
      return node;
    }
  case zeroExtendL_regI_rule: {
      zeroExtendL_regINode *node = new zeroExtendL_regINode();
      return node;
    }
  case zeroExtendL_regL_rule: {
      zeroExtendL_regLNode *node = new zeroExtendL_regLNode();
      return node;
    }
  case convF2L_reg_ExEx_rule: {
      convF2L_reg_ExExNode *node = new convF2L_reg_ExExNode();
      return node;
    }
  case convF2L_reg_mffprd_ExEx_rule: {
      convF2L_reg_mffprd_ExExNode *node = new convF2L_reg_mffprd_ExExNode();
      return node;
    }
  case convD2L_reg_ExEx_rule: {
      convD2L_reg_ExExNode *node = new convD2L_reg_ExExNode();
      return node;
    }
  case convD2L_reg_mffprd_ExEx_rule: {
      convD2L_reg_mffprd_ExExNode *node = new convD2L_reg_mffprd_ExExNode();
      return node;
    }
  case convD2F_reg_rule: {
      convD2F_regNode *node = new convD2F_regNode();
      return node;
    }
  case convI2F_ireg_Ex_rule: {
      convI2F_ireg_ExNode *node = new convI2F_ireg_ExNode();
      return node;
    }
  case convI2F_ireg_fcfids_Ex_rule: {
      convI2F_ireg_fcfids_ExNode *node = new convI2F_ireg_fcfids_ExNode();
      return node;
    }
  case convI2F_ireg_mtfprd_Ex_rule: {
      convI2F_ireg_mtfprd_ExNode *node = new convI2F_ireg_mtfprd_ExNode();
      return node;
    }
  case convL2F_ireg_fcfids_Ex_rule: {
      convL2F_ireg_fcfids_ExNode *node = new convL2F_ireg_fcfids_ExNode();
      return node;
    }
  case convL2F_ireg_mtfprd_Ex_rule: {
      convL2F_ireg_mtfprd_ExNode *node = new convL2F_ireg_mtfprd_ExNode();
      return node;
    }
  case convI2D_reg_Ex_rule: {
      convI2D_reg_ExNode *node = new convI2D_reg_ExNode();
      return node;
    }
  case convI2D_reg_mtfprd_Ex_rule: {
      convI2D_reg_mtfprd_ExNode *node = new convI2D_reg_mtfprd_ExNode();
      return node;
    }
  case convL2D_reg_Ex_rule: {
      convL2D_reg_ExNode *node = new convL2D_reg_ExNode();
      return node;
    }
  case convL2D_reg_mtfprd_Ex_rule: {
      convL2D_reg_mtfprd_ExNode *node = new convL2D_reg_mtfprd_ExNode();
      return node;
    }
  case convF2D_reg_rule: {
      convF2D_regNode *node = new convF2D_regNode();
      return node;
    }
  case cmpI_reg_reg_rule: {
      cmpI_reg_regNode *node = new cmpI_reg_regNode();
      return node;
    }
  case cmpI_reg_imm16_rule: {
      cmpI_reg_imm16Node *node = new cmpI_reg_imm16Node();
      return node;
    }
  case testI_reg_imm_rule: {
      testI_reg_immNode *node = new testI_reg_immNode();
      return node;
    }
  case cmpL_reg_reg_rule: {
      cmpL_reg_regNode *node = new cmpL_reg_regNode();
      return node;
    }
  case cmpL_reg_imm16_rule: {
      cmpL_reg_imm16Node *node = new cmpL_reg_imm16Node();
      return node;
    }
  case cmpUL_reg_reg_rule: {
      cmpUL_reg_regNode *node = new cmpUL_reg_regNode();
      return node;
    }
  case cmpUL_reg_imm16_rule: {
      cmpUL_reg_imm16Node *node = new cmpUL_reg_imm16Node();
      return node;
    }
  case testL_reg_reg_rule: {
      testL_reg_regNode *node = new testL_reg_regNode();
      return node;
    }
  case testL_reg_imm_rule: {
      testL_reg_immNode *node = new testL_reg_immNode();
      return node;
    }
  case cmpL3_reg_reg_rule: {
      cmpL3_reg_regNode *node = new cmpL3_reg_regNode();
      return node;
    }
  case rangeCheck_iReg_uimm15_rule: {
      rangeCheck_iReg_uimm15Node *node = new rangeCheck_iReg_uimm15Node();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case rangeCheck_iReg_iReg_rule: {
      rangeCheck_iReg_iRegNode *node = new rangeCheck_iReg_iRegNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case rangeCheck_uimm15_iReg_rule: {
      rangeCheck_uimm15_iRegNode *node = new rangeCheck_uimm15_iRegNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case compU_reg_reg_rule: {
      compU_reg_regNode *node = new compU_reg_regNode();
      return node;
    }
  case compU_reg_uimm16_rule: {
      compU_reg_uimm16Node *node = new compU_reg_uimm16Node();
      return node;
    }
  case zeroCheckN_iReg_imm0_rule: {
      zeroCheckN_iReg_imm0Node *node = new zeroCheckN_iReg_imm0Node();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpN_reg_reg_rule: {
      cmpN_reg_regNode *node = new cmpN_reg_regNode();
      return node;
    }
  case cmpN_reg_imm0_rule: {
      cmpN_reg_imm0Node *node = new cmpN_reg_imm0Node();
      return node;
    }
  case zeroCheckP_reg_imm0_rule: {
      zeroCheckP_reg_imm0Node *node = new zeroCheckP_reg_imm0Node();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpP_reg_reg_rule: {
      cmpP_reg_regNode *node = new cmpP_reg_regNode();
      return node;
    }
  case cmpP_reg_null_rule: {
      cmpP_reg_nullNode *node = new cmpP_reg_nullNode();
      return node;
    }
  case cmpP_reg_imm16_rule: {
      cmpP_reg_imm16Node *node = new cmpP_reg_imm16Node();
      return node;
    }
  case cmpFUnordered_reg_reg_rule: {
      cmpFUnordered_reg_regNode *node = new cmpFUnordered_reg_regNode();
      return node;
    }
  case cmpF_reg_reg_Ex_rule: {
      cmpF_reg_reg_ExNode *node = new cmpF_reg_reg_ExNode();
      return node;
    }
  case cmpF3_reg_reg_rule: {
      cmpF3_reg_regNode *node = new cmpF3_reg_regNode();
      return node;
    }
  case cmpDUnordered_reg_reg_rule: {
      cmpDUnordered_reg_regNode *node = new cmpDUnordered_reg_regNode();
      return node;
    }
  case cmpD_reg_reg_Ex_rule: {
      cmpD_reg_reg_ExNode *node = new cmpD_reg_reg_ExNode();
      return node;
    }
  case cmpD3_reg_reg_rule: {
      cmpD3_reg_regNode *node = new cmpD3_reg_regNode();
      return node;
    }
  case cmprb_Digit_reg_reg_rule: {
      cmprb_Digit_reg_regNode *node = new cmprb_Digit_reg_regNode();
      node->set_opnd_array(2, MachOperGenerator(IREGISRC));
      node->set_opnd_array(3, MachOperGenerator(FLAGSREG));
      return node;
    }
  case cmprb_LowerCase_reg_reg_rule: {
      cmprb_LowerCase_reg_regNode *node = new cmprb_LowerCase_reg_regNode();
      node->set_opnd_array(2, MachOperGenerator(IREGISRC));
      node->set_opnd_array(3, MachOperGenerator(FLAGSREG));
      return node;
    }
  case cmprb_UpperCase_reg_reg_rule: {
      cmprb_UpperCase_reg_regNode *node = new cmprb_UpperCase_reg_regNode();
      node->set_opnd_array(2, MachOperGenerator(IREGISRC));
      node->set_opnd_array(3, MachOperGenerator(FLAGSREG));
      return node;
    }
  case cmprb_Whitespace_reg_reg_rule: {
      cmprb_Whitespace_reg_regNode *node = new cmprb_Whitespace_reg_regNode();
      node->set_opnd_array(2, MachOperGenerator(IREGISRC));
      node->set_opnd_array(3, MachOperGenerator(FLAGSREG));
      return node;
    }
  case cmprb_Whitespace_reg_reg_prefixed_rule: {
      cmprb_Whitespace_reg_reg_prefixedNode *node = new cmprb_Whitespace_reg_reg_prefixedNode();
      node->set_opnd_array(2, MachOperGenerator(IREGISRC));
      node->set_opnd_array(3, MachOperGenerator(FLAGSREG));
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
  case branchConFar_rule: {
      branchConFarNode *node = new branchConFarNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case branchLoopEnd_rule: {
      branchLoopEndNode *node = new branchLoopEndNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case branchLoopEndFar_rule: {
      branchLoopEndFarNode *node = new branchLoopEndFarNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case partialSubtypeCheck_rule: {
      partialSubtypeCheckNode *node = new partialSubtypeCheckNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPDST));
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      return node;
    }
  case cmpFastLock_rule: {
      cmpFastLockNode *node = new cmpFastLockNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPDST));
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->_rtm_counters = _leaf->as_FastLock()->rtm_counters();
      node->_stack_rtm_counters = _leaf->as_FastLock()->stack_rtm_counters();
      return node;
    }
  case cmpFastLock_tm_rule: {
      cmpFastLock_tmNode *node = new cmpFastLock_tmNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPDST));
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->_rtm_counters = _leaf->as_FastLock()->rtm_counters();
      node->_stack_rtm_counters = _leaf->as_FastLock()->stack_rtm_counters();
      return node;
    }
  case cmpFastUnlock_rule: {
      cmpFastUnlockNode *node = new cmpFastUnlockNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPDST));
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      return node;
    }
  case cmpFastUnlock_tm_rule: {
      cmpFastUnlock_tmNode *node = new cmpFastUnlock_tmNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPDST));
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      return node;
    }
  case align_addr_rule: {
      align_addrNode *node = new align_addrNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case array_size_rule: {
      array_sizeNode *node = new array_sizeNode();
      return node;
    }
  case inlineCallClearArrayShort_rule: {
      inlineCallClearArrayShortNode *node = new inlineCallClearArrayShortNode();
      return node;
    }
  case inlineCallClearArrayLarge_rule: {
      inlineCallClearArrayLargeNode *node = new inlineCallClearArrayLargeNode();
      node->set_opnd_array(3, MachOperGenerator(IREGLDST));
      return node;
    }
  case inlineCallClearArray_rule: {
      inlineCallClearArrayNode *node = new inlineCallClearArrayNode();
      return node;
    }
  case string_compareL_rule: {
      string_compareLNode *node = new string_compareLNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      return node;
    }
  case string_compareU_rule: {
      string_compareUNode *node = new string_compareUNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      return node;
    }
  case string_compareLU_rule: {
      string_compareLUNode *node = new string_compareLUNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      return node;
    }
  case string_compareUL_rule: {
      string_compareULNode *node = new string_compareULNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      return node;
    }
  case string_equalsL_rule: {
      string_equalsLNode *node = new string_equalsLNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      return node;
    }
  case string_equalsU_rule: {
      string_equalsUNode *node = new string_equalsUNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      return node;
    }
  case array_equalsB_rule: {
      array_equalsBNode *node = new array_equalsBNode();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      return node;
    }
  case array_equalsC_rule: {
      array_equalsCNode *node = new array_equalsCNode();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOf_imm1_char_U_rule: {
      indexOf_imm1_char_UNode *node = new indexOf_imm1_char_UNode();
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOf_imm1_char_L_rule: {
      indexOf_imm1_char_LNode *node = new indexOf_imm1_char_LNode();
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOf_imm1_char_UL_rule: {
      indexOf_imm1_char_ULNode *node = new indexOf_imm1_char_ULNode();
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOf_imm1_U_rule: {
      indexOf_imm1_UNode *node = new indexOf_imm1_UNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOf_imm1_L_rule: {
      indexOf_imm1_LNode *node = new indexOf_imm1_LNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOf_imm1_UL_rule: {
      indexOf_imm1_ULNode *node = new indexOf_imm1_ULNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOfChar_U_rule: {
      indexOfChar_UNode *node = new indexOfChar_UNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOfChar_L_rule: {
      indexOfChar_LNode *node = new indexOfChar_LNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOf_imm_U_rule: {
      indexOf_imm_UNode *node = new indexOf_imm_UNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(IREGIDST));
      node->set_opnd_array(8, MachOperGenerator(IREGIDST));
      node->set_opnd_array(9, MachOperGenerator(IREGIDST));
      node->set_opnd_array(10, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOf_imm_L_rule: {
      indexOf_imm_LNode *node = new indexOf_imm_LNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(IREGIDST));
      node->set_opnd_array(8, MachOperGenerator(IREGIDST));
      node->set_opnd_array(9, MachOperGenerator(IREGIDST));
      node->set_opnd_array(10, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOf_imm_UL_rule: {
      indexOf_imm_ULNode *node = new indexOf_imm_ULNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGIDST));
      node->set_opnd_array(7, MachOperGenerator(IREGIDST));
      node->set_opnd_array(8, MachOperGenerator(IREGIDST));
      node->set_opnd_array(9, MachOperGenerator(IREGIDST));
      node->set_opnd_array(10, MachOperGenerator(IREGIDST));
      return node;
    }
  case indexOf_U_rule: {
      indexOf_UNode *node = new indexOf_UNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGLDST));
      node->set_opnd_array(7, MachOperGenerator(IREGLDST));
      node->set_opnd_array(8, MachOperGenerator(IREGLDST));
      node->set_opnd_array(9, MachOperGenerator(IREGLDST));
      return node;
    }
  case indexOf_L_rule: {
      indexOf_LNode *node = new indexOf_LNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGLDST));
      node->set_opnd_array(7, MachOperGenerator(IREGLDST));
      node->set_opnd_array(8, MachOperGenerator(IREGLDST));
      node->set_opnd_array(9, MachOperGenerator(IREGLDST));
      return node;
    }
  case indexOf_UL_rule: {
      indexOf_ULNode *node = new indexOf_ULNode();
      node->set_opnd_array(5, MachOperGenerator(IREGIDST));
      node->set_opnd_array(6, MachOperGenerator(IREGLDST));
      node->set_opnd_array(7, MachOperGenerator(IREGLDST));
      node->set_opnd_array(8, MachOperGenerator(IREGLDST));
      node->set_opnd_array(9, MachOperGenerator(IREGLDST));
      return node;
    }
  case string_compress_rule: {
      string_compressNode *node = new string_compressNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGLDST));
      node->set_opnd_array(6, MachOperGenerator(IREGLDST));
      node->set_opnd_array(7, MachOperGenerator(IREGLDST));
      node->set_opnd_array(8, MachOperGenerator(IREGLDST));
      node->set_opnd_array(9, MachOperGenerator(IREGLDST));
      return node;
    }
  case string_inflate_rule: {
      string_inflateNode *node = new string_inflateNode();
      node->set_opnd_array(4, MachOperGenerator(IREGLDST));
      node->set_opnd_array(5, MachOperGenerator(IREGLDST));
      node->set_opnd_array(6, MachOperGenerator(IREGLDST));
      node->set_opnd_array(7, MachOperGenerator(IREGLDST));
      node->set_opnd_array(8, MachOperGenerator(IREGLDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case count_positives_rule: {
      count_positivesNode *node = new count_positivesNode();
      node->set_opnd_array(3, MachOperGenerator(IREGIDST));
      node->set_opnd_array(4, MachOperGenerator(IREGLDST));
      node->set_opnd_array(5, MachOperGenerator(IREGLDST));
      return node;
    }
  case encode_iso_array_rule: {
      encode_iso_arrayNode *node = new encode_iso_arrayNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGLDST));
      node->set_opnd_array(6, MachOperGenerator(IREGLDST));
      node->set_opnd_array(7, MachOperGenerator(IREGLDST));
      node->set_opnd_array(8, MachOperGenerator(IREGLDST));
      node->set_opnd_array(9, MachOperGenerator(IREGLDST));
      return node;
    }
  case encode_ascii_array_rule: {
      encode_ascii_arrayNode *node = new encode_ascii_arrayNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGLDST));
      node->set_opnd_array(6, MachOperGenerator(IREGLDST));
      node->set_opnd_array(7, MachOperGenerator(IREGLDST));
      node->set_opnd_array(8, MachOperGenerator(IREGLDST));
      node->set_opnd_array(9, MachOperGenerator(IREGLDST));
      return node;
    }
  case minI_reg_reg_Ex_rule: {
      minI_reg_reg_ExNode *node = new minI_reg_reg_ExNode();
      return node;
    }
  case minI_reg_reg_isel_rule: {
      minI_reg_reg_iselNode *node = new minI_reg_reg_iselNode();
      return node;
    }
  case maxI_reg_reg_Ex_rule: {
      maxI_reg_reg_ExNode *node = new maxI_reg_reg_ExNode();
      return node;
    }
  case maxI_reg_reg_isel_rule: {
      maxI_reg_reg_iselNode *node = new maxI_reg_reg_iselNode();
      return node;
    }
  case popCountI_rule: {
      popCountINode *node = new popCountINode();
      return node;
    }
  case popCountL_rule: {
      popCountLNode *node = new popCountLNode();
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
  case countTrailingZerosI_Ex_rule: {
      countTrailingZerosI_ExNode *node = new countTrailingZerosI_ExNode();
      return node;
    }
  case countTrailingZerosI_cnttzw_rule: {
      countTrailingZerosI_cnttzwNode *node = new countTrailingZerosI_cnttzwNode();
      return node;
    }
  case countTrailingZerosL_Ex_rule: {
      countTrailingZerosL_ExNode *node = new countTrailingZerosL_ExNode();
      return node;
    }
  case countTrailingZerosL_cnttzd_rule: {
      countTrailingZerosL_cnttzdNode *node = new countTrailingZerosL_cnttzdNode();
      return node;
    }
  case bytes_reverse_int_Ex_rule: {
      bytes_reverse_int_ExNode *node = new bytes_reverse_int_ExNode();
      return node;
    }
  case bytes_reverse_int_vec_rule: {
      bytes_reverse_int_vecNode *node = new bytes_reverse_int_vecNode();
      node->set_opnd_array(2, MachOperGenerator(VECX));
      return node;
    }
  case bytes_reverse_int_rule: {
      bytes_reverse_intNode *node = new bytes_reverse_intNode();
      return node;
    }
  case bytes_reverse_long_Ex_rule: {
      bytes_reverse_long_ExNode *node = new bytes_reverse_long_ExNode();
      return node;
    }
  case bytes_reverse_long_vec_rule: {
      bytes_reverse_long_vecNode *node = new bytes_reverse_long_vecNode();
      node->set_opnd_array(2, MachOperGenerator(VECX));
      return node;
    }
  case bytes_reverse_long_rule: {
      bytes_reverse_longNode *node = new bytes_reverse_longNode();
      return node;
    }
  case bytes_reverse_ushort_Ex_rule: {
      bytes_reverse_ushort_ExNode *node = new bytes_reverse_ushort_ExNode();
      return node;
    }
  case bytes_reverse_ushort_rule: {
      bytes_reverse_ushortNode *node = new bytes_reverse_ushortNode();
      return node;
    }
  case bytes_reverse_short_Ex_rule: {
      bytes_reverse_short_ExNode *node = new bytes_reverse_short_ExNode();
      return node;
    }
  case bytes_reverse_short_rule: {
      bytes_reverse_shortNode *node = new bytes_reverse_shortNode();
      return node;
    }
  case loadI_reversed_rule: {
      loadI_reversedNode *node = new loadI_reversedNode();
      return node;
    }
  case loadI_reversed_acquire_rule: {
      loadI_reversed_acquireNode *node = new loadI_reversed_acquireNode();
      return node;
    }
  case loadL_reversed_rule: {
      loadL_reversedNode *node = new loadL_reversedNode();
      return node;
    }
  case loadL_reversed_acquire_rule: {
      loadL_reversed_acquireNode *node = new loadL_reversed_acquireNode();
      return node;
    }
  case loadUS_reversed_rule: {
      loadUS_reversedNode *node = new loadUS_reversedNode();
      return node;
    }
  case loadUS_reversed_acquire_rule: {
      loadUS_reversed_acquireNode *node = new loadUS_reversed_acquireNode();
      return node;
    }
  case loadS_reversed_rule: {
      loadS_reversedNode *node = new loadS_reversedNode();
      return node;
    }
  case loadS_reversed_acquire_rule: {
      loadS_reversed_acquireNode *node = new loadS_reversed_acquireNode();
      return node;
    }
  case storeI_reversed_rule: {
      storeI_reversedNode *node = new storeI_reversedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeL_reversed_rule: {
      storeL_reversedNode *node = new storeL_reversedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeUS_reversed_rule: {
      storeUS_reversedNode *node = new storeUS_reversedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeS_reversed_rule: {
      storeS_reversedNode *node = new storeS_reversedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl8B_reg_Ex_rule: {
      repl8B_reg_ExNode *node = new repl8B_reg_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl8B_immI0_rule: {
      repl8B_immI0Node *node = new repl8B_immI0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl8B_immIminus1_rule: {
      repl8B_immIminus1Node *node = new repl8B_immIminus1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl16B_reg_Ex_rule: {
      repl16B_reg_ExNode *node = new repl16B_reg_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl16B_immI0_rule: {
      repl16B_immI0Node *node = new repl16B_immI0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl16B_immIminus1_rule: {
      repl16B_immIminus1Node *node = new repl16B_immIminus1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl4S_reg_Ex_rule: {
      repl4S_reg_ExNode *node = new repl4S_reg_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl4S_immI0_rule: {
      repl4S_immI0Node *node = new repl4S_immI0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl4S_immIminus1_rule: {
      repl4S_immIminus1Node *node = new repl4S_immIminus1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl8S_reg_Ex_rule: {
      repl8S_reg_ExNode *node = new repl8S_reg_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl8S_immI0_rule: {
      repl8S_immI0Node *node = new repl8S_immI0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl8S_immIminus1_rule: {
      repl8S_immIminus1Node *node = new repl8S_immIminus1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2I_reg_Ex_rule: {
      repl2I_reg_ExNode *node = new repl2I_reg_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2I_immI0_rule: {
      repl2I_immI0Node *node = new repl2I_immI0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2I_immIminus1_rule: {
      repl2I_immIminus1Node *node = new repl2I_immIminus1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl4I_reg_Ex_rule: {
      repl4I_reg_ExNode *node = new repl4I_reg_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl4I_immI0_rule: {
      repl4I_immI0Node *node = new repl4I_immI0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl4I_immIminus1_rule: {
      repl4I_immIminus1Node *node = new repl4I_immIminus1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2F_reg_Ex_rule: {
      repl2F_reg_ExNode *node = new repl2F_reg_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2F_immF_Ex_rule: {
      repl2F_immF_ExNode *node = new repl2F_immF_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2F_immF0_rule: {
      repl2F_immF0Node *node = new repl2F_immF0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16B_reg_rule: {
      vadd16B_regNode *node = new vadd16B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8S_reg_rule: {
      vadd8S_regNode *node = new vadd8S_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4I_reg_rule: {
      vadd4I_regNode *node = new vadd4I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4F_reg_rule: {
      vadd4F_regNode *node = new vadd4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2L_reg_rule: {
      vadd2L_regNode *node = new vadd2L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2D_reg_rule: {
      vadd2D_regNode *node = new vadd2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16B_reg_rule: {
      vsub16B_regNode *node = new vsub16B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8S_reg_rule: {
      vsub8S_regNode *node = new vsub8S_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4I_reg_rule: {
      vsub4I_regNode *node = new vsub4I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4F_reg_rule: {
      vsub4F_regNode *node = new vsub4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2L_reg_rule: {
      vsub2L_regNode *node = new vsub2L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2D_reg_rule: {
      vsub2D_regNode *node = new vsub2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8S_reg_rule: {
      vmul8S_regNode *node = new vmul8S_regNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4I_reg_rule: {
      vmul4I_regNode *node = new vmul4I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4F_reg_rule: {
      vmul4F_regNode *node = new vmul4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2D_reg_rule: {
      vmul2D_regNode *node = new vmul2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv4F_reg_rule: {
      vdiv4F_regNode *node = new vdiv4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv2D_reg_rule: {
      vdiv2D_regNode *node = new vdiv2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs4F_reg_rule: {
      vabs4F_regNode *node = new vabs4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vabs2D_reg_rule: {
      vabs2D_regNode *node = new vabs2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case roundD_reg_rule: {
      roundD_regNode *node = new roundD_regNode();
      return node;
    }
  case vround2D_reg_rule: {
      vround2D_regNode *node = new vround2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vneg4F_reg_rule: {
      vneg4F_regNode *node = new vneg4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vneg2D_reg_rule: {
      vneg2D_regNode *node = new vneg2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt4F_reg_rule: {
      vsqrt4F_regNode *node = new vsqrt4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt2D_reg_rule: {
      vsqrt2D_regNode *node = new vsqrt2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vpopcnt_reg_rule: {
      vpopcnt_regNode *node = new vpopcnt_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma4F_rule: {
      vfma4FNode *node = new vfma4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma4F_neg1_rule: {
      vfma4F_neg1Node *node = new vfma4F_neg1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma4F_neg1_0_rule: {
      vfma4F_neg1_0Node *node = new vfma4F_neg1_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma4F_neg2_rule: {
      vfma4F_neg2Node *node = new vfma4F_neg2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma2D_rule: {
      vfma2DNode *node = new vfma2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma2D_neg1_rule: {
      vfma2D_neg1Node *node = new vfma2D_neg1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma2D_neg1_0_rule: {
      vfma2D_neg1_0Node *node = new vfma2D_neg1_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vfma2D_neg2_rule: {
      vfma2D_neg2Node *node = new vfma2D_neg2Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case overflowAddL_reg_reg_rule: {
      overflowAddL_reg_regNode *node = new overflowAddL_reg_regNode();
      return node;
    }
  case overflowSubL_reg_reg_rule: {
      overflowSubL_reg_regNode *node = new overflowSubL_reg_regNode();
      return node;
    }
  case overflowNegL_reg_rule: {
      overflowNegL_regNode *node = new overflowNegL_regNode();
      return node;
    }
  case overflowMulL_reg_reg_rule: {
      overflowMulL_reg_regNode *node = new overflowMulL_reg_regNode();
      return node;
    }
  case repl4F_reg_Ex_rule: {
      repl4F_reg_ExNode *node = new repl4F_reg_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl4F_immF_Ex_rule: {
      repl4F_immF_ExNode *node = new repl4F_immF_ExNode();
      node->set_opnd_array(2, MachOperGenerator(IREGLDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl4F_immF0_rule: {
      repl4F_immF0Node *node = new repl4F_immF0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2D_reg_Ex_rule: {
      repl2D_reg_ExNode *node = new repl2D_reg_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2D_immD0_rule: {
      repl2D_immD0Node *node = new repl2D_immD0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2L_reg_Ex_rule: {
      repl2L_reg_ExNode *node = new repl2L_reg_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2L_immI0_rule: {
      repl2L_immI0Node *node = new repl2L_immI0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case repl2L_immIminus1_rule: {
      repl2L_immIminus1Node *node = new repl2L_immIminus1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case safePoint_poll_rule: {
      safePoint_pollNode *node = new safePoint_pollNode();
      return node;
    }
  case CallStaticJavaDirect_rule: {
      CallStaticJavaDirectNode *node = new CallStaticJavaDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallDynamicJavaDirectSched_rule: {
      CallDynamicJavaDirectSchedNode *node = new CallDynamicJavaDirectSchedNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallDynamicJavaDirectSched_Ex_rule: {
      CallDynamicJavaDirectSched_ExNode *node = new CallDynamicJavaDirectSched_ExNode();
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
  case CallLeafDirect_Ex_rule: {
      CallLeafDirect_ExNode *node = new CallLeafDirect_ExNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallLeafNoFPDirect_Ex_rule: {
      CallLeafNoFPDirect_ExNode *node = new CallLeafNoFPDirect_ExNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case TailCalljmpInd_rule: {
      TailCalljmpIndNode *node = new TailCalljmpIndNode();
      return node;
    }
  case Ret_rule: {
      RetNode *node = new RetNode();
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
  case ShouldNotReachHere_rule: {
      ShouldNotReachHereNode *node = new ShouldNotReachHereNode();
      node->_halt_reason = _leaf->as_Halt()->_halt_reason;
      node->_reachable   = _leaf->as_Halt()->_reachable;
      return node;
    }
  case tlsLoadP_rule: {
      tlsLoadPNode *node = new tlsLoadPNode();
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
  case compareAndSwapP_shenandoah_rule: {
      compareAndSwapP_shenandoahNode *node = new compareAndSwapP_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->set_opnd_array(6, MachOperGenerator(IREGPDST));
      return node;
    }
  case compareAndSwapP_shenandoah_0_rule: {
      compareAndSwapP_shenandoah_0Node *node = new compareAndSwapP_shenandoah_0Node();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->set_opnd_array(6, MachOperGenerator(IREGPDST));
      return node;
    }
  case compareAndSwapN_shenandoah_rule: {
      compareAndSwapN_shenandoahNode *node = new compareAndSwapN_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGNDST));
      node->set_opnd_array(6, MachOperGenerator(IREGNDST));
      return node;
    }
  case compareAndSwapN_shenandoah_0_rule: {
      compareAndSwapN_shenandoah_0Node *node = new compareAndSwapN_shenandoah_0Node();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGNDST));
      node->set_opnd_array(6, MachOperGenerator(IREGNDST));
      return node;
    }
  case compareAndSwapP_acq_shenandoah_rule: {
      compareAndSwapP_acq_shenandoahNode *node = new compareAndSwapP_acq_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->set_opnd_array(6, MachOperGenerator(IREGPDST));
      return node;
    }
  case compareAndSwapP_acq_shenandoah_0_rule: {
      compareAndSwapP_acq_shenandoah_0Node *node = new compareAndSwapP_acq_shenandoah_0Node();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->set_opnd_array(6, MachOperGenerator(IREGPDST));
      return node;
    }
  case compareAndSwapN_acq_shenandoah_rule: {
      compareAndSwapN_acq_shenandoahNode *node = new compareAndSwapN_acq_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGNDST));
      node->set_opnd_array(6, MachOperGenerator(IREGNDST));
      return node;
    }
  case compareAndSwapN_acq_shenandoah_0_rule: {
      compareAndSwapN_acq_shenandoah_0Node *node = new compareAndSwapN_acq_shenandoah_0Node();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGNDST));
      node->set_opnd_array(6, MachOperGenerator(IREGNDST));
      return node;
    }
  case compareAndExchangeP_shenandoah_rule: {
      compareAndExchangeP_shenandoahNode *node = new compareAndExchangeP_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->set_opnd_array(6, MachOperGenerator(IREGPDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeN_shenandoah_rule: {
      compareAndExchangeN_shenandoahNode *node = new compareAndExchangeN_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNDST));
      node->set_opnd_array(5, MachOperGenerator(IREGNDST));
      node->set_opnd_array(6, MachOperGenerator(IREGNDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangePAcq_shenandoah_rule: {
      compareAndExchangePAcq_shenandoahNode *node = new compareAndExchangePAcq_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->set_opnd_array(6, MachOperGenerator(IREGPDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeNAcq_shenandoah_rule: {
      compareAndExchangeNAcq_shenandoahNode *node = new compareAndExchangeNAcq_shenandoahNode();
      node->set_opnd_array(4, MachOperGenerator(IREGNDST));
      node->set_opnd_array(5, MachOperGenerator(IREGNDST));
      node->set_opnd_array(6, MachOperGenerator(IREGNDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zLoadP_rule: {
      zLoadPNode *node = new zLoadPNode();
      node->set_opnd_array(2, MachOperGenerator(IREGPDST));
      node->set_opnd_array(3, MachOperGenerator(IREGPDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zLoadP_acq_rule: {
      zLoadP_acqNode *node = new zLoadP_acqNode();
      node->set_opnd_array(2, MachOperGenerator(IREGPDST));
      node->set_opnd_array(3, MachOperGenerator(IREGPDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zCompareAndSwapP_rule: {
      zCompareAndSwapPNode *node = new zCompareAndSwapPNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->set_opnd_array(6, MachOperGenerator(IREGPDST));
      return node;
    }
  case zCompareAndSwapP_acq_rule: {
      zCompareAndSwapP_acqNode *node = new zCompareAndSwapP_acqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->set_opnd_array(6, MachOperGenerator(IREGPDST));
      return node;
    }
  case zCompareAndSwapPWeak_rule: {
      zCompareAndSwapPWeakNode *node = new zCompareAndSwapPWeakNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->set_opnd_array(6, MachOperGenerator(IREGPDST));
      return node;
    }
  case zCompareAndSwapPWeak_acq_rule: {
      zCompareAndSwapPWeak_acqNode *node = new zCompareAndSwapPWeak_acqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGIDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->set_opnd_array(6, MachOperGenerator(IREGPDST));
      return node;
    }
  case zCompareAndExchangeP_rule: {
      zCompareAndExchangePNode *node = new zCompareAndExchangePNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zCompareAndExchangeP_acq_rule: {
      zCompareAndExchangeP_acqNode *node = new zCompareAndExchangeP_acqNode();
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
      node->set_opnd_array(5, MachOperGenerator(IREGPDST));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case zGetAndSetP_rule: {
      zGetAndSetPNode *node = new zGetAndSetPNode();
      node->set_opnd_array(3, MachOperGenerator(IREGPDST));
      node->set_opnd_array(4, MachOperGenerator(IREGPDST));
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
// Check adlc -DPPC64=1
#ifndef PPC64
#  error "PPC64 must be defined"
#endif // PPC64
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
