#line 1 "ad_s390_gen.cpp"
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
#include "opto/cfgnode.hpp"
#include "opto/locknode.hpp"


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
  case IMMB_MINUS1:
    return new immB_minus1Oper(_leaf->get_int() );
  case IMMB_N0M1:
    return new immB_n0m1Oper(_leaf->get_int() );
  case IMMS_MINUS1:
    return new immS_minus1Oper(_leaf->get_int() );
  case IMMS_N0M1:
    return new immS_n0m1Oper(_leaf->get_int() );
  case IMMI:
    return new immIOper(_leaf->get_int() );
  case IMMI20:
    return new immI20Oper(_leaf->get_int() );
  case IMMI16:
    return new immI16Oper(_leaf->get_int() );
  case IMMI8:
    return new immI8Oper(_leaf->get_int() );
  case IMMI_0:
    return new immI_0Oper(_leaf->get_int() );
  case IMMI_MINUS1:
    return new immI_minus1Oper(_leaf->get_int() );
  case IMMI_N0M1:
    return new immI_n0m1Oper(_leaf->get_int() );
  case UIMMI:
    return new uimmIOper(_leaf->get_int() );
  case UIMMI16:
    return new uimmI16Oper(_leaf->get_int() );
  case UIMMI12:
    return new uimmI12Oper(_leaf->get_int() );
  case UIMMI8:
    return new uimmI8Oper(_leaf->get_int() );
  case UIMMI6:
    return new uimmI6Oper(_leaf->get_int() );
  case UIMMI5:
    return new uimmI5Oper(_leaf->get_int() );
  case SSLENDW:
    return new SSlenDWOper(_leaf->get_long() );
  case IMMI_1:
    return new immI_1Oper(_leaf->get_int() );
  case IMMI_16:
    return new immI_16Oper(_leaf->get_int() );
  case IMMI_24:
    return new immI_24Oper(_leaf->get_int() );
  case IMMI_255:
    return new immI_255Oper(_leaf->get_int() );
  case IMMI_32_63:
    return new immI_32_63Oper(_leaf->get_int() );
  case UIMMI_LL1:
    return new uimmI_LL1Oper(_leaf->get_int() );
  case UIMMI_LH1:
    return new uimmI_LH1Oper(_leaf->get_int() );
  case IMML:
    return new immLOper(_leaf->get_long() );
  case IMML32:
    return new immL32Oper(_leaf->get_long() );
  case IMML20:
    return new immL20Oper(_leaf->get_long() );
  case IMML16:
    return new immL16Oper(_leaf->get_long() );
  case IMML8:
    return new immL8Oper(_leaf->get_long() );
  case UIMML32:
    return new uimmL32Oper(_leaf->get_long() );
  case UIMML16:
    return new uimmL16Oper(_leaf->get_long() );
  case UIMML12:
    return new uimmL12Oper(_leaf->get_long() );
  case UIMML8:
    return new uimmL8Oper(_leaf->get_long() );
  case IMML_FF:
    return new immL_FFOper(_leaf->get_long() );
  case IMML_FFFF:
    return new immL_FFFFOper(_leaf->get_long() );
  case IMML_FFFFFFFF:
    return new immL_FFFFFFFFOper(_leaf->get_long() );
  case IMML_0:
    return new immL_0Oper(_leaf->get_long() );
  case UIMML_LL1:
    return new uimmL_LL1Oper(_leaf->get_long() );
  case UIMML_LH1:
    return new uimmL_LH1Oper(_leaf->get_long() );
  case UIMML_HL1:
    return new uimmL_HL1Oper(_leaf->get_long() );
  case UIMML_HH1:
    return new uimmL_HH1Oper(_leaf->get_long() );
  case IMML_32BITS:
    return new immL_32bitsOper(_leaf->get_long() );
  case IMMP:
    return new immPOper(_leaf->bottom_type()->is_ptr() );
  case IMMP32:
    return new immP32Oper(_leaf->bottom_type()->is_ptr() );
  case IMMP16:
    return new immP16Oper(_leaf->bottom_type()->is_ptr() );
  case IMMP8:
    return new immP8Oper(_leaf->bottom_type()->is_ptr() );
  case IMMP0:
    return new immP0Oper(_leaf->bottom_type()->is_ptr() );
  case IMMN:
    return new immNOper(_leaf->bottom_type()->is_narrowoop() );
  case IMMNKLASS:
    return new immNKlassOper(_leaf->bottom_type()->is_narrowklass() );
  case IMMN8:
    return new immN8Oper(_leaf->bottom_type()->is_narrowoop() );
  case IMMN0:
    return new immN0Oper(_leaf->bottom_type()->is_narrowoop() );
  case IMMD:
    return new immDOper(_leaf->getd() );
  case IMMDPM0:
    return new immDpm0Oper(_leaf->getd() );
  case IMMDP0:
    return new immDp0Oper(_leaf->getd() );
  case IMMF:
    return new immFOper(_leaf->getf() );
  case IMMFPM0:
    return new immFpm0Oper(_leaf->getf() );
  case IMMFP0:
    return new immFp0Oper(_leaf->getf() );
  case IREGI:
    return new iRegIOper( );
  case NOARG_IREGI:
    return new noArg_iRegIOper( );
  case REVENREGI:
    return new revenRegIOper( );
  case RODDREGI:
    return new roddRegIOper( );
  case RARG1REGI:
    return new rarg1RegIOper( );
  case RARG2REGI:
    return new rarg2RegIOper( );
  case RARG3REGI:
    return new rarg3RegIOper( );
  case RARG4REGI:
    return new rarg4RegIOper( );
  case RARG5REGI:
    return new rarg5RegIOper( );
  case NOODD_IREGI:
    return new noOdd_iRegIOper( );
  case IREGP:
    return new iRegPOper( );
  case THREADREGP:
    return new threadRegPOper( );
  case NOARG_IREGP:
    return new noArg_iRegPOper( );
  case RARG1REGP:
    return new rarg1RegPOper( );
  case RARG2REGP:
    return new rarg2RegPOper( );
  case RARG3REGP:
    return new rarg3RegPOper( );
  case RARG4REGP:
    return new rarg4RegPOper( );
  case RARG5REGP:
    return new rarg5RegPOper( );
  case MEMORYREGP:
    return new memoryRegPOper( );
  case REVENREGP:
    return new revenRegPOper( );
  case RODDREGP:
    return new roddRegPOper( );
  case LOCK_PTR_REGP:
    return new lock_ptr_RegPOper( );
  case RSCRATCH2REGP:
    return new rscratch2RegPOper( );
  case IREGN:
    return new iRegNOper( );
  case NOARG_IREGN:
    return new noArg_iRegNOper( );
  case RARG1REGN:
    return new rarg1RegNOper( );
  case RARG2REGN:
    return new rarg2RegNOper( );
  case RARG3REGN:
    return new rarg3RegNOper( );
  case RARG4REGN:
    return new rarg4RegNOper( );
  case RARG5REGN:
    return new rarg5RegNOper( );
  case IREGL:
    return new iRegLOper( );
  case REVENREGL:
    return new revenRegLOper( );
  case RODDREGL:
    return new roddRegLOper( );
  case RARG1REGL:
    return new rarg1RegLOper( );
  case RARG5REGL:
    return new rarg5RegLOper( );
  case FLAGSREG:
    return new flagsRegOper( );
  case TD_FLAGSREG:
    return new TD_flagsRegOper( );
  case REGD:
    return new regDOper( );
  case RSCRATCHREGD:
    return new rscratchRegDOper( );
  case REGF:
    return new regFOper( );
  case RSCRATCHREGF:
    return new rscratchRegFOper( );
  case INLINE_CACHE_REGP:
    return new inline_cache_regPOper( );
  case COMPILER_METHOD_OOP_REGP:
    return new compiler_method_oop_regPOper( );
  case INTERPRETER_METHOD_OOP_REGP:
    return new interpreter_method_oop_regPOper( );
  case IREGP2N:
    return new iRegP2NOper( );
  case IREGN2P:
    return new iRegN2POper( );
  case INDIRECT:
    return new indirectOper( );
  case INDOFFSET20:
    return new indOffset20Oper(_kids[1]->_leaf->get_long() );
  case INDOFFSET20NARROW:
    return new indOffset20NarrowOper(_kids[1]->_leaf->get_long() );
  case INDOFFSET12:
    return new indOffset12Oper(_kids[1]->_leaf->get_long() );
  case INDOFFSET12NARROW:
    return new indOffset12NarrowOper(_kids[1]->_leaf->get_long() );
  case INDINDEX:
    return new indIndexOper( );
  case INDOFFSET20INDEX:
    return new indOffset20indexOper(_kids[1]->_leaf->get_long() );
  case INDOFFSET20INDEXNARROW:
    return new indOffset20indexNarrowOper(_kids[1]->_leaf->get_long() );
  case INDOFFSET12INDEX:
    return new indOffset12indexOper(_kids[1]->_leaf->get_long() );
  case INDOFFSET12INDEXNARROW:
    return new indOffset12indexNarrowOper(_kids[1]->_leaf->get_long() );
  case STACKSLOTI:
    return new stackSlotIOper( );
  case STACKSLOTP:
    return new stackSlotPOper( );
  case STACKSLOTF:
    return new stackSlotFOper( );
  case STACKSLOTD:
    return new stackSlotDOper( );
  case STACKSLOTL:
    return new stackSlotLOper( );
  case CMPOPT:
    return new cmpOpTOper(_leaf->as_Bool()->_test._test );
  case CMPOPF:
    return new cmpOpFOper(_leaf->as_Bool()->_test._test );
  case CMPOP:
    return new cmpOpOper(_leaf->as_Bool()->_test._test );
  case _DECODEN_IREGN_:    return NULL;
  case _ADDP_MEMORYREGP_IREGL:    return NULL;
  case _ADDP__DECODEN_IREGN__IREGL:    return NULL;
  case _LOADB_MEMORY_:    return NULL;
  case _LOADUB_MEMORY_:    return NULL;
  case _LOADS_MEMORY_:    return NULL;
  case _LOADUS_MEMORY_:    return NULL;
  case _LOADI_MEMORY_:    return NULL;
  case _CONVI2L__LOADI_MEMORY__:    return NULL;
  case _LOADP_MEMORY_:    return NULL;
  case _LOADN_MEMORY_:    return NULL;
  case _LOADNKLASS_MEMORY_:    return NULL;
  case _BINARY_IREGL_IREGN:    return NULL;
  case _BINARY_CMPOP_FLAGSREG:    return NULL;
  case _BINARY_IREGN_IREGN_P2N:    return NULL;
  case _BINARY_IREGN_IMMN0:    return NULL;
  case _BINARY_IREGI_IREGI:    return NULL;
  case _BINARY_IREGI_IMMI16:    return NULL;
  case _BINARY_IREGP_IREGP_N2P:    return NULL;
  case _BINARY_IREGP_IMMP0:    return NULL;
  case _BINARY_CMPOPF_FLAGSREG:    return NULL;
  case _BINARY_REGF_REGF:    return NULL;
  case _BINARY_REGD_REGD:    return NULL;
  case _BINARY_IREGL_IREGL:    return NULL;
  case _BINARY_IREGL_IMML16:    return NULL;
  case _BINARY_RARG5REGP_IREGP_N2P:    return NULL;
  case _BINARY_RARG5REGL_IREGL:    return NULL;
  case _BINARY_RARG5REGI_IREGI:    return NULL;
  case _BINARY_RARG5REGN_IREGN_P2N:    return NULL;
  case _ADDI_IREGI_IREGI:    return NULL;
  case _LOADI_MEMORYRSY_:    return NULL;
  case _ADDI__LOADI_MEMORYRSY__IMMI8:    return NULL;
  case _CONVI2L_IREGI_:    return NULL;
  case _LOADL_MEMORY_:    return NULL;
  case _ADDL_IREGL_IREGL:    return NULL;
  case _LOADL_MEMORYRSY_:    return NULL;
  case _ADDL__LOADL_MEMORYRSY__IMML8:    return NULL;
  case _ADDP_IREGP_N2P_IREGL:    return NULL;
  case _LOADP_MEMORYRSY_:    return NULL;
  case _ADDP__LOADP_MEMORYRSY__IMML8:    return NULL;
  case _CASTP2X_IREGP_N2P_:    return NULL;
  case _LSHIFTI_IREGI_IMMI8:    return NULL;
  case _URSHIFTI_IREGI_IMMI8:    return NULL;
  case _LSHIFTL_IREGL_IMMI8:    return NULL;
  case _URSHIFTL_IREGL_IMMI8:    return NULL;
  case _LOADF_MEMORYRX_:    return NULL;
  case _LOADD_MEMORYRX_:    return NULL;
  case _NEGF_REGF_:    return NULL;
  case _NEGD_REGD_:    return NULL;
  case _BINARY_REGF__LOADF_MEMORYRX_:    return NULL;
  case _BINARY_REGD__LOADD_MEMORYRX_:    return NULL;
  case _BINARY__LOADF_MEMORYRX__REGF:    return NULL;
  case _BINARY__LOADD_MEMORYRX__REGD:    return NULL;
  case _ABSF_REGF_:    return NULL;
  case _ABSD_REGD_:    return NULL;
  case _CONVF2D_REGF_:    return NULL;
  case _SQRTD__CONVF2D_REGF__:    return NULL;
  case _CONVF2D_MEMORYRX_:    return NULL;
  case _SQRTD__CONVF2D_MEMORYRX__:    return NULL;
  case _LSHIFTI_IREGI_IMMI_16:    return NULL;
  case _LSHIFTI_IREGI_IMMI_24:    return NULL;
  case _RSHIFTL_IREGL_IMMI_32_63:    return NULL;
  case _CMPU_IREGI_UIMMI16:    return NULL;
  case _CMPU_IREGI_IREGI:    return NULL;
  case _CMPP_IREGP_N2P_IMMP0:    return NULL;
  case _CMPN_IREGN_P2N_IMMN0:    return NULL;
  case _ABSI_IREGI_:    return NULL;
  case _CMPI_IREGI_IREGI:    return NULL;
  case _CMPL_IREGL_IREGL:    return NULL;
  case _CMPP_IREGP_IREGP:    return NULL;
  case _CMPP__DECODEN_IREGN___DECODEN_IREGN_:    return NULL;
  case _CMPI_IREGI_IMMI8:    return NULL;
  case _CMPU_IREGI_UIMMI8:    return NULL;
  case _CMPL_IREGL_IMML8:    return NULL;
  case _CMPP_IREGP_IMMP8:    return NULL;
  case _CMPP__DECODEN_IREGN__IMMP0:    return NULL;
  case _DECODEN_IMMN8_:    return NULL;
  case _CMPP__DECODEN_IREGN___DECODEN_IMMN8_:    return NULL;
  case _PARTIALSUBTYPECHECK_RARG2REGP_RARG3REGP:    return NULL;
  case _BINARY_IREGP_IREGP:    return NULL;
  case _BINARY_IREGP_RARG2REGI:    return NULL;
  case _BINARY_IREGP_RARG5REGI:    return NULL;
  case _BINARY_IREGP_IREGI:    return NULL;
  case _BINARY_IMMP_IMMI_1:    return NULL;
  case _BINARY_IREGP_IMMI16:    return NULL;
  case _BINARY_IREGP_IMMI:    return NULL;
  
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
  case stkP_to_regP_rule: {
      stkP_to_regPNode *node = new stkP_to_regPNode();
      return node;
    }
  case regP_to_stkP_rule: {
      regP_to_stkPNode *node = new regP_to_stkPNode();
      return node;
    }
  case stkF_to_regF_rule: {
      stkF_to_regFNode *node = new stkF_to_regFNode();
      return node;
    }
  case regF_to_stkF_rule: {
      regF_to_stkFNode *node = new regF_to_stkFNode();
      return node;
    }
  case stkD_to_regD_rule: {
      stkD_to_regDNode *node = new stkD_to_regDNode();
      return node;
    }
  case regD_to_stkD_rule: {
      regD_to_stkDNode *node = new regD_to_stkDNode();
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
  case loadRange_rule: {
      loadRangeNode *node = new loadRangeNode();
      return node;
    }
  case loadL_rule: {
      loadLNode *node = new loadLNode();
      return node;
    }
  case loadL_unaligned_rule: {
      loadL_unalignedNode *node = new loadL_unalignedNode();
      return node;
    }
  case loadP_rule: {
      loadPNode *node = new loadPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castP2X_loadP_rule: {
      castP2X_loadPNode *node = new castP2X_loadPNode();
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
  case loadD_rule: {
      loadDNode *node = new loadDNode();
      return node;
    }
  case loadD_unaligned_rule: {
      loadD_unalignedNode *node = new loadD_unalignedNode();
      return node;
    }
  case loadConI_rule: {
      loadConINode *node = new loadConINode();
      node->_opnd_array[1] = new immIOper(_leaf->get_int() );
      return node;
    }
  case loadConI16_rule: {
      loadConI16Node *node = new loadConI16Node();
      node->_opnd_array[1] = new immI16Oper(_leaf->get_int() );
      return node;
    }
  case loadConI_0_rule: {
      loadConI_0Node *node = new loadConI_0Node();
      return node;
    }
  case loadConUI16_rule: {
      loadConUI16Node *node = new loadConUI16Node();
      node->_opnd_array[1] = new uimmI16Oper(_leaf->get_int() );
      return node;
    }
  case loadConL_pcrelTOC_rule: {
      loadConL_pcrelTOCNode *node = new loadConL_pcrelTOCNode();
      node->_opnd_array[1] = new immLOper(_leaf->get_long() );
      return node;
    }
  case loadConL32_rule: {
      loadConL32Node *node = new loadConL32Node();
      node->_opnd_array[1] = new immL32Oper(_leaf->get_long() );
      return node;
    }
  case loadConL16_rule: {
      loadConL16Node *node = new loadConL16Node();
      node->_opnd_array[1] = new immL16Oper(_leaf->get_long() );
      return node;
    }
  case loadConL_0_rule: {
      loadConL_0Node *node = new loadConL_0Node();
      return node;
    }
  case loadConP_pcrelTOC_rule: {
      loadConP_pcrelTOCNode *node = new loadConP_pcrelTOCNode();
      node->_opnd_array[1] = new immPOper(_leaf->bottom_type()->is_ptr() );
      return node;
    }
  case loadConP0_rule: {
      loadConP0Node *node = new loadConP0Node();
      return node;
    }
  case loadConF_dynTOC_rule: {
      loadConF_dynTOCNode *node = new loadConF_dynTOCNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConD_dynTOC_rule: {
      loadConD_dynTOCNode *node = new loadConD_dynTOCNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConF0_rule: {
      loadConF0Node *node = new loadConF0Node();
      node->_opnd_array[1] = new immFp0Oper(_leaf->getf() );
      return node;
    }
  case loadConD0_rule: {
      loadConD0Node *node = new loadConD0Node();
      node->_opnd_array[1] = new immDp0Oper(_leaf->getd() );
      return node;
    }
  case storeB_rule: {
      storeBNode *node = new storeBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeCM_rule: {
      storeCMNode *node = new storeCMNode();
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
  case prefetchAlloc_rule: {
      prefetchAllocNode *node = new prefetchAllocNode();
      return node;
    }
  case memInitB_rule: {
      memInitBNode *node = new memInitBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case memInitC_rule: {
      memInitCNode *node = new memInitCNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case memInitI_rule: {
      memInitINode *node = new memInitINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case memInitL_rule: {
      memInitLNode *node = new memInitLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case memInitP_rule: {
      memInitPNode *node = new memInitPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case negL_reg_reg_rule: {
      negL_reg_regNode *node = new negL_reg_regNode();
      return node;
    }
  case loadN_rule: {
      loadNNode *node = new loadNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadNKlass_rule: {
      loadNKlassNode *node = new loadNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConN_rule: {
      loadConNNode *node = new loadConNNode();
      node->_opnd_array[1] = new immNOper(_leaf->bottom_type()->is_narrowoop() );
      return node;
    }
  case loadConN0_rule: {
      loadConN0Node *node = new loadConN0Node();
      return node;
    }
  case loadConNKlass_rule: {
      loadConNKlassNode *node = new loadConNKlassNode();
      node->_opnd_array[1] = new immNKlassOper(_leaf->bottom_type()->is_narrowklass() );
      return node;
    }
  case decodeLoadN_rule: {
      decodeLoadNNode *node = new decodeLoadNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeLoadNKlass_rule: {
      decodeLoadNKlassNode *node = new decodeLoadNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeLoadConNKlass_rule: {
      decodeLoadConNKlassNode *node = new decodeLoadConNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_rule: {
      decodeNNode *node = new decodeNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeKlass_rule: {
      decodeKlassNode *node = new decodeKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_NN_rule: {
      decodeN_NNNode *node = new decodeN_NNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_base_rule: {
      decodeN_baseNode *node = new decodeN_baseNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_NN_base_rule: {
      decodeN_NN_baseNode *node = new decodeN_NN_baseNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_Ex_rule: {
      decodeN_ExNode *node = new decodeN_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeN_NN_Ex_rule: {
      decodeN_NN_ExNode *node = new decodeN_NN_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_rule: {
      encodePNode *node = new encodePNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeKlass_rule: {
      encodeKlassNode *node = new encodeKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_NN_rule: {
      encodeP_NNNode *node = new encodeP_NNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_base_rule: {
      encodeP_baseNode *node = new encodeP_baseNode();
      node->set_opnd_array(4, MachOperGenerator(IREGN));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_NN_base_rule: {
      encodeP_NN_baseNode *node = new encodeP_NN_baseNode();
      node->set_opnd_array(3, MachOperGenerator(IMML));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_Ex_rule: {
      encodeP_ExNode *node = new encodeP_ExNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeP_NN_Ex_rule: {
      encodeP_NN_ExNode *node = new encodeP_NN_ExNode();
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
  case compN_iRegN_rule: {
      compN_iRegNNode *node = new compN_iRegNNode();
      return node;
    }
  case compN_iRegN_immN_rule: {
      compN_iRegN_immNNode *node = new compN_iRegN_immNNode();
      return node;
    }
  case compNKlass_iRegN_immN_rule: {
      compNKlass_iRegN_immNNode *node = new compNKlass_iRegN_immNNode();
      return node;
    }
  case compN_iRegN_immN0_rule: {
      compN_iRegN_immN0Node *node = new compN_iRegN_immN0Node();
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
      return node;
    }
  case unnecessary_membar_volatile_rule: {
      unnecessary_membar_volatileNode *node = new unnecessary_membar_volatileNode();
      return node;
    }
  case membar_CPUOrder_rule: {
      membar_CPUOrderNode *node = new membar_CPUOrderNode();
      return node;
    }
  case membar_storestore_rule: {
      membar_storestoreNode *node = new membar_storestoreNode();
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
  case castX2P_rule: {
      castX2PNode *node = new castX2PNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castP2X_rule: {
      castP2XNode *node = new castP2XNode();
      return node;
    }
  case stfSSD_rule: {
      stfSSDNode *node = new stfSSDNode();
      return node;
    }
  case stfSSF_rule: {
      stfSSFNode *node = new stfSSFNode();
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
  case cmovI_reg_rule: {
      cmovI_regNode *node = new cmovI_regNode();
      return node;
    }
  case cmovI_imm_rule: {
      cmovI_immNode *node = new cmovI_immNode();
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
  case cmovL_reg_rule: {
      cmovL_regNode *node = new cmovL_regNode();
      return node;
    }
  case cmovL_imm_rule: {
      cmovL_immNode *node = new cmovL_immNode();
      return node;
    }
  case tlsLoadP_rule: {
      tlsLoadPNode *node = new tlsLoadPNode();
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
  case compareAndSwapI_bool_rule: {
      compareAndSwapI_boolNode *node = new compareAndSwapI_boolNode();
      return node;
    }
  case compareAndSwapL_bool_rule: {
      compareAndSwapL_boolNode *node = new compareAndSwapL_boolNode();
      return node;
    }
  case compareAndSwapP_bool_rule: {
      compareAndSwapP_boolNode *node = new compareAndSwapP_boolNode();
      return node;
    }
  case compareAndSwapN_bool_rule: {
      compareAndSwapN_boolNode *node = new compareAndSwapN_boolNode();
      return node;
    }
  case addI_mem_imm8_atomic_no_res_rule: {
      addI_mem_imm8_atomic_no_resNode *node = new addI_mem_imm8_atomic_no_resNode();
      return node;
    }
  case addI_mem_imm16_atomic_rule: {
      addI_mem_imm16_atomicNode *node = new addI_mem_imm16_atomicNode();
      node->set_opnd_array(3, MachOperGenerator(IREGI));
      node->set_opnd_array(4, MachOperGenerator(IREGI));
      return node;
    }
  case addI_mem_imm32_atomic_rule: {
      addI_mem_imm32_atomicNode *node = new addI_mem_imm32_atomicNode();
      node->set_opnd_array(3, MachOperGenerator(IREGI));
      node->set_opnd_array(4, MachOperGenerator(IREGI));
      return node;
    }
  case addI_mem_reg_atomic_rule: {
      addI_mem_reg_atomicNode *node = new addI_mem_reg_atomicNode();
      node->set_opnd_array(3, MachOperGenerator(IREGI));
      node->set_opnd_array(4, MachOperGenerator(IREGI));
      return node;
    }
  case addL_mem_imm8_atomic_no_res_rule: {
      addL_mem_imm8_atomic_no_resNode *node = new addL_mem_imm8_atomic_no_resNode();
      return node;
    }
  case addL_mem_imm16_atomic_rule: {
      addL_mem_imm16_atomicNode *node = new addL_mem_imm16_atomicNode();
      node->set_opnd_array(3, MachOperGenerator(IREGL));
      node->set_opnd_array(4, MachOperGenerator(IREGL));
      return node;
    }
  case addL_mem_imm32_atomic_rule: {
      addL_mem_imm32_atomicNode *node = new addL_mem_imm32_atomicNode();
      node->set_opnd_array(3, MachOperGenerator(IREGL));
      node->set_opnd_array(4, MachOperGenerator(IREGL));
      return node;
    }
  case addL_mem_reg_atomic_rule: {
      addL_mem_reg_atomicNode *node = new addL_mem_reg_atomicNode();
      node->set_opnd_array(3, MachOperGenerator(IREGL));
      node->set_opnd_array(4, MachOperGenerator(IREGL));
      return node;
    }
  case addI_mem_reg_atomic_z196_rule: {
      addI_mem_reg_atomic_z196Node *node = new addI_mem_reg_atomic_z196Node();
      return node;
    }
  case addL_mem_reg_atomic_z196_rule: {
      addL_mem_reg_atomic_z196Node *node = new addL_mem_reg_atomic_z196Node();
      return node;
    }
  case xchgI_reg_mem_rule: {
      xchgI_reg_memNode *node = new xchgI_reg_memNode();
      node->set_opnd_array(3, MachOperGenerator(IREGI));
      return node;
    }
  case xchgL_reg_mem_rule: {
      xchgL_reg_memNode *node = new xchgL_reg_memNode();
      node->set_opnd_array(3, MachOperGenerator(IREGL));
      return node;
    }
  case xchgN_reg_mem_rule: {
      xchgN_reg_memNode *node = new xchgN_reg_memNode();
      node->set_opnd_array(3, MachOperGenerator(IREGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xchgP_reg_mem_rule: {
      xchgP_reg_memNode *node = new xchgP_reg_memNode();
      node->set_opnd_array(3, MachOperGenerator(IREGL));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addI_reg_reg_CISC_rule: {
      addI_reg_reg_CISCNode *node = new addI_reg_reg_CISCNode();
      return node;
    }
  case addI_reg_reg_RISC_rule: {
      addI_reg_reg_RISCNode *node = new addI_reg_reg_RISCNode();
      return node;
    }
  case addI_reg_imm16_CISC_rule: {
      addI_reg_imm16_CISCNode *node = new addI_reg_imm16_CISCNode();
      return node;
    }
  case addI_reg_imm16_RISC_rule: {
      addI_reg_imm16_RISCNode *node = new addI_reg_imm16_RISCNode();
      return node;
    }
  case addI_reg_imm32_rule: {
      addI_reg_imm32Node *node = new addI_reg_imm32Node();
      return node;
    }
  case addI_reg_imm12_rule: {
      addI_reg_imm12Node *node = new addI_reg_imm12Node();
      return node;
    }
  case addI_reg_imm20_rule: {
      addI_reg_imm20Node *node = new addI_reg_imm20Node();
      return node;
    }
  case addI_reg_reg_imm12_rule: {
      addI_reg_reg_imm12Node *node = new addI_reg_reg_imm12Node();
      return node;
    }
  case addI_reg_reg_imm20_rule: {
      addI_reg_reg_imm20Node *node = new addI_reg_reg_imm20Node();
      return node;
    }
  case addI_Reg_mem_rule: {
      addI_Reg_memNode *node = new addI_Reg_memNode();
      return node;
    }
  case addI_Reg_mem_0_rule: {
      addI_Reg_mem_0Node *node = new addI_Reg_mem_0Node();
      return node;
    }
  case addI_mem_imm_rule: {
      addI_mem_immNode *node = new addI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addL_reg_regI_rule: {
      addL_reg_regINode *node = new addL_reg_regINode();
      return node;
    }
  case addL_reg_regI_0_rule: {
      addL_reg_regI_0Node *node = new addL_reg_regI_0Node();
      return node;
    }
  case addL_reg_reg_CISC_rule: {
      addL_reg_reg_CISCNode *node = new addL_reg_reg_CISCNode();
      return node;
    }
  case addL_reg_reg_RISC_rule: {
      addL_reg_reg_RISCNode *node = new addL_reg_reg_RISCNode();
      return node;
    }
  case addL_reg_imm12_rule: {
      addL_reg_imm12Node *node = new addL_reg_imm12Node();
      return node;
    }
  case addL_reg_imm20_rule: {
      addL_reg_imm20Node *node = new addL_reg_imm20Node();
      return node;
    }
  case addL_reg_imm32_rule: {
      addL_reg_imm32Node *node = new addL_reg_imm32Node();
      return node;
    }
  case addL_reg_imm16_CISC_rule: {
      addL_reg_imm16_CISCNode *node = new addL_reg_imm16_CISCNode();
      return node;
    }
  case addL_reg_imm16_RISC_rule: {
      addL_reg_imm16_RISCNode *node = new addL_reg_imm16_RISCNode();
      return node;
    }
  case addL_Reg_memI_rule: {
      addL_Reg_memINode *node = new addL_Reg_memINode();
      return node;
    }
  case addL_Reg_memI_0_rule: {
      addL_Reg_memI_0Node *node = new addL_Reg_memI_0Node();
      return node;
    }
  case addL_Reg_mem_rule: {
      addL_Reg_memNode *node = new addL_Reg_memNode();
      return node;
    }
  case addL_Reg_mem_0_rule: {
      addL_Reg_mem_0Node *node = new addL_Reg_mem_0Node();
      return node;
    }
  case addL_reg_reg_imm12_rule: {
      addL_reg_reg_imm12Node *node = new addL_reg_reg_imm12Node();
      return node;
    }
  case addL_reg_reg_imm20_rule: {
      addL_reg_reg_imm20Node *node = new addL_reg_reg_imm20Node();
      return node;
    }
  case addL_mem_imm_rule: {
      addL_mem_immNode *node = new addL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_reg_LA_rule: {
      addP_reg_reg_LANode *node = new addP_reg_reg_LANode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_reg_CISC_rule: {
      addP_reg_reg_CISCNode *node = new addP_reg_reg_CISCNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_reg_RISC_rule: {
      addP_reg_reg_RISCNode *node = new addP_reg_reg_RISCNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_imm12_rule: {
      addP_reg_imm12Node *node = new addP_reg_imm12Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_imm16_CISC_rule: {
      addP_reg_imm16_CISCNode *node = new addP_reg_imm16_CISCNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_imm16_RISC_rule: {
      addP_reg_imm16_RISCNode *node = new addP_reg_imm16_RISCNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_imm20_rule: {
      addP_reg_imm20Node *node = new addP_reg_imm20Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_imm32_rule: {
      addP_reg_imm32Node *node = new addP_reg_imm32Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_reg_imm12_rule: {
      addP_reg_reg_imm12Node *node = new addP_reg_reg_imm12Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_regN_reg_imm12_rule: {
      addP_regN_reg_imm12Node *node = new addP_regN_reg_imm12Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_reg_reg_imm20_rule: {
      addP_reg_reg_imm20Node *node = new addP_reg_reg_imm20Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_regN_reg_imm20_rule: {
      addP_regN_reg_imm20Node *node = new addP_regN_reg_imm20Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_mem_imm_rule: {
      addP_mem_immNode *node = new addP_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subI_reg_reg_CISC_rule: {
      subI_reg_reg_CISCNode *node = new subI_reg_reg_CISCNode();
      return node;
    }
  case subI_reg_reg_RISC_rule: {
      subI_reg_reg_RISCNode *node = new subI_reg_reg_RISCNode();
      return node;
    }
  case subI_Reg_mem_rule: {
      subI_Reg_memNode *node = new subI_Reg_memNode();
      return node;
    }
  case subI_zero_reg_rule: {
      subI_zero_regNode *node = new subI_zero_regNode();
      return node;
    }
  case subL_reg_reg_CISC_rule: {
      subL_reg_reg_CISCNode *node = new subL_reg_reg_CISCNode();
      return node;
    }
  case subL_reg_reg_RISC_rule: {
      subL_reg_reg_RISCNode *node = new subL_reg_reg_RISCNode();
      return node;
    }
  case subL_reg_regI_CISC_rule: {
      subL_reg_regI_CISCNode *node = new subL_reg_regI_CISCNode();
      return node;
    }
  case subL_Reg_memI_rule: {
      subL_Reg_memINode *node = new subL_Reg_memINode();
      return node;
    }
  case subL_Reg_mem_rule: {
      subL_Reg_memNode *node = new subL_Reg_memNode();
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
  case mulI_reg_imm32_rule: {
      mulI_reg_imm32Node *node = new mulI_reg_imm32Node();
      return node;
    }
  case mulI_Reg_mem_rule: {
      mulI_Reg_memNode *node = new mulI_Reg_memNode();
      return node;
    }
  case mulI_Reg_mem_0_rule: {
      mulI_Reg_mem_0Node *node = new mulI_Reg_mem_0Node();
      return node;
    }
  case mulL_reg_regI_rule: {
      mulL_reg_regINode *node = new mulL_reg_regINode();
      return node;
    }
  case mulL_reg_regI_0_rule: {
      mulL_reg_regI_0Node *node = new mulL_reg_regI_0Node();
      return node;
    }
  case mulL_reg_reg_rule: {
      mulL_reg_regNode *node = new mulL_reg_regNode();
      return node;
    }
  case mulL_reg_imm16_rule: {
      mulL_reg_imm16Node *node = new mulL_reg_imm16Node();
      return node;
    }
  case mulL_reg_imm32_rule: {
      mulL_reg_imm32Node *node = new mulL_reg_imm32Node();
      return node;
    }
  case mulL_Reg_memI_rule: {
      mulL_Reg_memINode *node = new mulL_Reg_memINode();
      return node;
    }
  case mulL_Reg_memI_0_rule: {
      mulL_Reg_memI_0Node *node = new mulL_Reg_memI_0Node();
      return node;
    }
  case mulL_Reg_mem_rule: {
      mulL_Reg_memNode *node = new mulL_Reg_memNode();
      return node;
    }
  case mulL_Reg_mem_0_rule: {
      mulL_Reg_mem_0Node *node = new mulL_Reg_mem_0Node();
      return node;
    }
  case mulHiL_reg_reg_rule: {
      mulHiL_reg_regNode *node = new mulHiL_reg_regNode();
      node->set_opnd_array(3, MachOperGenerator(REVENREGL));
      node->set_opnd_array(4, MachOperGenerator(IREGL));
      return node;
    }
  case divModI_reg_divmod_rule: {
      divModI_reg_divmodNode *node = new divModI_reg_divmodNode();
      return node;
    }
  case divI_reg_reg_rule: {
      divI_reg_regNode *node = new divI_reg_regNode();
      return node;
    }
  case divI_reg_imm16_rule: {
      divI_reg_imm16Node *node = new divI_reg_imm16Node();
      return node;
    }
  case divModL_reg_divmod_rule: {
      divModL_reg_divmodNode *node = new divModL_reg_divmodNode();
      return node;
    }
  case divL_reg_reg_rule: {
      divL_reg_regNode *node = new divL_reg_regNode();
      return node;
    }
  case divL_reg_imm16_rule: {
      divL_reg_imm16Node *node = new divL_reg_imm16Node();
      return node;
    }
  case modI_reg_reg_rule: {
      modI_reg_regNode *node = new modI_reg_regNode();
      return node;
    }
  case modI_reg_imm16_rule: {
      modI_reg_imm16Node *node = new modI_reg_imm16Node();
      return node;
    }
  case modL_reg_reg_rule: {
      modL_reg_regNode *node = new modL_reg_regNode();
      return node;
    }
  case modL_reg_imm16_rule: {
      modL_reg_imm16Node *node = new modL_reg_imm16Node();
      return node;
    }
  case sllI_reg_reg_rule: {
      sllI_reg_regNode *node = new sllI_reg_regNode();
      return node;
    }
  case sllI_reg_imm_rule: {
      sllI_reg_immNode *node = new sllI_reg_immNode();
      return node;
    }
  case sllI_reg_imm_1_rule: {
      sllI_reg_imm_1Node *node = new sllI_reg_imm_1Node();
      return node;
    }
  case sllL_reg_reg_rule: {
      sllL_reg_regNode *node = new sllL_reg_regNode();
      return node;
    }
  case sllL_reg_imm_rule: {
      sllL_reg_immNode *node = new sllL_reg_immNode();
      return node;
    }
  case sllL_reg_imm_1_rule: {
      sllL_reg_imm_1Node *node = new sllL_reg_imm_1Node();
      return node;
    }
  case sraI_reg_reg_rule: {
      sraI_reg_regNode *node = new sraI_reg_regNode();
      return node;
    }
  case sraI_reg_imm_rule: {
      sraI_reg_immNode *node = new sraI_reg_immNode();
      return node;
    }
  case sraL_reg_reg_rule: {
      sraL_reg_regNode *node = new sraL_reg_regNode();
      return node;
    }
  case sraL_reg_imm_rule: {
      sraL_reg_immNode *node = new sraL_reg_immNode();
      return node;
    }
  case srlI_reg_reg_rule: {
      srlI_reg_regNode *node = new srlI_reg_regNode();
      return node;
    }
  case srlI_reg_imm_rule: {
      srlI_reg_immNode *node = new srlI_reg_immNode();
      return node;
    }
  case srlL_reg_reg_rule: {
      srlL_reg_regNode *node = new srlL_reg_regNode();
      return node;
    }
  case srlL_reg_imm_rule: {
      srlL_reg_immNode *node = new srlL_reg_immNode();
      return node;
    }
  case srlP_reg_imm_rule: {
      srlP_reg_immNode *node = new srlP_reg_immNode();
      return node;
    }
  case rotlI_reg_immI8_rule: {
      rotlI_reg_immI8Node *node = new rotlI_reg_immI8Node();
      return node;
    }
  case rotlI_reg_immI8_0_rule: {
      rotlI_reg_immI8_0Node *node = new rotlI_reg_immI8_0Node();
      return node;
    }
  case rotlL_reg_immI8_rule: {
      rotlL_reg_immI8Node *node = new rotlL_reg_immI8Node();
      return node;
    }
  case rotlL_reg_immI8_0_rule: {
      rotlL_reg_immI8_0Node *node = new rotlL_reg_immI8_0Node();
      return node;
    }
  case rotrI_reg_immI8_rule: {
      rotrI_reg_immI8Node *node = new rotrI_reg_immI8Node();
      return node;
    }
  case rotrI_reg_immI8_0_rule: {
      rotrI_reg_immI8_0Node *node = new rotrI_reg_immI8_0Node();
      return node;
    }
  case rotrL_reg_immI8_rule: {
      rotrL_reg_immI8Node *node = new rotrL_reg_immI8Node();
      return node;
    }
  case rotrL_reg_immI8_0_rule: {
      rotrL_reg_immI8_0Node *node = new rotrL_reg_immI8_0Node();
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
  case overflowNegI_rReg_rule: {
      overflowNegI_rRegNode *node = new overflowNegI_rRegNode();
      return node;
    }
  case overflowNegL_rReg_rule: {
      overflowNegL_rRegNode *node = new overflowNegL_rRegNode();
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
  case subF_reg_reg_rule: {
      subF_reg_regNode *node = new subF_reg_regNode();
      return node;
    }
  case subF_reg_mem_rule: {
      subF_reg_memNode *node = new subF_reg_memNode();
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
  case maddF_reg_mem_rule: {
      maddF_reg_memNode *node = new maddF_reg_memNode();
      return node;
    }
  case maddD_reg_mem_rule: {
      maddD_reg_memNode *node = new maddD_reg_memNode();
      return node;
    }
  case msubF_reg_mem_rule: {
      msubF_reg_memNode *node = new msubF_reg_memNode();
      return node;
    }
  case msubD_reg_mem_rule: {
      msubD_reg_memNode *node = new msubD_reg_memNode();
      return node;
    }
  case maddF_mem_reg_rule: {
      maddF_mem_regNode *node = new maddF_mem_regNode();
      return node;
    }
  case maddD_mem_reg_rule: {
      maddD_mem_regNode *node = new maddD_mem_regNode();
      return node;
    }
  case msubF_mem_reg_rule: {
      msubF_mem_regNode *node = new msubF_mem_regNode();
      return node;
    }
  case msubD_mem_reg_rule: {
      msubD_mem_regNode *node = new msubD_mem_regNode();
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
  case divD_reg_reg_rule: {
      divD_reg_regNode *node = new divD_reg_regNode();
      return node;
    }
  case divD_reg_mem_rule: {
      divD_reg_memNode *node = new divD_reg_memNode();
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
  case nabsF_reg_rule: {
      nabsF_regNode *node = new nabsF_regNode();
      return node;
    }
  case nabsD_reg_rule: {
      nabsD_regNode *node = new nabsD_regNode();
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
  case sqrtF_reg_rule: {
      sqrtF_regNode *node = new sqrtF_regNode();
      return node;
    }
  case sqrtD_reg_rule: {
      sqrtD_regNode *node = new sqrtD_regNode();
      return node;
    }
  case sqrtF_mem_rule: {
      sqrtF_memNode *node = new sqrtF_memNode();
      return node;
    }
  case sqrtD_mem_rule: {
      sqrtD_memNode *node = new sqrtD_memNode();
      return node;
    }
  case andI_reg_reg_rule: {
      andI_reg_regNode *node = new andI_reg_regNode();
      return node;
    }
  case andI_Reg_mem_rule: {
      andI_Reg_memNode *node = new andI_Reg_memNode();
      return node;
    }
  case andI_Reg_mem_0_rule: {
      andI_Reg_mem_0Node *node = new andI_Reg_mem_0Node();
      return node;
    }
  case andI_reg_uimm32_rule: {
      andI_reg_uimm32Node *node = new andI_reg_uimm32Node();
      return node;
    }
  case andI_reg_uimmI_LH1_rule: {
      andI_reg_uimmI_LH1Node *node = new andI_reg_uimmI_LH1Node();
      return node;
    }
  case andI_reg_uimmI_LL1_rule: {
      andI_reg_uimmI_LL1Node *node = new andI_reg_uimmI_LL1Node();
      return node;
    }
  case andL_reg_reg_rule: {
      andL_reg_regNode *node = new andL_reg_regNode();
      return node;
    }
  case andL_Reg_mem_rule: {
      andL_Reg_memNode *node = new andL_Reg_memNode();
      return node;
    }
  case andL_Reg_mem_0_rule: {
      andL_Reg_mem_0Node *node = new andL_Reg_mem_0Node();
      return node;
    }
  case andL_reg_uimmL_LL1_rule: {
      andL_reg_uimmL_LL1Node *node = new andL_reg_uimmL_LL1Node();
      return node;
    }
  case andL_reg_uimmL_LH1_rule: {
      andL_reg_uimmL_LH1Node *node = new andL_reg_uimmL_LH1Node();
      return node;
    }
  case andL_reg_uimmL_HL1_rule: {
      andL_reg_uimmL_HL1Node *node = new andL_reg_uimmL_HL1Node();
      return node;
    }
  case andL_reg_uimmL_HH1_rule: {
      andL_reg_uimmL_HH1Node *node = new andL_reg_uimmL_HH1Node();
      return node;
    }
  case orI_reg_reg_rule: {
      orI_reg_regNode *node = new orI_reg_regNode();
      return node;
    }
  case orI_Reg_mem_rule: {
      orI_Reg_memNode *node = new orI_Reg_memNode();
      return node;
    }
  case orI_Reg_mem_0_rule: {
      orI_Reg_mem_0Node *node = new orI_Reg_mem_0Node();
      return node;
    }
  case orI_reg_uimm16_rule: {
      orI_reg_uimm16Node *node = new orI_reg_uimm16Node();
      return node;
    }
  case orI_reg_uimm32_rule: {
      orI_reg_uimm32Node *node = new orI_reg_uimm32Node();
      return node;
    }
  case orL_reg_reg_rule: {
      orL_reg_regNode *node = new orL_reg_regNode();
      return node;
    }
  case orL_Reg_mem_rule: {
      orL_Reg_memNode *node = new orL_Reg_memNode();
      return node;
    }
  case orL_Reg_mem_0_rule: {
      orL_Reg_mem_0Node *node = new orL_Reg_mem_0Node();
      return node;
    }
  case orL_reg_uimm16_rule: {
      orL_reg_uimm16Node *node = new orL_reg_uimm16Node();
      return node;
    }
  case orL_reg_uimm32_rule: {
      orL_reg_uimm32Node *node = new orL_reg_uimm32Node();
      return node;
    }
  case xorI_reg_reg_rule: {
      xorI_reg_regNode *node = new xorI_reg_regNode();
      return node;
    }
  case xorI_Reg_mem_rule: {
      xorI_Reg_memNode *node = new xorI_Reg_memNode();
      return node;
    }
  case xorI_Reg_mem_0_rule: {
      xorI_Reg_mem_0Node *node = new xorI_Reg_mem_0Node();
      return node;
    }
  case xorI_reg_uimm32_rule: {
      xorI_reg_uimm32Node *node = new xorI_reg_uimm32Node();
      return node;
    }
  case xorL_reg_reg_rule: {
      xorL_reg_regNode *node = new xorL_reg_regNode();
      return node;
    }
  case xorL_Reg_mem_rule: {
      xorL_Reg_memNode *node = new xorL_Reg_memNode();
      return node;
    }
  case xorL_Reg_mem_0_rule: {
      xorL_Reg_mem_0Node *node = new xorL_Reg_mem_0Node();
      return node;
    }
  case xorL_reg_uimm32_rule: {
      xorL_reg_uimm32Node *node = new xorL_reg_uimm32Node();
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
  case cmpLTMask_reg_reg_rule: {
      cmpLTMask_reg_regNode *node = new cmpLTMask_reg_regNode();
      return node;
    }
  case cmpLTMask_reg_zero_rule: {
      cmpLTMask_reg_zeroNode *node = new cmpLTMask_reg_zeroNode();
      return node;
    }
  case convD2F_reg_rule: {
      convD2F_regNode *node = new convD2F_regNode();
      return node;
    }
  case convF2I_reg_rule: {
      convF2I_regNode *node = new convF2I_regNode();
      return node;
    }
  case convD2I_reg_rule: {
      convD2I_regNode *node = new convD2I_regNode();
      return node;
    }
  case convF2L_reg_rule: {
      convF2L_regNode *node = new convF2L_regNode();
      return node;
    }
  case convD2L_reg_rule: {
      convD2L_regNode *node = new convD2L_regNode();
      return node;
    }
  case convF2D_reg_rule: {
      convF2D_regNode *node = new convF2D_regNode();
      return node;
    }
  case convF2D_mem_rule: {
      convF2D_memNode *node = new convF2D_memNode();
      return node;
    }
  case convI2D_reg_rule: {
      convI2D_regNode *node = new convI2D_regNode();
      return node;
    }
  case convI2F_ireg_rule: {
      convI2F_iregNode *node = new convI2F_iregNode();
      return node;
    }
  case convI2L_reg_rule: {
      convI2L_regNode *node = new convI2L_regNode();
      return node;
    }
  case convI2L_reg_zex_rule: {
      convI2L_reg_zexNode *node = new convI2L_reg_zexNode();
      return node;
    }
  case convI2L_mem_zex_rule: {
      convI2L_mem_zexNode *node = new convI2L_mem_zexNode();
      return node;
    }
  case zeroExtend_long_rule: {
      zeroExtend_longNode *node = new zeroExtend_longNode();
      return node;
    }
  case rShiftI16_lShiftI16_reg_rule: {
      rShiftI16_lShiftI16_regNode *node = new rShiftI16_lShiftI16_regNode();
      return node;
    }
  case rShiftI24_lShiftI24_reg_rule: {
      rShiftI24_lShiftI24_regNode *node = new rShiftI24_lShiftI24_regNode();
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
  case convL2F_reg_rule: {
      convL2F_regNode *node = new convL2F_regNode();
      return node;
    }
  case convL2D_reg_rule: {
      convL2D_regNode *node = new convL2D_regNode();
      return node;
    }
  case convL2I_reg_rule: {
      convL2I_regNode *node = new convL2I_regNode();
      return node;
    }
  case shrL_reg_imm6_L2I_rule: {
      shrL_reg_imm6_L2INode *node = new shrL_reg_imm6_L2INode();
      return node;
    }
  case rangeCheck_iReg_uimmI16_rule: {
      rangeCheck_iReg_uimmI16Node *node = new rangeCheck_iReg_uimmI16Node();
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
  case rangeCheck_uimmI16_iReg_rule: {
      rangeCheck_uimmI16_iRegNode *node = new rangeCheck_uimmI16_iRegNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case zeroCheckP_iReg_imm0_rule: {
      zeroCheckP_iReg_imm0Node *node = new zeroCheckP_iReg_imm0Node();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case zeroCheckN_iReg_imm0_rule: {
      zeroCheckN_iReg_imm0Node *node = new zeroCheckN_iReg_imm0Node();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case compI_reg_reg_rule: {
      compI_reg_regNode *node = new compI_reg_regNode();
      return node;
    }
  case compI_reg_imm_rule: {
      compI_reg_immNode *node = new compI_reg_immNode();
      return node;
    }
  case compI_reg_imm16_rule: {
      compI_reg_imm16Node *node = new compI_reg_imm16Node();
      return node;
    }
  case compI_reg_imm0_rule: {
      compI_reg_imm0Node *node = new compI_reg_imm0Node();
      return node;
    }
  case compI_reg_mem_rule: {
      compI_reg_memNode *node = new compI_reg_memNode();
      return node;
    }
  case compU_reg_reg_rule: {
      compU_reg_regNode *node = new compU_reg_regNode();
      return node;
    }
  case compU_reg_uimm_rule: {
      compU_reg_uimmNode *node = new compU_reg_uimmNode();
      return node;
    }
  case compU_reg_mem_rule: {
      compU_reg_memNode *node = new compU_reg_memNode();
      return node;
    }
  case compL_reg_reg_rule: {
      compL_reg_regNode *node = new compL_reg_regNode();
      return node;
    }
  case compL_reg_regI_rule: {
      compL_reg_regINode *node = new compL_reg_regINode();
      return node;
    }
  case compL_reg_imm32_rule: {
      compL_reg_imm32Node *node = new compL_reg_imm32Node();
      return node;
    }
  case compL_reg_imm16_rule: {
      compL_reg_imm16Node *node = new compL_reg_imm16Node();
      return node;
    }
  case compL_reg_imm0_rule: {
      compL_reg_imm0Node *node = new compL_reg_imm0Node();
      return node;
    }
  case compL_conv_reg_imm0_rule: {
      compL_conv_reg_imm0Node *node = new compL_conv_reg_imm0Node();
      return node;
    }
  case compL_reg_mem_rule: {
      compL_reg_memNode *node = new compL_reg_memNode();
      return node;
    }
  case compL_reg_memI_rule: {
      compL_reg_memINode *node = new compL_reg_memINode();
      return node;
    }
  case compUL_reg_reg_rule: {
      compUL_reg_regNode *node = new compUL_reg_regNode();
      return node;
    }
  case compUL_reg_imm32_rule: {
      compUL_reg_imm32Node *node = new compUL_reg_imm32Node();
      return node;
    }
  case compP_reg_reg_rule: {
      compP_reg_regNode *node = new compP_reg_regNode();
      return node;
    }
  case compP_reg_imm0_rule: {
      compP_reg_imm0Node *node = new compP_reg_imm0Node();
      return node;
    }
  case compP_decode_reg_imm0_rule: {
      compP_decode_reg_imm0Node *node = new compP_decode_reg_imm0Node();
      return node;
    }
  case compP_reg_mem_rule: {
      compP_reg_memNode *node = new compP_reg_memNode();
      return node;
    }
  case z196_minI_reg_reg_rule: {
      z196_minI_reg_regNode *node = new z196_minI_reg_regNode();
      return node;
    }
  case z10_minI_reg_reg_rule: {
      z10_minI_reg_regNode *node = new z10_minI_reg_regNode();
      return node;
    }
  case minI_reg_reg_rule: {
      minI_reg_regNode *node = new minI_reg_regNode();
      return node;
    }
  case z196_minI_reg_imm32_rule: {
      z196_minI_reg_imm32Node *node = new z196_minI_reg_imm32Node();
      return node;
    }
  case minI_reg_imm32_rule: {
      minI_reg_imm32Node *node = new minI_reg_imm32Node();
      return node;
    }
  case z196_minI_reg_imm16_rule: {
      z196_minI_reg_imm16Node *node = new z196_minI_reg_imm16Node();
      return node;
    }
  case minI_reg_imm16_rule: {
      minI_reg_imm16Node *node = new minI_reg_imm16Node();
      return node;
    }
  case z10_minI_reg_imm8_rule: {
      z10_minI_reg_imm8Node *node = new z10_minI_reg_imm8Node();
      return node;
    }
  case z196_maxI_reg_reg_rule: {
      z196_maxI_reg_regNode *node = new z196_maxI_reg_regNode();
      return node;
    }
  case z10_maxI_reg_reg_rule: {
      z10_maxI_reg_regNode *node = new z10_maxI_reg_regNode();
      return node;
    }
  case maxI_reg_reg_rule: {
      maxI_reg_regNode *node = new maxI_reg_regNode();
      return node;
    }
  case z196_maxI_reg_imm32_rule: {
      z196_maxI_reg_imm32Node *node = new z196_maxI_reg_imm32Node();
      return node;
    }
  case maxI_reg_imm32_rule: {
      maxI_reg_imm32Node *node = new maxI_reg_imm32Node();
      return node;
    }
  case z196_maxI_reg_imm16_rule: {
      z196_maxI_reg_imm16Node *node = new z196_maxI_reg_imm16Node();
      return node;
    }
  case maxI_reg_imm16_rule: {
      maxI_reg_imm16Node *node = new maxI_reg_imm16Node();
      return node;
    }
  case z10_maxI_reg_imm8_rule: {
      z10_maxI_reg_imm8Node *node = new z10_maxI_reg_imm8Node();
      return node;
    }
  case absI_reg_rule: {
      absI_regNode *node = new absI_regNode();
      return node;
    }
  case negabsI_reg_rule: {
      negabsI_regNode *node = new negabsI_regNode();
      return node;
    }
  case cmpF_cc_rule: {
      cmpF_ccNode *node = new cmpF_ccNode();
      return node;
    }
  case cmpD_cc_rule: {
      cmpD_ccNode *node = new cmpD_ccNode();
      return node;
    }
  case cmpF_cc_mem_rule: {
      cmpF_cc_memNode *node = new cmpF_cc_memNode();
      return node;
    }
  case cmpD_cc_mem_rule: {
      cmpD_cc_memNode *node = new cmpD_cc_memNode();
      return node;
    }
  case cmpF0_cc_rule: {
      cmpF0_ccNode *node = new cmpF0_ccNode();
      return node;
    }
  case cmpD0_cc_rule: {
      cmpD0_ccNode *node = new cmpD0_ccNode();
      return node;
    }
  case cmpF_reg_rule: {
      cmpF_regNode *node = new cmpF_regNode();
      return node;
    }
  case cmpD_reg_rule: {
      cmpD_regNode *node = new cmpD_regNode();
      return node;
    }
  case branch_rule: {
      branchNode *node = new branchNode();
      node->set_opnd_array(1, MachOperGenerator(LABEL));
      return node;
    }
  case branchFar_rule: {
      branchFarNode *node = new branchFarNode();
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
  case testAndBranchLoopEnd_Reg_rule: {
      testAndBranchLoopEnd_RegNode *node = new testAndBranchLoopEnd_RegNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegI_rule: {
      cmpb_RegINode *node = new cmpb_RegINode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpbU_RegI_rule: {
      cmpbU_RegINode *node = new cmpbU_RegINode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegL_rule: {
      cmpb_RegLNode *node = new cmpb_RegLNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegPP_rule: {
      cmpb_RegPPNode *node = new cmpb_RegPPNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegNN_rule: {
      cmpb_RegNNNode *node = new cmpb_RegNNNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case testAndBranchLoopEnd_Imm_rule: {
      testAndBranchLoopEnd_ImmNode *node = new testAndBranchLoopEnd_ImmNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegI_imm_rule: {
      cmpb_RegI_immNode *node = new cmpb_RegI_immNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpbU_RegI_imm_rule: {
      cmpbU_RegI_immNode *node = new cmpbU_RegI_immNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegL_imm_rule: {
      cmpb_RegL_immNode *node = new cmpb_RegL_immNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegP_immP_rule: {
      cmpb_RegP_immPNode *node = new cmpb_RegP_immPNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegN_immP0_rule: {
      cmpb_RegN_immP0Node *node = new cmpb_RegN_immP0Node();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegN_imm_rule: {
      cmpb_RegN_immNode *node = new cmpb_RegN_immNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case testAndBranchLoopEnd_RegFar_rule: {
      testAndBranchLoopEnd_RegFarNode *node = new testAndBranchLoopEnd_RegFarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegI_Far_rule: {
      cmpb_RegI_FarNode *node = new cmpb_RegI_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpbU_RegI_Far_rule: {
      cmpbU_RegI_FarNode *node = new cmpbU_RegI_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegL_Far_rule: {
      cmpb_RegL_FarNode *node = new cmpb_RegL_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegPP_Far_rule: {
      cmpb_RegPP_FarNode *node = new cmpb_RegPP_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegNN_Far_rule: {
      cmpb_RegNN_FarNode *node = new cmpb_RegNN_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case testAndBranchLoopEnd_ImmFar_rule: {
      testAndBranchLoopEnd_ImmFarNode *node = new testAndBranchLoopEnd_ImmFarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegI_imm_Far_rule: {
      cmpb_RegI_imm_FarNode *node = new cmpb_RegI_imm_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpbU_RegI_imm_Far_rule: {
      cmpbU_RegI_imm_FarNode *node = new cmpbU_RegI_imm_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegL_imm_Far_rule: {
      cmpb_RegL_imm_FarNode *node = new cmpb_RegL_imm_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegP_immP_Far_rule: {
      cmpb_RegP_immP_FarNode *node = new cmpb_RegP_immP_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegN_immP0_Far_rule: {
      cmpb_RegN_immP0_FarNode *node = new cmpb_RegN_immP0_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpb_RegN_immN_Far_rule: {
      cmpb_RegN_immN_FarNode *node = new cmpb_RegN_immN_FarNode();
      node->set_opnd_array(4, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpL3_reg_reg_rule: {
      cmpL3_reg_regNode *node = new cmpL3_reg_regNode();
      return node;
    }
  case safePoint_rule: {
      safePointNode *node = new safePointNode();
      return node;
    }
  case safePoint_poll_rule: {
      safePoint_pollNode *node = new safePoint_pollNode();
      return node;
    }
  case CallStaticJavaDirect_dynTOC_rule: {
      CallStaticJavaDirect_dynTOCNode *node = new CallStaticJavaDirect_dynTOCNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallDynamicJavaDirect_dynTOC_rule: {
      CallDynamicJavaDirect_dynTOCNode *node = new CallDynamicJavaDirect_dynTOCNode();
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
      return node;
    }
  case partialSubtypeCheck_rule: {
      partialSubtypeCheckNode *node = new partialSubtypeCheckNode();
      return node;
    }
  case partialSubtypeCheck_vs_zero_rule: {
      partialSubtypeCheck_vs_zeroNode *node = new partialSubtypeCheck_vs_zeroNode();
      return node;
    }
  case cmpFastLock_rule: {
      cmpFastLockNode *node = new cmpFastLockNode();
      node->set_opnd_array(3, MachOperGenerator(IREGP));
      node->set_opnd_array(4, MachOperGenerator(IREGP));
      node->_counters = _leaf->as_FastLock()->counters();
      node->_rtm_counters = _leaf->as_FastLock()->rtm_counters();
      node->_stack_rtm_counters = _leaf->as_FastLock()->stack_rtm_counters();
      return node;
    }
  case cmpFastUnlock_rule: {
      cmpFastUnlockNode *node = new cmpFastUnlockNode();
      node->set_opnd_array(3, MachOperGenerator(IREGP));
      node->set_opnd_array(4, MachOperGenerator(IREGP));
      return node;
    }
  case inlineCallClearArrayConst_rule: {
      inlineCallClearArrayConstNode *node = new inlineCallClearArrayConstNode();
      return node;
    }
  case inlineCallClearArrayConstBig_rule: {
      inlineCallClearArrayConstBigNode *node = new inlineCallClearArrayConstBigNode();
      node->set_opnd_array(3, MachOperGenerator(REVENREGL));
      node->set_opnd_array(4, MachOperGenerator(RODDREGL));
      return node;
    }
  case inlineCallClearArray_rule: {
      inlineCallClearArrayNode *node = new inlineCallClearArrayNode();
      node->set_opnd_array(3, MachOperGenerator(REVENREGL));
      node->set_opnd_array(4, MachOperGenerator(RODDREGL));
      return node;
    }
  case string_equalsL_rule: {
      string_equalsLNode *node = new string_equalsLNode();
      node->set_opnd_array(4, MachOperGenerator(RODDREGL));
      node->set_opnd_array(5, MachOperGenerator(REVENREGL));
      return node;
    }
  case string_equalsU_rule: {
      string_equalsUNode *node = new string_equalsUNode();
      node->set_opnd_array(4, MachOperGenerator(RODDREGL));
      node->set_opnd_array(5, MachOperGenerator(REVENREGL));
      return node;
    }
  case string_equals_imm_rule: {
      string_equals_immNode *node = new string_equals_immNode();
      return node;
    }
  case string_equalsC_imm_rule: {
      string_equalsC_immNode *node = new string_equalsC_immNode();
      return node;
    }
  case array_equalsB_rule: {
      array_equalsBNode *node = new array_equalsBNode();
      node->set_opnd_array(3, MachOperGenerator(RODDREGL));
      node->set_opnd_array(4, MachOperGenerator(REVENREGL));
      return node;
    }
  case array_equalsC_rule: {
      array_equalsCNode *node = new array_equalsCNode();
      node->set_opnd_array(3, MachOperGenerator(RODDREGL));
      node->set_opnd_array(4, MachOperGenerator(REVENREGL));
      return node;
    }
  case string_compareL_rule: {
      string_compareLNode *node = new string_compareLNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case string_compareU_rule: {
      string_compareUNode *node = new string_compareUNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case string_compareLU_rule: {
      string_compareLUNode *node = new string_compareLUNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case string_compareUL_rule: {
      string_compareULNode *node = new string_compareULNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case indexOfChar_U_rule: {
      indexOfChar_UNode *node = new indexOfChar_UNode();
      node->set_opnd_array(4, MachOperGenerator(IREGI));
      node->set_opnd_array(5, MachOperGenerator(RODDREGL));
      node->set_opnd_array(6, MachOperGenerator(REVENREGL));
      return node;
    }
  case indexOf_imm1_U_rule: {
      indexOf_imm1_UNode *node = new indexOf_imm1_UNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case indexOf_imm1_L_rule: {
      indexOf_imm1_LNode *node = new indexOf_imm1_LNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case indexOf_imm1_UL_rule: {
      indexOf_imm1_ULNode *node = new indexOf_imm1_ULNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case indexOf_imm_U_rule: {
      indexOf_imm_UNode *node = new indexOf_imm_UNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case indexOf_imm_L_rule: {
      indexOf_imm_LNode *node = new indexOf_imm_LNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case indexOf_imm_UL_rule: {
      indexOf_imm_ULNode *node = new indexOf_imm_ULNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case indexOf_U_rule: {
      indexOf_UNode *node = new indexOf_UNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case indexOf_L_rule: {
      indexOf_LNode *node = new indexOf_LNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case indexOf_UL_rule: {
      indexOf_ULNode *node = new indexOf_ULNode();
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      node->set_opnd_array(6, MachOperGenerator(RODDREGL));
      node->set_opnd_array(7, MachOperGenerator(REVENREGL));
      return node;
    }
  case string_compress_rule: {
      string_compressNode *node = new string_compressNode();
      node->set_opnd_array(4, MachOperGenerator(IREGI));
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      return node;
    }
  case string_inflate_rule: {
      string_inflateNode *node = new string_inflateNode();
      node->set_opnd_array(4, MachOperGenerator(IREGI));
      return node;
    }
  case string_inflate_const_rule: {
      string_inflate_constNode *node = new string_inflate_constNode();
      node->set_opnd_array(4, MachOperGenerator(IREGI));
      return node;
    }
  case has_negatives_rule: {
      has_negativesNode *node = new has_negativesNode();
      node->set_opnd_array(3, MachOperGenerator(IREGI));
      node->set_opnd_array(4, MachOperGenerator(RODDREGI));
      node->set_opnd_array(5, MachOperGenerator(REVENREGI));
      node->set_opnd_array(6, MachOperGenerator(IREGI));
      return node;
    }
  case encode_iso_array_rule: {
      encode_iso_arrayNode *node = new encode_iso_arrayNode();
      node->set_opnd_array(4, MachOperGenerator(IREGI));
      node->set_opnd_array(5, MachOperGenerator(IREGI));
      return node;
    }
  case expand_Repl2I_reg_rule: {
      expand_Repl2I_regNode *node = new expand_Repl2I_regNode();
      return node;
    }
  case Repl8B_reg_risbg_rule: {
      Repl8B_reg_risbgNode *node = new Repl8B_reg_risbgNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8B_imm_rule: {
      Repl8B_immNode *node = new Repl8B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8B_imm0_rule: {
      Repl8B_imm0Node *node = new Repl8B_imm0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8B_immm1_rule: {
      Repl8B_immm1Node *node = new Repl8B_immm1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4S_reg_risbg_rule: {
      Repl4S_reg_risbgNode *node = new Repl4S_reg_risbgNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4S_imm_rule: {
      Repl4S_immNode *node = new Repl4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4S_imm0_rule: {
      Repl4S_imm0Node *node = new Repl4S_imm0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4S_immm1_rule: {
      Repl4S_immm1Node *node = new Repl4S_immm1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2I_reg_risbg_rule: {
      Repl2I_reg_risbgNode *node = new Repl2I_reg_risbgNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2I_imm_rule: {
      Repl2I_immNode *node = new Repl2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2I_imm0_rule: {
      Repl2I_imm0Node *node = new Repl2I_imm0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2I_immm1_rule: {
      Repl2I_immm1Node *node = new Repl2I_immm1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2F_reg_indirect_rule: {
      Repl2F_reg_indirectNode *node = new Repl2F_reg_indirectNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2F_reg_direct_rule: {
      Repl2F_reg_directNode *node = new Repl2F_reg_directNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2F_imm_rule: {
      Repl2F_immNode *node = new Repl2F_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2F_imm0_rule: {
      Repl2F_imm0Node *node = new Repl2F_imm0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeA8B_rule: {
      storeA8BNode *node = new storeA8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV8_rule: {
      loadV8Node *node = new loadV8Node();
      node->_bottom_type = _leaf->bottom_type();
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
      node->set_opnd_array(2, MachOperGenerator(REVENREGI));
      node->set_opnd_array(3, MachOperGenerator(RODDREGI));
      return node;
    }
  case countTrailingZerosL_rule: {
      countTrailingZerosLNode *node = new countTrailingZerosLNode();
      node->set_opnd_array(2, MachOperGenerator(REVENREGI));
      return node;
    }
  case popCountI_rule: {
      popCountINode *node = new popCountINode();
      node->set_opnd_array(2, MachOperGenerator(IREGI));
      node->set_opnd_array(3, MachOperGenerator(IREGI));
      return node;
    }
  case popCountL_rule: {
      popCountLNode *node = new popCountLNode();
      node->set_opnd_array(2, MachOperGenerator(IREGI));
      node->set_opnd_array(3, MachOperGenerator(IREGL));
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
// Check adlc -DS390=1
#ifndef S390
#  error "S390 must be defined"
#endif // S390
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
